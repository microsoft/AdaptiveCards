# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.
<#
.SYNOPSIS
    Gets the current AdaptiveCards.NET version string
.DESCRIPTION
    Find and Extracts the current AdaptiveCards.NET NuGet package version from the custom.props file.
.PARAMETER ProjectRoot
    The root folder of the project.
#>
param(
    [Parameter(Mandatory = $true)]
    [string]$ProjectRoot
)

if ( $Verbose ) { $VerbosePreference = 'Continue' }

$ProjectRoot = Resolve-Path -Path $ProjectRoot

$PathToPropsFile = Join-Path -Path $ProjectRoot -ChildPath 'custom.props'

if (-not (Test-Path $PathToPropsFile -PathType Leaf)) {
    throw "Failed to retrive version info. $PathToPropsFile does not exist."
}

$match = Get-Content -Path $PathToPropsFile -Raw | Select-String -Pattern '<NuGetPackVersion>([0-9]+.[0-9]+.[0-9]+)</NuGetPackVersion>'

if ($match.Matches.Length -eq 1 && $match.Matches.groups.Length -eq 2) {
	$version = $match.Matches.groups[1].Value
    Write-Verbose "Found version: $version"
}
else {
    throw "Failed to retrive version info. $PathToPropsFile does not exist."
}

return $version