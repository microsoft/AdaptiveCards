<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Input.Date

|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**id**|`string`|Yes|Unique identifier for the value. Used to identify collected input when the Submit action is performed.|1.0
|**max**|`string`| No|Hint of maximum value expressed in ISO-8601 format (may be ignored by some clients).|1.0
|**min**|`string`| No|Hint of minimum value expressed in ISO-8601 format (may be ignored by some clients).|1.0
|**placeholder**|`string`| No|Description of the input desired. Displayed when no selection has been made.|1.0
|**type**|`"Input.Date"`|Yes|Must be `"Input.Date"`.|1.0
|**value**|`string`| No|The initial value for this field expressed in ISO-8601 format.|1.0
|**spacing**|`string`| No|Controls the amount of spacing between this element and the preceding element.|1.0
|**separator**|`boolean`| No, default: `false`|When `true`, draw a separating line at the top of the element.|1.0

<!-- END AUTO-GENERATED -->

## Rendering