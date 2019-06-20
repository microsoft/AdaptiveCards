// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as DesignerSurface from "./card-designer-surface";
import * as DesignerPeers from "./designer-peers";
import * as Adaptive from "adaptivecards";
import { DraggableElement } from "./draggable-element";

export abstract class BasePaletteItem extends DraggableElement {
    protected abstract getText(): string;
    protected abstract getIconClass(): string;

    protected internalRender(): HTMLElement {
        let element = document.createElement("div");
        element.className = "acd-palette-item";
        element.style.display = "flex";

        let iconElement = document.createElement("div");
        iconElement.classList.add("acd-icon", this.getIconClass());
        iconElement.style.flex = "0 0 auto";

        let labelElement = document.createElement("div");
        labelElement.className = "acd-palette-item-label";
        labelElement.style.flex = "1 1 100%";
        labelElement.innerText = this.getText();

        element.appendChild(iconElement);
        element.appendChild(labelElement);

        return element;
    }

    cloneElement(): HTMLElement {
        return this.internalRender();
    }

    abstract createPeer(designer: DesignerSurface.CardDesignerSurface): DesignerPeers.CardElementPeer;
}

export class ElementPaletteItem extends BasePaletteItem {
    protected getText(): string {
        return this.typeRegistration.typeName;
    }

    protected getIconClass(): string {
        return this.peerRegistration.iconClass;
    }

    readonly typeRegistration: Adaptive.ITypeRegistration<Adaptive.CardElement>;
    readonly peerRegistration: DesignerPeers.DesignerPeerRegistrationBase;

    constructor(typeRegistration: Adaptive.ITypeRegistration<Adaptive.CardElement>, peerRegistration: DesignerPeers.DesignerPeerRegistrationBase) {
        super();

        this.typeRegistration = typeRegistration;
        this.peerRegistration = peerRegistration;
    }

    createPeer(designer: DesignerSurface.CardDesignerSurface): DesignerPeers.CardElementPeer {
        let peer = DesignerSurface.CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(designer, null, this.typeRegistration.createInstance());
        peer.initializeCardElement();

        return peer;
    }
}

/* DO NOT REMOVE - future feature
class SnippetPaletteItem extends BasePaletteItem {
    protected getText(): string {
        return this.name;
    }

    protected getIconClass(): string {
        return null;
    }

    readonly name: string;
    snippet: object;

    constructor(name: string) {
        super();

        this.name = name;
    }

    createPeer(designer: Designer.CardDesigner): Designer.CardElementPeer {
        if (this.snippet) {
            let rootElementTypeName = this.snippet["type"];

            if (rootElementTypeName) {
                let adaptiveElement = Adaptive.AdaptiveCard.elementTypeRegistry.createInstance(rootElementTypeName);

                if (adaptiveElement) {
                    adaptiveElement.parse(this.snippet);

                    let peer = Designer.CardDesigner.cardElementPeerRegistry.createPeerInstance(designer, null, adaptiveElement);
                    peer.initializeCardElement();

                    return peer;
                }
            }
        }
    }
}
*/
