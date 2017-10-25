using AdaptiveCardTestApp.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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

        protected abstract Task<BaseViewModel> InitializeViewModel();
    }
}
