(function webpackUniversalModuleDefinition(root, factory) {
	if(typeof exports === 'object' && typeof module === 'object')
		module.exports = factory();
	else if(typeof define === 'function' && define.amd)
		define([], factory);
	else if(typeof exports === 'object')
		exports["TemplateEngine"] = factory();
	else
		root["TemplateEngine"] = factory();
})(window, function() {
return /******/ (function(modules) { // webpackBootstrap
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
    alert(context.$root);
    var transformedCard = template.expand(context);
    return JSON.stringify(transformedCard);
}
exports.transform = transform;


/***/ })

/******/ });
});
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly9UZW1wbGF0ZUVuZ2luZS93ZWJwYWNrL3VuaXZlcnNhbE1vZHVsZURlZmluaXRpb24iLCJ3ZWJwYWNrOi8vVGVtcGxhdGVFbmdpbmUvd2VicGFjay9ib290c3RyYXAiLCJ3ZWJwYWNrOi8vVGVtcGxhdGVFbmdpbmUvLi9zcmMvZXhwcmVzc2lvbi1wYXJzZXIudHMiLCJ3ZWJwYWNrOi8vVGVtcGxhdGVFbmdpbmUvLi9zcmMvdGVtcGxhdGUtZW5naW5lLnRzIl0sIm5hbWVzIjpbXSwibWFwcGluZ3MiOiJBQUFBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLENBQUM7QUFDRCxPO0FDVkE7QUFDQTs7QUFFQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7OztBQUdBO0FBQ0E7O0FBRUE7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQSxrREFBMEMsZ0NBQWdDO0FBQzFFO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0EsZ0VBQXdELGtCQUFrQjtBQUMxRTtBQUNBLHlEQUFpRCxjQUFjO0FBQy9EOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxpREFBeUMsaUNBQWlDO0FBQzFFLHdIQUFnSCxtQkFBbUIsRUFBRTtBQUNySTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBLG1DQUEyQiwwQkFBMEIsRUFBRTtBQUN2RCx5Q0FBaUMsZUFBZTtBQUNoRDtBQUNBO0FBQ0E7O0FBRUE7QUFDQSw4REFBc0QsK0RBQStEOztBQUVySDtBQUNBOzs7QUFHQTtBQUNBOzs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7O0FDekRBLElBQU0sZ0JBQWdCLEdBQXFCO0lBQ3ZDLEdBQUc7SUFDSCxHQUFHO0lBQ0gsR0FBRztJQUNILEdBQUc7SUFDSCxJQUFJ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O29CQUNELE1BQU0sR0FBRyxJQUFJLENBQUMsa0JBQWtCLENBQUMsSUFBSSxDQUFDLENBQUM7aUJBQzFDO2FBQ0o7aUJBQ0k7Z0JBQ0QsTUFBTSxHQUFHLElBQUksQ0FBQzthQUNqQjtTQUNKO2FBQ0k7WUFDRCxNQUFNLEdBQUcsSUFBSSxDQUFDO1NBQ2pCO1FBRUQsSUFBSSxDQUFDLFFBQVEsQ0FBQyxnQkFBZ0IsRUFBRSxDQUFDO1FBRWpDLE9BQU8sTUFBTSxDQUFDO0lBQ2xCLENBQUM7SUFRRCx5QkFBTSxHQUFOLFVBQU8sT0FBMEI7UUFDN0IsSUFBSSxDQUFDLFFBQVEsR0FBRyxPQUFPLENBQUM7UUFFeEIsT0FBTyxJQUFJLENBQUMsY0FBYyxDQUFDLElBQUksQ0FBQyxlQUFlLENBQUMsQ0FBQztJQUNyRCxDQUFDO0lBQ0wsZUFBQztBQUFELENBQUM7QUFwSlksNEJBQVE7QUFzSnJCLFNBQWdCLFNBQVMsQ0FBQyxRQUFnQixFQUFFLFFBQWdCO0lBQzNELElBQUksUUFBUSxHQUFHLElBQUksUUFBUSxDQUFDLElBQUksQ0FBQyxLQUFLLENBQUMsUUFBUSxDQUFDLENBQUMsQ0FBQztJQUUvQyxJQUFJLE9BQU8sR0FBRyxJQUFJLHFDQUFpQixFQUFFLENBQUM7SUFDekMsT0FBTyxDQUFDLEtBQUssR0FBRyxJQUFJLENBQUMsS0FBSyxDQUFDLFFBQVEsQ0FBQyxDQUFDO0lBQ3JDLEtBQUssQ0FBQyxPQUFPLENBQUMsS0FBSyxDQUFDLENBQUM7SUFFbEIsSUFBSSxlQUFlLEdBQUcsUUFBUSxDQUFDLE1BQU0sQ0FBQyxPQUFPLENBQUMsQ0FBQztJQUMvQyxPQUFPLElBQUksQ0FBQyxTQUFTLENBQUMsZUFBZSxDQUFDLENBQUM7QUFDM0MsQ0FBQztBQVRELDhCQVNDIiwiZmlsZSI6InRlbXBsYXRlLWVuZ2luZS5qcyIsInNvdXJjZXNDb250ZW50IjpbIihmdW5jdGlvbiB3ZWJwYWNrVW5pdmVyc2FsTW9kdWxlRGVmaW5pdGlvbihyb290LCBmYWN0b3J5KSB7XG5cdGlmKHR5cGVvZiBleHBvcnRzID09PSAnb2JqZWN0JyAmJiB0eXBlb2YgbW9kdWxlID09PSAnb2JqZWN0Jylcblx0XHRtb2R1bGUuZXhwb3J0cyA9IGZhY3RvcnkoKTtcblx0ZWxzZSBpZih0eXBlb2YgZGVmaW5lID09PSAnZnVuY3Rpb24nICYmIGRlZmluZS5hbWQpXG5cdFx0ZGVmaW5lKFtdLCBmYWN0b3J5KTtcblx0ZWxzZSBpZih0eXBlb2YgZXhwb3J0cyA9PT0gJ29iamVjdCcpXG5cdFx0ZXhwb3J0c1tcIlRlbXBsYXRlRW5naW5lXCJdID0gZmFjdG9yeSgpO1xuXHRlbHNlXG5cdFx0cm9vdFtcIlRlbXBsYXRlRW5naW5lXCJdID0gZmFjdG9yeSgpO1xufSkod2luZG93LCBmdW5jdGlvbigpIHtcbnJldHVybiAiLCIgXHQvLyBUaGUgbW9kdWxlIGNhY2hlXG4gXHR2YXIgaW5zdGFsbGVkTW9kdWxlcyA9IHt9O1xuXG4gXHQvLyBUaGUgcmVxdWlyZSBmdW5jdGlvblxuIFx0ZnVuY3Rpb24gX193ZWJwYWNrX3JlcXVpcmVfXyhtb2R1bGVJZCkge1xuXG4gXHRcdC8vIENoZWNrIGlmIG1vZHVsZSBpcyBpbiBjYWNoZVxuIFx0XHRpZihpbnN0YWxsZWRNb2R1bGVzW21vZHVsZUlkXSkge1xuIFx0XHRcdHJldHVybiBpbnN0YWxsZWRNb2R1bGVzW21vZHVsZUlkXS5leHBvcnRzO1xuIFx0XHR9XG4gXHRcdC8vIENyZWF0ZSBhIG5ldyBtb2R1bGUgKGFuZCBwdXQgaXQgaW50byB0aGUgY2FjaGUpXG4gXHRcdHZhciBtb2R1bGUgPSBpbnN0YWxsZWRNb2R1bGVzW21vZHVsZUlkXSA9IHtcbiBcdFx0XHRpOiBtb2R1bGVJZCxcbiBcdFx0XHRsOiBmYWxzZSxcbiBcdFx0XHRleHBvcnRzOiB7fVxuIFx0XHR9O1xuXG4gXHRcdC8vIEV4ZWN1dGUgdGhlIG1vZHVsZSBmdW5jdGlvblxuIFx0XHRtb2R1bGVzW21vZHVsZUlkXS5jYWxsKG1vZHVsZS5leHBvcnRzLCBtb2R1bGUsIG1vZHVsZS5leHBvcnRzLCBfX3dlYnBhY2tfcmVxdWlyZV9fKTtcblxuIFx0XHQvLyBGbGFnIHRoZSBtb2R1bGUgYXMgbG9hZGVkXG4gXHRcdG1vZHVsZS5sID0gdHJ1ZTtcblxuIFx0XHQvLyBSZXR1cm4gdGhlIGV4cG9ydHMgb2YgdGhlIG1vZHVsZVxuIFx0XHRyZXR1cm4gbW9kdWxlLmV4cG9ydHM7XG4gXHR9XG5cblxuIFx0Ly8gZXhwb3NlIHRoZSBtb2R1bGVzIG9iamVjdCAoX193ZWJwYWNrX21vZHVsZXNfXylcbiBcdF9fd2VicGFja19yZXF1aXJlX18ubSA9IG1vZHVsZXM7XG5cbiBcdC8vIGV4cG9zZSB0aGUgbW9kdWxlIGNhY2hlXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLmMgPSBpbnN0YWxsZWRNb2R1bGVzO1xuXG4gXHQvLyBkZWZpbmUgZ2V0dGVyIGZ1bmN0aW9uIGZvciBoYXJtb255IGV4cG9ydHNcbiBcdF9fd2VicGFja19yZXF1aXJlX18uZCA9IGZ1bmN0aW9uKGV4cG9ydHMsIG5hbWUsIGdldHRlcikge1xuIFx0XHRpZighX193ZWJwYWNrX3JlcXVpcmVfXy5vKGV4cG9ydHMsIG5hbWUpKSB7XG4gXHRcdFx0T2JqZWN0LmRlZmluZVByb3BlcnR5KGV4cG9ydHMsIG5hbWUsIHsgZW51bWVyYWJsZTogdHJ1ZSwgZ2V0OiBnZXR0ZXIgfSk7XG4gXHRcdH1cbiBcdH07XG5cbiBcdC8vIGRlZmluZSBfX2VzTW9kdWxlIG9uIGV4cG9ydHNcbiBcdF9fd2VicGFja19yZXF1aXJlX18uciA9IGZ1bmN0aW9uKGV4cG9ydHMpIHtcbiBcdFx0aWYodHlwZW9mIFN5bWJvbCAhPT0gJ3VuZGVmaW5lZCcgJiYgU3ltYm9sLnRvU3RyaW5nVGFnKSB7XG4gXHRcdFx0T2JqZWN0LmRlZmluZVByb3BlcnR5KGV4cG9ydHMsIFN5bWJvbC50b1N0cmluZ1RhZywgeyB2YWx1ZTogJ01vZHVsZScgfSk7XG4gXHRcdH1cbiBcdFx0T2JqZWN0LmRlZmluZVByb3BlcnR5KGV4cG9ydHMsICdfX2VzTW9kdWxlJywgeyB2YWx1ZTogdHJ1ZSB9KTtcbiBcdH07XG5cbiBcdC8vIGNyZWF0ZSBhIGZha2UgbmFtZXNwYWNlIG9iamVjdFxuIFx0Ly8gbW9kZSAmIDE6IHZhbHVlIGlzIGEgbW9kdWxlIGlkLCByZXF1aXJlIGl0XG4gXHQvLyBtb2RlICYgMjogbWVyZ2UgYWxsIHByb3BlcnRpZXMgb2YgdmFsdWUgaW50byB0aGUgbnNcbiBcdC8vIG1vZGUgJiA0OiByZXR1cm4gdmFsdWUgd2hlbiBhbHJlYWR5IG5zIG9iamVjdFxuIFx0Ly8gbW9kZSAmIDh8MTogYmVoYXZlIGxpa2UgcmVxdWlyZVxuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy50ID0gZnVuY3Rpb24odmFsdWUsIG1vZGUpIHtcbiBcdFx0aWYobW9kZSAmIDEpIHZhbHVlID0gX193ZWJwYWNrX3JlcXVpcmVfXyh2YWx1ZSk7XG4gXHRcdGlmKG1vZGUgJiA4KSByZXR1cm4gdmFsdWU7XG4gXHRcdGlmKChtb2RlICYgNCkgJiYgdHlwZW9mIHZhbHVlID09PSAnb2JqZWN0JyAmJiB2YWx1ZSAmJiB2YWx1ZS5fX2VzTW9kdWxlKSByZXR1cm4gdmFsdWU7XG4gXHRcdHZhciBucyA9IE9iamVjdC5jcmVhdGUobnVsbCk7XG4gXHRcdF9fd2VicGFja19yZXF1aXJlX18ucihucyk7XG4gXHRcdE9iamVjdC5kZWZpbmVQcm9wZXJ0eShucywgJ2RlZmF1bHQnLCB7IGVudW1lcmFibGU6IHRydWUsIHZhbHVlOiB2YWx1ZSB9KTtcbiBcdFx0aWYobW9kZSAmIDIgJiYgdHlwZW9mIHZhbHVlICE9ICdzdHJpbmcnKSBmb3IodmFyIGtleSBpbiB2YWx1ZSkgX193ZWJwYWNrX3JlcXVpcmVfXy5kKG5zLCBrZXksIGZ1bmN0aW9uKGtleSkgeyByZXR1cm4gdmFsdWVba2V5XTsgfS5iaW5kKG51bGwsIGtleSkpO1xuIFx0XHRyZXR1cm4gbnM7XG4gXHR9O1xuXG4gXHQvLyBnZXREZWZhdWx0RXhwb3J0IGZ1bmN0aW9uIGZvciBjb21wYXRpYmlsaXR5IHdpdGggbm9uLWhhcm1vbnkgbW9kdWxlc1xuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5uID0gZnVuY3Rpb24obW9kdWxlKSB7XG4gXHRcdHZhciBnZXR0ZXIgPSBtb2R1bGUgJiYgbW9kdWxlLl9fZXNNb2R1bGUgP1xuIFx0XHRcdGZ1bmN0aW9uIGdldERlZmF1bHQoKSB7IHJldHVybiBtb2R1bGVbJ2RlZmF1bHQnXTsgfSA6XG4gXHRcdFx0ZnVuY3Rpb24gZ2V0TW9kdWxlRXhwb3J0cygpIHsgcmV0dXJuIG1vZHVsZTsgfTtcbiBcdFx0X193ZWJwYWNrX3JlcXVpcmVfXy5kKGdldHRlciwgJ2EnLCBnZXR0ZXIpO1xuIFx0XHRyZXR1cm4gZ2V0dGVyO1xuIFx0fTtcblxuIFx0Ly8gT2JqZWN0LnByb3RvdHlwZS5oYXNPd25Qcm9wZXJ0eS5jYWxsXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLm8gPSBmdW5jdGlvbihvYmplY3QsIHByb3BlcnR5KSB7IHJldHVybiBPYmplY3QucHJvdG90eXBlLmhhc093blByb3BlcnR5LmNhbGwob2JqZWN0LCBwcm9wZXJ0eSk7IH07XG5cbiBcdC8vIF9fd2VicGFja19wdWJsaWNfcGF0aF9fXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLnAgPSBcIlwiO1xuXG5cbiBcdC8vIExvYWQgZW50cnkgbW9kdWxlIGFuZCByZXR1cm4gZXhwb3J0c1xuIFx0cmV0dXJuIF9fd2VicGFja19yZXF1aXJlX18oX193ZWJwYWNrX3JlcXVpcmVfXy5zID0gXCIuL3NyYy90ZW1wbGF0ZS1lbmdpbmUudHNcIik7XG4iLCJ0eXBlIFRva2VuVHlwZSA9XHJcbiAgICBcIntcIiB8XHJcbiAgICBcIj8jXCIgfFxyXG4gICAgXCJ9XCIgfFxyXG4gICAgXCJbXCIgfFxyXG4gICAgXCJdXCIgfFxyXG4gICAgXCIoXCIgfFxyXG4gICAgXCIpXCIgfFxyXG4gICAgXCJpZGVudGlmaWVyXCIgfFxyXG4gICAgXCIuXCIgfFxyXG4gICAgXCIsXCIgfFxyXG4gICAgXCIrXCIgfFxyXG4gICAgXCItXCIgfFxyXG4gICAgXCIqXCIgfFxyXG4gICAgXCIvXCIgfFxyXG4gICAgXCI9PVwiIHxcclxuICAgIFwiIT1cIiB8XHJcbiAgICBcIjxcIiB8XHJcbiAgICBcIjw9XCIgfFxyXG4gICAgXCI+XCIgfFxyXG4gICAgXCI+PVwiIHxcclxuICAgIFwic3RyaW5nXCIgfFxyXG4gICAgXCJudW1iZXJcIiB8XHJcbiAgICBcImJvb2xlYW5cIjtcclxuXHJcbmNvbnN0IG9yZGVyZWRPcGVyYXRvcnM6IEFycmF5PFRva2VuVHlwZT4gPSBbXHJcbiAgICBcIi9cIixcclxuICAgIFwiKlwiLFxyXG4gICAgXCItXCIsXHJcbiAgICBcIitcIixcclxuICAgIFwiPT1cIixcclxuICAgIFwiIT1cIixcclxuICAgIFwiPFwiLFxyXG4gICAgXCI8PVwiLFxyXG4gICAgXCI+XCIsXHJcbiAgICBcIj49XCJcclxuXTtcclxuXHJcbmNvbnN0IGxpdGVyYWxzOiBBcnJheTxUb2tlblR5cGU+ID0gW1xyXG4gICAgXCJpZGVudGlmaWVyXCIsXHJcbiAgICBcInN0cmluZ1wiLFxyXG4gICAgXCJudW1iZXJcIixcclxuICAgIFwiYm9vbGVhblwiXHJcbl07XHJcblxyXG5pbnRlcmZhY2UgVG9rZW5pemVyUnVsZSB7XHJcbiAgICB0b2tlblR5cGU6IFRva2VuVHlwZTtcclxuICAgIHJlZ0V4OiBSZWdFeHA7XHJcbn1cclxuXHJcbmludGVyZmFjZSBUb2tlbiB7XHJcbiAgICB0eXBlOiBUb2tlblR5cGU7XHJcbiAgICB2YWx1ZTogc3RyaW5nO1xyXG4gICAgb3JpZ2luYWxQb3NpdGlvbjogbnVtYmVyO1xyXG59XHJcblxyXG5jbGFzcyBUb2tlbml6ZXIge1xyXG4gICAgc3RhdGljIHJ1bGVzOiBBcnJheTxUb2tlbml6ZXJSdWxlPiA9IFtdO1xyXG5cclxuICAgIHN0YXRpYyBpbml0KCkge1xyXG4gICAgICAgIFRva2VuaXplci5ydWxlcy5wdXNoKFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogdW5kZWZpbmVkLCByZWdFeDogL15cXHMvIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcIntcIiwgcmVnRXg6IC9eey8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiPyNcIiwgcmVnRXg6IC9eXFw/Iy8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwifVwiLCByZWdFeDogL159LyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCJbXCIsIHJlZ0V4OiAvXlxcWy8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiXVwiLCByZWdFeDogL15cXF0vIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcIihcIiwgcmVnRXg6IC9eXFwoLyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCIpXCIsIHJlZ0V4OiAvXlxcKS8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiYm9vbGVhblwiLCByZWdFeDogL150cnVlfF5mYWxzZS8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiaWRlbnRpZmllclwiLCByZWdFeDogL15bJGEtel9dKy9pIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcIi5cIiwgcmVnRXg6IC9eXFwuLyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCIsXCIsIHJlZ0V4OiAvXiwvIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcIitcIiwgcmVnRXg6IC9eXFwrLyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCItXCIsIHJlZ0V4OiAvXi0vIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcIipcIiwgcmVnRXg6IC9eXFwqLyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCIvXCIsIHJlZ0V4OiAvXlxcLy8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiPT1cIiwgcmVnRXg6IC9ePT0vIH0sXHJcbiAgICAgICAgICAgIHsgdG9rZW5UeXBlOiBcIiE9XCIsIHJlZ0V4OiAvXiE9LyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCI8PVwiLCByZWdFeDogL148PS8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiPFwiLCByZWdFeDogL148LyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCI+PVwiLCByZWdFeDogL14+PS8gfSxcclxuICAgICAgICAgICAgeyB0b2tlblR5cGU6IFwiPlwiLCByZWdFeDogL14+LyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCJzdHJpbmdcIiwgcmVnRXg6IC9eXCIoW15cIl0qKVwiLyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCJzdHJpbmdcIiwgcmVnRXg6IC9eJyhbXiddKiknLyB9LFxyXG4gICAgICAgICAgICB7IHRva2VuVHlwZTogXCJudW1iZXJcIiwgcmVnRXg6IC9eXFxkKlxcLj9cXGQrLyB9XHJcbiAgICAgICAgKVxyXG4gICAgfVxyXG5cclxuICAgIHN0YXRpYyBwYXJzZShleHByZXNzaW9uOiBzdHJpbmcpOiBUb2tlbltdIHtcclxuICAgICAgICBsZXQgcmVzdWx0OiBUb2tlbltdID0gW107XHJcbiAgICAgICAgbGV0IGkgPSAwO1xyXG5cclxuICAgICAgICB3aGlsZSAoaSA8IGV4cHJlc3Npb24ubGVuZ3RoKSB7XHJcbiAgICAgICAgICAgIGxldCBzdWJFeHByZXNzaW9uID0gZXhwcmVzc2lvbi5zdWJzdHJpbmcoaSk7XHJcbiAgICAgICAgICAgIGxldCBtYXRjaEZvdW5kID0gZmFsc2U7XHJcblxyXG4gICAgICAgICAgICBmb3IgKGxldCBydWxlIG9mIFRva2VuaXplci5ydWxlcykge1xyXG4gICAgICAgICAgICAgICAgbGV0IG1hdGNoZXMgPSBydWxlLnJlZ0V4LmV4ZWMoc3ViRXhwcmVzc2lvbik7XHJcblxyXG4gICAgICAgICAgICAgICAgaWYgKG1hdGNoZXMpIHtcclxuICAgICAgICAgICAgICAgICAgICBpZiAobWF0Y2hlcy5sZW5ndGggPiAyKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHRocm93IG5ldyBFcnJvcihcIkEgdG9rZW5pemVyIHJ1bGUgbWF0Y2hlZCBtb3JlIHRoYW4gb25lIGdyb3VwLlwiKTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGlmIChydWxlLnRva2VuVHlwZSAhPSB1bmRlZmluZWQpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0LnB1c2goXHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgdHlwZTogcnVsZS50b2tlblR5cGUsXHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgdmFsdWU6IG1hdGNoZXNbbWF0Y2hlcy5sZW5ndGggPT0gMSA/IDAgOiAxXSxcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICBvcmlnaW5hbFBvc2l0aW9uOiBpXHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIClcclxuICAgICAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGkgKz0gbWF0Y2hlc1swXS5sZW5ndGg7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIG1hdGNoRm91bmQgPSB0cnVlO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgaWYgKCFtYXRjaEZvdW5kKSB7XHJcbiAgICAgICAgICAgICAgICB0aHJvdyBuZXcgRXJyb3IoXCJVbmV4cGVjdGVkIGNoYXJhY3RlciBcIiArIHN1YkV4cHJlc3Npb25bMF0gKyBcIiBhdCBwb3NpdGlvbiBcIiArIGkpO1xyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICByZXR1cm4gcmVzdWx0O1xyXG4gICAgfVxyXG59XHJcblxyXG5Ub2tlbml6ZXIuaW5pdCgpO1xyXG5cclxudHlwZSBMaXRlcmFsVmFsdWUgPSBzdHJpbmcgfCBudW1iZXIgfCBib29sZWFuO1xyXG5cclxuZnVuY3Rpb24gZW5zdXJlVmFsdWVUeXBlKHZhbHVlOiBhbnkpOiBMaXRlcmFsVmFsdWUge1xyXG4gICAgaWYgKHR5cGVvZiB2YWx1ZSA9PT0gXCJudW1iZXJcIiB8fCB0eXBlb2YgdmFsdWUgPT09IFwic3RyaW5nXCIgfHwgdHlwZW9mIHZhbHVlID09PSBcImJvb2xlYW5cIikge1xyXG4gICAgICAgIHJldHVybiB2YWx1ZTtcclxuICAgIH1cclxuXHJcbiAgICB0aHJvdyBuZXcgRXJyb3IoXCJJbnZhbGlkIHZhbHVlIHR5cGU6IFwiICsgdHlwZW9mIHZhbHVlKTtcclxufVxyXG5cclxudHlwZSBGdW5jdGlvbkNhbGxiYWNrID0gKHBhcmFtczogYW55W10pID0+IGFueTtcclxudHlwZSBGdW5jdGlvbkRpY3Rpb25hcnkgPSB7IFtrZXk6IHN0cmluZ106IEZ1bmN0aW9uQ2FsbGJhY2sgfTtcclxuXHJcbmludGVyZmFjZSBFdmFsdWF0aW9uQ29udGV4dFN0YXRlIHtcclxuICAgICRkYXRhOiBhbnk7XHJcbiAgICAkaW5kZXg6IGFueTtcclxufVxyXG5cclxuZXhwb3J0IGNsYXNzIEV2YWx1YXRpb25Db250ZXh0IHtcclxuICAgIHByaXZhdGUgc3RhdGljIHJlYWRvbmx5IF9yZXNlcnZlZEZpZWxkcyA9IFtcIiRkYXRhXCIsIFwiJHJvb3RcIiwgXCIkaW5kZXhcIl07XHJcbiAgICBwcml2YXRlIHN0YXRpYyBfYnVpbHRJbkZ1bmN0aW9uczogRnVuY3Rpb25EaWN0aW9uYXJ5ID0ge31cclxuXHJcbiAgICBzdGF0aWMgaW5pdCgpIHtcclxuICAgICAgICBFdmFsdWF0aW9uQ29udGV4dC5fYnVpbHRJbkZ1bmN0aW9uc1tcInN1YnN0clwiXSA9IChwYXJhbXM6IGFueVtdKSA9PiB7XHJcbiAgICAgICAgICAgIHJldHVybiAoPHN0cmluZz5wYXJhbXNbMF0pLnN1YnN0cig8bnVtYmVyPnBhcmFtc1sxXSwgPG51bWJlcj5wYXJhbXNbMl0pO1xyXG4gICAgICAgIH07XHJcbiAgICAgICAgRXZhbHVhdGlvbkNvbnRleHQuX2J1aWx0SW5GdW5jdGlvbnNbXCJKU09OLnBhcnNlXCJdID0gKHBhcmFtczogYW55W10pID0+IHtcclxuICAgICAgICAgICAgcmV0dXJuIEpTT04ucGFyc2UocGFyYW1zWzBdKTtcclxuICAgICAgICB9O1xyXG4gICAgICAgIEV2YWx1YXRpb25Db250ZXh0Ll9idWlsdEluRnVuY3Rpb25zW1wiaWZcIl0gPSAocGFyYW1zOiBhbnlbXSkgPT4ge1xyXG4gICAgICAgICAgICByZXR1cm4gcGFyYW1zWzBdID8gcGFyYW1zWzFdIDogcGFyYW1zWzJdO1xyXG4gICAgICAgIH07XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBfZnVuY3Rpb25zID0ge307XHJcbiAgICBwcml2YXRlIF9zdGF0ZVN0YWNrOiBFdmFsdWF0aW9uQ29udGV4dFN0YXRlW10gPSBbXTtcclxuXHJcbiAgICAkcm9vdDogYW55O1xyXG4gICAgJGRhdGE6IGFueTtcclxuICAgICRpbmRleDogbnVtYmVyO1xyXG5cclxuICAgIHJlZ2lzdGVyRnVuY3Rpb24obmFtZTogc3RyaW5nLCBjYWxsYmFjazogRnVuY3Rpb25DYWxsYmFjaykge1xyXG4gICAgICAgIHRoaXMuX2Z1bmN0aW9uc1tuYW1lXSA9IGNhbGxiYWNrO1xyXG4gICAgfVxyXG5cclxuICAgIHVucmVnaXN0ZXJGdW5jdGlvbihuYW1lOiBzdHJpbmcpIHtcclxuICAgICAgICBkZWxldGUgdGhpcy5fZnVuY3Rpb25zW25hbWVdO1xyXG5cdH1cclxuXHJcbiAgICBnZXRGdW5jdGlvbihuYW1lOiBzdHJpbmcpOiBGdW5jdGlvbkNhbGxiYWNrIHtcclxuICAgICAgICBsZXQgcmVzdWx0ID0gdGhpcy5fZnVuY3Rpb25zW25hbWVdO1xyXG5cclxuICAgICAgICBpZiAocmVzdWx0ID09IHVuZGVmaW5lZCkge1xyXG4gICAgICAgICAgICByZXN1bHQgPSBFdmFsdWF0aW9uQ29udGV4dC5fYnVpbHRJbkZ1bmN0aW9uc1tuYW1lXTtcclxuICAgICAgICB9XHJcblxyXG4gICAgICAgIHJldHVybiByZXN1bHQ7XHJcbiAgICB9XHJcblxyXG4gICAgaXNSZXNlcnZlZEZpZWxkKG5hbWU6IHN0cmluZyk6IGJvb2xlYW4ge1xyXG4gICAgICAgIHJldHVybiBFdmFsdWF0aW9uQ29udGV4dC5fcmVzZXJ2ZWRGaWVsZHMuaW5kZXhPZihuYW1lKSA+PSAwO1xyXG4gICAgfVxyXG5cclxuICAgIHNhdmVTdGF0ZSgpIHtcclxuICAgICAgICB0aGlzLl9zdGF0ZVN0YWNrLnB1c2goeyAkZGF0YTogdGhpcy4kZGF0YSwgJGluZGV4OiB0aGlzLiRpbmRleCB9KTtcclxuICAgIH1cclxuXHJcbiAgICByZXN0b3JlTGFzdFN0YXRlKCkge1xyXG4gICAgICAgIGlmICh0aGlzLl9zdGF0ZVN0YWNrLmxlbmd0aCA9PSAwKSB7XHJcbiAgICAgICAgICAgIHRocm93IG5ldyBFcnJvcihcIlRoZXJlIGlzIG5vIGV2YWx1YXRpb24gY29udGV4dCBzdGF0ZSB0byByZXN0b3JlLlwiKTtcclxuICAgICAgICB9XHJcblxyXG4gICAgICAgIGxldCBzYXZlZENvbnRleHQgPSB0aGlzLl9zdGF0ZVN0YWNrLnBvcCgpO1xyXG5cclxuICAgICAgICB0aGlzLiRkYXRhID0gc2F2ZWRDb250ZXh0LiRkYXRhO1xyXG4gICAgICAgIHRoaXMuJGluZGV4ID0gc2F2ZWRDb250ZXh0LiRpbmRleDtcclxuICAgIH1cclxuXHJcbiAgICBnZXQgY3VycmVudERhdGFDb250ZXh0KCk6IGFueSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuJGRhdGEgIT0gdW5kZWZpbmVkID8gdGhpcy4kZGF0YSA6IHRoaXMuJHJvb3Q7XHJcbiAgICB9XHJcbn1cclxuXHJcbkV2YWx1YXRpb25Db250ZXh0LmluaXQoKTtcclxuXHJcbmFic3RyYWN0IGNsYXNzIEV2YWx1YXRpb25Ob2RlIHtcclxuICAgIGFic3RyYWN0IGV2YWx1YXRlKGNvbnRleHQ6IEV2YWx1YXRpb25Db250ZXh0KTogTGl0ZXJhbFZhbHVlO1xyXG59XHJcblxyXG5jbGFzcyBFeHByZXNzaW9uTm9kZSBleHRlbmRzIEV2YWx1YXRpb25Ob2RlIHtcclxuICAgIG5vZGVzOiBBcnJheTxFdmFsdWF0aW9uTm9kZT4gPSBbXTtcclxuICAgIGFsbG93TnVsbDogYm9vbGVhbiA9IHRydWU7XHJcblxyXG4gICAgZXZhbHVhdGUoY29udGV4dDogRXZhbHVhdGlvbkNvbnRleHQpOiBhbnkge1xyXG4gICAgICAgIGNvbnN0IG9wZXJhdG9yUHJpb3JpdHlHcm91cHMgPSBbXHJcbiAgICAgICAgICAgIFtcIi9cIiwgXCIqXCJdLFxyXG4gICAgICAgICAgICBbXCItXCIsIFwiK1wiXSxcclxuICAgICAgICAgICAgW1wiPT1cIiwgXCIhPVwiLCBcIjxcIiwgXCI8PVwiLCBcIj5cIiwgXCI+PVwiXVxyXG4gICAgICAgIF07XHJcblxyXG4gICAgICAgIGxldCBub2Rlc0NvcHkgPSB0aGlzLm5vZGVzO1xyXG5cclxuICAgICAgICBmb3IgKGxldCBwcmlvcml0eUdyb3VwIG9mIG9wZXJhdG9yUHJpb3JpdHlHcm91cHMpIHtcclxuICAgICAgICAgICAgbGV0IGkgPSAwO1xyXG5cclxuICAgICAgICAgICAgd2hpbGUgKGkgPCBub2Rlc0NvcHkubGVuZ3RoKSB7XHJcbiAgICAgICAgICAgICAgICBsZXQgbm9kZSA9IG5vZGVzQ29weVtpXTtcclxuXHJcbiAgICAgICAgICAgICAgICBpZiAobm9kZSBpbnN0YW5jZW9mIE9wZXJhdG9yTm9kZSAmJiBwcmlvcml0eUdyb3VwLmluZGV4T2Yobm9kZS5vcGVyYXRvcikgPj0gMCkge1xyXG4gICAgICAgICAgICAgICAgICAgIGxldCBsZWZ0ID0gZW5zdXJlVmFsdWVUeXBlKG5vZGVzQ29weVtpIC0gMV0uZXZhbHVhdGUoY29udGV4dCkpO1xyXG4gICAgICAgICAgICAgICAgICAgIGxldCByaWdodCA9IGVuc3VyZVZhbHVlVHlwZShub2Rlc0NvcHlbaSArIDFdLmV2YWx1YXRlKGNvbnRleHQpKTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKHR5cGVvZiBsZWZ0ICE9PSB0eXBlb2YgcmlnaHQpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgdGhyb3cgbmV3IEVycm9yKFwiSW5jb21wYXRpYmxlIG9wZXJhbmRzIFwiICsgbGVmdCArIFwiIGFuZCBcIiArIHJpZ2h0ICsgXCIgZm9yIG9wZXJhdG9yIFwiICsgbm9kZS5vcGVyYXRvcik7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgICAgICBsZXQgcmVzdWx0OiBMaXRlcmFsVmFsdWU7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGlmICh0eXBlb2YgbGVmdCA9PT0gXCJudW1iZXJcIiAmJiB0eXBlb2YgcmlnaHQgPT09IFwibnVtYmVyXCIpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgc3dpdGNoIChub2RlLm9wZXJhdG9yKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBjYXNlIFwiL1wiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IGxlZnQgLyByaWdodDtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGNhc2UgXCIqXCI6XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gbGVmdCAqIHJpZ2h0O1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgY2FzZSBcIi1cIjpcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQgPSBsZWZ0IC0gcmlnaHQ7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBjYXNlIFwiK1wiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IGxlZnQgKyByaWdodDtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKHR5cGVvZiBsZWZ0ID09PSBcInN0cmluZ1wiICYmIHR5cGVvZiByaWdodCA9PT0gXCJzdHJpbmdcIikge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBzd2l0Y2ggKG5vZGUub3BlcmF0b3IpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGNhc2UgXCIrXCI6XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gbGVmdCArIHJpZ2h0O1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgICAgICBzd2l0Y2ggKG5vZGUub3BlcmF0b3IpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgY2FzZSBcIj09XCI6XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQgPSBsZWZ0ID09IHJpZ2h0O1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGNhc2UgXCIhPVwiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gbGVmdCAhPSByaWdodDtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBjYXNlIFwiPFwiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gbGVmdCA8IHJpZ2h0O1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGNhc2UgXCI8PVwiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gbGVmdCA8PSByaWdodDtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBjYXNlIFwiPlwiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gbGVmdCA+IHJpZ2h0O1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGNhc2UgXCI+PVwiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gbGVmdCA+PSByaWdodDtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBkZWZhdWx0OlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgLy8gVGhpcyBzaG91bGQgbmV2ZXIgaGFwcGVuXHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgICAgICBub2Rlc0NvcHkuc3BsaWNlKGkgLSAxLCAzLCBuZXcgTGl0ZXJhbE5vZGUocmVzdWx0KSk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGktLTtcclxuICAgICAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgICAgICBpKys7XHJcbiAgICAgICAgICAgIH07XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICByZXR1cm4gbm9kZXNDb3B5WzBdLmV2YWx1YXRlKGNvbnRleHQpO1xyXG4gICAgfVxyXG59XHJcblxyXG5jbGFzcyBJZGVudGlmaWVyTm9kZSBleHRlbmRzIEV2YWx1YXRpb25Ob2RlIHtcclxuICAgIGlkZW50aWZpZXI6IHN0cmluZztcclxuXHJcbiAgICBldmFsdWF0ZShjb250ZXh0OiBFdmFsdWF0aW9uQ29udGV4dCk6IExpdGVyYWxWYWx1ZSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuaWRlbnRpZmllcjtcclxuICAgIH1cclxufVxyXG5cclxuY2xhc3MgSW5kZXhlck5vZGUgZXh0ZW5kcyBFdmFsdWF0aW9uTm9kZSB7XHJcbiAgICBpbmRleDogRXhwcmVzc2lvbk5vZGU7XHJcblxyXG4gICAgZXZhbHVhdGUoY29udGV4dDogRXZhbHVhdGlvbkNvbnRleHQpOiBMaXRlcmFsVmFsdWUge1xyXG4gICAgICAgIHJldHVybiB0aGlzLmluZGV4LmV2YWx1YXRlKGNvbnRleHQpO1xyXG4gICAgfVxyXG59XHJcblxyXG5jbGFzcyBGdW5jdGlvbkNhbGxOb2RlIGV4dGVuZHMgRXZhbHVhdGlvbk5vZGUge1xyXG4gICAgZnVuY3Rpb25OYW1lOiBzdHJpbmcgPSBudWxsO1xyXG4gICAgcGFyYW1ldGVyczogQXJyYXk8RXhwcmVzc2lvbk5vZGU+ID0gW107XHJcblxyXG4gICAgZXZhbHVhdGUoY29udGV4dDogRXZhbHVhdGlvbkNvbnRleHQpOiBMaXRlcmFsVmFsdWUge1xyXG4gICAgICAgIGxldCBjYWxsYmFjayA9IGNvbnRleHQuZ2V0RnVuY3Rpb24odGhpcy5mdW5jdGlvbk5hbWUpO1xyXG5cclxuICAgICAgICBpZiAoY2FsbGJhY2sgIT0gdW5kZWZpbmVkKSB7XHJcbiAgICAgICAgICAgIGxldCBldmFsdWF0ZWRQYXJhbXMgPSBbXTtcclxuXHJcbiAgICAgICAgICAgIGZvciAobGV0IHBhcmFtIG9mIHRoaXMucGFyYW1ldGVycykge1xyXG4gICAgICAgICAgICAgICAgZXZhbHVhdGVkUGFyYW1zLnB1c2gocGFyYW0uZXZhbHVhdGUoY29udGV4dCkpO1xyXG4gICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICByZXR1cm4gY2FsbGJhY2soZXZhbHVhdGVkUGFyYW1zKTtcclxuICAgICAgICB9XHJcblxyXG4gICAgICAgIHRocm93IG5ldyBFcnJvcihcIlVuZGVmaW5lZCBmdW5jdGlvbjogXCIgKyB0aGlzLmZ1bmN0aW9uTmFtZSk7XHJcbiAgICB9XHJcbn1cclxuXHJcbmNsYXNzIExpdGVyYWxOb2RlIGV4dGVuZHMgRXZhbHVhdGlvbk5vZGUge1xyXG4gICAgY29uc3RydWN0b3IocmVhZG9ubHkgdmFsdWU6IExpdGVyYWxWYWx1ZSkge1xyXG4gICAgICAgIHN1cGVyKCk7XHJcbiAgICB9XHJcblxyXG4gICAgZXZhbHVhdGUoY29udGV4dDogRXZhbHVhdGlvbkNvbnRleHQpOiBMaXRlcmFsVmFsdWUge1xyXG4gICAgICAgIHJldHVybiB0aGlzLnZhbHVlO1xyXG4gICAgfVxyXG59XHJcblxyXG5jbGFzcyBPcGVyYXRvck5vZGUgZXh0ZW5kcyBFdmFsdWF0aW9uTm9kZSB7XHJcbiAgICBjb25zdHJ1Y3RvcihyZWFkb25seSBvcGVyYXRvcjogVG9rZW5UeXBlKSB7XHJcbiAgICAgICAgc3VwZXIoKTtcclxuICAgIH1cclxuXHJcbiAgICBldmFsdWF0ZShjb250ZXh0OiBFdmFsdWF0aW9uQ29udGV4dCk6IExpdGVyYWxWYWx1ZSB7XHJcbiAgICAgICAgdGhyb3cgbmV3IEVycm9yKFwiQW4gb3BlcmF0b3IgY2Fubm90IGJlIGV2YWx1YXRlZCBvbiBpdHMgb3duLlwiKTtcclxuICAgIH1cclxufVxyXG5cclxudHlwZSBQYXRoUGFydCA9IEV4cHJlc3Npb25Ob2RlIHwgSWRlbnRpZmllck5vZGUgfCBJbmRleGVyTm9kZSB8IEZ1bmN0aW9uQ2FsbE5vZGU7XHJcblxyXG5jbGFzcyBQYXRoTm9kZSBleHRlbmRzIEV2YWx1YXRpb25Ob2RlIHtcclxuICAgIHBhcnRzOiBQYXRoUGFydFtdID0gW107XHJcblxyXG4gICAgZXZhbHVhdGUoY29udGV4dDogRXZhbHVhdGlvbkNvbnRleHQpOiBMaXRlcmFsVmFsdWUge1xyXG4gICAgICAgIGxldCByZXN1bHQ6IGFueSA9IHVuZGVmaW5lZDtcclxuICAgICAgICBsZXQgaW5kZXggPSAwO1xyXG5cclxuICAgICAgICB3aGlsZSAoaW5kZXggPCB0aGlzLnBhcnRzLmxlbmd0aCkge1xyXG4gICAgICAgICAgICBsZXQgcGFydCA9IHRoaXMucGFydHNbaW5kZXhdO1xyXG5cclxuICAgICAgICAgICAgdHJ5IHtcclxuICAgICAgICAgICAgICAgIGlmIChwYXJ0IGluc3RhbmNlb2YgSWRlbnRpZmllck5vZGUgJiYgaW5kZXggPT0gMCkge1xyXG4gICAgICAgICAgICAgICAgICAgIHN3aXRjaCAocGFydC5pZGVudGlmaWVyKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGNhc2UgXCIkcm9vdFwiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gY29udGV4dC4kcm9vdDtcclxuICAgICAgICAgICAgXHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgICAgICAgICAgY2FzZSBcIiRkYXRhXCI6XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQgPSBjb250ZXh0LmN1cnJlbnREYXRhQ29udGV4dDtcclxuICAgICAgICAgICAgXHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgICAgICAgICAgY2FzZSBcIiRpbmRleFwiOlxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gY29udGV4dC4kaW5kZXg7XHJcbiAgICAgICAgICAgIFxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGRlZmF1bHQ6XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQgPSBjb250ZXh0LmN1cnJlbnREYXRhQ29udGV4dFtwYXJ0LmlkZW50aWZpZXJdO1xyXG4gICAgICAgICAgICBcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgICAgIH0gICAgICAgICAgICBcclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgIGxldCBwYXJ0VmFsdWUgPSBwYXJ0LmV2YWx1YXRlKGNvbnRleHQpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBpZiAoaW5kZXggPT0gMCkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQgPSBwYXJ0VmFsdWU7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQgPSB0eXBlb2YgcGFydFZhbHVlICE9PSBcImJvb2xlYW5cIiA/IHJlc3VsdFtwYXJ0VmFsdWVdIDogcmVzdWx0W3BhcnRWYWx1ZS50b1N0cmluZygpXTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgY2F0Y2ggKGUpIHtcclxuICAgICAgICAgICAgICAgIHJldHVybiB1bmRlZmluZWQ7XHJcbiAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgIGluZGV4Kys7XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICByZXR1cm4gcmVzdWx0O1xyXG4gICAgfVxyXG59XHJcblxyXG5leHBvcnQgY2xhc3MgRXhwcmVzc2lvblBhcnNlciB7XHJcbiAgICBwcml2YXRlIF9pbmRleDogbnVtYmVyID0gMDtcclxuICAgIHByaXZhdGUgX3Rva2VuczogVG9rZW5bXTtcclxuXHJcbiAgICBwcml2YXRlIHVuZXhwZWN0ZWRUb2tlbigpIHtcclxuICAgICAgICB0aHJvdyBuZXcgRXJyb3IoXCJVbmV4cGVjdGVkIHRva2VuIFwiICsgdGhpcy5jdXJyZW50LnZhbHVlICsgXCIgYXQgcG9zaXRpb24gXCIgKyB0aGlzLmN1cnJlbnQub3JpZ2luYWxQb3NpdGlvbiArIFwiLlwiKTtcclxuICAgIH1cclxuXHJcbiAgICBwcml2YXRlIHVuZXhwZWN0ZWRFb2UoKSB7XHJcbiAgICAgICAgdGhyb3cgbmV3IEVycm9yKFwiVW5leHBlY3RlZCBlbmQgb2YgZXhwcmVzc2lvbi5cIik7XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBtb3ZlTmV4dCgpIHtcclxuICAgICAgICB0aGlzLl9pbmRleCsrO1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgcGFyc2VUb2tlbiguLi5leHBlY3RlZFRva2VuVHlwZXM6IFRva2VuVHlwZVtdKTogVG9rZW4ge1xyXG4gICAgICAgIGlmICh0aGlzLmVvZSkge1xyXG4gICAgICAgICAgICB0aGlzLnVuZXhwZWN0ZWRFb2UoKTtcclxuICAgICAgICB9XHJcblxyXG4gICAgICAgIGxldCBjdXJyZW50VG9rZW4gPSB0aGlzLmN1cnJlbnQ7XHJcblxyXG4gICAgICAgIGlmIChleHBlY3RlZFRva2VuVHlwZXMuaW5kZXhPZih0aGlzLmN1cnJlbnQudHlwZSkgPCAwKSB7XHJcbiAgICAgICAgICAgIHRoaXMudW5leHBlY3RlZFRva2VuKCk7XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICB0aGlzLm1vdmVOZXh0KCk7XHJcblxyXG4gICAgICAgIHJldHVybiBjdXJyZW50VG9rZW47XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBwYXJzZU9wdGlvbmFsVG9rZW4oLi4uZXhwZWN0ZWRUb2tlblR5cGVzOiBUb2tlblR5cGVbXSk6IGJvb2xlYW4ge1xyXG4gICAgICAgIGlmICh0aGlzLmVvZSkge1xyXG4gICAgICAgICAgICB0aGlzLnVuZXhwZWN0ZWRFb2UoKTtcclxuICAgICAgICB9XHJcbiAgICAgICAgZWxzZSBpZiAoZXhwZWN0ZWRUb2tlblR5cGVzLmluZGV4T2YodGhpcy5jdXJyZW50LnR5cGUpIDwgMCkge1xyXG4gICAgICAgICAgICByZXR1cm4gZmFsc2U7XHJcbiAgICAgICAgfVxyXG4gICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICB0aGlzLm1vdmVOZXh0KCk7XHJcblxyXG4gICAgICAgICAgICByZXR1cm4gdHJ1ZTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBwYXJzZUZ1bmN0aW9uQ2FsbChmdW5jdGlvbk5hbWU6IHN0cmluZyk6IEZ1bmN0aW9uQ2FsbE5vZGUge1xyXG4gICAgICAgIGxldCByZXN1bHQgPSBuZXcgRnVuY3Rpb25DYWxsTm9kZSgpO1xyXG4gICAgICAgIHJlc3VsdC5mdW5jdGlvbk5hbWUgPSBmdW5jdGlvbk5hbWU7XHJcblxyXG4gICAgICAgIHRoaXMucGFyc2VUb2tlbihcIihcIik7XHJcblxyXG4gICAgICAgIGxldCBmaXJzdFBhcmFtZXRlciA9IHRoaXMucGFyc2VFeHByZXNzaW9uKCk7XHJcbiAgICAgICAgbGV0IG1vcmVQYXJhbWV0ZXJzOiBib29sZWFuID0gZmFsc2U7XHJcblxyXG4gICAgICAgIGlmIChmaXJzdFBhcmFtZXRlcikge1xyXG4gICAgICAgICAgICByZXN1bHQucGFyYW1ldGVycy5wdXNoKGZpcnN0UGFyYW1ldGVyKTtcclxuXHJcbiAgICAgICAgICAgIGRvIHtcclxuICAgICAgICAgICAgICAgIG1vcmVQYXJhbWV0ZXJzID0gdGhpcy5wYXJzZU9wdGlvbmFsVG9rZW4oXCIsXCIpO1xyXG5cclxuICAgICAgICAgICAgICAgIGlmIChtb3JlUGFyYW1ldGVycykge1xyXG4gICAgICAgICAgICAgICAgICAgIGxldCBwYXJhbWV0ZXIgPSB0aGlzLnBhcnNlRXhwcmVzc2lvbigpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICByZXN1bHQucGFyYW1ldGVycy5wdXNoKHBhcmFtZXRlcik7XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIH0gd2hpbGUgKG1vcmVQYXJhbWV0ZXJzKTtcclxuICAgICAgICB9XHJcblxyXG4gICAgICAgIHRoaXMucGFyc2VUb2tlbihcIilcIik7XHJcblxyXG4gICAgICAgIHJldHVybiByZXN1bHQ7XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBwYXJzZUlkZW50aWZpZXIoKTogSWRlbnRpZmllck5vZGUge1xyXG4gICAgICAgIGxldCByZXN1bHQgPSBuZXcgSWRlbnRpZmllck5vZGUoKTtcclxuXHJcbiAgICAgICAgcmVzdWx0LmlkZW50aWZpZXIgPSB0aGlzLmN1cnJlbnQudmFsdWU7XHJcblxyXG4gICAgICAgIHRoaXMubW92ZU5leHQoKTtcclxuXHJcbiAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgIH1cclxuXHJcbiAgICBwcml2YXRlIHBhcnNlSW5kZXhlcigpOiBJbmRleGVyTm9kZSB7XHJcbiAgICAgICAgbGV0IHJlc3VsdCA9IG5ldyBJbmRleGVyTm9kZSgpO1xyXG5cclxuICAgICAgICB0aGlzLnBhcnNlVG9rZW4oXCJbXCIpO1xyXG5cclxuICAgICAgICByZXN1bHQuaW5kZXggPSB0aGlzLnBhcnNlRXhwcmVzc2lvbigpO1xyXG5cclxuICAgICAgICB0aGlzLnBhcnNlVG9rZW4oXCJdXCIpO1xyXG5cclxuICAgICAgICByZXR1cm4gcmVzdWx0O1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgcGFyc2VQYXRoKCk6IFBhdGhOb2RlIHtcclxuICAgICAgICBsZXQgcmVzdWx0ID0gbmV3IFBhdGhOb2RlKCk7XHJcblxyXG4gICAgICAgIGxldCBleHBlY3RlZE5leHRUb2tlblR5cGVzOiBUb2tlblR5cGVbXSA9IFtcImlkZW50aWZpZXJcIiwgXCIoXCJdO1xyXG5cclxuICAgICAgICB3aGlsZSAoIXRoaXMuZW9lKSB7XHJcbiAgICAgICAgICAgIGlmIChleHBlY3RlZE5leHRUb2tlblR5cGVzLmluZGV4T2YodGhpcy5jdXJyZW50LnR5cGUpIDwgMCkge1xyXG4gICAgICAgICAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgc3dpdGNoICh0aGlzLmN1cnJlbnQudHlwZSkge1xyXG4gICAgICAgICAgICAgICAgY2FzZSBcIihcIjpcclxuICAgICAgICAgICAgICAgICAgICBpZiAocmVzdWx0LnBhcnRzLmxlbmd0aCA9PSAwKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHRoaXMubW92ZU5leHQoKTtcclxuICAgIFxyXG4gICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQucGFydHMucHVzaCh0aGlzLnBhcnNlRXhwcmVzc2lvbigpKTtcclxuICAgIFxyXG4gICAgICAgICAgICAgICAgICAgICAgICB0aGlzLnBhcnNlVG9rZW4oXCIpXCIpO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgbGV0IGZ1bmN0aW9uTmFtZTogc3RyaW5nID0gXCJcIjtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGZvciAobGV0IHBhcnQgb2YgcmVzdWx0LnBhcnRzKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBpZiAoIShwYXJ0IGluc3RhbmNlb2YgSWRlbnRpZmllck5vZGUpKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgdGhpcy51bmV4cGVjdGVkVG9rZW4oKTtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBpZiAoZnVuY3Rpb25OYW1lICE9IFwiXCIpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICBmdW5jdGlvbk5hbWUgKz0gXCIuXCI7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgZnVuY3Rpb25OYW1lICs9ICg8SWRlbnRpZmllck5vZGU+cGFydCkuaWRlbnRpZmllcjtcclxuICAgICAgICAgICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0LnBhcnRzID0gW107XHJcblxyXG4gICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQucGFydHMucHVzaCh0aGlzLnBhcnNlRnVuY3Rpb25DYWxsKGZ1bmN0aW9uTmFtZSkpO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgICAgICAgICAgZXhwZWN0ZWROZXh0VG9rZW5UeXBlcyA9IFtcIi5cIiwgXCJbXCJdO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgIGNhc2UgXCJbXCI6XHJcbiAgICAgICAgICAgICAgICAgICAgcmVzdWx0LnBhcnRzLnB1c2godGhpcy5wYXJzZUluZGV4ZXIoKSk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGV4cGVjdGVkTmV4dFRva2VuVHlwZXMgPSBbXCIuXCIsIFwiKFwiLCBcIltcIl07XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgY2FzZSBcImlkZW50aWZpZXJcIjpcclxuICAgICAgICAgICAgICAgICAgICByZXN1bHQucGFydHMucHVzaCh0aGlzLnBhcnNlSWRlbnRpZmllcigpKTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgZXhwZWN0ZWROZXh0VG9rZW5UeXBlcyA9IFtcIi5cIiwgXCIoXCIsIFwiW1wiXTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICBjYXNlIFwiLlwiOlxyXG4gICAgICAgICAgICAgICAgICAgIHRoaXMubW92ZU5leHQoKTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgZXhwZWN0ZWROZXh0VG9rZW5UeXBlcyA9IFtcImlkZW50aWZpZXJcIl07XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgZGVmYXVsdDpcclxuICAgICAgICAgICAgICAgICAgICBleHBlY3RlZE5leHRUb2tlblR5cGVzID0gW107XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgcGFyc2VFeHByZXNzaW9uKCk6IEV4cHJlc3Npb25Ob2RlIHtcclxuICAgICAgICBsZXQgcmVzdWx0OiBFeHByZXNzaW9uTm9kZSA9IG5ldyBFeHByZXNzaW9uTm9kZSgpO1xyXG5cclxuICAgICAgICBsZXQgZXhwZWN0ZWROZXh0VG9rZW5UeXBlczogVG9rZW5UeXBlW10gPSBsaXRlcmFscy5jb25jYXQoXCIoXCIsIFwiK1wiLCBcIi1cIik7XHJcblxyXG4gICAgICAgIHdoaWxlICghdGhpcy5lb2UpIHtcclxuICAgICAgICAgICAgaWYgKGV4cGVjdGVkTmV4dFRva2VuVHlwZXMuaW5kZXhPZih0aGlzLmN1cnJlbnQudHlwZSkgPCAwKSB7XHJcbiAgICAgICAgICAgICAgICBpZiAocmVzdWx0Lm5vZGVzLmxlbmd0aCA9PSAwKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgdGhpcy51bmV4cGVjdGVkVG9rZW4oKTtcclxuICAgICAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgICAgICByZXR1cm4gcmVzdWx0O1xyXG4gICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICBzd2l0Y2ggKHRoaXMuY3VycmVudC50eXBlKSB7XHJcbiAgICAgICAgICAgICAgICBjYXNlIFwiKFwiOlxyXG4gICAgICAgICAgICAgICAgY2FzZSBcImlkZW50aWZpZXJcIjpcclxuICAgICAgICAgICAgICAgICAgICByZXN1bHQubm9kZXMucHVzaCh0aGlzLnBhcnNlUGF0aCgpKTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgZXhwZWN0ZWROZXh0VG9rZW5UeXBlcyA9IG9yZGVyZWRPcGVyYXRvcnM7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgY2FzZSBcInN0cmluZ1wiOlxyXG4gICAgICAgICAgICAgICAgY2FzZSBcIm51bWJlclwiOlxyXG4gICAgICAgICAgICAgICAgY2FzZSBcImJvb2xlYW5cIjpcclxuICAgICAgICAgICAgICAgICAgICBpZiAodGhpcy5jdXJyZW50LnR5cGUgPT0gXCJzdHJpbmdcIikge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQubm9kZXMucHVzaChuZXcgTGl0ZXJhbE5vZGUodGhpcy5jdXJyZW50LnZhbHVlKSk7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgIGVsc2UgaWYgKHRoaXMuY3VycmVudC50eXBlID09IFwibnVtYmVyXCIpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0Lm5vZGVzLnB1c2gobmV3IExpdGVyYWxOb2RlKHBhcnNlRmxvYXQodGhpcy5jdXJyZW50LnZhbHVlKSkpO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0Lm5vZGVzLnB1c2gobmV3IExpdGVyYWxOb2RlKHRoaXMuY3VycmVudC52YWx1ZSA9PT0gXCJ0cnVlXCIpKTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIHRoaXMubW92ZU5leHQoKTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgZXhwZWN0ZWROZXh0VG9rZW5UeXBlcyA9IG9yZGVyZWRPcGVyYXRvcnM7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAgICAgY2FzZSBcIi1cIjpcclxuICAgICAgICAgICAgICAgICAgICBpZiAocmVzdWx0Lm5vZGVzLmxlbmd0aCA9PSAwKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdC5ub2Rlcy5wdXNoKG5ldyBMaXRlcmFsTm9kZSgtMSkpO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQubm9kZXMucHVzaChuZXcgT3BlcmF0b3JOb2RlKFwiKlwiKSk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgICAgICBleHBlY3RlZE5leHRUb2tlblR5cGVzID0gW1wiaWRlbnRpZmllclwiLCBcIm51bWJlclwiLCBcIihcIl07XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQubm9kZXMucHVzaChuZXcgT3BlcmF0b3JOb2RlKHRoaXMuY3VycmVudC50eXBlKSk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgICAgICBleHBlY3RlZE5leHRUb2tlblR5cGVzID0gbGl0ZXJhbHMuY29uY2F0KFwiKFwiKTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIHRoaXMubW92ZU5leHQoKTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICBjYXNlIFwiK1wiOlxyXG4gICAgICAgICAgICAgICAgICAgIGlmIChyZXN1bHQubm9kZXMubGVuZ3RoID09IDApIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgZXhwZWN0ZWROZXh0VG9rZW5UeXBlcyA9IGxpdGVyYWxzLmNvbmNhdChcIihcIik7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQubm9kZXMucHVzaChuZXcgT3BlcmF0b3JOb2RlKHRoaXMuY3VycmVudC50eXBlKSk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgICAgICBleHBlY3RlZE5leHRUb2tlblR5cGVzID0gbGl0ZXJhbHMuY29uY2F0KFwiKFwiKTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIHRoaXMubW92ZU5leHQoKTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICBjYXNlIFwiKlwiOlxyXG4gICAgICAgICAgICAgICAgY2FzZSBcIi9cIjpcclxuICAgICAgICAgICAgICAgIGNhc2UgXCI9PVwiOlxyXG4gICAgICAgICAgICAgICAgY2FzZSBcIiE9XCI6XHJcbiAgICAgICAgICAgICAgICBjYXNlIFwiPFwiOlxyXG4gICAgICAgICAgICAgICAgY2FzZSBcIjw9XCI6XHJcbiAgICAgICAgICAgICAgICBjYXNlIFwiPlwiOlxyXG4gICAgICAgICAgICAgICAgY2FzZSBcIj49XCI6XHJcbiAgICAgICAgICAgICAgICAgICAgcmVzdWx0Lm5vZGVzLnB1c2gobmV3IE9wZXJhdG9yTm9kZSh0aGlzLmN1cnJlbnQudHlwZSkpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICB0aGlzLm1vdmVOZXh0KCk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGV4cGVjdGVkTmV4dFRva2VuVHlwZXMgPSBsaXRlcmFscy5jb25jYXQoXCIoXCIpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgICAgIGRlZmF1bHQ6XHJcbiAgICAgICAgICAgICAgICAgICAgZXhwZWN0ZWROZXh0VG9rZW5UeXBlcyA9IFtdO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgIH1cclxuICAgIH1cclxuXHJcbiAgICBwcml2YXRlIGdldCBlb2UoKTogYm9vbGVhbiB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX2luZGV4ID49IHRoaXMuX3Rva2Vucy5sZW5ndGg7XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBnZXQgY3VycmVudCgpOiBUb2tlbiB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX3Rva2Vuc1t0aGlzLl9pbmRleF07XHJcbiAgICB9XHJcblxyXG4gICAgc3RhdGljIHBhcnNlQmluZGluZyhiaW5kaW5nRXhwcmVzc2lvbjogc3RyaW5nKTogQmluZGluZyB7XHJcbiAgICAgICAgbGV0IHBhcnNlciA9IG5ldyBFeHByZXNzaW9uUGFyc2VyKFRva2VuaXplci5wYXJzZShiaW5kaW5nRXhwcmVzc2lvbikpO1xyXG4gICAgICAgIHBhcnNlci5wYXJzZVRva2VuKFwie1wiKTtcclxuXHJcbiAgICAgICAgbGV0IGFsbG93TnVsbCA9ICFwYXJzZXIucGFyc2VPcHRpb25hbFRva2VuKFwiPyNcIik7XHJcbiAgICAgICAgbGV0IGV4cHJlc3Npb24gPSBwYXJzZXIucGFyc2VFeHByZXNzaW9uKCk7XHJcblxyXG4gICAgICAgIHBhcnNlci5wYXJzZVRva2VuKFwifVwiKTtcclxuXHJcbiAgICAgICAgcmV0dXJuIG5ldyBCaW5kaW5nKGV4cHJlc3Npb24sIGFsbG93TnVsbCk7XHJcbiAgICB9XHJcblxyXG4gICAgY29uc3RydWN0b3IodG9rZW5zOiBUb2tlbltdKSB7XHJcbiAgICAgICAgdGhpcy5fdG9rZW5zID0gdG9rZW5zO1xyXG4gICAgfVxyXG59XHJcblxyXG5leHBvcnQgY2xhc3MgQmluZGluZyB7XHJcbiAgICBjb25zdHJ1Y3Rvcihwcml2YXRlIHJlYWRvbmx5IGV4cHJlc3Npb246IEV2YWx1YXRpb25Ob2RlLCByZWFkb25seSBhbGxvd051bGw6IGJvb2xlYW4gPSB0cnVlKSB7fVxyXG5cclxuICAgIGV2YWx1YXRlKGNvbnRleHQ6IEV2YWx1YXRpb25Db250ZXh0KTogTGl0ZXJhbFZhbHVlIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5leHByZXNzaW9uLmV2YWx1YXRlKGNvbnRleHQpO1xyXG4gICAgfVxyXG59IiwiaW1wb3J0IHsgQmluZGluZywgRXhwcmVzc2lvblBhcnNlciwgRXZhbHVhdGlvbkNvbnRleHQgfSBmcm9tIFwiLi9leHByZXNzaW9uLXBhcnNlclwiO1xyXG5pbXBvcnQgeyBUcmFuc2Zvcm0gfSBmcm9tIFwic3RyZWFtXCI7XHJcblxyXG5jbGFzcyBUZW1wbGF0aXplZFN0cmluZyB7XHJcbiAgICBwcml2YXRlIF9wYXJ0czogQXJyYXk8c3RyaW5nIHwgQmluZGluZz4gPSBbXTtcclxuXHJcbiAgICBzdGF0aWMgcGFyc2Uoczogc3RyaW5nKTogc3RyaW5nIHwgVGVtcGxhdGl6ZWRTdHJpbmcge1xyXG4gICAgICAgIGxldCByZXN1bHQgPSBuZXcgVGVtcGxhdGl6ZWRTdHJpbmcoKTtcclxuICAgICAgICBsZXQgaSA9IDA7XHJcblxyXG4gICAgICAgIGRvIHtcclxuICAgICAgICAgICAgbGV0IGV4cHJlc3Npb25Gb3VuZCA9IGZhbHNlO1xyXG4gICAgICAgICAgICBsZXQgc3RhcnQgPSBpO1xyXG4gICAgICAgICAgICBsZXQgbG9vcDtcclxuICAgICAgICAgICAgXHJcbiAgICAgICAgICAgIGRvIHtcclxuICAgICAgICAgICAgICAgIGxvb3AgPSBmYWxzZTtcclxuXHJcbiAgICAgICAgICAgICAgICBzdGFydCA9IHMuaW5kZXhPZihcIntcIiwgc3RhcnQpO1xyXG5cclxuICAgICAgICAgICAgICAgIGlmIChzdGFydCA+PSAwKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKHN0YXJ0ICsgMSA8IHMubGVuZ3RoICYmIHNbc3RhcnQgKyAxXSA9PSBcIntcIikge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBzdGFydCArPSAyO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICAgICAgbG9vcCA9IHRydWU7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICB9IHdoaWxlIChsb29wKTtcclxuXHJcbiAgICAgICAgICAgIGlmIChzdGFydCA+PSAwKSB7XHJcbiAgICAgICAgICAgICAgICBsZXQgZW5kID0gcy5pbmRleE9mKFwifVwiLCBzdGFydCk7XHJcblxyXG4gICAgICAgICAgICAgICAgaWYgKGVuZCA+PSAwKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgZXhwcmVzc2lvbkZvdW5kID0gdHJ1ZTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKHN0YXJ0ID4gaSkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQuX3BhcnRzLnB1c2gocy5zdWJzdHJpbmcoaSwgc3RhcnQpKTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgICAgIGxldCBiaW5kbmdFeHByZXNzaW9uID0gcy5zdWJzdHJpbmcoc3RhcnQsIGVuZCArIDEpO1xyXG4gICAgICAgICAgICAgICAgICAgIGxldCBwYXJ0OiBzdHJpbmcgfCBCaW5kaW5nO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICB0cnkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBwYXJ0ID0gRXhwcmVzc2lvblBhcnNlci5wYXJzZUJpbmRpbmcoYmluZG5nRXhwcmVzc2lvbik7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgIGNhdGNoIChlKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHBhcnQgPSBiaW5kbmdFeHByZXNzaW9uO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgICAgICAgICAgcmVzdWx0Ll9wYXJ0cy5wdXNoKHBhcnQpO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBpID0gZW5kICsgMTtcclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgaWYgKCFleHByZXNzaW9uRm91bmQpIHtcclxuICAgICAgICAgICAgICAgIHJlc3VsdC5fcGFydHMucHVzaChzLnN1YnN0cihpKSk7XHJcblxyXG4gICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICB9IHdoaWxlIChpIDwgcy5sZW5ndGgpO1xyXG5cclxuICAgICAgICBpZiAocmVzdWx0Ll9wYXJ0cy5sZW5ndGggPT0gMSAmJiB0eXBlb2YgcmVzdWx0Ll9wYXJ0c1swXSA9PT0gXCJzdHJpbmdcIikge1xyXG4gICAgICAgICAgICByZXR1cm4gPHN0cmluZz5yZXN1bHQuX3BhcnRzWzBdO1xyXG4gICAgICAgIH1cclxuICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgICAgICB9XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBfc2hvdWxkRHJvcE93bmVyOiBib29sZWFuID0gZmFsc2U7XHJcblxyXG4gICAgcHJpdmF0ZSBldmFsRXhwcmVzc2lvbihiaW5kaW5nRXhwcmVzc2lvbjogQmluZGluZywgY29udGV4dDogRXZhbHVhdGlvbkNvbnRleHQpOiBhbnkge1xyXG4gICAgICAgIGxldCByZXN1bHQgPSBiaW5kaW5nRXhwcmVzc2lvbi5ldmFsdWF0ZShjb250ZXh0KTtcclxuXHJcbiAgICAgICAgaWYgKHJlc3VsdCA9PSB1bmRlZmluZWQpIHtcclxuICAgICAgICAgICAgdGhpcy5fc2hvdWxkRHJvcE93bmVyID0gdGhpcy5fc2hvdWxkRHJvcE93bmVyIHx8ICFiaW5kaW5nRXhwcmVzc2lvbi5hbGxvd051bGw7XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICByZXR1cm4gcmVzdWx0O1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgaW50ZXJuYWxFdmFsdWF0ZShjb250ZXh0OiBFdmFsdWF0aW9uQ29udGV4dCk6IGFueSB7XHJcbiAgICAgICAgaWYgKHRoaXMuX3BhcnRzLmxlbmd0aCA9PSAwKSB7XHJcbiAgICAgICAgICAgIHJldHVybiB1bmRlZmluZWQ7XHJcbiAgICAgICAgfVxyXG4gICAgICAgIGVsc2UgaWYgKHRoaXMuX3BhcnRzLmxlbmd0aCA9PSAxKSB7XHJcbiAgICAgICAgICAgIGlmICh0eXBlb2YgdGhpcy5fcGFydHNbMF0gPT09IFwic3RyaW5nXCIpIHtcclxuICAgICAgICAgICAgICAgIHJldHVybiB0aGlzLl9wYXJ0c1swXTtcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgIHJldHVybiB0aGlzLmV2YWxFeHByZXNzaW9uKDxCaW5kaW5nPnRoaXMuX3BhcnRzWzBdLCBjb250ZXh0KTtcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgIH1cclxuICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgbGV0IHMgPSBcIlwiO1xyXG5cclxuICAgICAgICAgICAgZm9yIChsZXQgcGFydCBvZiB0aGlzLl9wYXJ0cykge1xyXG4gICAgICAgICAgICAgICAgaWYgKHR5cGVvZiBwYXJ0ID09PSBcInN0cmluZ1wiKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgcyArPSBwYXJ0O1xyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgICAgICAgICAgcyArPSB0aGlzLmV2YWxFeHByZXNzaW9uKDxCaW5kaW5nPnBhcnQsIGNvbnRleHQpO1xyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICByZXR1cm4gcztcclxuICAgICAgICB9XHJcbiAgICB9XHJcblxyXG4gICAgZXZhbHVhdGUoY29udGV4dDogRXZhbHVhdGlvbkNvbnRleHQpOiBhbnkge1xyXG4gICAgICAgIHRoaXMuX3Nob3VsZERyb3BPd25lciA9IGZhbHNlO1xyXG5cclxuICAgICAgICByZXR1cm4gdGhpcy5pbnRlcm5hbEV2YWx1YXRlKGNvbnRleHQpO1xyXG4gICAgfVxyXG5cclxuICAgIGdldCBzaG91bGREcm9wT3duZXIoKTogYm9vbGVhbiB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX3Nob3VsZERyb3BPd25lcjtcclxuICAgIH1cclxufVxyXG5cclxuZXhwb3J0IGNsYXNzIFRlbXBsYXRlIHtcclxuICAgIHByaXZhdGUgc3RhdGljIHByZXBhcmUobm9kZTogYW55KTogYW55IHtcclxuICAgICAgICBpZiAodHlwZW9mIG5vZGUgPT09IFwic3RyaW5nXCIpIHtcclxuICAgICAgICAgICAgcmV0dXJuIFRlbXBsYXRpemVkU3RyaW5nLnBhcnNlKG5vZGUpO1xyXG4gICAgICAgIH1cclxuICAgICAgICBlbHNlIGlmICh0eXBlb2Ygbm9kZSA9PT0gXCJvYmplY3RcIiAmJiBub2RlICE9IG51bGwpIHtcclxuICAgICAgICAgICAgaWYgKEFycmF5LmlzQXJyYXkobm9kZSkpIHtcclxuICAgICAgICAgICAgICAgIGxldCByZXN1bHQ6IGFueVtdID0gW107XHJcblxyXG4gICAgICAgICAgICAgICAgZm9yIChsZXQgaXRlbSBvZiBub2RlKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgcmVzdWx0LnB1c2goVGVtcGxhdGUucHJlcGFyZShpdGVtKSk7XHJcbiAgICAgICAgICAgICAgICB9XHJcblxyXG4gICAgICAgICAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgIGxldCBrZXlzID0gT2JqZWN0LmtleXMobm9kZSk7XHJcbiAgICAgICAgICAgICAgICBsZXQgcmVzdWx0ID0ge307XHJcblxyXG4gICAgICAgICAgICAgICAgZm9yIChsZXQga2V5IG9mIGtleXMpIHtcclxuICAgICAgICAgICAgICAgICAgICByZXN1bHRba2V5XSA9IFRlbXBsYXRlLnByZXBhcmUobm9kZVtrZXldKTtcclxuICAgICAgICAgICAgICAgIH1cclxuXHJcbiAgICAgICAgICAgICAgICByZXR1cm4gcmVzdWx0O1xyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgfVxyXG4gICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICByZXR1cm4gbm9kZTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBfY29udGV4dDogRXZhbHVhdGlvbkNvbnRleHQ7XHJcblxyXG4gICAgcHJpdmF0ZSBleHBhbmRTaW5nbGVPYmplY3Qobm9kZTogb2JqZWN0KTogYW55IHtcclxuICAgICAgICBsZXQgcmVzdWx0ID0ge307XHJcbiAgICAgICAgbGV0IGtleXMgPSBPYmplY3Qua2V5cyhub2RlKTtcclxuXHJcbiAgICAgICAgZm9yIChsZXQga2V5IG9mIGtleXMpIHtcclxuICAgICAgICAgICAgaWYgKCF0aGlzLl9jb250ZXh0LmlzUmVzZXJ2ZWRGaWVsZChrZXkpKSB7XHJcbiAgICAgICAgICAgICAgICBsZXQgdmFsdWUgPSB0aGlzLmludGVybmFsRXhwYW5kKG5vZGVba2V5XSk7XHJcblxyXG4gICAgICAgICAgICAgICAgaWYgKHZhbHVlICE9IHVuZGVmaW5lZCkge1xyXG4gICAgICAgICAgICAgICAgICAgIHJlc3VsdFtrZXldID0gdmFsdWU7XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICB9XHJcblxyXG4gICAgICAgIHJldHVybiByZXN1bHQ7XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBpbnRlcm5hbEV4cGFuZChub2RlOiBhbnkpOiBhbnkge1xyXG4gICAgICAgIGxldCByZXN1bHQ6IGFueTtcclxuXHJcbiAgICAgICAgdGhpcy5fY29udGV4dC5zYXZlU3RhdGUoKTtcclxuXHJcbiAgICAgICAgaWYgKEFycmF5LmlzQXJyYXkobm9kZSkpIHtcclxuICAgICAgICAgICAgbGV0IGl0ZW1BcnJheTogYW55W10gPSBbXTtcclxuXHJcbiAgICAgICAgICAgIGZvciAobGV0IGl0ZW0gb2Ygbm9kZSkge1xyXG4gICAgICAgICAgICAgICAgbGV0IGV4cGFuZGVkSXRlbSA9IHRoaXMuaW50ZXJuYWxFeHBhbmQoaXRlbSk7XHJcblxyXG4gICAgICAgICAgICAgICAgaWYgKGV4cGFuZGVkSXRlbSAhPSBudWxsKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKEFycmF5LmlzQXJyYXkoZXhwYW5kZWRJdGVtKSkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBpdGVtQXJyYXkgPSBpdGVtQXJyYXkuY29uY2F0KGV4cGFuZGVkSXRlbSk7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBpdGVtQXJyYXkucHVzaChleHBhbmRlZEl0ZW0pO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgcmVzdWx0ID0gaXRlbUFycmF5O1xyXG4gICAgICAgIH1cclxuICAgICAgICBlbHNlIGlmIChub2RlIGluc3RhbmNlb2YgVGVtcGxhdGl6ZWRTdHJpbmcpIHtcclxuICAgICAgICAgICAgcmVzdWx0ID0gbm9kZS5ldmFsdWF0ZSh0aGlzLl9jb250ZXh0KTtcclxuXHJcbiAgICAgICAgICAgIGlmIChub2RlLnNob3VsZERyb3BPd25lcikge1xyXG4gICAgICAgICAgICAgICAgcmVzdWx0ID0gbnVsbDtcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgIH1cclxuICAgICAgICBlbHNlIGlmICh0eXBlb2Ygbm9kZSA9PT0gXCJvYmplY3RcIiAmJiBub2RlICE9IG51bGwpIHtcclxuICAgICAgICAgICAgbGV0IGRyb3BPYmplY3QgPSBmYWxzZTtcclxuICAgICAgICAgICAgbGV0IHdoZW4gPSBub2RlW1wiJHdoZW5cIl07XHJcblxyXG4gICAgICAgICAgICBpZiAod2hlbiBpbnN0YW5jZW9mIFRlbXBsYXRpemVkU3RyaW5nKSB7XHJcbiAgICAgICAgICAgICAgICBsZXQgd2hlblZhbHVlID0gd2hlbi5ldmFsdWF0ZSh0aGlzLl9jb250ZXh0KTtcclxuXHJcbiAgICAgICAgICAgICAgICBpZiAodHlwZW9mIHdoZW5WYWx1ZSA9PT0gXCJib29sZWFuXCIpIHtcclxuICAgICAgICAgICAgICAgICAgICBkcm9wT2JqZWN0ID0gIXdoZW5WYWx1ZTtcclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgaWYgKCFkcm9wT2JqZWN0KSB7XHJcbiAgICAgICAgICAgICAgICBsZXQgZGF0YUNvbnRleHQgPSBub2RlW1wiJGRhdGFcIl07XHJcblxyXG4gICAgICAgICAgICAgICAgaWYgKGRhdGFDb250ZXh0ICE9IHVuZGVmaW5lZCkge1xyXG4gICAgICAgICAgICAgICAgICAgIGlmIChkYXRhQ29udGV4dCBpbnN0YW5jZW9mIFRlbXBsYXRpemVkU3RyaW5nKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGRhdGFDb250ZXh0ID0gZGF0YUNvbnRleHQuZXZhbHVhdGUodGhpcy5fY29udGV4dCk7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgICAgICBpZiAoQXJyYXkuaXNBcnJheShkYXRhQ29udGV4dCkpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gW107XHJcblxyXG4gICAgICAgICAgICAgICAgICAgICAgICBmb3IgKGxldCBpID0gMDsgaSA8IGRhdGFDb250ZXh0Lmxlbmd0aDsgaSsrKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICB0aGlzLl9jb250ZXh0LiRkYXRhID0gZGF0YUNvbnRleHRbaV07XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICB0aGlzLl9jb250ZXh0LiRpbmRleCA9IGk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgbGV0IGV4cGFuZGVkT2JqZWN0ID0gdGhpcy5leHBhbmRTaW5nbGVPYmplY3Qobm9kZSk7XHJcblxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgaWYgKGV4cGFuZGVkT2JqZWN0ICE9IG51bGwpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICByZXN1bHQucHVzaChleHBhbmRlZE9iamVjdCk7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHRoaXMuX2NvbnRleHQuJGRhdGEgPSBkYXRhQ29udGV4dDtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IHRoaXMuZXhwYW5kU2luZ2xlT2JqZWN0KG5vZGUpO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IHRoaXMuZXhwYW5kU2luZ2xlT2JqZWN0KG5vZGUpO1xyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgcmVzdWx0ID0gbnVsbDtcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgIH1cclxuICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgcmVzdWx0ID0gbm9kZTtcclxuICAgICAgICB9XHJcblxyXG4gICAgICAgIHRoaXMuX2NvbnRleHQucmVzdG9yZUxhc3RTdGF0ZSgpO1xyXG5cclxuICAgICAgICByZXR1cm4gcmVzdWx0O1xyXG4gICAgfVxyXG5cclxuICAgIHByZXBhcmVkUGF5bG9hZDogYW55O1xyXG5cclxuICAgIGNvbnN0cnVjdG9yKHBheWxvYWQ6IGFueSkge1xyXG4gICAgICAgIHRoaXMucHJlcGFyZWRQYXlsb2FkID0gVGVtcGxhdGUucHJlcGFyZShwYXlsb2FkKTtcclxuICAgIH1cclxuXHJcbiAgICBleHBhbmQoY29udGV4dDogRXZhbHVhdGlvbkNvbnRleHQpOiBhbnkge1xyXG4gICAgICAgIHRoaXMuX2NvbnRleHQgPSBjb250ZXh0O1xyXG5cclxuICAgICAgICByZXR1cm4gdGhpcy5pbnRlcm5hbEV4cGFuZCh0aGlzLnByZXBhcmVkUGF5bG9hZCk7XHJcbiAgICB9XHJcbn1cclxuXHJcbmV4cG9ydCBmdW5jdGlvbiB0cmFuc2Zvcm0oY2FyZEpzb246IHN0cmluZywgZGF0YUpzb246IHN0cmluZykge1xyXG5cdHZhciB0ZW1wbGF0ZSA9IG5ldyBUZW1wbGF0ZShKU09OLnBhcnNlKGNhcmRKc29uKSk7XHJcblxyXG4gICAgdmFyIGNvbnRleHQgPSBuZXcgRXZhbHVhdGlvbkNvbnRleHQoKTtcclxuXHRjb250ZXh0LiRyb290ID0gSlNPTi5wYXJzZShkYXRhSnNvbik7XHJcblx0YWxlcnQoY29udGV4dC4kcm9vdCk7XHJcblxyXG4gICAgdmFyIHRyYW5zZm9ybWVkQ2FyZCA9IHRlbXBsYXRlLmV4cGFuZChjb250ZXh0KTtcclxuICAgIHJldHVybiBKU09OLnN0cmluZ2lmeSh0cmFuc2Zvcm1lZENhcmQpO1xyXG59Il0sInNvdXJjZVJvb3QiOiIifQ==