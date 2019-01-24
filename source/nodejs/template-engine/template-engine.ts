enum TokenType {
    WhiteSpace,
    OpenCurlyBracket,
    CloseCurlyBracket,
    OpenSquareBracket,
    CloseSquareBracket,
    OpenParenthese,
    CloseParenthese,
    Identifier,
    Period,
    Comma,
    PlusSign,
    MinusSign,
    MultiplySign,
    DivideSign,
    EqualOperator,
    NotEqualOperator,
    LessThanOperator,
    LessThanOrEqualOperator,
    GreaterThanOperator,
    GreaterThanOrEqualOperator,
    StringLiteral,
    NumberLitteral,
    BooleanLiteral
}

type BinaryOperatorTokenType =
    TokenType.PlusSign |
    TokenType.MinusSign |
    TokenType.MultiplySign |
    TokenType.DivideSign |
    TokenType.EqualOperator |
    TokenType.NotEqualOperator |
    TokenType.LessThanOperator |
    TokenType.LessThanOrEqualOperator |
    TokenType.GreaterThanOperator |
    TokenType.GreaterThanOrEqualOperator;

type LiteralTokenType = 
    TokenType.StringLiteral |
    TokenType.NumberLitteral |
    TokenType.BooleanLiteral;

const arithmeticOperatorTokenTypes = [
    TokenType.PlusSign,
    TokenType.MinusSign,
    TokenType.MultiplySign,
    TokenType.DivideSign
];

const comparisonOperatorTokenTypes = [
    TokenType.EqualOperator,
    TokenType.NotEqualOperator,
    TokenType.LessThanOperator,
    TokenType.LessThanOrEqualOperator,
    TokenType.GreaterThanOperator,
    TokenType.GreaterThanOrEqualOperator
];

const operatorTokenTypes = arithmeticOperatorTokenTypes.concat(comparisonOperatorTokenTypes);

const literalTokenTypes = [
    TokenType.Identifier,
    TokenType.StringLiteral,
    TokenType.NumberLitteral,
    TokenType.BooleanLiteral
];

interface TokenizerRule {
    tokenType: TokenType;
    regEx: RegExp;
    skip?: boolean
}

interface Token {
    type: TokenType;
    value: string;
    originalPosition: number;
}

class Tokenizer {
    static rules: Array<TokenizerRule> = [];

    static initialize() {
        Tokenizer.rules.push(
            { tokenType: TokenType.WhiteSpace, regEx: /^\s/, skip: true },
            { tokenType: TokenType.OpenCurlyBracket, regEx: /^{/ },
            { tokenType: TokenType.CloseCurlyBracket, regEx: /^}/ },
            { tokenType: TokenType.OpenSquareBracket, regEx: /^\[/ },
            { tokenType: TokenType.CloseSquareBracket, regEx: /^\]/ },
            { tokenType: TokenType.OpenParenthese, regEx: /^\(/ },
            { tokenType: TokenType.CloseParenthese, regEx: /^\)/ },
            { tokenType: TokenType.BooleanLiteral, regEx: /^true|^false/ },
            { tokenType: TokenType.Identifier, regEx: /^[a-z_]+/i },
            { tokenType: TokenType.Period, regEx: /^\./ },
            { tokenType: TokenType.Comma, regEx: /^,/ },
            { tokenType: TokenType.PlusSign, regEx: /^\+/ },
            { tokenType: TokenType.MinusSign, regEx: /^-/ },
            { tokenType: TokenType.MultiplySign, regEx: /^\*/ },
            { tokenType: TokenType.DivideSign, regEx: /^\// },
            { tokenType: TokenType.EqualOperator, regEx: /^==/ },
            { tokenType: TokenType.NotEqualOperator, regEx: /^!=/ },
            { tokenType: TokenType.LessThanOrEqualOperator, regEx: /^<=/ },
            { tokenType: TokenType.LessThanOperator, regEx: /^</ },
            { tokenType: TokenType.GreaterThanOrEqualOperator, regEx: /^>=/ },
            { tokenType: TokenType.GreaterThanOperator, regEx: /^>/ },
            { tokenType: TokenType.StringLiteral, regEx: /^(?:"[^"]*")|^(?:'[^']*')/ },
            { tokenType: TokenType.NumberLitteral, regEx: /^\d*\.?\d+/ }
        )
    }

    private _tokens: Array<Token>;

    protected internalParse(expression: string) {
        let i = 0;

        while (i < expression.length) {
            let subExpression = expression.substring(i);
            let matchFound = false;

            for (let rule of Tokenizer.rules) {
                let matches = rule.regEx.exec(subExpression);

                if (matches) {
                    if (matches.length > 1) {
                        throw new Error("A tokenizer rule found more than 1 match.");
                    }

                    if (!rule.skip) {
                        this._tokens.push(
                            {
                                type: rule.tokenType,
                                value: matches[0],
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
    }

    parse(expression: string) {
        this._tokens = [];

        this.internalParse(expression);
    }

    get tokens(): Array<Token> {
        return this._tokens;
    }
}

Tokenizer.initialize();

abstract class ExpressionNode {
    abstract print(): string;
}

class Expression extends ExpressionNode {
    nodes: Array<ExpressionNode> = [];

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

type LiteralValue = string | number | boolean;

class LiteralNode extends ExpressionNode {
    constructor(readonly value: LiteralValue) {
        super();
    }

    print(): string {
        return this.value.toString();
    }
}

class OperatorNode extends ExpressionNode {
    constructor(readonly operator: BinaryOperatorTokenType) {
        super();
    }

    print(): string {
        switch (this.operator) {
            case TokenType.PlusSign:
                return "+";
            case TokenType.MinusSign:
                return "-";
            case TokenType.MultiplySign:
                return "*";
            case TokenType.DivideSign:
                return "/";
            case TokenType.EqualOperator:
                return "==";
            case TokenType.NotEqualOperator:
                return "!=";
            case TokenType.LessThanOperator:
                return "<";
            case TokenType.LessThanOrEqualOperator:
                return "<=";
            case TokenType.GreaterThanOperator:
                return ">";
            case TokenType.GreaterThanOrEqualOperator:
                return ">=";
            default:
                return TokenType[this.operator];
        }
    }
}

class ExpressionParser {
    private _currentTokenIndex: number = 0;

    private unexpectedTokenType() {
        throw new Error("Unexpected token " + this.currentToken.value + " at position " + this.currentToken.originalPosition + ".");
    }

    private unexpectedEndOfExpression() {
        throw new Error("Unexpected end of expression.");
    }

    private isTokenType(tokenTypes: TokenType[]): boolean {
        return tokenTypes.indexOf(this.currentToken.type) >= 0;
    }

    private isNextTokenType(tokenTypes: TokenType[]): boolean {
        return tokenTypes.indexOf(this.nextTokenType) >= 0;
    }

    private ensureTokenType(expectedTokenTypes: TokenType[]) {
        if (this.eof) {
            this.unexpectedEndOfExpression();
        }
        else if (!this.isTokenType(expectedTokenTypes)) {
            this.unexpectedTokenType();
        }
    }

    private moveToNextToken(expectedTokenTypes?: TokenType[]) {
        this._currentTokenIndex++;

        if (expectedTokenTypes) {
            this.ensureTokenType(expectedTokenTypes);    
        }
    }

    private get eof(): boolean {
        return this._currentTokenIndex >= this.tokens.length;
    }

    private get currentToken(): Token {
        return this.tokens[this._currentTokenIndex];
    }

    private get nextTokenType(): TokenType {
        if (this._currentTokenIndex < this.tokens.length - 1) {
            return this.tokens[this._currentTokenIndex + 1].type;
        }
        else {
            return null;
        }
    }

    constructor(readonly tokens: Token[]) {
    }

    private parseFunctionParameters(functionCall: FunctionCallNode) {
        let moreParameters = false;
        let startTokenType = TokenType.OpenParenthese;

        do {
            functionCall.parameters.push(this.parseExpression(startTokenType, [TokenType.CloseParenthese, TokenType.Comma]));

            moreParameters = this.currentToken.type == TokenType.Comma;

            if (moreParameters) {
                startTokenType = TokenType.Comma;
            }
        } while (moreParameters);
    }

    private parsePropertyPathOrFunctionCall(): PropertyPathNode | FunctionCallNode {
        let result = new PropertyPathNode();

        let expectedTokenTypes: Array<TokenType> = [TokenType.Identifier];
        let canEndPath = false;
        let canBeFunctionCall = true;

        while (!this.eof) {
            this.ensureTokenType(expectedTokenTypes);

            switch (this.currentToken.type) {
                case TokenType.Identifier:
                    result.properties.push(this.currentToken.value);

                    expectedTokenTypes = [TokenType.Period, TokenType.OpenSquareBracket];

                    if (canBeFunctionCall) {
                        expectedTokenTypes.push(TokenType.OpenParenthese);
                    }

                    canEndPath = true;

                    break;
                case TokenType.Period:
                    expectedTokenTypes = [TokenType.Identifier];

                    canEndPath = false;

                    break;
                case TokenType.OpenSquareBracket:
                    result.properties.push(this.parseExpression(TokenType.OpenSquareBracket, [TokenType.CloseSquareBracket]));

                    expectedTokenTypes = [TokenType.Period];

                    canEndPath = true;
                    canBeFunctionCall = false;

                    break;
                case TokenType.OpenParenthese:
                    let functionCall = new FunctionCallNode();
                    functionCall.functionName = result.properties.join(".");

                    this.parseFunctionParameters(functionCall);
            
                    return functionCall;
                default:
                    this.unexpectedTokenType();
            }

            if (!this.isNextTokenType(expectedTokenTypes) && canEndPath) {
                return result;
            }

            this.moveToNextToken();
        }

        this.unexpectedTokenType();
    }

    private parseExpression(startTokenType: TokenType, endTokenTypes: TokenType[]): Expression {
        let result: Expression = new Expression();

        this.ensureTokenType([startTokenType]);
        this.moveToNextToken();

        let expectedNextTokenTypes: Array<TokenType> = literalTokenTypes.concat([ TokenType.PlusSign, TokenType.MinusSign ]).concat([TokenType.OpenParenthese]);
        let hasArithmeticOperator = false;
        let hasComparisonOperator = false;
        let allowedLiteralType: LiteralTokenType = null;

        while (!this.eof) {
            this.ensureTokenType(expectedNextTokenTypes);

            switch (this.currentToken.type) {
                case TokenType.OpenParenthese:
                    result.nodes.push(this.parseExpression(TokenType.OpenParenthese, [TokenType.CloseParenthese]));

                    expectedNextTokenTypes = operatorTokenTypes.concat(endTokenTypes);

                    break;
                case TokenType.CloseSquareBracket:
                case TokenType.CloseParenthese:
                case TokenType.CloseCurlyBracket:
                case TokenType.Comma:
                    if (result.nodes.length == 0) {
                        this.unexpectedTokenType();
                    }

                    this.ensureTokenType(endTokenTypes);

                    return result;
                case TokenType.Identifier:
                    result.nodes.push(this.parsePropertyPathOrFunctionCall());

                    expectedNextTokenTypes = operatorTokenTypes.concat(endTokenTypes);

                    break;
                case TokenType.StringLiteral:
                case TokenType.NumberLitteral:
                case TokenType.BooleanLiteral:
                    if (allowedLiteralType && allowedLiteralType != this.currentToken.type) {
                        this.unexpectedTokenType();
                    }

                    if (this.currentToken.type == TokenType.StringLiteral) {
                        result.nodes.push(new LiteralNode(this.currentToken.value));
                    }
                    else if (this.currentToken.type == TokenType.NumberLitteral) {
                        result.nodes.push(new LiteralNode(parseFloat(this.currentToken.value)));
                    }
                    else {
                        result.nodes.push(new LiteralNode(this.currentToken.value === "true"));
                    }

                    expectedNextTokenTypes = operatorTokenTypes.concat(endTokenTypes);
                    allowedLiteralType = this.currentToken.type;

                    break;
                case TokenType.PlusSign:
                case TokenType.MinusSign:
                    if (result.nodes.length == 0) {
                        if (this.currentToken.type == TokenType.MinusSign) {
                            result.nodes.push(new LiteralNode(-1));
                            result.nodes.push(new OperatorNode(TokenType.MultiplySign));
                        }
                    }
                    else {
                        if (hasComparisonOperator) {
                            this.unexpectedTokenType();
                        }
    
                        result.nodes.push(new OperatorNode(this.currentToken.type));

                        expectedNextTokenTypes = literalTokenTypes.concat([TokenType.OpenParenthese]);

                        hasArithmeticOperator = true;
                    }

                    break;
                case TokenType.MultiplySign:
                case TokenType.DivideSign:
                    if (result.nodes.length == 0 || hasComparisonOperator) {
                        this.unexpectedTokenType();
                    }

                    result.nodes.push(new OperatorNode(this.currentToken.type));

                    expectedNextTokenTypes = literalTokenTypes.concat([TokenType.OpenParenthese]);

                    hasArithmeticOperator = true;

                    break;
                case TokenType.EqualOperator:
                case TokenType.NotEqualOperator:
                case TokenType.LessThanOperator:
                case TokenType.LessThanOrEqualOperator:
                case TokenType.GreaterThanOperator:
                case TokenType.GreaterThanOrEqualOperator:
                    if (result.nodes.length == 0 || hasArithmeticOperator) {
                        this.unexpectedTokenType();
                    }

                    result.nodes.push(new OperatorNode(this.currentToken.type));

                    expectedNextTokenTypes = literalTokenTypes.concat([TokenType.OpenParenthese]);

                    hasComparisonOperator = true;

                    break;
                default:
                    this.unexpectedTokenType();
            }

            this.moveToNextToken();
        }

        this.unexpectedEndOfExpression();
    }

    reset() {
        this._currentTokenIndex = 0;
    }

    parse(): Expression {
        this.reset();

        return this.parseExpression(TokenType.OpenCurlyBracket, [TokenType.CloseCurlyBracket]);
    }
}