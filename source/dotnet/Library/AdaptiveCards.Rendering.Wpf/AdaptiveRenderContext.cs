using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards.Rendering.Wpf
{
    public class AdaptiveRenderContext
    {
        private readonly Func<Uri, MemoryStream> _imageResolver;
        private readonly Dictionary<string, SolidColorBrush> _colors = new Dictionary<string, SolidColorBrush>();

        public AdaptiveRenderContext(Action<object, AdaptiveActionEventArgs> actionCallback,
            Action<object, MissingInputEventArgs> missingDataCallback,
            Func<Uri, MemoryStream> imageResolver = null)
        {
            if (actionCallback != null)
                OnAction += (obj, args) => actionCallback(obj, args);

            if (missingDataCallback != null)
                OnMissingInput += (obj, args) => missingDataCallback(obj, args);

            _imageResolver = imageResolver;
        }

        public AdaptiveHostConfig Config { get; set; } = new AdaptiveHostConfig();

        public IList<AdaptiveWarning> Warnings { get; } = new List<AdaptiveWarning>();

        public AdaptiveElementRenderers<FrameworkElement, AdaptiveRenderContext> ElementRenderers { get; set; }


        public BitmapImage ResolveImageSource(Uri url)
        {
            BitmapImage source = null;
            // off screen rendering can pass already loaded image to us so we can render immediately
            var stream = _imageResolver?.Invoke(url);
            if (stream != null)
            {
                source = new BitmapImage();
                source.BeginInit();
                source.StreamSource = stream;
                source.EndInit();
            }
            return source ?? new BitmapImage(url);
        }


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

        public ResourceDictionary Resources { get; set; }

        public AdaptiveActionHandlers ActionHandlers { get; set; }

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
            var renderer = ElementRenderers.Get(element.GetType());
            if (renderer != null)
            {
                return renderer.Invoke(element, this);
            }
            else
            {
                Warnings.Add(new AdaptiveWarning(-1, $"No renderer for element type '{element.Type}'"));
                return null;
            }
        }

        public Dictionary<string, Func<string>> InputBindings = new Dictionary<string, Func<string>>();
    }
}
