using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using System.Diagnostics;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using Windows.Data.Json;

using AdaptiveCards.Rendering.Uwp;
using AdaptiveCards.Rendering.UWP.Helpers;
using AdaptiveCards.Rendering.UWP.ResourceResolvers;
using Windows.UI.Xaml.Controls;

namespace AdaptiveCards.Rendering.UWP.ViewModel
{
    public class AdaptiveCardViewModel : BindableBase
    {
        public MainPageViewModel MainPageViewModel { get; private set; }
        public bool IsOutdated { get; set; } = true;
        protected string m_payload = "";
        public string Payload
        {
            get { return m_payload; }
            set { SetPayload(value); }
        }
        private bool m_isLoading;
        /// <summary>
        /// Represents whether the system is delaying loading. Views should indicate this.
        /// </summary>
        public bool IsLoading
        {
            get { return m_isLoading; }
            private set { SetProperty(ref m_isLoading, value); }
        }

        private AdaptiveHostConfig m_hostConfig = null;
        private static AdaptiveCardRenderer _renderer;
        private UIElement _renderedCard;
        public UIElement RenderedCard
        {
            get { return _renderedCard; }
            private set { SetProperty(ref _renderedCard, value); }
        }

        public AdaptiveCardViewModel(MainPageViewModel model)
        {
            MainPageViewModel = model;
            Reload();
        }

        public static void InitializeRenderer(AdaptiveHostConfig hostConfig)
        {
            try
            {
                _renderer = new AdaptiveCardRenderer();
                if (hostConfig != null)
                {
                    _renderer.HostConfig = hostConfig;
                }

                // Custom resource resolvers
                _renderer.ResourceResolvers.Set("symbol", new MySymbolResourceResolver());
            }
            catch
            {
                if (Debugger.IsAttached)
                {
                    Debugger.Break();
                }
                throw;
            }
        }

        private void SetPayload(string value)
        {
            if (value == null)
            {
                throw new ArgumentNullException(nameof(value));
            }

            if (object.Equals(m_payload, value))
            {
                return;
            }

            SetProperty(ref m_payload, value);

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

                NotifyPropertyChanged(Payload);
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

        private void Load()
        {
            if (string.IsNullOrWhiteSpace(Payload))
            {
                return;
            }

            try
            {
                LoadPayload(Payload);
            }
            catch (Exception ex)
            {
            }

            IsOutdated = false;
        }

        public async void LoadPayload(string payload)
        {
            PayloadValidator.ValidateAsync(payload);

            try
            {
                if (_renderer == null)
                {
                    string hostConfigPaylaod = await ReadHostConfig();
                    m_hostConfig = AdaptiveHostConfig.FromJsonString(hostConfigPaylaod).HostConfig;
                    InitializeRenderer(m_hostConfig);
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.ToString());
                return;
            }

            try
            {
                JsonObject jsonObject;
                if (JsonObject.TryParse(payload, out jsonObject))
                {
                    RenderedAdaptiveCard renderResult = _renderer.RenderAdaptiveCardFromJson(jsonObject);
                    if (renderResult.FrameworkElement != null)
                    {
                        RenderedCard = renderResult.FrameworkElement;
                        renderResult.Action += async (sender, e) =>
                        {
                            var m_actionDialog = new ContentDialog();

                            if (e.Action.ActionType == ActionType.ShowCard)
                            {
                                AdaptiveShowCardAction showCardAction = (AdaptiveShowCardAction)e.Action;
                                RenderedAdaptiveCard renderedShowCard = _renderer.RenderAdaptiveCard(showCardAction.Card);
                                if (renderedShowCard.FrameworkElement != null)
                                {
                                    m_actionDialog.Content = renderedShowCard.FrameworkElement;
                                }
                            }
                            else
                            {
                                m_actionDialog.Content = SerializeActionEventArgsToString(e);
                            }

                            m_actionDialog.PrimaryButtonText = "Close";

                            await m_actionDialog.ShowAsync();
                        };
                    }
                }

                if (RenderedCard is FrameworkElement)
                {
                    (RenderedCard as FrameworkElement).VerticalAlignment = VerticalAlignment.Top;
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.ToString());
            }
        }

        public string SerializeActionEventArgsToString(AdaptiveActionEventArgs args)
        {
            string answer = "Action invoked!\nType: " + args.Action.ActionType;

            if (args.Action is AdaptiveSubmitAction)
            {
                answer += "\nData: " + (args.Action as AdaptiveSubmitAction).DataJson.Stringify();
            }
            else if (args.Action is AdaptiveOpenUrlAction)
            {
                answer += "\nUrl: " + (args.Action as AdaptiveOpenUrlAction).Url;
            }

            answer += "\nInputs: " + args.Inputs.AsJson().Stringify();
            return answer;
        }

        private async Task<string> ReadHostConfig()
        {
            try
            {
                StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(new Uri("ms-appx:///HostConfigs/DefaultHostConfig.json"));
                string text = await FileIO.ReadTextAsync(file);
                return text;
            }
            catch
            {
                return "";
            }
        }
    }
}

