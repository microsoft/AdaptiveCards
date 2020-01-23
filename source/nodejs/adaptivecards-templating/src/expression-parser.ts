// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
type TokenType =
    "{" |
    "?#" |
    "}" |
    "[" |
    "]" |
    "(" |
    ")" |
    "identifier" |
    "." |
    "," |
    "+" |
    "-" |
    "*" |
    "/" |
    "%" |
    "==" |
    "!=" |
    "<" |
    "<=" |
    ">" |
    ">=" |
    "string" |
    "number" |
    "boolean";

const orderedOperators: Array<TokenType> = [
    "/",
    "%",
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

const literals: Array<TokenType> = [
    "identifier",
    "string",
    "number",
    "boolean"
];

interface TokenizerRule {
    tokenType: TokenType;
    regEx: RegExp;
}

interface Token {
    type: TokenType;
    value: string;
    originalPosition: number;
}

class Tokenizer {
    static rules: Array<TokenizerRule> = [];

    static init() {
        Tokenizer.rules.push(
            { tokenType: undefined, regEx: /^\s/ },
            { tokenType: "{", regEx: /^{/ },
            { tokenType: "?#", regEx: /^\?#/ },
            { tokenType: "}", regEx: /^}/ },
            { tokenType: "[", regEx: /^\[/ },
            { tokenType: "]", regEx: /^\]/ },
            { tokenType: "(", regEx: /^\(/ },
            { tokenType: ")", regEx: /^\)/ },
            { tokenType: "boolean", regEx: /^true|^false/ },
            { tokenType: "identifier", regEx: /^[$a-z_]+/i },
            { tokenType: ".", regEx: /^\./ },
            { tokenType: ",", regEx: /^,/ },
            { tokenType: "+", regEx: /^\+/ },
            { tokenType: "-", regEx: /^-/ },
            { tokenType: "*", regEx: /^\*/ },
            { tokenType: "/", regEx: /^\// },
            { tokenType: "%", regEx: /^\%/ },
            { tokenType: "==", regEx: /^==/ },
            { tokenType: "!=", regEx: /^!=/ },
            { tokenType: "<=", regEx: /^<=/ },
            { tokenType: "<", regEx: /^</ },
            { tokenType: ">=", regEx: /^>=/ },
            { tokenType: ">", regEx: /^>/ },
            { tokenType: "string", regEx: /^"([^"]*)"/ },
            { tokenType: "string", regEx: /^'([^']*)'/ },
            { tokenType: "number", regEx: /^\d*\.?\d+/ }
        )
    }

    static parse(expression: string): Token[] {
        let result: Token[] = [];
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
                        result.push(
                            {
                                type: rule.tokenType,
                                value: matches[matches.length == 1 ? 0 : 1],
                                originalPosition: i
                            }
                        )
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

Tokenizer.init();

type LiteralValue = string | number | boolean;

function ensureValueType(value: any): LiteralValue {
    if (typeof value === "number" || typeof value === "string" || typeof value === "boolean") {
        return value;
    }

    throw new Error("Invalid value type: " + typeof value);
}

type FunctionCallback = (...params: any[]) => any;
type FunctionDictionary = { [key: string]: FunctionCallback };

interface EvaluationContextState {
    $data: any;
    $index: any;
}

export class EvaluationContext {
    private static readonly _reservedFields = ["$data", "$root", "$index"];
    private static _builtInFunctions: FunctionDictionary = {}

    static init() {
        EvaluationContext._builtInFunctions["substr"] = (s, index, count) => {
            if (typeof s === "string" && typeof index === "number" && typeof count === "number") {
                return (s.substr(index, count));
            }
            else {
                return "";
            }
        };
        EvaluationContext._builtInFunctions["JSON.parse"] = (input) => {
            return JSON.parse(input);
        };
        EvaluationContext._builtInFunctions["if"] = (condition, ifTrue, ifFalse) => {
            return condition ? ifTrue : ifFalse;
        };
        EvaluationContext._builtInFunctions["toUpper"] = (input) => {
            return typeof input === "string" ? input.toUpperCase() : input;
        };
        EvaluationContext._builtInFunctions["toLower"] = (input) => {
            return typeof input === "string" ? input.toLowerCase() : input;
        };
        EvaluationContext._builtInFunctions["Date.format"] = (input, format) => {
            const acceptedFormats = [ "long", "short", "compact" ];

            let inputAsNumber: number;

            if (typeof input === "string") {
                inputAsNumber = Date.parse(input);
            }
            else if (typeof input === "number") {
                inputAsNumber = input;
            }
            else {
                return input;
            }

            let date = new Date(inputAsNumber);

            let effectiveFormat: string = "compact";

            if (typeof format === "string") {
                effectiveFormat = format.toLowerCase();

                if (acceptedFormats.indexOf(effectiveFormat) < 0) {
                    effectiveFormat = "compact";
                }
            }

            return effectiveFormat === "compact" ? date.toLocaleDateString() : date.toLocaleDateString(undefined, { day: "numeric", weekday: effectiveFormat, month: effectiveFormat, year: "numeric" });
        };
        EvaluationContext._builtInFunctions["Time.format"] = (input) => {
            let inputAsNumber: number;

            if (typeof input === "string") {
                inputAsNumber = Date.parse(input);
            }
            else if (typeof input === "number") {
                inputAsNumber = input;
            }
            else {
                return input;
            }

            let date = new Date(inputAsNumber);

            return date.toLocaleTimeString(undefined, { hour: 'numeric', minute: '2-digit' });
        };
        EvaluationContext._builtInFunctions["round"] = (input) => {
            return typeof input === "number" ? Math.round(input) : input;
        };
        EvaluationContext._builtInFunctions["ceil"] = (input) => {
            return typeof input === "number" ? Math.ceil(input) : input;
        };
        EvaluationContext._builtInFunctions["floor"] = (input) => {
            return typeof input === "number" ? Math.floor(input) : input;
        };
    }

    private _functions = {};
    private _stateStack: EvaluationContextState[] = [];

    $root: any;
    $data: any;
    $index: number;

    registerFunction(name: string, callback: FunctionCallback) {
        this._functions[name] = callback;
    }

    unregisterFunction(name: string) {
        delete this._functions[name];
    }

    getFunction(name: string): FunctionCallback {
        let result = this._functions[name];

        if (result == undefined) {
            result = EvaluationContext._builtInFunctions[name];
        }

        return result;
    }

    isReservedField(name: string): boolean {
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

    get currentDataContext(): any {
        return this.$data != undefined ? this.$data : this.$root;
    }
}

EvaluationContext.init();

abstract class EvaluationNode {
    abstract evaluate(context: EvaluationContext): LiteralValue;
}

class ExpressionNode extends EvaluationNode {
    nodes: Array<EvaluationNode> = [];
    allowNull: boolean = true;

    evaluate(context: EvaluationContext): any {
        const operatorPriorityGroups = [
            ["/", "%", "*"],
            ["-", "+"],
            ["==", "!=", "<", "<=", ">", ">="]
        ];

        let nodesCopy = this.nodes.slice();

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

                    let result: LiteralValue;

                    if (typeof left === "number" && typeof right === "number") {
                        switch (node.operator) {
                            case "/":
                                result = left / right;
                                break;
                            case "%":
                                result = left % right;
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
            };
        }

        return nodesCopy[0].evaluate(context);
    }
}

class IdentifierNode extends EvaluationNode {
    identifier: string;

    evaluate(context: EvaluationContext): LiteralValue {
        return this.identifier;
    }
}

class IndexerNode extends EvaluationNode {
    index: ExpressionNode;

    evaluate(context: EvaluationContext): LiteralValue {
        return this.index.evaluate(context);
    }
}

class FunctionCallNode extends EvaluationNode {
    functionName: string = null;
    parameters: Array<ExpressionNode> = [];

    evaluate(context: EvaluationContext): LiteralValue {
        let callback = context.getFunction(this.functionName);

        if (callback != undefined) {
            let evaluatedParams = [];

            for (let param of this.parameters) {
                evaluatedParams.push(param.evaluate(context));
            }

            return callback(...evaluatedParams);
        }

        throw new Error("Undefined function: " + this.functionName);
    }
}

class LiteralNode extends EvaluationNode {
    constructor(readonly value: LiteralValue) {
        super();
    }

    evaluate(context: EvaluationContext): LiteralValue {
        return this.value;
    }
}

class OperatorNode extends EvaluationNode {
    constructor(readonly operator: TokenType) {
        super();
    }

    evaluate(context: EvaluationContext): LiteralValue {
        throw new Error("An operator cannot be evaluated on its own.");
    }
}

type PathPart = ExpressionNode | IdentifierNode | IndexerNode | FunctionCallNode;

class PathNode extends EvaluationNode {
    parts: PathPart[] = [];

    evaluate(context: EvaluationContext): LiteralValue {
        let result: any = undefined;
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

export class ExpressionParser {
    private _index: number = 0;
    private _tokens: Token[];

    private unexpectedToken() {
        throw new Error("Unexpected token " + this.current.value + " at position " + this.current.originalPosition + ".");
    }

    private unexpectedEoe() {
        throw new Error("Unexpected end of expression.");
    }

    private moveNext() {
        this._index++;
    }

    private parseToken(...expectedTokenTypes: TokenType[]): Token {
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

    private parseOptionalToken(...expectedTokenTypes: TokenType[]): boolean {
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

    private parseFunctionCall(functionName: string): FunctionCallNode {
        let result = new FunctionCallNode();
        result.functionName = functionName;

        this.parseToken("(");

        let firstParameter = this.parseExpression();
        let moreParameters: boolean = false;

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

    private parseIdentifier(): IdentifierNode {
        let result = new IdentifierNode();

        result.identifier = this.current.value;

        this.moveNext();

        return result;
    }

    private parseIndexer(): IndexerNode {
        let result = new IndexerNode();

        this.parseToken("[");

        result.index = this.parseExpression();

        this.parseToken("]");

        return result;
    }

    private parsePath(): PathNode {
        let result = new PathNode();

        let expectedNextTokenTypes: TokenType[] = ["identifier", "("];

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
                        let functionName: string = "";

                        for (let part of result.parts) {
                            if (!(part instanceof IdentifierNode)) {
                                this.unexpectedToken();
                            }

                            if (functionName != "") {
                                functionName += ".";
                            }

                            functionName += (<IdentifierNode>part).identifier;
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

    private parseExpression(): ExpressionNode {
        let result: ExpressionNode = new ExpressionNode();

        let expectedNextTokenTypes: TokenType[] = literals.concat("(", "+", "-");

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
                case "%":
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

    private get eoe(): boolean {
        return this._index >= this._tokens.length;
    }

    private get current(): Token {
        return this._tokens[this._index];
    }

    static parseBinding(bindingExpression: string): Binding {
        let parser = new ExpressionParser(Tokenizer.parse(bindingExpression));
        parser.parseToken("{");

        let allowNull = !parser.parseOptionalToken("?#");
        let expression = parser.parseExpression();

        parser.parseToken("}");

        return new Binding(expression, allowNull);
    }

    constructor(tokens: Token[]) {
        this._tokens = tokens;
    }
}

export class Binding {
    constructor(private readonly expression: EvaluationNode, readonly allowNull: boolean = true) {}

    evaluate(context: EvaluationContext): LiteralValue {
        return this.expression.evaluate(context);
    }
}
