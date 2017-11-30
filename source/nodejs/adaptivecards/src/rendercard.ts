import { Action, ShowCardAction, CardElement, AdaptiveCard, HostConfig } from "./adaptivecards";
import { IAdaptiveCard } from "./schema";

export interface IRenderOptions {
    hostConfig?: HostConfig | string | object;
    onAnchorClicked?: (anchor: HTMLAnchorElement) => boolean;
    onExecuteAction?: (action: Action) => void;
    onElementVisibilityChanged?: (element: CardElement) => void;
    onInlineCardExpanded?: (action: ShowCardAction, isExpanded: boolean) => void;
    onParseElement?: (element: CardElement, json: any) => void;
    processMarkdown?: (text: string) => string;
}

export function renderCard(card: IAdaptiveCard | string,
                           options?: IRenderOptions,
                           target?: HTMLElement): HTMLElement {

    if (typeof card === "string") {
        card = <IAdaptiveCard>JSON.parse(card);
    }

    options = options || {};

    // Setup a card
    let adaptiveCard = new AdaptiveCard();

    if (typeof options.hostConfig === "string") {
        adaptiveCard.hostConfig = new HostConfig(JSON.parse(options.hostConfig));
    }
    else if (typeof options.hostConfig === "object" && !(options.hostConfig instanceof HostConfig)) {
        adaptiveCard.hostConfig = new HostConfig(options.hostConfig);
    }
    else {
        adaptiveCard.hostConfig = options.hostConfig;
    }

    adaptiveCard.onAnchorClicked = options.onAnchorClicked;
    adaptiveCard.onExecuteAction = options.onExecuteAction;
    adaptiveCard.onElementVisibilityChanged = options.onElementVisibilityChanged;
    adaptiveCard.onInlineCardExpanded = options.onInlineCardExpanded;
    adaptiveCard.onParseElement = options.onParseElement;

    if (options.processMarkdown) {
        AdaptiveCard.processMarkdown = options.processMarkdown;
    }

    // Parse the card
    adaptiveCard.parse(card);
    
    // Render the card
    return adaptiveCard.render(target);
}
