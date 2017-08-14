@echo off

echo Welcome, let's create a new NuGet package for AdaptiveCards.UWP.Beta!
echo.

set /p version="Enter Version Number (ex. 1.0.0): "

if not exist "NugetPackages" mkdir "NugetPackages"

"C:\Program Files (x86)\NuGet\nuget.exe" pack AdaptiveCards.UWP.Beta.nuspec -Version %version% -OutputDirectory "NugetPackages"

PAUSE

explorer NugetPackages




exit
:file_not_found

echo File not found: %1
PAUSE
exit