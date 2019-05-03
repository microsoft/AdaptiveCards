var TemplateEngine =
/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, { enumerable: true, get: getter });
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 			Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 		}
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// create a fake namespace object
/******/ 	// mode & 1: value is a module id, require it
/******/ 	// mode & 2: merge all properties of value into the ns
/******/ 	// mode & 4: return value when already ns object
/******/ 	// mode & 8|1: behave like require
/******/ 	__webpack_require__.t = function(value, mode) {
/******/ 		if(mode & 1) value = __webpack_require__(value);
/******/ 		if(mode & 8) return value;
/******/ 		if((mode & 4) && typeof value === 'object' && value && value.__esModule) return value;
/******/ 		var ns = Object.create(null);
/******/ 		__webpack_require__.r(ns);
/******/ 		Object.defineProperty(ns, 'default', { enumerable: true, value: value });
/******/ 		if(mode & 2 && typeof value != 'string') for(var key in value) __webpack_require__.d(ns, key, function(key) { return value[key]; }.bind(null, key));
/******/ 		return ns;
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = "./src/template-engine.ts");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./src/expression-parser.ts":
/*!**********************************!*\
  !*** ./src/expression-parser.ts ***!
  \**********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

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
Object.defineProperty(exports, "__esModule", { value: true });
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
var EvaluationContext = /** @class */ (function () {
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
        EvaluationContext._builtInFunctions["if"] = function (params) {
            return params[0] ? params[1] : params[2];
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
exports.EvaluationContext = EvaluationContext;
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
    return ExpressionNode;
}(EvaluationNode));
var IdentifierNode = /** @class */ (function (_super) {
    __extends(IdentifierNode, _super);
    function IdentifierNode() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
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
                        result = typeof partValue !== "boolean" ? result[partValue] : result[partValue.toString()];
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
    return PathNode;
}(EvaluationNode));
var ExpressionParser = /** @class */ (function () {
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
exports.ExpressionParser = ExpressionParser;
var Binding = /** @class */ (function () {
    function Binding(expression, allowNull) {
        if (allowNull === void 0) { allowNull = true; }
        this.expression = expression;
        this.allowNull = allowNull;
    }
    Binding.prototype.evaluate = function (context) {
        return this.expression.evaluate(context);
    };
    return Binding;
}());
exports.Binding = Binding;


/***/ }),

/***/ "./src/template-engine.ts":
/*!********************************!*\
  !*** ./src/template-engine.ts ***!
  \********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

Object.defineProperty(exports, "__esModule", { value: true });
var expression_parser_1 = __webpack_require__(/*! ./expression-parser */ "./src/expression-parser.ts");
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
            var start = i;
            var loop = void 0;
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
                var end = s.indexOf("}", start);
                if (end >= 0) {
                    expressionFound = true;
                    if (start > i) {
                        result._parts.push(s.substring(i, start));
                    }
                    var bindngExpression = s.substring(start, end + 1);
                    var part = void 0;
                    try {
                        part = expression_parser_1.ExpressionParser.parseBinding(bindngExpression);
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
var Template = /** @class */ (function () {
    function Template(payload) {
        this.preparedPayload = Template.prepare(payload);
    }
    Template.prepare = function (node) {
        if (typeof node === "string") {
            return TemplatizedString.parse(node);
        }
        else if (typeof node === "object" && node != null) {
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
                if (value != undefined) {
                    result[key] = value;
                }
            }
        }
        return result;
    };
    Template.prototype.internalExpand = function (node) {
        var result;
        this._context.saveState();
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
        else if (typeof node === "object" && node != null) {
            var dropObject = false;
            var when = node["$when"];
            if (when instanceof TemplatizedString) {
                var whenValue = when.evaluate(this._context);
                if (typeof whenValue === "boolean") {
                    dropObject = !whenValue;
                }
            }
            if (!dropObject) {
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
                result = null;
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
exports.Template = Template;
function transform(cardJson, dataJson) {
    var template = new Template(JSON.parse(cardJson));
    var context = new expression_parser_1.EvaluationContext();
    context.$root = JSON.parse(dataJson);
    var transformedCard = template.expand(context);
    return JSON.stringify(transformedCard);
}
exports.transform = transform;


/***/ })

/******/ });
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly9UZW1wbGF0ZUVuZ2luZS93ZWJwYWNrL2Jvb3RzdHJhcCIsIndlYnBhY2s6Ly9UZW1wbGF0ZUVuZ2luZS8uL3NyYy9leHByZXNzaW9uLXBhcnNlci50cyIsIndlYnBhY2s6Ly9UZW1wbGF0ZUVuZ2luZS8uL3NyYy90ZW1wbGF0ZS1lbmdpbmUudHMiXSwibmFtZXMiOltdLCJtYXBwaW5ncyI6Ijs7QUFBQTtBQUNBOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTs7QUFFQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7O0FBR0E7QUFDQTs7QUFFQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBLGtEQUEwQyxnQ0FBZ0M7QUFDMUU7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQSxnRUFBd0Qsa0JBQWtCO0FBQzFFO0FBQ0EseURBQWlELGNBQWM7QUFDL0Q7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLGlEQUF5QyxpQ0FBaUM7QUFDMUUsd0hBQWdILG1CQUFtQixFQUFFO0FBQ3JJO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0EsbUNBQTJCLDBCQUEwQixFQUFFO0FBQ3ZELHlDQUFpQyxlQUFlO0FBQ2hEO0FBQ0E7QUFDQTs7QUFFQTtBQUNBLDhEQUFzRCwrREFBK0Q7O0FBRXJIO0FBQ0E7OztBQUdBO0FBQ0E7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7QUN6REEsSUFBTSxnQkFBZ0IsR0FBcUI7SUFDdkMsR0FBRztJQUNILEdBQUc7SUFDSCxHQUFHO0lBQ0gsR0FBRztJQUNILElBQUk7SUFDSixJQUFJO0lBQ0osR0FBRztJQUNILElBQUk7SUFDSixHQUFHO0lBQ0gsSUFBSTtDQUNQLENBQUM7QUFFRixJQUFNLFFBQVEsR0FBcUI7SUFDL0IsWUFBWTtJQUNaLFFBQVE7SUFDUixRQUFRO0lBQ1IsU0FBUztDQUNaLENBQUM7QUFhRjtJQUFBO0lBMEVBLENBQUM7SUF2RVUsY0FBSSxHQUFYO1FBQ0ksU0FBUyxDQUFDLEtBQUssQ0FBQyxJQUFJLENBQ2hCLEVBQUUsU0FBUyxFQUFFLFNBQVMsRUFBRSxLQUFLLEVBQUUsS0FBSyxFQUFFLEVBQ3RDLEVBQUUsU0FBUyxFQUFFLEdBQUcsRUFBRSxLQUFLLEVBQUUsSUFBSSxFQUFFLEVBQy9CLEVBQUUsU0FBUyxFQUFFLElBQUksRUFBRSxLQUFLLEVBQUUsTUFBTSxFQUFFLEVBQ2xDLEVBQUUsU0FBUyxFQUFFLEdBQUcsRUFBRSxLQUFLLEVBQUUsSUFBSSxFQUFFLEVBQy9CLEVBQUUsU0FBUyxFQUFFLEdBQUcsRUFBRSxLQUFLLEVBQUUsS0FBSyxFQUFFLEVBQ2hDLEVBQUUsU0FBUyxFQUFFLEdBQUcsRUFBRSxLQUFLLEVBQUUsS0FBSyxFQUFFLEVBQ2hDLEVBQUUsU0FBUyxFQUFFLEdBQUcsRUFBRSxLQUFLLEVBQUUsS0FBSyxFQUFFLEVBQ2hDLEVBQUUsU0FBUyxFQUFFLEdBQUcsRUFBRSxLQUFLLEVBQUUsS0FBSyxFQUFFLEVBQ2hDLEVBQUUsU0FBUyxFQUFFLFNBQVMsRUFBRSxLQUFLLEVBQUUsY0FBYyxFQUFFLEVBQy9DLEVBQUUsU0FBUyxFQUFFLFlBQVksRUFBRSxLQUFLLEVBQUUsWUFBWSxFQUFFLEVBQ2hELEVBQUUsU0FBUyxFQUFFLEdBQUcsRUFBRSxLQUFLLEVBQUUsS0FBSyxFQUFFLEVBQ2hDLEVBQUUsU0FBUyxFQUFFLEdBQUcsRUFBRSxLQUFLLEVBQUUsSUFBSSxFQUFFLEVBQy9CLEVBQUUsU0FBUyxFQUFFLEdBQUcsRUFBRSxLQUFLLEVBQUUsS0FBSyxFQUFFLEVBQ2hDLEVBQUUsU0FBUyxFQUFFLEdBQUcsRUFBRSxLQUFLLEVBQUUsSUFBSSxFQUFFLEVBQy9CLEVBQUUsU0FBUyxFQUFFLEdBQUcsRUFBRSxLQUFLLEVBQUUsS0FBSyxFQUFFLEVBQ2hDLEVBQUUsU0FBUyxFQUFFLEdBQUcsRUFBRSxLQUFLLEVBQUUsS0FBSyxFQUFFLEVBQ2hD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QU0sR0FBRyxJQUFJLENBQUM7U0FDakI7UUFFRCxJQUFJLENBQUMsUUFBUSxDQUFDLGdCQUFnQixFQUFFLENBQUM7UUFFakMsT0FBTyxNQUFNLENBQUM7SUFDbEIsQ0FBQztJQVFELHlCQUFNLEdBQU4sVUFBTyxPQUEwQjtRQUM3QixJQUFJLENBQUMsUUFBUSxHQUFHLE9BQU8sQ0FBQztRQUV4QixPQUFPLElBQUksQ0FBQyxjQUFjLENBQUMsSUFBSSxDQUFDLGVBQWUsQ0FBQyxDQUFDO0lBQ3JELENBQUM7SUFDTCxlQUFDO0FBQUQsQ0FBQztBQXBKWSw0QkFBUTtBQXNKckIsU0FBZ0IsU0FBUyxDQUFDLFFBQWdCLEVBQUUsUUFBZ0I7SUFDM0QsSUFBSSxRQUFRLEdBQUcsSUFBSSxRQUFRLENBQUMsSUFBSSxDQUFDLEtBQUssQ0FBQyxRQUFRLENBQUMsQ0FBQyxDQUFDO0lBRS9DLElBQUksT0FBTyxHQUFHLElBQUkscUNBQWlCLEVBQUUsQ0FBQztJQUN6QyxPQUFPLENBQUMsS0FBSyxHQUFHLElBQUksQ0FBQyxLQUFLLENBQUMsUUFBUSxDQUFDLENBQUM7SUFDckMsS0FBSyxDQUFDLE9BQU8sQ0FBQyxLQUFLLENBQUMsQ0FBQztJQUVsQixJQUFJLGVBQWUsR0FBRyxRQUFRLENBQUMsTUFBTSxDQUFDLE9BQU8sQ0FBQyxDQUFDO0lBQy9DLE9BQU8sSUFBSSxDQUFDLFNBQVMsQ0FBQyxlQUFlLENBQUMsQ0FBQztBQUMzQyxDQUFDO0FBVEQsOEJBU0MiLCJmaWxlIjoidGVtcGxhdGUtZW5naW5lLmpzIiwic291cmNlc0NvbnRlbnQiOlsiIFx0Ly8gVGhlIG1vZHVsZSBjYWNoZVxuIFx0dmFyIGluc3RhbGxlZE1vZHVsZXMgPSB7fTtcblxuIFx0Ly8gVGhlIHJlcXVpcmUgZnVuY3Rpb25cbiBcdGZ1bmN0aW9uIF9fd2VicGFja19yZXF1aXJlX18obW9kdWxlSWQpIHtcblxuIFx0XHQvLyBDaGVjayBpZiBtb2R1bGUgaXMgaW4gY2FjaGVcbiBcdFx0aWYoaW5zdGFsbGVkTW9kdWxlc1ttb2R1bGVJZF0pIHtcbiBcdFx0XHRyZXR1cm4gaW5zdGFsbGVkTW9kdWxlc1ttb2R1bGVJZF0uZXhwb3J0cztcbiBcdFx0fVxuIFx0XHQvLyBDcmVhdGUgYSBuZXcgbW9kdWxlIChhbmQgcHV0IGl0IGludG8gdGhlIGNhY2hlKVxuIFx0XHR2YXIgbW9kdWxlID0gaW5zdGFsbGVkTW9kdWxlc1ttb2R1bGVJZF0gPSB7XG4gXHRcdFx0aTogbW9kdWxlSWQsXG4gXHRcdFx0bDogZmFsc2UsXG4gXHRcdFx0ZXhwb3J0czoge31cbiBcdFx0fTtcblxuIFx0XHQvLyBFeGVjdXRlIHRoZSBtb2R1bGUgZnVuY3Rpb25cbiBcdFx0bW9kdWxlc1ttb2R1bGVJZF0uY2FsbChtb2R1bGUuZXhwb3J0cywgbW9kdWxlLCBtb2R1bGUuZXhwb3J0cywgX193ZWJwYWNrX3JlcXVpcmVfXyk7XG5cbiBcdFx0Ly8gRmxhZyB0aGUgbW9kdWxlIGFzIGxvYWRlZFxuIFx0XHRtb2R1bGUubCA9IHRydWU7XG5cbiBcdFx0Ly8gUmV0dXJuIHRoZSBleHBvcnRzIG9mIHRoZSBtb2R1bGVcbiBcdFx0cmV0dXJuIG1vZHVsZS5leHBvcnRzO1xuIFx0fVxuXG5cbiBcdC8vIGV4cG9zZSB0aGUgbW9kdWxlcyBvYmplY3QgKF9fd2VicGFja19tb2R1bGVzX18pXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLm0gPSBtb2R1bGVzO1xuXG4gXHQvLyBleHBvc2UgdGhlIG1vZHVsZSBjYWNoZVxuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5jID0gaW5zdGFsbGVkTW9kdWxlcztcblxuIFx0Ly8gZGVmaW5lIGdldHRlciBmdW5jdGlvbiBmb3IgaGFybW9ueSBleHBvcnRzXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLmQgPSBmdW5jdGlvbihleHBvcnRzLCBuYW1lLCBnZXR0ZXIpIHtcbiBcdFx0aWYoIV9fd2VicGFja19yZXF1aXJlX18ubyhleHBvcnRzLCBuYW1lKSkge1xuIFx0XHRcdE9iamVjdC5kZWZpbmVQcm9wZXJ0eShleHBvcnRzLCBuYW1lLCB7IGVudW1lcmFibGU6IHRydWUsIGdldDogZ2V0dGVyIH0pO1xuIFx0XHR9XG4gXHR9O1xuXG4gXHQvLyBkZWZpbmUgX19lc01vZHVsZSBvbiBleHBvcnRzXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLnIgPSBmdW5jdGlvbihleHBvcnRzKSB7XG4gXHRcdGlmKHR5cGVvZiBTeW1ib2wgIT09ICd1bmRlZmluZWQnICYmIFN5bWJvbC50b1N0cmluZ1RhZykge1xuIFx0XHRcdE9iamVjdC5kZWZpbmVQcm9wZXJ0eShleHBvcnRzLCBTeW1ib2wudG9TdHJpbmdUYWcsIHsgdmFsdWU6ICdNb2R1bGUnIH0pO1xuIFx0XHR9XG4gXHRcdE9iamVjdC5kZWZpbmVQcm9wZXJ0eShleHBvcnRzLCAnX19lc01vZHVsZScsIHsgdmFsdWU6IHRydWUgfSk7XG4gXHR9O1xuXG4gXHQvLyBjcmVhdGUgYSBmYWtlIG5hbWVzcGFjZSBvYmplY3RcbiBcdC8vIG1vZGUgJiAxOiB2YWx1ZSBpcyBhIG1vZHVsZSBpZCwgcmVxdWlyZSBpdFxuIFx0Ly8gbW9kZSAmIDI6IG1lcmdlIGFsbCBwcm9wZXJ0aWVzIG9mIHZhbHVlIGludG8gdGhlIG5zXG4gXHQvLyBtb2RlICYgNDogcmV0dXJuIHZhbHVlIHdoZW4gYWxyZWFkeSBucyBvYmplY3RcbiBcdC8vIG1vZGUgJiA4fDE6IGJlaGF2ZSBsaWtlIHJlcXVpcmVcbiBcdF9fd2VicGFja19yZXF1aXJlX18udCA9IGZ1bmN0aW9uKHZhbHVlLCBtb2RlKSB7XG4gXHRcdGlmKG1vZGUgJiAxKSB2YWx1ZSA9IF9fd2VicGFja19yZXF1aXJlX18odmFsdWUpO1xuIFx0XHRpZihtb2RlICYgOCkgcmV0dXJuIHZhbHVlO1xuIFx0XHRpZigobW9kZSAmIDQpICYmIHR5cGVvZiB2YWx1ZSA9PT0gJ29iamVjdCcgJiYgdmFsdWUgJiYgdmFsdWUuX19lc01vZHVsZSkgcmV0dXJuIHZhbHVlO1xuIFx0XHR2YXIgbnMgPSBPYmplY3QuY3JlYXRlKG51bGwpO1xuIFx0XHRfX3dlYnBhY2tfcmVxdWlyZV9fLnIobnMpO1xuIFx0XHRPYmplY3QuZGVmaW5lUHJvcGVydHkobnMsICdkZWZhdWx0JywgeyBlbnVtZXJhYmxlOiB0cnVlLCB2YWx1ZTogdmFsdWUgfSk7XG4gXHRcdGlmKG1vZGUgJiAyICYmIHR5cGVvZiB2YWx1ZSAhPSAnc3RyaW5nJykgZm9yKHZhciBrZXkgaW4gdmFsdWUpIF9fd2VicGFja19yZXF1aXJlX18uZChucywga2V5LCBmdW5jdGlvbihrZXkpIHsgcmV0dXJuIHZhbHVlW2tleV07IH0uYmluZChudWxsLCBrZXkpKTtcbiBcdFx0cmV0dXJuIG5zO1xuIFx0fTtcblxuIFx0Ly8gZ2V0RGVmYXVsdEV4cG9ydCBmdW5jdGlvbiBmb3IgY29tcGF0aWJpbGl0eSB3aXRoIG5vbi1oYXJtb255IG1vZHVsZXNcbiBcdF9fd2VicGFja19yZXF1aXJlX18ubiA9IGZ1bmN0aW9uKG1vZHVsZSkge1xuIFx0XHR2YXIgZ2V0dGVyID0gbW9kdWxlICYmIG1vZHVsZS5fX2VzTW9kdWxlID9cbiBcdFx0XHRmdW5jdGlvbiBnZXREZWZhdWx0KCkgeyByZXR1cm4gbW9kdWxlWydkZWZhdWx0J107IH0gOlxuIFx0XHRcdGZ1bmN0aW9uIGdldE1vZHVsZUV4cG9ydHMoKSB7IHJldHVybiBtb2R1bGU7IH07XG4gXHRcdF9fd2VicGFja19yZXF1aXJlX18uZChnZXR0ZXIsICdhJywgZ2V0dGVyKTtcbiBcdFx0cmV0dXJuIGdldHRlcjtcbiBcdH07XG5cbiBcdC8vIE9iamVjdC5wcm90b3R5cGUuaGFzT3duUHJvcGVydHkuY2FsbFxuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5vID0gZnVuY3Rpb24ob2JqZWN0LCBwcm9wZXJ0eSkgeyByZXR1cm4gT2JqZWN0LnByb3RvdHlwZS5oYXNPd25Qcm9wZXJ0eS5jYWxsKG9iamVjdCwgcHJvcGVydHkpOyB9O1xuXG4gXHQvLyBfX3dlYnBhY2tfcHVibGljX3BhdGhfX1xuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5wID0gXCJcIjtcblxuXG4gXHQvLyBMb2FkIGVudHJ5IG1vZHVsZSBhbmQgcmV0dXJuIGV4cG9ydHNcbiBcdHJldHVybiBfX3dlYnBhY2tfcmVxdWlyZV9fKF9fd2VicGFja19yZXF1aXJlX18ucyA9IFwiLi9zcmMvdGVtcGxhdGUtZW5naW5lLnRzXCIpO1xuIiwidHlwZSBUb2tlblR5cGUgPVxyXG4gICAgXCJ7XCIgfFxyXG4gICAgXCI/I1wiIHxcclxuICAgIFwifVwiIHxcclxuICAgIFwiW1wiIHxcclxuICAgIFwiXVwiIHxcclxuICAgIFwiKFwiIHxcclxuICAgIFwiKVwiIHxcclxuICAgIFwiaWRlbnRpZmllclwiIHxcclxuICAgIFwiLlwiIHxcclxuICAgIFwiLFwiIHxcclxuICAgIFwiK1wiIHxcclxuICAgIFwiLVwiIHxcclxuICAgIFwiKlwiIHxcclxuICAgIFwiL1wiIHxcclxuICAgIFwiPT1cIiB8XHJcbiAgICBcIiE9XCIgfFxyXG4gICAgXCI8XCIgfFxyXG4gICAgXCI8PVwiIHxcclxuICAgIFwiPlwiIHxcclxuICAgIFwiPj1cIiB8XHJcbiAgICBcInN0cmluZ1wiIHxcclxuICAgIFwibnVtYmVyXCIgfFxyXG4gICAgXCJib29sZWFuXCI7XHJcblxyXG5jb25zdCBvcmRlcmVkT3BlcmF0b3JzOiBBcnJheTxUb2tlblR5cGU+ID0gW1xyXG4gICAgXCIvXCIsXHJcbiAgICBcIipcIixcclxuICAgIFwiLVwiLFxyXG4gICAgXCIrXCIsXHJcbiAgICBcIj09XCIsXHJcbiAgICBcIiE9XCIsXHJcbiAgICBcIjxcIixcclxuICAgIFwiPD1cIixcclxuICAgIFwiPlwiLFxyXG4gICAgXCI+PVwiXHJcbl07XHJcblxyXG5jb25zdCBsaXRlcmFsczogQXJyYXk8VG9rZW5UeXBlPiA9IFtcclxuICAgIFwiaWRlbnRpZmllclwiLFxyXG4gICAgXCJzdHJpbmdcIixcclxuICAgIFwibnVtYmVyXCIsXHJcbiAgICBcImJvb2xlYW5cIlxyXG5dO1xyXG5cclxuaW50ZXJmYWNlIFRva2VuaXplclJ1bGUge1xyXG4gICAgdG9rZW5UeXBlOiBUb2tlblR5cGU7XHJcbiAgICByZWdFeDogUmVnRXhwO1xyXG59XHJcblxyXG5pbnRlcmZhY2UgVG9rZW4ge1xyXG4gICAgdHlwZTogVG9rZW5UeXBlO1xyXG4gICAgdmFsdWU6IHN0cmluZztcclxuICAgIG9yaWdpbmFsUG9zaXRpb246IG51bWJlcjtcclxufVxyXG5cclxuY2xhc3MgVG9rZW5pemVyIHtcclxuICAgIHN0YXRpYyBydWxlczogQXJyYXk8VG9rZW5pemVyUnVsZT4gPSBbXTtcclxuXHJcbiAgICBzdGF0aWMgaW5pdCgpIHtcclxuICAgICAgICBUb2tlbml6ZXIucnVsZXMucHVzaChcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IHVuZGVmaW5lZCwgcmVnRXg6IC9eXFxzLyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCJ7XCIsIHJlZ0V4OiAvXnsvIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcIj8jXCIsIHJlZ0V4OiAvXlxcPyMvIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcIn1cIiwgcmVnRXg6IC9efS8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiW1wiLCByZWdFeDogL15cXFsvIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcIl1cIiwgcmVnRXg6IC9eXFxdLyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCIoXCIsIHJlZ0V4OiAvXlxcKC8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiKVwiLCByZWdFeDogL15cXCkvIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcImJvb2xlYW5cIiwgcmVnRXg6IC9edHJ1ZXxeZmFsc2UvIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcImlkZW50aWZpZXJcIiwgcmVnRXg6IC9eWyRhLXpfXSsvaSB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCIuXCIsIHJlZ0V4OiAvXlxcLi8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiLFwiLCByZWdFeDogL14sLyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCIrXCIsIHJlZ0V4OiAvXlxcKy8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiLVwiLCByZWdFeDogL14tLyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCIqXCIsIHJlZ0V4OiAvXlxcKi8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiL1wiLCByZWdFeDogL15cXC8vIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcIj09XCIsIHJlZ0V4OiAvXj09LyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCIhPVwiLCByZWdFeDogL14hPS8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiPD1cIiwgcmVnRXg6IC9ePD0vIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcIjxcIiwgcmVnRXg6IC9ePC8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiPj1cIiwgcmVnRXg6IC9ePj0vIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcIj5cIiwgcmVnRXg6IC9ePi8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwic3RyaW5nXCIsIHJlZ0V4OiAvXlwiKFteXCJdKilcIi8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwic3RyaW5nXCIsIHJlZ0V4OiAvXicoW14nXSopJy8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwibnVtYmVyXCIsIHJlZ0V4OiAvXlxcZCpcXC4/XFxkKy8gfVxyXG4gICAgICAgIClcclxuICAgIH1cclxuXHJcbiAgICBzdGF0aWMgcGFyc2UoZXhwcmVzc2lvbjogc3RyaW5nKTogVG9rZW5bXSB7XHJcbiAgICAgICAgbGV0IHJlc3VsdDogVG9rZW5bXSA9IFtdO1xyXG4gICAgICAgIGxldCBpID0gMDtcclxuXHJcbiAgICAgICAgd2hpbGUgKGkgPCBleHByZXNzaW9uLmxlbmd0aCkge1xyXG4gICAgICAgICAgICBsZXQgc3ViRXhwcmVzc2lvbiA9IGV4cHJlc3Npb24uc3Vic3RyaW5nKGkpO1xyXG4gICAgICAgICAgICBsZXQgbWF0Y2hGb3VuZCA9IGZhbHNlO1xyXG5cclxuICAgICAgICAgICAgZm9yIChsZXQgcnVsZSBvZiBUb2tlbml6ZXIucnVsZXMpIHtcclxuICAgICAgICAgICAgICAgIGxldCBtYXRjaGVzID0gcnVsZS5yZWdFeC5leGVjKHN1YkV4cHJlc3Npb24pO1xyXG5cclxuICAgICAgICAgICAgICAgIGlmIChtYXRjaGVzKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKG1hdGNoZXMubGVuZ3RoID4gMikge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICB0aHJvdyBuZXcgRXJyb3IoXCJBIHRva2VuaXplciBydWxlIG1hdGNoZWQgbW9yZSB0aGFuIG9uZSBncm91cC5cIik7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgICAgICBpZiAocnVsZS50b2tlblR5cGUgIT0gdW5kZWZpbmVkKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdC5wdXNoKFxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIHR5cGU6IHJ1bGUudG9rZW5UeXBlLFxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIHZhbHVlOiBtYXRjaGVzW21hdGNoZXMubGVuZ3RoID09IDEgPyAwIDogMV0sXHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgb3JpZ2luYWxQb3NpdGlvbjogaVxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgICAgICApXHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgICAgICBpICs9IG1hdGNoZXNbMF0ubGVuZ3RoO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBtYXRjaEZvdW5kID0gdHJ1ZTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgIGlmICghbWF0Y2hGb3VuZCkge1xyXG4gICAgICAgICAgICAgICAgdGhyb3cgbmV3IEVycm9yKFwiVW5leHBlY3RlZCBjaGFyYWN0ZXIgXCIgKyBzdWJFeHByZXNzaW9uWzBdICsgXCIgYXQgcG9zaXRpb24gXCIgKyBpKTtcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgIH1cclxuXHJcbiAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgIH1cclxufVxyXG5cclxuVG9rZW5pemVyLmluaXQoKTtcclxuXHJcbnR5cGUgTGl0ZXJhbFZhbHVlID0gc3RyaW5nIHwgbnVtYmVyIHwgYm9vbGVhbjtcclxuXHJcbmZ1bmN0aW9uIGVuc3VyZVZhbHVlVHlwZSh2YWx1ZTogYW55KTogTGl0ZXJhbFZhbHVlIHtcclxuICAgIGlmICh0eXBlb2YgdmFsdWUgPT09IFwibnVtYmVyXCIgfHwgdHlwZW9mIHZhbHVlID09PSBcInN0cmluZ1wiIHx8IHR5cGVvZiB2YWx1ZSA9PT0gXCJib29sZWFuXCIpIHtcclxuICAgICAgICByZXR1cm4gdmFsdWU7XHJcbiAgICB9XHJcblxyXG4gICAgdGhyb3cgbmV3IEVycm9yKFwiSW52YWxpZCB2YWx1ZSB0eXBlOiBcIiArIHR5cGVvZiB2YWx1ZSk7XHJcbn1cclxuXHJcbnR5cGUgRnVuY3Rpb25DYWxsYmFjayA9IChwYXJhbXM6IGFueVtdKSA9PiBhbnk7XHJcbnR5cGUgRnVuY3Rpb25EaWN0aW9uYXJ5ID0geyBba2V5OiBzdHJpbmddOiBGdW5jdGlvbkNhbGxiYWNrIH07XHJcblxyXG5pbnRlcmZhY2UgRXZhbHVhdGlvbkNvbnRleHRTdGF0ZSB7XHJcbiAgICAkZGF0YTogYW55O1xyXG4gICAgJGluZGV4OiBhbnk7XHJcbn1cclxuXHJcbmV4cG9ydCBjbGFzcyBFdmFsdWF0aW9uQ29udGV4dCB7XHJcbiAgICBwcml2YXRlIHN0YXRpYyByZWFkb25seSBfcmVzZXJ2ZWRGaWVsZHMgPSBbXCIkZGF0YVwiLCBcIiRyb290XCIsIFwiJGluZGV4XCJdO1xyXG4gICAgcHJpdmF0ZSBzdGF0aWMgX2J1aWx0SW5GdW5jdGlvbnM6IEZ1bmN0aW9uRGljdGlvbmFyeSA9IHt9XHJcblxyXG4gICAgc3RhdGljIGluaXQoKSB7XHJcbiAgICAgICAgRXZhbHVhdGlvbkNvbnRleHQuX2J1aWx0SW5GdW5jdGlvbnNbXCJzdWJzdHJcIl0gPSAocGFyYW1zOiBhbnlbXSkgPT4ge1xyXG4gICAgICAgICAgICByZXR1cm4gKDxzdHJpbmc+cGFyYW1zWzBdKS5zdWJzdHIoPG51bWJlcj5wYXJhbXNbMV0sIDxudW1iZXI+cGFyYW1zWzJdKTtcclxuICAgICAgICB9O1xyXG4gICAgICAgIEV2YWx1YXRpb25Db250ZXh0Ll9idWlsdEluRnVuY3Rpb25zW1wiSlNPTi5wYXJzZVwiXSA9IChwYXJhbXM6IGFueVtdKSA9PiB7XHJcbiAgICAgICAgICAgIHJldHVybiBKU09OLnBhcnNlKHBhcmFtc1swXSk7XHJcbiAgICAgICAgfTtcclxuICAgICAgICBFdmFsdWF0aW9uQ29udGV4dC5fYnVpbHRJbkZ1bmN0aW9uc1tcImlmXCJdID0gKHBhcmFtczogYW55W10pID0+IHtcclxuICAgICAgICAgICAgcmV0dXJuIHBhcmFtc1swXSA/IHBhcmFtc1sxXSA6IHBhcmFtc1syXTtcclxuICAgICAgICB9O1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgX2Z1bmN0aW9ucyA9IHt9O1xyXG4gICAgcHJpdmF0ZSBfc3RhdGVTdGFjazogRXZhbHVhdGlvbkNvbnRleHRTdGF0ZVtdID0gW107XHJcblxyXG4gICAgJHJvb3Q6IGFueTtcclxuICAgICRkYXRhOiBhbnk7XHJcbiAgICAkaW5kZXg6IG51bWJlcjtcclxuXHJcbiAgICByZWdpc3RlckZ1bmN0aW9uKG5hbWU6IHN0cmluZywgY2FsbGJhY2s6IEZ1bmN0aW9uQ2FsbGJhY2spIHtcclxuICAgICAgICB0aGlzLl9mdW5jdGlvbnNbbmFtZV0gPSBjYWxsYmFjaztcclxuICAgIH1cclxuXHJcbiAgICB1bnJlZ2lzdGVyRnVuY3Rpb24obmFtZTogc3RyaW5nKSB7XHJcbiAgICAgICAgZGVsZXRlIHRoaXMuX2Z1bmN0aW9uc1tuYW1lXTtcclxuXHR9XHJcblxyXG4gICAgZ2V0RnVuY3Rpb24obmFtZTogc3RyaW5nKTogRnVuY3Rpb25DYWxsYmFjayB7XHJcbiAgICAgICAgbGV0IHJlc3VsdCA9IHRoaXMuX2Z1bmN0aW9uc1tuYW1lXTtcclxuXHJcbiAgICAgICAgaWYgKHJlc3VsdCA9PSB1bmRlZmluZWQpIHtcclxuICAgICAgICAgICAgcmVzdWx0ID0gRXZhbHVhdGlvbkNvbnRleHQuX2J1aWx0SW5GdW5jdGlvbnNbbmFtZV07XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICByZXR1cm4gcmVzdWx0O1xyXG4gICAgfVxyXG5cclxuICAgIGlzUmVzZXJ2ZWRGaWVsZChuYW1lOiBzdHJpbmcpOiBib29sZWFuIHtcclxuICAgICAgICByZXR1cm4gRXZhbHVhdGlvbkNvbnRleHQuX3Jlc2VydmVkRmllbGRzLmluZGV4T2YobmFtZSkgPj0gMDtcclxuICAgIH1cclxuXHJcbiAgICBzYXZlU3RhdGUoKSB7XHJcbiAgICAgICAgdGhpcy5fc3RhdGVTdGFjay5wdXNoKHsgJGRhdGE6IHRoaXMuJGRhdGEsICRpbmRleDogdGhpcy4kaW5kZXggfSk7XHJcbiAgICB9XHJcblxyXG4gICAgcmVzdG9yZUxhc3RTdGF0ZSgpIHtcclxuICAgICAgICBpZiAodGhpcy5fc3RhdGVTdGFjay5sZW5ndGggPT0gMCkge1xyXG4gICAgICAgICAgICB0aHJvdyBuZXcgRXJyb3IoXCJUaGVyZSBpcyBubyBldmFsdWF0aW9uIGNvbnRleHQgc3RhdGUgdG8gcmVzdG9yZS5cIik7XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICBsZXQgc2F2ZWRDb250ZXh0ID0gdGhpcy5fc3RhdGVTdGFjay5wb3AoKTtcclxuXHJcbiAgICAgICAgdGhpcy4kZGF0YSA9IHNhdmVkQ29udGV4dC4kZGF0YTtcclxuICAgICAgICB0aGlzLiRpbmRleCA9IHNhdmVkQ29udGV4dC4kaW5kZXg7XHJcbiAgICB9XHJcblxyXG4gICAgZ2V0IGN1cnJlbnREYXRhQ29udGV4dCgpOiBhbnkge1xyXG4gICAgICAgIHJldHVybiB0aGlzLiRkYXRhICE9IHVuZGVmaW5lZCA/IHRoaXMuJGRhdGEgOiB0aGlzLiRyb290O1xyXG4gICAgfVxyXG59XHJcblxyXG5FdmFsdWF0aW9uQ29udGV4dC5pbml0KCk7XHJcblxyXG5hYnN0cmFjdCBjbGFzcyBFdmFsdWF0aW9uTm9kZSB7XHJcbiAgICBhYnN0cmFjdCBldmFsdWF0ZShjb250ZXh0OiBFdmFsdWF0aW9uQ29udGV4dCk6IExpdGVyYWxWYWx1ZTtcclxufVxyXG5cclxuY2xhc3MgRXhwcmVzc2lvbk5vZGUgZXh0ZW5kcyBFdmFsdWF0aW9uTm9kZSB7XHJcbiAgICBub2RlczogQXJyYXk8RXZhbHVhdGlvbk5vZGU+ID0gW107XHJcbiAgICBhbGxvd051bGw6IGJvb2xlYW4gPSB0cnVlO1xyXG5cclxuICAgIGV2YWx1YXRlKGNvbnRleHQ6IEV2YWx1YXRpb25Db250ZXh0KTogYW55IHtcclxuICAgICAgICBjb25zdCBvcGVyYXRvclByaW9yaXR5R3JvdXBzID0gW1xyXG4gICAgICAgICAgICBbXCIvXCIsIFwiKlwiXSxcclxuICAgICAgICAgICAgW1wiLVwiLCBcIitcIl0sXHJcbiAgICAgICAgICAgIFtcIj09XCIsIFwiIT1cIiwgXCI8XCIsIFwiPD1cIiwgXCI+XCIsIFwiPj1cIl1cclxuICAgICAgICBdO1xyXG5cclxuICAgICAgICBsZXQgbm9kZXNDb3B5ID0gdGhpcy5ub2RlcztcclxuXHJcbiAgICAgICAgZm9yIChsZXQgcHJpb3JpdHlHcm91cCBvZiBvcGVyYXRvclByaW9yaXR5R3JvdXBzKSB7XHJcbiAgICAgICAgICAgIGxldCBpID0gMDtcclxuXHJcbiAgICAgICAgICAgIHdoaWxlIChpIDwgbm9kZXNDb3B5Lmxlbmd0aCkge1xyXG4gICAgICAgICAgICAgICAgbGV0IG5vZGUgPSBub2Rlc0NvcHlbaV07XHJcblxyXG4gICAgICAgICAgICAgICAgaWYgKG5vZGUgaW5zdGFuY2VvZiBPcGVyYXRvck5vZGUgJiYgcHJpb3JpdHlHcm91cC5pbmRleE9mKG5vZGUub3BlcmF0b3IpID49IDApIHtcclxuICAgICAgICAgICAgICAgICAgICBsZXQgbGVmdCA9IGVuc3VyZVZhbHVlVHlwZShub2Rlc0NvcHlbaSAtIDFdLmV2YWx1YXRlKGNvbnRleHQpKTtcclxuICAgICAgICAgICAgICAgICAgICBsZXQgcmlnaHQgPSBlbnN1cmVWYWx1ZVR5cGUobm9kZXNDb3B5W2kgKyAxXS5ldmFsdWF0ZShjb250ZXh0KSk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGlmICh0eXBlb2YgbGVmdCAhPT0gdHlwZW9mIHJpZ2h0KSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHRocm93IG5ldyBFcnJvcihcIkluY29tcGF0aWJsZSBvcGVyYW5kcyBcIiArIGxlZnQgKyBcIiBhbmQgXCIgKyByaWdodCArIFwiIGZvciBvcGVyYXRvciBcIiArIG5vZGUub3BlcmF0b3IpO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgICAgICAgICAgbGV0IHJlc3VsdDogTGl0ZXJhbFZhbHVlO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBpZiAodHlwZW9mIGxlZnQgPT09IFwibnVtYmVyXCIgJiYgdHlwZW9mIHJpZ2h0ID09PSBcIm51bWJlclwiKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHN3aXRjaCAobm9kZS5vcGVyYXRvcikge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgY2FzZSBcIi9cIjpcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQgPSBsZWZ0IC8gcmlnaHQ7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBjYXNlIFwiKlwiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IGxlZnQgKiByaWdodDtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGNhc2UgXCItXCI6XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gbGVmdCAtIHJpZ2h0O1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgY2FzZSBcIitcIjpcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQgPSBsZWZ0ICsgcmlnaHQ7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGlmICh0eXBlb2YgbGVmdCA9PT0gXCJzdHJpbmdcIiAmJiB0eXBlb2YgcmlnaHQgPT09IFwic3RyaW5nXCIpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgc3dpdGNoIChub2RlLm9wZXJhdG9yKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBjYXNlIFwiK1wiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IGxlZnQgKyByaWdodDtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgICAgICAgICAgc3dpdGNoIChub2RlLm9wZXJhdG9yKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGNhc2UgXCI9PVwiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gbGVmdCA9PSByaWdodDtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBjYXNlIFwiIT1cIjpcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IGxlZnQgIT0gcmlnaHQ7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgICAgICAgICAgY2FzZSBcIjxcIjpcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IGxlZnQgPCByaWdodDtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBjYXNlIFwiPD1cIjpcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IGxlZnQgPD0gcmlnaHQ7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgICAgICAgICAgY2FzZSBcIj5cIjpcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IGxlZnQgPiByaWdodDtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBjYXNlIFwiPj1cIjpcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IGxlZnQgPj0gcmlnaHQ7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgICAgICAgICAgZGVmYXVsdDpcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIC8vIFRoaXMgc2hvdWxkIG5ldmVyIGhhcHBlblxyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgICAgICAgICAgbm9kZXNDb3B5LnNwbGljZShpIC0gMSwgMywgbmV3IExpdGVyYWxOb2RlKHJlc3VsdCkpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBpLS07XHJcbiAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgaSsrO1xyXG4gICAgICAgICAgICB9O1xyXG4gICAgICAgIH1cclxuXHJcbiAgICAgICAgcmV0dXJuIG5vZGVzQ29weVswXS5ldmFsdWF0ZShjb250ZXh0KTtcclxuICAgIH1cclxufVxyXG5cclxuY2xhc3MgSWRlbnRpZmllck5vZGUgZXh0ZW5kcyBFdmFsdWF0aW9uTm9kZSB7XHJcbiAgICBpZGVudGlmaWVyOiBzdHJpbmc7XHJcblxyXG4gICAgZXZhbHVhdGUoY29udGV4dDogRXZhbHVhdGlvbkNvbnRleHQpOiBMaXRlcmFsVmFsdWUge1xyXG4gICAgICAgIHJldHVybiB0aGlzLmlkZW50aWZpZXI7XHJcbiAgICB9XHJcbn1cclxuXHJcbmNsYXNzIEluZGV4ZXJOb2RlIGV4dGVuZHMgRXZhbHVhdGlvbk5vZGUge1xyXG4gICAgaW5kZXg6IEV4cHJlc3Npb25Ob2RlO1xyXG5cclxuICAgIGV2YWx1YXRlKGNvbnRleHQ6IEV2YWx1YXRpb25Db250ZXh0KTogTGl0ZXJhbFZhbHVlIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5pbmRleC5ldmFsdWF0ZShjb250ZXh0KTtcclxuICAgIH1cclxufVxyXG5cclxuY2xhc3MgRnVuY3Rpb25DYWxsTm9kZSBleHRlbmRzIEV2YWx1YXRpb25Ob2RlIHtcclxuICAgIGZ1bmN0aW9uTmFtZTogc3RyaW5nID0gbnVsbDtcclxuICAgIHBhcmFtZXRlcnM6IEFycmF5PEV4cHJlc3Npb25Ob2RlPiA9IFtdO1xyXG5cclxuICAgIGV2YWx1YXRlKGNvbnRleHQ6IEV2YWx1YXRpb25Db250ZXh0KTogTGl0ZXJhbFZhbHVlIHtcclxuICAgICAgICBsZXQgY2FsbGJhY2sgPSBjb250ZXh0LmdldEZ1bmN0aW9uKHRoaXMuZnVuY3Rpb25OYW1lKTtcclxuXHJcbiAgICAgICAgaWYgKGNhbGxiYWNrICE9IHVuZGVmaW5lZCkge1xyXG4gICAgICAgICAgICBsZXQgZXZhbHVhdGVkUGFyYW1zID0gW107XHJcblxyXG4gICAgICAgICAgICBmb3IgKGxldCBwYXJhbSBvZiB0aGlzLnBhcmFtZXRlcnMpIHtcclxuICAgICAgICAgICAgICAgIGV2YWx1YXRlZFBhcmFtcy5wdXNoKHBhcmFtLmV2YWx1YXRlKGNvbnRleHQpKTtcclxuICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgcmV0dXJuIGNhbGxiYWNrKGV2YWx1YXRlZFBhcmFtcyk7XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICB0aHJvdyBuZXcgRXJyb3IoXCJVbmRlZmluZWQgZnVuY3Rpb246IFwiICsgdGhpcy5mdW5jdGlvbk5hbWUpO1xyXG4gICAgfVxyXG59XHJcblxyXG5jbGFzcyBMaXRlcmFsTm9kZSBleHRlbmRzIEV2YWx1YXRpb25Ob2RlIHtcclxuICAgIGNvbnN0cnVjdG9yKHJlYWRvbmx5IHZhbHVlOiBMaXRlcmFsVmFsdWUpIHtcclxuICAgICAgICBzdXBlcigpO1xyXG4gICAgfVxyXG5cclxuICAgIGV2YWx1YXRlKGNvbnRleHQ6IEV2YWx1YXRpb25Db250ZXh0KTogTGl0ZXJhbFZhbHVlIHtcclxuICAgICAgICByZXR1cm4gdGhpcy52YWx1ZTtcclxuICAgIH1cclxufVxyXG5cclxuY2xhc3MgT3BlcmF0b3JOb2RlIGV4dGVuZHMgRXZhbHVhdGlvbk5vZGUge1xyXG4gICAgY29uc3RydWN0b3IocmVhZG9ubHkgb3BlcmF0b3I6IFRva2VuVHlwZSkge1xyXG4gICAgICAgIHN1cGVyKCk7XHJcbiAgICB9XHJcblxyXG4gICAgZXZhbHVhdGUoY29udGV4dDogRXZhbHVhdGlvbkNvbnRleHQpOiBMaXRlcmFsVmFsdWUge1xyXG4gICAgICAgIHRocm93IG5ldyBFcnJvcihcIkFuIG9wZXJhdG9yIGNhbm5vdCBiZSBldmFsdWF0ZWQgb24gaXRzIG93bi5cIik7XHJcbiAgICB9XHJcbn1cclxuXHJcbnR5cGUgUGF0aFBhcnQgPSBFeHByZXNzaW9uTm9kZSB8IElkZW50aWZpZXJOb2RlIHwgSW5kZXhlck5vZGUgfCBGdW5jdGlvbkNhbGxOb2RlO1xyXG5cclxuY2xhc3MgUGF0aE5vZGUgZXh0ZW5kcyBFdmFsdWF0aW9uTm9kZSB7XHJcbiAgICBwYXJ0czogUGF0aFBhcnRbXSA9IFtdO1xyXG5cclxuICAgIGV2YWx1YXRlKGNvbnRleHQ6IEV2YWx1YXRpb25Db250ZXh0KTogTGl0ZXJhbFZhbHVlIHtcclxuICAgICAgICBsZXQgcmVzdWx0OiBhbnkgPSB1bmRlZmluZWQ7XHJcbiAgICAgICAgbGV0IGluZGV4ID0gMDtcclxuXHJcbiAgICAgICAgd2hpbGUgKGluZGV4IDwgdGhpcy5wYXJ0cy5sZW5ndGgpIHtcclxuICAgICAgICAgICAgbGV0IHBhcnQgPSB0aGlzLnBhcnRzW2luZGV4XTtcclxuXHJcbiAgICAgICAgICAgIHRyeSB7XHJcbiAgICAgICAgICAgICAgICBpZiAocGFydCBpbnN0YW5jZW9mIElkZW50aWZpZXJOb2RlICYmIGluZGV4ID09IDApIHtcclxuICAgICAgICAgICAgICAgICAgICBzd2l0Y2ggKHBhcnQuaWRlbnRpZmllcikge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBjYXNlIFwiJHJvb3RcIjpcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IGNvbnRleHQuJHJvb3Q7XHJcbiAgICAgICAgICAgIFxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGNhc2UgXCIkZGF0YVwiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gY29udGV4dC5jdXJyZW50RGF0YUNvbnRleHQ7XHJcbiAgICAgICAgICAgIFxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGNhc2UgXCIkaW5kZXhcIjpcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IGNvbnRleHQuJGluZGV4O1xyXG4gICAgICAgICAgICBcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBkZWZhdWx0OlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gY29udGV4dC5jdXJyZW50RGF0YUNvbnRleHRbcGFydC5pZGVudGlmaWVyXTtcclxuICAgICAgICAgICAgXHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgICAgICB9ICAgICAgICAgICAgXHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICBsZXQgcGFydFZhbHVlID0gcGFydC5ldmFsdWF0ZShjb250ZXh0KTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKGluZGV4ID09IDApIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gcGFydFZhbHVlO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gdHlwZW9mIHBhcnRWYWx1ZSAhPT0gXCJib29sZWFuXCIgPyByZXN1bHRbcGFydFZhbHVlXSA6IHJlc3VsdFtwYXJ0VmFsdWUudG9TdHJpbmcoKV07XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIGNhdGNoIChlKSB7XHJcbiAgICAgICAgICAgICAgICByZXR1cm4gdW5kZWZpbmVkO1xyXG4gICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICBpbmRleCsrO1xyXG4gICAgICAgIH1cclxuXHJcbiAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgIH1cclxufVxyXG5cclxuZXhwb3J0IGNsYXNzIEV4cHJlc3Npb25QYXJzZXIge1xyXG4gICAgcHJpdmF0ZSBfaW5kZXg6IG51bWJlciA9IDA7XHJcbiAgICBwcml2YXRlIF90b2tlbnM6IFRva2VuW107XHJcblxyXG4gICAgcHJpdmF0ZSB1bmV4cGVjdGVkVG9rZW4oKSB7XHJcbiAgICAgICAgdGhyb3cgbmV3IEVycm9yKFwiVW5leHBlY3RlZCB0b2tlbiBcIiArIHRoaXMuY3VycmVudC52YWx1ZSArIFwiIGF0IHBvc2l0aW9uIFwiICsgdGhpcy5jdXJyZW50Lm9yaWdpbmFsUG9zaXRpb24gKyBcIi5cIik7XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSB1bmV4cGVjdGVkRW9lKCkge1xyXG4gICAgICAgIHRocm93IG5ldyBFcnJvcihcIlVuZXhwZWN0ZWQgZW5kIG9mIGV4cHJlc3Npb24uXCIpO1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgbW92ZU5leHQoKSB7XHJcbiAgICAgICAgdGhpcy5faW5kZXgrKztcclxuICAgIH1cclxuXHJcbiAgICBwcml2YXRlIHBhcnNlVG9rZW4oLi4uZXhwZWN0ZWRUb2tlblR5cGVzOiBUb2tlblR5cGVbXSk6IFRva2VuIHtcclxuICAgICAgICBpZiAodGhpcy5lb2UpIHtcclxuICAgICAgICAgICAgdGhpcy51bmV4cGVjdGVkRW9lKCk7XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICBsZXQgY3VycmVudFRva2VuID0gdGhpcy5jdXJyZW50O1xyXG5cclxuICAgICAgICBpZiAoZXhwZWN0ZWRUb2tlblR5cGVzLmluZGV4T2YodGhpcy5jdXJyZW50LnR5cGUpIDwgMCkge1xyXG4gICAgICAgICAgICB0aGlzLnVuZXhwZWN0ZWRUb2tlbigpO1xyXG4gICAgICAgIH1cclxuXHJcbiAgICAgICAgdGhpcy5tb3ZlTmV4dCgpO1xyXG5cclxuICAgICAgICByZXR1cm4gY3VycmVudFRva2VuO1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgcGFyc2VPcHRpb25hbFRva2VuKC4uLmV4cGVjdGVkVG9rZW5UeXBlczogVG9rZW5UeXBlW10pOiBib29sZWFuIHtcclxuICAgICAgICBpZiAodGhpcy5lb2UpIHtcclxuICAgICAgICAgICAgdGhpcy51bmV4cGVjdGVkRW9lKCk7XHJcbiAgICAgICAgfVxyXG4gICAgICAgIGVsc2UgaWYgKGV4cGVjdGVkVG9rZW5UeXBlcy5pbmRleE9mKHRoaXMuY3VycmVudC50eXBlKSA8IDApIHtcclxuICAgICAgICAgICAgcmV0dXJuIGZhbHNlO1xyXG4gICAgICAgIH1cclxuICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgdGhpcy5tb3ZlTmV4dCgpO1xyXG5cclxuICAgICAgICAgICAgcmV0dXJuIHRydWU7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgcGFyc2VGdW5jdGlvbkNhbGwoZnVuY3Rpb25OYW1lOiBzdHJpbmcpOiBGdW5jdGlvbkNhbGxOb2RlIHtcclxuICAgICAgICBsZXQgcmVzdWx0ID0gbmV3IEZ1bmN0aW9uQ2FsbE5vZGUoKTtcclxuICAgICAgICByZXN1bHQuZnVuY3Rpb25OYW1lID0gZnVuY3Rpb25OYW1lO1xyXG5cclxuICAgICAgICB0aGlzLnBhcnNlVG9rZW4oXCIoXCIpO1xyXG5cclxuICAgICAgICBsZXQgZmlyc3RQYXJhbWV0ZXIgPSB0aGlzLnBhcnNlRXhwcmVzc2lvbigpO1xyXG4gICAgICAgIGxldCBtb3JlUGFyYW1ldGVyczogYm9vbGVhbiA9IGZhbHNlO1xyXG5cclxuICAgICAgICBpZiAoZmlyc3RQYXJhbWV0ZXIpIHtcclxuICAgICAgICAgICAgcmVzdWx0LnBhcmFtZXRlcnMucHVzaChmaXJzdFBhcmFtZXRlcik7XHJcblxyXG4gICAgICAgICAgICBkbyB7XHJcbiAgICAgICAgICAgICAgICBtb3JlUGFyYW1ldGVycyA9IHRoaXMucGFyc2VPcHRpb25hbFRva2VuKFwiLFwiKTtcclxuXHJcbiAgICAgICAgICAgICAgICBpZiAobW9yZVBhcmFtZXRlcnMpIHtcclxuICAgICAgICAgICAgICAgICAgICBsZXQgcGFyYW1ldGVyID0gdGhpcy5wYXJzZUV4cHJlc3Npb24oKTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgcmVzdWx0LnBhcmFtZXRlcnMucHVzaChwYXJhbWV0ZXIpO1xyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICB9IHdoaWxlIChtb3JlUGFyYW1ldGVycyk7XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICB0aGlzLnBhcnNlVG9rZW4oXCIpXCIpO1xyXG5cclxuICAgICAgICByZXR1cm4gcmVzdWx0O1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgcGFyc2VJZGVudGlmaWVyKCk6IElkZW50aWZpZXJOb2RlIHtcclxuICAgICAgICBsZXQgcmVzdWx0ID0gbmV3IElkZW50aWZpZXJOb2RlKCk7XHJcblxyXG4gICAgICAgIHJlc3VsdC5pZGVudGlmaWVyID0gdGhpcy5jdXJyZW50LnZhbHVlO1xyXG5cclxuICAgICAgICB0aGlzLm1vdmVOZXh0KCk7XHJcblxyXG4gICAgICAgIHJldHVybiByZXN1bHQ7XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBwYXJzZUluZGV4ZXIoKTogSW5kZXhlck5vZGUge1xyXG4gICAgICAgIGxldCByZXN1bHQgPSBuZXcgSW5kZXhlck5vZGUoKTtcclxuXHJcbiAgICAgICAgdGhpcy5wYXJzZVRva2VuKFwiW1wiKTtcclxuXHJcbiAgICAgICAgcmVzdWx0LmluZGV4ID0gdGhpcy5wYXJzZUV4cHJlc3Npb24oKTtcclxuXHJcbiAgICAgICAgdGhpcy5wYXJzZVRva2VuKFwiXVwiKTtcclxuXHJcbiAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgIH1cclxuXHJcbiAgICBwcml2YXRlIHBhcnNlUGF0aCgpOiBQYXRoTm9kZSB7XHJcbiAgICAgICAgbGV0IHJlc3VsdCA9IG5ldyBQYXRoTm9kZSgpO1xyXG5cclxuICAgICAgICBsZXQgZXhwZWN0ZWROZXh0VG9rZW5UeXBlczogVG9rZW5UeXBlW10gPSBbXCJpZGVudGlmaWVyXCIsIFwiKFwiXTtcclxuXHJcbiAgICAgICAgd2hpbGUgKCF0aGlzLmVvZSkge1xyXG4gICAgICAgICAgICBpZiAoZXhwZWN0ZWROZXh0VG9rZW5UeXBlcy5pbmRleE9mKHRoaXMuY3VycmVudC50eXBlKSA8IDApIHtcclxuICAgICAgICAgICAgICAgIHJldHVybiByZXN1bHQ7XHJcbiAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgIHN3aXRjaCAodGhpcy5jdXJyZW50LnR5cGUpIHtcclxuICAgICAgICAgICAgICAgIGNhc2UgXCIoXCI6XHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKHJlc3VsdC5wYXJ0cy5sZW5ndGggPT0gMCkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICB0aGlzLm1vdmVOZXh0KCk7XHJcbiAgICBcclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0LnBhcnRzLnB1c2godGhpcy5wYXJzZUV4cHJlc3Npb24oKSk7XHJcbiAgICBcclxuICAgICAgICAgICAgICAgICAgICAgICAgdGhpcy5wYXJzZVRva2VuKFwiKVwiKTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGxldCBmdW5jdGlvbk5hbWU6IHN0cmluZyA9IFwiXCI7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgICAgICBmb3IgKGxldCBwYXJ0IG9mIHJlc3VsdC5wYXJ0cykge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgaWYgKCEocGFydCBpbnN0YW5jZW9mIElkZW50aWZpZXJOb2RlKSkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIHRoaXMudW5leHBlY3RlZFRva2VuKCk7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgaWYgKGZ1bmN0aW9uTmFtZSAhPSBcIlwiKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgZnVuY3Rpb25OYW1lICs9IFwiLlwiO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGZ1bmN0aW9uTmFtZSArPSAoPElkZW50aWZpZXJOb2RlPnBhcnQpLmlkZW50aWZpZXI7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdC5wYXJ0cyA9IFtdO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0LnBhcnRzLnB1c2godGhpcy5wYXJzZUZ1bmN0aW9uQ2FsbChmdW5jdGlvbk5hbWUpKTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGV4cGVjdGVkTmV4dFRva2VuVHlwZXMgPSBbXCIuXCIsIFwiW1wiXTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICBjYXNlIFwiW1wiOlxyXG4gICAgICAgICAgICAgICAgICAgIHJlc3VsdC5wYXJ0cy5wdXNoKHRoaXMucGFyc2VJbmRleGVyKCkpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBleHBlY3RlZE5leHRUb2tlblR5cGVzID0gW1wiLlwiLCBcIihcIiwgXCJbXCJdO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgIGNhc2UgXCJpZGVudGlmaWVyXCI6XHJcbiAgICAgICAgICAgICAgICAgICAgcmVzdWx0LnBhcnRzLnB1c2godGhpcy5wYXJzZUlkZW50aWZpZXIoKSk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGV4cGVjdGVkTmV4dFRva2VuVHlwZXMgPSBbXCIuXCIsIFwiKFwiLCBcIltcIl07XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgY2FzZSBcIi5cIjpcclxuICAgICAgICAgICAgICAgICAgICB0aGlzLm1vdmVOZXh0KCk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGV4cGVjdGVkTmV4dFRva2VuVHlwZXMgPSBbXCJpZGVudGlmaWVyXCJdO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgIGRlZmF1bHQ6XHJcbiAgICAgICAgICAgICAgICAgICAgZXhwZWN0ZWROZXh0VG9rZW5UeXBlcyA9IFtdO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgIH1cclxuICAgIH1cclxuXHJcbiAgICBwcml2YXRlIHBhcnNlRXhwcmVzc2lvbigpOiBFeHByZXNzaW9uTm9kZSB7XHJcbiAgICAgICAgbGV0IHJlc3VsdDogRXhwcmVzc2lvbk5vZGUgPSBuZXcgRXhwcmVzc2lvbk5vZGUoKTtcclxuXHJcbiAgICAgICAgbGV0IGV4cGVjdGVkTmV4dFRva2VuVHlwZXM6IFRva2VuVHlwZVtdID0gbGl0ZXJhbHMuY29uY2F0KFwiKFwiLCBcIitcIiwgXCItXCIpO1xyXG5cclxuICAgICAgICB3aGlsZSAoIXRoaXMuZW9lKSB7XHJcbiAgICAgICAgICAgIGlmIChleHBlY3RlZE5leHRUb2tlblR5cGVzLmluZGV4T2YodGhpcy5jdXJyZW50LnR5cGUpIDwgMCkge1xyXG4gICAgICAgICAgICAgICAgaWYgKHJlc3VsdC5ub2Rlcy5sZW5ndGggPT0gMCkge1xyXG4gICAgICAgICAgICAgICAgICAgIHRoaXMudW5leHBlY3RlZFRva2VuKCk7XHJcbiAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgc3dpdGNoICh0aGlzLmN1cnJlbnQudHlwZSkge1xyXG4gICAgICAgICAgICAgICAgY2FzZSBcIihcIjpcclxuICAgICAgICAgICAgICAgIGNhc2UgXCJpZGVudGlmaWVyXCI6XHJcbiAgICAgICAgICAgICAgICAgICAgcmVzdWx0Lm5vZGVzLnB1c2godGhpcy5wYXJzZVBhdGgoKSk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGV4cGVjdGVkTmV4dFRva2VuVHlwZXMgPSBvcmRlcmVkT3BlcmF0b3JzO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgIGNhc2UgXCJzdHJpbmdcIjpcclxuICAgICAgICAgICAgICAgIGNhc2UgXCJudW1iZXJcIjpcclxuICAgICAgICAgICAgICAgIGNhc2UgXCJib29sZWFuXCI6XHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKHRoaXMuY3VycmVudC50eXBlID09IFwic3RyaW5nXCIpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0Lm5vZGVzLnB1c2gobmV3IExpdGVyYWxOb2RlKHRoaXMuY3VycmVudC52YWx1ZSkpO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgICAgICBlbHNlIGlmICh0aGlzLmN1cnJlbnQudHlwZSA9PSBcIm51bWJlclwiKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdC5ub2Rlcy5wdXNoKG5ldyBMaXRlcmFsTm9kZShwYXJzZUZsb2F0KHRoaXMuY3VycmVudC52YWx1ZSkpKTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdC5ub2Rlcy5wdXNoKG5ldyBMaXRlcmFsTm9kZSh0aGlzLmN1cnJlbnQudmFsdWUgPT09IFwidHJ1ZVwiKSk7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgICAgICB0aGlzLm1vdmVOZXh0KCk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGV4cGVjdGVkTmV4dFRva2VuVHlwZXMgPSBvcmRlcmVkT3BlcmF0b3JzO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgIGNhc2UgXCItXCI6XHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKHJlc3VsdC5ub2Rlcy5sZW5ndGggPT0gMCkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQubm9kZXMucHVzaChuZXcgTGl0ZXJhbE5vZGUoLTEpKTtcclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0Lm5vZGVzLnB1c2gobmV3IE9wZXJhdG9yTm9kZShcIipcIikpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICAgICAgZXhwZWN0ZWROZXh0VG9rZW5UeXBlcyA9IFtcImlkZW50aWZpZXJcIiwgXCJudW1iZXJcIiwgXCIoXCJdO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0Lm5vZGVzLnB1c2gobmV3IE9wZXJhdG9yTm9kZSh0aGlzLmN1cnJlbnQudHlwZSkpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICAgICAgZXhwZWN0ZWROZXh0VG9rZW5UeXBlcyA9IGxpdGVyYWxzLmNvbmNhdChcIihcIik7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgICAgICB0aGlzLm1vdmVOZXh0KCk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgY2FzZSBcIitcIjpcclxuICAgICAgICAgICAgICAgICAgICBpZiAocmVzdWx0Lm5vZGVzLmxlbmd0aCA9PSAwKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGV4cGVjdGVkTmV4dFRva2VuVHlwZXMgPSBsaXRlcmFscy5jb25jYXQoXCIoXCIpO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0Lm5vZGVzLnB1c2gobmV3IE9wZXJhdG9yTm9kZSh0aGlzLmN1cnJlbnQudHlwZSkpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICAgICAgZXhwZWN0ZWROZXh0VG9rZW5UeXBlcyA9IGxpdGVyYWxzLmNvbmNhdChcIihcIik7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgICAgICB0aGlzLm1vdmVOZXh0KCk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgY2FzZSBcIipcIjpcclxuICAgICAgICAgICAgICAgIGNhc2UgXCIvXCI6XHJcbiAgICAgICAgICAgICAgICBjYXNlIFwiPT1cIjpcclxuICAgICAgICAgICAgICAgIGNhc2UgXCIhPVwiOlxyXG4gICAgICAgICAgICAgICAgY2FzZSBcIjxcIjpcclxuICAgICAgICAgICAgICAgIGNhc2UgXCI8PVwiOlxyXG4gICAgICAgICAgICAgICAgY2FzZSBcIj5cIjpcclxuICAgICAgICAgICAgICAgIGNhc2UgXCI+PVwiOlxyXG4gICAgICAgICAgICAgICAgICAgIHJlc3VsdC5ub2Rlcy5wdXNoKG5ldyBPcGVyYXRvck5vZGUodGhpcy5jdXJyZW50LnR5cGUpKTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgdGhpcy5tb3ZlTmV4dCgpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBleHBlY3RlZE5leHRUb2tlblR5cGVzID0gbGl0ZXJhbHMuY29uY2F0KFwiKFwiKTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICBkZWZhdWx0OlxyXG4gICAgICAgICAgICAgICAgICAgIGV4cGVjdGVkTmV4dFRva2VuVHlwZXMgPSBbXTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICB9XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBnZXQgZW9lKCk6IGJvb2xlYW4ge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl9pbmRleCA+PSB0aGlzLl90b2tlbnMubGVuZ3RoO1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgZ2V0IGN1cnJlbnQoKTogVG9rZW4ge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl90b2tlbnNbdGhpcy5faW5kZXhdO1xyXG4gICAgfVxyXG5cclxuICAgIHN0YXRpYyBwYXJzZUJpbmRpbmcoYmluZGluZ0V4cHJlc3Npb246IHN0cmluZyk6IEJpbmRpbmcge1xyXG4gICAgICAgIGxldCBwYXJzZXIgPSBuZXcgRXhwcmVzc2lvblBhcnNlcihUb2tlbml6ZXIucGFyc2UoYmluZGluZ0V4cHJlc3Npb24pKTtcclxuICAgICAgICBwYXJzZXIucGFyc2VUb2tlbihcIntcIik7XHJcblxyXG4gICAgICAgIGxldCBhbGxvd051bGwgPSAhcGFyc2VyLnBhcnNlT3B0aW9uYWxUb2tlbihcIj8jXCIpO1xyXG4gICAgICAgIGxldCBleHByZXNzaW9uID0gcGFyc2VyLnBhcnNlRXhwcmVzc2lvbigpO1xyXG5cclxuICAgICAgICBwYXJzZXIucGFyc2VUb2tlbihcIn1cIik7XHJcblxyXG4gICAgICAgIHJldHVybiBuZXcgQmluZGluZyhleHByZXNzaW9uLCBhbGxvd051bGwpO1xyXG4gICAgfVxyXG5cclxuICAgIGNvbnN0cnVjdG9yKHRva2VuczogVG9rZW5bXSkge1xyXG4gICAgICAgIHRoaXMuX3Rva2VucyA9IHRva2VucztcclxuICAgIH1cclxufVxyXG5cclxuZXhwb3J0IGNsYXNzIEJpbmRpbmcge1xyXG4gICAgY29uc3RydWN0b3IocHJpdmF0ZSByZWFkb25seSBleHByZXNzaW9uOiBFdmFsdWF0aW9uTm9kZSwgcmVhZG9ubHkgYWxsb3dOdWxsOiBib29sZWFuID0gdHJ1ZSkge31cclxuXHJcbiAgICBldmFsdWF0ZShjb250ZXh0OiBFdmFsdWF0aW9uQ29udGV4dCk6IExpdGVyYWxWYWx1ZSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuZXhwcmVzc2lvbi5ldmFsdWF0ZShjb250ZXh0KTtcclxuICAgIH1cclxufSIsImltcG9ydCB7IEJpbmRpbmcsIEV4cHJlc3Npb25QYXJzZXIsIEV2YWx1YXRpb25Db250ZXh0IH0gZnJvbSBcIi4vZXhwcmVzc2lvbi1wYXJzZXJcIjtcclxuaW1wb3J0IHsgVHJhbnNmb3JtIH0gZnJvbSBcInN0cmVhbVwiO1xyXG5cclxuY2xhc3MgVGVtcGxhdGl6ZWRTdHJpbmcge1xyXG4gICAgcHJpdmF0ZSBfcGFydHM6IEFycmF5PHN0cmluZyB8IEJpbmRpbmc+ID0gW107XHJcblxyXG4gICAgc3RhdGljIHBhcnNlKHM6IHN0cmluZyk6IHN0cmluZyB8IFRlbXBsYXRpemVkU3RyaW5nIHtcclxuICAgICAgICBsZXQgcmVzdWx0ID0gbmV3IFRlbXBsYXRpemVkU3RyaW5nKCk7XHJcbiAgICAgICAgbGV0IGkgPSAwO1xyXG5cclxuICAgICAgICBkbyB7XHJcbiAgICAgICAgICAgIGxldCBleHByZXNzaW9uRm91bmQgPSBmYWxzZTtcclxuICAgICAgICAgICAgbGV0IHN0YXJ0ID0gaTtcclxuICAgICAgICAgICAgbGV0IGxvb3A7XHJcbiAgICAgICAgICAgIFxyXG4gICAgICAgICAgICBkbyB7XHJcbiAgICAgICAgICAgICAgICBsb29wID0gZmFsc2U7XHJcblxyXG4gICAgICAgICAgICAgICAgc3RhcnQgPSBzLmluZGV4T2YoXCJ7XCIsIHN0YXJ0KTtcclxuXHJcbiAgICAgICAgICAgICAgICBpZiAoc3RhcnQgPj0gMCkge1xyXG4gICAgICAgICAgICAgICAgICAgIGlmIChzdGFydCArIDEgPCBzLmxlbmd0aCAmJiBzW3N0YXJ0ICsgMV0gPT0gXCJ7XCIpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgc3RhcnQgKz0gMjtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGxvb3AgPSB0cnVlO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgfSB3aGlsZSAobG9vcCk7XHJcblxyXG4gICAgICAgICAgICBpZiAoc3RhcnQgPj0gMCkge1xyXG4gICAgICAgICAgICAgICAgbGV0IGVuZCA9IHMuaW5kZXhPZihcIn1cIiwgc3RhcnQpO1xyXG5cclxuICAgICAgICAgICAgICAgIGlmIChlbmQgPj0gMCkge1xyXG4gICAgICAgICAgICAgICAgICAgIGV4cHJlc3Npb25Gb3VuZCA9IHRydWU7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGlmIChzdGFydCA+IGkpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0Ll9wYXJ0cy5wdXNoKHMuc3Vic3RyaW5nKGksIHN0YXJ0KSk7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgICAgICBsZXQgYmluZG5nRXhwcmVzc2lvbiA9IHMuc3Vic3RyaW5nKHN0YXJ0LCBlbmQgKyAxKTtcclxuICAgICAgICAgICAgICAgICAgICBsZXQgcGFydDogc3RyaW5nIHwgQmluZGluZztcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgdHJ5IHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgcGFydCA9IEV4cHJlc3Npb25QYXJzZXIucGFyc2VCaW5kaW5nKGJpbmRuZ0V4cHJlc3Npb24pO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgICAgICBjYXRjaCAoZSkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBwYXJ0ID0gYmluZG5nRXhwcmVzc2lvbjtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIHJlc3VsdC5fcGFydHMucHVzaChwYXJ0KTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgaSA9IGVuZCArIDE7XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgIGlmICghZXhwcmVzc2lvbkZvdW5kKSB7XHJcbiAgICAgICAgICAgICAgICByZXN1bHQuX3BhcnRzLnB1c2gocy5zdWJzdHIoaSkpO1xyXG5cclxuICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgfSB3aGlsZSAoaSA8IHMubGVuZ3RoKTtcclxuXHJcbiAgICAgICAgaWYgKHJlc3VsdC5fcGFydHMubGVuZ3RoID09IDEgJiYgdHlwZW9mIHJlc3VsdC5fcGFydHNbMF0gPT09IFwic3RyaW5nXCIpIHtcclxuICAgICAgICAgICAgcmV0dXJuIDxzdHJpbmc+cmVzdWx0Ll9wYXJ0c1swXTtcclxuICAgICAgICB9XHJcbiAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgIHJldHVybiByZXN1bHQ7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgX3Nob3VsZERyb3BPd25lcjogYm9vbGVhbiA9IGZhbHNlO1xyXG5cclxuICAgIHByaXZhdGUgZXZhbEV4cHJlc3Npb24oYmluZGluZ0V4cHJlc3Npb246IEJpbmRpbmcsIGNvbnRleHQ6IEV2YWx1YXRpb25Db250ZXh0KTogYW55IHtcclxuICAgICAgICBsZXQgcmVzdWx0ID0gYmluZGluZ0V4cHJlc3Npb24uZXZhbHVhdGUoY29udGV4dCk7XHJcblxyXG4gICAgICAgIGlmIChyZXN1bHQgPT0gdW5kZWZpbmVkKSB7XHJcbiAgICAgICAgICAgIHRoaXMuX3Nob3VsZERyb3BPd25lciA9IHRoaXMuX3Nob3VsZERyb3BPd25lciB8fCAhYmluZGluZ0V4cHJlc3Npb24uYWxsb3dOdWxsO1xyXG4gICAgICAgIH1cclxuXHJcbiAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgIH1cclxuXHJcbiAgICBwcml2YXRlIGludGVybmFsRXZhbHVhdGUoY29udGV4dDogRXZhbHVhdGlvbkNvbnRleHQpOiBhbnkge1xyXG4gICAgICAgIGlmICh0aGlzLl9wYXJ0cy5sZW5ndGggPT0gMCkge1xyXG4gICAgICAgICAgICByZXR1cm4gdW5kZWZpbmVkO1xyXG4gICAgICAgIH1cclxuICAgICAgICBlbHNlIGlmICh0aGlzLl9wYXJ0cy5sZW5ndGggPT0gMSkge1xyXG4gICAgICAgICAgICBpZiAodHlwZW9mIHRoaXMuX3BhcnRzWzBdID09PSBcInN0cmluZ1wiKSB7XHJcbiAgICAgICAgICAgICAgICByZXR1cm4gdGhpcy5fcGFydHNbMF07XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgICAgICByZXR1cm4gdGhpcy5ldmFsRXhwcmVzc2lvbig8QmluZGluZz50aGlzLl9wYXJ0c1swXSwgY29udGV4dCk7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICB9XHJcbiAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgIGxldCBzID0gXCJcIjtcclxuXHJcbiAgICAgICAgICAgIGZvciAobGV0IHBhcnQgb2YgdGhpcy5fcGFydHMpIHtcclxuICAgICAgICAgICAgICAgIGlmICh0eXBlb2YgcGFydCA9PT0gXCJzdHJpbmdcIikge1xyXG4gICAgICAgICAgICAgICAgICAgIHMgKz0gcGFydDtcclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgIHMgKz0gdGhpcy5ldmFsRXhwcmVzc2lvbig8QmluZGluZz5wYXJ0LCBjb250ZXh0KTtcclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgcmV0dXJuIHM7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG5cclxuICAgIGV2YWx1YXRlKGNvbnRleHQ6IEV2YWx1YXRpb25Db250ZXh0KTogYW55IHtcclxuICAgICAgICB0aGlzLl9zaG91bGREcm9wT3duZXIgPSBmYWxzZTtcclxuXHJcbiAgICAgICAgcmV0dXJuIHRoaXMuaW50ZXJuYWxFdmFsdWF0ZShjb250ZXh0KTtcclxuICAgIH1cclxuXHJcbiAgICBnZXQgc2hvdWxkRHJvcE93bmVyKCk6IGJvb2xlYW4ge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl9zaG91bGREcm9wT3duZXI7XHJcbiAgICB9XHJcbn1cclxuXHJcbmV4cG9ydCBjbGFzcyBUZW1wbGF0ZSB7XHJcbiAgICBwcml2YXRlIHN0YXRpYyBwcmVwYXJlKG5vZGU6IGFueSk6IGFueSB7XHJcbiAgICAgICAgaWYgKHR5cGVvZiBub2RlID09PSBcInN0cmluZ1wiKSB7XHJcbiAgICAgICAgICAgIHJldHVybiBUZW1wbGF0aXplZFN0cmluZy5wYXJzZShub2RlKTtcclxuICAgICAgICB9XHJcbiAgICAgICAgZWxzZSBpZiAodHlwZW9mIG5vZGUgPT09IFwib2JqZWN0XCIgJiYgbm9kZSAhPSBudWxsKSB7XHJcbiAgICAgICAgICAgIGlmIChBcnJheS5pc0FycmF5KG5vZGUpKSB7XHJcbiAgICAgICAgICAgICAgICBsZXQgcmVzdWx0OiBhbnlbXSA9IFtdO1xyXG5cclxuICAgICAgICAgICAgICAgIGZvciAobGV0IGl0ZW0gb2Ygbm9kZSkge1xyXG4gICAgICAgICAgICAgICAgICAgIHJlc3VsdC5wdXNoKFRlbXBsYXRlLnByZXBhcmUoaXRlbSkpO1xyXG4gICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgIHJldHVybiByZXN1bHQ7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgICAgICBsZXQga2V5cyA9IE9iamVjdC5rZXlzKG5vZGUpO1xyXG4gICAgICAgICAgICAgICAgbGV0IHJlc3VsdCA9IHt9O1xyXG5cclxuICAgICAgICAgICAgICAgIGZvciAobGV0IGtleSBvZiBrZXlzKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgcmVzdWx0W2tleV0gPSBUZW1wbGF0ZS5wcmVwYXJlKG5vZGVba2V5XSk7XHJcbiAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgIH1cclxuICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgcmV0dXJuIG5vZGU7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgX2NvbnRleHQ6IEV2YWx1YXRpb25Db250ZXh0O1xyXG5cclxuICAgIHByaXZhdGUgZXhwYW5kU2luZ2xlT2JqZWN0KG5vZGU6IG9iamVjdCk6IGFueSB7XHJcbiAgICAgICAgbGV0IHJlc3VsdCA9IHt9O1xyXG4gICAgICAgIGxldCBrZXlzID0gT2JqZWN0LmtleXMobm9kZSk7XHJcblxyXG4gICAgICAgIGZvciAobGV0IGtleSBvZiBrZXlzKSB7XHJcbiAgICAgICAgICAgIGlmICghdGhpcy5fY29udGV4dC5pc1Jlc2VydmVkRmllbGQoa2V5KSkge1xyXG4gICAgICAgICAgICAgICAgbGV0IHZhbHVlID0gdGhpcy5pbnRlcm5hbEV4cGFuZChub2RlW2tleV0pO1xyXG5cclxuICAgICAgICAgICAgICAgIGlmICh2YWx1ZSAhPSB1bmRlZmluZWQpIHtcclxuICAgICAgICAgICAgICAgICAgICByZXN1bHRba2V5XSA9IHZhbHVlO1xyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICByZXR1cm4gcmVzdWx0O1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgaW50ZXJuYWxFeHBhbmQobm9kZTogYW55KTogYW55IHtcclxuICAgICAgICBsZXQgcmVzdWx0OiBhbnk7XHJcblxyXG4gICAgICAgIHRoaXMuX2NvbnRleHQuc2F2ZVN0YXRlKCk7XHJcblxyXG4gICAgICAgIGlmIChBcnJheS5pc0FycmF5KG5vZGUpKSB7XHJcbiAgICAgICAgICAgIGxldCBpdGVtQXJyYXk6IGFueVtdID0gW107XHJcblxyXG4gICAgICAgICAgICBmb3IgKGxldCBpdGVtIG9mIG5vZGUpIHtcclxuICAgICAgICAgICAgICAgIGxldCBleHBhbmRlZEl0ZW0gPSB0aGlzLmludGVybmFsRXhwYW5kKGl0ZW0pO1xyXG5cclxuICAgICAgICAgICAgICAgIGlmIChleHBhbmRlZEl0ZW0gIT0gbnVsbCkge1xyXG4gICAgICAgICAgICAgICAgICAgIGlmIChBcnJheS5pc0FycmF5KGV4cGFuZGVkSXRlbSkpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgaXRlbUFycmF5ID0gaXRlbUFycmF5LmNvbmNhdChleHBhbmRlZEl0ZW0pO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgaXRlbUFycmF5LnB1c2goZXhwYW5kZWRJdGVtKTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgIHJlc3VsdCA9IGl0ZW1BcnJheTtcclxuICAgICAgICB9XHJcbiAgICAgICAgZWxzZSBpZiAobm9kZSBpbnN0YW5jZW9mIFRlbXBsYXRpemVkU3RyaW5nKSB7XHJcbiAgICAgICAgICAgIHJlc3VsdCA9IG5vZGUuZXZhbHVhdGUodGhpcy5fY29udGV4dCk7XHJcblxyXG4gICAgICAgICAgICBpZiAobm9kZS5zaG91bGREcm9wT3duZXIpIHtcclxuICAgICAgICAgICAgICAgIHJlc3VsdCA9IG51bGw7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICB9XHJcbiAgICAgICAgZWxzZSBpZiAodHlwZW9mIG5vZGUgPT09IFwib2JqZWN0XCIgJiYgbm9kZSAhPSBudWxsKSB7XHJcbiAgICAgICAgICAgIGxldCBkcm9wT2JqZWN0ID0gZmFsc2U7XHJcbiAgICAgICAgICAgIGxldCB3aGVuID0gbm9kZVtcIiR3aGVuXCJdO1xyXG5cclxuICAgICAgICAgICAgaWYgKHdoZW4gaW5zdGFuY2VvZiBUZW1wbGF0aXplZFN0cmluZykge1xyXG4gICAgICAgICAgICAgICAgbGV0IHdoZW5WYWx1ZSA9IHdoZW4uZXZhbHVhdGUodGhpcy5fY29udGV4dCk7XHJcblxyXG4gICAgICAgICAgICAgICAgaWYgKHR5cGVvZiB3aGVuVmFsdWUgPT09IFwiYm9vbGVhblwiKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgZHJvcE9iamVjdCA9ICF3aGVuVmFsdWU7XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgIGlmICghZHJvcE9iamVjdCkge1xyXG4gICAgICAgICAgICAgICAgbGV0IGRhdGFDb250ZXh0ID0gbm9kZVtcIiRkYXRhXCJdO1xyXG5cclxuICAgICAgICAgICAgICAgIGlmIChkYXRhQ29udGV4dCAhPSB1bmRlZmluZWQpIHtcclxuICAgICAgICAgICAgICAgICAgICBpZiAoZGF0YUNvbnRleHQgaW5zdGFuY2VvZiBUZW1wbGF0aXplZFN0cmluZykge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBkYXRhQ29udGV4dCA9IGRhdGFDb250ZXh0LmV2YWx1YXRlKHRoaXMuX2NvbnRleHQpO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKEFycmF5LmlzQXJyYXkoZGF0YUNvbnRleHQpKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IFtdO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICAgICAgZm9yIChsZXQgaSA9IDA7IGkgPCBkYXRhQ29udGV4dC5sZW5ndGg7IGkrKykge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgdGhpcy5fY29udGV4dC4kZGF0YSA9IGRhdGFDb250ZXh0W2ldO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgdGhpcy5fY29udGV4dC4kaW5kZXggPSBpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGxldCBleHBhbmRlZE9iamVjdCA9IHRoaXMuZXhwYW5kU2luZ2xlT2JqZWN0KG5vZGUpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGlmIChleHBhbmRlZE9iamVjdCAhPSBudWxsKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0LnB1c2goZXhwYW5kZWRPYmplY3QpO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICB0aGlzLl9jb250ZXh0LiRkYXRhID0gZGF0YUNvbnRleHQ7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQgPSB0aGlzLmV4cGFuZFNpbmdsZU9iamVjdChub2RlKTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICByZXN1bHQgPSB0aGlzLmV4cGFuZFNpbmdsZU9iamVjdChub2RlKTtcclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgIHJlc3VsdCA9IG51bGw7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICB9XHJcbiAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgIHJlc3VsdCA9IG5vZGU7XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICB0aGlzLl9jb250ZXh0LnJlc3RvcmVMYXN0U3RhdGUoKTtcclxuXHJcbiAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgIH1cclxuXHJcbiAgICBwcmVwYXJlZFBheWxvYWQ6IGFueTtcclxuXHJcbiAgICBjb25zdHJ1Y3RvcihwYXlsb2FkOiBhbnkpIHtcclxuICAgICAgICB0aGlzLnByZXBhcmVkUGF5bG9hZCA9IFRlbXBsYXRlLnByZXBhcmUocGF5bG9hZCk7XHJcbiAgICB9XHJcblxyXG4gICAgZXhwYW5kKGNvbnRleHQ6IEV2YWx1YXRpb25Db250ZXh0KTogYW55IHtcclxuICAgICAgICB0aGlzLl9jb250ZXh0ID0gY29udGV4dDtcclxuXHJcbiAgICAgICAgcmV0dXJuIHRoaXMuaW50ZXJuYWxFeHBhbmQodGhpcy5wcmVwYXJlZFBheWxvYWQpO1xyXG4gICAgfVxyXG59XHJcblxyXG5leHBvcnQgZnVuY3Rpb24gdHJhbnNmb3JtKGNhcmRKc29uOiBzdHJpbmcsIGRhdGFKc29uOiBzdHJpbmcpIHtcclxuXHR2YXIgdGVtcGxhdGUgPSBuZXcgVGVtcGxhdGUoSlNPTi5wYXJzZShjYXJkSnNvbikpO1xyXG5cclxuICAgIHZhciBjb250ZXh0ID0gbmV3IEV2YWx1YXRpb25Db250ZXh0KCk7XHJcblx0Y29udGV4dC4kcm9vdCA9IEpTT04ucGFyc2UoZGF0YUpzb24pO1xyXG5cdGFsZXJ0KGNvbnRleHQuJHJvb3QpO1xyXG5cclxuICAgIHZhciB0cmFuc2Zvcm1lZENhcmQgPSB0ZW1wbGF0ZS5leHBhbmQoY29udGV4dCk7XHJcbiAgICByZXR1cm4gSlNPTi5zdHJpbmdpZnkodHJhbnNmb3JtZWRDYXJkKTtcclxufSJdLCJzb3VyY2VSb290IjoiIn0=
