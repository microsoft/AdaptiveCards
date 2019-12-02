REM @echo off
REM This script copies the dll and winmd files to have different names to be signed and copies them back

REM setting platform variables
set ACXAMARINDROID= AdaptiveCards.Rendering.Xamarin.Android

REM setting path variables
set ACROOT=source\xamarin\
set ACXAMARINDROIDPATH=Xamarin.Droid\
set BINPATH=bin\Release\

if "%2" == "" goto :usage
if "%1" == "sign" goto :sign
if "%1" == "afterSign" goto :afterSign

goto :usage

:sign
pushd "%2"

REM AdaptiveCards.Rendering.Xamarin.Android
mkdir tosign\%ACXAMARINDROIDPATH%

REM AdaptiveCards.Rendering.Xamarin.Android
call :checkedCopy %ACROOT%%ACXAMARINDROIDPATH%%BINPATH%%ACXAMARINDROID%.dll tosign\%ACXAMARINDROIDPATH%%ACXAMARINDROID%.dll

popd
goto :end

:afterSign
pushd "%2"

REM AdaptiveCards.Rendering.Xamarin.Android
call :checkedCopy signed\%ACXAMARINDROIDPATH%%ACXAMARINDROID%.dll %ACROOT%%ACXAMARINDROIDPATH%%BINPATH%%ACXAMARINDROID%.dll                    

popd
goto :end

:checkedCopy
copy %1 %2
if %errorlevel% NEQ 0 (
    popd
    echo "copy failed"
    exit 1
)
exit /b

:usage
echo "Usage: CopySignFiles <sign| afterSign> <root of the repo>"
echo "Will copy the binary release from <root>\Release to be sent to signed"

:end
