import { Splitter } from "./splitter";
import { Toolbox, ToolboxOrientation } from "./tool-box";
import { SettingsManager } from "./settings-manager";

export enum SidePanelAlignment {
    Top,
    Right,
    Bottom,
    Left
}

class ToolboxInfo {
    private _splitter: Splitter;

    private resizeEnded() {
        if (this.onResizeEnded) {
            this.onResizeEnded(this);
        }
    }

    private resized() {
        if (this.onResized) {
            this.onResized(this);
        }
    }

    onToggled: (sender: ToolboxInfo) => void;
    onResizeEnded: (sender: ToolboxInfo) => void;
    onResized: (sender: ToolboxInfo) => void;

    showSplitter() {
        if (this.splitter) {
            this.splitter.attachedTo.classList.remove("acd-hidden");
        }
    }

    hideSplitter() {
        if (this.splitter) {
            this.splitter.attachedTo.classList.add("acd-hidden");
        }
    }

    constructor(readonly toolbox: Toolbox) {
        toolbox.onToggled = (sender: Toolbox) => {
            if (sender.isExpanded) {
                this.showSplitter();

                this.toolbox.renderedElement.classList.remove("acd-hidden");
            }
            else {
                this.hideSplitter();

                this.toolbox.renderedElement.classList.add("acd-hidden");
            }

            if (this.onToggled) {
                this.onToggled(this);
            }
        }
    }

    get splitter(): Splitter {
        return this._splitter;
    }

    set splitter(value: Splitter) {
        this._splitter = value;

        this._splitter.onResizeEnded = (sender: Splitter) => {
            this.resizeEnded();
        }

        this._splitter.onResized = (sender: Splitter) => {
            this.resized();
        }
    }
}

export class SidePanel {
    private _attachedTo: HTMLElement;
    private _alignment: SidePanelAlignment;
    private _collapsedTabContainer: HTMLElement;
    private _contentHost: HTMLElement;
    private _toolboxes: ToolboxInfo[] = [];
    private _isRestoring: boolean = false;

    private updateLayout() {
        let expandedToolboxCount = 0;

        for (let toolboxInfo of this._toolboxes) {
            if (toolboxInfo.toolbox.isExpanded) {
                expandedToolboxCount++;

                if (expandedToolboxCount == 1) {
                    toolboxInfo.hideSplitter();
                    toolboxInfo.toolbox.stretch = true;
                }
                else {
                    toolboxInfo.showSplitter();
                    toolboxInfo.toolbox.stretch = false;
                }
            }
        }

        if (expandedToolboxCount > 0) {
            this._attachedTo.classList.remove("acd-hidden");
        }
        else {
            this._attachedTo.classList.add("acd-hidden");
        }
    }

    private computeToolboxSize(toolbox: Toolbox) {
        let boundingRect = this._attachedTo.getBoundingClientRect();
        let toolboxBoundingRect = toolbox.renderedElement.getBoundingClientRect();

        if (this.isVertical) {
            toolbox.renderedElement.style.height = (100 / boundingRect.height * toolboxBoundingRect.height) + "%";
        }
        else {
            toolbox.renderedElement.style.width = (100 / boundingRect.width * toolboxBoundingRect.width) + "%";
        }
    }

    private resized() {
        if (this.onResized) {
            this.onResized(this);
        }

        this.saveState();
    }

    private toolboxResized(toolbox: Toolbox) {
        if (this.onToolboxResized) {
            this.onToolboxResized(this, toolbox);
        }

        this.saveState();
    }

    private toolboxExpandedOrCollapsed(toolbox: Toolbox) {
        if (this.onToolboxExpandedOrCollapsed) {
            this.onToolboxExpandedOrCollapsed(this, toolbox);
        }

        this.saveState();
    }

    private getDimensionSettingName(): string {
        return this.id + (this.isVertical ? "Height" : "Width");
    }

    private get isVertical(): boolean {
        return this._alignment == SidePanelAlignment.Right || this._alignment == SidePanelAlignment.Left;
    }

    onResized: (sender: SidePanel) => void;
    onToolboxResized: (sender: SidePanel, toolbox: Toolbox) => void;
    onToolboxExpandedOrCollapsed: (sender: SidePanel, toolbox: Toolbox) => void;

    readonly id;

    size?: number;
    isResizable: boolean = true;

    addToolbox(toolbox: Toolbox) {
        let toolboxInfo = new ToolboxInfo(toolbox);
        toolboxInfo.onToggled = (sender: ToolboxInfo) => {
            this.updateLayout();
            this.toolboxExpandedOrCollapsed(toolboxInfo.toolbox);
        }
        toolboxInfo.onResizeEnded = (sender: ToolboxInfo) => {
            this.computeToolboxSize(sender.toolbox);
            this.toolboxResized(sender.toolbox);
        }
        toolboxInfo.onResized = (sender: ToolboxInfo) => {
            this.toolboxResized(sender.toolbox);
        }

        this._toolboxes.push(toolboxInfo);
    }

    attachTo(attachTo: HTMLElement) {
        this._attachedTo = attachTo;
        this._attachedTo.style.position = "relative";

        this._contentHost = document.createElement("div");
        this._contentHost.style.display = "flex";
        this._contentHost.style.overflow = "hidden";
        this._contentHost.style.flex = "1 1 auto";
        this._contentHost.style.position = "relative";

        if (this.isVertical) {
            this._contentHost.style.flexDirection = "column";
        }
        else {
            this._contentHost.style.flexDirection = "row";
        }

        for (let i = 0; i < this._toolboxes.length; i++) {
            let toolboxInfo = this._toolboxes[i];
            toolboxInfo.toolbox.render(
                this.isVertical ? ToolboxOrientation.Vertical : ToolboxOrientation.Horizontal,
                this._collapsedTabContainer);

            if (i > 0) {
                let splitterElement = document.createElement("div");

                if (this.isVertical) {
                    splitterElement.className = "acd-horizontal-splitter";

                    toolboxInfo.toolbox.renderedElement.style.height = (100 / this._toolboxes.length) + "%";
                }
                else {
                    splitterElement.className = "acd-vertical-splitter";

                    toolboxInfo.toolbox.renderedElement.style.width = (100 / this._toolboxes.length) + "%";
                }

                toolboxInfo.toolbox.renderedElement.appendChild(splitterElement);

                toolboxInfo.splitter = new Splitter(
                    splitterElement,
                    toolboxInfo.toolbox.renderedElement,
                    !this.isVertical);
            }

            this._contentHost.appendChild(toolboxInfo.toolbox.renderedElement);
        }

        let splitterElement: HTMLElement = null;

        if (this.isResizable) {
            splitterElement = document.createElement("div");
            splitterElement.className = this.isVertical ? "acd-vertical-splitter" : "acd-horizontal-splitter";

            let splitter = new Splitter(
                splitterElement,
                this._attachedTo,
                this.isVertical,
                this._alignment == SidePanelAlignment.Left || this._alignment == SidePanelAlignment.Top);
            splitter.onResized = (splitter: Splitter) => {
                this.resized();
            }
        }

        this._attachedTo.innerHTML = "";
        this._attachedTo.style.display = "flex";

        if (this.isVertical) {
            if (this.size) {
                this._attachedTo.style.width = this.size + "px";
            }

            this._attachedTo.style.flexDirection = "row";
            this._attachedTo.style.overflowX = "hidden";
        }
        else {
            if (this.size) {
                this._attachedTo.style.height = this.size + "px";
            }

            this._attachedTo.style.flexDirection = "column";
            this._attachedTo.style.overflowY = "hidden";
        }

        if (this._alignment == SidePanelAlignment.Right || this._alignment == SidePanelAlignment.Bottom) {
            if (splitterElement) {
                this._attachedTo.appendChild(splitterElement);
            }

            this._attachedTo.appendChild(this._contentHost);
        }
        else {
            this._attachedTo.append(this._contentHost);

            if (splitterElement) {
                this._attachedTo.appendChild(splitterElement);
            }
        }

        this.restoreState();
        this.updateLayout();
    }

    constructor(id: string, alignment: SidePanelAlignment, collapsedTabContainer: HTMLElement) {
        this.id = id;
        this._alignment = alignment;
        this._collapsedTabContainer = collapsedTabContainer;
    }

    saveState() {
        if (!this._isRestoring) {
            SettingsManager.trySaveSetting(
                this.getDimensionSettingName(),
                this.isVertical ? this._attachedTo.style.width : this._attachedTo.style.height);

            for (let toolboxInfo of this._toolboxes) {
                toolboxInfo.toolbox.saveState();
            }
        }
    }

    restoreState() {
        if (this._attachedTo && !this._isRestoring) {
            this._isRestoring = true;

            try {
                let dimensionSetting = SettingsManager.tryLoadStringSetting(this.getDimensionSettingName());

                if (dimensionSetting.succeeded && dimensionSetting.value != undefined && dimensionSetting.value != "") {
                    if (this.isVertical) {
                        this._attachedTo.style.width = dimensionSetting.value;
                    }
                    else {
                        this._attachedTo.style.height = dimensionSetting.value;
                    }
                }

                for (let toolboxInfo of this._toolboxes) {
                    toolboxInfo.toolbox.restoreState();
                }

                this.updateLayout();
                this.resized();
            }
            finally {
                this._isRestoring = false;
            }
        }
    }

    get contentHost(): HTMLElement {
        return this._contentHost;
    }
}
