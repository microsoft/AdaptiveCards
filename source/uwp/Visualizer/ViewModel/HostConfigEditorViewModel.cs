// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards.Rendering.Uwp;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;
using AdaptiveCardVisualizer.Helpers;

namespace AdaptiveCardVisualizer.ViewModel
{
    public class HostConfigEditorViewModel : GenericDocumentViewModel
    {
        private HostConfigEditorViewModel(MainPageViewModel mainPageViewModel) : base(mainPageViewModel) { }

        public event EventHandler<AdaptiveHostConfig> HostConfigChanged;

        public AdaptiveHostConfig HostConfig { get; private set; }

        protected override void LoadPayload(string payload)
        {
            try
            {
                var newHostConfig = AdaptiveHostConfig.FromJsonString(payload).HostConfig;

                if (newHostConfig != null)
                {
                    HostConfig = newHostConfig;

                    HostConfigChanged?.Invoke(this, HostConfig);

                    MakeErrorsLike(new List<ErrorViewModel>());
                }
                else
                {
                    SetSingleError(new ErrorViewModel()
                    {
                        Message = "Invalid Host Config payload",
                        Type = ErrorViewModelType.ErrorButRenderAllowed
                    });
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.ToString());
                SetSingleError(new ErrorViewModel()
                {
                    Message = ex.ToString(),
                    Type = ErrorViewModelType.ErrorButRenderAllowed
                });
            }
        }

        public static async Task<HostConfigEditorViewModel> LoadAsync(MainPageViewModel mainPageViewModel)
        {
            try
            {
                StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(new Uri("ms-appx:///HostConfigs/DefaultHostConfig.json"));
                string text = await FileIO.ReadTextAsync(file);

                return new HostConfigEditorViewModel(mainPageViewModel)
                {
                    Payload = text
                };
            }
            catch
            {
                return new HostConfigEditorViewModel(mainPageViewModel);
            }
        }
    }
}
