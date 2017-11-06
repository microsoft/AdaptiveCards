using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering.Wpf
{
    /// <summary>
    /// Walk tree and fetch any images referenced
    /// </summary>
    internal class PreFetchImageVisitor : AdaptiveVisitor
    {
        private readonly List<Task> _tasks = new List<Task>();

        public ConcurrentDictionary<Uri, MemoryStream> LoadedImages { get; } = new ConcurrentDictionary<Uri, MemoryStream>();

        /// <summary>
        /// Get all images 
        /// </summary>
        public async Task GetAllImages(AdaptiveCard card)
        {
            Visit(card);

            await Task.WhenAll(_tasks.ToArray()).ConfigureAwait(false);
        }

        public MemoryStream GetCachedImageStream(Uri url)
        {
            if (LoadedImages.TryGetValue(url, out var stream))
            {
                return stream;
            }
            return null;
        }

        protected async Task GetImage(Uri url)
        {
            using (WebClient client = new WebClient())
            {
                var data = await client.DownloadDataTaskAsync(url).ConfigureAwait(false);
                LoadedImages[url] = new MemoryStream(data, writable: false);
            }
        }

        public override void Visit(AdaptiveCard card)
        {
            if (card.BackgroundImage != null)
                _tasks.Add(GetImage(card.BackgroundImage));
            base.Visit(card);
        }

        public override void Visit(AdaptiveImage image)
        {
            _tasks.Add(GetImage(image.Url));
            base.Visit(image);
        }
    }
}