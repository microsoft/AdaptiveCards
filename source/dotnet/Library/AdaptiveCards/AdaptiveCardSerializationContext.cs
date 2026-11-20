// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Provides serialization context for AdaptiveCard parsing, including warning collection
    /// and parse context for element ID tracking. Replaces the Newtonsoft WarningLoggingContractResolver pattern.
    /// </summary>
    internal class AdaptiveCardSerializationContext
    {
        /// <summary>
        /// The parse result that collects warnings during deserialization.
        /// </summary>
        public AdaptiveCardParseResult ParseResult { get; }

        /// <summary>
        /// The parse context used for element ID tracking and collision detection.
        /// </summary>
        public ParseContext ParseContext { get; }

        /// <summary>
        /// The configured <see cref="JsonSerializerOptions"/> with all converters pre-injected.
        /// </summary>
        public JsonSerializerOptions Options { get; }

        /// <summary>
        /// Creates a new serialization context for deserializing an AdaptiveCard.
        /// </summary>
        /// <param name="parseResult">The parse result to collect warnings into.</param>
        /// <param name="parseContext">The parse context for element tracking.</param>
        public AdaptiveCardSerializationContext(AdaptiveCardParseResult parseResult, ParseContext parseContext)
        {
            ParseResult = parseResult ?? throw new ArgumentNullException(nameof(parseResult));
            ParseContext = parseContext ?? throw new ArgumentNullException(nameof(parseContext));
            Options = BuildOptions();
        }

        private JsonSerializerOptions BuildOptions()
        {
            var options = new JsonSerializerOptions
            {
                PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
                PropertyNameCaseInsensitive = true,
                DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull,
                AllowTrailingCommas = true,
                ReadCommentHandling = JsonCommentHandling.Skip
            };

            // Add converters that need parse context and warnings.
            // AdaptiveTypedElementConverter explicitly excludes AdaptiveCard (via CanConvert)
            // so that AdaptiveCardConverter always handles cards and performs version validation.
            // This makes converter registration order-independent.
            options.Converters.Add(new AdaptiveCardConverter(ParseResult.Warnings, ParseContext));
            options.Converters.Add(new AdaptiveTypedElementConverter(ParseResult.Warnings, ParseContext));
            options.Converters.Add(new AdaptiveFallbackConverter(ParseResult.Warnings, ParseContext));
            options.Converters.Add(new IgnoreEmptyItemsConverter<AdaptiveElement>(ParseContext, ParseResult.Warnings));
            options.Converters.Add(new IgnoreEmptyItemsConverter<AdaptiveAction>(ParseContext, ParseResult.Warnings));
            options.Converters.Add(new AdaptiveActionPolymorphicConverter(ParseResult.Warnings, ParseContext));
            options.Converters.Add(new AdaptiveInlinesConverter(ParseContext));

            // Add converters that need warnings only
            options.Converters.Add(new AdaptiveBackgroundImageConverter(ParseResult.Warnings));
            options.Converters.Add(new AdaptiveHeightConverter(ParseResult.Warnings));
            options.Converters.Add(new AdaptiveWidthConverter(ParseResult.Warnings));
            options.Converters.Add(new TableColumnWidthConverter(ParseResult.Warnings));

            // Add converters that are stateless
            options.Converters.Add(new StrictIntConverter());
            options.Converters.Add(new AdaptiveSchemaVersion.AdaptiveSchemaJsonConverter());
            options.Converters.Add(new ToggleElementsConverter());
            options.Converters.Add(new Iso8601DateTimeConverter());
            options.Converters.Add(new AdaptiveCollectionElementConverterFactory());

            return options;
        }

        /// <summary>
        /// Gets a static <see cref="JsonSerializerOptions"/> for serialization (no per-call state needed).
        /// </summary>
        public static JsonSerializerOptions SerializationOptions { get; } = BuildSerializationOptions();

        private static JsonSerializerOptions BuildSerializationOptions()
        {
            var options = new JsonSerializerOptions
            {
                PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
                WriteIndented = true,
                DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull
            };

            // Add converters needed for serialization
            options.Converters.Add(new AdaptiveCardConverter());
            options.Converters.Add(new AdaptiveTypedElementConverter());
            options.Converters.Add(new AdaptiveFallbackConverter());
            options.Converters.Add(new IgnoreEmptyItemsConverter<AdaptiveElement>());
            options.Converters.Add(new IgnoreEmptyItemsConverter<AdaptiveAction>());
            options.Converters.Add(new AdaptiveActionPolymorphicConverter());
            options.Converters.Add(new AdaptiveBackgroundImageConverter());
            options.Converters.Add(new AdaptiveHeightConverter());
            options.Converters.Add(new AdaptiveWidthConverter());
            options.Converters.Add(new AdaptiveSchemaVersion.AdaptiveSchemaJsonConverter());
            options.Converters.Add(new ToggleElementsConverter());
            options.Converters.Add(new TableColumnWidthConverter());
            options.Converters.Add(new Iso8601DateTimeConverter());
            options.Converters.Add(new AdaptiveCollectionElementConverterFactory());

            return options;
        }

        /// <summary>
        /// Gets a static <see cref="JsonSerializerOptions"/> for host config deserialization.
        /// </summary>
        public static JsonSerializerOptions HostConfigOptions { get; } = BuildHostConfigOptions();

        private static JsonSerializerOptions BuildHostConfigOptions()
        {
            var options = new JsonSerializerOptions
            {
                PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
                PropertyNameCaseInsensitive = true,
                DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull
            };

            options.Converters.Add(new StrictIntConverter());

            return options;
        }
    }
}
