// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export class PeerCommand {
    private _renderedElement: HTMLElement;

    protected internalRender(): HTMLElement {
        var buttonElement = document.createElement("button");
        buttonElement.type = "button";
        buttonElement.title = this.name;
        buttonElement.classList.add("acd-peerButton");
        buttonElement.classList.add(this.iconClass);
        buttonElement.style.display = "flex";
        buttonElement.style.flex = "0 0 auto";
        buttonElement.style.alignItems = "center";
        buttonElement.onclick = (e: MouseEvent) => {
            if (this.execute) {
                this.execute(this, buttonElement);
            }
        }
        buttonElement.onpointerdown = (e: PointerEvent) => { e.cancelBubble = true; };

        return buttonElement;
    }

    name: string;
    iconClass: string;
    isPromotable: boolean = false;
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
