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

                ButtonUpdateImage.Visibility = Visibility.Collapsed;
                ButtonUpdateJson.Visibility = Visibility.Collapsed;
                ButtonUpdateOriginals.Visibility = Visibility.Collapsed;
                ButtonUpdateAll.Visibility = Visibility.Collapsed;

                if (model.Status.NewCard)
                {
                    // For a new card, only let them update "all"
                    ButtonUpdateAll.Visibility = Visibility.Visible;

                }
                else if (model.Status.MatchedViaError)
                {
                    // If they matched via error nothing to update except possibly the original
                    ButtonUpdateOriginals.Visibility = model.Status.OriginalMatched ? Visibility.Collapsed : Visibility.Visible;
                }
                else
                {
                    // Provide the appropriate buttons to update as needed
                    uint buttonsShown = 0;
                    if (!model.Status.ImageMatched)
                    {
                        ButtonUpdateImage.Visibility = Visibility.Visible;
                        buttonsShown++;
                    }
                    if (!model.Status.JsonRoundTripMatched)
                    {
                        ButtonUpdateJson.Visibility = Visibility.Visible;
                        buttonsShown++;
                    }
                    if (!model.Status.OriginalMatched)
                    {
                        ButtonUpdateOriginals.Visibility = Visibility.Visible;
                        buttonsShown++;
                    }

                    // Only show the update all button if we have more than one thing to update
                    if (buttonsShown > 1)
                    {
                        ButtonUpdateAll.Visibility = Visibility.Visible;
                    }
                }

                ButtonCompareCard.Visibility = model.DidCardPayloadChange ? Visibility.Visible : Visibility.Collapsed;
                ButtonCompareHostConfig.Visibility = model.DidHostConfigChange ? Visibility.Visible : Visibility.Collapsed;
                ButtonRoundTrippedJson.Visibility = model.DidRoundtrippedJsonChange ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        private async void ButtonSaveAsExpected_Click(object sender, RoutedEventArgs e)
        {
            bool updateOriginals = false;
            bool updateImage = false;
            bool updateJson = false;

            Button buttonSender = sender as Button;
            if (buttonSender == ButtonUpdateOriginals)
            {
                updateOriginals = true;
            }
            else if (buttonSender == ButtonUpdateJson)
            {
                updateJson = true;
            }
            else if (buttonSender == ButtonUpdateImage)
            {
                updateImage = true;
            }
            else if (buttonSender == ButtonUpdateAll)
            {
                updateOriginals = updateJson = updateImage = true;
            }

            base.IsEnabled = false;
            await (DataContext as TestResultViewModel).SaveAsNewExpectedAsync(updateOriginals, updateJson, updateImage);
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
