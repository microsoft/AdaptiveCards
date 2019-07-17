REM @echo off
REM This script copies the dll and winmd files to have different names to be signed and copies them back

REM setting platform varialbes
set ACT=AdaptiveCards.Templating
set ACSTANDARD20=netstandard2.0

REM setting path variables
set ACROOT=source\experimental\dotnet\
set ACTPATH=AdaptiveCards.Templating\
set BINPATH=bin\Release\
set ACSTANDARD20PATH=netstandard2.0\

if "%2" == "" goto :usage
if "%1" == "sign" goto :sign
if "%1" == "afterSign" goto :afterSign

goto :usage

:sign
pushd "%2"

REM AdaptiveCards
echo %ACTPATH%
mkdir tosign\%ACTPATH%%ACSTANDARD20PATH%


REM AdaptiveCards
call :checkedCopy %ACROOT%%ACTPATH%%BINPATH%%ACSTANDARD20PATH%%ACT%.dll tosign\%ACTPATH%%ACSTANDARD20PATH%%ACT%%ACSTANDARD20%.dll  

popd
goto :end

:afterSign
pushd "%2"

REM AdaptiveCards                      
call :checkedCopy signed\%ACTPATH%%ACSTANDARD20PATH%%ACT%%ACSTANDARD20%.dll %ACROOT%%ACTPATH%%BINPATH%%ACSTANDARD20PATH%%ACT%.dll          

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
