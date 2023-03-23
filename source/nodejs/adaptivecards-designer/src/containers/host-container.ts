// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { GlobalSettings, GlobalRegistry, CardObjectRegistry, CardElement, Action, HostConfig, SerializationContext, Version, Versions } from "adaptivecards";
import * as hostConfig from "../hostConfigs/sample.json";

export enum ColorTheme {
    Light = "Light",
    Dark = "Dark"
};

export abstract class HostContainer {
    private _cardHost: HTMLElement;
    private _elementsRegistry = new CardObjectRegistry<CardElement>();
    private _actionsRegistry = new CardObjectRegistry<Action>();

    readonly name: string;

    constructor(name: string) {
        this.name = name;

        this._cardHost = document.createElement("div");
        this._cardHost.className = "cardHost";

        GlobalRegistry.populateWithDefaultElements(this._elementsRegistry);
        GlobalRegistry.populateWithDefaultActions(this._actionsRegistry);
    }

    abstract renderTo(hostElement: HTMLElement);
    
    abstract getCurrentStyleSheet(): string;

    public initialize() {
        GlobalSettings.useMarkdownInRadioButtonAndCheckbox = true;
        GlobalSettings.useAdvancedCardBottomTruncation = false;
        GlobalSettings.useAdvancedTextBlockTruncation = true;
    }

    public createSerializationContext(targetVersion: Version): SerializationContext {
        let context = new SerializationContext(targetVersion);
        context.setElementRegistry(this.elementsRegistry);
        context.setActionRegistry(this.actionsRegistry);

        return context;
    }

    public getBackgroundColor(): string {
        return "#F6F6F6";
    }

    public parseElement(element: CardElement, source: any, context: SerializationContext) {
        // Do nothing in base implementation
    }

    public anchorClicked(element: CardElement, anchor: HTMLAnchorElement): boolean {
        // Not handled by the host container by default
        return false;
    }

    public getHostConfig(): HostConfig {
        return new HostConfig(hostConfig);
    }

    public requiresOverflowStyling(): boolean {
        // By default, overflow styling is not handled
        return false;
    }

    public adjustStyleForBackground(): void {
        // By default, we make no adjustments
        return;
    }

    supportsActionBar: boolean = false;

    get cardHost(): HTMLElement {
        return this._cardHost;
    }

    get isFixedHeight(): boolean {
        return false;
    }

    get elementsRegistry(): CardObjectRegistry<CardElement> {
        return this._elementsRegistry;
    }

    get actionsRegistry(): CardObjectRegistry<Action> {
        return this._actionsRegistry;
    }

    get targetVersion(): Version {
        return Versions.v1_0;
    }

    get enableDeviceEmulation(): boolean {
        return false;
    }

    get supportsMultipleSizes(): boolean {
        // By default, we do not support different container sizes
        return false;
    }

    // if various containers support different themes in the future, we can override this method
    static get supportedContainerThemes(): string[] {
        return Object.values(ColorTheme);
    }

    get supportsMultipleThemes(): boolean {
        // By default, we do not support different color themes
        return false;
    }

    set colorTheme(value: ColorTheme) {
        // Not handled by the host container by default
    }
}
