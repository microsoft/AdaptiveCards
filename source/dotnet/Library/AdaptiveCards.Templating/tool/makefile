sources = $(wildcard *.java)
classes = $(wildcard *.class)
JAR=/usr/local/lib/antlr-4.8-complete.jar
JAVA=/usr/bin/java
LEXER=../AdaptiveCardsTemplateLexer.g4
PARSER=../AdaptiveCardsTemplateParser.g4

all: classes

lexer: $(LEXER)  
	@cp $(LEXER) .
	$(JAVA) -jar $(JAR) AdaptiveCardsTemplateLexer.g4 -Werror

parser: $(PARSER) 
	@cp $(PARSER) .
	$(JAVA) -jar $(JAR) AdaptiveCardsTemplateParser.g4 -no-listener -Werror

classes: lexer parser
	javac AdaptiveCardsTemplate*.java

clean:
	@rm -rf *.java *.tokens *.interp *.class  *.g4

all: $(classes)
