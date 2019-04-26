// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { SettingsManager } from "./settings-manager";

export enum SidePaneOrientation {
    Horizontal,
    Vertical
}

export class SidePane {
    private _headerRootElement: HTMLElement;
    private _headerContentElement: HTMLElement;
    private _headerTitleElement: HTMLElement;
    private _headerIconElement: HTMLElement;
    private _headerStatusTextElement: HTMLElement;
    private _isExpanded: boolean = true;
    private _content: HTMLElement;

    private getDimensionSettingName(): string {
        return this.id + (this.orientation == SidePaneOrientation.Vertical ? "Height" : "Width");
    }

    private updateLayout() {
        if (this.orientation == SidePaneOrientation.Vertical) {
            this._headerRootElement.classList.toggle("rotated90DegreesCounterClockwise", !this._isExpanded);
            this._headerContentElement.classList.toggle("rotated90DegreesCounterClockwise", !this._isExpanded);
        }

        if (this.targetElementSelector) {
            let targetNodes = document.getElementsByClassName(this.targetElementSelector);

            for (let i = 0; i < targetNodes.length; i++) {
                (<HTMLElement>targetNodes[i]).classList.toggle("acd-hidden", !this._isExpanded);
            }
        }
    }

    private toggled() {
        if (this.onToggled) {
            this.onToggled(this);
        }
    }

    readonly attachedTo: HTMLElement = null;
    readonly id: string;
    readonly title: string;
    readonly targetElementSelector: string;
    readonly collapsedTabContainer: HTMLElement = null;
    readonly orientation: SidePaneOrientation = SidePaneOrientation.Vertical;

    onToggled: (sender: SidePane) => void;

    constructor(
        attachedTo: HTMLElement,
        collapsedTabContainer: HTMLElement,
        id: string,
        title: string,
        targetElementSelector: string,
        orientation: SidePaneOrientation = SidePaneOrientation.Vertical) {
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

        let expandCollapseElement = document.createElement("span");
        expandCollapseElement.className = "acd-sidePane-header-expandCollapseButton";

        this._headerIconElement = document.createElement("span")
        this._headerIconElement.classList.add("acd-icon", "acd-icon-header-expanded");

        expandCollapseElement.appendChild(this._headerIconElement);

        this._headerStatusTextElement = document.createElement("span");
        this._headerStatusTextElement.className = "acd-sidePane-header-status";
        this._headerStatusTextElement.innerText = "Hide";

        expandCollapseElement.appendChild(this._headerStatusTextElement);

        expandCollapseElement.onmousedown = (e) => {
            e.preventDefault();

            return true;
        }

        expandCollapseElement.onclick = (e) => {
            this.toggle();

            e.preventDefault();

            return true;
        }

        this._headerContentElement.appendChild(expandCollapseElement);
        this._headerRootElement.appendChild(this._headerContentElement);

        this.attachedTo.insertBefore(this._headerRootElement, this.attachedTo.firstChild);

        let dimensionSetting = SettingsManager.tryLoadNumberSetting(this.getDimensionSettingName());

        if (dimensionSetting.succeeded && dimensionSetting.value != undefined) {
            if (this.orientation == SidePaneOrientation.Vertical) {
                this.attachedTo.style.width = dimensionSetting.value + "px";
            }
            else {
                this.attachedTo.style.height = dimensionSetting.value + "px";
            }
        }

        let isExpandedSetting = SettingsManager.tryLoadBooleanSetting(this.id + "IsExpanded", true);

        if (isExpandedSetting.succeeded && !isExpandedSetting.value) {
            this.toggle();
        }
    }

    collapse() {
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
    }

    expand() {
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
    }

    toggle() {
        if (this.isExpanded) {
            this.collapse();
        }
        else {
            this.expand();
        }
    }

    getHeaderBoundingRect(): ClientRect {
        return this._headerRootElement.getBoundingClientRect();
    }

    saveState() {
        SettingsManager.trySaveSetting(this.id + "IsExpanded", this.isExpanded.toString());

        let boundingRect = this.attachedTo.getBoundingClientRect();

        SettingsManager.trySaveSetting(
            this.getDimensionSettingName(),
            (this.orientation == SidePaneOrientation.Vertical ? boundingRect.width : boundingRect.height).toString());
    }

    get content(): HTMLElement {
        return this._content;
    }

    set content(value: HTMLElement) {
        if (this._content) {
            this.attachedTo.removeChild(this._content);
        }

        this._content = value;

        if (this._content) {
            this.attachedTo.appendChild(this._content);
        }
    }

    get isExpanded(): boolean {
        return this._isExpanded;
    }
}
