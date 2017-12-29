using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace AdaptiveCards
{
    /// <summary>
    ///     Base class for all elements in a container
    /// </summary>
    public abstract class AdaptiveElement : AdaptiveTypedElement
    {
        /// <summary>
        /// The amount of space the element should be separated from the previous element. Default value is <see cref="Spacing.Default"/>.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveSpacing Spacing { get { return _Spacing; } set { SetPropertyValue(ref _Spacing, value); } }
        private AdaptiveSpacing _Spacing;

        /// <summary>
        /// Indicates whether there should be a visible separator (e.g. a line) between the element and the one before it.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public bool Separator { get { return _Separator; } set { SetPropertyValue(ref _Separator, value); } }
        private bool _Separator;

        /// <summary>
        /// Events to subscribe to for this element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ObservableCollection<string> Events { get { return _Events; }  set { SetPropertyValue(ref _Events, value); } } 
        private ObservableCollection<string> _Events = new ObservableCollection<string>();

        /// <summary>
        ///     SSML fragment for spoken interaction
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("CardElement.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get { return _Speak; } set { SetPropertyValue(ref _Speak, value); } }
        private string _Speak;

        /// <summary>
        ///     How should this element be emphasized relative to previous element
        /// </summary>
        [JsonIgnore]
        [Obsolete("Use Separator and Spacing instead")]
#pragma warning disable 612, 618
        public AdaptiveSeparationStyle Separation
        {
            get
            {
                // There's no good way to back-compat convert this, so we'll just go
                // based on the spacing value
                switch (Spacing)
                {
                    case AdaptiveSpacing.None:
                        return AdaptiveSeparationStyle.None;

                    case AdaptiveSpacing.Large:
                        return AdaptiveSeparationStyle.Strong;

                    default:
                        return AdaptiveSeparationStyle.Default;
                }
            }

            set
            {
                // Back-compat for upgrading the obsolete Separation value to the new values
                switch (value)
                {
                    case AdaptiveSeparationStyle.Default:
                        Separator = false;
                        Spacing = AdaptiveSpacing.Default;
                        break;

                    case AdaptiveSeparationStyle.None:
                        Separator = false;
                        Spacing = AdaptiveSpacing.None;
                        break;

                    case AdaptiveSeparationStyle.Strong:
                        Separator = true;
                        Spacing = AdaptiveSpacing.Large;
                        break;

                    default:
                        throw new NotImplementedException();
                }
                FirePropertyChanged();
            }
        }
#pragma warning restore 612, 618

        // Allow deserializing but not serializing: https://stackoverflow.com/questions/11564091/making-a-property-deserialize-but-not-serialize-with-json-net
        [JsonProperty("separation")]
#pragma warning disable 612, 618
        private AdaptiveSeparationStyle SeparationSetter
        {
            set
            {
                Separation = value;
            }
        }
#pragma warning restore 612, 618

        private event EventHandler _OnClick;
        public event EventHandler OnClick
        {
            add { _OnClick += value; this.Events.Add(EventTypes.OnClick); }
            remove { _OnClick -= value; this.Events.Remove(EventTypes.OnClick); }
        }

        private event EventHandler _OnMouseEnter;
        public event EventHandler OnMouseEnter
        {
            add { _OnMouseEnter += value; this.Events.Add(EventTypes.OnMouseEnter); }
            remove { _OnMouseEnter -= value; this.Events.Remove(EventTypes.OnMouseEnter); }
        }

        private event EventHandler _OnMouseLeave;
        public event EventHandler OnMouseLeave
        {
            add { _OnMouseLeave += value; this.Events.Add(EventTypes.OnMouseLeave); }
            remove { _OnMouseLeave -= value; this.Events.Remove(EventTypes.OnMouseLeave); }
        }

        public void FireClick()
        {
            _OnClick?.Invoke(this, new EventArgs());
        }

        public void FireMouseEnter()
        {
            _OnMouseEnter?.Invoke(this, new EventArgs());
        }

        public void FireMouseLeave()
        {
            _OnMouseLeave?.Invoke(this, new EventArgs());
        }
    }
}