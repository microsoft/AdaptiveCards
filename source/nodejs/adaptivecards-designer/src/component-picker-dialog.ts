// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { AdaptiveComponent, AdaptiveComponentManager, Downloader } from "adaptivecards";
import { Dialog } from "./dialog";

class ComponentListItem {
    private _component?: AdaptiveComponent;
    private _renderedElement: HTMLElement;
    private _isSelected: boolean = false;

    private updateCddStyles() {
        if (this.isSelected) {
            this._renderedElement.classList.add("selected");
        }
        else {
            this._renderedElement.classList.remove("selected");
        }
    }

    private renderContent() {
        while (this._renderedElement.firstChild) {
            this._renderedElement.removeChild(this._renderedElement.firstChild);            
        }

        let cardPayload: object;

        if (this._component) {
            let previewCardPayload = {
                type: "AdaptiveCard",
                version: "1.0",
                body: [
                    {
                        type: "Component",
                        name: this._component.name
                    }
                ]
            };

            let previewCard = new Adaptive.AdaptiveCard();
            previewCard.parse(previewCardPayload);
            previewCard.render();
            previewCard.renderedElement.style.width = "100%";

            let previewHost = document.createElement("div");
            previewHost.className = "acd-component-picker-list-item-thumbnail";
            previewHost.appendChild(previewCard.renderedElement);

            this._renderedElement.appendChild(previewHost);

            cardPayload = {
                type: "AdaptiveCard",
                version: "1.0",
                body: [
                    {
                        type: "TextBlock",
                        weight: "Bolder",
                        size: "Medium",
                        horizontalAlignment: "Center",
                        text: this._component.displayName ? this._component.displayName : this._component.name
                    },
                    {
                        type: "TextBlock",
                        spacing: "None",
                        horizontalAlignment: "Center",
                        wrap: true,
                        text: this._component.description ? this._component.description : "<No description>"
                    }
                ]
            }
        }
        else {
            cardPayload = {
                type: "AdaptiveCard",
                version: "1.0",
                body: [
                    {
                        type: "TextBlock",
                        weight: "Bolder",
                        size: "Medium",
                        horizontalAlignment: "Center",
                        text: this.componentName
                    }
                ]
            }
        }

        let card = new Adaptive.AdaptiveCard();
        card.parse(cardPayload);
        card.render();
        card.renderedElement.style.width = "100%";

        this._renderedElement.appendChild(card.renderedElement);
    }

    onSelectedChanged: (sender: ComponentListItem) => void;

    constructor(readonly componentName: string) {
        this._renderedElement = document.createElement("div");
        this._renderedElement.className = "acd-component-picker-list-item";
        this._renderedElement.onclick = (ev: MouseEvent) => {
            this.isSelected = true;
        }
    }

    render(): HTMLElement {
        this.renderContent();

        return this._renderedElement;
    }

    load() {
        if (!this._component) {

            this.renderContent();

            AdaptiveComponentManager.loadComponent(
                this.componentName,
                (component: AdaptiveComponent) => {
                    this._component = component;

                    this.renderContent();
                },
                (error: string) => {
                });
        }
    }

    get isSelected(): boolean {
        return this._isSelected;
    }

    set isSelected(value: boolean) {
        if (this._isSelected !== value) {
            this._isSelected = value;

            this.updateCddStyles();

            if (this.onSelectedChanged) {
                this.onSelectedChanged(this);
            }
        }
    }
}

export class ComponentPickerDialog extends Dialog {
    private _renderedElement: HTMLElement;
    private _componentListHostElement: HTMLElement;
    private _componentList: ComponentListItem[];
    private _selectedItem?: ComponentListItem;

    private setContent(hostElement: HTMLElement, element: HTMLElement) {
        while (hostElement.firstChild) {
            hostElement.removeChild(hostElement.firstChild);
        }

        if (element) {
            hostElement.appendChild(element);
        }
    }

    private renderMessage(message: string, showSpinner: boolean): HTMLElement {
        let messageHostElement = document.createElement("div");
        messageHostElement.style.display = "flex";
        messageHostElement.style.flexDirection = "column";
        messageHostElement.style.alignItems = "center";
        messageHostElement.style.justifyContent = "center";
        messageHostElement.style.height = "100%";

        if (showSpinner) {
            let spinnerElement = document.createElement("div");
            spinnerElement.className = "acd-spinner";
            spinnerElement.style.width = "28px";
            spinnerElement.style.height = "28px";

            messageHostElement.appendChild(spinnerElement);
        }

        let textElement = document.createElement("div");
        textElement.className = "acd-dialog-message";
        textElement.innerText = message;
        textElement.style.marginTop = "10px";

        messageHostElement.appendChild(textElement);

        return messageHostElement;
    }

    private renderComponentList(): HTMLElement {
        let element = document.createElement("div");
        element.className = "acd-component-picker-list-container";

        for (let listItem of this._componentList) {
            element.appendChild(listItem.render());

            listItem.load();
        }

        return element;
    }

    protected renderContent(): HTMLElement {
        this._renderedElement = document.createElement("div");
        this._renderedElement.style.overflow = "auto";

        this._componentListHostElement = document.createElement("div");

        this.setContent(
            this._componentListHostElement,
            this.renderMessage("Loading component list, please wait...", true));

        let downloader = new Downloader("https://adaptivecardsapi.azurewebsites.net/components/find");
        downloader.onSuccess = (sender: Downloader) => {
            this._componentList = [];

            let responseJson = JSON.parse(sender.data);

            if (Array.isArray(responseJson)) {
                for (let component of responseJson) {
                    if (typeof component["name"] === "string") {
                        let listItem = new ComponentListItem(component["name"]);
                        listItem.onSelectedChanged = (sender: ComponentListItem) => {
                            if (sender.isSelected) {
                                this._selectedItem = sender;

                                for (let item of this._componentList) {
                                    if (item !== sender) {
                                        item.isSelected = false;
                                    }
                                }

                                this.close();
                            }
                        }

                        this._componentList.push(listItem);
                    }
                }
            }

            this.setContent(this._componentListHostElement, this.renderComponentList());
        };
        downloader.onError = (sender: Downloader) => {
            this.setContent(
                this._componentListHostElement,
                this.renderMessage("The component list could not be loaded, please try again later.", false));    
        };
        downloader.download();

        this.setContent(this._renderedElement, this._componentListHostElement);

        return this._renderedElement;
    }

    get selectedComponentName(): string | undefined {
        return this._selectedItem ? this._selectedItem.componentName : undefined;
    }
} 