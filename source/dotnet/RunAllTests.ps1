New-Item -ErrorAction Ignore -ItemType directory -Path .\TestResults
New-Item -ErrorAction Ignore -ItemType directory -Path .\TestResults\HTML
New-Item -ErrorAction Ignore -ItemType directory -Path .\TestResults\WPF

$samplesPath =  "..\..\..\..\samples\v1.0"
$scenariosPath = $samplesPath + "\scenarios"
$testResultsPath = "..\..\TestResults"

Write-Host Running HTML tests...
cd .\Samples\AdaptiveCards.Sample.Html

Write-Host SupportsInteractivity = false...
dotnet run $scenariosPath -r -o $testResultsPath\HTML\StandardNonInteractive.html

Write-Host SupportsInteractivity = true...
dotnet run $scenariosPath -r -i -o $testResultsPath\HTML\Standard.html

Write-Host Windows notification config...
dotnet run $scenariosPath -r -o $testResultsPath\HTML\WindowsNotification.html --host-config $samplesPath\hostconfig\windows-notification.json

Write-Host Timeline config...
dotnet run $scenariosPath -r -o $testResultsPath\HTML\WindowsTimeline.html --host-config $samplesPath\hostconfig\windows-timeline.json

Write-Host Running WPF tests...
cd ..\AdaptiveCards.Sample.ImageRender

Write-Host SupportsInteractivity = false...
dotnet run $scenariosPath -r -o $testResultsPath\WPF\StandardNonInteractive

Write-Host SupportsInteractivity = true...
dotnet run $scenariosPath -r -i -o $testResultsPath\WPF\Standard

Write-Host Windows notification config....
dotnet run $scenariosPath -r -o $testResultsPath\WPF\WindowsNotification --host-config $samplesPath\hostconfig\windows-notification.json

Write-Host Timeline config...
dotnet run $scenariosPath -r -o $testResultsPath\WPF\WindowsTimeline --host-config $samplesPath\hostconfig\windows-timeline.json

cd ..\..\