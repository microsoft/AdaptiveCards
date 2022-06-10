# FactSet renewal

## Justification

FactSet is one of the elements were created and designed in the first version of Adaptive Cards, during the first version of the platform the scope of using a FactSet was really limited and accessibility was not a priority in the team, as such the element has no customization properties at all, this has provoked [bugs](https://microsoft.visualstudio.com/OS/_workitems/edit/37990023) to be filed against us and developers using other controls to achieve the same results.

## Design proposal

To service as many customization scenarios as possible the following updates in the schema are proposed:

### TextBlock properties on FactSet

An easy way to customize a whole FactSet can be by supporting all `TextBlock` properties in the FactSet element.

The resulting schema would be:

| Property | Type | Required | Description | Version |
| --- | --- | --- | --- | --- |
| type | "FactSet" | Yes | Must be "FactSet". | 1.0 |
| facts | Fact[] | Yes | The array of Fact's. | 1.0 |
| color | Colors? | No | Controls the color of TextBlock elements. | 1.4 |
| fontType | FontType? | No | Type of font to use for rendering | 1.4 |
| horizontalAlignment | HorizontalAlignment? | No | Controls the horizontal text alignment. When not specified, the value of horizontalAlignment is inherited from the parent container. If no parent container has horizontalAlignment set, it defaults to  Left. | 1.4 |
| isSubtle | boolean? | No | If true, displays text slightly toned down to appear less prominent. | 1.4 |
| maxLines | number | No | Specifies the maximum number of lines to display. | 1.4 |
| size | FontSize? | No | Controls size of text. | 1.4 |
| weight | FontWeight? | No | Controls the weight of fact elements. | 1.4 |
| wrap | boolean | No | If true, allow text to wrap. Otherwise, text is clipped. | 1.4 |

#### Sample

```
{
	"type": "FactSet",
    "color": "dark",
    "wrap": true,
    "size": "small",
	"facts": [
		{
			"title": "High",
			"value": "50"
		},
		{
			"title": "Low",
			"value": "32"
		}
	]
}
```

// TODO: Mock image here

### Facts as TextBlocks

A more granular way of customizing a single fact would be allowing `Fact`'s title or value properties support `string` or `TextBlock` as valid values, this would enable card authors to have the flexibility of updating a single title or value inside a Fact without having to update the whole `FactSet`.

As this is more specific than updating the whole `FactSet` if the card author would use a `TextBlock` as a title or value then the `TextBlock` properties would override any properties set in the `FactSet`.

#### Sample

```
{
	"type": "FactSet",
    "weight": "bolder",
	"facts": [
		{
			"title": "Processor",
			"value": 
                { 
                    "type": "TextBlock",
                    "text": "Intel Core i9" 
                }
		},
		{
			"title": "Memory",
			"value": 
                { 
                    "type": "TextBlock",
                    "text": "1 GB",
                    "color: "attention"
                }
		},
        {
			"title": "Status",
			"value": { 
                    "type": "TextBlock",
                    "text": "Components may need an update",
                    "color: "warning"
                }
		}
	]
}
```

// TODO: Mock image here

## Work Plan

### Immediate work

To fix the open bug the affected card can be updated to make use of the `Table` element so text can be colored in a specific way without breaking the scenario.

### Version 1: Applying design updates

Due to the limited time resource this updates can be brought up later as the planning allows.