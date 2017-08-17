using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.Storage;
using Windows.Storage.AccessCache;
using Windows.Storage.Pickers;
using XamlCardVisualizer.Helpers;

namespace XamlCardVisualizer.ViewModel
{
    public class MainPageViewModel : BindableBase
    {
        public ObservableCollection<DocumentViewModel> OpenDocuments { get; private set; } = new ObservableCollection<DocumentViewModel>();

        private DocumentViewModel _currentDocument;
        public DocumentViewModel CurrentDocument
        {
            get { return _currentDocument; }
            set { SetProperty(ref _currentDocument, value); }
        }

        public void NewDocument()
        {
            OpenDocuments.Add(new DocumentViewModel()
            {
                Payload = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""0.5"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Untitled card""
    }
  ]
}"
            });
            CurrentDocument = OpenDocuments.Last();
        }

        public async void OpenDocument()
        {
            try
            {
                FileOpenPicker openPicker = new FileOpenPicker();
                openPicker.ViewMode = PickerViewMode.List;
                openPicker.FileTypeFilter.Add(".json");

                StorageFile file = await openPicker.PickSingleFileAsync();
                if (file != null)
                {
                    string token = StorageApplicationPermissions.FutureAccessList.Add(file);
                    OpenDocuments.Add(await DocumentViewModel.LoadFromFileAsync(this, file, token));
                    CurrentDocument = OpenDocuments.LastOrDefault();
                    SaveFileTokensAsync();
                }
                else
                {
                }
            }
            catch { }
        }

        public void CloseDocument(DocumentViewModel document)
        {
            // TODO: Check if not saved
            OpenDocuments.Remove(document);

            if (document.Token != null)
            {
                SaveFileTokensAsync();
            }
        }

        public static async Task<MainPageViewModel> LoadAsync()
        {
            var viewModel = new MainPageViewModel();

            var tokens = await GetFileTokensAsync();
            ObservableCollection<DocumentViewModel> documents = new ObservableCollection<DocumentViewModel>();
            foreach (string token in tokens)
            {
                try
                {
                    IStorageFile file;
                    if (token.StartsWith("SampleFile:"))
                    {
                        string fileName = token.Substring("SampleFile:".Length);
                        file = await StorageFile.GetFileFromApplicationUriAsync(new Uri("ms-appx:///Samples/" + fileName));
                    }
                    else
                    {
                        file = await StorageApplicationPermissions.FutureAccessList.GetFileAsync(token);
                    }

                    if (file != null)
                    {
                        documents.Add(await DocumentViewModel.LoadFromFileAsync(viewModel, file, token));
                    }
                }
                catch { }
            }

            if (documents.Count == 0)
            {
                try
                {
                    var samplesFolder = await Package.Current.InstalledLocation.GetFolderAsync("Samples");
                    foreach (var file in await samplesFolder.GetFilesAsync())
                    {
                        if (file.FileType.ToLower().Equals(".json"))
                        {
                            documents.Add(await DocumentViewModel.LoadFromFileAsync(viewModel, file, "SampleFile:" + file.Name));
                        }
                    }
                }
                catch { }
            }

            viewModel.OpenDocuments = documents;
            viewModel.CurrentDocument = documents.FirstOrDefault();
            return viewModel;
        }

        private static async Task<string[]> GetFileTokensAsync()
        {
            try
            {
                var file = await ApplicationData.Current.LocalCacheFolder.GetFileAsync("Files.dat");
                return (await FileIO.ReadLinesAsync(file)).ToArray();
            }
            catch { return new string[0]; }
        }

        private async void SaveFileTokensAsync()
        {
            try
            {
                var tokens = OpenDocuments.Where(i => i.Token != null).Select(i => i.Token).ToArray();
                var file = await ApplicationData.Current.LocalCacheFolder.CreateFileAsync("Files.dat", CreationCollisionOption.ReplaceExisting);
                await FileIO.WriteLinesAsync(file, tokens);
            }
            catch { }
        }
    }
}