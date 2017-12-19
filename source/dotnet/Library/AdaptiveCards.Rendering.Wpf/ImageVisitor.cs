using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering.Wpf
{
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
            VisitCard(card);

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

        public override void VisitCard(AdaptiveCard card)
        {
            if (card.BackgroundImage != null)
                tasks.Add(GetImage(card.BackgroundImage));
            base.VisitCard(card);
        }

        public override void VisitImage(AdaptiveContainer parent, AdaptiveImage image)
        {
            tasks.Add(GetImage(image.Url));
            base.VisitImage(parent, image);
        }
    }
}