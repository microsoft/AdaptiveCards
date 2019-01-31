import { SettingsManager } from "./settings-manager";

export enum ToolboxOrientation {
    Horizontal,
    Vertical
}

export class Toolbox {
    private _renderedElement: HTMLElement;
    private _headerRootElement: HTMLElement;
    private _headerContentElement: HTMLElement;
    private _headerTitleElement: HTMLElement;
    private _headerIconElement: HTMLElement;
    private _headerStatusTextElement: HTMLElement;
    private _contentHost: HTMLElement;
    private _isExpanded: boolean = true;
    private _content: HTMLElement;
    private _stretch: boolean = false;
    private _orientation: ToolboxOrientation;
    private _isRestoring: boolean = false;

    private getDimensionSettingName(): string {
        return "Toolbox" + this.id + (this._orientation == ToolboxOrientation.Vertical ? "Height" : "Width");
    }

    private updateContent() {
        if (this._contentHost) {
            this._contentHost.innerHTML = "";

            if (this._content) {
                this._contentHost.appendChild(this._content);
            }
        }
    }

    private toggled() {
        if (this.onToggled) {
            this.onToggled(this);
        }
    }
    
    onToggled: (sender: Toolbox) => void;

    readonly id: string;
    readonly title: string;

    collapsedTabContainer: HTMLElement;

    constructor(id: string, title: string) {
        this.id = id;
        this.title = title;
    }

    render(orientation: ToolboxOrientation) {
        this._orientation = orientation;

        this._renderedElement = document.createElement("div");
        /*
        this._renderedElement.style.width = "100%";
        this._renderedElement.style.height = "100%";
        */
        this._renderedElement.style.overflow = "auto";
        this._renderedElement.style.display = "flex";
        this._renderedElement.style.flexDirection = "column";

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

        this._contentHost = document.createElement("div");
        this._contentHost.style.overflow = "auto";

        this._renderedElement.append(this._headerRootElement, this._contentHost);

        this.updateContent();
    }

    collapse() {
        if (this._isExpanded) {
            this._headerIconElement.classList.add("acd-icon-header-collapsed");
            this._headerIconElement.classList.remove("acd-icon-header-expanded");
            this._headerStatusTextElement.classList.add("acd-hidden");

            if (this.collapsedTabContainer) {
                this._renderedElement.removeChild(this._headerRootElement);
                this.collapsedTabContainer.appendChild(this._headerRootElement);
            }

            this._isExpanded = false;

            this.toggled();
        }
    }

    expand() {
        if (!this._isExpanded) {
            this._headerIconElement.classList.add("acd-icon-header-expanded");
            this._headerIconElement.classList.remove("acd-icon-header-collapsed");
            this._headerStatusTextElement.classList.remove("acd-hidden");

            if (this.collapsedTabContainer) {
                this.collapsedTabContainer.removeChild(this._headerRootElement);
                this._renderedElement.insertBefore(this._headerRootElement, this._renderedElement.firstChild);
            }

            this._isExpanded = true;

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
        if (!this._isRestoring) {
            SettingsManager.trySaveSetting("Toolbox" + this.id + "IsExpanded", this.isExpanded.toString());

            SettingsManager.trySaveSetting(
                this.getDimensionSettingName(),
                this.orientation == ToolboxOrientation.Vertical ? this.renderedElement.style.height : this.renderedElement.style.width);
        }
    }

    restoreState() {
        if (this.renderedElement && !this._isRestoring) {
            this._isRestoring = true;

            try {
                let dimensionSetting = SettingsManager.tryLoadStringSetting(this.getDimensionSettingName());

                if (dimensionSetting.succeeded && dimensionSetting.value != undefined && dimensionSetting.value != "") {
                    if (this.orientation == ToolboxOrientation.Vertical) {
                        this.renderedElement.style.height = dimensionSetting.value;
                    }
                    else {
                        this.renderedElement.style.width = dimensionSetting.value;
                    }
                }

                let isExpandedSetting = SettingsManager.tryLoadBooleanSetting("Toolbox" + this.id + "IsExpanded", true);
        
                if (isExpandedSetting.succeeded) {
                    if (isExpandedSetting.value) {
                        this.expand();
                    }
                    else {
                        this.collapse();
                    }
                }
            }
            finally {
                this._isRestoring = false;
            }
        }
    }

    get orientation(): ToolboxOrientation {
        return this._orientation;
    }

    get renderedElement(): HTMLElement {
        return this._renderedElement;
    }

    get content(): HTMLElement {
        return this._content;
    }

    set content(value: HTMLElement) {
        this._content = value;

        this.updateContent();
    }

    get isExpanded(): boolean {
        return this._isExpanded;
    }

    get stretch(): boolean {
        return this._stretch;
    }

    set stretch(value: boolean) {
        this._stretch = value;

        if (this._stretch) {
            this.renderedElement.style.flex = "1 1 auto";
        }
        else {
            this.renderedElement.style.flex = "0 0 auto";
        }
    }
}