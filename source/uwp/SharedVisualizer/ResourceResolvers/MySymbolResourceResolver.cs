// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#if USE_WINUI3
using AdaptiveCards.Rendering.WinUI3;
#else
using AdaptiveCards.Rendering.Uwp;
#endif
using System;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Storage;
using Windows.Storage.Streams;

namespace AdaptiveCardVisualizer.ResourceResolvers
{
    public class MySymbolResourceResolver : IAdaptiveCardResourceResolver
    {
        public IAsyncOperation<IRandomAccessStream> GetResourceStreamAsync(AdaptiveCardGetResourceStreamArgs args)
        {
            return GetResourceStreamHelperAsync(args).AsAsyncOperation();
        }

        public async Task<IRandomAccessStream> GetResourceStreamHelperAsync(AdaptiveCardGetResourceStreamArgs args)
        {
            // We expect something like "symbol:up.png", and then map "up.png" to the file name
            StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(new Uri($"ms-appx:///Assets/Symbols/{args.Url.AbsolutePath}"));
            return await file.OpenAsync(FileAccessMode.Read);
        }
    }
}
