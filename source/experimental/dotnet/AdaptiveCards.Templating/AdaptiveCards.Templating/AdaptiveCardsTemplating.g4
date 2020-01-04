// Define a grammar for AdaptiveCards Templating
grammar AdaptiveCardsTemplating;
prog: template;
template : '{' prop ('.' prop)* '}'
    | '{' '}'
    ;
prop : ID'[' NUM ']' # propArray
    | ID # propID
    ;

ID : [a-zA-Z]+ ;             // match lower-case identifiers
NUM : [0-9]+;
WS : [ \t\r\n]+ -> skip ; // skip spaces, tabs, newlines
