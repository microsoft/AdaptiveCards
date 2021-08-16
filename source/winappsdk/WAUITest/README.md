# Running Automation Tests Locally

## Before running the tests

Before running the tests the WinUITestApp must be built and the appx package that will be installed for testing must be generated, this can be done by building the project in VisualStudio, but if the package was not generated you can follow the steps below to generate the package: 

1. Open a "Developer Command Prompt for VS 2019"
2. From the AdaptiveCards repository root: ` cd source\uwp\UWPUITestApp `
3. Build the appx package by executing the command ` msbuild .\UWPUITestApp.csproj /p:DeployOnBuild=true `

## Executing the tests

Tests can be executed from Visual studio by running them as any other unit test, you can look for them in the Test explorer. Executing the tests require the system to install the appx package built on the previous steps, you may require to provide permissions for the certificate to be installed. 

## Troubleshoot

### The TestApp is not being initialized

The UI tests require the UI TestApp to be installed in the system, the installation process is done automatically when tests are run but the UITestApp should be built before tests are run. This is required for generating the required Appx files to be used for installing the application. 

Another possible problem for the installation may be provoked from having an application with the same ID installed from an outside source, this can be fixed by finding the application with the same ID and uninstalling it by executing `Remove-AppxPackage -Package "<package_id>"`.

### Display Scale

The framework used for interacting with the TestApp does not support having a display scale factor different than 100%, you can check the value of this property by going to `System > Display`