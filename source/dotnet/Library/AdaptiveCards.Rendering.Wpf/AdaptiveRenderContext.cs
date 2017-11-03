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
        private readonly Func<string, MemoryStream> _imageResolver;
        private readonly AdaptiveCardParseResult _parseResult;

        public AdaptiveRenderContext(Action<object, AdaptiveActionEventArgs> actionCallback,
            Action<object, MissingInputEventArgs> missingDataCallback,
            Func<string, MemoryStream> imageResolver = null)
        {
            if (actionCallback != null)
                this.OnAction += (obj, args) => actionCallback(obj, args);

            if (missingDataCallback != null)
                this.OnMissingInput += (obj, args) => missingDataCallback(obj, args);

            this._imageResolver = imageResolver;
        }

        public AdaptiveHostConfig Config { get; set; } = new AdaptiveHostConfig();

        public IList<AdaptiveViolation> Warnings { get; } = new List<AdaptiveViolation>();

        public AdaptiveElementRenderers<FrameworkElement, AdaptiveRenderContext> ElementRenderers { get; set; }


        public BitmapImage ResolveImageSource(string url)
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
            return source ?? new BitmapImage(new Uri(url));
        }


        public event EventHandler<AdaptiveActionEventArgs> OnAction;

        /// <summary>
        /// Event fires when missing input for submit/http actions
        /// </summary>
        public delegate void MissingInputEventHandler(object sender, MissingInputEventArgs e);

        public event MissingInputEventHandler OnMissingInput;

        public void InvokeAction(FrameworkElement ui, AdaptiveActionEventArgs args)
        {
            OnAction?.Invoke(ui, args);
        }

        public void MissingInput(AdaptiveAction sender, MissingInputEventArgs args)
        {
            OnMissingInput?.Invoke(sender, args);
        }

        private readonly Dictionary<string, SolidColorBrush> _colors = new Dictionary<string, SolidColorBrush>();

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


        public virtual dynamic MergeInputData(dynamic data)
        {
            foreach (var id in InputBindings.Keys)
            {
                var value = InputBindings[id]();
                if (value != null)
                {
                    data[id] = JToken.FromObject(value);
                }
            }
            return data;
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
                Warnings.Add(new AdaptiveViolation(-1, $"No renderer for element type '{element.Type}'"));
                return null;
            }
        }

        public Dictionary<string, Func<object>> InputBindings = new Dictionary<string, Func<object>>();
    }


    public class MissingInputEventArgs : EventArgs
    {
        public MissingInputEventArgs(AdaptiveInput input, FrameworkElement frameworkElement)
        {
            this.FrameworkElement = frameworkElement;
            this.AdaptiveInput = input;
        }

        public FrameworkElement FrameworkElement { get; private set; }

        public AdaptiveInput AdaptiveInput { get; private set; }
    }


    public class MissingInputException : Exception
    {
        public MissingInputException(string message, AdaptiveInput input, FrameworkElement frameworkElement)
            : base(message)
        {
            this.FrameworkElement = frameworkElement;
            this.AdaptiveInput = input;
        }

        public FrameworkElement FrameworkElement { get; set; }

        public AdaptiveInput AdaptiveInput { get; set; }
    }
}
