using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace AdaptiveCards.Rendering.Wpf
{
    /// <summary>
    /// Context state for a render pass
    /// </summary>
    public class AdaptiveRenderContext
    {
        private readonly Dictionary<string, SolidColorBrush> _colors = new Dictionary<string, SolidColorBrush>();

        public List<Task> AssetTasks { get; } = new List<Task>();

        public AdaptiveRenderContext(Action<object, AdaptiveActionEventArgs> actionCallback,
            Action<object, MissingInputEventArgs> missingDataCallback)
        {
            if (actionCallback != null)
                OnAction += (obj, args) => actionCallback(obj, args);

            if (missingDataCallback != null)
                OnMissingInput += (obj, args) => missingDataCallback(obj, args);
        }

        public AdaptiveHostConfig Config { get; set; } = new AdaptiveHostConfig();

        public IList<AdaptiveWarning> Warnings { get; } = new List<AdaptiveWarning>();

        public AdaptiveElementRenderers<FrameworkElement, AdaptiveRenderContext> ElementRenderers { get; set; }

        public ResourceDictionary Resources { get; set; }

        public AdaptiveActionHandlers ActionHandlers { get; set; }

        public ResourceResolver ResourceResolvers { get; set; }

        public IDictionary<Uri, MemoryStream> CardAssets { get; set; } = new Dictionary<Uri, MemoryStream>();

        public IDictionary<string, Func<string>> InputBindings = new Dictionary<string, Func<string>>();

        public event EventHandler<AdaptiveActionEventArgs> OnAction;

        /// <summary>
        /// Event fires when missing input for submit/http actions
        /// </summary>
        public event EventHandler<MissingInputEventArgs> OnMissingInput;

        public void InvokeAction(FrameworkElement ui, AdaptiveActionEventArgs args)
        {
            OnAction?.Invoke(ui, args);
        }

        public void MissingInput(AdaptiveAction sender, MissingInputEventArgs args)
        {
            OnMissingInput?.Invoke(sender, args);
        }

        /// <summary>
        /// All remote assets should be resolved through this method for tracking
        /// </summary>
        public async Task<BitmapImage> ResolveImageSource(Uri url)
        {
            var completeTask = new TaskCompletionSource<object>();
            AssetTasks.Add(completeTask.Task);

            try
            {
                // Load the stream from the pre-populated CardAssets or try to load from the ResourceResolver
                var streamTask = CardAssets.TryGetValue(url, out var s) ? Task.FromResult(s) : ResourceResolvers.LoadAssetAsync(url);

                Debug.WriteLine($"ASSETS: Starting asset down task for {url}");

                var source = new BitmapImage();

                var stream = await streamTask;
                if (stream != null)
                {
                    stream.Position = 0;
                    source.BeginInit();
                    source.CacheOption = BitmapCacheOption.OnLoad;
                    source.StreamSource = stream;
                    source.EndInit();
                    Debug.WriteLine($"ASSETS: Finished loading asset for {url} ({stream.Length} bytes)");
                }
                completeTask.SetResult(new object());
                return source;
            }
            catch (Exception e)
            {
                Debug.WriteLine($"ASSETS: Failed to load asset for {url}. {e.Message}");
                completeTask.SetException(e);
                return null;
            }
        }

        public SolidColorBrush GetColorBrush(string color)
        {
            lock (_colors)
            {
                if (_colors.TryGetValue(color, out var brush))
                    return brush;
                brush = new SolidColorBrush((Color)ColorConverter.ConvertFromString(color));
                _colors[color] = brush;
                return brush;
            }
        }


        public virtual Style GetStyle(string styleName)
        {
            while (!String.IsNullOrEmpty(styleName))
            {
                Style style = this.Resources.TryGetValue<Style>(styleName);
                if (style != null)
                    return style;
                var iPos = styleName.LastIndexOf('.');
                if (iPos <= 0)
                    break;
                styleName = styleName.Substring(0, iPos);
            }

            // Debug.WriteLine($"Unable to find Style {styleName} from the supplied ResourceDictionary");
            return null;
        }

        /// <summary>
        /// Helper to deal with casting
        /// </summary>
        public FrameworkElement Render(AdaptiveTypedElement element)
        {
            // Inputs should render read-only if interactivity is false
            if (!Config.SupportsInteractivity && element is AdaptiveInput input)
            {
                var tb = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
                tb.Text = input.GetNonInteractiveValue() ?? "*[Input]*";
                tb.Color = AdaptiveTextColor.Accent;
                tb.Wrap = true;
                Warnings.Add(new AdaptiveWarning(-1, $"Rendering non-interactive input element '{element.Type}'"));
                return Render(tb);
            }

            var renderer = ElementRenderers.Get(element.GetType());
            if (renderer != null)
            {
                return renderer.Invoke(element, this);
            }

            Warnings.Add(new AdaptiveWarning(-1, $"No renderer for element '{element.Type}'"));
            return null;
        }

    }
}
