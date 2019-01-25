type TokenType = 
    "{" |
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
                i++;
            }
        }

        return result;
    }
}

Tokenizer.init();

type LiteralValue = string | number | boolean;

abstract class ExpressionNode {
    abstract print(): string;
    abstract evaluate(context: Object): LiteralValue;
}

function ensureValueType(value: any): LiteralValue {
    if (typeof value === "number" || typeof value ==="string" || typeof value === "boolean") {
        return value;
    }

    throw new Error("Invalid value type: " + typeof value);
}


type FunctionCallback = (params: any[]) => any;
type FunctionDictionary = { [key: string]: FunctionCallback };

class ExpressionContext {
    private static _builtInFunctions: FunctionDictionary = {}
    
    static init() {
        ExpressionContext._builtInFunctions["substr"] = (params: any[]) => {
            return (<string>params[0]).substr(<number>params[1], <number>params[2]);
        };
    }

    private _functions = {};
    private _$data: any;

    $root: any;

    registerFunction(name: string, callback: FunctionCallback) {
        this._functions[name] = callback;
    }

    unregisterFunction(name: string) {
        delete this._functions[name];
    }

    getFunction(name: string): FunctionCallback {
        let result = this._functions[name];

        if (result == undefined) {
            result = ExpressionContext._builtInFunctions[name];
        }

        return result;
    }

    get $data(): any {
        return this._$data != undefined ? this._$data : this.$root;
    }

    set $data(value: any) {
        this._$data = value;
    }
}

ExpressionContext.init();

class Expression extends ExpressionNode {
    nodes: Array<ExpressionNode> = [];

    evaluate(context: ExpressionContext): any {
        const operatorPriorityGroups = [
            [ "/", "*" ],
            [ "-", "+" ],
            [ "==", "!=", "<", "<=", ">", ">=" ]
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

                    let result: LiteralValue;

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
            };
        }

        return nodesCopy[0].evaluate(context);
    }

    print(): string {
        let result = "";

        for (let node of this.nodes) {
            if (result != "") {
                result += " ";
            }

            result += node.print();
        }

        return "(" + result + ")";
    }
}

type PropertyPathPart = string | Expression;

class PropertyPathNode extends ExpressionNode {
    properties: Array<PropertyPathPart> = [];

    evaluate(context: ExpressionContext): LiteralValue {
        let result: any;
        let index = 0;
        
        switch (<string>this.properties[0]) {
            case "$root":
                result = context.$root;
                index++;

                break;
            case "$data":
                result = context.$data;
                index++;

                break;
            default:
                result = context.$data;

                break;
        }

        while (index < this.properties.length) {
            let part = this.properties[index];

            try {
                if (typeof part === "string") {
                    result = result[part];
                }
                else {
                    result = result[part.evaluate(context)];
                }
            }
            catch {
                return undefined;
            }

            index++;
        }

        return result;
    }
    
    print(): string {
        let result = "";

        for (let part of this.properties) {
            if (typeof part === "string") {
                if (result != "") {
                    result += ".";
                }

                result += part;
            }
            else {
                result += "[" + part.print() + "]";
            }
        }

        return result;
    }
}

class FunctionCallNode extends ExpressionNode {
    functionName: string;
    parameters: Array<Expression> = [];

    evaluate(context: ExpressionContext): LiteralValue {
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
    
    print(): string {
        let result = "";

        for (let parameter of this.parameters) {
            if (result != "") {
                result += ", ";
            }

            result += parameter.print();
        }

        return this.functionName + "(" + result + ")";
    }
}

class LiteralNode extends ExpressionNode {
    constructor(readonly value: LiteralValue) {
        super();
    }

    evaluate(context: ExpressionContext): LiteralValue {
        return this.value;
    }
    
    print(): string {
        return this.value.toString();
    }
}

class OperatorNode extends ExpressionNode {
    constructor(readonly operator: TokenType) {
        super();
    }

    evaluate(context: ExpressionContext): LiteralValue {
        throw new Error("An operator cannot be evaluated on its own.");
    }
    
    print(): string {
        return this.operator;
    }
}

class ExpressionParser {
    private _index: number = 0;
    private _tokens: Token[];

    private unexpectedToken() {
        throw new Error("Unexpected token " + this.current.value + " at position " + this.current.originalPosition + ".");
    }

    private unexpectedEoe() {
        throw new Error("Unexpected end of expression.");
    }

    private isNextTokenType(types: TokenType[]): boolean {
        return types.indexOf(this.nextTokenType) >= 0;
    }

    private ensureTokenType(types: TokenType[]) {
        if (this.eoe) {
            this.unexpectedEoe();
        }
        else if (!(types.indexOf(this.current.type) >= 0)) {
            this.unexpectedToken();
        }
    }

    private moveNext(expectedTypes?: TokenType[]) {
        this._index++;

        if (expectedTypes) {
            this.ensureTokenType(expectedTypes);    
        }
    }

    private parseFunctionParameters(functionCall: FunctionCallNode) {
        let moreParameters = false;
        let startTokenType: TokenType = "(";

        do {
            functionCall.parameters.push(this.parseExpression(startTokenType, [")", ","]));

            moreParameters = this.current.type == ",";

            if (moreParameters) {
                startTokenType = ",";
            }
        } while (moreParameters);
    }

    private parsePropertyPathOrFunctionCall(): PropertyPathNode | FunctionCallNode {
        let result = new PropertyPathNode();

        let expectedTokenTypes: Array<TokenType> = ["identifier"];
        let canEndPath = false;
        let canBeFunctionCall = true;

        while (!this.eoe) {
            this.ensureTokenType(expectedTokenTypes);

            switch (this.current.type) {
                case "identifier":
                    result.properties.push(this.current.value);

                    expectedTokenTypes = [".", "["];

                    if (canBeFunctionCall) {
                        expectedTokenTypes.push("(");
                    }

                    canEndPath = true;

                    break;
                case ".":
                    expectedTokenTypes = ["identifier"];

                    canEndPath = false;

                    break;
                case "[":
                    result.properties.push(this.parseExpression("[", ["]"]));

                    expectedTokenTypes = ["."];

                    canEndPath = true;
                    canBeFunctionCall = false;

                    break;
                case "(":
                    let functionCall = new FunctionCallNode();
                    functionCall.functionName = result.properties.join(".");

                    this.parseFunctionParameters(functionCall);
            
                    return functionCall;
                default:
                    this.unexpectedToken();
            }

            if (!this.isNextTokenType(expectedTokenTypes) && canEndPath) {
                return result;
            }

            this.moveNext();
        }

        this.unexpectedToken();
    }

    private parseExpression(startTokenType: TokenType, endTokenTypes: TokenType[]): Expression {
        let result: Expression = new Expression();

        this.ensureTokenType([startTokenType]);
        this.moveNext();

        let expectedNextTokenTypes: Array<TokenType> = literals.concat(["+", "-"]).concat(["("]);

        while (!this.eoe) {
            this.ensureTokenType(expectedNextTokenTypes);

            switch (this.current.type) {
                case "(":
                    result.nodes.push(this.parseExpression("(", [")"]));

                    expectedNextTokenTypes = orderedOperators.concat(endTokenTypes);

                    break;
                case "]":
                case ")":
                case "}":
                case ",":
                    if (result.nodes.length == 0) {
                        this.unexpectedToken();
                    }

                    this.ensureTokenType(endTokenTypes);

                    return result;
                case "identifier":
                    result.nodes.push(this.parsePropertyPathOrFunctionCall());

                    expectedNextTokenTypes = orderedOperators.concat(endTokenTypes);

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

                    expectedNextTokenTypes = orderedOperators.concat(endTokenTypes);

                    break;
                case "-":
                    if (result.nodes.length == 0) {
                        result.nodes.push(new LiteralNode(-1));
                        result.nodes.push(new OperatorNode("*"));

                        expectedNextTokenTypes = ["identifier", "number", "("];

                        break;
                    }
                case "+":
                    if (result.nodes.length == 0) {
                        expectedNextTokenTypes = literals.concat(["("]);

                        break;
                    }
                case "*":
                case "/":
                case "==":
                case "!=":
                case "<":
                case "<=":
                case ">":
                case ">=":
                    if (result.nodes.length == 0) {
                        this.unexpectedToken();
                    }

                    result.nodes.push(new OperatorNode(this.current.type));

                    expectedNextTokenTypes = literals.concat(["("]);

                    break;
                default:
                    this.unexpectedToken();
            }

            this.moveNext();
        }

        this.unexpectedEoe();
    }

    private reset() {
        this._index = 0;
    }

    private get eoe(): boolean {
        return this._index >= this._tokens.length;
    }

    private get current(): Token {
        return this._tokens[this._index];
    }

    private get nextTokenType(): TokenType {
        if (this._index < this._tokens.length - 1) {
            return this._tokens[this._index + 1].type;
        }
        else {
            return null;
        }
    }

    parse(expression: string): Expression {
        this.reset();

        this._tokens = Tokenizer.parse(expression);

        return this.parseExpression("{", ["}"]);
    }
}