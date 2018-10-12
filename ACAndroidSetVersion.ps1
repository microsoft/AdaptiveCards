
$adaptivecardsversion = "$env:XES_PACKAGEVERSIONNUMBER-20$env:TFS_VersionNumber"
foreach($pathComponent in $env:BUILD_SOURCEBRANCH.ToString().Split('\'))
{
    if($pathComponent -eq "release") {
        $adaptivecardsversion = $env:XES_PACKAGEVERSIONNUMBER
    }
}

Write-Host "##vso[task.setvariable variable=AdaptiveCardsVersion]$adaptivecardsversion"
