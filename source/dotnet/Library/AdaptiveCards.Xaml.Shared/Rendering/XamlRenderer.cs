using System;
using System.Diagnostics;
using System.IO;
using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Markup;
#elif XAMARIN
using Xamarin.Forms;
#endif


namespace AdaptiveCards.Rendering
{
    public partial class XamlRenderer : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
        protected Action<object, ActionEventArgs> actionCallback;
        protected Action<object, MissingInputEventArgs> missingDataCallback;
        protected HostOptions _defaultCardStyling;

        public XamlRenderer(HostOptions options,
            ResourceDictionary resources,
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
            : base(options)
        {
            this.Resources = resources;
            this.actionCallback = actionCallback;
            this.missingDataCallback = missingDataCallback;
            AddDefaultRenderers();
        }

#if WPF
        public XamlRenderer(HostOptions options,
            string stylePath,
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
            : base(options)
        {
            this.StylePath = stylePath;
            this.actionCallback = actionCallback;
            this.missingDataCallback = missingDataCallback;
            AddDefaultRenderers();
        }
#endif

        private void AddDefaultRenderers()
        {
            base.ElementRenderers["AdaptiveCard"] = RenderAdaptiveCard;
            base.ElementRenderers["TextBlock"] = RenderTextBlock;
            base.ElementRenderers["Image"] = RenderImage;
            base.ElementRenderers["Container"] = RenderContainer;
            base.ElementRenderers["Column"] = RenderColumn;
            base.ElementRenderers["ColumnSet"] = RenderColumnSet;
            base.ElementRenderers["ActionSet"] = RenderActionSet;
            base.ElementRenderers["FactSet"] = RenderFactSet;
            base.ElementRenderers["ImageSet"] = RenderImageSet;
            base.ElementRenderers["Input.Text"] = RenderInputText;
            base.ElementRenderers["Input.Number"] = RenderInputNumber;
            base.ElementRenderers["Input.Date"] = RenderInputDate;
            base.ElementRenderers["Input.ChoiceSet"] = RenderInputChoiceSet;
            base.ElementRenderers["Input.Time"] = RenderInputTime;
            base.ElementRenderers["Input.Toggle"] = RenderInputToggle;
            base.ElementRenderers["Action.Submit"] = RenderActionSubmit;
            base.ElementRenderers["Action.Http"] = RenderActionHttp;
            base.ElementRenderers["Action.OpenUrl"] = RenderActionOpenUrl;
            base.ElementRenderers["Action.ShowCard"] = RenderActionShowCard;
        }

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

#if WPF
                using (var styleStream = File.OpenRead(this.StylePath))
                {
                    _resources = (ResourceDictionary)XamlReader.Load(styleStream);
                }
#elif XAMARIN
                // TODO
#endif
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


#if WPF
        /// <summary>
        /// AdaptiveCard
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        public FrameworkElement RenderAdaptiveCard(AdaptiveCard card, Func<string, MemoryStream> imageResolver = null, HostOptions styling = null)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback, imageResolver)
            {
                Options = styling ?? this.DefaultOptions,
                Resources = this.Resources,
                ElementRenderers = this.ElementRenderers
            };
            return context.Render(card);
        }

        public FrameworkElement RenderShowCard(ShowCardAction showCard, Func<string, MemoryStream> imageResolver = null, HostOptions styling = null)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback, imageResolver)
            {
                Options = styling ?? this.DefaultOptions,
                Resources = this.Resources,
                ElementRenderers = this.ElementRenderers
            };

            return context.Render(showCard.Card);
        }

#elif XAMARIN
        /// <summary>
        /// AdaptiveCard
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        public View RenderAdaptiveCard(AdaptiveCard card, Func<string, MemoryStream> imageResolver = null, HostOptions options = null)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback, imageResolver)
            {
                Options = options ?? this.DefaultOptions
            };
            return context.Render(card);
        }

        public View RenderShowCard(ShowCardAction showCard, Func<string, MemoryStream> imageResolver = null, HostOptions options = null)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback, imageResolver)
            {
                Options = options ?? this.DefaultOptions
            };
            return context.Render(showCard.Card);
        }

#endif

    }
}
