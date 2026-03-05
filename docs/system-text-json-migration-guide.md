# Migrating from Newtonsoft.Json to System.Text.Json — Consumer Guide

> **Applies to**: AdaptiveCards .NET SDK v4.0+  
> **GitHub Issue**: [#9146](https://github.com/microsoft/AdaptiveCards/issues/9146)

## Overview

Starting with v4.0, the AdaptiveCards .NET SDK has migrated from `Newtonsoft.Json` to `System.Text.Json`. This removes the `Newtonsoft.Json` transitive dependency entirely, aligning with the modern .NET ecosystem.

**This is a breaking change.** If your code references Newtonsoft.Json types exposed by the AdaptiveCards SDK, you will need to update it. This guide covers what changed and how to migrate.

---

## What Didn't Change

The core API surface remains the same:

```csharp
// These still work identically
var result = AdaptiveCard.FromJson(jsonString);
var card = result.Card;
var json = card.ToJson();

var hostConfig = AdaptiveHostConfig.FromJson(hostConfigJson);
```

Card parsing, rendering, and the object model (`AdaptiveTextBlock`, `AdaptiveImage`, `AdaptiveAction`, etc.) are unchanged. If you only use `FromJson()` / `ToJson()` and interact with the card object model, your code likely requires **no changes**.

---

## Breaking Changes

### 1. NuGet Dependency: `Newtonsoft.Json` → `System.Text.Json`

**Before**: `AdaptiveCards` package depended on `Newtonsoft.Json 13.0.3`  
**After**: `AdaptiveCards` package depends on `System.Text.Json 8.0.5`

If your project still needs Newtonsoft.Json for other reasons, you can keep both packages. They don't conflict.

### 2. `AdditionalProperties` Type Changed

The `AdditionalProperties` dictionary on `AdaptiveTypedElement`, `AdaptiveInline`, and `AdaptiveMetadata` changed from `SerializableDictionary<string, object>` to `Dictionary<string, JsonElement>`.

**Before (Newtonsoft)**:

```csharp
using Newtonsoft.Json.Linq;

var card = AdaptiveCard.FromJson(json).Card;
var textBlock = card.Body[0] as AdaptiveTextBlock;

// Values were boxed objects or JToken
object value = textBlock.AdditionalProperties["customProp"];
string str = value.ToString();
int num = (int)(long)value;
```

**After (System.Text.Json)**:

```csharp
using System.Text.Json;

var card = AdaptiveCard.FromJson(json).Card;
var textBlock = card.Body[0] as AdaptiveTextBlock;

// Values are now JsonElement
JsonElement value = textBlock.AdditionalProperties["customProp"];
string str = value.GetString();
int num = value.GetInt32();
bool flag = value.GetBoolean();

// To set additional properties programmatically:
textBlock.AdditionalProperties["myProp"] = JsonSerializer.SerializeToElement("hello");
textBlock.AdditionalProperties["myNum"] = JsonSerializer.SerializeToElement(42);
```

### 3. `AdaptiveConfigBase.AdditionalData` Type Changed

**Before**: `IDictionary<string, JToken>`  
**After**: `Dictionary<string, JsonElement>`

Same migration pattern as `AdditionalProperties` above.

### 4. `RenderedAdaptiveCardInputs.AsJson()` Return Type Changed

**Before**: Returns `Newtonsoft.Json.Linq.JObject`  
**After**: Returns `System.Text.Json.Nodes.JsonNode`

**Before (Newtonsoft)**:

```csharp
using Newtonsoft.Json.Linq;

JObject inputs = renderedCard.UserInputs.AsJson();
string value = inputs["inputId"].Value<string>();
string jsonStr = inputs.ToString();
```

**After (System.Text.Json)**:

```csharp
using System.Text.Json.Nodes;

JsonNode inputs = renderedCard.UserInputs.AsJson();
string value = inputs["inputId"]?.GetValue<string>();
string jsonStr = inputs.ToJsonString();
```

### 5. Public Converter Base Classes Changed

If you implemented custom `JsonConverter` classes that inherited from AdaptiveCards converter types, their base classes have changed:

| Class | Before (Newtonsoft) | After (System.Text.Json) |
| ----- | ------------------- | ------------------------ |
| `AdaptiveTypedBaseElementConverter` | `Newtonsoft.Json.JsonConverter` | `System.Text.Json.Serialization.JsonConverter<AdaptiveTypedElement>` |
| `AdaptiveCardConverter` | `Newtonsoft.Json.JsonConverter` | `System.Text.Json.Serialization.JsonConverter<AdaptiveCard>` |
| `AdaptiveTypedElementConverter` | `Newtonsoft.Json.JsonConverter` | `System.Text.Json.Serialization.JsonConverterFactory` |
| `AdaptiveFallbackConverter` | `Newtonsoft.Json.JsonConverter` | `System.Text.Json.Serialization.JsonConverter<AdaptiveFallbackElement>` |

### 6. Serialization Output Differences

`card.ToJson()` produces **semantically identical but not byte-identical** JSON compared to the Newtonsoft version. Differences include:

| Aspect | Newtonsoft Output | System.Text.Json Output |
| ------ | ----------------- | ----------------------- |
| Property order | `type` always first | Declaration order (still deterministic) |
| Integer doubles | `5.0` | `5` |
| Default values | Omitted (`isVisible: true` not shown) | May be included |
| Empty arrays | Omitted (`"actions": []` not shown) | May be included |

**These differences do not affect any Adaptive Card renderer.** JSON is an unordered format by specification, and all renderers parse by property name, not position. Extra properties with default values are ignored by renderers.

**If your code compares `ToJson()` output as exact strings, you will need to update those comparisons.** Use semantic JSON comparison instead:

```csharp
// DON'T: Exact string comparison (fragile)
Assert.AreEqual(expectedJson, card.ToJson());

// DO: Semantic comparison via parse roundtrip
var reparsed = AdaptiveCard.FromJson(card.ToJson()).Card;
Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
Assert.AreEqual(card.Version.ToString(), reparsed.Version.ToString());
```

### 7. Duplicate JSON Keys

JSON payloads with duplicate property names (e.g., `{"type": "TextBlock", "text": "A", "text": "B"}`) are technically valid per RFC 8259, though discouraged. Newtonsoft.Json silently accepted duplicates, keeping the last value.

System.Text.Json's `JsonObject.Create()` throws an `ArgumentException` on duplicate keys. To maintain compatibility, the SDK uses an internal `SafeJsonHelper` that handles duplicates by keeping the last value — matching the previous behavior.

**If your card payloads have duplicate keys**, they will still parse correctly. However, duplicate keys indicate a malformed payload and should be fixed at the source.

---

## Common Migration Patterns

### Replacing `JsonConvert`

```csharp
// Before
using Newtonsoft.Json;
var obj = JsonConvert.DeserializeObject<MyType>(json);
var json = JsonConvert.SerializeObject(obj);

// After
using System.Text.Json;
var obj = JsonSerializer.Deserialize<MyType>(json);
var json = JsonSerializer.Serialize(obj);
```

### Replacing `JObject` / `JToken` / `JArray`

```csharp
// Before
using Newtonsoft.Json.Linq;
var jObj = JObject.Parse(json);
string val = jObj["key"].Value<string>();
var jArr = JArray.Parse(arrayJson);

// After
using System.Text.Json.Nodes;
var jObj = JsonNode.Parse(json).AsObject();
string val = jObj["key"]?.GetValue<string>();
var jArr = JsonNode.Parse(arrayJson).AsArray();
```

### Replacing `JObject.FromObject()`

```csharp
// Before
var jObj = JObject.FromObject(myDictionary);

// After
var node = JsonSerializer.SerializeToNode(myDictionary);
```

### Replacing `Formatting.Indented`

```csharp
// Before
var json = JsonConvert.SerializeObject(obj, Formatting.Indented);

// After
var json = JsonSerializer.Serialize(obj, new JsonSerializerOptions { WriteIndented = true });
```

---

## FAQ

### Do I need to update my Adaptive Card JSON payloads?

**No.** Card JSON is parsed identically by both libraries. Your existing card payloads work without changes.

### Do I need to update my Host Config JSON?

**No.** Host config JSON is parsed identically.

### Can I still use Newtonsoft.Json in my project alongside AdaptiveCards?

**Yes.** Both packages can coexist. The AdaptiveCards SDK no longer depends on Newtonsoft.Json but doesn't prevent you from using it.

### Why was this change made?

1. `System.Text.Json` is the built-in JSON library for modern .NET — no additional dependency needed for .NET 6+
2. ~2x faster serialization and ~1.5-3x faster deserialization
3. ~50-80% fewer memory allocations
4. `Newtonsoft.Json` is no longer actively developed
5. Aligns with the rest of the .NET ecosystem (ASP.NET Core, Azure SDK, etc.)

### What .NET versions are supported?

The SDK continues to target `netstandard2.0`, using `System.Text.Json 8.0.5` as a NuGet package. This supports:

- .NET 6, 7, 8, 9+
- .NET Framework 4.6.2+ (via NuGet package)
- .NET Standard 2.0 compatible runtimes

### I found a behavioral difference not listed here. What should I do?

Please open an issue at [github.com/microsoft/AdaptiveCards](https://github.com/microsoft/AdaptiveCards/issues) with a repro case showing the difference.
