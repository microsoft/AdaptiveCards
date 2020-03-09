// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCardVisualizer.Helpers;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Threading.Tasks;
using Windows.Storage;
using Windows.UI.Popups;
using Windows.Storage.Pickers;
using Windows.UI.Xaml;
using Windows.Storage.Provider;

namespace AdaptiveCardVisualizer.ViewModel
{
    public abstract class GenericDocumentViewModel : BindableBase
    {
        public MainPageViewModel MainPageViewModel { get; private set; }
        public string Token { get; private set; }
        public IStorageFile File { get; private set; }

        private string _name = "Untitled";
        public string Name
        {
            get { return _name; }
            set { SetProperty(ref _name, value); }
        }

        public GenericDocumentViewModel(MainPageViewModel model)
        {
            MainPageViewModel = model;
        }

        public bool IsOutdated { get; set; } = true;

        protected string _payload = "";
        public string Payload
        {
            get { return _payload; }
            set { SetPayload(value); }
        }

        private void SetPayload(string value)
        {
            if (value == null)
            {
                throw new ArgumentNullException(nameof(value));
            }

            if (object.Equals(_payload, value))
            {
                return;
            }

            SetProperty(ref _payload, value);

            Reload();
        }

        public async void Reload()
        {
            IsOutdated = true;

            if (!IsLoading)
            {
                IsLoading = true;

                await Task.Delay(1000);

                IsLoading = false;
                NotifyPropertyChanged(DelayedUpdatePayload);
                Load();
            }
        }

        public void ReloadIfNeeded()
        {
            if (IsOutdated)
            {
                Reload();
            }
        }

        private bool _isLoading;
        /// <summary>
        /// Represents whether the system is delaying loading. Views should indicate this.
        /// </summary>
        public bool IsLoading
        {
            get { return _isLoading; }
            private set { SetProperty(ref _isLoading, value); }
        }

        /// <summary>
        /// This property will be notified of changes on a delayed schedule, so that it's not
        /// changing every single time a character is typed. Views presenting
        /// </summary>
        public string DelayedUpdatePayload
        {
            get { return Payload; }
        }

        public ObservableCollection<ErrorViewModel> Errors { get; private set; } = new ObservableCollection<ErrorViewModel>();

        protected async Task LoadFromFileAsync(IStorageFile file, string token, bool assignPayloadWithoutLoading)
        {
            this.Name = file.Name;
            this.File = file;
            this.Token = token;

            string payloadText = await FileIO.ReadTextAsync(file);
            if (assignPayloadWithoutLoading)
            {
                _payload = payloadText;
            }
            else
            {
                Payload = payloadText;
            }
        }

        private void CreateMessageDialog(string text)
        {
            var messageDialog = new MessageDialog(text);
            // Set the index of the command to be used as cancel (when ESC is pressed)
            // As there's only one command, command 0 is selected
            messageDialog.CancelCommandIndex = 0;
            var dontWait = messageDialog.ShowAsync();
        }

        private async Task SaveNewFile()
        {
            var savePicker = new FileSavePicker();
            savePicker.SuggestedStartLocation = PickerLocationId.DocumentsLibrary;
            savePicker.FileTypeChoices.Add("Plain Text", new List<string>() { ".json" });
            savePicker.SuggestedFileName = "NewAdaptiveCard.json";

            File = await savePicker.PickSaveFileAsync();
            if (File != null)
            {
                CachedFileManager.DeferUpdates(File);
                await FileIO.WriteTextAsync(File, File.Name);
                FileUpdateStatus status = await CachedFileManager.CompleteUpdatesAsync(File);
                if (status == FileUpdateStatus.Complete)
                {
                    this.Name = File.Name;
                }
                else
                {
                    CreateMessageDialog("File " + File.Name + " couldn't be saved");
                }
            }
        }

        public async Task SaveAsync()
        {
            if (File == null)
            {
                await SaveNewFile();
            }
            else
            {
                try
                {
                    await FileIO.WriteTextAsync(File, Payload);
                }
                catch (Exception ex)
                {
                    CreateMessageDialog(ex.ToString());
                }
            }
        }

        private void Load()
        {
            if (string.IsNullOrWhiteSpace(Payload))
            {
                SetSingleError(new ErrorViewModel()
                {
                    Message = "Invalid payload",
                    Type = ErrorViewModelType.Error
                });
                return;
            }

            string payload = Payload;

            try
            {
                LoadPayload(payload);
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.ToString());
                MakeErrorsLike(new List<ErrorViewModel>()
                {
                    new ErrorViewModel()
                    {
                        Message = "Loading failed",
                        Type = ErrorViewModelType.Error
                    }
                });
            }

            IsOutdated = false;
        }

        protected abstract void LoadPayload(string payload);

        protected void SetSingleError(ErrorViewModel error)
        {
            MakeErrorsLike(new List<ErrorViewModel>() { error });
        }

        protected void MakeErrorsLike(List<ErrorViewModel> errors)
        {
            errors.Sort();
            Errors.MakeListLike(errors);
        }
    }
}
