import * as Adaptive from "adaptivecards";
import * as Constants from "./constants";
import * as Designer from "./card-designer";

export class ToggleVisibilityAction extends Adaptive.Action {
    targetElementIds: Array<string> = [];

    getJsonTypeName(): string {
        return "Action.ToggleVisibility";
    }

    execute() {
        if (this.targetElementIds) {
            for (var i = 0; i < this.targetElementIds.length; i++) {
                var targetElement = this.parent.getRootElement().getElementById(this.targetElementIds[i]);

                if (targetElement) {
                    targetElement.isVisible = !targetElement.isVisible;
                }
            }
        }
    }

    parse(json: any) {
        super.parse(json);

        this.targetElementIds = json["targetElements"] as Array<string>;
    }
}

class PaletteItem extends Designer.DraggableElement {
    protected internalRender(): HTMLElement {
        var element = document.createElement("div");
        element.classList.add("acd-palette-item");
        element.innerText = this.typeRegistration.typeName;

        return element;
    }

    readonly typeRegistration: Adaptive.ITypeRegistration<Adaptive.CardElement>;

    constructor(typeRegistration: Adaptive.ITypeRegistration<Adaptive.CardElement>) {
        super();

        this.typeRegistration = typeRegistration;
    }

    cloneElement(): HTMLElement {
        return this.internalRender();
    }

    createPeer(): Designer.CardElementPeer {
        var peer = Designer.CardDesigner.cardElementPeerRegistry.createPeerInstance(null, this.typeRegistration.createInstance());
        peer.initializeCardElement();

        return peer;
    }
}

class DesignerApp {
    private _designer: Designer.CardDesigner;
    private _designerHostElement: HTMLElement;
    private _paletteHostElement: HTMLElement;
    private _draggedPaletteItem: PaletteItem;
    private _draggedElement: HTMLElement;
    private _currentMousePosition: Designer.IPoint;
    private _card: Adaptive.AdaptiveCard;

    private buildPropertySheet(peer: Designer.DesignerPeer) {
        if (this.propertySheetHostElement) {
            this.propertySheetHostElement.innerHTML = "";

            if (peer) {
                var card = peer.buildPropertySheetCard();
        
                this.propertySheetHostElement.appendChild(card.render());
            }
        }
    }
    
    private buildPalette() {
        if (this.paletteHostElement) {
            this.paletteHostElement.innerHTML = "";

            var sortedRegisteredTypes: Array<Adaptive.ITypeRegistration<Adaptive.CardElement>> = [];

            for (var i = 0; i < Adaptive.AdaptiveCard.elementTypeRegistry.getItemCount(); i++) {
                sortedRegisteredTypes.push(Adaptive.AdaptiveCard.elementTypeRegistry.getItemAt(i));
            }

            sortedRegisteredTypes.sort(
                (a, b) => {
                    if (a.typeName < b.typeName) {
                        return -1
                    }
                    else {
                        return 1;
                    }
                }
            )

            for (var i = 0; i < sortedRegisteredTypes.length; i++) {
                var paletteItem = new PaletteItem(sortedRegisteredTypes[i]);
                paletteItem.render();
                paletteItem.onStartDrag = (sender: PaletteItem) => {
                    this._draggedPaletteItem = sender;
        
                    this._draggedElement = sender.cloneElement();
                    this._draggedElement.style.position = "absolute";
                    this._draggedElement.style.left = this._currentMousePosition.x + "px";
                    this._draggedElement.style.top = this._currentMousePosition.y + "px";
        
                    document.body.appendChild(this._draggedElement);
        
                    sender.releasePointerCapture();
                    sender.endDrag();
                }
        
                this.paletteHostElement.appendChild(paletteItem.renderedElement);
            }
        }
    }

    private endDrag() {
        if (this._draggedPaletteItem) {
            this._draggedElement.remove();
            this._draggedPaletteItem = null;
        }
    }
    
    propertySheetHostElement: HTMLElement;
    commandListHostElement: HTMLElement;

    constructor(designerHostElement: HTMLElement) {
        this._designerHostElement = designerHostElement;
        this._designer = new Designer.CardDesigner(this._designerHostElement);

        this._designer.onSelectedPeerChanged = (peer: Designer.CardElementPeer) => {
            this.buildPropertySheet(peer);
        };
    
        /*
        this._designer.onPointerMoved = (designer: Designer.CardDesigner) => {
            if (this._draggedPaletteItem) {
                let peer = this._draggedPaletteItem.createPeer();

                if (this._designer.tryDrop(peer)) {
                    this._designer.startDrag(peer);

                    this.endDrag();
                }
            }
        }
        */

    }

    handlePointerMove(e: PointerEvent) {
        this._currentMousePosition = { x: e.x, y: e.y };

        document.getElementById("windowMouseMoveStatus").innerText = "x: " + this._currentMousePosition.x + ", y: " + this._currentMousePosition.y;

        var isPointerOverDesigner = this.designer.isPointerOver(this._currentMousePosition.x, this._currentMousePosition.y);

        document.getElementById("isOverDesignerStatus").innerText = "Over designer: " + isPointerOverDesigner;

        if (this._draggedElement) {
            this._draggedElement.style.left = this._currentMousePosition.x - 10 + "px";
            this._draggedElement.style.top = this._currentMousePosition.y - 10 + "px";
        }

        if (this._draggedPaletteItem && isPointerOverDesigner) {
            let peer = this._draggedPaletteItem.createPeer();

            if (this.designer.tryDrop(this._currentMousePosition, peer)) {
                this.designer.startDrag(peer);

                this.endDrag();
            }
        }
    }

    handlePointerUp(e: PointerEvent) {
        this.endDrag();
    }

    get paletteHostElement(): HTMLElement {
        return this._paletteHostElement;
    }

    set paletteHostElement(value: HTMLElement) {
        if (this._paletteHostElement != value) {
            this._paletteHostElement = value;

            this.buildPalette();
        }
    }

    get card(): Adaptive.AdaptiveCard {
        return this._card;
    }

    set card(value: Adaptive.AdaptiveCard) {
        if (this._card = value) {
            if (this._card) {
                this._card.designMode = false;
            }

            this._card = value;

            if (this._card) {
                this._card.designMode = true;
            }

            this.designer.card = this._card;
        }
    }

    get designer(): Designer.CardDesigner {
        return this._designer;
    }
}

var designerApp: DesignerApp;

window.onload = () => {
    Adaptive.AdaptiveCard.elementTypeRegistry.registerType("ActionSet", () => { return new Adaptive.ActionSet(); });
    Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Action.Http", () => { return new Adaptive.HttpAction(); });
    Adaptive.AdaptiveCard.actionTypeRegistry.registerType("Action.ToggleVisibility", () => { return new ToggleVisibilityAction(); });

    var card = new Adaptive.AdaptiveCard();
    card.designMode = true;
    card.parse(JSON.parse(Constants.defaultPayload));

    designerApp = new DesignerApp(document.getElementById("designerHost"));
    designerApp.propertySheetHostElement = document.getElementById("propertySheetHost");
    designerApp.commandListHostElement = document.getElementById("commandsHost");
    designerApp.paletteHostElement = document.getElementById("toolPalette");
    designerApp.card = card;

    window.addEventListener("pointermove", (e: PointerEvent) => { designerApp.handlePointerMove(e); });
    window.addEventListener("resize", () => { designerApp.designer.updateLayout(); });
    window.addEventListener("pointerup", (e: PointerEvent) => { designerApp.handlePointerUp(e); });
};