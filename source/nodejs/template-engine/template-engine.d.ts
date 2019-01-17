declare enum TokenType {
    expressionStart = 0,
    expressionEnd = 1,
    indexerStart = 2,
    indexerEnd = 3,
    identifier = 4,
    openParenthese = 5,
    closeParenthese = 6,
    stringLiteral = 7,
    numberLitteral = 8
}
interface TokenizerRule {
    regEx: RegExp;
    tokenType: TokenType;
}
interface Token {
    type: TokenType;
    value: string;
}
declare class Tokenizer {
    static rules: Array<TokenizerRule>;
    static initialize(): void;
    private _tokens;
    protected internalParse(expression: string): void;
    parse(expression: string): void;
    readonly tokens: Array<Token>;
}
