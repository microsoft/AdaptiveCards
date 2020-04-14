// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as AEL from "adaptive-expressions";

export class GlobalSettings {
    static getUndefinedFieldValueSubstitutionString?: (path: string) => string | undefined = undefined;
}

interface EvaluationContextState {
    $data: any;
    $index: any;
}

export class EvaluationContext {
    private static readonly _reservedFields = ["$data", "$root", "$index"];

    private _stateStack: EvaluationContextState[] = [];
    private _$data: any;

    $root: any;
    $index: number;

    isReservedField(name: string): boolean {
        return EvaluationContext._reservedFields.indexOf(name) >= 0;
    }

    saveState() {
        this._stateStack.push(
            {
                $data: this.$data,
                $index: this.$index
            });
    }

    restoreLastState() {
        if (this._stateStack.length === 0) {
            throw new Error("There is no evaluation context state to restore.");
        }

        let savedContext = this._stateStack.pop();

        this.$data = savedContext.$data;
        this.$index = savedContext.$index;
    }

    get $data(): any {
        return this._$data !== undefined ? this._$data : this.$root;
    }

    set $data(value: any) {
        this._$data = value;
    }
}

export class TemplateObjectMemory implements AEL.MemoryInterface {
    private _memory: AEL.MemoryInterface;

    $root: any;
    $data: any;
    $index: any;

    constructor() {
        this._memory = new AEL.SimpleObjectMemory(this);
    }

    getValue(path: string): any {
        let actualPath = (path.length > 0 && path[0] !== "$") ? "$data." + path : path;

        return this._memory.getValue(actualPath);
    }

    setValue(path: string, input: any) {
        this._memory.setValue(path, input);
    }

    version(): string {
        return this._memory.version();
    }
}

export class Template {
    private static prepare(node: any): any {
        if (typeof node === "string") {
            return Template.parseExpression(node);
        }
        else if (typeof node === "object" && node !== null) {
            if (Array.isArray(node)) {
                let result: any[] = [];

                for (let item of node) {
                    result.push(Template.prepare(item));
                }

                return result;
            }
            else {
                let keys = Object.keys(node);
                let result = {};

                for (let key of keys) {
                    result[key] = Template.prepare(node[key]);
                }

                return result;
            }
        }
        else {
            return node;
        }
    }

    public static parseExpression(expression: string): AEL.Expression | string {
        let regExp = /\${([^}]*)}/g;
        let matches: RegExpExecArray = null;
        let lastMatch: RegExpExecArray;
        let matchCount = 0;

        // Determine if the string contains any ${<expression>}
        while (matchCount <= 1 && (matches = regExp.exec(expression)) != null) {
            lastMatch = matches;

            matchCount++;
        };

        let lookup: AEL.EvaluatorLookup = (type: string) => {
            let standardFunction = AEL.ExpressionFunctions.standardFunctions.get(type);

            if (standardFunction) {
                return standardFunction;
            }
            else {
                return new AEL.ExpressionEvaluator(
                    type,
                    (expression: AEL.Expression, state: AEL.MemoryInterface, options: AEL.Options) => { throw new Error("Unknown function " + type); },
                    AEL.ReturnType.String);
            }
        }

        // If there are none, it's just a string
        if (matchCount === 0) {
            return expression;
        }
        // If the entire string is enclosed in a single ${}, extract the enclosed expression
        else if (matchCount === 1 && lastMatch[0].length === expression.length) {
            return AEL.Expression.parse(lastMatch[1], lookup);
        }

        // Otherwise, it's an interpolated string with multiple embedded expressions
        return AEL.Expression.parse("`" + expression + "`", lookup);
    }

    public static tryEvaluateExpression(expression: AEL.Expression, context: EvaluationContext, allowSubstitutions: boolean): { value: any; error: string } {
        let memory = new TemplateObjectMemory();
        memory.$root = context.$root;
        memory.$data = context.$data;
        memory.$index = context.$index;

        let options: AEL.Options | undefined = undefined;

        if (allowSubstitutions) {
            options = new AEL.Options();
            options.nullSubstitution = (path: string) => {
                let substitutionValue: string | undefined = undefined;

                if (GlobalSettings.getUndefinedFieldValueSubstitutionString) {
                    substitutionValue = GlobalSettings.getUndefinedFieldValueSubstitutionString(path);    
                }
        
                return substitutionValue ? substitutionValue : "${" + path + "}";
            }
        }

        // The root of an expression coming from an interpolated string is of type Concat.
        // In that case, and if the caller allows it, we're doing our own concatenation
        // in order to catch each individual expression evaluation error and substitute in
        // the final string
        if (expression.type === AEL.ExpressionType.Concat && allowSubstitutions) {
            let result = "";

            for (let childExpression of expression.children) {
                let evaluationResult: { value: any; error: string };
                
                try {
                    evaluationResult = childExpression.tryEvaluate(memory, options);
                }
                catch (ex) {
                    // We'll swallow all exceptions here
                    evaluationResult = {
                        value: "${" + childExpression.toString() + "}",
                        error: ex
                    };
                }

                result += evaluationResult.value.toString();
            }

            return { value: result, error: undefined };
        }
        
        return expression.tryEvaluate(memory, options);
    }

    private _context: EvaluationContext;

    private expandSingleObject(node: object): any {
        let result = {};
        let keys = Object.keys(node);

        for (let key of keys) {
            if (!this._context.isReservedField(key)) {
                let value = this.internalExpand(node[key]);

                if (value !== undefined) {
                    result[key] = value;
                }
            }
        }

        return result;
    }

    private internalExpand(node: any): any {
        let result: any;

        this._context.saveState();

        if (Array.isArray(node)) {
            let itemArray: any[] = [];

            for (let item of node) {
                let expandedItem = this.internalExpand(item);

                if (expandedItem !== null) {
                    if (Array.isArray(expandedItem)) {
                        itemArray = itemArray.concat(expandedItem);
                    }
                    else {
                        itemArray.push(expandedItem);
                    }
                }
            }

            result = itemArray;
        }
        else if (node instanceof AEL.Expression) {
            let evaluationResult = Template.tryEvaluateExpression(node, this._context, true);

            if (!evaluationResult.error) {
                result = evaluationResult.value;
            }
            else {
                throw new Error(evaluationResult.error);
            }
        }
        else if (typeof node === "object" && node !== null) {
            let dropObject = false;
            let when = node["$when"];

            if (when instanceof AEL.Expression) {
                let evaluationResult = Template.tryEvaluateExpression(when, this._context, false);
                let whenValue: boolean = false;
                
                // If $when fails to evaluate or evaluates to anything but a boolean, consider it is false
                if (!evaluationResult.error) {
                    whenValue = typeof evaluationResult.value === "boolean" && evaluationResult.value;
                }
                dropObject = !whenValue;
            }

            if (!dropObject) {
                let dataContext = node["$data"];

                if (dataContext !== undefined) {
                    if (dataContext instanceof AEL.Expression) {
                        let evaluationResult = Template.tryEvaluateExpression(dataContext, this._context, true);

                        if (!evaluationResult.error) {
                            dataContext = evaluationResult.value;
                        }
                        else {
                            throw new Error(evaluationResult.error);
                        }
                    }

                    if (Array.isArray(dataContext)) {
                        result = [];

                        for (let i = 0; i < dataContext.length; i++) {
                            this._context.$data = dataContext[i];
                            this._context.$index = i;

                            let expandedObject = this.expandSingleObject(node);

                            if (expandedObject !== null) {
                                result.push(expandedObject);
                            }
                        }
                    }
                    else {
                        this._context.$data = dataContext;

                        result = this.expandSingleObject(node);
                    }
                }
                else {
                    result = this.expandSingleObject(node);
                }
            }
            else {
                result = null;
            }
        }
        else {
            result = node;
        }

        this._context.restoreLastState();

        return result;
    }

    preparedPayload: any;

    constructor(payload: any) {
        this.preparedPayload = Template.prepare(payload);
    }

    expand(context: EvaluationContext): any {
        this._context = context;

        return this.internalExpand(this.preparedPayload);
    }
}