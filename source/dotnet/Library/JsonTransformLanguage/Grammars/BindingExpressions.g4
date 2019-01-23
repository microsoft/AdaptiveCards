grammar BindingExpressions;

/*
 * Parser Rules
 */

bindingExpression: '{' expression '}';

// Modified from C#'s grammar: https://raw.githubusercontent.com/antlr/grammars-v4/master/csharp/CSharpParser.g4
// Modified from C's grammar: https://raw.githubusercontent.com/antlr/grammars-v4/master/c/C.g4

expression: non_assignment_expression;
non_assignment_expression: conditional_expression;

conditional_expression
	: null_coalescing_expression ('?' expression ':' expression)?
	;

null_coalescing_expression
	: conditional_or_expression ('??' null_coalescing_expression)?
	;

conditional_or_expression
	: conditional_and_expression (OP_OR conditional_and_expression)*
	;

conditional_and_expression
	: inclusive_or_expression (OP_AND inclusive_or_expression)*
	;

inclusive_or_expression
	: exclusive_or_expression ('|' exclusive_or_expression)*
	;

exclusive_or_expression
	: and_expression ('^' and_expression)*
	;

and_expression
	: equality_expression ('&' equality_expression)*
	;

equality_expression
	: relational_expression (BinaryOperator  relational_expression)*
	;

relational_expression
	: additive_expression (('<' | '>' | '<=' | '>=') additive_expression)*
	;

additive_expression
	: multiplicative_expression (AdditiveOperator  multiplicative_expression)*
	;

multiplicative_expression
	: unary_expression (MultiplicativeOperator  unary_expression)*
	;

// https://msdn.microsoft.com/library/6a71f45d(v=vs.110).aspx
// Removed ones that don't make sense, like address locator, ++ operators (they change the value of the item), etc
unary_expression
	: primary_expression
	| '+' unary_expression // Positive sign
	| '-' unary_expression // Make number negative
	| Bang unary_expression // Negate
	| '&' unary_expression
	;

// person[][].name[].first.info[][].last
primary_expression
	: primary_expression_start member_access_or_bracket_expression*
	;

member_access_or_bracket_expression
	: member_access
	| bracket_expression
	;

primary_expression_start
	: literal                                   // Literal expression
	| identifier                                // Simple identifier name expression
	| OpenParens expression CloseParens       // Parenthesis expression
	;

member_access
	: '.' identifier
	;

bracket_expression
	: '[' indexer_argument ']'
	;

indexer_argument
	: expression
	;

generic_dimension_specifier
	: '<' ','* '>'
	;

identifier: Identifier;

literal
	: boolean_literal #boolean
	| string_literal #string
	| DoubleConstant #double
	| DigitSequence #int
	| Null #null
	;

boolean_literal
	: True
	| False
	;

string_literal
	: StringConstant
	;



// I can use definitions like # to define selections of the or operators.




//binaryExpression: (('(' binaryExpression ')') | unaryExpression) BinaryOperator Identifier;
//binaryExpression: (binaryExplicitExpression | binaryAmbiguousExpression) BinaryOperator Identifier;
//binaryExplicitExpression: '(' binaryExpression ')' BinaryOperator Identifier;
//binaryAmbiguousExpression: binaryExpression BinaryOperator Identifier;
//unaryExpression: unaryPropertyAccessorExpression | unaryDictionaryAccessorExpression;

//unaryPropertyAccessorExpression: Identifier '.' Identifier;
//unaryDictionaryAccessorExpression: Identifier '[' Identifier ']';

//identifierWithAccessor: identifierWithDictionaryAccessor | identifierWithPropertyAccessor;
//identifierWithDictionaryAccessor: Identifier dictionaryAccessor;
//identifierWithPropertyAccessor: Identifier propertyAccessor;
//propertyAccessor: '.' Identifier;
//dictionaryAccessor: '[' complexExpression ']';

compileUnit
	:	EOF
	;

/*
 * Lexer Rules
 */

// Note that fragments can NOT be used in the above rules

fragment IdentifierNondigit
	: Letter | '_' | '$' | '@'
	;

fragment Letter: [a-z] | [A-Z] ;
fragment Digit: [0-9] ;

fragment
SCharSequence
    :   SChar+
    ;

fragment
StringEscapeSequence
    :   '\\' [\'nr\\]
    ;

fragment
SChar
    :   ~[\'\\\r\n]
    |   StringEscapeSequence
    |   '\\\n'   // Added line
    |   '\\\r\n' // Added line
    ;

Identifier
	: IdentifierNondigit (IdentifierNondigit | Digit)* ;

BinaryOperator : OP_EQ | OP_NE ;
AdditiveOperator: '+' | '-';
MultiplicativeOperator: '*' | '/' | '%';

WS
	:	' ' -> channel(HIDDEN)
	;

DigitSequence: Digit+;


DoubleConstant
	:	DigitSequence? '.' DigitSequence;


StringConstant
    :   '\'' SCharSequence? '\''
    ;

OpenParens:              '(';
CloseParens:             ')';
Bang:                     '!';
OP_OR:                    '||';
OP_AND:                   '&&';
OP_EQ:                    '==';
OP_NE:                    '!=';

True:          'true';
False:         'false';
Null:          'null';