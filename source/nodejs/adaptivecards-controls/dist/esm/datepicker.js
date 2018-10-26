import { InputWithPopup, PopupControl } from "./inputwithpopup";
import { Calendar } from "./calendar";
export class CalendarPopupControl extends PopupControl {
    constructor(owner) {
        super();
        this._owner = owner;
    }
    renderContent() {
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
export class DatePicker extends InputWithPopup {
    validateRootElement(rootElement) {
        if (!(rootElement instanceof HTMLDivElement)) {
            throw new Error("DatePicker requires a DIV element as its root.");
        }
    }
    createPopupControl() {
        return new CalendarPopupControl(this);
    }
    getValueAsString() {
        return this.value.toLocaleDateString();
    }
    getCssClassName() {
        return "ms-ctrl ms-ctrl-datePicker";
    }
    getButtonIconCssClassName() {
        return "ms-icon-calendar";
    }
    popup() {
        super.popup();
        if (this.isOpen) {
            this.popupControl.focus();
        }
    }
}
//# sourceMappingURL=datepicker.js.map