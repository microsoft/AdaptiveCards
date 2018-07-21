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
import { FullScreenHandler } from "./components/fullscreenhandler";

declare var monacoEditor: any;
declare function loadMonacoEditor(schema, callback);

var isMonacoEditorLoaded: boolean = false;

function monacoEditorLoaded() {
    document.getElementById("loadingEditor").remove();

    monacoEditor.onDidChangeModelContent(
        function (e) {
            scheduleCardRefresh();
        });

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

class SidePaneHeader {
    private _sidePaneElement: HTMLElement;
    private _rootElement: HTMLElement;
    private _contentElement: HTMLElement;
    private _titleElement: HTMLElement;
    private _iconElement: HTMLElement;
    private _statusTextElement: HTMLElement;
    private _isExpanded: boolean = true;

    collapsedTabContainer: HTMLElement = null;
    collapsedTabClass: string = null;
    targetElementsSelector: string = null;

    onToggled: (sender: SidePaneHeader) => void;

    constructor(sidePaneElement: HTMLElement, title: string) {
        this._sidePaneElement = sidePaneElement;

        this._rootElement = document.createElement("div");
        this._rootElement.innerHTML = "";
        this._rootElement.className = "acd-sidePane-header";

        this._contentElement = document.createElement("div");
        this._contentElement.className = "acd-sidePane-header-content";

        this._titleElement = document.createElement("span");
        this._titleElement.className = "acd-sidePane-header-title";
        this._titleElement.innerText = title;

        this._contentElement.appendChild(this._titleElement);

        let expandCollapseElement = document.createElement("span");
        expandCollapseElement.className = "acd-sidePane-header-expandCollapseButton";

        this._iconElement = document.createElement("span")
        this._iconElement.classList.add("acd-icon", "acd-icon-header-expanded");
        
        expandCollapseElement.appendChild(this._iconElement);

        this._statusTextElement = document.createElement("span");
        this._statusTextElement.className = "acd-sidePane-header-status";
        this._statusTextElement.innerText = "Hide";

        expandCollapseElement.appendChild(this._statusTextElement);

        expandCollapseElement.onmousedown = (e) => {
            e.preventDefault();

            return true;
        }

        expandCollapseElement.onclick = (e) => {
            this.toggle();

            e.preventDefault();

            return true;
        }

        this._contentElement.appendChild(expandCollapseElement);
        this._rootElement.appendChild(this._contentElement);

        this._sidePaneElement.insertBefore(this._rootElement, this._sidePaneElement.firstChild);
    }

    toggle() {
        if (this._isExpanded) {
            this._iconElement.classList.add("acd-icon-header-collapsed");
            this._iconElement.classList.remove("acd-icon-header-expanded");
            this._statusTextElement.style.display = "none";

            if (this.collapsedTabContainer) {
                this._rootElement.remove();
                this.collapsedTabContainer.appendChild(this._rootElement);
            }
        }
        else {
            this._iconElement.classList.add("acd-icon-header-expanded");
            this._iconElement.classList.remove("acd-icon-header-collapsed");
            this._statusTextElement.style.display = null;

            if (this.collapsedTabContainer) {
                this._rootElement.remove();
                this._sidePaneElement.insertBefore(this._rootElement, this._sidePaneElement.firstChild);
            }
        }

        this._isExpanded = !this._isExpanded;

        if (this.collapsedTabClass) {
            this._rootElement.classList.toggle(this.collapsedTabClass, !this._isExpanded);
            this._contentElement.classList.toggle(this.collapsedTabClass, !this._isExpanded);
        }

        if (this.targetElementsSelector) {
            let targetNodes = document.getElementsByClassName(this.targetElementsSelector);

            for (let i = 0; i < targetNodes.length; i++) {
                (<HTMLElement>targetNodes[i]).style.display = this._isExpanded ? null : "none";
            }
        }

        if (this.onToggled) {
            this.onToggled(this);
        }
    }

    getBoundingRect(): ClientRect {
        return this._rootElement.getBoundingClientRect();
    }
}

abstract class BasePaletteItem extends Designer.DraggableElement {
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

    abstract createPeer(designer: Designer.CardDesigner): Designer.CardElementPeer;
}

class ElementPaletteItem extends BasePaletteItem {
    protected getText(): string {
        return this.typeRegistration.typeName;
    }

    protected getIconClass(): string {
        return this.peerRegistration.iconClass;
    }
    
    readonly typeRegistration: Adaptive.ITypeRegistration<Adaptive.CardElement>;
    readonly peerRegistration: Designer.DesignerPeerRegistrationBase;

    constructor(typeRegistration: Adaptive.ITypeRegistration<Adaptive.CardElement>, peerRegistration: Designer.DesignerPeerRegistrationBase) {
        super();

        this.typeRegistration = typeRegistration;
        this.peerRegistration = peerRegistration;
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

class DesignerApp {
    private _designer: Designer.CardDesigner;
    private _propertySheetHostConfig: Adaptive.HostConfig;
    private _designerHostElement: HTMLElement;
    private _paletteHostElement: HTMLElement;
    private _draggedPaletteItem: BasePaletteItem;
    private _draggedElement: HTMLElement;
    private _currentMousePosition: Designer.IPoint;
    private _card: Adaptive.AdaptiveCard;
    private _hostContainerPicker: Controls.DropDown;
    private _selectedHostContainer: HostContainer;

    public buildTreeView() {
        if (this.treeViewHostElement) {
            this.treeViewHostElement.innerHTML = "";
            this.treeViewHostElement.appendChild(this.designer.rootPeer.treeItem.render());
        }
    }

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
                card.padding = new Adaptive.PaddingDefinition(
                    Adaptive.Spacing.Small,
                    Adaptive.Spacing.Small,
                    Adaptive.Spacing.Small,
                    Adaptive.Spacing.Small
                )
            }

            card.hostConfig = this._propertySheetHostConfig;

            this.propertySheetHostElement.appendChild(card.render());
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

            let categorizedTypes: Object = {};

            for (let i = 0; i < Adaptive.AdaptiveCard.elementTypeRegistry.getItemCount(); i++) {
                let dummyCardElement = Adaptive.AdaptiveCard.elementTypeRegistry.getItemAt(i).createInstance();
                let peerRegistration = Designer.CardDesigner.cardElementPeerRegistry.findTypeRegistration((<any>dummyCardElement).constructor);

                if (peerRegistration) {
                    if (!categorizedTypes.hasOwnProperty(peerRegistration.category)) {
                        categorizedTypes[peerRegistration.category] = [];
                    }

                    let paletteItem = new ElementPaletteItem(
                        Adaptive.AdaptiveCard.elementTypeRegistry.getItemAt(i),
                        peerRegistration
                    )

                    categorizedTypes[peerRegistration.category].push(paletteItem);
                }
            }

            for (let category in categorizedTypes) {
                let node = document.createElement('li');
                node.innerText = category;
                node.className = "acd-palette-category";
                this.paletteHostElement.appendChild(node);

                for (var i = 0; i < categorizedTypes[category].length; i++) {
                    this.addPaletteItem(categorizedTypes[category][i]);
                }
            }

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

            this.buildTreeView();
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
    treeViewHostElement: HTMLElement;
    commandListHostElement: HTMLElement;

    constructor(designerHostElement: HTMLElement) {
        this._propertySheetHostConfig = new Adaptive.HostConfig(
            {
                preExpandSingleShowCardAction: true,
                supportsInteractivity: true,
                fontFamily: "Segoe UI",
                spacing: {
                    small: 10,
                    default: 20,
                    medium: 30,
                    large: 40,
                    extraLarge: 50,
                    padding: 20
                },
                separator: {
                    lineThickness: 1,
                    lineColor: "#EEEEEE"
                },
                textAlign: {
                    right: "right"
                },
                fontSizes: {
                    small: 12,
                    default: 14,
                    medium: 17,
                    large: 21,
                    extraLarge: 26
                },
                fontWeights: {
                    lighter: 200,
                    default: 400,
                    bolder: 600
                },
                imageSizes: {
                    small: 40,
                    medium: 80,
                    large: 160
                },
                containerStyles: {
                    default: {
                        backgroundColor: "#f9f9f9",
                        foregroundColors: {
                            default: {
                                default: "#333333",
                                subtle: "#EE333333"
                            },
                            accent: {
                                default: "#2E89FC",
                                subtle: "#882E89FC"
                            },
                            attention: {
                                default: "#cc3300",
                                subtle: "#DDcc3300"
                            },
                            good: {
                                default: "#54a254",
                                subtle: "#DD54a254"
                            },
                            warning: {
                                default: "#e69500",
                                subtle: "#DDe69500"
                            }
                        }
                    },
                    emphasis: {
                        backgroundColor: "#08000000",
                        foregroundColors: {
                            default: {
                                default: "#333333",
                                subtle: "#EE333333"
                            },
                            accent: {
                                default: "#2E89FC",
                                subtle: "#882E89FC"
                            },
                            attention: {
                                default: "#cc3300",
                                subtle: "#DDcc3300"
                            },
                            good: {
                                default: "#54a254",
                                subtle: "#DD54a254"
                            },
                            warning: {
                                default: "#e69500",
                                subtle: "#DDe69500"
                            }
                        }
                    }
                },
                actions: {
                    maxActions: 5,
                    spacing: Adaptive.Spacing.Default,
                    buttonSpacing: 10,
                    showCard: {
                        actionMode: Adaptive.ShowCardActionMode.Inline,
                        inlineTopMargin: 16
                    },
                    actionsOrientation: Adaptive.Orientation.Horizontal,
                    actionAlignment: Adaptive.ActionAlignment.Left
                },
                adaptiveCard: {
                    allowCustomStyle: true
                },
                imageSet: {
                    imageSize: Adaptive.Size.Medium,
                    maxImageHeight: 100
                },
                factSet: {
                    title: {
                        color: Adaptive.TextColor.Default,
                        size: Adaptive.TextSize.Default,
                        isSubtle: false,
                        weight: Adaptive.TextWeight.Bolder,
                        wrap: true,
                        maxWidth: 150,
                    },
                    value: {
                        color: Adaptive.TextColor.Default,
                        size: Adaptive.TextSize.Default,
                        isSubtle: false,
                        weight: Adaptive.TextWeight.Default,
                        wrap: true,
                    },
                    spacing: 10
                }
            }
        );

        this._propertySheetHostConfig.cssClassNamePrefix = "default";

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

    newCard() {
        let card = {
            type: "AdaptiveCard",
            version: "1.0",
            body: [                
            ]
        }
        
        monacoEditor.setValue(JSON.stringify(card, null, 4));
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
var jsonEditorHorizontalSplitter: Splitter;
var propertySheetVerticalSplitter: Splitter;
var treeViewVerticalSplitter: Splitter;
var jsonEditorPaneHeader: SidePaneHeader;

function updateJsonEditorLayout() {
    if (isMonacoEditorLoaded) {
        // Monaco is very finicky. It will apparently only properly layout if
        // its direct container has an explicit height.
        let jsonEditorPaneRect = document.getElementById("jsonEditorPane").getBoundingClientRect();
        let jsonEditorHeaderRect = jsonEditorPaneHeader.getBoundingRect();

        let jsonEditorHost = document.getElementById("jsonEditorHost");

        jsonEditorHost.style.height = (jsonEditorPaneRect.height - jsonEditorHeaderRect.height) + "px";

        monacoEditor.layout();
    }
}

function updateFullLayout() {
    scheduleLayoutUpdate();
    updateJsonEditorLayout();
}

window.onload = () => {
    let treeViewPaneHeader = new SidePaneHeader(document.getElementById("treeViewPane"), "Visual tree view");
    treeViewPaneHeader.collapsedTabContainer = document.getElementById("rightCollapsedPaneTabHost");
    treeViewPaneHeader.collapsedTabClass = "rotated90DegreesClockwise";
    treeViewPaneHeader.targetElementsSelector = "selector-treeView";
    treeViewPaneHeader.onToggled = (sender: SidePaneHeader) => {
        updateFullLayout();
    };

    let propertySheetPaneHeader = new SidePaneHeader(document.getElementById("propertySheetPane"), "Element properties");
    propertySheetPaneHeader.collapsedTabContainer = treeViewPaneHeader.collapsedTabContainer;
    propertySheetPaneHeader.collapsedTabClass = "rotated90DegreesClockwise";
    propertySheetPaneHeader.targetElementsSelector = "selector-propertySheet";
    propertySheetPaneHeader.onToggled = (sender: SidePaneHeader) => {
        updateFullLayout();
    };

    let toolPalettePaneHeader = new SidePaneHeader(document.getElementById("toolPalettePane"), "Tool box");
    toolPalettePaneHeader.collapsedTabContainer = document.getElementById("leftCollapsedPaneTabHost");
    toolPalettePaneHeader.collapsedTabClass = "rotated90DegreesCounterClockwise";
    toolPalettePaneHeader.targetElementsSelector = "selector-toolPalette";
    toolPalettePaneHeader.onToggled = (sender: SidePaneHeader) => {
        updateFullLayout();
    };

    jsonEditorPaneHeader = new SidePaneHeader(document.getElementById("jsonEditorPane"), "JSON");
    jsonEditorPaneHeader.collapsedTabContainer = document.getElementById("bottomCollapsedPaneTabHost");
    jsonEditorPaneHeader.targetElementsSelector = "selector-jsonEditor";
    jsonEditorPaneHeader.onToggled = (sender: SidePaneHeader) => {
        updateFullLayout();
    };

    let fullScreenHandler = new FullScreenHandler();
    fullScreenHandler.onFullScreenChanged = (isFullScreen: boolean) => {
        document.getElementById("btnToggleFullScreen").innerText = isFullScreen ? "Exit full screen" : "Enter full screen";

        updateFullLayout();
    }

    document.getElementById("btnToggleFullScreen").onclick = (e) => {
        fullScreenHandler.toggleFullScreen();
    }

    new Clipboard(
        document.getElementById("btnCopyToClipboard"),
        {
            text: function () {
                return JSON.stringify(app.card.toJSON(), null, 4);
            }
        });

    document.getElementById("btnNewCard").onclick = (e) => {
        app.newCard();
    }

    jsonEditorHorizontalSplitter = new Splitter(document.getElementById("horizontalSplitter"), document.getElementById("jsonEditorPane"));
    jsonEditorHorizontalSplitter.onRezized = (splitter: Splitter) => {
        updateJsonEditorLayout();
    }

    propertySheetVerticalSplitter = new Splitter(document.getElementById("propertyVerticalSplitter"), document.getElementById("propertySheetPane"));
    propertySheetVerticalSplitter.isVertical = true;
    propertySheetVerticalSplitter.minimum = 230;
    propertySheetVerticalSplitter.onRezized = (splitter: Splitter) => {
        scheduleLayoutUpdate();
    }

    treeViewVerticalSplitter = new Splitter(document.getElementById("treeViewVerticalSplitter"), document.getElementById("treeViewPane"));
    treeViewVerticalSplitter.isVertical = true;
    treeViewVerticalSplitter.minimum = 140;
    treeViewVerticalSplitter.onRezized = (splitter: Splitter) => {
        scheduleLayoutUpdate();
    }

    let card = new Adaptive.AdaptiveCard();
    card.onImageLoaded = (image: Adaptive.Image) => {
        scheduleLayoutUpdate();
    }

    app = new DesignerApp(document.getElementById("designerHost"));
    app.propertySheetHostElement = document.getElementById("propertySheetHost");
    app.treeViewHostElement = document.getElementById("treeViewHost");
    app.commandListHostElement = document.getElementById("commandsHost");
    app.paletteHostElement = document.getElementById("toolPalette");

    app.createContainerPicker().attach(document.getElementById("containerPickerHost"));

    window.addEventListener("pointermove", (e: PointerEvent) => { app.handlePointerMove(e); });
    window.addEventListener("resize", () => { scheduleLayoutUpdate(); });
    window.addEventListener("pointerup", (e: PointerEvent) => { app.handlePointerUp(e); });

    app.card = card;

    loadMonacoEditor(adaptiveCardSchema, monacoEditorLoaded);

    updateCardFromJson();
};
