using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Adaptive card which has flexible container
    /// </summary>
    public class AdaptiveCard : AdaptiveTypedElement
#if WINDOWS_UWP
      // TODO: uncomment when I figure out the Windows build
       //   , Windows.UI.Shell.IAdaptiveCard
#endif
    {
        public const string TypeName = "AdaptiveCard";

        public override string Type => TypeName;

        /// <summary>
        /// The latest known schema version supported by this library
        /// </summary>
        public static AdaptiveSchemaVersion KnownSchemaVersion = new AdaptiveSchemaVersion(1, 0);

        /// <summary>
        /// Creates an AdaptiveCard using a specific schema version
        /// </summary>
        /// <param name="schemaVersion">The schema version to use</param>
        public AdaptiveCard(AdaptiveSchemaVersion schemaVersion)
        {
            Version = schemaVersion;
        }


        /// <inheritdoc />
        /// <param name="schemaVersion">The schema version to use</param>
        public AdaptiveCard(string schemaVersion) : this(new AdaptiveSchemaVersion(schemaVersion)) { }

        /// <inheritdoc />
        /// <summary>
        /// Creates an AdaptiveCard using the <see cref="F:AdaptiveCards.AdaptiveCard.KnownSchemaVersion" /> of this library
        /// </summary>
        public AdaptiveCard() : this(KnownSchemaVersion) { }


        /// <summary>
        /// Parse an AdaptiveCard from a JSON string
        /// </summary>
        /// <param name="json">A JSON-serialized Adaptive Card</param>
        /// <returns></returns>
        public static AdaptiveCardParseResult FromJson(string json)
        {
            var parseResult = new AdaptiveCardParseResult();

            var settings = new JsonSerializerSettings
            {
                Converters =
                    {
                        new AdaptiveCardConverter(parseResult),
                        new AdaptiveTypedElementConverter(parseResult),
                        new IgnoreEmptyItemsConverter<AdaptiveAction>(),
                        new IgnoreEmptyItemsConverter<AdaptiveElement>()
                    }
            };
            try
            {
                parseResult.Card = JsonConvert.DeserializeObject<AdaptiveCard>(json, settings);
            }
            catch (JsonException ex)
            {
                throw new AdaptiveSerializationException(ex.Message, ex);
            }

            return parseResult;
        }

        public const string ContentType = "application/vnd.microsoft.card.adaptive";

        /// <summary>
        /// The Body elements for this card
        /// </summary>
        [JsonProperty(Order = -3)]
        public ObservableCollection<AdaptiveElement> Body { get { return _Body; } set { SetPropertyValue(ref _Body, value); } }
        private ObservableCollection<AdaptiveElement> _Body = new ObservableCollection<AdaptiveElement>();

        /// <summary>
        ///     Actions for the card
        /// </summary>
        [JsonProperty(Order = -2)]
        public ObservableCollection<AdaptiveAction> Actions { get { return _Actions; } set { SetPropertyValue(ref _Actions, value); } }
        private ObservableCollection<AdaptiveAction> _Actions = new ObservableCollection<AdaptiveAction>();

        /// <summary>
        ///     Speak annotation for the card
        /// </summary>
        [JsonProperty(Order = -6, NullValueHandling = NullValueHandling.Ignore)]
        public string Speak { get { return _Speak; } set { SetPropertyValue(ref _Speak, value); } }
        private string _Speak;

        /// <summary>
        ///     Title for the card (used when displayed in a dialog)
        /// </summary>
        [JsonProperty(Order = -5, NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("The Title property is not officially supported right now and should not be used")]
        public string Title { get { return _Title; } set { SetPropertyValue(ref _Title, value); } }
        private string _Title;

        /// <summary>
        ///     Background image for card
        /// </summary>
        [JsonProperty(Order = -4, NullValueHandling = NullValueHandling.Ignore)]
        public string BackgroundImage { get { return _BackgroundImage; } set { SetPropertyValue(ref _BackgroundImage, value); } } // TODO: Should this be Uri?
        private string _BackgroundImage;

        /// <summary>
        ///     Version of schema that this card was authored. Defaults to the latest Adaptive Card schema version that this library supports.
        /// </summary>
        [JsonProperty(Order = -9, NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveSchemaVersion Version { get { return _Version; } set { SetPropertyValue(ref _Version, value); } }
        private AdaptiveSchemaVersion _Version;

        /// <summary>
        ///     if a client doesn't support the minVersion the card should be rejected.  If it does, then the elements that are not
        ///     supported are safe to ignore
        /// </summary>
        [JsonProperty(Order = -8, NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveSchemaVersion MinVersion { get { return _MinVersion; } set { SetPropertyValue(ref _MinVersion, value); } }
        private AdaptiveSchemaVersion _MinVersion;

        /// <summary>
        ///     if a client is not able to show the card, show fallbackText to the user. This can be in markdown format.
        /// </summary>
        [JsonProperty(Order = -7, NullValueHandling = NullValueHandling.Ignore)]
        public string FallbackText { get { return _FallbackText; } set { SetPropertyValue(ref _FallbackText, value); } }
        private string _FallbackText;

        /// <summary>
        /// WS ServiceUrl for live cards
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string ServiceUrl { get { return _ServiceUrl; } set { SetPropertyValue(ref _ServiceUrl, value); } }
        private string _ServiceUrl;

        /// <summary>
        /// Events to subscribe to for this element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ObservableCollection<string> Events { get { return _events; } set { _events = value; FirePropertyChanged(); } }
        private ObservableCollection<string> _events = new ObservableCollection<string>();

        private event EventHandler _OnCardActivate;
        public event EventHandler OnCardActivate
        {
            add { _OnCardActivate += value; this.Events.Add(EventTypes.OnCardActivate); }
            remove { _OnCardActivate -= value; this.Events.Remove(EventTypes.OnCardActivate); }
        }

        private event EventHandler _OnCardDeactivate;
        public event EventHandler OnCardDeactivate
        {
            add { _OnCardDeactivate += value; this.Events.Add(EventTypes.OnCardDeactivate); }
            remove { _OnCardDeactivate -= value; this.Events.Remove(EventTypes.OnCardDeactivate); }
        }

        public void FireActivate()
        {
            _OnCardActivate?.Invoke(this, new EventArgs());
        }

        public void FireDeactivate()
        {
            _OnCardDeactivate?.Invoke(this, new EventArgs());
        }

        /// <summary>
        ///  Serialize this Adaptive Card to JSON
        /// </summary>
        /// <returns></returns>
        public string ToJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }
    }
}