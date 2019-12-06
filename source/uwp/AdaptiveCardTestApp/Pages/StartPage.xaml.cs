// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCardTestApp.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using UWPTestLibrary;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.Graphics.Display;
using Windows.Storage;
using Windows.Storage.AccessCache;
using Windows.Storage.Pickers;

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
            if (ListViewCards.SelectedItems.Count == 0 || ListViewHostConfigs.SelectedItems.Count == 0)
            {
                return;
            }

            if (DisplayInformation.GetForCurrentView().RawPixelsPerViewPixel != 1)
            {
                var dontWait = new MessageDialog($"You must run these tests on a monitor that is using 100% scale factor (yours appears to be {DisplayInformation.GetForCurrentView().RawPixelsPerViewPixel * 100}%). Otherwise the XAML and images are rendered at a higher resolution and will not match the current Expected image results.");
                dontWait.Commands.Clear();
                dontWait.Commands.Add(new UICommand($"Run anyway"));
                dontWait.Commands.Add(new UICommand($"Cancel"));
                dontWait.CancelCommandIndex = 1;
                dontWait.DefaultCommandIndex = 1;
                var result = await dontWait.ShowAsync();
                if (result.Label == $"Cancel")
                {
                    return;
                }
            }

            MakeSelectedLike(ViewModel.SelectedCards, ListViewCards);
            MakeSelectedLike(ViewModel.SelectedHostConfigs, ListViewHostConfigs);

            StorageFolder folder = null;
            try
            {
                folder = await StorageApplicationPermissions.FutureAccessList.GetFolderAsync("Expected");
            }
            catch { }

            if (folder == null)
            {
                var dialog = new MessageDialog("Please select the folder that contains the Expected render results (located in the project folder). ");
                dialog.Commands.Add(new UICommand("Pick Expected folder"));
                dialog.Commands.Add(new UICommand("Cancel"));
                dialog.DefaultCommandIndex = 0;
                dialog.CancelCommandIndex = 1;

                var cmd = await dialog.ShowAsync();
                if (cmd == dialog.Commands[0])
                {
                    FolderPicker folderPicker = new FolderPicker();
                    folderPicker.FileTypeFilter.Add("*");
                    folderPicker.CommitButtonText = "Pick folder";
                    folderPicker.ViewMode = PickerViewMode.List;

                    folder = await folderPicker.PickSingleFolderAsync();
                    if (folder != null)
                    {
                        StorageApplicationPermissions.FutureAccessList.AddOrReplace("Expected", folder);
                    }
                }
            }

            if (folder != null)
            {
                ViewModel.ExpectedFolder = folder;
                Frame.Navigate(typeof(RunningTestsPage), ViewModel);
            }
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

        private bool lastSelectedAllCards = true;

        private void CardButton_Click(object sender, RoutedEventArgs e)
        {
            if (lastSelectedAllCards)
            {
                foreach (var range in ListViewCards.SelectedRanges)
                {
                    ListViewCards.DeselectRange(range);
                }
            }
            else
            {
                ListViewCards.SelectAll();
            }
            lastSelectedAllCards = !lastSelectedAllCards;
        }

        private bool lastSelectedAllHosts = true;
        private void HostButton_Click(object sender, RoutedEventArgs e)
        {
            if (lastSelectedAllHosts)
            {
                foreach (var range in ListViewHostConfigs.SelectedRanges)
                {
                    ListViewHostConfigs.DeselectRange(range);
                }
            }
            else
            {
                ListViewHostConfigs.SelectAll();
            }
            lastSelectedAllHosts = !lastSelectedAllHosts;
        }
    }
}
