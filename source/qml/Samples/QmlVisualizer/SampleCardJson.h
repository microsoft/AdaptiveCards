#pragma once
#include "stdafx.h"

namespace Samples
{
    const std::string card_Empty = R"({
    "type": "AdaptiveCard",
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "version": "1.3"
    })";

    const std::string card_TextBlock = R"({
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.0",
      "body": [
        {
          "type": "TextBlock",
          "text": "This is some text",
          "size": "large"
        },
        {
          "type": "TextBlock",
          "text": "It doesn't wrap by default",
          "weight": "bolder"
        },
        {
          "type": "TextBlock",
          "text": "So set **wrap** to true if you plan on showing a paragraph of text",
          "wrap": true
        },
        {
          "type": "TextBlock",
          "text": "You can also use **maxLines** to prevent it from getting out of hand",
          "wrap": true,
          "maxLines": 2
        },
        {
          "type": "TextBlock",
          "text": "You can even draw attention to certain text with color",
          "wrap": true,
          "color": "attention"
        },
        {
          "type": "TextBlock",
          "text": "color: default",
          "color": "default"
        },
        {
          "type": "TextBlock",
          "text": "color: accent",
          "color": "accent"
        },
        {
          "type": "TextBlock",
          "text": "color: good",
          "color": "good"
        },
        {
          "type": "TextBlock",
          "text": "color: warning",
          "color": "warning"
        },
        {
          "type": "TextBlock",
          "text": "color: attention",
          "color": "attention"
        },
        {
          "type": "TextBlock",
          "text": "color: light",
          "color": "light"
        },
        {
          "type": "TextBlock",
          "text": "color: dark",
          "color": "dark"
        },
        {
          "type": "TextBlock",
          "text": "**horizontalAlignment:left**",
          "horizontalAlignment": "left"
        },
        {
          "type": "TextBlock",
          "text": "**horizontalAlignment:center**",
          "horizontalAlignment": "center"
        },
        {
          "type": "TextBlock",
          "text": "**horizontalAlignment:right**",
          "horizontalAlignment": "right"
        },
        {
          "type": "TextBlock",
          "text": "isSubtle:false",
          "isSubtle": false
        },
        {
          "type": "TextBlock",
          "text": "isSubtle:true",
          "isSubtle": true
        },
        {
          "type": "TextBlock",
          "text": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
          "wrap": true,
          "maxLines": 1
        },
        {
          "type": "TextBlock",
          "text": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
          "wrap": true,
          "maxLines": 2
        },
        {
          "type": "TextBlock",
          "text": "size:default"
        },
        {
          "type": "TextBlock",
          "text": "size:small",
          "size": "small"
        },
        {
          "type": "TextBlock",
          "text": "size:default",
          "size": "default"
        },
        {
          "type": "TextBlock",
          "text": "size:medium",
          "size": "medium"
        },
        {
          "type": "TextBlock",
          "text": "size:large",
          "size": "large"
        },
        {
          "type": "TextBlock",
          "text": "size:extraLarge",
          "size": "extraLarge"
        },
        {
          "type": "TextBlock",
          "text": "weight: lighter",
          "weight": "lighter"
        },
        {
          "type": "TextBlock",
          "text": "weight: default",
          "weight": "default"
        },
        {
          "type": "TextBlock",
          "text": "weight: bolder",
          "weight": "bolder"
        },
        {
          "type": "TextBlock",
          "text": "**wrap: false** Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat",
          "wrap": false
        },
        {
          "type": "TextBlock",
          "text": "**wrap: true** Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
          "wrap": true
        },
        {
          "type": "TextBlock",
          "text": "Font type not set."
        },
        {
          "type": "TextBlock",
          "text": "Font type set to *default*.",
          "fontType": "default"
        },
        {
          "type": "TextBlock",
          "text": "Font type set to *monospace*.",
          "fontType": "monospace"
        }
      ]
    }
    )";

    const std::string card_InputText = R"({
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.0",
      "body": [
        {
          "type": "TextBlock",
          "text": "Default text input"
        },
        {
          "type": "Input.Text",
          "id": "defaultInputId",
          "placeholder": "enter comment",
          "maxLength": 500
        },
        {
          "type": "TextBlock",
          "text": "Multiline text input"
        },
        {
          "type": "Input.Text",
          "id": "multilineInputId",
          "placeholder": "enter comment",
          "maxLength": 50,
          "isMultiline": true
        },
        {
          "type": "TextBlock",
          "text": "Pre-filled value"
        },
        {
          "type": "Input.Text",
          "id": "prefilledInputId",
          "placeholder": "enter comment",
          "maxLength": 500,
          "isMultiline": true,
          "value": "This value was pre-filled"
        }
      ],
      "actions": [
        {
          "type": "Action.Submit",
          "title": "OK"
        }
      ]
    })";

    const std::string card_InputNumber = R"({
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.0",
      "body": [
        {
          "type": "TextBlock",
          "text": "Default text input"
        },
        {
          "type": "Input.Text",
          "id": "defaultInputId",
          "placeholder": "enter comment",
          "maxLength": 500
        },
        {
          "type": "TextBlock",
          "text": "Multiline text input"
        },
        {
          "type": "Input.Text",
          "id": "multilineInputId",
          "placeholder": "enter comment",
          "maxLength": 50,
          "isMultiline": true
        },
        {
          "type": "TextBlock",
          "text": "Input Number"
        },
        {
          "type": "Input.Number",
          "id": "number",
          "placeholder": "Enter a number",
          "min": 1,
          "max": 10,
          "value": 3
        }
      ],
      "actions": [
        {
          "type": "Action.Submit",
          "title": "OK"
        }
      ]
    })";

    const std::string card_richText = R"({
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.0",
      "body": [
        {
          "type": "RichTextBlock",
          "inlines": [
            "This is the first inline. ",
            {
              "type": "TextRun",
              "text": "We support colors,",
              "color": "good"
            },
            {
              "type": "TextRun",
              "text": " both regular and subtle. ",
              "isSubtle": true
            },
            {
              "type": "TextRun",
              "text": "Text ",
              "size": "small"
            },
            {
              "type": "TextRun",
              "text": "of ",
              "size": "medium"
            },
            {
              "type": "TextRun",
              "text": "all ",
              "size": "large"
            },
            {
              "type": "TextRun",
              "text": "sizes! ",
              "size": "extraLarge"
            },
            {
              "type": "TextRun",
              "text": "Light weight text. ",
              "weight": "lighter"
            },
            {
              "type": "TextRun",
              "text": "Bold weight text. ",
              "weight": "bolder"
            },
            {
              "type": "TextRun",
              "text": "Highlights. ",
              "highlight": true
            },
            {
              "type": "TextRun",
              "text": "Italics. ",
              "italic": true
            },
            {
              "type": "TextRun",
              "text": "Strikethrough. ",
              "strikethrough": true
            },
            {
              "type": "TextRun",
              "text": "Monospace too!",
              "fontType": "monospace"
            }
          ]
        },
        {
          "type": "RichTextBlock",
          "inlines": [
            {
              "type": "TextRun",
              "text": "Date-Time parsing: {{DATE(2017-02-14T06:08:39Z,LONG)}} {{TIME(2017-02-14T06:08:39Z)}}"
            }
          ]
        },
        {
          "type": "RichTextBlock",
          "horizontalAlignment": "center",
          "inlines": [
            {
              "type": "TextRun",
              "text": "Rich text blocks also support center alignment. Lorem ipsum dolor Lorem ipsum dolor Lorem ipsum dolor Lorem ipsum dolor Lorem ipsum dolor "
            }
          ]
        },
        {
          "type": "RichTextBlock",
          "horizontalAlignment": "right",
          "inlines": [
            {
              "type": "TextRun",
              "text": "Rich text blocks also support right alignment. Lorem ipsum dolor Lorem ipsum dolor Lorem ipsum dolor Lorem ipsum dolor Lorem ipsum dolor "
            }
          ]
        }
      ]
    })";

    const std::string card_CheckboxInput = R"({
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.0",
      "body": [
        {
          "type": "TextBlock",
          "text": "Input Number"
        },
        {
          "type": "Input.Number",
          "id": "number",
          "placeholder": "Enter a number",
          "min": 1,
          "max": 10,
          "value": 3
        },
        {
          "type": "TextBlock",
          "text": "Toggle Input"
        },
        {
          "type": "Input.Toggle",
          "id": "acceptTerms",
          "title": "I accept the terms and agreements",
          "value": "true",
          "valueOn": "true",
          "valueOff": "false"
        },
        {
          "type": "TextBlock",
          "text": "Default text input"
        },
        {
          "type": "Input.Text",
          "id": "defaultInputId",
          "placeholder": "enter comment",
          "maxLength": 500
        }
      ],
      "actions": [
        {
          "type": "Action.Submit",
          "title": "OK"
        }
      ]
    })";

    const std::string card_dateInput = R"({
	"$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
	"type": "AdaptiveCard",
	"version": "1.0",
	"body": [
		{
		    "type": "TextBlock",
		    "text": "Date Format: MM/DD/YYYY"
		},
		{
		    "type": "Input.Date",
		    "id": "date",
		    "placeholder": "Enter a date",
		    "value": "2017-10-12",
		    "min":"1900-01-01",
		    "max":"2030-01-01"
		},
	    {
		    "type": "TextBlock",
		    "text": "Date Input Test"
		},
		{
		    "type": "Input.Date",
		    "id": "sample2",
		    "placeholder": "Enter a date",
		    "min":"1900-01-01",
		    "max":"2030-01-01"
		}
	]
    })";

    const std::string card_ChoiceSetInput = R"({
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.0",
      "body": [
        {
          "type": "TextBlock",
          "text": "What color do you want? *(isMultiSelect:false, style:compact)*"
        },
        {
          "type": "Input.ChoiceSet",
          "id": "myColor",
          "style": "compact",
          "isMultiSelect": false,
          "value": "2",
          "choices": [
            {
              "title": "Red",
              "value": "1"
            },
            {
              "title": "Green",
              "value": "2"
            },
            {
              "title": "Blue",
              "value": "3"
            }
          ]
        },
        {
          "type": "TextBlock",
          "text": "What color do you want? *(isMultiSelect:false, style:expanded)*"
        },
        {
          "type": "Input.ChoiceSet",
          "id": "myColor2",
          "style": "expanded",
          "isMultiSelect": false,
          "value": "1",
          "choices": [
            {
              "title": "Red",
              "value": "1"
            },
            {
              "title": "Green",
              "value": "2"
            },
            {
              "title": "Blue",
              "value": "3"
            }
          ]
        },
        {
          "type": "TextBlock",
          "text": "What colors do you want? *(isMultiSelect:true, style:compact)*"
        },
        {
          "type": "Input.ChoiceSet",
          "id": "myColor3",
          "isMultiSelect": true,
          "value": "1,3",
          "style": "compact",
          "choices": [
            {
              "title": "Red",
              "value": "1"
            },
            {
              "title": "Green",
              "value": "2"
            },
            {
              "title": "Blue",
              "value": "3"
            }
          ]
        },
        {
          "type": "TextBlock",
          "text": "What colors do you want? *(isMultiSelect:true, style:expanded)*"
        },
        {
          "type": "Input.ChoiceSet",
          "id": "myColor4",
          "isMultiSelect": true,
          "value": "1",
          "style": "expanded",
          "choices": [
            {
              "title": "Red",
              "value": "1"
            },
            {
              "title": "Green",
              "value": "2"
            },
            {
              "title": "Blue",
              "value": "3"
            }
          ]
        }
      ],
      "actions": [
        {
          "type": "Action.Submit",
          "title": "OK"
        }
      ]
    })";

    const std::string card_FactSet = R"({
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.0",
      "body": [
        {
          "type": "FactSet",
          "facts": [
            {
              "title": "Fact 1",
              "value": "Value 1"
            },
            {
              "title": "Fact 2",
              "value": "Value 2"
            },
            {
              "title": "Fact 3",
              "value": "Value 3"
            },
            {
              "title": "Fact 4",
              "value": "Value 5"
            }
          ]
        }
      ]
    })";

    const std::string card_Image = R"({
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.0",
      "body": [
	    {
          "type": "TextBlock",
          "text": "size: small, alignment: right with background-color set"
        },
	    {
          "type": "Image",
          "url": "https://adaptivecards.io/content/cats/1.png",
          "size": "Small",
          "horizontalAlignment": "Right",
	      "backgroundColor": "#FF0000FF"
        },
	    {
          "type": "TextBlock",
          "text": "size: medium, alignment: center"
        },
	    {
          "type": "Image",
          "url": "https://adaptivecards.io/content/cats/1.png",
          "id": "img1",
          "size": "Medium",
          "horizontalAlignment": "Center"
        },
        {
          "type": "TextBlock",
          "text": "size: large, style: person, alignment: left with background-color set"
        },
	    {
          "type": "Image",
          "url": "https://adaptivecards.io/content/cats/1.png",
          "id": "img2",
          "size": "Large",
          "style": "person",
          "horizontalAlignment": "Left",
          "backgroundColor": "#FF0000FF"
        },
	    {
          "type": "TextBlock",
          "text": "height,width and background-color are set"
        },
	    {
          "type": "Image",
          "url": "https://adaptivecards.io/content/cats/1.png",
          "id": "img3",
	      "backgroundColor": "#FF0000FF",
          "height": "200px",
	      "width": "300px"
        },
	    {
          "type": "TextBlock",
          "text": "height and background-color set"
        },
	    {
          "type": "Image",
          "url": "https://adaptivecards.io/content/cats/1.png",
          "id": "img4",
	      "backgroundColor": "#FF0000FF",
	      "height": "80px"
       }
      ]
    })";

	const std::string card_Container = R"({
	"$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
	"type": "AdaptiveCard",
	"version": "1.0",
	"body": [
    {
      "type": "Container",
      "items": [
        {
          "type": "TextBlock",
          "text": "This is some text"
        },
        {
          "type": "Image",
	      "id": "image1",
          "url": "https://adaptivecards.io/content/cats/1.png"
        }
      ]
    },
	{
      "type": "Container",
      "style": "accent",
      "items": [
        {
          "type": "Container",
          "style": "emphasis",
          "items": [
            {
              "type": "TextBlock",
              "text": "Contained container - emphasis"
            }
          ]
        },
        {
          "type": "Container",
          "style": "default",
	      "bleed": true,
          "items": [
            {
              "type": "TextBlock",
              "text": "Contained container - default"
            }
          ]
        },
        {
          "type": "Container",
          "style": "good",
          "items": [
            {
              "type": "TextBlock",
              "text": "Contained container - good"
            }
          ]
        },
        {
          "type": "Container",
          "style": "warning",
	      "bleed": true,
          "items": [
            {
              "type": "TextBlock",
              "text": "Contained container - warning"
            }
          ]
        },
        {
          "type": "Container",
          "style": "attention",
          "items": [
            {
              "type": "TextBlock",
              "text": "Contained container - attention"
            }
          ]
        },
        {
          "type": "Container",
          "style": "accent",
		  "bleed": true,
          "items": [
            {
              "type": "TextBlock",
              "text": "Contained container - accent"
            }
          ]
        }
      ]
    },
	{
      "type": "TextBlock",
      "text": "I'm a regular TextBlock..."
    },
    {
      "type": "Container",
      "minHeight": "400px",
      "verticalContentAlignment": "center",
      "items": [
        {
          "type": "TextBlock",
          "text": "But I'm centered..."
        },
        {
          "type": "Container",
          "style": "accent",
          "verticalContentAlignment": "center",
          "items": [
            {
              "type": "TextBlock",
              "text": "But I'm centered..."
            }
          ]
        }
      ]
    },
    {
      "type": "Container",
      "verticalContentAlignment": "bottom",
      "items": [
        {
          "type": "TextBlock",
          "text": "And I'm like a footer!"
        }
      ]
    },
	{
	  "type": "Container",
	  "minHeight": "150px",
	  "backgroundImage": "https://adaptivecards.io/content/AlkiBeach.jpg",
	  "items": [
		{
		  "type": "TextBlock",
		  "text": "What a beautiful background"
		}
		]
	  }
	  ]
  })";

	const std::string card_timeInput = R"({
	  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
	  "type": "AdaptiveCard",
	  "version": "1.0",
	  "body": [
		{
		  "type": "TextBlock",
		  "text": "What time do you want to meet?"
		},
		{
		  "type": "Input.Time",
		  "id": "time1",
		  "min": "09:00",
		  "max": "17:00",
		  "value": "15:30"
		},
		{
		  "type": "Input.Time",
		  "id": "time2",
		  "min": "09:00",
		  "max": "17:00",
		  "value": "25:30"
		}
	   ]
	})";

	const std::string card_ImageSet = R"({
	  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.0",
      "body": [
        {
          "type": "ImageSet",
          "imageSize": "Small",
          "images": [
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ]
        }
      ]
	})";
}
