// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export const otherTestPayload: string = `{
	"$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
	"type": "AdaptiveCard",
	"version": "1.0",
	"body": [
		{
			"type": "ActionSet",
			"actions": [
				{
					"type": "Action.ShowCard",
					"title": "Set due date",
					"card": {
						"type": "AdaptiveCard",
						"body": [
							{
								"type": "Input.Date",
								"id": "dueDate",
								"title": "Select due date"
							},
							{
								"type": "Input.Text",
								"id": "comment",
								"isMultiline": true,
								"placeholder": "Add a comment"
							}
						],
						"actions": [
							{
								"type": "Action.OpenUrl",
								"title": "OK",
								"url": "http://adaptivecards.io"
							}
						]
					}
				},
				{
					"type": "Action.OpenUrl",
					"title": "View",
					"url": "http://adaptivecards.io"
				}
			]
		}
	]
}`;

export const defaultPayload: string = `{
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "TextBlock",
            "size": "Large",
            "weight": "Bolder",
            "text": "Welcome to Build 2019!",
            "wrap": true
        },
        {
            "type": "TextBlock",
            "text": "Local device information..."
        },
        {
            "type": "FactSet",
            "facts": [
                {
                    "title": "Platform",
                    "value": "{platform}"
                },
                {
                    "title": "Manufacturer",
                    "value": "{manufacturer}"
                },
                {
                    "title": "Model",
                    "value": "{model}"
                },
                {
                    "title": "OS Version",
                    "value": "{osVersion}"
                }
            ]
        },
        {
            "type": "ColumnSet",
            "spacing": "Large",
            "columns": [
                {
                    "type": "Column",
                    "items": [
                        {
                            "type": "TextBlock",
                            "size": "Small",
                            "weight": "Bolder",
                            "text": "This card was natively rendered on {platform} using the Adaptive Cards {platform} library",
                            "wrap": true
                        }
                    ],
                    "width": "stretch",
                    "verticalContentAlignment": "Bottom"
                },
                {
                    "type": "Column",
                    "items": [
                        {
                            "type": "Image",
                            "url": "https://raw.githubusercontent.com/Microsoft/AdaptiveCards/master/assets/adaptive-card-200.png",
                            "size": "Stretch"
                        }
                    ],
                    "width": "40px",
                    "verticalContentAlignment": "Bottom"
                },
                {
                    "type": "Column",
                    "items": [
                        {
                            "$when": "{platform == 'Android'}",
                            "type": "Image",
                            "url": "https://upload.wikimedia.org/wikipedia/commons/thumb/d/d7/Android_robot.svg/872px-Android_robot.svg.png",
                            "height": "40px"
                        },
                        {
                            "$when": "{platform == 'WPF'}",
                            "type": "Image",
                            "url": "https://upload.wikimedia.org/wikipedia/commons/thumb/5/5f/Windows_logo_-_2012.svg/768px-Windows_logo_-_2012.svg.png",
                            "height": "40px"
                        },
                        {
                            "$when": "{platform == 'HTML JS'}",
                            "type": "Image",
                            "url": "https://www.w3.org/html/logo/downloads/HTML5_Logo_512.png",
                            "height": "40px"
                        }
                    ],
                    "width": "40px",
                    "verticalContentAlignment": "Bottom"
                }
            ]
        }
    ],
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json"
}`;
