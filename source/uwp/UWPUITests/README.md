# Running Automation Tests Locally

## Before running the tests

Before running the tests the WinUITestApp must be built and the appx package that will be installed for testing must be generated, this can be done by building the project in VisualStudio, but if the package was not generated you can follow the steps below to generate the package: 

1. Open a "Developer Command Prompt for VS 2019"
2. From the AdaptiveCards repository root: ` cd source\uwp\UWPUITestApp `
3. Build the appx package by executing the command ` msbuild .\UWPUITestApp.csproj /p:DeployOnBuild=true `

## Executing the tests

Tests can be executed from Visual studio by running them as any other unit test, you can look for them in the Test explorer. Executing the tests require the system to install the appx package built on the previous steps, you may require to provide permissions for the certificate to be installed. 