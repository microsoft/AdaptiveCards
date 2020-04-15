lexer grammar AdaptiveCardsTemplateLexer;

COMMA : ',';

COLON : ':';

LCB : '{';

RCB : '}';

LSB : '[';

RSB : ']';

TRUE : 'true';

FALSE : 'false';

NULL : 'null';

StringDeclOpen 
   : '"'  -> pushMode(INSIDE);

NUMBER
   : '-'? INT ('.' [0-9] +)? EXP?
   ;

fragment INT
   : '0' | [1-9] [0-9]*
   ;

// no leading zeros

fragment EXP
   : [Ee] [+\-]? INT
   ;

// \- since - means "range" inside [...]

WS
   : [ \t\n\r] + -> skip
   ;

mode INSIDE;

CLOSE 
   : '"' -> popMode
   ;

TEMPLATEDATA
   : '$data'
   ;

TEMPLATEWHEN
   : '$when'
   ;

JPATH
   : ('.' STRING | '[' INT ']')+ '}'
   ;

TEMPLATELITERAL
   : '${' ~ ["]*? '}'
   ;

TEMPLATEROOT
   : '${$root' JPATH
   ;

STRING
   : (ESC | SAFECODEPOINT)+
   | '$'
   ;

fragment ESC
   : '\\' (["\\/bfnrt] | UNICODE)
   ;
fragment UNICODE
   : 'u' HEX HEX HEX HEX
   ;
fragment HEX
   : [0-9a-fA-F]
   ;
fragment SAFECODEPOINT
   : ~ ["\\\u0000-\u001F$]
   ;
