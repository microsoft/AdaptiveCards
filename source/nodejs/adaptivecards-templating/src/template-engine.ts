// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Binding, ExpressionParser, EvaluationContext } from "./expression-parser";

export class TemplatizedString {
    private _parts: Array<string | Binding> = [];

    static parse(s: string): string | TemplatizedString {
        let result = new TemplatizedString();
        let i = 0;

        do {
            let expressionFound = false;
            let start = i;
            let loop;

            do {
                loop = false;

                start = s.indexOf("{", start);

                if (start >= 0) {
                    if (start + 1 < s.length && s[start + 1] == "{") {
                        start += 2;

                        loop = true;
                    }
                }
            } while (loop);

            if (start >= 0) {
                let end = s.indexOf("}", start);

                if (end >= 0) {
                    expressionFound = true;

                    if (start > i) {
                        result._parts.push(s.substring(i, start));
                    }

                    let bindngExpression = s.substring(start, end + 1);
                    let part: string | Binding;

                    try {
                        part = ExpressionParser.parseBinding(bindngExpression);
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

        if (result._parts.length == 1 && typeof result._parts[0] === "string") {
            return <string>result._parts[0];
        }
        else {
            return result;
        }
    }

    private _shouldDropOwner: boolean = false;

    private evalExpression(bindingExpression: Binding, context: EvaluationContext): any {
        let result = bindingExpression.evaluate(context);

        if (result == undefined) {
            this._shouldDropOwner = this._shouldDropOwner || !bindingExpression.allowNull;
        }

        return result;
    }

    private internalEvaluate(context: EvaluationContext): any {
        if (this._parts.length == 0) {
            return undefined;
        }
        else if (this._parts.length == 1) {
            if (typeof this._parts[0] === "string") {
                return this._parts[0];
            }
            else {
                return this.evalExpression(<Binding>this._parts[0], context);
            }
        }
        else {
            let s = "";

            for (let part of this._parts) {
                if (typeof part === "string") {
                    s += part;
                }
                else {
                    s += this.evalExpression(<Binding>part, context);
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

export class Template {
    private static prepare(node: any): any {
        if (typeof node === "string") {
            return TemplatizedString.parse(node);
        }
        else if (typeof node === "object" && node != null) {
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

                if (value != undefined) {
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

                if (expandedItem != null) {
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
        else if (typeof node === "object" && node != null) {
            let dropObject = false;
            let when = node["$when"];

            if (when instanceof TemplatizedString) {
                let whenValue = when.evaluate(this._context);

                if (typeof whenValue === "boolean") {
                    dropObject = !whenValue;
                }
            }

            if (!dropObject) {
                let dataContext = node["$data"];

                if (dataContext != undefined) {
                    if (dataContext instanceof TemplatizedString) {
                        dataContext = dataContext.evaluate(this._context);
                    }

                    if (Array.isArray(dataContext)) {
                        result = [];

                        for (let i = 0; i < dataContext.length; i++) {
                            this._context.$data = dataContext[i];
                            this._context.$index = i;

                            let expandedObject = this.expandSingleObject(node);

                            if (expandedObject != null) {
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
