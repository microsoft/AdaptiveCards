// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import * as Controls from "adaptivecards-controls";
import { DraggableElement } from "./draggable-element";
import { IPoint } from "./miscellaneous";
import * as DesignerPeers from "./designer-peers";
import * as ACData from "adaptivecards-templating";
import * as Shared from "./shared";
import { HostContainer } from "./containers";

export type CardElementType = { new(): Adaptive.CardElement };
export type ActionType = { new(): Adaptive.Action };
export type CardElementPeerType = {
    new(
        parent: DesignerPeers.DesignerPeer,
        designerSurface: CardDesignerSurface,
        registration: DesignerPeers.DesignerPeerRegistrationBase,
        cardElement: Adaptive.CardElement
    ): DesignerPeers.CardElementPeer
};
export type ActionPeerType = {
    new(
        parent: DesignerPeers.DesignerPeer,
        designerSurface: CardDesignerSurface,
        registration: DesignerPeers.DesignerPeerRegistrationBase,
        action: Adaptive.Action
    ): DesignerPeers.ActionPeer
};

class DesignerPeerCategory {
    static Unknown = "Unknown";
    static Containers = "Containers";
    static Elements = "Elements";
    static Inputs = "Inputs";
    static Actions = "Actions";
}

export abstract class DesignerPeerRegistry<TSource, TPeer> {
    protected _items: Array<DesignerPeers.DesignerPeerRegistration<TSource, TPeer>> = [];

    readonly defaultRegistration = new DesignerPeers.DesignerPeerRegistrationBase(DesignerPeerCategory.Unknown, "acd-icon-unknownPeer");

    constructor() {
        this.reset();
    }

    abstract reset();

    clear() {
        this._items = [];
    }

    findTypeRegistration(sourceType: TSource): DesignerPeers.DesignerPeerRegistration<TSource, TPeer> {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].sourceType === sourceType) {
                return this._items[i];
            }
        }

        return null;
    }

    registerPeer(sourceType: TSource, peerType: TPeer, category: string, iconClass: string = null) {
        var registrationInfo = this.findTypeRegistration(sourceType);

        if (registrationInfo != null) {
            registrationInfo.peerType = peerType;
        }
        else {
            registrationInfo = new DesignerPeers.DesignerPeerRegistration<TSource, TPeer> (
                sourceType,
                peerType,
                category,
                iconClass);

            this._items.push(registrationInfo);
        }
    }

    unregisterPeer(sourceType: TSource) {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].sourceType === sourceType) {
                this._items.splice(i, 1);

                return;
            }
        }
    }
}

export class CardElementPeerRegistry extends DesignerPeerRegistry<CardElementType, CardElementPeerType> {
    reset() {
        this.clear();

        this.registerPeer(Adaptive.AdaptiveCard, DesignerPeers.AdaptiveCardPeer, DesignerPeerCategory.Containers, "acd-icon-adaptiveCard");
        this.registerPeer(Adaptive.Container, DesignerPeers.ContainerPeer, DesignerPeerCategory.Containers, "acd-icon-container");
        this.registerPeer(Adaptive.ColumnSet, DesignerPeers.ColumnSetPeer, DesignerPeerCategory.Containers, "acd-icon-columnSet");
        this.registerPeer(Adaptive.Column, DesignerPeers.ColumnPeer, DesignerPeerCategory.Containers, "acd-icon-column");
        this.registerPeer(Adaptive.ImageSet, DesignerPeers.ImageSetPeer, DesignerPeerCategory.Containers, "acd-icon-imageSet");
        this.registerPeer(Adaptive.FactSet, DesignerPeers.FactSetPeer, DesignerPeerCategory.Containers, "acd-icon-factSet");

        this.registerPeer(Adaptive.TextBlock, DesignerPeers.TextBlockPeer, DesignerPeerCategory.Elements, "acd-icon-textBlock");
        this.registerPeer(Adaptive.RichTextBlock, DesignerPeers.RichTextBlockPeer, DesignerPeerCategory.Elements, "acd-icon-richTextBlock");
        this.registerPeer(Adaptive.Image, DesignerPeers.ImagePeer, DesignerPeerCategory.Elements, "acd-icon-image");
        this.registerPeer(Adaptive.Media, DesignerPeers.MediaPeer, DesignerPeerCategory.Elements, "acd-icon-media");
        this.registerPeer(Adaptive.ActionSet, DesignerPeers.ActionSetPeer, DesignerPeerCategory.Elements, "acd-icon-actionSet");

        this.registerPeer(Adaptive.TextInput, DesignerPeers.TextInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputText");
        this.registerPeer(Adaptive.DateInput, DesignerPeers.DateInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputDate");
        this.registerPeer(Adaptive.TimeInput, DesignerPeers.TimeInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputTime");
        this.registerPeer(Adaptive.ToggleInput, DesignerPeers.ToggleInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputToggle");
        this.registerPeer(Adaptive.NumberInput, DesignerPeers.NumberInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputNumber");
        this.registerPeer(Adaptive.ChoiceSetInput, DesignerPeers.ChoiceSetInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputChoiceSet");
    }

    createPeerInstance(designerSurface: CardDesignerSurface, parent: DesignerPeers.DesignerPeer, cardElement: Adaptive.CardElement): DesignerPeers.CardElementPeer {
        var registrationInfo = this.findTypeRegistration((<any>cardElement).constructor);

        var peer = registrationInfo ? new registrationInfo.peerType(parent, designerSurface, registrationInfo, cardElement) : new DesignerPeers.CardElementPeer(parent, designerSurface, this.defaultRegistration, cardElement);

        return peer;
    }
}

export class ActionPeerRegistry extends DesignerPeerRegistry<ActionType, ActionPeerType> {
    reset() {
        this.clear();

        this.registerPeer(Adaptive.HttpAction, DesignerPeers.HttpActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionHttp");
        this.registerPeer(Adaptive.SubmitAction, DesignerPeers.SubmitActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionSubmit");
        this.registerPeer(Adaptive.OpenUrlAction, DesignerPeers.OpenUrlActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionOpenUrl");
        this.registerPeer(Adaptive.ShowCardAction, DesignerPeers.ShowCardActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionShowCard");
        this.registerPeer(Adaptive.ToggleVisibilityAction, DesignerPeers.ToggleVisibilityActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionToggleVisibility");
    }

    createPeerInstance(designerSurface: CardDesignerSurface, parent: DesignerPeers.DesignerPeer, action: Adaptive.Action): DesignerPeers.ActionPeer {
        var registrationInfo = this.findTypeRegistration((<any>action).constructor);

        var peer = registrationInfo ? new registrationInfo.peerType(parent, designerSurface, registrationInfo, action) : new DesignerPeers.ActionPeer(parent, designerSurface, this.defaultRegistration, action);

        return peer;
    }
}

class DragHandle extends DraggableElement {
    protected internalRender(): HTMLElement {
        let element = document.createElement("div");
        element.classList.add("acd-peerButton", "acd-icon-drag");
        element.title = "Drag to move this element";
        element.style.visibility = "hidden";
        element.style.position = "absolute";
        element.style.zIndex = "500";

        return element;
    }
}

export class CardDesignerSurface {
    static readonly cardElementPeerRegistry: CardElementPeerRegistry = new CardElementPeerRegistry();
    static readonly actionPeerRegistry: ActionPeerRegistry = new ActionPeerRegistry();

    private _updateCount: number = 0;

    private _card: Adaptive.AdaptiveCard;
    private _allPeers: Array<DesignerPeers.DesignerPeer> = [];
    private _rootPeer: DesignerPeers.DesignerPeer;
    private _cardHost: HTMLElement;
    private _designerSurface: HTMLDivElement;
    private _selectedPeer: DesignerPeers.DesignerPeer;
    private _draggedPeer: DesignerPeers.DesignerPeer;
    private _dropTarget: DesignerPeers.DesignerPeer;
    private _dragHandle: DragHandle;
    private _removeCommandElement: HTMLElement;
    private _peerCommandsHostElement: HTMLElement;
    private _parseContext: Adaptive.ParseContext = new Adaptive.ParseContext();
    private _isPreviewMode: boolean = false;
    private _sampleData: any;

    private updatePeerCommandsLayout() {
        if (this._selectedPeer) {
            let peerRect = this._selectedPeer.getBoundingRect();
            let dragHandleRect = this._dragHandle.renderedElement.getBoundingClientRect();
            let removeButtonRect = this._removeCommandElement.getBoundingClientRect();
            let commandsHostRect = this._peerCommandsHostElement.getBoundingClientRect();

            this._dragHandle.renderedElement.style.left = (peerRect.left - dragHandleRect.width) + "px";
            this._dragHandle.renderedElement.style.top = (peerRect.top - dragHandleRect.height) + "px";

            this._removeCommandElement.style.left = peerRect.right + "px";
            this._removeCommandElement.style.top = (peerRect.top - removeButtonRect.height) + "px";

            this._peerCommandsHostElement.style.left = (peerRect.right - commandsHostRect.width) + "px";
            this._peerCommandsHostElement.style.top = (peerRect.bottom + 2) + "px";

            this._dragHandle.renderedElement.style.visibility = this._selectedPeer.isDraggable() ? "visible" : "hidden";
            this._removeCommandElement.style.visibility = this._selectedPeer.canBeRemoved() ? "visible" : "hidden";
            this._peerCommandsHostElement.style.visibility = this._peerCommandsHostElement.childElementCount > 0 ? "visible" : "hidden";
        }
        else {
            this._dragHandle.renderedElement.style.visibility = "hidden";
            this._removeCommandElement.style.visibility = "hidden";
            this._peerCommandsHostElement.style.visibility = "hidden";
        }
    }

    private setSelectedPeer(value: DesignerPeers.DesignerPeer) {
        if (this._selectedPeer != value) {
            if (this._selectedPeer) {
                this._selectedPeer.isSelected = false;
            }

            this._selectedPeer = value;

            this._peerCommandsHostElement.innerHTML = "";

            if (this._selectedPeer) {
                this._selectedPeer.isSelected = true;

                let commands = this._selectedPeer.getCommands(this.hostContainer);

                for (let command of commands) {
                    this._peerCommandsHostElement.appendChild(command.render());
                }

                this._designerSurface.focus();
            }

            this.updatePeerCommandsLayout();

            if (this.onSelectedPeerChanged) {
                this.onSelectedPeerChanged(this._selectedPeer);
            }
        }
    }

    private peerChanged(peer: DesignerPeers.DesignerPeer, updatePropertySheet: boolean) {
        this._parseContext = new Adaptive.ParseContext();

        this.renderCard()
        this.updateLayout();

        if (updatePropertySheet && this.onSelectedPeerChanged) {
            this.onSelectedPeerChanged(this._selectedPeer);
        }
    }

    private peerRemoved(peer: DesignerPeers.DesignerPeer) {
        this._allPeers.splice(this._allPeers.indexOf(peer), 1);

        if (peer == this._selectedPeer) {
            this.setSelectedPeer(null);
        }

        if (this._updateCount == 0) {
            this.renderCard();
            this.updateLayout();
        }
    }

    private renderCard() {
        this._cardHost.innerHTML = "";

        if (this.card) {
            if (this.onCardValidated) {
                this.onCardValidated(this._parseContext.errors, this.card.validateProperties());
            }

            let cardToRender: Adaptive.AdaptiveCard;

            if (this.isPreviewMode) {
                if (Shared.GlobalSettings.previewFeaturesEnabled) {
                    let cardPayload = this.card.toJSON();

                    try {
                        let template = new ACData.Template(cardPayload);
            
                        let context = new ACData.EvaluationContext();
                        context.$root = this.sampleData;

                        let expandedCardPayload = template.expand(context);

                        cardToRender = new Adaptive.AdaptiveCard();
                        cardToRender.hostConfig = this.card.hostConfig;
                        cardToRender.parse(expandedCardPayload, new Adaptive.ParseContext());
                    }
                    catch (e) {
                        console.log("Template expansion error: " + e.message);
                    }
                }

                if (!cardToRender) {
                    cardToRender = this.card;
                    cardToRender.designMode = false;
                }
            }
            else {
                cardToRender = this.card;
                cardToRender.designMode = true;
            }

            let renderedCard = cardToRender.render();

            if (this.fixedHeightCard) {
                renderedCard.style.height = "100%";

            }
            this._cardHost.appendChild(renderedCard);
        }
    }

    private addPeer(peer: DesignerPeers.DesignerPeer) {
        if (this._allPeers.indexOf(peer) < 0) {
            this._allPeers.push(peer);

            peer.render();

            peer.onSelectedChanged = (peer: DesignerPeers.DesignerPeer) => {
                if (peer.isSelected) {
                    this.setSelectedPeer(peer);
                }
                else {
                    if (this._selectedPeer == peer) {
                        this.setSelectedPeer(null);
                    }
                }
            };
            peer.onChanged = (sender: DesignerPeers.DesignerPeer, updatePropertySheet: boolean) => { this.peerChanged(sender, updatePropertySheet); };
            peer.onPeerRemoved = (sender: DesignerPeers.DesignerPeer) => { this.peerRemoved(sender); };
            peer.onPeerAdded = (sender: DesignerPeers.DesignerPeer, newPeer: DesignerPeers.DesignerPeer) => {
                this.addPeer(newPeer);
                this.updateLayout();
            };
            peer.onStartDrag = (sender: DesignerPeers.DesignerPeer) => { this.startDrag(sender); }
            peer.onEndDrag = (sender: DesignerPeers.DesignerPeer) => { this.endDrag(); }

            peer.addElementsToDesignerSurface(this._designerSurface);

            for (var i = 0; i < peer.getChildCount(); i++) {
                this.addPeer(peer.getChildAt(i));
            }
        }
    }

    private internalFindDropTarget(pointerPosition: IPoint, currentPeer: DesignerPeers.DesignerPeer, forPeer: DesignerPeers.DesignerPeer): DesignerPeers.DesignerPeer {
        if (currentPeer == forPeer) {
            return null;
        }

        var result: DesignerPeers.DesignerPeer = null;
        var lookDeeper = currentPeer instanceof DesignerPeers.ActionPeer;

        if (!lookDeeper) {
            var boundingRect = currentPeer.getBoundingRect();

            lookDeeper = boundingRect.isInside(pointerPosition);
        }

        if (lookDeeper) {
            let canDrop = currentPeer.canDrop(forPeer);

            if (canDrop) {
                result = currentPeer;
            }

            for (var i = 0; i < currentPeer.getChildCount(); i++) {
                var deeperResult = this.internalFindDropTarget(pointerPosition, currentPeer.getChildAt(i), forPeer);

                if (deeperResult) {
                    result = deeperResult;

                    break;
                }
            }
        }

        return result;
    }

    private findCardElementPeer(cardElement: Adaptive.CardElement): DesignerPeers.CardElementPeer {
        for (var i = 0; i < this._allPeers.length; i++) {
            var peer = this._allPeers[i];

            if (peer instanceof DesignerPeers.CardElementPeer && peer.cardElement == cardElement) {
                return peer;
            }
        }

        return null;
    }

    private findActionPeer(action: Adaptive.Action): DesignerPeers.ActionPeer {
        for (var i = 0; i < this._allPeers.length; i++) {
            var peer = this._allPeers[i];

            if (peer instanceof DesignerPeers.ActionPeer && peer.action == action) {
                return peer;
            }
        }

        return null;
    }

    private inlineCardExpanded(action: Adaptive.ShowCardAction, isExpanded: boolean) {
        let peer = this.findCardElementPeer(action.card);

        if (isExpanded) {
            if (!peer) {
                let registration = CardDesignerSurface.cardElementPeerRegistry.findTypeRegistration(Adaptive.AdaptiveCard);

                peer = new registration.peerType(peer, this, registration, action.card);

                let parentPeer = this.findActionPeer(action);

                if (parentPeer) {
                    parentPeer.insertChild(peer);
                }
                else {
                    this._rootPeer.insertChild(peer);
                }
            }
            else {
                peer.addElementsToDesignerSurface(this._designerSurface, true);
            }
        }
        else {
            if (peer) {
                peer.removeElementsFromDesignerSurface(true);
            }
        }

        this.updateLayout();
    }

    private get draggedPeer(): DesignerPeers.DesignerPeer {
        return this._draggedPeer;
    }

    private set draggedPeer(value: DesignerPeers.DesignerPeer) {
        if (this._draggedPeer != value) {
            if (this._draggedPeer) {
                this._draggedPeer.dragging = false;
            }

            this._draggedPeer = value;

            if (this._draggedPeer) {
                this._draggedPeer.dragging = true;
            }
        }
    }

    constructor(readonly hostContainer: HostContainer) {
        var rootElement = document.createElement("div");
        rootElement.style.position = "relative";
        rootElement.style.width = "100%";
        rootElement.style.height = "100%";

        this._cardHost = document.createElement("div");
        this._cardHost.style.height = "100%";

        rootElement.appendChild(this._cardHost);

        this._designerSurface = document.createElement("div");
        this._designerSurface.classList.add("acd-designersurface");
        this._designerSurface.tabIndex = 0;
        this._designerSurface.style.position = "absolute";
        this._designerSurface.style.left = "0";
        this._designerSurface.style.top = "0";
        this._designerSurface.style.width = "100%";
        this._designerSurface.style.height = "100%";

        this._designerSurface.onkeyup = (e: KeyboardEvent) => {
            if (this._selectedPeer) {
                switch (e.keyCode) {
                    case Controls.KEY_ESCAPE:
                        this.setSelectedPeer(this._selectedPeer.parent);

                        break;
                    case Controls.KEY_DELETE:
                        this.removeSelected();

                        break;
                }
            }

            return !e.cancelBubble;
        }

        this._designerSurface.onpointermove = (e: PointerEvent) => {
            let clientRect = this._designerSurface.getBoundingClientRect();

            this.tryDrop({ x: e.x - clientRect.left, y: e.y - clientRect.top }, this.draggedPeer);
        }

        this._designerSurface.onpointerup = (e: PointerEvent) => {
            if (this.draggedPeer) {
                this.endDrag();
            }
        }

        rootElement.appendChild(this._designerSurface);

        this.hostContainer.cardHost.innerHTML = "";
        this.hostContainer.cardHost.appendChild(rootElement);
    }

    onCardValidated: (errors: Adaptive.IValidationError[], validationResults: Adaptive.ValidationResults) => void;
    onSelectedPeerChanged: (peer: DesignerPeers.DesignerPeer) => void;
    onLayoutUpdated: (isFullRefresh: boolean) => void;

    fixedHeightCard: boolean = false;

    getDesignerSurfaceOffset(): IPoint {
        let clientRect = this._designerSurface.getBoundingClientRect();

        return { x: clientRect.left, y: clientRect.top };
    }

    findDropTarget(pointerPosition: IPoint, peer: DesignerPeers.DesignerPeer): DesignerPeers.DesignerPeer {
        return this.internalFindDropTarget(pointerPosition, this._rootPeer, peer);
    }

    findPeer(cardObject: Adaptive.CardObject) {
        for (let peer of this._allPeers) {
            if (peer.getCardObject() === cardObject) {
                return peer;
            }
        }

        return undefined;
    }

    beginUpdate() {
        this._updateCount++;
    }

    endUpdate(renderCard: boolean) {
        if (this._updateCount > 0) {
            this._updateCount--;

            if (this._updateCount == 0) {
                if (renderCard) {
                    this.renderCard();
                }

                this.updateLayout();
            }
        }
    }

    render() {
        this._designerSurface.innerHTML = "";
        this._allPeers = [];

        this.setSelectedPeer(null);

        this.renderCard();

        if (this.card) {
            this._rootPeer = CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(this, null, this.card);

            this.addPeer(this._rootPeer);
        }

        this._removeCommandElement = document.createElement("div");
        this._removeCommandElement.classList.add("acd-peerButton", "acd-icon-remove");
        this._removeCommandElement.title = "Remove";
        this._removeCommandElement.style.visibility = "hidden";
        this._removeCommandElement.style.position = "absolute";
        this._removeCommandElement.style.zIndex = "500";
        this._removeCommandElement.onclick = (e) => {
            this.removeSelected();
        }

        this._dragHandle = new DragHandle();
        this._dragHandle.onStartDrag = (sender) => {
            this._dragHandle.endDrag();
            this.startDrag(this._selectedPeer);
        }
        this._dragHandle.render();

        this._peerCommandsHostElement = document.createElement("div");
        this._peerCommandsHostElement.style.visibility = "hidden";
        this._peerCommandsHostElement.style.position = "absolute";
        this._peerCommandsHostElement.style.display = "flex";
        this._peerCommandsHostElement.style.zIndex = "500";

        this._designerSurface.appendChild(this._dragHandle.renderedElement);
        this._designerSurface.appendChild(this._removeCommandElement);
        this._designerSurface.appendChild(this._peerCommandsHostElement);

        this.updateLayout();
    }

    setCardPayloadAsObject(payload: object) {
        this._parseContext = new Adaptive.ParseContext();

        this.card.parse(payload, this._parseContext);

        this.render();
    }

    setCardPayloadAsString(payload: string) {
        this.setCardPayloadAsObject(JSON.parse(payload));
    }

    updateLayout(isFullRefresh: boolean = true) {
        for (var i = 0; i < this._allPeers.length; i++) {
            this._allPeers[i].updateLayout();
        }

        this.updatePeerCommandsLayout();

        if (this.onLayoutUpdated) {
            this.onLayoutUpdated(isFullRefresh);
        }
    }

    removeSelected() {
        if (this.selectedPeer) {
            this.beginUpdate();

            try {
                let parent = this.selectedPeer.parent;

                if (this.selectedPeer.remove(false, true)) {
                    this.setSelectedPeer(parent);
                }
            }
            finally {
                this.endUpdate(true);
            }
        }
    }

    startDrag(peer: DesignerPeers.DesignerPeer) {
        if (!this.draggedPeer) {
            this._designerSurface.classList.add("dragging");

            this.draggedPeer = peer;

            this.setSelectedPeer(this.draggedPeer);
        }
    }

    endDrag() {
        if (this.draggedPeer) {
            // Ensure that the dragged peer's elements are at the top in Z order
            this.draggedPeer.removeElementsFromDesignerSurface(true);
            this.draggedPeer.addElementsToDesignerSurface(this._designerSurface, true);

            this._dropTarget.renderedElement.classList.remove("dragover");

            this.draggedPeer = null;

            this._designerSurface.classList.remove("dragging");
        }
    }

    tryDrop(pointerPosition: IPoint, peer: DesignerPeers.DesignerPeer): boolean {
        var result = false;

        if (peer) {
            if (this._dropTarget) {
                this._dropTarget.renderedElement.classList.remove("dragover");
            }

            var newDropTarget = this.findDropTarget(pointerPosition, peer);

            if (newDropTarget) {
                this._dropTarget = newDropTarget;
                this._dropTarget.renderedElement.classList.add("dragover");

                result = this._dropTarget.tryDrop(peer, pointerPosition);
            }
        }

        return result;
    }

    isPointerOver(x: number, y: number) {
        let clientRect = this._designerSurface.getBoundingClientRect();

        return (x >= clientRect.left) && (x <= clientRect.right) && (y >= clientRect.top) && (y <= clientRect.bottom);
    }

    pageToClientCoordinates(x: number, y: number): IPoint {
        let clientRect = this._designerSurface.getBoundingClientRect();

        return {
            x: x - clientRect.left,
            y: y - clientRect.top
        }
    }

    get rootPeer(): DesignerPeers.DesignerPeer {
        return this._rootPeer;
    }

    get selectedPeer(): DesignerPeers.DesignerPeer {
        return this._selectedPeer;
    }

    get card(): Adaptive.AdaptiveCard {
        return this._card;
    }

    set card(value: Adaptive.AdaptiveCard) {
        if (value != this._card) {
            if (this._card) {
                this._card.onInlineCardExpanded = null;
            }

            this._card = value;

            if (this._card) {
                this._card.onInlineCardExpanded = (action: Adaptive.ShowCardAction, isExpanded: boolean) => { this.inlineCardExpanded(action, isExpanded); };
            }

            this.render();
        }
    }

    get isPreviewMode(): boolean {
        return this._isPreviewMode;
    }

    set isPreviewMode(value: boolean) {
        if (this._isPreviewMode != value) {
            this._isPreviewMode = value;

            if (this._isPreviewMode) {
                this._designerSurface.classList.add("acd-hidden");
                this._dragHandle.renderedElement.classList.add("acd-hidden");
                this._removeCommandElement.classList.add("acd-hidden");
                this._peerCommandsHostElement.classList.add("acd-hidden");
            }
            else {
                this._designerSurface.classList.remove("acd-hidden");
                this._dragHandle.renderedElement.classList.remove("acd-hidden");
                this._removeCommandElement.classList.remove("acd-hidden");
                this._peerCommandsHostElement.classList.remove("acd-hidden");
            }

            this.renderCard();
        }
    }

    get sampleData(): any {
        return this._sampleData;
    }

    set sampleData(value: any) {
        this._sampleData = value;

        if (this.isPreviewMode) {
            this.renderCard();
        }
    }
}
