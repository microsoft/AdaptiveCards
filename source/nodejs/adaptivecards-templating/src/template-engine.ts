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
    private static processPathValue(path: string, value: any): string {
        let substitutionValue: string | undefined = undefined;

        if (GlobalSettings.getUndefinedFieldValueSubstitutionString) {
            substitutionValue = GlobalSettings.getUndefinedFieldValueSubstitutionString(path);    
        }

        return substitutionValue ? substitutionValue : "${" + path + "}";
    }

    private _memory: AEL.MemoryInterface;

    $root: any;
    $data: any;
    $index: any;

    constructor() {
        this._memory = new AEL.SimpleObjectMemory(this);
    }

    getValue(path: string): any {
        let actualPath = (path.length > 0 && path[0] !== "$") ? "$data." + path : path;

        let value = this._memory.getValue(actualPath);

        if (value === undefined) {
            value = TemplateObjectMemory.processPathValue(path, value);
        }

        return value;
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
            let regExp = /\${([^}]*)}/g;
            let matches: RegExpExecArray = null;
            let lastMatch: RegExpExecArray;
            let matchCount = 0;

            // Determine if the string contains any ${<expression>}
            while (matchCount <= 1 && (matches = regExp.exec(node)) != null) {
                lastMatch = matches;

                matchCount++;
            };

            // If there are none, it's just a string
            if (matchCount === 0) {
                return node;
            }
            // If the entire string is enclosed in a single ${}, extract the enclosed expression
            else if (matchCount === 1 && lastMatch[0].length === node.length) {
                return AEL.Expression.parse(lastMatch[1]);
            }

            // Otherwise, it's an interpolated string with multiple embedded expressions
            return AEL.Expression.parse("`" + node + "`");
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

    private createEvaluationState(): TemplateObjectMemory {
        let memory = new TemplateObjectMemory();
        memory.$root = this._context.$root;
        memory.$data = this._context.$data;
        memory.$index = this._context.$index;

        return memory;
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
            let evaluationResult = node.tryEvaluate(this.createEvaluationState());

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
                let evaluationResult = when.tryEvaluate(this.createEvaluationState());
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
                        let evaluationResult = dataContext.tryEvaluate(this.createEvaluationState());

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