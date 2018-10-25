import * as Adaptive from "adaptivecards";
export declare abstract class HostContainer {
    private _cardHost;
    readonly name: string;
    readonly styleSheet: string;
    constructor(name: string, styleSheet: string);
    abstract renderTo(hostElement: HTMLElement): any;
    initialize(): void;
    getBackgroundColor(): string;
    parseElement(element: Adaptive.CardElement, json: any): void;
    anchorClicked(element: Adaptive.CardElement, anchor: HTMLAnchorElement): boolean;
    getHostConfig(): Adaptive.HostConfig;
    supportsActionBar: boolean;
    readonly cardHost: HTMLElement;
}
