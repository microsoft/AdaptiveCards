// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

using AdaptiveCards.Rendering.Uwp;
using AdaptiveCardVisualizer.ViewModel;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace AdaptiveCardVisualizer
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPageViewModel ViewModel { get; set; }

        public MainPage()
        {
            this.InitializeComponent();

            Load();
        }

        private async void Load()
        {
            IsEnabled = false;

            ViewModel = await MainPageViewModel.LoadAsync();
            DataContext = ViewModel;

            IsEnabled = true;
        }

        private void loadFileButton_Clicked(object sender, RoutedEventArgs args)
        {
            ViewModel.OpenDocument();
        }

        private void ButtonNewCard_Click(object sender, RoutedEventArgs e)
        {
            ViewModel.NewDocument();
        }

        private void AppBarNew_Click(object sender, RoutedEventArgs e)
        {
            ViewModel.NewDocument();
        }

        private void AppBarOpen_Click(object sender, RoutedEventArgs e)
        {
            ViewModel.OpenDocument();
        }

        private async void AppBarSave_Click(object sender, RoutedEventArgs e)
        {
            if (ViewModel.CurrentDocument == null)
            {
                return;
            }

            IsEnabled = false;
            await ViewModel.CurrentDocument.SaveAsync();
            IsEnabled = true;
        }

        private void CommandBar_Opening(object sender, object e)
        {
            SetIsCompactOnAppBarButtons(false);
        }

        private void CommandBar_Closing(object sender, object e)
        {
            SetIsCompactOnAppBarButtons(true);
        }

        private void SetIsCompactOnAppBarButtons(bool isCompact)
        {
            foreach (var button in StackPanelMainAppBarButtons.Children.OfType<ICommandBarElement>())
            {
                button.IsCompact = isCompact;
            }
        }

        private void AppBarHostConfigEditor_Click(object sender, RoutedEventArgs e)
        {
            SetIsInHostConfigEditor(!IsInHostConfigEditor);
        }

        public bool IsInHostConfigEditor { get; private set; }

        private void SetIsInHostConfigEditor(bool isInHostConfigEditor)
        {
            IsInHostConfigEditor = isInHostConfigEditor;

            AdaptiveCardDocumentView.IsEnabled = !isInHostConfigEditor;

            foreach (var button in StackPanelMainAppBarButtons.Children.OfType<ButtonBase>())
            {
                if (button != AppBarHostConfigEditor)
                {
                    button.IsEnabled = !isInHostConfigEditor;
                }
            }

            HostConfigEditorView.Visibility = isInHostConfigEditor ? Visibility.Visible : Visibility.Collapsed;
        }

        private void HostConfigTransparentBackdrop_Tapped(object sender, TappedRoutedEventArgs e)
        {
            SetIsInHostConfigEditor(false);
        }

        private void CheckBox_Click(object sender, RoutedEventArgs e)
        {
            CheckBox checkBox = sender as CheckBox;
            ViewModel.InlineValidation = checkBox.IsChecked.HasValue && checkBox.IsChecked.Value;
        }
    }
}
