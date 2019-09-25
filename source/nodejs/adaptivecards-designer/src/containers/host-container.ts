// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import * as hostConfig from "../hostConfigs/sample.json";

export abstract class HostContainer {
    private _cardHost: HTMLElement;

    readonly name: string;
    readonly styleSheet: string;

    constructor(name: string, styleSheet: string) {
        this.name = name;
        this.styleSheet = styleSheet;

        this._cardHost = document.createElement("div");
        this._cardHost.className = "cardHost";
    }

    abstract renderTo(hostElement: HTMLElement);

    public initialize() {
        Adaptive.AdaptiveCard.elementTypeRegistry.reset();
        Adaptive.AdaptiveCard.actionTypeRegistry.reset();

        Adaptive.GlobalSettings.useMarkdownInRadioButtonAndCheckbox = true;
        Adaptive.GlobalSettings.useAdvancedCardBottomTruncation = false;
        Adaptive.GlobalSettings.useAdvancedTextBlockTruncation = true;
    }

    public getBackgroundColor(): string {
        return "#F6F6F6";
    }

    public parseElement(element: Adaptive.CardElement, source: any, parseContext: Adaptive.CardObjectParseContext) {
        // Do nothing in base implementation
    }

    public anchorClicked(element: Adaptive.CardElement, anchor: HTMLAnchorElement): boolean {
        // Not handled by the host container by default
        return false;
    }

    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfig);
    }

    supportsActionBar: boolean = false;

    get cardHost(): HTMLElement {
        return this._cardHost;
    }

    get isFixedHeight(): boolean {
        return false;
    }
}
