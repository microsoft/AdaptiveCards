import { InputWithPopup, PopupControl } from "./inputwithpopup";
export declare class CalendarPopupControl extends PopupControl {
    private _owner;
    private _calendar;
    constructor(owner: DatePicker);
    protected renderContent(): HTMLElement;
    focus(): void;
}
export declare class DatePicker extends InputWithPopup<CalendarPopupControl, Date> {
    protected validateRootElement(rootElement: HTMLElement): void;
    protected createPopupControl(): CalendarPopupControl;
    protected getValueAsString(): string;
    protected getCssClassName(): string;
    protected getButtonIconCssClassName(): string;
    popup(): void;
}
