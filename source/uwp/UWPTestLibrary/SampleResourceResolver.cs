// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards.Rendering.Uwp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Storage;
using Windows.Storage.Streams;

namespace UWPTestLibrary
{
    class SampleResourceResolver : IAdaptiveCardResourceResolver
    {
        public IAsyncOperation<IRandomAccessStream> GetResourceStreamAsync(AdaptiveCardGetResourceStreamArgs args)
        {
            return GetResourceStreamHelperAsync(args).AsAsyncOperation();
        }

        public async Task<IRandomAccessStream> GetResourceStreamHelperAsync(AdaptiveCardGetResourceStreamArgs args)
        {
            // We expect something like "symbol:up", and then map "up" to the file name
            StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(new Uri($"ms-appx:///Assets/{args.Url.AbsolutePath}.png"));
            return await file.OpenAsync(FileAccessMode.Read);
        }
    }
}
