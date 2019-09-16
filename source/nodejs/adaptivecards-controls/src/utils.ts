// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";

export class CalendarSettings {
    static monthsInYear = 12;
    static daysInWeek = 7;
    static firstDayOfWeek = Enums.DayOfWeek.Sunday;
    static longDayNames = [ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" ];
    static shortDayNames = [ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" ];
    static minimalDayNames = [ "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa" ];
    static longMonthNames = [ "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" ];
    static shortMonthNames = [ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" ];

    static getLongDayName(dayIndex: number) {
        if (dayIndex >= 0 && dayIndex < CalendarSettings.longDayNames.length) {
            return CalendarSettings.longDayNames[dayIndex];
        }

        throw new Error("Day index out of range: " + dayIndex);
    }

    static getShortDayName(dayIndex: number) {
        if (dayIndex >= 0 && dayIndex < CalendarSettings.shortDayNames.length) {
            return CalendarSettings.shortDayNames[dayIndex];
        }

        throw new Error("Day index out of range: " + dayIndex);
    }

    static getInitialDayName(dayIndex: number) {
        if (dayIndex >= 0 && dayIndex < CalendarSettings.minimalDayNames.length) {
            return CalendarSettings.minimalDayNames[dayIndex];
        }

        throw new Error("Day index out of range: " + dayIndex);
    }

    static getLongMonthName(monthIndex: number) {
        if (monthIndex >= 0 && monthIndex < CalendarSettings.longMonthNames.length) {
            return CalendarSettings.longMonthNames[monthIndex];
        }

        throw new Error("Month index out of range: " + monthIndex);
    }

    static getShortMonthName(monthIndex: number) {
        if (monthIndex >= 0 && monthIndex < CalendarSettings.shortMonthNames.length) {
            return CalendarSettings.shortMonthNames[monthIndex];
        }

        throw new Error("Month index out of range: " + monthIndex);
    }
}

export function daysInMonth(year: number, month: number) {
    switch (month) {
        case 1:
            return (year % 4 == 0 && year % 100) || year % 400 == 0 ? 29 : 28;
        case 3:
        case 5:
        case 8:
        case 10:
            return 30;
        default:
            return 31
    }
}

export function addDays(date: Date, days: number): Date {
    var result = new Date(date.getTime());

    result.setDate(result.getDate() + days);

    return result;
}

export function addMonths(date: Date, months: number): Date {
    var result = new Date(date.getTime());
    var newMonth = result.getMonth() + months;

    result.setMonth(newMonth);

    // We want to maintain the same day-of-month, but that may not be possible if the new month doesn't have enough days.
    // Loop until we back up to a day the new month has.
    // (Weird modulo math is due to Javascript's treatment of negative numbers in modulo)
    if (result.getMonth() !== ((newMonth % CalendarSettings.monthsInYear) + CalendarSettings.monthsInYear) % CalendarSettings.monthsInYear) {
        result = addDays(result, -result.getDate());
    }

    return result;
}

export function areDatesEqual(date1: Date, date2: Date): boolean {
    return date1.getFullYear() == date2.getFullYear() &&
           date1.getMonth() == date2.getMonth() &&
           date1.getDate() == date2.getDate();
}

export function getScrollX(): number {
    return window.pageXOffset;
}

export function getScrollY(): number {
    return window.pageYOffset;
}

export function getAttributeValueAsBool(element: HTMLElement, attributeName: string, defaultValue: boolean) {
    var attribute = element.attributes[attributeName];

    if (attribute) {
        return attribute.value === "true";
    }

    return defaultValue;
}

export function getAttributeValueAsString(element: HTMLElement, attributeName: string, defaultValue: string) {
    var attribute = element.attributes[attributeName];

    if (attribute) {
        return attribute.value;
    }

    return defaultValue;
}

export function getAttributeValueAsInt(element: HTMLElement, attributeName: string, defaultValue: number) {
    var attribute = element.attributes[attributeName];

    if (attribute) {
        var n = parseInt(attribute.value);

        if (!isNaN(n)) {
            return n;
        }
    }

    return defaultValue;
}
