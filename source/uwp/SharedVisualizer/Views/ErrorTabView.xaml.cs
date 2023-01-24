// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#if !USE_WINUI3
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
#endif

// The User Control item template is documented at https://go.microsoft.com/fwlink/?LinkId=234236

namespace AdaptiveCardVisualizer
{
    public sealed partial class ErrorTabView : UserControl
    {
        public ErrorTabView()
        {
            this.InitializeComponent();
            this.Loaded += ErrorTabView_Loaded;
        }

        private void ErrorTabView_Loaded(object sender, RoutedEventArgs e)
        {
            Focus(FocusState.Keyboard);
        }
    }
}
