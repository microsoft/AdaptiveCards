using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Adaptive card which has flexible container
    /// </summary>
    [JsonConverter(typeof(AdaptiveCardConverter))]
#if !NETSTANDARD1_3
    [XmlRoot(ElementName = "Card")]
#endif
    public class AdaptiveCard : AdaptiveTypedElement
#if WINDOWS_UWP
      // TODO: uncomment when I figure out the Windows build
       //   , Windows.UI.Shell.IAdaptiveCard
#endif
    {
        public const string ContentType = "application/vnd.microsoft.card.adaptive";

        public const string TypeName = "AdaptiveCard";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

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
        [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveElement>))]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveTextBlock))]
        [XmlElement(typeof(AdaptiveImage))]
        [XmlElement(typeof(AdaptiveContainer))]
        [XmlElement(typeof(AdaptiveColumnSet))]
        [XmlElement(typeof(AdaptiveImageSet))]
        [XmlElement(typeof(AdaptiveFactSet))]
        [XmlElement(typeof(AdaptiveTextInput))]
        [XmlElement(typeof(AdaptiveDateInput))]
        [XmlElement(typeof(AdaptiveTimeInput))]
        [XmlElement(typeof(AdaptiveNumberInput))]
        [XmlElement(typeof(AdaptiveToggleInput))]
        [XmlElement(typeof(AdaptiveChoiceSetInput))]
#endif
        public List<AdaptiveElement> Body { get; set; } = new List<AdaptiveElement>();

        public bool ShouldSerializeBody() => Body?.Count > 0;

        /// <summary>
        ///     Actions for the card
        /// </summary>
        [JsonProperty(Order = -2)]
        [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveAction>))]
#if !NETSTANDARD1_3
        [XmlArray("Actions")]
        [XmlArrayItem(ElementName = "OpenUrl", Type = typeof(AdaptiveOpenUrlAction))]
        [XmlArrayItem(ElementName = "ShowCard", Type = typeof(AdaptiveShowCardAction))]
        [XmlArrayItem(ElementName = "Submit", Type = typeof(AdaptiveSubmitAction))]
#endif
        public List<AdaptiveAction> Actions { get; set; } = new List<AdaptiveAction>();

        public bool ShouldSerializeActions() => Actions?.Count > 0;

        /// <summary>
        ///     Speak annotation for the card
        /// </summary>
        [JsonProperty(Order = -6, NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
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
        [JsonProperty(Order = -4, DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public Uri BackgroundImage { get; set; }

        /// <summary>
        ///     This is necessary for XML serialization. You should use the <see cref="F:BackgroundImage" /> property directly.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlAttribute("BackgroundImage")]
        [Browsable(false), EditorBrowsable(EditorBrowsableState.Never)]
#endif
        [JsonIgnore]
        public string BackgroundImageString
        {
            get { return BackgroundImage?.ToString(); }
            set { BackgroundImage = new Uri(value); }
        }

        /// <summary>
        ///     Schema version that this card requires. If a client is lower than this version the fallbackText will be rendered.
        /// </summary>
        [JsonProperty(Order = -9, DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate, NullValueHandling = NullValueHandling.Include)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveSchemaVersion Version { get; set; }

        /// <summary>
        ///     This is obsolete. Use the <see cref="Version" property instead/>
        /// </summary>
        [JsonProperty(Order = -8, NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("Use the Version property instead")]
        public AdaptiveSchemaVersion MinVersion { get; set; }

        /// <summary>
        ///     Text shown when the client doesn’t support the version specified. This can be in markdown format.
        /// </summary>
        [JsonProperty(Order = -7, NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string FallbackText { get; set; }

        /// <summary>
        ///     The 2-letter ISO-639-1 language used in the card. Used to localize any date/time functions
        /// </summary>
        [JsonProperty(Order = -6, NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Lang { get; set; }

        /// <summary>
        /// Parse an AdaptiveCard from a JSON string
        /// </summary>
        /// <param name="json">A JSON-serialized Adaptive Card</param>
        /// <returns></returns>
        public static AdaptiveCardParseResult FromJson(string json)
        {
            var parseResult = new AdaptiveCardParseResult();

            try
            {
                parseResult.Card = JsonConvert.DeserializeObject<AdaptiveCard>(json, new JsonSerializerSettings
                {
                    ContractResolver = new WarningLoggingContractResolver(parseResult)
                });
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
            return JsonConvert.SerializeObject(this, Newtonsoft.Json.Formatting.Indented);
        }

        /// <summary>
        /// This makes sure the $schema property doesn't show up in AdditionalProperties
        /// </summary>
        [JsonProperty("$schema")]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        internal string JsonSchema { get; set; }

        public bool ShouldSerializeJsonSchema()
        {
            return false;
        }
    }
}