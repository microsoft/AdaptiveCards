using AdaptiveCards.XamlCardRenderer;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using Windows.Storage;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using XamlCardVisualizer.Helpers;
using XamlCardVisualizer.ResourceResolvers;

namespace XamlCardVisualizer.ViewModel
{
    public class DocumentViewModel : BindableBase
    {
        private static XamlCardRenderer _renderer;

        public MainPageViewModel MainPageViewModel { get; private set; }
        public string Token { get; private set; }
        public IStorageFile File { get; private set; }

        private string _name = "Untitled";
        public string Name
        {
            get { return _name; }
            set { SetProperty(ref _name, value); }
        }

        private string _payload = "";
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

            ReRender();
        }

        public async void ReRender()
        {
            if (!IsRendering)
            {
                IsRendering = true;

                await Task.Delay(1000);

                IsRendering = false;
                NotifyPropertyChanged(DelayedUpdatePayload);
                Render();
            }
        }

        private bool _isRendering;
        /// <summary>
        /// Represents whether the system is delaying rendering. Views should indicate this.
        /// </summary>
        public bool IsRendering
        {
            get { return _isRendering; }
            private set { SetProperty(ref _isRendering, value); }
        }

        /// <summary>
        /// This property will be notified of changes on a delayed schedule, so that it's not
        /// changing every single time a character is typed. Views presenting 
        /// </summary>
        public string DelayedUpdatePayload
        {
            get { return Payload; }
        }

        private UIElement _renderedCard;
        public UIElement RenderedCard
        {
            get { return _renderedCard; }
            private set { SetProperty(ref _renderedCard, value); }
        }

        public ObservableCollection<ErrorViewModel> Errors { get; private set; } = new ObservableCollection<ErrorViewModel>();

        public static async Task<DocumentViewModel> LoadFromFileAsync(MainPageViewModel mainPageViewModel, IStorageFile file, string token)
        {
            return new DocumentViewModel()
            {
                MainPageViewModel = mainPageViewModel,
                Name = file.Name,
                Payload = await FileIO.ReadTextAsync(file),
                Token = token,
                File = file
            };
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

        private async void Render()
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

            var newErrors = await PayloadValidator.ValidateAsync(payload);
            if (newErrors.Any(i => i.Type == ErrorViewModelType.Error))
            {
                MakeErrorsLike(newErrors);
                return;
            }

            try
            {
                if (_renderer == null)
                {
                    InitializeRenderer();
                }
            }
            catch (Exception ex)
            {
                newErrors.Add(new ErrorViewModel()
                {
                    Message = "Initializing renderer error: " + ex.ToString(),
                    Type = ErrorViewModelType.Error
                });
                MakeErrorsLike(newErrors);
                return;
            }

            try
            {
                RenderedAdaptiveCard renderResult = _renderer.RenderAdaptiveCardFromJsonString(payload);
                if (renderResult.IsRenderedSuccessfully)
                {
                    RenderedCard = renderResult.FrameworkElement;
                    renderResult.Action += async (sender, e) =>
                    {
                        var m_actionDialog = new ContentDialog();

                        if (e.Action.ActionType == ActionType.ShowCard)
                        {
                            AdaptiveShowCardAction showCardAction = (AdaptiveShowCardAction)e.Action;
                            m_actionDialog.Content = await _renderer.RenderCardAsXamlAsync(showCardAction.Card);
                        }
                        else
                        {
                            m_actionDialog.Content = "We got an action!\n" + e.Action.ActionType + "\n" + e.Inputs.ToString();
                        }

                        m_actionDialog.PrimaryButtonText = "Close";

                        await m_actionDialog.ShowAsync();
                    };
                }
                else
                {
                    IList<string> renderingErrors = renderResult.Errors;
                    foreach (string error in renderingErrors)
                    {
                        newErrors.Add(new ErrorViewModel()
                        {
                            Message = error,
                            Type = ErrorViewModelType.Error
                        });
                    }

                }


                if (RenderedCard is FrameworkElement)
                {
                    (RenderedCard as FrameworkElement).VerticalAlignment = VerticalAlignment.Top;
                }
                MakeErrorsLike(newErrors);
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.ToString());
                newErrors.Add(new ErrorViewModel()
                {
                    Message = "Rendering failed",
                    Type = ErrorViewModelType.Error
                });
                MakeErrorsLike(newErrors);
            }
        }

        private void SetSingleError(ErrorViewModel error)
        {
            MakeErrorsLike(new List<ErrorViewModel>() { error });
        }

        private void MakeErrorsLike(List<ErrorViewModel> errors)
        {
            errors.Sort();
            Errors.MakeListLike(errors);
        }

        private static void InitializeRenderer()
        {
            try
            {
                _renderer = new XamlCardRenderer();
                //_renderer.SetHostConfig

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
    }
}
