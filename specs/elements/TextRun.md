<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# TextRun

#### Introduced in version 1.2

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"TextRun"` | Yes | Must be `"TextRun"`. | 1.2 |
| **text** | `string` | Yes | Text to display | 1.2 |
| **color** | `Colors` | No | Controls the color of the text. | 1.2 |
| **fontType** | `FontType` | No | The type of font to use | 1.2 |
| **highlight** | `boolean` | No | If `true`, displays the text highlighted. | 1.2 |
| **isSubtle** | `boolean` | No | If `true`, displays text slightly toned down to appear less prominent. | 1.2 |
| **italic** | `boolean` | No | If `true`, displays the text using italic font. | 1.2 |
| **selectAction** | `ISelectAction` | No | Action to invoke when this text run is clicked. Visually changes the text run into a hyperlink. `Action.ShowCard` is not supported. | 1.2 |
| **size** | `FontSize` | No | Controls size of text. | 1.2 |
| **strikethrough** | `boolean` | No | If `true`, displays the text with strikethrough. | 1.2 |
| **weight** | `FontWeight` | No | Controls the weight of the text. | 1.2 |
<!-- END AUTO-GENERATED -->

## Rendering