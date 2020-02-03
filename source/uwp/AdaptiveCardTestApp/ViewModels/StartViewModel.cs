// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.ObjectModel;
using System.Threading.Tasks;
using UWPTestLibrary;
using Windows.Storage;

namespace AdaptiveCardTestApp.ViewModels
{
    public class StartViewModel : BindableBase
    {
        public ObservableCollection<FileViewModel> Cards { get; private set; } = new ObservableCollection<FileViewModel>();
        public ObservableCollection<FileViewModel> HostConfigs { get; private set; } = new ObservableCollection<FileViewModel>();

        public ObservableCollection<FileViewModel> SelectedCards { get; private set; } = new ObservableCollection<FileViewModel>();

        public ObservableCollection<FileViewModel> SelectedHostConfigs { get; private set; } = new ObservableCollection<FileViewModel>();
        public Boolean AddToTimeline { get; set; } = false;

        public StorageFolder ExpectedFolder { get; set; }

        public async Task LoadAsync()
        {
            // Delete any old temp data
            try
            {
                var tempResultsFolder = await ApplicationData.Current.TemporaryFolder.GetFolderAsync("Results");
                if (tempResultsFolder != null)
                {
                    await tempResultsFolder.DeleteAsync();
                }
            }
            catch { }

            await UWPTestLibrary.FileLoadHelpers.LoadAsync(Cards, HostConfigs);

            foreach (var c in Cards)
            {
                SelectedCards.Add(c);
            }

            foreach (var hc in HostConfigs)
            {
                SelectedHostConfigs.Add(hc);
            }
        }
    }
}
