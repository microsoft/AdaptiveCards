// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export class PeerCommand {
    private _renderedElement: HTMLElement;

    protected internalRender(): HTMLElement {
        let buttonElement = document.createElement("button");
        buttonElement.classList.add("acd-peerButton");
        buttonElement.type = "button";
        buttonElement.title = this.toolTip ? this.toolTip : this.name;

        if (this.iconClass) {
            let iconElement = document.createElement("div");
            iconElement.classList.add("acd-peerButton-icon", this.iconClass);

            buttonElement.appendChild(iconElement);
        }

        if (this.name && (!this.iconClass || this.alwaysShowName)) {
            let nameElement = document.createElement("div");
            nameElement.classList.add("acd-peerButton-text");
            nameElement.innerText = this.name;

            buttonElement.classList.add("variableWidth");
            buttonElement.appendChild(nameElement);
        }
        else {
            buttonElement.classList.add("fixedWidth");
        }

        buttonElement.onclick = (e: MouseEvent) => {
            if (this.execute) {
                this.execute(this, buttonElement);
            }
        }
        buttonElement.onpointerdown = (e: PointerEvent) => { e.cancelBubble = true; };

        return buttonElement;
    }

    name: string;
    alwaysShowName: boolean = false;
    toolTip: string = undefined;
    iconClass: string;
    isPromotable: boolean = false;
    showInPropertySheet: boolean = false;
    execute: (command: PeerCommand, clickedElement: HTMLElement) => void;

    constructor(init?: Partial<PeerCommand>) {
        Object.assign(this, init);
    }

    render(): HTMLElement {
        this._renderedElement = this.internalRender();

        return this._renderedElement;
    }

    get renderedElement(): HTMLElement {
        return this._renderedElement;
    }
}
