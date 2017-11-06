using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Net.Cache;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Threading;
using System.Timers;
using Newtonsoft.Json;

namespace AdaptiveCards.Rendering.Wpf
{
    public class RenderedAdaptiveCard : RenderedAdaptiveCardBase
    {
        private readonly List<Task> _assetDownLoad;

        public RenderedAdaptiveCard(FrameworkElement frameworkElement, AdaptiveCard originatingCard, IList<AdaptiveWarning> warnings, List<Task> assetDownLoadTask)
            : base(originatingCard, warnings)
        {
            _assetDownLoad = assetDownLoadTask;
            FrameworkElement = frameworkElement;
            UserInputs = new RenderedAdaptiveCardInputs(this);
        }

        /// <summary>
        /// The rendered card
        /// </summary
        public FrameworkElement FrameworkElement { get; set; } // TODO: make setter private

        internal Dictionary<string, Func<string>> InputBindings { get; set; } = new Dictionary<string, Func<string>>();

        /// <summary>
        /// Event handler for when user invokes an action.
        /// </summary>
        public event TypedEventHandler<RenderedAdaptiveCard, AdaptiveActionEventArgs> OnAction;

        internal void InvokeOnAction(AdaptiveActionEventArgs args)
        {
            OnAction?.Invoke(this, args);
        }

        /// <summary>
        /// Gather the current values from inputs on the card
        /// </summary>
        public RenderedAdaptiveCardInputs UserInputs { get; }

        public Task WaitForAssetsAsync(CancellationToken cancel)
        {
            //if (cancel.IsCancellationRequested)
            //{
            //    return;
            //}
            return Task.WhenAll(_assetDownLoad);
        }

        public async Task<MemoryStream> ToImageAsync(int width = 480)
        {
            Debug.WriteLine($"Starting to render to image...");

            Debug.WriteLine($"Waiting for assets...");
            await Task.WhenAll(_assetDownLoad);
            Debug.WriteLine("Finished loading assets... waiting for layout update");

            FrameworkElement.UpdateLayout();

            await FrameworkElement.AwaitLayoutUpdated();
            Debug.WriteLine("Framework layout updated...");

            FrameworkElement.Measure(new Size(width, 4000));
            FrameworkElement.Arrange(new Rect(new Size(width, FrameworkElement.DesiredSize.Height)));
            FrameworkElement.UpdateLayout();        

            RenderTargetBitmap bitmapImage = new RenderTargetBitmap((int)width, (int)FrameworkElement.DesiredSize.Height, 96, 96, PixelFormats.Default);
            bitmapImage.Render(FrameworkElement);

            var encoder = new PngBitmapEncoder();
            BitmapMetadata metadata = new BitmapMetadata("png");
            metadata.SetQuery("/tEXt/{str=Description}", JsonConvert.SerializeObject(OriginatingCard));
            BitmapFrame pngFrame = BitmapFrame.Create(bitmapImage, null, metadata, null);
            encoder.Frames.Add(pngFrame);

            MemoryStream stream = new MemoryStream();
            encoder.Save(stream);
            stream.Seek(0, SeekOrigin.Begin);
            return stream;
        }
    }
}
