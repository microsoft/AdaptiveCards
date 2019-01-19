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
    StringLiteral,
    NumberLitteral
}

type OperatorTokenKind = TokenType.PlusSign | TokenType.MinusSign;

interface TokenTypeInfo {
    friendlyName: string;
    matchingEndToken?: TokenType;
}

interface TokenizerRule {
    regEx: RegExp;
    tokenType: TokenType;
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
            { tokenType: TokenType.WhiteSpace, regEx: /^\s/ },
            { tokenType: TokenType.OpenCurlyBracket, regEx: /^{/ },
            { tokenType: TokenType.CloseCurlyBracket, regEx: /^}/ },
            { tokenType: TokenType.OpenSquareBracket, regEx: /^\[/ },
            { tokenType: TokenType.CloseSquareBracket, regEx: /^\]/ },
            { tokenType: TokenType.OpenParenthese, regEx: /^\(/ },
            { tokenType: TokenType.CloseParenthese, regEx: /^\)/ },
            { tokenType: TokenType.Identifier, regEx: /^[a-z_]+/i },
            { tokenType: TokenType.Period, regEx: /^\./ },
            { tokenType: TokenType.Comma, regEx: /^,/ },
            { tokenType: TokenType.PlusSign, regEx: /^\+/ },
            { tokenType: TokenType.MinusSign, regEx: /^-/ },
            { tokenType: TokenType.StringLiteral, regEx: /^(?:".*")|^(?:'.*')/ },
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

                    this._tokens.push(
                        {
                            type: rule.tokenType,
                            value: matches[0],
                            originalPosition: i
                        }
                    )

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

        return result;
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

class StringLiteralNode extends ExpressionNode {
    constructor(readonly value: string) {
        super();
    }

    print(): string {
        return this.value;
    }
}

class NumberLiteralNode extends ExpressionNode {
    constructor(readonly value: number) {
        super();
    }

    print(): string {
        return this.value.toString();
    }
}

class OperatorNode extends ExpressionNode {
    constructor(readonly operator: OperatorTokenKind) {
        super();
    }

    print(): string {
        return TokenType[this.operator];
    }
}

class ExpressionParser {
    private _currentTokenIndex: number = 0;

    private unexpectedTokenType() {
        throw new Error("Unexpected token \"" + this.current.value + "\" at position " + this.current.originalPosition + ".");
    }

    private unexpectedEndOfExpression() {
        throw new Error("Unexpected end of expression.");
    }

    private ensureTokenType(expectedTokenTypes: TokenType[]) {
        if (this.eof) {
            this.unexpectedEndOfExpression();
        }
        else if (expectedTokenTypes.indexOf(this.current.type) < 0) {
            this.unexpectedTokenType();
        }
    }

    private moveNext() {
        this._currentTokenIndex++;
    }

    private moveNextAndEnsureTokenType(expectedTokenTypes: TokenType[]) {
        this._currentTokenIndex++;

        this.ensureTokenType(expectedTokenTypes);
    }

    private skipWhitespace() {
        while (!this.eof && this.current.type == TokenType.WhiteSpace) {
            this.moveNext();
        }
    }

    private get eof(): boolean {
        return this._currentTokenIndex >= this.tokens.length;
    }

    private get current(): Token {
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

    private parsePropertyPath(): PropertyPathNode {
        let result = new PropertyPathNode();

        this.ensureTokenType([TokenType.Identifier]);

        while (!this.eof) {
            switch (this.current.type) {
                case TokenType.Identifier:
                    result.properties.push(this.current.value);

                    if (this.nextTokenType != TokenType.Period) {
                        return;
                    }

                    break;
                case TokenType.Period:
                    break;
                case TokenType.OpenSquareBracket:
                    result.properties.push(this.parseExpression(TokenType.OpenSquareBracket, [TokenType.CloseSquareBracket]));

                    break;
                default:
                    this.unexpectedTokenType();
            }

            this.moveNext();
        }

        return result;
    }

    /*
    private ensureHasMatchingEndToken(startTokenType: TokenType, endTokenType: TokenType) {
        this.ensureTokenType(startTokenType);

        let startTokenCount = 0;

        for (let i = this._currentTokenIndex; i < this.tokens.length; i++) {
            if (this.tokens[i].type == startTokenType) {
                startTokenCount++;
            }

            if (this.tokens[i].type == startTokenType) {
                startTokenCount--;

                if (startTokenCount == 0) {
                    return true;
                }
            }
        }

        return false;
    }
    */

    private parseFunctionCall(): FunctionCallNode {
        let result = new FunctionCallNode();

        this.ensureTokenType([TokenType.Identifier]);

        result.functionName = this.current.value;

        this.moveNextAndEnsureTokenType([TokenType.OpenParenthese]);

        let moreParameters = false;
        let startTokenType = TokenType.OpenParenthese;

        do {
            result.parameters.push(this.parseExpression(startTokenType, [TokenType.CloseParenthese, TokenType.Comma]));

            moreParameters = this.current.type == TokenType.Comma;

            if (moreParameters) {
                startTokenType = TokenType.Comma;
            }
        } while (moreParameters);

        return result;
    }

    private isOperator(tokenType: TokenType): boolean {
        const operators: Array<TokenType> = [ TokenType.PlusSign, TokenType.MinusSign ];

        return operators.indexOf(tokenType) >= 0;
    }

    private parseExpression(startTokenType: TokenType, endTokenTypes: TokenType[]): Expression {
        let result: Expression = new Expression();

        this.skipWhitespace();
        this.ensureTokenType([startTokenType]);
        this.moveNext();
        this.skipWhitespace();

        while (!this.eof) {
            switch (this.current.type) {
                case TokenType.Identifier:
                    result.nodes.push(this.nextTokenType == TokenType.OpenParenthese ? this.parseFunctionCall() : this.parsePropertyPath());

                    this.moveNext();
                    this.skipWhitespace();
                    this.ensureTokenType(endTokenTypes);

                    return result;
                case TokenType.StringLiteral:
                    result.nodes.push(new StringLiteralNode(this.current.value));

                    this.moveNext();
                    this.skipWhitespace();
                    this.ensureTokenType(endTokenTypes);

                    return result;
                case TokenType.NumberLitteral:
                    result.nodes.push(new NumberLiteralNode(parseFloat(this.current.value)));

                    this.moveNext();
                    this.skipWhitespace();

                    if (this.isOperator(this.current.type)) {
                        result.nodes.push(new OperatorNode(<OperatorTokenKind>this.current.type));

                        this.moveNext();
                        this.skipWhitespace();

                        break;
                    }
                    else {
                        this.ensureTokenType(endTokenTypes);

                        return result;
                    }
                case TokenType.PlusSign:
                case TokenType.MinusSign:
                    if (result.nodes.length == 0) {
                        if (this.nextTokenType != TokenType.NumberLitteral) {
                            this.unexpectedTokenType();
                        }

                        let isNegative = this.current.type == TokenType.MinusSign;

                        this.moveNext();

                        result.nodes.push(new NumberLiteralNode((isNegative ? -1 : 1) * parseFloat(this.current.value)));

                        this.moveNext();
                        this.skipWhitespace();
                        this.ensureTokenType(endTokenTypes);
    
                        return result;
                    }
                    else {
                        // TODO - Operators within expressions
                        this.unexpectedTokenType();
                    }
                default:
                    this.unexpectedTokenType();
            }
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