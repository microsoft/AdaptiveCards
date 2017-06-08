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
        //Use Literal Host Config String while Visualizer is updated with HostConfig Panel
        const string hostConfigString = @"{
                ""fontSizes"": {
                    ""small"": 10,
                    ""normal"" : 20,
                    ""medium"" : 30,
                    ""large"" : 40,
                    ""extraLarge"" : 50
                },
                ""colors"": {
                    ""default"": {
                        ""normal"": ""#FF000000"",
                        ""subtle"" : ""#b2000000""
                        },
                    ""accent"" : {
                        ""normal"": ""#FF0000FF"",
                        ""subtle"" : ""#b20000FF""
                        },
                    ""dark"" : {
                        ""normal"": ""#FF101010"",
                        ""subtle"" : ""#b2101010""
                        },
                        ""light"" : {
                            ""normal"": ""#FFFFFFFF"",
                            ""subtle"" : ""#b2FFFFFF""
                        },
                        ""good"" : {
                            ""normal"": ""#FF008000"",
                            ""subtle"" : ""#b2008000""
                            },
                        ""warning"" : {
                            ""normal"": ""#FFFFD700"",
                            ""subtle"" : ""#b2FFD700""
                        },
                        ""attention"" : {
                        ""normal"": ""#FF8B0000"",
                        ""subtle"" : ""#b28B0000""
                        }}
                }";

        public MainPage()
        {


            this.InitializeComponent();
            // Construct a temporary object model tree until the parser is available
            AdaptiveCard card = new AdaptiveCard();
            AdaptiveContainer container1 = new AdaptiveContainer();

            AdaptiveTextBlock textBlock1 = new AdaptiveTextBlock();
            textBlock1.Text = "Hello";
            textBlock1.Weight = TextWeight.Normal;
            textBlock1.Color = TextColor.Warning;
            textBlock1.Size = TextSize.Large;
            container1.Items.Add(textBlock1);
            AdaptiveTextBlock textBlock2 = new AdaptiveTextBlock();
            textBlock2.Text = "World";
            textBlock2.Weight = TextWeight.Normal;
            textBlock2.Color = TextColor.Accent;
            container1.Items.Add(textBlock2);

            card.Body.Add(container1);

            AdaptiveContainer container2 = new AdaptiveContainer();

            AdaptiveTextBlock textBlock3 = new AdaptiveTextBlock();
            textBlock3.Text = "In new container";
            textBlock3.Weight = TextWeight.Normal;
            textBlock3.Color = TextColor.Default;
            container2.Items.Add(textBlock3);

            card.Body.Add(container2);

            AdaptiveImage image = new AdaptiveImage();
            image.Url = new Uri("https://unsplash.it/360/202?image=883");
            card.Body.Add(image);

            m_renderer = new AdaptiveCards.XamlCardRenderer.XamlCardRenderer();

            AdaptiveHostConfig hostConfig = AdaptiveHostConfig.CreateHostConfigFromJson(hostConfigString);
            m_renderer.SetHostConfig(hostConfig);

            m_renderer.Action += async (sender, e) =>
            {
                if (m_actionDialog != null)
                {
                    m_actionDialog.Hide();
                }

                m_actionDialog = new ContentDialog();

                if (e.Action.ActionType == ActionType.ShowCard)
                {
                    AdaptiveShowCardAction showCardAction = (AdaptiveShowCardAction)e.Action;
                    m_actionDialog.Content = await m_renderer.RenderCardAsXamlAsync(showCardAction.Card);
                }
                else
                {
                    m_actionDialog.Content = "We got an action!\n" + e.Action.ActionType + "\n" + e.Inputs;
                }

                m_actionDialog.PrimaryButtonText = "Close";

                await m_actionDialog.ShowAsync();
            };

            PopulateXamlContent(card);
        }

        private async void PopulateXamlContent(AdaptiveCard card)
        {
            renderedXamlPresenter.Content = await m_renderer.RenderCardAsXamlAsync(card);
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
        private ContentDialog m_actionDialog;
    }
}
