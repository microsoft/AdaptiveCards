var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
var orderedOperators = [
    "/",
    "*",
    "-",
    "+",
    "==",
    "!=",
    "<",
    "<=",
    ">",
    ">="
];
var literals = [
    "identifier",
    "string",
    "number",
    "boolean"
];
var Tokenizer = /** @class */ (function () {
    function Tokenizer() {
    }
    Tokenizer.init = function () {
        Tokenizer.rules.push({ tokenType: undefined, regEx: /^\s/ }, { tokenType: "{", regEx: /^{/ }, { tokenType: "?#", regEx: /^\?#/ }, { tokenType: "}", regEx: /^}/ }, { tokenType: "[", regEx: /^\[/ }, { tokenType: "]", regEx: /^\]/ }, { tokenType: "(", regEx: /^\(/ }, { tokenType: ")", regEx: /^\)/ }, { tokenType: "boolean", regEx: /^true|^false/ }, { tokenType: "identifier", regEx: /^[$a-z_]+/i }, { tokenType: ".", regEx: /^\./ }, { tokenType: ",", regEx: /^,/ }, { tokenType: "+", regEx: /^\+/ }, { tokenType: "-", regEx: /^-/ }, { tokenType: "*", regEx: /^\*/ }, { tokenType: "/", regEx: /^\// }, { tokenType: "==", regEx: /^==/ }, { tokenType: "!=", regEx: /^!=/ }, { tokenType: "<=", regEx: /^<=/ }, { tokenType: "<", regEx: /^</ }, { tokenType: ">=", regEx: /^>=/ }, { tokenType: ">", regEx: /^>/ }, { tokenType: "string", regEx: /^"([^"]*)"/ }, { tokenType: "string", regEx: /^'([^']*)'/ }, { tokenType: "number", regEx: /^\d*\.?\d+/ });
    };
    Tokenizer.parse = function (expression) {
        var result = [];
        var i = 0;
        while (i < expression.length) {
            var subExpression = expression.substring(i);
            var matchFound = false;
            for (var _i = 0, _a = Tokenizer.rules; _i < _a.length; _i++) {
                var rule = _a[_i];
                var matches = rule.regEx.exec(subExpression);
                if (matches) {
                    if (matches.length > 2) {
                        throw new Error("A tokenizer rule matched more than one group.");
                    }
                    if (rule.tokenType != undefined) {
                        result.push({
                            type: rule.tokenType,
                            value: matches[matches.length == 1 ? 0 : 1],
                            originalPosition: i
                        });
                    }
                    i += matches[0].length;
                    matchFound = true;
                    break;
                }
            }
            if (!matchFound) {
                throw new Error("Unexpected character " + subExpression[0] + " at position " + i);
            }
        }
        return result;
    };
    Tokenizer.rules = [];
    return Tokenizer;
}());
Tokenizer.init();
function ensureValueType(value) {
    if (typeof value === "number" || typeof value === "string" || typeof value === "boolean") {
        return value;
    }
    throw new Error("Invalid value type: " + typeof value);
}
export var EvaluationContext = /** @class */ (function () {
    function EvaluationContext() {
        this._functions = {};
        this._stateStack = [];
    }
    EvaluationContext.init = function () {
        EvaluationContext._builtInFunctions["substr"] = function (params) {
            return params[0].substr(params[1], params[2]);
        };
        EvaluationContext._builtInFunctions["JSON.parse"] = function (params) {
            return JSON.parse(params[0]);
        };
    };
    EvaluationContext.prototype.registerFunction = function (name, callback) {
        this._functions[name] = callback;
    };
    EvaluationContext.prototype.unregisterFunction = function (name) {
        delete this._functions[name];
    };
    EvaluationContext.prototype.getFunction = function (name) {
        var result = this._functions[name];
        if (result == undefined) {
            result = EvaluationContext._builtInFunctions[name];
        }
        return result;
    };
    EvaluationContext.prototype.isReservedField = function (name) {
        return EvaluationContext._reservedFields.indexOf(name) >= 0;
    };
    EvaluationContext.prototype.saveState = function () {
        this._stateStack.push({ $data: this.$data, $index: this.$index });
    };
    EvaluationContext.prototype.restoreLastState = function () {
        if (this._stateStack.length == 0) {
            throw new Error("There is no evaluation context state to restore.");
        }
        var savedContext = this._stateStack.pop();
        this.$data = savedContext.$data;
        this.$index = savedContext.$index;
    };
    Object.defineProperty(EvaluationContext.prototype, "currentDataContext", {
        get: function () {
            return this.$data != undefined ? this.$data : this.$root;
        },
        enumerable: true,
        configurable: true
    });
    EvaluationContext._reservedFields = ["$data", "$root", "$index"];
    EvaluationContext._builtInFunctions = {};
    return EvaluationContext;
}());
EvaluationContext.init();
var EvaluationNode = /** @class */ (function () {
    function EvaluationNode() {
    }
    return EvaluationNode;
}());
var ExpressionNode = /** @class */ (function (_super) {
    __extends(ExpressionNode, _super);
    function ExpressionNode() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.nodes = [];
        _this.allowNull = true;
        return _this;
    }
    ExpressionNode.prototype.evaluate = function (context) {
        var operatorPriorityGroups = [
            ["/", "*"],
            ["-", "+"],
            ["==", "!=", "<", "<=", ">", ">="]
        ];
        var nodesCopy = this.nodes;
        for (var _i = 0, operatorPriorityGroups_1 = operatorPriorityGroups; _i < operatorPriorityGroups_1.length; _i++) {
            var priorityGroup = operatorPriorityGroups_1[_i];
            var i = 0;
            while (i < nodesCopy.length) {
                var node = nodesCopy[i];
                if (node instanceof OperatorNode && priorityGroup.indexOf(node.operator) >= 0) {
                    var left = ensureValueType(nodesCopy[i - 1].evaluate(context));
                    var right = ensureValueType(nodesCopy[i + 1].evaluate(context));
                    if (typeof left !== typeof right) {
                        throw new Error("Incompatible operands " + left + " and " + right + " for operator " + node.operator);
                    }
                    var result = void 0;
                    if (typeof left === "number" && typeof right === "number") {
                        switch (node.operator) {
                            case "/":
                                result = left / right;
                                break;
                            case "*":
                                result = left * right;
                                break;
                            case "-":
                                result = left - right;
                                break;
                            case "+":
                                result = left + right;
                                break;
                        }
                    }
                    if (typeof left === "string" && typeof right === "string") {
                        switch (node.operator) {
                            case "+":
                                result = left + right;
                                break;
                        }
                    }
                    switch (node.operator) {
                        case "==":
                            result = left == right;
                            break;
                        case "!=":
                            result = left != right;
                            break;
                        case "<":
                            result = left < right;
                            break;
                        case "<=":
                            result = left <= right;
                            break;
                        case ">":
                            result = left > right;
                            break;
                        case ">=":
                            result = left >= right;
                            break;
                        default:
                        // This should never happen
                    }
                    nodesCopy.splice(i - 1, 3, new LiteralNode(result));
                    i--;
                }
                i++;
            }
            ;
        }
        return nodesCopy[0].evaluate(context);
    };
    ExpressionNode.prototype.print = function () {
        var result = "";
        for (var _i = 0, _a = this.nodes; _i < _a.length; _i++) {
            var node = _a[_i];
            if (result != "") {
                result += " ";
            }
            result += node.print();
        }
        return "(" + result + ")";
    };
    return ExpressionNode;
}(EvaluationNode));
var IdentifierNode = /** @class */ (function (_super) {
    __extends(IdentifierNode, _super);
    function IdentifierNode() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    IdentifierNode.prototype.print = function () {
        return this.identifier;
    };
    IdentifierNode.prototype.evaluate = function (context) {
        return this.identifier;
    };
    return IdentifierNode;
}(EvaluationNode));
var IndexerNode = /** @class */ (function (_super) {
    __extends(IndexerNode, _super);
    function IndexerNode() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    IndexerNode.prototype.print = function () {
        return "[" + this.index.print() + "]";
    };
    IndexerNode.prototype.evaluate = function (context) {
        return this.index.evaluate(context);
    };
    return IndexerNode;
}(EvaluationNode));
var FunctionCallNode = /** @class */ (function (_super) {
    __extends(FunctionCallNode, _super);
    function FunctionCallNode() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.functionName = null;
        _this.parameters = [];
        return _this;
    }
    FunctionCallNode.prototype.evaluate = function (context) {
        var callback = context.getFunction(this.functionName);
        if (callback != undefined) {
            var evaluatedParams = [];
            for (var _i = 0, _a = this.parameters; _i < _a.length; _i++) {
                var param = _a[_i];
                evaluatedParams.push(param.evaluate(context));
            }
            return callback(evaluatedParams);
        }
        throw new Error("Undefined function: " + this.functionName);
    };
    FunctionCallNode.prototype.print = function () {
        var result = "";
        for (var _i = 0, _a = this.parameters; _i < _a.length; _i++) {
            var parameter = _a[_i];
            if (result != "") {
                result += ", ";
            }
            result += parameter.print();
        }
        return "FUNCTION:" + this.functionName + "{" + result + "}";
    };
    return FunctionCallNode;
}(EvaluationNode));
var LiteralNode = /** @class */ (function (_super) {
    __extends(LiteralNode, _super);
    function LiteralNode(value) {
        var _this = _super.call(this) || this;
        _this.value = value;
        return _this;
    }
    LiteralNode.prototype.evaluate = function (context) {
        return this.value;
    };
    LiteralNode.prototype.print = function () {
        return "LITERAL:" + this.value.toString();
    };
    return LiteralNode;
}(EvaluationNode));
var OperatorNode = /** @class */ (function (_super) {
    __extends(OperatorNode, _super);
    function OperatorNode(operator) {
        var _this = _super.call(this) || this;
        _this.operator = operator;
        return _this;
    }
    OperatorNode.prototype.evaluate = function (context) {
        throw new Error("An operator cannot be evaluated on its own.");
    };
    OperatorNode.prototype.print = function () {
        return this.operator;
    };
    return OperatorNode;
}(EvaluationNode));
var PathNode = /** @class */ (function (_super) {
    __extends(PathNode, _super);
    function PathNode() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.parts = [];
        return _this;
    }
    PathNode.prototype.evaluate = function (context) {
        var result = undefined;
        var index = 0;
        while (index < this.parts.length) {
            var part = this.parts[index];
            try {
                if (part instanceof IdentifierNode && index == 0) {
                    switch (part.identifier) {
                        case "$root":
                            result = context.$root;
                            break;
                        case "$data":
                            result = context.currentDataContext;
                            break;
                        case "$index":
                            result = context.$index;
                            break;
                        default:
                            result = context.currentDataContext[part.identifier];
                            break;
                    }
                }
                else {
                    var partValue = part.evaluate(context);
                    if (index == 0) {
                        result = partValue;
                    }
                    else {
                        typeof partValue !== "boolean" ? result = result[partValue] : result = result[partValue.toString()];
                    }
                }
            }
            catch (e) {
                return undefined;
            }
            index++;
        }
        return result;
    };
    PathNode.prototype.print = function () {
        var result = "";
        for (var _i = 0, _a = this.parts; _i < _a.length; _i++) {
            var part = _a[_i];
            if (result != "") {
                result += ".";
            }
            result += part.print();
        }
        return "PATH{" + result + "}";
    };
    return PathNode;
}(EvaluationNode));
export default ExpressionParser = /** @class */ (function () {
    function ExpressionParser(tokens) {
        this._index = 0;
        this._tokens = tokens;
    }
    ExpressionParser.prototype.unexpectedToken = function () {
        throw new Error("Unexpected token " + this.current.value + " at position " + this.current.originalPosition + ".");
    };
    ExpressionParser.prototype.unexpectedEoe = function () {
        throw new Error("Unexpected end of expression.");
    };
    ExpressionParser.prototype.moveNext = function () {
        this._index++;
    };
    ExpressionParser.prototype.parseToken = function () {
        var expectedTokenTypes = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            expectedTokenTypes[_i] = arguments[_i];
        }
        if (this.eoe) {
            this.unexpectedEoe();
        }
        var currentToken = this.current;
        if (expectedTokenTypes.indexOf(this.current.type) < 0) {
            this.unexpectedToken();
        }
        this.moveNext();
        return currentToken;
    };
    ExpressionParser.prototype.parseOptionalToken = function () {
        var expectedTokenTypes = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            expectedTokenTypes[_i] = arguments[_i];
        }
        if (this.eoe) {
            this.unexpectedEoe();
        }
        else if (expectedTokenTypes.indexOf(this.current.type) < 0) {
            return false;
        }
        else {
            this.moveNext();
            return true;
        }
    };
    ExpressionParser.prototype.parseFunctionCall = function (functionName) {
        var result = new FunctionCallNode();
        result.functionName = functionName;
        this.parseToken("(");
        var firstParameter = this.parseExpression();
        var moreParameters = false;
        if (firstParameter) {
            result.parameters.push(firstParameter);
            do {
                moreParameters = this.parseOptionalToken(",");
                if (moreParameters) {
                    var parameter = this.parseExpression();
                    result.parameters.push(parameter);
                }
            } while (moreParameters);
        }
        this.parseToken(")");
        return result;
    };
    ExpressionParser.prototype.parseIdentifier = function () {
        var result = new IdentifierNode();
        result.identifier = this.current.value;
        this.moveNext();
        return result;
    };
    ExpressionParser.prototype.parseIndexer = function () {
        var result = new IndexerNode();
        this.parseToken("[");
        result.index = this.parseExpression();
        this.parseToken("]");
        return result;
    };
    ExpressionParser.prototype.parsePath = function () {
        var result = new PathNode();
        var expectedNextTokenTypes = ["identifier", "("];
        while (!this.eoe) {
            if (expectedNextTokenTypes.indexOf(this.current.type) < 0) {
                return result;
            }
            switch (this.current.type) {
                case "(":
                    if (result.parts.length == 0) {
                        this.moveNext();
                        result.parts.push(this.parseExpression());
                        this.parseToken(")");
                    }
                    else {
                        var functionName = "";
                        for (var _i = 0, _a = result.parts; _i < _a.length; _i++) {
                            var part = _a[_i];
                            if (!(part instanceof IdentifierNode)) {
                                this.unexpectedToken();
                            }
                            if (functionName != "") {
                                functionName += ".";
                            }
                            functionName += part.identifier;
                        }
                        result.parts = [];
                        result.parts.push(this.parseFunctionCall(functionName));
                    }
                    expectedNextTokenTypes = [".", "["];
                    break;
                case "[":
                    result.parts.push(this.parseIndexer());
                    expectedNextTokenTypes = [".", "(", "["];
                    break;
                case "identifier":
                    result.parts.push(this.parseIdentifier());
                    expectedNextTokenTypes = [".", "(", "["];
                    break;
                case ".":
                    this.moveNext();
                    expectedNextTokenTypes = ["identifier"];
                    break;
                default:
                    expectedNextTokenTypes = [];
                    break;
            }
        }
    };
    ExpressionParser.prototype.parseExpression = function () {
        var result = new ExpressionNode();
        var expectedNextTokenTypes = literals.concat("(", "+", "-");
        while (!this.eoe) {
            if (expectedNextTokenTypes.indexOf(this.current.type) < 0) {
                if (result.nodes.length == 0) {
                    this.unexpectedToken();
                }
                return result;
            }
            switch (this.current.type) {
                case "(":
                case "identifier":
                    result.nodes.push(this.parsePath());
                    expectedNextTokenTypes = orderedOperators;
                    break;
                case "string":
                case "number":
                case "boolean":
                    if (this.current.type == "string") {
                        result.nodes.push(new LiteralNode(this.current.value));
                    }
                    else if (this.current.type == "number") {
                        result.nodes.push(new LiteralNode(parseFloat(this.current.value)));
                    }
                    else {
                        result.nodes.push(new LiteralNode(this.current.value === "true"));
                    }
                    this.moveNext();
                    expectedNextTokenTypes = orderedOperators;
                    break;
                case "-":
                    if (result.nodes.length == 0) {
                        result.nodes.push(new LiteralNode(-1));
                        result.nodes.push(new OperatorNode("*"));
                        expectedNextTokenTypes = ["identifier", "number", "("];
                    }
                    else {
                        result.nodes.push(new OperatorNode(this.current.type));
                        expectedNextTokenTypes = literals.concat("(");
                    }
                    this.moveNext();
                    break;
                case "+":
                    if (result.nodes.length == 0) {
                        expectedNextTokenTypes = literals.concat("(");
                    }
                    else {
                        result.nodes.push(new OperatorNode(this.current.type));
                        expectedNextTokenTypes = literals.concat("(");
                    }
                    this.moveNext();
                    break;
                case "*":
                case "/":
                case "==":
                case "!=":
                case "<":
                case "<=":
                case ">":
                case ">=":
                    result.nodes.push(new OperatorNode(this.current.type));
                    this.moveNext();
                    expectedNextTokenTypes = literals.concat("(");
                    break;
                default:
                    expectedNextTokenTypes = [];
                    break;
            }
        }
    };
    Object.defineProperty(ExpressionParser.prototype, "eoe", {
        get: function () {
            return this._index >= this._tokens.length;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ExpressionParser.prototype, "current", {
        get: function () {
            return this._tokens[this._index];
        },
        enumerable: true,
        configurable: true
    });
    ExpressionParser.parseBinding = function (bindingExpression) {
        var parser = new ExpressionParser(Tokenizer.parse(bindingExpression));
        parser.parseToken("{");
        var allowNull = !parser.parseOptionalToken("?#");
        var expression = parser.parseExpression();
        parser.parseToken("}");
        return new Binding(expression, allowNull);
    };
    return ExpressionParser;
}());
var Binding = /** @class */ (function () {
    function Binding(expression, allowNull) {
        if (allowNull === void 0) { allowNull = true; }
        this.expression = expression;
        this.allowNull = allowNull;
    }
    Binding.prototype.evaluate = function (context) {
        return this.expression.evaluate(context);
    };
    Binding.prototype.print = function () {
        return this.expression.print();
    };
    return Binding;
}());
//# sourceMappingURL=expression-parser.js.map