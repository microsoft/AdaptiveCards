// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Shared from "./shared";
import * as CEL from "adaptive-expressions";

export class TemplateBinding {
    static parse(expressionString: string): TemplateBinding {
        let expression = CEL.Expression.parse(expressionString);

        // NOTE: Planned syntax ?# isn't supported yet
        return new TemplateBinding(expressionString, expression, true /* allowNull */);
    }

    private constructor(readonly expressionString: string, private readonly expression: CEL.Expression, readonly allowNull: boolean = true) {}

    evaluate(context: EvaluationContext): any {
        let evaluationResult = this.expression.tryEvaluate(context);

        if (!evaluationResult.error) {
            return evaluationResult.value;
        }

        throw new Error(evaluationResult.error);
    }
}

class TemplatizedString {
    private _parts: Array<string | TemplateBinding> = [];

    static parse(s: string): string | TemplatizedString {
        let result = new TemplatizedString();
        let i = 0;

        do {
            let expressionFound = false;
            let start = i;
            let loop;
            
            do {
                loop = false;

                start = s.indexOf(Shared.GlobalSettings.expressionStartMarker, start);

                if (start >= 0) {
                    // This handles the {{...}} syntax used for DATE and TIME functions in the AC renderer
                    // Should probably be removed if we can find a way to migrate DATE and TIME to the
                    // expression language.
                    if (start + Shared.GlobalSettings.expressionStartMarker.length < s.length && s[start + Shared.GlobalSettings.expressionStartMarker.length] === "{") {
                        start += 2;

                        loop = true;
                    }
                }
            } while (loop);

            if (start >= 0) {
                let end = s.indexOf(Shared.GlobalSettings.expressionEndMarker, start);

                if (end >= 0) {
                    expressionFound = true;

                    if (start > i) {
                        result._parts.push(s.substring(i, start));
                    }

                    let bindngExpression = s.substring(start + Shared.GlobalSettings.expressionStartMarker.length, end);
                    let part: string | TemplateBinding;

                    try {
                        part = TemplateBinding.parse(bindngExpression);
                    }
                    catch (e) {
                        part = bindngExpression;
                    }

                    result._parts.push(part);

                    i = end + 1;
                }
            }

            if (!expressionFound) {
                result._parts.push(s.substr(i));

                break;
            }
        } while (i < s.length);

        if (result._parts.length === 1 && typeof result._parts[0] === "string") {
            return <string>result._parts[0];
        }
        else {
            return result;
        }
    }

    private _shouldDropOwner: boolean = false;

    private evalExpression(binding: TemplateBinding, context: EvaluationContext): any {
        let result = binding.evaluate(context);

        if (result === undefined) {
            this._shouldDropOwner = this._shouldDropOwner || !binding.allowNull;
        }

        return result;
    }

    private internalEvaluate(context: EvaluationContext): any {
        if (this._parts.length === 0) {
            return undefined;
        }
        else if (this._parts.length === 1) {
            // If the templatized string only has 1 part, we want it to evaluate
            // to same the type as produced by the expression
            if (typeof this._parts[0] === "string") {
                return this._parts[0];
            }
            else {
                return this.evalExpression(<TemplateBinding>this._parts[0], context);
            }
        }
        else {
            // If the templatized string has multiple parts, we want it to evaluate
            // to a string. In that context, each part that evaluates to undefined
            // gets replaced by the original expression by default or by a resource
            // string provided by the application
            let s = "";

            for (let part of this._parts) {
                if (typeof part === "string") {
                    s += part;
                }
                else {
                    let evaluatedPart = this.evalExpression(<TemplateBinding>part, context);

                    if (evaluatedPart === undefined) {
                        evaluatedPart = Shared.GlobalSettings.undefinedExpressionValueSubstitutionString ? Shared.GlobalSettings.undefinedExpressionValueSubstitutionString : (<TemplateBinding>part).expressionString;
                    }

                    s += evaluatedPart;
                }
            }

            return s;
        }
    }

    evaluate(context: EvaluationContext): any {
        this._shouldDropOwner = false;

        return this.internalEvaluate(context);
    }

    get shouldDropOwner(): boolean {
        return this._shouldDropOwner;
    }
}

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
            return TemplatizedString.parse(node);
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
        else if (node instanceof TemplatizedString) {
            result = node.evaluate(this._context);

            if (node.shouldDropOwner) {
                result = null;
            }
        }
        else if (typeof node === "object" && node !== null) {
            let dropObject = false;
            let when = node["$when"];

            if (when instanceof TemplatizedString) {
                let whenValue: any;
                
                try {
                    whenValue = when.evaluate(this._context);

                    // If $when doesn't evaluate to a boolean, consider it is false
                    if (typeof whenValue !== "boolean") {
                        whenValue = false;
                    }
                }
                catch {
                    // If we hit an exception, consider $when to be false
                    whenValue = false;
                }

                dropObject = !whenValue;
            }

            if (!dropObject) {
                let dataContext = node["$data"];

                if (dataContext !== undefined) {
                    if (dataContext instanceof TemplatizedString) {
                        dataContext = dataContext.evaluate(this._context);
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