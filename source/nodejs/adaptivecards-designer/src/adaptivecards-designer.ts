// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as containers from "./containers";

export * from "./adaptivecards-designer-standalone";
export * from "./containers/index";

export const defaultMicrosoftHosts: containers.HostContainer[] = [
	new containers.WebChatContainer("Bot Framework WebChat", "containers/webchat-container.css"),
	new containers.OutlookContainer("Outlook Actionable Messages", "containers/outlook-container.css"),
	new containers.DarkTeamsContainer("Microsoft Teams - Dark", "containers/teams-container-dark.css"),
	new containers.LightTeamsContainer("Microsoft Teams - Light", "containers/teams-container-light.css"),
	new containers.DarkCortanaContainer("Cortana Skills - Dark", "containers/cortana-container-dark.css"),
	new containers.LightCortanaContainer("Cortana Skills - Light", "containers/cortana-container-light.css"),
	new containers.TimelineContainer("Windows Timeline", "containers/timeline-container.css"),
	new containers.BotFrameworkContainer("Bot Framework Other Channels (Image render)", "containers/bf-image-container.css"),
	new containers.CortanaClassicContainer("Cortana Skills (Classic)", "containers/cortana-classic-container.css"),
	new containers.ToastContainer("Windows Notifications (Preview)", "containers/toast-container.css"),
]