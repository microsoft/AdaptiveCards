function Invoke-TagRelease {
param([string]$tagPrefix, [string]$version)

    if(!$env:BUILD_SOURCEBRANCH) { 
        Write-Error "Unknown source branch. Is this running from VSTS?" 
        return -1;
    }


    # Convert "/refs/head/master" => "master"
    $sourceBranch = $env:BUILD_SOURCEBRANCH -Split "/",3 | select -skip 2

    $tagName = "$tagPrefix-v$version"
    git checkout $sourceBranch 
    git tag -a -m "Released $tagPrefix v$version" $tagName
    git push origin $tagName

}

function Get-VersionFromNupkg {
param([string]$packagePath)

    if(!$packagePath) { $packagePath = "$env:SYSTEM_DEFAULTWORKINGDIRECTORY\**" }

    $file = (Get-Item $packagePath\*.nupkg | Select-Object -first 1).Name;
    $matches = ([regex]"AdaptiveCards\.(.+)\.nupkg").Matches($file);
    $version = $matches[0].Groups[1].Value;

    return $version
}
