export declare abstract class ToolbarElement {
    private _renderedElement;
    protected abstract internalRender(): HTMLElement;
    protected internalUpdateLayout(): void;
    updateLayout(): void;
    render(): HTMLElement;
    readonly renderedElement: HTMLElement;
}
export declare class ToolbarSeparator extends ToolbarElement {
    protected internalRender(): HTMLElement;
}
export declare class ToolbarLabel extends ToolbarElement {
    private _text;
    protected internalUpdateLayout(): void;
    protected internalRender(): HTMLElement;
    constructor(text: string);
    text: string;
}
export declare class ToolbarButton extends ToolbarElement {
    private _caption;
    private _displayCaption;
    private _iconClass;
    private _toolTip;
    private _isEnabled;
    protected clicked(): void;
    protected internalUpdateLayout(): void;
    protected internalRender(): HTMLElement;
    onClick: (sender: ToolbarButton) => void;
    constructor(caption: string, iconClass: string, onClick?: (sender: ToolbarButton) => void);
    caption: string;
    displayCaption: boolean;
    iconClass: string;
    toolTip: string;
    isEnabled: boolean;
}
export interface IChoicePickerItem {
    name: string;
    value: string;
}
export declare class ToolbarChoicePicker extends ToolbarElement {
    private _dropDown;
    protected internalRender(): HTMLElement;
    onChanged: (sender: ToolbarChoicePicker) => void;
    choices: Array<IChoicePickerItem>;
    readonly value: string;
}
export declare class Toolbar {
    private _elements;
    private _attachedTo;
    attachTo(element: HTMLElement): void;
    addElement(element: ToolbarElement): void;
}
