using AdaptiveCardTestApp.ViewModels;
using System;
using System.Collections;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using UWPTestLibrary;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
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

        protected override async void OnNavigatedTo(NavigationEventArgs e)
        {
            var runningTestsViewModel = e.Parameter as RunningTestsViewModel;
            if (runningTestsViewModel == null)
            {
                throw new InvalidOperationException("Running tests view model not provided");
            }

            // Force a Garbage Collection to make sure that the WeakReferences as invalidated.
            GC.Collect(GC.MaxGeneration, GCCollectionMode.Default, blocking: true);
            await System.Threading.Tasks.Task.Delay(1000);

            var model = new TestResultsViewModel(runningTestsViewModel.Results);
            DataContext = model;

            ListViewCategories.ItemsSource = new TestResultsCategoryViewModel[]
            {
                model.Passed,
                model.Failed,
                model.JsonFailed,
                model.ImageAndJsonFailed,
                model.FailedButSourceWasChanged,
                model.PassedButSourceWasChanged,
                model.Leaked,
                model.New,
            };

            if (model.Failed.Results.Count > 0)
            {
                ListViewCategories.SelectedItem = model.Failed;
            }

            else if (model.JsonFailed.Results.Count > 0)
            {
                ListViewCategories.SelectedItem = model.JsonFailed;
            }

            else if (model.ImageAndJsonFailed.Results.Count > 0)
            {
                ListViewCategories.SelectedItem = model.ImageAndJsonFailed;
            }

            else if (model.FailedButSourceWasChanged.Results.Count > 0)
            {
                ListViewCategories.SelectedItem = model.FailedButSourceWasChanged;
            }

            else if (model.PassedButSourceWasChanged.Results.Count > 0)
            {
                ListViewCategories.SelectedItem = model.PassedButSourceWasChanged;
            }

            else if (model.Leaked.Results.Count > 0)
            {
                ListViewCategories.SelectedItem = model.Leaked;
            }

            else if (model.New.Results.Count > 0)
            {
                ListViewCategories.SelectedItem = model.New;
            }

            else
            {
                ListViewCategories.SelectedItem = model.Passed;
            }

            base.OnNavigatedTo(e);
        }

        private void ListViewCategories_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var model = DataContext as TestResultsViewModel;
            ButtonAcceptAll.Visibility = Visibility.Visible;

            var category = ListViewCategories.SelectedItem as TestResultsCategoryViewModel;

            ListViewResults.ItemsSource = category?.Results;
            ButtonAcceptAll.Visibility = (category == model.Passed) ? Visibility.Collapsed : Visibility.Visible;
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
