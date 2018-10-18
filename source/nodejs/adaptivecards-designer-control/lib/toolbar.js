"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var adaptivecards_controls_1 = require("adaptivecards-controls");
var ToolbarElement = /** @class */ (function () {
    function ToolbarElement() {
        this._renderedElement = undefined;
    }
    ToolbarElement.prototype.internalUpdateLayout = function () {
        // Do nothing in base implementation
    };
    ToolbarElement.prototype.updateLayout = function () {
        if (this._renderedElement) {
            this.internalUpdateLayout();
        }
    };
    ToolbarElement.prototype.render = function () {
        this._renderedElement = this.internalRender();
        this.updateLayout();
        return this._renderedElement;
    };
    Object.defineProperty(ToolbarElement.prototype, "renderedElement", {
        get: function () {
            return this._renderedElement;
        },
        enumerable: true,
        configurable: true
    });
    return ToolbarElement;
}());
exports.ToolbarElement = ToolbarElement;
var ToolbarSeparator = /** @class */ (function (_super) {
    __extends(ToolbarSeparator, _super);
    function ToolbarSeparator() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ToolbarSeparator.prototype.internalRender = function () {
        var element = document.createElement("div");
        element.className = "acd-toolbar-separator";
        return element;
    };
    return ToolbarSeparator;
}(ToolbarElement));
exports.ToolbarSeparator = ToolbarSeparator;
var ToolbarLabel = /** @class */ (function (_super) {
    __extends(ToolbarLabel, _super);
    function ToolbarLabel(text) {
        var _this = _super.call(this) || this;
        _this._text = undefined;
        _this.text = text;
        return _this;
    }
    ToolbarLabel.prototype.internalUpdateLayout = function () {
        this.renderedElement.innerText = this._text;
    };
    ToolbarLabel.prototype.internalRender = function () {
        var element = document.createElement("span");
        element.className = "acd-toolbar-label";
        return element;
    };
    Object.defineProperty(ToolbarLabel.prototype, "text", {
        get: function () {
            return this._text;
        },
        set: function (value) {
            this._text = value;
            this.updateLayout();
        },
        enumerable: true,
        configurable: true
    });
    return ToolbarLabel;
}(ToolbarElement));
exports.ToolbarLabel = ToolbarLabel;
var ToolbarButton = /** @class */ (function (_super) {
    __extends(ToolbarButton, _super);
    function ToolbarButton(caption, iconClass, onClick) {
        if (onClick === void 0) { onClick = null; }
        var _this = _super.call(this) || this;
        _this._displayCaption = true;
        _this._iconClass = undefined;
        _this._toolTip = undefined;
        _this._isEnabled = true;
        _this.caption = caption;
        _this.iconClass = iconClass;
        _this.onClick = onClick;
        return _this;
    }
    ToolbarButton.prototype.clicked = function () {
        if (this.onClick) {
            this.onClick(this);
        }
    };
    ToolbarButton.prototype.internalUpdateLayout = function () {
        this.renderedElement.className = "acd-toolbar-button";
        this.renderedElement.disabled = !this.isEnabled;
        if (this.iconClass) {
            this.renderedElement.classList.add(this.iconClass);
        }
        if (!this.displayCaption) {
            this.renderedElement.classList.add("acd-toolbar-button-iconOnly");
            this.renderedElement.innerText = "";
        }
        else {
            this.renderedElement.innerText = this.caption;
        }
        this.renderedElement.title = this.toolTip ? this.toolTip : "";
    };
    ToolbarButton.prototype.internalRender = function () {
        var _this = this;
        var element = document.createElement("button");
        element.onclick = function (e) {
            _this.clicked();
        };
        return element;
    };
    Object.defineProperty(ToolbarButton.prototype, "caption", {
        get: function () {
            return this._caption;
        },
        set: function (value) {
            this._caption = value;
            this.updateLayout();
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ToolbarButton.prototype, "displayCaption", {
        get: function () {
            return this._displayCaption;
        },
        set: function (value) {
            this._displayCaption = value;
            this.updateLayout();
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ToolbarButton.prototype, "iconClass", {
        get: function () {
            return this._iconClass;
        },
        set: function (value) {
            this._iconClass = value;
            this.updateLayout();
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ToolbarButton.prototype, "toolTip", {
        get: function () {
            return this._toolTip;
        },
        set: function (value) {
            this._toolTip = value;
            this.updateLayout();
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ToolbarButton.prototype, "isEnabled", {
        get: function () {
            return this._isEnabled;
        },
        set: function (value) {
            this._isEnabled = value;
            this.updateLayout();
        },
        enumerable: true,
        configurable: true
    });
    return ToolbarButton;
}(ToolbarElement));
exports.ToolbarButton = ToolbarButton;
var ToolbarChoicePicker = /** @class */ (function (_super) {
    __extends(ToolbarChoicePicker, _super);
    function ToolbarChoicePicker() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.choices = [];
        return _this;
    }
    ToolbarChoicePicker.prototype.internalRender = function () {
        var _this = this;
        this._dropDown = new adaptivecards_controls_1.DropDown();
        for (var _i = 0, _a = this.choices; _i < _a.length; _i++) {
            var choice = _a[_i];
            var dropDownItem = new adaptivecards_controls_1.DropDownItem(choice.value, choice.name);
            this._dropDown.items.add(dropDownItem);
        }
        this._dropDown.selectedIndex = 0;
        this._dropDown.onValueChanged = function (sender) {
            if (_this.onChanged) {
                _this.onChanged(_this);
            }
        };
        var pickerElement = document.createElement("div");
        this._dropDown.attach(pickerElement);
        var pickerContainerElement = document.createElement("div");
        pickerContainerElement.className = "acd-toolbar-choicePicker";
        pickerContainerElement.appendChild(pickerElement);
        return pickerContainerElement;
    };
    Object.defineProperty(ToolbarChoicePicker.prototype, "value", {
        get: function () {
            return this._dropDown.value.key;
        },
        enumerable: true,
        configurable: true
    });
    return ToolbarChoicePicker;
}(ToolbarElement));
exports.ToolbarChoicePicker = ToolbarChoicePicker;
var Toolbar = /** @class */ (function () {
    function Toolbar() {
        this._elements = [];
    }
    Toolbar.prototype.attachTo = function (element) {
        this._attachedTo = element;
        this._attachedTo.className = "acd-toolbar";
        this._attachedTo.innerHTML = "";
        for (var _i = 0, _a = this._elements; _i < _a.length; _i++) {
            var toolbarElement = _a[_i];
            var renderedToolbarElement = toolbarElement.render();
            this._attachedTo.appendChild(renderedToolbarElement);
        }
    };
    Toolbar.prototype.addElement = function (element) {
        this._elements.push(element);
    };
    return Toolbar;
}());
exports.Toolbar = Toolbar;
//# sourceMappingURL=toolbar.js.map