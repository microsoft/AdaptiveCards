using AdaptiveCards.Rendering.Uwp;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;
using AdaptiveCardVisualizer.Helpers;
using Windows.Data.Json;

namespace AdaptiveCardVisualizer.ViewModel
{
    public class FrameEditorViewModel : GenericDocumentViewModel
    {
        private FrameEditorViewModel(MainPageViewModel mainPageViewModel) : base(mainPageViewModel) { }

        public event EventHandler<string> FrameChanged;

        public string Frame { get; private set; }

        protected override void LoadPayload(string payload)
        {
            try
            {
                var newFrame = payload;

                if (newFrame != null)
                {
                    Frame = newFrame;

                    FrameChanged?.Invoke(this, Frame);

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

        public static async Task<FrameEditorViewModel> LoadAsync(MainPageViewModel mainPageViewModel)
        {
            try
            {
                StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(new Uri("ms-appx:///HostConfigs/DefaultFrame.json"));
                string text = await FileIO.ReadTextAsync(file);

                return new FrameEditorViewModel(mainPageViewModel)
                {
                    Payload = text
                };
            }
            catch
            {
                return new FrameEditorViewModel(mainPageViewModel);
            }
        }
    }
}
