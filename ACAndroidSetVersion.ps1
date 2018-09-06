#$version=Get-Content .\custom.props | Select-String -Pattern "NugetPackVersion"
#$version.ToString().Split('>')[1].Split('<')[0]

$adaptivecardsversion = $env:XES_PACKAGEVERSIONNUMBER
foreach($pathComponent in $env:BUILD_SOURCEBRANCH.ToString().Split('\'))
{
    if($pathComponent -eq "release") {
        $adaptivecardsversion = "($adaptivecardsversion + $env:BUILD_BUILDNUMBER)"
    }
}
 
Write-Host "##vso[task.setvariable variable=AdaptiveCardsVersion]$adaptivecardsversion"