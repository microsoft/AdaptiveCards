all: AdaptiveCards.aar

AdaptiveCards.aar: clean
	cd adaptivecards/src && swig -c++ -java -package com.microsoft.adaptivecards.objectmodel -outdir main/java/com/microsoft/adaptivecards/objectmodel -o main/cpp/objectmodel_wrap.cpp AdaptiveCardObjectModel.i
	./gradlew build
clean:
	-rm -rf build/
