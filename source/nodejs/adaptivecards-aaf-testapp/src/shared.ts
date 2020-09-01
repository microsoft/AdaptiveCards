/*
    autoRefresh: {
        userIds: [ "john@contoso.com", "jane@contoso.com" ],
        displayCurrentCardWhileRefreshing: false,
        action: {
            type: "Action.Execute",
            verb: "succeedReturnCard",
            title: "Auto-refresh"
        },
    },
*/

export const sampleCard = {
    type: "AdaptiveCard",
    body: [
        {
            type: "TextBlock",
            size: "Medium",
            weight: "Bolder",
            text: "Publish Adaptive Card Schema"
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
                            url: "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg",
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
            verb: "remoteFailedUnauthenticated",
            title: "Fail with auth"
        },
        {
            type: "Action.Execute",
            verb: "localException",
            title: "Fail with exception"
        }
    ],
    $schema: "http://adaptivecards.io/schemas/adaptive-card.json",
    version: "1.0"
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
