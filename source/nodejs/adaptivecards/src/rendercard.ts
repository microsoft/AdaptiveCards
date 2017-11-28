import { Action, AdaptiveCard, HostConfig } from "./adaptivecards";
import { IAdaptiveCard } from "./schema";

export interface RenderOptions {
    hostConfig?: HostConfig | string | object;
    onExecuteAction?: (action: Action) => void;
    onValidationError?: (error: string) => void;
    processMarkdown?: (text: string) => string;
}

export function renderCard(card: IAdaptiveCard | string, options?: RenderOptions): HTMLElement {

    if (typeof card === "string") {
        card = <IAdaptiveCard>JSON.parse(card);
    }

    options = options || {};

    // Parse the host config
    let hostConfig: HostConfig;
    if (isHostConfig(options.hostConfig)) {
        hostConfig = options.hostConfig;
    }
    else if (options.hostConfig instanceof String) {
        hostConfig = new HostConfig(JSON.parse(options.hostConfig));
    } else {
        hostConfig = new HostConfig(options.hostConfig);
    }

    // Parse the card
    let adaptiveCard = new AdaptiveCard();
    adaptiveCard.parse(card);
    adaptiveCard.hostConfig = hostConfig;    
    adaptiveCard.onExecuteAction = options.onExecuteAction;
    
    // Process markdown
    if (options.processMarkdown) {
        AdaptiveCard.processMarkdown = options.processMarkdown;
    }

    // Render the card
    return adaptiveCard.render();
}

function isHostConfig(hostConfig: HostConfig | string | any): hostConfig is HostConfig {
    // TODO: make this check better
    return hostConfig && hostConfig.getContainerStyleDefinition;
}
