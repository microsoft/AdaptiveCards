// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using System.Net;
#if WPF
using System.Net.Cache;

using System.Windows;
using System.Windows.Resources;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public class ResourceResolver
    {
        private readonly Dictionary<string, Func<Uri, Task<MemoryStream>>> _internalResolver = new Dictionary<string, Func<Uri, Task<MemoryStream>>>(StringComparer.OrdinalIgnoreCase);

        public ResourceResolver()
        {
#if WPF
            Register("http", GetHttpAsync);
            Register("https", GetHttpAsync);
            Register("pack", GetPackAsync);
#endif
            Register("data", GetDataUriAsync);
        }

#if WPF
        private static async Task<MemoryStream> GetHttpAsync(Uri uri)
        {
            using (var webclient = new WebClient())
            {
                webclient.CachePolicy = new RequestCachePolicy(RequestCacheLevel.CacheIfAvailable);
                var bytes = await webclient.DownloadDataTaskAsync(uri);
                return new MemoryStream(bytes);
            }
        }

        /* Helper function to get stream from either Resource or Content */
        private static StreamResourceInfo GetResourceOrContentStream(Uri uri)
        {
            StreamResourceInfo info = Application.GetResourceStream(uri);
            if (info == null)
            {
                info = Application.GetContentStream(uri);
            }

            return info;
        }


        private static Task<MemoryStream> GetPackAsync(Uri uri)
        {
            try
            {
                var info = GetResourceOrContentStream(uri);
                if (info == null)
                {
                    throw new IOException("Unable to locate pack URI");
                }

                var memoryStream = new MemoryStream();
                info.Stream.CopyTo(memoryStream);
                return Task.FromResult(memoryStream);
            }
            catch (Exception)
            {
                return Task.FromResult<MemoryStream>(null);
            }
        }
#endif

        private static Task<MemoryStream> GetDataUriAsync(Uri uri)
        {
            try
            {
                var encodedData = uri.AbsoluteUri.Substring(uri.AbsoluteUri.LastIndexOf(',') + 1);

                var decodedDataUri = Convert.FromBase64String(encodedData);
                var memoryStream = new MemoryStream(decodedDataUri);

                return Task.FromResult(memoryStream);
            }
            catch (Exception)
            {
                return Task.FromResult<MemoryStream>(null);
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
