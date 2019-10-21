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

        protected override JsonConverter ResolveContractConverter(Type objectType)
        {
            if (typeof(Spacing).IsAssignableFrom(objectType) || typeof(HeightType).IsAssignableFrom(objectType))
            {
                // Use the string enum converter for these types to get them serialized as enum names rather than integers.
                // These are the types that are used by the base element type. We could consider checking our other enum types
                // here in case they are used by the custom element, but as the caller can easily set this converter on their
                // own properties we don't do that for now to reduce our maintenance burden.
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

            // These properties should not be directly serialized, they require special case code
            // handled in AdaptiveElementConverter.
            if (member.Name == "FallbackType" ||
                member.Name == "FallbackContent" ||
                member.Name == "AdditionalProperties" ||
                member.Name == "ElementType" ||
                member.Name == "Requirements")
            {
                jsonProperty.ShouldSerialize = o => { return false; };
            }

            // To handle element type, ignore the "ElementType" property, and write out the
            // ElementTypeString property as "type"
            if (member.Name == "ElementTypeString")
            {
                jsonProperty.PropertyName = "type";
            }

            // Don't out these properties if they're set to the default value
            if (member.Name == "Id" ||
                member.Name == "Height" ||
                member.Name == "Separator" ||
                member.Name == "Spacing" ||
                member.Name == "IsVisible")
            {
                jsonProperty.DefaultValueHandling = DefaultValueHandling.Ignore;
            }

            // The default value for IsVisible is true
            if (member.Name == "IsVisible")
            {
                jsonProperty.DefaultValue = true;
            }

            return jsonProperty;
        }
    }
}
