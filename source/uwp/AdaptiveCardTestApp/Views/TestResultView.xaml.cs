using AdaptiveCardTestApp.ViewModels;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;

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
        private async void TestResultView_DataContextChanged(FrameworkElement sender, DataContextChangedEventArgs args)
        {
            TestResultViewModel model = DataContext as TestResultViewModel;
            if (model != null)
            {
                _currModel = model;
                TextBlockError.Visibility = Visibility.Collapsed;
                ImageResult.Visibility = Visibility.Visible;

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
                        case TestStatus.FailedButSourceWasChanged:
                            ButtonSaveAsExpected.Content = "Accept new version";
                            break;

                        case TestStatus.Passed:
                            ButtonSaveAsExpected.Content = "Set as expected";
                            break;
                    }
                }

                if (model.Status != TestStatus.New && model.OldFile != null)
                {
                    var bmpExpected = new BitmapImage();
                    bmpExpected.ImageOpened += ExpectedImageResult_ImageOpened;
                    bmpExpected.ImageFailed += ExpectedImageResult_ImageFailed;
                    bmpExpected.SetSource(await model.OldFile.OpenAsync(FileAccessMode.Read));
                    ExpectedImageResult.Source = bmpExpected;
                }
                else
                {
                    ExpectedImageResult.Source = null;
                }

                var bmp = new BitmapImage();
                bmp.ImageOpened += ImageResult_ImageOpened;
                bmp.ImageFailed += ImageResult_ImageFailed;
                bmp.SetSource(await model.NewFile.OpenAsync(FileAccessMode.Read));
                ImageResult.Source = bmp;
            }
        }

        private async void ImageResult_ImageFailed(object sender, ExceptionRoutedEventArgs e)
        {
            if (_currModel == DataContext)
            {
                ImageResult.Visibility = Visibility.Collapsed;
                TextBlockError.Text = "";
                TextBlockError.Visibility = Visibility.Visible;
                try
                {
                    TextBlockError.Text = await FileIO.ReadTextAsync(_currModel.NewFile);
                }
                catch { }
            }
        }

        private void ExpectedImageResult_ImageOpened(object sender, RoutedEventArgs e)
        {
            ExpectedTextBlockError.Visibility = Visibility.Collapsed;
            ExpectedImageResult.Visibility = Visibility.Visible;
        }

        private async void ExpectedImageResult_ImageFailed(object sender, ExceptionRoutedEventArgs e)
        {
            if (_currModel == DataContext)
            {
                ExpectedImageResult.Visibility = Visibility.Collapsed;
                ExpectedTextBlockError.Text = "";
                ExpectedTextBlockError.Visibility = Visibility.Visible;
                try
                {
                    ExpectedTextBlockError.Text = await FileIO.ReadTextAsync(_currModel.NewFile);
                }
                catch { }
            }
        }

        private void ImageResult_ImageOpened(object sender, RoutedEventArgs e)
        {
            TextBlockError.Visibility = Visibility.Collapsed;
            ImageResult.Visibility = Visibility.Visible;
        }

        private async void ButtonSaveAsExpected_Click(object sender, RoutedEventArgs e)
        {
            base.IsEnabled = false;
            await (DataContext as TestResultViewModel).SaveAsNewExpectedAsync();
            base.IsEnabled = true;
        }
    }
}
