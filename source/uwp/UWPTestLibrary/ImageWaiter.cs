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

        /// <summary>
        /// This method ensures that any time pickers that didn't have a specific assigned value end up with the same time
        /// as previous tests, to ensure that the fact that the time is different on a machine doesn't make the test fail
        /// </summary>
        /// <param name="el"></param>
        private static void NormalizeTimePickers(UIElement el)
        {
            foreach (var timePicker in UWPTestLibrary.RenderTestHelpers.GetAllDescendants(el).OfType<TimePicker>())
            {
                // If didn't have a value from the Card payload
                if ((DateTime.Now.TimeOfDay - timePicker.Time).TotalMinutes <= 1)
                {
                    timePicker.Time = new TimeSpan(9, 0, 0);
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
            NormalizeTimePickers(el);

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
