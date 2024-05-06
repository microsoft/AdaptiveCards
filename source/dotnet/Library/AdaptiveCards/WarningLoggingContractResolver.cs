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
        private ParseContext _parseContext;

        public WarningLoggingContractResolver(AdaptiveCardParseResult parseResult, ParseContext parseContext)
        {
            _parseResult = parseResult;
            _parseContext = parseContext;
        }

        protected override JsonConverter ResolveContractConverter(Type type)
        {
            var converter = base.ResolveContractConverter(type);

            if (converter is AdaptiveTypedBaseElementConverter converterWithContext)
            {
                converterWithContext.ParseContext = _parseContext;
            }

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

            if (property?.Converter is AdaptiveTypedBaseElementConverter converterWithContext)
            {
                converterWithContext.ParseContext = _parseContext;
            }

#pragma warning disable CS0618 // Type or member is obsolete
            if (property?.MemberConverter is ILogWarnings memberConverter)
            {
                memberConverter.Warnings = _parseResult.Warnings;
            }
#pragma warning restore CS0618 // Type or member is obsolete

            return property;
        }
    }
}
