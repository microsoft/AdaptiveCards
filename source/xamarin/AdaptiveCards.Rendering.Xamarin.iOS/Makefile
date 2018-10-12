BTOUCH=/Developer/MonoTouch/usr/bin/btouch
SMCS=/Developer/MonoTouch/usr/bin/smcs
MONOXBUILD=/Library/Frameworks/Mono.framework/Commands/msbuild

all: AdaptiveCards.dll

AdaptiveCards.framework: clean
	$(MAKE) -C ../../ios

AdaptiveCards.dll: ApiDefinition.cs Structs.cs Makefile AdaptiveCards.framework ../../ios/AdaptiveCards/AdaptiveCards/AdaptiveCards.framework 
	$(MONOXBUILD) /p:Configuration=Release AdaptiveCards.Rendering.Xamarin.iOS.csproj

clean:
	-rm -rf list *.a *.dll *.mdb *.sln bin/ obj/
