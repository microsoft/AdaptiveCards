// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
// Modifed json parser grammar from "The Definitive ANTLR 4 Reference" by Terence Parr
// Derived from http://json.org

parser grammar AdaptiveCardsTemplateParser;
options { tokenVocab=AdaptiveCardsTemplateLexer; }

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
   : StringDeclOpen templateString (templateString)* CLOSE # valueTemplateString
   | StringDeclOpen templateRoot  CLOSE # valueTemplateStringWithRoot
   | StringDeclOpen STRING* CLOSE # valueString
   | NUMBER # valueNumber
   | obj    # valueObject
   | array  # valueArray
   | TRUE # valueTrue
   | FALSE # valueFalse
   | NULL  # valueNull
   ;

templateString
   : (STRING? TEMPLATELITERAL STRING?) # templatedString
   ;

templateRoot
   :  TEMPLATEROOT # templateStringWithRoot
   ;

templateExpression
   : StringDeclOpen TEMPLATELITERAL CLOSE # valueTemplateExpression
   ;
