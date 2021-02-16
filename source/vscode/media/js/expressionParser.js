"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const orderedOperators = [
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
const literals = [
    "identifier",
    "string",
    "number",
    "boolean"
];
class Tokenizer {
    static init() {
        Tokenizer.rules.push({ tokenType: undefined, regEx: /^\s/ }, { tokenType: "{", regEx: /^{/ }, { tokenType: "?#", regEx: /^\?#/ }, { tokenType: "}", regEx: /^}/ }, { tokenType: "[", regEx: /^\[/ }, { tokenType: "]", regEx: /^\]/ }, { tokenType: "(", regEx: /^\(/ }, { tokenType: ")", regEx: /^\)/ }, { tokenType: "boolean", regEx: /^true|^false/ }, { tokenType: "identifier", regEx: /^[$a-z_]+/i }, { tokenType: ".", regEx: /^\./ }, { tokenType: ",", regEx: /^,/ }, { tokenType: "+", regEx: /^\+/ }, { tokenType: "-", regEx: /^-/ }, { tokenType: "*", regEx: /^\*/ }, { tokenType: "/", regEx: /^\// }, { tokenType: "==", regEx: /^==/ }, { tokenType: "!=", regEx: /^!=/ }, { tokenType: "<=", regEx: /^<=/ }, { tokenType: "<", regEx: /^</ }, { tokenType: ">=", regEx: /^>=/ }, { tokenType: ">", regEx: /^>/ }, { tokenType: "string", regEx: /^"([^"]*)"/ }, { tokenType: "string", regEx: /^'([^']*)'/ }, { tokenType: "number", regEx: /^\d*\.?\d+/ });
    }
    static parse(expression) {
        let result = [];
        let i = 0;
        while (i < expression.length) {
            let subExpression = expression.substring(i);
            let matchFound = false;
            for (let rule of Tokenizer.rules) {
                let matches = rule.regEx.exec(subExpression);
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
    }
}
Tokenizer.rules = [];
Tokenizer.init();
function ensureValueType(value) {
    if (typeof value === "number" || typeof value === "string" || typeof value === "boolean") {
        return value;
    }
    throw new Error("Invalid value type: " + typeof value);
}
class EvaluationContext {
    constructor() {
        this._functions = {};
        this._stateStack = [];
    }
    static init() {
        EvaluationContext._builtInFunctions["substr"] = (params) => {
            return params[0].substr(params[1], params[2]);
        };
        EvaluationContext._builtInFunctions["JSON.parse"] = (params) => {
            return JSON.parse(params[0]);
        };
        EvaluationContext._builtInFunctions["if"] = (params) => {
            return params[0] ? params[1] : params[2];
        };
    }
    registerFunction(name, callback) {
        this._functions[name] = callback;
    }
    unregisterFunction(name) {
        delete this._functions[name];
    }
    getFunction(name) {
        let result = this._functions[name];
        if (result == undefined) {
            result = EvaluationContext._builtInFunctions[name];
        }
        return result;
    }
    isReservedField(name) {
        return EvaluationContext._reservedFields.indexOf(name) >= 0;
    }
    saveState() {
        this._stateStack.push({ $data: this.$data, $index: this.$index });
    }
    restoreLastState() {
        if (this._stateStack.length == 0) {
            throw new Error("There is no evaluation context state to restore.");
        }
        let savedContext = this._stateStack.pop();
        this.$data = savedContext.$data;
        this.$index = savedContext.$index;
    }
    get currentDataContext() {
        return this.$data != undefined ? this.$data : this.$root;
    }
}
EvaluationContext._reservedFields = ["$data", "$root", "$index"];
EvaluationContext._builtInFunctions = {};
exports.EvaluationContext = EvaluationContext;
EvaluationContext.init();
class EvaluationNode {
}
class ExpressionNode extends EvaluationNode {
    constructor() {
        super(...arguments);
        this.nodes = [];
        this.allowNull = true;
    }
    evaluate(context) {
        const operatorPriorityGroups = [
            ["/", "*"],
            ["-", "+"],
            ["==", "!=", "<", "<=", ">", ">="]
        ];
        let nodesCopy = this.nodes;
        for (let priorityGroup of operatorPriorityGroups) {
            let i = 0;
            while (i < nodesCopy.length) {
                let node = nodesCopy[i];
                if (node instanceof OperatorNode && priorityGroup.indexOf(node.operator) >= 0) {
                    let left = ensureValueType(nodesCopy[i - 1].evaluate(context));
                    let right = ensureValueType(nodesCopy[i + 1].evaluate(context));
                    if (typeof left !== typeof right) {
                        throw new Error("Incompatible operands " + left + " and " + right + " for operator " + node.operator);
                    }
                    let result;
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
    }
}
class IdentifierNode extends EvaluationNode {
    evaluate(context) {
        return this.identifier;
    }
}
class IndexerNode extends EvaluationNode {
    evaluate(context) {
        return this.index.evaluate(context);
    }
}
class FunctionCallNode extends EvaluationNode {
    constructor() {
        super(...arguments);
        this.functionName = null;
        this.parameters = [];
    }
    evaluate(context) {
        let callback = context.getFunction(this.functionName);
        if (callback != undefined) {
            let evaluatedParams = [];
            for (let param of this.parameters) {
                evaluatedParams.push(param.evaluate(context));
            }
            return callback(evaluatedParams);
        }
        throw new Error("Undefined function: " + this.functionName);
    }
}
class LiteralNode extends EvaluationNode {
    constructor(value) {
        super();
        this.value = value;
    }
    evaluate(context) {
        return this.value;
    }
}
class OperatorNode extends EvaluationNode {
    constructor(operator) {
        super();
        this.operator = operator;
    }
    evaluate(context) {
        throw new Error("An operator cannot be evaluated on its own.");
    }
}
class PathNode extends EvaluationNode {
    constructor() {
        super(...arguments);
        this.parts = [];
    }
    evaluate(context) {
        let result = undefined;
        let index = 0;
        while (index < this.parts.length) {
            let part = this.parts[index];
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
                    let partValue = part.evaluate(context);
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
    }
}
class ExpressionParser {
    constructor(tokens) {
        this._index = 0;
        this._tokens = tokens;
    }
    unexpectedToken() {
        throw new Error("Unexpected token " + this.current.value + " at position " + this.current.originalPosition + ".");
    }
    unexpectedEoe() {
        throw new Error("Unexpected end of expression.");
    }
    moveNext() {
        this._index++;
    }
    parseToken(...expectedTokenTypes) {
        if (this.eoe) {
            this.unexpectedEoe();
        }
        let currentToken = this.current;
        if (expectedTokenTypes.indexOf(this.current.type) < 0) {
            this.unexpectedToken();
        }
        this.moveNext();
        return currentToken;
    }
    parseOptionalToken(...expectedTokenTypes) {
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
    }
    parseFunctionCall(functionName) {
        let result = new FunctionCallNode();
        result.functionName = functionName;
        this.parseToken("(");
        let firstParameter = this.parseExpression();
        let moreParameters = false;
        if (firstParameter) {
            result.parameters.push(firstParameter);
            do {
                moreParameters = this.parseOptionalToken(",");
                if (moreParameters) {
                    let parameter = this.parseExpression();
                    result.parameters.push(parameter);
                }
            } while (moreParameters);
        }
        this.parseToken(")");
        return result;
    }
    parseIdentifier() {
        let result = new IdentifierNode();
        result.identifier = this.current.value;
        this.moveNext();
        return result;
    }
    parseIndexer() {
        let result = new IndexerNode();
        this.parseToken("[");
        result.index = this.parseExpression();
        this.parseToken("]");
        return result;
    }
    parsePath() {
        let result = new PathNode();
        let expectedNextTokenTypes = ["identifier", "("];
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
                        let functionName = "";
                        for (let part of result.parts) {
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
    }
    parseExpression() {
        let result = new ExpressionNode();
        let expectedNextTokenTypes = literals.concat("(", "+", "-");
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
    }
    get eoe() {
        return this._index >= this._tokens.length;
    }
    get current() {
        return this._tokens[this._index];
    }
    static parseBinding(bindingExpression) {
        let parser = new ExpressionParser(Tokenizer.parse(bindingExpression));
        parser.parseToken("{");
        let allowNull = !parser.parseOptionalToken("?#");
        let expression = parser.parseExpression();
        parser.parseToken("}");
        return new Binding(expression, allowNull);
    }
}
exports.ExpressionParser = ExpressionParser;
class Binding {
    constructor(expression, allowNull = true) {
        this.expression = expression;
        this.allowNull = allowNull;
    }
    evaluate(context) {
        return this.expression.evaluate(context);
    }
}
exports.Binding = Binding;
//# sourceMappingURL=expressionParser.js.map