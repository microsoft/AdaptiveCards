using System;
using System.IO;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Newtonsoft.Json;

namespace AdaptiveCards.Rendering.Wpf
{
    /// <summary>
    /// Renderer which renders adaptive card to an image
    /// </summary>
    public partial class AdaptiveCardRenderer
    {

        /// <summary>
        /// render the card to an png image stream (must be called on STA thread)
        /// </summary>
        /// <returns></returns>
        public Stream RenderToImage(AdaptiveCard card, int width)
        {
            return _renderToImage(card, width);
        }

        /// <summary>
        /// Render the card as a PNG image in a STA compliant way suitable for running on servers 
        /// </summary>
        /// <returns>PNG file</returns>
        public async Task<Stream> RenderToImageAsync(AdaptiveCard card, int width = 480)
        {
            var visitor = new ImageVisitor();
            
            // prefetch images
            await visitor.GetAllImages(card).ConfigureAwait(false);

            return await Task.Factory.StartNewSta(() =>
            {
                return _renderToImage(card, width, (url) => visitor.GetCachedImageStream(url));
            }).ConfigureAwait(false);
        }

        protected Stream _renderToImage(AdaptiveCard card, int width, Func<Uri, MemoryStream> imageResolver = null)
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
        protected BitmapSource _renderToBitmapSource(AdaptiveCard card, int width, Func<Uri, MemoryStream> imageResolver = null)
        {
            // TODO: When ResourceResolver support is added, wire up the image resolver
            var result = RenderCard(card);
            if (result.FrameworkElement != null)
            {
                var uiCard = result.FrameworkElement;

                uiCard.Measure(new Size(width, 4000));
                uiCard.Arrange(new Rect(new Size(width, uiCard.DesiredSize.Height)));
                uiCard.UpdateLayout();

                RenderTargetBitmap bitmapImage = new RenderTargetBitmap((int)width, (int)uiCard.DesiredSize.Height, 96, 96, PixelFormats.Default);
                bitmapImage.Render(uiCard);
                return bitmapImage;
            }
            else
            {
                throw new Exception("Rendering failed");
            }
        }
    }
}
