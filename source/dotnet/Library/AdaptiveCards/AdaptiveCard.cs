// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Adaptive card which has flexible container
    /// </summary>
    [JsonConverter(typeof(AdaptiveCardConverter))]
#if !NETSTANDARD1_3
    [XmlRoot(ElementName = "Card", Namespace = AdaptiveCard.ContentType)]
#endif
    public class AdaptiveCard : AdaptiveTypedElement
    {
#if !NETSTANDARD1_3
        public static XmlSerializer XmlSerializer = new XmlSerializer(typeof(AdaptiveCard), defaultNamespace: AdaptiveCard.ContentType);
#endif

        /// <summary>
        /// AdaptiveCard mimetype.
        /// </summary>
        public const string ContentType = "application/vnd.microsoft.card.adaptive";

        /// <summary>
        /// The AdaptiveCard element that this class implements.
        /// </summary>
        public const string TypeName = "AdaptiveCard";

        /// <inheritdoc/>
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
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
        [JsonProperty(Order = -10)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public AdaptiveSchemaVersion Version { get; set; } = new AdaptiveSchemaVersion("1.0");

#if !NETSTANDARD1_3
        /// <summary>
        /// Xml serialization for complex type version.
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(Version))]
        public string _Version { get => Version.ToString(); set => this.Version = new AdaptiveSchemaVersion(value); }
#endif

        /// <summary>
        /// This is obsolete. Use the <see cref="Version"/> property instead.
        /// </summary>
        [JsonProperty(Order = -9, NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("Use the Version property instead")]
        public AdaptiveSchemaVersion MinVersion { get; set; }

        /// <summary>
        /// Text shown when the client doesn’t support the version specified. This can be in markdown format.
        /// </summary>
        [JsonProperty(Order = -8, NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string FallbackText { get; set; }

        /// <summary>
        /// Speak annotation for the card.
        /// </summary>
        [JsonProperty(Order = -7, NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Speak { get; set; }

        /// <summary>
        /// The 2-letter ISO-639-1 language used in the card. Used to localize any date/time functions.
        /// </summary>
        [JsonProperty(Order = -7, NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Lang { get; set; }

        /// <summary>
        /// Title for the card (used when displayed in a dialog).
        /// </summary>
        [JsonProperty(Order = -6, NullValueHandling = NullValueHandling.Ignore)]
        //[Obsolete("The Title property is not officially supported right now and should not be used")]
        public string Title { get; set; }

        /// <summary>
        /// Background image for card.
        /// </summary>
        [JsonProperty(Order = -5, DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [JsonConverter(typeof(AdaptiveBackgroundImageConverter))]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveBackgroundImage BackgroundImage { get; set; }

        /// <summary>
        /// Value that denotes if the card must use all the vertical space that is set to it. Default value is <see cref="AdaptiveDimensionType.Auto"/>.
        /// </summary>
        /// <summary>
        /// Explicit image Height.
        /// </summary>
        [JsonProperty(Order = -4, DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public AdaptiveDimension Height { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// XmlProperty for serialization of height
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(Height))]
        [DefaultValue(null)]
        public string _Height { get => Height?.ToString(); set => this.Height = (value != null) ? new AdaptiveDimension(value) : null; }

        /// <summary>
        /// Control serialization of empty values
        /// </summary>
        /// <returns></returns>
        public bool ShouldSerialize_Height() => Height != null;
#endif

        /// <summary>
        /// Explicit card minimum height with 'px'. (100px, 200px)
        /// </summary>
        [JsonProperty("minHeight", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string MinHeight { get; set; }

        /// <summary>
        /// PixelMinHeight if height is not auto/stretch
        /// </summary>
        [JsonIgnore]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public int PixelMinHeight { get => int.TryParse(MinHeight?.Replace("px", ""), out var val) ? (int)val : 0; set => MinHeight = $"{value}px"; }

        /// <summary>
        /// The Body elements for this card.
        /// </summary>
        [JsonProperty(Order = -3)]
        [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveElement>))]
#if !NETSTANDARD1_3
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
        [XmlElement(typeof(AdaptiveUnknownElement))]
        [XmlElement(typeof(AdaptiveTable))]
#endif
        public List<AdaptiveElement> Body { get; set; } = new List<AdaptiveElement>();

        /// <summary>
        /// Determines whether the body portion of an AdaptiveCard should be serialized.
        /// </summary>
        /// <returns>true iff the body should be serialized.</returns>
        public bool ShouldSerializeBody() => Body?.Count > 0;

        /// <summary>
        /// The Actions for this card.
        /// </summary>
        [JsonProperty(Order = -2)]
        [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveAction>))]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveOpenUrlAction))]
        [XmlElement(typeof(AdaptiveShowCardAction))]
        [XmlElement(typeof(AdaptiveSubmitAction))]
        [XmlElement(typeof(AdaptiveToggleVisibilityAction))]
        [XmlElement(typeof(AdaptiveExecuteAction))]
        [XmlElement(typeof(AdaptiveUnknownAction))]
#endif
        public List<AdaptiveAction> Actions { get; set; } = new List<AdaptiveAction>();

        /// <summary>
        /// Determines whether the actions portion of an AdaptiveCard should be serialized.
        /// </summary>
        /// <returns>true iff actions should be serialized.</returns>
        public bool ShouldSerializeActions() => Actions?.Count > 0;

        /// <summary>
        /// This makes sure the $schema property doesn't show up in AdditionalProperties
        /// </summary>
        [JsonProperty("$schema")]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        internal string JsonSchema { get; set; }

        /// <summary>
        /// Determines whether the schema entry in an AdaptiveCard should be serialized.
        /// </summary>
        /// <returns>false</returns>
        public bool ShouldSerializeJsonSchema() => false;

        /// <summary>
        /// The content alignment for the element inside the container.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(typeof(AdaptiveVerticalContentAlignment), "top")]
        public AdaptiveVerticalContentAlignment VerticalContentAlignment { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls xml serialization of enum attribute
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(VerticalContentAlignment))]
        [DefaultValue(null)]
        public string _VerticalContentAlignment
        {
            get => JToken.FromObject(VerticalContentAlignment).ToString();
            set => VerticalContentAlignment = (AdaptiveVerticalContentAlignment)Enum.Parse(typeof(AdaptiveVerticalContentAlignment), value, true);
        }

        /// <summary>
        /// hides default value for xml serialization
        /// </summary>
        public bool ShouldSerialize_VerticalContentAlignment() => VerticalContentAlignment != AdaptiveVerticalContentAlignment.Top;
#endif

        /// <summary>
        /// Action for the card (this allows a default action at the card level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveSelectAction SelectAction { get; set; }

        /// <summary>
        /// Defines how the card can be refreshed by making a request to the target Bot.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveRefresh Refresh { get; set; }


        /// <summary>
        /// The style used to display this element. See <see cref="AdaptiveContainerStyle" />.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(typeof(AdaptiveContainerStyle), "default")]
        public AdaptiveContainerStyle Style { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Controls xml serialization of enum attribute
        /// </summary>
        [JsonIgnore]
        [XmlAttribute(nameof(Style))]
        [DefaultValue(null)]
        public string _Style
        {
            get => JToken.FromObject(Style).ToString();
            set => Style = (AdaptiveContainerStyle)Enum.Parse(typeof(AdaptiveContainerStyle), value, true);
        }

        /// <summary>
        /// hides default value for xml serialization
        /// </summary>
        public bool ShouldSerialize_Style() => Style != AdaptiveContainerStyle.Default;
#endif

        /// <summary>
        /// Defines authentication information to enable on-behalf-of single sign on or just-in-time OAuth.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveAuthentication Authentication { get; set; }

        /// <summary>
        /// Sets the text flow direction
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Rtl { get; set; }


        /// <summary>
        /// Defines various metadata properties typically not used for rendering the card
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
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
                parseResult.Card = JsonConvert.DeserializeObject<AdaptiveCard>(json, new JsonSerializerSettings
                {
                    ContractResolver = new WarningLoggingContractResolver(parseResult, new ParseContext()),
                    Converters = { new StrictIntConverter() },
                    Error = delegate (object sender, Newtonsoft.Json.Serialization.ErrorEventArgs args)
                    {
                        if (args.ErrorContext.Error.GetType() == typeof(JsonSerializationException))
                        {
                            args.ErrorContext.Handled = true;
                        }
                    }
                });
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
            return JsonConvert.SerializeObject(this, Newtonsoft.Json.Formatting.Indented);
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
            if (!String.IsNullOrEmpty(card.BackgroundImage?.Url))
            {
                resourceInformationList.Add(new RemoteResourceInformation(
                    card.BackgroundImage?.Url,
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
            if (element is AdaptiveImage imageElement && !String.IsNullOrEmpty(imageElement.Url))
            {
                resourceInformationList.Add(new RemoteResourceInformation(
                    imageElement.Url,
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
