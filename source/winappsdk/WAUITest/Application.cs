// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Reflection;

using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.VisualStudio.TestTools.UnitTesting.Logging;

using System.Runtime.InteropServices;
using Windows.Foundation;
using Windows.Management.Deployment;
using Microsoft.Windows.Apps.Test.Foundation;
using Microsoft.Windows.Apps.Test.Foundation.Controls;
using Microsoft.Windows.Apps.Test.Foundation.Waiters;
using Microsoft.Windows.Apps.Test.Automation;

namespace UWPUITests
{
    using Window = Microsoft.Windows.Apps.Test.Foundation.Controls.Window;

    // Most of this code is part of the MUX Testing Infrastructure,
    // investigation on the added packages must be made to verify if there's any API that can do the same
    // TODO: Verify if the MUXTestInfra package can be used, instead of duplicating their code (Issue #6052)
    public class Application
    {
        private readonly string _simplePackageName;

        private readonly string _packageName;
        private readonly string _packageFamilyName;
        private readonly string _appName;
        private readonly string _appWindowTitle;

        private readonly string _certSerialNumber;
        private readonly string _baseAppxDir;

        private readonly UICondition _windowCondition = null;
        private readonly UICondition _appFrameWindowCondition = null;

        private static Application _Instance = null;

        public static Application Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new Application();
                }
                return _Instance;
            }
        }

        private Application()
        {
            _simplePackageName = "UWPUITestApp";

            _packageName = "AdaptiveCardsUWPUITestApp";
            _packageFamilyName = "AdaptiveCardsUWPUITestApp_ghhk6r1bdgbcc";
            _appName = "AdaptiveCardsUWPUITestApp_ghhk6r1bdgbcc!App";
            _appWindowTitle = "UWPUITestApp";

            _certSerialNumber = "55caf56ff51d839e482b7c988be2c263";

            string assemblyDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            string baseDirectory = Directory.GetParent(assemblyDir).Parent.Parent.FullName;

            // Replace the TestLibrary folder for the TestApp folder
            string appBaseDirectory = baseDirectory.Replace("UWPUITests", "UWPUITestApp");

            _baseAppxDir = appBaseDirectory;

            _windowCondition = UICondition.Create("@ClassName='Window' AND @Name={0}", _appWindowTitle);
            _appFrameWindowCondition = UICondition.Create("@ClassName='Window' AND @Name={0}", _appWindowTitle);
        }

        #region Properties
        public UIObject CoreWindow { get; private set; }
        public UIObject ApplicationFrameWindow { get; private set; }
        public Process Process { get; private set; }

        #endregion

        #region Methods
        internal void Initialize(bool doLaunch = false, string deploymentDir = null)
        {
            var topWindowCondition = _windowCondition.OrWith(_appFrameWindowCondition);

            UIObject topWindowObj = null;
            bool didFindWindow = UIObject.Root.Children.TryFind(topWindowCondition, out topWindowObj);

            // Only try to launch the app if we couldn't find the window.
            if (!didFindWindow)
            {
                CoreWindow = Launch();

                foreach (UIObject obj in CoreWindow.Ancestors)
                {
                    if (obj.Matches(_appFrameWindowCondition))
                    {
                        ApplicationFrameWindow = CoreWindow.Parent;
                        break;
                    }
                }
            }
            else if (didFindWindow)
            {
                // topWindowObj should match either _windowCondition or _appFrameWindowCondition

                if (topWindowObj.Matches(_windowCondition))
                {
                    // If the top level window is CoreWindow, then there is no AppFrame window:
                    CoreWindow = topWindowObj;
                    ApplicationFrameWindow = null;
                }
                else // _appFrameWindowCondition
                {
                    if (!topWindowObj.Matches(_appFrameWindowCondition))
                    {
                    }

                    // Maxmize window to ensure we can find UIA elements
                    var appFrameWindow = new Window(topWindowObj);
                    if (appFrameWindow.CanMaximize)
                    {
                        appFrameWindow.SetWindowVisualState(WindowVisualState.Maximized);
                    }

                    Assert.IsTrue(topWindowObj.Matches(_appFrameWindowCondition));
                    ApplicationFrameWindow = topWindowObj;

                    Logger.LogMessage("Looking for CoreWindow...");
                    for (int retries = 0; retries < 5; ++retries)
                    {
                        if (topWindowObj.Children.TryFind(_windowCondition, out var coreWindowObject))
                        {
                            CoreWindow = coreWindowObject;
                            Logger.LogMessage("Found CoreWindow.");
                            break;
                        }

                        Logger.LogMessage("CoreWindow not found. Sleep for 500 ms and retry");
                        Thread.Sleep(500);
                    }
                }
            }

            if (CoreWindow == null)
            {
                // We expect to have a window by this point.
                // LogDumpTree();
                throw new UIObjectNotFoundException("Could not find application window.");
            }

            // If this is running on desktop (it has an app frame window) then try to
            // maximize the window.

            if (ApplicationFrameWindow != null)
            {
                var appFrameWindow = new Window(ApplicationFrameWindow);
                if (appFrameWindow.CanMaximize)
                {
                    appFrameWindow.SetWindowVisualState(WindowVisualState.Maximized);
                }
            }

            Process = Process.GetProcessById(CoreWindow.ProcessId);
        }

        private UIObject Launch()
        {
            UIObject coreWindow = null;

            InstallTestAppIfNeeded();

            Logger.LogMessage("Launching app {0}", _appName);

            coreWindow = LaunchApp();

            Assert.IsNotNull(coreWindow, "coreWindow");

            Logger.LogMessage("Waiting for the close-app invoker to be found to signal that the app has launched successfully...");

            for (int retries = 0; retries < 5; ++retries)
            {
                UIObject obj;
                coreWindow.Descendants.TryFind(UICondition.Create("@AutomationId='__CloseAppInvoker'"), out obj);
                if (obj != null)
                {
                    Logger.LogMessage("Invoker found!");
                    break;
                }

                Logger.LogMessage("Invoker not found. Sleeping for 500 ms before trying again...");
                Thread.Sleep(500);
            }

            Logger.LogMessage("15056441 tracing, device family:" + Windows.System.Profile.AnalyticsInfo.VersionInfo.DeviceFamily);

            return coreWindow;
        }

        private UIObject LaunchApp()
        {
            UIObject coreWindow = null;

            // Launch sometimes times out but the app is just slow to launch and Launch has what appears to be
            // a 5-second timeout built in. 5 seconds isn't always enough in VM scenarios. If we try again, 
            // Launch will see that the app is already running and move on.
            const int MaxLaunchRetries = 5;
            for (int retries = 1; retries <= MaxLaunchRetries; ++retries)
            {
                try
                {
                    Logger.LogMessage("Attempting launch, try #{0}...", retries);
                    coreWindow = LaunchUWPApp();
                    Logger.LogMessage("Launch successful!");
                    break;
                }
                catch (Exception ex)
                {
                    Logger.LogMessage("Failed to launch app. Exception: " + ex.ToString());

                    if (retries < MaxLaunchRetries)
                    {
                        Logger.LogMessage("UAPApp.Launch might not have waited long enough, trying again {0}", retries);
                        Thread.Sleep(TimeSpan.FromSeconds(10)); // Give a healthy wait time.
                    }
                    else
                    {
                        Logger.LogMessage("Dumping UIA tree...");
                        // LogDumpTree();
                        Logger.LogMessage("Could not launch app {0} with top-level window condition '{1}'!", _appName, CreateTopLevelWindowCondition().ToString());
                        throw;
                    }
                }
            }

            return coreWindow;
        }

        private UIObject LaunchUWPApp()
        {
            var nameCondition = UICondition.CreateFromName(_appWindowTitle);
            var topLevelWindowCondition = CreateTopLevelWindowCondition().AndWith(nameCondition);
            return UAPApp.Launch(_appName, topLevelWindowCondition);
        }

        private UICondition CreateTopLevelWindowCondition()
        {
            string deviceFamily = Windows.System.Profile.AnalyticsInfo.VersionInfo.DeviceFamily;
            if (deviceFamily.Equals("Windows.Desktop", StringComparison.OrdinalIgnoreCase)
                || deviceFamily.Equals("Windows.Server", StringComparison.OrdinalIgnoreCase)
                || deviceFamily.Equals("Windows.Team", StringComparison.OrdinalIgnoreCase))
            {
                return UICondition.CreateFromClassName("ApplicationFrameWindow");
            }
            else
            {
                return UICondition.CreateFromClassName("Windows.UI.Core.CoreWindow");
            }
        }

        public void Close()
        {
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
