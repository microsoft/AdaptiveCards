// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as containers from "./containers";
import { DeviceEmulation } from "./device-emulation";

export * from "./adaptivecards-designer-standalone";
export * from "./containers/index";

export const defaultMicrosoftHosts: containers.HostContainer[] = [
    new containers.WebChatContainer("Bot Framework WebChat", "containers/webchat-container.css"),
    new containers.OutlookContainer("Outlook Actionable Messages", "containers/outlook-container.css"),
    new containers.TeamsContainer(),
    new containers.VivaConnectionsContainer(),
    new containers.CortanaContainer(),
    new containers.BotFrameworkContainer("Bot Framework Other Channels (Image render)", "containers/bf-image-container.css"),
    new containers.CortanaClassicContainer("Cortana Skills (Classic)", "containers/cortana-classic-container.css"),
    new containers.FederatedSearchContainer("Federated Search","containers/federated-search-container.css"),
    new containers.WidgetContainer(containers.ContainerSize.Small),
];

export const defaultMicrosoftDeviceEmulations: DeviceEmulation[] = [
  { name: "Desktop (unconstrained)", maxWidth: undefined },
  { name: "Small mobile (320px)", maxWidth: "320px" },
  { name: "Large mobile (414px)", maxWidth: "414px" },
  { name: "Small tablet (768px)", maxWidth: "768px" },
  { name: "Large tablet (1024px)", maxWidth: "1024px" },
];
