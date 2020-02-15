sources = $(wildcard *.java)
classes = $(wildcard *.class)
JAR=/usr/local/lib/antlr-4.7.1-complete.jar
JAVA=/usr/bin/java

all: classes

lexer: JSONLexer.g4 
	$(JAVA) -jar $(JAR) JSONLexer.g4
	#antlr4 JSONLexer.g4 
parser: JSONParser.g4 
	$(JAVA) -jar $(JAR) JSONParser.g4

classes: lexer parser
	javac JSON*.java

clean:
	rm -rf *.java *.tokens *.interp *.class

all: $(classes)
