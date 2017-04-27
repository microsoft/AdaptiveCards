@echo You need to be running in "DEVELOPER COMMAND PROMPT for 2017" for this script to work
@pause

call enabledelaysign.cmd
md Library\bin
erase /q Library\bin\*.*
cd Library/AdaptiveCards
call createpackage
cd ..\AdaptiveCards.Html
call createpackage
cd ..\AdaptiveCards.Xaml.Wpf
call createpackage
cd ..\AdaptiveCards.Xaml.Wpf.RichInput
call createpackage
cd ..\..
cd library/bin
dir /b

