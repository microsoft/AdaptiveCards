import * as Adaptive from "adaptivecards";
import { IPoint } from "./miscellaneous";
import * as DesignerPeers from "./designer-peers";
export declare type CardElementType = {
    new (): Adaptive.CardElement;
};
export declare type ActionType = {
    new (): Adaptive.Action;
};
export declare type CardElementPeerType = {
    new (designerSurface: CardDesignerSurface, registration: DesignerPeers.DesignerPeerRegistrationBase, cardElement: Adaptive.CardElement): DesignerPeers.CardElementPeer;
};
export declare type ActionPeerType = {
    new (designerSurface: CardDesignerSurface, registration: DesignerPeers.DesignerPeerRegistrationBase, action: Adaptive.Action): DesignerPeers.ActionPeer;
};
export declare abstract class DesignerPeerRegistry<TSource, TPeer> {
    protected _items: Array<DesignerPeers.DesignerPeerRegistration<TSource, TPeer>>;
    readonly defaultRegistration: DesignerPeers.DesignerPeerRegistrationBase;
    constructor();
    abstract reset(): any;
    clear(): void;
    findTypeRegistration(sourceType: TSource): DesignerPeers.DesignerPeerRegistration<TSource, TPeer>;
    registerPeer(sourceType: TSource, peerType: TPeer, category: string, iconClass?: string): void;
    unregisterPeer(sourceType: TSource): void;
}
export declare class CardElementPeerRegistry extends DesignerPeerRegistry<CardElementType, CardElementPeerType> {
    reset(): void;
    createPeerInstance(designerSurface: CardDesignerSurface, parent: DesignerPeers.DesignerPeer, cardElement: Adaptive.CardElement): DesignerPeers.CardElementPeer;
}
export declare class ActionPeerRegistry extends DesignerPeerRegistry<ActionType, ActionPeerType> {
    reset(): void;
    createPeerInstance(designerSurface: CardDesignerSurface, parent: DesignerPeers.DesignerPeer, action: Adaptive.Action): DesignerPeers.ActionPeer;
}
export declare class CardDesignerSurface {
    static readonly cardElementPeerRegistry: CardElementPeerRegistry;
    static readonly actionPeerRegistry: ActionPeerRegistry;
    private _updateCount;
    private _card;
    private _allPeers;
    private _rootPeer;
    private _cardHost;
    private _designerSurface;
    private _selectedPeer;
    private _draggedPeer;
    private _dropTarget;
    private _dragHandle;
    private _removeCommandElement;
    private _peerCommandsHostElement;
    private _lastParseErrors;
    private updatePeerCommandsLayout;
    private setSelectedPeer;
    private peerChanged;
    private peerRemoved;
    private renderCard;
    private addPeer;
    private internalFindDropTarget;
    private findCardElementPeer;
    private findActionPeer;
    private inlineCardExpanded;
    private draggedPeer;
    readonly parentElement: HTMLElement;
    constructor(parentElement: HTMLElement);
    onCardValidated: (errors: Array<Adaptive.IValidationError>) => void;
    onSelectedPeerChanged: (peer: DesignerPeers.DesignerPeer) => void;
    onLayoutUpdated: (isFullRefresh: boolean) => void;
    getDesignerSurfaceOffset(): IPoint;
    findDropTarget(pointerPosition: IPoint, peer: DesignerPeers.DesignerPeer): DesignerPeers.DesignerPeer;
    beginUpdate(): void;
    endUpdate(renderCard: boolean): void;
    render(): void;
    setCardPayloadAsObject(payload: object): void;
    setCardPayloadAsString(payload: string): void;
    updateLayout(isFullRefresh?: boolean): void;
    removeSelected(): void;
    startDrag(peer: DesignerPeers.DesignerPeer): void;
    endDrag(): void;
    tryDrop(pointerPosition: IPoint, peer: DesignerPeers.DesignerPeer): boolean;
    isPointerOver(x: number, y: number): boolean;
    pageToClientCoordinates(x: number, y: number): IPoint;
    readonly rootPeer: DesignerPeers.DesignerPeer;
    readonly selectedPeer: DesignerPeers.DesignerPeer;
    card: Adaptive.AdaptiveCard;
}
