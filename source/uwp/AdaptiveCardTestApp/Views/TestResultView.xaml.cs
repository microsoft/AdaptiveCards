// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using UWPTestLibrary;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

// The User Control item template is documented at https://go.microsoft.com/fwlink/?LinkId=234236

namespace AdaptiveCardTestApp.Views
{
    public sealed partial class TestResultView : UserControl
    {
        public TestResultView()
        {
            this.InitializeComponent();

            DataContextChanged += TestResultView_DataContextChanged;
        }

        private TestResultViewModel _currModel;
        private void TestResultView_DataContextChanged(FrameworkElement sender, DataContextChangedEventArgs args)
        {
            TestResultViewModel model = DataContext as TestResultViewModel;
            if (model != null)
            {
                _currModel = model;

                if (model.Status == TestStatus.Passed)
                {
                    ButtonSaveAsExpected.Visibility = Visibility.Collapsed;
                }
                else
                {
                    ButtonSaveAsExpected.Visibility = Visibility.Visible;

                    switch (model.Status)
                    {
                        case TestStatus.Failed:
                        case TestStatus.JsonFailed:
                        case TestStatus.ImageAndJsonFailed:
                        case TestStatus.FailedButSourceWasChanged:
                            ButtonSaveAsExpected.Content = "Accept new version";
                            break;

                        case TestStatus.PassedButSourceWasChanged:
                            ButtonSaveAsExpected.Content = "Accept new source";
                            break;

                        case TestStatus.Passed:
                            ButtonSaveAsExpected.Content = "Set as expected";
                            break;
                    }
                }

                ButtonCompareCard.Visibility = model.DidCardPayloadChange ? Visibility.Visible : Visibility.Collapsed;
                ButtonCompareHostConfig.Visibility = model.DidHostConfigChange ? Visibility.Visible : Visibility.Collapsed;
                ButtonRoundTrippedJson.Visibility = model.DidRoundtrippedJsonChange ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        private async void ButtonSaveAsExpected_Click(object sender, RoutedEventArgs e)
        {
            base.IsEnabled = false;
            await (DataContext as TestResultViewModel).SaveAsNewExpectedAsync();
            base.IsEnabled = true;
        }

        private async void ButtonCompareCard_Click(object sender, RoutedEventArgs e)
        {
            TestResultViewModel model = DataContext as TestResultViewModel;
            if (model != null)
            {
                ShowComparison(await model.GetOldCardContentsAsync(), model.CardFile.Contents);
            }
        }

        private async void ButtonCompareHostConfig_Click(object sender, RoutedEventArgs e)
        {
            TestResultViewModel model = DataContext as TestResultViewModel;
            if (model != null)
            {
                ShowComparison(await model.GetOldHostConfigContentsAsync(), model.HostConfigFile.Contents);
            }
        }
        private async void ButtonRoundTrippedJson_Click(object sender, RoutedEventArgs e)
        {
            TestResultViewModel model = DataContext as TestResultViewModel;
            if (model != null)
            {
                ShowComparison(model.ExpectedRoundtrippedJsonModel.Contents, model.RoundtrippedJsonModel.Contents);
            }
        }

        private void ShowComparison(string oldText, string newText)
        {
            var diffView = new DiffView();
            diffView.FontFamily = new Windows.UI.Xaml.Media.FontFamily("Consolas");
            diffView.ShowDiff(oldText, newText);

            var dontWait = new ContentDialog()
            {
                Content = diffView,
                PrimaryButtonText = "Close",
                MinWidth = this.ActualWidth,
                MaxWidth = this.ActualWidth
            }.ShowAsync();
        }
    }
}
