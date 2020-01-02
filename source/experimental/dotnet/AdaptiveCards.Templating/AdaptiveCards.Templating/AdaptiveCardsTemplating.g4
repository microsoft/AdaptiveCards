// Define a grammar for AdaptiveCards Templating
grammar AdaptiveCardsTemplating;
prog: r;
r :prop+;
prop : prop('[') NUM (']')
    | prop('.') prop
    | ID
    ;

ID : [a-z]+ ;             // match lower-case identifiers
NUM : [0-9]+;
WS : [ \t\r\n]+ -> skip ; // skip spaces, tabs, newlines
