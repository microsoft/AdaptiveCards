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
            AppBarHostConfigEditor.IsChecked = false;
            SetIsInHostConfigEditor(false);
        }

        private void AppBarFrameEditor_Click(object sender, RoutedEventArgs e)
        {
            SetIsInFrameEditor(!IsInFrameEditor);
        }

        public bool IsInFrameEditor { get; private set; }

        private void SetIsInFrameEditor(bool isInFrameEditor)
        {
            IsInFrameEditor = isInFrameEditor;

            foreach (var button in StackPanelMainAppBarButtons.Children.OfType<ButtonBase>())
            {
                if (button != AppBarFrameEditor)
                {
                    button.IsEnabled = !isInFrameEditor;
                }
            }

            FrameEditorView.Visibility = isInFrameEditor ? Visibility.Visible : Visibility.Collapsed;
        }

        private void FrameTransparentBackdrop_Tapped(object sender, TappedRoutedEventArgs e)
        {
            AppBarFrameEditor.IsChecked = false;
            SetIsInFrameEditor(false);
        }

        private void AppBarRuntimeObjectEditor_Click(object sender, RoutedEventArgs e)
        {
            SetIsInRuntimeObjectEditor(!IsInRuntimeObjectEditor);
        }

        public bool IsInRuntimeObjectEditor { get; private set; }

        private void SetIsInRuntimeObjectEditor(bool isInRuntimeObjectEditor)
        {
            IsInRuntimeObjectEditor = isInRuntimeObjectEditor;

            foreach (var button in StackPanelMainAppBarButtons.Children.OfType<ButtonBase>())
            {
                if (button != AppBarRuntimeObjectEditor)
                {
                    button.IsEnabled = !isInRuntimeObjectEditor;
                }
            }

            RuntimeObjectEditorView.Visibility = isInRuntimeObjectEditor ? Visibility.Visible : Visibility.Collapsed;
        }

        private void RuntimeObjectTransparentBackdrop_Tapped(object sender, TappedRoutedEventArgs e)
        {
            AppBarRuntimeObjectEditor.IsChecked = false;
            SetIsInRuntimeObjectEditor(false);
        }
    }
}
