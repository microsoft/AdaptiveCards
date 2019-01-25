class TemplatizedString {
    private _parts: Array<string | Expression> = [];

    static parse(s: string): string | TemplatizedString {
        let result = new TemplatizedString();
        let parser = new ExpressionParser();
        let i = 0;

        do {
            let expressionFound = false;
            let start = s.indexOf("{", i);

            if (start >= 0) {
                let end = s.indexOf("}", start);

                if (end >= 0) {
                    expressionFound = true;

                    if (start > i) {
                        result._parts.push(s.substring(i, start));
                    }

                    result._parts.push(parser.parse(s.substring(start, end + 1)));

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

    evaluate(context: ExpressionContext): any {
        if (this._parts.length == 0) {
            return undefined;
        }
        else if (this._parts.length == 1) {
            if (typeof this._parts[0] === "string") {
                return this._parts[0];
            }
            else {
                return (<Expression>this._parts[0]).evaluate(context);
            }
        }
        else {
            let s = "";

            for (let part of this._parts) {
                if (typeof part === "string") {
                    s += part;
                }
                else {
                    s += (<Expression>part).evaluate(context);
                }
            }

            return s;
        }
    }
}

class Template {
    private static prepare(node: any): any {
        if (typeof node === "string") {
            return TemplatizedString.parse(node);
        }
        else if (typeof node === "object") {
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

    private _context: ExpressionContext;

    private internalExpand(node: any): any {
        let result: any;
        let previousDataContext = this._context.$data;

        if (Array.isArray(node)) {
            result = [];

            for (let item of node) {
                let dataContext = item["$data"];

                if (dataContext != undefined) {
                    if (dataContext instanceof TemplatizedString) {
                        dataContext = dataContext.evaluate(this._context);
                    }

                    if (Array.isArray(dataContext)) {
                        for (let itemDataContext of dataContext) {
                            this._context.$data = itemDataContext;

                            result.push(this.internalExpand(item));
                        }
                    }
                    else {
                        this._context.$data = dataContext;

                        result.push(this.internalExpand(item));
                    }
                }
                else {
                    result.push(this.internalExpand(item));
                }
            }
        }
        else if (node instanceof TemplatizedString) {
            result = node.evaluate(this._context);
        }
        else if (typeof node === "object") {
            let keys = Object.keys(node);
            result = {};

            for (let key of keys) {
                result[key] = this.internalExpand(node[key]);
            }
        }
        else {
            result = node;
        }

        this._context.$data = previousDataContext;

        return result;
    }

    preparedPayload: any;

    constructor(payload: any) {
        this.preparedPayload = Template.prepare(payload);
    }

    expand(context: ExpressionContext): any {
        this._context = context;

        return this.internalExpand(this.preparedPayload);
    }
}