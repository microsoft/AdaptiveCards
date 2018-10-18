export declare enum SidePaneOrientation {
    Horizontal = 0,
    Vertical = 1
}
export declare class SidePane {
    private _headerRootElement;
    private _headerContentElement;
    private _headerTitleElement;
    private _headerIconElement;
    private _headerStatusTextElement;
    private _isExpanded;
    private _content;
    private getDimensionSettingName;
    private updateLayout;
    private toggled;
    readonly attachedTo: HTMLElement;
    readonly id: string;
    readonly title: string;
    readonly targetElementSelector: string;
    readonly collapsedTabContainer: HTMLElement;
    readonly orientation: SidePaneOrientation;
    onToggled: (sender: SidePane) => void;
    constructor(attachedTo: HTMLElement, collapsedTabContainer: HTMLElement, id: string, title: string, targetElementSelector: string, orientation?: SidePaneOrientation);
    collapse(): void;
    expand(): void;
    toggle(): void;
    getHeaderBoundingRect(): ClientRect;
    saveState(): void;
    content: HTMLElement;
    readonly isExpanded: boolean;
}
