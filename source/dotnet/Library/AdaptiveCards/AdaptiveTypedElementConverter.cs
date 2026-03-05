// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Factory that creates the appropriate converter for AdaptiveTypedElement and its derived abstract types.
    /// </summary>
    public class AdaptiveTypedElementConverter : JsonConverterFactory, ILogWarnings
    {
        /// <summary>
        /// The list of warnings generated while converting.
        /// </summary>
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        /// <summary>
        /// The <see cref="ParseContext"/> for element tracking.
        /// </summary>
        public ParseContext ParseContext { get; set; } = new ParseContext();

        /// <summary>
        /// Initializes a new instance for serialization (no warnings/context needed).
        /// </summary>
        public AdaptiveTypedElementConverter() { }

        /// <summary>
        /// Initializes a new instance for deserialization with warnings and parse context.
        /// </summary>
        public AdaptiveTypedElementConverter(List<AdaptiveWarning> warnings, ParseContext parseContext)
        {
            Warnings = warnings ?? new List<AdaptiveWarning>();
            ParseContext = parseContext ?? new ParseContext();
        }

        /// <inheritdoc />
        /// <remarks>
        /// Returns true for all types derived from <see cref="AdaptiveTypedElement"/>,
        /// except <see cref="AdaptiveCard"/> which is handled by <see cref="AdaptiveCardConverter"/>
        /// to ensure version validation occurs.
        /// </remarks>
        public override bool CanConvert(Type typeToConvert)
        {
            return typeof(AdaptiveTypedElement).GetTypeInfo().IsAssignableFrom(typeToConvert.GetTypeInfo())
                && typeToConvert != typeof(AdaptiveCard);
        }

        /// <inheritdoc />
        public override JsonConverter CreateConverter(Type typeToConvert, JsonSerializerOptions options)
        {
            return new AdaptiveTypedElementInnerConverter(Warnings, ParseContext);
        }

        /// <summary>
        /// Default types to support, register any new types to this list.
        /// </summary>
        public static readonly Lazy<Dictionary<string, Type>> TypedElementTypes = new Lazy<Dictionary<string, Type>>(() =>
        {
            var types = new Dictionary<string, Type>
            {
                [AdaptiveCard.TypeName] = typeof(AdaptiveCard),
                [AdaptiveTextBlock.TypeName] = typeof(AdaptiveTextBlock),
                [AdaptiveRichTextBlock.TypeName] = typeof(AdaptiveRichTextBlock),
                [AdaptiveImage.TypeName] = typeof(AdaptiveImage),
                [AdaptiveContainer.TypeName] = typeof(AdaptiveContainer),
                [AdaptiveColumn.TypeName] = typeof(AdaptiveColumn),
                [AdaptiveColumnSet.TypeName] = typeof(AdaptiveColumnSet),
                [AdaptiveFactSet.TypeName] = typeof(AdaptiveFactSet),
                [AdaptiveImageSet.TypeName] = typeof(AdaptiveImageSet),
                [AdaptiveTextInput.TypeName] = typeof(AdaptiveTextInput),
                [AdaptiveDateInput.TypeName] = typeof(AdaptiveDateInput),
                [AdaptiveTimeInput.TypeName] = typeof(AdaptiveTimeInput),
                [AdaptiveChoiceSetInput.TypeName] = typeof(AdaptiveChoiceSetInput),
                [AdaptiveNumberInput.TypeName] = typeof(AdaptiveNumberInput),
                [AdaptiveToggleInput.TypeName] = typeof(AdaptiveToggleInput),
                [AdaptiveTable.TypeName] = typeof(AdaptiveTable),
                [AdaptiveTableColumnDefinition.TypeName] = typeof(AdaptiveTableColumnDefinition),
                [AdaptiveTableRow.TypeName] = typeof(AdaptiveTableRow),
                [AdaptiveTableCell.TypeName] = typeof(AdaptiveTableCell),
                [AdaptiveSubmitAction.TypeName] = typeof(AdaptiveSubmitAction),
                [AdaptiveExecuteAction.TypeName] = typeof(AdaptiveExecuteAction),
                [AdaptiveOpenUrlAction.TypeName] = typeof(AdaptiveOpenUrlAction),
                [AdaptiveShowCardAction.TypeName] = typeof(AdaptiveShowCardAction),
                [AdaptiveMedia.TypeName] = typeof(AdaptiveMedia),
                [AdaptiveToggleVisibilityAction.TypeName] = typeof(AdaptiveToggleVisibilityAction),
                [AdaptiveActionSet.TypeName] = typeof(AdaptiveActionSet)
            };
            return types;
        });

        /// <summary>
        /// Registers a new element with the element converter.
        /// </summary>
        /// <param name="typeName">The <see cref="AdaptiveTypedElement.Type"/> of the element to register.</param>
        public static void RegisterTypedElement<T>(string typeName = null)
            where T : AdaptiveTypedElement
        {
            if (typeName == null)
                typeName = ((AdaptiveTypedElement)Activator.CreateInstance(typeof(T))).Type;

            TypedElementTypes.Value[typeName] = typeof(T);
        }

        /// <inheritdoc />

        /// <summary>
        /// Retrieves the type name of an AdaptiveCards object.
        /// </summary>
        public static string GetElementTypeName(Type objectType, JsonObject jObject)
        {
            string typeName = jObject["type"]?.GetValue<string>() ?? jObject["@type"]?.GetValue<string>();
            if (typeName == null)
            {
                // Get value of this objectType's "Type" JsonProperty(Required)
                var typeProperty = objectType.GetRuntimeProperty("Type");
                var jsonRequiredAttr = typeProperty?.CustomAttributes
                    .FirstOrDefault(a => a.AttributeType == typeof(JsonRequiredAttribute));

                // If the Type property is not required, use the TypeName static field
                if (jsonRequiredAttr == null)
                {
                    typeName = objectType
                        .GetRuntimeFields().FirstOrDefault(x => x.Name == "TypeName")?
                        .GetValue("TypeName")?.ToString();
                }

                if (typeName == null)
                {
                    throw new AdaptiveSerializationException("Required property 'type' not found on adaptive card element");
                }
            }

            return typeName;
        }

        /// <summary>
        /// Instantiates a new strongly-typed element of the given type.
        /// </summary>
        public static T CreateElement<T>(string typeName = null)
            where T : AdaptiveTypedElement
        {
            if (typeName == null)
            {
                typeName = ((T)Activator.CreateInstance(typeof(T))).Type;
            }

            if (TypedElementTypes.Value.TryGetValue(typeName, out var type))
            {
                return (T)Activator.CreateInstance(type);
            }
            return null;
        }

        private enum WarningStatusCode { UnknownElementType = 0 };
    }

    /// <summary>
    /// Internal converter that handles the actual read/write of AdaptiveTypedElement instances.
    /// Uses object base type so it can handle any derived type of AdaptiveTypedElement.
    /// </summary>
    internal class AdaptiveTypedElementInnerConverter : JsonConverter<object>
    {
        public List<AdaptiveWarning> Warnings { get; set; }
        public ParseContext ParseContext { get; set; }

        public AdaptiveTypedElementInnerConverter(List<AdaptiveWarning> warnings, ParseContext parseContext)
        {
            Warnings = warnings ?? new List<AdaptiveWarning>();
            ParseContext = parseContext ?? new ParseContext();
        }

        /// <summary>
        /// Returns true for all types derived from AdaptiveTypedElement,
        /// except AdaptiveCard which is handled by AdaptiveCardConverter.
        /// </summary>
        public override bool CanConvert(Type typeToConvert)
        {
            return typeof(AdaptiveTypedElement).GetTypeInfo().IsAssignableFrom(typeToConvert.GetTypeInfo())
                && typeToConvert != typeof(AdaptiveCard);
        }

        public override object Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            var doc = JsonDocument.ParseValue(ref reader);
            var jObject = SafeJsonHelper.SafeCreateJsonObject(doc.RootElement);
            if (jObject == null)
            {
                return null;
            }

            string typeName = AdaptiveTypedElementConverter.GetElementTypeName(typeToConvert, jObject);

            if (AdaptiveTypedElementConverter.TypedElementTypes.Value.TryGetValue(typeName, out var type))
            {
                string objectId = jObject["id"]?.GetValue<string>();
                if (objectId == null)
                {
                    if (typeof(AdaptiveInput).GetTypeInfo().IsAssignableFrom(type.GetTypeInfo()))
                    {
                        throw new AdaptiveSerializationException($"Required property 'id' not found on '{typeName}'");
                    }
                }

                AdaptiveInternalID internalID = AdaptiveInternalID.Current();
                if (type != typeof(AdaptiveCard))
                {
                    internalID = AdaptiveInternalID.Next();
                    ParseContext.PushElement(objectId, internalID);
                }

                AdaptiveTypedElement result;
                try
                {
                    result = (AdaptiveTypedElement)jObject.Deserialize(type, GetOptionsWithoutThisConverter(options));
                    result.InternalID = internalID;
                }
                catch (JsonException)
                {
                    result = (AdaptiveTypedElement)Activator.CreateInstance(type);
                    result.InternalID = internalID;
                }

                if (type != typeof(AdaptiveCard))
                {
                    ParseContext.PopElement();
                }

                return result;
            }
            else
            {
                string objectId = jObject["id"]?.GetValue<string>();
                AdaptiveInternalID internalID = AdaptiveInternalID.Next();

                ParseContext.PushElement(objectId, internalID);
                AdaptiveTypedElement result;

                if (ParseContext.Type == ParseContext.ContextType.Element)
                {
                    result = jObject.Deserialize<AdaptiveUnknownElement>(GetOptionsWithoutThisConverter(options))
                             ?? new AdaptiveUnknownElement();
                }
                else
                {
                    result = jObject.Deserialize<AdaptiveUnknownAction>(GetOptionsWithoutThisConverter(options))
                             ?? new AdaptiveUnknownAction();
                }

                ParseContext.PopElement();

                Warnings.Add(new AdaptiveWarning(-1, $"Unknown element '{typeName}'"));
                return result;
            }
        }

        public override void Write(Utf8JsonWriter writer, object value, JsonSerializerOptions options)
        {
            JsonSerializer.Serialize(writer, value, value.GetType(), GetOptionsWithoutThisConverter(options));
        }

        private JsonSerializerOptions GetOptionsWithoutThisConverter(JsonSerializerOptions options)
        {
            var newOptions = new JsonSerializerOptions
            {
                PropertyNamingPolicy = options.PropertyNamingPolicy,
                PropertyNameCaseInsensitive = options.PropertyNameCaseInsensitive,
                DefaultIgnoreCondition = options.DefaultIgnoreCondition,
                WriteIndented = options.WriteIndented,
                AllowTrailingCommas = options.AllowTrailingCommas,
                ReadCommentHandling = options.ReadCommentHandling
            };

            foreach (var c in options.Converters)
            {
                if (!(c is AdaptiveTypedElementConverter) && !(c is AdaptiveTypedElementInnerConverter))
                {
                    newOptions.Converters.Add(c);
                }
            }

            return newOptions;
        }
    }
}
