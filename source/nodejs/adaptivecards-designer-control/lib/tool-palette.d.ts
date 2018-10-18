import * as DesignerSurface from "./card-designer-surface";
import * as DesignerPeers from "./designer-peers";
import * as Adaptive from "adaptivecards";
import { DraggableElement } from "./draggable-element";
export declare abstract class BasePaletteItem extends DraggableElement {
    protected abstract getText(): string;
    protected abstract getIconClass(): string;
    protected internalRender(): HTMLElement;
    cloneElement(): HTMLElement;
    abstract createPeer(designer: DesignerSurface.CardDesignerSurface): DesignerPeers.CardElementPeer;
}
export declare class ElementPaletteItem extends BasePaletteItem {
    protected getText(): string;
    protected getIconClass(): string;
    readonly typeRegistration: Adaptive.ITypeRegistration<Adaptive.CardElement>;
    readonly peerRegistration: DesignerPeers.DesignerPeerRegistrationBase;
    constructor(typeRegistration: Adaptive.ITypeRegistration<Adaptive.CardElement>, peerRegistration: DesignerPeers.DesignerPeerRegistrationBase);
    createPeer(designer: DesignerSurface.CardDesignerSurface): DesignerPeers.CardElementPeer;
}
