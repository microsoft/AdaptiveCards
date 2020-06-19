function Invoke-TagRelease {
param(
[Parameter(Mandatory)]
[string]$tagPrefix, 

[Parameter(Mandatory)]
[string]$version,

[AllowNull()]
[string]$commitWithMessage
)

    if(!$env:BUILD_SOURCEBRANCH) { 
        Write-Error "Unknown source branch. Is this running from VSTS?" 
        return;
    }

    # Convert "/refs/head/main" => "main"
    $sourceBranch = $env:BUILD_SOURCEBRANCH -Split "/",3 | select -skip 2
    git checkout $sourceBranch 

    # Commit any changes
    if($commitWithMessage) {
        # This worked around a build issue
        git pull

        git add .
        git commit -m "$commitWithMessage ***NO_CI***"
        git push origin $sourceBranch
    }

    # Tag and push
    $tagName = "$tagPrefix-v$version"
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
