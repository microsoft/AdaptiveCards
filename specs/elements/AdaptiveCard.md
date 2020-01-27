<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# AdaptiveCard

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"AdaptiveCard"` | Yes | Must be `"AdaptiveCard"`. | 1.0 |
| **version** | `string` | Yes | Schema version that this card requires. If a client is **lower** than this version, the `fallbackText` will be rendered. NOTE: Version is not required for cards within an `Action.ShowCard`. However, it *is* required for the top-level card. | 1.0 |
| **body** | `Element[]` | No | The card elements to show in the primary card region. | 1.0 |
| **actions** | `Action[]` | No | The Actions to show in the card's action bar. | 1.0 |
| **selectAction** | `ISelectAction` | No | An Action that will be invoked when the card is tapped or selected. `Action.ShowCard` is not supported. | 1.1 |
| **fallbackText** | `string` | No | Text shown when the client doesn't support the version specified (may contain markdown). | 1.0 |
| **backgroundImage** | `BackgroundImage`, `uri` | No | Specifies the background image of the card. | 1.2, 1.0 |
| **minHeight** | `string` | No | Specifies the minimum height of the card. | 1.2 |
| **speak** | `string` | No | Specifies what should be spoken for this entire card. This is simple text or SSML fragment. | 1.0 |
| **lang** | `string` | No | The 2-letter ISO-639-1 language used in the card. Used to localize any date/time functions. | 1.0 |
| **verticalContentAlignment** | `VerticalContentAlignment` | No | Defines how the content should be aligned vertically within the container. Only relevant for fixed-height cards, or cards with a `minHeight` specified. | 1.1 |
| **$schema** | `uri` | No | The Adaptive Card schema. | 1.0 |
| **id** | `string` | No | A unique identifier associated with the AdaptiveCard. | 1.0 |


## body

The card elements to show in the primary card region.

* **Type**: `Element[]`
* **Required**: No
* **Allowed values**:
  * `ActionSet`
  * `ColumnSet`
  * `Container`
  * `FactSet`
  * `Image`
  * `ImageSet`
  * `Input.ChoiceSet`
  * `Input.Date`
  * `Input.Number`
  * `Input.Text`
  * `Input.Time`
  * `Input.Toggle`
  * `Media`
  * `RichTextBlock`
  * `TextBlock`


## actions

The Actions to show in the card's action bar.

* **Type**: `Action[]`
* **Required**: No
* **Allowed values**:
  * `Action.OpenUrl`
  * `Action.ShowCard`
  * `Action.Submit`
  * `Action.ToggleVisibility`


## selectAction

An Action that will be invoked when the card is tapped or selected. `Action.ShowCard` is not supported.

* **Type**: `ISelectAction`
* **Version** : 1.1
* **Required**: No
* **Allowed values**:
  * `Action.OpenUrl`
  * `Action.Submit`
  * `Action.ToggleVisibility`


## backgroundImage

Specifies the background image of the card.

* **Type**: `BackgroundImage`, `uri`
* **Version** : 1.2, 1.0
* **Required**: No
* **Allowed values**:
  * `BackgroundImage`
  * `uri`


## verticalContentAlignment

Defines how the content should be aligned vertically within the container. Only relevant for fixed-height cards, or cards with a `minHeight` specified.

* **Type**: `VerticalContentAlignment`
* **Version** : 1.1
* **Required**: No
* **Allowed values**:
  * `"top"`
  * `"center"`
  * `"bottom"`
<!-- END AUTO-GENERATED -->

## Rendering

1. First check that all required properties are present and valid. If not, return a rendering error.
1. Then, check the `version` value. It is formatted as a string like `1.2`. If the `version` value is greater than your current Adaptive Cards supported version of your renderer...
	1. Display the `fallbackText` instead. Use the same markdown and text processing support as described in `TextBlock`.
	1. If the `fallbackText` wasn't provided, return a rendering error.
1. Else, start creating the card...
1. Create a native UI container with the padding specified in `hostConfig.spacing.padding`.
1. If `body` is specified, render each element following the same rules as `Container`.
1. If `actions` is specified, render each action following the same rules as `ActionSet`. Typically the actions should be rendered BELOW the `body`, but renderers can choose where to render them depending on what makes the most sense.
1. If both `body` and `actions` were rendered, ensure spacing between the `body` and `actions` is set to the value specified in `hostConfig.actions.spacing`.
1. If `selectAction` was specified and valid, make the entire card clickable, invoking that action when clicked.
1. If supporting reading cards aloud, use the `speak` tag if specified and process it as SSML fragment text.