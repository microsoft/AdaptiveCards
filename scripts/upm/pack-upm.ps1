# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.
<#
.SYNOPSIS
    Builds the Adaptive Cards .NET Unity Package Manager (UPM) package.
.DESCRIPTION
    Builds UPM packages for the Adaptive Cards .NET.
.PARAMETER ProjectRoot
    The root folder of the project.
.PARAMETER OutputDirectory
    Where should we place the output? Defaults to ".\artifacts"
.PARAMETER Version
    What version of the artifacts should we build?
.PARAMETER BuildNumber
    The fourth digit (revision) for the full version.
.PARAMETER KeepStagingFolder
    If true, the staging folder created for generating the package is not deleted. Callers will be responsible
    for cleaning up package folder.
#>
param(
    [Parameter(Mandatory = $true)]
    [string]$ProjectRoot,

    [string]$OutputDirectory = "./artifacts/upm",

    [ValidatePattern("\d+\.\d+\.\d+")]
    [string]$Version,

    [ValidatePattern("\d+")]
    [string]$BuildNumber,

    [switch]$KeepStagingFolder
)

if ( $Verbose ) { $VerbosePreference = 'Continue' }

$ProjectRoot = Resolve-Path -Path $ProjectRoot

if ($PreviewTag) {
    $PreviewTag = "-$PreviewTag"
    Write-Output "Version preview: $PreviewTag"
}

if ($BuildNumber) {
    $BuildNumber = ".$BuildNumber"
}

if (-not (Test-Path $OutputDirectory -PathType Container)) {
    New-Item $OutputDirectory -ItemType Directory | Out-Null
}

$OutputDirectory = Resolve-Path -Path $OutputDirectory
Write-Verbose "OutputDirectory: $OutputDirectory"

$TempDirectory = Join-Path -Path $OutputDirectory -ChildPath "AdaptiveCards"
Write-Verbose "TempDirectory: $TempDirectory"

try {
    Push-Location $OutputDirectory

    $parseVersion = -not $Version

    $packages = Get-ChildItem -Path (Join-Path -Path $ProjectRoot -ChildPath "source/dotnet/Library/AdaptiveCards/package.json")
    if ($packages.Count -ne 1) {
        Write-Output "Error looking for package at $ProjectRoot/source/dotnet/Library/AdaptiveCards/package.json. Expecting 1 package, found $packages.Count"
        return;
    }

    $package = $packages[0];
    $packagePath = $package.Directory

    $metaFilesRootDirectory = Join-Path -Path $ProjectRoot -ChildPath "scripts/upm/meta-files"

    $folderFullPath = "$packagePath/*"

    $excludelist = (Join-Path -Path $packagePath -ChildPath "docs"), (Join-Path -Path $packagePath -ChildPath "AdaptiveCards.csproj")

    # Copy the desired package files to a temp directory
    (Get-ChildItem -Path "$folderFullPath") | Where { $excludeList -notcontains $_ } | ForEach-Object {
        if (-not(Test-Path "$TempDirectory")) {
            Write-Verbose "Creating temp folder: $TempDirectory"
            New-Item "$TempDirectory" -ItemType Directory
        }

        Copy-Item -Path $_.FullName -Destination "$TempDirectory" -Force -Recurse
    }

    $packageFileTempPath = Join-Path -Path $TempDirectory -ChildPath "package.json"

    # Update the version number in the package.json
    ((Get-Content -Path $package.FullName -Raw) -Replace '("version": )"([0-9.]+-?[a-zA-Z0-9.]*|%version%)', "`$1`"$Version") | Set-Content -Path $packageFileTempPath -NoNewline

    # Copy the associated .meta files
    (Get-ChildItem -Path "$metaFilesRootDirectory/*" -Filter "*.meta" -Recurse) | ForEach-Object {

        $rootDir = $metaFilesRootDirectory
        $currentDir = $_.Directory.FullName
        $tmp = Get-Location
        Set-Location $rootDir
        $relativePath = Resolve-Path -relative $currentDir

        $currentTargetDir = Join-Path -Path $OutputDirectory -ChildPath $relativePath

        Copy-Item -Path $_.FullName -Destination $currentTargetDir -Force
        Set-Location $tmp
    }

    Write-Output "======================="
    Write-Output "Creating com.microsoft.adaptivecards.net"
    Write-Output "======================="
    npm pack "$TempDirectory"

    if (-not ($KeepStagingFolder.IsPresent)) {
        Write-Verbose "Cleaning staging folder"
        Remove-Item -Path "$TempDirectory" -Recurse -Force
    }
}
finally {
    Pop-Location
}