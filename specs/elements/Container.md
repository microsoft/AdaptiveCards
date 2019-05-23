<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Container

|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**type**|`"Container"`|Yes|Must be `"Container"`.|1.0
|**items**|`array[]`|Yes|The card elements to render inside the `Container`.|1.0
|**selectAction**|`object`| No|An Action that will be invoked when the `Container` is tapped or selected. `Action.ShowCard` is not supported.|1.1
|**style**|`string`| No|Style hint for `Container`.|1.0
|**verticalContentAlignment**|`string`| No, default: `"top"`|Defines how the content should be aligned vertically within the container.|1.1
|**bleed**|`boolean`| No, default: `false`|Determines whether the element should bleed through its ancestor's padding.|1.2
|**id**|`string`| No|A unique identifier associated with the element.|1.0
|**spacing**|`string`| No|Controls the amount of spacing between this element and the preceding element.|1.0
|**separator**|`boolean`| No, default: `false`|When `true`, draw a separating line at the top of the element.|1.0

<!-- END AUTO-GENERATED -->

## Rendering