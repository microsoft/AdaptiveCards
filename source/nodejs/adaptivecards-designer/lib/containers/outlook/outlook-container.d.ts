import * as Adaptive from "adaptivecards";
import * as Designer from "../../adaptivecards-designer";
export declare class ToggleVisibilityAction extends Adaptive.Action {
    targetElementIds: Array<string>;
    getJsonTypeName(): string;
    execute(): void;
    parse(json: any): void;
}
export declare class OutlookContainer extends Designer.HostContainer {
    renderTo(hostElement: HTMLElement): void;
    initialize(): void;
    private parsePadding;
    parseElement(element: Adaptive.CardElement, json: any): void;
    anchorClicked(element: Adaptive.CardElement, anchor: HTMLAnchorElement): boolean;
    getHostConfig(): Adaptive.HostConfig;
}
