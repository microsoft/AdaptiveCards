import * as AC from "adaptivecards";

/*
The below code demonstrates how to implement a custom Adaptive Card action using
the JS SDK version 2.0 and greater.
   
IMPORTANT: the JS SDK now leverages decorators, which must be enabled in your tsconfig file:

{
    ...,
    "compilerOptions": {
        "experimentalDecorators": true,
        ...
    },
    ...
}
*/

export class AlertAction extends AC.Action {
    static readonly JsonTypeName = "Action.Alert";

    //#region Schema

    static readonly textProperty = new AC.StringProperty(AC.Versions.v1_0, "text", true);

    @AC.property(AlertAction.textProperty)
    text?: string;

    //#endregion

    getJsonTypeName(): string {
        return AlertAction.JsonTypeName;
    }

    execute() {
        alert(this.text);
    }
}

AC.GlobalRegistry.actions.register(AlertAction.JsonTypeName, AlertAction);

/* A per-card registry can also be used instead of the global registry,
   as demonstrated below

// Create a custom registry for actions
let actionRegistry = new AC.CardObjectRegistry<AC.Action>();

// Populate it with the default set of actions
AC.GlobalRegistry.populateWithDefaultActions(actionRegistry);

// Register the custom AlertAction type
actionRegistry.register(AlertAction.JsonTypeName, AlertAction);

// Parse a card payload using the custom registry
let serializationContext = new AC.SerializationContext();
serializationContext.setActionRegistry(actionRegistry);

let card = new AC.AdaptiveCard();
card.parse(
    {
        type: "AdaptiveCard",
        version: "1.0",
        body: [
            {
                type: "TextBlock",
                text: "This demonstrates the ProgressBar element."
            }
        ],
        actions: [
            {
                type: "Action.Alert",
                title: "Click me!",
                text: "Hello World"
            }
        ]
    },
    serializationContext
);
*/