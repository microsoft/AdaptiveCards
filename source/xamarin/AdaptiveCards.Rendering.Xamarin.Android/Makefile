BTOUCH=/Developer/MonoTouch/usr/bin/btouch
SMCS=/Developer/MonoTouch/usr/bin/smcs
MONOXBUILD=/Library/Frameworks/Mono.framework/Commands/msbuild

all: AdaptiveCards.dll

AdaptiveCards.aar: clean
	$(MAKE) -C ../../android

AdaptiveCards.dll: Makefile AdaptiveCards.aar 
	$(MONOXBUILD) /p:Configuration=Release AdaptiveCards.Rendering.Xamarin.Android.csproj

clean:
	-rm -rf list *.a *.dll *.mdb *.sln bin/ obj/ *.aar
