# Adaptive Cards .NET: System.Text.Json Migration Plan

> **GitHub Issue**: [#9146 - Switch to System.Text.Json from Newtonsoft.Json](https://github.com/microsoft/AdaptiveCards/issues/9146)
> **Created**: March 2, 2026
> **Status**: Complete

## Summary

Migrated all .NET projects from Newtonsoft.Json 13.0.3 to System.Text.Json 8.0.5.
The core AdaptiveCards library remains on `netstandard2.0` using STJ as a NuGet package.
This is a breaking change for consumers who reference Newtonsoft.Json types exposed
by the SDK. See [system-text-json-migration-guide.md](system-text-json-migration-guide.md)
for the consumer migration guide.

## Decisions

| Decision | Choice | Rationale |
| -------- | ------ | --------- |
| Target framework | Keep `netstandard2.0` | Widest compatibility; STJ 8.0.x available via NuGet |
| Breaking API changes | Accepted | Clean break - replace all Newtonsoft types with STJ equivalents |
| Scope | Everything at once | Core library, WPF renderers, samples, and all tests |
| STJ version | 8.0.5 | Aligned with AdaptiveCards.Templating |
| Serialization output | Accept STJ native format | JSON is semantically equivalent; renderers unaffected |
| Error tolerance | Try/catch in converters + tolerant enum converters | Replaces Newtonsoft's ErrorEventArgs.Handled |

## What Was Done

### Infrastructure

- Created `AdaptiveCardSerializationContext` - replaces `WarningLoggingContractResolver` with constructor injection
- Created `AdaptiveCollectionElementConverterFactory` - forces STJ to treat `IEnumerable<AdaptiveElement>` types as objects
- Created `NanDoubleConverter` - handles `double.NaN` serialization for `AdaptiveNumberInput`

### Converters Rewritten (14 total)

- `AdaptiveTypedElementConverter` - polymorphic dispatch via `JsonConverterFactory`
- `AdaptiveCardConverter` - version validation, fallback card creation
- `AdaptiveFallbackConverter` - drop/content fallback handling
- `IgnoreEmptyItemsConverter<T>` - filters empty items in body/actions arrays
- `AdaptiveInlinesConverter` - text run parsing
- `AdaptiveBackgroundImageConverter` - string URL and object form
- `AdaptiveHeightConverter` / `AdaptiveWidthConverter` - dimension parsing
- `HashColorConverter` - color validation
- `StrictIntConverter` - rejects floats for integer properties
- `StringSizeWithUnitConverter` / `TableColumnWidthConverter` - pixel parsing
- `AdaptiveSchemaJsonConverter` - version string conversion
- `IgnoreDefaultStringEnumConverter<T>` / `IgnoreNullEnumConverter<T>` - tolerant enum parsing
- `ToggleElementsConverter` - mixed string/object arrays
- `Iso8601DateTimeConverter` - date format handling

### Dead Code Removed

- `WarningLoggingContractResolver` - deleted (replaced by constructor injection)
- `AdaptiveTypedBaseElementConverter` - deleted (unused abstract base)
- `AdaptiveCardTypeInfoResolver` - deleted (empty pass-through)
- `ShouldSerializeBody()`, `ShouldSerializeActions()`, `ShouldSerializeHeight()`, `ShouldSerializeJsonSchema()`, `ShouldSerializeCaptionSources()` - deleted (STJ does not call these)

### Model Changes

- 200+ `[JsonProperty]` attributes replaced with `[JsonPropertyName]`, `[JsonPropertyOrder]`, `[JsonIgnore(Condition=...)]`
- `AdditionalProperties` type changed from `SerializableDictionary<string, object>` to `Dictionary<string, JsonElement>`
- `AdaptiveNumberInput.Value/Min/Max` changed from `double` (NaN default) to `double?` (null default)
- `[JsonInclude]` added to private/internal properties that STJ needs to see

### Files Changed

- **136 files** modified across library, tests, samples, and packaging
- **1,717 lines** added, **1,581 lines** removed
- **3 files** deleted, **4 files** created

## Verification

| Check | Result |
| ----- | ------ |
| Newtonsoft references in .cs files | **0** |
| Newtonsoft references in .csproj files | **0** |
| Newtonsoft references in .nuspec files | **0** |
| Library build | **0 errors, 0 warnings** |
| Test build | **0 errors** |
| Tests passing | **169/170** (1 pre-existing skip) |
| New STJ-specific tests added | **33** |

## Key Files

| File | Role |
| ---- | ---- |
| `AdaptiveCard.cs` | `FromJson()` / `ToJson()` entry points |
| `AdaptiveTypedElementConverter.cs` | Polymorphic dispatch (`JsonConverterFactory`) |
| `AdaptiveCardConverter.cs` | Top-level card deserialization + version validation |
| `AdaptiveCardSerializationContext.cs` | Builds `JsonSerializerOptions` with all converters |
| `AdaptiveCollectionElementConverterFactory.cs` | Forces object deserialization for collection elements |
| `IgnoreEmptyItemsConverter.cs` | Handles body/actions/items list deserialization |
| `SystemTextJsonMigrationTests.cs` | 33 new tests validating STJ behavior |
