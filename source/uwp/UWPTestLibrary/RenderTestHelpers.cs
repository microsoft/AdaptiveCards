using AdaptiveCards.Rendering.Uwp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.Data.Json;
using Windows.Graphics.Imaging;
using Windows.Storage;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;

namespace UWPTestLibrary
{
    public class RenderTestHelpers
    {
        public static IEnumerable<UIElement> GetAllDescendants(UIElement element)
        {
            int count = VisualTreeHelper.GetChildrenCount(element);
            for (int i = 0; i < count; i++)
            {
                var child = VisualTreeHelper.GetChild(element, i) as UIElement;
                if (child != null)
                {
                    yield return child;

                    foreach (var descendant in GetAllDescendants(child))
                    {
                        yield return descendant;
                    }
                }
            }

            // Make sure contents of touch targets get walked, the VisualTreeHelper doesn't grab these
            if (element is ContentControl)
            {
                var content = (element as ContentControl).Content as UIElement;
                if (content != null)
                {
                    yield return content;

                    foreach (var descendant in GetAllDescendants(content))
                    {
                        yield return descendant;
                    }
                }
            }
        }

        public static async Task<Tuple<string, string, UIElement, double>> RenderCard(FileViewModel cardFile, FileViewModel hostConfigFile)
        {
            string error = null;
            string roundTrippedJsonString = null;
            FrameworkElement xaml = null;
            double cardWidth = 400;

            try
            {
                AdaptiveHostConfig hostConfig = AdaptiveHostConfig.FromJsonString(hostConfigFile.Contents).HostConfig;

                if (hostConfig == null)
                {
                    error = "Parsing hostConfig failed";
                }

                else
                {
                    JsonObject templatedJson = AdaptiveJsonTemplater.ApplyJsonTemplating(JsonObject.Parse(cardFile.Contents), null);

                    AdaptiveCard card = AdaptiveCard.FromJson(templatedJson).AdaptiveCard;

                    if (card == null)
                    {
                        error = "Parsing card failed";
                    }

                    else
                    {
                        roundTrippedJsonString = card.ToJson().ToString();
                        card = AdaptiveCard.FromJsonString(roundTrippedJsonString).AdaptiveCard;

                        var renderer = new AdaptiveCardRenderer()
                        {
                            HostConfig = hostConfig
                        };

                        if (hostConfigFile.Name.Contains("windows-timeline"))
                        {
                            renderer.SetFixedDimensions(320, 180);
                            cardWidth = 320;
                        }
                        else if (hostConfigFile.Name.Contains("windows-live-tile"))
                        {
                            renderer.SetFixedDimensions(310, 310);
                            cardWidth = 310;
                        }

                        xaml = renderer.RenderAdaptiveCard(card).FrameworkElement as FrameworkElement;

                        if (xaml == null)
                        {
                            error = "Rendering card failed";
                        }

                        else
                        {
                            xaml = new Border()
                            {
                                Background = new SolidColorBrush(Colors.White),
                                Child = xaml,
                                IsHitTestVisible = false // Disable HitTest so that mouse pointer can't accidently hover over a button
                            };

                            // The theme is important to set since it'll ensure buttons/inputs appear correctly
                            if (hostConfigFile.Name.Contains("windows-notification"))
                            {
                                xaml.RequestedTheme = ElementTheme.Dark;
                            }
                            else
                            {
                                xaml.RequestedTheme = ElementTheme.Light;
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                error = ex.ToString();
            }

            return new Tuple<string, string, UIElement, double>(error, roundTrippedJsonString, xaml, cardWidth);
        }

        public static async Task ResultsToFile(
            StorageFile imageResult,
            StorageFile jsonResult,
            string roundTrippedJsonString,
            UIElement xaml)
        {
            RenderTargetBitmap rtb = null;

            rtb = new RenderTargetBitmap();
            await rtb.RenderAsync(xaml);

            // https://basquang.wordpress.com/2013/09/26/windows-store-8-1-save-visual-element-to-bitmap-image-file/
            var buffer = await rtb.GetPixelsAsync();

            using (var stream = await imageResult.OpenAsync(FileAccessMode.ReadWrite))
            {
                var encoder = await BitmapEncoder.CreateAsync(BitmapEncoder.PngEncoderId, stream);

                encoder.SetPixelData(BitmapPixelFormat.Bgra8, BitmapAlphaMode.Straight, (uint)rtb.PixelWidth, (uint)rtb.PixelHeight, 96, 96, buffer.ToArray());

                // Set the size of the card so that it can be rendered just like the bitmap
                if (xaml is FrameworkElement fe)
                {
                    fe.Width = rtb.PixelWidth;
                    fe.Height = rtb.PixelHeight;
                }

                await encoder.FlushAsync();
            }

            if (roundTrippedJsonString != null)
            {
                await Windows.Storage.FileIO.WriteTextAsync(jsonResult, roundTrippedJsonString);
            }
        }
    }
}
