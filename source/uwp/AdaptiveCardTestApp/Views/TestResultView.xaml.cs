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
                        case TestStatus.FailedButSourceWasChanged:
                            ButtonSaveAsExpected.Content = "Accept new version";
                            break;

                        case TestStatus.Passed:
                            ButtonSaveAsExpected.Content = "Set as expected";
                            break;
                    }
                }
            }
        }

        private async void ButtonSaveAsExpected_Click(object sender, RoutedEventArgs e)
        {
            base.IsEnabled = false;
            await (DataContext as TestResultViewModel).SaveAsNewExpectedAsync();
            base.IsEnabled = true;
        }
    }
}
