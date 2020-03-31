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
   : StringDeclOpen STRING* CLOSE COLON value    # jsonPair
   | StringDeclOpen TEMPLATEDATA CLOSE COLON StringDeclOpen templateRoot CLOSE # templateRootData
   | StringDeclOpen TEMPLATEDATA CLOSE COLON value # templateData
   | StringDeclOpen TEMPLATEWHEN CLOSE COLON templateExpression # templateWhen
   ;

array
   : LSB value (COMMA value)* RSB
   | LSB RSB
   ;

value
   : StringDeclOpen templateRoot  CLOSE # valueTemplateStringWithRoot
   | StringDeclOpen templateString CLOSE # valueTemplateString
   | StringDeclOpen STRING* CLOSE # valueString
   | NUMBER # valueNumber
   | obj    # valueObject
   | array  # valueArray
   | TRUE # valueTrue
   | FALSE # valueFalse
   | NULL  # valueNull
   ;

templateRoot
   :  TEMPLATEROOT # templateStringWithRoot
   ;


templateString
   : (STRING? TEMPLATELITERAL STRING?)+ # templatedString
   ;

templateExpression
   : StringDeclOpen TEMPLATELITERAL CLOSE # valueTemplateExpression
   ;

