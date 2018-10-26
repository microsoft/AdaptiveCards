import { Collection } from "./collection";
import { PopupControl } from "./inputwithpopup";
import { DropDownItem } from "./dropdown";
export declare class PopupMenu extends PopupControl {
    private _overlayElement;
    private _popupControlElement;
    private _isOpen;
    private _items;
    private _renderedItems;
    private _selectedIndex;
    constructor();
    protected renderContent(): HTMLElement;
    keyDown(e: KeyboardEvent): void;
    popup(rootElement: HTMLElement): void;
    closePopup(): void;
    readonly isOpen: boolean;
    readonly items: Collection<DropDownItem>;
    selectedIndex: number;
}
