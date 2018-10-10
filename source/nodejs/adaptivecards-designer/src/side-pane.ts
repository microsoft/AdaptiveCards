import { SettingsManager } from "./settings-manager";

export enum SidePaneOrientation {
    Horizontal,
    Vertical
}

export class SidePane {
    private _renderedElement: HTMLElement = null;
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
    
    readonly id: string;
    readonly title: string;
    readonly targetElementSelector: string;
    readonly collapsedTabContainer: HTMLElement = null;
    // readonly collapsedTabClass: string = null;
    readonly orientation: SidePaneOrientation = SidePaneOrientation.Vertical;

    onToggled: (sender: SidePane) => void;

    constructor(
        id: string,
        title: string,
        targetElementSelector: string,
        collapsedTabContainer: HTMLElement,
        orientation: SidePaneOrientation = SidePaneOrientation.Vertical) {
        // collapsedTabClass: string = null) {
        this.id = id;
        this.title = title;
        this.targetElementSelector = targetElementSelector;
        this.collapsedTabContainer = collapsedTabContainer;
        // this.collapsedTabClass = collapsedTabClass;
        this.orientation = orientation;
    }

    render() {
        this._renderedElement = document.createElement("div");
        this._renderedElement.classList.add(this.targetElementSelector);

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

        this._renderedElement.insertBefore(this._headerRootElement, this._renderedElement.firstChild);
        
        let heightSetting = SettingsManager.tryLoadNumberSetting(this.getDimensionSettingName());

        if (heightSetting.succeeded && heightSetting.value != undefined) {
            this._renderedElement.style.height = heightSetting.value + "px";
        }
    
        let isExpandedSetting = SettingsManager.tryLoadBooleanSetting(this.id + "IsExpanded", true);
    
        if (isExpandedSetting.succeeded && !isExpandedSetting.value) {
            this.toggle();
        }
    }

    toggle() {
        if (this._renderedElement) {
            if (this._isExpanded) {
                this._headerIconElement.classList.add("acd-icon-header-collapsed");
                this._headerIconElement.classList.remove("acd-icon-header-expanded");
                this._headerStatusTextElement.classList.add("acd-hidden");

                if (this.collapsedTabContainer) {
                    this._renderedElement.removeChild(this._headerRootElement);
                    this.collapsedTabContainer.appendChild(this._headerRootElement);
                }
            }
            else {
                this._headerIconElement.classList.add("acd-icon-header-expanded");
                this._headerIconElement.classList.remove("acd-icon-header-collapsed");
                this._headerStatusTextElement.classList.remove("acd-hidden");

                if (this.collapsedTabContainer) {
                    this.collapsedTabContainer.removeChild(this._headerRootElement);
                    this._renderedElement.insertBefore(this._headerRootElement, this._renderedElement.firstChild);
                }
            }

            this._isExpanded = !this._isExpanded;

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

            if (this.onToggled) {
                this.onToggled(this);
            }
        }
    }

    getHeaderBoundingRect(): ClientRect {
        return this._headerRootElement.getBoundingClientRect();
    }

    saveState() {
        SettingsManager.trySaveSetting(this.id + "IsExpanded", this.isExpanded.toString());

        let boundingRect = this.renderedElement.getBoundingClientRect();

        SettingsManager.trySaveSetting(
            this.getDimensionSettingName(),
            (this.orientation == SidePaneOrientation.Vertical ? boundingRect.width : boundingRect.height).toString());
    }

    get content(): HTMLElement {
        return this._content;
    }

    set content(value: HTMLElement) {
        if (this._content) {
            this._renderedElement.removeChild(this._content);
        }

        this._content = value;

        if (this._content) {
            this._renderedElement.appendChild(this._content);
        }
    }

    get isExpanded(): boolean {
        return this._isExpanded;
    }

    get renderedElement(): HTMLElement {
        return this._renderedElement;
    }
}