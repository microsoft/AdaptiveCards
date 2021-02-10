<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# TextRun

#### Introduced in version 1.2

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"TextRun"` | Yes | Must be `"TextRun"`. | 1.2 |
| **text** | `string` | Yes | Text to display. Markdown is not supported. | 1.2 |
| **color** | `Colors` | No | Controls the color of the text. | 1.2 |
| **fontType** | `FontType` | No | The type of font to use | 1.2 |
| **highlight** | `boolean` | No | If `true`, displays the text highlighted. | 1.2 |
| **isSubtle** | `boolean` | No | If `true`, displays text slightly toned down to appear less prominent. | 1.2 |
| **italic** | `boolean` | No | If `true`, displays the text using italic font. | 1.2 |
| **selectAction** | `ISelectAction` | No | Action to invoke when this text run is clicked. Visually changes the text run into a hyperlink. `Action.ShowCard` is not supported. | 1.2 |
| **size** | `FontSize` | No | Controls size of text. | 1.2 |
| **strikethrough** | `boolean` | No | If `true`, displays the text with strikethrough. | 1.2 |
| **underline** | `boolean` | No | If `true`, displays the text with an underline. | 1.3 |
| **weight** | `FontWeight` | No | Controls the weight of the text. | 1.2 |


## color

Controls the color of the text.

* **Type**: `Colors`
* **Required**: No
* **Allowed values**:
  * `"default"`
  * `"dark"`
  * `"light"`
  * `"accent"`
  * `"good"`
  * `"warning"`
  * `"attention"`


## fontType

The type of font to use

* **Type**: `FontType`
* **Required**: No
* **Allowed values**:
  * `"default"`
  * `"monospace"`


## selectAction

Action to invoke when this text run is clicked. Visually changes the text run into a hyperlink. `Action.ShowCard` is not supported.

* **Type**: `ISelectAction`
* **Required**: No
* **Allowed values**:
  * `Action.OpenUrl`
  * `Action.Submit`
  * `Action.ToggleVisibility`


## size

Controls size of text.

* **Type**: `FontSize`
* **Required**: No
* **Allowed values**:
  * `"default"`
  * `"small"`
  * `"medium"`
  * `"large"`
  * `"extraLarge"`


## weight

Controls the weight of the text.

* **Type**: `FontWeight`
* **Required**: No
* **Allowed values**:
  * `"default"`
  * `"lighter"`
  * `"bolder"`
<!-- END AUTO-GENERATED -->

## Rendering

Display all the properties as described.