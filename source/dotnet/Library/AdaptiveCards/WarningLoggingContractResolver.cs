// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// This JSON contract resolver checks if the JsonConverter can log warnings, and if so sets the Warnings property
    /// </summary>
    internal class WarningLoggingContractResolver : DefaultContractResolver
    {
        private readonly AdaptiveCardParseResult _parseResult;

        public WarningLoggingContractResolver(AdaptiveCardParseResult parseResult)
        {
            _parseResult = parseResult;
        }

        protected override JsonConverter ResolveContractConverter(Type type)
        {
            var converter = base.ResolveContractConverter(type);

            if (converter is ILogWarnings logWarnings)
            {
                logWarnings.Warnings = _parseResult.Warnings;
            }

            return converter;
        }

        /// <summary>
        ///     Override when a member property is being instantiated. At this point we know what converter
        ///     is being used for the property. If the converter can log warnings, then give it our collection
        /// </summary>
        /// <param name="member"></param>
        /// <param name="memberSerialization"></param>
        /// <returns></returns>
        protected override JsonProperty CreateProperty(MemberInfo member, MemberSerialization memberSerialization)
        {
            var property = base.CreateProperty(member, memberSerialization);
            if (property?.Converter is ILogWarnings converter)
            {
                converter.Warnings = _parseResult.Warnings;
            }

            if (property?.MemberConverter is ILogWarnings memberConverter)
            {
                memberConverter.Warnings = _parseResult.Warnings;
            }

            return property;
        }
    }
}
