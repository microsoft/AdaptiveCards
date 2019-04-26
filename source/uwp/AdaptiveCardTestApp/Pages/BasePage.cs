// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Threading.Tasks;
using UWPTestLibrary;
using Windows.UI.Xaml.Controls;

namespace AdaptiveCardTestApp.Pages
{
    public abstract class BasePage : Page
    {
        public BasePage()
        {
            LoadViewModel();
        }

        private async void LoadViewModel()
        {
            base.IsEnabled = false;

            DataContext = await InitializeViewModel();
            OnViewModelLoaded();

            base.IsEnabled = true;
        }

        protected virtual void OnViewModelLoaded() { }

        protected abstract Task<BindableBase> InitializeViewModel();
    }
}
