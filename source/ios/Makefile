all: AdaptiveCards.framework

AdaptiveCards.framework: clean
	xcodebuild -workspace AdaptiveCards/AdaptiveCards.xcworkspace -scheme AdaptiveCards-Universal
	unzip AdaptiveCards/AdaptiveCards/AdaptiveCards.framework.zip -d AdaptiveCards/AdaptiveCards

clean:
	-rm -rf list *.framework *.zip
