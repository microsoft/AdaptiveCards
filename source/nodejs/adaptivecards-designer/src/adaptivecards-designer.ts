// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { CardDesigner } from "./card-designer";
import * as containers from "./containers";
import { DeviceEmulation } from "./device-emulation";
import { PlatformPackage, PlatformType } from "./platform-package";

export * from "./adaptivecards-designer-standalone";
export * from "./containers/index";

// Which hosts are shown with common?? Right now I'm going to show all of them
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
]

export const defaultMicrosoftWindowsHosts: containers.HostContainer[] = [
	new containers.WebChatContainer("Bot Framework WebChat", "containers/webchat-container.css"),
    new containers.VivaConnectionsContainer(),
    new containers.CortanaContainer(),
    new containers.BotFrameworkContainer("Bot Framework Other Channels (Image render)", "containers/bf-image-container.css"),
    new containers.CortanaClassicContainer("Cortana Skills (Classic)", "containers/cortana-classic-container.css"),
    new containers.FederatedSearchContainer("Federated Search","containers/federated-search-container.css"),
    new containers.WidgetContainer(containers.ContainerSize.Small),
]

export const defaultMicrosoftMobileHosts: containers.HostContainer[] = [
    new containers.OutlookContainer("Outlook Actionable Messages", "containers/outlook-container.css"),
    new containers.TeamsContainer(),
];

export const defaultPlatformPackages: PlatformPackage[] = [
	new PlatformPackage(PlatformType.Common, defaultMicrosoftHosts, CardDesigner.ToolbarCommands.CommonHostAppPicker),
	new PlatformPackage(PlatformType.Windows, defaultMicrosoftWindowsHosts, CardDesigner.ToolbarCommands.WindowsHostAppPicker),
	new PlatformPackage(PlatformType.Mobile, defaultMicrosoftMobileHosts, CardDesigner.ToolbarCommands.MobileHostAppPicker)
];

export const defaultMicrosoftDeviceEmulations: DeviceEmulation[] = [
  { name: "Desktop (unconstrained)", maxWidth: undefined },
  { name: "Small mobile (320px)", maxWidth: "320px" },
  { name: "Large mobile (414px)", maxWidth: "414px" },
  { name: "Small tablet (768px)", maxWidth: "768px" },
  { name: "Large tablet (1024px)", maxWidth: "1024px" },
];
