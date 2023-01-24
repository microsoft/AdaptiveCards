// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#if !USE_WINUI3
using Windows.UI.Xaml.Controls;
#endif
using AdaptiveCardVisualizer.ViewModel;

// The User Control item template is documented at https://go.microsoft.com/fwlink/?LinkId=234236

namespace AdaptiveCardVisualizer
{
    public sealed partial class DocumentView : UserControl
    {
        public DocumentViewModel ViewModel
        {
            get { return DataContext as DocumentViewModel; }
        }

        public DocumentView()
        {
            this.InitializeComponent();
        }
    }
}
