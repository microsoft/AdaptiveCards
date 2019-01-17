var TokenType;
(function (TokenType) {
    TokenType[TokenType["expressionStart"] = 0] = "expressionStart";
    TokenType[TokenType["expressionEnd"] = 1] = "expressionEnd";
    TokenType[TokenType["indexerStart"] = 2] = "indexerStart";
    TokenType[TokenType["indexerEnd"] = 3] = "indexerEnd";
    TokenType[TokenType["identifier"] = 4] = "identifier";
    TokenType[TokenType["openParenthese"] = 5] = "openParenthese";
    TokenType[TokenType["closeParenthese"] = 6] = "closeParenthese";
    TokenType[TokenType["stringLiteral"] = 7] = "stringLiteral";
    TokenType[TokenType["numberLitteral"] = 8] = "numberLitteral";
})(TokenType || (TokenType = {}));
var Tokenizer = /** @class */ (function () {
    function Tokenizer() {
    }
    Tokenizer.initialize = function () {
        Tokenizer.rules.push({
            regEx: /^{/g,
            tokenType: TokenType.expressionStart
        }, {
            regEx: /^}/g,
            tokenType: TokenType.expressionEnd
        }, {
            regEx: /^\[/g,
            tokenType: TokenType.indexerStart
        }, {
            regEx: /^\]/g,
            tokenType: TokenType.indexerEnd
        }, {
            regEx: /^\(/g,
            tokenType: TokenType.openParenthese
        }, {
            regEx: /^\)/g,
            tokenType: TokenType.closeParenthese
        }, {
            regEx: /^[a-z_]+(?:(?:\w*)\.*)+/ig,
            tokenType: TokenType.identifier
        }, {
            regEx: /^(?:".*")|^(?:'.*')/g,
            tokenType: TokenType.stringLiteral
        }, {
            regEx: /^\d*\.?\d+/g,
            tokenType: TokenType.numberLitteral
        });
    };
    Tokenizer.prototype.internalParse = function (expression) {
        var i = 0;
        while (i < expression.length) {
            var subExpression = expression.substr(i);
            var matchFound = false;
            for (var _i = 0, _a = Tokenizer.rules; _i < _a.length; _i++) {
                var rule = _a[_i];
                var matches = rule.regEx.exec(subExpression);
                if (matches) {
                    if (matches.length > 1) {
                        throw new Error("A tokenizer rule found more than 1 match.");
                    }
                    this._tokens.push({
                        type: rule.tokenType,
                        value: subExpression.substr(0, matches[0].length)
                    });
                    i += matches[0].length;
                    matchFound = true;
                    break;
                }
            }
            if (!matchFound) {
                i++;
            }
        }
    };
    Tokenizer.prototype.parse = function (expression) {
        this._tokens = [];
        this.internalParse(expression);
    };
    Object.defineProperty(Tokenizer.prototype, "tokens", {
        get: function () {
            return this._tokens;
        },
        enumerable: true,
        configurable: true
    });
    Tokenizer.rules = [];
    return Tokenizer;
}());
Tokenizer.initialize();
//# sourceMappingURL=template-engine.js.map