// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

namespace AdaptiveCards
{
    /// <summary>
    /// This handles using the type field to instantiate strongly typed objects on deserialization.
    /// </summary>
    public class AdaptiveTypedElementConverter : AdaptiveTypedBaseElementConverter, ILogWarnings
    {
        /// <summary>
        /// The list of warnings generated while converting.
        /// </summary>
        public List<AdaptiveWarning> Warnings { get; set; } = new List<AdaptiveWarning>();

        /// <summary>
        /// Default types to support, register any new types to this list
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
                [AdaptiveSubmitAction.TypeName] = typeof(AdaptiveSubmitAction),
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
        public override bool CanConvert(Type objectType)
        {
            return typeof(AdaptiveTypedElement).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }

        /// <inheritdoc />
        public override bool CanWrite => false;

        /// <inheritdoc />
        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }

        /// <inheritdoc />
        public override bool CanRead => true;

        /// <inheritdoc />
        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var jObject = JObject.Load(reader);

            string typeName = GetElementTypeName(objectType, jObject);

            if (TypedElementTypes.Value.TryGetValue(typeName, out var type))
            {
                string objectId = jObject.Value<string>("id");
                if (objectId == null)
                {
                    if (typeof(AdaptiveInput).GetTypeInfo().IsAssignableFrom(type.GetTypeInfo()))
                    {
                        throw new AdaptiveSerializationException($"Required property 'id' not found on '{typeName}'");
                    }
                }

                // add id of element to ParseContext
                AdaptiveInternalID internalID = AdaptiveInternalID.Current();
                if (type != typeof(AdaptiveCard))
                {
                    internalID = AdaptiveInternalID.Next();
                    ParseContext.PushElement(objectId, internalID);
                }

                var result = (AdaptiveTypedElement)Activator.CreateInstance(type);
                try
                {
                    serializer.Populate(jObject.CreateReader(), result);
                    result.InternalID = internalID;
                }
                catch (JsonSerializationException) { }

                // remove id of element from ParseContext
                if (type != typeof(AdaptiveCard))
                {
                    ParseContext.PopElement();
                }

                return result;
            }
            else // We're looking at an unknown element
            {
                string objectId = jObject.Value<string>("id");
                AdaptiveInternalID internalID = AdaptiveInternalID.Next();

                // Handle deserializing unknown element
                ParseContext.PushElement(objectId, internalID);
                AdaptiveTypedElement result = null;
                if (ParseContext.Type == ParseContext.ContextType.Element)
                {
                    result = (AdaptiveTypedElement)Activator.CreateInstance(typeof(AdaptiveUnknownElement));
                    serializer.Populate(jObject.CreateReader(), result);
                }
                else // ParseContext.Type == ParseContext.ContextType.Action
                {
                    result = (AdaptiveTypedElement)Activator.CreateInstance(typeof(AdaptiveUnknownAction));
                    serializer.Populate(jObject.CreateReader(), result);
                }
                ParseContext.PopElement();

                Warnings.Add(new AdaptiveWarning(-1, $"Unknown element '{typeName}'"));
                return result;
            }
        }

        /// <summary>
        /// Retrieves the type name of an AdaptiveCards object.
        /// </summary>
        public static string GetElementTypeName(Type objectType, JObject jObject)
        {
            string typeName = jObject["type"]?.Value<string>() ?? jObject["@type"]?.Value<string>();
            if (typeName == null)
            {
                // Get value of this objectType's "Type" JsonProperty(Required)
                string typeJsonPropertyRequiredValue = objectType.GetRuntimeProperty("Type")
                    .CustomAttributes.Where(a => a.AttributeType == typeof(JsonPropertyAttribute)).FirstOrDefault()?
                    .NamedArguments.Where(a => a.TypedValue.ArgumentType == typeof(Required)).FirstOrDefault()
                    .TypedValue.Value.ToString();

                // If this objectType does not require "Type" attribute, use the objectType's XML "TypeName" attribute
                if (typeJsonPropertyRequiredValue == "0")
                {
                    typeName = objectType
                        .GetRuntimeFields().Where(x => x.Name == "TypeName").FirstOrDefault()?
                        .GetValue("TypeName").ToString();
                }
                else
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
}
