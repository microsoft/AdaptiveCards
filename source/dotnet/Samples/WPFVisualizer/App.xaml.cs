// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace WpfVisualizer
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public App()
        {
            SetCurrentDirectory();
        }

        /// <summary>
        /// Sets the current directory to the app's output directory. This is needed for Desktop Bridge, which
        /// defaults to the Windows directory.
        /// </summary>
        private void SetCurrentDirectory()
        {
            // Gets the location of the EXE, including the EXE name
            var exePath = typeof(App).Assembly.Location;
            var outputDir = Path.GetDirectoryName(exePath);
            Directory.SetCurrentDirectory(outputDir);
        }
    }
}
