import { Action, AdaptiveCard, HostConfig } from "./adaptivecards";
import { IAdaptiveCard } from "./schema";

export interface RenderOptions {
    hostConfig?: HostConfig | string | object;
    onAction?: (action: Action) => void;
    onValidationError?: (error: string) => void;
}

export function render(card: IAdaptiveCard | string, options?: RenderOptions): HTMLElement {

    if (typeof card === "string") {
        card = <IAdaptiveCard>JSON.parse(card);
    }

    if (typeof options === "undefined") {
        options = {}
    }

    let adaptiveCard = new AdaptiveCard();
    adaptiveCard.parse(card);
    adaptiveCard.onAction = options.onAction;

    let hostConfig: HostConfig;

    if (isHostConfig(options.hostConfig)) {
        hostConfig = options.hostConfig;
    }
    else if (options.hostConfig instanceof String) {
        hostConfig = new HostConfig(JSON.parse(options.hostConfig));
    } else {
        hostConfig = new HostConfig(options.hostConfig);
    }

    AdaptiveCard.onExecuteAction = options.onAction;
    adaptiveCard.hostConfig = hostConfig;
    return adaptiveCard.render();
}

function isHostConfig(hostConfig: HostConfig | string | any): hostConfig is HostConfig {
    // TODO: make this 5check better
    return hostConfig && hostConfig.getContainerStyleDefinition;
}
