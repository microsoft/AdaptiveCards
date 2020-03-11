sources = $(wildcard *.java)
classes = $(wildcard *.class)
JAR=/usr/local/lib/antlr-4.7.1-complete.jar
JAVA=/usr/bin/java
LEXER=../AdaptiveCards.Templating/JSONLexer.g4
PARSER=../AdaptiveCards.Templating/JSONParser.g4  

all: classes

lexer: $(LEXER)  
	cp $(LEXER) .
	$(JAVA) -jar $(JAR) JSONLexer.g4

parser: $(PARSER) 
	cp $(PARSER) .
	$(JAVA) -jar $(JAR) JSONParser.g4

classes: lexer parser
	javac JSON*.java

clean:
	rm -rf *.java *.tokens *.interp *.class  *.g4

all: $(classes)
