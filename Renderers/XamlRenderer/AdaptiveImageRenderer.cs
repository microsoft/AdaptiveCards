using System;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Threading;
using Adaptive.Renderers;
using Adaptive.Schema.Net;

namespace Adaptive.Renderers
{
    /// <summary>
    /// This adaptiveCard renderer will render to a BitmapSource suitable for saving
    /// NOTE: This needs to be called from a STAThread
    /// </summary>
    public class AdaptiveImageRenderer : AdaptiveXamlRenderer
    {
        private bool showInput;
        private bool showAction;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="resources"></param>
        /// <param name="showInput">set to true to show input controls on image</param>
        /// <param name="showAction">set to true to show action controls on image</param>
        public AdaptiveImageRenderer(ResourceDictionary resources, bool showInput = false, bool showAction = false) : base(resources)
        {
            this.showInput = showInput;
            this.showAction = showAction;
        }

        protected override Style GetStyle(string styleName)
        {
            if (styleName.Contains(".Input") && !this.showInput)
            {
                return this.Resources["Hidden"] as Style;
            }

            if (styleName.Contains(".Action") && !this.showInput)
            {
                return this.Resources["Hidden"] as Style;
            }

            return base.GetStyle(styleName);
        }

        /// <summary>
        /// Render card to desired width (height is variable)
        /// </summary>
        /// <param name="card">card to render</param>
        /// <param name="width">desired width of image</param>
        /// <returns>BitmapSource of the card</returns>
        public async Task<BitmapSource> RenderToImageAsync(AdaptiveCard card, int width)
        {
            var uiCard = (FrameworkElement)this.Render(card);
            uiCard.Measure(new System.Windows.Size(width, 4000));
            // width = Math.Max(width, (int)uiCard.DesiredSize.Width);
            uiCard.Arrange(new Rect(new System.Windows.Size(width, uiCard.DesiredSize.Height)));
            uiCard.UpdateLayout();

            RenderTargetBitmap bitmapImage = new RenderTargetBitmap((int)width, (int)uiCard.DesiredSize.Height, 96, 96, PixelFormats.Default);
            await Task.Delay(1000);
            // Dispatcher.Invoke(new Action(() => { }), DispatcherPriority.ContextIdle, null);
            bitmapImage.Render(uiCard);
            return bitmapImage;
        }

    }
}