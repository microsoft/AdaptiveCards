using System;
using System.Collections.Generic;
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
        public const string ContentType = "application/vnd.microsoft.card.adaptive";

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
        /// The Body elements for this card
        /// </summary>
        [JsonProperty(Order = -3)]
        public List<AdaptiveElement> Body { get; set; } = new List<AdaptiveElement>();

        public bool ShouldSerializeBody() => Body?.Count > 0;


        /// <summary>
        ///     Actions for the card
        /// </summary>
        [JsonProperty(Order = -2)]
        public List<AdaptiveAction> Actions { get; set; } = new List<AdaptiveAction>();

        public bool ShouldSerializeActions() => Actions?.Count > 0;

        /// <summary>
        ///     Speak annotation for the card
        /// </summary>
        [JsonProperty(Order = -6, NullValueHandling = NullValueHandling.Ignore)]
        public string Speak { get; set; }

        /// <summary>
        ///     Title for the card (used when displayed in a dialog)
        /// </summary>
        [JsonProperty(Order = -5, NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("The Title property is not officially supported right now and should not be used")]
        public string Title { get; set; }

        /// <summary>
        ///     Background image for card
        /// </summary>
        [JsonProperty(Order = -4, NullValueHandling = NullValueHandling.Ignore)]
        public string BackgroundImage { get; set; } // TODO: Should this be Uri?

        /// <summary>
        ///     Version of schema that this card was authored. Defaults to the latest Adaptive Card schema version that this library supports.
        /// </summary>
        [JsonProperty(Order = -9, NullValueHandling = NullValueHandling.Ignore)]
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


        /// <summary>
        ///  Serialize this Adaptive Card to JSON
        /// </summary>
        /// <returns></returns>
        public string ToJson()
        {
            var settings = new JsonSerializerSettings
            {
                Converters =
                {
                    new AdaptiveCardConverter(),
                    new AdaptiveTypedElementConverter(),
                    new IgnoreEmptyItemsConverter<AdaptiveAction>(),
                    new IgnoreEmptyItemsConverter<AdaptiveElement>()
                }
            };
            return JsonConvert.SerializeObject(this, Formatting.Indented, settings);
        }
    }
}