var ACFabric =
/******/ (function(modules) { // webpackBootstrap
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
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = "./src/index.ts");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./src/actions/ActionButton.tsx":
/*!**************************************!*\
  !*** ./src/actions/ActionButton.tsx ***!
  \**************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
Object.defineProperty(exports, "__esModule", { value: true });
var React = __webpack_require__(/*! react */ "react");
var office_ui_fabric_react_1 = __webpack_require__(/*! office-ui-fabric-react */ "office-ui-fabric-react");
var AC = __webpack_require__(/*! adaptivecards */ "adaptivecards");
exports.ActionButton = function (props) { return (props.iconUrl ?
    React.createElement(office_ui_fabric_react_1.CompoundButton, { className: props.className },
        React.createElement("div", { style: {
                display: "flex",
                flexDirection: props.iconPlacement === AC.ActionIconPlacement.LeftOfTitle ? "row" : "column",
                justifyContent: "center",
            } },
            React.createElement("img", { src: props.iconUrl, style: {
                    alignSelf: "center",
                    width: props.iconSize,
                    height: props.iconSize,
                    flex: "0 0 auto",
                } }),
            React.createElement("span", { style: { alignSelf: "center" } }, props.text))) :
    React.createElement(office_ui_fabric_react_1.PrimaryButton, { className: props.className, text: props.text })); };


/***/ }),

/***/ "./src/actions/Actions.tsx":
/*!*********************************!*\
  !*** ./src/actions/Actions.tsx ***!
  \*********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var React = __webpack_require__(/*! react */ "react");
var ReactDOM = __webpack_require__(/*! react-dom */ "react-dom");
var AC = __webpack_require__(/*! adaptivecards */ "adaptivecards");
var Shared = __webpack_require__(/*! ../utils/shared */ "./src/utils/shared.tsx");
var ActionButton_1 = __webpack_require__(/*! ./ActionButton */ "./src/actions/ActionButton.tsx");
exports.createActionDiv = function (title, iconUrl, baseCssClass, iconPlacement, iconSize) {
    var div = Shared.getDiv();
    ReactDOM.render(React.createElement(ActionButton_1.ActionButton, { text: title, className: baseCssClass, iconUrl: iconUrl, iconPlacement: iconPlacement, iconSize: iconSize }), div);
    return div;
};
var OpenUrlActionFabric = /** @class */ (function (_super) {
    __extends(OpenUrlActionFabric, _super);
    function OpenUrlActionFabric() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    Object.defineProperty(OpenUrlActionFabric.prototype, "renderedElement", {
        get: function () {
            return this.internalRenderedElement;
        },
        enumerable: true,
        configurable: true
    });
    OpenUrlActionFabric.prototype.render = function (baseCssClass) {
        var actionsConfig = this.parent.hostConfig.actions;
        var div = exports.createActionDiv(this.title, this.iconUrl, baseCssClass, actionsConfig.iconPlacement, actionsConfig.iconSize);
        this.internalRenderedElement = div;
    };
    return OpenUrlActionFabric;
}(AC.OpenUrlAction));
exports.OpenUrlActionFabric = OpenUrlActionFabric;
var SubmitActionFabric = /** @class */ (function (_super) {
    __extends(SubmitActionFabric, _super);
    function SubmitActionFabric() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    Object.defineProperty(SubmitActionFabric.prototype, "renderedElement", {
        get: function () {
            return this.internalRenderedElement;
        },
        enumerable: true,
        configurable: true
    });
    SubmitActionFabric.prototype.render = function (baseCssClass) {
        var actionsConfig = this.parent.hostConfig.actions;
        var div = exports.createActionDiv(this.title, this.iconUrl, baseCssClass, actionsConfig.iconPlacement, actionsConfig.iconSize);
        this.internalRenderedElement = div;
    };
    return SubmitActionFabric;
}(AC.SubmitAction));
exports.SubmitActionFabric = SubmitActionFabric;
var ShowCardActionFabric = /** @class */ (function (_super) {
    __extends(ShowCardActionFabric, _super);
    function ShowCardActionFabric() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    Object.defineProperty(ShowCardActionFabric.prototype, "renderedElement", {
        get: function () {
            return this.internalRenderedElement;
        },
        enumerable: true,
        configurable: true
    });
    ShowCardActionFabric.prototype.render = function (baseCssClass) {
        var actionsConfig = this.parent.hostConfig.actions;
        var div = exports.createActionDiv(this.title, this.iconUrl, baseCssClass, actionsConfig.iconPlacement, actionsConfig.iconSize);
        this.internalRenderedElement = div;
    };
    return ShowCardActionFabric;
}(AC.ShowCardAction));
exports.ShowCardActionFabric = ShowCardActionFabric;
var ToggleVisibilityActionFabric = /** @class */ (function (_super) {
    __extends(ToggleVisibilityActionFabric, _super);
    function ToggleVisibilityActionFabric() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    Object.defineProperty(ToggleVisibilityActionFabric.prototype, "renderedElement", {
        get: function () {
            return this.internalRenderedElement;
        },
        enumerable: true,
        configurable: true
    });
    ToggleVisibilityActionFabric.prototype.render = function (baseCssClass) {
        var div = Shared.getDiv();
        ReactDOM.render(React.createElement(ActionButton_1.ActionButton, { text: this.title, className: baseCssClass }), div);
        this.internalRenderedElement = div;
    };
    return ToggleVisibilityActionFabric;
}(AC.ToggleVisibilityAction));
exports.ToggleVisibilityActionFabric = ToggleVisibilityActionFabric;


/***/ }),

/***/ "./src/actions/index.ts":
/*!******************************!*\
  !*** ./src/actions/index.ts ***!
  \******************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

function __export(m) {
    for (var p in m) if (!exports.hasOwnProperty(p)) exports[p] = m[p];
}
Object.defineProperty(exports, "__esModule", { value: true });
__export(__webpack_require__(/*! ./Actions */ "./src/actions/Actions.tsx"));


/***/ }),

/***/ "./src/components/Fabric.tsx":
/*!***********************************!*\
  !*** ./src/components/Fabric.tsx ***!
  \***********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
Object.defineProperty(exports, "__esModule", { value: true });
var AC = __webpack_require__(/*! adaptivecards */ "adaptivecards");
var office_ui_fabric_react_1 = __webpack_require__(/*! office-ui-fabric-react */ "office-ui-fabric-react");
var Components = __webpack_require__(/*! . */ "./src/components/index.ts");
var Actions = __webpack_require__(/*! ../actions */ "./src/actions/index.ts");
var iconsInitialized = false;
exports.useFabricComponents = function () {
    if (!iconsInitialized) {
        office_ui_fabric_react_1.initializeIcons();
        iconsInitialized = true;
    }
    // add component extensions
    AC.AdaptiveCard.elementTypeRegistry.registerType("Input.Date", function () { return new Components.InputDateFabric(); });
    AC.AdaptiveCard.elementTypeRegistry.registerType("Input.Text", function () { return new Components.InputTextFabric(); });
    AC.AdaptiveCard.elementTypeRegistry.registerType("Input.Time", function () { return new Components.InputTimeFabric(); });
    AC.AdaptiveCard.elementTypeRegistry.registerType("Input.Number", function () { return new Components.InputNumberFabric(); });
    AC.AdaptiveCard.elementTypeRegistry.registerType("Input.Toggle", function () { return new Components.InputToggleFabric(); });
    AC.AdaptiveCard.elementTypeRegistry.registerType("Input.ChoiceSet", function () { return new Components.InputChoiceSetFabric(); });
    // add actions extensions
    AC.AdaptiveCard.actionTypeRegistry.registerType("Action.OpenUrl", function () { return new Actions.OpenUrlActionFabric(); });
    AC.AdaptiveCard.actionTypeRegistry.registerType("Action.Submit", function () { return new Actions.SubmitActionFabric(); });
    AC.AdaptiveCard.actionTypeRegistry.registerType("Action.ShowCard", function () { return new Actions.ShowCardActionFabric(); });
    AC.AdaptiveCard.actionTypeRegistry.registerType("Action.ToggleVisibility", function () { return new Actions.ToggleVisibilityActionFabric(); });
};


/***/ }),

/***/ "./src/components/index.ts":
/*!*********************************!*\
  !*** ./src/components/index.ts ***!
  \*********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
function __export(m) {
    for (var p in m) if (!exports.hasOwnProperty(p)) exports[p] = m[p];
}
Object.defineProperty(exports, "__esModule", { value: true });
__export(__webpack_require__(/*! ./inputs */ "./src/components/inputs/index.ts"));
__export(__webpack_require__(/*! ./Fabric */ "./src/components/Fabric.tsx"));


/***/ }),

/***/ "./src/components/inputs/InputChoiceSetFabric.tsx":
/*!********************************************************!*\
  !*** ./src/components/inputs/InputChoiceSetFabric.tsx ***!
  \********************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var React = __webpack_require__(/*! react */ "react");
var AC = __webpack_require__(/*! adaptivecards */ "adaptivecards");
var FabricUI = __webpack_require__(/*! office-ui-fabric-react */ "office-ui-fabric-react");
var Shared = __webpack_require__(/*! ../../utils/shared */ "./src/utils/shared.tsx");
var InputChoiceSetFabric = /** @class */ (function (_super) {
    __extends(InputChoiceSetFabric, _super);
    function InputChoiceSetFabric() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.selectedValues = [];
        _this.parse = function (json, errors) {
            _super.prototype.parse.call(_this, json, errors);
            _this.value = _this.defaultValue;
            _this.selectedValues = _this.defaultValueToArray(_this.value);
            _this.isMultiSelect = AC.getBoolValue(json.isMultiSelect, false);
            _this.title = AC.getStringValue(json.title);
            _this.style = AC.getStringValue(json.style);
            _this.parseChoises(json);
        };
        _this.renderReact = function () { return (_this.isCompact() ?
            React.createElement(_this.ComboBox, null) :
            _this.createExpandedView()); };
        _this.getJsonTypeName = function () { return "Input.ChoiceSet"; };
        _this.toJSON = function () {
            var result = _super.prototype.toJSON.call(_this);
            if (_this.choices.length > 0) {
                AC.setProperty(result, "choices", _this.choices.map(function (ch) { return ch.toJSON(); }));
            }
            if (!_this.isCompact()) {
                AC.setProperty(result, "style", "expanded", false);
            }
            AC.setProperty(result, "isMultiSelect", _this.isMultiSelect, false);
            return result;
        };
        _this.parseChoises = function (json) {
            _this.choices = Array.isArray(json.choices) ?
                json.choices.map(function (ch) {
                    var choice = new AC.Choice();
                    choice.parse(ch);
                    return choice;
                }) :
                [];
        };
        _this.isCompact = function () { return _this.style === "compact"; };
        _this.ComboBox = function () { return (React.createElement(FabricUI.ComboBox, { onChange: _this.handleComboBoxChange, id: _this.id, options: _this.inputChoicesToComboBoxOptions(_this.choices), multiSelect: _this.isMultiSelect, selectedKey: _this.defaultValueToArray(_this.value) })); };
        _this.createExpandedView = function () {
            return _this.isMultiSelect ?
                _this.inputChoicesToCheckbox() :
                _this.createChoiceGroup();
        };
        _this.createChoiceGroup = function () { return (React.createElement(FabricUI.ChoiceGroup, { id: _this.id, onChange: _this.handleChoiceGroupChange, options: _this.inputChoicesToChoiceGroupOptions(_this.choices, _this.defaultValueToArray(_this.value)), multiple: _this.isMultiSelect })); };
        _this.inputChoicesToCheckbox = function () { return (React.createElement(React.Fragment, null, _this.choices.map(function (c, i) {
            return React.createElement(FabricUI.Checkbox, { key: c.value, label: c.title, defaultChecked: _this.defaultValueToArray(_this.value).includes(c.value), onChange: function (ev, checked) {
                    _this.updateMultiselectData(checked, c.value);
                    ev.stopPropagation();
                    ev.preventDefault();
                }, styles: {
                    root: {
                        paddingTop: i > 0 ? _this.hostConfig.spacing.default : 0,
                    },
                } });
        }))); };
        _this.defaultValueToArray = function (value) {
            if (value) {
                return value.split(",");
            }
            return [];
        };
        _this.inputChoicesToComboBoxOptions = function (choices) {
            return choices.map(function (c) { return ({ key: c.value, text: c.title }); });
        };
        _this.inputChoicesToChoiceGroupOptions = function (choices, value) {
            return choices.map(function (c) { return ({ key: c.value, text: c.title, checked: value.includes(c.value) }); });
        };
        _this.handleChoiceGroupChange = function (ev, option) {
            _this.value = option.key;
            ev.stopPropagation();
            ev.preventDefault();
        };
        _this.handleComboBoxChange = function (event, option, index, value) {
            if (_this.isMultiSelect) {
                _this.updateMultiselectData(option.selected, option.key);
            }
            else {
                _this.value = "" + option.key;
            }
            event.stopPropagation();
            event.preventDefault();
        };
        _this.updateMultiselectData = function (selected, key) {
            _this.updateSelectedValues(selected, key);
            _this.value = _this.selectedValues.join(",");
        };
        _this.updateSelectedValues = function (selected, key) {
            selected ? _this.selectedValues.push(key) : _this.removeItemFromArray(_this.selectedValues, key);
        };
        _this.removeItemFromArray = function (arr, item) {
            var index = arr.indexOf(item);
            arr.splice(index, 1);
        };
        return _this;
    }
    return InputChoiceSetFabric;
}(Shared.ReactInputElement));
exports.InputChoiceSetFabric = InputChoiceSetFabric;


/***/ }),

/***/ "./src/components/inputs/InputDateFabric.tsx":
/*!***************************************************!*\
  !*** ./src/components/inputs/InputDateFabric.tsx ***!
  \***************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var React = __webpack_require__(/*! react */ "react");
var FabricUI = __webpack_require__(/*! office-ui-fabric-react */ "office-ui-fabric-react");
var AC = __webpack_require__(/*! adaptivecards */ "adaptivecards");
var Shared = __webpack_require__(/*! ../../utils/shared */ "./src/utils/shared.tsx");
var InputDateFabric = /** @class */ (function (_super) {
    __extends(InputDateFabric, _super);
    function InputDateFabric() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.renderReact = function () {
            return _this.buildDatePicker();
        };
        _this.getJsonTypeName = function () { return "Input.Date"; };
        _this.parse = function (json, errors) {
            _super.prototype.parse.call(_this, json, errors);
            _this.placeholder = AC.getStringValue(json.placeholder);
            _this.parseDates(json, errors);
        };
        _this.toJSON = function () {
            var result = _super.prototype.toJSON.call(_this);
            AC.setProperty(result, "min", _this.minDate);
            AC.setProperty(result, "max", _this.maxDate);
            AC.setProperty(result, "placeholder", _this.placeholder);
            return result;
        };
        _this.parseDates = function (json, errors) {
            _this.value = _this.defaultValue;
            _this.date = _this.value ? _this.getDate(_this.value) : new Date();
            _this.minDate = json.min ? _this.getDate(AC.getStringValue(json.min)) : undefined;
            _this.maxDate = json.max ? _this.getDate(AC.getStringValue(json.max)) : undefined;
        };
        _this.getDate = function (dateString, errors) {
            try {
                return new Date(dateString);
            }
            catch (error) {
                Shared.raiseParseError({
                    error: AC.ValidationError.InvalidPropertyValue,
                    message: error,
                }, errors);
                return undefined;
            }
        };
        _this.buildDatePicker = function () {
            return (React.createElement(FabricUI.DatePicker, { id: _this.id, onSelectDate: _this.handleSelectDate, value: _this.date, placeholder: _this.placeholder, allowTextInput: true, minDate: _this.minDate, maxDate: _this.maxDate }));
        };
        _this.handleSelectDate = function (date) {
            _this.value = date.toLocaleDateString("en-US");
        };
        return _this;
    }
    return InputDateFabric;
}(Shared.ReactInputElement));
exports.InputDateFabric = InputDateFabric;


/***/ }),

/***/ "./src/components/inputs/InputNumberFabric.tsx":
/*!*****************************************************!*\
  !*** ./src/components/inputs/InputNumberFabric.tsx ***!
  \*****************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var React = __webpack_require__(/*! react */ "react");
var AC = __webpack_require__(/*! adaptivecards */ "adaptivecards");
var FabricUI = __webpack_require__(/*! office-ui-fabric-react */ "office-ui-fabric-react");
var Shared = __webpack_require__(/*! ../../utils/shared */ "./src/utils/shared.tsx");
var InputNumberFabric = /** @class */ (function (_super) {
    __extends(InputNumberFabric, _super);
    function InputNumberFabric() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.parse = function (json, errors) {
            _super.prototype.parse.call(_this, json, errors);
            _this.value = _this.defaultValue;
            _this.min = Shared.getIntValue(json.min);
            _this.max = Shared.getIntValue(json.max);
            _this.placeholder = AC.getStringValue(json.placeholder);
        };
        _this.renderReact = function () { return (React.createElement(FabricUI.TextField, { id: _this.id, placeholder: "" + _this.placeholder, value: "" + _this.defaultValue, type: "number", max: _this.max, min: _this.min, onChange: _this.handleChange })); };
        _this.getJsonTypeName = function () { return "Input.Number"; };
        _this.toJSON = function () {
            var result = _super.prototype.toJSON.call(_this);
            AC.setProperty(result, "placeholder", _this.placeholder);
            AC.setProperty(result, "min", _this.min);
            AC.setProperty(result, "max", _this.max);
            return result;
        };
        return _this;
    }
    return InputNumberFabric;
}(Shared.ReactInputElement));
exports.InputNumberFabric = InputNumberFabric;


/***/ }),

/***/ "./src/components/inputs/InputTextFabric.tsx":
/*!***************************************************!*\
  !*** ./src/components/inputs/InputTextFabric.tsx ***!
  \***************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var React = __webpack_require__(/*! react */ "react");
var office_ui_fabric_react_1 = __webpack_require__(/*! office-ui-fabric-react */ "office-ui-fabric-react");
var AC = __webpack_require__(/*! adaptivecards */ "adaptivecards");
var Shared = __webpack_require__(/*! ../../utils/shared */ "./src/utils/shared.tsx");
var InputTextFabric = /** @class */ (function (_super) {
    __extends(InputTextFabric, _super);
    function InputTextFabric() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.style = AC.InputTextStyle.Text;
        _this.renderReact = function () {
            return _this.buildInput();
        };
        _this.getJsonTypeName = function () { return "Input.Text"; };
        _this.parse = function (json, errors) {
            _super.prototype.parse.call(_this, json, errors);
            _this.value = _this.defaultValue;
            _this.isMultiline = AC.getBoolValue(json.isMultiline, false);
            _this.maxLength = Shared.getIntValue(json.maxLength);
            _this.placeholder = AC.getStringValue(json.placeholder);
            _this.label = AC.getStringValue(json.label);
            _this.style = AC.getEnumValue(AC.InputTextStyle, json.style, AC.InputTextStyle.Text);
            _this.inlineAction = AC.createActionInstance(_this, json.inlineAction, [AC.ShowCardAction.JsonTypeName], false, errors);
        };
        _this.toJSON = function () {
            var result = _super.prototype.toJSON.call(_this);
            AC.setProperty(result, "placeholder", _this.placeholder);
            AC.setProperty(result, "maxLength", _this.maxLength, 0);
            AC.setProperty(result, "isMultiline", _this.isMultiline, false);
            AC.setEnumProperty(AC.InputTextStyle, result, "style", _this.style, AC.InputTextStyle.Text);
            if (_this.inlineAction) {
                AC.setProperty(result, "inlineAction", _this.inlineAction.toJSON());
            }
            return result;
        };
        _this.buildInput = function () {
            return (React.createElement(office_ui_fabric_react_1.TextField, { id: _this.id, type: AC.InputTextStyle[_this.style].toLowerCase(), value: _this.defaultValue, multiline: _this.isMultiline, maxLength: _this.maxLength, placeholder: _this.placeholder, label: _this.label, onChange: _this.handleChange, onKeyDown: _this.handleKeyDown }));
        };
        _this.handleKeyDown = function (e) {
            // Enter pressed
            if (e.keyCode === 13 && _this.inlineAction) {
                _this.inlineAction.execute();
            }
        };
        return _this;
    }
    return InputTextFabric;
}(Shared.ReactInputElement));
exports.InputTextFabric = InputTextFabric;


/***/ }),

/***/ "./src/components/inputs/InputTimeFabric.tsx":
/*!***************************************************!*\
  !*** ./src/components/inputs/InputTimeFabric.tsx ***!
  \***************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var React = __webpack_require__(/*! react */ "react");
var AC = __webpack_require__(/*! adaptivecards */ "adaptivecards");
var FabricUI = __webpack_require__(/*! office-ui-fabric-react */ "office-ui-fabric-react");
var Shared = __webpack_require__(/*! ../../utils/shared */ "./src/utils/shared.tsx");
var InputTimeFabric = /** @class */ (function (_super) {
    __extends(InputTimeFabric, _super);
    function InputTimeFabric() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.parse = function (json, errors) {
            _super.prototype.parse.call(_this, json, errors);
            _this.value = _this.defaultValue;
            _this.placeholder = AC.getStringValue(json.placeholder);
            _this.min = AC.getStringValue(json.min);
            _this.max = AC.getStringValue(json.max);
        };
        _this.renderReact = function () {
            return (React.createElement(FabricUI.TextField, { id: _this.id, placeholder: "" + _this.placeholder, value: "" + _this.defaultValue, type: "time", onChange: _this.handleChange, max: _this.max, min: _this.min }));
        };
        _this.getJsonTypeName = function () { return "Input.Time"; };
        _this.toJSON = function () {
            var result = _super.prototype.toJSON.call(_this);
            AC.setProperty(result, "min", _this.min);
            AC.setProperty(result, "max", _this.max);
            return result;
        };
        return _this;
    }
    return InputTimeFabric;
}(Shared.ReactInputElement));
exports.InputTimeFabric = InputTimeFabric;


/***/ }),

/***/ "./src/components/inputs/InputToggleFabric.tsx":
/*!*****************************************************!*\
  !*** ./src/components/inputs/InputToggleFabric.tsx ***!
  \*****************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var React = __webpack_require__(/*! react */ "react");
var AC = __webpack_require__(/*! adaptivecards */ "adaptivecards");
var FabricUI = __webpack_require__(/*! office-ui-fabric-react */ "office-ui-fabric-react");
var Shared = __webpack_require__(/*! ../../utils/shared */ "./src/utils/shared.tsx");
var InputToggleFabric = /** @class */ (function (_super) {
    __extends(InputToggleFabric, _super);
    function InputToggleFabric() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.parse = function (json, errors) {
            _super.prototype.parse.call(_this, json, errors);
            _this.value = _this.defaultValue;
            _this.valueOn = AC.getStringValue(json.valueOn);
            _this.valueOff = AC.getStringValue(json.valueOff);
            _this.title = AC.getStringValue(json.title);
        };
        _this.renderReact = function () { return (React.createElement(FabricUI.Toggle, { id: _this.id, inlineLabel: true, onChange: _this.handleToggleChange, defaultChecked: _this.defaultValue === _this.valueOn, label: _this.title, styles: {
                root: {
                    marginBottom: 0,
                    marginTop: 0,
                },
            } })); };
        _this.getJsonTypeName = function () { return "Input.Toggle"; };
        _this.toJSON = function () {
            var result = _super.prototype.toJSON.call(_this);
            AC.setProperty(result, "valueOn", _this.valueOn, "true");
            AC.setProperty(result, "valueOff", _this.valueOff, "false");
            return result;
        };
        _this.handleToggleChange = function (event, checked) {
            _this.value = checked ? _this.valueOn : _this.valueOff;
        };
        return _this;
    }
    return InputToggleFabric;
}(Shared.ReactInputElement));
exports.InputToggleFabric = InputToggleFabric;


/***/ }),

/***/ "./src/components/inputs/index.ts":
/*!****************************************!*\
  !*** ./src/components/inputs/index.ts ***!
  \****************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

function __export(m) {
    for (var p in m) if (!exports.hasOwnProperty(p)) exports[p] = m[p];
}
Object.defineProperty(exports, "__esModule", { value: true });
__export(__webpack_require__(/*! ./InputChoiceSetFabric */ "./src/components/inputs/InputChoiceSetFabric.tsx"));
__export(__webpack_require__(/*! ./InputDateFabric */ "./src/components/inputs/InputDateFabric.tsx"));
__export(__webpack_require__(/*! ./InputNumberFabric */ "./src/components/inputs/InputNumberFabric.tsx"));
__export(__webpack_require__(/*! ./InputTextFabric */ "./src/components/inputs/InputTextFabric.tsx"));
__export(__webpack_require__(/*! ./InputTimeFabric */ "./src/components/inputs/InputTimeFabric.tsx"));
__export(__webpack_require__(/*! ./InputToggleFabric */ "./src/components/inputs/InputToggleFabric.tsx"));


/***/ }),

/***/ "./src/index.ts":
/*!**********************!*\
  !*** ./src/index.ts ***!
  \**********************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
function __export(m) {
    for (var p in m) if (!exports.hasOwnProperty(p)) exports[p] = m[p];
}
Object.defineProperty(exports, "__esModule", { value: true });
__export(__webpack_require__(/*! ./components */ "./src/components/index.ts"));
__export(__webpack_require__(/*! ./actions */ "./src/actions/index.ts"));
__export(__webpack_require__(/*! ./utils/shared */ "./src/utils/shared.tsx"));


/***/ }),

/***/ "./src/utils/shared.tsx":
/*!******************************!*\
  !*** ./src/utils/shared.tsx ***!
  \******************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var React = __webpack_require__(/*! react */ "react");
var ReactDOM = __webpack_require__(/*! react-dom */ "react-dom");
var AC = __webpack_require__(/*! adaptivecards */ "adaptivecards");
var office_ui_fabric_react_1 = __webpack_require__(/*! office-ui-fabric-react */ "office-ui-fabric-react");
exports.getDiv = function () { return document.createElement("div"); };
var sharedInternalRender = function (renderReact) {
    var div = exports.getDiv();
    ReactDOM.render(renderReact(), div);
    return div;
};
var ReactCardElement = /** @class */ (function (_super) {
    __extends(ReactCardElement, _super);
    function ReactCardElement() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ReactCardElement.prototype.internalRender = function () {
        return sharedInternalRender(this.renderReact);
    };
    return ReactCardElement;
}(AC.CardElement));
exports.ReactCardElement = ReactCardElement;
var ReactCardElementContainer = /** @class */ (function (_super) {
    __extends(ReactCardElementContainer, _super);
    function ReactCardElementContainer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ReactCardElementContainer.prototype.internalRender = function () {
        return sharedInternalRender(this.renderReact);
    };
    return ReactCardElementContainer;
}(AC.Container));
exports.ReactCardElementContainer = ReactCardElementContainer;
var inlineButtonRootStyle = {
    marginLeft: 8,
};
var ReactInputElement = /** @class */ (function (_super) {
    __extends(ReactInputElement, _super);
    function ReactInputElement() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.handleChange = function (event, newValue) {
            _this._value = newValue;
        };
        _this.buildInlineActionButton = function () {
            return sharedInternalRender(AC.isNullOrEmpty(_this.inlineAction.iconUrl) ?
                _this.buildTextOnlyInlineActionActionButton :
                _this.inlineIconActionButton);
        };
        _this.inlineActionClickHandler = function (e) {
            e.stopPropagation();
            e.preventDefault();
            _this._inlineAction.execute();
        };
        _this.inlineIconActionButton = function () { return (React.createElement(office_ui_fabric_react_1.IconButton, { default: true, text: _this._inlineAction.title, className: _this.hostConfig.makeCssClassName("ac-inlineActionButton", "iconOnly"), styles: {
                icon: {
                    height: "100%",
                },
                root: inlineButtonRootStyle,
            }, iconProps: {
                iconType: office_ui_fabric_react_1.IconType.image,
                imageProps: {
                    height: "100%",
                    src: _this._inlineAction.iconUrl,
                },
            }, onClick: _this.inlineActionClickHandler })); };
        _this.buildTextOnlyInlineActionActionButton = function () { return (React.createElement(office_ui_fabric_react_1.PrimaryButton, { className: _this.hostConfig.makeCssClassName("ac-inlineActionButton", "textOnly"), text: _this._inlineAction.title, onClick: _this.inlineActionClickHandler, styles: {
                root: inlineButtonRootStyle,
            } })); };
        return _this;
    }
    ReactInputElement.prototype.internalRender = function () {
        var element = sharedInternalRender(this.renderReact);
        element.style.width = "100%";
        return element;
    };
    ReactInputElement.prototype.overrideInternalRender = function () {
        var inputControl = _super.prototype.overrideInternalRender.call(this);
        if (this._inlineAction) {
            this.inputControlContainerElement.appendChild(this.buildInlineActionButton());
        }
        return inputControl;
    };
    Object.defineProperty(ReactInputElement.prototype, "value", {
        get: function () {
            return this._value;
        },
        set: function (value) {
            this._value = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ReactInputElement.prototype, "inlineAction", {
        get: function () {
            return this._inlineAction;
        },
        set: function (action) {
            this._inlineAction = action;
            if (this._inlineAction) {
                this._inlineAction.setParent(this);
            }
        },
        enumerable: true,
        configurable: true
    });
    return ReactInputElement;
}(AC.Input));
exports.ReactInputElement = ReactInputElement;
exports.raiseParseError = function (error, errors) {
    if (errors) {
        errors.push(error);
    }
    if (AC.AdaptiveCard.onParseError != null) {
        AC.AdaptiveCard.onParseError(error);
    }
};
exports.getIntValue = function (val, errors, defaultValue) {
    if (defaultValue === void 0) { defaultValue = undefined; }
    try {
        return val ? parseInt(val, 10) : defaultValue;
    }
    catch (error) {
        exports.raiseParseError({
            error: AC.ValidationError.InvalidPropertyValue,
            message: error,
        }, errors);
    }
};


/***/ }),

/***/ "adaptivecards":
/*!********************************!*\
  !*** external "AdaptiveCards" ***!
  \********************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = AdaptiveCards;

/***/ }),

/***/ "office-ui-fabric-react":
/*!*************************!*\
  !*** external "fabric" ***!
  \*************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = fabric;

/***/ }),

/***/ "react":
/*!************************!*\
  !*** external "React" ***!
  \************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = React;

/***/ }),

/***/ "react-dom":
/*!***************************!*\
  !*** external "ReactDOM" ***!
  \***************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = ReactDOM;

/***/ })

/******/ });
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly9BQ0ZhYnJpYy93ZWJwYWNrL2Jvb3RzdHJhcCIsIndlYnBhY2s6Ly9BQ0ZhYnJpYy8uL3NyYy9hY3Rpb25zL0FjdGlvbkJ1dHRvbi50c3giLCJ3ZWJwYWNrOi8vQUNGYWJyaWMvLi9zcmMvYWN0aW9ucy9BY3Rpb25zLnRzeCIsIndlYnBhY2s6Ly9BQ0ZhYnJpYy8uL3NyYy9hY3Rpb25zL2luZGV4LnRzIiwid2VicGFjazovL0FDRmFicmljLy4vc3JjL2NvbXBvbmVudHMvRmFicmljLnRzeCIsIndlYnBhY2s6Ly9BQ0ZhYnJpYy8uL3NyYy9jb21wb25lbnRzL2luZGV4LnRzIiwid2VicGFjazovL0FDRmFicmljLy4vc3JjL2NvbXBvbmVudHMvaW5wdXRzL0lucHV0Q2hvaWNlU2V0RmFicmljLnRzeCIsIndlYnBhY2s6Ly9BQ0ZhYnJpYy8uL3NyYy9jb21wb25lbnRzL2lucHV0cy9JbnB1dERhdGVGYWJyaWMudHN4Iiwid2VicGFjazovL0FDRmFicmljLy4vc3JjL2NvbXBvbmVudHMvaW5wdXRzL0lucHV0TnVtYmVyRmFicmljLnRzeCIsIndlYnBhY2s6Ly9BQ0ZhYnJpYy8uL3NyYy9jb21wb25lbnRzL2lucHV0cy9JbnB1dFRleHRGYWJyaWMudHN4Iiwid2VicGFjazovL0FDRmFicmljLy4vc3JjL2NvbXBvbmVudHMvaW5wdXRzL0lucHV0VGltZUZhYnJpYy50c3giLCJ3ZWJwYWNrOi8vQUNGYWJyaWMvLi9zcmMvY29tcG9uZW50cy9pbnB1dHMvSW5wdXRUb2dnbGVGYWJyaWMudHN4Iiwid2VicGFjazovL0FDRmFicmljLy4vc3JjL2NvbXBvbmVudHMvaW5wdXRzL2luZGV4LnRzIiwid2VicGFjazovL0FDRmFicmljLy4vc3JjL2luZGV4LnRzIiwid2VicGFjazovL0FDRmFicmljLy4vc3JjL3V0aWxzL3NoYXJlZC50c3giLCJ3ZWJwYWNrOi8vQUNGYWJyaWMvZXh0ZXJuYWwgXCJBZGFwdGl2ZUNhcmRzXCIiLCJ3ZWJwYWNrOi8vQUNGYWJyaWMvZXh0ZXJuYWwgXCJmYWJyaWNcIiIsIndlYnBhY2s6Ly9BQ0ZhYnJpYy9leHRlcm5hbCBcIlJlYWN0XCIiLCJ3ZWJwYWNrOi8vQUNGYWJyaWMvZXh0ZXJuYWwgXCJSZWFjdERPTVwiIl0sIm5hbWVzIjpbXSwibWFwcGluZ3MiOiI7O0FBQUE7QUFDQTs7QUFFQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7OztBQUdBO0FBQ0E7O0FBRUE7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQSxrREFBMEMsZ0NBQWdDO0FBQzFFO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0EsZ0VBQXdELGtCQUFrQjtBQUMxRTtBQUNBLHlEQUFpRCxjQUFjO0FBQy9EOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxpREFBeUMsaUNBQWlDO0FBQzFFLHdIQUFnSCxtQkFBbUIsRUFBRTtBQUNySTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBLG1DQUEyQiwwQkFBMEIsRUFBRTtBQUN2RCx5Q0FBaUMsZUFBZTtBQUNoRDtBQUNBO0FBQ0E7O0FBRUE7QUFDQSw4REFBc0QsK0RBQStEOztBQUVySDtBQUNBOzs7QUFHQTtBQUNBOzs7Ozs7Ozs7Ozs7OztBQ2xGQSw0REFBNEQ7QUFDNUQsa0NBQWtDOztBQUVsQyxzREFBK0I7QUFDL0IsMkdBQXVFO0FBQ3ZFLG1FQUFvQztBQVV2QixvQkFBWSxHQUFHLFVBQUMsS0FBd0IsSUFBSyxRQUN0RCxLQUFLLENBQUMsT0FBTyxDQUFDLENBQUM7SUFDWCxvQkFBQyx1Q0FBYyxJQUFDLFNBQVMsRUFBRSxLQUFLLENBQUMsU0FBUztRQUN0Qyw2QkFBSyxLQUFLLEVBQ047Z0JBQ0ksT0FBTyxFQUFFLE1BQU07Z0JBQ2YsYUFBYSxFQUFFLEtBQUssQ0FBQyxhQUFhLEtBQUssRUFBRSxDQUFDLG1CQUFtQixDQUFD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Q0FBQztLQUNqRDtJQUFDLE9BQU8sS0FBSyxFQUFFO1FBQ1osdUJBQWUsQ0FBQztZQUNaLEtBQUssRUFBRSxFQUFFLENBQUMsZUFBZSxDQUFDLG9CQUFvQjtZQUM5QyxPQUFPLEVBQUUsS0FBSztTQUNqQixFQUFFLE1BQU0sQ0FBQyxDQUFDO0tBQ2Q7QUFDTCxDQUFDLENBQUM7Ozs7Ozs7Ozs7OztBQ3JKRiwrQjs7Ozs7Ozs7Ozs7QUNBQSx3Qjs7Ozs7Ozs7Ozs7QUNBQSx1Qjs7Ozs7Ozs7Ozs7QUNBQSwwQiIsImZpbGUiOiJhZGFwdGl2ZWNhcmRzLWZhYnJpYy5qcyIsInNvdXJjZXNDb250ZW50IjpbIiBcdC8vIFRoZSBtb2R1bGUgY2FjaGVcbiBcdHZhciBpbnN0YWxsZWRNb2R1bGVzID0ge307XG5cbiBcdC8vIFRoZSByZXF1aXJlIGZ1bmN0aW9uXG4gXHRmdW5jdGlvbiBfX3dlYnBhY2tfcmVxdWlyZV9fKG1vZHVsZUlkKSB7XG5cbiBcdFx0Ly8gQ2hlY2sgaWYgbW9kdWxlIGlzIGluIGNhY2hlXG4gXHRcdGlmKGluc3RhbGxlZE1vZHVsZXNbbW9kdWxlSWRdKSB7XG4gXHRcdFx0cmV0dXJuIGluc3RhbGxlZE1vZHVsZXNbbW9kdWxlSWRdLmV4cG9ydHM7XG4gXHRcdH1cbiBcdFx0Ly8gQ3JlYXRlIGEgbmV3IG1vZHVsZSAoYW5kIHB1dCBpdCBpbnRvIHRoZSBjYWNoZSlcbiBcdFx0dmFyIG1vZHVsZSA9IGluc3RhbGxlZE1vZHVsZXNbbW9kdWxlSWRdID0ge1xuIFx0XHRcdGk6IG1vZHVsZUlkLFxuIFx0XHRcdGw6IGZhbHNlLFxuIFx0XHRcdGV4cG9ydHM6IHt9XG4gXHRcdH07XG5cbiBcdFx0Ly8gRXhlY3V0ZSB0aGUgbW9kdWxlIGZ1bmN0aW9uXG4gXHRcdG1vZHVsZXNbbW9kdWxlSWRdLmNhbGwobW9kdWxlLmV4cG9ydHMsIG1vZHVsZSwgbW9kdWxlLmV4cG9ydHMsIF9fd2VicGFja19yZXF1aXJlX18pO1xuXG4gXHRcdC8vIEZsYWcgdGhlIG1vZHVsZSBhcyBsb2FkZWRcbiBcdFx0bW9kdWxlLmwgPSB0cnVlO1xuXG4gXHRcdC8vIFJldHVybiB0aGUgZXhwb3J0cyBvZiB0aGUgbW9kdWxlXG4gXHRcdHJldHVybiBtb2R1bGUuZXhwb3J0cztcbiBcdH1cblxuXG4gXHQvLyBleHBvc2UgdGhlIG1vZHVsZXMgb2JqZWN0IChfX3dlYnBhY2tfbW9kdWxlc19fKVxuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5tID0gbW9kdWxlcztcblxuIFx0Ly8gZXhwb3NlIHRoZSBtb2R1bGUgY2FjaGVcbiBcdF9fd2VicGFja19yZXF1aXJlX18uYyA9IGluc3RhbGxlZE1vZHVsZXM7XG5cbiBcdC8vIGRlZmluZSBnZXR0ZXIgZnVuY3Rpb24gZm9yIGhhcm1vbnkgZXhwb3J0c1xuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5kID0gZnVuY3Rpb24oZXhwb3J0cywgbmFtZSwgZ2V0dGVyKSB7XG4gXHRcdGlmKCFfX3dlYnBhY2tfcmVxdWlyZV9fLm8oZXhwb3J0cywgbmFtZSkpIHtcbiBcdFx0XHRPYmplY3QuZGVmaW5lUHJvcGVydHkoZXhwb3J0cywgbmFtZSwgeyBlbnVtZXJhYmxlOiB0cnVlLCBnZXQ6IGdldHRlciB9KTtcbiBcdFx0fVxuIFx0fTtcblxuIFx0Ly8gZGVmaW5lIF9fZXNNb2R1bGUgb24gZXhwb3J0c1xuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5yID0gZnVuY3Rpb24oZXhwb3J0cykge1xuIFx0XHRpZih0eXBlb2YgU3ltYm9sICE9PSAndW5kZWZpbmVkJyAmJiBTeW1ib2wudG9TdHJpbmdUYWcpIHtcbiBcdFx0XHRPYmplY3QuZGVmaW5lUHJvcGVydHkoZXhwb3J0cywgU3ltYm9sLnRvU3RyaW5nVGFnLCB7IHZhbHVlOiAnTW9kdWxlJyB9KTtcbiBcdFx0fVxuIFx0XHRPYmplY3QuZGVmaW5lUHJvcGVydHkoZXhwb3J0cywgJ19fZXNNb2R1bGUnLCB7IHZhbHVlOiB0cnVlIH0pO1xuIFx0fTtcblxuIFx0Ly8gY3JlYXRlIGEgZmFrZSBuYW1lc3BhY2Ugb2JqZWN0XG4gXHQvLyBtb2RlICYgMTogdmFsdWUgaXMgYSBtb2R1bGUgaWQsIHJlcXVpcmUgaXRcbiBcdC8vIG1vZGUgJiAyOiBtZXJnZSBhbGwgcHJvcGVydGllcyBvZiB2YWx1ZSBpbnRvIHRoZSBuc1xuIFx0Ly8gbW9kZSAmIDQ6IHJldHVybiB2YWx1ZSB3aGVuIGFscmVhZHkgbnMgb2JqZWN0XG4gXHQvLyBtb2RlICYgOHwxOiBiZWhhdmUgbGlrZSByZXF1aXJlXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLnQgPSBmdW5jdGlvbih2YWx1ZSwgbW9kZSkge1xuIFx0XHRpZihtb2RlICYgMSkgdmFsdWUgPSBfX3dlYnBhY2tfcmVxdWlyZV9fKHZhbHVlKTtcbiBcdFx0aWYobW9kZSAmIDgpIHJldHVybiB2YWx1ZTtcbiBcdFx0aWYoKG1vZGUgJiA0KSAmJiB0eXBlb2YgdmFsdWUgPT09ICdvYmplY3QnICYmIHZhbHVlICYmIHZhbHVlLl9fZXNNb2R1bGUpIHJldHVybiB2YWx1ZTtcbiBcdFx0dmFyIG5zID0gT2JqZWN0LmNyZWF0ZShudWxsKTtcbiBcdFx0X193ZWJwYWNrX3JlcXVpcmVfXy5yKG5zKTtcbiBcdFx0T2JqZWN0LmRlZmluZVByb3BlcnR5KG5zLCAnZGVmYXVsdCcsIHsgZW51bWVyYWJsZTogdHJ1ZSwgdmFsdWU6IHZhbHVlIH0pO1xuIFx0XHRpZihtb2RlICYgMiAmJiB0eXBlb2YgdmFsdWUgIT0gJ3N0cmluZycpIGZvcih2YXIga2V5IGluIHZhbHVlKSBfX3dlYnBhY2tfcmVxdWlyZV9fLmQobnMsIGtleSwgZnVuY3Rpb24oa2V5KSB7IHJldHVybiB2YWx1ZVtrZXldOyB9LmJpbmQobnVsbCwga2V5KSk7XG4gXHRcdHJldHVybiBucztcbiBcdH07XG5cbiBcdC8vIGdldERlZmF1bHRFeHBvcnQgZnVuY3Rpb24gZm9yIGNvbXBhdGliaWxpdHkgd2l0aCBub24taGFybW9ueSBtb2R1bGVzXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLm4gPSBmdW5jdGlvbihtb2R1bGUpIHtcbiBcdFx0dmFyIGdldHRlciA9IG1vZHVsZSAmJiBtb2R1bGUuX19lc01vZHVsZSA/XG4gXHRcdFx0ZnVuY3Rpb24gZ2V0RGVmYXVsdCgpIHsgcmV0dXJuIG1vZHVsZVsnZGVmYXVsdCddOyB9IDpcbiBcdFx0XHRmdW5jdGlvbiBnZXRNb2R1bGVFeHBvcnRzKCkgeyByZXR1cm4gbW9kdWxlOyB9O1xuIFx0XHRfX3dlYnBhY2tfcmVxdWlyZV9fLmQoZ2V0dGVyLCAnYScsIGdldHRlcik7XG4gXHRcdHJldHVybiBnZXR0ZXI7XG4gXHR9O1xuXG4gXHQvLyBPYmplY3QucHJvdG90eXBlLmhhc093blByb3BlcnR5LmNhbGxcbiBcdF9fd2VicGFja19yZXF1aXJlX18ubyA9IGZ1bmN0aW9uKG9iamVjdCwgcHJvcGVydHkpIHsgcmV0dXJuIE9iamVjdC5wcm90b3R5cGUuaGFzT3duUHJvcGVydHkuY2FsbChvYmplY3QsIHByb3BlcnR5KTsgfTtcblxuIFx0Ly8gX193ZWJwYWNrX3B1YmxpY19wYXRoX19cbiBcdF9fd2VicGFja19yZXF1aXJlX18ucCA9IFwiXCI7XG5cblxuIFx0Ly8gTG9hZCBlbnRyeSBtb2R1bGUgYW5kIHJldHVybiBleHBvcnRzXG4gXHRyZXR1cm4gX193ZWJwYWNrX3JlcXVpcmVfXyhfX3dlYnBhY2tfcmVxdWlyZV9fLnMgPSBcIi4vc3JjL2luZGV4LnRzXCIpO1xuIiwiLy8gQ29weXJpZ2h0IChjKSBNaWNyb3NvZnQgQ29ycG9yYXRpb24uIEFsbCByaWdodHMgcmVzZXJ2ZWQuXHJcbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBNSVQgTGljZW5zZS5cclxuXHJcbmltcG9ydCAqIGFzIFJlYWN0IGZyb20gXCJyZWFjdFwiO1xyXG5pbXBvcnQgeyBQcmltYXJ5QnV0dG9uLCBDb21wb3VuZEJ1dHRvbiB9IGZyb20gXCJvZmZpY2UtdWktZmFicmljLXJlYWN0XCI7XHJcbmltcG9ydCAqIGFzIEFDIGZyb20gXCJhZGFwdGl2ZWNhcmRzXCI7XHJcblxyXG5leHBvcnQgaW50ZXJmYWNlIEFjdGlvbkJ1dHRvblByb3BzIHtcclxuICAgIHRleHQ6IHN0cmluZztcclxuICAgIGNsYXNzTmFtZT86IHN0cmluZztcclxuICAgIGljb25Vcmw/OiBzdHJpbmc7XHJcbiAgICBpY29uUGxhY2VtZW50PzogQUMuQWN0aW9uSWNvblBsYWNlbWVudDtcclxuICAgIGljb25TaXplPzogbnVtYmVyO1xyXG59XHJcblxyXG5leHBvcnQgY29uc3QgQWN0aW9uQnV0dG9uID0gKHByb3BzOiBBY3Rpb25CdXR0b25Qcm9wcykgPT4gKFxyXG4gICAgcHJvcHMuaWNvblVybCA/XHJcbiAgICAgICAgPENvbXBvdW5kQnV0dG9uIGNsYXNzTmFtZT17cHJvcHMuY2xhc3NOYW1lfSA+XHJcbiAgICAgICAgICAgIDxkaXYgc3R5bGU9e1xyXG4gICAgICAgICAgICAgICAge1xyXG4gICAgICAgICAgICAgICAgICAgIGRpc3BsYXk6IFwiZmxleFwiLFxyXG4gICAgICAgICAgICAgICAgICAgIGZsZXhEaXJlY3Rpb246IHByb3BzLmljb25QbGFjZW1lbnQgPT09IEFDLkFjdGlvbkljb25QbGFjZW1lbnQuTGVmdE9mVGl0bGUgPyBcInJvd1wiIDogXCJjb2x1bW5cIixcclxuICAgICAgICAgICAgICAgICAgICBqdXN0aWZ5Q29udGVudDogXCJjZW50ZXJcIixcclxuICAgICAgICAgICAgICAgIH1cclxuICAgICAgICAgICAgfT48aW1nIHNyYz17cHJvcHMuaWNvblVybH1cclxuICAgICAgICAgICAgICAgIHN0eWxlPXtcclxuICAgICAgICAgICAgICAgICAgICB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIGFsaWduU2VsZjogXCJjZW50ZXJcIixcclxuICAgICAgICAgICAgICAgICAgICAgICAgd2lkdGg6IHByb3BzLmljb25TaXplLFxyXG4gICAgICAgICAgICAgICAgICAgICAgICBoZWlnaHQ6IHByb3BzLmljb25TaXplLFxyXG4gICAgICAgICAgICAgICAgICAgICAgICBmbGV4OiBcIjAgMCBhdXRvXCIsXHJcbiAgICAgICAgICAgICAgICAgICAgfVxyXG4gICAgICAgICAgICAgICAgfSAvPlxyXG4gICAgICAgICAgICAgICAgPHNwYW4gc3R5bGU9e3sgYWxpZ25TZWxmOiBcImNlbnRlclwiIH19Pntwcm9wcy50ZXh0fTwvc3Bhbj5cclxuICAgICAgICAgICAgPC9kaXY+XHJcbiAgICAgICAgPC9Db21wb3VuZEJ1dHRvbj4gOlxyXG4gICAgICAgIDxQcmltYXJ5QnV0dG9uXHJcbiAgICAgICAgICAgIGNsYXNzTmFtZT17cHJvcHMuY2xhc3NOYW1lfVxyXG4gICAgICAgICAgICB0ZXh0PXtwcm9wcy50ZXh0fSAvPlxyXG4pO1xyXG4iLCIvLyBDb3B5cmlnaHQgKGMpIE1pY3Jvc29mdCBDb3Jwb3JhdGlvbi4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cclxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIE1JVCBMaWNlbnNlLlxyXG5cclxuaW1wb3J0ICogYXMgUmVhY3QgZnJvbSBcInJlYWN0XCI7XHJcbmltcG9ydCAqIGFzIFJlYWN0RE9NIGZyb20gXCJyZWFjdC1kb21cIjtcclxuaW1wb3J0ICogYXMgQUMgZnJvbSBcImFkYXB0aXZlY2FyZHNcIjtcclxuaW1wb3J0ICogYXMgU2hhcmVkIGZyb20gXCIuLi91dGlscy9zaGFyZWRcIjtcclxuaW1wb3J0IHsgQWN0aW9uQnV0dG9uIH0gZnJvbSBcIi4vQWN0aW9uQnV0dG9uXCI7XHJcblxyXG5leHBvcnQgY29uc3QgY3JlYXRlQWN0aW9uRGl2ID0gKFxyXG4gICAgdGl0bGU6IHN0cmluZyxcclxuICAgIGljb25Vcmw6IHN0cmluZyxcclxuICAgIGJhc2VDc3NDbGFzczogc3RyaW5nLFxyXG4gICAgaWNvblBsYWNlbWVudDogQUMuQWN0aW9uSWNvblBsYWNlbWVudCxcclxuICAgIGljb25TaXplOiBudW1iZXIpOiBIVE1MRGl2RWxlbWVudCA9PiB7XHJcbiAgICBjb25zdCBkaXYgPSBTaGFyZWQuZ2V0RGl2KCk7XHJcbiAgICBSZWFjdERPTS5yZW5kZXIoXHJcbiAgICAgICAgPEFjdGlvbkJ1dHRvblxyXG4gICAgICAgICAgICB0ZXh0PXt0aXRsZX1cclxuICAgICAgICAgICAgY2xhc3NOYW1lPXtiYXNlQ3NzQ2xhc3N9XHJcbiAgICAgICAgICAgIGljb25Vcmw9e2ljb25Vcmx9XHJcbiAgICAgICAgICAgIGljb25QbGFjZW1lbnQ9e2ljb25QbGFjZW1lbnR9XHJcbiAgICAgICAgICAgIGljb25TaXplPXtpY29uU2l6ZX0+PC9BY3Rpb25CdXR0b24+LCBkaXYpO1xyXG4gICAgcmV0dXJuIGRpdjtcclxufTtcclxuXHJcbmV4cG9ydCBjbGFzcyBPcGVuVXJsQWN0aW9uRmFicmljIGV4dGVuZHMgQUMuT3BlblVybEFjdGlvbiB7XHJcblxyXG4gICAgcHJpdmF0ZSBpbnRlcm5hbFJlbmRlcmVkRWxlbWVudDogYW55O1xyXG5cclxuICAgIGdldCByZW5kZXJlZEVsZW1lbnQoKTogSFRNTEVsZW1lbnQge1xyXG4gICAgICAgIHJldHVybiB0aGlzLmludGVybmFsUmVuZGVyZWRFbGVtZW50O1xyXG4gICAgfVxyXG5cclxuICAgIHB1YmxpYyByZW5kZXIoYmFzZUNzc0NsYXNzPzogc3RyaW5nKSB7XHJcbiAgICAgICAgbGV0IGFjdGlvbnNDb25maWcgPSB0aGlzLnBhcmVudC5ob3N0Q29uZmlnLmFjdGlvbnM7XHJcbiAgICAgICAgY29uc3QgZGl2ID0gY3JlYXRlQWN0aW9uRGl2KHRoaXMudGl0bGUsIHRoaXMuaWNvblVybCwgYmFzZUNzc0NsYXNzLCBhY3Rpb25zQ29uZmlnLmljb25QbGFjZW1lbnQsIGFjdGlvbnNDb25maWcuaWNvblNpemUpO1xyXG4gICAgICAgIHRoaXMuaW50ZXJuYWxSZW5kZXJlZEVsZW1lbnQgPSBkaXY7XHJcbiAgICB9XHJcbn1cclxuXHJcbmV4cG9ydCBjbGFzcyBTdWJtaXRBY3Rpb25GYWJyaWMgZXh0ZW5kcyBBQy5TdWJtaXRBY3Rpb24ge1xyXG5cclxuICAgIHByaXZhdGUgaW50ZXJuYWxSZW5kZXJlZEVsZW1lbnQ6IEhUTUxFbGVtZW50O1xyXG5cclxuICAgIGdldCByZW5kZXJlZEVsZW1lbnQoKTogSFRNTEVsZW1lbnQge1xyXG4gICAgICAgIHJldHVybiB0aGlzLmludGVybmFsUmVuZGVyZWRFbGVtZW50O1xyXG4gICAgfVxyXG5cclxuICAgIHB1YmxpYyByZW5kZXIoYmFzZUNzc0NsYXNzPzogc3RyaW5nKTogdm9pZCB7XHJcbiAgICAgICAgbGV0IGFjdGlvbnNDb25maWcgPSB0aGlzLnBhcmVudC5ob3N0Q29uZmlnLmFjdGlvbnM7XHJcbiAgICAgICAgY29uc3QgZGl2ID0gY3JlYXRlQWN0aW9uRGl2KHRoaXMudGl0bGUsIHRoaXMuaWNvblVybCwgYmFzZUNzc0NsYXNzLCBhY3Rpb25zQ29uZmlnLmljb25QbGFjZW1lbnQsIGFjdGlvbnNDb25maWcuaWNvblNpemUpO1xyXG4gICAgICAgIHRoaXMuaW50ZXJuYWxSZW5kZXJlZEVsZW1lbnQgPSBkaXY7XHJcbiAgICB9XHJcbn1cclxuXHJcbmV4cG9ydCBjbGFzcyBTaG93Q2FyZEFjdGlvbkZhYnJpYyBleHRlbmRzIEFDLlNob3dDYXJkQWN0aW9uIHtcclxuXHJcbiAgICBwcml2YXRlIGludGVybmFsUmVuZGVyZWRFbGVtZW50OiBIVE1MRWxlbWVudDtcclxuXHJcbiAgICBnZXQgcmVuZGVyZWRFbGVtZW50KCk6IEhUTUxFbGVtZW50IHtcclxuICAgICAgICByZXR1cm4gdGhpcy5pbnRlcm5hbFJlbmRlcmVkRWxlbWVudDtcclxuICAgIH1cclxuXHJcbiAgICBwdWJsaWMgcmVuZGVyKGJhc2VDc3NDbGFzcz86IHN0cmluZyk6IHZvaWQge1xyXG4gICAgICAgIGxldCBhY3Rpb25zQ29uZmlnID0gdGhpcy5wYXJlbnQuaG9zdENvbmZpZy5hY3Rpb25zO1xyXG4gICAgICAgIGNvbnN0IGRpdiA9IGNyZWF0ZUFjdGlvbkRpdih0aGlzLnRpdGxlLCB0aGlzLmljb25VcmwsIGJhc2VDc3NDbGFzcywgYWN0aW9uc0NvbmZpZy5pY29uUGxhY2VtZW50LCBhY3Rpb25zQ29uZmlnLmljb25TaXplKTtcclxuICAgICAgICB0aGlzLmludGVybmFsUmVuZGVyZWRFbGVtZW50ID0gZGl2O1xyXG4gICAgfVxyXG59XHJcblxyXG5leHBvcnQgY2xhc3MgVG9nZ2xlVmlzaWJpbGl0eUFjdGlvbkZhYnJpYyBleHRlbmRzIEFDLlRvZ2dsZVZpc2liaWxpdHlBY3Rpb24ge1xyXG5cclxuICAgIHByaXZhdGUgaW50ZXJuYWxSZW5kZXJlZEVsZW1lbnQ6IEhUTUxFbGVtZW50O1xyXG5cclxuICAgIGdldCByZW5kZXJlZEVsZW1lbnQoKTogSFRNTEVsZW1lbnQge1xyXG4gICAgICAgIHJldHVybiB0aGlzLmludGVybmFsUmVuZGVyZWRFbGVtZW50O1xyXG4gICAgfVxyXG5cclxuICAgIHB1YmxpYyByZW5kZXIoYmFzZUNzc0NsYXNzPzogc3RyaW5nKTogdm9pZCB7XHJcbiAgICAgICAgY29uc3QgZGl2ID0gU2hhcmVkLmdldERpdigpO1xyXG4gICAgICAgIFJlYWN0RE9NLnJlbmRlcig8QWN0aW9uQnV0dG9uIHRleHQ9e3RoaXMudGl0bGV9IGNsYXNzTmFtZT17YmFzZUNzc0NsYXNzfSAvPiwgZGl2KTtcclxuICAgICAgICB0aGlzLmludGVybmFsUmVuZGVyZWRFbGVtZW50ID0gZGl2O1xyXG4gICAgfVxyXG59XHJcbiIsImV4cG9ydCAqIGZyb20gXCIuL0FjdGlvbnNcIjtcclxuIiwiLy8gQ29weXJpZ2h0IChjKSBNaWNyb3NvZnQgQ29ycG9yYXRpb24uIEFsbCByaWdodHMgcmVzZXJ2ZWQuXHJcbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBNSVQgTGljZW5zZS5cclxuXHJcbmltcG9ydCAqIGFzIEFDIGZyb20gXCJhZGFwdGl2ZWNhcmRzXCI7XHJcbmltcG9ydCB7IGluaXRpYWxpemVJY29ucyB9IGZyb20gXCJvZmZpY2UtdWktZmFicmljLXJlYWN0XCI7XHJcbmltcG9ydCAqIGFzIENvbXBvbmVudHMgZnJvbSBcIi5cIjtcclxuaW1wb3J0ICogYXMgQWN0aW9ucyBmcm9tIFwiLi4vYWN0aW9uc1wiO1xyXG5cclxubGV0IGljb25zSW5pdGlhbGl6ZWQgPSBmYWxzZTtcclxuXHJcbmV4cG9ydCBjb25zdCB1c2VGYWJyaWNDb21wb25lbnRzID0gKCkgPT4ge1xyXG4gICAgaWYgKCFpY29uc0luaXRpYWxpemVkKSB7XHJcbiAgICAgICAgaW5pdGlhbGl6ZUljb25zKCk7XHJcbiAgICAgICAgaWNvbnNJbml0aWFsaXplZCA9IHRydWU7XHJcbiAgICB9XHJcblxyXG4gICAgLy8gYWRkIGNvbXBvbmVudCBleHRlbnNpb25zXHJcbiAgICBBQy5BZGFwdGl2ZUNhcmQuZWxlbWVudFR5cGVSZWdpc3RyeS5yZWdpc3RlclR5cGUoXCJJbnB1dC5EYXRlXCIsICgpID0+IG5ldyBDb21wb25lbnRzLklucHV0RGF0ZUZhYnJpYygpKTtcclxuICAgIEFDLkFkYXB0aXZlQ2FyZC5lbGVtZW50VHlwZVJlZ2lzdHJ5LnJlZ2lzdGVyVHlwZShcIklucHV0LlRleHRcIiwgKCkgPT4gbmV3IENvbXBvbmVudHMuSW5wdXRUZXh0RmFicmljKCkpO1xyXG4gICAgQUMuQWRhcHRpdmVDYXJkLmVsZW1lbnRUeXBlUmVnaXN0cnkucmVnaXN0ZXJUeXBlKFwiSW5wdXQuVGltZVwiLCAoKSA9PiBuZXcgQ29tcG9uZW50cy5JbnB1dFRpbWVGYWJyaWMoKSk7XHJcbiAgICBBQy5BZGFwdGl2ZUNhcmQuZWxlbWVudFR5cGVSZWdpc3RyeS5yZWdpc3RlclR5cGUoXCJJbnB1dC5OdW1iZXJcIiwgKCkgPT4gbmV3IENvbXBvbmVudHMuSW5wdXROdW1iZXJGYWJyaWMoKSk7XHJcbiAgICBBQy5BZGFwdGl2ZUNhcmQuZWxlbWVudFR5cGVSZWdpc3RyeS5yZWdpc3RlclR5cGUoXCJJbnB1dC5Ub2dnbGVcIiwgKCkgPT4gbmV3IENvbXBvbmVudHMuSW5wdXRUb2dnbGVGYWJyaWMoKSk7XHJcbiAgICBBQy5BZGFwdGl2ZUNhcmQuZWxlbWVudFR5cGVSZWdpc3RyeS5yZWdpc3RlclR5cGUoXCJJbnB1dC5DaG9pY2VTZXRcIiwgKCkgPT4gbmV3IENvbXBvbmVudHMuSW5wdXRDaG9pY2VTZXRGYWJyaWMoKSk7XHJcblxyXG4gICAgLy8gYWRkIGFjdGlvbnMgZXh0ZW5zaW9uc1xyXG4gICAgQUMuQWRhcHRpdmVDYXJkLmFjdGlvblR5cGVSZWdpc3RyeS5yZWdpc3RlclR5cGUoXCJBY3Rpb24uT3BlblVybFwiLCAoKSA9PiBuZXcgQWN0aW9ucy5PcGVuVXJsQWN0aW9uRmFicmljKCkpO1xyXG4gICAgQUMuQWRhcHRpdmVDYXJkLmFjdGlvblR5cGVSZWdpc3RyeS5yZWdpc3RlclR5cGUoXCJBY3Rpb24uU3VibWl0XCIsICgpID0+IG5ldyBBY3Rpb25zLlN1Ym1pdEFjdGlvbkZhYnJpYygpKTtcclxuICAgIEFDLkFkYXB0aXZlQ2FyZC5hY3Rpb25UeXBlUmVnaXN0cnkucmVnaXN0ZXJUeXBlKFwiQWN0aW9uLlNob3dDYXJkXCIsICgpID0+IG5ldyBBY3Rpb25zLlNob3dDYXJkQWN0aW9uRmFicmljKCkpO1xyXG4gICAgQUMuQWRhcHRpdmVDYXJkLmFjdGlvblR5cGVSZWdpc3RyeS5yZWdpc3RlclR5cGUoXCJBY3Rpb24uVG9nZ2xlVmlzaWJpbGl0eVwiLCAoKSA9PiBuZXcgQWN0aW9ucy5Ub2dnbGVWaXNpYmlsaXR5QWN0aW9uRmFicmljKCkpO1xyXG59O1xyXG4iLCIvLyBDb3B5cmlnaHQgKGMpIE1pY3Jvc29mdCBDb3Jwb3JhdGlvbi4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cclxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIE1JVCBMaWNlbnNlLlxyXG5cclxuZXhwb3J0ICogZnJvbSBcIi4vaW5wdXRzXCI7XHJcbmV4cG9ydCAqIGZyb20gXCIuL0ZhYnJpY1wiO1xyXG4iLCIvLyBDb3B5cmlnaHQgKGMpIE1pY3Jvc29mdCBDb3Jwb3JhdGlvbi4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cclxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIE1JVCBMaWNlbnNlLlxyXG5cclxuaW1wb3J0ICogYXMgUmVhY3QgZnJvbSBcInJlYWN0XCI7XHJcbmltcG9ydCAqIGFzIEFDIGZyb20gXCJhZGFwdGl2ZWNhcmRzXCI7XHJcbmltcG9ydCAqIGFzIEZhYnJpY1VJIGZyb20gXCJvZmZpY2UtdWktZmFicmljLXJlYWN0XCI7XHJcbmltcG9ydCAqIGFzIFNoYXJlZCBmcm9tIFwiLi4vLi4vdXRpbHMvc2hhcmVkXCI7XHJcblxyXG5leHBvcnQgY2xhc3MgSW5wdXRDaG9pY2VTZXRGYWJyaWMgZXh0ZW5kcyBTaGFyZWQuUmVhY3RJbnB1dEVsZW1lbnQge1xyXG5cclxuICAgIHByaXZhdGUgaXNNdWx0aVNlbGVjdDogYm9vbGVhbjtcclxuICAgIHByaXZhdGUgY2hvaWNlczogQUMuQ2hvaWNlW107XHJcbiAgICBwcml2YXRlIHN0eWxlOiBzdHJpbmc7XHJcbiAgICBwcml2YXRlIHNlbGVjdGVkVmFsdWVzOiBzdHJpbmdbXSA9IFtdO1xyXG5cclxuICAgIHB1YmxpYyBwYXJzZSA9IChqc29uOiBhbnksIGVycm9ycz86IEFDLklWYWxpZGF0aW9uRXJyb3JbXSkgPT4ge1xyXG4gICAgICAgIHN1cGVyLnBhcnNlKGpzb24sIGVycm9ycyk7XHJcbiAgICAgICAgdGhpcy52YWx1ZSA9IHRoaXMuZGVmYXVsdFZhbHVlO1xyXG4gICAgICAgIHRoaXMuc2VsZWN0ZWRWYWx1ZXMgPSB0aGlzLmRlZmF1bHRWYWx1ZVRvQXJyYXkodGhpcy52YWx1ZSk7XHJcbiAgICAgICAgdGhpcy5pc011bHRpU2VsZWN0ID0gQUMuZ2V0Qm9vbFZhbHVlKGpzb24uaXNNdWx0aVNlbGVjdCwgZmFsc2UpO1xyXG4gICAgICAgIHRoaXMudGl0bGUgPSBBQy5nZXRTdHJpbmdWYWx1ZShqc29uLnRpdGxlKTtcclxuICAgICAgICB0aGlzLnN0eWxlID0gQUMuZ2V0U3RyaW5nVmFsdWUoanNvbi5zdHlsZSk7XHJcbiAgICAgICAgdGhpcy5wYXJzZUNob2lzZXMoanNvbik7XHJcbiAgICB9XHJcblxyXG4gICAgcHJvdGVjdGVkIHJlbmRlclJlYWN0ID0gKCk6IEpTWC5FbGVtZW50ID0+IChcclxuICAgICAgICB0aGlzLmlzQ29tcGFjdCgpID9cclxuICAgICAgICAgICAgPHRoaXMuQ29tYm9Cb3ggLz4gOlxyXG4gICAgICAgICAgICB0aGlzLmNyZWF0ZUV4cGFuZGVkVmlldygpXHJcbiAgICApXHJcblxyXG4gICAgcHVibGljIGdldEpzb25UeXBlTmFtZSA9ICgpOiBzdHJpbmcgPT4gXCJJbnB1dC5DaG9pY2VTZXRcIjtcclxuXHJcbiAgICBwdWJsaWMgdG9KU09OID0gKCkgPT4ge1xyXG4gICAgICAgIGxldCByZXN1bHQgPSBzdXBlci50b0pTT04oKTtcclxuXHJcbiAgICAgICAgaWYgKHRoaXMuY2hvaWNlcy5sZW5ndGggPiAwKSB7XHJcbiAgICAgICAgICAgIEFDLnNldFByb3BlcnR5KHJlc3VsdCwgXCJjaG9pY2VzXCIsIHRoaXMuY2hvaWNlcy5tYXAoY2ggPT4gY2gudG9KU09OKCkpKTtcclxuICAgICAgICB9XHJcblxyXG4gICAgICAgIGlmICghdGhpcy5pc0NvbXBhY3QoKSkge1xyXG4gICAgICAgICAgICBBQy5zZXRQcm9wZXJ0eShyZXN1bHQsIFwic3R5bGVcIiwgXCJleHBhbmRlZFwiLCBmYWxzZSk7XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICBBQy5zZXRQcm9wZXJ0eShyZXN1bHQsIFwiaXNNdWx0aVNlbGVjdFwiLCB0aGlzLmlzTXVsdGlTZWxlY3QsIGZhbHNlKTtcclxuXHJcbiAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgIH1cclxuXHJcbiAgICBwcml2YXRlIHBhcnNlQ2hvaXNlcyA9IChqc29uOiBhbnkpID0+IHtcclxuICAgICAgICB0aGlzLmNob2ljZXMgPSBBcnJheS5pc0FycmF5KGpzb24uY2hvaWNlcykgP1xyXG4gICAgICAgICAgICBqc29uLmNob2ljZXMubWFwKGNoID0+IHtcclxuICAgICAgICAgICAgICAgIGxldCBjaG9pY2UgPSBuZXcgQUMuQ2hvaWNlKCk7XHJcbiAgICAgICAgICAgICAgICBjaG9pY2UucGFyc2UoY2gpO1xyXG4gICAgICAgICAgICAgICAgcmV0dXJuIGNob2ljZTtcclxuICAgICAgICAgICAgfSkgOlxyXG4gICAgICAgICAgICBbXTtcclxuICAgIH1cclxuXHJcbiAgICBwcml2YXRlIGlzQ29tcGFjdCA9ICgpID0+IHRoaXMuc3R5bGUgPT09IFwiY29tcGFjdFwiO1xyXG5cclxuICAgIHByaXZhdGUgQ29tYm9Cb3ggPSAoKTogSlNYLkVsZW1lbnQgPT4gKFxyXG4gICAgICAgIDxGYWJyaWNVSS5Db21ib0JveFxyXG4gICAgICAgICAgICBvbkNoYW5nZT17dGhpcy5oYW5kbGVDb21ib0JveENoYW5nZX1cclxuICAgICAgICAgICAgaWQ9e3RoaXMuaWR9XHJcbiAgICAgICAgICAgIG9wdGlvbnM9e3RoaXMuaW5wdXRDaG9pY2VzVG9Db21ib0JveE9wdGlvbnModGhpcy5jaG9pY2VzKX1cclxuICAgICAgICAgICAgbXVsdGlTZWxlY3Q9e3RoaXMuaXNNdWx0aVNlbGVjdH1cclxuICAgICAgICAgICAgc2VsZWN0ZWRLZXk9e3RoaXMuZGVmYXVsdFZhbHVlVG9BcnJheSh0aGlzLnZhbHVlKX1cclxuICAgICAgICAvPlxyXG4gICAgKVxyXG5cclxuICAgIHByaXZhdGUgY3JlYXRlRXhwYW5kZWRWaWV3ID0gKCk6IEpTWC5FbGVtZW50ID0+IHtcclxuICAgICAgICByZXR1cm4gdGhpcy5pc011bHRpU2VsZWN0ID9cclxuICAgICAgICAgICAgdGhpcy5pbnB1dENob2ljZXNUb0NoZWNrYm94KCkgOlxyXG4gICAgICAgICAgICB0aGlzLmNyZWF0ZUNob2ljZUdyb3VwKCk7XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBjcmVhdGVDaG9pY2VHcm91cCA9ICgpOiBKU1guRWxlbWVudCA9PiAoXHJcbiAgICAgICAgPEZhYnJpY1VJLkNob2ljZUdyb3VwXHJcbiAgICAgICAgICAgIGlkPXt0aGlzLmlkfVxyXG4gICAgICAgICAgICBvbkNoYW5nZT17dGhpcy5oYW5kbGVDaG9pY2VHcm91cENoYW5nZX1cclxuICAgICAgICAgICAgb3B0aW9ucz17dGhpcy5pbnB1dENob2ljZXNUb0Nob2ljZUdyb3VwT3B0aW9ucyhcclxuICAgICAgICAgICAgICAgIHRoaXMuY2hvaWNlcyxcclxuICAgICAgICAgICAgICAgIHRoaXMuZGVmYXVsdFZhbHVlVG9BcnJheSh0aGlzLnZhbHVlKSl9XHJcbiAgICAgICAgICAgIG11bHRpcGxlPXt0aGlzLmlzTXVsdGlTZWxlY3R9XHJcbiAgICAgICAgLz5cclxuICAgIClcclxuXHJcbiAgICBwcml2YXRlIGlucHV0Q2hvaWNlc1RvQ2hlY2tib3ggPSAoKTogSlNYLkVsZW1lbnQgPT4gKFxyXG4gICAgICAgIDxSZWFjdC5GcmFnbWVudD5cclxuICAgICAgICAgICAge3RoaXMuY2hvaWNlcy5tYXAoKGMsIGkpID0+XHJcbiAgICAgICAgICAgICAgICA8RmFicmljVUkuQ2hlY2tib3hcclxuICAgICAgICAgICAgICAgICAgICBrZXk9e2MudmFsdWV9XHJcbiAgICAgICAgICAgICAgICAgICAgbGFiZWw9e2MudGl0bGV9XHJcbiAgICAgICAgICAgICAgICAgICAgZGVmYXVsdENoZWNrZWQ9e3RoaXMuZGVmYXVsdFZhbHVlVG9BcnJheSh0aGlzLnZhbHVlKS5pbmNsdWRlcyhjLnZhbHVlKX1cclxuICAgICAgICAgICAgICAgICAgICBvbkNoYW5nZT17KGV2LCBjaGVja2VkKSA9PiB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgIHRoaXMudXBkYXRlTXVsdGlzZWxlY3REYXRhKGNoZWNrZWQsIGMudmFsdWUpO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBldi5zdG9wUHJvcGFnYXRpb24oKTtcclxuICAgICAgICAgICAgICAgICAgICAgICAgZXYucHJldmVudERlZmF1bHQoKTtcclxuICAgICAgICAgICAgICAgICAgICB9fVxyXG4gICAgICAgICAgICAgICAgICAgIHN0eWxlcz17e1xyXG4gICAgICAgICAgICAgICAgICAgICAgICByb290OiB7XHJcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBwYWRkaW5nVG9wOiBpID4gMCA/IHRoaXMuaG9zdENvbmZpZy5zcGFjaW5nLmRlZmF1bHQgOiAwLFxyXG4gICAgICAgICAgICAgICAgICAgICAgICB9LFxyXG4gICAgICAgICAgICAgICAgICAgIH19XHJcbiAgICAgICAgICAgICAgICAvPixcclxuICAgICAgICAgICAgKX1cclxuICAgICAgICA8L1JlYWN0LkZyYWdtZW50PlxyXG4gICAgKVxyXG5cclxuICAgIHByaXZhdGUgZGVmYXVsdFZhbHVlVG9BcnJheSA9ICh2YWx1ZTogc3RyaW5nKTogc3RyaW5nW10gPT4ge1xyXG4gICAgICAgIGlmICh2YWx1ZSkge1xyXG4gICAgICAgICAgICByZXR1cm4gdmFsdWUuc3BsaXQoXCIsXCIpO1xyXG4gICAgICAgIH1cclxuICAgICAgICByZXR1cm4gW107XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBpbnB1dENob2ljZXNUb0NvbWJvQm94T3B0aW9ucyA9IChjaG9pY2VzOiBBQy5DaG9pY2VbXSk6IEZhYnJpY1VJLklDb21ib0JveE9wdGlvbltdID0+IHtcclxuICAgICAgICByZXR1cm4gY2hvaWNlcy5tYXA8RmFicmljVUkuSUNvbWJvQm94T3B0aW9uPihjID0+ICh7IGtleTogYy52YWx1ZSwgdGV4dDogYy50aXRsZSB9KSk7XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBpbnB1dENob2ljZXNUb0Nob2ljZUdyb3VwT3B0aW9ucyA9IChjaG9pY2VzOiBBQy5DaG9pY2VbXSwgdmFsdWU6IHN0cmluZ1tdKTogRmFicmljVUkuSUNob2ljZUdyb3VwT3B0aW9uW10gPT4ge1xyXG4gICAgICAgIHJldHVybiBjaG9pY2VzLm1hcDxGYWJyaWNVSS5JQ2hvaWNlR3JvdXBPcHRpb24+KGMgPT4gKHsga2V5OiBjLnZhbHVlLCB0ZXh0OiBjLnRpdGxlLCBjaGVja2VkOiB2YWx1ZS5pbmNsdWRlcyhjLnZhbHVlKSB9KSk7XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBoYW5kbGVDaG9pY2VHcm91cENoYW5nZSA9XHJcbiAgICAgICAgKGV2PzogUmVhY3QuRm9ybUV2ZW50PEhUTUxFbGVtZW50IHwgSFRNTElucHV0RWxlbWVudD4sIG9wdGlvbj86IEZhYnJpY1VJLklDaG9pY2VHcm91cE9wdGlvbik6IHZvaWQgPT4ge1xyXG4gICAgICAgICAgICB0aGlzLnZhbHVlID0gb3B0aW9uLmtleTtcclxuICAgICAgICAgICAgZXYuc3RvcFByb3BhZ2F0aW9uKCk7XHJcbiAgICAgICAgICAgIGV2LnByZXZlbnREZWZhdWx0KCk7XHJcbiAgICAgICAgfVxyXG5cclxuICAgIHByaXZhdGUgaGFuZGxlQ29tYm9Cb3hDaGFuZ2UgPVxyXG4gICAgICAgIChldmVudDogUmVhY3QuRm9ybUV2ZW50PEZhYnJpY1VJLklDb21ib0JveD4sIG9wdGlvbj86IEZhYnJpY1VJLklDb21ib0JveE9wdGlvbiwgaW5kZXg/OiBudW1iZXIsIHZhbHVlPzogc3RyaW5nKTogdm9pZCA9PiB7XHJcbiAgICAgICAgICAgIGlmICh0aGlzLmlzTXVsdGlTZWxlY3QpIHtcclxuICAgICAgICAgICAgICAgIHRoaXMudXBkYXRlTXVsdGlzZWxlY3REYXRhKG9wdGlvbi5zZWxlY3RlZCwgb3B0aW9uLmtleSk7XHJcbiAgICAgICAgICAgIH0gZWxzZSB7XHJcbiAgICAgICAgICAgICAgICB0aGlzLnZhbHVlID0gYCR7b3B0aW9uLmtleX1gO1xyXG4gICAgICAgICAgICB9XHJcbiAgICAgICAgICAgIGV2ZW50LnN0b3BQcm9wYWdhdGlvbigpO1xyXG4gICAgICAgICAgICBldmVudC5wcmV2ZW50RGVmYXVsdCgpO1xyXG4gICAgICAgIH1cclxuXHJcbiAgICBwcml2YXRlIHVwZGF0ZU11bHRpc2VsZWN0RGF0YSA9IChzZWxlY3RlZDogYm9vbGVhbiwga2V5OiBhbnkpOiB2b2lkID0+IHtcclxuICAgICAgICB0aGlzLnVwZGF0ZVNlbGVjdGVkVmFsdWVzKHNlbGVjdGVkLCBrZXkpO1xyXG4gICAgICAgIHRoaXMudmFsdWUgPSB0aGlzLnNlbGVjdGVkVmFsdWVzLmpvaW4oXCIsXCIpO1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgdXBkYXRlU2VsZWN0ZWRWYWx1ZXMgPSAoc2VsZWN0ZWQ6IGJvb2xlYW4sIGtleTogYW55KTogdm9pZCA9PiB7XHJcbiAgICAgICAgc2VsZWN0ZWQgPyB0aGlzLnNlbGVjdGVkVmFsdWVzLnB1c2goa2V5KSA6IHRoaXMucmVtb3ZlSXRlbUZyb21BcnJheSh0aGlzLnNlbGVjdGVkVmFsdWVzLCBrZXkpO1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgcmVtb3ZlSXRlbUZyb21BcnJheSA9IChhcnI6IGFueVtdLCBpdGVtOiBhbnkpOiB2b2lkID0+IHtcclxuICAgICAgICBjb25zdCBpbmRleCA9IGFyci5pbmRleE9mKGl0ZW0pO1xyXG4gICAgICAgIGFyci5zcGxpY2UoaW5kZXgsIDEpO1xyXG4gICAgfVxyXG59XHJcbiIsIi8vIENvcHlyaWdodCAoYykgTWljcm9zb2Z0IENvcnBvcmF0aW9uLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxyXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgTUlUIExpY2Vuc2UuXHJcblxyXG5pbXBvcnQgKiBhcyBSZWFjdCBmcm9tIFwicmVhY3RcIjtcclxuaW1wb3J0ICogYXMgRmFicmljVUkgZnJvbSBcIm9mZmljZS11aS1mYWJyaWMtcmVhY3RcIjtcclxuaW1wb3J0ICogYXMgQUMgZnJvbSBcImFkYXB0aXZlY2FyZHNcIjtcclxuaW1wb3J0ICogYXMgU2hhcmVkIGZyb20gXCIuLi8uLi91dGlscy9zaGFyZWRcIjtcclxuXHJcbmV4cG9ydCBjbGFzcyBJbnB1dERhdGVGYWJyaWMgZXh0ZW5kcyBTaGFyZWQuUmVhY3RJbnB1dEVsZW1lbnQge1xyXG5cclxuICAgIHByaXZhdGUgZGF0ZTogRGF0ZTtcclxuICAgIHByaXZhdGUgcGxhY2Vob2xkZXI6IHN0cmluZztcclxuICAgIHByaXZhdGUgbWluRGF0ZTogRGF0ZTtcclxuICAgIHByaXZhdGUgbWF4RGF0ZTogRGF0ZTtcclxuXHJcbiAgICBwcm90ZWN0ZWQgcmVuZGVyUmVhY3QgPSAoKTogSlNYLkVsZW1lbnQgPT4ge1xyXG4gICAgICAgIHJldHVybiB0aGlzLmJ1aWxkRGF0ZVBpY2tlcigpO1xyXG4gICAgfVxyXG5cclxuICAgIHB1YmxpYyBnZXRKc29uVHlwZU5hbWUgPSAoKTogc3RyaW5nID0+IFwiSW5wdXQuRGF0ZVwiO1xyXG5cclxuICAgIHB1YmxpYyBwYXJzZSA9IChqc29uOiBhbnksIGVycm9ycz86IEFDLklWYWxpZGF0aW9uRXJyb3JbXSkgPT4ge1xyXG4gICAgICAgIHN1cGVyLnBhcnNlKGpzb24sIGVycm9ycyk7XHJcbiAgICAgICAgdGhpcy5wbGFjZWhvbGRlciA9IEFDLmdldFN0cmluZ1ZhbHVlKGpzb24ucGxhY2Vob2xkZXIpO1xyXG4gICAgICAgIHRoaXMucGFyc2VEYXRlcyhqc29uLCBlcnJvcnMpO1xyXG4gICAgfVxyXG5cclxuICAgIHB1YmxpYyB0b0pTT04gPSAoKSA9PiB7XHJcbiAgICAgICAgbGV0IHJlc3VsdCA9IHN1cGVyLnRvSlNPTigpO1xyXG5cclxuICAgICAgICBBQy5zZXRQcm9wZXJ0eShyZXN1bHQsIFwibWluXCIsIHRoaXMubWluRGF0ZSk7XHJcbiAgICAgICAgQUMuc2V0UHJvcGVydHkocmVzdWx0LCBcIm1heFwiLCB0aGlzLm1heERhdGUpO1xyXG4gICAgICAgIEFDLnNldFByb3BlcnR5KHJlc3VsdCwgXCJwbGFjZWhvbGRlclwiLCB0aGlzLnBsYWNlaG9sZGVyKTtcclxuXHJcbiAgICAgICAgcmV0dXJuIHJlc3VsdDtcclxuICAgIH1cclxuXHJcbiAgICBwcml2YXRlIHBhcnNlRGF0ZXMgPSAoanNvbjogYW55LCBlcnJvcnM/OiBBQy5JVmFsaWRhdGlvbkVycm9yW10pID0+IHtcclxuICAgICAgICB0aGlzLnZhbHVlID0gdGhpcy5kZWZhdWx0VmFsdWU7XHJcbiAgICAgICAgdGhpcy5kYXRlID0gdGhpcy52YWx1ZSA/IHRoaXMuZ2V0RGF0ZSh0aGlzLnZhbHVlKSA6IG5ldyBEYXRlKCk7XHJcbiAgICAgICAgdGhpcy5taW5EYXRlID0ganNvbi5taW4gPyB0aGlzLmdldERhdGUoQUMuZ2V0U3RyaW5nVmFsdWUoanNvbi5taW4pKSA6IHVuZGVmaW5lZDtcclxuICAgICAgICB0aGlzLm1heERhdGUgPSBqc29uLm1heCA/IHRoaXMuZ2V0RGF0ZShBQy5nZXRTdHJpbmdWYWx1ZShqc29uLm1heCkpIDogdW5kZWZpbmVkO1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgZ2V0RGF0ZSA9IChkYXRlU3RyaW5nOiBzdHJpbmcsIGVycm9ycz86IEFDLklWYWxpZGF0aW9uRXJyb3JbXSk6IERhdGUgPT4ge1xyXG4gICAgICAgIHRyeSB7XHJcbiAgICAgICAgICAgIHJldHVybiBuZXcgRGF0ZShkYXRlU3RyaW5nKTtcclxuICAgICAgICB9IGNhdGNoIChlcnJvcikge1xyXG4gICAgICAgICAgICBTaGFyZWQucmFpc2VQYXJzZUVycm9yKHtcclxuICAgICAgICAgICAgICAgIGVycm9yOiBBQy5WYWxpZGF0aW9uRXJyb3IuSW52YWxpZFByb3BlcnR5VmFsdWUsXHJcbiAgICAgICAgICAgICAgICBtZXNzYWdlOiBlcnJvcixcclxuICAgICAgICAgICAgfSwgZXJyb3JzKTtcclxuICAgICAgICAgICAgcmV0dXJuIHVuZGVmaW5lZDtcclxuICAgICAgICB9XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBidWlsZERhdGVQaWNrZXIgPSAoKSA9PiB7XHJcbiAgICAgICAgcmV0dXJuICg8RmFicmljVUkuRGF0ZVBpY2tlclxyXG4gICAgICAgICAgICBpZD17dGhpcy5pZH1cclxuICAgICAgICAgICAgb25TZWxlY3REYXRlPXt0aGlzLmhhbmRsZVNlbGVjdERhdGV9XHJcbiAgICAgICAgICAgIHZhbHVlPXt0aGlzLmRhdGV9XHJcbiAgICAgICAgICAgIHBsYWNlaG9sZGVyPXt0aGlzLnBsYWNlaG9sZGVyfVxyXG4gICAgICAgICAgICBhbGxvd1RleHRJbnB1dD17dHJ1ZX1cclxuICAgICAgICAgICAgbWluRGF0ZT17dGhpcy5taW5EYXRlfVxyXG4gICAgICAgICAgICBtYXhEYXRlPXt0aGlzLm1heERhdGV9XHJcbiAgICAgICAgLz4pO1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgaGFuZGxlU2VsZWN0RGF0ZSA9IChkYXRlOiBEYXRlKSA9PiB7XHJcbiAgICAgICAgdGhpcy52YWx1ZSA9IGRhdGUudG9Mb2NhbGVEYXRlU3RyaW5nKFwiZW4tVVNcIik7XHJcbiAgICB9XHJcbn1cclxuIiwiLy8gQ29weXJpZ2h0IChjKSBNaWNyb3NvZnQgQ29ycG9yYXRpb24uIEFsbCByaWdodHMgcmVzZXJ2ZWQuXHJcbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBNSVQgTGljZW5zZS5cclxuXHJcbmltcG9ydCAqIGFzIFJlYWN0IGZyb20gXCJyZWFjdFwiO1xyXG5pbXBvcnQgKiBhcyBBQyBmcm9tIFwiYWRhcHRpdmVjYXJkc1wiO1xyXG5pbXBvcnQgKiBhcyBGYWJyaWNVSSBmcm9tIFwib2ZmaWNlLXVpLWZhYnJpYy1yZWFjdFwiO1xyXG5pbXBvcnQgKiBhcyBTaGFyZWQgZnJvbSBcIi4uLy4uL3V0aWxzL3NoYXJlZFwiO1xyXG5cclxuZXhwb3J0IGNsYXNzIElucHV0TnVtYmVyRmFicmljIGV4dGVuZHMgU2hhcmVkLlJlYWN0SW5wdXRFbGVtZW50IHtcclxuXHJcbiAgICBwcml2YXRlIG1heD86IG51bWJlcjtcclxuICAgIHByaXZhdGUgbWluPzogbnVtYmVyO1xyXG4gICAgcHJpdmF0ZSBwbGFjZWhvbGRlcjogc3RyaW5nO1xyXG5cclxuICAgIHB1YmxpYyBwYXJzZSA9IChqc29uOiBhbnksIGVycm9ycz86IEFDLklWYWxpZGF0aW9uRXJyb3JbXSkgPT4ge1xyXG4gICAgICAgIHN1cGVyLnBhcnNlKGpzb24sIGVycm9ycyk7XHJcbiAgICAgICAgdGhpcy52YWx1ZSA9IHRoaXMuZGVmYXVsdFZhbHVlO1xyXG4gICAgICAgIHRoaXMubWluID0gU2hhcmVkLmdldEludFZhbHVlKGpzb24ubWluKTtcclxuICAgICAgICB0aGlzLm1heCA9IFNoYXJlZC5nZXRJbnRWYWx1ZShqc29uLm1heCk7XHJcbiAgICAgICAgdGhpcy5wbGFjZWhvbGRlciA9IEFDLmdldFN0cmluZ1ZhbHVlKGpzb24ucGxhY2Vob2xkZXIpO1xyXG4gICAgfVxyXG5cclxuICAgIHByb3RlY3RlZCByZW5kZXJSZWFjdCA9ICgpOiBKU1guRWxlbWVudCA9PiAoXHJcbiAgICAgICAgPEZhYnJpY1VJLlRleHRGaWVsZFxyXG4gICAgICAgICAgICBpZD17dGhpcy5pZH1cclxuICAgICAgICAgICAgcGxhY2Vob2xkZXI9e2Ake3RoaXMucGxhY2Vob2xkZXJ9YH1cclxuICAgICAgICAgICAgdmFsdWU9e2Ake3RoaXMuZGVmYXVsdFZhbHVlfWB9XHJcbiAgICAgICAgICAgIHR5cGU9XCJudW1iZXJcIlxyXG4gICAgICAgICAgICBtYXg9e3RoaXMubWF4fVxyXG4gICAgICAgICAgICBtaW49e3RoaXMubWlufVxyXG4gICAgICAgICAgICBvbkNoYW5nZT17dGhpcy5oYW5kbGVDaGFuZ2V9XHJcbiAgICAgICAgLz5cclxuICAgIClcclxuXHJcbiAgICBwdWJsaWMgZ2V0SnNvblR5cGVOYW1lID0gKCk6IHN0cmluZyA9PiBcIklucHV0Lk51bWJlclwiO1xyXG5cclxuICAgIHB1YmxpYyB0b0pTT04gPSAoKSA9PiB7XHJcbiAgICAgICAgbGV0IHJlc3VsdCA9IHN1cGVyLnRvSlNPTigpO1xyXG5cclxuICAgICAgICBBQy5zZXRQcm9wZXJ0eShyZXN1bHQsIFwicGxhY2Vob2xkZXJcIiwgdGhpcy5wbGFjZWhvbGRlcik7XHJcbiAgICAgICAgQUMuc2V0UHJvcGVydHkocmVzdWx0LCBcIm1pblwiLCB0aGlzLm1pbik7XHJcbiAgICAgICAgQUMuc2V0UHJvcGVydHkocmVzdWx0LCBcIm1heFwiLCB0aGlzLm1heCk7XHJcblxyXG4gICAgICAgIHJldHVybiByZXN1bHQ7XHJcbiAgICB9XHJcbn1cclxuIiwiLy8gQ29weXJpZ2h0IChjKSBNaWNyb3NvZnQgQ29ycG9yYXRpb24uIEFsbCByaWdodHMgcmVzZXJ2ZWQuXHJcbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBNSVQgTGljZW5zZS5cclxuXHJcbmltcG9ydCAqIGFzIFJlYWN0IGZyb20gXCJyZWFjdFwiO1xyXG5pbXBvcnQgeyBUZXh0RmllbGQgfSBmcm9tIFwib2ZmaWNlLXVpLWZhYnJpYy1yZWFjdFwiO1xyXG5pbXBvcnQgKiBhcyBBQyBmcm9tIFwiYWRhcHRpdmVjYXJkc1wiO1xyXG5pbXBvcnQgKiBhcyBTaGFyZWQgZnJvbSBcIi4uLy4uL3V0aWxzL3NoYXJlZFwiO1xyXG5cclxuZXhwb3J0IGNsYXNzIElucHV0VGV4dEZhYnJpYyBleHRlbmRzIFNoYXJlZC5SZWFjdElucHV0RWxlbWVudCB7XHJcblxyXG4gICAgcHJpdmF0ZSBpc011bHRpbGluZTogYm9vbGVhbjtcclxuICAgIHByaXZhdGUgbWF4TGVuZ3RoOiBudW1iZXI7XHJcbiAgICBwcml2YXRlIHBsYWNlaG9sZGVyOiBzdHJpbmc7XHJcbiAgICBwcml2YXRlIGxhYmVsOiBzdHJpbmc7XHJcbiAgICBwcml2YXRlIHN0eWxlOiBBQy5JbnB1dFRleHRTdHlsZSA9IEFDLklucHV0VGV4dFN0eWxlLlRleHQ7XHJcblxyXG4gICAgcHJvdGVjdGVkIHJlbmRlclJlYWN0ID0gKCk6IEpTWC5FbGVtZW50ID0+IHtcclxuICAgICAgICByZXR1cm4gdGhpcy5idWlsZElucHV0KCk7XHJcbiAgICB9XHJcblxyXG4gICAgcHVibGljIGdldEpzb25UeXBlTmFtZSA9ICgpOiBzdHJpbmcgPT4gXCJJbnB1dC5UZXh0XCI7XHJcblxyXG4gICAgcHVibGljIHBhcnNlID0gKGpzb246IGFueSwgZXJyb3JzPzogYW55KSA9PiB7XHJcbiAgICAgICAgc3VwZXIucGFyc2UoanNvbiwgZXJyb3JzKTtcclxuICAgICAgICB0aGlzLnZhbHVlID0gdGhpcy5kZWZhdWx0VmFsdWU7XHJcbiAgICAgICAgdGhpcy5pc011bHRpbGluZSA9IEFDLmdldEJvb2xWYWx1ZShqc29uLmlzTXVsdGlsaW5lLCBmYWxzZSk7XHJcbiAgICAgICAgdGhpcy5tYXhMZW5ndGggPSBTaGFyZWQuZ2V0SW50VmFsdWUoanNvbi5tYXhMZW5ndGgpO1xyXG4gICAgICAgIHRoaXMucGxhY2Vob2xkZXIgPSBBQy5nZXRTdHJpbmdWYWx1ZShqc29uLnBsYWNlaG9sZGVyKTtcclxuICAgICAgICB0aGlzLmxhYmVsID0gQUMuZ2V0U3RyaW5nVmFsdWUoanNvbi5sYWJlbCk7XHJcbiAgICAgICAgdGhpcy5zdHlsZSA9IEFDLmdldEVudW1WYWx1ZShBQy5JbnB1dFRleHRTdHlsZSwganNvbi5zdHlsZSwgQUMuSW5wdXRUZXh0U3R5bGUuVGV4dCk7XHJcbiAgICAgICAgdGhpcy5pbmxpbmVBY3Rpb24gPSBBQy5jcmVhdGVBY3Rpb25JbnN0YW5jZSh0aGlzLCBqc29uLmlubGluZUFjdGlvbiwgW0FDLlNob3dDYXJkQWN0aW9uLkpzb25UeXBlTmFtZV0sIGZhbHNlLCBlcnJvcnMpO1xyXG4gICAgfVxyXG5cclxuICAgIHB1YmxpYyB0b0pTT04gPSAoKSA9PiB7XHJcbiAgICAgICAgbGV0IHJlc3VsdCA9IHN1cGVyLnRvSlNPTigpO1xyXG5cclxuICAgICAgICBBQy5zZXRQcm9wZXJ0eShyZXN1bHQsIFwicGxhY2Vob2xkZXJcIiwgdGhpcy5wbGFjZWhvbGRlcik7XHJcbiAgICAgICAgQUMuc2V0UHJvcGVydHkocmVzdWx0LCBcIm1heExlbmd0aFwiLCB0aGlzLm1heExlbmd0aCwgMCk7XHJcbiAgICAgICAgQUMuc2V0UHJvcGVydHkocmVzdWx0LCBcImlzTXVsdGlsaW5lXCIsIHRoaXMuaXNNdWx0aWxpbmUsIGZhbHNlKTtcclxuICAgICAgICBBQy5zZXRFbnVtUHJvcGVydHkoQUMuSW5wdXRUZXh0U3R5bGUsIHJlc3VsdCwgXCJzdHlsZVwiLCB0aGlzLnN0eWxlLCBBQy5JbnB1dFRleHRTdHlsZS5UZXh0KTtcclxuICAgICAgICBpZiAodGhpcy5pbmxpbmVBY3Rpb24pIHtcclxuICAgICAgICAgICAgQUMuc2V0UHJvcGVydHkocmVzdWx0LCBcImlubGluZUFjdGlvblwiLCB0aGlzLmlubGluZUFjdGlvbi50b0pTT04oKSk7XHJcbiAgICAgICAgfVxyXG5cclxuICAgICAgICByZXR1cm4gcmVzdWx0O1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgYnVpbGRJbnB1dCA9ICgpOiBKU1guRWxlbWVudCA9PiB7XHJcbiAgICAgICAgcmV0dXJuIChcclxuICAgICAgICAgICAgPFRleHRGaWVsZFxyXG4gICAgICAgICAgICAgICAgaWQ9e3RoaXMuaWR9XHJcbiAgICAgICAgICAgICAgICB0eXBlPXtBQy5JbnB1dFRleHRTdHlsZVt0aGlzLnN0eWxlXS50b0xvd2VyQ2FzZSgpfVxyXG4gICAgICAgICAgICAgICAgdmFsdWU9e3RoaXMuZGVmYXVsdFZhbHVlfVxyXG4gICAgICAgICAgICAgICAgbXVsdGlsaW5lPXt0aGlzLmlzTXVsdGlsaW5lfVxyXG4gICAgICAgICAgICAgICAgbWF4TGVuZ3RoPXt0aGlzLm1heExlbmd0aH1cclxuICAgICAgICAgICAgICAgIHBsYWNlaG9sZGVyPXt0aGlzLnBsYWNlaG9sZGVyfVxyXG4gICAgICAgICAgICAgICAgbGFiZWw9e3RoaXMubGFiZWx9XHJcbiAgICAgICAgICAgICAgICBvbkNoYW5nZT17dGhpcy5oYW5kbGVDaGFuZ2V9XHJcbiAgICAgICAgICAgICAgICBvbktleURvd249e3RoaXMuaGFuZGxlS2V5RG93bn1cclxuICAgICAgICAgICAgLz5cclxuICAgICAgICApO1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgaGFuZGxlS2V5RG93biA9IChlOiBSZWFjdC5LZXlib2FyZEV2ZW50PEhUTUxJbnB1dEVsZW1lbnQgfCBIVE1MVGV4dEFyZWFFbGVtZW50Pik6IHZvaWQgPT4ge1xyXG4gICAgICAgIC8vIEVudGVyIHByZXNzZWRcclxuICAgICAgICBpZiAoZS5rZXlDb2RlID09PSAxMyAmJiB0aGlzLmlubGluZUFjdGlvbikge1xyXG4gICAgICAgICAgICB0aGlzLmlubGluZUFjdGlvbi5leGVjdXRlKCk7XHJcbiAgICAgICAgfVxyXG4gICAgfVxyXG59XHJcbiIsIi8vIENvcHlyaWdodCAoYykgTWljcm9zb2Z0IENvcnBvcmF0aW9uLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxyXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgTUlUIExpY2Vuc2UuXHJcblxyXG5pbXBvcnQgKiBhcyBSZWFjdCBmcm9tIFwicmVhY3RcIjtcclxuaW1wb3J0ICogYXMgQUMgZnJvbSBcImFkYXB0aXZlY2FyZHNcIjtcclxuaW1wb3J0ICogYXMgRmFicmljVUkgZnJvbSBcIm9mZmljZS11aS1mYWJyaWMtcmVhY3RcIjtcclxuaW1wb3J0ICogYXMgU2hhcmVkIGZyb20gXCIuLi8uLi91dGlscy9zaGFyZWRcIjtcclxuXHJcbmV4cG9ydCBjbGFzcyBJbnB1dFRpbWVGYWJyaWMgZXh0ZW5kcyBTaGFyZWQuUmVhY3RJbnB1dEVsZW1lbnQge1xyXG5cclxuICAgIHByaXZhdGUgcGxhY2Vob2xkZXI6IHN0cmluZztcclxuICAgIHByaXZhdGUgbWluOiBzdHJpbmc7XHJcbiAgICBwcml2YXRlIG1heDogc3RyaW5nO1xyXG5cclxuICAgIHB1YmxpYyBwYXJzZSA9IChqc29uOiBhbnksIGVycm9ycz86IEFDLklWYWxpZGF0aW9uRXJyb3JbXSkgPT4ge1xyXG4gICAgICAgIHN1cGVyLnBhcnNlKGpzb24sIGVycm9ycyk7XHJcbiAgICAgICAgdGhpcy52YWx1ZSA9IHRoaXMuZGVmYXVsdFZhbHVlO1xyXG4gICAgICAgIHRoaXMucGxhY2Vob2xkZXIgPSBBQy5nZXRTdHJpbmdWYWx1ZShqc29uLnBsYWNlaG9sZGVyKTtcclxuICAgICAgICB0aGlzLm1pbiA9IEFDLmdldFN0cmluZ1ZhbHVlKGpzb24ubWluKTtcclxuICAgICAgICB0aGlzLm1heCA9IEFDLmdldFN0cmluZ1ZhbHVlKGpzb24ubWF4KTtcclxuICAgIH1cclxuXHJcbiAgICBwcm90ZWN0ZWQgcmVuZGVyUmVhY3QgPSAoKTogSlNYLkVsZW1lbnQgPT4ge1xyXG4gICAgICAgIHJldHVybiAoXHJcbiAgICAgICAgICAgIDxGYWJyaWNVSS5UZXh0RmllbGRcclxuICAgICAgICAgICAgICAgIGlkPXt0aGlzLmlkfVxyXG4gICAgICAgICAgICAgICAgcGxhY2Vob2xkZXI9e2Ake3RoaXMucGxhY2Vob2xkZXJ9YH1cclxuICAgICAgICAgICAgICAgIHZhbHVlPXtgJHt0aGlzLmRlZmF1bHRWYWx1ZX1gfVxyXG4gICAgICAgICAgICAgICAgdHlwZT1cInRpbWVcIlxyXG4gICAgICAgICAgICAgICAgb25DaGFuZ2U9e3RoaXMuaGFuZGxlQ2hhbmdlfVxyXG4gICAgICAgICAgICAgICAgbWF4PXt0aGlzLm1heH1cclxuICAgICAgICAgICAgICAgIG1pbj17dGhpcy5taW59XHJcbiAgICAgICAgICAgIC8+XHJcbiAgICAgICAgKTtcclxuICAgIH1cclxuXHJcbiAgICBwdWJsaWMgZ2V0SnNvblR5cGVOYW1lID0gKCk6IHN0cmluZyA9PiBcIklucHV0LlRpbWVcIjtcclxuXHJcbiAgICBwdWJsaWMgdG9KU09OID0gKCkgPT4ge1xyXG4gICAgICAgIGxldCByZXN1bHQgPSBzdXBlci50b0pTT04oKTtcclxuXHJcbiAgICAgICAgQUMuc2V0UHJvcGVydHkocmVzdWx0LCBcIm1pblwiLCB0aGlzLm1pbik7XHJcbiAgICAgICAgQUMuc2V0UHJvcGVydHkocmVzdWx0LCBcIm1heFwiLCB0aGlzLm1heCk7XHJcblxyXG4gICAgICAgIHJldHVybiByZXN1bHQ7XHJcbiAgICB9XHJcbn1cclxuIiwiLy8gQ29weXJpZ2h0IChjKSBNaWNyb3NvZnQgQ29ycG9yYXRpb24uIEFsbCByaWdodHMgcmVzZXJ2ZWQuXHJcbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBNSVQgTGljZW5zZS5cclxuXHJcbmltcG9ydCAqIGFzIFJlYWN0IGZyb20gXCJyZWFjdFwiO1xyXG5pbXBvcnQgKiBhcyBBQyBmcm9tIFwiYWRhcHRpdmVjYXJkc1wiO1xyXG5pbXBvcnQgKiBhcyBGYWJyaWNVSSBmcm9tIFwib2ZmaWNlLXVpLWZhYnJpYy1yZWFjdFwiO1xyXG5pbXBvcnQgKiBhcyBTaGFyZWQgZnJvbSBcIi4uLy4uL3V0aWxzL3NoYXJlZFwiO1xyXG5cclxuZXhwb3J0IGNsYXNzIElucHV0VG9nZ2xlRmFicmljIGV4dGVuZHMgU2hhcmVkLlJlYWN0SW5wdXRFbGVtZW50IHtcclxuXHJcbiAgICBwcml2YXRlIHZhbHVlT246IHN0cmluZztcclxuICAgIHByaXZhdGUgdmFsdWVPZmY6IHN0cmluZztcclxuXHJcbiAgICBwdWJsaWMgcGFyc2UgPSAoanNvbjogYW55LCBlcnJvcnM/OiBBQy5JVmFsaWRhdGlvbkVycm9yW10pID0+IHtcclxuICAgICAgICBzdXBlci5wYXJzZShqc29uLCBlcnJvcnMpO1xyXG4gICAgICAgIHRoaXMudmFsdWUgPSB0aGlzLmRlZmF1bHRWYWx1ZTtcclxuICAgICAgICB0aGlzLnZhbHVlT24gPSBBQy5nZXRTdHJpbmdWYWx1ZShqc29uLnZhbHVlT24pO1xyXG4gICAgICAgIHRoaXMudmFsdWVPZmYgPSBBQy5nZXRTdHJpbmdWYWx1ZShqc29uLnZhbHVlT2ZmKTtcclxuICAgICAgICB0aGlzLnRpdGxlID0gQUMuZ2V0U3RyaW5nVmFsdWUoanNvbi50aXRsZSk7XHJcbiAgICB9XHJcblxyXG4gICAgcHJvdGVjdGVkIHJlbmRlclJlYWN0ID0gKCk6IEpTWC5FbGVtZW50ID0+IChcclxuICAgICAgICA8RmFicmljVUkuVG9nZ2xlXHJcbiAgICAgICAgICAgIGlkPXt0aGlzLmlkfVxyXG4gICAgICAgICAgICBpbmxpbmVMYWJlbD17dHJ1ZX1cclxuICAgICAgICAgICAgb25DaGFuZ2U9e3RoaXMuaGFuZGxlVG9nZ2xlQ2hhbmdlfVxyXG4gICAgICAgICAgICBkZWZhdWx0Q2hlY2tlZD17dGhpcy5kZWZhdWx0VmFsdWUgPT09IHRoaXMudmFsdWVPbn1cclxuICAgICAgICAgICAgbGFiZWw9e3RoaXMudGl0bGV9XHJcbiAgICAgICAgICAgIHN0eWxlcz17e1xyXG4gICAgICAgICAgICAgICAgcm9vdDoge1xyXG4gICAgICAgICAgICAgICAgICAgIG1hcmdpbkJvdHRvbTogMCxcclxuICAgICAgICAgICAgICAgICAgICBtYXJnaW5Ub3A6IDAsXHJcbiAgICAgICAgICAgICAgICB9LFxyXG4gICAgICAgICAgICB9fVxyXG4gICAgICAgIC8+XHJcbiAgICApXHJcblxyXG4gICAgcHVibGljIGdldEpzb25UeXBlTmFtZSA9ICgpOiBzdHJpbmcgPT4gXCJJbnB1dC5Ub2dnbGVcIjtcclxuXHJcbiAgICBwdWJsaWMgdG9KU09OID0gKCkgPT4ge1xyXG4gICAgICAgIGxldCByZXN1bHQgPSBzdXBlci50b0pTT04oKTtcclxuXHJcbiAgICAgICAgQUMuc2V0UHJvcGVydHkocmVzdWx0LCBcInZhbHVlT25cIiwgdGhpcy52YWx1ZU9uLCBcInRydWVcIik7XHJcbiAgICAgICAgQUMuc2V0UHJvcGVydHkocmVzdWx0LCBcInZhbHVlT2ZmXCIsIHRoaXMudmFsdWVPZmYsIFwiZmFsc2VcIik7XHJcblxyXG4gICAgICAgIHJldHVybiByZXN1bHQ7XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBoYW5kbGVUb2dnbGVDaGFuZ2UgPSAoZXZlbnQ6IFJlYWN0Lk1vdXNlRXZlbnQ8SFRNTEVsZW1lbnQ+IHwgUmVhY3QuQ2hhbmdlRXZlbnQsIGNoZWNrZWQ/OiBib29sZWFuKSA9PiB7XHJcbiAgICAgICAgdGhpcy52YWx1ZSA9IGNoZWNrZWQgPyB0aGlzLnZhbHVlT24gOiB0aGlzLnZhbHVlT2ZmO1xyXG4gICAgfVxyXG59XHJcbiIsImV4cG9ydCAqIGZyb20gXCIuL0lucHV0Q2hvaWNlU2V0RmFicmljXCI7XHJcbmV4cG9ydCAqIGZyb20gXCIuL0lucHV0RGF0ZUZhYnJpY1wiO1xyXG5leHBvcnQgKiBmcm9tIFwiLi9JbnB1dE51bWJlckZhYnJpY1wiO1xyXG5leHBvcnQgKiBmcm9tIFwiLi9JbnB1dFRleHRGYWJyaWNcIjtcclxuZXhwb3J0ICogZnJvbSBcIi4vSW5wdXRUaW1lRmFicmljXCI7XHJcbmV4cG9ydCAqIGZyb20gXCIuL0lucHV0VG9nZ2xlRmFicmljXCI7XHJcbiIsIi8vIENvcHlyaWdodCAoYykgTWljcm9zb2Z0IENvcnBvcmF0aW9uLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxyXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgTUlUIExpY2Vuc2UuXHJcblxyXG5leHBvcnQgKiBmcm9tIFwiLi9jb21wb25lbnRzXCI7XHJcbmV4cG9ydCAqIGZyb20gXCIuL2FjdGlvbnNcIjtcclxuZXhwb3J0ICogZnJvbSBcIi4vdXRpbHMvc2hhcmVkXCI7XHJcbiIsIi8vIENvcHlyaWdodCAoYykgTWljcm9zb2Z0IENvcnBvcmF0aW9uLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxyXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgTUlUIExpY2Vuc2UuXHJcblxyXG5pbXBvcnQgKiBhcyBSZWFjdCBmcm9tIFwicmVhY3RcIjtcclxuaW1wb3J0ICogYXMgUmVhY3RET00gZnJvbSBcInJlYWN0LWRvbVwiO1xyXG5pbXBvcnQgKiBhcyBBQyBmcm9tIFwiYWRhcHRpdmVjYXJkc1wiO1xyXG5pbXBvcnQgeyBCdXR0b24sIEljb25CdXR0b24sIEljb25UeXBlLCBQcmltYXJ5QnV0dG9uLCBJU3R5bGUgfSBmcm9tIFwib2ZmaWNlLXVpLWZhYnJpYy1yZWFjdFwiO1xyXG5cclxuZXhwb3J0IGNvbnN0IGdldERpdiA9ICgpOiBIVE1MRGl2RWxlbWVudCA9PiBkb2N1bWVudC5jcmVhdGVFbGVtZW50KFwiZGl2XCIpO1xyXG5cclxuY29uc3Qgc2hhcmVkSW50ZXJuYWxSZW5kZXIgPSAocmVuZGVyUmVhY3Q6ICgpID0+IEpTWC5FbGVtZW50KTogSFRNTEVsZW1lbnQgPT4ge1xyXG4gICAgY29uc3QgZGl2ID0gZ2V0RGl2KCk7XHJcbiAgICBSZWFjdERPTS5yZW5kZXIocmVuZGVyUmVhY3QoKSwgZGl2KTtcclxuICAgIHJldHVybiBkaXY7XHJcbn07XHJcblxyXG5leHBvcnQgYWJzdHJhY3QgY2xhc3MgUmVhY3RDYXJkRWxlbWVudCBleHRlbmRzIEFDLkNhcmRFbGVtZW50IHtcclxuXHJcbiAgICBwcm90ZWN0ZWQgYWJzdHJhY3QgcmVuZGVyUmVhY3QoKTogSlNYLkVsZW1lbnQ7XHJcblxyXG4gICAgcHJvdGVjdGVkIGludGVybmFsUmVuZGVyKCk6IEhUTUxFbGVtZW50IHtcclxuICAgICAgICByZXR1cm4gc2hhcmVkSW50ZXJuYWxSZW5kZXIodGhpcy5yZW5kZXJSZWFjdCk7XHJcbiAgICB9XHJcbn1cclxuXHJcbmV4cG9ydCBhYnN0cmFjdCBjbGFzcyBSZWFjdENhcmRFbGVtZW50Q29udGFpbmVyIGV4dGVuZHMgQUMuQ29udGFpbmVyIHtcclxuXHJcbiAgICBwcm90ZWN0ZWQgYWJzdHJhY3QgcmVuZGVyUmVhY3QoKTogSlNYLkVsZW1lbnQ7XHJcblxyXG4gICAgcHJvdGVjdGVkIGludGVybmFsUmVuZGVyKCk6IEhUTUxFbGVtZW50IHtcclxuICAgICAgICByZXR1cm4gc2hhcmVkSW50ZXJuYWxSZW5kZXIodGhpcy5yZW5kZXJSZWFjdCk7XHJcbiAgICB9XHJcbn1cclxuXHJcbmNvbnN0IGlubGluZUJ1dHRvblJvb3RTdHlsZTogSVN0eWxlID0ge1xyXG4gICAgbWFyZ2luTGVmdDogOCxcclxufTtcclxuXHJcbmV4cG9ydCBhYnN0cmFjdCBjbGFzcyBSZWFjdElucHV0RWxlbWVudCBleHRlbmRzIEFDLklucHV0IHtcclxuXHJcbiAgICBwcml2YXRlIF92YWx1ZTogc3RyaW5nO1xyXG4gICAgcHJpdmF0ZSBfaW5saW5lQWN0aW9uOiBBQy5BY3Rpb247XHJcbiAgICBwcm90ZWN0ZWQgYWJzdHJhY3QgcmVuZGVyUmVhY3QoKTogSlNYLkVsZW1lbnQ7XHJcblxyXG4gICAgcHJvdGVjdGVkIGludGVybmFsUmVuZGVyKCk6IEhUTUxFbGVtZW50IHtcclxuICAgICAgICBjb25zdCBlbGVtZW50ID0gc2hhcmVkSW50ZXJuYWxSZW5kZXIodGhpcy5yZW5kZXJSZWFjdCk7XHJcbiAgICAgICAgZWxlbWVudC5zdHlsZS53aWR0aCA9IFwiMTAwJVwiO1xyXG4gICAgICAgIHJldHVybiBlbGVtZW50O1xyXG4gICAgfVxyXG5cclxuICAgIHByb3RlY3RlZCBvdmVycmlkZUludGVybmFsUmVuZGVyKCk6IEhUTUxFbGVtZW50IHtcclxuICAgICAgICBsZXQgaW5wdXRDb250cm9sID0gc3VwZXIub3ZlcnJpZGVJbnRlcm5hbFJlbmRlcigpO1xyXG5cclxuICAgICAgICBpZiAodGhpcy5faW5saW5lQWN0aW9uKSB7XHJcbiAgICAgICAgICAgIHRoaXMuaW5wdXRDb250cm9sQ29udGFpbmVyRWxlbWVudC5hcHBlbmRDaGlsZCh0aGlzLmJ1aWxkSW5saW5lQWN0aW9uQnV0dG9uKCkpO1xyXG4gICAgICAgIH1cclxuICAgICAgICByZXR1cm4gaW5wdXRDb250cm9sO1xyXG4gICAgfVxyXG5cclxuICAgIHByb3RlY3RlZCBoYW5kbGVDaGFuZ2UgPSAoZXZlbnQ6IFJlYWN0LkZvcm1FdmVudDxIVE1MSW5wdXRFbGVtZW50IHwgSFRNTFRleHRBcmVhRWxlbWVudD4sIG5ld1ZhbHVlPzogc3RyaW5nKSA9PiB7XHJcbiAgICAgICAgdGhpcy5fdmFsdWUgPSBuZXdWYWx1ZTtcclxuICAgIH1cclxuXHJcbiAgICBnZXQgdmFsdWUoKTogc3RyaW5nIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5fdmFsdWU7XHJcbiAgICB9XHJcblxyXG4gICAgc2V0IHZhbHVlKHZhbHVlOiBzdHJpbmcpIHtcclxuICAgICAgICB0aGlzLl92YWx1ZSA9IHZhbHVlO1xyXG4gICAgfVxyXG5cclxuICAgIGdldCBpbmxpbmVBY3Rpb24oKTogQUMuQWN0aW9uIHtcclxuICAgICAgICByZXR1cm4gdGhpcy5faW5saW5lQWN0aW9uO1xyXG4gICAgfVxyXG5cclxuICAgIHNldCBpbmxpbmVBY3Rpb24oYWN0aW9uOiBBQy5BY3Rpb24pIHtcclxuICAgICAgICB0aGlzLl9pbmxpbmVBY3Rpb24gPSBhY3Rpb247XHJcblxyXG4gICAgICAgIGlmICh0aGlzLl9pbmxpbmVBY3Rpb24pIHtcclxuICAgICAgICAgICAgdGhpcy5faW5saW5lQWN0aW9uLnNldFBhcmVudCh0aGlzKTtcclxuICAgICAgICB9XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBidWlsZElubGluZUFjdGlvbkJ1dHRvbiA9ICgpOiBIVE1MRWxlbWVudCA9PiB7XHJcbiAgICAgICAgcmV0dXJuIHNoYXJlZEludGVybmFsUmVuZGVyKFxyXG4gICAgICAgICAgICBBQy5pc051bGxPckVtcHR5KHRoaXMuaW5saW5lQWN0aW9uLmljb25VcmwpID9cclxuICAgICAgICAgICAgICAgIHRoaXMuYnVpbGRUZXh0T25seUlubGluZUFjdGlvbkFjdGlvbkJ1dHRvbiA6XHJcbiAgICAgICAgICAgICAgICB0aGlzLmlubGluZUljb25BY3Rpb25CdXR0b24pO1xyXG4gICAgfVxyXG5cclxuICAgIHByaXZhdGUgaW5saW5lQWN0aW9uQ2xpY2tIYW5kbGVyID0gKGU6IFJlYWN0Lk1vdXNlRXZlbnQ8QnV0dG9uPik6IHZvaWQgPT4ge1xyXG4gICAgICAgIGUuc3RvcFByb3BhZ2F0aW9uKCk7XHJcbiAgICAgICAgZS5wcmV2ZW50RGVmYXVsdCgpO1xyXG4gICAgICAgIHRoaXMuX2lubGluZUFjdGlvbi5leGVjdXRlKCk7XHJcbiAgICB9XHJcblxyXG4gICAgcHJpdmF0ZSBpbmxpbmVJY29uQWN0aW9uQnV0dG9uID0gKCk6IEpTWC5FbGVtZW50ID0+IChcclxuICAgICAgICA8SWNvbkJ1dHRvblxyXG4gICAgICAgICAgICBkZWZhdWx0PXt0cnVlfVxyXG4gICAgICAgICAgICB0ZXh0PXt0aGlzLl9pbmxpbmVBY3Rpb24udGl0bGV9XHJcbiAgICAgICAgICAgIGNsYXNzTmFtZT17dGhpcy5ob3N0Q29uZmlnLm1ha2VDc3NDbGFzc05hbWUoXCJhYy1pbmxpbmVBY3Rpb25CdXR0b25cIiwgXCJpY29uT25seVwiKX1cclxuICAgICAgICAgICAgc3R5bGVzPXt7XHJcbiAgICAgICAgICAgICAgICBpY29uOiB7XHJcbiAgICAgICAgICAgICAgICAgICAgaGVpZ2h0OiBgMTAwJWAsXHJcbiAgICAgICAgICAgICAgICB9LFxyXG4gICAgICAgICAgICAgICAgcm9vdDogaW5saW5lQnV0dG9uUm9vdFN0eWxlLFxyXG4gICAgICAgICAgICB9fVxyXG4gICAgICAgICAgICBpY29uUHJvcHM9e3tcclxuICAgICAgICAgICAgICAgIGljb25UeXBlOiBJY29uVHlwZS5pbWFnZSxcclxuICAgICAgICAgICAgICAgIGltYWdlUHJvcHM6IHtcclxuICAgICAgICAgICAgICAgICAgICBoZWlnaHQ6IFwiMTAwJVwiLFxyXG4gICAgICAgICAgICAgICAgICAgIHNyYzogdGhpcy5faW5saW5lQWN0aW9uLmljb25VcmwsXHJcbiAgICAgICAgICAgICAgICB9LFxyXG4gICAgICAgICAgICB9fVxyXG4gICAgICAgICAgICBvbkNsaWNrPXt0aGlzLmlubGluZUFjdGlvbkNsaWNrSGFuZGxlcn1cclxuICAgICAgICAvPlxyXG4gICAgKVxyXG5cclxuICAgIHByaXZhdGUgYnVpbGRUZXh0T25seUlubGluZUFjdGlvbkFjdGlvbkJ1dHRvbiA9ICgpOiBKU1guRWxlbWVudCA9PiAoXHJcbiAgICAgICAgPFByaW1hcnlCdXR0b25cclxuICAgICAgICAgICAgY2xhc3NOYW1lPXt0aGlzLmhvc3RDb25maWcubWFrZUNzc0NsYXNzTmFtZShcImFjLWlubGluZUFjdGlvbkJ1dHRvblwiLCBcInRleHRPbmx5XCIpfVxyXG4gICAgICAgICAgICB0ZXh0PXt0aGlzLl9pbmxpbmVBY3Rpb24udGl0bGV9XHJcbiAgICAgICAgICAgIG9uQ2xpY2s9e3RoaXMuaW5saW5lQWN0aW9uQ2xpY2tIYW5kbGVyfVxyXG4gICAgICAgICAgICBzdHlsZXM9e3tcclxuICAgICAgICAgICAgICAgIHJvb3Q6IGlubGluZUJ1dHRvblJvb3RTdHlsZSxcclxuICAgICAgICAgICAgfX1cclxuICAgICAgICAvPlxyXG4gICAgKVxyXG59XHJcblxyXG5leHBvcnQgY29uc3QgcmFpc2VQYXJzZUVycm9yID0gKGVycm9yOiBBQy5JVmFsaWRhdGlvbkVycm9yLCBlcnJvcnM6IEFycmF5PEFDLklWYWxpZGF0aW9uRXJyb3I+KSA9PiB7XHJcbiAgICBpZiAoZXJyb3JzKSB7XHJcbiAgICAgICAgZXJyb3JzLnB1c2goZXJyb3IpO1xyXG4gICAgfVxyXG5cclxuICAgIGlmIChBQy5BZGFwdGl2ZUNhcmQub25QYXJzZUVycm9yICE9IG51bGwpIHtcclxuICAgICAgICBBQy5BZGFwdGl2ZUNhcmQub25QYXJzZUVycm9yKGVycm9yKTtcclxuICAgIH1cclxufTtcclxuXHJcbmV4cG9ydCBjb25zdCBnZXRJbnRWYWx1ZSA9ICh2YWw6IGFueSwgZXJyb3JzPzogQUMuSVZhbGlkYXRpb25FcnJvcltdLCBkZWZhdWx0VmFsdWU6IG51bWJlciA9IHVuZGVmaW5lZCk6IG51bWJlciA9PiB7XHJcbiAgICB0cnkge1xyXG4gICAgICAgIHJldHVybiB2YWwgPyBwYXJzZUludCh2YWwsIDEwKSA6IGRlZmF1bHRWYWx1ZTtcclxuICAgIH0gY2F0Y2ggKGVycm9yKSB7XHJcbiAgICAgICAgcmFpc2VQYXJzZUVycm9yKHtcclxuICAgICAgICAgICAgZXJyb3I6IEFDLlZhbGlkYXRpb25FcnJvci5JbnZhbGlkUHJvcGVydHlWYWx1ZSxcclxuICAgICAgICAgICAgbWVzc2FnZTogZXJyb3IsXHJcbiAgICAgICAgfSwgZXJyb3JzKTtcclxuICAgIH1cclxufTtcclxuIiwibW9kdWxlLmV4cG9ydHMgPSBBZGFwdGl2ZUNhcmRzOyIsIm1vZHVsZS5leHBvcnRzID0gZmFicmljOyIsIm1vZHVsZS5leHBvcnRzID0gUmVhY3Q7IiwibW9kdWxlLmV4cG9ydHMgPSBSZWFjdERPTTsiXSwic291cmNlUm9vdCI6IiJ9