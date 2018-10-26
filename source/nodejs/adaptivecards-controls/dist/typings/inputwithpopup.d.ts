import { InputControl } from "./inputcontrol";
export declare abstract class PopupControl {
    private _popupElement;
    protected abstract renderContent(): HTMLElement;
    protected close(): void;
    onClose: (popupControl: PopupControl) => void;
    keyDown(e: KeyboardEvent): void;
    render(rootElementBounds: ClientRect): HTMLElement;
    focus(): void;
}
export declare abstract class InputWithPopup<TPopupControl extends PopupControl, TValue> extends InputControl {
    private _isOpen;
    private _labelElement;
    private _dropDownButtonElement;
    private _overlayElement;
    private _popupControl;
    private _popupControlElement;
    private _placeholderText;
    private _value;
    protected keyDown(e: KeyboardEvent): void;
    private updateLabel;
    protected readonly popupControl: TPopupControl;
    protected abstract createPopupControl(): TPopupControl;
    protected abstract getCssClassName(): string;
    protected getButtonIconCssClassName(): string;
    protected getValueAsString(): string;
    protected valueChanged(): void;
    onValueChanged: (sender: InputControl) => void;
    attach(rootElement: HTMLElement): void;
    popup(): void;
    closePopup(): void;
    readonly isOpen: boolean;
    placeholderText: string;
    value: TValue;
}
