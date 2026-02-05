# System.Text.Json Support for AdaptiveCards

This document demonstrates the System.Text.Json serialization support in the AdaptiveCards .NET library.

## 🚨 BREAKING CHANGE NOTICE

**As of this version, AdaptiveCards has migrated from Newtonsoft.Json to System.Text.Json for all JSON operations.**

## Overview

The AdaptiveCards library now uses **System.Text.Json** as the primary JSON serialization engine. This change provides:

- **Better Performance**: Significant improvements over Newtonsoft.Json
- **Modern .NET Support**: Full compatibility with current .NET applications  
- **Reduced Dependencies**: Less reliance on external libraries
- **Enhanced Security**: Built-in .NET serialization

## Migration Guide

### For Most Users: No Code Changes Required

If you were using the standard AdaptiveCards API, **no changes are needed**:

```csharp
// This code continues to work exactly the same
var card = new AdaptiveCard("1.0");
card.Body.Add(new AdaptiveTextBlock("Hello, World!"));

// ToJson() now uses System.Text.Json internally
string json = card.ToJson();

// FromJson() now uses System.Text.Json internally  
var result = AdaptiveCard.FromJson(json);
```

### What Changed

- `ToJson()` and `FromJson()` methods now use System.Text.Json internally
- JSON output may have minor formatting differences (property order, whitespace)
- Better performance for serialization/deserialization operations

## Usage

### Creating and Serializing Cards

```csharp
using AdaptiveCards;

// Create an AdaptiveCard
var card = new AdaptiveCard("1.0")
{
    FallbackText = "This card requires a newer client",
    Speak = "Welcome to our service"
};

// Add content
card.Body.Add(new AdaptiveTextBlock("Hello, World!")
{
    Size = AdaptiveTextSize.Large,
    Weight = AdaptiveTextWeight.Bolder,
    Color = AdaptiveTextColor.Accent
});

// Add actions
card.Actions.Add(new AdaptiveSubmitAction
{
    Title = "Submit",
    Id = "submitButton"
});

// Serialize using System.Text.Json (now the default)
string json = card.ToJson();
```

### Deserializing Cards

```csharp
string json = @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""Hello from System.Text.Json!""
        }
    ]
}";

// Deserialize using System.Text.Json (now the default)
var result = AdaptiveCard.FromJson(json);
var card = result.Card;
```

## JSON Output Comparison

Both serializers produce similar, clean JSON output:

### Newtonsoft.Json Output
```json
{
  "type": "AdaptiveCard",
  "version": "1.0",
  "fallbackText": "This card requires a newer client",
  "speak": "Welcome to our service",
  "body": [
    {
      "type": "TextBlock",
      "text": "Hello, World!",
      "size": "large",
      "weight": "bolder",
      "color": "accent"
    }
  ],
  "actions": [
    {
      "type": "Action.Submit",
      "title": "Submit",
      "id": "submitButton"
    }
  ]
}
```

### System.Text.Json Output
```json
{
  "type": "AdaptiveCard",
  "version": "1.0",
  "fallbackText": "This card requires a newer client",
  "speak": "Welcome to our service",
  "body": [
    {
      "text": "Hello, World!",
      "color": "accent",
      "size": "large",
      "weight": "bolder",
      "type": "TextBlock"
    }
  ],
  "actions": [
    {
      "type": "Action.Submit",
      "id": "submitButton",
      "title": "Submit"
    }
  ]
}
```

## Migration Benefits

1. **Modern .NET Support**: System.Text.Json is the recommended JSON library for modern .NET applications
2. **Performance**: System.Text.Json typically offers better performance than Newtonsoft.Json
3. **Reduced Dependencies**: System.Text.Json is built into modern .NET, reducing external dependencies
4. **Compatibility**: Both APIs can be used side-by-side during migration

## Current Support

### Supported Elements
- ✅ AdaptiveCard (base properties)
- ✅ AdaptiveTextBlock
- ✅ Basic actions (Submit, OpenUrl)

### Supported Features  
- ✅ Version handling
- ✅ Card-level properties (fallbackText, speak, lang, etc.)
- ✅ Element properties (id, spacing, separator, visibility)
- ✅ Text formatting (size, weight, color, wrap)
- ✅ Basic actions

### Roadmap
- 🔄 Additional element types (Image, Container, ColumnSet, etc.)
- 🔄 Complex actions (ShowCard, ToggleVisibility, Execute)
- 🔄 Input elements
- 🔄 Advanced features (fallback, refresh, authentication)

## Backward Compatibility

The existing Newtonsoft.Json API remains unchanged and fully supported:
- `AdaptiveCard.ToJson()` - uses Newtonsoft.Json
- `AdaptiveCard.FromJson(json)` - uses Newtonsoft.Json

The new System.Text.Json API is additive:
- `AdaptiveCard.ToJsonSystemText()` - uses System.Text.Json
- `AdaptiveCard.FromJsonSystemText(json)` - uses System.Text.Json

## Technical Implementation

The System.Text.Json implementation uses a DTO (Data Transfer Object) approach:

1. **Clean DTOs** - Specialized classes for JSON representation with proper attributes
2. **Object Mapping** - Conversion between rich domain objects and DTOs  
3. **Polymorphic Support** - Handles different element and action types
4. **Attribute Control** - Uses JsonPropertyName and JsonIgnore for clean output

This approach ensures the JSON output is clean and minimal while maintaining the full functionality of the rich object model.