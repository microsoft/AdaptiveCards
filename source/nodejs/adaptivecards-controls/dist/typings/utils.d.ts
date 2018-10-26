import * as Enums from "./enums";
export declare class CalendarSettings {
    static monthsInYear: number;
    static daysInWeek: number;
    static firstDayOfWeek: Enums.DayOfWeek;
    static longDayNames: string[];
    static shortDayNames: string[];
    static minimalDayNames: string[];
    static longMonthNames: string[];
    static shortMonthNames: string[];
    static getLongDayName(dayIndex: number): string;
    static getShortDayName(dayIndex: number): string;
    static getInitialDayName(dayIndex: number): string;
    static getLongMonthName(monthIndex: number): string;
    static getShortMonthName(monthIndex: number): string;
}
export declare function daysInMonth(year: number, month: number): 29 | 28 | 30 | 31;
export declare function addDays(date: Date, days: number): Date;
export declare function addMonths(date: Date, months: number): Date;
export declare function areDatesEqual(date1: Date, date2: Date): boolean;
export declare function getScrollX(): number;
export declare function getScrollY(): number;
export declare function getAttributeValueAsBool(element: HTMLElement, attributeName: string, defaultValue: boolean): boolean;
export declare function getAttributeValueAsString(element: HTMLElement, attributeName: string, defaultValue: string): any;
export declare function getAttributeValueAsInt(element: HTMLElement, attributeName: string, defaultValue: number): number;
