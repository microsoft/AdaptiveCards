import * as Adaptive from "adaptivecards";
import * as Controls from "adaptivecards-controls";
import * as Constants from "./constants";
import * as Designer from "./card-designer";
import { HostContainer } from "./containers/host-container";
import { OutlookContainer } from "./containers/outlook-container";
import { CortanaContainer } from "./containers/cortana-container";
import { SkypeContainer } from "./containers/skype-container";

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
                }
        
                this.paletteHostElement.appendChild(paletteItem.renderedElement);
            }
        }
    }

    private endDrag() {
        if (this._draggedPaletteItem) {
            this._draggedPaletteItem.endDrag();
            this._draggedElement.remove();

            this._draggedPaletteItem = null;
            this._draggedElement = null;
        }
    }

    private addContainers() {
        this.hostContainers.push(new OutlookContainer("Outlook Actionable Messages", "css/outlook-container.css"));
        this.hostContainers.push(new CortanaContainer("Cortana Skills", "css/cortana-container.css"));
        this.hostContainers.push(new SkypeContainer("Skype (Preview)", "css/skype-container.css"));
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
        styleSheetLinkElement.href = this._selectedHostContainer.styleSheet;
    
        this._selectedHostContainer.initialize();
    
        this._designerHostElement.innerHTML = "";
        this._selectedHostContainer.renderTo(this._designerHostElement);

        this._designer = new Designer.CardDesigner(this._selectedHostContainer.cardHost);
        this._designer.onSelectedPeerChanged = (peer: Designer.CardElementPeer) => {
            this.buildPropertySheet(peer);
        };

        this.buildPalette();
        this.buildPropertySheet(null);

        if (this._card) {
            this._card.hostConfig = this._selectedHostContainer.getHostConfig();
        }

        // Forces a relayout after layout has completed. Needed because the Cortana host
        // (and other) use Flex and there is a condition by which the Flex layout happens
        // asynchronously and prevents the designer from properly sizing its peer elements.
        // Not super clean, but the best solution I've found for now.
        window.setTimeout(
            () => {
                this._designer.card = this._card;
            },
            100
        );
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

        let isPointerOverDesigner = this.designer.isPointerOver(this._currentMousePosition.x, this._currentMousePosition.y);
        let peerDropped = false;

        if (this._draggedPaletteItem && isPointerOverDesigner) {
            let peer = this._draggedPaletteItem.createPeer();

            if (this.designer.tryDrop(this._currentMousePosition, peer)) {
                this.endDrag();

                this.designer.startDrag(peer);

                peerDropped = true;
            }
        }

        if (!peerDropped && this._draggedElement) {
            this._draggedElement.style.left = this._currentMousePosition.x - 10 + "px";
            this._draggedElement.style.top = this._currentMousePosition.y - 10 + "px";
        }
    }

    handlePointerUp(e: PointerEvent) {
        this.endDrag();
        this.designer.endDrag();
    }

    updateLayout() {
        this._designer.updateLayout();
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
        }
    }

    get designer(): Designer.CardDesigner {
        return this._designer;
    }
}

var app: DesignerApp;

window.onload = () => {
    var card = new Adaptive.AdaptiveCard();
    card.designMode = true;
    card.parse(JSON.parse(Constants.defaultPayload));

    app = new DesignerApp(document.getElementById("designerHost"));
    app.propertySheetHostElement = document.getElementById("propertySheetHost");
    app.commandListHostElement = document.getElementById("commandsHost");
    app.paletteHostElement = document.getElementById("toolPalette");

    app.createContainerPicker().attach(document.getElementById("containerPickerHost"));

    window.addEventListener("pointermove", (e: PointerEvent) => { app.handlePointerMove(e); });
    window.addEventListener("resize", () => { app.designer.updateLayout(); });
    window.addEventListener("pointerup", (e: PointerEvent) => { app.handlePointerUp(e); });

    app.card = card;
};