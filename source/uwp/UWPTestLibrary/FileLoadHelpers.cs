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
        public static async Task LoadAsync(
            ObservableCollection<FileViewModel> cards,
            ObservableCollection<FileViewModel> hostConfigs)
        {
            await LoadFilesAsync("LinkedCards", cards);

            // Load two host configs to test
            var hostConfigFolder = await Package.Current.InstalledLocation.GetFolderAsync("LinkedHostConfigs");
            hostConfigs.Add(await FileViewModel.LoadAsync(await hostConfigFolder.GetFileAsync("sample")));
            hostConfigs.Add(await FileViewModel.LoadAsync(await hostConfigFolder.GetFileAsync("windows-timeline")));

            // Remove the WeatherLarge card since it contains a background image and often fails image comparisons
            var weatherLarge = cards.FirstOrDefault(i => i.Name.EndsWith("WeatherLarge"));
            if (weatherLarge != null)
            {
                cards.Remove(weatherLarge);
            }
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
