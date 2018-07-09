import * as Clipboard from "clipboard";
import * as Adaptive from "adaptivecards";
import * as Controls from "adaptivecards-controls";
import * as Constants from "./constants";
import * as Designer from "./card-designer";
import * as Utils from "./utils";
import { HostContainer } from "./containers/host-container";
import { OutlookContainer } from "./containers/outlook-container";
import { LightTeamsContainer, DarkTeamsContainer } from "./containers/teams-container";
import { CortanaContainer } from "./containers/cortana-container";
import { SkypeContainer } from "./containers/skype-container";
import { WebChatContainer } from "./containers/webchat-container";
import { ToastContainer } from "./containers/toast-container";
import { BotFrameworkContainer } from "./containers/bf-image-container";
import { adaptiveCardSchema } from "./adaptive-card-schema";
import FullScreenHandler from "./components/fullscreenhandler";

declare var monacoEditor: any;
declare function loadMonacoEditor(schema, callback);

var isMonacoEditorLoaded: boolean = false;

function monacoEditorLoaded() {
    document.getElementById("loadingEditor").remove();

    monacoEditor.onDidChangeModelContent(
        function (e) {
            scheduleCardRefresh();
        });
    document.querySelector(".monaco-editor").insertAdjacentHTML("afterbegin", "<div class='jsonEditorHost-title'>JSON</div>");
    isMonacoEditorLoaded = true;

    updateJsonFromCard();
}

function getCurrentJsonPayload(): string {
    return isMonacoEditorLoaded ? monacoEditor.getValue() : Constants.defaultPayload;
}

var jsonUpdateTimer: NodeJS.Timer;
var cardUpdateTimer: NodeJS.Timer;
var updateLayoutTimer: NodeJS.Timer;

var preventCardUpdate: boolean = false;

function updateJsonFromCard() {
    try {
        preventCardUpdate = true;

        if (!preventJsonUpdate && isMonacoEditorLoaded) {
            monacoEditor.setValue(JSON.stringify(app.card.toJSON(), null, 4));
        }
    }
    finally {
        preventCardUpdate = false;
    }
}

function scheduleJsonUpdate() {
    clearTimeout(jsonUpdateTimer);

    if (!preventJsonUpdate) {
        jsonUpdateTimer = setTimeout(updateJsonFromCard, 100);
    }
}

var preventJsonUpdate: boolean = false;

function updateCardFromJson() {
    try {
        preventJsonUpdate = true;
        if (!preventCardUpdate) {
            app.designer.parseCard(getCurrentJsonPayload());
        }
    }
    finally {
        preventJsonUpdate = false;
    }
}

function scheduleCardRefresh() {
    clearTimeout(cardUpdateTimer);

    if (!preventCardUpdate) {
        cardUpdateTimer = setTimeout(updateCardFromJson, 200);
    }
}

function scheduleLayoutUpdate() {
    clearTimeout(updateLayoutTimer);

    updateLayoutTimer = setTimeout(
        () => {
            app.designer.updateLayout(false);
        },
        50);
}

// Monaco loads asynchronously via a call to require() from index.html
// App initialization needs to happen after.
declare function loadMonacoEditor(schema: any, callback: () => void);

abstract class BasePaletteItem extends Designer.DraggableElement {
    protected abstract getText(): string;

    protected internalRender(): HTMLElement {
        let element = document.createElement("li");
        element.className = `aside-item aside-item__icon aside-item__icon--${Utils.sanitizeString(this.getText())}`;
        element.innerText = this.getText();

        return element;
    }

    cloneElement(): HTMLElement {
        return this.internalRender();
    }

    abstract createPeer(designer: Designer.CardDesigner): Designer.CardElementPeer;
}

class ElementPaletteItem extends BasePaletteItem {
    protected getText(): string {
        return this.typeRegistration.typeName;
    }

    readonly typeRegistration: Adaptive.ITypeRegistration<Adaptive.CardElement>;

    constructor(typeRegistration: Adaptive.ITypeRegistration<Adaptive.CardElement>) {
        super();

        this.typeRegistration = typeRegistration;
    }

    createPeer(designer: Designer.CardDesigner): Designer.CardElementPeer {
        let peer = Designer.CardDesigner.cardElementPeerRegistry.createPeerInstance(designer, null, this.typeRegistration.createInstance());
        peer.initializeCardElement();

        return peer;
    }
}

class SnippetPaletteItem extends BasePaletteItem {
    protected getText(): string {
        return this.name;
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

class DesignerApp {
    private _designer: Designer.CardDesigner;
    private _designerHostElement: HTMLElement;
    private _paletteHostElement: HTMLElement;
    private _draggedPaletteItem: BasePaletteItem;
    private _draggedElement: HTMLElement;
    private _currentMousePosition: Designer.IPoint;
    private _card: Adaptive.AdaptiveCard;
    private _hostContainerPicker: Controls.DropDown;
    private _selectedHostContainer: HostContainer;

    public buildTreeViewSheet() {
        if (this.treeViewSheetHostElement) {
            let treeview = this.treeViewSheetHostElement.getElementsByClassName("treeview-items")[0];
            treeview.innerHTML = "";

            treeview.appendChild(this.designer.rootPeer.treeItem.render());
        }
    }

    private buildPropertySheet(peer: Designer.DesignerPeer) {
        let properties = document.getElementsByClassName("js-properties-items")[0];
        if (this.propertySheetHostElement) {
            properties.innerHTML = "";

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

            properties.appendChild(card.render());
            let cardNodes = card.renderedElement.children;

            for (let element = 0; element < cardNodes.length; element++) {
                (cardNodes[element] as HTMLElement).className += " wrapper";
             }
        }
    }

    private addPaletteItem(paletteItem: BasePaletteItem) {
        paletteItem.render();
        paletteItem.onStartDrag = (sender: BasePaletteItem) => {
            this._draggedPaletteItem = sender;

            this._draggedElement = sender.cloneElement();
            this._draggedElement.style.position = "absolute";
            this._draggedElement.style.left = this._currentMousePosition.x + "px";
            this._draggedElement.style.top = this._currentMousePosition.y + "px";

            document.body.appendChild(this._draggedElement);
        }

        this.paletteHostElement.appendChild(paletteItem.renderedElement);
    }

    private buildPalette() {
        if (this.paletteHostElement) {
            this.paletteHostElement.innerHTML = "";

            let sortedRegisteredTypes = {};

            const categoriesMap = {
                cardElements: {
                    title: "Card Elements",
                    items: ["TextBlock", "Image"]
                },
                container: {
                    title: "Container",
                    items: ["Container", "ColumnSet", "Column", "FactSet", "Fact", "ImageSet"]
                },
                actions: {
                    title: "Actions",
                    items: ["Action.OpenUrl", "Action.Submit", "Action.ShowCard"]
                },
                inputs: {
                    title: "Inputs",
                    items: ["Input.Text", "Input.Number", "Input.Date", "Input.Time", "Input.Toggle", "Input.ChoiceSet", "Input.Choice"]
                }
            }

            let categoriesMapKeys = Object.keys(categoriesMap);
            for (let i = 0; i < categoriesMapKeys.length; i++) {
                const category = categoriesMapKeys[i];
                const categoryItems = categoriesMap[category].items;
                for (let j = 0; j < categoryItems.length; j++) {
                    let item = categoryItems[j];
                    let itemType = Adaptive.AdaptiveCard.elementTypeRegistry.getItems().find(elementType => {
                        return elementType.typeName === item;
                    });
                    if (typeof itemType !== "undefined") {
                        sortedRegisteredTypes[category] = sortedRegisteredTypes[category] || {};
                        sortedRegisteredTypes[category].title = sortedRegisteredTypes[category].title || categoriesMap[category].title;
                        sortedRegisteredTypes[category].items = Array.isArray(sortedRegisteredTypes[category].items) ? [...sortedRegisteredTypes[category].items, itemType] : [itemType];
                    }
                }
            }

            Object.keys(sortedRegisteredTypes).forEach(objectKey => {
                let node = document.createElement('li');
                node.innerText = sortedRegisteredTypes[objectKey].title;
                node.className = "aside-title";
                this.paletteHostElement.appendChild(node);

                for (var i = 0; i < sortedRegisteredTypes[objectKey].items.length; i++) {
                    var paletteItem = new ElementPaletteItem(sortedRegisteredTypes[objectKey].items[i]);
                    this.addPaletteItem(paletteItem);
                }
            });

            /* This is to test "snippet" support. Snippets are not yet fully baked
            let personaHeaderSnippet = new SnippetPaletteItem("Persona header");
            personaHeaderSnippet.snippet = {
                type: "ColumnSet",
                columns: [
                    {
                        width: "auto",
                        items: [
                            {
                                type: "Image",
                                size: "Small",
                                style: "Person",
                                url: "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"
                            }
                        ]
                    },
                    {
                        width: "stretch",
                        items: [
                            {
                                type: "TextBlock",
                                text: "John Doe",
                                weight: "Bolder",
                                wrap: true
                            },
                            {
                                type: "TextBlock",
                                spacing: "None",
                                text: "Additional information",
                                wrap: true
                            }
                        ]
                    }
                ]
            };

            this.addPaletteItem(personaHeaderSnippet);
            */
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
        this.hostContainers.push(new WebChatContainer("Bot Framework WebChat", "css/webchat-container.css"));
        this.hostContainers.push(new LightTeamsContainer("Microsoft Teams - Light (preview)", "css/teams-container-light.css"));
        this.hostContainers.push(new DarkTeamsContainer("Microsoft Teams - Dark (preview)", "css/teams-container-dark.css"));
        this.hostContainers.push(new CortanaContainer("Cortana Skills", "css/cortana-container.css"));
        // this.hostContainers.push(new TimelineContainer("Windows Timeline", "css/timeline-container.css")); This element overflows it's container and can't fit the content
        this.hostContainers.push(new SkypeContainer("Skype (Preview)", "css/skype-container.css"));
        this.hostContainers.push(new OutlookContainer("Outlook Actionable Messages", "css/outlook-container.css"));
        this.hostContainers.push(new ToastContainer("Windows Notifications (Preview)", "css/toast-container.css"));
        this.hostContainers.push(new BotFrameworkContainer("Bot Framework Other Channels (Image render)", "css/bf-image-container.css"));
    }

    private recreateDesigner() {
        let styleSheetLinkElement = <HTMLLinkElement>document.getElementById("adaptiveCardStylesheet");

        if (styleSheetLinkElement == null) {
            styleSheetLinkElement = document.createElement("link");
            styleSheetLinkElement.id = "adaptiveCardStylesheet";

            document.getElementsByTagName("head")[0].appendChild(styleSheetLinkElement);
        }

        styleSheetLinkElement.rel = "stylesheet";
        styleSheetLinkElement.type = "text/css";
        styleSheetLinkElement.href = this._selectedHostContainer.styleSheet;

        let designerBackground = document.getElementById("designerBackground");

        if (designerBackground) {
            designerBackground.style.backgroundColor = this._selectedHostContainer.getBackgroundColor();
        }

        this._selectedHostContainer.initialize();

        this._designerHostElement.innerHTML = "";
        this._selectedHostContainer.renderTo(this._designerHostElement);

        this._designer = new Designer.CardDesigner(this._selectedHostContainer.cardHost);
        this._designer.onSelectedPeerChanged = (peer: Designer.CardElementPeer) => {
            this.buildPropertySheet(peer);
        };
        this._designer.onLayoutUpdated = (isFullRefresh: boolean) => {
            if (isFullRefresh) {
                scheduleJsonUpdate();
            }
            this.buildTreeViewSheet();
        };
        this._designer.onCardValidated = (errors: Array<Adaptive.IValidationError>) => {
            let errorPane = document.getElementById("errorPane");
            errorPane.innerHTML = "";

            if (errors.length > 0) {
                let errorMessages: Array<string> = [];

                for (let error of errors) {
                    if (errorMessages.indexOf(error.message) < 0) {
                        errorMessages.push(error.message);
                    }
                }

                for (let message of errorMessages) {
                    let errorElement = document.createElement("div");
                    errorElement.style.overflow = "hidden";
                    errorElement.style.textOverflow = "ellipsis";
                    errorElement.innerText = message;

                    errorPane.appendChild(errorElement);
                }

                errorPane.style.display = null;
            }
            else {
                errorPane.style.display = "none";
            }
        };

        this.buildPalette();
        this.buildPropertySheet(null);

        if (this._card) {
            this._card.hostConfig = this._selectedHostContainer.getHostConfig();
        }

        this._designer.card = this._card;
    }

    private selectedHostContainerChanged() {
        this.recreateDesigner();
    }

    readonly hostContainers: Array<HostContainer> = [];

    propertySheetHostElement: HTMLElement;
    treeViewSheetHostElement: HTMLElement;
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
            let peer = this._draggedPaletteItem.createPeer(this.designer);

            let clientCoordinates = this.designer.pageToClientCoordinates(this._currentMousePosition.x, this._currentMousePosition.y);

            if (this.designer.tryDrop(clientCoordinates, peer)) {
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

    private handleClosePanel(panelType: string): void {
        const typeOfPanel = document.querySelector(`.js-${panelType}-menu`);
        let description = document.querySelector(`.js-${panelType}-description`);
        let aside = document.querySelector(".js-aside-panel");

        if (aside.childNodes.length === 0) {
            document.querySelector(`.js-${panelType}-bullet`).addEventListener("click", () => {
                description.innerHTML = "";
                const elementNode = typeOfPanel.cloneNode(true);
                elementNode.addEventListener("click", () => {
                    description.innerHTML = "Hide";
                    this.openPanel(panelType);
                });
                aside.classList.add("is-active");
                aside.appendChild(elementNode);

                (document.querySelector(`.js-${panelType}`) as HTMLElement).style.display = "none";
                (document.querySelector(`.js-${panelType}-splitter`) as HTMLElement).style.display = "none";
            });
        }
    }

    private openPanel(panelType: string): void {
        if (document.querySelector(".js-aside-panel").hasChildNodes()) {
            let foldedPanel = document.querySelector(`.js-aside-panel.is-active > .js-${panelType}-menu`);
            let aside = document.querySelector(".js-aside-panel");

            (document.querySelector(`.js-${panelType}`) as HTMLElement).style.display = "block";
            (document.querySelector(`.js-${panelType}-splitter`) as HTMLElement).style.display = "block";
            foldedPanel.remove();

            if (aside.childNodes.length === 0) {
                (aside as HTMLElement).classList.toggle("is-active");
            }
        }
    }

    public cloneNodesTrees(): void {
        this.handleClosePanel("treeview");
        this.handleClosePanel("properties");
    }

    private toggleAside():void {
        document.querySelector(".js-aside-bullet").addEventListener("click", () => {
            const aside = document.querySelector(".js-aside");
            aside.classList.toggle("is-toggled");

            const items = document.querySelector(".js-aside-items");
            items.classList.toggle("is-hidden");

            const icon = document.querySelector(".js-aside-icon");
            icon.classList.toggle("icon--expand");

            const description = document.querySelector(".js-aside-description");
            description.classList.toggle("is-hidden");
        })
    }

    public togglePanels(): void {
        this.toggleAside();
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

class Splitter {
    private _splitterElement: HTMLElement;
    private _sizedELement: HTMLElement;
    private _isPointerDown: boolean;
    private _lastClickedOffset: Designer.IPoint;

    private pointerDown(e: PointerEvent) {
        e.preventDefault();

        this._splitterElement.setPointerCapture(e.pointerId);

        this._lastClickedOffset = { x: e.x, y: e.y };

        this._isPointerDown = true;
    }

    private pointerMove(e: PointerEvent) {
        if (this._isPointerDown) {
            e.preventDefault();

            let sizeApplied = false;

            if (this.isVertical) {
                let newWidth = this._sizedELement.getBoundingClientRect().width - (e.x - this._lastClickedOffset.x);

                if (newWidth >= this.minimum) {
                    this._sizedELement.style.width = newWidth + "px";

                    sizeApplied = true;
                }
            }
            else {
                let newHeight = this._sizedELement.getBoundingClientRect().height - (e.y - this._lastClickedOffset.y);

                if (newHeight >= this.minimum) {
                    this._sizedELement.style.height = newHeight + "px";

                    sizeApplied = true;
                }
            }

            if (sizeApplied) {
                if (this.onRezized) {
                    this.onRezized(this);
                }

                this._lastClickedOffset = { x: e.x, y: e.y };
            }
        }
    }

    private pointerUp(e: PointerEvent) {
        e.preventDefault();

        this._splitterElement.releasePointerCapture(e.pointerId);

        this._isPointerDown = false;
    }

    onRezized: (sender: Splitter) => void;

    isVertical: boolean = false;
    minimum: number = 50;

    constructor(splitterElement: HTMLElement, sizedElement: HTMLElement) {
        this._splitterElement = splitterElement;
        this._sizedELement = sizedElement;

        this._splitterElement.onmousedown = (e: MouseEvent) => {e.preventDefault(); };
        this._splitterElement.onpointerdown = (e: PointerEvent) => { this.pointerDown(e); };
        this._splitterElement.onpointermove = (e: PointerEvent) => { this.pointerMove(e); };
        this._splitterElement.onpointerup = (e: PointerEvent) => { this.pointerUp(e); };
    }
}

var app: DesignerApp;
var horizontalSplitter: Splitter;
var propertyVerticalSplitter: Splitter;
var treeViewVerticalSplitter: Splitter;

window.onload = () => {
    const fullScreenHandler = new FullScreenHandler(document.querySelector(".js-enter-fullscreen"));
    fullScreenHandler.init();

    new Clipboard(".js-copy-json", {
        text: function () {
            return JSON.stringify(app.card.toJSON(), null, 4);
        }
    });

    horizontalSplitter = new Splitter(document.getElementById("horizontalSplitter"), document.getElementById("jsonEditorHost"));
    horizontalSplitter.onRezized = (splitter: Splitter) => {
        if (isMonacoEditorLoaded) {
            monacoEditor.layout();
        }
    }

    propertyVerticalSplitter
        = new Splitter(document.getElementById("propertyVerticalSplitter"), document.getElementById("propertySheetHost"));
    propertyVerticalSplitter.isVertical = true;
    propertyVerticalSplitter.onRezized = (splitter: Splitter) => {
        scheduleLayoutUpdate();
    }

    treeViewVerticalSplitter
        = new Splitter(document.getElementById("treeViewVerticalSplitter"), document.getElementById("treeViewSheetHost"));
    treeViewVerticalSplitter.isVertical = true;

    let card = new Adaptive.AdaptiveCard();
    card.onImageLoaded = (image: Adaptive.Image) => {
        scheduleLayoutUpdate();
    }

    app = new DesignerApp(document.getElementById("designerHost"));
    app.propertySheetHostElement = document.getElementById("propertySheetHost");
    app.treeViewSheetHostElement = document.getElementById("treeViewSheetHost");
    app.commandListHostElement = document.getElementById("commandsHost");
    app.paletteHostElement = document.getElementById("toolPalette");

    app.createContainerPicker().attach(document.getElementById("containerPickerHost"));

    app.togglePanels();
    app.cloneNodesTrees();

    window.addEventListener("pointermove", (e: PointerEvent) => { app.handlePointerMove(e); });
    window.addEventListener("resize", () => { scheduleLayoutUpdate(); });
    window.addEventListener("pointerup", (e: PointerEvent) => { app.handlePointerUp(e); });

    app.card = card;

    loadMonacoEditor(adaptiveCardSchema, monacoEditorLoaded);

    updateCardFromJson();
};
