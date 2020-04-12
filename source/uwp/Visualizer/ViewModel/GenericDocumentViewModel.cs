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

        protected KeyboardPressTimeCounter TimeCounter;

        public GenericDocumentViewModel(MainPageViewModel model)
        {
            MainPageViewModel = model;
            TimeCounter = new KeyboardPressTimeCounter(this);
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

                await Task.Delay(TimeSpan.FromSeconds(1));

                IsLoading = false;
                NotifyPropertyChanged(DelayedUpdatePayload);
                Load();

                TimeCounter.ResetCounter();
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
                var dontWait = new MessageDialog(ex.ToString()).ShowAsync();
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
                errors = new List<ErrorViewModel>()
                {
                    new ErrorViewModel()
                    {
                        Message = "Loading failed",
                        Type = ErrorViewModelType.Error
                    }
                };

                TimeCounter.ResetCounter();
            }

            IsOutdated = false;
        }

        protected abstract void LoadPayload(string payload);

        protected void SetSingleError(ErrorViewModel error)
        {
            errors = new List<ErrorViewModel>() { error };
            TimeCounter.ResetCounter();
        }

        public void MakeErrorsLike()
        {
            if (errors != null)
            {
                errors.Sort();
                Errors.MakeListLike(errors);
            }
        }

        protected List<ErrorViewModel> errors = new List<ErrorViewModel>();
    }
}
