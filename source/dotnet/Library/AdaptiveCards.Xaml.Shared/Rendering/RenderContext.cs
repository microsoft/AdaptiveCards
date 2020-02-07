using Newtonsoft.Json.Linq;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using AdaptiveCards.Rendering;
#if XAMARIN
using FrameworkElement = Xamarin.Forms.View;
using Xamarin.Forms;
using Xamarin.Forms.Xaml.Internals;
#elif WPF
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#endif

namespace AdaptiveCards.Rendering
{
    public class RenderContext
    {
        private Func<string, MemoryStream> _imageResolver = null;

        public RenderContext(Action<object, ActionEventArgs> actionCallback,
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

        public AdaptiveElementRenderers<View, RenderContext> ElementRenderers = new AdaptiveElementRenderers<View, RenderContext>();

        // public Dictionary<FrameworkElement, RenderContext> ElementRenderers = new Dictionary<FrameworkElement, RenderContext>();

        public FrameworkElement CardRoot { get; set; }

#if WPF
        public BitmapImage ResolveImageSource(string url)
        {
            BitmapImage source = null;
            if (this._imageResolver != null)
            {
                // off screen rendering can pass already loaded image to us so we can render immediately
                var stream = this._imageResolver(url);
                if (stream != null)
                {
                    source = new BitmapImage();
                    source.BeginInit();
                    source.StreamSource = stream;
                    source.EndInit();
                }
            }
            return source ?? new BitmapImage(new Uri(url));
        }
#endif

        /// <summary>
        /// Event fires when action is invoked
        /// </summary>
        public delegate void ActionEventHandler(object sender, ActionEventArgs e);

        public event ActionEventHandler OnAction;

        /// <summary>
        /// Event fires when missing input for submit/http actions
        /// </summary>
        public delegate void MissingInputEventHandler(object sender, MissingInputEventArgs e);

        public event MissingInputEventHandler OnMissingInput;

        public void Action(FrameworkElement ui, ActionEventArgs args)
        {
            this.OnAction?.Invoke(ui, args);
        }

        public void MissingInput(AdaptiveAction sender, MissingInputEventArgs args)
        {
            this.OnMissingInput?.Invoke(sender, args);
        }
#if WPF
        private Dictionary<string, SolidColorBrush> colors = new Dictionary<string, SolidColorBrush>();

        public SolidColorBrush GetColorBrush(string color)
        {
            lock (colors)
            {
                if (colors.TryGetValue(color, out var brush))
                    return brush;
                brush = new SolidColorBrush((Color)ColorConverter.ConvertFromString(color));
                colors[color] = brush;
                return brush;
            }
        }
#elif XAMARIN
        // TODO
        public object GetColorBrush(string color)
        {
            return null;
        }
#endif

        public ResourceDictionary Resources { get; set; }


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
            foreach (var id in this.InputBindings.Keys)
            {
                var value = this.InputBindings[id]();
                bool hasValue = false;
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
        /// <param name="element"></param>
        /// <returns></returns>
        public FrameworkElement Render(AdaptiveTypedElement element)
        {
            return this.ElementRenderers.Get(element.GetType()).Invoke(element, this);
            // return null;
        }

        public Dictionary<string, Func<object>> InputBindings = new Dictionary<string, Func<object>>();
    }


    public class ActionEventArgs : EventArgs
    {
        public ActionEventArgs()
        {
        }

        /// <summary>
        /// The action that fired
        /// </summary>
        public AdaptiveAction Action { get; set; }

        /// <summary>
        /// Data for Input controls (if appropriate)
        /// </summary>
        public object Data { get; set; }
    }

    public class MissingInputEventArgs : EventArgs
    {
        public MissingInputEventArgs(AdaptiveInput input, FrameworkElement frameworkElement)
        {
            this.FrameworkElement = frameworkElement;
            this.Input = input;
        }

        public FrameworkElement FrameworkElement { get; private set; }

        public AdaptiveInput Input { get; private set; }
    }


    public class MissingInputException : Exception
    {
        public MissingInputException(string message, AdaptiveInput input, FrameworkElement frameworkElement)
            : base(message)
        {
            this.FrameworkElement = frameworkElement;
            this.Input = input;
        }

        public FrameworkElement FrameworkElement { get; set; }

        public AdaptiveInput Input { get; set; }
    }
}
