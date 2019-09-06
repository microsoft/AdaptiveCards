using System;
using AdaptiveCards.Rendering.Uwp;
using Newtonsoft.Json;
using System.Reflection;
using Newtonsoft.Json.Serialization;
using Newtonsoft.Json.Converters;

namespace CustomElementJsonNetHelpers
{
    internal class AdaptiveCardSerializationResolver : DefaultContractResolver
    {
        public AdaptiveCardSerializationResolver()
        {
        }

        // BECKYTODO - Make sure container type would be ok...

        protected override JsonConverter ResolveContractConverter(Type objectType)
        {
            if (typeof(Spacing).IsAssignableFrom(objectType) || typeof(HeightType).IsAssignableFrom(objectType))
            {
                // Use the string enum converter for these types to get them serialized as enum names rather than integers
                return new StringEnumConverter();
            }
            else
            {
                return base.ResolveContractConverter(objectType);
            }
        }

        protected override JsonProperty CreateProperty(MemberInfo member, MemberSerialization memberSerialization)
        {
            JsonProperty jsonProperty = base.CreateProperty(member, memberSerialization);

            // To handle element type, ignore the "ElementType" property, and write out the ElementTypeString property as "type"
            if (member.Name == "FallbackType" ||
                member.Name == "FallbackContent" ||
                member.Name == "AdditionalProperties" ||
                member.Name == "ElementType" ||
                member.Name == "Requirements")
            {
                jsonProperty.ShouldSerialize = o => { return false; };
            }

            // Convert the "E
            if (member.Name == "ElementTypeString")
            {
                jsonProperty.PropertyName = "type";
            }

            // Don't write out default values for these properties
            if (member.Name == "Id" ||
                member.Name == "Height" ||
                member.Name == "Separator" ||
                member.Name == "Spacing" ||
                member.Name == "IsVisible")
            {
                jsonProperty.DefaultValueHandling = DefaultValueHandling.Ignore;
            }

            if (member.Name == "IsVisible")
            {
                jsonProperty.DefaultValue = true;
            }

            return jsonProperty;
        }
    }
}
