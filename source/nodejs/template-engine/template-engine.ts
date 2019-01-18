type TokenType = 
    "whiteSpace" |
    "expressionStart" |
    "expressionEnd" |
    "indexerStart" |
    "indexerEnd" |
    "identifier" |
    "openParenthese" |
    "closeParenthese" |
    "propertyPathSeparator" |
    "stringLiteral" |
    "numberLitteral";

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
            {
                regEx: /^\s/,
                tokenType: "whiteSpace"
            },
            {
                regEx: /^{/,
                tokenType: "expressionStart"
            },
            {
                regEx: /^}/,
                tokenType: "expressionEnd"
            },
            {
                regEx: /^\[/,
                tokenType: "indexerStart"
            },
            {
                regEx: /^\]/,
                tokenType: "indexerEnd"
            },
            {
                regEx: /^\(/,
                tokenType: "openParenthese"
            },
            {
                regEx: /^\)/,
                tokenType: "closeParenthese"
            },
            {
                regEx: /^[a-z_]+/i,
                tokenType: "identifier"
            },
            {
                regEx: /^\./,
                tokenType: "propertyPathSeparator"
            },
            {
                regEx: /^(?:".*")|^(?:'.*')/,
                tokenType: "stringLiteral"
            },
            {
                regEx: /^\d*\.?\d+/,
                tokenType: "numberLitteral"
            }
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

/*
interface NextTokenDefinition {
    type: TokenType;
    canEndExpression: boolean;
}

class NextTokenDefinitions {
    definitions: NextTokenDefinition[];

    getDefinition(tokenType: TokenType): NextTokenDefinition {
        if (this.definitions) {
            for (let definition of this.definitions) {
                if ()
            }
        }

        return null;
    }
}
*/

type ExpectedNextTokens = { [token in TokenType]?: boolean };

abstract class ExpressionNode {

}

class PropertyPathNode extends ExpressionNode {
    properties: Array<string> = [];
}

class FunctionCallNode extends ExpressionNode {
    functionName: string;
}

class Expression {
    private _currentTokenIndex: number = 0;
    private _parts: ExpressionNode[] = null;

    private moveNext() {
        this._currentTokenIndex++;
    }

    private skipWhitespace() {
        while (!this.eof && this.current.type == "whiteSpace") {
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

    private ensureTokenType(tokenType: TokenType) {
        if (this.eof) {
            throw new Error("Unexpected end of expression. A token of type \"" + tokenType + "\" was expected.");
        }
        else if (this.current.type != tokenType) {
            throw new Error("Unexpected token of type \"" + this.current.type + "\" at position " + this.current.originalPosition + "(" + this.current.value + "). A token of type \"" + tokenType + "\" was expected.");
        }
    }

    constructor(readonly tokens: Token[]) {
    }

    reset() {
        this._currentTokenIndex = 0;
        this._parts = [];
    }

    private parsePropertyPath(): PropertyPathNode {
        let result = new PropertyPathNode();

        this.ensureTokenType("identifier");

        while (!this.eof) {
            switch (this.current.type) {
                case "identifier":
                    result.properties.push(this.current.value);
                    break;
                case "propertyPathSeparator":
                    break;
                case "indexerStart":
                    break;
                default:
                    return result;
            }

            this.moveNext();
        }

        return result;
    }

    private findMatchingEndTokenIndex(startTokenType: TokenType, endTokenType: TokenType) {
        this.ensureTokenType(startTokenType);

        let startTokenCount = 0;

        for (let i = this._currentTokenIndex; i < this.tokens.length; i++) {
            if (this.tokens[i].type == startTokenType) {
                startTokenCount++;
            }

            if (this.tokens[i].type == startTokenType) {
                startTokenCount--;

                if (startTokenCount == 0) {
                    return i;
                }
            }
        }

        return -1;
    }

    private parseFunctionCall(): FunctionCallNode {
        let result = new FunctionCallNode();

        this.ensureTokenType("identifier");

        result.functionName = this.current.value;

        this.moveNext();

        this.ensureTokenType("openParenthese");

        let index = this.findMatchingEndTokenIndex("openParenthese", "closeParenthese");

        if (index == -1) {
            throw new Error("Syntax error: missing )");
        }

        

        return result;
    }

    parse() {
        this.reset();

        /*
        let expectedNextTokens: NextTokenDefinition[] = [
            { type: "whiteSpace", canEndExpression: false },
            { type: "identifier", canEndExpression: true },
            { type: "numberLitteral", canEndExpression: true },
            { type: "stringLiteral", canEndExpression: true },
            { type: "expressionStart", canEndExpression: false },
            { type: "openParenthese", canEndExpression: false }
        ];
        */

        let expectedNextTokens: ExpectedNextTokens = {
            "whiteSpace": false,
            "identifier": true,
            "numberLitteral": true,
            "stringLiteral": true,
            "expressionStart": false,
            "openParenthese": false
        };

        while (!this.eof) {
            let currentToken = this.current;

            if (typeof expectedNextTokens[currentToken.type] !== "boolean") {
                throw new Error("Found unexpected token of type " + currentToken.type + " at position " + currentToken.originalPosition);
            }

            if (this.eof && !expectedNextTokens[currentToken.type]) {
                throw new Error("Unexpected end of expression.");
            }

            switch (currentToken.type) {
                /*
                case "expressionStart":
                case "expressionEnd":
                    this.moveNext();

                    break;
                case "indexerStart":
                case "indexerEnd":
                */
                case "identifier":
                    let node: ExpressionNode = null;

                    if (this.nextTokenType == "openParenthese") {
                        node = this.parseFunctionCall();
                    }
                    else {
                        node = this.parsePropertyPath();
                    }

                    expectedNextTokens = {
                        "whiteSpace": true,
                    };

                    break;
                /*
                case "propertyPathSeparator":
                    expectedNextTokens = {
                        "identifier": true
                    };

                    this.moveNext();

                    break;
                case "openParenthese":
                case "closeParenthese":
                */
                case "stringLiteral":
                case "numberLitteral":
                    expectedNextTokens = {
                        "whiteSpace": true
                    };

                    this.moveNext();
                    
                    break;
                case "whiteSpace":
                default:
                    this.moveNext();
                        
                    break
            }

            if (currentToken.type != "identifier" && currentToken.type != "propertyPathSeparator") {
                if (propertyPath) {
                    console.log("Found property path: " + propertyPath.join("."));
                }

                propertyPath = null;
            }
        }

        if (propertyPath) {
            console.log("Found property path: " + propertyPath.join("."));
        }
    }
}
