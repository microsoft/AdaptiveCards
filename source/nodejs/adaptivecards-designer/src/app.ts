import { SettingsManager } from "./settings-manager";
import { CardDesigner } from "./card-designer";
import { OutlookContainer } from "./containers/outlook-container";
import { LightTeamsContainer, DarkTeamsContainer } from "./containers/teams-container";
import { CortanaContainer } from "./containers/cortana-container";
import { WebChatContainer } from "./containers/webchat-container";
import { ToastContainer } from "./containers/toast-container";
import { TimelineContainer } from "./containers/timeline-container";
import { BotFrameworkContainer } from "./containers/bf-image-container";
import { ToolbarButton, ToolbarSeparator } from "./toolbar";

window.onload = () => {
    if (!SettingsManager.isLocalStorageAvailable) {
        console.log("Local storage is not available.");
    }

    let designer = new CardDesigner();

    designer.hostContainers.push(new WebChatContainer("Bot Framework WebChat", "css/webchat-container.css"));
    designer.hostContainers.push(new CortanaContainer("Cortana Skills", "css/cortana-container.css"));
    designer.hostContainers.push(new OutlookContainer("Outlook Actionable Messages", "css/outlook-container.css"));
    designer.hostContainers.push(new TimelineContainer("Windows Timeline", "css/timeline-container.css"));
    designer.hostContainers.push(new DarkTeamsContainer("Microsoft Teams - Dark", "css/teams-container-dark.css"));
    designer.hostContainers.push(new LightTeamsContainer("Microsoft Teams - Light", "css/teams-container-light.css"));
    designer.hostContainers.push(new BotFrameworkContainer("Bot Framework Other Channels (Image render)", "css/bf-image-container.css"));
    designer.hostContainers.push(new ToastContainer("Windows Notifications (Preview)", "css/toast-container.css"));

    designer.toolbar.addElement(new ToolbarSeparator());
    designer.toolbar.addElement(
        new ToolbarButton(
            "Save",
            null,
            (sender) => {
                let card = designer.getCard();

                alert(JSON.stringify(card, null, 4));
            }
        )
    )

    designer.attachTo(document.getElementById("designerRootHost"));

    designer.treeViewPane.collapse();
    designer.jsonEditorPane.collapse();

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
};
