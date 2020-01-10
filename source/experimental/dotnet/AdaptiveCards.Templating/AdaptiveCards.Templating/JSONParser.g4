/** Taken from "The Definitive ANTLR 4 Reference" by Terence Parr */

// Derived from http://json.org
parser grammar JSONParser;
options { tokenVocab=JSONLexer; }

json
   : value
   ;

obj
   : LCB pair (COMMA pair)* RCB
   | LCB RCB
   ;

pair
   : StringDeclOpen STRING CLOSE COLON value    # jsonPair
   | StringDeclOpen TEMPLKEYWRD CLOSE COLON value # templateData
   ;

array
   : LSB value (COMMA value)* RSB
   | LSB RSB
   ;

value
   : StringDeclOpen STRING CLOSE # valueString
   | StringDeclOpen templateString CLOSE # valueTemplateString
   | NUMBER # valueNumber
   | obj    # valueObject
   | array  # valueArray
   | TRUE # valueTrue
   | FALSE # valueFalse
   | NULL  # valueNull
   ;

templateString
   : (STRING? TemplateOpen TEMPLATELITERAL TEMPLATECLOSE STRING?)+ 
   ;
