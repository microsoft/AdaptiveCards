// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
// Modified json lexer rules from "The Definitive ANTLR 4 Reference" by Terence Parr
// Derived from http://json.org

lexer grammar AdaptiveCardsTemplateLexer;

tokens { TEMPLATELITERAL }

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

// no leading zeros
fragment INT
   : '0' | [1-9] [0-9]*
   ;

fragment EXP
   : [Ee] [+\-]? INT
   ;

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

TemplateStart
   : '${' -> pushMode(TemplateString), more
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

mode TemplateString;

TRCB 
   : RCB  -> popMode, type(TEMPLATELITERAL)
   ;
   
TEXT : (SINGLE | DOUBLE | TSTM | . ) -> more 
   ;
  
SINGLE : '\'' .*? '\''
   ;
   
DOUBLE : '\\"' .*? '\\"'
   ;

TSTM
   : LCB (TSTM | . )*? RCB;
