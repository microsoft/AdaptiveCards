/*
    refresh: {
        action: {
            type: "Action.Execute",
            verb: "refreshAction"
        },
        userIds: [ "fdsfds@consotos.com", "david@ms.com" ]
    },
*/
export const sampleCard = {
    type: "AdaptiveCard",
    $schema: "http://adaptivecards.io/schemas/adaptive-card.json",
    version: "1.6",
    authentication: {
        text: "Let's authenticate",
        connectionName: "myConnection",
        tokenExchangeResource: {
            id: "abc",
            uri: "http://contoso.com/ter",
            providerId: "myProviderId"
        },
        buttons: [
            {
                type: "signin",
                title: "Click me to sign in",
                image: "http://contoso.com/someimage.jpg",
                value: "http://singinurl"
            }
        ]
    },
    body: [
        {
            type: "TextBlock",
            size: "Medium",
            weight: "Bolder",
            text: "Publish [Adaptive Card Schema](https://adaptivecards.io)"
        },
        {
            type: "ColumnSet",
            columns: [
                {
                    type: "Column",
                    items: [
                        {
                            type: "Image",
                            style: "Person",
                            url: "https://matthidinger.com/images/bio-photo.jpg",
                            size: "Small"
                        }
                    ],
                    width: "auto"
                },
                {
                    type: "Column",
                    items: [
                        {
                            type: "TextBlock",
                            weight: "Bolder",
                            text: "Matt Hidinger",
                            wrap: true
                        },
                        {
                            type: "TextBlock",
                            spacing: "None",
                            text: "Created {{DATE(2017-02-14T06:08:39Z,SHORT)}}",
                            isSubtle: true,
                            wrap: true
                        }
                    ],
                    width: "stretch"
                }
            ]
        },
        {
            type: "TextBlock",
            text: "Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub. The schema will be the starting point of our reference documentation.",
            wrap: true
        },
        {
            type: "FactSet",
            facts: [
                { title: "Board", value: "Adaptive Cards" },
                { title: "List", value: "Backlog" },
                { title: "Assigned to", value: "Matt Hidinger" },
                { title: "Due date", value: "Not set" }
            ]
        },
        {
            "type": "Input.ChoiceSet",
            "choices": [
                {
                    "title": "Surya",
                    "value": "Choice 1"
                },
                {
                    "title": "Suryansh",
                    "value": "Choice 2"
                },
                {
                    "title": "Suryanarayan",
                    "value": "Choice 3"
                },
                {
                    "title": "Suryavanshi",
                    "value": "Choice 4"
                }
            ],
            "style": "compact",
            "placeholder": "Filtered ChoiceSet"
        },
        {
            "type": "Input.ChoiceSet",
            "choices": [
                {
                    "title": "Surya",
                    "value": "Choice 1"
                },
                {
                    "title": "Suryansh",
                    "value": "Choice 2"
                },
                {
                    "title": "Suryanarayan",
                    "value": "Choice 3"
                },
                {
                    "title": "Suryavanshi",
                    "value": "Choice 4"
                }
            ],
            "choices.data": {
                "type": "Data.Query",
                "dataset": "random"
            },
            "placeholder": "Dynamically Filtered Choiceset"
        }
    ],
    actions: [
        {
            type: "Action.Execute",
            verb: "remoteSucceedReturnCard",
            title: "Succeed in 3 attempts with card"
        },
        {
            type: "Action.Execute",
            verb: "remoteSucceedReturnString",
            title: "Succeed with string"
        },
        {
            type: "Action.Execute",
            verb: "remoteFailedUnrecoverable",
            title: "Fail"
        },
        {
            type: "Action.Execute",
            verb: "localFailSSO",
            title: "Fail, require SSO"
        },
        {
            type: "Action.Execute",
            verb: "localFailOAuth",
            title: "Fail, require OAuth"
        },
        {
            type: "Action.Execute",
            verb: "localException",
            title: "Fail with exception"
        }
    ]
};

export const sampleRefreshCard = {
    type: "AdaptiveCard",
    body: [
        {
            type: "TextBlock",
            text: "This card has been refreshed",
            size: "ExtraLarge",
            wrap: true
        },
        {
            type: "TextBlock",
            text: "The response to the Submit action included a new card payload.",
            wrap: true
        }
    ],
    $schema: "http://adaptivecards.io/schemas/adaptive-card.json",
    version: "1.0"
};

export const ssoSuccessCard = {
    type: "AdaptiveCard",
    body: [
        {
            type: "TextBlock",
            text: "Successfully authenticated with SSO!",
            size: "ExtraLarge",
            wrap: true
        }
    ],
    $schema: "http://adaptivecards.io/schemas/adaptive-card.json",
    version: "1.0"
};


export const oauthSuccessCard = {
    type: "AdaptiveCard",
    body: [
        {
            type: "TextBlock",
            text: "Successfully authenticated with OAuth!",
            size: "ExtraLarge",
            wrap: true
        }
    ],
    $schema: "http://adaptivecards.io/schemas/adaptive-card.json",
    version: "1.0"
};
