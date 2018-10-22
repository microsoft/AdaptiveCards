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
    public class RuntimeObjectEditorViewModel : GenericDocumentViewModel
    {
        private RuntimeObjectEditorViewModel(MainPageViewModel mainPageViewModel) : base(mainPageViewModel) { }

        public event EventHandler<string> RuntimeObjectChanged;

        public string RuntimeObject { get; private set; }

        protected override void LoadPayload(string payload)
        {
            try
            {
                var newRuntimeObject = payload;

                if (newRuntimeObject != null)
                {
                    RuntimeObject = newRuntimeObject;

                    RuntimeObjectChanged?.Invoke(this, RuntimeObject);

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

        public static async Task<RuntimeObjectEditorViewModel> LoadAsync(MainPageViewModel mainPageViewModel)
        {
            try
            {
                StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(new Uri("ms-appx:///HostConfigs/DefaultRuntimeObject.json"));
                string text = await FileIO.ReadTextAsync(file);

                return new RuntimeObjectEditorViewModel(mainPageViewModel)
                {
                    Payload = text
                };
            }
            catch
            {
                return new RuntimeObjectEditorViewModel(mainPageViewModel);
            }
        }
    }
}
