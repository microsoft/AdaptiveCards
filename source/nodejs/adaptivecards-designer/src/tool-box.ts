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
    private _headerRootElement: HTMLElement;
    private _headerIconElement: HTMLElement;
    private _expandCollapseButtonElement: HTMLElement;
    private _customCommandsHost: HTMLElement;
    private _contentHost: HTMLElement;
    private _isExpanded: boolean = true;
    private _content: HTMLElement;
    private _stretch: boolean = false;
    private _orientation: ToolboxOrientation;
    private _isRestoring: boolean = false;
    private _collapsedTabContainer: HTMLElement;

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

    commands: Array<IToolboxCommand> = null;

    constructor(id: string, title: string) {
        this.id = id;
        this.title = title;
    }

    render(orientation: ToolboxOrientation, collapsedTabContainer: HTMLElement) {
        this._orientation = orientation;
        this._collapsedTabContainer = collapsedTabContainer;

        this._renderedElement = document.createElement("div");
        this._renderedElement.style.overflow = "auto";
        this._renderedElement.style.display = "flex";
        this._renderedElement.style.flexDirection = "column";
        this._renderedElement.style.position = "relative";

        this._headerRootElement = document.createElement("div");
        this._headerRootElement.innerHTML = "";
        this._headerRootElement.className = "acd-toolbox-header";

        let headerContentElement = document.createElement("div");
        headerContentElement.className = "acd-toolbox-header-content";

        let headerTitleElement = document.createElement("span");
        headerTitleElement.className = "acd-toolbox-header-title";
        headerTitleElement.innerText = this.title;

        headerContentElement.appendChild(headerTitleElement);

        let headerCommandsHostElement = document.createElement("span");
        headerCommandsHostElement.className = "acd-toolbox-header-commandsHost";

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

        headerCommandsHostElement.appendChild(this._customCommandsHost);

        this._expandCollapseButtonElement = document.createElement("span");
        this._expandCollapseButtonElement.className = "acd-toolbox-header-commandButton";
        this._expandCollapseButtonElement.title = "Hide " + this.title;
        this._expandCollapseButtonElement.tabIndex = 0;
        this._expandCollapseButtonElement.setAttribute("role", "button");
        this._expandCollapseButtonElement.setAttribute("aria-expanded", "true");

        this._headerIconElement = document.createElement("span")
        this._headerIconElement.classList.add("acd-icon", "acd-icon-header-expanded");

        this._expandCollapseButtonElement.appendChild(this._headerIconElement);

        this._expandCollapseButtonElement.onkeydown = (e) => {
            if (e.key === Constants.keys.enter || e.key === Constants.keys.space) {
                this.toggle();

                e.preventDefault();
                this._expandCollapseButtonElement.focus();
            }
        }

        this._expandCollapseButtonElement.onclick = (e) => {
            this.toggle();

            e.preventDefault();

            return true;
        }

        headerCommandsHostElement.appendChild(this._expandCollapseButtonElement);

        headerContentElement.appendChild(headerCommandsHostElement);

        this._headerRootElement.appendChild(headerContentElement);

        this._contentHost = document.createElement("div");
        this._contentHost.style.overflow = "auto";

        this._renderedElement.append(this._headerRootElement, this._contentHost);

        this.updateContent();
    }

    collapse() {
        if (this._isExpanded) {
            this._headerIconElement.classList.add("acd-icon-header-collapsed");
            this._headerIconElement.classList.remove("acd-icon-header-expanded");
            this._customCommandsHost.classList.add("acd-hidden");

            if (this._collapsedTabContainer) {
                this._renderedElement.removeChild(this._headerRootElement);
                this._collapsedTabContainer.appendChild(this._headerRootElement);
            }

            this._expandCollapseButtonElement.title = "Show " + this.title;
            this._expandCollapseButtonElement.setAttribute("aria-expanded", "false");

            this._isExpanded = false;

            this.toggled();
        }
    }

    expand() {
        if (!this._isExpanded) {
            this._headerIconElement.classList.add("acd-icon-header-expanded");
            this._headerIconElement.classList.remove("acd-icon-header-collapsed");
            this._customCommandsHost.classList.remove("acd-hidden");

            if (this._collapsedTabContainer) {
                this._collapsedTabContainer.removeChild(this._headerRootElement);
                this._renderedElement.insertBefore(this._headerRootElement, this._renderedElement.firstChild);
            }

            this._expandCollapseButtonElement.title = "Hide " + this.title;
            this._expandCollapseButtonElement.setAttribute("aria-expanded", "true");

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
