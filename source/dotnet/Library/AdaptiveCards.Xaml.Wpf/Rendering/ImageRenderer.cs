using AdaptiveCards;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Config;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Renderer which renders adaptive card to an image
    /// </summary>
    public class ImageRenderer
    {
        private AdaptiveCardRenderer _xamlRenderer;

        /// <summary>
        /// You can use this from within a WPF app, passing in resource dictionary directly
        /// </summary>
        /// <param name="hostConfig"></param>
        /// <param name="resources"></param>
        public ImageRenderer(HostConfig hostConfig, ResourceDictionary resources)
        {
            hostConfig.SupportsInteractivity = false;
            _xamlRenderer = new AdaptiveCardRenderer(hostConfig)
            {
                Resources = resources
            };
        }

        /// <summary>
        /// Use this from a Server, passing in the path to a resource dictionary so that UI resources can be created in correct thread
        /// </summary>
        /// <param name="hostConfig"></param>
        /// <param name="stylePath"></param>
        public ImageRenderer(HostConfig hostConfig, string stylePath)
        {
            hostConfig.SupportsInteractivity = false;
            _xamlRenderer = new AdaptiveCardRenderer(hostConfig)
            {
                StylePath = stylePath
            };
        }

        public AdaptiveCardRenderer Renderer { get { return this._xamlRenderer; } }

        public HostConfig Options { get { return _xamlRenderer.HostConfig; } set { _xamlRenderer.HostConfig = value; } }



        /// <summary>
        /// render the card to an png image stream (must be called on STA thread)
        /// </summary>
        /// <param name="context"></param>
        /// <param name="width"></param>
        /// <returns></returns>
        public Stream RenderAdaptiveCard(AdaptiveCard card, int width)
        {
            return _renderAdaptiveCard(card, width);
        }

        /// <summary>
        /// Render the card as a PNG image in a STA compliant way suitable for running on servers 
        /// </summary>
        /// <param name="context"></param>
        /// <param name="width"></param>
        /// <returns>PNG file</returns>
        public async Task<Stream> RenderAdaptiveCardAsync(AdaptiveCard card, int width = 480)
        {
            ImageVisitor visitor = new ImageVisitor();
            
            // prefetch images
            await visitor.GetAllImages(card).ConfigureAwait(false);

            return await Task.Factory.StartNewSTA(() =>
            {
                return _renderAdaptiveCard(card, width, (url) => visitor.GetCachedImageStream(url));
            }).ConfigureAwait(false);
        }

        protected Stream _renderAdaptiveCard(AdaptiveCard card, int width, Func<string, MemoryStream> imageResolver = null)
        {
            var bitmapImage = _renderToBitmapSource(card, width, imageResolver);
            var encoder = new PngBitmapEncoder();
            BitmapMetadata metadata = new BitmapMetadata("png");
            metadata.SetQuery("/tEXt/{str=Description}", JsonConvert.SerializeObject(card));
            BitmapFrame pngFrame = BitmapFrame.Create(bitmapImage, null, metadata, null);
            encoder.Frames.Add(pngFrame);

            MemoryStream stream = new MemoryStream();
            encoder.Save(stream);
            stream.Seek(0, SeekOrigin.Begin);
            return stream;
        }

        /// <summary>
        /// Render card to bitmap source (must be called on STA thread)
        /// </summary>
        /// <param name="context"></param>
        /// <param name="width"></param>
        /// <returns></returns>
        protected BitmapSource _renderToBitmapSource(AdaptiveCard card, int width, Func<string, MemoryStream> imageResolver = null)
        {
            // Have to use obsolete method since the official image resolver isn't coded up yet
            var uiCard = this._xamlRenderer.RenderAdaptiveCard(card, imageResolver);

            uiCard.Measure(new System.Windows.Size(width, 4000));
            uiCard.Arrange(new Rect(new System.Windows.Size(width, uiCard.DesiredSize.Height)));
            uiCard.UpdateLayout();

            RenderTargetBitmap bitmapImage = new RenderTargetBitmap((int)width, (int)uiCard.DesiredSize.Height, 96, 96, PixelFormats.Default);
            bitmapImage.Render(uiCard);
            return bitmapImage;
        }
    }

    /// <summary>
    /// Walk tree and fetch any images referenced
    /// </summary>
    class ImageVisitor : AdaptiveVisitor
    {
        List<Task> tasks = new List<Task>();

        public ImageVisitor()
        {
        }

        public Dictionary<string, byte[]> Images = new Dictionary<string, byte[]>();

        /// <summary>
        /// Get all images 
        /// </summary>
        /// <param name="card"></param>
        /// <returns></returns>
        public async Task GetAllImages(AdaptiveCard card)
        {
            Visit(card);

            await Task.WhenAll(tasks.ToArray()).ConfigureAwait(false);
        }

        public MemoryStream GetCachedImageStream(String url)
        {
            if (this.Images.TryGetValue(url, out var bytes))
            {
                return new MemoryStream(bytes, writable: false);
            }
            return null;
        }

        protected async Task GetImage(string url)
        {
            using (WebClient client = new WebClient())
            {
                var data = await client.DownloadDataTaskAsync(url).ConfigureAwait(false);
                lock (Images)
                    Images[url] = data;
            }
        }

        public override void Visit(AdaptiveCard card)
        {
            if (card.BackgroundImage != null)
                tasks.Add(GetImage(card.BackgroundImage));
            base.Visit(card);
        }

        public override void Visit(Image image)
        {
            tasks.Add(GetImage(image.Url));
            base.Visit(image);
        }
    }


    public static class TaskFactoryExtensions
    {
        private static readonly TaskScheduler _staScheduler = new StaTaskScheduler(numberOfThreads: Environment.ProcessorCount);

        public static Task<TResult> StartNewSTA<TResult>(this TaskFactory factory, Func<TResult> action)
        {
            return factory.StartNew(action, CancellationToken.None, TaskCreationOptions.None, _staScheduler);
        }
    }
}
