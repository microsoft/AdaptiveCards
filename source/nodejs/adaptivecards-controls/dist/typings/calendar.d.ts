import { InputControl } from "./inputcontrol";
export declare class DayCell {
    private _element;
    private _isSubdued;
    private _isSelected;
    private selected;
    readonly date: Date;
    onSelected: (cell: DayCell) => void;
    constructor(date: Date);
    render(): HTMLElement;
    focus(): void;
    isSubdued: boolean;
    isSelected: boolean;
}
export declare class Calendar extends InputControl {
    private _date;
    private _days;
    private _selectedDay;
    private _rootContainerElement;
    private _miniCalendarElement;
    private _monthYearLabelElement;
    private generateDayCells;
    private selectedDayCell;
    private initializeSelection;
    private rebuildMiniCalendar;
    onDateChanged: (calendar: Calendar) => void;
    constructor();
    attach(rootElement: HTMLElement): void;
    focus(): void;
    date: Date;
}
