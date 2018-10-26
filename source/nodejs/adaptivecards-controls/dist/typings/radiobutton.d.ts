import { InputControl } from "./inputcontrol";
export declare class RadioButton extends InputControl {
    private static creationIndex;
    private static createId;
    private _label;
    private _isChecked;
    private _checkboxElement;
    private _spanElement;
    private changed;
    protected keyDown(e: KeyboardEvent): void;
    onChange: (sender: RadioButton) => void;
    attach(rootElement: HTMLElement): void;
    label: string;
    isChecked: boolean;
}
