import * as Designer from "adaptivecards-designer";
// import { WebChatContainer } from "./containers/webchat-container";
// import { CortanaContainer } from "./containers/cortana-container";
// import { OutlookContainer } from "./containers/outlook-container";
// import { TimelineContainer } from "./containers/timeline-container";
// import { DarkTeamsContainer, LightTeamsContainer } from "./containers/teams-container";
// import { BotFrameworkContainer } from "./containers/bf-image-container";
// import { ToastContainer } from "./containers/toast-container";
import "./app.css";
import "adaptivecards/dist/adaptivecards-default.css";
import "adaptivecards-controls/dist/adaptivecards-controls.css";
import "adaptivecards-designer/dist/adaptivecards-designer.css";

window.onload = () => {
    if (!Designer.SettingsManager.isLocalStorageAvailable) {
        console.log("Local storage is not available.");
    }

    // Prepare a list of host containers
    // This is not required. When no list is passed (empty array or null), the designer
    // uses a default built-in host container, and the host container pixker in the
    // toolbar is hidden.
    let hostContainers: Array<Designer.HostContainer> = [];
    // hostContainers.push(new WebChatContainer("Bot Framework WebChat", "css/webchat-container.css"));
    // hostContainers.push(new CortanaContainer("Cortana Skills", "css/cortana-container.css"));
    // hostContainers.push(new OutlookContainer("Outlook Actionable Messages", "css/outlook-container.css"));
    // hostContainers.push(new TimelineContainer("Windows Timeline", "css/timeline-container.css"));
    // hostContainers.push(new DarkTeamsContainer("Microsoft Teams - Dark", "css/teams-container-dark.css"));
    // hostContainers.push(new LightTeamsContainer("Microsoft Teams - Light", "css/teams-container-light.css"));
    // hostContainers.push(new BotFrameworkContainer("Bot Framework Other Channels (Image render)", "css/bf-image-container.css"));
    // hostContainers.push(new ToastContainer("Windows Notifications (Preview)", "css/toast-container.css"));

    let designer = new Designer.CardDesigner(hostContainers);

    /* Here's how to add buttons to the toolbar:

    designer.toolbar.addElement(new ToolbarSeparator());
    designer.toolbar.addElement(
        new ToolbarButton(
            "Save",
            null,
            (sender) => {
                // Here is how to get the payload of the current card from the designer
                let card = designer.getCard();

                alert(JSON.stringify(card, null, 4));
            }
        )
    )
    */

    // NOTE: Adding toolbar elements must be done BEFORE the designer is attached

    designer.attachTo(document.getElementById("designerRootHost"));

    /* Here's how to collapse certain panes by default:
    
    designer.treeViewPane.collapse();
    designer.jsonEditorPane.collapse();
    */

    /* Here's how to set the card payload in the designer:

    designer.setCard(
        {
            type: "AdaptiveCard",
            version: "1.0",
            body: [
                {
                    type: "TextBlock",
                    text: "Hello world"
                }
            ]
        }
    );
    */

    // NOTE: Collapsing panes/setting the card payload must be done AFTER the designer is attached
};
