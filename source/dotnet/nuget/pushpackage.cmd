@if "%1" == "" goto  :needpackage
@if "%2" == "" goto :needfeed
..\..\..\packages\NuGet.CommandLine.3.5.0\tools\NuGet.exe push -Source %2 -ApiKey VSTS %1
@goto end
nuget.exe push -Source "packages" -ApiKey VSTS my_package.nupkg

:needpackage
@echo "You need to pass a package as first parameter"
@goto end

:needfeed
@echo "You need to pass a feed name, either: fuse or fusesymbols"

:end