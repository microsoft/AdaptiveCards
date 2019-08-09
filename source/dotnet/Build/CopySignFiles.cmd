REM @echo off
REM This script copies the dll and winmd files to have different names to be signed and copies them back

REM setting platform varialbes
set AC=AdaptiveCards
set ACHTML=AdaptiveCards.Rendering.Html
set ACWPF=AdaptiveCards.Rendering.Wpf
set ACWPFX=AdaptiveCards.Rendering.Wpf.Xceed
set ACNET=net4.5.2
set ACSTANDARD13=netstandard1.3
set ACSTANDARD20=netstandard2.0

REM setting path variables
set ACROOT=source\dotnet\Library\
set ACPATH=AdaptiveCards\
set ACHTMLPATH=AdaptiveCards.Rendering.Html\
set ACWPFPATH=AdaptiveCards.Rendering.Wpf\
set ACWPFXPATH=AdaptiveCards.Rendering.Wpf.Xceed\
set BINPATH=bin\Release\
set ACNETPATH=net4.5.2\
set ACSTANDARD13PATH=netstandard1.3\
set ACSTANDARD20PATH=netstandard2.0\

if "%2" == "" goto :usage
if "%1" == "sign" goto :sign
if "%1" == "afterSign" goto :afterSign

goto :usage

:sign
pushd "%2"

REM AdaptiveCards
echo %ACPATH%
mkdir tosign\%ACPATH%%ACNETPATH%
mkdir tosign\%ACPATH%%ACSTANDARD13PATH%
mkdir tosign\%ACPATH%%ACSTANDARD20PATH%

REM AdaptiveCards.Html
mkdir tosign\%ACHTMLPATH%%ACNETPATH%
mkdir tosign\%ACHTMLPATH%%ACSTANDARD13PATH%
mkdir tosign\%ACHTMLPATH%%ACSTANDARD20PATH%

REM AdaptiveCards.Rendering.Wpf
mkdir tosign\%ACWPFPATH%%ACNETPATH%

REM AdaptiveCards.Rendering.Wpf.Xceed
mkdir tosign\%ACWPFXPATH%%ACNETPATH%


REM AdaptiveCards
call :checkedCopy %ACROOT%%ACPATH%%BINPATH%%ACNETPATH%%AC%.dll tosign\%ACPATH%%ACNETPATH%%AC%.dll
call :checkedCopy %ACROOT%%ACPATH%%BINPATH%%ACSTANDARD13PATH%%AC%.dll tosign\%ACPATH%%ACSTANDARD13PATH%%AC%%ACSTANDARD13%.dll
call :checkedCopy %ACROOT%%ACPATH%%BINPATH%%ACSTANDARD20PATH%%AC%.dll tosign\%ACPATH%%ACSTANDARD20PATH%%AC%%ACSTANDARD20%.dll

REM AdaptiveCards.Html
call :checkedCopy %ACROOT%%ACHTMLPATH%%BINPATH%%ACNETPATH%%ACHTML%.dll tosign\%ACHTMLPATH%%ACNETPATH%%ACHTML%.dll      
call :checkedCopy %ACROOT%%ACHTMLPATH%%BINPATH%%ACSTANDARD13PATH%%ACHTML%.dll tosign\%ACHTMLPATH%%ACSTANDARD13PATH%%ACHTML%%ACSTANDARD13%.dll
call :checkedCopy %ACROOT%%ACHTMLPATH%%BINPATH%%ACSTANDARD20PATH%%ACHTML%.dll tosign\%ACHTMLPATH%%ACSTANDARD20PATH%%ACHTML%%ACSTANDARD20%.dll

REM AdaptiveCards.Rendering.Wpf
call :checkedCopy %ACROOT%%ACWPFPATH%%BINPATH%%ACNETPATH%%ACWPF%.dll tosign\%ACWPFPATH%%ACNETPATH%%ACWPF%.dll      

REM AdaptiveCards.Rendering.Wpf.Xceed
call :checkedCopy %ACROOT%%ACWPFXPATH%%BINPATH%%ACNETPATH%%ACWPFX%.dll tosign\%ACWPFXPATH%%ACNETPATH%%ACWPFX%.dll      

popd
goto :end

:afterSign
pushd "%2"

REM AdaptiveCards
call :checkedCopy signed\%ACPATH%%ACNETPATH%%AC%.dll %ACROOT%%ACPATH%%BINPATH%%ACNETPATH%%AC%.dll                         
call :checkedCopy signed\%ACPATH%%ACSTANDARD13PATH%%AC%%ACSTANDARD13%.dll %ACROOT%%ACPATH%%BINPATH%%ACSTANDARD13PATH%%AC%.dll                         
call :checkedCopy signed\%ACPATH%%ACSTANDARD20PATH%%AC%%ACSTANDARD20%.dll %ACROOT%%ACPATH%%BINPATH%%ACSTANDARD20PATH%%AC%.dll                         

REM AdaptiveCards.Html
call :checkedCopy signed\%ACHTMLPATH%%ACNETPATH%%ACHTML%.dll %ACROOT%%ACHTMLPATH%%BINPATH%%ACNETPATH%%ACHTML%.dll                         
call :checkedCopy signed\%ACHTMLPATH%%ACSTANDARD13PATH%%ACHTML%%ACSTANDARD13%.dll %ACROOT%%ACHTMLPATH%%BINPATH%%ACSTANDARD13PATH%%ACHTML%.dll                         
call :checkedCopy signed\%ACHTMLPATH%%ACSTANDARD20PATH%%ACHTML%%ACSTANDARD20%.dll %ACROOT%%ACHTMLPATH%%BINPATH%%ACSTANDARD20PATH%%ACHTML%.dll                         

REM AdaptiveCards.Rendering.Wpf
call :checkedCopy signed\%ACWPFPATH%%ACNETPATH%%ACWPF%.dll %ACROOT%%ACWPFPATH%%BINPATH%%ACNETPATH%%ACWPF%.dll                         

REM AdaptiveCards.Rendering.Wpf.Xceed
call :checkedCopy signed\%ACWPFXPATH%%ACNETPATH%%ACWPFX%.dll %ACROOT%%ACWPFXPATH%%BINPATH%%ACNETPATH%%ACWPFX%.dll                         

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
