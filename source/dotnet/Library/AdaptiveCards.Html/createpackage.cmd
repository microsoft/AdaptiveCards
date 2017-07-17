erase bin\debug\*.nupkg
erase bin\release\*.nupkg
msbuild /t:rebuild /t:pack /p:Configuration=Debug
copy bin\debug\*.nupkg ..\bin
