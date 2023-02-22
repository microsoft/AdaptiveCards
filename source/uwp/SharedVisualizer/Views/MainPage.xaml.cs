// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCardVisualizer.ViewModel;
using System.Linq;
using Windows.System;

#if !USE_WINUI3
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Input;
#endif

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
            SetKeyboardAcceleratorForSettingsButton();

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

        /*
         * We need to set KeyboardAccelerator for Settings button in code behind
         * because virtual key for "comma" doesn't exist in the Windows.System.VirtualKey enum
         * and we're not able to assign this shortcut in the markup.
        */
        private void SetKeyboardAcceleratorForSettingsButton()
        {
            KeyboardAccelerator accelerator = new KeyboardAccelerator
            {
                Key = (Windows.System.VirtualKey)188, // 188 is VK_OEM_COMMA which doesn't exist in enum
                Modifiers = VirtualKeyModifiers.Control
            };
            AppBarHostConfigEditor.KeyboardAccelerators.Add(accelerator);
        }
    }
}
