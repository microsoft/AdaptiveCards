using System;
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
    }
}