import { SettingsManager } from "./settings-manager";
import { DesignerApp } from "./card-designer";
import { OutlookContainer } from "./containers/outlook-container";
import { LightTeamsContainer, DarkTeamsContainer } from "./containers/teams-container";
import { CortanaContainer } from "./containers/cortana-container";
import { WebChatContainer } from "./containers/webchat-container";
import { ToastContainer } from "./containers/toast-container";
import { TimelineContainer } from "./containers/timeline-container";
import { BotFrameworkContainer } from "./containers/bf-image-container";

window.onload = () => {
    if (!SettingsManager.isLocalStorageAvailable) {
        console.log("Local storage is not available.");
    }

    let app = new DesignerApp();

    app.hostContainers.push(new WebChatContainer("Bot Framework WebChat", "css/webchat-container.css"));
    app.hostContainers.push(new CortanaContainer("Cortana Skills", "css/cortana-container.css"));
    app.hostContainers.push(new OutlookContainer("Outlook Actionable Messages", "css/outlook-container.css"));
    app.hostContainers.push(new TimelineContainer("Windows Timeline", "css/timeline-container.css"));
    app.hostContainers.push(new DarkTeamsContainer("Microsoft Teams - Dark", "css/teams-container-dark.css"));
    app.hostContainers.push(new LightTeamsContainer("Microsoft Teams - Light", "css/teams-container-light.css"));
    app.hostContainers.push(new BotFrameworkContainer("Bot Framework Other Channels (Image render)", "css/bf-image-container.css"));
    app.hostContainers.push(new ToastContainer("Windows Notifications (Preview)", "css/toast-container.css"));

    app.attachTo(document.getElementById("designerRootHost"));
};
