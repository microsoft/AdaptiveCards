Push-Location $PSScriptRoot

# Disable our build versionning for the tests as it doesn't support .NETCore
$env:XES_DISABLEMSBUILDVERSIONING ="True"

$testResultsPath = New-Item -ErrorAction Ignore -ItemType directory -Path .\TestResults\$(get-date -f MM-dd-yyyy-HH-mm-ss)
New-Item -ItemType directory $testResultsPath/HTML
New-Item -ItemType directory $testResultsPath/WPF

$samplesPath =  "..\..\..\..\samples\v1.0"
$scenariosPath = $samplesPath + "\scenarios"

Write-Host Running unit tests...
dotnet test .\test\AdaptiveCards.Test
dotnet test .\test\AdaptiveCards.Rendering.Html.Test

Write-Host Running HTML tests...
Set-Location .\Samples\AdaptiveCards.Sample.Html

Write-Host SupportsInteractivity = false...
dotnet run $scenariosPath -r -o $testResultsPath\HTML\StandardNonInteractive.html

Write-Host SupportsInteractivity = true...
dotnet run $scenariosPath -r -i -o $testResultsPath\HTML\Standard.html

Write-Host Windows notification config...
dotnet run $scenariosPath -r -o $testResultsPath\HTML\WindowsNotification.html --host-config $samplesPath\hostconfig\windows-notification.json

Write-Host Timeline config...
dotnet run $scenariosPath -r -o $testResultsPath\HTML\WindowsTimeline.html --host-config $samplesPath\hostconfig\windows-timeline.json

Write-Host Running WPF tests...
Set-Location ..\AdaptiveCards.Sample.ImageRender

Write-Host SupportsInteractivity = false...
dotnet run $scenariosPath -r -o $testResultsPath\WPF\StandardNonInteractive

Write-Host SupportsInteractivity = true...
dotnet run $scenariosPath -r -i -o $testResultsPath\WPF\Standard

Write-Host Windows notification config....
dotnet run $scenariosPath -r -o $testResultsPath\WPF\WindowsNotification --host-config $samplesPath\hostconfig\windows-notification.json

Write-Host Timeline config...
dotnet run $scenariosPath -r -o $testResultsPath\WPF\WindowsTimeline --host-config $samplesPath\hostconfig\windows-timeline.json

Pop-Location