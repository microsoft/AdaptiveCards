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
            SetObjectTypes();
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
            SetObjectTypes();
        }
#endif

        private void SetObjectTypes()
        {
            TypedElementConverter.RegisterTypedElement<XamlAdaptiveCard>("AdaptiveCard");
            TypedElementConverter.RegisterTypedElement<XamlTextBlock>("TextBlock");
            TypedElementConverter.RegisterTypedElement<XamlImage>("Image");
            TypedElementConverter.RegisterTypedElement<XamlContainer>("Container");
            TypedElementConverter.RegisterTypedElement<XamlColumn>("Column");
            TypedElementConverter.RegisterTypedElement<XamlColumnSet>("ColumnSet");
            TypedElementConverter.RegisterTypedElement<XamlActionSet>("ActionSet");
            TypedElementConverter.RegisterTypedElement<XamlFactSet>("FactSet");
            TypedElementConverter.RegisterTypedElement<XamlImageSet>("ImageSet");
            TypedElementConverter.RegisterTypedElement<XamlTextInput>("Input.Text");
            TypedElementConverter.RegisterTypedElement<XamlNumberInput>("Input.Number");
            TypedElementConverter.RegisterTypedElement<XamlDateInput>("Input.Date");
            TypedElementConverter.RegisterTypedElement<XamlChoiceSet>("Input.ChoiceSet");
            TypedElementConverter.RegisterTypedElement<XamlTimeInput>("Input.Time");
            TypedElementConverter.RegisterTypedElement<XamlToggleInput>("Input.Toggle");
            TypedElementConverter.RegisterTypedElement<XamlSubmitAction>("Action.Submit");
            TypedElementConverter.RegisterTypedElement<XamlHttpAction>("Action.Http");
            TypedElementConverter.RegisterTypedElement<XamlOpenUrlAction>("Action.OpenUrl");
            TypedElementConverter.RegisterTypedElement<XamlShowCardAction>("Action.ShowCard");
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
        public FrameworkElement RenderAdaptiveCard(AdaptiveCard card, Func<string, MemoryStream> imageResolver = null, HostOptions options = null)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback, imageResolver)
            {
                Options = options ?? this.DefaultOptions,
                Resources = this.Resources
            };
            return context.Render(card);
        }

        public FrameworkElement RenderShowCard(ShowCardAction showCard, Func<string, MemoryStream> imageResolver = null, HostOptions options = null)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback, imageResolver)
            {
                Options = options ?? this.DefaultOptions,
                Resources = this.Resources
            };

            return context.Render(showCard);
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
            return context.Render(showCard);
        }

#endif

    }
}
