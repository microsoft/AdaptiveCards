import * as AdaptiveCards from "adaptivecards";

function asdf2(){
    // author a card
    // in practice you'll probably get this from a service
    // see http://adaptivecards.io/samples/ for inspiration
    var card = {
        "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
        "type": "AdaptiveCard",
        "version": "1.0",
        "body": [
            {
                "type": "TextBlock",
                "size": "medium",
                "weight": "bolder",
                "text": "Input.Text elements",
                "horizontalAlignment": "center"
            },
            {
                "type": "Input.Text",
                "placeholder": "Name",
                "style": "text",
                "maxLength": 0,
                "id": "SimpleVal"
            },
            {
                "type": "Input.Text",
                "placeholder": "Comments",
                "style": "text",
                "isMultiline": true,
                "maxLength": 0,
                "id": "MultiLineVal"
            },
            {
                "type": "Input.Number",
                "placeholder": "Quantity",
                "min": -5,
                "max": 5,
                "value": 1,
                "id": "NumVal"
            },
            {
                "type": "Input.Date",
                "placeholder": "Due Date",
                "id": "DateVal",
                "value": "2017-09-20"
            },
            {
                "type": "Input.Time",
                "placeholder": "Start time",
                "id": "TimeVal",
                "value": "16:59"
            },
            {
                "type": "TextBlock",
                "size": "medium",
                "weight": "bolder",
                "text": "Input.ChoiceSet",
                "horizontalAlignment": "center"
            },
            {
                "type": "TextBlock",
                "text": "What color do you want? (compact)"
            },
            {
                "type": "Input.ChoiceSet",
                "id": "CompactSelectVal",
                "style": "compact",
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
                "text": "What color do you want? (expanded)"
            },
            {
                "type": "Input.ChoiceSet",
                "id": "SingleSelectVal",
                "style": "expanded",
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
                "text": "What colors do you want? (multiselect)"
            },
            {
                "type": "Input.ChoiceSet",
                "id": "MultiSelectVal",
                "isMultiSelect": true,
                "value": "1,3",
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
                "size": "medium",
                "weight": "bolder",
                "text": "Input.Toggle",
                "horizontalAlignment": "center"
            },
            {
                "type": "Input.Toggle",
                "title": "I accept the terms and conditions",
                "valueOn": "true",
                "valueOff": "false",
                "id": "AcceptsTerms"
            },
            {
                "type": "Input.Toggle",
                "title": "Red cars are better than other cars",
                "valueOn": "RedCars",
                "valueOff": "NotRedCars",
                "id": "ColorPreference"
            }
        ],
        "actions": [
            {
                "type": "Action.Submit",
                "title": "Submit",
                "data": {
                    "id": "1234567890"
                }
            },
            {
                "type": "Action.ShowCard",
                "title": "Show Card",
                "card": {
                    "type": "AdaptiveCard",
                    "body": [
                        {
                            "type": "Input.Text",
                            "placeholder": "enter comment",
                            "style": "text",
                            "maxLength": 0,
                            "id": "CommentVal"
                        }
                    ],
                    "actions": [
                        {
                            "type": "Action.Submit",
                            "title": "OK"
                        }
                    ]
                }
            }
        ]
    };

    // Create an AdaptiveCard instance
    var adaptiveCard = new AdaptiveCards.AdaptiveCard();

    // Set its hostConfig property unless you want to use the default Host Config
    // Host Config defines the style and behavior of a card
    adaptiveCard.hostConfig = new AdaptiveCards.HostConfig({
        fontFamily: "Segoe UI, Helvetica Neue, sans-serif"
        // More host config options
        // You can find example configs here: https://github.com/microsoft/AdaptiveCards/tree/main/samples/HostConfig
    });

    // Set the adaptive card's event handlers. onExecuteAction is invoked
    // whenever an action is clicked in the card
    adaptiveCard.onExecuteAction = function (action) {
        alert("Ow!");
    }

    // Parse the card payload
    adaptiveCard.parse(card);

    // Render the card to an HTML element:
    var renderedCard = adaptiveCard.render();

    // And finally insert it in the page:
    // document.getElementById('exampleDiv').appendChild(renderedCard);
}
