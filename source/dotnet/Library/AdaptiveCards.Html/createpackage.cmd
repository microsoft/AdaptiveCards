erase /s *.nupkg
NuGet.exe pack AdaptiveCards.Rendering.Html.csproj -Prop Configuration=Debug -Build
copy *.nupkg ..\bin
