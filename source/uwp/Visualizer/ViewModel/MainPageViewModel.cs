// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards.Rendering.Uwp;
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
using AdaptiveCardVisualizer.Helpers;

namespace AdaptiveCardVisualizer.ViewModel
{
    public class MainPageViewModel : BindableBase
    {
        public ObservableCollection<DocumentViewModel> OpenDocuments { get; private set; } = new ObservableCollection<DocumentViewModel>();

        private DocumentViewModel _currentDocument;
        public DocumentViewModel CurrentDocument
        {
            get { return _currentDocument; }
            set
            {
                SetProperty(ref _currentDocument, value);

                if (value != null)
                {
                    value.ReloadIfNeeded();
                }
            }
        }

        public HostConfigEditorViewModel HostConfigEditor { get; private set; }

        private bool _inlineValidation = true;
        public bool InlineValidation
        {
            get { return _inlineValidation; }
            set
            {
                _inlineValidation = value;
                // Need to re-initialize Renderer so it changes whether it uses inline validation
                DocumentViewModel.InitializeRenderer(HostConfigEditor.HostConfig, _inlineValidation);
                ReRenderCards();
            }
        }

        public bool UseFixedDimensions
        {
            get { return Settings.UseFixedDimensions; }
            set
            {
                if (value != Settings.UseFixedDimensions)
                {
                    Settings.UseFixedDimensions = value;

                    // Need to re-initialize Renderer so it changes whether it uses fixed dimensions
                    DocumentViewModel.InitializeRenderer(HostConfigEditor.HostConfig, _inlineValidation);
                    ReRenderCards();
                }
            }
        }

        private void ReRenderCards()
        {
            // Set all card docs to outdated
            foreach (var doc in OpenDocuments)
            {
                doc.IsOutdated = true;
            }

            if (CurrentDocument != null)
            {
                // Reload the current doc
                CurrentDocument.ReloadIfNeeded();
            }
        }

        public void NewDocument()
        {
            OpenDocuments.Add(DocumentViewModel.LoadFromPayload(this, @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""0.5"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Untitled card""
    }
  ]
}"));
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

            viewModel.HostConfigEditor = await HostConfigEditorViewModel.LoadAsync(viewModel);
            viewModel.HostConfigEditor.HostConfigChanged += viewModel.HostConfigEditor_HostConfigChanged;

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

        private void HostConfigEditor_HostConfigChanged(object sender, AdaptiveHostConfig e)
        {
            DocumentViewModel.InitializeRenderer(e, _inlineValidation);
            ReRenderCards();
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
