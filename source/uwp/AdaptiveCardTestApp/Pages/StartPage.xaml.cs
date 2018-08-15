using AdaptiveCardTestApp.ViewModels;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using System.Threading.Tasks;
using Windows.UI.Popups;
using Windows.Storage.Pickers;
using Windows.Graphics.Display;
using Windows.Storage.AccessCache;
using Windows.Storage;
using UWPTestLibrary;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace AdaptiveCardTestApp.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class StartPage : BasePage
    {
        public StartViewModel ViewModel => this.DataContext as StartViewModel;

        public StartPage()
        {
            this.InitializeComponent();
        }

        protected override async Task<BindableBase> InitializeViewModel()
        {
            var viewModel = new StartViewModel();
            await viewModel.LoadAsync();
            return viewModel;
        }

        protected override void OnViewModelLoaded()
        {
            ListViewCards.SelectAll();
            ListViewHostConfigs.SelectAll();

            base.OnViewModelLoaded();
        }

        private async void ButtonStartTest_Click(object sender, RoutedEventArgs e)
        {
            if (DisplayInformation.GetForCurrentView().RawPixelsPerViewPixel != 1)
            {
                var dontWait = new MessageDialog($"You must run these tests on a monitor that is using 100% scale factor (yours appears to be {DisplayInformation.GetForCurrentView().RawPixelsPerViewPixel * 100}%). Otherwise the XAML and images are rendered at a higher resolution and will not match the current Expected image results.").ShowAsync();
                return;
            }

            MakeSelectedLike(ViewModel.SelectedCards, ListViewCards);
            MakeSelectedLike(ViewModel.SelectedHostConfigs, ListViewHostConfigs);

            Frame.Navigate(typeof(RunningTestsPage), ViewModel);
        }

        private void MakeSelectedLike(IList<FileViewModel> viewModelList, ListView listView)
        {
            viewModelList.Clear();
            foreach (var selected in listView.SelectedItems.OfType<FileViewModel>())
            {
                viewModelList.Add(selected);
            }
        }

        private void TimelineCheckBox_Checked(object sender, RoutedEventArgs e)
        {
            ViewModel.AddToTimeline = (TimelineCheckBox.IsChecked == true);
        }
    }
}
