import * as monaco from "monaco-editor/esm/vs/editor/editor.api";
import * as markdownit from "markdown-it";
import * as Designer from "adaptivecards-designer";
import "./app.css";
import "adaptivecards/dist/adaptivecards-default.css";
import "adaptivecards-controls/dist/adaptivecards-controls.css";
import "adaptivecards-designer/dist/adaptivecards-designer.css";

window.onload = () => {
	Designer.CardDesigner.processMarkdown = (text: string) => new markdownit().render(text);

	if (!Designer.SettingsManager.isLocalStorageAvailable) {
		console.log("Local storage is not available.");
	}

	let hostContainers: Array<Designer.HostContainer> = [];
	hostContainers.push(new Designer.WebChatContainer("Bot Framework WebChat", "containers/webchat-container.css"));
	hostContainers.push(new Designer.CortanaContainer("Cortana Skills", "containers/cortana-container.css"));
	hostContainers.push(new Designer.OutlookContainer("Outlook Actionable Messages", "containers/outlook-container.css"));
	hostContainers.push(new Designer.TimelineContainer("Windows Timeline", "containers/timeline-container.css"));
	hostContainers.push(new Designer.DarkTeamsContainer("Microsoft Teams - Dark", "containers/teams-container-dark.css"));
	hostContainers.push(new Designer.LightTeamsContainer("Microsoft Teams - Light", "containers/teams-container-light.css"));
	hostContainers.push(new Designer.BotFrameworkContainer("Bot Framework Other Channels (Image render)", "containers/bf-image-container.css"));
	hostContainers.push(new Designer.ToastContainer("Windows Notifications (Preview)", "containers/toast-container.css"));

	let designer = new Designer.CardDesigner(hostContainers);
	designer.attachTo(document.getElementById("designerRootHost"));
	designer.monacoModuleLoaded(monaco);
};
