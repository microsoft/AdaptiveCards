<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# AdaptiveCard

|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**type**|`"AdaptiveCard"`|Yes|Must be `"AdaptiveCard"`.|1.0
|**actions**|`array[]`| No|The Actions to show in the card's action bar.|1.0
|**body**|`array[]`| No|The card elements to show in the primary card region.|1.0
|**selectAction**|`object`| No|An Action that will be invoked when the card is tapped or selected. `Action.ShowCard` is not supported.|1.1
|**version**|`string`| No|Schema version that this card requires. If a client is **lower** than this version, the `fallbackText` will be rendered. NOTE: Version is not required for cards within an `Action.ShowCard`|1.0
|**fallbackText**|`string`| No|Text shown when the client doesn't support the version specified (may contain markdown).|1.0
|**backgroundImage**|`string`| No|An image to use as the background of the card.|1.0
|**speak**|`string`| No|Specifies what should be spoken for this entire card. This is simple text or SSML fragment.|1.0
|**lang**|`string`| No|The 2-letter ISO-639-1 language used in the card. Used to localize any date/time functions.|1.0

<!-- END AUTO-GENERATED -->

## Rendering