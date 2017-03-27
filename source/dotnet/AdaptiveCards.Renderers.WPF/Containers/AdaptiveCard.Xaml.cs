using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Threading.Tasks;
using System.IO;
using System.Net;
using Adaptive.Threading.Tasks.Schedulers;
using System.Threading;

namespace Adaptive
{
    public partial class AdaptiveCard
    {
        private MemoryStream _backgroundImage;

        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<AdaptiveCard, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// AdaptiveCard
        /// </summary>
        /// <param name="card"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);
            var outerGrid = new Grid();
            outerGrid.Style = context.GetStyle("Adaptive.Card");
            if (this.BackgroundImage != null)
            {
                Uri uri = new Uri(this.BackgroundImage);
                BitmapImage backgroundSource;
                if (_backgroundImage != null)
                {
                    backgroundSource = new BitmapImage();
                    backgroundSource.BeginInit();
                    backgroundSource.StreamSource = _backgroundImage;
                    backgroundSource.EndInit();
                }
                else
                    backgroundSource = new BitmapImage(uri);

                outerGrid.Background = new ImageBrush(backgroundSource);
            }

            var grid = new Grid();
            grid.Style = context.GetStyle("Adaptive.InnerCard");
            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

            var inputControls = new List<FrameworkElement>();
            Container.AddContainerElements(grid, this.Body, this.Actions, context);

            outerGrid.Children.Add(grid);
            return outerGrid;
        }

        /// <summary>
        /// Render the card as a PNG image in a STA compliant way suitable for running on servers 
        /// </summary>
        /// <param name="context"></param>
        /// <param name="width"></param>
        /// <returns>PNG file</returns>
        public async Task<Stream> RenderToImageAsync(RenderContext context, int width = 480)
        {
            await this.PreRender();

            return await Task.Factory.StartNewSTA(() =>
            {
                return RenderToImageStream(context, width);
            }).ConfigureAwait(false);
        }

        /// <summary>
        /// render the card to an png image stream (must be called on STA thread)
        /// </summary>
        /// <param name="context"></param>
        /// <param name="width"></param>
        /// <returns></returns>
        public Stream RenderToImageStream(RenderContext context, int width)
        {
            var bitmapImage = RenderToBitmapSource(context, width);
            var encoder = new PngBitmapEncoder();
            encoder.Frames.Add(BitmapFrame.Create(bitmapImage));

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
        public BitmapSource RenderToBitmapSource(RenderContext context, int width)
        {
            var uiCard = this.Render(context);

            uiCard.Measure(new System.Windows.Size(width, 4000));
            uiCard.Arrange(new Rect(new System.Windows.Size(width, uiCard.DesiredSize.Height)));
            uiCard.UpdateLayout();

            RenderTargetBitmap bitmapImage = new RenderTargetBitmap((int)width, (int)uiCard.DesiredSize.Height, 96, 96, PixelFormats.Default);
            bitmapImage.Render(uiCard);
            return bitmapImage;
        }

        public override async Task PreRender()
        {
            List<Task> tasks = new List<Task>();

            if (this.BackgroundImage != null && _backgroundImage == null)
            {
                tasks.Add(Task.Run(async () =>
                {
                    MemoryStream stream = new MemoryStream();
                    using (WebClient client = new WebClient())
                    {
                        var data = await client.DownloadDataTaskAsync(this.BackgroundImage).ConfigureAwait(false);
                        _backgroundImage = new MemoryStream(data);
                    }
                }));
            }

            foreach (var item in this.Body)
                tasks.Add(item.PreRender());

            await Task.WhenAll(tasks.ToArray());
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