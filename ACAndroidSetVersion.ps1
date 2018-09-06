#$version=Get-Content .\custom.props | Select-String -Pattern "NugetPackVersion"
#$version.ToString().Split('>')[1].Split('<')[0]

$adaptivecardsversion = "($env:XES_PACKAGEVERSIONNUMBER-20$env:BUILD_BUILDNUMBER)"
foreach($pathComponent in $env:BUILD_SOURCEBRANCH.ToString().Split('\'))
{
    if($pathComponent -eq "release") {
        $adaptivecardsversion = $env:XES_PACKAGEVERSIONNUMBER
    }
}

Write-Host "##vso[task.setvariable variable=AdaptiveCardsVersion]$adaptivecardsversion"
