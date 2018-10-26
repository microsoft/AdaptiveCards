import { InputControl } from "./inputcontrol";
export declare class CheckBox extends InputControl {
    private static creationIndex;
    private static createId;
    private _label;
    private _isChecked;
    private _checkboxElement;
    private _spanElement;
    private changed;
    protected keyDown(e: KeyboardEvent): void;
    onChange: (sender: CheckBox) => void;
    attach(rootElement: HTMLElement): void;
    label: string;
    isChecked: boolean;
}
