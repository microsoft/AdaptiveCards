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
          "weight": "bolder",
		  "spacing":"large",
		  "seperator":true
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
		    "text": "Sample Card with InputDate"
		},
		{
		    "type": "Input.Date",
		    "id": "date1",
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
	],
      "actions": [
        {
          "type": "Action.Submit",
          "title": "OK"
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
              "title": "TEXT FOR FACTSET TESTING",
              "value": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
            },
            {
              "title": "Fact 3",
              "value": "Value 3"
            },
            {
              "title": "Fact 4",
              "value": "Value 4"
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
	   ],
      "actions": [
        {
          "type": "Action.Submit",
          "title": "OK"
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

	const std::string card_Separator = R"({
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.0",
      "body": [
	    {
          "type": "TextBlock",
          "text": "Demo for Spacing and Separator",
          "size": "Large"
        },
        {
          "type": "Image",
          "url": "https://adaptivecards.io/content/cats/1.png",
          "id": "img4",
	      "backgroundColor": "#FF0000FF",
	      "height": "80px",
          "spacing": "small",
          "separator":true
        },
        {
           "type":"TextBlock",
           "text":"Spacing:Small, Separator:true"
        },
        {
          "type": "Input.Date",
          "id": "defaultDateid",
          "text": "Spacing: None",
          "wrap": true,
          "separator": false,
          "spacing": "default"
        },
        {
           "type":"TextBlock",
           "text":"Spacing:default, Separator:false"
        },
        {
          "type": "Input.Time",
          "id": "defaulttimeid",
          "wrap": true,
          "separator": true,
          "spacing": "none"
        },
        {
           "type":"TextBlock",
           "text":"Spacing:None, Separator:true"
        },
        {
          "type": "FactSet",
          "spacing":"large",
          "separator":true,
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
        },
        {
           "type":"TextBlock",
           "text":"Spacing:Large, Separator:true"
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
          ],
          "spacing": "extraLarge",
          "separator": true
        },
        {
           "type":"TextBlock",
           "text":"Spacing:extraLarge, Separator:true"
        },
        {
          "type": "Input.Toggle",
          "id": "acceptTerms",
          "title": "I accept the terms and agreements",
          "value": "true",
          "valueOn": "true",
          "valueOff": "false",
          "spacing": "padding",
          "separator": true 
        },
        {
           "type":"TextBlock",
           "text":"Spacing:padding, Separator:true"
        },
        {
          "type": "Input.Text",
          "id": "defaultInputId",
          "placeholder": "enter comment",
          "maxLength": 500,
          "spacing": "extraLarge",
          "separator":false
       },
       {
           "type":"TextBlock",
           "text":"Spacing:extraLarge, Separator:false"
        },
       {
          "type": "Input.Number",
          "id": "defaultNumberId",
          "placeholder": "enter comment",
          "value": 0,
          "spacing": "none",
          "separator":false
       },
       {
           "type":"TextBlock",
           "text":"Spacing:none, Separator:false"
       }
      ]
    })";

	const std::string card_columnSet = R"({
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
  "type": "AdaptiveCard",
  "version": "1.0",
  "body": [
    {
      "type": "TextBlock",
      "text": "Simple ColumnSet"
    },
    {
      "type": "ColumnSet",
      "columns": [
        {
          "type": "Column",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 1"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ],
          "width": "auto"
        },
        {
          "type": "Column",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 2"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ],
          "width": "auto"
        },
        {
          "type": "Column",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 3"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ],
          "width": "auto"
        }
      ]
    },
    {
      "type": "TextBlock",
      "text": "ColumnSet with bleed property"
    },
    {
      "type": "ColumnSet",
      "style": "good",
      "bleed": true,
      "columns": [
        {
          "type": "Column",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 1"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ],
          "style": "default",
          "width": "auto",
          "bleed": true
        },
        {
          "type": "Column",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 2"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ],
          "width": "auto"
        },
        {
          "type": "Column",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 3"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ],
          "width": "auto",
          "style": "attention",
          "bleed": true
        }
      ]
    },
    {
      "type": "TextBlock",
      "text": "MinHeight"
    },
    {
      "type": "ColumnSet",
      "style": "good",
      "bleed": true,
      "minHeight": "300px",
      "columns": [
        {
          "type": "Column",
          "items": [
            {
              "type": "TextBlock",
              "text": "Aligned Top"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ],
          "style": "default",
          "width": "auto"
        },
        {
          "type": "Column",
          "verticalContentAlignment": "Center",
          "items": [
            {
              "type": "TextBlock",
              "text": "Aligned Center"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ],
          "width": "auto",
          "style": "warning"
        },
        {
          "type": "Column",
          "verticalContentAlignment": "Bottom",
          "items": [
            {
              "type": "TextBlock",
              "text": "Aligned Bottom"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ],
          "width": "auto",
          "style": "accent"
        }
      ]
    },
    {
      "type": "TextBlock",
      "text": "BackGround Image"
    },
    {
      "type": "ColumnSet",
      "columns": [
        {
          "type": "Column",
          "minHeight": "50px",
          "backgroundImage": "https://adaptivecards.io/content/AlkiBeach.jpg",
          "width": "auto",
          "items": [
            {
              "type": "TextBlock",
              "text": "Background Image"
            }
          ]
        }
      ]
    },
    {
      "type": "TextBlock",
      "text": "Bleed left"
    },
    {
      "type": "ColumnSet",
      "style": "emphasis",
      "columns": [
        {
          "type": "Column",
          "style": "good",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 1"
            }
          ],
          "bleed": true,
          "width": "stretch"
        },
        {
          "type": "Column",
          "style": "attention",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 2"
            }
          ],
          "width": "stretch"
        },
        {
          "type": "Column",
          "style": "warning",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 3"
            }
          ],
          "width": "stretch"
        }
      ]
    },
    {
      "type": "TextBlock",
      "text": "Bleed center"
    },
    {
      "type": "ColumnSet",
      "style": "emphasis",
      "columns": [
        {
          "type": "Column",
          "style": "good",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 1"
            }
          ],
          "width": "stretch"
        },
        {
          "type": "Column",
          "style": "attention",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 2"
            }
          ],
          "bleed": true,
          "width": "stretch"
        },
        {
          "type": "Column",
          "style": "warning",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 3"
            }
          ],
          "width": "stretch"
        }
      ]
    },
    {
      "type": "TextBlock",
      "text": "Bleed right"
    },
    {
      "type": "ColumnSet",
      "style": "emphasis",
      "columns": [
        {
          "type": "Column",
          "style": "good",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 1"
            }
          ],
          "width": "stretch"
        },
        {
          "type": "Column",
          "style": "attention",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 2"
            }
          ],
          "width": "stretch"
        },
        {
          "type": "Column",
          "style": "warning",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 3"
            }
          ],
          "bleed": true,
          "width": "stretch"
        }
      ]
    },
    {
      "type": "TextBlock",
      "text": "Bleed all"
    },
    {
      "type": "ColumnSet",
      "style": "emphasis",
      "columns": [
        {
          "type": "Column",
          "style": "good",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 1"
            }
          ],
          "bleed": true,
          "width": "stretch"
        },
        {
          "type": "Column",
          "style": "attention",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 2"
            }
          ],
          "bleed": true,
          "width": "stretch"
        },
        {
          "type": "Column",
          "style": "warning",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 3"
            }
          ],
          "bleed": true,
          "width": "stretch"
        }
      ]
    },
    {
      "type": "TextBlock",
      "text": "Columns With Seperator"
    },
    {
      "type": "ColumnSet",
      "columns": [
        {
          "type": "Column",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 1"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ],
          "spacing": "ExtraLarge",
          "width": "auto",
          "separator": true
        },
        {
          "type": "Column",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 2 Large Spacing"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ],
          "width": "auto",
          "spacing": "ExtraLarge",
          "separator": true
        },
        {
          "type": "Column",
          "items": [
            {
              "type": "TextBlock",
              "text": "Column 3 Small Spacing"
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/cats/1.png"
            }
          ],
          "width": "auto",
          "spacing": "small",
          "separator": true
        }
      ]
    },
	{
      "type": "TextBlock",
      "text": "Weighted Width"
    },
    {
      "type": "ColumnSet",
      "style": "emphasis",
      "columns": [
        {
          "type": "Column",
          "width": 30,
          "items": [
            {
              "type": "TextBlock",
              "text": "WeightedWidth:30%"
            }
          ]
        },
        {
          "type": "Column",
          "width": 70,
          "items": [
            {
              "type": "TextBlock",
              "text": "WeightedWidth:70%"
            }
          ]
        }
      ]
    }
  ]
})";

    const std::string card_Action_OpenUrl = R"({
        "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
        "type": "AdaptiveCard",
        "version": "1.0",
        "body": [
        {
            "type": "TextBlock",
            "text": "This card's action will open a URL"
        }
        ],
        "actions": [
            {
                "type": "Action.OpenUrl",
                "title": "Action.OpenUrl",
                "url": "https://adaptivecards.io"
            },
            {
                "type": "Action.OpenUrl",
                "title": "Action.OpenUrl.icon",
                "url": "https://adaptivecards.io",
                "iconUrl": "https://adaptivecards.io/content/cats/1.png"
            },
            {
                "type": "Action.OpenUrl",
                "title": "Action.OpenUrl",
                "url": "https://adaptivecards.io",
                "style": "destructive"
            },
            {
                "type": "Action.OpenUrl",
                "title": "Action.OpenUrl.icon",
                "url": "https://adaptivecards.io",
                "iconUrl": "https://adaptivecards.io/content/cats/1.png",
                "style": "positive"
            }
        ]
    })";

    const std::string card_Action_Submit = R"({
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.0",
      "body": [
        {
          "type": "TextBlock",
          "text": "Present a form and submit it back to the originator"
        },
        {
          "type": "Input.Text",
          "id": "firstName",
          "placeholder": "What is your first name?"
        },
        {
          "type": "Input.Text",
          "id": "lastName",
          "placeholder": "What is your last name?"
        }
      ],
      "actions": [
        {
          "type": "Action.Submit",
          "title": "Action.Submit",
          "data": {
            "x": 13
          }
        }
      ]
    })";
  
	const std::string card_ActionSet = R"({
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.0",
      "body": [
        {
          "type": "TextBlock",
          "wrap": true,
          "text": "Cards can have action sets in the middle of their body."
        },
        {
          "type": "ActionSet",
          "actions": [
            {
              "type": "Action.ShowCard",
              "title": "ShowCard",
              "card": {
                "type": "AdaptiveCard",
                "body": [
                  {
                    "type": "TextBlock",
                    "text": "This is a show card"
                  }
                ]
              }
            },
            {
              "type": "Action.OpenUrl",
              "title": "OpenUrl",
              "url": "https://adaptivecards.io"
            }
          ]
        },
        {
          "type": "TextBlock",
          "wrap": true,
          "text": "There are also still actions at the bottom of the card"
        }
      ],
      "actions": [
        {
          "type": "Action.ShowCard",
          "title": "ShowCard",
          "card": {
            "type": "AdaptiveCard",
            "body": [
              {
                "type": "TextBlock",
                "text": "This is a show card"
              }
            ]
          }
        },
        {
          "type": "Action.OpenUrl",
          "title": "OpenUrl",
          "url": "https://adaptivecards.io"
		}
      ]
    })";

	const std::string card_Action_ShowCard_1 = R"({
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
  "type": "AdaptiveCard",
  "version": "1.0",
  "body": [
    {
      "type": "TextBlock",
      "text": "This card's action will show another card"
    }
  ],
  "actions": [
    {
      "type": "Action.ShowCard",
      "title": "Action.ShowCard",
      "card": {
        "type": "AdaptiveCard",
        "body": [
          {
            "type": "TextBlock",
            "text": "What do you think?"
          }
        ],
        "actions": [
          {
            "type": "Action.Submit",
            "title": "Neat!"
          }
        ]
      }
    }
  ]
}
)";

    const std::string card_Action_ShowCard_2 = R"({
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
    },
        {
      "type": "TextBlock",
      "text": "Your registration is almost complete",
      "size": "medium",
      "weight": "bolder",
      "wrap": true
    },
    {
      "type": "Container",
      "items": [
        {
          "type": "ActionSet",
          "actions": [
            {
              "type": "Action.Submit",
              "title": "Approve",
              "style": "positive",
              "data": {
                "id": "_qkQW8dJlUeLVi7ZMEzYVw",
                "action": "approve"
              }
            },
            {
              "type": "Action.ShowCard",
              "title": "Reject",
              "style": "destructive",
              "card": {
                "type": "AdaptiveCard",
                "body": [
                  {
                    "type": "Input.Text",
                    "id": "RejectCommentID",
                    "placeholder": "Please specify an appropriate reason for rejection.",
                    "isMultiline": true
                  }
                ],
                "actions": [
                  {
                    "type": "Action.Submit",
                    "title": "Send",
                    "data": {
                      "id": "_qkQW8dJlUeLVi7ZMEzYVw",
                      "action": "reject"
                    }
                  }
                ]
              }
            }
          ]
        }
      ]
    },
    {
      "type": "TextBlock",
      "text": "What type of food do you prefer?",
      "wrap": true
    },
    {
      "type": "ImageSet",
      "imageSize": "medium",
      "images": [
        {
          "type": "Image",
          "url": "https://contososcubademo.azurewebsites.net/assets/steak.jpg",
          "altText": "Steak cut with fries"
        },
        {
          "type": "Image",
          "url": "https://contososcubademo.azurewebsites.net/assets/chicken.jpg",
          "altText": "Fried chicken with lettuce"
        },
        {
          "type": "Image",
          "url": "https://contososcubademo.azurewebsites.net/assets/tofu.jpg",
          "altText": "Tofu topped with red sauce"
        }
      ]
    }
  ],
  "actions": [
    {
      "type": "Action.ShowCard",
      "title": "Steak",
      "card": {
        "type": "AdaptiveCard",
        "body": [
          {
            "type": "TextBlock",
            "text": "How would you like your steak prepared?",
            "size": "medium",
            "wrap": true
          },
          {
            "type": "Input.ChoiceSet",
            "id": "SteakTemp",
            "style": "expanded",
            "choices": [
              {
                "title": "Rare",
                "value": "rare"
              },
              {
                "title": "Medium-Rare",
                "value": "medium-rare"
              },
              {
                "title": "Well-done",
                "value": "well-done"
              }
            ]
          },
          {
            "type": "Input.Text",
            "id": "SteakOther",
            "isMultiline": true,
            "placeholder": "Any other preparation requests?"
          }
        ],
        "actions": [
          {
            "type": "Action.Submit",
            "title": "OK",
            "data": {
              "FoodChoice": "Steak"
            }
          }
        ]
      }
    },
    {
      "type": "Action.ShowCard",
      "title": "Chicken",
      "card": {
        "type": "AdaptiveCard",
        "body": [
          {
            "type": "TextBlock",
            "text": "Do you have any allergies?",
            "size": "medium",
            "wrap": true
          },
          {
            "type": "Input.ChoiceSet",
            "id": "ChickenAllergy",
            "style": "expanded",
            "isMultiSelect": true,
            "choices": [
              {
                "title": "I'm allergic to peanuts",
                "value": "peanut"
              }
            ]
          },
          {
            "type": "Input.Text",
            "id": "ChickenOther",
            "isMultiline": true,
            "placeholder": "Any other preparation requests?"
          }
        ],
        "actions": [
          {
            "type": "Action.Submit",
            "title": "OK",
            "data": {
              "FoodChoice": "Chicken"
            }
          }
        ]
      }
    },
    {
      "type": "Action.ShowCard",
      "title": "Tofu",
      "card": {
        "type": "AdaptiveCard",
        "body": [
          {
            "type": "TextBlock",
            "text": "Would you like it prepared vegan?",
            "size": "medium",
            "wrap": true
          },
          {
            "type": "Input.Toggle",
            "id": "Vegetarian",
            "title": "Please prepare it vegan",
            "valueOn": "vegan",
            "valueOff": "notVegan"
          },
          {
            "type": "Input.Text",
            "id": "VegOther",
            "isMultiline": true,
            "placeholder": "Any other preparation requests?"
          }
        ],
        "actions": [
          {
            "type": "Action.Submit",
            "title": "OK",
            "data": {
              "FoodChoice": "Vegetarian"
            }
          }
        ]
      }
    }
  ]
})";

	const std::string card_Action_Inline = R"({
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "type": "AdaptiveCard",
      "version": "1.2",
      "body": [
        {
          "type": "TextBlock",
          "text": "Text input with an inline action"
        },
        {
          "type": "Input.Text",
          "id": "iconInlineActionId",
          "inlineAction": {
            "type": "Action.Submit",
            "iconUrl": "https://adaptivecards.io/content/send.png",
            "title": "Send"
          }
        },
        {
          "type": "TextBlock",
          "text": "Text input with an inline action with no icon",
          "wrap": true
        },
        {
          "type": "Input.Text",
          "id": "textInlineActionId",
          "inlineAction": {
            "type": "Action.OpenUrl",
            "title": "Reply",
            "url": "https://adaptivecards.io"
          }
        },
        {
          "type": "TextBlock",
          "text": "Multiline text input with an inline action"
        },
        {
          "type": "Input.Text",
          "id": "multilineInputId",
          "inlineAction": {
            "type": "Action.Submit",
            "iconUrl": "https://adaptivecards.io/content/send.png",
            "title": "Send"
          },
          "placeholder": "enter comment",
          "maxLength": 500,
          "isMultiline": true
        }
      ]
    })";

	const std::string card_Action_ToggleVisibility = R"({
	  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
	  "type": "AdaptiveCard",
	  "version": "1.2",
	  "body": [
		{
		  "type": "TextBlock",
		  "text": "Press the buttons to toggle the images!",
		  "wrap": true
		},
		{
		  "type": "TextBlock",
		  "text": "Here are some images:",
		  "isVisible": false,
		  "id": "textToToggle"
		},
		{
		  "type": "ColumnSet",
		  "columns": [
			{
			  "type": "Column",
			  "items": [
				{
				  "style": "person",
				  "type": "Image",
				  "url": "https://adaptivecards.io/content/cats/1.png",
				  "isVisible": false,
				  "id": "imageToToggle",
				  "altText": "sample image 1",
				  "size": "medium"
				}
			  ],
			  "width":"auto"
			},
			{
			  "type": "Column",
			  "items": [

				{
				  "type": "Image",
				  "url": "https://adaptivecards.io/content/cats/1.png",
				  "isVisible": false,
				  "id": "imageToToggle2",
				  "altText": "sample image 2",
				  "size": "medium"
				}
			  ],
			  "width":"auto"
			}
		  ]
		}
	  ],
	  "actions": [
		{
		  "type": "Action.ToggleVisibility",
		  "title": "Toggle!",
		  "targetElements": [ "textToToggle", "imageToToggle", "imageToToggle2" ]
		},
		{
		  "type": "Action.ToggleVisibility",
		  "title": "Also Toggle!",
		  "targetElements": [
			{
			  "elementId": "textToToggle"
			},
			{
			  "elementId": "imageToToggle"
			},
			{
			  "elementId": "imageToToggle2"
			}
		  ]
		},
		{
		  "type": "Action.ToggleVisibility",
		  "title": "Show!",
		  "targetElements": [
			{
			  "elementId": "textToToggle",
			  "isVisible": true
			},
			{
			  "elementId": "imageToToggle",
			  "isVisible": true
			},
			{
			  "elementId": "imageToToggle2",
			  "isVisible": true
			}
		  ]
		},
		{
		  "type": "Action.ToggleVisibility",
		  "title": "Hide!",
		  "targetElements": [
			{
			  "elementId": "textToToggle",
			  "isVisible": false
			},
			{
			  "elementId": "imageToToggle",
			  "isVisible": false
			},
			{
			  "elementId": "imageToToggle2",
			  "isVisible": false
			}
		  ]
		},
		{
		  "type": "Action.ToggleVisibility",
		  "title": "Cat 1",
		  "targetElements": [
			{
			  "elementId": "textToToggle",
			  "isVisible": true
			},
			{
			  "elementId": "imageToToggle",
			  "isVisible": true
			},
			{
			  "elementId": "imageToToggle2",
			  "isVisible": false
			}
		  ]
		},
		{
		  "type": "Action.ToggleVisibility",
		  "title": "Water!",
		  "targetElements": [
			{
			  "elementId": "textToToggle",
			  "isVisible": true
			},
			{
			  "elementId": "imageToToggle",
			  "isVisible": false
			},
			{
			  "elementId": "imageToToggle2",
			  "isVisible": true
			}
		  ]
		}
	  ]
	})";

	const std::string card_flight = R"(
	{
  "$schema":"http://adaptivecards.io/schemas/adaptive-card.json",
  "version":"1.0",
  "type":"AdaptiveCard",
  "speak":"Your flight is confirmed for you and 3 other passengers from San Francisco to Amsterdam on Friday, October 10 8:30 AM",
  "body":[
    {
      "type":"TextBlock",
      "text":"Passengers",
      "weight":"Bolder",
      "isSubtle":false,
      "wrap":true
    },
    {
      "type":"TextBlock",
      "text":"Sarah Hum",
      "separator":true,
      "wrap":true
    },
    {
      "type":"TextBlock",
      "text":"Jeremy Goldberg",
      "spacing":"None",
      "wrap":true
    },
    {
      "type":"TextBlock",
      "text":"Evan Litvak",
      "spacing":"None",
      "wrap":true
    },
    {
      "type":"TextBlock",
      "text":"2 Stops",
      "weight":"Bolder",
      "spacing":"Medium",
      "wrap":true
    },
    {
      "type":"TextBlock",
      "text":"Tue, May 30, 2017 12:25 PM",
      "weight":"Bolder",
      "spacing":"None",
      "wrap":true
    },
    {
      "type":"ColumnSet",
      "separator":true,
      "columns":[
        {
          "type":"Column",
          "width":1,
          "items":[
            {
              "type":"TextBlock",
              "text":"San Francisco",
              "isSubtle":true,
              "wrap":true
            }
          ]
        },
        {
          "type":"Column",
          "width":1,
          "items":[
            {
              "type":"TextBlock",
              "horizontalAlignment":"Right",
              "text":"Amsterdam",
              "isSubtle":true,
              "wrap":true
            }
          ]
        }
      ]
    },
    {
      "type":"ColumnSet",
      "spacing":"None",
      "columns":[
        {
          "type":"Column",
          "width":1,
          "items":[
            {
              "type":"TextBlock",
              "size":"ExtraLarge",
              "color":"Accent",
              "text":"SFO",
              "spacing":"None",
              "wrap":true
            }
          ]
        },
        {
          "type":"Column",
          "width":"auto",
          "items":[
            {
              "type":"Image",
              "url":"https://adaptivecards.io/content/airplane.png",
              "size":"Small",
              "spacing":"None",
              "altText":"Flight to"
            }
          ]
        },
        {
          "type":"Column",
          "width":1,
          "items":[
            {
              "type":"TextBlock",
              "horizontalAlignment":"Right",
              "size":"ExtraLarge",
              "color":"Accent",
              "text":"AMS",
              "spacing":"None",
              "wrap":true
            }
          ]
        }
      ]
    },
    {
      "type":"TextBlock",
      "text":"Non-Stop",
      "weight":"Bolder",
      "spacing":"Medium",
      "wrap":true
    },
    {
      "type":"TextBlock",
      "text":"Fri, Jun 2, 2017 1:55 PM",
      "weight":"Bolder",
      "spacing":"None",
      "wrap":true
    },
    {
      "type":"ColumnSet",
      "separator":true,
      "columns":[
        {
          "type":"Column",
          "width":1,
          "items":[
            {
              "type":"TextBlock",
              "text":"Amsterdam",
              "isSubtle":true,
              "wrap":true
            }
          ]
        },
        {
          "type":"Column",
          "width":1,
          "items":[
            {
              "type":"TextBlock",
              "horizontalAlignment":"Right",
              "text":"San Francisco",
              "isSubtle":true,
              "wrap":true
            }
          ]
        }
      ]
    },
    {
      "type":"ColumnSet",
      "spacing":"None",
      "columns":[
        {
          "type":"Column",
          "width":1,
          "items":[
            {
              "type":"TextBlock",
              "size":"ExtraLarge",
              "color":"Accent",
              "text":"AMS",
              "spacing":"None",
              "wrap":true
            }
          ]
        },
        {
          "type":"Column",
          "width":"auto",
          "items":[
            {
              "type":"Image",
              "url":"https://adaptivecards.io/content/airplane.png",
              "size":"Small",
              "spacing":"None",
              "altText":"Flight to"
            }
          ]
        },
        {
          "type":"Column",
          "width":1,
          "items":[
            {
              "type":"TextBlock",
              "horizontalAlignment":"Right",
              "size":"ExtraLarge",
              "color":"Accent",
              "text":"SFO",
              "spacing":"None",
              "wrap":true
            }
          ]
        }
      ]
    },
    {
      "type":"ColumnSet",
      "spacing":"Medium",
      "columns":[
        {
          "type":"Column",
          "width":"1",
          "items":[
            {
              "type":"TextBlock",
              "text":"Total",
              "size":"Medium",
              "isSubtle":true,
              "wrap":true
            }
          ]
        },
        {
          "type":"Column",
          "width":1,
          "items":[
            {
              "type":"TextBlock",
              "horizontalAlignment":"Right",
              "text":"$4,032.54",
              "size":"Medium",
              "weight":"Bolder",
              "wrap":true
             }
           ]
         }
       ]
      }
	 ]
    }
	)";

	const std::string card_weather = R"(
		{
  "$schema":"http://adaptivecards.io/schemas/adaptive-card.json",
  "type":"AdaptiveCard",
  "version":"1.0",
  "speak":"Weather forecast for Monday is high of 62 and low of 42 degrees with a 20% chance of rainWinds will be 5 mph from the northeast",
  "backgroundImage":"https://messagecardplayground.azurewebsites.net/assets/Mostly%20Cloudy-Background.jpg",
  "body":[
    {
      "type":"ColumnSet",
      "columns":[
        {
          "type":"Column",
          "width":"35",
          "items":[
            {
              "type":"Image",
              "url":"https://messagecardplayground.azurewebsites.net/assets/Mostly%20Cloudy-Square.png",
              "size":"stretch",
              "altText":"Mostly cloudy weather"
            }
          ]
        },
        {
          "type":"Column",
          "width":"65",
          "items":[
            {
              "type":"TextBlock",
              "text":"Tue, Nov 5, 2019",
              "weight":"bolder",
              "size":"large",
              "wrap":true
            },
            {
              "type":"TextBlock",
              "text":"32 / 50",
              "size":"medium",
              "spacing":"none",
              "wrap":true
            },
            {
              "type":"TextBlock",
              "text":"31% chance of rain",
              "spacing":"none",
              "wrap":true
            },
            {
              "type":"TextBlock",
              "text":"Winds 4.4 mph SSE",
              "spacing":"none",
              "wrap":true
            }
          ]
        }
      ]
    },
    {
      "type":"ColumnSet",
      "columns":[
        {
          "type":"Column",
          "width":"20",
          "items":[
            {
              "type":"TextBlock",
              "horizontalAlignment":"center",
              "wrap":false,
              "text":"Wednesday"
            },
            {
              "type":"Image",
              "size":"auto",
              "url":"https://messagecardplayground.azurewebsites.net/assets/Drizzle-Square.png",
              "altText":"Drizzly weather"
            },
            {
              "type":"FactSet",
              "horizontalAlignment":"right",
              "facts":[
                {
                  "title":"High",
                  "value":"50"
                },
                {
                  "title":"Low",
                  "value":"32"
                }
              ]
            }
          ],
          "selectAction":{
            "type":"Action.OpenUrl",
            "title":"View Wednesday",
            "url":"https://www.microsoft.com"
          }
        },
        {
          "type":"Column",
          "width":"20",
          "items":[
            {
              "type":"TextBlock",
              "horizontalAlignment":"center",
              "wrap":false,
              "text":"Thursday"
            },
            {
              "type":"Image",
              "size":"auto",
              "url":"https://messagecardplayground.azurewebsites.net/assets/Mostly%20Cloudy-Square.png",
              "altText":"Mostly cloudy weather"
            },
            {
              "type":"FactSet",
              "facts":[
                {
                  "title":"High",
                  "value":"50"
                },
                {
                  "title":"Low",
                  "value":"32"
                }
              ]
            }
          ],
          "selectAction":{
            "type":"Action.OpenUrl",
            "title":"View Thursday",
            "url":"https://www.microsoft.com"
          }
        },
        {
          "type":"Column",
          "width":"20",
          "items":[
            {
              "type":"TextBlock",
              "horizontalAlignment":"center",
              "wrap":false,
              "text":"Friday"
            },
            {
              "type":"Image",
              "size":"auto",
              "url":"https://messagecardplayground.azurewebsites.net/assets/Mostly%20Cloudy-Square.png",
              "altText":"Mostly cloudy weather"
            },
            {
              "type":"FactSet",
              "facts":[
                {
                  "title":"High",
                  "value":"59"
                },
                {
                  "title":"Low",
                  "value":"32"
                }
              ]
            }
          ],
          "selectAction":{
            "type":"Action.OpenUrl",
            "title":"View Friday",
            "url":"https://www.microsoft.com"
          }
        },
        {
          "type":"Column",
          "width":"20",
          "items":[
            {
              "type":"TextBlock",
              "horizontalAlignment":"center",
              "wrap":false,
              "text":"Saturday"
            },
            {
              "type":"Image",
              "size":"auto",
              "url":"https://messagecardplayground.azurewebsites.net/assets/Mostly%20Cloudy-Square.png",
              "altText":"Mostly cloudy weather"
            },
            {
              "type":"FactSet",
              "facts":[
                {
                  "title":"High",
                  "value":"50"
                },
                {
                  "title":"Low",
                  "value":"32"
                }
              ]
            }
          ],
          "selectAction":{
            "type":"Action.OpenUrl",
            "title":"View Saturday",
            "url":"https://www.microsoft.com"
          }
        }
      ]
    }
  ]
}
	)";

	const std::string card_FoodOrder = R"({
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
  "type": "AdaptiveCard",
  "version": "1.0",
  "body": [
    {
      "type": "TextBlock",
      "text": "Your registration is almost complete",
      "size": "medium",
      "weight": "bolder",
      "wrap": true
    },
    {
      "type": "TextBlock",
      "text": "What type of food do you prefer?",
      "wrap": true
    },
    {
      "type": "ImageSet",
      "imageSize": "medium",
      "images": [
        {
          "type": "Image",
          "url": "https://contososcubademo.azurewebsites.net/assets/steak.jpg",
          "altText": "Steak cut with fries"
        },
        {
          "type": "Image",
          "url": "https://contososcubademo.azurewebsites.net/assets/chicken.jpg",
          "altText": "Fried chicken with lettuce"
        },
        {
          "type": "Image",
          "url": "https://contososcubademo.azurewebsites.net/assets/tofu.jpg",
          "altText": "Tofu topped with red sauce"
        }
      ]
    }
  ],
  "actions": [
    {
      "type": "Action.ShowCard",
      "title": "Steak",
      "card": {
        "type": "AdaptiveCard",
        "body": [
          {
            "type": "TextBlock",
            "text": "How would you like your steak prepared?",
            "size": "medium",
            "wrap": true
          },
          {
            "type": "Input.ChoiceSet",
            "id": "SteakTemp",
            "style": "expanded",
            "choices": [
              {
                "title": "Rare",
                "value": "rare"
              },
              {
                "title": "Medium-Rare",
                "value": "medium-rare"
              },
              {
                "title": "Well-done",
                "value": "well-done"
              }
            ]
          },
          {
            "type": "Input.Text",
            "id": "SteakOther",
            "isMultiline": true,
            "placeholder": "Any other preparation requests?"
          }
        ],
        "actions": [
          {
            "type": "Action.Submit",
            "title": "OK",
            "data": {
              "FoodChoice": "Steak"
            }
          }
        ]
      }
    },
    {
      "type": "Action.ShowCard",
      "title": "Chicken",
      "card": {
        "type": "AdaptiveCard",
        "body": [
          {
            "type": "TextBlock",
            "text": "Do you have any allergies?",
            "size": "medium",
            "wrap": true
          },
          {
            "type": "Input.ChoiceSet",
            "id": "ChickenAllergy",
            "style": "expanded",
            "isMultiSelect": true,
            "choices": [
              {
                "title": "I'm allergic to peanuts",
                "value": "peanut"
              }
            ]
          },
          {
            "type": "Input.Text",
            "id": "ChickenOther",
            "isMultiline": true,
            "placeholder": "Any other preparation requests?"
          }
        ],
        "actions": [
          {
            "type": "Action.Submit",
            "title": "OK",
            "data": {
              "FoodChoice": "Chicken"
            }
          }
        ]
      }
    },
    {
      "type": "Action.ShowCard",
      "title": "Tofu",
      "card": {
        "type": "AdaptiveCard",
        "body": [
          {
            "type": "TextBlock",
            "text": "Would you like it prepared vegan?",
            "size": "medium",
            "wrap": true
          },
          {
            "type": "Input.Toggle",
            "id": "Vegetarian",
            "title": "Please prepare it vegan",
            "valueOn": "vegan",
            "valueOff": "notVegan"
          },
          {
            "type": "Input.Text",
            "id": "VegOther",
            "isMultiline": true,
            "placeholder": "Any other preparation requests?"
          }
        ],
        "actions": [
          {
            "type": "Action.Submit",
            "title": "OK",
            "data": {
              "FoodChoice": "Vegetarian"
            }
          }
        ]
      }
    }
  ]
})";

			  const std::string card_ShowCardWiz = R"({
  "type": "AdaptiveCard",
  "version": "1.0",
  "body": [
    {
      "type": "TextBlock",
      "text": "Please provide the following information:",
      "wrap": true
    }
  ],
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
  "actions": [
    {
      "type": "Action.ShowCard",
      "title": "1. Name",
      "card": {
        "type": "AdaptiveCard",
        "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
        "body": [
          {
            "type": "Container",
            "id": "nameProperties",
            "items": [
            {
                "type": "TextBlock",
                "text": "First Name",
                "wrap": true
            },
              {
                "type": "Input.Text",
                "label": "First Name",
                "id": "FirstName",
                "isRequired": true,
                "errorMessage": "First Name is required"
              },
            {
                "type": "TextBlock",
                "text": "Middle Name",
                "wrap": true
            },
              {
                "type": "Input.Text",
                "label": "Middle Name",
                "id": "MiddleName"
              },
            {
                "type": "TextBlock",
                "text": "Last Name",
                "wrap": true
            },
              {
                "type": "Input.Text",
                "label": "Last Name",
                "id": "LastName",
                "isRequired": true,
                "errorMessage": "Last Name is required"
              }
            ]
          }
        ],
        "actions": [
          {
            "type": "Action.ShowCard",
            "title": "2. Address",
            "card": {
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
              "body": [
                {
                  "type": "Container",
                  "id": "addressProperties",
                  "items": [
                    {
                        "type": "TextBlock",
                        "text": "Address line 1",
                        "wrap": true
                    },
                    {
                      "type": "Input.Text",
                      "label": "Address line 1",
                      "id": "AddressLine1"
                    },
                    {
                        "type": "TextBlock",
                        "text": "Address line 2",
                        "wrap": true
                    },
                    {
                      "type": "Input.Text",
                      "label": "Address line 2",
                      "id": "AddressLine2"
                    },
                    {
                      "type": "ColumnSet",
                      "columns": [
                        {
                          "type": "Column",
                          "width": "stretch",
                          "items": [
                            {
                                "type": "TextBlock",
                                "text": "City",
                                "wrap": true
                            },
                            {
                              "type": "Input.Text",
                              "label": "City",
                              "id": "City"
                            }
                          ]
                        },
                        {
                          "type": "Column",
                          "width": "stretch",
                          "items": [
                            {
                                "type": "TextBlock",
                                "text": "State",
                                "wrap": true
                            },
                            {
                              "type": "Input.Text",
                              "label": "State",
                              "id": "State1"
                            }
                          ]
                        },
                        {
                          "type": "Column",
                          "width": "stretch",
                          "items": [
                            {
                                "type": "TextBlock",
                                "text": "Zip",
                                "wrap": true
                            },
                            {
                              "type": "Input.Text",
                              "label": "Zip Code",
                              "id": "Zip"
                            }
                          ]
                        }
                      ]
                    }
                  ]
                }
              ],
              "actions": [
                {
                  "type": "Action.ShowCard",
                  "title": "3. Phone/Email",
                  "card": {
                    "type": "AdaptiveCard",
                    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                    "body": [
                    {
                        "type": "TextBlock",
                        "text": "Cell Number",
                        "wrap": true
                    },
                      {
                        "type": "Input.Text",
                        "label": "Cell Number",
                        "id": "CellPhone"
                      },
                    {
                        "type": "TextBlock",
                        "text": "Home Number",
                        "wrap": true
                    },
                      {
                        "type": "Input.Text",
                        "label": "Home Number",
                        "id": "HomePhone"
                      },
                    {
                        "type": "TextBlock",
                        "text": "Email Address",
                        "wrap": true
                    },
                      {
                        "type": "Input.Text",
                        "label": "Email Address",
                        "id": "Email"
                      }
                    ],
                    "actions": [
                      {
                        "type": "Action.Submit",
                        "title": "Submit"
                      }
                    ]
                  }
                }
              ]
            }
          }
        ]
      }
    }
  ]
})";

	const std::string card_BackgroundImage = R"({
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "TextBlock",
            "text": "TextBlock"
        },
        {
            "type": "TextBlock",
            "text": "TextBlock"
        },
        {
            "type": "TextBlock",
            "text": "TextBlock"
        },
        {
            "type": "Input.Text",
            "placeholder": "Placeholder text",
            "id": "textField1"
        },
        {
            "type": "Input.Text",
            "placeholder": "Placeholder text",
            "id": "textField2"
        }
    ],
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "backgroundImage": {
        "url": "https://adaptivecards.io/content/cats/1.png",
        "horizontalAlignment": "Left",
        "verticalAlignment": "Top",
        "fillMode": "Cover"
    }
    })";

	const std::string card_ToggleVisibilityWiz = R"({
    "type": "AdaptiveCard",
    "version": "1.2",
    "body": [
        {
            "type": "TextBlock",
            "text": "Press the buttons to toggle the Elements!",
            "wrap": true
        },
        {
            "type": "TextBlock",
            "text": "Text Block"
        },
        {
            "type": "TextBlock",
            "text": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
            "wrap": true,
            "id": "textblock"
        },
        {
            "type": "TextBlock",
            "text": "Rich Text Block"
        },
        {
            "type": "RichTextBlock",
            "id":"richtext",
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
                }
            ]
        },
        {
            "type": "TextBlock",
            "text": "Default Input Text"
        },
        {
            "type": "Input.Text",
            "id": "inputtext",
            "placeholder": "enter comment",
            "maxLength": 500
        },
        {
            "type": "TextBlock",
            "text": "Image Set"
        },
        {
            "type": "ImageSet",
            "imageSize": "Small",
            "id":"imageset",
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
                }
            ]
        }

    ],
    "actions": [
        {
            "type": "Action.ToggleVisibility",
            "title": "Text Block",
            "targetElements": [ "textblock"]
        },
        {
            "type": "Action.ToggleVisibility",
            "title": "Rich Text",
            "targetElements": [
                {
                    "elementId": "richtext"
                }
            ]
        },
        {
            "type": "Action.ToggleVisibility",
            "title": "Input Text",
            "targetElements": [
                {
                    "elementId": "inputtext"
                }
            ]
        },
        {
            "type": "Action.ToggleVisibility",
            "title": "Image Set",
            "targetElements": [
                {
                    "elementId": "imageset"
                }
            ]
        },
        {
            "type": "Action.ShowCard",
            "title": "Show More",
            "card": {
              "type": "AdaptiveCard",
              "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
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
                        "text": "Input Date"
                    },
                    {
                        "type": "Input.Date",
                        "id": "date1",
                        "placeholder": "Enter a date",
                        "value": "2017-10-12",
                        "min":"1900-01-01",
                        "max":"2030-01-01"
                    },
                    {
                        "type": "TextBlock",
                        "text": "Toggle Input"
                    },
                    {
                        "type": "Input.Toggle",
                        "id": "toggle",
                        "title": "I accept the terms and agreements",
                        "value": "true",
                        "valueOn": "true",
                        "valueOff": "false"
                    },
                    {
                              "type": "TextBlock",
                              "text": "Input ChoiceSet"
                    },
                    {
                        "type": "Input.ChoiceSet",
                        "id": "choiceset",
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
                    }
                ],
                "actions": [
                    {
                        "type": "Action.ToggleVisibility",
                        "title": "Input Number",
                        "targetElements": [ "number"]
                    },
                    {
                        "type": "Action.ToggleVisibility",
                        "title": "Input Date",
                        "targetElements": [
                            {
                                "elementId": "date1"
                            }
                        ]
                    },
                    {
                        "type": "Action.ToggleVisibility",
                        "title": "Input Toggle",
                        "targetElements": [
                            {
                                "elementId": "toggle"
                            }
                        ]
                    },
                    {
                        "type": "Action.ToggleVisibility",
                        "title": "Choiceset",
                        "targetElements": [
                            {
                                "elementId": "choiceset"
                            }
                        ]
                    },
                    {
                        "type": "Action.ShowCard",
                        "title": "Show More",
                        "card": {
                          "type": "AdaptiveCard",
                          "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                          "body": [
                                {
                                    "type": "TextBlock",
                                    "text": "Fact Set"
                                },
                                {
                                    "type": "FactSet",
                                    "id":"factset",
                                    "facts": [
                                        {
                                            "title": "Fact 1",
                                            "value": "Value 1"
                                        },
                                        {
                                            "title": "TEXT FOR FACTSET TESTING",
                                            "value": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
                                        },
                                        {
                                            "title": "Fact 3",
                                            "value": "Value 3"
                                        },
                                        {
                                            "title": "Fact 4",
                                            "value": "Value 4"
                                        }
                                    ]
                                },
                                {
                                    "type": "TextBlock",
                                    "text": "Container"
                                },
                                {
                                    "type": "Container",
                                    "style": "good",
                                    "id":"container",
                                    "items": [
                                        {
                                            "type": "TextBlock",
                                            "text": "Contained container - good"
                                        }
                                    ]
                                },
                                {
                                    "type": "TextBlock",
                                    "text": "Input Time"
                                },
                                {
                                    "type": "Input.Time",
                                    "id": "time1",
                                    "min": "09:00",
                                    "max": "17:00",
                                    "value": "15:30"
                                },
                                {
                                    "type": "TextBlock",
                                    "text": "Multiline Input Text"
                                },
                                {
                                    "type": "Input.Text",
                                    "id": "multilineinput",
                                    "placeholder": "enter comment",
                                    "maxLength": 50,
                                    "isMultiline": true
                                }

                            ],
                            "actions": [
                                {
                                    "type": "Action.ToggleVisibility",
                                    "title": "Fact Set",
                                    "targetElements": ["factset"]
                                },
                                {
                                    "type": "Action.ToggleVisibility",
                                    "title": "Container",
                                    "targetElements": [
                                        {
                                            "elementId": "container"
                                        }
                                    ]
                                },
                                {
                                    "type": "Action.ToggleVisibility",
                                    "title": "Input Time",
                                    "targetElements": [
                                        {
                                            "elementId": "time1"
                                        }
                                    ]
                                },
                                {
                                    "type": "Action.ToggleVisibility",
                                    "title": "Input Text Multiline  ",
                                    "targetElements": [
                                        {
                                            "elementId": "multilineinput"
                                        }
                                    ]
                                }
                            ]
                        }
                    }
                ]
            }
        }
    ]
})";

    const std::string card_CardSelectAction = R"({
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "type": "AdaptiveCard",
    "version": "1.2",
    "selectAction": {
        "type": "Action.Submit",
        "title": "Submit action",
        "data": {
            "info": "My submit action data"
        }
    },
    "body": [
        {
            "type": "Container",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "Publish Adaptive Card schema",
                    "weight": "Bolder",
                    "size": "Medium"
                },
                {
                    "type": "ColumnSet",
                    "columns": [
                        {
                            "type": "Column",
                            "width": "auto",
                            "items": [
                                {
                                    "type": "Image",
                                    "url": "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg",
                                    "size": "Small",
                                    "style": "Person"
                                }
                            ]
                        },
                        {
                            "type": "Column",
                            "width": "stretch",
                            "items": [
                                {
                                    "type": "TextBlock",
                                    "text": "Matt Hidinger",
                                    "weight": "Bolder",
                                    "wrap": true
                                },
                                {
                                    "type": "TextBlock",
                                    "spacing": "None",
                                    "text": "Created {{DATE(2017-02-14T06:08:39Z, SHORT)}}",
                                    "isSubtle": true,
                                    "wrap": true
                                }
                            ]
                        }
                    ]
                }
            ]
        },
        {
            "type": "Container",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub. The schema will be the starting point of our reference documentation.",
                    "wrap": true
                },
                {
                    "type": "FactSet",
                    "facts": [
                        {
                            "title": "Board:",
                            "value": "Adaptive Card"
                        },
                        {
                            "title": "List:",
                            "value": "Backlog"
                        },
                        {
                            "title": "Assigned to:",
                            "value": "Matt Hidinger"
                        },
                        {
                            "title": "Due date:",
                            "value": "Not set"
                        }
                    ]
                }
            ]
        },
        {
            "type": "TextBlock",
            "text": "What time do you want to meet?"
        },
        {
            "type": "Input.Time",
            "id": "time",
            "min": "09:00",
            "max": "17:00",
            "value": "15:30"
        }
    ],
    "actions": [
        {
            "type": "Action.ShowCard",
            "title": "Comment",
            "card": {
                "type": "AdaptiveCard",
                "body": [
                    {
                        "type": "Input.Text",
                        "id": "comment",
                        "isMultiline": true,
                        "placeholder": "Enter your comment"
                    }
                ],
                "actions": [
                    {
                        "type": "Action.Submit",
                        "title": "OK"
                    }
                ]
            }
        },
        {
            "type": "Action.OpenUrl",
            "title": "View",
            "url": "https://adaptivecards.io"
        }
    ]
})";

    const std::string card_ImageSelectAction = R"({
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "type": "AdaptiveCard",
    "version": "1.2",
    "body": [
        {
            "type": "Image",
            "url": "https://adaptivecards.io/content/cats/1.png",
            "selectAction": {
                "type": "Action.Submit",
                "title": "Submit action",
                "data": {
                    "info": "My submit action data"
                }
            }
        }
    ]
})";

    const std::string card_TextRunSelectAction = R"({
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
  "type": "AdaptiveCard",
  "version": "1.2",
  "body": [
    {
      "type": "TextBlock",
      "text": "What time do you want to meet?"
    },
    {
      "type": "Input.Time",
      "id": "time",
      "min": "09:00",
      "max": "17:00",
      "value": "15:30"
    },
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
          "text": " We support select action,",
          "color": "good",
          "selectAction": {
                "type": "Action.Submit",
                "title": "Submit action",
                "data": {
                    "info": "My submit action data"
                }
            }
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
          "fontType": "monospace",
          "selectAction": {
            "type": "Action.OpenUrl",
            "url": "https://msn.com"
          }
        }
      ]
    },
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
      "type": "TextBlock",
      "text": "Date Input"
    },
    {
      "type": "Input.Date",
      "id": "date",
      "placeholder": "Enter a date",
      "value": "2017-10-12"
    }
  ]
})";

    const std::string card_ContainerSelectAction = R"({
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "type": "AdaptiveCard",
    "version": "1.2",
    "body": [
        {
            "type": "Container",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "Cool link"
                }
            ],
            "selectAction": {
                "type": "Action.OpenUrl",
                "url": "https://www.youtube.com/watch?v=dQw4w9WgXcQ"
            }
        },
        {
            "type": "Container",
            "style": "emphasis",
            "backgroundImage": "https://adaptivecards.io/content/AlkiBeach.jpg",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "Emphasis link"
                }
            ],
            "selectAction": {
                "type": "Action.OpenUrl",
                "url": "https://msn.com"
            }
        },
        {
            "type": "Container",
            "style": "good",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "Submit action"
                }
            ],
            "selectAction": {
                "type": "Action.Submit",
                "title": "Submit action",
                "data": {
                    "info": "My submit action data"
                }
            }
        },
        {
            "type": "TextBlock",
            "text": "Date Input"
        },
        {
            "type": "Input.Date",
            "id": "date",
            "placeholder": "Enter a date",
            "value": "2017-10-12"
        }
    ]
})";

    const std::string card_ColumnSetSelectAction = R"({
    "type": "AdaptiveCard",
    "version": "1.2",
    "body": [
        {
            "type": "TextBlock",
            "text": "Pick up where you left off?",
            "weight": "Bolder"
        },
        {
            "type": "ColumnSet",
            "spacing": "Medium",
            "columns": [
                {
                    "type": "Column",
                    "width": "auto",
                    "items": [
                        {
                            "type": "Image",
                            "url": "https://unsplash.it/80?image=1083",
                            "size": "Medium"
                        }
                    ]
                },
                {
                    "type": "Column",
                    "width": 4,
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Silver Star Mountain"
                        },
                        {
                            "type": "TextBlock",
                            "text": "Maps",
                            "isSubtle": true,
                            "spacing": "None"
                        }
                    ]
                }
            ],
            "selectAction": {
                "type": "Action.OpenUrl",
                "url": "https://www.msn.com"
            }
        },
        {
            "type": "ColumnSet",
            "columns": [
                {
                    "type": "Column",
                    "width": "auto",
                    "items": [
                        {
                            "type": "Image",
                            "url": "https://unsplash.it/80?image=1082",
                            "size": "Medium"
                        }
                    ]
                },
                {
                    "type": "Column",
                    "width": 4,
                    "style": "emphasis",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Kitchen Remodel"
                        },
                        {
                            "type": "TextBlock",
                            "text": "With EMPHASIS",
                            "isSubtle": true,
                            "spacing": "None"
                        }
                    ]
                }
            ],
            "selectAction": {
                "type": "Action.OpenUrl",
                "url": "https://www.AdaptiveCards.io"
            }
        },
        {
            "type": "ColumnSet",
            "columns": [
                {
                    "type": "Column",
                    "width": "auto",
                    "items": [
                        {
                            "type": "Image",
                            "url": "https://unsplash.it/80?image=1080",
                            "size": "Medium"
                        }
                    ]
                },
                {
                    "type": "Column",
                    "width": 4,
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "The Witcher"
                        },
                        {
                            "type": "TextBlock",
                            "text": "Netflix",
                            "isSubtle": true,
                            "spacing": "None"
                        }
                    ],
                    "selectAction": {
                        "type": "Action.OpenUrl",
                        "url": "https://www.youtube.com/watch?v=dQw4w9WgXcQ"
                    }
                }
            ],
            "selectAction": {
                "type": "Action.OpenUrl",
                "url": "https://www.outlook.com"
            }
        }
    ],
    "actions": [
        {
            "type": "Action.OpenUrl",
            "title": "Resume all",
            "url": "ms-cortana:resume-all"
        },
        {
            "type": "Action.OpenUrl",
            "title": "More activities",
            "url": "ms-cortana:more-activities"
        }
    ],
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json"
})";

	const std::string card_Bleed = R"({
    "type": "AdaptiveCard",
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "version": "1.2",
    "body": [
        {
            "type": "TextBlock",
            "text": "Container Bleed",
            "wrap": true
        },
        {
            "type": "Container",
            "style": "warning",
            "items": [
                {
                    "type": "Container",
                    "style": "attention",
                    "bleed": true,
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Container with bleed",
                            "wrap": true
                        }
                    ]
                },
                {
                    "type": "Container",
                    "style": "attention",
  
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Container without bleed",
                            "wrap": true
                        }
                    ]
                }
            ]
        },
        {
            "type": "TextBlock",
            "text": "ColumnSet Bleed",
            "wrap": true
        },
        {
            "type": "TextBlock",
            "text": "Bleed left"
        },
        {
            "type": "ColumnSet",
            "style": "emphasis",
            "columns": [
                {
                    "type": "Column",
                    "style": "good",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Column 1"
                        }
                    ],
                    "bleed": true,
                    "width": "stretch"
                },
                {
                    "type": "Column",
                    "style": "attention",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Column 2"
                        }
                    ],
                    "width": "stretch"
                },
                {
                    "type": "Column",
                    "style": "warning",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Column 3"
                        }
                    ],
                    "width": "stretch"
                }
            ]
        },
        {
            "type": "TextBlock",
            "text": "Bleed center"
        },
        {
            "type": "ColumnSet",
            "style": "emphasis",
            "bleed": true,
            "columns": [
                {
                    "type": "Column",
                    "style": "good",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Column 1"
                        }
                    ],
                    "width": "stretch"
                },
                {
                    "type": "Column",
                    "style": "attention",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Column 2"
                        }
                    ],
                    "bleed": true,
                    "width": "stretch"
                },
                {
                    "type": "Column",
                    "style": "warning",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Column 3"
                        }
                    ],
                    "width": "stretch"
                }
            ]
        },
        {
            "type": "TextBlock",
            "text": "Bleed right"
        },
        {
            "type": "ColumnSet",
            "style": "emphasis",
            "bleed": true,
            "columns": [
                {
                    "type": "Column",
                    "style": "good",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Column 1"
                        }
                    ],
                    "width": "stretch"
                },
                {
                    "type": "Column",
                    "style": "attention",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Column 2"
                        }
                    ],
                    "width": "stretch"
                },
                {
                    "type": "Column",
                    "style": "warning",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Column 3"
                        }
                    ],
                    "bleed": true,
                    "width": "stretch"
                }
            ]
        },
        {
            "type": "TextBlock",
            "text": "Bleed all"
        },
        {
            "type": "ColumnSet",
            "style": "emphasis",
            "columns": [
                {
                    "type": "Column",
                    "style": "good",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Column 1"
                        }
                    ],
                    "bleed": true,
                    "width": "stretch"
                },
                {
                    "type": "Column",
                    "style": "attention",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Column 2"
                        }
                    ],
                    "bleed": true,
                    "width": "stretch"
                },
                {
                    "type": "Column",
                    "style": "warning",
                    "items": [
                        {
                            "type": "TextBlock",
                            "text": "Column 3"
                        }
                    ],
                    "bleed": true,
                    "width": "stretch"
                }
            ]
        },
        {
            "type": "TextBlock",
            "text": "Sample Card with Bleed",
            "wrap": true
        },
        {
      "type": "ColumnSet",
      "columns": [
        {
          "type": "Column",
          "items": [
            {
              "type": "Container",
              "backgroundImage": "https://messagecardplayground.azurewebsites.net/assets/TxP_Background.png",
              "items": [
                {
                  "type": "Image",
                  "horizontalAlignment": "center",
                  "url": "https://messagecardplayground.azurewebsites.net/assets/TxP_Flight.png",
                  "altText": "Departing airplane"
                }
              ],
              "bleed": true
            },
            {
              "type": "Container",
              "spacing": "None",
              "style": "emphasis",
              "items": [
                {
                  "type": "TextBlock",
                  "size": "extraLarge",
                  "weight": "lighter",
                  "color": "accent",
                  "text": "Flight to JFK",
                  "wrap": true
                },
                {
                  "type": "TextBlock",
                  "spacing": "small",
                  "text": "Continental Air Lines flight UA110",
                  "wrap": true
                },
                {
                  "type": "TextBlock",
                  "spacing": "none",
                  "text": "Confirmation code: RXJ34P",
                  "wrap": true
                },
                {
                  "type": "TextBlock",
                  "spacing": "none",
                  "text": "4 hours 15 minutes",
                  "wrap": true
                }
              ],
              "bleed": true,
              "height": "stretch"
            }
          ],
          "width": 45,
          "height": "stretch"
        },
        {
          "type": "Column",
          "items": [
            {
              "type": "Container",
              "height": "stretch",
              "items": [
                {
                  "type": "ColumnSet",
                  "columns": [
                    {
                      "type": "Column",
                      "items": [
                        {
                          "type": "TextBlock",
                          "size": "extraLarge",
                          "weight": "lighter",
                          "text": "SFO",
                          "wrap": true
                        }
                      ],
                      "width": "auto"
                    },
                    {
                      "type": "Column",
                      "verticalContentAlignment": "center",
                      "items": [
                        {
                          "type": "Image",
                          "url": "https://messagecardplayground.azurewebsites.net/assets/graydot2x2.png",
                          "width": "10000px",
                          "height": "2px"
                        }
                      ],
                      "width": "stretch"
                    },
                    {
                      "type": "Column",
                      "spacing": "small",
                      "verticalContentAlignment": "center",
                      "items": [
                        {
                          "type": "Image",
                          "url": "https://messagecardplayground.azurewebsites.net/assets/smallairplane.png",
                          "height": "16px",
                          "altText": "Flight to"
                        }
                      ],
                      "width": "auto"
                    },
                    {
                      "type": "Column",
                      "items": [
                        {
                          "type": "TextBlock",
                          "horizontalAlignment": "right",
                          "size": "extraLarge",
                          "weight": "lighter",
                          "text": "JFK",
                          "wrap": true
                        }
                      ],
                      "width": "auto"
                    }
                  ]
                },
                {
                  "type": "ColumnSet",
                  "columns": [
                    {
                      "type": "Column",
                      "items": [
                        {
                          "type": "RichTextBlock",
                          "inlines": [
                            {
                              "type": "TextRun",
                              "size": "medium",
                              "text": "8:15 PM\n"
                            },
                            {
                              "type": "TextRun",
                              "text": "Sat, Mar 4, 2017\n",
                              "isSubtle": true,
                              "wrap": true
                            },
                            {
                              "type": "TextRun",
                              "text": "San Francisco",
                              "isSubtle": true
                            }
                          ]
                        }
                      ],
                      "width": 1
                    },
                    {
                      "type": "Column",
                      "items": [
                        {
                          "type": "RichTextBlock",
                          "horizontalAlignment": "right",
                          "inlines": [
                            {
                              "type": "TextRun",
                              "size": "medium",
                              "text": "3:30 AM\n"
                            },
                            {
                              "type": "TextRun",
                              "text": "Sat, Mar 4, 2017\n",
                              "isSubtle": true,
                              "wrap": true
                            },
                            {
                              "type": "TextRun",
                              "text": "New York",
                              "isSubtle": true
                            }
                          ]
                        }
                      ],
                      "width": 1
                    }
                  ]
                },
                {
                  "type": "ActionSet",
                  "separator": true,
                  "actions": [
                    {
                      "type": "Action.Submit",
                      "title": "Check in",
                      "style": "positive"
                    },
                    {
                      "type": "Action.Submit",
                      "title": "View"
                    }
                  ],
                  "spacing": "medium"
                }
              ]
            }
          ],
          "width": 55
        }
      ],
      "height": "stretch"
    }
    ]
}
	)";
}

    
