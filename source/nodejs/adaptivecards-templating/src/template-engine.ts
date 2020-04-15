// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as AEL from "adaptive-expressions";

class EvaluationContext {
    private static readonly _reservedFields = ["$data", "$root", "$index"];

    private _stateStack: Array<{ $data: any, $index: any }> = [];
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

class TemplateObjectMemory implements AEL.MemoryInterface {
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

/***
 * Holds global settings that can be used to customize the way templates are expanded.
 */
export class GlobalSettings {
    /**
     * Callback invoked when expression evaluation needs the value of a field in the source data object
     * and that field is undefined or null. By default, expression evaluation will substitute an undefined
     * field with its binding expression (e.g. `${field}`). This callback makes it possible to customize that
     * behavior.
     * 
     * **Example**
     * Given this data object:
     * 
     * ```json
     * {
     *     firstName: "David"
     * }
     * ```
     * 
     * The expression `${firstName} ${lastName}` will evaluate to "David ${lastName}" because the `lastName`
     * field is undefined.
     * 
     * Now let's set the callback:
     * ```typescript
     * GlobalSettings.getUndefinedFieldValueSubstitutionString = (path: string) => { return "<undefined value>"; }
     * ```
     * 
     * With that, the above expression will evaluate to "David <undefined value>"
     */
    static getUndefinedFieldValueSubstitutionString?: (path: string) => string | undefined = undefined;
}

/**
 * Holds the context used to expand a template.
 */
export interface IEvaluationContext {
    /**
     * The root data object the template will bind to. Expressions that refer to $root in the template payload
     * map to this field. Initially, $data also maps to $root.
     */
    $root: any
}

/**
 * Represents a template that can be bound to data.
 */
export class Template {
    private static prepare(node: any): any {
        if (typeof node === "string") {
            let regExp = /\${([^}]*)}/g;
            let matches: RegExpExecArray = null;
            let lastMatch: RegExpExecArray;
            let matchCount = 0;

            // Determine if the string contains any ${<expression>}
            while (matchCount <= 1 && (matches = regExp.exec(node)) != null) {
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
                return node;
            }
            // If the entire string is enclosed in a single ${}, extract the enclosed expression
            else if (matchCount === 1 && lastMatch[0].length === node.length) {
                return AEL.Expression.parse(lastMatch[1], lookup);
            }

            // Otherwise, it's an interpolated string with multiple embedded expressions
            return AEL.Expression.parse("`" + node + "`", lookup);
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

    private _context: EvaluationContext;
    private _preparedPayload: any;

    private tryEvaluateExpression(expression: AEL.Expression, allowSubstitutions: boolean): { value: any; error: string } {
        let memory = new TemplateObjectMemory();
        memory.$root = this._context.$root;
        memory.$data = this._context.$data;
        memory.$index = this._context.$index;

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
            let evaluationResult = this.tryEvaluateExpression(node, true);

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
                let evaluationResult = this.tryEvaluateExpression(when, false);
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
                        let evaluationResult = this.tryEvaluateExpression(dataContext, true);

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

    /**
     * Initializes a new Template instance based on the provided payload.
     * Once created, the instance can be bound to different data objects
     * in a loop.
     * 
     * @param payload The template payload.  
     */
    constructor(payload: any) {
        this._preparedPayload = Template.prepare(payload);
    }

    /**
     * Expands the template using the provided context. Template expansion involves
     * evaluating the expressions used in the original template payload, as well as
     * repeating (expanding) parts of the original payload when those parts are bound
     * to array fields.
     * 
     * Example:
     * 
     * ```
     * let context = {
     *     $root: {
     *         firstName: "John",
     *         lastName: "Doe",
     *         children: [
     *             { fullName: "Jane Doe", age: 9 },
     *             { fullName: "Alex Doe", age: 12 }
     *         ]
     *     }
     * }
     * 
     * let templatePayload = {
     *     type: "AdaptiveCard",
     *     version: "1.2",
     *     body: [
     *         {
     *             type: "TextBlock",
     *             text: "${firstName} ${lastName}"
     *         },
     *         {
     *             type: "TextBlock",
     *             $data: "${children}",
     *             text: "${fullName} (${age})"
     *         }
     *     ]
     * }
     * 
     * let template = new Template(templatePayload);
     * 
     * let expandedTemplate = template.expand(context);
     * ```
     * 
     * With the above code, the value of `expandedTemplate` will be
     * 
     * ```
     * {
     *     type: "AdaptiveCard",
     *     version: "1.2",
     *     body: [
     *         {
     *             type: "TextBlock",
     *             text: "John Doe"
     *         },
     *         {
     *             type: "TextBlock",
     *             text: "Jane Doe (9)"
     *         },
     *         {
     *             type: "TextBlock",
     *             text: "Alex Doe (12)"
     *         }
     *     ]
     * }
     * ```
     * 
     * @param context The context to bind the template to. 
     */
    expand(context: IEvaluationContext): any {
        this._context = new EvaluationContext();
        this._context.$root = context.$root;

        return this.internalExpand(this._preparedPayload);
    }
}