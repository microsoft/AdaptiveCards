using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Threading.Tasks;
using System.IO;
using System.Net;

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

            var grid = new Grid();
            grid.Style = context.GetStyle("Adaptive.Card");
            if (this.BackgroundImage != null)
            {
                Uri uri = new Uri(this.BackgroundImage);
                BitmapImage backgroundSource;
                if (_backgroundImage!= null)
                {
                    backgroundSource = new BitmapImage();
                    backgroundSource.BeginInit();
                    backgroundSource.StreamSource = _backgroundImage;
                    backgroundSource.EndInit();
                }
                else
                    backgroundSource = new BitmapImage(uri);

                grid.Background = new ImageBrush(backgroundSource);
            }
            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

            var inputControls = new List<FrameworkElement>();
            Container.AddContainerElements(grid, this.Body, this.Actions, context);
            return grid;
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
}