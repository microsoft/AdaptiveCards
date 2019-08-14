// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using Windows.ApplicationModel;
using Windows.Storage;

namespace UWPTestLibrary
{
    public class FileLoadHelpers
    {
        public static String defaultHostConfigName = "No host config (default values)";
        public static String fixedNonInteractiveName = "Fixed Size Non-Interactive";
        public static String testVarientHostConfigName = "testVariantHostConfig";

        public static async Task LoadAsync(
            ObservableCollection<FileViewModel> cards,
            ObservableCollection<FileViewModel> hostConfigs)
        {
            await LoadFilesAsync("LinkedCards", cards);

            // Create two dummy host config file views, one for default values and one for default
            // values but with fixed height and interactivity turned off
            FileViewModel noFileModel = new FileViewModel();
            noFileModel.Name = defaultHostConfigName;
            hostConfigs.Add(noFileModel);

            FileViewModel fixedNonInteractive = new FileViewModel();
            fixedNonInteractive.Name = fixedNonInteractiveName;
            hostConfigs.Add(fixedNonInteractive);

            // Load the testVariantHostConfig to test non-default host config values
            var hostConfigFolder = await Package.Current.InstalledLocation.GetFolderAsync("LinkedHostConfigs");
            hostConfigs.Add(await FileViewModel.LoadAsync(await hostConfigFolder.GetFileAsync(testVarientHostConfigName)));
        }

        private static async Task LoadFilesAsync(string folder, IList<FileViewModel> insertInto)
        {
            await LoadFilesAsyncHelper(folder, await Package.Current.InstalledLocation.GetFolderAsync(folder), insertInto);
        }

        private static async Task LoadFilesAsyncHelper(string currentName, StorageFolder currentFolder, IList<FileViewModel> insertInto)
        {
            foreach (var file in await currentFolder.GetFilesAsync())
            {
                insertInto.Add(await FileViewModel.LoadAsync(file));
            }

            foreach (var folder in await currentFolder.GetFoldersAsync())
            {
                await LoadFilesAsyncHelper(currentName + "/" + folder.Name, folder, insertInto);
            }
        }
    }
}
