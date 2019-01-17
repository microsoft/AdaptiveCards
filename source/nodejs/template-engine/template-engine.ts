enum TokenType {
    expressionStart,
    expressionEnd,
    indexerStart,
    indexerEnd,
    identifier,
    openParenthese,
    closeParenthese,
    stringLiteral,
    numberLitteral
}

interface TokenizerRule {
    regEx: RegExp;
    tokenType: TokenType;
}

interface Token {
    type: TokenType;
    value: string;
}

class Tokenizer {
    static rules: Array<TokenizerRule> = [];

    static initialize() {
        Tokenizer.rules.push(
            {
                regEx: /^{/g,
                tokenType: TokenType.expressionStart
            },
            {
                regEx: /^}/g,
                tokenType: TokenType.expressionEnd
            },
            {
                regEx: /^\[/g,
                tokenType: TokenType.indexerStart
            },
            {
                regEx: /^\]/g,
                tokenType: TokenType.indexerEnd
            },
            {
                regEx: /^\(/g,
                tokenType: TokenType.openParenthese
            },
            {
                regEx: /^\)/g,
                tokenType: TokenType.closeParenthese
            },
            {
                regEx: /^[a-z_]+(?:(?:\w*)\.*)+/ig,
                tokenType: TokenType.identifier
            },
            {
                regEx: /^(?:".*")|^(?:'.*')/g,
                tokenType: TokenType.stringLiteral
            },
            {
                regEx: /^\d*\.?\d+/g,
                tokenType: TokenType.numberLitteral
            }
        )
    }

    private _tokens: Array<Token>;

    protected internalParse(expression: string) {
        let i = 0;

        while (i < expression.length) {
            let subExpression = expression.substr(i);
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
                            value: subExpression.substr(0, matches[0].length)
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
