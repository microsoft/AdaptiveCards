$version=Get-Content .\custom.props | Select-String -Pattern "NugetPackVersion"
$adaptivecardsversion=$version.ToString().Split('>')[1].Split('<')[0]
$adaptivecardsversion= "$($adaptivecardsversion + '-' + $(Get-Date -Format FileDateTime))"
Write-Host "##vso[task.setvariable variable=AdaptiveCardsVersion]$adaptivecardsversion"