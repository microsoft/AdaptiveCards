// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Linq;
using System.Threading.Tasks;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace UWPTestLibrary
{
    public class ImageWaiter
    {
        private int _imageCountRemaining = 0;
        private int _loopsUnchanged = 0;

        /// <summary>
        /// This method expands all inline show cards so that changes in how show cards are rendered can be covered by this test suite
        /// </summary>
        /// <param name="el"></param>
        private static void ExpandShowCards(UIElement el)
        {
            foreach (var card in UWPTestLibrary.RenderTestHelpers.GetAllDescendants(el).OfType<Grid>())
            {
                if (card.Visibility == Visibility.Collapsed)
                {
                    card.Visibility = Visibility.Visible;
                }
            }
        }

        public ImageWaiter(UIElement el)
        {
            if (el == null)
            {
                return;
            }

            ExpandShowCards(el);

            ExceptionRoutedEventHandler failedHandler = new ExceptionRoutedEventHandler(delegate
            {
                _imageCountRemaining--;
            });
            RoutedEventHandler openedHandler = new RoutedEventHandler(delegate
            {
                _imageCountRemaining--;
            });

            EventHandler<object> layoutHandler = new EventHandler<object>(delegate
            {
                _loopsUnchanged = 0;
            });

            (el as FrameworkElement).LayoutUpdated += layoutHandler;

            foreach (var shape in UWPTestLibrary.RenderTestHelpers.GetAllDescendants(el).OfType<Shape>())
            {
                if (shape.Fill is ImageBrush)
                {
                    _imageCountRemaining++;
                    (shape.Fill as ImageBrush).ImageFailed += failedHandler;
                    (shape.Fill as ImageBrush).ImageOpened += openedHandler;
                }
            }

            foreach (var img in UWPTestLibrary.RenderTestHelpers.GetAllDescendants(el).OfType<Image>())
            {
                _imageCountRemaining++;
                img.ImageFailed += failedHandler;
                img.ImageOpened += openedHandler;
            }
        }

        public async Task WaitOnAllImagesAsync()
        {
            int totalLoops = 0;
            const int maxLoops = 500;

            while (((_imageCountRemaining > 0) || (_loopsUnchanged < 2)) && (totalLoops < maxLoops))
            {
                totalLoops++;
                _loopsUnchanged++;

                await Task.Delay(10);
            }
        }
    }
}
