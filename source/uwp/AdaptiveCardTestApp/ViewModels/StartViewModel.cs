using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.Storage;

namespace AdaptiveCardTestApp.ViewModels
{
    public class StartViewModel : BaseViewModel
    {
        public ObservableCollection<FileViewModel> Cards { get; private set; } = new ObservableCollection<FileViewModel>();
        public ObservableCollection<FileViewModel> HostConfigs { get; private set; } = new ObservableCollection<FileViewModel>();

        public ObservableCollection<FileViewModel> SelectedCards { get; private set; } = new ObservableCollection<FileViewModel>();

        public ObservableCollection<FileViewModel> SelectedHostConfigs { get; private set; } = new ObservableCollection<FileViewModel>();

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

            await LoadFilesAsync("LinkedCards", Cards);
            await LoadFilesAsync("LinkedHostConfigs", HostConfigs);

            // Remove the WeatherLarge card since it contains a background image and often fails image comparisons
            var weatherLarge = Cards.FirstOrDefault(i => i.Name.EndsWith("WeatherLarge"));
            if (weatherLarge != null)
            {
                Cards.Remove(weatherLarge);
            }

            foreach (var c in Cards)
            {
                SelectedCards.Add(c);
            }

            foreach (var hc in HostConfigs)
            {
                SelectedHostConfigs.Add(hc);
            }
        }

        private async Task LoadFilesAsync(string folder, IList<FileViewModel> insertInto)
        {
            await LoadFilesAsyncHelper(folder, await Package.Current.InstalledLocation.GetFolderAsync(folder), insertInto);
        }

        private async Task LoadFilesAsyncHelper(string currentName, StorageFolder currentFolder, IList<FileViewModel> insertInto)
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
