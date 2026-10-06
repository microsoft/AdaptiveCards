// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Xml;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Adaptive card which has flexible container
    /// </summary>
    [XmlRoot(ElementName = "Card")]
    public class AdaptiveCard : AdaptiveTypedElement
    {
        /// <summary>
        /// AdaptiveCard mimetype.
        /// </summary>
        public const string ContentType = "application/vnd.microsoft.card.adaptive";

        /// <summary>
        /// The AdaptiveCard element that this class implements.
        /// </summary>
        public const string TypeName = "AdaptiveCard";

        /// <inheritdoc/>
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// The latest known schema version supported by this library.
        /// </summary>
        public static AdaptiveSchemaVersion KnownSchemaVersion = new AdaptiveSchemaVersion(1, 6);

        /// <summary>
        /// Creates an AdaptiveCard using a specific schema version.
        /// </summary>
        /// <param name="schemaVersion">The schema version to use</param>
        public AdaptiveCard(AdaptiveSchemaVersion schemaVersion)
        {
            Version = schemaVersion;
        }

        /// <inheritdoc />
        /// <param name="schemaVersion">The schema version to use</param>.
        public AdaptiveCard(string schemaVersion) : this(new AdaptiveSchemaVersion(schemaVersion)) { }

        /// <inheritdoc />
        /// <summary>
        /// Creates an AdaptiveCard using the <see cref="F:AdaptiveCards.AdaptiveCard.KnownSchemaVersion" /> of this library.
        /// </summary>
        [Obsolete("Please use the overload that accepts a version parameter and specify the version your card requires")]
        public AdaptiveCard() : this(new AdaptiveSchemaVersion(1, 0)) { }

        /// <summary>
        /// Schema version that this card requires. If a client is lower than this version the fallbackText will be rendered.
        /// </summary>
        [JsonPropertyOrder(-10)]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlElement]
        [DefaultValue(null)]
        public AdaptiveSchemaVersion Version { get; set; }

        /// <summary>
        /// This is obsolete. Use the <see cref="Version"/> property instead.
        /// </summary>
        [JsonPropertyOrder(-9)]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [Obsolete("Use the Version property instead")]
        public AdaptiveSchemaVersion MinVersion { get; set; }

        /// <summary>
        /// Text shown when the client doesn’t support the version specified. This can be in markdown format.
        /// </summary>
        [JsonPropertyOrder(-8)]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string FallbackText { get; set; }

        /// <summary>
        /// Speak annotation for the card.
        /// </summary>
        [JsonPropertyOrder(-7)]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlElement]
        [DefaultValue(null)]
        public string Speak { get; set; }

        /// <summary>
        /// The 2-letter ISO-639-1 language used in the card. Used to localize any date/time functions.
        /// </summary>
        [JsonPropertyOrder(-7)]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Lang { get; set; }

        /// <summary>
        /// Title for the card (used when displayed in a dialog).
        /// </summary>
        [JsonPropertyOrder(-6)]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [Obsolete("The Title property is not officially supported right now and should not be used")]
        public string Title { get; set; }

        /// <summary>
        /// Background image for card.
        /// </summary>
        [XmlElement]
        [JsonPropertyOrder(-5)]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [JsonConverter(typeof(AdaptiveBackgroundImageConverter))]
        [DefaultValue(null)]
        public AdaptiveBackgroundImage BackgroundImage { get; set; }

        /// <summary>
        /// Value that denotes if the card must use all the vertical space that is set to it. Default value is <see cref="AdaptiveHeightType.Auto"/>.
        /// </summary>
        [JsonConverter(typeof(AdaptiveHeightConverter))]
        [JsonPropertyOrder(-4)]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlElement]
        public AdaptiveHeight Height { get; set; } = new AdaptiveHeight(AdaptiveHeightType.Auto);

        /// <summary>
        /// Explicit card minimum height with 'px'. (100px, 200px)
        /// </summary>
        [JsonPropertyName("minHeight")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string MinHeight { get; set; }

        /// <summary>
        /// PixelMinHeight if height is not auto/stretch
        /// </summary>
        [JsonIgnore]
        [XmlIgnore]
        public uint PixelMinHeight { get => uint.TryParse(MinHeight?.Replace("px", ""), out var val) ? (uint)val : 0; set => MinHeight = $"{value}px"; }

        /// <summary>
        /// The Body elements for this card.
        /// </summary>
        [JsonPropertyOrder(-3)]
        [XmlElement(typeof(AdaptiveTextBlock))]
        [XmlElement(typeof(AdaptiveRichTextBlock))]
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
        [XmlElement(typeof(AdaptiveMedia))]
        [XmlElement(typeof(AdaptiveActionSet))]
        [XmlElement(typeof(AdaptiveTable))]
        [XmlElement(typeof(AdaptiveUnknownElement))]
        public List<AdaptiveElement> Body { get; set; } = new List<AdaptiveElement>();

        /// <summary>
        /// Sets the text flow direction
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlIgnore]
        [DefaultValue(null)]
        public bool? Rtl { get; set; } = null;

        /// <summary>
        /// Controls XML serialization of style.
        /// </summary>
        // The XML serializer doesn't handle nullable value types. This allows serialization if non-null.
        [JsonIgnore]
        [XmlAttribute("Rtl")]
        [EditorBrowsable(EditorBrowsableState.Never)]
        public bool RtlXml { get { return (Rtl.HasValue) ? Rtl.Value : false; } set { Rtl = value; } }

        /// <summary>
        /// Determines whether to serialize the style for XML.
        /// </summary>
        public bool ShouldSerializeRtlXml() => this.Rtl.HasValue;

        /// <summary>
        /// The Actions for this card.
        /// </summary>
        [JsonPropertyOrder(-2)]
        [XmlElement(typeof(AdaptiveOpenUrlAction))]
        [XmlElement(typeof(AdaptiveShowCardAction))]
        [XmlElement(typeof(AdaptiveSubmitAction))]
        [XmlElement(typeof(AdaptiveToggleVisibilityAction))]
        [XmlElement(typeof(AdaptiveExecuteAction))]
        [XmlElement(typeof(AdaptiveUnknownAction))]
        public List<AdaptiveAction> Actions { get; set; } = new List<AdaptiveAction>();

        /// <summary>
        /// This makes sure the $schema property doesn't show up in AdditionalProperties
        /// </summary>
        [JsonPropertyName("$schema")]
        [JsonInclude]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlIgnore]
        internal string JsonSchema { get; set; }

        /// <summary>
        /// The content alignment for the element inside the container.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlElement]
        [DefaultValue(typeof(AdaptiveVerticalContentAlignment), "top")]
        public AdaptiveVerticalContentAlignment VerticalContentAlignment { get; set; }

        /// <summary>
        /// Action for the card (this allows a default action at the card level)
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlElement]
        [DefaultValue(null)]
        public AdaptiveAction SelectAction { get; set; }

        /// <summary>
        /// Defines how the card can be refreshed by making a request to the target Bot.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlElement]
        [DefaultValue(null)]
        public AdaptiveRefresh Refresh { get; set; }

        /// <summary>
        /// Defines authentication information to enable on-behalf-of single sign on or just-in-time OAuth.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlElement]
        [DefaultValue(null)]
        public AdaptiveAuthentication Authentication { get; set; }

        /// <summary>
        /// Defines various metadata properties typically not used for rendering the card
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlElement]
        [DefaultValue(null)]
        public AdaptiveMetadata Metadata { get; set; }

        /// <summary>
        /// Callback that will be invoked should a null or empty version string is encountered. The callback may return an alternate version to use for parsing.
        /// </summary>
        /// <example>
        ///     AdaptiveCard.OnDeserializingMissingVersion = () => new AdaptiveSchemaVersion(0, 5);
        /// </example>
        public static Func<AdaptiveSchemaVersion> OnDeserializingMissingVersion { get; set; }

        /// <summary>
        /// Parse an AdaptiveCard from a JSON string.
        /// </summary>
        /// <param name="json">A JSON-serialized Adaptive Card.</param>
        /// <returns>The result of parsing <paramref name="json"/>.</returns>
        public static AdaptiveCardParseResult FromJson(string json)
        {
            var parseResult = new AdaptiveCardParseResult();

            try
            {
                var context = new AdaptiveCardSerializationContext(parseResult, new ParseContext());
                WarningContext.Current = parseResult.Warnings;
                try
                {
                    parseResult.Card = JsonSerializer.Deserialize<AdaptiveCard>(json, context.Options);
                }
                finally
                {
                    WarningContext.Current = null;
                }
            }
            catch (JsonException ex)
            {
                throw new AdaptiveSerializationException(ex.Message, ex);
            }
            return parseResult;
        }

        /// <summary>
        /// Serialize this AdaptiveCard to JSON.
        /// </summary>
        /// <returns>The JSON representation of this AdaptiveCard.</returns>
        public string ToJson()
        {
            return JsonSerializer.Serialize(this, AdaptiveCardSerializationContext.SerializationOptions);
        }

        /// <summary>
        /// Get resource information for all images and media present in this card.
        /// </summary>
        /// <returns>Resource information for the entire card.</returns>
        public RemoteResourceInformation[] GetResourceInformation()
        {
            // TODO: Add Media information to the list when Media type is added
            return GetResourceInformationInCard(this).ToArray();
        }

        private List<RemoteResourceInformation> GetResourceInformationInCard(AdaptiveCard card)
        {
            // Initialize the result array
            List<RemoteResourceInformation> resourceInformationList = new List<RemoteResourceInformation>();

            // Get background image
            if (!String.IsNullOrEmpty(card.BackgroundImage?.UrlString))
            {
                resourceInformationList.Add(new RemoteResourceInformation(
                    card.BackgroundImage?.UrlString,
                    "image"
                ));
            }

            // Get all resource information in body
            foreach (AdaptiveElement bodyElement in card.Body)
            {
                resourceInformationList.AddRange(GetResourceInformationInElement(bodyElement));
            }

            // Get all resource information in actions
            foreach (AdaptiveAction action in card.Actions)
            {
                // Get all resource information for iconUrl
                if (!String.IsNullOrEmpty(action.IconUrl))
                {
                    resourceInformationList.Add(new RemoteResourceInformation(
                        action.IconUrl,
                        "image"
                    ));
                }

                // Get all resource information in ShowCard actions' cards
                if (action is AdaptiveShowCardAction showCardAction)
                {
                    resourceInformationList.AddRange(GetResourceInformationInCard(showCardAction.Card));
                }
            }

            return resourceInformationList;
        }

        private List<RemoteResourceInformation> GetResourceInformationInElement(AdaptiveElement element)
        {
            List<RemoteResourceInformation> resourceInformationList = new List<RemoteResourceInformation>();

            // Base case
            if (element is AdaptiveImage imageElement && !String.IsNullOrEmpty(imageElement.UrlString))
            {
                resourceInformationList.Add(new RemoteResourceInformation(
                    imageElement.UrlString,
                    "image"
                ));
            }

            // If element is any kind of container, iterate over its items.
            else if (element is AdaptiveContainer container)
            {
                foreach (AdaptiveElement item in container.Items)
                {
                    resourceInformationList.AddRange(GetResourceInformationInElement(item));
                }
            }
            else if (element is AdaptiveImageSet imageSet)
            {
                foreach (AdaptiveElement item in imageSet.Images)
                {
                    resourceInformationList.AddRange(GetResourceInformationInElement(item));
                }
            }
            else if (element is AdaptiveColumnSet columnSet)
            {
                foreach (AdaptiveElement item in columnSet.Columns)
                {
                    resourceInformationList.AddRange(GetResourceInformationInElement(item));
                }
            }
            else if (element is AdaptiveColumn column)
            {
                foreach (AdaptiveElement item in column.Items)
                {
                    resourceInformationList.AddRange(GetResourceInformationInElement(item));
                }
            }

            return resourceInformationList;
        }
    }
}
