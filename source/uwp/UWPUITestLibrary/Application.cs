// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;
using Windows.Management.Deployment;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Reflection;

using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.VisualStudio.TestTools.UnitTesting.Logging;

using System.Runtime.InteropServices;
using OpenQA.Selenium.Appium.Windows;
using OpenQA.Selenium.Appium;
using Windows.Foundation;

namespace UWPUITestLibrary
{

    public class Application
    {
        protected const string WindowsApplicationDriverUrl = "http://127.0.0.1:4723/wd/hub";
        private WindowsDriver<WindowsElement> TestAppSession = null;

        private readonly string _simplePackageName;

        private readonly string _packageName;
        private readonly string _packageFamilyName;
        private readonly string _appName;

        private readonly string _certSerialNumber;
        private readonly string _baseAppxDir;

        public Application()
        {
            _simplePackageName = "UWPUITestApp";

            _packageName = "AdaptiveCardsUWPUITestApp";
            _packageFamilyName = "AdaptiveCardsUWPUITestApp_ghhk6r1bdgbcc";
            _appName = "AdaptiveCardsUWPUITestApp_ghhk6r1bdgbcc!App";

            _certSerialNumber = "55caf56ff51d839e482b7c988be2c263";

            string assemblyDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            string baseDirectory = Directory.GetParent(assemblyDir).Parent.FullName;

            // Replace the TestLibrary folder for the TestApp folder
            string appBaseDirectory = baseDirectory.Replace("UWPUITestLibrary", "UWPUITestApp");

            _baseAppxDir = appBaseDirectory;
        }

        #region Properties
        public Process Process { get; private set; }

        #endregion

        #region Methods
        internal void Initialize(bool doLaunch = false, string deploymentDir = null)
        {
            if (TestAppSession == null)
            {
                TestAppSession = Launch();
            }
        }

        private WindowsDriver<WindowsElement> Launch()
        {
            WindowsDriver<WindowsElement> testAppSession = null;

            InstallTestAppIfNeeded();

            Logger.LogMessage("Launching app {0}", _appName);

            testAppSession = LaunchApp();

            Assert.IsNotNull(testAppSession, "coreWindow");

            return testAppSession;
        }

        private WindowsDriver<WindowsElement> LaunchApp()
        {
            AppiumOptions options = new AppiumOptions();
            options.AddAdditionalCapability("platformName", "Windows");
            options.AddAdditionalCapability("platformVersion", "10");
            options.AddAdditionalCapability("deviceName", "WindowsPC");

            // Update this value
            options.AddAdditionalCapability("app", _appName);

            WindowsDriver<WindowsElement> testAppSession = new WindowsDriver<WindowsElement>(new Uri(WindowsApplicationDriverUrl), options);

            return testAppSession;
        }

        public void Close()
        {
            if (TestAppSession != null)
            {
                TestAppSession.Quit();
            }
        }

        // This is a slightly modified version of how WinUI remove a previously installed version of the test app, as Appium is not
        // compatible with UWP projects we have to remove the packages using the RemovePackage command rather than use the PackageManager class 
        private void InstallTestAppIfNeeded()
        {
            string mostRecentlyBuiltAppx = string.Empty;
            DateTime timeMostRecentlyBuilt = DateTime.MinValue;

            var exclude = new[] { "Microsoft.NET.CoreRuntime", "Microsoft.VCLibs" };

            var files = Directory.GetFiles(_baseAppxDir, $"{_simplePackageName}*.appx", SearchOption.AllDirectories).ToList();
            files.AddRange(Directory.GetFiles(_baseAppxDir, $"{_simplePackageName}*.msix", SearchOption.AllDirectories));

            var filteredFiles = files.Where(f => !exclude.Any(Path.GetFileNameWithoutExtension(f).Contains));

            if (filteredFiles.Count() == 0)
            {
                throw new Exception(string.Format("Failed to find '{1}*.appx' or '*{1}.msix' in {0}'!", _baseAppxDir, _packageName));
            }

            foreach (string file in filteredFiles)
            {
                DateTime fileWriteTime = File.GetLastWriteTime(file);

                if (fileWriteTime > timeMostRecentlyBuilt)
                {
                    timeMostRecentlyBuilt = fileWriteTime;
                    mostRecentlyBuiltAppx = file;
                }
            }

            PackageManager packageManager = new PackageManager();
            DeploymentResult result = null;

            var installedPackages = packageManager.FindPackagesForUser(string.Empty, _packageFamilyName);
            foreach (var installedPackage in installedPackages)
            {
                Logger.LogMessage("Test AppX package already installed. Removing existing package by name: {0}", installedPackage.Id.FullName);
                
                AutoResetEvent removePackageCompleteEvent = new AutoResetEvent(false);

                var removeAppPowershellProcess = Process.Start(new ProcessStartInfo("powershell",
                    string.Format("-ExecutionPolicy Unrestricted Get-AppxPackage *{0}* | Remove-AppxPackage",
                        "AdaptiveCardsUWPUITestApp"))
                {
                    UseShellExecute = true
                });
                removeAppPowershellProcess.WaitForExit();

                if (removeAppPowershellProcess.ExitCode == 0)
                {
                    Logger.LogMessage("Removal successful.");
                }
                else
                {
                    Logger.LogMessage("Removal failed!");
                    Logger.LogMessage("Package removal ActivityId = {0}", result.ActivityId);
                    Logger.LogMessage("Package removal ErrorText = {0}", result.ErrorText);
                    Logger.LogMessage("Package removal ExtendedErrorCode = {0}", result.ExtendedErrorCode);
                }
            }

            Logger.LogMessage("Installing AppX...");

            Logger.LogMessage("Checking if the app's certificate is installed...");

            var certutilProcess = Process.Start(new ProcessStartInfo("certutil.exe",
                    string.Format("-verifystore TrustedPeople {0}", _certSerialNumber))
            {
                UseShellExecute = true
            });
            certutilProcess.WaitForExit();

            if (certutilProcess.ExitCode == 0)
            {
                Logger.LogMessage("Certificate is installed. Installing app...");
            }
            else
            {
                Logger.LogMessage("Certificate is not installed. Installing app and certificate...");
            }

            var powershellProcess = Process.Start(new ProcessStartInfo("powershell",
                    string.Format("-ExecutionPolicy Unrestricted -File {0}\\Add-AppDevPackage.ps1 {1}",
                        Path.GetDirectoryName(mostRecentlyBuiltAppx),
                        certutilProcess.ExitCode == 0 ? "-Force" : ""))
            {
                UseShellExecute = true
            });
            powershellProcess.WaitForExit();

            if (powershellProcess.ExitCode != 0)
            {
                throw new Exception(string.Format("Failed to install AppX for {0}!", _packageName));
            }
        }
        #endregion
    }
}
