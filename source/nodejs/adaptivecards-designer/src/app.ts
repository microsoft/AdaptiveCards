import * as Adaptive from "adaptivecards";
import * as Controls from "adaptivecards-controls";
import * as Constants from "./constants";
import * as Designer from "./card-designer";
import { HostContainer } from "./containers/host-container";
import { OutlookContainer } from "./containers/outlook-container";
import { CortanaContainer } from "./containers/cortana-container";

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
    private _hostContainerPicker: Controls.DropDown;
    private _selectedHostContainer: HostContainer;

    private buildPropertySheet(peer: Designer.DesignerPeer) {
        if (this.propertySheetHostElement) {
            this.propertySheetHostElement.innerHTML = "";

            let card: Adaptive.AdaptiveCard;

            if (peer) {
                card = peer.buildPropertySheetCard();
            }
            else {

                card = new Adaptive.AdaptiveCard();
                card.parse(
                    {
                        type: "AdaptiveCard",
                        version: "1.0",
                        body: [
                            {
                                type: "TextBlock",
                                wrap: true,
                                size: "medium",
                                text: "**Nothing is selected**"
                            },
                            {
                                type: "TextBlock",
                                wrap: true,
                                text: "Select an element in the card to modify its properties."
                            }
                        ]
                    }
                );
            }
        
            this.propertySheetHostElement.appendChild(card.render());
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

    private addContainers() {
        this.hostContainers.push(new CortanaContainer("Cortana Skills", "css/cortana.css"));
        this.hostContainers.push(new OutlookContainer("Outlook Actionable Messages", "css/outlook.css"));
    }

    private recreateDesigner() {
        var styleSheetLinkElement = <HTMLLinkElement>document.getElementById("adaptiveCardStylesheet");
    
        if (styleSheetLinkElement == null) {
            styleSheetLinkElement = document.createElement("link");
            styleSheetLinkElement.id = "adaptiveCardStylesheet";
    
            document.getElementsByTagName("head")[0].appendChild(styleSheetLinkElement);
        }
    
        styleSheetLinkElement.rel = "stylesheet";
        styleSheetLinkElement.type = "text/css";
    
        this._selectedHostContainer.initialize();
    
        styleSheetLinkElement.href = this._selectedHostContainer.styleSheet;
    
        this._designer = new Designer.CardDesigner(this._selectedHostContainer.cardHost);

        this._designer.onSelectedPeerChanged = (peer: Designer.CardElementPeer) => {
            this.buildPropertySheet(peer);
        };

        this._designerHostElement.innerHTML = "";
        this._designerHostElement.appendChild(this._selectedHostContainer.render());

        this.buildPalette();

        if (this._card) {
            this._card.hostConfig = this._selectedHostContainer.getHostConfig();
        }

        this._designer.card = this._card;

        this.buildPropertySheet(null);
    }

    private selectedHostContainerChanged() {
        this.recreateDesigner();
    }

    readonly hostContainers: Array<HostContainer> = [];
    
    propertySheetHostElement: HTMLElement;
    commandListHostElement: HTMLElement;

    constructor(designerHostElement: HTMLElement) {
        this._designerHostElement = designerHostElement;

        this.addContainers();

        this._selectedHostContainer = this.hostContainers[0];
        
        this.recreateDesigner();
    }

    createContainerPicker(): Controls.DropDown {
        this._hostContainerPicker = new Controls.DropDown();
        
        for (var i = 0; i < this.hostContainers.length; i++) {
            let item = new Controls.DropDownItem(i.toString(), this.hostContainers[i].name);

            this._hostContainerPicker.items.add(item);
        }

        this._hostContainerPicker.selectedIndex = 0;
        this._hostContainerPicker.onValueChanged = (sender: Controls.InputControl) => {
            this._selectedHostContainer = this.hostContainers[Number.parseInt(this._hostContainerPicker.value.key)];

            this.selectedHostContainerChanged();
        }

        return this._hostContainerPicker;
    }
    
    handlePointerMove(e: PointerEvent) {
        this._currentMousePosition = { x: e.x, y: e.y };

        var isPointerOverDesigner = this.designer.isPointerOver(this._currentMousePosition.x, this._currentMousePosition.y);

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
        }
    }

    get card(): Adaptive.AdaptiveCard {
        return this._card;
    }

    set card(value: Adaptive.AdaptiveCard) {
        if (this._card != value) {
            if (this._card) {
                this._card.designMode = false;
            }

            this._card = value;

            if (this._card) {
                this._card.designMode = true;
                this._card.hostConfig = this._selectedHostContainer.getHostConfig();
            }

            this.recreateDesigner();
            /*
            this.designer.card = this._card;
    
            this.buildPropertySheet(null);
            */
        }
    }

    get designer(): Designer.CardDesigner {
        return this._designer;
    }
}

var designerApp: DesignerApp;

window.onload = () => {
    var card = new Adaptive.AdaptiveCard();
    card.designMode = true;
    card.parse(JSON.parse(Constants.defaultPayload));

    designerApp = new DesignerApp(document.getElementById("designerHost"));
    designerApp.propertySheetHostElement = document.getElementById("propertySheetHost");
    designerApp.commandListHostElement = document.getElementById("commandsHost");
    designerApp.paletteHostElement = document.getElementById("toolPalette");

    designerApp.createContainerPicker().attach(document.getElementById("containerPickerHost"));

    designerApp.card = card;

    window.addEventListener("pointermove", (e: PointerEvent) => { designerApp.handlePointerMove(e); });
    window.addEventListener("resize", () => { designerApp.designer.updateLayout(); });
    window.addEventListener("pointerup", (e: PointerEvent) => { designerApp.handlePointerUp(e); });
};