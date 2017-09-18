using AdaptiveCards.XamlCardRenderer;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Storage;
using Windows.Storage.Streams;

namespace XamlCardVisualizer.ResourceResolvers
{
    public class MySymbolResourceResolver : IXamlCardResourceResolver
    {
        public IAsyncOperation<IRandomAccessStream> GetResourceStreamAsync(XamlCardGetResourceStreamArgs args)
        {
            return GetResourceStreamHelperAsync(args).AsAsyncOperation();
        }

        public async Task<IRandomAccessStream> GetResourceStreamHelperAsync(XamlCardGetResourceStreamArgs args)
        {
            StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(new Uri($"ms-appx:///Assets/Symbols/{args.Url.Host}.png"));
            return await file.OpenAsync(FileAccessMode.Read);
        }
    }
}
