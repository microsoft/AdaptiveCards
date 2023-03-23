// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#if USE_WINUI3
using Microsoft.UI;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Automation;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Media;
using CommunityToolkit.WinUI.UI.Controls;
#else
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Automation;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Microsoft.Toolkit.Uwp.UI.Controls;
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

            // Create GridSplitter control in code behind instead of markup so we can use the 
            // correct namespace for the version of XAML we're compiling.
            var backgroundBrush = (SolidColorBrush)Resources["SystemControlBackgroundAccentBrush"];
            var gridSplitter = new GridSplitter
            {
                Width = 11,
                Background = backgroundBrush,
                GripperCursor = GridSplitter.GripperCursorType.Default,
                HorizontalAlignment = HorizontalAlignment.Left,
                ResizeDirection = GridSplitter.GridResizeDirection.Auto,
                ResizeBehavior = GridSplitter.GridResizeBehavior.BasedOnAlignment,
                CursorBehavior = GridSplitter.SplitterCursorBehavior.ChangeOnSplitterHover,
                GripperForeground = new SolidColorBrush(Colors.White)
            };
            AutomationProperties.SetName(gridSplitter, "Content splitter");

            GridSplitterPlaceholder.Children.Add(gridSplitter);
        }
    }
}
