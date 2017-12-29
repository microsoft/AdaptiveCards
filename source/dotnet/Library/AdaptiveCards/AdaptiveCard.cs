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
        public ObservableCollection<AdaptiveElement> Body { get { return _Body; } set { SetValue(ref _Body, value); } }
        private ObservableCollection<AdaptiveElement> _Body = new ObservableCollection<AdaptiveElement>();

        /// <summary>
        ///     Actions for the card
        /// </summary>
        [JsonProperty(Order = -2)]
        public ObservableCollection<AdaptiveAction> Actions { get { return _Actions; } set { SetValue(ref _Actions, value); } }
        private ObservableCollection<AdaptiveAction> _Actions = new ObservableCollection<AdaptiveAction>();

        /// <summary>
        ///     Speak annotation for the card
        /// </summary>
        [JsonProperty(Order = -6, NullValueHandling = NullValueHandling.Ignore)]
        public string Speak { get { return _Speak; } set { SetValue(ref _Speak, value); } }
        private string _Speak;

        /// <summary>
        ///     Title for the card (used when displayed in a dialog)
        /// </summary>
        [JsonProperty(Order = -5, NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("The Title property is not officially supported right now and should not be used")]
        public string Title { get { return _Title; } set { SetValue(ref _Title, value); } }
        private string _Title;

        /// <summary>
        ///     Background image for card
        /// </summary>
        [JsonProperty(Order = -4, NullValueHandling = NullValueHandling.Ignore)]
        public string BackgroundImage { get { return _BackgroundImage; } set { SetValue(ref _BackgroundImage, value); } } // TODO: Should this be Uri?
        private string _BackgroundImage;

        /// <summary>
        ///     Version of schema that this card was authored. Defaults to the latest Adaptive Card schema version that this library supports.
        /// </summary>
        [JsonProperty(Order = -9, NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveSchemaVersion Version { get { return _Version; } set { SetValue(ref _Version, value); } }
        private AdaptiveSchemaVersion _Version;

        /// <summary>
        ///     if a client doesn't support the minVersion the card should be rejected.  If it does, then the elements that are not
        ///     supported are safe to ignore
        /// </summary>
        [JsonProperty(Order = -8, NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveSchemaVersion MinVersion { get { return _MinVersion; } set { SetValue(ref _MinVersion, value); } }
        private AdaptiveSchemaVersion _MinVersion;

        /// <summary>
        ///     if a client is not able to show the card, show fallbackText to the user. This can be in markdown format.
        /// </summary>
        [JsonProperty(Order = -7, NullValueHandling = NullValueHandling.Ignore)]
        public string FallbackText { get { return _FallbackText; } set { SetValue(ref _FallbackText, value); } }
        private string _FallbackText;

        /// <summary>
        /// WS ServiceUrl for live cards
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string ServiceUrl { get { return _ServiceUrl; } set { SetValue(ref _ServiceUrl, value); } }
        private string _ServiceUrl;

        /// <summary>
        /// Events to subscribe to for this element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ObservableCollection<string> Events { get { return _events; } set { _events = value; FirePropertyChanged(); } }
        private ObservableCollection<string> _events = new ObservableCollection<string>();

        public void SetEvents()
        {
            if (this.OnCardActivate != null)
                _events.Add(EventTypes.OnCardActivate);
            if (this.OnCardDeactivate != null)
                _events.Add(EventTypes.OnCardDeactivate);
        }

        public event EventHandler OnCardActivate;
        public event EventHandler OnCardDeactivate;

        public void Activate()
        {
            OnCardActivate?.Invoke(this, new EventArgs());
        }

        public void Deactivate()
        {
            OnCardDeactivate?.Invoke(this, new EventArgs());
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