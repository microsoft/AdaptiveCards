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
        /// </summary>
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

        /// <summary>
        ///  Wait for all assets in the card to be loaded. Useful to delay adding the card to the UI tree until images have been rendered
        /// </summary>
        /// <param name="cancellationToken">A token to cancel the operation</param>
        /// <returns></returns>
        public Task WaitForAssetsAsync(CancellationToken cancellationToken)
        {
            return Task.WhenAll(_assetDownLoad).WithCancellation(cancellationToken);
        }

        /// <summary>
        /// Renders the current card to a bitmap image
        /// </summary>
        /// <param name="width">Desired width of the image</param>
        /// <param name="cancellationToken">A token to cancel the operation</param>
        /// <returns></returns>
        public async Task<MemoryStream> ToImageAsync(int width = 400, CancellationToken cancellationToken = default(CancellationToken))
        {
            Debug.WriteLine("Starting to render to image...");

            Debug.WriteLine("Waiting for assets...");
            var at = WaitForAssetsAsync(cancellationToken);
            await at;
            if (!at.IsCompleted)
                throw new OperationCanceledException();

            Debug.WriteLine("Finished loading assets... waiting for layout update");

            await FrameworkElement.AwaitLayoutUpdated();
            Debug.WriteLine("Framework layout updated...");


            FrameworkElement.Measure(new Size(width, int.MaxValue));
            FrameworkElement.Arrange(new Rect(new Size(width, FrameworkElement.DesiredSize.Height)));
            FrameworkElement.UpdateLayout();

            var bitmapImage = new RenderTargetBitmap((int)width, (int)FrameworkElement.DesiredSize.Height, 96, 96, PixelFormats.Default);
            bitmapImage.Render(FrameworkElement);

            var encoder = new PngBitmapEncoder();
            var metadata = new BitmapMetadata("png");
            metadata.SetQuery("/tEXt/{str=Description}", JsonConvert.SerializeObject(OriginatingCard));
            var pngFrame = BitmapFrame.Create(bitmapImage, null, metadata, null);
            encoder.Frames.Add(pngFrame);

            var stream = new MemoryStream();
            encoder.Save(stream);
            stream.Seek(0, SeekOrigin.Begin);
            return stream;
        }
    }
}
