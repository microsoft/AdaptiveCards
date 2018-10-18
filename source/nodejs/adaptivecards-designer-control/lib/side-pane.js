"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var settings_manager_1 = require("./settings-manager");
var SidePaneOrientation;
(function (SidePaneOrientation) {
    SidePaneOrientation[SidePaneOrientation["Horizontal"] = 0] = "Horizontal";
    SidePaneOrientation[SidePaneOrientation["Vertical"] = 1] = "Vertical";
})(SidePaneOrientation = exports.SidePaneOrientation || (exports.SidePaneOrientation = {}));
var SidePane = /** @class */ (function () {
    function SidePane(attachedTo, collapsedTabContainer, id, title, targetElementSelector, orientation) {
        if (orientation === void 0) { orientation = SidePaneOrientation.Vertical; }
        var _this = this;
        this._isExpanded = true;
        this.attachedTo = null;
        this.collapsedTabContainer = null;
        this.orientation = SidePaneOrientation.Vertical;
        this.attachedTo = attachedTo;
        this.collapsedTabContainer = collapsedTabContainer;
        this.id = id;
        this.title = title;
        this.targetElementSelector = targetElementSelector;
        this.orientation = orientation;
        this.attachedTo.classList.add(this.targetElementSelector);
        this._headerRootElement = document.createElement("div");
        this._headerRootElement.innerHTML = "";
        this._headerRootElement.className = "acd-sidePane-header";
        this._headerContentElement = document.createElement("div");
        this._headerContentElement.className = "acd-sidePane-header-content";
        this._headerTitleElement = document.createElement("span");
        this._headerTitleElement.className = "acd-sidePane-header-title";
        this._headerTitleElement.innerText = this.title;
        this._headerContentElement.appendChild(this._headerTitleElement);
        var expandCollapseElement = document.createElement("span");
        expandCollapseElement.className = "acd-sidePane-header-expandCollapseButton";
        this._headerIconElement = document.createElement("span");
        this._headerIconElement.classList.add("acd-icon", "acd-icon-header-expanded");
        expandCollapseElement.appendChild(this._headerIconElement);
        this._headerStatusTextElement = document.createElement("span");
        this._headerStatusTextElement.className = "acd-sidePane-header-status";
        this._headerStatusTextElement.innerText = "Hide";
        expandCollapseElement.appendChild(this._headerStatusTextElement);
        expandCollapseElement.onmousedown = function (e) {
            e.preventDefault();
            return true;
        };
        expandCollapseElement.onclick = function (e) {
            _this.toggle();
            e.preventDefault();
            return true;
        };
        this._headerContentElement.appendChild(expandCollapseElement);
        this._headerRootElement.appendChild(this._headerContentElement);
        this.attachedTo.insertBefore(this._headerRootElement, this.attachedTo.firstChild);
        var heightSetting = settings_manager_1.SettingsManager.tryLoadNumberSetting(this.getDimensionSettingName());
        if (heightSetting.succeeded && heightSetting.value != undefined) {
            this.attachedTo.style.height = heightSetting.value + "px";
        }
        var isExpandedSetting = settings_manager_1.SettingsManager.tryLoadBooleanSetting(this.id + "IsExpanded", true);
        if (isExpandedSetting.succeeded && !isExpandedSetting.value) {
            this.toggle();
        }
    }
    SidePane.prototype.getDimensionSettingName = function () {
        return this.id + (this.orientation == SidePaneOrientation.Vertical ? "Height" : "Width");
    };
    SidePane.prototype.updateLayout = function () {
        if (this.orientation == SidePaneOrientation.Vertical) {
            this._headerRootElement.classList.toggle("rotated90DegreesCounterClockwise", !this._isExpanded);
            this._headerContentElement.classList.toggle("rotated90DegreesCounterClockwise", !this._isExpanded);
        }
        if (this.targetElementSelector) {
            var targetNodes = document.getElementsByClassName(this.targetElementSelector);
            for (var i = 0; i < targetNodes.length; i++) {
                targetNodes[i].classList.toggle("acd-hidden", !this._isExpanded);
            }
        }
    };
    SidePane.prototype.toggled = function () {
        if (this.onToggled) {
            this.onToggled(this);
        }
    };
    SidePane.prototype.collapse = function () {
        if (this.attachedTo && this._isExpanded) {
            this._headerIconElement.classList.add("acd-icon-header-collapsed");
            this._headerIconElement.classList.remove("acd-icon-header-expanded");
            this._headerStatusTextElement.classList.add("acd-hidden");
            if (this.collapsedTabContainer) {
                this.attachedTo.removeChild(this._headerRootElement);
                this.collapsedTabContainer.appendChild(this._headerRootElement);
            }
            this._isExpanded = false;
            this.updateLayout();
            this.toggled();
        }
    };
    SidePane.prototype.expand = function () {
        if (this.attachedTo && !this._isExpanded) {
            this._headerIconElement.classList.add("acd-icon-header-expanded");
            this._headerIconElement.classList.remove("acd-icon-header-collapsed");
            this._headerStatusTextElement.classList.remove("acd-hidden");
            if (this.collapsedTabContainer) {
                this.collapsedTabContainer.removeChild(this._headerRootElement);
                this.attachedTo.insertBefore(this._headerRootElement, this.attachedTo.firstChild);
            }
            this._isExpanded = true;
            this.updateLayout();
            this.toggled();
        }
    };
    SidePane.prototype.toggle = function () {
        if (this.isExpanded) {
            this.collapse();
        }
        else {
            this.expand();
        }
    };
    SidePane.prototype.getHeaderBoundingRect = function () {
        return this._headerRootElement.getBoundingClientRect();
    };
    SidePane.prototype.saveState = function () {
        settings_manager_1.SettingsManager.trySaveSetting(this.id + "IsExpanded", this.isExpanded.toString());
        var boundingRect = this.attachedTo.getBoundingClientRect();
        settings_manager_1.SettingsManager.trySaveSetting(this.getDimensionSettingName(), (this.orientation == SidePaneOrientation.Vertical ? boundingRect.width : boundingRect.height).toString());
    };
    Object.defineProperty(SidePane.prototype, "content", {
        get: function () {
            return this._content;
        },
        set: function (value) {
            if (this._content) {
                this.attachedTo.removeChild(this._content);
            }
            this._content = value;
            if (this._content) {
                this.attachedTo.appendChild(this._content);
            }
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(SidePane.prototype, "isExpanded", {
        get: function () {
            return this._isExpanded;
        },
        enumerable: true,
        configurable: true
    });
    return SidePane;
}());
exports.SidePane = SidePane;
//# sourceMappingURL=side-pane.js.map