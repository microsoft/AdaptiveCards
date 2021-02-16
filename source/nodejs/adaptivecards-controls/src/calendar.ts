// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Utils from "./utils";
import { Constants } from "./constants";
import * as Enums from "./enums";
import { InputControl } from "./inputcontrol";

export class DayCell {
    private _element: HTMLElement;
    private _isSubdued: boolean = false;
    private _isSelected: boolean = false;

    private selected() {
        if (this.onSelected) {
            this.onSelected(this);
        }
    }

    readonly date: Date;

    onSelected: (cell: DayCell) => void;

    constructor(date: Date) {
        this.date = date;
    }

    render(): HTMLElement {
        this._element = document.createElement("div");
        this._element.className = "ms-ctrl ms-ctrl-calendarDay";
        this._element.innerText = this.date.getDate().toString();
        this._element.tabIndex = 0;
        this._element.onclick = (e) => { this.selected(); };
        this._element.onkeydown = (e) => {
            if (e.key == Constants.keys.enter) {
                this.selected();
                return false;
            }
        };

        return this._element;
    }

    focus() {
        this._element.focus();
    }

    get isSubdued(): boolean {
        return this._isSubdued;
    }

    set isSubdued(value: boolean) {
        this._isSubdued = value;

        if (this._isSubdued) {
            this._element.classList.add("subdued");
        }
        else {
            this._element.classList.remove("subdued");
        }
    }

    get isSelected(): boolean {
        return this._isSelected;
    }

    set isSelected(value: boolean) {
        this._isSelected = value;

        if (this._isSelected) {
            this._element.classList.add("selected");
        }
        else {
            this._element.classList.remove("selected");
        }
    }
}

export class Calendar extends InputControl {
    private _date: Date;
    private _days: Array<DayCell>;
    private _selectedDay: DayCell = null;
    private _rootContainerElement: HTMLElement;
    private _miniCalendarElement: HTMLTableElement;
    private _monthYearLabelElement: HTMLElement;

    private generateDayCells(baseDate: Date) {
        this._days = [];

        var inputMonth = baseDate.getMonth();
        var inputYear = baseDate.getFullYear();

        var start = new Date(inputYear, inputMonth, 1);
        var end = new Date(inputYear, inputMonth, Utils.daysInMonth(inputYear, inputMonth));

        var startDateDayOfWeek = start.getDay();

        if ((startDateDayOfWeek - Utils.CalendarSettings.firstDayOfWeek) > 0) {
            start = Utils.addDays(start, Utils.CalendarSettings.firstDayOfWeek - startDateDayOfWeek);
        }

        var endDateDayOfWeek = end.getDay();
        var lastDayOfWeek = Utils.CalendarSettings.firstDayOfWeek + 6;

        if ((lastDayOfWeek - endDateDayOfWeek) > 0) {
            end = Utils.addDays(end, lastDayOfWeek - endDateDayOfWeek);
        }

        var endDate = end.getDate();
        var endMonth = end.getMonth();
        var endYear = end.getFullYear();

        do {
            var dayCell = new DayCell(start);

            dayCell.onSelected = (clickedCell) => {
                this.selectedDayCell = clickedCell;

                if (this.onDateChanged) {
                    this.onDateChanged(this);
                }
            }

            this._days.push(dayCell);

            var done = start.getDate() == endDate && start.getMonth() == endMonth && start.getFullYear() == endYear;

            start = Utils.addDays(start, 1);
        } while (!done);
    }

    private get selectedDayCell(): DayCell {
        return this._selectedDay;
    }

    private set selectedDayCell(value: DayCell) {
        if (this._selectedDay) {
            this._selectedDay.isSelected = false;
        }

        this._selectedDay = value;

        if (this._selectedDay) {
            this._selectedDay.isSelected = true;
            this._date = this._selectedDay.date;
        }
    }

    private initializeSelection() {
        if (this._date) {
            for (var i = 0; i < this._days.length; i++) {
                if (Utils.areDatesEqual(this._days[i].date, this.date)) {
                    this.selectedDayCell = this._days[i];

                    break;
                }
            }
        }
    }

    private rebuildMiniCalendar(newDate: Date, oldDate: Date) {
        this.generateDayCells(newDate);

        var month = newDate.getMonth();

        this._miniCalendarElement.innerHTML = "";

        this._miniCalendarElement.classList.remove(
            "ms-ctrl-slide",
            "ms-ctrl-slideLeftToRight",
            "ms-ctrl-slideRightToLeft");

        var row = document.createElement("tr");

        var dayIndex = <number>Utils.CalendarSettings.firstDayOfWeek;

        for (var i = 0; i < Utils.CalendarSettings.daysInWeek; i++) {
            var cell = document.createElement("td");
            cell.className = "ms-ctrl ms-ctrl-calendarDayHeader";
            cell.innerText = Utils.CalendarSettings.getInitialDayName(dayIndex);

            row.appendChild(cell);

            dayIndex++;

            if (dayIndex >= Utils.CalendarSettings.daysInWeek) {
                dayIndex = 0;
            }
        }

        this._miniCalendarElement.appendChild(row);

        for (var i = 0; i < this._days.length; i++) {
            if (i % 7 == 0) {
                row = document.createElement("tr");
                this._miniCalendarElement.appendChild(row);
            }

            var tableCell = document.createElement("td");
            tableCell.appendChild(this._days[i].render());

            if (this._days[i].date.getMonth() != month) {
                this._days[i].isSubdued = true;
            }

            row.appendChild(tableCell);
        }

        if (oldDate) {
            var timeDelta = newDate.getTime() - oldDate.getTime();

            if (timeDelta > 0) {
                this._miniCalendarElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideRightToLeft");
            }
            else if (timeDelta < 0) {
                this._miniCalendarElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideLeftToRight");
            }
        }
    }

    onDateChanged: (calendar: Calendar) => void;

    constructor() {
        super();

        this._miniCalendarElement = document.createElement("table");
        this._miniCalendarElement.className = "ms-ctrl ms-ctrl-slide";
        this._miniCalendarElement.cellPadding = "0px";
        this._miniCalendarElement.cellSpacing = "0px";

        var miniCalendarHeader = document.createElement("div");
        miniCalendarHeader.className = "ms-ctrl ms-ctrl-calendarHeader";
        miniCalendarHeader.style.display = "flex";

        this._monthYearLabelElement = document.createElement("div");
        this._monthYearLabelElement.style.flex = "1 1 100%";

        miniCalendarHeader.appendChild(this._monthYearLabelElement);

        var navButtons = document.createElement("div");
        navButtons.style.flex = "0 0 auto";

        var button = document.createElement("i");
        button.className = "ms-icon ms-ctrl-calendarNavButton ms-icon-chevronLeft";
        button.tabIndex = 0;
        button.onclick = (e) => {
            this.date = Utils.addMonths(this.date, -1);
        };
        button.onkeydown = (e) => {
            if (e.key == Constants.keys.enter) {
                this.date = Utils.addMonths(this.date, -1);
                return false;
            }
        };

        navButtons.appendChild(button);

        button = document.createElement("i");
        button.className = "ms-icon ms-ctrl-calendarNavButton ms-icon-chevronRight";
        button.tabIndex = 0;
        button.onclick = (e) => {
            this.date = Utils.addMonths(this.date, 1);
        };
        button.onkeydown = (e) => {
            if (e.key == Constants.keys.enter) {
                this.date = Utils.addMonths(this.date, 1);
                return false;
            }
        };

        navButtons.appendChild(button);

        miniCalendarHeader.appendChild(navButtons);

        this._rootContainerElement = document.createElement("div");
        this._rootContainerElement.className = "ms-ctrl ms-ctrl-calendar";
        this._rootContainerElement.appendChild(miniCalendarHeader);
        this._rootContainerElement.appendChild(this._miniCalendarElement);

        this.date = new Date();
    }

    attach(rootElement: HTMLElement) {
        super.attach(rootElement);

        rootElement.innerHTML = "";
        rootElement.appendChild(this._rootContainerElement);
    }

    focus() {
        if (this._selectedDay) {
            this._selectedDay.focus();
        }
    }

    get date(): Date {
        return this._date;
    }

    set date(value: Date) {
        var rebuildNeeded = true;
        var timeDelta = 0;

        var newDate = value ? value : new Date();

        if (this._date) {
            rebuildNeeded = !this._days || newDate.getFullYear() != this._date.getFullYear() || newDate.getMonth() != this._date.getMonth();
        }

        if (rebuildNeeded) {
            this.rebuildMiniCalendar(newDate, this._date);
        }

        this._date = newDate;

        this.initializeSelection();

        this._monthYearLabelElement.innerText = Utils.CalendarSettings.getLongMonthName(this._date.getMonth()) + " " + this._date.getFullYear();
    }
}
