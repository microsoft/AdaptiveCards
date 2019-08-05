// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { AdaptiveCardPeer } from "../designer-peers";
import { isNullOrEmpty } from "adaptivecards";
import { isNullOrUndefined } from "util";

var sampleConfiguration = require("../../../../../samples/HostConfig/sample.json");

export abstract class HostContainer {

    get cardHost(): HTMLElement {
        return this._cardHost;
    }

    get isFixedHeight(): boolean {
        return false;
    }

    readonly name: string;
    readonly styleSheet: string;

    public supportsActionBar: boolean = false;
	public _cardHostConfig: Adaptive.HostConfig;
	public _cardHostBackground: string;
	private _cardHost: HTMLElement;

    constructor(name: string, styleSheet: string, hostConfig?: string, background?: string) {
        this.name = name;
        this.styleSheet = styleSheet;

        if ( !isNullOrEmpty(hostConfig) ) {
            this._cardHostConfig = new Adaptive.HostConfig(hostConfig);
        } else {
            this._cardHostConfig = new Adaptive.HostConfig(sampleConfiguration);
		}

		if ( !isNullOrEmpty(background) ) {
            this._cardHostBackground = background;
        } else {
            this._cardHostBackground = "#F6F6F6";
		}

        this._cardHost = document.createElement("div");
        this._cardHost.className = "cardHost";
    }

    abstract renderTo(hostElement: HTMLElement);

    public initialize() {
        Adaptive.AdaptiveCard.elementTypeRegistry.reset();
        Adaptive.AdaptiveCard.actionTypeRegistry.reset();

        Adaptive.AdaptiveCard.useMarkdownInRadioButtonAndCheckbox = true;
        Adaptive.AdaptiveCard.useAdvancedCardBottomTruncation = false;
        Adaptive.AdaptiveCard.useAdvancedTextBlockTruncation = true;
    }

    public getBackgroundColor(): string {
        return this._cardHostBackground;
    }

    public parseElement(element: Adaptive.CardElement, json: any) {
        // Do nothing in base implementation
    }

    public anchorClicked(element: Adaptive.CardElement, anchor: HTMLAnchorElement): boolean {
        // Not handled by the host container by default
        return false;
    }

    public getHostConfig(): Adaptive.HostConfig {
        return this._cardHostConfig;
    }
}
