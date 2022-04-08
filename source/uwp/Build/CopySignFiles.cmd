REM @echo off
REM This script copies the dll and winmd files to have different names to be signed and copies them back

REM setting platform variables
set AC=AdaptiveCards
set ACUWP=AdaptiveCards.Rendering.Uwp

REM setting path variables
set ACROOT=source\uwp\
set ACPATH=AdaptiveCardRenderer\
set BINPATH=Release\

if "%2" == "" goto :usage
if "%1" == "sign" goto :sign
if "%1" == "afterSign" goto :afterSign

goto :usage

:sign
pushd "%2"

REM AdaptiveCards
echo %ACPATH%
REM AdaptiveCards UWP

mkdir tosign\%ACPATH%\Win32
mkdir tosign\%ACPATH%\x64
mkdir tosign\%ACPATH%\ARM
mkdir tosign\%ACPATH%\ARM64

call :checkedCopy %ACROOT%\Release\%ACPATH%%ACUWP%.winmd tosign\%ACPATH%%ACUWP%.winmd
call :checkedCopy %ACROOT%Release\%ACPATH%%ACUWP%.dll tosign\%ACPATH%Win32\%ACUWP%.dll
call :checkedCopy %ACROOT%x64\Release\%ACPATH%%ACUWP%.dll tosign\%ACPATH%x64\%ACUWP%.dll
call :checkedCopy %ACROOT%ARM\Release\%ACPATH%%ACUWP%.dll tosign\%ACPATH%ARM\%ACUWP%.dll
call :checkedCopy %ACROOT%ARM64\Release\%ACPATH%%ACUWP%.dll tosign\%ACPATH%ARM64\%ACUWP%.dll

popd
goto :end

:afterSign
pushd "%2"

REM AdaptiveCards
call :checkedCopy signed\%ACPATH%%ACUWP%.winmd %ACROOT%Release\%ACPATH%%ACUWP%.winmd
call :checkedCopy signed\%ACPATH%Win32\%ACUWP%.dll %ACROOT%Release\%ACPATH%%ACUWP%.dll
call :checkedCopy signed\%ACPATH%x64\%ACUWP%.dll %ACROOT%x64\Release\%ACPATH%%ACUWP%.dll
call :checkedCopy signed\%ACPATH%ARM\%ACUWP%.dll %ACROOT%ARM\Release\%ACPATH%%ACUWP%.dll
call :checkedCopy signed\%ACPATH%ARM64\%ACUWP%.dll %ACROOT%ARM64\Release\%ACPATH%%ACUWP%.dll

popd
goto :end

:checkedCopy
copy %1 %2
if %errorlevel% NEQ 0 (
    popd
    echo "copy failed"
    REM exit 1
)
REM exit /b

:usage
echo "Usage: CopySignFiles <sign | afterSign> <root of the repo>"
echo "Will copy the binary release from <root>\Release to be sent to signed"

:end
