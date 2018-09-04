#!/bin/bash
version=$(grep -i "NugetPackVersion" custom.props | cut -d '>' -f 2 | cut -d '<' -f 1)
##vso[task.setvariable variable=AdaptiveCardsVersion]$version
