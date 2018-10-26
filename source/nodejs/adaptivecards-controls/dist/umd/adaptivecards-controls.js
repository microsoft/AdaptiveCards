(function webpackUniversalModuleDefinition(root, factory) {
	if(typeof exports === 'object' && typeof module === 'object')
		module.exports = factory();
	else if(typeof define === 'function' && define.amd)
		define("ACControls", [], factory);
	else if(typeof exports === 'object')
		exports["ACControls"] = factory();
	else
		root["ACControls"] = factory();
})(this, function() {
return /******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, { enumerable: true, get: getter });
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 			Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 		}
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// create a fake namespace object
/******/ 	// mode & 1: value is a module id, require it
/******/ 	// mode & 2: merge all properties of value into the ns
/******/ 	// mode & 4: return value when already ns object
/******/ 	// mode & 8|1: behave like require
/******/ 	__webpack_require__.t = function(value, mode) {
/******/ 		if(mode & 1) value = __webpack_require__(value);
/******/ 		if(mode & 8) return value;
/******/ 		if((mode & 4) && typeof value === 'object' && value && value.__esModule) return value;
/******/ 		var ns = Object.create(null);
/******/ 		__webpack_require__.r(ns);
/******/ 		Object.defineProperty(ns, 'default', { enumerable: true, value: value });
/******/ 		if(mode & 2 && typeof value != 'string') for(var key in value) __webpack_require__.d(ns, key, function(key) { return value[key]; }.bind(null, key));
/******/ 		return ns;
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "/dist/";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = "./dist/esm/index.js");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./dist/esm/adaptivecards-controls.css":
/*!*********************************************!*\
  !*** ./dist/esm/adaptivecards-controls.css ***!
  \*********************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {


var content = __webpack_require__(/*! !../../node_modules/mini-css-extract-plugin/dist/loader.js!../../node_modules/css-loader!./adaptivecards-controls.css */ "./node_modules/mini-css-extract-plugin/dist/loader.js!./node_modules/css-loader/index.js!./dist/esm/adaptivecards-controls.css");

if(typeof content === 'string') content = [[module.i, content, '']];

var transform;
var insertInto;



var options = {"hmr":true}

options.transform = transform
options.insertInto = undefined;

var update = __webpack_require__(/*! ../../node_modules/style-loader/lib/addStyles.js */ "./node_modules/style-loader/lib/addStyles.js")(content, options);

if(content.locals) module.exports = content.locals;

if(false) {}

/***/ }),

/***/ "./dist/esm/calendar.js":
/*!******************************!*\
  !*** ./dist/esm/calendar.js ***!
  \******************************/
/*! exports provided: DayCell, Calendar */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "DayCell", function() { return DayCell; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "Calendar", function() { return Calendar; });
/* harmony import */ var _utils__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./utils */ "./dist/esm/utils.js");
/* harmony import */ var _constants__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./constants */ "./dist/esm/constants.js");
/* harmony import */ var _inputcontrol__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./inputcontrol */ "./dist/esm/inputcontrol.js");



class DayCell {
    constructor(date) {
        this._isSubdued = false;
        this._isSelected = false;
        this.date = date;
    }
    selected() {
        if (this.onSelected) {
            this.onSelected(this);
        }
    }
    render() {
        this._element = document.createElement("div");
        this._element.className = "ms-ctrl ms-ctrl-calendarDay";
        this._element.innerText = this.date.getDate().toString();
        this._element.tabIndex = 0;
        this._element.onclick = (e) => { this.selected(); };
        this._element.onkeydown = (e) => {
            if (e.keyCode == _constants__WEBPACK_IMPORTED_MODULE_1__["KEY_ENTER"]) {
                this.selected();
                return false;
            }
        };
        return this._element;
    }
    focus() {
        this._element.focus();
    }
    get isSubdued() {
        return this._isSubdued;
    }
    set isSubdued(value) {
        this._isSubdued = value;
        if (this._isSubdued) {
            this._element.classList.add("subdued");
        }
        else {
            this._element.classList.remove("subdued");
        }
    }
    get isSelected() {
        return this._isSelected;
    }
    set isSelected(value) {
        this._isSelected = value;
        if (this._isSelected) {
            this._element.classList.add("selected");
        }
        else {
            this._element.classList.remove("selected");
        }
    }
}
class Calendar extends _inputcontrol__WEBPACK_IMPORTED_MODULE_2__["InputControl"] {
    constructor() {
        super();
        this._selectedDay = null;
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
            this.date = _utils__WEBPACK_IMPORTED_MODULE_0__["addMonths"](this.date, -1);
        };
        button.onkeydown = (e) => {
            if (e.keyCode == _constants__WEBPACK_IMPORTED_MODULE_1__["KEY_ENTER"]) {
                this.date = _utils__WEBPACK_IMPORTED_MODULE_0__["addMonths"](this.date, -1);
                return false;
            }
        };
        navButtons.appendChild(button);
        button = document.createElement("i");
        button.className = "ms-icon ms-ctrl-calendarNavButton ms-icon-chevronRight";
        button.tabIndex = 0;
        button.onclick = (e) => {
            this.date = _utils__WEBPACK_IMPORTED_MODULE_0__["addMonths"](this.date, 1);
        };
        button.onkeydown = (e) => {
            if (e.keyCode == _constants__WEBPACK_IMPORTED_MODULE_1__["KEY_ENTER"]) {
                this.date = _utils__WEBPACK_IMPORTED_MODULE_0__["addMonths"](this.date, 1);
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
    generateDayCells(baseDate) {
        this._days = [];
        var inputMonth = baseDate.getMonth();
        var inputYear = baseDate.getFullYear();
        var start = new Date(inputYear, inputMonth, 1);
        var end = new Date(inputYear, inputMonth, _utils__WEBPACK_IMPORTED_MODULE_0__["daysInMonth"](inputYear, inputMonth));
        var startDateDayOfWeek = start.getDay();
        if ((startDateDayOfWeek - _utils__WEBPACK_IMPORTED_MODULE_0__["CalendarSettings"].firstDayOfWeek) > 0) {
            start = _utils__WEBPACK_IMPORTED_MODULE_0__["addDays"](start, _utils__WEBPACK_IMPORTED_MODULE_0__["CalendarSettings"].firstDayOfWeek - startDateDayOfWeek);
        }
        var endDateDayOfWeek = end.getDay();
        var lastDayOfWeek = _utils__WEBPACK_IMPORTED_MODULE_0__["CalendarSettings"].firstDayOfWeek + 6;
        if ((lastDayOfWeek - endDateDayOfWeek) > 0) {
            end = _utils__WEBPACK_IMPORTED_MODULE_0__["addDays"](end, lastDayOfWeek - endDateDayOfWeek);
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
            };
            this._days.push(dayCell);
            var done = start.getDate() == endDate && start.getMonth() == endMonth && start.getFullYear() == endYear;
            start = _utils__WEBPACK_IMPORTED_MODULE_0__["addDays"](start, 1);
        } while (!done);
    }
    get selectedDayCell() {
        return this._selectedDay;
    }
    set selectedDayCell(value) {
        if (this._selectedDay) {
            this._selectedDay.isSelected = false;
        }
        this._selectedDay = value;
        if (this._selectedDay) {
            this._selectedDay.isSelected = true;
            this._date = this._selectedDay.date;
        }
    }
    initializeSelection() {
        if (this._date) {
            for (var i = 0; i < this._days.length; i++) {
                if (_utils__WEBPACK_IMPORTED_MODULE_0__["areDatesEqual"](this._days[i].date, this.date)) {
                    this.selectedDayCell = this._days[i];
                    break;
                }
            }
        }
    }
    rebuildMiniCalendar(newDate, oldDate) {
        this.generateDayCells(newDate);
        var month = newDate.getMonth();
        this._miniCalendarElement.innerHTML = "";
        this._miniCalendarElement.classList.remove("ms-ctrl-slide", "ms-ctrl-slideLeftToRight", "ms-ctrl-slideRightToLeft");
        var row = document.createElement("tr");
        var dayIndex = _utils__WEBPACK_IMPORTED_MODULE_0__["CalendarSettings"].firstDayOfWeek;
        for (var i = 0; i < _utils__WEBPACK_IMPORTED_MODULE_0__["CalendarSettings"].daysInWeek; i++) {
            var cell = document.createElement("td");
            cell.className = "ms-ctrl ms-ctrl-calendarDayHeader";
            cell.innerText = _utils__WEBPACK_IMPORTED_MODULE_0__["CalendarSettings"].getInitialDayName(dayIndex);
            row.appendChild(cell);
            dayIndex++;
            if (dayIndex >= _utils__WEBPACK_IMPORTED_MODULE_0__["CalendarSettings"].daysInWeek) {
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
    attach(rootElement) {
        super.attach(rootElement);
        rootElement.innerHTML = "";
        rootElement.appendChild(this._rootContainerElement);
    }
    focus() {
        if (this._selectedDay) {
            this._selectedDay.focus();
        }
    }
    get date() {
        return this._date;
    }
    set date(value) {
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
        this._monthYearLabelElement.innerText = _utils__WEBPACK_IMPORTED_MODULE_0__["CalendarSettings"].getLongMonthName(this._date.getMonth()) + " " + this._date.getFullYear();
    }
}
//# sourceMappingURL=calendar.js.map

/***/ }),

/***/ "./dist/esm/checkbox.js":
/*!******************************!*\
  !*** ./dist/esm/checkbox.js ***!
  \******************************/
/*! exports provided: CheckBox */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "CheckBox", function() { return CheckBox; });
/* harmony import */ var _constants__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./constants */ "./dist/esm/constants.js");
/* harmony import */ var _inputcontrol__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./inputcontrol */ "./dist/esm/inputcontrol.js");


class CheckBox extends _inputcontrol__WEBPACK_IMPORTED_MODULE_1__["InputControl"] {
    constructor() {
        super(...arguments);
        this._label = "";
        this._checkboxElement = null;
        this._spanElement = null;
    }
    static createId() {
        var result = CheckBox.creationIndex;
        CheckBox.creationIndex++;
        return result;
    }
    changed() {
        if (this.onChange) {
            this.onChange(this);
        }
    }
    keyDown(e) {
        switch (e.keyCode) {
            case _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_ENTER"]:
                this.isChecked = !this.isChecked;
                break;
        }
    }
    attach(rootElement) {
        super.attach(rootElement);
        rootElement.className = "ms-ctrl ms-ctrl-checkbox";
        rootElement.tabIndex = 0;
        var labelAttribute = rootElement.attributes["label"];
        if (labelAttribute) {
            this._label = labelAttribute.value;
        }
        var isCheckedAttribute = rootElement.attributes["ischecked"];
        if (isCheckedAttribute) {
            this._isChecked = isCheckedAttribute.value === "true";
        }
        this._checkboxElement = document.createElement("input");
        this._checkboxElement.id = "ms-ctrl-checkbox-" + CheckBox.createId();
        this._checkboxElement.type = "checkbox";
        this._checkboxElement.style.position = "absolute";
        this._checkboxElement.checked = this.isChecked;
        this._checkboxElement.onchange = (e) => { this.changed(); };
        var labelElement = document.createElement("label");
        labelElement.htmlFor = this._checkboxElement.id;
        this._spanElement = document.createElement("span");
        this._spanElement.innerText = this._label;
        labelElement.appendChild(this._spanElement);
        rootElement.innerHTML = "";
        rootElement.appendChild(this._checkboxElement);
        rootElement.appendChild(labelElement);
    }
    get label() {
        return this._label;
    }
    set label(value) {
        this._label = value;
        if (this._spanElement) {
            this._spanElement.innerText = this._label;
        }
    }
    get isChecked() {
        return this._isChecked;
    }
    set isChecked(value) {
        if (this._isChecked != value) {
            this._isChecked = value;
            if (this._checkboxElement) {
                this._checkboxElement.checked = this._isChecked;
            }
            this.changed();
        }
    }
}
// Used to generate unique Ids
CheckBox.creationIndex = 0;
//# sourceMappingURL=checkbox.js.map

/***/ }),

/***/ "./dist/esm/collection.js":
/*!********************************!*\
  !*** ./dist/esm/collection.js ***!
  \********************************/
/*! exports provided: Collection */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "Collection", function() { return Collection; });
class Collection {
    constructor() {
        this._items = [];
        this.onItemAdded = null;
        this.onItemRemoved = null;
    }
    get(index) {
        return this._items[index];
    }
    add(item) {
        this._items.push(item);
        if (this.onItemAdded) {
            this.onItemAdded(item);
        }
    }
    remove(item) {
        var i = this._items.indexOf(item);
        if (i >= 0) {
            this._items = this._items.splice(i, 1);
            if (this.onItemRemoved) {
                this.onItemRemoved(item);
            }
        }
    }
    indexOf(item) {
        return this._items.indexOf(item);
    }
    get length() {
        return this._items.length;
    }
}
//# sourceMappingURL=collection.js.map

/***/ }),

/***/ "./dist/esm/constants.js":
/*!*******************************!*\
  !*** ./dist/esm/constants.js ***!
  \*******************************/
/*! exports provided: KEY_TAB, KEY_ENTER, KEY_ESCAPE, KEY_UP, KEY_DOWN, KEY_DELETE */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "KEY_TAB", function() { return KEY_TAB; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "KEY_ENTER", function() { return KEY_ENTER; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "KEY_ESCAPE", function() { return KEY_ESCAPE; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "KEY_UP", function() { return KEY_UP; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "KEY_DOWN", function() { return KEY_DOWN; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "KEY_DELETE", function() { return KEY_DELETE; });
const KEY_TAB = 9;
const KEY_ENTER = 13;
const KEY_ESCAPE = 27;
const KEY_UP = 38;
const KEY_DOWN = 40;
const KEY_DELETE = 46;
//# sourceMappingURL=constants.js.map

/***/ }),

/***/ "./dist/esm/datepicker.js":
/*!********************************!*\
  !*** ./dist/esm/datepicker.js ***!
  \********************************/
/*! exports provided: CalendarPopupControl, DatePicker */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "CalendarPopupControl", function() { return CalendarPopupControl; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "DatePicker", function() { return DatePicker; });
/* harmony import */ var _inputwithpopup__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./inputwithpopup */ "./dist/esm/inputwithpopup.js");
/* harmony import */ var _calendar__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./calendar */ "./dist/esm/calendar.js");


class CalendarPopupControl extends _inputwithpopup__WEBPACK_IMPORTED_MODULE_0__["PopupControl"] {
    constructor(owner) {
        super();
        this._owner = owner;
    }
    renderContent() {
        var element = document.createElement("div");
        element.className = "ms-ctrl ms-calendarPopup";
        this._calendar = new _calendar__WEBPACK_IMPORTED_MODULE_1__["Calendar"]();
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
class DatePicker extends _inputwithpopup__WEBPACK_IMPORTED_MODULE_0__["InputWithPopup"] {
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

/***/ }),

/***/ "./dist/esm/dropdown.js":
/*!******************************!*\
  !*** ./dist/esm/dropdown.js ***!
  \******************************/
/*! exports provided: DropDownItem, DropDownPopupControl, DropDown */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "DropDownItem", function() { return DropDownItem; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "DropDownPopupControl", function() { return DropDownPopupControl; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "DropDown", function() { return DropDown; });
/* harmony import */ var _constants__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./constants */ "./dist/esm/constants.js");
/* harmony import */ var _collection__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./collection */ "./dist/esm/collection.js");
/* harmony import */ var _inputwithpopup__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./inputwithpopup */ "./dist/esm/inputwithpopup.js");



class DropDownItem {
    click() {
        if (this.onClick) {
            this.onClick(this);
        }
    }
    constructor(key, value) {
        this.key = key;
        this._value = value;
    }
    toString() {
        return this.value;
    }
    render() {
        if (!this._element) {
            this._element = document.createElement("span");
            this._element.className = "ms-ctrl ms-ctrl-dropdown-item";
            this._element.innerText = this.value;
            this._element.onmouseup = (e) => { this.click(); };
        }
        return this._element;
    }
    get value() {
        return this._value;
    }
    set value(newValue) {
        this._value = newValue;
        if (this._element) {
            this._element.innerText = newValue;
        }
    }
}
class DropDownPopupControl extends _inputwithpopup__WEBPACK_IMPORTED_MODULE_2__["PopupControl"] {
    constructor(owner) {
        super();
        this._renderedItems = [];
        this._selectedIndex = -1;
        this._owner = owner;
    }
    renderContent() {
        var element = document.createElement("div");
        element.className = "ms-ctrl ms-popup";
        var selectedIndex = this._owner.selectedIndex;
        for (var i = 0; i < this._owner.items.length; i++) {
            var renderedItem = this._owner.items.get(i).render();
            renderedItem.tabIndex = 0;
            element.appendChild(renderedItem);
            if (i == selectedIndex) {
                renderedItem.focus();
            }
            this._renderedItems.push(renderedItem);
        }
        return element;
    }
    keyDown(e) {
        super.keyDown(e);
        var selectedItemIndex = this._selectedIndex;
        switch (e.keyCode) {
            case _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_TAB"]:
                this.close();
                break;
            case _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_ENTER"]:
                if (this.selectedIndex >= 0) {
                    this._owner.selectedIndex = this.selectedIndex;
                    this.close();
                }
                break;
            case _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_UP"]:
                if (selectedItemIndex <= 0) {
                    selectedItemIndex = this._renderedItems.length - 1;
                }
                else {
                    selectedItemIndex--;
                    if (selectedItemIndex < 0) {
                        selectedItemIndex = this._renderedItems.length - 1;
                    }
                }
                this.selectedIndex = selectedItemIndex;
                e.cancelBubble = true;
                break;
            case _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_DOWN"]:
                if (selectedItemIndex < 0) {
                    selectedItemIndex = 0;
                }
                else {
                    selectedItemIndex++;
                    if (selectedItemIndex >= this._renderedItems.length) {
                        selectedItemIndex = 0;
                    }
                }
                this.selectedIndex = selectedItemIndex;
                e.cancelBubble = true;
                break;
        }
    }
    render(rootElementBounds) {
        var renderedElement = super.render(rootElementBounds);
        renderedElement.style.minWidth = (rootElementBounds.width / 2) + "px";
        renderedElement.style.maxWidth = rootElementBounds.width + "px";
        return renderedElement;
    }
    get selectedIndex() {
        return this._selectedIndex;
    }
    set selectedIndex(index) {
        if (index >= 0 && index < this._renderedItems.length) {
            this._renderedItems[index].focus();
            this._selectedIndex = index;
        }
    }
}
class DropDown extends _inputwithpopup__WEBPACK_IMPORTED_MODULE_2__["InputWithPopup"] {
    itemClicked(item) {
        this.selectedItem = item;
        this.closePopup();
        this.rootElement.focus();
    }
    validateRootElement(rootElement) {
        if (!(rootElement instanceof HTMLDivElement)) {
            throw new Error("DropDown requires a DIV element as its root.");
        }
    }
    createPopupControl() {
        return new DropDownPopupControl(this);
    }
    getCssClassName() {
        return "ms-ctrl ms-ctrl-dropdown";
    }
    constructor() {
        super();
        this._items = new _collection__WEBPACK_IMPORTED_MODULE_1__["Collection"]();
        this._items.onItemAdded = (item) => { item.onClick = (clickedItem) => { this.itemClicked(clickedItem); }; };
        this._items.onItemRemoved = (item) => { item.onClick = null; };
    }
    attach(rootElement) {
        super.attach(rootElement);
        for (var i = 0; i < this.rootElement.children.length; i++) {
            var childElement = this.rootElement.children[i];
            if (childElement.tagName.toLowerCase() == "ms-dropdown-item") {
                var item = new DropDownItem(childElement.attributes.getNamedItem("key").value, childElement.attributes.getNamedItem("value").value);
                this._items.add(item);
            }
        }
    }
    popup() {
        super.popup();
        this.popupControl.selectedIndex = this.selectedIndex;
    }
    get items() {
        return this._items;
    }
    get selectedItem() {
        return this.value;
    }
    set selectedItem(newValue) {
        this.value = newValue;
    }
    get selectedIndex() {
        return this.items.indexOf(this.value);
    }
    set selectedIndex(index) {
        if (index >= 0 && this.items.length > index) {
            this.selectedItem = this.items.get(index);
        }
    }
}
//# sourceMappingURL=dropdown.js.map

/***/ }),

/***/ "./dist/esm/enums.js":
/*!***************************!*\
  !*** ./dist/esm/enums.js ***!
  \***************************/
/*! exports provided: DayOfWeek */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "DayOfWeek", function() { return DayOfWeek; });
var DayOfWeek;
(function (DayOfWeek) {
    DayOfWeek[DayOfWeek["Sunday"] = 0] = "Sunday";
    DayOfWeek[DayOfWeek["Monday"] = 1] = "Monday";
    DayOfWeek[DayOfWeek["Tuesday"] = 2] = "Tuesday";
    DayOfWeek[DayOfWeek["Wednesday"] = 3] = "Wednesday";
    DayOfWeek[DayOfWeek["Thursday"] = 4] = "Thursday";
    DayOfWeek[DayOfWeek["Friday"] = 5] = "Friday";
    DayOfWeek[DayOfWeek["Saturday"] = 6] = "Saturday";
})(DayOfWeek || (DayOfWeek = {}));
//# sourceMappingURL=enums.js.map

/***/ }),

/***/ "./dist/esm/index.js":
/*!***************************!*\
  !*** ./dist/esm/index.js ***!
  \***************************/
/*! exports provided: KEY_TAB, KEY_ENTER, KEY_ESCAPE, KEY_UP, KEY_DOWN, KEY_DELETE, DayOfWeek, CalendarSettings, daysInMonth, addDays, addMonths, areDatesEqual, getScrollX, getScrollY, getAttributeValueAsBool, getAttributeValueAsString, getAttributeValueAsInt, Collection, InputControl, PopupControl, InputWithPopup, DayCell, Calendar, DropDownItem, DropDownPopupControl, DropDown, CalendarPopupControl, DatePicker, CheckBox, RadioButton, TextBox, PopupMenu */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _constants__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./constants */ "./dist/esm/constants.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "KEY_TAB", function() { return _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_TAB"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "KEY_ENTER", function() { return _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_ENTER"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "KEY_ESCAPE", function() { return _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_ESCAPE"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "KEY_UP", function() { return _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_UP"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "KEY_DOWN", function() { return _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_DOWN"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "KEY_DELETE", function() { return _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_DELETE"]; });

/* harmony import */ var _enums__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./enums */ "./dist/esm/enums.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "DayOfWeek", function() { return _enums__WEBPACK_IMPORTED_MODULE_1__["DayOfWeek"]; });

/* harmony import */ var _utils__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./utils */ "./dist/esm/utils.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "CalendarSettings", function() { return _utils__WEBPACK_IMPORTED_MODULE_2__["CalendarSettings"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "daysInMonth", function() { return _utils__WEBPACK_IMPORTED_MODULE_2__["daysInMonth"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "addDays", function() { return _utils__WEBPACK_IMPORTED_MODULE_2__["addDays"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "addMonths", function() { return _utils__WEBPACK_IMPORTED_MODULE_2__["addMonths"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "areDatesEqual", function() { return _utils__WEBPACK_IMPORTED_MODULE_2__["areDatesEqual"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "getScrollX", function() { return _utils__WEBPACK_IMPORTED_MODULE_2__["getScrollX"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "getScrollY", function() { return _utils__WEBPACK_IMPORTED_MODULE_2__["getScrollY"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "getAttributeValueAsBool", function() { return _utils__WEBPACK_IMPORTED_MODULE_2__["getAttributeValueAsBool"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "getAttributeValueAsString", function() { return _utils__WEBPACK_IMPORTED_MODULE_2__["getAttributeValueAsString"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "getAttributeValueAsInt", function() { return _utils__WEBPACK_IMPORTED_MODULE_2__["getAttributeValueAsInt"]; });

/* harmony import */ var _collection__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ./collection */ "./dist/esm/collection.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "Collection", function() { return _collection__WEBPACK_IMPORTED_MODULE_3__["Collection"]; });

/* harmony import */ var _inputcontrol__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! ./inputcontrol */ "./dist/esm/inputcontrol.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "InputControl", function() { return _inputcontrol__WEBPACK_IMPORTED_MODULE_4__["InputControl"]; });

/* harmony import */ var _inputwithpopup__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! ./inputwithpopup */ "./dist/esm/inputwithpopup.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "PopupControl", function() { return _inputwithpopup__WEBPACK_IMPORTED_MODULE_5__["PopupControl"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "InputWithPopup", function() { return _inputwithpopup__WEBPACK_IMPORTED_MODULE_5__["InputWithPopup"]; });

/* harmony import */ var _calendar__WEBPACK_IMPORTED_MODULE_6__ = __webpack_require__(/*! ./calendar */ "./dist/esm/calendar.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "DayCell", function() { return _calendar__WEBPACK_IMPORTED_MODULE_6__["DayCell"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "Calendar", function() { return _calendar__WEBPACK_IMPORTED_MODULE_6__["Calendar"]; });

/* harmony import */ var _dropdown__WEBPACK_IMPORTED_MODULE_7__ = __webpack_require__(/*! ./dropdown */ "./dist/esm/dropdown.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "DropDownItem", function() { return _dropdown__WEBPACK_IMPORTED_MODULE_7__["DropDownItem"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "DropDownPopupControl", function() { return _dropdown__WEBPACK_IMPORTED_MODULE_7__["DropDownPopupControl"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "DropDown", function() { return _dropdown__WEBPACK_IMPORTED_MODULE_7__["DropDown"]; });

/* harmony import */ var _datepicker__WEBPACK_IMPORTED_MODULE_8__ = __webpack_require__(/*! ./datepicker */ "./dist/esm/datepicker.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "CalendarPopupControl", function() { return _datepicker__WEBPACK_IMPORTED_MODULE_8__["CalendarPopupControl"]; });

/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "DatePicker", function() { return _datepicker__WEBPACK_IMPORTED_MODULE_8__["DatePicker"]; });

/* harmony import */ var _checkbox__WEBPACK_IMPORTED_MODULE_9__ = __webpack_require__(/*! ./checkbox */ "./dist/esm/checkbox.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "CheckBox", function() { return _checkbox__WEBPACK_IMPORTED_MODULE_9__["CheckBox"]; });

/* harmony import */ var _radiobutton__WEBPACK_IMPORTED_MODULE_10__ = __webpack_require__(/*! ./radiobutton */ "./dist/esm/radiobutton.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "RadioButton", function() { return _radiobutton__WEBPACK_IMPORTED_MODULE_10__["RadioButton"]; });

/* harmony import */ var _textbox__WEBPACK_IMPORTED_MODULE_11__ = __webpack_require__(/*! ./textbox */ "./dist/esm/textbox.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "TextBox", function() { return _textbox__WEBPACK_IMPORTED_MODULE_11__["TextBox"]; });

/* harmony import */ var _popupmenu__WEBPACK_IMPORTED_MODULE_12__ = __webpack_require__(/*! ./popupmenu */ "./dist/esm/popupmenu.js");
/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, "PopupMenu", function() { return _popupmenu__WEBPACK_IMPORTED_MODULE_12__["PopupMenu"]; });

/* harmony import */ var _adaptivecards_controls_css__WEBPACK_IMPORTED_MODULE_13__ = __webpack_require__(/*! ./adaptivecards-controls.css */ "./dist/esm/adaptivecards-controls.css");
/* harmony import */ var _adaptivecards_controls_css__WEBPACK_IMPORTED_MODULE_13___default = /*#__PURE__*/__webpack_require__.n(_adaptivecards_controls_css__WEBPACK_IMPORTED_MODULE_13__);














//# sourceMappingURL=index.js.map

/***/ }),

/***/ "./dist/esm/inputcontrol.js":
/*!**********************************!*\
  !*** ./dist/esm/inputcontrol.js ***!
  \**********************************/
/*! exports provided: InputControl */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "InputControl", function() { return InputControl; });
class InputControl {
    validateRootElement(rootElement) {
        // Do nothing - all root element types are valid.
    }
    keyDown(e) {
        // Do nothing in base implementation
    }
    get rootElement() {
        return this._rootElement;
    }
    attach(rootElement) {
        this.validateRootElement(rootElement);
        this._rootElement = rootElement;
        this._rootElement.onkeydown = (e) => { this.keyDown(e); };
    }
}
//# sourceMappingURL=inputcontrol.js.map

/***/ }),

/***/ "./dist/esm/inputwithpopup.js":
/*!************************************!*\
  !*** ./dist/esm/inputwithpopup.js ***!
  \************************************/
/*! exports provided: PopupControl, InputWithPopup */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "PopupControl", function() { return PopupControl; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "InputWithPopup", function() { return InputWithPopup; });
/* harmony import */ var _constants__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./constants */ "./dist/esm/constants.js");
/* harmony import */ var _utils__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./utils */ "./dist/esm/utils.js");
/* harmony import */ var _inputcontrol__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./inputcontrol */ "./dist/esm/inputcontrol.js");



class PopupControl {
    close() {
        if (this.onClose) {
            this.onClose(this);
        }
    }
    keyDown(e) {
        switch (e.keyCode) {
            case _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_ESCAPE"]:
                this.close();
                break;
        }
    }
    render(rootElementBounds) {
        this._popupElement = document.createElement("div");
        this._popupElement.tabIndex = 0;
        this._popupElement.className = "ms-ctrl ms-ctrl-popup-container";
        this._popupElement.onkeydown = (e) => {
            this.keyDown(e);
            return !e.cancelBubble;
        };
        this._popupElement.appendChild(this.renderContent());
        return this._popupElement;
    }
    focus() {
        if (this._popupElement) {
            this._popupElement.firstElementChild.focus();
        }
    }
}
class InputWithPopup extends _inputcontrol__WEBPACK_IMPORTED_MODULE_2__["InputControl"] {
    keyDown(e) {
        switch (e.keyCode) {
            case _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_ENTER"]:
                this.popup();
                break;
        }
    }
    updateLabel() {
        if (this._labelElement) {
            if (this._value) {
                this._labelElement.innerHTML = this.getValueAsString();
                this._labelElement.classList.remove("placeholder");
            }
            else {
                this._labelElement.innerText = this._placeholderText ? this._placeholderText : "";
                this._labelElement.classList.add("placeholder");
            }
        }
    }
    get popupControl() {
        return this._popupControl;
    }
    getButtonIconCssClassName() {
        return "ms-icon-chevronDown";
    }
    getValueAsString() {
        return this._value.toString();
    }
    valueChanged() {
        if (this.onValueChanged) {
            this.onValueChanged(this);
        }
    }
    attach(rootElement) {
        super.attach(rootElement);
        rootElement.tabIndex = 0;
        rootElement.className = this.getCssClassName();
        window.addEventListener("resize", (e) => { this.closePopup(); });
        this.rootElement.onclick = (e) => {
            if (this._isOpen) {
                this.closePopup();
            }
            else {
                this.popup();
            }
        };
        let placeHolderDomItem = this.rootElement.attributes.getNamedItem("placeholder");
        if (placeHolderDomItem) {
            this._placeholderText = placeHolderDomItem.value;
        }
        this._labelElement = document.createElement("span");
        this._labelElement.className = "ms-ctrl ms-dropdown-label";
        this._dropDownButtonElement = document.createElement("i");
        this._dropDownButtonElement.className = "ms-icon ms-ctrl-dropdown-button " + this.getButtonIconCssClassName();
        ;
        this.rootElement.appendChild(this._labelElement);
        this.rootElement.appendChild(this._dropDownButtonElement);
        this.updateLabel();
    }
    popup() {
        if (!this._isOpen) {
            this._overlayElement = document.createElement("div");
            this._overlayElement.className = "ms-ctrl-overlay";
            this._overlayElement.tabIndex = 0;
            this._overlayElement.style.width = document.documentElement.scrollWidth + "px";
            this._overlayElement.style.height = document.documentElement.scrollHeight + "px";
            this._overlayElement.onfocus = (e) => { this.closePopup(); };
            document.body.appendChild(this._overlayElement);
            this._popupControl = this.createPopupControl();
            this._popupControl.onClose = (sender) => {
                this.closePopup();
                this.rootElement.focus();
            };
            var rootElementBounds = this.rootElement.getBoundingClientRect();
            this._popupControlElement = this._popupControl.render(rootElementBounds);
            this._popupControlElement.classList.remove("ms-ctrl-slide", "ms-ctrl-slideLeftToRight", "ms-ctrl-slideRightToLeft", "ms-ctrl-slideTopToBottom", "ms-ctrl-slideRightToLeft");
            this._overlayElement.appendChild(this._popupControlElement);
            var popupElementBounds = this._popupControlElement.getBoundingClientRect();
            var availableSpaceBelow = window.innerHeight - rootElementBounds.bottom;
            var availableSpaceAbove = rootElementBounds.top;
            var left = rootElementBounds.left + _utils__WEBPACK_IMPORTED_MODULE_1__["getScrollX"]();
            var top;
            if (availableSpaceAbove < popupElementBounds.height && availableSpaceBelow < popupElementBounds.height) {
                // Not enough space above or below root element
                var actualPopupHeight = Math.min(popupElementBounds.height, window.innerHeight);
                this._popupControlElement.style.maxHeight = actualPopupHeight + "px";
                if (actualPopupHeight < popupElementBounds.height) {
                    top = _utils__WEBPACK_IMPORTED_MODULE_1__["getScrollY"]();
                }
                else {
                    top = _utils__WEBPACK_IMPORTED_MODULE_1__["getScrollY"]() + rootElementBounds.top + (rootElementBounds.height - actualPopupHeight) / 2;
                }
                var availableSpaceRight = window.innerWidth - rootElementBounds.right;
                var availableSpaceLeft = rootElementBounds.left;
                if (availableSpaceLeft < popupElementBounds.width && availableSpaceRight < popupElementBounds.width) {
                    // Not enough space left or right of root element
                    var actualPopupWidth = Math.min(popupElementBounds.width, window.innerWidth);
                    this._popupControlElement.style.maxWidth = actualPopupWidth + "px";
                    if (actualPopupWidth < popupElementBounds.width) {
                        left = _utils__WEBPACK_IMPORTED_MODULE_1__["getScrollX"]();
                    }
                    else {
                        left = _utils__WEBPACK_IMPORTED_MODULE_1__["getScrollX"]() + rootElementBounds.left + (rootElementBounds.width - actualPopupWidth) / 2;
                    }
                }
                else {
                    // Enough space on the left or right of the root element
                    if (availableSpaceRight >= popupElementBounds.width) {
                        left = _utils__WEBPACK_IMPORTED_MODULE_1__["getScrollX"]() + rootElementBounds.right;
                        this._popupControlElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideLeftToRight");
                    }
                    else {
                        left = _utils__WEBPACK_IMPORTED_MODULE_1__["getScrollX"]() + rootElementBounds.left - popupElementBounds.width;
                        this._popupControlElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideRightToLeft");
                    }
                }
            }
            else {
                // Enough space above or below root element
                if (availableSpaceBelow >= popupElementBounds.height) {
                    top = _utils__WEBPACK_IMPORTED_MODULE_1__["getScrollY"]() + rootElementBounds.bottom;
                    this._popupControlElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideTopToBottom");
                }
                else {
                    top = _utils__WEBPACK_IMPORTED_MODULE_1__["getScrollY"]() + rootElementBounds.top - popupElementBounds.height;
                    this._popupControlElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideBottomToTop");
                }
            }
            this._popupControlElement.style.left = left + "px";
            this._popupControlElement.style.top = top + "px";
            this._popupControlElement.focus();
            this._isOpen = true;
        }
    }
    closePopup() {
        if (this._isOpen) {
            document.body.removeChild(this._overlayElement);
            this._isOpen = false;
        }
    }
    get isOpen() {
        return this._isOpen;
    }
    get placeholderText() {
        return this._placeholderText;
    }
    set placeholderText(value) {
        this._placeholderText = value;
    }
    get value() {
        return this._value;
    }
    set value(newValue) {
        if (this._value != newValue) {
            this._value = newValue;
            this.updateLabel();
            this.valueChanged();
        }
    }
}
//# sourceMappingURL=inputwithpopup.js.map

/***/ }),

/***/ "./dist/esm/popupmenu.js":
/*!*******************************!*\
  !*** ./dist/esm/popupmenu.js ***!
  \*******************************/
/*! exports provided: PopupMenu */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "PopupMenu", function() { return PopupMenu; });
/* harmony import */ var _utils__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./utils */ "./dist/esm/utils.js");
/* harmony import */ var _constants__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./constants */ "./dist/esm/constants.js");
/* harmony import */ var _collection__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./collection */ "./dist/esm/collection.js");
/* harmony import */ var _inputwithpopup__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ./inputwithpopup */ "./dist/esm/inputwithpopup.js");




class PopupMenu extends _inputwithpopup__WEBPACK_IMPORTED_MODULE_3__["PopupControl"] {
    constructor() {
        super();
        this._items = new _collection__WEBPACK_IMPORTED_MODULE_2__["Collection"]();
        this._renderedItems = [];
        this._selectedIndex = -1;
    }
    renderContent() {
        var element = document.createElement("div");
        element.className = "ms-ctrl ms-popup";
        for (var i = 0; i < this._items.length; i++) {
            var renderedItem = this._items.get(i).render();
            renderedItem.tabIndex = 0;
            element.appendChild(renderedItem);
            if (i == this.selectedIndex) {
                renderedItem.focus();
            }
            this._renderedItems.push(renderedItem);
        }
        return element;
    }
    keyDown(e) {
        super.keyDown(e);
        var selectedItemIndex = this._selectedIndex;
        switch (e.keyCode) {
            case _constants__WEBPACK_IMPORTED_MODULE_1__["KEY_TAB"]:
                this.close();
                break;
            /*
            case Constants.KEY_ENTER:
                if (this.selectedIndex >= 0) {
                    this.selectedIndex = this.selectedIndex;

                    this.close();
                }

                break;
            */
            case _constants__WEBPACK_IMPORTED_MODULE_1__["KEY_UP"]:
                if (selectedItemIndex <= 0) {
                    selectedItemIndex = this._renderedItems.length - 1;
                }
                else {
                    selectedItemIndex--;
                    if (selectedItemIndex < 0) {
                        selectedItemIndex = this._renderedItems.length - 1;
                    }
                }
                this.selectedIndex = selectedItemIndex;
                e.cancelBubble = true;
                break;
            case _constants__WEBPACK_IMPORTED_MODULE_1__["KEY_DOWN"]:
                if (selectedItemIndex < 0) {
                    selectedItemIndex = 0;
                }
                else {
                    selectedItemIndex++;
                    if (selectedItemIndex >= this._renderedItems.length) {
                        selectedItemIndex = 0;
                    }
                }
                this.selectedIndex = selectedItemIndex;
                e.cancelBubble = true;
                break;
        }
    }
    popup(rootElement) {
        if (!this._isOpen) {
            this._overlayElement = document.createElement("div");
            this._overlayElement.className = "ms-ctrl-overlay";
            this._overlayElement.tabIndex = 0;
            this._overlayElement.style.zIndex = "1000";
            this._overlayElement.style.width = document.documentElement.scrollWidth + "px";
            this._overlayElement.style.height = document.documentElement.scrollHeight + "px";
            this._overlayElement.onfocus = (e) => { this.closePopup(); };
            document.body.appendChild(this._overlayElement);
            var rootElementBounds = rootElement.getBoundingClientRect();
            this._popupControlElement = this.render(rootElementBounds);
            this._popupControlElement.classList.remove("ms-ctrl-slide", "ms-ctrl-slideLeftToRight", "ms-ctrl-slideRightToLeft", "ms-ctrl-slideTopToBottom", "ms-ctrl-slideRightToLeft");
            this._overlayElement.appendChild(this._popupControlElement);
            var popupElementBounds = this._popupControlElement.getBoundingClientRect();
            var availableSpaceBelow = window.innerHeight - rootElementBounds.bottom;
            var availableSpaceAbove = rootElementBounds.top;
            var left = rootElementBounds.left + _utils__WEBPACK_IMPORTED_MODULE_0__["getScrollX"]();
            var top;
            if (availableSpaceAbove < popupElementBounds.height && availableSpaceBelow < popupElementBounds.height) {
                // Not enough space above or below root element
                var maxPopupHeight = window.innerHeight;
                this._popupControlElement.style.maxHeight = maxPopupHeight + "px";
                if (maxPopupHeight < popupElementBounds.height) {
                    top = _utils__WEBPACK_IMPORTED_MODULE_0__["getScrollY"]();
                }
                else {
                    top = _utils__WEBPACK_IMPORTED_MODULE_0__["getScrollY"]() + rootElementBounds.top + (rootElementBounds.height - maxPopupHeight) / 2;
                }
                var availableSpaceRight = window.innerWidth - rootElementBounds.right;
                var availableSpaceLeft = rootElementBounds.left;
                if (availableSpaceLeft < popupElementBounds.width && availableSpaceRight < popupElementBounds.width) {
                    // Not enough space left or right of root element
                    var maxPopupWidth = window.innerWidth;
                    this._popupControlElement.style.maxWidth = maxPopupWidth + "px";
                    if (maxPopupWidth < popupElementBounds.width) {
                        left = _utils__WEBPACK_IMPORTED_MODULE_0__["getScrollX"]();
                    }
                    else {
                        left = _utils__WEBPACK_IMPORTED_MODULE_0__["getScrollX"]() + rootElementBounds.left + (rootElementBounds.width - maxPopupWidth) / 2;
                    }
                }
                else {
                    // Enough space on the left or right of the root element
                    if (availableSpaceRight >= popupElementBounds.width) {
                        left = _utils__WEBPACK_IMPORTED_MODULE_0__["getScrollX"]() + rootElementBounds.right;
                        this._popupControlElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideLeftToRight");
                    }
                    else {
                        left = _utils__WEBPACK_IMPORTED_MODULE_0__["getScrollX"]() + rootElementBounds.left - popupElementBounds.width;
                        this._popupControlElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideRightToLeft");
                    }
                }
            }
            else {
                // Enough space above or below root element
                if (availableSpaceBelow >= popupElementBounds.height) {
                    top = _utils__WEBPACK_IMPORTED_MODULE_0__["getScrollY"]() + rootElementBounds.bottom;
                    this._popupControlElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideTopToBottom");
                }
                else {
                    top = _utils__WEBPACK_IMPORTED_MODULE_0__["getScrollY"]() + rootElementBounds.top - popupElementBounds.height;
                    this._popupControlElement.classList.add("ms-ctrl-slide", "ms-ctrl-slideBottomToTop");
                }
            }
            this._popupControlElement.style.left = left + "px";
            this._popupControlElement.style.top = top + "px";
            this._popupControlElement.focus();
            this._isOpen = true;
        }
    }
    closePopup() {
        if (this._isOpen) {
            document.body.removeChild(this._overlayElement);
            this._isOpen = false;
        }
    }
    get isOpen() {
        return this._isOpen;
    }
    get items() {
        return this._items;
    }
    get selectedIndex() {
        return this._selectedIndex;
    }
    set selectedIndex(index) {
        if (index >= 0 && index < this._renderedItems.length) {
            this._renderedItems[index].focus();
            this._selectedIndex = index;
        }
    }
}
//# sourceMappingURL=popupmenu.js.map

/***/ }),

/***/ "./dist/esm/radiobutton.js":
/*!*********************************!*\
  !*** ./dist/esm/radiobutton.js ***!
  \*********************************/
/*! exports provided: RadioButton */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "RadioButton", function() { return RadioButton; });
/* harmony import */ var _constants__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./constants */ "./dist/esm/constants.js");
/* harmony import */ var _inputcontrol__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./inputcontrol */ "./dist/esm/inputcontrol.js");


class RadioButton extends _inputcontrol__WEBPACK_IMPORTED_MODULE_1__["InputControl"] {
    constructor() {
        super(...arguments);
        this._label = "";
        this._checkboxElement = null;
        this._spanElement = null;
    }
    static createId() {
        var result = RadioButton.creationIndex;
        RadioButton.creationIndex++;
        return result;
    }
    changed() {
        if (this.onChange) {
            this.onChange(this);
        }
    }
    keyDown(e) {
        switch (e.keyCode) {
            case _constants__WEBPACK_IMPORTED_MODULE_0__["KEY_ENTER"]:
                this.isChecked = !this.isChecked;
                break;
        }
    }
    attach(rootElement) {
        super.attach(rootElement);
        rootElement.className = "ms-ctrl ms-ctrl-radiobutton";
        rootElement.tabIndex = 0;
        var labelAttribute = rootElement.attributes["label"];
        if (labelAttribute) {
            this._label = labelAttribute.value;
        }
        var isCheckedAttribute = rootElement.attributes["ischecked"];
        if (isCheckedAttribute) {
            this._isChecked = isCheckedAttribute.value === "true";
        }
        this._checkboxElement = document.createElement("input");
        this._checkboxElement.id = "ms-ctrl-radio-" + RadioButton.createId();
        this._checkboxElement.type = "radio";
        this._checkboxElement.style.position = "absolute";
        this._checkboxElement.checked = this.isChecked;
        this._checkboxElement.onchange = (e) => { this.changed(); };
        var groupNameAttribute = rootElement.attributes["groupname"];
        if (groupNameAttribute) {
            this._checkboxElement.name = groupNameAttribute.value;
        }
        var labelElement = document.createElement("label");
        labelElement.htmlFor = this._checkboxElement.id;
        this._spanElement = document.createElement("span");
        this._spanElement.innerText = this._label;
        labelElement.appendChild(this._spanElement);
        rootElement.innerHTML = "";
        rootElement.appendChild(this._checkboxElement);
        rootElement.appendChild(labelElement);
    }
    get label() {
        return this._label;
    }
    set label(value) {
        this._label = value;
        if (this._spanElement) {
            this._spanElement.innerText = this._label;
        }
    }
    get isChecked() {
        return this._isChecked;
    }
    set isChecked(value) {
        if (this._isChecked != value) {
            this._isChecked = value;
            if (this._checkboxElement) {
                this._checkboxElement.checked = this._isChecked;
            }
            this.changed();
        }
    }
}
// Used to generate unique Ids
RadioButton.creationIndex = 0;
//# sourceMappingURL=radiobutton.js.map

/***/ }),

/***/ "./dist/esm/textbox.js":
/*!*****************************!*\
  !*** ./dist/esm/textbox.js ***!
  \*****************************/
/*! exports provided: TextBox */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "TextBox", function() { return TextBox; });
/* harmony import */ var _utils__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./utils */ "./dist/esm/utils.js");
/* harmony import */ var _inputcontrol__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./inputcontrol */ "./dist/esm/inputcontrol.js");


class EditBox {
    changed() {
        if (this.onChange) {
            this.onChange();
        }
    }
}
class SingleLineEditBox extends EditBox {
    constructor() {
        super();
        this._inputElement = document.createElement("input");
        this._inputElement.className = "ms-ctrl ms-ctrl-textbox";
        this._inputElement.type = "text";
        this._inputElement.oninput = (e) => {
            this.changed();
        };
    }
    get element() {
        return this._inputElement;
    }
    set placeholder(value) {
        this._inputElement.placeholder = value;
    }
    set lineCount(value) {
        // lineCount can't be set on a SingleLineEditBox
    }
    set maxLength(value) {
        if (this._inputElement.maxLength != value) {
            this._inputElement.maxLength = value;
            this.value = this.value.substr(0, value);
        }
    }
    get value() {
        return this._inputElement.value;
    }
    set value(newValue) {
        this._inputElement.value = newValue;
    }
}
class MultilineEditBox extends EditBox {
    constructor() {
        super();
        this._textareaElement = document.createElement("textarea");
        this._textareaElement.className = "ms-ctrl ms-ctrl-textbox ms-ctrl-textbox-multiline";
        this._textareaElement.oninput = (e) => {
            this.changed();
        };
    }
    get element() {
        return this._textareaElement;
    }
    set placeholder(value) {
        this._textareaElement.placeholder = value;
    }
    set lineCount(value) {
        this._textareaElement.rows = value;
    }
    set maxLength(value) {
        if (this._textareaElement.maxLength != value) {
            this._textareaElement.maxLength = value;
            this.value = this.value.substr(0, value);
        }
    }
    get value() {
        return this._textareaElement.value;
    }
    set value(newValue) {
        this._textareaElement.value = newValue;
    }
}
class TextBox extends _inputcontrol__WEBPACK_IMPORTED_MODULE_1__["InputControl"] {
    constructor() {
        super(...arguments);
        this._isMultiline = false;
        this._lineCount = 3;
    }
    editBoxChanged() {
        if (this.onChange) {
            this.onChange(this);
        }
    }
    recreateEditBox() {
        var currentValue = null;
        if (this._editBox) {
            currentValue = this._editBox.value;
        }
        else {
            currentValue = this.rootElement.innerText;
        }
        if (this._isMultiline) {
            this._editBox = new MultilineEditBox();
        }
        else {
            this._editBox = new SingleLineEditBox();
        }
        if (currentValue) {
            this._editBox.value = currentValue;
        }
        this._editBox.lineCount = this._lineCount;
        this._editBox.maxLength = this._maxLength;
        this._editBox.placeholder = this._placeholder;
        this._editBox.onChange = () => { this.editBoxChanged(); };
        this.rootElement.innerHTML = "";
        this.rootElement.appendChild(this._editBox.element);
    }
    get editBox() {
        if (!this._editBox) {
            this.recreateEditBox();
        }
        return this._editBox;
    }
    attach(rootElement) {
        super.attach(rootElement);
        this._isMultiline = _utils__WEBPACK_IMPORTED_MODULE_0__["getAttributeValueAsBool"](rootElement, "ismultiline", false);
        this._lineCount = _utils__WEBPACK_IMPORTED_MODULE_0__["getAttributeValueAsInt"](rootElement, "lines", 3);
        this._maxLength = _utils__WEBPACK_IMPORTED_MODULE_0__["getAttributeValueAsInt"](rootElement, "maxlength", 50000);
        this._placeholder = _utils__WEBPACK_IMPORTED_MODULE_0__["getAttributeValueAsString"](rootElement, "placeholder", null);
        this.recreateEditBox();
    }
    get value() {
        return this.editBox.value;
    }
    set value(newValue) {
        this.editBox.value = newValue;
    }
    get placeholder() {
        return this._placeholder;
    }
    set placeholder(value) {
        this._placeholder = value;
        this.editBox.placeholder = value;
    }
    get isMultiline() {
        return this._isMultiline;
    }
    set isMultiline(value) {
        if (this._isMultiline != value) {
            this._isMultiline = value;
            this.recreateEditBox();
        }
    }
    get lineCount() {
        return this._lineCount;
    }
    set lineCount(value) {
        if (value > 0) {
            this._lineCount = value;
            this.editBox.lineCount = value;
        }
    }
    get maxLength() {
        return this._maxLength;
    }
    set maxLength(value) {
        if (value > 0) {
            this._maxLength = value;
            this.editBox.maxLength = value;
        }
    }
}
//# sourceMappingURL=textbox.js.map

/***/ }),

/***/ "./dist/esm/utils.js":
/*!***************************!*\
  !*** ./dist/esm/utils.js ***!
  \***************************/
/*! exports provided: CalendarSettings, daysInMonth, addDays, addMonths, areDatesEqual, getScrollX, getScrollY, getAttributeValueAsBool, getAttributeValueAsString, getAttributeValueAsInt */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "CalendarSettings", function() { return CalendarSettings; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "daysInMonth", function() { return daysInMonth; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "addDays", function() { return addDays; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "addMonths", function() { return addMonths; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "areDatesEqual", function() { return areDatesEqual; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "getScrollX", function() { return getScrollX; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "getScrollY", function() { return getScrollY; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "getAttributeValueAsBool", function() { return getAttributeValueAsBool; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "getAttributeValueAsString", function() { return getAttributeValueAsString; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "getAttributeValueAsInt", function() { return getAttributeValueAsInt; });
/* harmony import */ var _enums__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./enums */ "./dist/esm/enums.js");

class CalendarSettings {
    static getLongDayName(dayIndex) {
        if (dayIndex >= 0 && dayIndex < CalendarSettings.longDayNames.length) {
            return CalendarSettings.longDayNames[dayIndex];
        }
        throw new Error("Day index out of range: " + dayIndex);
    }
    static getShortDayName(dayIndex) {
        if (dayIndex >= 0 && dayIndex < CalendarSettings.shortDayNames.length) {
            return CalendarSettings.shortDayNames[dayIndex];
        }
        throw new Error("Day index out of range: " + dayIndex);
    }
    static getInitialDayName(dayIndex) {
        if (dayIndex >= 0 && dayIndex < CalendarSettings.minimalDayNames.length) {
            return CalendarSettings.minimalDayNames[dayIndex];
        }
        throw new Error("Day index out of range: " + dayIndex);
    }
    static getLongMonthName(monthIndex) {
        if (monthIndex >= 0 && monthIndex < CalendarSettings.longMonthNames.length) {
            return CalendarSettings.longMonthNames[monthIndex];
        }
        throw new Error("Month index out of range: " + monthIndex);
    }
    static getShortMonthName(monthIndex) {
        if (monthIndex >= 0 && monthIndex < CalendarSettings.shortMonthNames.length) {
            return CalendarSettings.shortMonthNames[monthIndex];
        }
        throw new Error("Month index out of range: " + monthIndex);
    }
}
CalendarSettings.monthsInYear = 12;
CalendarSettings.daysInWeek = 7;
CalendarSettings.firstDayOfWeek = _enums__WEBPACK_IMPORTED_MODULE_0__["DayOfWeek"].Sunday;
CalendarSettings.longDayNames = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];
CalendarSettings.shortDayNames = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];
CalendarSettings.minimalDayNames = ["Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"];
CalendarSettings.longMonthNames = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
CalendarSettings.shortMonthNames = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];
function daysInMonth(year, month) {
    switch (month) {
        case 1:
            return (year % 4 == 0 && year % 100) || year % 400 == 0 ? 29 : 28;
        case 3:
        case 5:
        case 8:
        case 10:
            return 30;
        default:
            return 31;
    }
}
function addDays(date, days) {
    var result = new Date(date.getTime());
    result.setDate(result.getDate() + days);
    return result;
}
function addMonths(date, months) {
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
function areDatesEqual(date1, date2) {
    return date1.getFullYear() == date2.getFullYear() &&
        date1.getMonth() == date2.getMonth() &&
        date1.getDate() == date2.getDate();
}
function getScrollX() {
    return window.pageXOffset;
}
function getScrollY() {
    return window.pageYOffset;
}
function getAttributeValueAsBool(element, attributeName, defaultValue) {
    var attribute = element.attributes[attributeName];
    if (attribute) {
        return attribute.value === "true";
    }
    return defaultValue;
}
function getAttributeValueAsString(element, attributeName, defaultValue) {
    var attribute = element.attributes[attributeName];
    if (attribute) {
        return attribute.value;
    }
    return defaultValue;
}
function getAttributeValueAsInt(element, attributeName, defaultValue) {
    var attribute = element.attributes[attributeName];
    if (attribute) {
        var n = parseInt(attribute.value);
        if (!isNaN(n)) {
            return n;
        }
    }
    return defaultValue;
}
//# sourceMappingURL=utils.js.map

/***/ }),

/***/ "./node_modules/mini-css-extract-plugin/dist/loader.js!./node_modules/css-loader/index.js!./dist/esm/adaptivecards-controls.css":
/*!*****************************************************************************************************************************!*\
  !*** ./node_modules/mini-css-extract-plugin/dist/loader.js!./node_modules/css-loader!./dist/esm/adaptivecards-controls.css ***!
  \*****************************************************************************************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

// extracted by mini-css-extract-plugin

/***/ }),

/***/ "./node_modules/style-loader/lib/addStyles.js":
/*!****************************************************!*\
  !*** ./node_modules/style-loader/lib/addStyles.js ***!
  \****************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

/*
	MIT License http://www.opensource.org/licenses/mit-license.php
	Author Tobias Koppers @sokra
*/

var stylesInDom = {};

var	memoize = function (fn) {
	var memo;

	return function () {
		if (typeof memo === "undefined") memo = fn.apply(this, arguments);
		return memo;
	};
};

var isOldIE = memoize(function () {
	// Test for IE <= 9 as proposed by Browserhacks
	// @see http://browserhacks.com/#hack-e71d8692f65334173fee715c222cb805
	// Tests for existence of standard globals is to allow style-loader
	// to operate correctly into non-standard environments
	// @see https://github.com/webpack-contrib/style-loader/issues/177
	return window && document && document.all && !window.atob;
});

var getTarget = function (target, parent) {
  if (parent){
    return parent.querySelector(target);
  }
  return document.querySelector(target);
};

var getElement = (function (fn) {
	var memo = {};

	return function(target, parent) {
                // If passing function in options, then use it for resolve "head" element.
                // Useful for Shadow Root style i.e
                // {
                //   insertInto: function () { return document.querySelector("#foo").shadowRoot }
                // }
                if (typeof target === 'function') {
                        return target();
                }
                if (typeof memo[target] === "undefined") {
			var styleTarget = getTarget.call(this, target, parent);
			// Special case to return head of iframe instead of iframe itself
			if (window.HTMLIFrameElement && styleTarget instanceof window.HTMLIFrameElement) {
				try {
					// This will throw an exception if access to iframe is blocked
					// due to cross-origin restrictions
					styleTarget = styleTarget.contentDocument.head;
				} catch(e) {
					styleTarget = null;
				}
			}
			memo[target] = styleTarget;
		}
		return memo[target]
	};
})();

var singleton = null;
var	singletonCounter = 0;
var	stylesInsertedAtTop = [];

var	fixUrls = __webpack_require__(/*! ./urls */ "./node_modules/style-loader/lib/urls.js");

module.exports = function(list, options) {
	if (typeof DEBUG !== "undefined" && DEBUG) {
		if (typeof document !== "object") throw new Error("The style-loader cannot be used in a non-browser environment");
	}

	options = options || {};

	options.attrs = typeof options.attrs === "object" ? options.attrs : {};

	// Force single-tag solution on IE6-9, which has a hard limit on the # of <style>
	// tags it will allow on a page
	if (!options.singleton && typeof options.singleton !== "boolean") options.singleton = isOldIE();

	// By default, add <style> tags to the <head> element
        if (!options.insertInto) options.insertInto = "head";

	// By default, add <style> tags to the bottom of the target
	if (!options.insertAt) options.insertAt = "bottom";

	var styles = listToStyles(list, options);

	addStylesToDom(styles, options);

	return function update (newList) {
		var mayRemove = [];

		for (var i = 0; i < styles.length; i++) {
			var item = styles[i];
			var domStyle = stylesInDom[item.id];

			domStyle.refs--;
			mayRemove.push(domStyle);
		}

		if(newList) {
			var newStyles = listToStyles(newList, options);
			addStylesToDom(newStyles, options);
		}

		for (var i = 0; i < mayRemove.length; i++) {
			var domStyle = mayRemove[i];

			if(domStyle.refs === 0) {
				for (var j = 0; j < domStyle.parts.length; j++) domStyle.parts[j]();

				delete stylesInDom[domStyle.id];
			}
		}
	};
};

function addStylesToDom (styles, options) {
	for (var i = 0; i < styles.length; i++) {
		var item = styles[i];
		var domStyle = stylesInDom[item.id];

		if(domStyle) {
			domStyle.refs++;

			for(var j = 0; j < domStyle.parts.length; j++) {
				domStyle.parts[j](item.parts[j]);
			}

			for(; j < item.parts.length; j++) {
				domStyle.parts.push(addStyle(item.parts[j], options));
			}
		} else {
			var parts = [];

			for(var j = 0; j < item.parts.length; j++) {
				parts.push(addStyle(item.parts[j], options));
			}

			stylesInDom[item.id] = {id: item.id, refs: 1, parts: parts};
		}
	}
}

function listToStyles (list, options) {
	var styles = [];
	var newStyles = {};

	for (var i = 0; i < list.length; i++) {
		var item = list[i];
		var id = options.base ? item[0] + options.base : item[0];
		var css = item[1];
		var media = item[2];
		var sourceMap = item[3];
		var part = {css: css, media: media, sourceMap: sourceMap};

		if(!newStyles[id]) styles.push(newStyles[id] = {id: id, parts: [part]});
		else newStyles[id].parts.push(part);
	}

	return styles;
}

function insertStyleElement (options, style) {
	var target = getElement(options.insertInto)

	if (!target) {
		throw new Error("Couldn't find a style target. This probably means that the value for the 'insertInto' parameter is invalid.");
	}

	var lastStyleElementInsertedAtTop = stylesInsertedAtTop[stylesInsertedAtTop.length - 1];

	if (options.insertAt === "top") {
		if (!lastStyleElementInsertedAtTop) {
			target.insertBefore(style, target.firstChild);
		} else if (lastStyleElementInsertedAtTop.nextSibling) {
			target.insertBefore(style, lastStyleElementInsertedAtTop.nextSibling);
		} else {
			target.appendChild(style);
		}
		stylesInsertedAtTop.push(style);
	} else if (options.insertAt === "bottom") {
		target.appendChild(style);
	} else if (typeof options.insertAt === "object" && options.insertAt.before) {
		var nextSibling = getElement(options.insertAt.before, target);
		target.insertBefore(style, nextSibling);
	} else {
		throw new Error("[Style Loader]\n\n Invalid value for parameter 'insertAt' ('options.insertAt') found.\n Must be 'top', 'bottom', or Object.\n (https://github.com/webpack-contrib/style-loader#insertat)\n");
	}
}

function removeStyleElement (style) {
	if (style.parentNode === null) return false;
	style.parentNode.removeChild(style);

	var idx = stylesInsertedAtTop.indexOf(style);
	if(idx >= 0) {
		stylesInsertedAtTop.splice(idx, 1);
	}
}

function createStyleElement (options) {
	var style = document.createElement("style");

	if(options.attrs.type === undefined) {
		options.attrs.type = "text/css";
	}

	if(options.attrs.nonce === undefined) {
		var nonce = getNonce();
		if (nonce) {
			options.attrs.nonce = nonce;
		}
	}

	addAttrs(style, options.attrs);
	insertStyleElement(options, style);

	return style;
}

function createLinkElement (options) {
	var link = document.createElement("link");

	if(options.attrs.type === undefined) {
		options.attrs.type = "text/css";
	}
	options.attrs.rel = "stylesheet";

	addAttrs(link, options.attrs);
	insertStyleElement(options, link);

	return link;
}

function addAttrs (el, attrs) {
	Object.keys(attrs).forEach(function (key) {
		el.setAttribute(key, attrs[key]);
	});
}

function getNonce() {
	if (false) {}

	return __webpack_require__.nc;
}

function addStyle (obj, options) {
	var style, update, remove, result;

	// If a transform function was defined, run it on the css
	if (options.transform && obj.css) {
	    result = typeof options.transform === 'function'
		 ? options.transform(obj.css) 
		 : options.transform.default(obj.css);

	    if (result) {
	    	// If transform returns a value, use that instead of the original css.
	    	// This allows running runtime transformations on the css.
	    	obj.css = result;
	    } else {
	    	// If the transform function returns a falsy value, don't add this css.
	    	// This allows conditional loading of css
	    	return function() {
	    		// noop
	    	};
	    }
	}

	if (options.singleton) {
		var styleIndex = singletonCounter++;

		style = singleton || (singleton = createStyleElement(options));

		update = applyToSingletonTag.bind(null, style, styleIndex, false);
		remove = applyToSingletonTag.bind(null, style, styleIndex, true);

	} else if (
		obj.sourceMap &&
		typeof URL === "function" &&
		typeof URL.createObjectURL === "function" &&
		typeof URL.revokeObjectURL === "function" &&
		typeof Blob === "function" &&
		typeof btoa === "function"
	) {
		style = createLinkElement(options);
		update = updateLink.bind(null, style, options);
		remove = function () {
			removeStyleElement(style);

			if(style.href) URL.revokeObjectURL(style.href);
		};
	} else {
		style = createStyleElement(options);
		update = applyToTag.bind(null, style);
		remove = function () {
			removeStyleElement(style);
		};
	}

	update(obj);

	return function updateStyle (newObj) {
		if (newObj) {
			if (
				newObj.css === obj.css &&
				newObj.media === obj.media &&
				newObj.sourceMap === obj.sourceMap
			) {
				return;
			}

			update(obj = newObj);
		} else {
			remove();
		}
	};
}

var replaceText = (function () {
	var textStore = [];

	return function (index, replacement) {
		textStore[index] = replacement;

		return textStore.filter(Boolean).join('\n');
	};
})();

function applyToSingletonTag (style, index, remove, obj) {
	var css = remove ? "" : obj.css;

	if (style.styleSheet) {
		style.styleSheet.cssText = replaceText(index, css);
	} else {
		var cssNode = document.createTextNode(css);
		var childNodes = style.childNodes;

		if (childNodes[index]) style.removeChild(childNodes[index]);

		if (childNodes.length) {
			style.insertBefore(cssNode, childNodes[index]);
		} else {
			style.appendChild(cssNode);
		}
	}
}

function applyToTag (style, obj) {
	var css = obj.css;
	var media = obj.media;

	if(media) {
		style.setAttribute("media", media)
	}

	if(style.styleSheet) {
		style.styleSheet.cssText = css;
	} else {
		while(style.firstChild) {
			style.removeChild(style.firstChild);
		}

		style.appendChild(document.createTextNode(css));
	}
}

function updateLink (link, options, obj) {
	var css = obj.css;
	var sourceMap = obj.sourceMap;

	/*
		If convertToAbsoluteUrls isn't defined, but sourcemaps are enabled
		and there is no publicPath defined then lets turn convertToAbsoluteUrls
		on by default.  Otherwise default to the convertToAbsoluteUrls option
		directly
	*/
	var autoFixUrls = options.convertToAbsoluteUrls === undefined && sourceMap;

	if (options.convertToAbsoluteUrls || autoFixUrls) {
		css = fixUrls(css);
	}

	if (sourceMap) {
		// http://stackoverflow.com/a/26603875
		css += "\n/*# sourceMappingURL=data:application/json;base64," + btoa(unescape(encodeURIComponent(JSON.stringify(sourceMap)))) + " */";
	}

	var blob = new Blob([css], { type: "text/css" });

	var oldSrc = link.href;

	link.href = URL.createObjectURL(blob);

	if(oldSrc) URL.revokeObjectURL(oldSrc);
}


/***/ }),

/***/ "./node_modules/style-loader/lib/urls.js":
/*!***********************************************!*\
  !*** ./node_modules/style-loader/lib/urls.js ***!
  \***********************************************/
/*! no static exports found */
/***/ (function(module, exports) {


/**
 * When source maps are enabled, `style-loader` uses a link element with a data-uri to
 * embed the css on the page. This breaks all relative urls because now they are relative to a
 * bundle instead of the current page.
 *
 * One solution is to only use full urls, but that may be impossible.
 *
 * Instead, this function "fixes" the relative urls to be absolute according to the current page location.
 *
 * A rudimentary test suite is located at `test/fixUrls.js` and can be run via the `npm test` command.
 *
 */

module.exports = function (css) {
  // get current location
  var location = typeof window !== "undefined" && window.location;

  if (!location) {
    throw new Error("fixUrls requires window.location");
  }

	// blank or null?
	if (!css || typeof css !== "string") {
	  return css;
  }

  var baseUrl = location.protocol + "//" + location.host;
  var currentDir = baseUrl + location.pathname.replace(/\/[^\/]*$/, "/");

	// convert each url(...)
	/*
	This regular expression is just a way to recursively match brackets within
	a string.

	 /url\s*\(  = Match on the word "url" with any whitespace after it and then a parens
	   (  = Start a capturing group
	     (?:  = Start a non-capturing group
	         [^)(]  = Match anything that isn't a parentheses
	         |  = OR
	         \(  = Match a start parentheses
	             (?:  = Start another non-capturing groups
	                 [^)(]+  = Match anything that isn't a parentheses
	                 |  = OR
	                 \(  = Match a start parentheses
	                     [^)(]*  = Match anything that isn't a parentheses
	                 \)  = Match a end parentheses
	             )  = End Group
              *\) = Match anything and then a close parens
          )  = Close non-capturing group
          *  = Match anything
       )  = Close capturing group
	 \)  = Match a close parens

	 /gi  = Get all matches, not the first.  Be case insensitive.
	 */
	var fixedCss = css.replace(/url\s*\(((?:[^)(]|\((?:[^)(]+|\([^)(]*\))*\))*)\)/gi, function(fullMatch, origUrl) {
		// strip quotes (if they exist)
		var unquotedOrigUrl = origUrl
			.trim()
			.replace(/^"(.*)"$/, function(o, $1){ return $1; })
			.replace(/^'(.*)'$/, function(o, $1){ return $1; });

		// already a full url? no change
		if (/^(#|data:|http:\/\/|https:\/\/|file:\/\/\/|\s*$)/i.test(unquotedOrigUrl)) {
		  return fullMatch;
		}

		// convert the url to a full url
		var newUrl;

		if (unquotedOrigUrl.indexOf("//") === 0) {
		  	//TODO: should we add protocol?
			newUrl = unquotedOrigUrl;
		} else if (unquotedOrigUrl.indexOf("/") === 0) {
			// path should be relative to the base url
			newUrl = baseUrl + unquotedOrigUrl; // already starts with '/'
		} else {
			// path should be relative to current directory
			newUrl = currentDir + unquotedOrigUrl.replace(/^\.\//, ""); // Strip leading './'
		}

		// send back the fixed url(...)
		return "url(" + JSON.stringify(newUrl) + ")";
	});

	// send back the fixed css
	return fixedCss;
};


/***/ })

/******/ });
});
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly9BQ0NvbnRyb2xzL3dlYnBhY2svdW5pdmVyc2FsTW9kdWxlRGVmaW5pdGlvbiIsIndlYnBhY2s6Ly9BQ0NvbnRyb2xzL3dlYnBhY2svYm9vdHN0cmFwIiwid2VicGFjazovL0FDQ29udHJvbHMvLi9kaXN0L2VzbS9hZGFwdGl2ZWNhcmRzLWNvbnRyb2xzLmNzcz9iM2EyIiwid2VicGFjazovL0FDQ29udHJvbHMvLi9kaXN0L2VzbS9jYWxlbmRhci5qcyIsIndlYnBhY2s6Ly9BQ0NvbnRyb2xzLy4vZGlzdC9lc20vY2hlY2tib3guanMiLCJ3ZWJwYWNrOi8vQUNDb250cm9scy8uL2Rpc3QvZXNtL2NvbGxlY3Rpb24uanMiLCJ3ZWJwYWNrOi8vQUNDb250cm9scy8uL2Rpc3QvZXNtL2NvbnN0YW50cy5qcyIsIndlYnBhY2s6Ly9BQ0NvbnRyb2xzLy4vZGlzdC9lc20vZGF0ZXBpY2tlci5qcyIsIndlYnBhY2s6Ly9BQ0NvbnRyb2xzLy4vZGlzdC9lc20vZHJvcGRvd24uanMiLCJ3ZWJwYWNrOi8vQUNDb250cm9scy8uL2Rpc3QvZXNtL2VudW1zLmpzIiwid2VicGFjazovL0FDQ29udHJvbHMvLi9kaXN0L2VzbS9pbmRleC5qcyIsIndlYnBhY2s6Ly9BQ0NvbnRyb2xzLy4vZGlzdC9lc20vaW5wdXRjb250cm9sLmpzIiwid2VicGFjazovL0FDQ29udHJvbHMvLi9kaXN0L2VzbS9pbnB1dHdpdGhwb3B1cC5qcyIsIndlYnBhY2s6Ly9BQ0NvbnRyb2xzLy4vZGlzdC9lc20vcG9wdXBtZW51LmpzIiwid2VicGFjazovL0FDQ29udHJvbHMvLi9kaXN0L2VzbS9yYWRpb2J1dHRvbi5qcyIsIndlYnBhY2s6Ly9BQ0NvbnRyb2xzLy4vZGlzdC9lc20vdGV4dGJveC5qcyIsIndlYnBhY2s6Ly9BQ0NvbnRyb2xzLy4vZGlzdC9lc20vdXRpbHMuanMiLCJ3ZWJwYWNrOi8vQUNDb250cm9scy8uL2Rpc3QvZXNtL2FkYXB0aXZlY2FyZHMtY29udHJvbHMuY3NzP2I5ZGQiLCJ3ZWJwYWNrOi8vQUNDb250cm9scy8uL25vZGVfbW9kdWxlcy9zdHlsZS1sb2FkZXIvbGliL2FkZFN0eWxlcy5qcyIsIndlYnBhY2s6Ly9BQ0NvbnRyb2xzLy4vbm9kZV9tb2R1bGVzL3N0eWxlLWxvYWRlci9saWIvdXJscy5qcyJdLCJuYW1lcyI6W10sIm1hcHBpbmdzIjoiQUFBQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxDQUFDO0FBQ0QsTztBQ1ZBO0FBQ0E7O0FBRUE7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOzs7QUFHQTtBQUNBOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0Esa0RBQTBDLGdDQUFnQztBQUMxRTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBLGdFQUF3RCxrQkFBa0I7QUFDMUU7QUFDQSx5REFBaUQsY0FBYztBQUMvRDs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsaURBQXlDLGlDQUFpQztBQUMxRSx3SEFBZ0gsbUJBQW1CLEVBQUU7QUFDckk7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQSxtQ0FBMkIsMEJBQTBCLEVBQUU7QUFDdkQseUNBQWlDLGVBQWU7QUFDaEQ7QUFDQTtBQUNBOztBQUVBO0FBQ0EsOERBQXNELCtEQUErRDs7QUFFckg7QUFDQTs7O0FBR0E7QUFDQTs7Ozs7Ozs7Ozs7OztBQ2pGQSxjQUFjLG1CQUFPLENBQUMsNlBBQWlJOztBQUV2Siw0Q0FBNEMsUUFBUzs7QUFFckQ7QUFDQTs7OztBQUlBLGVBQWU7O0FBRWY7QUFDQTs7QUFFQSxhQUFhLG1CQUFPLENBQUMsc0dBQW1EOztBQUV4RTs7QUFFQSxHQUFHLEtBQVUsRUFBRSxFOzs7Ozs7Ozs7Ozs7QUNuQmY7QUFBQTtBQUFBO0FBQUE7QUFBQTtBQUFBO0FB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QTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxtQzs7Ozs7Ozs7Ozs7O0FDbEtBO0FBQUE7QUFBQTtBQUFBO0FBQUE7QUFBQTtBQUFBO0FBQUE7QUFBQTtBQUFBO0FBQUE7QUFBQTtBQUFpQztBQUMxQjtBQUNQO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLGtDQUFrQyxnREFBZTtBQUNqRDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ087QUFDUDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDTztBQUNQO0FBQ0E7QUFDQTtBQUNBO0FBQ087QUFDUDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ087QUFDUDtBQUNBO0FBQ0E7QUFDQTtBQUNPO0FBQ1A7QUFDQTtBQUNPO0FBQ1A7QUFDQTtBQUNPO0FBQ1A7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ087QUFDUDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDTztBQUNQO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLGlDOzs7Ozs7Ozs7OztBQzFHQSx1Qzs7Ozs7Ozs7Ozs7QUNBQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTs7QUFFQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxDQUFDOztBQUVEO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsOENBQThDO0FBQzlDO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLENBQUM7O0FBRUQ7QUFDQTtBQUNBOztBQUVBLGNBQWMsbUJBQU8sQ0FBQyx1REFBUTs7QUFFOUI7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7O0FBRUE7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTs7QUFFQTs7QUFFQTs7QUFFQTtBQUNBOztBQUVBLGlCQUFpQixtQkFBbUI7QUFDcEM7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7O0FBRUEsaUJBQWlCLHNCQUFzQjtBQUN2Qzs7QUFFQTtBQUNBLG1CQUFtQiwyQkFBMkI7O0FBRTlDO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQSxnQkFBZ0IsbUJBQW1CO0FBQ25DO0FBQ0E7O0FBRUE7QUFDQTs7QUFFQSxpQkFBaUIsMkJBQTJCO0FBQzVDO0FBQ0E7O0FBRUEsUUFBUSx1QkFBdUI7QUFDL0I7QUFDQTtBQUNBLEdBQUc7QUFDSDs7QUFFQSxpQkFBaUIsdUJBQXVCO0FBQ3hDO0FBQ0E7O0FBRUEsMkJBQTJCO0FBQzNCO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUEsZ0JBQWdCLGlCQUFpQjtBQUNqQztBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsY0FBYzs7QUFFZCxrREFBa0Qsc0JBQXNCO0FBQ3hFO0FBQ0E7O0FBRUE7QUFDQTs7QUFFQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBO0FBQ0EsRUFBRTtBQUNGO0FBQ0EsRUFBRTtBQUNGO0FBQ0E7QUFDQSxFQUFFO0FBQ0Y7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0EsRUFBRTtBQUNGOztBQUVBO0FBQ0EsS0FBSyxLQUF3QyxFQUFFLEVBRTdDOztBQUVGLFFBQVEsc0JBQWlCO0FBQ3pCOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLE1BQU07QUFDTjtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBOztBQUVBOztBQUVBO0FBQ0E7O0FBRUEsRUFBRTtBQUNGO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBLEVBQUU7QUFDRjtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0EsR0FBRztBQUNIO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTs7QUFFQTtBQUNBO0FBQ0EsQ0FBQzs7QUFFRDtBQUNBOztBQUVBO0FBQ0E7QUFDQSxFQUFFO0FBQ0Y7QUFDQTs7QUFFQTs7QUFFQTtBQUNBO0FBQ0EsR0FBRztBQUNIO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBLEVBQUU7QUFDRjtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBLHVEQUF1RDtBQUN2RDs7QUFFQSw2QkFBNkIsbUJBQW1COztBQUVoRDs7QUFFQTs7QUFFQTtBQUNBOzs7Ozs7Ozs7Ozs7O0FDOVlBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLHdDQUF3QyxXQUFXLEVBQUU7QUFDckQsd0NBQXdDLFdBQVcsRUFBRTs7QUFFckQ7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQSxzQ0FBc0M7QUFDdEMsR0FBRztBQUNIO0FBQ0EsOERBQThEO0FBQzlEOztBQUVBO0FBQ0E7QUFDQSxFQUFFOztBQUVGO0FBQ0E7QUFDQSIsImZpbGUiOiJhZGFwdGl2ZWNhcmRzLWNvbnRyb2xzLmpzIiwic291cmNlc0NvbnRlbnQiOlsiKGZ1bmN0aW9uIHdlYnBhY2tVbml2ZXJzYWxNb2R1bGVEZWZpbml0aW9uKHJvb3QsIGZhY3RvcnkpIHtcblx0aWYodHlwZW9mIGV4cG9ydHMgPT09ICdvYmplY3QnICYmIHR5cGVvZiBtb2R1bGUgPT09ICdvYmplY3QnKVxuXHRcdG1vZHVsZS5leHBvcnRzID0gZmFjdG9yeSgpO1xuXHRlbHNlIGlmKHR5cGVvZiBkZWZpbmUgPT09ICdmdW5jdGlvbicgJiYgZGVmaW5lLmFtZClcblx0XHRkZWZpbmUoXCJBQ0NvbnRyb2xzXCIsIFtdLCBmYWN0b3J5KTtcblx0ZWxzZSBpZih0eXBlb2YgZXhwb3J0cyA9PT0gJ29iamVjdCcpXG5cdFx0ZXhwb3J0c1tcIkFDQ29udHJvbHNcIl0gPSBmYWN0b3J5KCk7XG5cdGVsc2Vcblx0XHRyb290W1wiQUNDb250cm9sc1wiXSA9IGZhY3RvcnkoKTtcbn0pKHRoaXMsIGZ1bmN0aW9uKCkge1xucmV0dXJuICIsIiBcdC8vIFRoZSBtb2R1bGUgY2FjaGVcbiBcdHZhciBpbnN0YWxsZWRNb2R1bGVzID0ge307XG5cbiBcdC8vIFRoZSByZXF1aXJlIGZ1bmN0aW9uXG4gXHRmdW5jdGlvbiBfX3dlYnBhY2tfcmVxdWlyZV9fKG1vZHVsZUlkKSB7XG5cbiBcdFx0Ly8gQ2hlY2sgaWYgbW9kdWxlIGlzIGluIGNhY2hlXG4gXHRcdGlmKGluc3RhbGxlZE1vZHVsZXNbbW9kdWxlSWRdKSB7XG4gXHRcdFx0cmV0dXJuIGluc3RhbGxlZE1vZHVsZXNbbW9kdWxlSWRdLmV4cG9ydHM7XG4gXHRcdH1cbiBcdFx0Ly8gQ3JlYXRlIGEgbmV3IG1vZHVsZSAoYW5kIHB1dCBpdCBpbnRvIHRoZSBjYWNoZSlcbiBcdFx0dmFyIG1vZHVsZSA9IGluc3RhbGxlZE1vZHVsZXNbbW9kdWxlSWRdID0ge1xuIFx0XHRcdGk6IG1vZHVsZUlkLFxuIFx0XHRcdGw6IGZhbHNlLFxuIFx0XHRcdGV4cG9ydHM6IHt9XG4gXHRcdH07XG5cbiBcdFx0Ly8gRXhlY3V0ZSB0aGUgbW9kdWxlIGZ1bmN0aW9uXG4gXHRcdG1vZHVsZXNbbW9kdWxlSWRdLmNhbGwobW9kdWxlLmV4cG9ydHMsIG1vZHVsZSwgbW9kdWxlLmV4cG9ydHMsIF9fd2VicGFja19yZXF1aXJlX18pO1xuXG4gXHRcdC8vIEZsYWcgdGhlIG1vZHVsZSBhcyBsb2FkZWRcbiBcdFx0bW9kdWxlLmwgPSB0cnVlO1xuXG4gXHRcdC8vIFJldHVybiB0aGUgZXhwb3J0cyBvZiB0aGUgbW9kdWxlXG4gXHRcdHJldHVybiBtb2R1bGUuZXhwb3J0cztcbiBcdH1cblxuXG4gXHQvLyBleHBvc2UgdGhlIG1vZHVsZXMgb2JqZWN0IChfX3dlYnBhY2tfbW9kdWxlc19fKVxuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5tID0gbW9kdWxlcztcblxuIFx0Ly8gZXhwb3NlIHRoZSBtb2R1bGUgY2FjaGVcbiBcdF9fd2VicGFja19yZXF1aXJlX18uYyA9IGluc3RhbGxlZE1vZHVsZXM7XG5cbiBcdC8vIGRlZmluZSBnZXR0ZXIgZnVuY3Rpb24gZm9yIGhhcm1vbnkgZXhwb3J0c1xuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5kID0gZnVuY3Rpb24oZXhwb3J0cywgbmFtZSwgZ2V0dGVyKSB7XG4gXHRcdGlmKCFfX3dlYnBhY2tfcmVxdWlyZV9fLm8oZXhwb3J0cywgbmFtZSkpIHtcbiBcdFx0XHRPYmplY3QuZGVmaW5lUHJvcGVydHkoZXhwb3J0cywgbmFtZSwgeyBlbnVtZXJhYmxlOiB0cnVlLCBnZXQ6IGdldHRlciB9KTtcbiBcdFx0fVxuIFx0fTtcblxuIFx0Ly8gZGVmaW5lIF9fZXNNb2R1bGUgb24gZXhwb3J0c1xuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5yID0gZnVuY3Rpb24oZXhwb3J0cykge1xuIFx0XHRpZih0eXBlb2YgU3ltYm9sICE9PSAndW5kZWZpbmVkJyAmJiBTeW1ib2wudG9TdHJpbmdUYWcpIHtcbiBcdFx0XHRPYmplY3QuZGVmaW5lUHJvcGVydHkoZXhwb3J0cywgU3ltYm9sLnRvU3RyaW5nVGFnLCB7IHZhbHVlOiAnTW9kdWxlJyB9KTtcbiBcdFx0fVxuIFx0XHRPYmplY3QuZGVmaW5lUHJvcGVydHkoZXhwb3J0cywgJ19fZXNNb2R1bGUnLCB7IHZhbHVlOiB0cnVlIH0pO1xuIFx0fTtcblxuIFx0Ly8gY3JlYXRlIGEgZmFrZSBuYW1lc3BhY2Ugb2JqZWN0XG4gXHQvLyBtb2RlICYgMTogdmFsdWUgaXMgYSBtb2R1bGUgaWQsIHJlcXVpcmUgaXRcbiBcdC8vIG1vZGUgJiAyOiBtZXJnZSBhbGwgcHJvcGVydGllcyBvZiB2YWx1ZSBpbnRvIHRoZSBuc1xuIFx0Ly8gbW9kZSAmIDQ6IHJldHVybiB2YWx1ZSB3aGVuIGFscmVhZHkgbnMgb2JqZWN0XG4gXHQvLyBtb2RlICYgOHwxOiBiZWhhdmUgbGlrZSByZXF1aXJlXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLnQgPSBmdW5jdGlvbih2YWx1ZSwgbW9kZSkge1xuIFx0XHRpZihtb2RlICYgMSkgdmFsdWUgPSBfX3dlYnBhY2tfcmVxdWlyZV9fKHZhbHVlKTtcbiBcdFx0aWYobW9kZSAmIDgpIHJldHVybiB2YWx1ZTtcbiBcdFx0aWYoKG1vZGUgJiA0KSAmJiB0eXBlb2YgdmFsdWUgPT09ICdvYmplY3QnICYmIHZhbHVlICYmIHZhbHVlLl9fZXNNb2R1bGUpIHJldHVybiB2YWx1ZTtcbiBcdFx0dmFyIG5zID0gT2JqZWN0LmNyZWF0ZShudWxsKTtcbiBcdFx0X193ZWJwYWNrX3JlcXVpcmVfXy5yKG5zKTtcbiBcdFx0T2JqZWN0LmRlZmluZVByb3BlcnR5KG5zLCAnZGVmYXVsdCcsIHsgZW51bWVyYWJsZTogdHJ1ZSwgdmFsdWU6IHZhbHVlIH0pO1xuIFx0XHRpZihtb2RlICYgMiAmJiB0eXBlb2YgdmFsdWUgIT0gJ3N0cmluZycpIGZvcih2YXIga2V5IGluIHZhbHVlKSBfX3dlYnBhY2tfcmVxdWlyZV9fLmQobnMsIGtleSwgZnVuY3Rpb24oa2V5KSB7IHJldHVybiB2YWx1ZVtrZXldOyB9LmJpbmQobnVsbCwga2V5KSk7XG4gXHRcdHJldHVybiBucztcbiBcdH07XG5cbiBcdC8vIGdldERlZmF1bHRFeHBvcnQgZnVuY3Rpb24gZm9yIGNvbXBhdGliaWxpdHkgd2l0aCBub24taGFybW9ueSBtb2R1bGVzXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLm4gPSBmdW5jdGlvbihtb2R1bGUpIHtcbiBcdFx0dmFyIGdldHRlciA9IG1vZHVsZSAmJiBtb2R1bGUuX19lc01vZHVsZSA/XG4gXHRcdFx0ZnVuY3Rpb24gZ2V0RGVmYXVsdCgpIHsgcmV0dXJuIG1vZHVsZVsnZGVmYXVsdCddOyB9IDpcbiBcdFx0XHRmdW5jdGlvbiBnZXRNb2R1bGVFeHBvcnRzKCkgeyByZXR1cm4gbW9kdWxlOyB9O1xuIFx0XHRfX3dlYnBhY2tfcmVxdWlyZV9fLmQoZ2V0dGVyLCAnYScsIGdldHRlcik7XG4gXHRcdHJldHVybiBnZXR0ZXI7XG4gXHR9O1xuXG4gXHQvLyBPYmplY3QucHJvdG90eXBlLmhhc093blByb3BlcnR5LmNhbGxcbiBcdF9fd2VicGFja19yZXF1aXJlX18ubyA9IGZ1bmN0aW9uKG9iamVjdCwgcHJvcGVydHkpIHsgcmV0dXJuIE9iamVjdC5wcm90b3R5cGUuaGFzT3duUHJvcGVydHkuY2FsbChvYmplY3QsIHByb3BlcnR5KTsgfTtcblxuIFx0Ly8gX193ZWJwYWNrX3B1YmxpY19wYXRoX19cbiBcdF9fd2VicGFja19yZXF1aXJlX18ucCA9IFwiL2Rpc3QvXCI7XG5cblxuIFx0Ly8gTG9hZCBlbnRyeSBtb2R1bGUgYW5kIHJldHVybiBleHBvcnRzXG4gXHRyZXR1cm4gX193ZWJwYWNrX3JlcXVpcmVfXyhfX3dlYnBhY2tfcmVxdWlyZV9fLnMgPSBcIi4vZGlzdC9lc20vaW5kZXguanNcIik7XG4iLCJcbnZhciBjb250ZW50ID0gcmVxdWlyZShcIiEhLi4vLi4vbm9kZV9tb2R1bGVzL21pbmktY3NzLWV4dHJhY3QtcGx1Z2luL2Rpc3QvbG9hZGVyLmpzIS4uLy4uL25vZGVfbW9kdWxlcy9jc3MtbG9hZGVyL2luZGV4LmpzIS4vYWRhcHRpdmVjYXJkcy1jb250cm9scy5jc3NcIik7XG5cbmlmKHR5cGVvZiBjb250ZW50ID09PSAnc3RyaW5nJykgY29udGVudCA9IFtbbW9kdWxlLmlkLCBjb250ZW50LCAnJ11dO1xuXG52YXIgdHJhbnNmb3JtO1xudmFyIGluc2VydEludG87XG5cblxuXG52YXIgb3B0aW9ucyA9IHtcImhtclwiOnRydWV9XG5cbm9wdGlvbnMudHJhbnNmb3JtID0gdHJhbnNmb3JtXG5vcHRpb25zLmluc2VydEludG8gPSB1bmRlZmluZWQ7XG5cbnZhciB1cGRhdGUgPSByZXF1aXJlKFwiIS4uLy4uL25vZGVfbW9kdWxlcy9zdHlsZS1sb2FkZXIvbGliL2FkZFN0eWxlcy5qc1wiKShjb250ZW50LCBvcHRpb25zKTtcblxuaWYoY29udGVudC5sb2NhbHMpIG1vZHVsZS5leHBvcnRzID0gY29udGVudC5sb2NhbHM7XG5cbmlmKG1vZHVsZS5ob3QpIHtcblx0bW9kdWxlLmhvdC5hY2NlcHQoXCIhIS4uLy4uL25vZGVfbW9kdWxlcy9taW5pLWNzcy1leHRyYWN0LXBsdWdpbi9kaXN0L2xvYWRlci5qcyEuLi8uLi9ub2RlX21vZHVsZXMvY3NzLWxvYWRlci9pbmRleC5qcyEuL2FkYXB0aXZlY2FyZHMtY29udHJvbHMuY3NzXCIsIGZ1bmN0aW9uKCkge1xuXHRcdHZhciBuZXdDb250ZW50ID0gcmVxdWlyZShcIiEhLi4vLi4vbm9kZV9tb2R1bGVzL21pbmktY3NzLWV4dHJhY3QtcGx1Z2luL2Rpc3QvbG9hZGVyLmpzIS4uLy4uL25vZGVfbW9kdWxlcy9jc3MtbG9hZGVyL2luZGV4LmpzIS4vYWRhcHRpdmVjYXJkcy1jb250cm9scy5jc3NcIik7XG5cblx0XHRpZih0eXBlb2YgbmV3Q29udGVudCA9PT0gJ3N0cmluZycpIG5ld0NvbnRlbnQgPSBbW21vZHVsZS5pZCwgbmV3Q29udGVudCwgJyddXTtcblxuXHRcdHZhciBsb2NhbHMgPSAoZnVuY3Rpb24oYSwgYikge1xuXHRcdFx0dmFyIGtleSwgaWR4ID0gMDtcblxuXHRcdFx0Zm9yKGtleSBpbiBhKSB7XG5cdFx0XHRcdGlmKCFiIHx8IGFba2V5XSAhPT0gYltrZXldKSByZXR1cm4gZmFsc2U7XG5cdFx0XHRcdGlkeCsrO1xuXHRcdFx0fVxuXG5cdFx0XHRmb3Ioa2V5IGluIGIpIGlkeC0tO1xuXG5cdFx0XHRyZXR1cm4gaWR4ID09PSAwO1xuXHRcdH0oY29udGVudC5sb2NhbHMsIG5ld0NvbnRlbnQubG9jYWxzKSk7XG5cblx0XHRpZighbG9jYWxzKSB0aHJvdyBuZXcgRXJyb3IoJ0Fib3J0aW5nIENTUyBITVIgZHVlIHRvIGNoYW5nZWQgY3NzLW1vZHVsZXMgbG9jYWxzLicpO1xuXG5cdFx0dXBkYXRlKG5ld0NvbnRlbnQpO1xuXHR9KTtcblxuXHRtb2R1bGUuaG90LmRpc3Bvc2UoZnVuY3Rpb24oKSB7IHVwZGF0ZSgpOyB9KTtcbn0iLCJpbXBvcnQgKiBhcyBVdGlscyBmcm9tIFwiLi91dGlsc1wiO1xyXG5pbXBvcnQgKiBhcyBDb25zdGFudHMgZnJvbSBcIi4vY29uc3RhbnRzXCI7XHJcbmltcG9ydCB7IElucHV0Q29udHJvbCB9IGZyb20gXCIuL2lucHV0Y29udHJvbFwiO1xyXG5leHBvcnQgY2xhc3MgRGF5Q2VsbCB7XHJcbiAgICBjb25zdHJ1Y3RvcihkYXRlKSB7XHJcbiAgICAgICAgdGhpcy5faXNTdWJkdWVkID0gZmFsc2U7XHJcbiAgICAgICAgdGhpcy5faXNTZWxlY3RlZCA9IGZhbHNlO1xyXG4gICAgICAgIHRoaXMuZGF0ZSA9IGRhdGU7XHJcbiAgICB9XHJcbiAgICBzZWxlY3RlZCgpIHtcclxuICAgICAgICBpZiAodGhpcy5vblNlbGVjdGVkKSB7XHJcbiAgICAgICAgICAgIHRoaXMub25TZWxlY3RlZCh0aGlzKTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICByZW5kZXIoKSB7XHJcbiAgICAgICAgdGhpcy5fZWxlbWVudCA9IGRvY3VtZW50LmNyZWF0ZUVsZW1lbnQoXCJkaXZcIik7XHJcbiAgICAgICAgdGhpcy5fZWxlbWVudC5jbGFzc05hbWUgPSBcIm1zLWN0cmwgbXMtY3RybC1jYWxlbmRhckRheVwiO1xyXG4gICAgICAgIHRoaXMuX2VsZW1lbnQuaW5uZXJUZXh0ID0gdGhpcy5kYXRlLmdldERhdGUoKS50b1N0cmluZygpO1xyXG4gICAgICAgIHRoaXMuX2VsZW1lbnQudGFiSW5kZXggPSAwO1xyXG4gICAgICAgIHRoaXMuX2VsZW1lbnQub25jbGljayA9IChlKSA9PiB7IHRoaXMuc2VsZWN0ZWQoKTsgfTtcclxuICAgICAgICB0aGlzLl9lbGVtZW50Lm9ua2V5ZG93biA9IChlKSA9PiB7XHJcbiAgICAgICAgICAgIGlmIChlLmtleUNvZGUgPT0gQ29uc3RhbnRzLktFWV9FTlRFUikge1xyXG4gICAgICAgICAgICAgICAgdGhpcy5zZWxlY3RlZCgpO1xyXG4gICAgICAgICAgICAgICAgcmV0dXJuIGZhbHNlO1xyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgfTtcclxuICAgICAgICByZXR1cm4gdGhpcy5fZWxlbWVudDtcclxuICAgIH1cclxuICAgIGZvY3VzKCkge1xyXG4gICAgICAgIHRoaXMuX2VsZW1lbnQuZm9jdXMoKTtcclxuICAgIH1cclxuICAgIGdldCBpc1N1YmR1ZWQoKSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX2lzU3ViZHVlZDtcclxuICAgIH1cclxuICAgIHNldCBpc1N1YmR1ZWQodmFsdWUpIHtcclxuICAgICAgICB0aGlzLl9pc1N1YmR1ZWQgPSB2YWx1ZTtcclxuICAgICAgICBpZiAodGhpcy5faXNTdWJkdWVkKSB7XHJcbiAgICAgICAgICAgIHRoaXMuX2VsZW1lbnQuY2xhc3NMaXN0LmFkZChcInN1YmR1ZWRcIik7XHJcbiAgICAgICAgfVxyXG4gICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICB0aGlzLl9lbGVtZW50LmNsYXNzTGlzdC5yZW1vdmUoXCJzdWJkdWVkXCIpO1xyXG4gICAgICAgIH1cclxuICAgIH1cclxuICAgIGdldCBpc1NlbGVjdGVkKCkge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl9pc1NlbGVjdGVkO1xyXG4gICAgfVxyXG4gICAgc2V0IGlzU2VsZWN0ZWQodmFsdWUpIHtcclxuICAgICAgICB0aGlzLl9pc1NlbGVjdGVkID0gdmFsdWU7XHJcbiAgICAgICAgaWYgKHRoaXMuX2lzU2VsZWN0ZWQpIHtcclxuICAgICAgICAgICAgdGhpcy5fZWxlbWVudC5jbGFzc0xpc3QuYWRkKFwic2VsZWN0ZWRcIik7XHJcbiAgICAgICAgfVxyXG4gICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICB0aGlzLl9lbGVtZW50LmNsYXNzTGlzdC5yZW1vdmUoXCJzZWxlY3RlZFwiKTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbn1cclxuZXhwb3J0IGNsYXNzIENhbGVuZGFyIGV4dGVuZHMgSW5wdXRDb250cm9sIHtcclxuICAgIGNvbnN0cnVjdG9yKCkge1xyXG4gICAgICAgIHN1cGVyKCk7XHJcbiAgICAgICAgdGhpcy5fc2VsZWN0ZWREYXkgPSBudWxsO1xyXG4gICAgICAgIHRoaXMuX21pbmlDYWxlbmRhckVsZW1lbnQgPSBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwidGFibGVcIik7XHJcbiAgICAgICAgdGhpcy5fbWluaUNhbGVuZGFyRWxlbWVudC5jbGFzc05hbWUgPSBcIm1zLWN0cmwgbXMtY3RybC1zbGlkZVwiO1xyXG4gICAgICAgIHRoaXMuX21pbmlDYWxlbmRhckVsZW1lbnQuY2VsbFBhZGRpbmcgPSBcIjBweFwiO1xyXG4gICAgICAgIHRoaXMuX21pbmlDYWxlbmRhckVsZW1lbnQuY2VsbFNwYWNpbmcgPSBcIjBweFwiO1xyXG4gICAgICAgIHZhciBtaW5pQ2FsZW5kYXJIZWFkZXIgPSBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwiZGl2XCIpO1xyXG4gICAgICAgIG1pbmlDYWxlbmRhckhlYWRlci5jbGFzc05hbWUgPSBcIm1zLWN0cmwgbXMtY3RybC1jYWxlbmRhckhlYWRlclwiO1xyXG4gICAgICAgIG1pbmlDYWxlbmRhckhlYWRlci5zdHlsZS5kaXNwbGF5ID0gXCJmbGV4XCI7XHJcbiAgICAgICAgdGhpcy5fbW9udGhZZWFyTGFiZWxFbGVtZW50ID0gZG9jdW1lbnQuY3JlYXRlRWxlbWVudChcImRpdlwiKTtcclxuICAgICAgICB0aGlzLl9tb250aFllYXJMYWJlbEVsZW1lbnQuc3R5bGUuZmxleCA9IFwiMSAxIDEwMCVcIjtcclxuICAgICAgICBtaW5pQ2FsZW5kYXJIZWFkZXIuYXBwZW5kQ2hpbGQodGhpcy5fbW9udGhZZWFyTGFiZWxFbGVtZW50KTtcclxuICAgICAgICB2YXIgbmF2QnV0dG9ucyA9IGRvY3VtZW50LmNyZWF0ZUVsZW1lbnQoXCJkaXZcIik7XHJcbiAgICAgICAgbmF2QnV0dG9ucy5zdHlsZS5mbGV4ID0gXCIwIDAgYXV0b1wiO1xyXG4gICAgICAgIHZhciBidXR0b24gPSBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwiaVwiKTtcclxuICAgICAgICBidXR0b24uY2xhc3NOYW1lID0gXCJtcy1pY29uIG1zLWN0cmwtY2FsZW5kYXJOYXZCdXR0b24gbXMtaWNvbi1jaGV2cm9uTGVmdFwiO1xyXG4gICAgICAgIGJ1dHRvbi50YWJJbmRleCA9IDA7XHJcbiAgICAgICAgYnV0dG9uLm9uY2xpY2sgPSAoZSkgPT4ge1xyXG4gICAgICAgICAgICB0aGlzLmRhdGUgPSBVdGlscy5hZGRNb250aHModGhpcy5kYXRlLCAtMSk7XHJcbiAgICAgICAgfTtcclxuICAgICAgICBidXR0b24ub25rZXlkb3duID0gKGUpID0+IHtcclxuICAgICAgICAgICAgaWYgKGUua2V5Q29kZSA9PSBDb25zdGFudHMuS0VZX0VOVEVSKSB7XHJcbiAgICAgICAgICAgICAgICB0aGlzLmRhdGUgPSBVdGlscy5hZGRNb250aHModGhpcy5kYXRlLCAtMSk7XHJcbiAgICAgICAgICAgICAgICByZXR1cm4gZmFsc2U7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICB9O1xyXG4gICAgICAgIG5hdkJ1dHRvbnMuYXBwZW5kQ2hpbGQoYnV0dG9uKTtcclxuICAgICAgICBidXR0b24gPSBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwiaVwiKTtcclxuICAgICAgICBidXR0b24uY2xhc3NOYW1lID0gXCJtcy1pY29uIG1zLWN0cmwtY2FsZW5kYXJOYXZCdXR0b24gbXMtaWNvbi1jaGV2cm9uUmlnaHRcIjtcclxuICAgICAgICBidXR0b24udGFiSW5kZXggPSAwO1xyXG4gICAgICAgIGJ1dHRvbi5vbmNsaWNrID0gKGUpID0+IHtcclxuICAgICAgICAgICAgdGhpcy5kYXRlID0gVXRpbHMuYWRkTW9udGhzKHRoaXMuZGF0ZSwgMSk7XHJcbiAgICAgICAgfTtcclxuICAgICAgICBidXR0b24ub25rZXlkb3duID0gKGUpID0+IHtcclxuICAgICAgICAgICAgaWYgKGUua2V5Q29kZSA9PSBDb25zdGFudHMuS0VZX0VOVEVSKSB7XHJcbiAgICAgICAgICAgICAgICB0aGlzLmRhdGUgPSBVdGlscy5hZGRNb250aHModGhpcy5kYXRlLCAxKTtcclxuICAgICAgICAgICAgICAgIHJldHVybiBmYWxzZTtcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgIH07XHJcbiAgICAgICAgbmF2QnV0dG9ucy5hcHBlbmRDaGlsZChidXR0b24pO1xyXG4gICAgICAgIG1pbmlDYWxlbmRhckhlYWRlci5hcHBlbmRDaGlsZChuYXZCdXR0b25zKTtcclxuICAgICAgICB0aGlzLl9yb290Q29udGFpbmVyRWxlbWVudCA9IGRvY3VtZW50LmNyZWF0ZUVsZW1lbnQoXCJkaXZcIik7XHJcbiAgICAgICAgdGhpcy5fcm9vdENvbnRhaW5lckVsZW1lbnQuY2xhc3NOYW1lID0gXCJtcy1jdHJsIG1zLWN0cmwtY2FsZW5kYXJcIjtcclxuICAgICAgICB0aGlzLl9yb290Q29udGFpbmVyRWxlbWVudC5hcHBlbmRDaGlsZChtaW5pQ2FsZW5kYXJIZWFkZXIpO1xyXG4gICAgICAgIHRoaXMuX3Jvb3RDb250YWluZXJFbGVtZW50LmFwcGVuZENoaWxkKHRoaXMuX21pbmlDYWxlbmRhckVsZW1lbnQpO1xyXG4gICAgICAgIHRoaXMuZGF0ZSA9IG5ldyBEYXRlKCk7XHJcbiAgICB9XHJcbiAgICBnZW5lcmF0ZURheUNlbGxzKGJhc2VEYXRlKSB7XHJcbiAgICAgICAgdGhpcy5fZGF5cyA9IFtdO1xyXG4gICAgICAgIHZhciBpbnB1dE1vbnRoID0gYmFzZURhdGUuZ2V0TW9udGgoKTtcclxuICAgICAgICB2YXIgaW5wdXRZZWFyID0gYmFzZURhdGUuZ2V0RnVsbFllYXIoKTtcclxuICAgICAgICB2YXIgc3RhcnQgPSBuZXcgRGF0ZShpbnB1dFllYXIsIGlucHV0TW9udGgsIDEpO1xyXG4gICAgICAgIHZhciBlbmQgPSBuZXcgRGF0ZShpbnB1dFllYXIsIGlucHV0TW9udGgsIFV0aWxzLmRheXNJbk1vbnRoKGlucHV0WWVhciwgaW5wdXRNb250aCkpO1xyXG4gICAgICAgIHZhciBzdGFydERhdGVEYXlPZldlZWsgPSBzdGFydC5nZXREYXkoKTtcclxuICAgICAgICBpZiAoKHN0YXJ0RGF0ZURheU9mV2VlayAtIFV0aWxzLkNhbGVuZGFyU2V0dGluZ3MuZmlyc3REYXlPZldlZWspID4gMCkge1xyXG4gICAgICAgICAgICBzdGFydCA9IFV0aWxzLmFkZERheXMoc3RhcnQsIFV0aWxzLkNhbGVuZGFyU2V0dGluZ3MuZmlyc3REYXlPZldlZWsgLSBzdGFydERhdGVEYXlPZldlZWspO1xyXG4gICAgICAgIH1cclxuICAgICAgICB2YXIgZW5kRGF0ZURheU9mV2VlayA9IGVuZC5nZXREYXkoKTtcclxuICAgICAgICB2YXIgbGFzdERheU9mV2VlayA9IFV0aWxzLkNhbGVuZGFyU2V0dGluZ3MuZmlyc3REYXlPZldlZWsgKyA2O1xyXG4gICAgICAgIGlmICgobGFzdERheU9mV2VlayAtIGVuZERhdGVEYXlPZldlZWspID4gMCkge1xyXG4gICAgICAgICAgICBlbmQgPSBVdGlscy5hZGREYXlzKGVuZCwgbGFzdERheU9mV2VlayAtIGVuZERhdGVEYXlPZldlZWspO1xyXG4gICAgICAgIH1cclxuICAgICAgICB2YXIgZW5kRGF0ZSA9IGVuZC5nZXREYXRlKCk7XHJcbiAgICAgICAgdmFyIGVuZE1vbnRoID0gZW5kLmdldE1vbnRoKCk7XHJcbiAgICAgICAgdmFyIGVuZFllYXIgPSBlbmQuZ2V0RnVsbFllYXIoKTtcclxuICAgICAgICBkbyB7XHJcbiAgICAgICAgICAgIHZhciBkYXlDZWxsID0gbmV3IERheUNlbGwoc3RhcnQpO1xyXG4gICAgICAgICAgICBkYXlDZWxsLm9uU2VsZWN0ZWQgPSAoY2xpY2tlZENlbGwpID0+IHtcclxuICAgICAgICAgICAgICAgIHRoaXMuc2VsZWN0ZWREYXlDZWxsID0gY2xpY2tlZENlbGw7XHJcbiAgICAgICAgICAgICAgICBpZiAodGhpcy5vbkRhdGVDaGFuZ2VkKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgdGhpcy5vbkRhdGVDaGFuZ2VkKHRoaXMpO1xyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICB9O1xyXG4gICAgICAgICAgICB0aGlzLl9kYXlzLnB1c2goZGF5Q2VsbCk7XHJcbiAgICAgICAgICAgIHZhciBkb25lID0gc3RhcnQuZ2V0RGF0ZSgpID09IGVuZERhdGUgJiYgc3RhcnQuZ2V0TW9udGgoKSA9PSBlbmRNb250aCAmJiBzdGFydC5nZXRGdWxsWWVhcigpID09IGVuZFllYXI7XHJcbiAgICAgICAgICAgIHN0YXJ0ID0gVXRpbHMuYWRkRGF5cyhzdGFydCwgMSk7XHJcbiAgICAgICAgfSB3aGlsZSAoIWRvbmUpO1xyXG4gICAgfVxyXG4gICAgZ2V0IHNlbGVjdGVkRGF5Q2VsbCgpIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5fc2VsZWN0ZWREYXk7XHJcbiAgICB9XHJcbiAgICBzZXQgc2VsZWN0ZWREYXlDZWxsKHZhbHVlKSB7XHJcbiAgICAgICAgaWYgKHRoaXMuX3NlbGVjdGVkRGF5KSB7XHJcbiAgICAgICAgICAgIHRoaXMuX3NlbGVjdGVkRGF5LmlzU2VsZWN0ZWQgPSBmYWxzZTtcclxuICAgICAgICB9XHJcbiAgICAgICAgdGhpcy5fc2VsZWN0ZWREYXkgPSB2YWx1ZTtcclxuICAgICAgICBpZiAodGhpcy5fc2VsZWN0ZWREYXkpIHtcclxuICAgICAgICAgICAgdGhpcy5fc2VsZWN0ZWREYXkuaXNTZWxlY3RlZCA9IHRydWU7XHJcbiAgICAgICAgICAgIHRoaXMuX2RhdGUgPSB0aGlzLl9zZWxlY3RlZERheS5kYXRlO1xyXG4gICAgICAgIH1cclxuICAgIH1cclxuICAgIGluaXRpYWxpemVTZWxlY3Rpb24oKSB7XHJcbiAgICAgICAgaWYgKHRoaXMuX2RhdGUpIHtcclxuICAgICAgICAgICAgZm9yICh2YXIgaSA9IDA7IGkgPCB0aGlzLl9kYXlzLmxlbmd0aDsgaSsrKSB7XHJcbiAgICAgICAgICAgICAgICBpZiAoVXRpbHMuYXJlRGF0ZXNFcXVhbCh0aGlzLl9kYXlzW2ldLmRhdGUsIHRoaXMuZGF0ZSkpIHtcclxuICAgICAgICAgICAgICAgICAgICB0aGlzLnNlbGVjdGVkRGF5Q2VsbCA9IHRoaXMuX2RheXNbaV07XHJcbiAgICAgICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICByZWJ1aWxkTWluaUNhbGVuZGFyKG5ld0RhdGUsIG9sZERhdGUpIHtcclxuICAgICAgICB0aGlzLmdlbmVyYXRlRGF5Q2VsbHMobmV3RGF0ZSk7XHJcbiAgICAgICAgdmFyIG1vbnRoID0gbmV3RGF0ZS5nZXRNb250aCgpO1xyXG4gICAgICAgIHRoaXMuX21pbmlDYWxlbmRhckVsZW1lbnQuaW5uZXJIVE1MID0gXCJcIjtcclxuICAgICAgICB0aGlzLl9taW5pQ2FsZW5kYXJFbGVtZW50LmNsYXNzTGlzdC5yZW1vdmUoXCJtcy1jdHJsLXNsaWRlXCIsIFwibXMtY3RybC1zbGlkZUxlZnRUb1JpZ2h0XCIsIFwibXMtY3RybC1zbGlkZVJpZ2h0VG9MZWZ0XCIpO1xyXG4gICAgICAgIHZhciByb3cgPSBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwidHJcIik7XHJcbiAgICAgICAgdmFyIGRheUluZGV4ID0gVXRpbHMuQ2FsZW5kYXJTZXR0aW5ncy5maXJzdERheU9mV2VlaztcclxuICAgICAgICBmb3IgKHZhciBpID0gMDsgaSA8IFV0aWxzLkNhbGVuZGFyU2V0dGluZ3MuZGF5c0luV2VlazsgaSsrKSB7XHJcbiAgICAgICAgICAgIHZhciBjZWxsID0gZG9jdW1lbnQuY3JlYXRlRWxlbWVudChcInRkXCIpO1xyXG4gICAgICAgICAgICBjZWxsLmNsYXNzTmFtZSA9IFwibXMtY3RybCBtcy1jdHJsLWNhbGVuZGFyRGF5SGVhZGVyXCI7XHJcbiAgICAgICAgICAgIGNlbGwuaW5uZXJUZXh0ID0gVXRpbHMuQ2FsZW5kYXJTZXR0aW5ncy5nZXRJbml0aWFsRGF5TmFtZShkYXlJbmRleCk7XHJcbiAgICAgICAgICAgIHJvdy5hcHBlbmRDaGlsZChjZWxsKTtcclxuICAgICAgICAgICAgZGF5SW5kZXgrKztcclxuICAgICAgICAgICAgaWYgKGRheUluZGV4ID49IFV0aWxzLkNhbGVuZGFyU2V0dGluZ3MuZGF5c0luV2Vlaykge1xyXG4gICAgICAgICAgICAgICAgZGF5SW5kZXggPSAwO1xyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgfVxyXG4gICAgICAgIHRoaXMuX21pbmlDYWxlbmRhckVsZW1lbnQuYXBwZW5kQ2hpbGQocm93KTtcclxuICAgICAgICBmb3IgKHZhciBpID0gMDsgaSA8IHRoaXMuX2RheXMubGVuZ3RoOyBpKyspIHtcclxuICAgICAgICAgICAgaWYgKGkgJSA3ID09IDApIHtcclxuICAgICAgICAgICAgICAgIHJvdyA9IGRvY3VtZW50LmNyZWF0ZUVsZW1lbnQoXCJ0clwiKTtcclxuICAgICAgICAgICAgICAgIHRoaXMuX21pbmlDYWxlbmRhckVsZW1lbnQuYXBwZW5kQ2hpbGQocm93KTtcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICB2YXIgdGFibGVDZWxsID0gZG9jdW1lbnQuY3JlYXRlRWxlbWVudChcInRkXCIpO1xyXG4gICAgICAgICAgICB0YWJsZUNlbGwuYXBwZW5kQ2hpbGQodGhpcy5fZGF5c1tpXS5yZW5kZXIoKSk7XHJcbiAgICAgICAgICAgIGlmICh0aGlzLl9kYXlzW2ldLmRhdGUuZ2V0TW9udGgoKSAhPSBtb250aCkge1xyXG4gICAgICAgICAgICAgICAgdGhpcy5fZGF5c1tpXS5pc1N1YmR1ZWQgPSB0cnVlO1xyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIHJvdy5hcHBlbmRDaGlsZCh0YWJsZUNlbGwpO1xyXG4gICAgICAgIH1cclxuICAgICAgICBpZiAob2xkRGF0ZSkge1xyXG4gICAgICAgICAgICB2YXIgdGltZURlbHRhID0gbmV3RGF0ZS5nZXRUaW1lKCkgLSBvbGREYXRlLmdldFRpbWUoKTtcclxuICAgICAgICAgICAgaWYgKHRpbWVEZWx0YSA+IDApIHtcclxuICAgICAgICAgICAgICAgIHRoaXMuX21pbmlDYWxlbmRhckVsZW1lbnQuY2xhc3NMaXN0LmFkZChcIm1zLWN0cmwtc2xpZGVcIiwgXCJtcy1jdHJsLXNsaWRlUmlnaHRUb0xlZnRcIik7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgZWxzZSBpZiAodGltZURlbHRhIDwgMCkge1xyXG4gICAgICAgICAgICAgICAgdGhpcy5fbWluaUNhbGVuZGFyRWxlbWVudC5jbGFzc0xpc3QuYWRkKFwibXMtY3RybC1zbGlkZVwiLCBcIm1zLWN0cmwtc2xpZGVMZWZ0VG9SaWdodFwiKTtcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgIH1cclxuICAgIH1cclxuICAgIGF0dGFjaChyb290RWxlbWVudCkge1xyXG4gICAgICAgIHN1cGVyLmF0dGFjaChyb290RWxlbWVudCk7XHJcbiAgICAgICAgcm9vdEVsZW1lbnQuaW5uZXJIVE1MID0gXCJcIjtcclxuICAgICAgICByb290RWxlbWVudC5hcHBlbmRDaGlsZCh0aGlzLl9yb290Q29udGFpbmVyRWxlbWVudCk7XHJcbiAgICB9XHJcbiAgICBmb2N1cygpIHtcclxuICAgICAgICBpZiAodGhpcy5fc2VsZWN0ZWREYXkpIHtcclxuICAgICAgICAgICAgdGhpcy5fc2VsZWN0ZWREYXkuZm9jdXMoKTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBnZXQgZGF0ZSgpIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5fZGF0ZTtcclxuICAgIH1cclxuICAgIHNldCBkYXRlKHZhbHVlKSB7XHJcbiAgICAgICAgdmFyIHJlYnVpbGROZWVkZWQgPSB0cnVlO1xyXG4gICAgICAgIHZhciB0aW1lRGVsdGEgPSAwO1xyXG4gICAgICAgIHZhciBuZXdEYXRlID0gdmFsdWUgPyB2YWx1ZSA6IG5ldyBEYXRlKCk7XHJcbiAgICAgICAgaWYgKHRoaXMuX2RhdGUpIHtcclxuICAgICAgICAgICAgcmVidWlsZE5lZWRlZCA9ICF0aGlzLl9kYXlzIHx8IG5ld0RhdGUuZ2V0RnVsbFllYXIoKSAhPSB0aGlzLl9kYXRlLmdldEZ1bGxZZWFyKCkgfHwgbmV3RGF0ZS5nZXRNb250aCgpICE9IHRoaXMuX2RhdGUuZ2V0TW9udGgoKTtcclxuICAgICAgICB9XHJcbiAgICAgICAgaWYgKHJlYnVpbGROZWVkZWQpIHtcclxuICAgICAgICAgICAgdGhpcy5yZWJ1aWxkTWluaUNhbGVuZGFyKG5ld0RhdGUsIHRoaXMuX2RhdGUpO1xyXG4gICAgICAgIH1cclxuICAgICAgICB0aGlzLl9kYXRlID0gbmV3RGF0ZTtcclxuICAgICAgICB0aGlzLmluaXRpYWxpemVTZWxlY3Rpb24oKTtcclxuICAgICAgICB0aGlzLl9tb250aFllYXJMYWJlbEVsZW1lbnQuaW5uZXJUZXh0ID0gVXRpbHMuQ2FsZW5kYXJTZXR0aW5ncy5nZXRMb25nTW9udGhOYW1lKHRoaXMuX2RhdGUuZ2V0TW9udGgoKSkgKyBcIiBcIiArIHRoaXMuX2RhdGUuZ2V0RnVsbFllYXIoKTtcclxuICAgIH1cclxufVxyXG4vLyMgc291cmNlTWFwcGluZ1VSTD1jYWxlbmRhci5qcy5tYXAiLCJpbXBvcnQgKiBhcyBDb25zdGFudHMgZnJvbSBcIi4vY29uc3RhbnRzXCI7XHJcbmltcG9ydCB7IElucHV0Q29udHJvbCB9IGZyb20gXCIuL2lucHV0Y29udHJvbFwiO1xyXG5leHBvcnQgY2xhc3MgQ2hlY2tCb3ggZXh0ZW5kcyBJbnB1dENvbnRyb2wge1xyXG4gICAgY29uc3RydWN0b3IoKSB7XHJcbiAgICAgICAgc3VwZXIoLi4uYXJndW1lbnRzKTtcclxuICAgICAgICB0aGlzLl9sYWJlbCA9IFwiXCI7XHJcbiAgICAgICAgdGhpcy5fY2hlY2tib3hFbGVtZW50ID0gbnVsbDtcclxuICAgICAgICB0aGlzLl9zcGFuRWxlbWVudCA9IG51bGw7XHJcbiAgICB9XHJcbiAgICBzdGF0aWMgY3JlYXRlSWQoKSB7XHJcbiAgICAgICAgdmFyIHJlc3VsdCA9IENoZWNrQm94LmNyZWF0aW9uSW5kZXg7XHJcbiAgICAgICAgQ2hlY2tCb3guY3JlYXRpb25JbmRleCsrO1xyXG4gICAgICAgIHJldHVybiByZXN1bHQ7XHJcbiAgICB9XHJcbiAgICBjaGFuZ2VkKCkge1xyXG4gICAgICAgIGlmICh0aGlzLm9uQ2hhbmdlKSB7XHJcbiAgICAgICAgICAgIHRoaXMub25DaGFuZ2UodGhpcyk7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG4gICAga2V5RG93bihlKSB7XHJcbiAgICAgICAgc3dpdGNoIChlLmtleUNvZGUpIHtcclxuICAgICAgICAgICAgY2FzZSBDb25zdGFudHMuS0VZX0VOVEVSOlxyXG4gICAgICAgICAgICAgICAgdGhpcy5pc0NoZWNrZWQgPSAhdGhpcy5pc0NoZWNrZWQ7XHJcbiAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBhdHRhY2gocm9vdEVsZW1lbnQpIHtcclxuICAgICAgICBzdXBlci5hdHRhY2gocm9vdEVsZW1lbnQpO1xyXG4gICAgICAgIHJvb3RFbGVtZW50LmNsYXNzTmFtZSA9IFwibXMtY3RybCBtcy1jdHJsLWNoZWNrYm94XCI7XHJcbiAgICAgICAgcm9vdEVsZW1lbnQudGFiSW5kZXggPSAwO1xyXG4gICAgICAgIHZhciBsYWJlbEF0dHJpYnV0ZSA9IHJvb3RFbGVtZW50LmF0dHJpYnV0ZXNbXCJsYWJlbFwiXTtcclxuICAgICAgICBpZiAobGFiZWxBdHRyaWJ1dGUpIHtcclxuICAgICAgICAgICAgdGhpcy5fbGFiZWwgPSBsYWJlbEF0dHJpYnV0ZS52YWx1ZTtcclxuICAgICAgICB9XHJcbiAgICAgICAgdmFyIGlzQ2hlY2tlZEF0dHJpYnV0ZSA9IHJvb3RFbGVtZW50LmF0dHJpYnV0ZXNbXCJpc2NoZWNrZWRcIl07XHJcbiAgICAgICAgaWYgKGlzQ2hlY2tlZEF0dHJpYnV0ZSkge1xyXG4gICAgICAgICAgICB0aGlzLl9pc0NoZWNrZWQgPSBpc0NoZWNrZWRBdHRyaWJ1dGUudmFsdWUgPT09IFwidHJ1ZVwiO1xyXG4gICAgICAgIH1cclxuICAgICAgICB0aGlzLl9jaGVja2JveEVsZW1lbnQgPSBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwiaW5wdXRcIik7XHJcbiAgICAgICAgdGhpcy5fY2hlY2tib3hFbGVtZW50LmlkID0gXCJtcy1jdHJsLWNoZWNrYm94LVwiICsgQ2hlY2tCb3guY3JlYXRlSWQoKTtcclxuICAgICAgICB0aGlzLl9jaGVja2JveEVsZW1lbnQudHlwZSA9IFwiY2hlY2tib3hcIjtcclxuICAgICAgICB0aGlzLl9jaGVja2JveEVsZW1lbnQuc3R5bGUucG9zaXRpb24gPSBcImFic29sdXRlXCI7XHJcbiAgICAgICAgdGhpcy5fY2hlY2tib3hFbGVtZW50LmNoZWNrZWQgPSB0aGlzLmlzQ2hlY2tlZDtcclxuICAgICAgICB0aGlzLl9jaGVja2JveEVsZW1lbnQub25jaGFuZ2UgPSAoZSkgPT4geyB0aGlzLmNoYW5nZWQoKTsgfTtcclxuICAgICAgICB2YXIgbGFiZWxFbGVtZW50ID0gZG9jdW1lbnQuY3JlYXRlRWxlbWVudChcImxhYmVsXCIpO1xyXG4gICAgICAgIGxhYmVsRWxlbWVudC5odG1sRm9yID0gdGhpcy5fY2hlY2tib3hFbGVtZW50LmlkO1xyXG4gICAgICAgIHRoaXMuX3NwYW5FbGVtZW50ID0gZG9jdW1lbnQuY3JlYXRlRWxlbWVudChcInNwYW5cIik7XHJcbiAgICAgICAgdGhpcy5fc3BhbkVsZW1lbnQuaW5uZXJUZXh0ID0gdGhpcy5fbGFiZWw7XHJcbiAgICAgICAgbGFiZWxFbGVtZW50LmFwcGVuZENoaWxkKHRoaXMuX3NwYW5FbGVtZW50KTtcclxuICAgICAgICByb290RWxlbWVudC5pbm5lckhUTUwgPSBcIlwiO1xyXG4gICAgICAgIHJvb3RFbGVtZW50LmFwcGVuZENoaWxkKHRoaXMuX2NoZWNrYm94RWxlbWVudCk7XHJcbiAgICAgICAgcm9vdEVsZW1lbnQuYXBwZW5kQ2hpbGQobGFiZWxFbGVtZW50KTtcclxuICAgIH1cclxuICAgIGdldCBsYWJlbCgpIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5fbGFiZWw7XHJcbiAgICB9XHJcbiAgICBzZXQgbGFiZWwodmFsdWUpIHtcclxuICAgICAgICB0aGlzLl9sYWJlbCA9IHZhbHVlO1xyXG4gICAgICAgIGlmICh0aGlzLl9zcGFuRWxlbWVudCkge1xyXG4gICAgICAgICAgICB0aGlzLl9zcGFuRWxlbWVudC5pbm5lclRleHQgPSB0aGlzLl9sYWJlbDtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBnZXQgaXNDaGVja2VkKCkge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl9pc0NoZWNrZWQ7XHJcbiAgICB9XHJcbiAgICBzZXQgaXNDaGVja2VkKHZhbHVlKSB7XHJcbiAgICAgICAgaWYgKHRoaXMuX2lzQ2hlY2tlZCAhPSB2YWx1ZSkge1xyXG4gICAgICAgICAgICB0aGlzLl9pc0NoZWNrZWQgPSB2YWx1ZTtcclxuICAgICAgICAgICAgaWYgKHRoaXMuX2NoZWNrYm94RWxlbWVudCkge1xyXG4gICAgICAgICAgICAgICAgdGhpcy5fY2hlY2tib3hFbGVtZW50LmNoZWNrZWQgPSB0aGlzLl9pc0NoZWNrZWQ7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgdGhpcy5jaGFuZ2VkKCk7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG59XHJcbi8vIFVzZWQgdG8gZ2VuZXJhdGUgdW5pcXVlIElkc1xyXG5DaGVja0JveC5jcmVhdGlvbkluZGV4ID0gMDtcclxuLy8jIHNvdXJjZU1hcHBpbmdVUkw9Y2hlY2tib3guanMubWFwIiwiZXhwb3J0IGNsYXNzIENvbGxlY3Rpb24ge1xyXG4gICAgY29uc3RydWN0b3IoKSB7XHJcbiAgICAgICAgdGhpcy5faXRlbXMgPSBbXTtcclxuICAgICAgICB0aGlzLm9uSXRlbUFkZGVkID0gbnVsbDtcclxuICAgICAgICB0aGlzLm9uSXRlbVJlbW92ZWQgPSBudWxsO1xyXG4gICAgfVxyXG4gICAgZ2V0KGluZGV4KSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX2l0ZW1zW2luZGV4XTtcclxuICAgIH1cclxuICAgIGFkZChpdGVtKSB7XHJcbiAgICAgICAgdGhpcy5faXRlbXMucHVzaChpdGVtKTtcclxuICAgICAgICBpZiAodGhpcy5vbkl0ZW1BZGRlZCkge1xyXG4gICAgICAgICAgICB0aGlzLm9uSXRlbUFkZGVkKGl0ZW0pO1xyXG4gICAgICAgIH1cclxuICAgIH1cclxuICAgIHJlbW92ZShpdGVtKSB7XHJcbiAgICAgICAgdmFyIGkgPSB0aGlzLl9pdGVtcy5pbmRleE9mKGl0ZW0pO1xyXG4gICAgICAgIGlmIChpID49IDApIHtcclxuICAgICAgICAgICAgdGhpcy5faXRlbXMgPSB0aGlzLl9pdGVtcy5zcGxpY2UoaSwgMSk7XHJcbiAgICAgICAgICAgIGlmICh0aGlzLm9uSXRlbVJlbW92ZWQpIHtcclxuICAgICAgICAgICAgICAgIHRoaXMub25JdGVtUmVtb3ZlZChpdGVtKTtcclxuICAgICAgICAgICAgfVxyXG4gICAgICAgIH1cclxuICAgIH1cclxuICAgIGluZGV4T2YoaXRlbSkge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl9pdGVtcy5pbmRleE9mKGl0ZW0pO1xyXG4gICAgfVxyXG4gICAgZ2V0IGxlbmd0aCgpIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5faXRlbXMubGVuZ3RoO1xyXG4gICAgfVxyXG59XHJcbi8vIyBzb3VyY2VNYXBwaW5nVVJMPWNvbGxlY3Rpb24uanMubWFwIiwiZXhwb3J0IGNvbnN0IEtFWV9UQUIgPSA5O1xyXG5leHBvcnQgY29uc3QgS0VZX0VOVEVSID0gMTM7XHJcbmV4cG9ydCBjb25zdCBLRVlfRVNDQVBFID0gMjc7XHJcbmV4cG9ydCBjb25zdCBLRVlfVVAgPSAzODtcclxuZXhwb3J0IGNvbnN0IEtFWV9ET1dOID0gNDA7XHJcbmV4cG9ydCBjb25zdCBLRVlfREVMRVRFID0gNDY7XHJcbi8vIyBzb3VyY2VNYXBwaW5nVVJMPWNvbnN0YW50cy5qcy5tYXAiLCJpbXBvcnQgeyBJbnB1dFdpdGhQb3B1cCwgUG9wdXBDb250cm9sIH0gZnJvbSBcIi4vaW5wdXR3aXRocG9wdXBcIjtcclxuaW1wb3J0IHsgQ2FsZW5kYXIgfSBmcm9tIFwiLi9jYWxlbmRhclwiO1xyXG5leHBvcnQgY2xhc3MgQ2FsZW5kYXJQb3B1cENvbnRyb2wgZXh0ZW5kcyBQb3B1cENvbnRyb2wge1xyXG4gICAgY29uc3RydWN0b3Iob3duZXIpIHtcclxuICAgICAgICBzdXBlcigpO1xyXG4gICAgICAgIHRoaXMuX293bmVyID0gb3duZXI7XHJcbiAgICB9XHJcbiAgICByZW5kZXJDb250ZW50KCkge1xyXG4gICAgICAgIHZhciBlbGVtZW50ID0gZG9jdW1lbnQuY3JlYXRlRWxlbWVudChcImRpdlwiKTtcclxuICAgICAgICBlbGVtZW50LmNsYXNzTmFtZSA9IFwibXMtY3RybCBtcy1jYWxlbmRhclBvcHVwXCI7XHJcbiAgICAgICAgdGhpcy5fY2FsZW5kYXIgPSBuZXcgQ2FsZW5kYXIoKTtcclxuICAgICAgICB0aGlzLl9jYWxlbmRhci5kYXRlID0gdGhpcy5fb3duZXIudmFsdWU7XHJcbiAgICAgICAgdGhpcy5fY2FsZW5kYXIub25EYXRlQ2hhbmdlZCA9IChjKSA9PiB7XHJcbiAgICAgICAgICAgIHRoaXMuX293bmVyLnZhbHVlID0gYy5kYXRlO1xyXG4gICAgICAgICAgICB0aGlzLmNsb3NlKCk7XHJcbiAgICAgICAgfTtcclxuICAgICAgICB0aGlzLl9jYWxlbmRhci5hdHRhY2goZWxlbWVudCk7XHJcbiAgICAgICAgcmV0dXJuIGVsZW1lbnQ7XHJcbiAgICB9XHJcbiAgICBmb2N1cygpIHtcclxuICAgICAgICBpZiAodGhpcy5fY2FsZW5kYXIpIHtcclxuICAgICAgICAgICAgdGhpcy5fY2FsZW5kYXIuZm9jdXMoKTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbn1cclxuZXhwb3J0IGNsYXNzIERhdGVQaWNrZXIgZXh0ZW5kcyBJbnB1dFdpdGhQb3B1cCB7XHJcbiAgICB2YWxpZGF0ZVJvb3RFbGVtZW50KHJvb3RFbGVtZW50KSB7XHJcbiAgICAgICAgaWYgKCEocm9vdEVsZW1lbnQgaW5zdGFuY2VvZiBIVE1MRGl2RWxlbWVudCkpIHtcclxuICAgICAgICAgICAgdGhyb3cgbmV3IEVycm9yKFwiRGF0ZVBpY2tlciByZXF1aXJlcyBhIERJViBlbGVtZW50IGFzIGl0cyByb290LlwiKTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBjcmVhdGVQb3B1cENvbnRyb2woKSB7XHJcbiAgICAgICAgcmV0dXJuIG5ldyBDYWxlbmRhclBvcHVwQ29udHJvbCh0aGlzKTtcclxuICAgIH1cclxuICAgIGdldFZhbHVlQXNTdHJpbmcoKSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMudmFsdWUudG9Mb2NhbGVEYXRlU3RyaW5nKCk7XHJcbiAgICB9XHJcbiAgICBnZXRDc3NDbGFzc05hbWUoKSB7XHJcbiAgICAgICAgcmV0dXJuIFwibXMtY3RybCBtcy1jdHJsLWRhdGVQaWNrZXJcIjtcclxuICAgIH1cclxuICAgIGdldEJ1dHRvbkljb25Dc3NDbGFzc05hbWUoKSB7XHJcbiAgICAgICAgcmV0dXJuIFwibXMtaWNvbi1jYWxlbmRhclwiO1xyXG4gICAgfVxyXG4gICAgcG9wdXAoKSB7XHJcbiAgICAgICAgc3VwZXIucG9wdXAoKTtcclxuICAgICAgICBpZiAodGhpcy5pc09wZW4pIHtcclxuICAgICAgICAgICAgdGhpcy5wb3B1cENvbnRyb2wuZm9jdXMoKTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbn1cclxuLy8jIHNvdXJjZU1hcHBpbmdVUkw9ZGF0ZXBpY2tlci5qcy5tYXAiLCJpbXBvcnQgKiBhcyBDb25zdGFudHMgZnJvbSBcIi4vY29uc3RhbnRzXCI7XHJcbmltcG9ydCB7IENvbGxlY3Rpb24gfSBmcm9tIFwiLi9jb2xsZWN0aW9uXCI7XHJcbmltcG9ydCB7IElucHV0V2l0aFBvcHVwLCBQb3B1cENvbnRyb2wgfSBmcm9tIFwiLi9pbnB1dHdpdGhwb3B1cFwiO1xyXG5leHBvcnQgY2xhc3MgRHJvcERvd25JdGVtIHtcclxuICAgIGNsaWNrKCkge1xyXG4gICAgICAgIGlmICh0aGlzLm9uQ2xpY2spIHtcclxuICAgICAgICAgICAgdGhpcy5vbkNsaWNrKHRoaXMpO1xyXG4gICAgICAgIH1cclxuICAgIH1cclxuICAgIGNvbnN0cnVjdG9yKGtleSwgdmFsdWUpIHtcclxuICAgICAgICB0aGlzLmtleSA9IGtleTtcclxuICAgICAgICB0aGlzLl92YWx1ZSA9IHZhbHVlO1xyXG4gICAgfVxyXG4gICAgdG9TdHJpbmcoKSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMudmFsdWU7XHJcbiAgICB9XHJcbiAgICByZW5kZXIoKSB7XHJcbiAgICAgICAgaWYgKCF0aGlzLl9lbGVtZW50KSB7XHJcbiAgICAgICAgICAgIHRoaXMuX2VsZW1lbnQgPSBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwic3BhblwiKTtcclxuICAgICAgICAgICAgdGhpcy5fZWxlbWVudC5jbGFzc05hbWUgPSBcIm1zLWN0cmwgbXMtY3RybC1kcm9wZG93bi1pdGVtXCI7XHJcbiAgICAgICAgICAgIHRoaXMuX2VsZW1lbnQuaW5uZXJUZXh0ID0gdGhpcy52YWx1ZTtcclxuICAgICAgICAgICAgdGhpcy5fZWxlbWVudC5vbm1vdXNldXAgPSAoZSkgPT4geyB0aGlzLmNsaWNrKCk7IH07XHJcbiAgICAgICAgfVxyXG4gICAgICAgIHJldHVybiB0aGlzLl9lbGVtZW50O1xyXG4gICAgfVxyXG4gICAgZ2V0IHZhbHVlKCkge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl92YWx1ZTtcclxuICAgIH1cclxuICAgIHNldCB2YWx1ZShuZXdWYWx1ZSkge1xyXG4gICAgICAgIHRoaXMuX3ZhbHVlID0gbmV3VmFsdWU7XHJcbiAgICAgICAgaWYgKHRoaXMuX2VsZW1lbnQpIHtcclxuICAgICAgICAgICAgdGhpcy5fZWxlbWVudC5pbm5lclRleHQgPSBuZXdWYWx1ZTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbn1cclxuZXhwb3J0IGNsYXNzIERyb3BEb3duUG9wdXBDb250cm9sIGV4dGVuZHMgUG9wdXBDb250cm9sIHtcclxuICAgIGNvbnN0cnVjdG9yKG93bmVyKSB7XHJcbiAgICAgICAgc3VwZXIoKTtcclxuICAgICAgICB0aGlzLl9yZW5kZXJlZEl0ZW1zID0gW107XHJcbiAgICAgICAgdGhpcy5fc2VsZWN0ZWRJbmRleCA9IC0xO1xyXG4gICAgICAgIHRoaXMuX293bmVyID0gb3duZXI7XHJcbiAgICB9XHJcbiAgICByZW5kZXJDb250ZW50KCkge1xyXG4gICAgICAgIHZhciBlbGVtZW50ID0gZG9jdW1lbnQuY3JlYXRlRWxlbWVudChcImRpdlwiKTtcclxuICAgICAgICBlbGVtZW50LmNsYXNzTmFtZSA9IFwibXMtY3RybCBtcy1wb3B1cFwiO1xyXG4gICAgICAgIHZhciBzZWxlY3RlZEluZGV4ID0gdGhpcy5fb3duZXIuc2VsZWN0ZWRJbmRleDtcclxuICAgICAgICBmb3IgKHZhciBpID0gMDsgaSA8IHRoaXMuX293bmVyLml0ZW1zLmxlbmd0aDsgaSsrKSB7XHJcbiAgICAgICAgICAgIHZhciByZW5kZXJlZEl0ZW0gPSB0aGlzLl9vd25lci5pdGVtcy5nZXQoaSkucmVuZGVyKCk7XHJcbiAgICAgICAgICAgIHJlbmRlcmVkSXRlbS50YWJJbmRleCA9IDA7XHJcbiAgICAgICAgICAgIGVsZW1lbnQuYXBwZW5kQ2hpbGQocmVuZGVyZWRJdGVtKTtcclxuICAgICAgICAgICAgaWYgKGkgPT0gc2VsZWN0ZWRJbmRleCkge1xyXG4gICAgICAgICAgICAgICAgcmVuZGVyZWRJdGVtLmZvY3VzKCk7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgdGhpcy5fcmVuZGVyZWRJdGVtcy5wdXNoKHJlbmRlcmVkSXRlbSk7XHJcbiAgICAgICAgfVxyXG4gICAgICAgIHJldHVybiBlbGVtZW50O1xyXG4gICAgfVxyXG4gICAga2V5RG93bihlKSB7XHJcbiAgICAgICAgc3VwZXIua2V5RG93bihlKTtcclxuICAgICAgICB2YXIgc2VsZWN0ZWRJdGVtSW5kZXggPSB0aGlzLl9zZWxlY3RlZEluZGV4O1xyXG4gICAgICAgIHN3aXRjaCAoZS5rZXlDb2RlKSB7XHJcbiAgICAgICAgICAgIGNhc2UgQ29uc3RhbnRzLktFWV9UQUI6XHJcbiAgICAgICAgICAgICAgICB0aGlzLmNsb3NlKCk7XHJcbiAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgY2FzZSBDb25zdGFudHMuS0VZX0VOVEVSOlxyXG4gICAgICAgICAgICAgICAgaWYgKHRoaXMuc2VsZWN0ZWRJbmRleCA+PSAwKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgdGhpcy5fb3duZXIuc2VsZWN0ZWRJbmRleCA9IHRoaXMuc2VsZWN0ZWRJbmRleDtcclxuICAgICAgICAgICAgICAgICAgICB0aGlzLmNsb3NlKCk7XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICAgICAgY2FzZSBDb25zdGFudHMuS0VZX1VQOlxyXG4gICAgICAgICAgICAgICAgaWYgKHNlbGVjdGVkSXRlbUluZGV4IDw9IDApIHtcclxuICAgICAgICAgICAgICAgICAgICBzZWxlY3RlZEl0ZW1JbmRleCA9IHRoaXMuX3JlbmRlcmVkSXRlbXMubGVuZ3RoIC0gMTtcclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgIHNlbGVjdGVkSXRlbUluZGV4LS07XHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKHNlbGVjdGVkSXRlbUluZGV4IDwgMCkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBzZWxlY3RlZEl0ZW1JbmRleCA9IHRoaXMuX3JlbmRlcmVkSXRlbXMubGVuZ3RoIC0gMTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICB0aGlzLnNlbGVjdGVkSW5kZXggPSBzZWxlY3RlZEl0ZW1JbmRleDtcclxuICAgICAgICAgICAgICAgIGUuY2FuY2VsQnViYmxlID0gdHJ1ZTtcclxuICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICBjYXNlIENvbnN0YW50cy5LRVlfRE9XTjpcclxuICAgICAgICAgICAgICAgIGlmIChzZWxlY3RlZEl0ZW1JbmRleCA8IDApIHtcclxuICAgICAgICAgICAgICAgICAgICBzZWxlY3RlZEl0ZW1JbmRleCA9IDA7XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICBzZWxlY3RlZEl0ZW1JbmRleCsrO1xyXG4gICAgICAgICAgICAgICAgICAgIGlmIChzZWxlY3RlZEl0ZW1JbmRleCA+PSB0aGlzLl9yZW5kZXJlZEl0ZW1zLmxlbmd0aCkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBzZWxlY3RlZEl0ZW1JbmRleCA9IDA7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgdGhpcy5zZWxlY3RlZEluZGV4ID0gc2VsZWN0ZWRJdGVtSW5kZXg7XHJcbiAgICAgICAgICAgICAgICBlLmNhbmNlbEJ1YmJsZSA9IHRydWU7XHJcbiAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICByZW5kZXIocm9vdEVsZW1lbnRCb3VuZHMpIHtcclxuICAgICAgICB2YXIgcmVuZGVyZWRFbGVtZW50ID0gc3VwZXIucmVuZGVyKHJvb3RFbGVtZW50Qm91bmRzKTtcclxuICAgICAgICByZW5kZXJlZEVsZW1lbnQuc3R5bGUubWluV2lkdGggPSAocm9vdEVsZW1lbnRCb3VuZHMud2lkdGggLyAyKSArIFwicHhcIjtcclxuICAgICAgICByZW5kZXJlZEVsZW1lbnQuc3R5bGUubWF4V2lkdGggPSByb290RWxlbWVudEJvdW5kcy53aWR0aCArIFwicHhcIjtcclxuICAgICAgICByZXR1cm4gcmVuZGVyZWRFbGVtZW50O1xyXG4gICAgfVxyXG4gICAgZ2V0IHNlbGVjdGVkSW5kZXgoKSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX3NlbGVjdGVkSW5kZXg7XHJcbiAgICB9XHJcbiAgICBzZXQgc2VsZWN0ZWRJbmRleChpbmRleCkge1xyXG4gICAgICAgIGlmIChpbmRleCA+PSAwICYmIGluZGV4IDwgdGhpcy5fcmVuZGVyZWRJdGVtcy5sZW5ndGgpIHtcclxuICAgICAgICAgICAgdGhpcy5fcmVuZGVyZWRJdGVtc1tpbmRleF0uZm9jdXMoKTtcclxuICAgICAgICAgICAgdGhpcy5fc2VsZWN0ZWRJbmRleCA9IGluZGV4O1xyXG4gICAgICAgIH1cclxuICAgIH1cclxufVxyXG5leHBvcnQgY2xhc3MgRHJvcERvd24gZXh0ZW5kcyBJbnB1dFdpdGhQb3B1cCB7XHJcbiAgICBpdGVtQ2xpY2tlZChpdGVtKSB7XHJcbiAgICAgICAgdGhpcy5zZWxlY3RlZEl0ZW0gPSBpdGVtO1xyXG4gICAgICAgIHRoaXMuY2xvc2VQb3B1cCgpO1xyXG4gICAgICAgIHRoaXMucm9vdEVsZW1lbnQuZm9jdXMoKTtcclxuICAgIH1cclxuICAgIHZhbGlkYXRlUm9vdEVsZW1lbnQocm9vdEVsZW1lbnQpIHtcclxuICAgICAgICBpZiAoIShyb290RWxlbWVudCBpbnN0YW5jZW9mIEhUTUxEaXZFbGVtZW50KSkge1xyXG4gICAgICAgICAgICB0aHJvdyBuZXcgRXJyb3IoXCJEcm9wRG93biByZXF1aXJlcyBhIERJViBlbGVtZW50IGFzIGl0cyByb290LlwiKTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBjcmVhdGVQb3B1cENvbnRyb2woKSB7XHJcbiAgICAgICAgcmV0dXJuIG5ldyBEcm9wRG93blBvcHVwQ29udHJvbCh0aGlzKTtcclxuICAgIH1cclxuICAgIGdldENzc0NsYXNzTmFtZSgpIHtcclxuICAgICAgICByZXR1cm4gXCJtcy1jdHJsIG1zLWN0cmwtZHJvcGRvd25cIjtcclxuICAgIH1cclxuICAgIGNvbnN0cnVjdG9yKCkge1xyXG4gICAgICAgIHN1cGVyKCk7XHJcbiAgICAgICAgdGhpcy5faXRlbXMgPSBuZXcgQ29sbGVjdGlvbigpO1xyXG4gICAgICAgIHRoaXMuX2l0ZW1zLm9uSXRlbUFkZGVkID0gKGl0ZW0pID0+IHsgaXRlbS5vbkNsaWNrID0gKGNsaWNrZWRJdGVtKSA9PiB7IHRoaXMuaXRlbUNsaWNrZWQoY2xpY2tlZEl0ZW0pOyB9OyB9O1xyXG4gICAgICAgIHRoaXMuX2l0ZW1zLm9uSXRlbVJlbW92ZWQgPSAoaXRlbSkgPT4geyBpdGVtLm9uQ2xpY2sgPSBudWxsOyB9O1xyXG4gICAgfVxyXG4gICAgYXR0YWNoKHJvb3RFbGVtZW50KSB7XHJcbiAgICAgICAgc3VwZXIuYXR0YWNoKHJvb3RFbGVtZW50KTtcclxuICAgICAgICBmb3IgKHZhciBpID0gMDsgaSA8IHRoaXMucm9vdEVsZW1lbnQuY2hpbGRyZW4ubGVuZ3RoOyBpKyspIHtcclxuICAgICAgICAgICAgdmFyIGNoaWxkRWxlbWVudCA9IHRoaXMucm9vdEVsZW1lbnQuY2hpbGRyZW5baV07XHJcbiAgICAgICAgICAgIGlmIChjaGlsZEVsZW1lbnQudGFnTmFtZS50b0xvd2VyQ2FzZSgpID09IFwibXMtZHJvcGRvd24taXRlbVwiKSB7XHJcbiAgICAgICAgICAgICAgICB2YXIgaXRlbSA9IG5ldyBEcm9wRG93bkl0ZW0oY2hpbGRFbGVtZW50LmF0dHJpYnV0ZXMuZ2V0TmFtZWRJdGVtKFwia2V5XCIpLnZhbHVlLCBjaGlsZEVsZW1lbnQuYXR0cmlidXRlcy5nZXROYW1lZEl0ZW0oXCJ2YWx1ZVwiKS52YWx1ZSk7XHJcbiAgICAgICAgICAgICAgICB0aGlzLl9pdGVtcy5hZGQoaXRlbSk7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBwb3B1cCgpIHtcclxuICAgICAgICBzdXBlci5wb3B1cCgpO1xyXG4gICAgICAgIHRoaXMucG9wdXBDb250cm9sLnNlbGVjdGVkSW5kZXggPSB0aGlzLnNlbGVjdGVkSW5kZXg7XHJcbiAgICB9XHJcbiAgICBnZXQgaXRlbXMoKSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX2l0ZW1zO1xyXG4gICAgfVxyXG4gICAgZ2V0IHNlbGVjdGVkSXRlbSgpIHtcclxuICAgICAgICByZXR1cm4gdGhpcy52YWx1ZTtcclxuICAgIH1cclxuICAgIHNldCBzZWxlY3RlZEl0ZW0obmV3VmFsdWUpIHtcclxuICAgICAgICB0aGlzLnZhbHVlID0gbmV3VmFsdWU7XHJcbiAgICB9XHJcbiAgICBnZXQgc2VsZWN0ZWRJbmRleCgpIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5pdGVtcy5pbmRleE9mKHRoaXMudmFsdWUpO1xyXG4gICAgfVxyXG4gICAgc2V0IHNlbGVjdGVkSW5kZXgoaW5kZXgpIHtcclxuICAgICAgICBpZiAoaW5kZXggPj0gMCAmJiB0aGlzLml0ZW1zLmxlbmd0aCA+IGluZGV4KSB7XHJcbiAgICAgICAgICAgIHRoaXMuc2VsZWN0ZWRJdGVtID0gdGhpcy5pdGVtcy5nZXQoaW5kZXgpO1xyXG4gICAgICAgIH1cclxuICAgIH1cclxufVxyXG4vLyMgc291cmNlTWFwcGluZ1VSTD1kcm9wZG93bi5qcy5tYXAiLCJleHBvcnQgdmFyIERheU9mV2VlaztcclxuKGZ1bmN0aW9uIChEYXlPZldlZWspIHtcclxuICAgIERheU9mV2Vla1tEYXlPZldlZWtbXCJTdW5kYXlcIl0gPSAwXSA9IFwiU3VuZGF5XCI7XHJcbiAgICBEYXlPZldlZWtbRGF5T2ZXZWVrW1wiTW9uZGF5XCJdID0gMV0gPSBcIk1vbmRheVwiO1xyXG4gICAgRGF5T2ZXZWVrW0RheU9mV2Vla1tcIlR1ZXNkYXlcIl0gPSAyXSA9IFwiVHVlc2RheVwiO1xyXG4gICAgRGF5T2ZXZWVrW0RheU9mV2Vla1tcIldlZG5lc2RheVwiXSA9IDNdID0gXCJXZWRuZXNkYXlcIjtcclxuICAgIERheU9mV2Vla1tEYXlPZldlZWtbXCJUaHVyc2RheVwiXSA9IDRdID0gXCJUaHVyc2RheVwiO1xyXG4gICAgRGF5T2ZXZWVrW0RheU9mV2Vla1tcIkZyaWRheVwiXSA9IDVdID0gXCJGcmlkYXlcIjtcclxuICAgIERheU9mV2Vla1tEYXlPZldlZWtbXCJTYXR1cmRheVwiXSA9IDZdID0gXCJTYXR1cmRheVwiO1xyXG59KShEYXlPZldlZWsgfHwgKERheU9mV2VlayA9IHt9KSk7XHJcbi8vIyBzb3VyY2VNYXBwaW5nVVJMPWVudW1zLmpzLm1hcCIsImV4cG9ydCAqIGZyb20gXCIuL2NvbnN0YW50c1wiO1xyXG5leHBvcnQgKiBmcm9tIFwiLi9lbnVtc1wiO1xyXG5leHBvcnQgKiBmcm9tIFwiLi91dGlsc1wiO1xyXG5leHBvcnQgKiBmcm9tIFwiLi9jb2xsZWN0aW9uXCI7XHJcbmV4cG9ydCAqIGZyb20gXCIuL2lucHV0Y29udHJvbFwiO1xyXG5leHBvcnQgKiBmcm9tIFwiLi9pbnB1dHdpdGhwb3B1cFwiO1xyXG5leHBvcnQgKiBmcm9tIFwiLi9jYWxlbmRhclwiO1xyXG5leHBvcnQgKiBmcm9tIFwiLi9kcm9wZG93blwiO1xyXG5leHBvcnQgKiBmcm9tIFwiLi9kYXRlcGlja2VyXCI7XHJcbmV4cG9ydCAqIGZyb20gXCIuL2NoZWNrYm94XCI7XHJcbmV4cG9ydCAqIGZyb20gXCIuL3JhZGlvYnV0dG9uXCI7XHJcbmV4cG9ydCAqIGZyb20gXCIuL3RleHRib3hcIjtcclxuZXhwb3J0ICogZnJvbSBcIi4vcG9wdXBtZW51XCI7XHJcbmltcG9ydCBcIi4vYWRhcHRpdmVjYXJkcy1jb250cm9scy5jc3NcIjtcclxuLy8jIHNvdXJjZU1hcHBpbmdVUkw9aW5kZXguanMubWFwIiwiZXhwb3J0IGNsYXNzIElucHV0Q29udHJvbCB7XHJcbiAgICB2YWxpZGF0ZVJvb3RFbGVtZW50KHJvb3RFbGVtZW50KSB7XHJcbiAgICAgICAgLy8gRG8gbm90aGluZyAtIGFsbCByb290IGVsZW1lbnQgdHlwZXMgYXJlIHZhbGlkLlxyXG4gICAgfVxyXG4gICAga2V5RG93bihlKSB7XHJcbiAgICAgICAgLy8gRG8gbm90aGluZyBpbiBiYXNlIGltcGxlbWVudGF0aW9uXHJcbiAgICB9XHJcbiAgICBnZXQgcm9vdEVsZW1lbnQoKSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX3Jvb3RFbGVtZW50O1xyXG4gICAgfVxyXG4gICAgYXR0YWNoKHJvb3RFbGVtZW50KSB7XHJcbiAgICAgICAgdGhpcy52YWxpZGF0ZVJvb3RFbGVtZW50KHJvb3RFbGVtZW50KTtcclxuICAgICAgICB0aGlzLl9yb290RWxlbWVudCA9IHJvb3RFbGVtZW50O1xyXG4gICAgICAgIHRoaXMuX3Jvb3RFbGVtZW50Lm9ua2V5ZG93biA9IChlKSA9PiB7IHRoaXMua2V5RG93bihlKTsgfTtcclxuICAgIH1cclxufVxyXG4vLyMgc291cmNlTWFwcGluZ1VSTD1pbnB1dGNvbnRyb2wuanMubWFwIiwiaW1wb3J0ICogYXMgQ29uc3RhbnRzIGZyb20gXCIuL2NvbnN0YW50c1wiO1xyXG5pbXBvcnQgKiBhcyBVdGlscyBmcm9tIFwiLi91dGlsc1wiO1xyXG5pbXBvcnQgeyBJbnB1dENvbnRyb2wgfSBmcm9tIFwiLi9pbnB1dGNvbnRyb2xcIjtcclxuZXhwb3J0IGNsYXNzIFBvcHVwQ29udHJvbCB7XHJcbiAgICBjbG9zZSgpIHtcclxuICAgICAgICBpZiAodGhpcy5vbkNsb3NlKSB7XHJcbiAgICAgICAgICAgIHRoaXMub25DbG9zZSh0aGlzKTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBrZXlEb3duKGUpIHtcclxuICAgICAgICBzd2l0Y2ggKGUua2V5Q29kZSkge1xyXG4gICAgICAgICAgICBjYXNlIENvbnN0YW50cy5LRVlfRVNDQVBFOlxyXG4gICAgICAgICAgICAgICAgdGhpcy5jbG9zZSgpO1xyXG4gICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG4gICAgcmVuZGVyKHJvb3RFbGVtZW50Qm91bmRzKSB7XHJcbiAgICAgICAgdGhpcy5fcG9wdXBFbGVtZW50ID0gZG9jdW1lbnQuY3JlYXRlRWxlbWVudChcImRpdlwiKTtcclxuICAgICAgICB0aGlzLl9wb3B1cEVsZW1lbnQudGFiSW5kZXggPSAwO1xyXG4gICAgICAgIHRoaXMuX3BvcHVwRWxlbWVudC5jbGFzc05hbWUgPSBcIm1zLWN0cmwgbXMtY3RybC1wb3B1cC1jb250YWluZXJcIjtcclxuICAgICAgICB0aGlzLl9wb3B1cEVsZW1lbnQub25rZXlkb3duID0gKGUpID0+IHtcclxuICAgICAgICAgICAgdGhpcy5rZXlEb3duKGUpO1xyXG4gICAgICAgICAgICByZXR1cm4gIWUuY2FuY2VsQnViYmxlO1xyXG4gICAgICAgIH07XHJcbiAgICAgICAgdGhpcy5fcG9wdXBFbGVtZW50LmFwcGVuZENoaWxkKHRoaXMucmVuZGVyQ29udGVudCgpKTtcclxuICAgICAgICByZXR1cm4gdGhpcy5fcG9wdXBFbGVtZW50O1xyXG4gICAgfVxyXG4gICAgZm9jdXMoKSB7XHJcbiAgICAgICAgaWYgKHRoaXMuX3BvcHVwRWxlbWVudCkge1xyXG4gICAgICAgICAgICB0aGlzLl9wb3B1cEVsZW1lbnQuZmlyc3RFbGVtZW50Q2hpbGQuZm9jdXMoKTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbn1cclxuZXhwb3J0IGNsYXNzIElucHV0V2l0aFBvcHVwIGV4dGVuZHMgSW5wdXRDb250cm9sIHtcclxuICAgIGtleURvd24oZSkge1xyXG4gICAgICAgIHN3aXRjaCAoZS5rZXlDb2RlKSB7XHJcbiAgICAgICAgICAgIGNhc2UgQ29uc3RhbnRzLktFWV9FTlRFUjpcclxuICAgICAgICAgICAgICAgIHRoaXMucG9wdXAoKTtcclxuICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgIH1cclxuICAgIH1cclxuICAgIHVwZGF0ZUxhYmVsKCkge1xyXG4gICAgICAgIGlmICh0aGlzLl9sYWJlbEVsZW1lbnQpIHtcclxuICAgICAgICAgICAgaWYgKHRoaXMuX3ZhbHVlKSB7XHJcbiAgICAgICAgICAgICAgICB0aGlzLl9sYWJlbEVsZW1lbnQuaW5uZXJIVE1MID0gdGhpcy5nZXRWYWx1ZUFzU3RyaW5nKCk7XHJcbiAgICAgICAgICAgICAgICB0aGlzLl9sYWJlbEVsZW1lbnQuY2xhc3NMaXN0LnJlbW92ZShcInBsYWNlaG9sZGVyXCIpO1xyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgdGhpcy5fbGFiZWxFbGVtZW50LmlubmVyVGV4dCA9IHRoaXMuX3BsYWNlaG9sZGVyVGV4dCA/IHRoaXMuX3BsYWNlaG9sZGVyVGV4dCA6IFwiXCI7XHJcbiAgICAgICAgICAgICAgICB0aGlzLl9sYWJlbEVsZW1lbnQuY2xhc3NMaXN0LmFkZChcInBsYWNlaG9sZGVyXCIpO1xyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG4gICAgZ2V0IHBvcHVwQ29udHJvbCgpIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5fcG9wdXBDb250cm9sO1xyXG4gICAgfVxyXG4gICAgZ2V0QnV0dG9uSWNvbkNzc0NsYXNzTmFtZSgpIHtcclxuICAgICAgICByZXR1cm4gXCJtcy1pY29uLWNoZXZyb25Eb3duXCI7XHJcbiAgICB9XHJcbiAgICBnZXRWYWx1ZUFzU3RyaW5nKCkge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl92YWx1ZS50b1N0cmluZygpO1xyXG4gICAgfVxyXG4gICAgdmFsdWVDaGFuZ2VkKCkge1xyXG4gICAgICAgIGlmICh0aGlzLm9uVmFsdWVDaGFuZ2VkKSB7XHJcbiAgICAgICAgICAgIHRoaXMub25WYWx1ZUNoYW5nZWQodGhpcyk7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG4gICAgYXR0YWNoKHJvb3RFbGVtZW50KSB7XHJcbiAgICAgICAgc3VwZXIuYXR0YWNoKHJvb3RFbGVtZW50KTtcclxuICAgICAgICByb290RWxlbWVudC50YWJJbmRleCA9IDA7XHJcbiAgICAgICAgcm9vdEVsZW1lbnQuY2xhc3NOYW1lID0gdGhpcy5nZXRDc3NDbGFzc05hbWUoKTtcclxuICAgICAgICB3aW5kb3cuYWRkRXZlbnRMaXN0ZW5lcihcInJlc2l6ZVwiLCAoZSkgPT4geyB0aGlzLmNsb3NlUG9wdXAoKTsgfSk7XHJcbiAgICAgICAgdGhpcy5yb290RWxlbWVudC5vbmNsaWNrID0gKGUpID0+IHtcclxuICAgICAgICAgICAgaWYgKHRoaXMuX2lzT3Blbikge1xyXG4gICAgICAgICAgICAgICAgdGhpcy5jbG9zZVBvcHVwKCk7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgICAgICB0aGlzLnBvcHVwKCk7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICB9O1xyXG4gICAgICAgIGxldCBwbGFjZUhvbGRlckRvbUl0ZW0gPSB0aGlzLnJvb3RFbGVtZW50LmF0dHJpYnV0ZXMuZ2V0TmFtZWRJdGVtKFwicGxhY2Vob2xkZXJcIik7XHJcbiAgICAgICAgaWYgKHBsYWNlSG9sZGVyRG9tSXRlbSkge1xyXG4gICAgICAgICAgICB0aGlzLl9wbGFjZWhvbGRlclRleHQgPSBwbGFjZUhvbGRlckRvbUl0ZW0udmFsdWU7XHJcbiAgICAgICAgfVxyXG4gICAgICAgIHRoaXMuX2xhYmVsRWxlbWVudCA9IGRvY3VtZW50LmNyZWF0ZUVsZW1lbnQoXCJzcGFuXCIpO1xyXG4gICAgICAgIHRoaXMuX2xhYmVsRWxlbWVudC5jbGFzc05hbWUgPSBcIm1zLWN0cmwgbXMtZHJvcGRvd24tbGFiZWxcIjtcclxuICAgICAgICB0aGlzLl9kcm9wRG93bkJ1dHRvbkVsZW1lbnQgPSBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwiaVwiKTtcclxuICAgICAgICB0aGlzLl9kcm9wRG93bkJ1dHRvbkVsZW1lbnQuY2xhc3NOYW1lID0gXCJtcy1pY29uIG1zLWN0cmwtZHJvcGRvd24tYnV0dG9uIFwiICsgdGhpcy5nZXRCdXR0b25JY29uQ3NzQ2xhc3NOYW1lKCk7XHJcbiAgICAgICAgO1xyXG4gICAgICAgIHRoaXMucm9vdEVsZW1lbnQuYXBwZW5kQ2hpbGQodGhpcy5fbGFiZWxFbGVtZW50KTtcclxuICAgICAgICB0aGlzLnJvb3RFbGVtZW50LmFwcGVuZENoaWxkKHRoaXMuX2Ryb3BEb3duQnV0dG9uRWxlbWVudCk7XHJcbiAgICAgICAgdGhpcy51cGRhdGVMYWJlbCgpO1xyXG4gICAgfVxyXG4gICAgcG9wdXAoKSB7XHJcbiAgICAgICAgaWYgKCF0aGlzLl9pc09wZW4pIHtcclxuICAgICAgICAgICAgdGhpcy5fb3ZlcmxheUVsZW1lbnQgPSBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwiZGl2XCIpO1xyXG4gICAgICAgICAgICB0aGlzLl9vdmVybGF5RWxlbWVudC5jbGFzc05hbWUgPSBcIm1zLWN0cmwtb3ZlcmxheVwiO1xyXG4gICAgICAgICAgICB0aGlzLl9vdmVybGF5RWxlbWVudC50YWJJbmRleCA9IDA7XHJcbiAgICAgICAgICAgIHRoaXMuX292ZXJsYXlFbGVtZW50LnN0eWxlLndpZHRoID0gZG9jdW1lbnQuZG9jdW1lbnRFbGVtZW50LnNjcm9sbFdpZHRoICsgXCJweFwiO1xyXG4gICAgICAgICAgICB0aGlzLl9vdmVybGF5RWxlbWVudC5zdHlsZS5oZWlnaHQgPSBkb2N1bWVudC5kb2N1bWVudEVsZW1lbnQuc2Nyb2xsSGVpZ2h0ICsgXCJweFwiO1xyXG4gICAgICAgICAgICB0aGlzLl9vdmVybGF5RWxlbWVudC5vbmZvY3VzID0gKGUpID0+IHsgdGhpcy5jbG9zZVBvcHVwKCk7IH07XHJcbiAgICAgICAgICAgIGRvY3VtZW50LmJvZHkuYXBwZW5kQ2hpbGQodGhpcy5fb3ZlcmxheUVsZW1lbnQpO1xyXG4gICAgICAgICAgICB0aGlzLl9wb3B1cENvbnRyb2wgPSB0aGlzLmNyZWF0ZVBvcHVwQ29udHJvbCgpO1xyXG4gICAgICAgICAgICB0aGlzLl9wb3B1cENvbnRyb2wub25DbG9zZSA9IChzZW5kZXIpID0+IHtcclxuICAgICAgICAgICAgICAgIHRoaXMuY2xvc2VQb3B1cCgpO1xyXG4gICAgICAgICAgICAgICAgdGhpcy5yb290RWxlbWVudC5mb2N1cygpO1xyXG4gICAgICAgICAgICB9O1xyXG4gICAgICAgICAgICB2YXIgcm9vdEVsZW1lbnRCb3VuZHMgPSB0aGlzLnJvb3RFbGVtZW50LmdldEJvdW5kaW5nQ2xpZW50UmVjdCgpO1xyXG4gICAgICAgICAgICB0aGlzLl9wb3B1cENvbnRyb2xFbGVtZW50ID0gdGhpcy5fcG9wdXBDb250cm9sLnJlbmRlcihyb290RWxlbWVudEJvdW5kcyk7XHJcbiAgICAgICAgICAgIHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQuY2xhc3NMaXN0LnJlbW92ZShcIm1zLWN0cmwtc2xpZGVcIiwgXCJtcy1jdHJsLXNsaWRlTGVmdFRvUmlnaHRcIiwgXCJtcy1jdHJsLXNsaWRlUmlnaHRUb0xlZnRcIiwgXCJtcy1jdHJsLXNsaWRlVG9wVG9Cb3R0b21cIiwgXCJtcy1jdHJsLXNsaWRlUmlnaHRUb0xlZnRcIik7XHJcbiAgICAgICAgICAgIHRoaXMuX292ZXJsYXlFbGVtZW50LmFwcGVuZENoaWxkKHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQpO1xyXG4gICAgICAgICAgICB2YXIgcG9wdXBFbGVtZW50Qm91bmRzID0gdGhpcy5fcG9wdXBDb250cm9sRWxlbWVudC5nZXRCb3VuZGluZ0NsaWVudFJlY3QoKTtcclxuICAgICAgICAgICAgdmFyIGF2YWlsYWJsZVNwYWNlQmVsb3cgPSB3aW5kb3cuaW5uZXJIZWlnaHQgLSByb290RWxlbWVudEJvdW5kcy5ib3R0b207XHJcbiAgICAgICAgICAgIHZhciBhdmFpbGFibGVTcGFjZUFib3ZlID0gcm9vdEVsZW1lbnRCb3VuZHMudG9wO1xyXG4gICAgICAgICAgICB2YXIgbGVmdCA9IHJvb3RFbGVtZW50Qm91bmRzLmxlZnQgKyBVdGlscy5nZXRTY3JvbGxYKCk7XHJcbiAgICAgICAgICAgIHZhciB0b3A7XHJcbiAgICAgICAgICAgIGlmIChhdmFpbGFibGVTcGFjZUFib3ZlIDwgcG9wdXBFbGVtZW50Qm91bmRzLmhlaWdodCAmJiBhdmFpbGFibGVTcGFjZUJlbG93IDwgcG9wdXBFbGVtZW50Qm91bmRzLmhlaWdodCkge1xyXG4gICAgICAgICAgICAgICAgLy8gTm90IGVub3VnaCBzcGFjZSBhYm92ZSBvciBiZWxvdyByb290IGVsZW1lbnRcclxuICAgICAgICAgICAgICAgIHZhciBhY3R1YWxQb3B1cEhlaWdodCA9IE1hdGgubWluKHBvcHVwRWxlbWVudEJvdW5kcy5oZWlnaHQsIHdpbmRvdy5pbm5lckhlaWdodCk7XHJcbiAgICAgICAgICAgICAgICB0aGlzLl9wb3B1cENvbnRyb2xFbGVtZW50LnN0eWxlLm1heEhlaWdodCA9IGFjdHVhbFBvcHVwSGVpZ2h0ICsgXCJweFwiO1xyXG4gICAgICAgICAgICAgICAgaWYgKGFjdHVhbFBvcHVwSGVpZ2h0IDwgcG9wdXBFbGVtZW50Qm91bmRzLmhlaWdodCkge1xyXG4gICAgICAgICAgICAgICAgICAgIHRvcCA9IFV0aWxzLmdldFNjcm9sbFkoKTtcclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgIHRvcCA9IFV0aWxzLmdldFNjcm9sbFkoKSArIHJvb3RFbGVtZW50Qm91bmRzLnRvcCArIChyb290RWxlbWVudEJvdW5kcy5oZWlnaHQgLSBhY3R1YWxQb3B1cEhlaWdodCkgLyAyO1xyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgdmFyIGF2YWlsYWJsZVNwYWNlUmlnaHQgPSB3aW5kb3cuaW5uZXJXaWR0aCAtIHJvb3RFbGVtZW50Qm91bmRzLnJpZ2h0O1xyXG4gICAgICAgICAgICAgICAgdmFyIGF2YWlsYWJsZVNwYWNlTGVmdCA9IHJvb3RFbGVtZW50Qm91bmRzLmxlZnQ7XHJcbiAgICAgICAgICAgICAgICBpZiAoYXZhaWxhYmxlU3BhY2VMZWZ0IDwgcG9wdXBFbGVtZW50Qm91bmRzLndpZHRoICYmIGF2YWlsYWJsZVNwYWNlUmlnaHQgPCBwb3B1cEVsZW1lbnRCb3VuZHMud2lkdGgpIHtcclxuICAgICAgICAgICAgICAgICAgICAvLyBOb3QgZW5vdWdoIHNwYWNlIGxlZnQgb3IgcmlnaHQgb2Ygcm9vdCBlbGVtZW50XHJcbiAgICAgICAgICAgICAgICAgICAgdmFyIGFjdHVhbFBvcHVwV2lkdGggPSBNYXRoLm1pbihwb3B1cEVsZW1lbnRCb3VuZHMud2lkdGgsIHdpbmRvdy5pbm5lcldpZHRoKTtcclxuICAgICAgICAgICAgICAgICAgICB0aGlzLl9wb3B1cENvbnRyb2xFbGVtZW50LnN0eWxlLm1heFdpZHRoID0gYWN0dWFsUG9wdXBXaWR0aCArIFwicHhcIjtcclxuICAgICAgICAgICAgICAgICAgICBpZiAoYWN0dWFsUG9wdXBXaWR0aCA8IHBvcHVwRWxlbWVudEJvdW5kcy53aWR0aCkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBsZWZ0ID0gVXRpbHMuZ2V0U2Nyb2xsWCgpO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgbGVmdCA9IFV0aWxzLmdldFNjcm9sbFgoKSArIHJvb3RFbGVtZW50Qm91bmRzLmxlZnQgKyAocm9vdEVsZW1lbnRCb3VuZHMud2lkdGggLSBhY3R1YWxQb3B1cFdpZHRoKSAvIDI7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgICAgICAgICAgLy8gRW5vdWdoIHNwYWNlIG9uIHRoZSBsZWZ0IG9yIHJpZ2h0IG9mIHRoZSByb290IGVsZW1lbnRcclxuICAgICAgICAgICAgICAgICAgICBpZiAoYXZhaWxhYmxlU3BhY2VSaWdodCA+PSBwb3B1cEVsZW1lbnRCb3VuZHMud2lkdGgpIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgbGVmdCA9IFV0aWxzLmdldFNjcm9sbFgoKSArIHJvb3RFbGVtZW50Qm91bmRzLnJpZ2h0O1xyXG4gICAgICAgICAgICAgICAgICAgICAgICB0aGlzLl9wb3B1cENvbnRyb2xFbGVtZW50LmNsYXNzTGlzdC5hZGQoXCJtcy1jdHJsLXNsaWRlXCIsIFwibXMtY3RybC1zbGlkZUxlZnRUb1JpZ2h0XCIpO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICAgICAgbGVmdCA9IFV0aWxzLmdldFNjcm9sbFgoKSArIHJvb3RFbGVtZW50Qm91bmRzLmxlZnQgLSBwb3B1cEVsZW1lbnRCb3VuZHMud2lkdGg7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQuY2xhc3NMaXN0LmFkZChcIm1zLWN0cmwtc2xpZGVcIiwgXCJtcy1jdHJsLXNsaWRlUmlnaHRUb0xlZnRcIik7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgLy8gRW5vdWdoIHNwYWNlIGFib3ZlIG9yIGJlbG93IHJvb3QgZWxlbWVudFxyXG4gICAgICAgICAgICAgICAgaWYgKGF2YWlsYWJsZVNwYWNlQmVsb3cgPj0gcG9wdXBFbGVtZW50Qm91bmRzLmhlaWdodCkge1xyXG4gICAgICAgICAgICAgICAgICAgIHRvcCA9IFV0aWxzLmdldFNjcm9sbFkoKSArIHJvb3RFbGVtZW50Qm91bmRzLmJvdHRvbTtcclxuICAgICAgICAgICAgICAgICAgICB0aGlzLl9wb3B1cENvbnRyb2xFbGVtZW50LmNsYXNzTGlzdC5hZGQoXCJtcy1jdHJsLXNsaWRlXCIsIFwibXMtY3RybC1zbGlkZVRvcFRvQm90dG9tXCIpO1xyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgICAgICAgICAgdG9wID0gVXRpbHMuZ2V0U2Nyb2xsWSgpICsgcm9vdEVsZW1lbnRCb3VuZHMudG9wIC0gcG9wdXBFbGVtZW50Qm91bmRzLmhlaWdodDtcclxuICAgICAgICAgICAgICAgICAgICB0aGlzLl9wb3B1cENvbnRyb2xFbGVtZW50LmNsYXNzTGlzdC5hZGQoXCJtcy1jdHJsLXNsaWRlXCIsIFwibXMtY3RybC1zbGlkZUJvdHRvbVRvVG9wXCIpO1xyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQuc3R5bGUubGVmdCA9IGxlZnQgKyBcInB4XCI7XHJcbiAgICAgICAgICAgIHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQuc3R5bGUudG9wID0gdG9wICsgXCJweFwiO1xyXG4gICAgICAgICAgICB0aGlzLl9wb3B1cENvbnRyb2xFbGVtZW50LmZvY3VzKCk7XHJcbiAgICAgICAgICAgIHRoaXMuX2lzT3BlbiA9IHRydWU7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG4gICAgY2xvc2VQb3B1cCgpIHtcclxuICAgICAgICBpZiAodGhpcy5faXNPcGVuKSB7XHJcbiAgICAgICAgICAgIGRvY3VtZW50LmJvZHkucmVtb3ZlQ2hpbGQodGhpcy5fb3ZlcmxheUVsZW1lbnQpO1xyXG4gICAgICAgICAgICB0aGlzLl9pc09wZW4gPSBmYWxzZTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBnZXQgaXNPcGVuKCkge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl9pc09wZW47XHJcbiAgICB9XHJcbiAgICBnZXQgcGxhY2Vob2xkZXJUZXh0KCkge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl9wbGFjZWhvbGRlclRleHQ7XHJcbiAgICB9XHJcbiAgICBzZXQgcGxhY2Vob2xkZXJUZXh0KHZhbHVlKSB7XHJcbiAgICAgICAgdGhpcy5fcGxhY2Vob2xkZXJUZXh0ID0gdmFsdWU7XHJcbiAgICB9XHJcbiAgICBnZXQgdmFsdWUoKSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX3ZhbHVlO1xyXG4gICAgfVxyXG4gICAgc2V0IHZhbHVlKG5ld1ZhbHVlKSB7XHJcbiAgICAgICAgaWYgKHRoaXMuX3ZhbHVlICE9IG5ld1ZhbHVlKSB7XHJcbiAgICAgICAgICAgIHRoaXMuX3ZhbHVlID0gbmV3VmFsdWU7XHJcbiAgICAgICAgICAgIHRoaXMudXBkYXRlTGFiZWwoKTtcclxuICAgICAgICAgICAgdGhpcy52YWx1ZUNoYW5nZWQoKTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbn1cclxuLy8jIHNvdXJjZU1hcHBpbmdVUkw9aW5wdXR3aXRocG9wdXAuanMubWFwIiwiaW1wb3J0ICogYXMgVXRpbHMgZnJvbSBcIi4vdXRpbHNcIjtcclxuaW1wb3J0ICogYXMgQ29uc3RhbnRzIGZyb20gXCIuL2NvbnN0YW50c1wiO1xyXG5pbXBvcnQgeyBDb2xsZWN0aW9uIH0gZnJvbSBcIi4vY29sbGVjdGlvblwiO1xyXG5pbXBvcnQgeyBQb3B1cENvbnRyb2wgfSBmcm9tIFwiLi9pbnB1dHdpdGhwb3B1cFwiO1xyXG5leHBvcnQgY2xhc3MgUG9wdXBNZW51IGV4dGVuZHMgUG9wdXBDb250cm9sIHtcclxuICAgIGNvbnN0cnVjdG9yKCkge1xyXG4gICAgICAgIHN1cGVyKCk7XHJcbiAgICAgICAgdGhpcy5faXRlbXMgPSBuZXcgQ29sbGVjdGlvbigpO1xyXG4gICAgICAgIHRoaXMuX3JlbmRlcmVkSXRlbXMgPSBbXTtcclxuICAgICAgICB0aGlzLl9zZWxlY3RlZEluZGV4ID0gLTE7XHJcbiAgICB9XHJcbiAgICByZW5kZXJDb250ZW50KCkge1xyXG4gICAgICAgIHZhciBlbGVtZW50ID0gZG9jdW1lbnQuY3JlYXRlRWxlbWVudChcImRpdlwiKTtcclxuICAgICAgICBlbGVtZW50LmNsYXNzTmFtZSA9IFwibXMtY3RybCBtcy1wb3B1cFwiO1xyXG4gICAgICAgIGZvciAodmFyIGkgPSAwOyBpIDwgdGhpcy5faXRlbXMubGVuZ3RoOyBpKyspIHtcclxuICAgICAgICAgICAgdmFyIHJlbmRlcmVkSXRlbSA9IHRoaXMuX2l0ZW1zLmdldChpKS5yZW5kZXIoKTtcclxuICAgICAgICAgICAgcmVuZGVyZWRJdGVtLnRhYkluZGV4ID0gMDtcclxuICAgICAgICAgICAgZWxlbWVudC5hcHBlbmRDaGlsZChyZW5kZXJlZEl0ZW0pO1xyXG4gICAgICAgICAgICBpZiAoaSA9PSB0aGlzLnNlbGVjdGVkSW5kZXgpIHtcclxuICAgICAgICAgICAgICAgIHJlbmRlcmVkSXRlbS5mb2N1cygpO1xyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIHRoaXMuX3JlbmRlcmVkSXRlbXMucHVzaChyZW5kZXJlZEl0ZW0pO1xyXG4gICAgICAgIH1cclxuICAgICAgICByZXR1cm4gZWxlbWVudDtcclxuICAgIH1cclxuICAgIGtleURvd24oZSkge1xyXG4gICAgICAgIHN1cGVyLmtleURvd24oZSk7XHJcbiAgICAgICAgdmFyIHNlbGVjdGVkSXRlbUluZGV4ID0gdGhpcy5fc2VsZWN0ZWRJbmRleDtcclxuICAgICAgICBzd2l0Y2ggKGUua2V5Q29kZSkge1xyXG4gICAgICAgICAgICBjYXNlIENvbnN0YW50cy5LRVlfVEFCOlxyXG4gICAgICAgICAgICAgICAgdGhpcy5jbG9zZSgpO1xyXG4gICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgIC8qXHJcbiAgICAgICAgICAgIGNhc2UgQ29uc3RhbnRzLktFWV9FTlRFUjpcclxuICAgICAgICAgICAgICAgIGlmICh0aGlzLnNlbGVjdGVkSW5kZXggPj0gMCkge1xyXG4gICAgICAgICAgICAgICAgICAgIHRoaXMuc2VsZWN0ZWRJbmRleCA9IHRoaXMuc2VsZWN0ZWRJbmRleDtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgdGhpcy5jbG9zZSgpO1xyXG4gICAgICAgICAgICAgICAgfVxyXG5cclxuICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgICAgICAqL1xyXG4gICAgICAgICAgICBjYXNlIENvbnN0YW50cy5LRVlfVVA6XHJcbiAgICAgICAgICAgICAgICBpZiAoc2VsZWN0ZWRJdGVtSW5kZXggPD0gMCkge1xyXG4gICAgICAgICAgICAgICAgICAgIHNlbGVjdGVkSXRlbUluZGV4ID0gdGhpcy5fcmVuZGVyZWRJdGVtcy5sZW5ndGggLSAxO1xyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgICAgICAgICAgc2VsZWN0ZWRJdGVtSW5kZXgtLTtcclxuICAgICAgICAgICAgICAgICAgICBpZiAoc2VsZWN0ZWRJdGVtSW5kZXggPCAwKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHNlbGVjdGVkSXRlbUluZGV4ID0gdGhpcy5fcmVuZGVyZWRJdGVtcy5sZW5ndGggLSAxO1xyXG4gICAgICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgIHRoaXMuc2VsZWN0ZWRJbmRleCA9IHNlbGVjdGVkSXRlbUluZGV4O1xyXG4gICAgICAgICAgICAgICAgZS5jYW5jZWxCdWJibGUgPSB0cnVlO1xyXG4gICAgICAgICAgICAgICAgYnJlYWs7XHJcbiAgICAgICAgICAgIGNhc2UgQ29uc3RhbnRzLktFWV9ET1dOOlxyXG4gICAgICAgICAgICAgICAgaWYgKHNlbGVjdGVkSXRlbUluZGV4IDwgMCkge1xyXG4gICAgICAgICAgICAgICAgICAgIHNlbGVjdGVkSXRlbUluZGV4ID0gMDtcclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgIHNlbGVjdGVkSXRlbUluZGV4Kys7XHJcbiAgICAgICAgICAgICAgICAgICAgaWYgKHNlbGVjdGVkSXRlbUluZGV4ID49IHRoaXMuX3JlbmRlcmVkSXRlbXMubGVuZ3RoKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHNlbGVjdGVkSXRlbUluZGV4ID0gMDtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICB0aGlzLnNlbGVjdGVkSW5kZXggPSBzZWxlY3RlZEl0ZW1JbmRleDtcclxuICAgICAgICAgICAgICAgIGUuY2FuY2VsQnViYmxlID0gdHJ1ZTtcclxuICAgICAgICAgICAgICAgIGJyZWFrO1xyXG4gICAgICAgIH1cclxuICAgIH1cclxuICAgIHBvcHVwKHJvb3RFbGVtZW50KSB7XHJcbiAgICAgICAgaWYgKCF0aGlzLl9pc09wZW4pIHtcclxuICAgICAgICAgICAgdGhpcy5fb3ZlcmxheUVsZW1lbnQgPSBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwiZGl2XCIpO1xyXG4gICAgICAgICAgICB0aGlzLl9vdmVybGF5RWxlbWVudC5jbGFzc05hbWUgPSBcIm1zLWN0cmwtb3ZlcmxheVwiO1xyXG4gICAgICAgICAgICB0aGlzLl9vdmVybGF5RWxlbWVudC50YWJJbmRleCA9IDA7XHJcbiAgICAgICAgICAgIHRoaXMuX292ZXJsYXlFbGVtZW50LnN0eWxlLnpJbmRleCA9IFwiMTAwMFwiO1xyXG4gICAgICAgICAgICB0aGlzLl9vdmVybGF5RWxlbWVudC5zdHlsZS53aWR0aCA9IGRvY3VtZW50LmRvY3VtZW50RWxlbWVudC5zY3JvbGxXaWR0aCArIFwicHhcIjtcclxuICAgICAgICAgICAgdGhpcy5fb3ZlcmxheUVsZW1lbnQuc3R5bGUuaGVpZ2h0ID0gZG9jdW1lbnQuZG9jdW1lbnRFbGVtZW50LnNjcm9sbEhlaWdodCArIFwicHhcIjtcclxuICAgICAgICAgICAgdGhpcy5fb3ZlcmxheUVsZW1lbnQub25mb2N1cyA9IChlKSA9PiB7IHRoaXMuY2xvc2VQb3B1cCgpOyB9O1xyXG4gICAgICAgICAgICBkb2N1bWVudC5ib2R5LmFwcGVuZENoaWxkKHRoaXMuX292ZXJsYXlFbGVtZW50KTtcclxuICAgICAgICAgICAgdmFyIHJvb3RFbGVtZW50Qm91bmRzID0gcm9vdEVsZW1lbnQuZ2V0Qm91bmRpbmdDbGllbnRSZWN0KCk7XHJcbiAgICAgICAgICAgIHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQgPSB0aGlzLnJlbmRlcihyb290RWxlbWVudEJvdW5kcyk7XHJcbiAgICAgICAgICAgIHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQuY2xhc3NMaXN0LnJlbW92ZShcIm1zLWN0cmwtc2xpZGVcIiwgXCJtcy1jdHJsLXNsaWRlTGVmdFRvUmlnaHRcIiwgXCJtcy1jdHJsLXNsaWRlUmlnaHRUb0xlZnRcIiwgXCJtcy1jdHJsLXNsaWRlVG9wVG9Cb3R0b21cIiwgXCJtcy1jdHJsLXNsaWRlUmlnaHRUb0xlZnRcIik7XHJcbiAgICAgICAgICAgIHRoaXMuX292ZXJsYXlFbGVtZW50LmFwcGVuZENoaWxkKHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQpO1xyXG4gICAgICAgICAgICB2YXIgcG9wdXBFbGVtZW50Qm91bmRzID0gdGhpcy5fcG9wdXBDb250cm9sRWxlbWVudC5nZXRCb3VuZGluZ0NsaWVudFJlY3QoKTtcclxuICAgICAgICAgICAgdmFyIGF2YWlsYWJsZVNwYWNlQmVsb3cgPSB3aW5kb3cuaW5uZXJIZWlnaHQgLSByb290RWxlbWVudEJvdW5kcy5ib3R0b207XHJcbiAgICAgICAgICAgIHZhciBhdmFpbGFibGVTcGFjZUFib3ZlID0gcm9vdEVsZW1lbnRCb3VuZHMudG9wO1xyXG4gICAgICAgICAgICB2YXIgbGVmdCA9IHJvb3RFbGVtZW50Qm91bmRzLmxlZnQgKyBVdGlscy5nZXRTY3JvbGxYKCk7XHJcbiAgICAgICAgICAgIHZhciB0b3A7XHJcbiAgICAgICAgICAgIGlmIChhdmFpbGFibGVTcGFjZUFib3ZlIDwgcG9wdXBFbGVtZW50Qm91bmRzLmhlaWdodCAmJiBhdmFpbGFibGVTcGFjZUJlbG93IDwgcG9wdXBFbGVtZW50Qm91bmRzLmhlaWdodCkge1xyXG4gICAgICAgICAgICAgICAgLy8gTm90IGVub3VnaCBzcGFjZSBhYm92ZSBvciBiZWxvdyByb290IGVsZW1lbnRcclxuICAgICAgICAgICAgICAgIHZhciBtYXhQb3B1cEhlaWdodCA9IHdpbmRvdy5pbm5lckhlaWdodDtcclxuICAgICAgICAgICAgICAgIHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQuc3R5bGUubWF4SGVpZ2h0ID0gbWF4UG9wdXBIZWlnaHQgKyBcInB4XCI7XHJcbiAgICAgICAgICAgICAgICBpZiAobWF4UG9wdXBIZWlnaHQgPCBwb3B1cEVsZW1lbnRCb3VuZHMuaGVpZ2h0KSB7XHJcbiAgICAgICAgICAgICAgICAgICAgdG9wID0gVXRpbHMuZ2V0U2Nyb2xsWSgpO1xyXG4gICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgICAgICAgICAgdG9wID0gVXRpbHMuZ2V0U2Nyb2xsWSgpICsgcm9vdEVsZW1lbnRCb3VuZHMudG9wICsgKHJvb3RFbGVtZW50Qm91bmRzLmhlaWdodCAtIG1heFBvcHVwSGVpZ2h0KSAvIDI7XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICB2YXIgYXZhaWxhYmxlU3BhY2VSaWdodCA9IHdpbmRvdy5pbm5lcldpZHRoIC0gcm9vdEVsZW1lbnRCb3VuZHMucmlnaHQ7XHJcbiAgICAgICAgICAgICAgICB2YXIgYXZhaWxhYmxlU3BhY2VMZWZ0ID0gcm9vdEVsZW1lbnRCb3VuZHMubGVmdDtcclxuICAgICAgICAgICAgICAgIGlmIChhdmFpbGFibGVTcGFjZUxlZnQgPCBwb3B1cEVsZW1lbnRCb3VuZHMud2lkdGggJiYgYXZhaWxhYmxlU3BhY2VSaWdodCA8IHBvcHVwRWxlbWVudEJvdW5kcy53aWR0aCkge1xyXG4gICAgICAgICAgICAgICAgICAgIC8vIE5vdCBlbm91Z2ggc3BhY2UgbGVmdCBvciByaWdodCBvZiByb290IGVsZW1lbnRcclxuICAgICAgICAgICAgICAgICAgICB2YXIgbWF4UG9wdXBXaWR0aCA9IHdpbmRvdy5pbm5lcldpZHRoO1xyXG4gICAgICAgICAgICAgICAgICAgIHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQuc3R5bGUubWF4V2lkdGggPSBtYXhQb3B1cFdpZHRoICsgXCJweFwiO1xyXG4gICAgICAgICAgICAgICAgICAgIGlmIChtYXhQb3B1cFdpZHRoIDwgcG9wdXBFbGVtZW50Qm91bmRzLndpZHRoKSB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGxlZnQgPSBVdGlscy5nZXRTY3JvbGxYKCk7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBsZWZ0ID0gVXRpbHMuZ2V0U2Nyb2xsWCgpICsgcm9vdEVsZW1lbnRCb3VuZHMubGVmdCArIChyb290RWxlbWVudEJvdW5kcy53aWR0aCAtIG1heFBvcHVwV2lkdGgpIC8gMjtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICAvLyBFbm91Z2ggc3BhY2Ugb24gdGhlIGxlZnQgb3IgcmlnaHQgb2YgdGhlIHJvb3QgZWxlbWVudFxyXG4gICAgICAgICAgICAgICAgICAgIGlmIChhdmFpbGFibGVTcGFjZVJpZ2h0ID49IHBvcHVwRWxlbWVudEJvdW5kcy53aWR0aCkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBsZWZ0ID0gVXRpbHMuZ2V0U2Nyb2xsWCgpICsgcm9vdEVsZW1lbnRCb3VuZHMucmlnaHQ7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQuY2xhc3NMaXN0LmFkZChcIm1zLWN0cmwtc2xpZGVcIiwgXCJtcy1jdHJsLXNsaWRlTGVmdFRvUmlnaHRcIik7XHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBsZWZ0ID0gVXRpbHMuZ2V0U2Nyb2xsWCgpICsgcm9vdEVsZW1lbnRCb3VuZHMubGVmdCAtIHBvcHVwRWxlbWVudEJvdW5kcy53aWR0aDtcclxuICAgICAgICAgICAgICAgICAgICAgICAgdGhpcy5fcG9wdXBDb250cm9sRWxlbWVudC5jbGFzc0xpc3QuYWRkKFwibXMtY3RybC1zbGlkZVwiLCBcIm1zLWN0cmwtc2xpZGVSaWdodFRvTGVmdFwiKTtcclxuICAgICAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgZWxzZSB7XHJcbiAgICAgICAgICAgICAgICAvLyBFbm91Z2ggc3BhY2UgYWJvdmUgb3IgYmVsb3cgcm9vdCBlbGVtZW50XHJcbiAgICAgICAgICAgICAgICBpZiAoYXZhaWxhYmxlU3BhY2VCZWxvdyA+PSBwb3B1cEVsZW1lbnRCb3VuZHMuaGVpZ2h0KSB7XHJcbiAgICAgICAgICAgICAgICAgICAgdG9wID0gVXRpbHMuZ2V0U2Nyb2xsWSgpICsgcm9vdEVsZW1lbnRCb3VuZHMuYm90dG9tO1xyXG4gICAgICAgICAgICAgICAgICAgIHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQuY2xhc3NMaXN0LmFkZChcIm1zLWN0cmwtc2xpZGVcIiwgXCJtcy1jdHJsLXNsaWRlVG9wVG9Cb3R0b21cIik7XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgICAgICAgICB0b3AgPSBVdGlscy5nZXRTY3JvbGxZKCkgKyByb290RWxlbWVudEJvdW5kcy50b3AgLSBwb3B1cEVsZW1lbnRCb3VuZHMuaGVpZ2h0O1xyXG4gICAgICAgICAgICAgICAgICAgIHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQuY2xhc3NMaXN0LmFkZChcIm1zLWN0cmwtc2xpZGVcIiwgXCJtcy1jdHJsLXNsaWRlQm90dG9tVG9Ub3BcIik7XHJcbiAgICAgICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgdGhpcy5fcG9wdXBDb250cm9sRWxlbWVudC5zdHlsZS5sZWZ0ID0gbGVmdCArIFwicHhcIjtcclxuICAgICAgICAgICAgdGhpcy5fcG9wdXBDb250cm9sRWxlbWVudC5zdHlsZS50b3AgPSB0b3AgKyBcInB4XCI7XHJcbiAgICAgICAgICAgIHRoaXMuX3BvcHVwQ29udHJvbEVsZW1lbnQuZm9jdXMoKTtcclxuICAgICAgICAgICAgdGhpcy5faXNPcGVuID0gdHJ1ZTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBjbG9zZVBvcHVwKCkge1xyXG4gICAgICAgIGlmICh0aGlzLl9pc09wZW4pIHtcclxuICAgICAgICAgICAgZG9jdW1lbnQuYm9keS5yZW1vdmVDaGlsZCh0aGlzLl9vdmVybGF5RWxlbWVudCk7XHJcbiAgICAgICAgICAgIHRoaXMuX2lzT3BlbiA9IGZhbHNlO1xyXG4gICAgICAgIH1cclxuICAgIH1cclxuICAgIGdldCBpc09wZW4oKSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX2lzT3BlbjtcclxuICAgIH1cclxuICAgIGdldCBpdGVtcygpIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5faXRlbXM7XHJcbiAgICB9XHJcbiAgICBnZXQgc2VsZWN0ZWRJbmRleCgpIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5fc2VsZWN0ZWRJbmRleDtcclxuICAgIH1cclxuICAgIHNldCBzZWxlY3RlZEluZGV4KGluZGV4KSB7XHJcbiAgICAgICAgaWYgKGluZGV4ID49IDAgJiYgaW5kZXggPCB0aGlzLl9yZW5kZXJlZEl0ZW1zLmxlbmd0aCkge1xyXG4gICAgICAgICAgICB0aGlzLl9yZW5kZXJlZEl0ZW1zW2luZGV4XS5mb2N1cygpO1xyXG4gICAgICAgICAgICB0aGlzLl9zZWxlY3RlZEluZGV4ID0gaW5kZXg7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG59XHJcbi8vIyBzb3VyY2VNYXBwaW5nVVJMPXBvcHVwbWVudS5qcy5tYXAiLCJpbXBvcnQgKiBhcyBDb25zdGFudHMgZnJvbSBcIi4vY29uc3RhbnRzXCI7XHJcbmltcG9ydCB7IElucHV0Q29udHJvbCB9IGZyb20gXCIuL2lucHV0Y29udHJvbFwiO1xyXG5leHBvcnQgY2xhc3MgUmFkaW9CdXR0b24gZXh0ZW5kcyBJbnB1dENvbnRyb2wge1xyXG4gICAgY29uc3RydWN0b3IoKSB7XHJcbiAgICAgICAgc3VwZXIoLi4uYXJndW1lbnRzKTtcclxuICAgICAgICB0aGlzLl9sYWJlbCA9IFwiXCI7XHJcbiAgICAgICAgdGhpcy5fY2hlY2tib3hFbGVtZW50ID0gbnVsbDtcclxuICAgICAgICB0aGlzLl9zcGFuRWxlbWVudCA9IG51bGw7XHJcbiAgICB9XHJcbiAgICBzdGF0aWMgY3JlYXRlSWQoKSB7XHJcbiAgICAgICAgdmFyIHJlc3VsdCA9IFJhZGlvQnV0dG9uLmNyZWF0aW9uSW5kZXg7XHJcbiAgICAgICAgUmFkaW9CdXR0b24uY3JlYXRpb25JbmRleCsrO1xyXG4gICAgICAgIHJldHVybiByZXN1bHQ7XHJcbiAgICB9XHJcbiAgICBjaGFuZ2VkKCkge1xyXG4gICAgICAgIGlmICh0aGlzLm9uQ2hhbmdlKSB7XHJcbiAgICAgICAgICAgIHRoaXMub25DaGFuZ2UodGhpcyk7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG4gICAga2V5RG93bihlKSB7XHJcbiAgICAgICAgc3dpdGNoIChlLmtleUNvZGUpIHtcclxuICAgICAgICAgICAgY2FzZSBDb25zdGFudHMuS0VZX0VOVEVSOlxyXG4gICAgICAgICAgICAgICAgdGhpcy5pc0NoZWNrZWQgPSAhdGhpcy5pc0NoZWNrZWQ7XHJcbiAgICAgICAgICAgICAgICBicmVhaztcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBhdHRhY2gocm9vdEVsZW1lbnQpIHtcclxuICAgICAgICBzdXBlci5hdHRhY2gocm9vdEVsZW1lbnQpO1xyXG4gICAgICAgIHJvb3RFbGVtZW50LmNsYXNzTmFtZSA9IFwibXMtY3RybCBtcy1jdHJsLXJhZGlvYnV0dG9uXCI7XHJcbiAgICAgICAgcm9vdEVsZW1lbnQudGFiSW5kZXggPSAwO1xyXG4gICAgICAgIHZhciBsYWJlbEF0dHJpYnV0ZSA9IHJvb3RFbGVtZW50LmF0dHJpYnV0ZXNbXCJsYWJlbFwiXTtcclxuICAgICAgICBpZiAobGFiZWxBdHRyaWJ1dGUpIHtcclxuICAgICAgICAgICAgdGhpcy5fbGFiZWwgPSBsYWJlbEF0dHJpYnV0ZS52YWx1ZTtcclxuICAgICAgICB9XHJcbiAgICAgICAgdmFyIGlzQ2hlY2tlZEF0dHJpYnV0ZSA9IHJvb3RFbGVtZW50LmF0dHJpYnV0ZXNbXCJpc2NoZWNrZWRcIl07XHJcbiAgICAgICAgaWYgKGlzQ2hlY2tlZEF0dHJpYnV0ZSkge1xyXG4gICAgICAgICAgICB0aGlzLl9pc0NoZWNrZWQgPSBpc0NoZWNrZWRBdHRyaWJ1dGUudmFsdWUgPT09IFwidHJ1ZVwiO1xyXG4gICAgICAgIH1cclxuICAgICAgICB0aGlzLl9jaGVja2JveEVsZW1lbnQgPSBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwiaW5wdXRcIik7XHJcbiAgICAgICAgdGhpcy5fY2hlY2tib3hFbGVtZW50LmlkID0gXCJtcy1jdHJsLXJhZGlvLVwiICsgUmFkaW9CdXR0b24uY3JlYXRlSWQoKTtcclxuICAgICAgICB0aGlzLl9jaGVja2JveEVsZW1lbnQudHlwZSA9IFwicmFkaW9cIjtcclxuICAgICAgICB0aGlzLl9jaGVja2JveEVsZW1lbnQuc3R5bGUucG9zaXRpb24gPSBcImFic29sdXRlXCI7XHJcbiAgICAgICAgdGhpcy5fY2hlY2tib3hFbGVtZW50LmNoZWNrZWQgPSB0aGlzLmlzQ2hlY2tlZDtcclxuICAgICAgICB0aGlzLl9jaGVja2JveEVsZW1lbnQub25jaGFuZ2UgPSAoZSkgPT4geyB0aGlzLmNoYW5nZWQoKTsgfTtcclxuICAgICAgICB2YXIgZ3JvdXBOYW1lQXR0cmlidXRlID0gcm9vdEVsZW1lbnQuYXR0cmlidXRlc1tcImdyb3VwbmFtZVwiXTtcclxuICAgICAgICBpZiAoZ3JvdXBOYW1lQXR0cmlidXRlKSB7XHJcbiAgICAgICAgICAgIHRoaXMuX2NoZWNrYm94RWxlbWVudC5uYW1lID0gZ3JvdXBOYW1lQXR0cmlidXRlLnZhbHVlO1xyXG4gICAgICAgIH1cclxuICAgICAgICB2YXIgbGFiZWxFbGVtZW50ID0gZG9jdW1lbnQuY3JlYXRlRWxlbWVudChcImxhYmVsXCIpO1xyXG4gICAgICAgIGxhYmVsRWxlbWVudC5odG1sRm9yID0gdGhpcy5fY2hlY2tib3hFbGVtZW50LmlkO1xyXG4gICAgICAgIHRoaXMuX3NwYW5FbGVtZW50ID0gZG9jdW1lbnQuY3JlYXRlRWxlbWVudChcInNwYW5cIik7XHJcbiAgICAgICAgdGhpcy5fc3BhbkVsZW1lbnQuaW5uZXJUZXh0ID0gdGhpcy5fbGFiZWw7XHJcbiAgICAgICAgbGFiZWxFbGVtZW50LmFwcGVuZENoaWxkKHRoaXMuX3NwYW5FbGVtZW50KTtcclxuICAgICAgICByb290RWxlbWVudC5pbm5lckhUTUwgPSBcIlwiO1xyXG4gICAgICAgIHJvb3RFbGVtZW50LmFwcGVuZENoaWxkKHRoaXMuX2NoZWNrYm94RWxlbWVudCk7XHJcbiAgICAgICAgcm9vdEVsZW1lbnQuYXBwZW5kQ2hpbGQobGFiZWxFbGVtZW50KTtcclxuICAgIH1cclxuICAgIGdldCBsYWJlbCgpIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5fbGFiZWw7XHJcbiAgICB9XHJcbiAgICBzZXQgbGFiZWwodmFsdWUpIHtcclxuICAgICAgICB0aGlzLl9sYWJlbCA9IHZhbHVlO1xyXG4gICAgICAgIGlmICh0aGlzLl9zcGFuRWxlbWVudCkge1xyXG4gICAgICAgICAgICB0aGlzLl9zcGFuRWxlbWVudC5pbm5lclRleHQgPSB0aGlzLl9sYWJlbDtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBnZXQgaXNDaGVja2VkKCkge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl9pc0NoZWNrZWQ7XHJcbiAgICB9XHJcbiAgICBzZXQgaXNDaGVja2VkKHZhbHVlKSB7XHJcbiAgICAgICAgaWYgKHRoaXMuX2lzQ2hlY2tlZCAhPSB2YWx1ZSkge1xyXG4gICAgICAgICAgICB0aGlzLl9pc0NoZWNrZWQgPSB2YWx1ZTtcclxuICAgICAgICAgICAgaWYgKHRoaXMuX2NoZWNrYm94RWxlbWVudCkge1xyXG4gICAgICAgICAgICAgICAgdGhpcy5fY2hlY2tib3hFbGVtZW50LmNoZWNrZWQgPSB0aGlzLl9pc0NoZWNrZWQ7XHJcbiAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgdGhpcy5jaGFuZ2VkKCk7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG59XHJcbi8vIFVzZWQgdG8gZ2VuZXJhdGUgdW5pcXVlIElkc1xyXG5SYWRpb0J1dHRvbi5jcmVhdGlvbkluZGV4ID0gMDtcclxuLy8jIHNvdXJjZU1hcHBpbmdVUkw9cmFkaW9idXR0b24uanMubWFwIiwiaW1wb3J0ICogYXMgVXRpbHMgZnJvbSBcIi4vdXRpbHNcIjtcclxuaW1wb3J0IHsgSW5wdXRDb250cm9sIH0gZnJvbSBcIi4vaW5wdXRjb250cm9sXCI7XHJcbmNsYXNzIEVkaXRCb3gge1xyXG4gICAgY2hhbmdlZCgpIHtcclxuICAgICAgICBpZiAodGhpcy5vbkNoYW5nZSkge1xyXG4gICAgICAgICAgICB0aGlzLm9uQ2hhbmdlKCk7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG59XHJcbmNsYXNzIFNpbmdsZUxpbmVFZGl0Qm94IGV4dGVuZHMgRWRpdEJveCB7XHJcbiAgICBjb25zdHJ1Y3RvcigpIHtcclxuICAgICAgICBzdXBlcigpO1xyXG4gICAgICAgIHRoaXMuX2lucHV0RWxlbWVudCA9IGRvY3VtZW50LmNyZWF0ZUVsZW1lbnQoXCJpbnB1dFwiKTtcclxuICAgICAgICB0aGlzLl9pbnB1dEVsZW1lbnQuY2xhc3NOYW1lID0gXCJtcy1jdHJsIG1zLWN0cmwtdGV4dGJveFwiO1xyXG4gICAgICAgIHRoaXMuX2lucHV0RWxlbWVudC50eXBlID0gXCJ0ZXh0XCI7XHJcbiAgICAgICAgdGhpcy5faW5wdXRFbGVtZW50Lm9uaW5wdXQgPSAoZSkgPT4ge1xyXG4gICAgICAgICAgICB0aGlzLmNoYW5nZWQoKTtcclxuICAgICAgICB9O1xyXG4gICAgfVxyXG4gICAgZ2V0IGVsZW1lbnQoKSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX2lucHV0RWxlbWVudDtcclxuICAgIH1cclxuICAgIHNldCBwbGFjZWhvbGRlcih2YWx1ZSkge1xyXG4gICAgICAgIHRoaXMuX2lucHV0RWxlbWVudC5wbGFjZWhvbGRlciA9IHZhbHVlO1xyXG4gICAgfVxyXG4gICAgc2V0IGxpbmVDb3VudCh2YWx1ZSkge1xyXG4gICAgICAgIC8vIGxpbmVDb3VudCBjYW4ndCBiZSBzZXQgb24gYSBTaW5nbGVMaW5lRWRpdEJveFxyXG4gICAgfVxyXG4gICAgc2V0IG1heExlbmd0aCh2YWx1ZSkge1xyXG4gICAgICAgIGlmICh0aGlzLl9pbnB1dEVsZW1lbnQubWF4TGVuZ3RoICE9IHZhbHVlKSB7XHJcbiAgICAgICAgICAgIHRoaXMuX2lucHV0RWxlbWVudC5tYXhMZW5ndGggPSB2YWx1ZTtcclxuICAgICAgICAgICAgdGhpcy52YWx1ZSA9IHRoaXMudmFsdWUuc3Vic3RyKDAsIHZhbHVlKTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBnZXQgdmFsdWUoKSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX2lucHV0RWxlbWVudC52YWx1ZTtcclxuICAgIH1cclxuICAgIHNldCB2YWx1ZShuZXdWYWx1ZSkge1xyXG4gICAgICAgIHRoaXMuX2lucHV0RWxlbWVudC52YWx1ZSA9IG5ld1ZhbHVlO1xyXG4gICAgfVxyXG59XHJcbmNsYXNzIE11bHRpbGluZUVkaXRCb3ggZXh0ZW5kcyBFZGl0Qm94IHtcclxuICAgIGNvbnN0cnVjdG9yKCkge1xyXG4gICAgICAgIHN1cGVyKCk7XHJcbiAgICAgICAgdGhpcy5fdGV4dGFyZWFFbGVtZW50ID0gZG9jdW1lbnQuY3JlYXRlRWxlbWVudChcInRleHRhcmVhXCIpO1xyXG4gICAgICAgIHRoaXMuX3RleHRhcmVhRWxlbWVudC5jbGFzc05hbWUgPSBcIm1zLWN0cmwgbXMtY3RybC10ZXh0Ym94IG1zLWN0cmwtdGV4dGJveC1tdWx0aWxpbmVcIjtcclxuICAgICAgICB0aGlzLl90ZXh0YXJlYUVsZW1lbnQub25pbnB1dCA9IChlKSA9PiB7XHJcbiAgICAgICAgICAgIHRoaXMuY2hhbmdlZCgpO1xyXG4gICAgICAgIH07XHJcbiAgICB9XHJcbiAgICBnZXQgZWxlbWVudCgpIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5fdGV4dGFyZWFFbGVtZW50O1xyXG4gICAgfVxyXG4gICAgc2V0IHBsYWNlaG9sZGVyKHZhbHVlKSB7XHJcbiAgICAgICAgdGhpcy5fdGV4dGFyZWFFbGVtZW50LnBsYWNlaG9sZGVyID0gdmFsdWU7XHJcbiAgICB9XHJcbiAgICBzZXQgbGluZUNvdW50KHZhbHVlKSB7XHJcbiAgICAgICAgdGhpcy5fdGV4dGFyZWFFbGVtZW50LnJvd3MgPSB2YWx1ZTtcclxuICAgIH1cclxuICAgIHNldCBtYXhMZW5ndGgodmFsdWUpIHtcclxuICAgICAgICBpZiAodGhpcy5fdGV4dGFyZWFFbGVtZW50Lm1heExlbmd0aCAhPSB2YWx1ZSkge1xyXG4gICAgICAgICAgICB0aGlzLl90ZXh0YXJlYUVsZW1lbnQubWF4TGVuZ3RoID0gdmFsdWU7XHJcbiAgICAgICAgICAgIHRoaXMudmFsdWUgPSB0aGlzLnZhbHVlLnN1YnN0cigwLCB2YWx1ZSk7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG4gICAgZ2V0IHZhbHVlKCkge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl90ZXh0YXJlYUVsZW1lbnQudmFsdWU7XHJcbiAgICB9XHJcbiAgICBzZXQgdmFsdWUobmV3VmFsdWUpIHtcclxuICAgICAgICB0aGlzLl90ZXh0YXJlYUVsZW1lbnQudmFsdWUgPSBuZXdWYWx1ZTtcclxuICAgIH1cclxufVxyXG5leHBvcnQgY2xhc3MgVGV4dEJveCBleHRlbmRzIElucHV0Q29udHJvbCB7XHJcbiAgICBjb25zdHJ1Y3RvcigpIHtcclxuICAgICAgICBzdXBlciguLi5hcmd1bWVudHMpO1xyXG4gICAgICAgIHRoaXMuX2lzTXVsdGlsaW5lID0gZmFsc2U7XHJcbiAgICAgICAgdGhpcy5fbGluZUNvdW50ID0gMztcclxuICAgIH1cclxuICAgIGVkaXRCb3hDaGFuZ2VkKCkge1xyXG4gICAgICAgIGlmICh0aGlzLm9uQ2hhbmdlKSB7XHJcbiAgICAgICAgICAgIHRoaXMub25DaGFuZ2UodGhpcyk7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG4gICAgcmVjcmVhdGVFZGl0Qm94KCkge1xyXG4gICAgICAgIHZhciBjdXJyZW50VmFsdWUgPSBudWxsO1xyXG4gICAgICAgIGlmICh0aGlzLl9lZGl0Qm94KSB7XHJcbiAgICAgICAgICAgIGN1cnJlbnRWYWx1ZSA9IHRoaXMuX2VkaXRCb3gudmFsdWU7XHJcbiAgICAgICAgfVxyXG4gICAgICAgIGVsc2Uge1xyXG4gICAgICAgICAgICBjdXJyZW50VmFsdWUgPSB0aGlzLnJvb3RFbGVtZW50LmlubmVyVGV4dDtcclxuICAgICAgICB9XHJcbiAgICAgICAgaWYgKHRoaXMuX2lzTXVsdGlsaW5lKSB7XHJcbiAgICAgICAgICAgIHRoaXMuX2VkaXRCb3ggPSBuZXcgTXVsdGlsaW5lRWRpdEJveCgpO1xyXG4gICAgICAgIH1cclxuICAgICAgICBlbHNlIHtcclxuICAgICAgICAgICAgdGhpcy5fZWRpdEJveCA9IG5ldyBTaW5nbGVMaW5lRWRpdEJveCgpO1xyXG4gICAgICAgIH1cclxuICAgICAgICBpZiAoY3VycmVudFZhbHVlKSB7XHJcbiAgICAgICAgICAgIHRoaXMuX2VkaXRCb3gudmFsdWUgPSBjdXJyZW50VmFsdWU7XHJcbiAgICAgICAgfVxyXG4gICAgICAgIHRoaXMuX2VkaXRCb3gubGluZUNvdW50ID0gdGhpcy5fbGluZUNvdW50O1xyXG4gICAgICAgIHRoaXMuX2VkaXRCb3gubWF4TGVuZ3RoID0gdGhpcy5fbWF4TGVuZ3RoO1xyXG4gICAgICAgIHRoaXMuX2VkaXRCb3gucGxhY2Vob2xkZXIgPSB0aGlzLl9wbGFjZWhvbGRlcjtcclxuICAgICAgICB0aGlzLl9lZGl0Qm94Lm9uQ2hhbmdlID0gKCkgPT4geyB0aGlzLmVkaXRCb3hDaGFuZ2VkKCk7IH07XHJcbiAgICAgICAgdGhpcy5yb290RWxlbWVudC5pbm5lckhUTUwgPSBcIlwiO1xyXG4gICAgICAgIHRoaXMucm9vdEVsZW1lbnQuYXBwZW5kQ2hpbGQodGhpcy5fZWRpdEJveC5lbGVtZW50KTtcclxuICAgIH1cclxuICAgIGdldCBlZGl0Qm94KCkge1xyXG4gICAgICAgIGlmICghdGhpcy5fZWRpdEJveCkge1xyXG4gICAgICAgICAgICB0aGlzLnJlY3JlYXRlRWRpdEJveCgpO1xyXG4gICAgICAgIH1cclxuICAgICAgICByZXR1cm4gdGhpcy5fZWRpdEJveDtcclxuICAgIH1cclxuICAgIGF0dGFjaChyb290RWxlbWVudCkge1xyXG4gICAgICAgIHN1cGVyLmF0dGFjaChyb290RWxlbWVudCk7XHJcbiAgICAgICAgdGhpcy5faXNNdWx0aWxpbmUgPSBVdGlscy5nZXRBdHRyaWJ1dGVWYWx1ZUFzQm9vbChyb290RWxlbWVudCwgXCJpc211bHRpbGluZVwiLCBmYWxzZSk7XHJcbiAgICAgICAgdGhpcy5fbGluZUNvdW50ID0gVXRpbHMuZ2V0QXR0cmlidXRlVmFsdWVBc0ludChyb290RWxlbWVudCwgXCJsaW5lc1wiLCAzKTtcclxuICAgICAgICB0aGlzLl9tYXhMZW5ndGggPSBVdGlscy5nZXRBdHRyaWJ1dGVWYWx1ZUFzSW50KHJvb3RFbGVtZW50LCBcIm1heGxlbmd0aFwiLCA1MDAwMCk7XHJcbiAgICAgICAgdGhpcy5fcGxhY2Vob2xkZXIgPSBVdGlscy5nZXRBdHRyaWJ1dGVWYWx1ZUFzU3RyaW5nKHJvb3RFbGVtZW50LCBcInBsYWNlaG9sZGVyXCIsIG51bGwpO1xyXG4gICAgICAgIHRoaXMucmVjcmVhdGVFZGl0Qm94KCk7XHJcbiAgICB9XHJcbiAgICBnZXQgdmFsdWUoKSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuZWRpdEJveC52YWx1ZTtcclxuICAgIH1cclxuICAgIHNldCB2YWx1ZShuZXdWYWx1ZSkge1xyXG4gICAgICAgIHRoaXMuZWRpdEJveC52YWx1ZSA9IG5ld1ZhbHVlO1xyXG4gICAgfVxyXG4gICAgZ2V0IHBsYWNlaG9sZGVyKCkge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl9wbGFjZWhvbGRlcjtcclxuICAgIH1cclxuICAgIHNldCBwbGFjZWhvbGRlcih2YWx1ZSkge1xyXG4gICAgICAgIHRoaXMuX3BsYWNlaG9sZGVyID0gdmFsdWU7XHJcbiAgICAgICAgdGhpcy5lZGl0Qm94LnBsYWNlaG9sZGVyID0gdmFsdWU7XHJcbiAgICB9XHJcbiAgICBnZXQgaXNNdWx0aWxpbmUoKSB7XHJcbiAgICAgICAgcmV0dXJuIHRoaXMuX2lzTXVsdGlsaW5lO1xyXG4gICAgfVxyXG4gICAgc2V0IGlzTXVsdGlsaW5lKHZhbHVlKSB7XHJcbiAgICAgICAgaWYgKHRoaXMuX2lzTXVsdGlsaW5lICE9IHZhbHVlKSB7XHJcbiAgICAgICAgICAgIHRoaXMuX2lzTXVsdGlsaW5lID0gdmFsdWU7XHJcbiAgICAgICAgICAgIHRoaXMucmVjcmVhdGVFZGl0Qm94KCk7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG4gICAgZ2V0IGxpbmVDb3VudCgpIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5fbGluZUNvdW50O1xyXG4gICAgfVxyXG4gICAgc2V0IGxpbmVDb3VudCh2YWx1ZSkge1xyXG4gICAgICAgIGlmICh2YWx1ZSA+IDApIHtcclxuICAgICAgICAgICAgdGhpcy5fbGluZUNvdW50ID0gdmFsdWU7XHJcbiAgICAgICAgICAgIHRoaXMuZWRpdEJveC5saW5lQ291bnQgPSB2YWx1ZTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcbiAgICBnZXQgbWF4TGVuZ3RoKCkge1xyXG4gICAgICAgIHJldHVybiB0aGlzLl9tYXhMZW5ndGg7XHJcbiAgICB9XHJcbiAgICBzZXQgbWF4TGVuZ3RoKHZhbHVlKSB7XHJcbiAgICAgICAgaWYgKHZhbHVlID4gMCkge1xyXG4gICAgICAgICAgICB0aGlzLl9tYXhMZW5ndGggPSB2YWx1ZTtcclxuICAgICAgICAgICAgdGhpcy5lZGl0Qm94Lm1heExlbmd0aCA9IHZhbHVlO1xyXG4gICAgICAgIH1cclxuICAgIH1cclxufVxyXG4vLyMgc291cmNlTWFwcGluZ1VSTD10ZXh0Ym94LmpzLm1hcCIsImltcG9ydCAqIGFzIEVudW1zIGZyb20gXCIuL2VudW1zXCI7XHJcbmV4cG9ydCBjbGFzcyBDYWxlbmRhclNldHRpbmdzIHtcclxuICAgIHN0YXRpYyBnZXRMb25nRGF5TmFtZShkYXlJbmRleCkge1xyXG4gICAgICAgIGlmIChkYXlJbmRleCA+PSAwICYmIGRheUluZGV4IDwgQ2FsZW5kYXJTZXR0aW5ncy5sb25nRGF5TmFtZXMubGVuZ3RoKSB7XHJcbiAgICAgICAgICAgIHJldHVybiBDYWxlbmRhclNldHRpbmdzLmxvbmdEYXlOYW1lc1tkYXlJbmRleF07XHJcbiAgICAgICAgfVxyXG4gICAgICAgIHRocm93IG5ldyBFcnJvcihcIkRheSBpbmRleCBvdXQgb2YgcmFuZ2U6IFwiICsgZGF5SW5kZXgpO1xyXG4gICAgfVxyXG4gICAgc3RhdGljIGdldFNob3J0RGF5TmFtZShkYXlJbmRleCkge1xyXG4gICAgICAgIGlmIChkYXlJbmRleCA+PSAwICYmIGRheUluZGV4IDwgQ2FsZW5kYXJTZXR0aW5ncy5zaG9ydERheU5hbWVzLmxlbmd0aCkge1xyXG4gICAgICAgICAgICByZXR1cm4gQ2FsZW5kYXJTZXR0aW5ncy5zaG9ydERheU5hbWVzW2RheUluZGV4XTtcclxuICAgICAgICB9XHJcbiAgICAgICAgdGhyb3cgbmV3IEVycm9yKFwiRGF5IGluZGV4IG91dCBvZiByYW5nZTogXCIgKyBkYXlJbmRleCk7XHJcbiAgICB9XHJcbiAgICBzdGF0aWMgZ2V0SW5pdGlhbERheU5hbWUoZGF5SW5kZXgpIHtcclxuICAgICAgICBpZiAoZGF5SW5kZXggPj0gMCAmJiBkYXlJbmRleCA8IENhbGVuZGFyU2V0dGluZ3MubWluaW1hbERheU5hbWVzLmxlbmd0aCkge1xyXG4gICAgICAgICAgICByZXR1cm4gQ2FsZW5kYXJTZXR0aW5ncy5taW5pbWFsRGF5TmFtZXNbZGF5SW5kZXhdO1xyXG4gICAgICAgIH1cclxuICAgICAgICB0aHJvdyBuZXcgRXJyb3IoXCJEYXkgaW5kZXggb3V0IG9mIHJhbmdlOiBcIiArIGRheUluZGV4KTtcclxuICAgIH1cclxuICAgIHN0YXRpYyBnZXRMb25nTW9udGhOYW1lKG1vbnRoSW5kZXgpIHtcclxuICAgICAgICBpZiAobW9udGhJbmRleCA+PSAwICYmIG1vbnRoSW5kZXggPCBDYWxlbmRhclNldHRpbmdzLmxvbmdNb250aE5hbWVzLmxlbmd0aCkge1xyXG4gICAgICAgICAgICByZXR1cm4gQ2FsZW5kYXJTZXR0aW5ncy5sb25nTW9udGhOYW1lc1ttb250aEluZGV4XTtcclxuICAgICAgICB9XHJcbiAgICAgICAgdGhyb3cgbmV3IEVycm9yKFwiTW9udGggaW5kZXggb3V0IG9mIHJhbmdlOiBcIiArIG1vbnRoSW5kZXgpO1xyXG4gICAgfVxyXG4gICAgc3RhdGljIGdldFNob3J0TW9udGhOYW1lKG1vbnRoSW5kZXgpIHtcclxuICAgICAgICBpZiAobW9udGhJbmRleCA+PSAwICYmIG1vbnRoSW5kZXggPCBDYWxlbmRhclNldHRpbmdzLnNob3J0TW9udGhOYW1lcy5sZW5ndGgpIHtcclxuICAgICAgICAgICAgcmV0dXJuIENhbGVuZGFyU2V0dGluZ3Muc2hvcnRNb250aE5hbWVzW21vbnRoSW5kZXhdO1xyXG4gICAgICAgIH1cclxuICAgICAgICB0aHJvdyBuZXcgRXJyb3IoXCJNb250aCBpbmRleCBvdXQgb2YgcmFuZ2U6IFwiICsgbW9udGhJbmRleCk7XHJcbiAgICB9XHJcbn1cclxuQ2FsZW5kYXJTZXR0aW5ncy5tb250aHNJblllYXIgPSAxMjtcclxuQ2FsZW5kYXJTZXR0aW5ncy5kYXlzSW5XZWVrID0gNztcclxuQ2FsZW5kYXJTZXR0aW5ncy5maXJzdERheU9mV2VlayA9IEVudW1zLkRheU9mV2Vlay5TdW5kYXk7XHJcbkNhbGVuZGFyU2V0dGluZ3MubG9uZ0RheU5hbWVzID0gW1wiU3VuZGF5XCIsIFwiTW9uZGF5XCIsIFwiVHVlc2RheVwiLCBcIldlZG5lc2RheVwiLCBcIlRodXJzZGF5XCIsIFwiRnJpZGF5XCIsIFwiU2F0dXJkYXlcIl07XHJcbkNhbGVuZGFyU2V0dGluZ3Muc2hvcnREYXlOYW1lcyA9IFtcIlN1blwiLCBcIk1vblwiLCBcIlR1ZVwiLCBcIldlZFwiLCBcIlRodVwiLCBcIkZyaVwiLCBcIlNhdFwiXTtcclxuQ2FsZW5kYXJTZXR0aW5ncy5taW5pbWFsRGF5TmFtZXMgPSBbXCJTdVwiLCBcIk1vXCIsIFwiVHVcIiwgXCJXZVwiLCBcIlRoXCIsIFwiRnJcIiwgXCJTYVwiXTtcclxuQ2FsZW5kYXJTZXR0aW5ncy5sb25nTW9udGhOYW1lcyA9IFtcIkphbnVhcnlcIiwgXCJGZWJydWFyeVwiLCBcIk1hcmNoXCIsIFwiQXByaWxcIiwgXCJNYXlcIiwgXCJKdW5lXCIsIFwiSnVseVwiLCBcIkF1Z3VzdFwiLCBcIlNlcHRlbWJlclwiLCBcIk9jdG9iZXJcIiwgXCJOb3ZlbWJlclwiLCBcIkRlY2VtYmVyXCJdO1xyXG5DYWxlbmRhclNldHRpbmdzLnNob3J0TW9udGhOYW1lcyA9IFtcIkphblwiLCBcIkZlYlwiLCBcIk1hclwiLCBcIkFwclwiLCBcIk1heVwiLCBcIkp1blwiLCBcIkp1bFwiLCBcIkF1Z1wiLCBcIlNlcFwiLCBcIk9jdFwiLCBcIk5vdlwiLCBcIkRlY1wiXTtcclxuZXhwb3J0IGZ1bmN0aW9uIGRheXNJbk1vbnRoKHllYXIsIG1vbnRoKSB7XHJcbiAgICBzd2l0Y2ggKG1vbnRoKSB7XHJcbiAgICAgICAgY2FzZSAxOlxyXG4gICAgICAgICAgICByZXR1cm4gKHllYXIgJSA0ID09IDAgJiYgeWVhciAlIDEwMCkgfHwgeWVhciAlIDQwMCA9PSAwID8gMjkgOiAyODtcclxuICAgICAgICBjYXNlIDM6XHJcbiAgICAgICAgY2FzZSA1OlxyXG4gICAgICAgIGNhc2UgODpcclxuICAgICAgICBjYXNlIDEwOlxyXG4gICAgICAgICAgICByZXR1cm4gMzA7XHJcbiAgICAgICAgZGVmYXVsdDpcclxuICAgICAgICAgICAgcmV0dXJuIDMxO1xyXG4gICAgfVxyXG59XHJcbmV4cG9ydCBmdW5jdGlvbiBhZGREYXlzKGRhdGUsIGRheXMpIHtcclxuICAgIHZhciByZXN1bHQgPSBuZXcgRGF0ZShkYXRlLmdldFRpbWUoKSk7XHJcbiAgICByZXN1bHQuc2V0RGF0ZShyZXN1bHQuZ2V0RGF0ZSgpICsgZGF5cyk7XHJcbiAgICByZXR1cm4gcmVzdWx0O1xyXG59XHJcbmV4cG9ydCBmdW5jdGlvbiBhZGRNb250aHMoZGF0ZSwgbW9udGhzKSB7XHJcbiAgICB2YXIgcmVzdWx0ID0gbmV3IERhdGUoZGF0ZS5nZXRUaW1lKCkpO1xyXG4gICAgdmFyIG5ld01vbnRoID0gcmVzdWx0LmdldE1vbnRoKCkgKyBtb250aHM7XHJcbiAgICByZXN1bHQuc2V0TW9udGgobmV3TW9udGgpO1xyXG4gICAgLy8gV2Ugd2FudCB0byBtYWludGFpbiB0aGUgc2FtZSBkYXktb2YtbW9udGgsIGJ1dCB0aGF0IG1heSBub3QgYmUgcG9zc2libGUgaWYgdGhlIG5ldyBtb250aCBkb2Vzbid0IGhhdmUgZW5vdWdoIGRheXMuXHJcbiAgICAvLyBMb29wIHVudGlsIHdlIGJhY2sgdXAgdG8gYSBkYXkgdGhlIG5ldyBtb250aCBoYXMuXHJcbiAgICAvLyAoV2VpcmQgbW9kdWxvIG1hdGggaXMgZHVlIHRvIEphdmFzY3JpcHQncyB0cmVhdG1lbnQgb2YgbmVnYXRpdmUgbnVtYmVycyBpbiBtb2R1bG8pXHJcbiAgICBpZiAocmVzdWx0LmdldE1vbnRoKCkgIT09ICgobmV3TW9udGggJSBDYWxlbmRhclNldHRpbmdzLm1vbnRoc0luWWVhcikgKyBDYWxlbmRhclNldHRpbmdzLm1vbnRoc0luWWVhcikgJSBDYWxlbmRhclNldHRpbmdzLm1vbnRoc0luWWVhcikge1xyXG4gICAgICAgIHJlc3VsdCA9IGFkZERheXMocmVzdWx0LCAtcmVzdWx0LmdldERhdGUoKSk7XHJcbiAgICB9XHJcbiAgICByZXR1cm4gcmVzdWx0O1xyXG59XHJcbmV4cG9ydCBmdW5jdGlvbiBhcmVEYXRlc0VxdWFsKGRhdGUxLCBkYXRlMikge1xyXG4gICAgcmV0dXJuIGRhdGUxLmdldEZ1bGxZZWFyKCkgPT0gZGF0ZTIuZ2V0RnVsbFllYXIoKSAmJlxyXG4gICAgICAgIGRhdGUxLmdldE1vbnRoKCkgPT0gZGF0ZTIuZ2V0TW9udGgoKSAmJlxyXG4gICAgICAgIGRhdGUxLmdldERhdGUoKSA9PSBkYXRlMi5nZXREYXRlKCk7XHJcbn1cclxuZXhwb3J0IGZ1bmN0aW9uIGdldFNjcm9sbFgoKSB7XHJcbiAgICByZXR1cm4gd2luZG93LnBhZ2VYT2Zmc2V0O1xyXG59XHJcbmV4cG9ydCBmdW5jdGlvbiBnZXRTY3JvbGxZKCkge1xyXG4gICAgcmV0dXJuIHdpbmRvdy5wYWdlWU9mZnNldDtcclxufVxyXG5leHBvcnQgZnVuY3Rpb24gZ2V0QXR0cmlidXRlVmFsdWVBc0Jvb2woZWxlbWVudCwgYXR0cmlidXRlTmFtZSwgZGVmYXVsdFZhbHVlKSB7XHJcbiAgICB2YXIgYXR0cmlidXRlID0gZWxlbWVudC5hdHRyaWJ1dGVzW2F0dHJpYnV0ZU5hbWVdO1xyXG4gICAgaWYgKGF0dHJpYnV0ZSkge1xyXG4gICAgICAgIHJldHVybiBhdHRyaWJ1dGUudmFsdWUgPT09IFwidHJ1ZVwiO1xyXG4gICAgfVxyXG4gICAgcmV0dXJuIGRlZmF1bHRWYWx1ZTtcclxufVxyXG5leHBvcnQgZnVuY3Rpb24gZ2V0QXR0cmlidXRlVmFsdWVBc1N0cmluZyhlbGVtZW50LCBhdHRyaWJ1dGVOYW1lLCBkZWZhdWx0VmFsdWUpIHtcclxuICAgIHZhciBhdHRyaWJ1dGUgPSBlbGVtZW50LmF0dHJpYnV0ZXNbYXR0cmlidXRlTmFtZV07XHJcbiAgICBpZiAoYXR0cmlidXRlKSB7XHJcbiAgICAgICAgcmV0dXJuIGF0dHJpYnV0ZS52YWx1ZTtcclxuICAgIH1cclxuICAgIHJldHVybiBkZWZhdWx0VmFsdWU7XHJcbn1cclxuZXhwb3J0IGZ1bmN0aW9uIGdldEF0dHJpYnV0ZVZhbHVlQXNJbnQoZWxlbWVudCwgYXR0cmlidXRlTmFtZSwgZGVmYXVsdFZhbHVlKSB7XHJcbiAgICB2YXIgYXR0cmlidXRlID0gZWxlbWVudC5hdHRyaWJ1dGVzW2F0dHJpYnV0ZU5hbWVdO1xyXG4gICAgaWYgKGF0dHJpYnV0ZSkge1xyXG4gICAgICAgIHZhciBuID0gcGFyc2VJbnQoYXR0cmlidXRlLnZhbHVlKTtcclxuICAgICAgICBpZiAoIWlzTmFOKG4pKSB7XHJcbiAgICAgICAgICAgIHJldHVybiBuO1xyXG4gICAgICAgIH1cclxuICAgIH1cclxuICAgIHJldHVybiBkZWZhdWx0VmFsdWU7XHJcbn1cclxuLy8jIHNvdXJjZU1hcHBpbmdVUkw9dXRpbHMuanMubWFwIiwiLy8gZXh0cmFjdGVkIGJ5IG1pbmktY3NzLWV4dHJhY3QtcGx1Z2luIiwiLypcblx0TUlUIExpY2Vuc2UgaHR0cDovL3d3dy5vcGVuc291cmNlLm9yZy9saWNlbnNlcy9taXQtbGljZW5zZS5waHBcblx0QXV0aG9yIFRvYmlhcyBLb3BwZXJzIEBzb2tyYVxuKi9cblxudmFyIHN0eWxlc0luRG9tID0ge307XG5cbnZhclx0bWVtb2l6ZSA9IGZ1bmN0aW9uIChmbikge1xuXHR2YXIgbWVtbztcblxuXHRyZXR1cm4gZnVuY3Rpb24gKCkge1xuXHRcdGlmICh0eXBlb2YgbWVtbyA9PT0gXCJ1bmRlZmluZWRcIikgbWVtbyA9IGZuLmFwcGx5KHRoaXMsIGFyZ3VtZW50cyk7XG5cdFx0cmV0dXJuIG1lbW87XG5cdH07XG59O1xuXG52YXIgaXNPbGRJRSA9IG1lbW9pemUoZnVuY3Rpb24gKCkge1xuXHQvLyBUZXN0IGZvciBJRSA8PSA5IGFzIHByb3Bvc2VkIGJ5IEJyb3dzZXJoYWNrc1xuXHQvLyBAc2VlIGh0dHA6Ly9icm93c2VyaGFja3MuY29tLyNoYWNrLWU3MWQ4NjkyZjY1MzM0MTczZmVlNzE1YzIyMmNiODA1XG5cdC8vIFRlc3RzIGZvciBleGlzdGVuY2Ugb2Ygc3RhbmRhcmQgZ2xvYmFscyBpcyB0byBhbGxvdyBzdHlsZS1sb2FkZXJcblx0Ly8gdG8gb3BlcmF0ZSBjb3JyZWN0bHkgaW50byBub24tc3RhbmRhcmQgZW52aXJvbm1lbnRzXG5cdC8vIEBzZWUgaHR0cHM6Ly9naXRodWIuY29tL3dlYnBhY2stY29udHJpYi9zdHlsZS1sb2FkZXIvaXNzdWVzLzE3N1xuXHRyZXR1cm4gd2luZG93ICYmIGRvY3VtZW50ICYmIGRvY3VtZW50LmFsbCAmJiAhd2luZG93LmF0b2I7XG59KTtcblxudmFyIGdldFRhcmdldCA9IGZ1bmN0aW9uICh0YXJnZXQsIHBhcmVudCkge1xuICBpZiAocGFyZW50KXtcbiAgICByZXR1cm4gcGFyZW50LnF1ZXJ5U2VsZWN0b3IodGFyZ2V0KTtcbiAgfVxuICByZXR1cm4gZG9jdW1lbnQucXVlcnlTZWxlY3Rvcih0YXJnZXQpO1xufTtcblxudmFyIGdldEVsZW1lbnQgPSAoZnVuY3Rpb24gKGZuKSB7XG5cdHZhciBtZW1vID0ge307XG5cblx0cmV0dXJuIGZ1bmN0aW9uKHRhcmdldCwgcGFyZW50KSB7XG4gICAgICAgICAgICAgICAgLy8gSWYgcGFzc2luZyBmdW5jdGlvbiBpbiBvcHRpb25zLCB0aGVuIHVzZSBpdCBmb3IgcmVzb2x2ZSBcImhlYWRcIiBlbGVtZW50LlxuICAgICAgICAgICAgICAgIC8vIFVzZWZ1bCBmb3IgU2hhZG93IFJvb3Qgc3R5bGUgaS5lXG4gICAgICAgICAgICAgICAgLy8ge1xuICAgICAgICAgICAgICAgIC8vICAgaW5zZXJ0SW50bzogZnVuY3Rpb24gKCkgeyByZXR1cm4gZG9jdW1lbnQucXVlcnlTZWxlY3RvcihcIiNmb29cIikuc2hhZG93Um9vdCB9XG4gICAgICAgICAgICAgICAgLy8gfVxuICAgICAgICAgICAgICAgIGlmICh0eXBlb2YgdGFyZ2V0ID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICByZXR1cm4gdGFyZ2V0KCk7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGlmICh0eXBlb2YgbWVtb1t0YXJnZXRdID09PSBcInVuZGVmaW5lZFwiKSB7XG5cdFx0XHR2YXIgc3R5bGVUYXJnZXQgPSBnZXRUYXJnZXQuY2FsbCh0aGlzLCB0YXJnZXQsIHBhcmVudCk7XG5cdFx0XHQvLyBTcGVjaWFsIGNhc2UgdG8gcmV0dXJuIGhlYWQgb2YgaWZyYW1lIGluc3RlYWQgb2YgaWZyYW1lIGl0c2VsZlxuXHRcdFx0aWYgKHdpbmRvdy5IVE1MSUZyYW1lRWxlbWVudCAmJiBzdHlsZVRhcmdldCBpbnN0YW5jZW9mIHdpbmRvdy5IVE1MSUZyYW1lRWxlbWVudCkge1xuXHRcdFx0XHR0cnkge1xuXHRcdFx0XHRcdC8vIFRoaXMgd2lsbCB0aHJvdyBhbiBleGNlcHRpb24gaWYgYWNjZXNzIHRvIGlmcmFtZSBpcyBibG9ja2VkXG5cdFx0XHRcdFx0Ly8gZHVlIHRvIGNyb3NzLW9yaWdpbiByZXN0cmljdGlvbnNcblx0XHRcdFx0XHRzdHlsZVRhcmdldCA9IHN0eWxlVGFyZ2V0LmNvbnRlbnREb2N1bWVudC5oZWFkO1xuXHRcdFx0XHR9IGNhdGNoKGUpIHtcblx0XHRcdFx0XHRzdHlsZVRhcmdldCA9IG51bGw7XG5cdFx0XHRcdH1cblx0XHRcdH1cblx0XHRcdG1lbW9bdGFyZ2V0XSA9IHN0eWxlVGFyZ2V0O1xuXHRcdH1cblx0XHRyZXR1cm4gbWVtb1t0YXJnZXRdXG5cdH07XG59KSgpO1xuXG52YXIgc2luZ2xldG9uID0gbnVsbDtcbnZhclx0c2luZ2xldG9uQ291bnRlciA9IDA7XG52YXJcdHN0eWxlc0luc2VydGVkQXRUb3AgPSBbXTtcblxudmFyXHRmaXhVcmxzID0gcmVxdWlyZShcIi4vdXJsc1wiKTtcblxubW9kdWxlLmV4cG9ydHMgPSBmdW5jdGlvbihsaXN0LCBvcHRpb25zKSB7XG5cdGlmICh0eXBlb2YgREVCVUcgIT09IFwidW5kZWZpbmVkXCIgJiYgREVCVUcpIHtcblx0XHRpZiAodHlwZW9mIGRvY3VtZW50ICE9PSBcIm9iamVjdFwiKSB0aHJvdyBuZXcgRXJyb3IoXCJUaGUgc3R5bGUtbG9hZGVyIGNhbm5vdCBiZSB1c2VkIGluIGEgbm9uLWJyb3dzZXIgZW52aXJvbm1lbnRcIik7XG5cdH1cblxuXHRvcHRpb25zID0gb3B0aW9ucyB8fCB7fTtcblxuXHRvcHRpb25zLmF0dHJzID0gdHlwZW9mIG9wdGlvbnMuYXR0cnMgPT09IFwib2JqZWN0XCIgPyBvcHRpb25zLmF0dHJzIDoge307XG5cblx0Ly8gRm9yY2Ugc2luZ2xlLXRhZyBzb2x1dGlvbiBvbiBJRTYtOSwgd2hpY2ggaGFzIGEgaGFyZCBsaW1pdCBvbiB0aGUgIyBvZiA8c3R5bGU+XG5cdC8vIHRhZ3MgaXQgd2lsbCBhbGxvdyBvbiBhIHBhZ2Vcblx0aWYgKCFvcHRpb25zLnNpbmdsZXRvbiAmJiB0eXBlb2Ygb3B0aW9ucy5zaW5nbGV0b24gIT09IFwiYm9vbGVhblwiKSBvcHRpb25zLnNpbmdsZXRvbiA9IGlzT2xkSUUoKTtcblxuXHQvLyBCeSBkZWZhdWx0LCBhZGQgPHN0eWxlPiB0YWdzIHRvIHRoZSA8aGVhZD4gZWxlbWVudFxuICAgICAgICBpZiAoIW9wdGlvbnMuaW5zZXJ0SW50bykgb3B0aW9ucy5pbnNlcnRJbnRvID0gXCJoZWFkXCI7XG5cblx0Ly8gQnkgZGVmYXVsdCwgYWRkIDxzdHlsZT4gdGFncyB0byB0aGUgYm90dG9tIG9mIHRoZSB0YXJnZXRcblx0aWYgKCFvcHRpb25zLmluc2VydEF0KSBvcHRpb25zLmluc2VydEF0ID0gXCJib3R0b21cIjtcblxuXHR2YXIgc3R5bGVzID0gbGlzdFRvU3R5bGVzKGxpc3QsIG9wdGlvbnMpO1xuXG5cdGFkZFN0eWxlc1RvRG9tKHN0eWxlcywgb3B0aW9ucyk7XG5cblx0cmV0dXJuIGZ1bmN0aW9uIHVwZGF0ZSAobmV3TGlzdCkge1xuXHRcdHZhciBtYXlSZW1vdmUgPSBbXTtcblxuXHRcdGZvciAodmFyIGkgPSAwOyBpIDwgc3R5bGVzLmxlbmd0aDsgaSsrKSB7XG5cdFx0XHR2YXIgaXRlbSA9IHN0eWxlc1tpXTtcblx0XHRcdHZhciBkb21TdHlsZSA9IHN0eWxlc0luRG9tW2l0ZW0uaWRdO1xuXG5cdFx0XHRkb21TdHlsZS5yZWZzLS07XG5cdFx0XHRtYXlSZW1vdmUucHVzaChkb21TdHlsZSk7XG5cdFx0fVxuXG5cdFx0aWYobmV3TGlzdCkge1xuXHRcdFx0dmFyIG5ld1N0eWxlcyA9IGxpc3RUb1N0eWxlcyhuZXdMaXN0LCBvcHRpb25zKTtcblx0XHRcdGFkZFN0eWxlc1RvRG9tKG5ld1N0eWxlcywgb3B0aW9ucyk7XG5cdFx0fVxuXG5cdFx0Zm9yICh2YXIgaSA9IDA7IGkgPCBtYXlSZW1vdmUubGVuZ3RoOyBpKyspIHtcblx0XHRcdHZhciBkb21TdHlsZSA9IG1heVJlbW92ZVtpXTtcblxuXHRcdFx0aWYoZG9tU3R5bGUucmVmcyA9PT0gMCkge1xuXHRcdFx0XHRmb3IgKHZhciBqID0gMDsgaiA8IGRvbVN0eWxlLnBhcnRzLmxlbmd0aDsgaisrKSBkb21TdHlsZS5wYXJ0c1tqXSgpO1xuXG5cdFx0XHRcdGRlbGV0ZSBzdHlsZXNJbkRvbVtkb21TdHlsZS5pZF07XG5cdFx0XHR9XG5cdFx0fVxuXHR9O1xufTtcblxuZnVuY3Rpb24gYWRkU3R5bGVzVG9Eb20gKHN0eWxlcywgb3B0aW9ucykge1xuXHRmb3IgKHZhciBpID0gMDsgaSA8IHN0eWxlcy5sZW5ndGg7IGkrKykge1xuXHRcdHZhciBpdGVtID0gc3R5bGVzW2ldO1xuXHRcdHZhciBkb21TdHlsZSA9IHN0eWxlc0luRG9tW2l0ZW0uaWRdO1xuXG5cdFx0aWYoZG9tU3R5bGUpIHtcblx0XHRcdGRvbVN0eWxlLnJlZnMrKztcblxuXHRcdFx0Zm9yKHZhciBqID0gMDsgaiA8IGRvbVN0eWxlLnBhcnRzLmxlbmd0aDsgaisrKSB7XG5cdFx0XHRcdGRvbVN0eWxlLnBhcnRzW2pdKGl0ZW0ucGFydHNbal0pO1xuXHRcdFx0fVxuXG5cdFx0XHRmb3IoOyBqIDwgaXRlbS5wYXJ0cy5sZW5ndGg7IGorKykge1xuXHRcdFx0XHRkb21TdHlsZS5wYXJ0cy5wdXNoKGFkZFN0eWxlKGl0ZW0ucGFydHNbal0sIG9wdGlvbnMpKTtcblx0XHRcdH1cblx0XHR9IGVsc2Uge1xuXHRcdFx0dmFyIHBhcnRzID0gW107XG5cblx0XHRcdGZvcih2YXIgaiA9IDA7IGogPCBpdGVtLnBhcnRzLmxlbmd0aDsgaisrKSB7XG5cdFx0XHRcdHBhcnRzLnB1c2goYWRkU3R5bGUoaXRlbS5wYXJ0c1tqXSwgb3B0aW9ucykpO1xuXHRcdFx0fVxuXG5cdFx0XHRzdHlsZXNJbkRvbVtpdGVtLmlkXSA9IHtpZDogaXRlbS5pZCwgcmVmczogMSwgcGFydHM6IHBhcnRzfTtcblx0XHR9XG5cdH1cbn1cblxuZnVuY3Rpb24gbGlzdFRvU3R5bGVzIChsaXN0LCBvcHRpb25zKSB7XG5cdHZhciBzdHlsZXMgPSBbXTtcblx0dmFyIG5ld1N0eWxlcyA9IHt9O1xuXG5cdGZvciAodmFyIGkgPSAwOyBpIDwgbGlzdC5sZW5ndGg7IGkrKykge1xuXHRcdHZhciBpdGVtID0gbGlzdFtpXTtcblx0XHR2YXIgaWQgPSBvcHRpb25zLmJhc2UgPyBpdGVtWzBdICsgb3B0aW9ucy5iYXNlIDogaXRlbVswXTtcblx0XHR2YXIgY3NzID0gaXRlbVsxXTtcblx0XHR2YXIgbWVkaWEgPSBpdGVtWzJdO1xuXHRcdHZhciBzb3VyY2VNYXAgPSBpdGVtWzNdO1xuXHRcdHZhciBwYXJ0ID0ge2NzczogY3NzLCBtZWRpYTogbWVkaWEsIHNvdXJjZU1hcDogc291cmNlTWFwfTtcblxuXHRcdGlmKCFuZXdTdHlsZXNbaWRdKSBzdHlsZXMucHVzaChuZXdTdHlsZXNbaWRdID0ge2lkOiBpZCwgcGFydHM6IFtwYXJ0XX0pO1xuXHRcdGVsc2UgbmV3U3R5bGVzW2lkXS5wYXJ0cy5wdXNoKHBhcnQpO1xuXHR9XG5cblx0cmV0dXJuIHN0eWxlcztcbn1cblxuZnVuY3Rpb24gaW5zZXJ0U3R5bGVFbGVtZW50IChvcHRpb25zLCBzdHlsZSkge1xuXHR2YXIgdGFyZ2V0ID0gZ2V0RWxlbWVudChvcHRpb25zLmluc2VydEludG8pXG5cblx0aWYgKCF0YXJnZXQpIHtcblx0XHR0aHJvdyBuZXcgRXJyb3IoXCJDb3VsZG4ndCBmaW5kIGEgc3R5bGUgdGFyZ2V0LiBUaGlzIHByb2JhYmx5IG1lYW5zIHRoYXQgdGhlIHZhbHVlIGZvciB0aGUgJ2luc2VydEludG8nIHBhcmFtZXRlciBpcyBpbnZhbGlkLlwiKTtcblx0fVxuXG5cdHZhciBsYXN0U3R5bGVFbGVtZW50SW5zZXJ0ZWRBdFRvcCA9IHN0eWxlc0luc2VydGVkQXRUb3Bbc3R5bGVzSW5zZXJ0ZWRBdFRvcC5sZW5ndGggLSAxXTtcblxuXHRpZiAob3B0aW9ucy5pbnNlcnRBdCA9PT0gXCJ0b3BcIikge1xuXHRcdGlmICghbGFzdFN0eWxlRWxlbWVudEluc2VydGVkQXRUb3ApIHtcblx0XHRcdHRhcmdldC5pbnNlcnRCZWZvcmUoc3R5bGUsIHRhcmdldC5maXJzdENoaWxkKTtcblx0XHR9IGVsc2UgaWYgKGxhc3RTdHlsZUVsZW1lbnRJbnNlcnRlZEF0VG9wLm5leHRTaWJsaW5nKSB7XG5cdFx0XHR0YXJnZXQuaW5zZXJ0QmVmb3JlKHN0eWxlLCBsYXN0U3R5bGVFbGVtZW50SW5zZXJ0ZWRBdFRvcC5uZXh0U2libGluZyk7XG5cdFx0fSBlbHNlIHtcblx0XHRcdHRhcmdldC5hcHBlbmRDaGlsZChzdHlsZSk7XG5cdFx0fVxuXHRcdHN0eWxlc0luc2VydGVkQXRUb3AucHVzaChzdHlsZSk7XG5cdH0gZWxzZSBpZiAob3B0aW9ucy5pbnNlcnRBdCA9PT0gXCJib3R0b21cIikge1xuXHRcdHRhcmdldC5hcHBlbmRDaGlsZChzdHlsZSk7XG5cdH0gZWxzZSBpZiAodHlwZW9mIG9wdGlvbnMuaW5zZXJ0QXQgPT09IFwib2JqZWN0XCIgJiYgb3B0aW9ucy5pbnNlcnRBdC5iZWZvcmUpIHtcblx0XHR2YXIgbmV4dFNpYmxpbmcgPSBnZXRFbGVtZW50KG9wdGlvbnMuaW5zZXJ0QXQuYmVmb3JlLCB0YXJnZXQpO1xuXHRcdHRhcmdldC5pbnNlcnRCZWZvcmUoc3R5bGUsIG5leHRTaWJsaW5nKTtcblx0fSBlbHNlIHtcblx0XHR0aHJvdyBuZXcgRXJyb3IoXCJbU3R5bGUgTG9hZGVyXVxcblxcbiBJbnZhbGlkIHZhbHVlIGZvciBwYXJhbWV0ZXIgJ2luc2VydEF0JyAoJ29wdGlvbnMuaW5zZXJ0QXQnKSBmb3VuZC5cXG4gTXVzdCBiZSAndG9wJywgJ2JvdHRvbScsIG9yIE9iamVjdC5cXG4gKGh0dHBzOi8vZ2l0aHViLmNvbS93ZWJwYWNrLWNvbnRyaWIvc3R5bGUtbG9hZGVyI2luc2VydGF0KVxcblwiKTtcblx0fVxufVxuXG5mdW5jdGlvbiByZW1vdmVTdHlsZUVsZW1lbnQgKHN0eWxlKSB7XG5cdGlmIChzdHlsZS5wYXJlbnROb2RlID09PSBudWxsKSByZXR1cm4gZmFsc2U7XG5cdHN0eWxlLnBhcmVudE5vZGUucmVtb3ZlQ2hpbGQoc3R5bGUpO1xuXG5cdHZhciBpZHggPSBzdHlsZXNJbnNlcnRlZEF0VG9wLmluZGV4T2Yoc3R5bGUpO1xuXHRpZihpZHggPj0gMCkge1xuXHRcdHN0eWxlc0luc2VydGVkQXRUb3Auc3BsaWNlKGlkeCwgMSk7XG5cdH1cbn1cblxuZnVuY3Rpb24gY3JlYXRlU3R5bGVFbGVtZW50IChvcHRpb25zKSB7XG5cdHZhciBzdHlsZSA9IGRvY3VtZW50LmNyZWF0ZUVsZW1lbnQoXCJzdHlsZVwiKTtcblxuXHRpZihvcHRpb25zLmF0dHJzLnR5cGUgPT09IHVuZGVmaW5lZCkge1xuXHRcdG9wdGlvbnMuYXR0cnMudHlwZSA9IFwidGV4dC9jc3NcIjtcblx0fVxuXG5cdGlmKG9wdGlvbnMuYXR0cnMubm9uY2UgPT09IHVuZGVmaW5lZCkge1xuXHRcdHZhciBub25jZSA9IGdldE5vbmNlKCk7XG5cdFx0aWYgKG5vbmNlKSB7XG5cdFx0XHRvcHRpb25zLmF0dHJzLm5vbmNlID0gbm9uY2U7XG5cdFx0fVxuXHR9XG5cblx0YWRkQXR0cnMoc3R5bGUsIG9wdGlvbnMuYXR0cnMpO1xuXHRpbnNlcnRTdHlsZUVsZW1lbnQob3B0aW9ucywgc3R5bGUpO1xuXG5cdHJldHVybiBzdHlsZTtcbn1cblxuZnVuY3Rpb24gY3JlYXRlTGlua0VsZW1lbnQgKG9wdGlvbnMpIHtcblx0dmFyIGxpbmsgPSBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwibGlua1wiKTtcblxuXHRpZihvcHRpb25zLmF0dHJzLnR5cGUgPT09IHVuZGVmaW5lZCkge1xuXHRcdG9wdGlvbnMuYXR0cnMudHlwZSA9IFwidGV4dC9jc3NcIjtcblx0fVxuXHRvcHRpb25zLmF0dHJzLnJlbCA9IFwic3R5bGVzaGVldFwiO1xuXG5cdGFkZEF0dHJzKGxpbmssIG9wdGlvbnMuYXR0cnMpO1xuXHRpbnNlcnRTdHlsZUVsZW1lbnQob3B0aW9ucywgbGluayk7XG5cblx0cmV0dXJuIGxpbms7XG59XG5cbmZ1bmN0aW9uIGFkZEF0dHJzIChlbCwgYXR0cnMpIHtcblx0T2JqZWN0LmtleXMoYXR0cnMpLmZvckVhY2goZnVuY3Rpb24gKGtleSkge1xuXHRcdGVsLnNldEF0dHJpYnV0ZShrZXksIGF0dHJzW2tleV0pO1xuXHR9KTtcbn1cblxuZnVuY3Rpb24gZ2V0Tm9uY2UoKSB7XG5cdGlmICh0eXBlb2YgX193ZWJwYWNrX25vbmNlX18gPT09ICd1bmRlZmluZWQnKSB7XG5cdFx0cmV0dXJuIG51bGw7XG5cdH1cblxuXHRyZXR1cm4gX193ZWJwYWNrX25vbmNlX187XG59XG5cbmZ1bmN0aW9uIGFkZFN0eWxlIChvYmosIG9wdGlvbnMpIHtcblx0dmFyIHN0eWxlLCB1cGRhdGUsIHJlbW92ZSwgcmVzdWx0O1xuXG5cdC8vIElmIGEgdHJhbnNmb3JtIGZ1bmN0aW9uIHdhcyBkZWZpbmVkLCBydW4gaXQgb24gdGhlIGNzc1xuXHRpZiAob3B0aW9ucy50cmFuc2Zvcm0gJiYgb2JqLmNzcykge1xuXHQgICAgcmVzdWx0ID0gdHlwZW9mIG9wdGlvbnMudHJhbnNmb3JtID09PSAnZnVuY3Rpb24nXG5cdFx0ID8gb3B0aW9ucy50cmFuc2Zvcm0ob2JqLmNzcykgXG5cdFx0IDogb3B0aW9ucy50cmFuc2Zvcm0uZGVmYXVsdChvYmouY3NzKTtcblxuXHQgICAgaWYgKHJlc3VsdCkge1xuXHQgICAgXHQvLyBJZiB0cmFuc2Zvcm0gcmV0dXJucyBhIHZhbHVlLCB1c2UgdGhhdCBpbnN0ZWFkIG9mIHRoZSBvcmlnaW5hbCBjc3MuXG5cdCAgICBcdC8vIFRoaXMgYWxsb3dzIHJ1bm5pbmcgcnVudGltZSB0cmFuc2Zvcm1hdGlvbnMgb24gdGhlIGNzcy5cblx0ICAgIFx0b2JqLmNzcyA9IHJlc3VsdDtcblx0ICAgIH0gZWxzZSB7XG5cdCAgICBcdC8vIElmIHRoZSB0cmFuc2Zvcm0gZnVuY3Rpb24gcmV0dXJucyBhIGZhbHN5IHZhbHVlLCBkb24ndCBhZGQgdGhpcyBjc3MuXG5cdCAgICBcdC8vIFRoaXMgYWxsb3dzIGNvbmRpdGlvbmFsIGxvYWRpbmcgb2YgY3NzXG5cdCAgICBcdHJldHVybiBmdW5jdGlvbigpIHtcblx0ICAgIFx0XHQvLyBub29wXG5cdCAgICBcdH07XG5cdCAgICB9XG5cdH1cblxuXHRpZiAob3B0aW9ucy5zaW5nbGV0b24pIHtcblx0XHR2YXIgc3R5bGVJbmRleCA9IHNpbmdsZXRvbkNvdW50ZXIrKztcblxuXHRcdHN0eWxlID0gc2luZ2xldG9uIHx8IChzaW5nbGV0b24gPSBjcmVhdGVTdHlsZUVsZW1lbnQob3B0aW9ucykpO1xuXG5cdFx0dXBkYXRlID0gYXBwbHlUb1NpbmdsZXRvblRhZy5iaW5kKG51bGwsIHN0eWxlLCBzdHlsZUluZGV4LCBmYWxzZSk7XG5cdFx0cmVtb3ZlID0gYXBwbHlUb1NpbmdsZXRvblRhZy5iaW5kKG51bGwsIHN0eWxlLCBzdHlsZUluZGV4LCB0cnVlKTtcblxuXHR9IGVsc2UgaWYgKFxuXHRcdG9iai5zb3VyY2VNYXAgJiZcblx0XHR0eXBlb2YgVVJMID09PSBcImZ1bmN0aW9uXCIgJiZcblx0XHR0eXBlb2YgVVJMLmNyZWF0ZU9iamVjdFVSTCA9PT0gXCJmdW5jdGlvblwiICYmXG5cdFx0dHlwZW9mIFVSTC5yZXZva2VPYmplY3RVUkwgPT09IFwiZnVuY3Rpb25cIiAmJlxuXHRcdHR5cGVvZiBCbG9iID09PSBcImZ1bmN0aW9uXCIgJiZcblx0XHR0eXBlb2YgYnRvYSA9PT0gXCJmdW5jdGlvblwiXG5cdCkge1xuXHRcdHN0eWxlID0gY3JlYXRlTGlua0VsZW1lbnQob3B0aW9ucyk7XG5cdFx0dXBkYXRlID0gdXBkYXRlTGluay5iaW5kKG51bGwsIHN0eWxlLCBvcHRpb25zKTtcblx0XHRyZW1vdmUgPSBmdW5jdGlvbiAoKSB7XG5cdFx0XHRyZW1vdmVTdHlsZUVsZW1lbnQoc3R5bGUpO1xuXG5cdFx0XHRpZihzdHlsZS5ocmVmKSBVUkwucmV2b2tlT2JqZWN0VVJMKHN0eWxlLmhyZWYpO1xuXHRcdH07XG5cdH0gZWxzZSB7XG5cdFx0c3R5bGUgPSBjcmVhdGVTdHlsZUVsZW1lbnQob3B0aW9ucyk7XG5cdFx0dXBkYXRlID0gYXBwbHlUb1RhZy5iaW5kKG51bGwsIHN0eWxlKTtcblx0XHRyZW1vdmUgPSBmdW5jdGlvbiAoKSB7XG5cdFx0XHRyZW1vdmVTdHlsZUVsZW1lbnQoc3R5bGUpO1xuXHRcdH07XG5cdH1cblxuXHR1cGRhdGUob2JqKTtcblxuXHRyZXR1cm4gZnVuY3Rpb24gdXBkYXRlU3R5bGUgKG5ld09iaikge1xuXHRcdGlmIChuZXdPYmopIHtcblx0XHRcdGlmIChcblx0XHRcdFx0bmV3T2JqLmNzcyA9PT0gb2JqLmNzcyAmJlxuXHRcdFx0XHRuZXdPYmoubWVkaWEgPT09IG9iai5tZWRpYSAmJlxuXHRcdFx0XHRuZXdPYmouc291cmNlTWFwID09PSBvYmouc291cmNlTWFwXG5cdFx0XHQpIHtcblx0XHRcdFx0cmV0dXJuO1xuXHRcdFx0fVxuXG5cdFx0XHR1cGRhdGUob2JqID0gbmV3T2JqKTtcblx0XHR9IGVsc2Uge1xuXHRcdFx0cmVtb3ZlKCk7XG5cdFx0fVxuXHR9O1xufVxuXG52YXIgcmVwbGFjZVRleHQgPSAoZnVuY3Rpb24gKCkge1xuXHR2YXIgdGV4dFN0b3JlID0gW107XG5cblx0cmV0dXJuIGZ1bmN0aW9uIChpbmRleCwgcmVwbGFjZW1lbnQpIHtcblx0XHR0ZXh0U3RvcmVbaW5kZXhdID0gcmVwbGFjZW1lbnQ7XG5cblx0XHRyZXR1cm4gdGV4dFN0b3JlLmZpbHRlcihCb29sZWFuKS5qb2luKCdcXG4nKTtcblx0fTtcbn0pKCk7XG5cbmZ1bmN0aW9uIGFwcGx5VG9TaW5nbGV0b25UYWcgKHN0eWxlLCBpbmRleCwgcmVtb3ZlLCBvYmopIHtcblx0dmFyIGNzcyA9IHJlbW92ZSA/IFwiXCIgOiBvYmouY3NzO1xuXG5cdGlmIChzdHlsZS5zdHlsZVNoZWV0KSB7XG5cdFx0c3R5bGUuc3R5bGVTaGVldC5jc3NUZXh0ID0gcmVwbGFjZVRleHQoaW5kZXgsIGNzcyk7XG5cdH0gZWxzZSB7XG5cdFx0dmFyIGNzc05vZGUgPSBkb2N1bWVudC5jcmVhdGVUZXh0Tm9kZShjc3MpO1xuXHRcdHZhciBjaGlsZE5vZGVzID0gc3R5bGUuY2hpbGROb2RlcztcblxuXHRcdGlmIChjaGlsZE5vZGVzW2luZGV4XSkgc3R5bGUucmVtb3ZlQ2hpbGQoY2hpbGROb2Rlc1tpbmRleF0pO1xuXG5cdFx0aWYgKGNoaWxkTm9kZXMubGVuZ3RoKSB7XG5cdFx0XHRzdHlsZS5pbnNlcnRCZWZvcmUoY3NzTm9kZSwgY2hpbGROb2Rlc1tpbmRleF0pO1xuXHRcdH0gZWxzZSB7XG5cdFx0XHRzdHlsZS5hcHBlbmRDaGlsZChjc3NOb2RlKTtcblx0XHR9XG5cdH1cbn1cblxuZnVuY3Rpb24gYXBwbHlUb1RhZyAoc3R5bGUsIG9iaikge1xuXHR2YXIgY3NzID0gb2JqLmNzcztcblx0dmFyIG1lZGlhID0gb2JqLm1lZGlhO1xuXG5cdGlmKG1lZGlhKSB7XG5cdFx0c3R5bGUuc2V0QXR0cmlidXRlKFwibWVkaWFcIiwgbWVkaWEpXG5cdH1cblxuXHRpZihzdHlsZS5zdHlsZVNoZWV0KSB7XG5cdFx0c3R5bGUuc3R5bGVTaGVldC5jc3NUZXh0ID0gY3NzO1xuXHR9IGVsc2Uge1xuXHRcdHdoaWxlKHN0eWxlLmZpcnN0Q2hpbGQpIHtcblx0XHRcdHN0eWxlLnJlbW92ZUNoaWxkKHN0eWxlLmZpcnN0Q2hpbGQpO1xuXHRcdH1cblxuXHRcdHN0eWxlLmFwcGVuZENoaWxkKGRvY3VtZW50LmNyZWF0ZVRleHROb2RlKGNzcykpO1xuXHR9XG59XG5cbmZ1bmN0aW9uIHVwZGF0ZUxpbmsgKGxpbmssIG9wdGlvbnMsIG9iaikge1xuXHR2YXIgY3NzID0gb2JqLmNzcztcblx0dmFyIHNvdXJjZU1hcCA9IG9iai5zb3VyY2VNYXA7XG5cblx0Lypcblx0XHRJZiBjb252ZXJ0VG9BYnNvbHV0ZVVybHMgaXNuJ3QgZGVmaW5lZCwgYnV0IHNvdXJjZW1hcHMgYXJlIGVuYWJsZWRcblx0XHRhbmQgdGhlcmUgaXMgbm8gcHVibGljUGF0aCBkZWZpbmVkIHRoZW4gbGV0cyB0dXJuIGNvbnZlcnRUb0Fic29sdXRlVXJsc1xuXHRcdG9uIGJ5IGRlZmF1bHQuICBPdGhlcndpc2UgZGVmYXVsdCB0byB0aGUgY29udmVydFRvQWJzb2x1dGVVcmxzIG9wdGlvblxuXHRcdGRpcmVjdGx5XG5cdCovXG5cdHZhciBhdXRvRml4VXJscyA9IG9wdGlvbnMuY29udmVydFRvQWJzb2x1dGVVcmxzID09PSB1bmRlZmluZWQgJiYgc291cmNlTWFwO1xuXG5cdGlmIChvcHRpb25zLmNvbnZlcnRUb0Fic29sdXRlVXJscyB8fCBhdXRvRml4VXJscykge1xuXHRcdGNzcyA9IGZpeFVybHMoY3NzKTtcblx0fVxuXG5cdGlmIChzb3VyY2VNYXApIHtcblx0XHQvLyBodHRwOi8vc3RhY2tvdmVyZmxvdy5jb20vYS8yNjYwMzg3NVxuXHRcdGNzcyArPSBcIlxcbi8qIyBzb3VyY2VNYXBwaW5nVVJMPWRhdGE6YXBwbGljYXRpb24vanNvbjtiYXNlNjQsXCIgKyBidG9hKHVuZXNjYXBlKGVuY29kZVVSSUNvbXBvbmVudChKU09OLnN0cmluZ2lmeShzb3VyY2VNYXApKSkpICsgXCIgKi9cIjtcblx0fVxuXG5cdHZhciBibG9iID0gbmV3IEJsb2IoW2Nzc10sIHsgdHlwZTogXCJ0ZXh0L2Nzc1wiIH0pO1xuXG5cdHZhciBvbGRTcmMgPSBsaW5rLmhyZWY7XG5cblx0bGluay5ocmVmID0gVVJMLmNyZWF0ZU9iamVjdFVSTChibG9iKTtcblxuXHRpZihvbGRTcmMpIFVSTC5yZXZva2VPYmplY3RVUkwob2xkU3JjKTtcbn1cbiIsIlxuLyoqXG4gKiBXaGVuIHNvdXJjZSBtYXBzIGFyZSBlbmFibGVkLCBgc3R5bGUtbG9hZGVyYCB1c2VzIGEgbGluayBlbGVtZW50IHdpdGggYSBkYXRhLXVyaSB0b1xuICogZW1iZWQgdGhlIGNzcyBvbiB0aGUgcGFnZS4gVGhpcyBicmVha3MgYWxsIHJlbGF0aXZlIHVybHMgYmVjYXVzZSBub3cgdGhleSBhcmUgcmVsYXRpdmUgdG8gYVxuICogYnVuZGxlIGluc3RlYWQgb2YgdGhlIGN1cnJlbnQgcGFnZS5cbiAqXG4gKiBPbmUgc29sdXRpb24gaXMgdG8gb25seSB1c2UgZnVsbCB1cmxzLCBidXQgdGhhdCBtYXkgYmUgaW1wb3NzaWJsZS5cbiAqXG4gKiBJbnN0ZWFkLCB0aGlzIGZ1bmN0aW9uIFwiZml4ZXNcIiB0aGUgcmVsYXRpdmUgdXJscyB0byBiZSBhYnNvbHV0ZSBhY2NvcmRpbmcgdG8gdGhlIGN1cnJlbnQgcGFnZSBsb2NhdGlvbi5cbiAqXG4gKiBBIHJ1ZGltZW50YXJ5IHRlc3Qgc3VpdGUgaXMgbG9jYXRlZCBhdCBgdGVzdC9maXhVcmxzLmpzYCBhbmQgY2FuIGJlIHJ1biB2aWEgdGhlIGBucG0gdGVzdGAgY29tbWFuZC5cbiAqXG4gKi9cblxubW9kdWxlLmV4cG9ydHMgPSBmdW5jdGlvbiAoY3NzKSB7XG4gIC8vIGdldCBjdXJyZW50IGxvY2F0aW9uXG4gIHZhciBsb2NhdGlvbiA9IHR5cGVvZiB3aW5kb3cgIT09IFwidW5kZWZpbmVkXCIgJiYgd2luZG93LmxvY2F0aW9uO1xuXG4gIGlmICghbG9jYXRpb24pIHtcbiAgICB0aHJvdyBuZXcgRXJyb3IoXCJmaXhVcmxzIHJlcXVpcmVzIHdpbmRvdy5sb2NhdGlvblwiKTtcbiAgfVxuXG5cdC8vIGJsYW5rIG9yIG51bGw/XG5cdGlmICghY3NzIHx8IHR5cGVvZiBjc3MgIT09IFwic3RyaW5nXCIpIHtcblx0ICByZXR1cm4gY3NzO1xuICB9XG5cbiAgdmFyIGJhc2VVcmwgPSBsb2NhdGlvbi5wcm90b2NvbCArIFwiLy9cIiArIGxvY2F0aW9uLmhvc3Q7XG4gIHZhciBjdXJyZW50RGlyID0gYmFzZVVybCArIGxvY2F0aW9uLnBhdGhuYW1lLnJlcGxhY2UoL1xcL1teXFwvXSokLywgXCIvXCIpO1xuXG5cdC8vIGNvbnZlcnQgZWFjaCB1cmwoLi4uKVxuXHQvKlxuXHRUaGlzIHJlZ3VsYXIgZXhwcmVzc2lvbiBpcyBqdXN0IGEgd2F5IHRvIHJlY3Vyc2l2ZWx5IG1hdGNoIGJyYWNrZXRzIHdpdGhpblxuXHRhIHN0cmluZy5cblxuXHQgL3VybFxccypcXCggID0gTWF0Y2ggb24gdGhlIHdvcmQgXCJ1cmxcIiB3aXRoIGFueSB3aGl0ZXNwYWNlIGFmdGVyIGl0IGFuZCB0aGVuIGEgcGFyZW5zXG5cdCAgICggID0gU3RhcnQgYSBjYXB0dXJpbmcgZ3JvdXBcblx0ICAgICAoPzogID0gU3RhcnQgYSBub24tY2FwdHVyaW5nIGdyb3VwXG5cdCAgICAgICAgIFteKShdICA9IE1hdGNoIGFueXRoaW5nIHRoYXQgaXNuJ3QgYSBwYXJlbnRoZXNlc1xuXHQgICAgICAgICB8ICA9IE9SXG5cdCAgICAgICAgIFxcKCAgPSBNYXRjaCBhIHN0YXJ0IHBhcmVudGhlc2VzXG5cdCAgICAgICAgICAgICAoPzogID0gU3RhcnQgYW5vdGhlciBub24tY2FwdHVyaW5nIGdyb3Vwc1xuXHQgICAgICAgICAgICAgICAgIFteKShdKyAgPSBNYXRjaCBhbnl0aGluZyB0aGF0IGlzbid0IGEgcGFyZW50aGVzZXNcblx0ICAgICAgICAgICAgICAgICB8ICA9IE9SXG5cdCAgICAgICAgICAgICAgICAgXFwoICA9IE1hdGNoIGEgc3RhcnQgcGFyZW50aGVzZXNcblx0ICAgICAgICAgICAgICAgICAgICAgW14pKF0qICA9IE1hdGNoIGFueXRoaW5nIHRoYXQgaXNuJ3QgYSBwYXJlbnRoZXNlc1xuXHQgICAgICAgICAgICAgICAgIFxcKSAgPSBNYXRjaCBhIGVuZCBwYXJlbnRoZXNlc1xuXHQgICAgICAgICAgICAgKSAgPSBFbmQgR3JvdXBcbiAgICAgICAgICAgICAgKlxcKSA9IE1hdGNoIGFueXRoaW5nIGFuZCB0aGVuIGEgY2xvc2UgcGFyZW5zXG4gICAgICAgICAgKSAgPSBDbG9zZSBub24tY2FwdHVyaW5nIGdyb3VwXG4gICAgICAgICAgKiAgPSBNYXRjaCBhbnl0aGluZ1xuICAgICAgICkgID0gQ2xvc2UgY2FwdHVyaW5nIGdyb3VwXG5cdCBcXCkgID0gTWF0Y2ggYSBjbG9zZSBwYXJlbnNcblxuXHQgL2dpICA9IEdldCBhbGwgbWF0Y2hlcywgbm90IHRoZSBmaXJzdC4gIEJlIGNhc2UgaW5zZW5zaXRpdmUuXG5cdCAqL1xuXHR2YXIgZml4ZWRDc3MgPSBjc3MucmVwbGFjZSgvdXJsXFxzKlxcKCgoPzpbXikoXXxcXCgoPzpbXikoXSt8XFwoW14pKF0qXFwpKSpcXCkpKilcXCkvZ2ksIGZ1bmN0aW9uKGZ1bGxNYXRjaCwgb3JpZ1VybCkge1xuXHRcdC8vIHN0cmlwIHF1b3RlcyAoaWYgdGhleSBleGlzdClcblx0XHR2YXIgdW5xdW90ZWRPcmlnVXJsID0gb3JpZ1VybFxuXHRcdFx0LnRyaW0oKVxuXHRcdFx0LnJlcGxhY2UoL15cIiguKilcIiQvLCBmdW5jdGlvbihvLCAkMSl7IHJldHVybiAkMTsgfSlcblx0XHRcdC5yZXBsYWNlKC9eJyguKiknJC8sIGZ1bmN0aW9uKG8sICQxKXsgcmV0dXJuICQxOyB9KTtcblxuXHRcdC8vIGFscmVhZHkgYSBmdWxsIHVybD8gbm8gY2hhbmdlXG5cdFx0aWYgKC9eKCN8ZGF0YTp8aHR0cDpcXC9cXC98aHR0cHM6XFwvXFwvfGZpbGU6XFwvXFwvXFwvfFxccyokKS9pLnRlc3QodW5xdW90ZWRPcmlnVXJsKSkge1xuXHRcdCAgcmV0dXJuIGZ1bGxNYXRjaDtcblx0XHR9XG5cblx0XHQvLyBjb252ZXJ0IHRoZSB1cmwgdG8gYSBmdWxsIHVybFxuXHRcdHZhciBuZXdVcmw7XG5cblx0XHRpZiAodW5xdW90ZWRPcmlnVXJsLmluZGV4T2YoXCIvL1wiKSA9PT0gMCkge1xuXHRcdCAgXHQvL1RPRE86IHNob3VsZCB3ZSBhZGQgcHJvdG9jb2w/XG5cdFx0XHRuZXdVcmwgPSB1bnF1b3RlZE9yaWdVcmw7XG5cdFx0fSBlbHNlIGlmICh1bnF1b3RlZE9yaWdVcmwuaW5kZXhPZihcIi9cIikgPT09IDApIHtcblx0XHRcdC8vIHBhdGggc2hvdWxkIGJlIHJlbGF0aXZlIHRvIHRoZSBiYXNlIHVybFxuXHRcdFx0bmV3VXJsID0gYmFzZVVybCArIHVucXVvdGVkT3JpZ1VybDsgLy8gYWxyZWFkeSBzdGFydHMgd2l0aCAnLydcblx0XHR9IGVsc2Uge1xuXHRcdFx0Ly8gcGF0aCBzaG91bGQgYmUgcmVsYXRpdmUgdG8gY3VycmVudCBkaXJlY3Rvcnlcblx0XHRcdG5ld1VybCA9IGN1cnJlbnREaXIgKyB1bnF1b3RlZE9yaWdVcmwucmVwbGFjZSgvXlxcLlxcLy8sIFwiXCIpOyAvLyBTdHJpcCBsZWFkaW5nICcuLydcblx0XHR9XG5cblx0XHQvLyBzZW5kIGJhY2sgdGhlIGZpeGVkIHVybCguLi4pXG5cdFx0cmV0dXJuIFwidXJsKFwiICsgSlNPTi5zdHJpbmdpZnkobmV3VXJsKSArIFwiKVwiO1xuXHR9KTtcblxuXHQvLyBzZW5kIGJhY2sgdGhlIGZpeGVkIGNzc1xuXHRyZXR1cm4gZml4ZWRDc3M7XG59O1xuIl0sInNvdXJjZVJvb3QiOiIifQ==