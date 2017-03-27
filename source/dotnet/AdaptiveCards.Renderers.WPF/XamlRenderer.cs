using AdaptiveCards;
using AdaptiveCards.Renderers;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
#if WPF
using System.Windows.Markup;
using System.Windows.Media.Imaging;
#endif

namespace AdaptiveCards.Renderers
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
        protected Action<object, ActionEventArgs> actionCallback;
        protected Action<object, MissingInputEventArgs> missingDataCallback;

        public XamlRenderer(RenderOptions options,
            ResourceDictionary resources,
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
            : base(options)
        {
            this.Resources = resources;
            this.actionCallback = actionCallback;
            this.missingDataCallback = missingDataCallback;
        }

#if WPF
        public XamlRenderer(RenderOptions options, string stylePath,
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
            : base(options)
        {
            this.StylePath = stylePath;
            this.actionCallback = actionCallback;
            this.missingDataCallback = missingDataCallback;
        }
#endif
        /// <summary>
        /// Resource dictionary to use when rendering
        /// </summary>
        private ResourceDictionary _resources;
        public ResourceDictionary Resources
        {
            get
            {
                if (_resources != null)
                    return _resources;

                using (var styleStream = File.OpenRead(this.StylePath))
                {
                    _resources = (ResourceDictionary)XamlReader.Load(styleStream);
                }
                return _resources;
            }
            set
            {
                this._resources = value;
            }
        }

        /// <summary>
        /// Path to Xaml resource dictionary
        /// </summary>
        private string _stylePath;
        public string StylePath
        {
            get { return _stylePath; }
            set
            {
                this._stylePath = value;
                this._resources = null;
            }
        }

        /// <summary>
        /// AdaptiveCard
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        public FrameworkElement RenderAdaptiveCard(AdaptiveCard card)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback);
            return Render(card, context);
        }

        public FrameworkElement RenderShowCard(ActionShowCard showCard)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback);
            return Render(showCard.Card, context);
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

            Debug.WriteLine($"Unable to find Style {styleName} from the supplied ResourceDictionary");
            return null;
        }
    }
}
