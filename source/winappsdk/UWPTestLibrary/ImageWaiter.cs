// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards.Rendering.Uwp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Shapes;

namespace UWPTestLibrary
{
    public class ImageWaiter
    {
        private List<Task> _allWaitTasks = new List<Task>();

        public ImageWaiter(UIElement el)
        {
            if (el == null)
            {
                return;
            }

            foreach (var shape in RenderTestHelpers.GetAllDescendants(el).OfType<Shape>())
            {
                if (shape.Fill is ImageBrush imgBrush)
                {
                    _allWaitTasks.Add(imgBrush.WaitForLoadedAsync());
                }
            }

            foreach (var img in RenderTestHelpers.GetAllDescendants(el).OfType<Image>())
            {
                _allWaitTasks.Add(img.WaitForLoadedAsync());
            }

            foreach (var tileControl in RenderTestHelpers.GetAllDescendants(el).OfType<TileControl>())
            {
                // Tile controls hold onto an image (but don't drop it into the visual tree) and they listen
                // to the bitmap's load event, so we have to listen to that too, and then when that triggers,
                // they finally update the UI with rectangles
                if (tileControl.ResolvedImage is Image img && img.Source is BitmapImage bmp)
                {
                    _allWaitTasks.Add(bmp.WaitForLoadedAsync());
                }
            }
        }

        /// <summary>
        /// We make sure the element and all of its parents are visible. Invisible elements should be ignored as they'll never load.
        /// </summary>
        /// <param name="el"></param>
        /// <returns></returns>
        private bool IsVisible(UIElement el)
        {
            if (el.Visibility == Visibility.Visible)
            {
                var parent = VisualTreeHelper.GetParent(el) as UIElement;
                if (parent == null)
                {
                    return true;
                }
                else
                {
                    return IsVisible(parent);
                }
            }
            return false;
        }

        public async Task WaitOnAllImagesAsync()
        {
            Task allCompleted = Task.WhenAll(_allWaitTasks);
            await WaitWithTimeoutAsync(allCompleted, 5000);
        }

        private Task WaitWithTimeoutAsync(Task task, int millisecondTimeout)
        {
            // https://stackoverflow.com/questions/4238345/asynchronously-wait-for-taskt-to-complete-with-timeout
            return Task.WhenAny(task, Task.Delay(millisecondTimeout));
        }
    }

    public static class ImageWaiterExtensions
    {
        private class SingleImageWaiter
        {
            private TaskCompletionSource<bool> _waitingSource = new TaskCompletionSource<bool>();

            public SingleImageWaiter(Image img)
            {
                img.ImageOpened += Img_ImageOpened;
                img.ImageFailed += Img_ImageFailed;
                CheckImageSource(img.Source);
            }

            public SingleImageWaiter(ImageBrush imgBrush)
            {
                imgBrush.ImageOpened += Img_ImageOpened;
                imgBrush.ImageFailed += Img_ImageFailed;
                CheckImageSource(imgBrush.ImageSource);
            }

            public SingleImageWaiter(BitmapImage bmp)
            {
                bmp.ImageOpened += Img_ImageOpened;
                bmp.ImageFailed += Img_ImageFailed;
                CheckImageSource(bmp);
            }

            private void Img_ImageFailed(object sender, ExceptionRoutedEventArgs e)
            {
                _waitingSource.TrySetException(new Exception(e.ErrorMessage));
            }

            private void Img_ImageOpened(object sender, RoutedEventArgs e)
            {
                TriggerLoaded();
            }

            private void CheckImageSource(ImageSource imageSource)
            {
                if (imageSource is BitmapImage bmp)
                {
                    if (bmp.PixelHeight > 0)
                    {
                        // Image is already loaded, Opened event isn't going to fire (this happens with data uris)
                        TriggerLoaded();
                    }
                }
            }

            private void TriggerLoaded()
            {
                _waitingSource.TrySetResult(true);
            }

            public Task WaitAsync()
            {
                return _waitingSource.Task;
            }
        }

        public static Task WaitForLoadedAsync(this Image img)
        {
            // Using the bitmap directly handles most hidden visibility cases
            if (img.Source is BitmapImage bmp)
            {
                return bmp.WaitForLoadedAsync();
            }

            return new SingleImageWaiter(img).WaitAsync();
        }

        public static Task WaitForLoadedAsync(this ImageBrush imgBrush)
        {
            return new SingleImageWaiter(imgBrush).WaitAsync();
        }

        public static Task WaitForLoadedAsync(this BitmapImage bmp)
        {
            return new SingleImageWaiter(bmp).WaitAsync();
        }
    }
}
