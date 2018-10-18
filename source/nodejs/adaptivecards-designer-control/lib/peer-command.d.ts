export declare class PeerCommand {
    private _renderedElement;
    protected internalRender(): HTMLElement;
    name: string;
    iconClass: string;
    isPromotable: boolean;
    execute: (command: PeerCommand, clickedElement: HTMLElement) => void;
    constructor(init?: Partial<PeerCommand>);
    render(): HTMLElement;
    readonly renderedElement: HTMLElement;
}
