using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Net.Cache;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering.Wpf
{
    public class ResourceResolver
    {
        private readonly Dictionary<string, Func<Uri, Task<MemoryStream>>> _internalResolver = new Dictionary<string, Func<Uri, Task<MemoryStream>>>(StringComparer.OrdinalIgnoreCase);

        public ResourceResolver()
        {
            Register("http", GetHttpAsync);
            Register("https", GetHttpAsync);
        }

        private static async Task<MemoryStream> GetHttpAsync(Uri uri)
        {
            using (var webclient = new WebClient())
            {
                webclient.CachePolicy = new RequestCachePolicy(RequestCacheLevel.CacheIfAvailable);
                var bytes = await webclient.DownloadDataTaskAsync(uri);
                return new MemoryStream(bytes);
            }
        }


        public void Register(string uriScheme, Func<Uri, Task<MemoryStream>> loadAsset)
        {
            _internalResolver[uriScheme] = loadAsset;
        }

        public void Clear()
        {
            _internalResolver.Clear();
        }

        public void Remove(string uriScheme)
        {
            _internalResolver.Remove(uriScheme);
        }

        public Task<MemoryStream> LoadAssetAsync(Uri uri)
        {
            if (uri == null) throw new ArgumentNullException(nameof(uri));

            if (_internalResolver.TryGetValue(uri.Scheme, out var func))
                return func(uri);

            // TODO: Context warning, no asset resolver for URI scheme
            return Task.FromResult<MemoryStream>(null);
        }
    }
}