// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as containers from "./containers";
import { DeviceEmulation } from "./device-emulation";

export * from "./adaptivecards-designer-standalone";
export * from "./containers/index";

export const defaultMicrosoftHosts: containers.HostContainer[] = [
    new containers.WebChatContainer("Bot Framework WebChat", "containers/webchat-container.css"),
    new containers.OutlookContainer("Outlook Actionable Messages", "containers/outlook-container.css"),
    new containers.DarkTeamsContainer("Microsoft Teams - Dark", "containers/teams-container-dark.css"),
    new containers.LightTeamsContainer("Microsoft Teams - Light", "containers/teams-container-light.css"),
    new containers.DarkVivaConnectionsContainer("Viva Connections - Dark (Preview)", "containers/viva-connections-container-dark.css"),
    new containers.LightVivaConnectionsContainer("Viva Connections - Light", "containers/viva-connections-container-light.css"),
    new containers.DarkCortanaContainer("Cortana Skills - Dark", "containers/cortana-container-dark.css"),
    new containers.LightCortanaContainer("Cortana Skills - Light", "containers/cortana-container-light.css"),
    new containers.BotFrameworkContainer("Bot Framework Other Channels (Image render)", "containers/bf-image-container.css"),
    new containers.CortanaClassicContainer("Cortana Skills (Classic)", "containers/cortana-classic-container.css"),
    new containers.FederatedSearchContainer("Federated Search","containers/federated-search-container.css"),
    new containers.BerlinContainer(containers.ContainerSize.Small, containers.ColorTheme.Light),
];

export const defaultMicrosoftDeviceEmulations: DeviceEmulation[] = [
  { name: "Desktop (unconstrained)", maxWidth: undefined },
  { name: "Small mobile (320px)", maxWidth: "320px" },
  { name: "Large mobile (414px)", maxWidth: "414px" },
  { name: "Small tablet (768px)", maxWidth: "768px" },
  { name: "Large tablet (1024px)", maxWidth: "1024px" },
];
