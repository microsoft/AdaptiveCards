// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { InputWithPopup, PopupControl } from "./inputwithpopup";
import { Calendar } from "./calendar";

export class CalendarPopupControl extends PopupControl {
    private _owner: DatePicker;
    private _calendar: Calendar;

    constructor(owner: DatePicker) {
        super();

        this._owner = owner;
    }

    protected renderContent(): HTMLElement {
        var element = document.createElement("div");
        element.className = "ms-ctrl ms-calendarPopup";

        this._calendar = new Calendar();
        this._calendar.date = this._owner.value;
        this._calendar.onDateChanged = (c) => {
            this._owner.value = c.date;

            this.close();
        };
        this._calendar.attach(element);

        return element;
    }

    focus() {
        if (this._calendar) {
            this._calendar.focus();
        }
    }
}

export class DatePicker extends InputWithPopup<CalendarPopupControl, Date> {
    protected validateRootElement(rootElement: HTMLElement) {
        if (!(rootElement instanceof HTMLDivElement)) {
            throw new Error("DatePicker requires a DIV element as its root.");
        }
    }

    protected createPopupControl(): CalendarPopupControl {
        return new CalendarPopupControl(this);
    }

    protected getValueAsString(): string {
        return this.value.toLocaleDateString();
    }

    protected getCssClassName(): string {
        return "ms-ctrl ms-ctrl-datePicker";
    }

    protected getButtonIconCssClassName(): string {
        return "ms-icon-calendar";
    }

    popup() {
        super.popup();

        if (this.isOpen) {
            this.popupControl.focus();
        }
    }
}
