// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#if USE_WINUI3
using AdaptiveCards.Rendering.WinUI3;
#else
using AdaptiveCards.Rendering.Uwp;
#endif
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading.Tasks;
using Windows.Storage;
using Windows.UI.ViewManagement;

namespace AdaptiveCardVisualizer.ViewModel
{
    public class HostConfigEditorViewModel : GenericDocumentViewModel
    {
        private HostConfigEditorViewModel(MainPageViewModel mainPageViewModel) : base(mainPageViewModel) {
#if !USE_WINUI3
            // HighContrastChanged event does not work without a core window in WinUI3
            accessibilitySettings.HighContrastChanged += AccessibilitySettings_HighContrastChanged;
#endif
        }

        public event EventHandler<AdaptiveHostConfig> HostConfigChanged;
        public event EventHandler<AccessibilitySettings> HighContrastThemeChanged;

        public AdaptiveHostConfig HostConfig { get; private set; }
        protected AccessibilitySettings accessibilitySettings = new AccessibilitySettings();

        protected override void LoadPayload(string payload)
        {
            try
            {
                var newHostConfig = AdaptiveHostConfig.FromJsonString(payload).HostConfig;

                if (newHostConfig != null)
                {
                    HostConfig = newHostConfig;

                    HostConfigChanged?.Invoke(this, HostConfig);

                    errors = new List<ErrorViewModel>();
                    TimeCounter.ResetCounter();
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
            string hostConfig = await LoadHostConfigFromFileAsync();

            if (hostConfig != null)
            {
                return new HostConfigEditorViewModel(mainPageViewModel)
                {
                    Payload = hostConfig
                };
            }
            return new HostConfigEditorViewModel(mainPageViewModel);
        }

        private void AccessibilitySettings_HighContrastChanged(AccessibilitySettings sender, object args)
        {
            HighContrastThemeChanged?.Invoke(this, sender);
        }

        public static async Task<string> LoadHostConfigFromFileAsync()
        {
            string fileName = PickHostConfigFile();
            try
            {
                StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(new Uri("ms-appx:///HostConfigs/" + fileName));
                string text = await FileIO.ReadTextAsync(file);

                return text;
            }
            catch
            {
                return null;
            }
        }

        protected static string PickHostConfigFile()
        {
            AccessibilitySettings accessibilitySettings = new AccessibilitySettings();

            if (accessibilitySettings.HighContrast)
            {
                switch (accessibilitySettings.HighContrastScheme)
                {
                    case "High Contrast Black":
                        return "DefaultHostConfigHighContrastAquatic.json";
                    case "High Contrast White":
                        return "DefaultHostConfigHighContrastDesert.json";
                    case "High Contrast #1":
                        return "DefaultHostConfigHighContrastDusk.json";
                    case "High Contrast #2":
                        return "DefaultHostConfigHighContrastNightSky.json";
                }
            }
            return "DefaultHostConfig.json";
        }
    }
}
