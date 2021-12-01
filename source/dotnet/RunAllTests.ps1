Push-Location $PSScriptRoot

# Disable our build versionning for the tests as it doesn't support .NETCore
$env:XES_DISABLEMSBUILDVERSIONING ="True"

$testResultsPath = New-Item -ErrorAction Ignore -ItemType directory -Path .\TestResults\$(get-date -f MM-dd-yyyy-HH-mm-ss)
New-Item -ItemType directory $testResultsPath/HTML
New-Item -ItemType directory $testResultsPath/WPF

$samplesPath =  "..\..\..\..\samples"
$v1scenariosPath = $samplesPath + "\v1.0\scenarios"

Write-Host Running unit tests...
dotnet test .\test\AdaptiveCards.Test

Write-Host Running WPF tests...
Set-Location .\Samples\AdaptiveCards.Sample.ImageRender

Write-Host SupportsInteractivity = false...
dotnet run $v1scenariosPath -- -r -o $testResultsPath\WPF\StandardNonInteractive

Write-Host SupportsInteractivity = true...
dotnet run $v1scenariosPath -- -r -i -o $testResultsPath\WPF\Standard

Write-Host Windows notification config....
dotnet run $v1scenariosPath -- -r -o $testResultsPath\WPF\WindowsNotification --host-config $samplesPath\hostconfig\windows-notification.json

Write-Host Timeline config...
dotnet run $v1scenariosPath -- -r -o $testResultsPath\WPF\WindowsTimeline --host-config $samplesPath\hostconfig\windows-timeline.json

Pop-Location
