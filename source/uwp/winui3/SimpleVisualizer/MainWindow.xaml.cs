// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using Microsoft.UI.Xaml;
using System.IO;
using System.Text;
using Windows.ApplicationModel;

using AdaptiveCards.ObjectModel.WinUI3;
using Newtonsoft.Json;

using AdaptiveCardRenderer = AdaptiveCards.Rendering.WinUI3.AdaptiveCardRenderer;

namespace SimpleVisualizer
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        public MainWindow()
        {
            this.InitializeComponent();
        }

        private void ShowButton_Click(object sender, RoutedEventArgs e)
        {
            showButton.Visibility = Visibility.Collapsed;

            var jsonContents = ReadFile(Package.Current.InstalledLocation.Path, "WeatherLarge.json");
            var card = AdaptiveCard.FromJsonString(jsonContents);

            var renderer = new AdaptiveCardRenderer();
            // Render the card
            var renderedCard = renderer.RenderAdaptiveCard(card.AdaptiveCard);

            // Check if the render was successful
            if (renderedCard.FrameworkElement != null)
            {
                // Get the framework element
                var uiCard = renderedCard.FrameworkElement;

                // Add it to your UI
                stackPanel.Children.Add(uiCard);
            }
        }

        private static string ReadFile(string folderPath, string fileName)
        {
            var path = Path.Combine(folderPath, fileName);
            if (File.Exists(path))
            {
                var json = File.ReadAllText(path);
                return json;
            }

            return string.Empty;
        }
    }
}
