using AdaptiveCardTestApp.ViewModels;
using System;
using System.Collections;
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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace AdaptiveCardTestApp.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class TestResultsPage : Page
    {
        public TestResultsPage()
        {
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            var runningTestsViewModel = e.Parameter as RunningTestsViewModel;
            if (runningTestsViewModel == null)
            {
                throw new InvalidOperationException("Running tests view model not provided");
            }

            var model = new TestResultsViewModel(runningTestsViewModel.Results);
            DataContext = model;

            ListViewCategories.ItemsSource = new string[]
            {
                "Passed",
                "Failed",
                "New"
            };

            if (model.Failed.Count > 0)
            {
                ListViewCategories.SelectedIndex = 1;
            }
            else if (model.New.Count > 0)
            {
                ListViewCategories.SelectedIndex = 2;
            }
            else
            {
                ListViewCategories.SelectedIndex = 0;
            }

            base.OnNavigatedTo(e);
        }

        private void ListViewCategories_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var model = DataContext as TestResultsViewModel;

            switch (ListViewCategories.SelectedIndex)
            {
                case 0:
                    ListViewResults.ItemsSource = model.Passed;
                    break;

                case 1:
                    ListViewResults.ItemsSource = model.Failed;
                    break;

                case 2:
                    ListViewResults.ItemsSource = model.New;
                    break;
            }
        }

        private async void ButtonAcceptAll_Click(object sender, RoutedEventArgs e)
        {
            foreach (var item in ((ListViewResults.ItemsSource as IEnumerable).OfType<TestResultViewModel>()).ToArray())
            {
                await item.SaveAsNewExpectedAsync();
            }
        }
    }
}
