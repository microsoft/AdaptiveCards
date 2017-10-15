erase /s *.nupkg
NuGet.exe pack AdaptiveCards.Xaml.WPF.RichInput.csproj -Prop Configuration=Debug -Build
copy *.nupkg ..\bin