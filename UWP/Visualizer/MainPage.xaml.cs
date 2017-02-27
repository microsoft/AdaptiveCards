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

using AdaptiveCards.XamlCardRenderer;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace XamlCardVisualizer
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            // Construct a temporary object model tree until the parser is available
            AdaptiveCard card = new AdaptiveCard();
            AdaptiveContainer container1 = new AdaptiveContainer();

            AdaptiveTextBlock textBlock1 = new AdaptiveTextBlock();
            textBlock1.Text = "Hello";
            textBlock1.Size = CardElementSize.Medium;
            textBlock1.TextWeight = TextWeight.Normal;
            textBlock1.TextColor = TextColor.Default;
            container1.Items.Add(textBlock1);
            AdaptiveTextBlock textBlock2 = new AdaptiveTextBlock();
            textBlock2.Text = "World";
            textBlock2.Size = CardElementSize.Medium;
            textBlock2.TextWeight = TextWeight.Normal;
            textBlock2.TextColor = TextColor.Accent;
            container1.Items.Add(textBlock2);

            card.Items.Add(container1);

            AdaptiveContainer container2 = new AdaptiveContainer();
            container2.StartGroup = true;

            AdaptiveTextBlock textBlock3 = new AdaptiveTextBlock();
            textBlock3.Text = "In new container";
            textBlock3.Size = CardElementSize.Medium;
            textBlock3.TextWeight = TextWeight.Normal;
            textBlock3.TextColor = TextColor.Default;
            container2.Items.Add(textBlock3);

            card.Items.Add(container2);

            AdaptiveImage image = new AdaptiveImage();
            image.Uri = new Uri("https://docs.microsoft.com/en-us/_themes/images/microsoft-header.png");
            card.Items.Add(image);

            m_renderer = new AdaptiveCards.XamlCardRenderer.XamlCardRenderer();

            PopulateXamlContent(card);
            PopulateImageContent(card);
        }

        private async void PopulateXamlContent(AdaptiveCard card)
        {
            renderedXamlPresenter.Content = await m_renderer.RenderCardAsXamlAsync(card);
        }

        private async void PopulateImageContent(AdaptiveCard card)
        {
            ImageRenderResult imageRenderResult = await m_renderer.RenderCardAsImageAsync(card);
        }

        private async void loadFileButton_Clicked(object sender, RoutedEventArgs args)
        {
            FileOpenPicker openPicker = new FileOpenPicker();
            openPicker.ViewMode = PickerViewMode.List;
            openPicker.FileTypeFilter.Add(".json");

            StorageFile file = await openPicker.PickSingleFileAsync();
            if (file != null)
            {
                this.adaptiveJson.Document.SetText(Windows.UI.Text.TextSetOptions.None, await FileIO.ReadTextAsync(file));
            }
            else
            {
            }
        }

        private async void generateButton_Clicked(object sender, RoutedEventArgs args)
        {
            renderedXamlPresenter.Content = null;

            string adaptiveJsonText;
            this.adaptiveJson.Document.GetText(Windows.UI.Text.TextGetOptions.None, out adaptiveJsonText);

            try
            {
                renderedXamlPresenter.Content = await m_renderer.RenderAdaptiveJsonAsXamlAsync(adaptiveJsonText);
            }
            catch (Exception)
            {
                GenerateErrorUI();
            }
            //ImageRenderResult imageRenderResult = await m_renderer.RenderCardAsImageAsync(card);
        }

        private void GenerateErrorUI()
        {
            Grid errorGrid = new Grid();
            TextBlock errorText = new TextBlock();
            errorText.Text = "An error occurred attempting to generate a visual from this Json";
            errorGrid.Children.Add(errorText);
            renderedXamlPresenter.Content = errorGrid;
        }

        private AdaptiveCards.XamlCardRenderer.XamlCardRenderer m_renderer;
    }
}
