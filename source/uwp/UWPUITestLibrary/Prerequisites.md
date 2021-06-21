# Running Automation Tests Locally

## Prerequisites 

Automation tests require the use of the Appium framework to be able to be executed, as appium is a webserver built on javascript we're going to require some extra software:
1. Install Node.js (https://nodejs.org/en/download/)
2. Install Appium 
    * Appium can be downloaded from their website (https://appium.io/)
    * OR can be downloaded using console by running the follwing commands
```
npm install -g appium  # get appium
npm install wd         # get appium client
```
3. Install Windows Application Driver, aka, WinAppDriver (https://github.com/Microsoft/WinAppDriver)


## Before running the tests

This extra process will most probably not be merged or be needed but currently the developer has to navigate to the WinUITestApp folder and generate the appx package that will be installed during testing: 

1. Open a "Developer Command Prompt for VS 2019"
2. From the AdaptiveCards repository root: ` cd source\uwp\UWPUITestApp `
3. Build the appx package by executing the command ` msbuild .\UWPUITestApp.csproj /p:DeployOnBuild=true `

Before executing the tests verify that you have started the appium server instance:
1. Open a command prompt window
2. Run the command ` appium `
3. You should see a message similar to
```
[Appium] Welcome to Appium v1.21.0
[Appium] Appium REST http interface listener started on 0.0.0.0:4723
```

## Executing the tests

Tests can be executed from Visual studio by running them as any other unit test, you can look for them in the Test explorer. Executing the tests require the system to install the appx package built on the previous steps, you may require to provide permissions for the certificate to be installed. 