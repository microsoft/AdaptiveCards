// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export const adaptiveCardSchema =
{
  "$schema": "http://json-schema.org/draft-06/schema#",
  "id": "http://adaptivecards.io/schemas/adaptive-card.json",
  "type": "object",
  "title": "Microsoft Adaptive Card Schema",
  "additionalProperties": true,
  "allOf": [
    {
      "$ref": "#/definitions/AdaptiveCard"
    }
  ],
  "properties": {
    "version": {
      "type": "string",
      "description": "version of schema that this card was authored "
    },
    "minVersion": {
      "type": "string",
      "description": "if a client doesn't support the minVersion the card should be rejected and return the fallbackText.  If it does, then the elements that are not supported are safe to ignore"
    },
    "fallbackText": {
      "type": "string",
      "description": "if a client is not able to show the card, show fallbackText to the user. This can be in markdown format. "
    },
    "speak": {
      "type": "string",
      "description": "Specifies what should be spoken for this entire Item. This is simple text or SSML fragment"
    }
  },
  "required": [
    "version"
  ],
  "definitions": {
    "Action": {
      "anyOf": [
        {
          "$ref": "#/definitions/Action.Submit"
        },
        {
          "$ref": "#/definitions/Action.ShowCard"
        },
        {
          "$ref": "#/definitions/Action.OpenUrl"
        }
      ]
    },
    "Action.OpenUrl": {
      "additionalProperties": true,
      "description": "When Action.OpenUrl is invoked it will show the given url, either by launching it to an external web browser or showing in-situ with embedded web browser.",
      "properties": {
        "title": {
          "type": "string",
          "description": "Label for button or link that represents this action"
        },
        "type": {
          "type": "string",
          "description": "Must be Action.OpenUrl",
          "enum": [
            "Action.OpenUrl"
          ]
        },
        "url": {
          "type": "string",
          "description": "The URL to open"
        }
      },
      "required": [
        "type",
        "url"
      ],
      "type": "object"
    },
    "Action.ShowCard": {
      "type": "object",
      "additionalProperties": true,
      "description": "Action.ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.",
      "properties": {
        "type": {
          "type": "string",
          "description": "Must be Action.ShowCard",
          "enum": [
            "Action.ShowCard"
          ]
        },
        "title": {
          "type": "string",
          "description": "Label for button or link that represents this action"
        },
        "card": {
          "$ref": "#/definitions/AdaptiveCard"
        }
      },
      "required": [
        "type",
        "card"
      ]
    },
    "Action.Submit": {
      "type": "object",
      "additionalProperties": true,
      "description": "Submit action gathers up input fields, merges with optional data field and generates event to client asking for data to be submitted. It is up to the client to determine how that data is processed. For example: With BotFramework bots the client would send an activity through the messaging medium to the bot.",
      "properties": {
        "type": {
          "type": "string",
          "description": "Must be Action.Submit",
          "enum": [
            "Action.Submit"
          ]
        },
        "title": {
          "type": "string",
          "description": "Label for button or link that represents this action"
        },
        "data": {
          "type": [ "string", "object" ],
          "description": "initial data that input fields will be combined with. This is essentially 'hidden' properties"
        }
      },
      "required": [
        "type"
      ]
    },
    "Actions": {
      "additionalItems": true,
      "items": {
        "$ref": "#/definitions/Action"
      },
      "type": "array"
    },
    "AdaptiveCard": {
      "additionalProperties": true,
      "type": "object",
      "description": "Card schema for an adaptive card",
      "properties": {
        "type": {
          "type": "string",
          "description": "Must be AdaptiveCard",
          "enum": [
            "AdaptiveCard"
          ]
        },
        "actions": {
          "description": "The Actions to show in the card's action bar",
          "$ref": "#/definitions/Actions"
        },
        "body": {
          "description": "The Card Elements to show in the primary card region",
          "$ref": "#/definitions/CardElements"
        }
      },
      "required": [
        "type",
        "version"
      ]
    },
    "CardElement": {
      "additionalProperties": true,
      "properties": {
        "type": {
          "type": "string"
        },
        "id": {
          "type": "string",
          "description": "A unique Id associated with the element"
        },
        "spacing": {
          "$ref": "#/definitions/SpacingStyle"
        },
        "separator": {
          "type": "boolean",
          "description": "The Separator object type describes the look and feel of a separation line between two elements.",
          "default": false
        }
      },
      "required": [
        "type"
      ]
    },
    "CardElements": {
      "type": "array",
      "additionalItems": true,
      "items": [
        {
          "anyOf": [
            {
              "$ref": "#/definitions/TextBlock"
            },
            {
              "$ref": "#/definitions/Image"
            },
            {
              "$ref": "#/definitions/Container"
            },
            {
              "$ref": "#/definitions/ColumnSet"
            },
            {
              "$ref": "#/definitions/FactSet"
            },
            {
              "$ref": "#/definitions/ImageSet"
            },
            {
              "$ref": "#/definitions/Input.Text"
            },
            {
              "$ref": "#/definitions/Input.Number"
            },
            {
              "$ref": "#/definitions/Input.Date"
            },
            {
              "$ref": "#/definitions/Input.Time"
            },
            {
              "$ref": "#/definitions/Input.Toggle"
            },
            {
              "$ref": "#/definitions/Input.ChoiceSet"
            }
          ]
        }
      ]
    },
    "Input.Choice": {
      "type": "object",
      "description": "Describes a Choice input. The value should be a simple string without a \",\"",
      "additionalProperties": true,
      "properties": {
        "type":{
          "type":"string",
          "enum": [
            "Input.Choice"
          ]
        },
        "title": {
          "type": "string",
          "description": "The text for a choice"
        },
        "value": {
          "type": "string",
          "description": "The raw value for the choice. NOTE: do not use a \",\" in the value, since MultiSelect ChoiceSet returns a comma-delimited string of choice values"
        }
      },
      "required": [
        "title",
        "value"
      ]
    },
    "ChoiceInputStyle": {
      "type": "string",
      "description": "Style hint for Input.ChoiceSet",
      "enum": [
        "compact",
        "expanded"
      ]
    },
    "Column": {
      "additionalProperties": true,
      "type": "object",
      "description": "Defines a container that is part of a ColumnSet",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "items": {
          "description": "The Card Elements to include in the Column",
          "$ref": "#/definitions/CardElements"
        },
        "selectAction": {
          "description": "An Action that will be invoked when the Column is tapped or selected",
          "$ref": "#/definitions/Action"
        },
        "width": {
          "type": [
            "string",
            "number"
          ],
          "description": "\"auto\", \"stretch\", or a number representing relative width of the column in the column group"
        },
        "type": {
          "type": "string",
          "description": "Must be Column",
          "enum": [
            "Column"
          ]
        }
      },
      "required": [
        "items"
      ]
    },
    "ColumnSet": {
      "additionalProperties": true,
      "type": "object",
      "description": "ColumnSet divides a region into Column's allowing elements to sit side-by-side",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "columns": {
          "type": "array",
          "description": "The array of Columns to divide the region into",
          "items": {
            "$ref": "#/definitions/Column"
          }
        },
        "selectAction": {
          "$ref": "#/definitions/Action",
          "description": "The Action that is executed when the ColumnSet is clicked/tapped"
        },
        "type": {
          "type": "string",
          "description": "Must be ColumnSet",
          "enum": [
            "ColumnSet"
          ]
        }
      }
    },
    "Container": {
      "additionalProperties": true,
      "type": "object",
      "description": "Containers group items together",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "items": {
          "description": "The Card Elements to render inside the Container",
          "$ref": "#/definitions/CardElements"
        },
        "selectAction": {
          "description": "An Action that will be invoked when the Image is tapped or selected",
          "$ref": "#/definitions/Action"
        },
        "style": {
          "type": "string",
          "description": "Style hint for Container",
          "enum": [
            "default",
            "emphasis"
          ]
        },
        "type": {
          "type": "string",
          "description": "Must be Container",
          "enum": [
            "Container"
          ]
        }
      },
      "required": [
        "items"
      ]
    },
    "Fact": {
      "additionalProperties": true,
      "type": "object",
      "description": "Describes a Fact in a FactSet as a key/value pair",
      "properties": {
        "type": {
          "type": "string",
          "enum": [
            "Fact"
          ]
        },
        "title": {
          "type": "string",
          "description": "The title of the fact"

        },
        "value": {
          "type": "string",
          "description": "The value of the fact"
        }
      },
      "required": [
        "title",
        "value"
      ]
    },
    "FactSet": {
      "additionalProperties": true,
      "type": "object",
      "description": "The FactSet Item makes it simple to display a series of facts (e.g. name/value pairs) in a tabular form.",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "facts": {
          "type": "array",
          "description": "The array of Facts",
          "items": {
            "$ref": "#/definitions/Fact"
          }
        },
        "type": {
          "type": "string",
          "description": "Must be FactSet",
          "enum": [
            "FactSet"
          ]
        }
      },
      "required": [
        "facts"
      ]
    },
    "HorizontalAlignment": {
      "type": "string",
      "description": "Controls how Items are horizontally positioned within their container.",
      "enum": [
        "left",
        "center",
        "right"
      ]
    },
    "Image": {
      "additionalProperties": true,
      "type": "object",
      "description": "The Image Item allows for the inclusion of images in an Adaptive Card.",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "altText": {
          "type": "string",
          "description": "Alternate text for the image for accessibility"
        },
        "horizontalAlignment": {
          "$ref": "#/definitions/HorizontalAlignment"
        },
        "selectAction": {
          "description": "An Action that will be invoked when the Image is tapped or selected",
          "$ref": "#/definitions/Action"
        },
        "size": {
          "type": "object",
          "$ref": "#/definitions/ImageSize"
        },
        "style": {
          "$ref": "#/definitions/ImageStyle"
        },
        "type": {
          "type": "string",
          "description": "Must be Image",
          "enum": [
            "Image"
          ]
        },
        "url": {
          "type": "string",
          "description": "The URL to the image."
        }
      },
      "required": [
        "url"
      ]
    },
    "ImageSet": {
      "additionalProperties": true,
      "type": "object",
      "description": "The ImageSet allows for the inclusion of a collection images like a photogallery.",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "images": {
          "type": "array",
          "description": "The array of Image elements to show",
          "items": {
            "$ref": "#/definitions/Image"
          }
        },
        "imageSize": {
          "$ref": "#/definitions/ImageSize"
        },
        "type": {
          "type": "string",
          "description": "Must be ImageSet",
          "enum": [
            "ImageSet"
          ]
        }
      },
      "required": [
        "images"
      ]
    },
    "ImageSize": {
      "type": "string",
      "description": "Controls the approximate size of the image. The physical dimensions will vary per host. Specify \"auto\" for true image dimension or \"stretch\" to force it to fill the container",
      "default": "auto",
      "enum": [
        "auto",
        "stretch",
        "small",
        "medium",
        "large"
      ]
    },
    "ImageStyle": {
      "type": "string",
      "description": "Controls the way Images are displayed",
      "enum": [
        "default",
        "person"
      ]
    },
    "Input.ChoiceSet": {
      "additionalProperties": true,
      "type": "object",
      "description": "Shows an array of Choice objects",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "choices": {
          "type": "array",
          "description": "the choice options",
          "items": {
            "$ref": "#/definitions/Input.Choice"
          }
        },
        "id": {
          "type": "string",
          "description": "Id for the value (will be used to identify collected input when SUBMIT is clicked)"
        },
        "isMultiSelect": {
          "type": "boolean",
          "description": "allow multiple choices to be selected",
          "default": false
        },
        "style": {
          "$ref": "#/definitions/ChoiceInputStyle"
        },
        "type": {
          "description": "Must be Input.ChoiceInput",
          "enum": [
            "Input.ChoiceSet"
          ],
          "type": "string"
        },
        "value": {
          "type": "string",
          "description": "The initial choice (or set of choices) that should be selected. For multi-select, specifcy a comma-separated string of values"
        }
      },
      "required": [
        "id",
        "choices"
      ]
    },
    "Input.Date": {
      "additionalProperties": true,
      "type": "object",
      "description": "Input.Date collects Date from the user,",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "id": {
          "type": "string",
          "description": "Id for the value (will be used to identify collected input when SUBMIT is clicked)"
        },
        "max": {
          "type": "string",
          "description": "hint of maximum value expressed in ISO-8601 format (may be ignored by some clients)"
        },
        "min": {
          "type": "string",
          "description": "hint of minimum value expressed in ISO-8601 format (may be ignored by some clients)"
        },
        "placeholder": {
          "type": "string",
          "description": "Title Description of the input desired"
        },
        "type": {
          "type": "string",
          "description": "The type must be Input.Date",
          "enum": [
            "Input.Date"
          ]
        },
        "value": {
          "type": "string",
          "description": "The initial value for a field expressed in ISO-8601 format"
        }
      },
      "required": [
        "id"
      ]
    },
    "Input.Number": {
      "additionalProperties": true,
      "type": "object",
      "description": "Input.Number collects number from the user,",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "id": {
          "type": "string",
          "description": "Id for the value (will be used to identify collected input when SUBMIT is clicked)"
        },
        "max": {
          "type": "number",
          "description": "hint of maximum value (may be ignored by some clients)"
        },
        "min": {
          "type": "number",
          "description": "hint of minimum value (may be ignored by some clients)"
        },
        "placeholder": {
          "type": "string",
          "description": "Title Description of the input desired"
        },
        "type": {
          "type": "string",
          "description": "The type must be Input.Number",
          "enum": [
            "Input.Number"
          ]
        },
        "value": {
          "type": "number",
          "description": "The initial value for a field"
        }
      },
      "required": [
        "id"
      ]
    },
    "Input.Text": {
      "additionalProperties": true,
      "type": "object",
      "description": "Input.Text collects text from the user,",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "id": {
          "type": "string",
          "description": "Id for the value (will be used to identify collected input when SUBMIT is clicked)"
        },
        "isMultiline": {
          "type": "boolean",
          "description": "Do you want to allow multiple lines of input"
        },
        "maxLength": {
          "type": "number",
          "description": "hint of maximum length characters to collect (may be ignored by some clients)"
        },
        "placeholder": {
          "type": "string",
          "description": "Title Description of the input desired"
        },
        "style": {
          "$ref": "#/definitions/TextInputStyle"
        },
        "type": {
          "type": "string",
          "description": "Input.Text",
          "enum": [
            "Input.Text"
          ]
        },
        "value": {
          "type": "string",
          "description": "The initial value for a field"
        }
      },
      "required": [
        "id"
      ]
    },
    "Input.Time": {
      "additionalProperties": true,
      "type": "object",
      "description": "Input.Time collects Time from the user,",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "id": {
          "type": "string",
          "description": "Id for the value (will be used to identify collected input when SUBMIT is clicked)"
        },
        "max": {
          "type": "string",
          "description": "hint of maximum value (may be ignored by some clients)"
        },
        "min": {
          "type": "string",
          "description": "hint of minimum value (may be ignored by some clients)"
        },
        "placeholder": {
          "type": "string",
          "description": "Title Description of the input desired"
        },
        "type": {
          "type": "string",
          "description": "The type must be Input.Time",
          "enum": [
            "Input.Time"
          ]
        },
        "value": {
          "type": "string",
          "description": "The initial value for a field expressed in ISO-8601 format"
        }
      },
      "required": [
        "id"
      ]
    },
    "Input.Toggle": {
      "additionalProperties": true,
      "type": "object",
      "description": "Input.Toggle collects a true/false response from the user",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "id": {
          "type": "string",
          "description": "Id for the value (will be used to identify collected input when SUBMIT is clicked)"
        },
        "title": {
          "type": "string",
          "description": "Title for the toggle"
        },
        "type": {
          "type": "string",
          "description": "Input.Toggle",
          "enum": [
            "Input.Toggle"
          ]
        },
        "value": {
          "type": "string",
          "description": "The current selected value (default:false)"
        },
        "valueOff": {
          "type": "string",
          "description": "The value when toggle is off (default:false)"
        },
        "valueOn": {
          "type": "string",
          "description": "The value when toggle is on (default:true)"
        }
      },
      "required": [
        "id",
        "title"
      ]
    },
    "TextBlock": {
      "additionalProperties": true,
      "type": "object",
      "description": "The TextBlock Item allows for the inclusion of text, with various font sizes, weight and color, in Adaptive Cards.",
      "allOf": [
        {
          "$ref": "#/definitions/CardElement"
        }
      ],
      "properties": {
        "color": {
          "type": "string",
          "description": "Controls the color of TextBlock Items.",
          "enum": [
            "default",
            "dark",
            "light",
            "accent",
            "good",
            "warning",
            "attention"
          ]
        },
        "horizontalAlignment": {
          "$ref": "#/definitions/HorizontalAlignment"
        },
        "isSubtle": {
          "type": "boolean",
          "description": "Indicates whether the color of the text should be slightly toned down to appear less prominent"
        },
        "maxLines": {
          "type": "number",
          "description": "When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use."
        },
        "size": {
          "type": "string",
          "description": "controls size of the text.",
          "enum": [
            "small",
            "default",
            "medium",
            "large",
            "extraLarge"
          ]
        },
        "text": {
          "type": "string",
          "description": "The actual text to display"
        },
        "type": {
          "type": "string",
          "description": "Must be TextBlock",
          "enum": [
            "TextBlock"
          ]
        },
        "weight": {
          "type": "string",
          "description": "Controls the weight of TextBlock Items",
          "enum": [
            "lighter",
            "default",
            "bolder"
          ]
        },
        "wrap": {
          "type": "boolean",
          "description": "True if be is allowed to wrap"
        }
      },
      "required": [
        "text"
      ]
    },
    "SeparatorStyle": {
      "type": "object",
      "description": "Indicates whether there should be a visible separator (e.g. a line) between the element and the one before it. If this property is not specified, no separator is displayed. If it is, a separator line is displayed. A separator will only appear if there was a preceding element.",
      "properties": {
        "thickness": {
          "type": "string",
          "description": "Specifies the thickness of the separation line.",
          "enum": [
            "default",
            "thick"
          ]
        },
        "color": {
          "type": "string",
          "description": "Specifies the color of the separation line.",
          "enum": [
            "default",
            "accent"
          ]
        }
      }
    },
    "SpacingStyle": {
      "type": "string",
      "description": "Controls the amount of spacing between this element and the previous element.",
      "enum": [
        "none",
        "small",
        "default",
        "medium",
        "large",
        "extraLarge",
        "padding"
      ]
    },
    "TextInputStyle": {
      "type": "string",
      "description": "Style hint for Input.Text.",
      "enum": [
        "text",
        "tel",
        "url",
        "email"
      ]
    }
  }
};
