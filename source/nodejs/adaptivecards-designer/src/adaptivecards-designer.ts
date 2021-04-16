// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as containers from "./containers";
import { __ } from './i18n';

export * from "./adaptivecards-designer-standalone";
export * from "./containers/index";

export const defaultMicrosoftHosts: containers.HostContainer[] = [
	new containers.WebChatContainer(__("hostContainer.names.webChat"), "containers/webchat-container.css"),
	new containers.OutlookContainer(__("hostContainer.names.outlook"), "containers/outlook-container.css"),
	new containers.DarkTeamsContainer(__("hostContainer.names.darkTeams"), "containers/teams-container-dark.css"),
	new containers.LightTeamsContainer(__("hostContainer.names.lightTeams"), "containers/teams-container-light.css"),
	new containers.DarkCortanaContainer(__("hostContainer.names.darkCortana"), "containers/cortana-container-dark.css"),
	new containers.LightCortanaContainer(__("hostContainer.names.lightCortana"), "containers/cortana-container-light.css"),
	new containers.TimelineContainer(__("hostContainer.names.timeline"), "containers/timeline-container.css"),
	new containers.BotFrameworkContainer(__("hostContainer.names.botFramework"), "containers/bf-image-container.css"),
	new containers.CortanaClassicContainer(__("hostContainer.names.cortanaClassic"), "containers/cortana-classic-container.css"),
	new containers.ToastContainer(__("hostContainer.names.toast"), "containers/toast-container.css"),
]
