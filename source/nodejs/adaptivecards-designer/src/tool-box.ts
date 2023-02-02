import { SettingsManager } from "./settings-manager";
import { Constants } from "adaptivecards-controls";

export interface IToolboxCommand {
    title: string;
    iconClass: string;
    execute: (sender: IToolboxCommand) => void;
}

export enum ToolboxOrientation {
    Horizontal,
    Vertical
}

export class Toolbox {
    private _renderedElement: HTMLElement;
    private _expandedStateHeaderRootElement: HTMLElement;
    private _expandedStateButtonElement: HTMLElement;
    private _collapsedStateHeaderRootElement: HTMLElement;
    private _collapsedStateButtonElement: HTMLElement;
    private _customCommandsHost: HTMLElement;
    private _contentHost: HTMLElement;
    private _isExpanded: boolean = true;
    private _content: HTMLElement;
    private _stretch: boolean = false;
    private _orientation: ToolboxOrientation;
    private _isRestoring: boolean = false;
    private _collapsedTabContainer: HTMLElement;
    private _isVisible = true;

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

    private toggled(saveState: boolean = true) {
        if (this.onToggled) {
            this.onToggled(this, saveState);
        }
    }

    private updateVisibility() {
        if (this._collapsedTabContainer) {
            if (!this._isVisible) {
                this.hideToolbox();
            } else {
                this._collapsedStateHeaderRootElement.classList.remove("acd-hidden");
                this.restoreState();
            }
        }
    }

    private hideToolbox() {
        if (this.isExpanded) {
            this.collapse(false);
        }
        this._collapsedStateHeaderRootElement.classList.add("acd-hidden");
    }

    onToggled: (sender: Toolbox, saveState?: boolean) => void;

    readonly id: string;
    readonly title: string;

    commands: Array<IToolboxCommand> = null;

    constructor(id: string, title: string) {
        this.id = id;
        this.title = title;
    }

    render(orientation: ToolboxOrientation, collapsedTabContainer: HTMLElement) {
        this._orientation = orientation;
        this._collapsedTabContainer = collapsedTabContainer;

        this._renderedElement = document.createElement("div");
        this._renderedElement.classList.add("acd-toolbox");
        this.stretch = this.stretch; // trigger CSS class painting based on defaults

        this.createCollapsedStateHeaderElement();
        this.createExpandedStateHeaderElement();

        this._contentHost = document.createElement("div");
        this._contentHost.style.overflow = "auto";

        this._renderedElement.appendChild(this._expandedStateHeaderRootElement);
        this._renderedElement.appendChild(this._contentHost);
        
        if (this._collapsedTabContainer) {
            this._collapsedTabContainer.appendChild(this._collapsedStateHeaderRootElement);
        }

        if (!this._isVisible) {
            this.hideToolbox();
        }

        this.updateContent();
    }

    collapse(saveState: boolean = true) {
        if (this._isExpanded) {			
            this._collapsedStateHeaderRootElement.classList.remove("acd-hidden");
            
            this._isExpanded = false;
            this.toggled(saveState);
        }
    }

    expand() {
        if (!this._isExpanded) {
            this._collapsedStateHeaderRootElement.classList.add("acd-hidden");

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

    // Q: Is this sufficient? It looks like we only care about the height of the header when it is expanded
    getHeaderBoundingRect(): ClientRect {
        return this._expandedStateHeaderRootElement.getBoundingClientRect();
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
        if (this.renderedElement && !this._isRestoring && this.isVisible) {
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

                if (isExpandedSetting.succeeded && this.isVisible) {
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

    createExpandedStateHeaderElement() {
        this._expandedStateHeaderRootElement = document.createElement("div");
        this._expandedStateHeaderRootElement.innerHTML = "";
        this._expandedStateHeaderRootElement.className = "acd-toolbox-header";

        let headerContentElement = this.createHeaderContentElement();

        let headerCommandsHostElement = document.createElement("span");
        headerCommandsHostElement.className = "acd-toolbox-header-commandsHost";

        // Q: Is it correct that we only need custom commands for the expanded state?
        this.createCustomCommandsHost();

        headerCommandsHostElement.appendChild(this._customCommandsHost);

        this._expandedStateButtonElement = document.createElement("span");
        this._expandedStateButtonElement.className = "acd-toolbox-header-commandButton";
        this._expandedStateButtonElement.title = "Hide " + this.title;
        this._expandedStateButtonElement.tabIndex = 0;
        this._expandedStateButtonElement.setAttribute("role", "button");
        this._expandedStateButtonElement.setAttribute("aria-expanded", "true");
        this._expandedStateButtonElement.ariaLabel = this.title;

        let expandedHeaderIconElement = document.createElement("span")
        expandedHeaderIconElement.classList.add("acd-icon", "acd-icon-header-expanded");

        this._expandedStateButtonElement.appendChild(expandedHeaderIconElement);

        this._expandedStateButtonElement.onkeydown = (e) => {
            if (e.key === Constants.keys.enter || e.key === Constants.keys.space) {
                this.collapse();

                // Now that we've updated the visual state, move focus 
                this._collapsedStateButtonElement.focus();
                
                e.preventDefault();
            }

            if (e.key === Constants.keys.escape) {
                this.collapse();

                // Now that we've updated the visual state, move focus 
                this._collapsedStateButtonElement.focus();
                
                e.preventDefault();
            }
        }

        this._expandedStateButtonElement.onclick = (e) => {
            this.collapse();
            e.preventDefault();
            return true;
        }

        headerCommandsHostElement.appendChild(this._expandedStateButtonElement);

        headerContentElement.appendChild(headerCommandsHostElement);

        this._expandedStateHeaderRootElement.appendChild(headerContentElement);
    }

    createCollapsedStateHeaderElement() {
        this._collapsedStateHeaderRootElement = document.createElement("div");
        this._collapsedStateHeaderRootElement.innerHTML = "";

        // Hide the collapsed state header on initial render
        this._collapsedStateHeaderRootElement.classList.add("acd-toolbox-header", "acd-hidden")

        let headerContentElement = this.createHeaderContentElement();

        this._collapsedStateButtonElement = document.createElement("span");
        this._collapsedStateButtonElement.className = "acd-toolbox-header-commandButton";
        this._collapsedStateButtonElement.title = "Show " + this.title;
        this._collapsedStateButtonElement.tabIndex = 0;
        this._collapsedStateButtonElement.setAttribute("role", "button");
        this._collapsedStateButtonElement.setAttribute("aria-expanded", "false");
        this._collapsedStateButtonElement.ariaLabel = this.title;
        
        let collapsedHeaderIconElement = document.createElement("span")
        collapsedHeaderIconElement.classList.add("acd-icon", "acd-icon-header-collapsed");

        this._collapsedStateButtonElement.appendChild(collapsedHeaderIconElement);

        this._collapsedStateButtonElement.onkeydown = (e) => {
            if (e.key === Constants.keys.enter || e.key === Constants.keys.space) {
                this.expand();

                // Now that we've updated the visual state, move focus
                this._expandedStateButtonElement.focus();
                
                e.preventDefault();
            }
        }

        this._collapsedStateButtonElement.onclick = (e) => {
            this.expand();

            // Now that we've updated the visual state, move focus
            this._expandedStateButtonElement.focus();

            e.preventDefault();
            return true;
        }

        headerContentElement.appendChild(this._collapsedStateButtonElement);
        this._collapsedStateHeaderRootElement.appendChild(headerContentElement);
    }

    createHeaderContentElement(): HTMLElement {
        let headerContentElement = document.createElement("div");
        headerContentElement.className = "acd-toolbox-header-content";

        let headerTitleElement = document.createElement("span");
        headerTitleElement.className = "acd-toolbox-header-title";
        headerTitleElement.innerText = this.title;

        headerContentElement.appendChild(headerTitleElement);

        return headerContentElement;
    }

    createCustomCommandsHost() {
        this._customCommandsHost = document.createElement("div");
        this._customCommandsHost.style.display = "flex";

        if (this.commands) {
            for (let command of this.commands) {
                let commandButtonElement = document.createElement("div");
                commandButtonElement.className = "acd-toolbox-header-commandButton";
                commandButtonElement.title = command.title;
                commandButtonElement.onclick = (e) => {
                    command.execute(command);
                }

                let commandIconElement = document.createElement("div");
                commandIconElement.classList.add("acd-icon", command.iconClass);

                commandButtonElement.appendChild(commandIconElement);

                this._customCommandsHost.appendChild(commandButtonElement);
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
            this.renderedElement.classList.add("acd-toolbox-stretch");
            this.renderedElement.classList.remove("acd-toolbox-no-stretch");
        }
        else {
            this.renderedElement.classList.add("acd-toolbox-no-stretch");
            this.renderedElement.classList.remove("acd-toolbox-stretch");
        }
    }

    set isVisible(value: boolean) {
        if (this._isVisible != value) {
            this._isVisible = value;

            this.updateVisibility();
        }
    }

    get isVisible() {
        return this._isVisible;
    }
}
