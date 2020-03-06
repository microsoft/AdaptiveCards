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

        public async Task SaveAsync()
        {
            try
            {
                await FileIO.WriteTextAsync(File, Payload);
            }
            catch (Exception ex)
            {
                var dontWait = new MessageDialog(ex.ToString());
                dontWait.CancelCommandIndex = 0;
                await dontWait.ShowAsync();
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
