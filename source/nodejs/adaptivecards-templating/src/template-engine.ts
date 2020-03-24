// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as CEL from "adaptive-expressions";

interface EvaluationContextState {
    $data: any;
    $index: any;
}

export class EvaluationContext {
    private static readonly _reservedFields = ["$data", "$root", "$index"];

    private _stateStack: EvaluationContextState[] = [];

    $root: any;
    $data: any;
    $index: number;
    // Below dummy propeties for testing purposes only
    // Will be removed once https://github.com/microsoft/botbuilder-dotnet/pull/3597 is merged
    stringProp: string = "It works";
    numberProp: number = 53;
    boolProp: boolean = true;
    arrayProp: any[] = [ "abc", 25, false ];

    isReservedField(name: string): boolean {
        return EvaluationContext._reservedFields.indexOf(name) >= 0;
    }

    saveState() {
        this._stateStack.push({ $data: this.$data, $index: this.$index });
    }

    restoreLastState() {
        if (this._stateStack.length === 0) {
            throw new Error("There is no evaluation context state to restore.");
        }

        let savedContext = this._stateStack.pop();

        this.$data = savedContext.$data;
        this.$index = savedContext.$index;
    }

    get currentDataContext(): any {
        return this.$data !== undefined ? this.$data : this.$root;
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
                return CEL.Expression.parse(lastMatch[1]);
            }

            // Otherwise, it's an interpolated string with multiple embedded expressions
            return CEL.Expression.parse("`" + node + "`");
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
        else if (node instanceof CEL.Expression) {
            let evaluationResult = node.tryEvaluate(this._context);

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

            if (when instanceof CEL.Expression) {
                let evaluationResult = when.tryEvaluate(this._context);
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
                    if (dataContext instanceof CEL.Expression) {
                        let evaluationResult = dataContext.tryEvaluate(this._context);

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