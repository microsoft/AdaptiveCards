import { InputControl } from "./inputcontrol";
export declare class TextBox extends InputControl {
    private _isMultiline;
    private _lineCount;
    private _maxLength;
    private _placeholder;
    private _editBox;
    private editBoxChanged;
    private recreateEditBox;
    private readonly editBox;
    onChange: (sender: TextBox) => void;
    attach(rootElement: HTMLElement): void;
    value: string;
    placeholder: string;
    isMultiline: boolean;
    lineCount: number;
    maxLength: number;
}
