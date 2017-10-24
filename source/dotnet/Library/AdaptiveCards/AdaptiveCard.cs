using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    /// <summary>
    ///     Adaptive card which has flexible container
    /// </summary>
    [JsonConverter(typeof(AdaptiveCardConverter))]
    public class AdaptiveCard : AdaptiveTypedElement
#if WINDOWS_UWP
      // TODO: uncomment when I figure out the Windows build
       //   , Windows.UI.Shell.IAdaptiveCard
#endif
    {
        public const string TypeName = "AdaptiveCard";

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
            Type = TypeName;
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
            AdaptiveCard card = null;

            try
            {
                card = JsonConvert.DeserializeObject<AdaptiveCard>(json);
            }

            catch
            {
                Debugger.Break();
                // TODO: Return errors here
            }

            return new AdaptiveCardParseResult(card);
        }

        public const string ContentType = "application/vnd.microsoft.card.adaptive";

        /// <summary>
        /// The Body elements for this card
        /// </summary>
        [JsonProperty(Order = -3)]
        public List<AdaptiveElement> Body { get; set; } = new List<AdaptiveElement>();

        /// <summary>
        ///     Actions for the card
        /// </summary>
        [JsonProperty(Order = -2, NullValueHandling = NullValueHandling.Ignore)]
        public List<AdaptiveActionBase> Actions { get; set; } = new List<AdaptiveActionBase>();

        /// <summary>
        ///     Speak annotation for the card
        /// </summary>
        [JsonProperty(Order = -6, NullValueHandling = NullValueHandling.Ignore)]
        public string Speak { get; set; }

        /// <summary>
        ///     Title for the card (used when displayed in a dialog)
        /// </summary>
        [JsonProperty(Order = -5, NullValueHandling = NullValueHandling.Ignore)]
        public string Title { get; set; }

        /// <summary>
        ///     Background image for card
        /// </summary>
        [JsonProperty(Order = -4, NullValueHandling = NullValueHandling.Ignore)]
        public string BackgroundImage { get; set; } // TODO: Should this be Uri?

        /// <summary>
        ///     Version of schema that this card was authored. Defaults to the latest Adaptive Card schema version that this library supports.
        /// </summary>
        [JsonProperty(Order = -9)]
        public AdaptiveSchemaVersion Version { get; set; }

        /// <summary>
        ///     if a client doesn't support the minVersion the card should be rejected.  If it does, then the elements that are not
        ///     supported are safe to ignore
        /// </summary>
        [JsonProperty(Order = -8, NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveSchemaVersion MinVersion { get; set; }

        /// <summary>
        ///     if a client is not able to show the card, show fallbackText to the user. This can be in markdown format.
        /// </summary>
        [JsonProperty(Order = -7, NullValueHandling = NullValueHandling.Ignore)]
        public string FallbackText { get; set; }

        /// <summary>
        ///  Serialize this Adaptive Card to JSON
        /// </summary>
        /// <returns></returns>
        public string ToJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }
    }

    public class AdaptiveCardConverter : JsonConverter
    {
        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }

        public override bool CanWrite => false;

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var jObject = JObject.Load(reader);

            var card = (AdaptiveCard) Activator.CreateInstance(objectType);
            // Get the version from the payload
            card.Version = null;

            serializer.Populate(jObject.CreateReader(), card);

            if (card.Version == null)
                return null;

            card.Actions.RemoveAll(item => item == null);
            card.Body.RemoveAll(item => item == null);

            return card;
        }

        public override bool CanConvert(Type objectType)
        {
            return typeof(AdaptiveCard).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }
    }
}