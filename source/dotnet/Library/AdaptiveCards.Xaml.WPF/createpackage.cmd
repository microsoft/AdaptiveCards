erase *.nupkg
NuGet.exe pack AdaptiveCards.Xaml.WPF.csproj -Prop Configuration=Debug -Build
copy *.nupkg ..\bin
