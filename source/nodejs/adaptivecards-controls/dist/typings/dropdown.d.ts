import { Collection } from "./collection";
import { InputWithPopup, PopupControl } from "./inputwithpopup";
export declare class DropDownItem {
    private _element;
    private _value;
    private click;
    readonly key: string;
    onClick: (item: DropDownItem) => void;
    constructor(key: string, value: string);
    toString(): string;
    render(): HTMLElement;
    value: string;
}
export declare class DropDownPopupControl extends PopupControl {
    private _owner;
    private _renderedItems;
    private _selectedIndex;
    constructor(owner: DropDown);
    protected renderContent(): HTMLElement;
    keyDown(e: KeyboardEvent): void;
    render(rootElementBounds: ClientRect): HTMLElement;
    selectedIndex: number;
}
export declare class DropDown extends InputWithPopup<DropDownPopupControl, DropDownItem> {
    private _items;
    private itemClicked;
    protected validateRootElement(rootElement: HTMLElement): void;
    protected createPopupControl(): DropDownPopupControl;
    protected getCssClassName(): string;
    constructor();
    attach(rootElement: HTMLElement): void;
    popup(): void;
    readonly items: Collection<DropDownItem>;
    selectedItem: DropDownItem;
    selectedIndex: number;
}
