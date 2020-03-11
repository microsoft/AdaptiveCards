// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
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
using AdaptiveCardVisualizer.ViewModel;

// The User Control item template is documented at https://go.microsoft.com/fwlink/?LinkId=234236

namespace AdaptiveCardVisualizer
{
    public sealed partial class TabView : UserControl
    {
        public DocumentViewModel ViewModel
        {
            get { return DataContext as DocumentViewModel; }
        }

        public TabView()
        {
            this.InitializeComponent();
        }

        private void ButtonClose_Click(object sender, RoutedEventArgs e)
        {
            if (ViewModel != null)
            {
                ViewModel.MainPageViewModel.CloseDocument(ViewModel);
            }
        }

        private void OnPointerEntered()
        {
        }

        private void OnPointerExited()
        {
        }

        private void Grid_PointerEntered(object sender, PointerRoutedEventArgs e)
        {
            OnPointerEntered();
        }

        private void Grid_PointerCaptureLost(object sender, PointerRoutedEventArgs e)
        {
            OnPointerExited();
        }

        private void Grid_PointerCanceled(object sender, PointerRoutedEventArgs e)
        {
            OnPointerExited();
        }

        private void Grid_PointerExited(object sender, PointerRoutedEventArgs e)
        {
            OnPointerExited();
        }
    }
}
