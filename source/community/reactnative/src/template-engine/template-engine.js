import ExpressionParser from './expression-parser'

var TemplatizedString = /** @class */ (function () {
    function TemplatizedString() {
        this._parts = [];
        this._shouldDropOwner = false;
    }
    TemplatizedString.parse = function (s) {
        var result = new TemplatizedString();
        var i = 0;
        do {
            var expressionFound = false;
            var start = s.indexOf("{", i);
            if (start >= 0) {
                var end = s.indexOf("}", start);
                if (end >= 0) {
                    expressionFound = true;
                    if (start > i) {
                        result._parts.push(s.substring(i, start));
                    }
                    result._parts.push(ExpressionParser.parseBinding(s.substring(start, end + 1)));
                    i = end + 1;
                }
            }
            if (!expressionFound) {
                result._parts.push(s.substr(i));
                break;
            }
        } while (i < s.length);
        if (result._parts.length == 1 && typeof result._parts[0] === "string") {
            return result._parts[0];
        }
        else {
            return result;
        }
    };
    TemplatizedString.prototype.evalExpression = function (bindingExpression, context) {
        var result = bindingExpression.evaluate(context);
        if (result == undefined) {
            this._shouldDropOwner = this._shouldDropOwner || !bindingExpression.allowNull;
        }
        return result;
    };
    TemplatizedString.prototype.internalEvaluate = function (context) {
        if (this._parts.length == 0) {
            return undefined;
        }
        else if (this._parts.length == 1) {
            if (typeof this._parts[0] === "string") {
                return this._parts[0];
            }
            else {
                return this.evalExpression(this._parts[0], context);
            }
        }
        else {
            var s = "";
            for (var _i = 0, _a = this._parts; _i < _a.length; _i++) {
                var part = _a[_i];
                if (typeof part === "string") {
                    s += part;
                }
                else {
                    s += this.evalExpression(part, context);
                }
            }
            return s;
        }
    };
    TemplatizedString.prototype.evaluate = function (context) {
        this._shouldDropOwner = false;
        return this.internalEvaluate(context);
    };
    Object.defineProperty(TemplatizedString.prototype, "shouldDropOwner", {
        get: function () {
            return this._shouldDropOwner;
        },
        enumerable: true,
        configurable: true
    });
    return TemplatizedString;
}());


export default Template = /** @class */ (function () {
    function Template(payload) {
        this.preparedPayload = Template.prepare(payload);
    }
    Template.prepare = function (node) {
        if (typeof node === "string") {
            return TemplatizedString.parse(node);
        }
        else if (typeof node === "object") {
            if (Array.isArray(node)) {
                var result = [];
                for (var _i = 0, node_1 = node; _i < node_1.length; _i++) {
                    var item = node_1[_i];
                    result.push(Template.prepare(item));
                }
                return result;
            }
            else {
                var keys = Object.keys(node);
                var result = {};
                for (var _a = 0, keys_1 = keys; _a < keys_1.length; _a++) {
                    var key = keys_1[_a];
                    result[key] = Template.prepare(node[key]);
                }
                return result;
            }
        }
        else {
            return node;
        }
    };
    Template.prototype.expandSingleObject = function (node) {
        var result = {};
        var keys = Object.keys(node);
        for (var _i = 0, keys_2 = keys; _i < keys_2.length; _i++) {
            var key = keys_2[_i];
            if (!this._context.isReservedField(key)) {
                var value = this.internalExpand(node[key]);
                if (value != null) {
                    result[key] = value;
                }
                else {
                    return null;
                }
            }
        }
        return result;
    };
    Template.prototype.internalExpand = function (node) {
        var result;
        this._context.saveState();
        debugger;
        if (Array.isArray(node)) {
            var itemArray = [];
            for (var _i = 0, node_2 = node; _i < node_2.length; _i++) {
                var item = node_2[_i];
                var expandedItem = this.internalExpand(item);
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
        else if (typeof node === "object") {
            var dataContext = node["$data"];
            if (dataContext != undefined) {
                if (dataContext instanceof TemplatizedString) {
                    dataContext = dataContext.evaluate(this._context);
                }
                if (Array.isArray(dataContext)) {
                    result = [];
                    for (var i = 0; i < dataContext.length; i++) {
                        this._context.$data = dataContext[i];
                        this._context.$index = i;
                        var expandedObject = this.expandSingleObject(node);
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
            result = node;
        }
        this._context.restoreLastState();
        return result;
    };
    Template.prototype.expand = function (context) {
        this._context = context;
        return this.internalExpand(this.preparedPayload);
    };
    return Template;
}());
//# sourceMappingURL=template-engine.js.map