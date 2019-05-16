// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Clipboard from "clipboard";
import * as Adaptive from "adaptivecards";
import * as monaco from 'monaco-editor/esm/vs/editor/editor.api';
import * as Constants from "./constants";
import * as Designer from "./card-designer-surface";
import * as DesignerPeers from "./designer-peers";
import { HostContainer } from "./containers/host-container";
import { adaptiveCardSchema } from "./adaptive-card-schema";
import { FullScreenHandler } from "./fullscreen-handler";
import { Toolbar, ToolbarButton, ToolbarChoicePicker, ToolbarElementAlignment } from "./toolbar";
import { SidePane, SidePaneOrientation } from "./side-pane";
import { Splitter } from "./splitter";
import { IPoint, Utils } from "./miscellaneous";
import { BasePaletteItem, ElementPaletteItem } from "./tool-palette";
import { DefaultContainer } from "./containers/default/default-container";

export class CardDesigner {
    private static internalProcessMarkdown(text: string, result: Adaptive.IMarkdownProcessingResult) {
        if (CardDesigner.onProcessMarkdown) {
            CardDesigner.onProcessMarkdown(text, result);
        }
        else {
            // Check for markdownit
            if (window["markdownit"]) {
                result.outputHtml = window["markdownit"]().render(text);
                result.didProcess = true;
            }
		}
    }

    static onProcessMarkdown: (text: string, result: Adaptive.IMarkdownProcessingResult) => void = null;

    private static MAX_UNDO_STACK_SIZE = 50;

    private _monacoEditor: monaco.editor.IStandaloneCodeEditor;
    private _hostContainers: Array<HostContainer>;
    private _isMonacoEditorLoaded: boolean = false;
    private _designerSurface: Designer.CardDesignerSurface;
    private _propertySheetHostConfig: Adaptive.HostConfig;
    private _designerHostElement: HTMLElement;
    private _draggedPaletteItem: BasePaletteItem;
    private _draggedElement: HTMLElement;
    private _currentMousePosition: IPoint;
    private _card: Adaptive.AdaptiveCard;
    private _activeHostContainer: HostContainer;
    private _undoStack: Array<object> = [];
    private _undoStackIndex: number = -1;
    private _toolPalettePane: SidePane;
    private _jsonEditorPane: SidePane;
    private _propertySheetPane: SidePane;
	private _treeViewPane: SidePane;
	private _assetPath: string;

    private buildTreeView() {
        if (this._treeViewPane.content) {
            this._treeViewPane.content.innerHTML = "";
            this._treeViewPane.content.appendChild(this.designerSurface.rootPeer.treeItem.render());
		}
    }

    private buildPropertySheet(peer: DesignerPeers.DesignerPeer) {
        if (this._propertySheetPane.content) {
            this._propertySheetPane.content.innerHTML = "";

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

            this._propertySheetPane.content.appendChild(card.render());
        }
    }

    private addPaletteItem(paletteItem: BasePaletteItem, hostElement: HTMLElement) {
        paletteItem.render();
        paletteItem.onStartDrag = (sender: BasePaletteItem) => {
            this._draggedPaletteItem = sender;

            this._draggedElement = sender.cloneElement();
            this._draggedElement.style.position = "absolute";
            this._draggedElement.style.left = this._currentMousePosition.x + "px";
            this._draggedElement.style.top = this._currentMousePosition.y + "px";

            document.body.appendChild(this._draggedElement);
        }

        hostElement.appendChild(paletteItem.renderedElement);
    }

    private buildPalette() {
        this._toolPalettePane.content.innerHTML = "";

        let categorizedTypes: Object = {};

        for (let i = 0; i < Adaptive.AdaptiveCard.elementTypeRegistry.getItemCount(); i++) {
            let dummyCardElement = Adaptive.AdaptiveCard.elementTypeRegistry.getItemAt(i).createInstance();
            let peerRegistration = Designer.CardDesignerSurface.cardElementPeerRegistry.findTypeRegistration((<any>dummyCardElement).constructor);

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

            this._toolPalettePane.content.appendChild(node);

            for (var i = 0; i < categorizedTypes[category].length; i++) {
                this.addPaletteItem(categorizedTypes[category][i], this._toolPalettePane.content);
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

    private endDrag() {
        if (this._draggedPaletteItem) {
            this._draggedPaletteItem.endDrag();
            this._draggedElement.remove();

            this._draggedPaletteItem = null;
            this._draggedElement = null;
        }
    }

    private renderErrorPaneElement(message: string, cardObject?: Adaptive.CardObject): HTMLElement {
        let errorElement = document.createElement("div");
        errorElement.className = "acd-error-pane-message";

        if (cardObject) {
            errorElement.classList.add("selectable");
            errorElement.title = "Click to select this element";
            errorElement.onclick = (e) => {
                let peer = this.designerSurface.findPeer(cardObject);

                if (peer) {
                    peer.isSelected = true;
                    peer.scrollIntoView();
                }
            }
        }

        errorElement.innerText = message;

        return errorElement;
    }

    private recreateDesignerSurface() {
        let styleSheetLinkElement = <HTMLLinkElement>document.getElementById("adaptiveCardStylesheet");

        if (styleSheetLinkElement == null) {
            styleSheetLinkElement = document.createElement("link");
            styleSheetLinkElement.id = "adaptiveCardStylesheet";

            document.getElementsByTagName("head")[0].appendChild(styleSheetLinkElement);
        }

        styleSheetLinkElement.rel = "stylesheet";
		styleSheetLinkElement.type = "text/css";

		if(Utils.isAbsoluteUrl(this.activeHostContainer.styleSheet))
        {
			styleSheetLinkElement.href = this.activeHostContainer.styleSheet;
		}
		else
		{
			styleSheetLinkElement.href = Utils.joinPaths(this._assetPath, this.activeHostContainer.styleSheet);
		}

        let designerBackground = document.getElementById("designerBackground");

        if (designerBackground) {
            designerBackground.style.backgroundColor = this.activeHostContainer.getBackgroundColor();
        }

        this.activeHostContainer.initialize();

        this._designerHostElement.innerHTML = "";
        this.activeHostContainer.renderTo(this._designerHostElement);

        this._designerSurface = new Designer.CardDesignerSurface(this.activeHostContainer.cardHost);
        this._designerSurface.fixedHeightCard = this.activeHostContainer.isFixedHeight;
        this._designerSurface.onSelectedPeerChanged = (peer: DesignerPeers.DesignerPeer) => {
            this.buildPropertySheet(peer);
        };
        this._designerSurface.onLayoutUpdated = (isFullRefresh: boolean) => {
            if (isFullRefresh) {
                this.scheduleUpdateJsonFromCard();
            }

            this.buildTreeView();
        };
        this._designerSurface.onCardValidated = (parseErrors: Array<Adaptive.IValidationError>, validationResults: Adaptive.ValidationResults) => {
            let errorPane = document.getElementById("errorPane");
            errorPane.innerHTML = "";

            if (parseErrors.length > 0) {
                let errorMessages: Array<string> = [];

                for (let error of parseErrors) {
                    if (errorMessages.indexOf(error.message) < 0) {
                        errorMessages.push(error.message);
                    }
                }

                for (let message of errorMessages) {
                    errorPane.appendChild(this.renderErrorPaneElement("[Error] " + message));
                }
            }

            if (validationResults.failures.length > 0) {
                for (let failure of validationResults.failures) {
                    for (let error of failure.errors) {
                        errorPane.appendChild(this.renderErrorPaneElement("[" + failure.cardObject.getJsonTypeName() + "] " + error.message, failure.cardObject));
                    }
                }
            }

            if (errorPane.childElementCount > 0) {
                errorPane.classList.remove("acd-hidden");
            }
            else {
                errorPane.classList.add("acd-hidden");
            }
        };

        this.buildPalette();
        this.buildPropertySheet(null);

        if (this._card) {
            this._card.hostConfig = this.activeHostContainer.getHostConfig();
        }

        this._designerSurface.card = this._card;
    }

    private activeHostContainerChanged() {
        this.recreateDesignerSurface();
    }

    public updateJsonEditorLayout() {
        if (this._isMonacoEditorLoaded) {
            // Monaco is very finicky. It will apparently only properly layout if
            // its direct container has an explicit height.
            let jsonEditorPaneRect = this._jsonEditorPane.attachedTo.getBoundingClientRect();
            let jsonEditorHeaderRect = this._jsonEditorPane.getHeaderBoundingRect();

            this._jsonEditorPane.content.style.height = (jsonEditorPaneRect.height - jsonEditorHeaderRect.height) + "px";

            this._monacoEditor.layout();
        }
    }

    private updateFullLayout() {
        this.scheduleLayoutUpdate();
        this.updateJsonEditorLayout();
    }

    private jsonUpdateTimer: any;
    private cardUpdateTimer: any;
    private updateLayoutTimer: any;

    private preventCardUpdate: boolean = false;

    private setJsonPayload(payload: object) {
        this._monacoEditor.setValue(JSON.stringify(payload, null, 4));
    }

    private updateJsonFromCard(addToUndoStack: boolean = true) {
        try {
            this.preventCardUpdate = true;

            if (!this.preventJsonUpdate && this._isMonacoEditorLoaded) {
                let cardPayload = this.card.toJSON();

                if (addToUndoStack) {
                    this.addToUndoStack(cardPayload);
                }

                this.setJsonPayload(cardPayload);
            }
        }
        finally {
            this.preventCardUpdate = false;
        }
    }

    private scheduleUpdateJsonFromCard() {
        clearTimeout(this.jsonUpdateTimer);

        if (!this.preventJsonUpdate) {
            this.jsonUpdateTimer = setTimeout(() => { this.updateJsonFromCard(); }, 100);
        }
    }

    private preventJsonUpdate: boolean = false;

    private getCurrentJsonPayload(): string {
        return this._isMonacoEditorLoaded ? this._monacoEditor.getValue() : Constants.defaultPayload;
    }

    private updateCardFromJson() {
        try {
            this.preventJsonUpdate = true;

            if (!this.preventCardUpdate) {
                this.designerSurface.setCardPayloadAsString(this.getCurrentJsonPayload());
            }
        }
        finally {
            this.preventJsonUpdate = false;
        }
    }

    private scheduleUpdateCardFromJson() {
        clearTimeout(this.cardUpdateTimer);

        if (!this.preventCardUpdate) {
            this.cardUpdateTimer = setTimeout(() => { this.updateCardFromJson(); }, 100);
        }
    }

    private scheduleLayoutUpdate() {
        clearTimeout(this.updateLayoutTimer);

        this.updateLayoutTimer = setTimeout(() => { this.designerSurface.updateLayout(false); }, 50);
    }

    private _fullScreenHandler = new FullScreenHandler();
    private _fullScreenButton: ToolbarButton;
    private _hostContainerChoicePicker: ToolbarChoicePicker;
    private _undoButton: ToolbarButton;
    private _redoButton: ToolbarButton;
    private _newCardButton: ToolbarButton;
    private _copyJSONButton: ToolbarButton;

    private prepareToolbar() {
        this._fullScreenButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.FullScreen,
            "Enter Full Screen",
            "acd-icon-fullScreen",
            (sender) => { this._fullScreenHandler.toggleFullScreen(); });
        this._fullScreenButton.displayCaption = false;
        this._fullScreenButton.toolTip = "Enter full screen";
        this._fullScreenButton.alignment = ToolbarElementAlignment.Right;

        this.toolbar.addElement(this._fullScreenButton);

        if (this._hostContainers && this._hostContainers.length > 0) {
            this._hostContainerChoicePicker = new ToolbarChoicePicker(CardDesigner.ToolbarCommands.HostAppPicker);
            this._hostContainerChoicePicker.separator = true;
            this._hostContainerChoicePicker.label = "Select host app:"
            this._hostContainerChoicePicker.width = 350;

            for (let i = 0; i < this._hostContainers.length; i++) {
                this._hostContainerChoicePicker.choices.push(
                    {
                        name: this._hostContainers[i].name,
                        value: i.toString(),
                    }
                );
            }

            this._hostContainerChoicePicker.onChanged = (sender) => {
                this.activeHostContainer = this._hostContainers[Number.parseInt(this._hostContainerChoicePicker.value)];

                this.activeHostContainerChanged();
            }

            this.toolbar.addElement(this._hostContainerChoicePicker);
        }

        this._undoButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.Undo,
            "Undo",
            "acd-icon-undo",
            (sender) => { this.undo(); });
        this._undoButton.separator = true;
        this._undoButton.toolTip = "Undo your last change";
        this._undoButton.isEnabled = false;
        this._undoButton.displayCaption = false;

        this.toolbar.addElement(this._undoButton);

        this._redoButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.Redo,
            "Redo",
            "acd-icon-redo",
            (sender) => { this.redo(); });
        this._redoButton.toolTip = "Redo your last changes";
        this._redoButton.isEnabled = false;
        this._redoButton.displayCaption = false;

        this.toolbar.addElement(this._redoButton);

        this._newCardButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.NewCard,
            "New card",
            "acd-icon-newCard",
            (sender) => { this.newCard(); });
            this._newCardButton.separator = true;

        this.toolbar.addElement(this._newCardButton);

        this._copyJSONButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.CopyJSON,
            "Copy JSON",
            "acd-icon-copy");
        this.toolbar.addElement(this._copyJSONButton);

        this._fullScreenHandler = new FullScreenHandler();
        this._fullScreenHandler.onFullScreenChanged = (isFullScreen: boolean) => {
            this._fullScreenButton.toolTip = isFullScreen ? "Exit full screen" : "Enter full screen";

            this.updateFullLayout();
        }
    }

    private onResize() {
        this._monacoEditor.layout();
    }

    private loadMonaco(callback: () => void) {
        // window["require"].config({ paths: { 'vs': './editor/monaco/min/vs' } });
        // window["require"](
        //     ['vs/editor/editor.main'],
        //     function () {
        //         callback();
		//     });

		// If loaded using WebPack this should work, but it's not right now...
		//callback();
    }

    public monacoModuleLoaded(monaco: any = null) {
		if (!monaco) {
            monaco = window["monaco"];
        }

        let monacoConfiguration = {
            schemas: [
                {
                    uri: "http://adaptivecards.io/schemas/adaptive-card.json",
                    schema: adaptiveCardSchema,
                    fileMatch: ["*"],
                }
            ],
            validate: false,
            allowComments: true
        }

		this._jsonEditorPane.content = document.createElement("div");
		this._jsonEditorPane.content.style.overflow = "hidden";

		// TODO: set this in our editor instead of defaults
        monaco.languages.json.jsonDefaults.setDiagnosticsOptions(monacoConfiguration);

        this._monacoEditor = monaco.editor.create(
            this._jsonEditorPane.content,
            {
                folding: true,
                // validate: false,
                fontSize: 13.5,
                language: 'json',
                minimap: {
                    enabled: false
                }
            }
        );

        this._monacoEditor.onDidChangeModelContent(() => { this.scheduleUpdateCardFromJson(); });

        window.addEventListener('resize', () => { this.onResize(); });

        this._isMonacoEditorLoaded = true;

        this.updateJsonEditorLayout();
        this.updateJsonFromCard(false);
    }

    private updateToolbar() {
        this._undoButton.isEnabled = this.canUndo;
        this._redoButton.isEnabled = this.canRedo;
    }

    private addToUndoStack(payload: object) {
        let doAdd: boolean = true;

        if (this._undoStack.length > 0) {
            doAdd = this._undoStack[this._undoStack.length - 1] != payload;
        }

        if (doAdd) {
            let undoPayloadsToDiscard = this._undoStack.length - (this._undoStackIndex + 1);

            if (undoPayloadsToDiscard > 0) {
                this._undoStack.splice(this._undoStackIndex + 1, undoPayloadsToDiscard);
            }

            this._undoStack.push(payload);

            if (this._undoStack.length > CardDesigner.MAX_UNDO_STACK_SIZE) {
                this._undoStack.splice(0, 1);
            }

            this._undoStackIndex = this._undoStack.length - 1;

            this.updateToolbar();
        }
    }

    private handlePointerUp(e: PointerEvent) {
        this.endDrag();
        this.designerSurface.endDrag();
    }

    private handlePointerMove(e: PointerEvent) {
        this._currentMousePosition = { x: e.x, y: e.y };

        let isPointerOverDesigner = this.designerSurface.isPointerOver(this._currentMousePosition.x, this._currentMousePosition.y);
        let peerDropped = false;

        if (this._draggedPaletteItem && isPointerOverDesigner) {
            let peer = this._draggedPaletteItem.createPeer(this.designerSurface);

            let clientCoordinates = this.designerSurface.pageToClientCoordinates(this._currentMousePosition.x, this._currentMousePosition.y);

            if (this.designerSurface.tryDrop(clientCoordinates, peer)) {
                this.endDrag();

                this.designerSurface.startDrag(peer);

                peerDropped = true;
            }
        }

        if (!peerDropped && this._draggedElement) {
            this._draggedElement.style.left = this._currentMousePosition.x - 10 + "px";
            this._draggedElement.style.top = this._currentMousePosition.y - 10 + "px";
        }
    }

    readonly toolbar: Toolbar = new Toolbar();

    constructor(hostContainers: Array<HostContainer> = null) {
        Adaptive.AdaptiveCard.onProcessMarkdown = (text: string, result: Adaptive.IMarkdownProcessingResult) => {
            CardDesigner.internalProcessMarkdown(text, result);
        }

        this._hostContainers = hostContainers ? hostContainers : [];

        this.prepareToolbar();

        this._propertySheetHostConfig = new Adaptive.HostConfig(
            {
                preExpandSingleShowCardAction: true,
                supportsInteractivity: true,
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
                imageSizes: {
                    small: 40,
                    medium: 80,
                    large: 160
                },
                fontTypes: {
                    default: {
                        fontFamily: "'Segoe UI', Tahoma, Geneva, Verdana, sans-serif",
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
                        }
                    },
                    monospace: {
                        fontFamily: "'Courier New', Courier, monospace",
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
                        }
                    }
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
                    },
                    accent: {
                        backgroundColor: "#C7DEF9",
                        foregroundColors: {
                            default: {
                                default: "#333333",
                                subtle: "#EE333333"
                            },
                            dark: {
                                default: "#000000",
                                subtle: "#66000000"
                            },
                            light: {
                                default: "#FFFFFF",
                                subtle: "#33000000"
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
                    good: {
                        backgroundColor: "#CCFFCC",
                        foregroundColors: {
                            default: {
                                default: "#333333",
                                subtle: "#EE333333"
                            },
                            dark: {
                                default: "#000000",
                                subtle: "#66000000"
                            },
                            light: {
                                default: "#FFFFFF",
                                subtle: "#33000000"
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
                    attention: {
                        backgroundColor: "#FFC5B2",
                        foregroundColors: {
                            default: {
                                default: "#333333",
                                subtle: "#EE333333"
                            },
                            dark: {
                                default: "#000000",
                                subtle: "#66000000"
                            },
                            light: {
                                default: "#FFFFFF",
                                subtle: "#33000000"
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
                    warning: {
                        backgroundColor: "#FFE2B2",
                        foregroundColors: {
                            default: {
                                default: "#333333",
                                subtle: "#EE333333"
                            },
                            dark: {
                                default: "#000000",
                                subtle: "#66000000"
                            },
                            light: {
                                default: "#FFFFFF",
                                subtle: "#33000000"
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
    }

    attachTo(root: HTMLElement)  {
        let styleSheetLinkElement = document.createElement("link");
        styleSheetLinkElement.id = "__ac-designer";
        styleSheetLinkElement.rel = "stylesheet";
		styleSheetLinkElement.type = "text/css";
        styleSheetLinkElement.href = Utils.joinPaths(this._assetPath, "adaptivecards-designer.css");

        document.getElementsByTagName("head")[0].appendChild(styleSheetLinkElement);

        if (this._hostContainers && this._hostContainers.length > 0) {
            this._activeHostContainer = this._hostContainers[0];
        }
        else {
            this._activeHostContainer = new DefaultContainer("Default", "default-container.css");
        }

        root.style.flex = "1 1 auto";
        root.style.display = "flex";
        root.style.flexDirection = "column";
        root.style.overflow = "hidden";

        root.innerHTML =
            '<div id="toolbarHost"></div>' +
            '<div class="content" style="display: flex; flex: 1 1 auto; overflow-y: hidden;">' +
                '<div id="leftCollapsedPaneTabHost" class="acd-verticalCollapsedTabContainer" style="border-right: 1px solid #D2D2D2;"></div>' +
                '<div id="toolPalettePane" class="selector-toolPalette" style="display: flex; flex-direction: column; background-color: white; border-right: 1px solid #D2D2D2;">' +
                    '<div id="toolPaletteHost" class="acd-dockedPane" style="overflow: auto"></div>' +
                '</div>' +
                '<div style="display: flex; flex-direction: column; flex: 1 1 100%; overflow: hidden;">' +
                    '<div style="display: flex; flex: 1 1 100%; overflow: hidden;">' +
                        '<div id="designerBackground" style="flex: 1 1 70%; background-color: #F6F6F6; display: flex; flex-direction: column; overflow: auto;">' +
                            '<div style="flex: 1 1 100%; overflow: auto;">' +
                                '<div id="designerHost" style="margin: 20px 40px 20px 20px;"></div>' +
                            '</div>' +
                            '<div id="errorPane" class="acd-error-pane acd-hidden"></div>' +
                        '</div>' +
                        '<div id="treeViewSplitter" class="acd-vertical-splitter selector-treeView"></div>' +
                        '<div id="treeViewPane" class="acd-treeView-pane selector-treeView">' +
                            '<div id="treeViewHost" class="acd-treeView-host"></div>' +
                        '</div>' +
                        '<div id="propertySheetSplitter" class="acd-vertical-splitter selector-propertySheet"></div>' +
                        '<div id="propertySheetPane" class="acd-propertySheet-pane selector-propertySheet">' +
                            '<div id="propertySheetHost" class="acd-propertySheet-host"></div>' +
                        '</div>' +
                    '</div>' +
                    '<div id="jsonEditorSplitter" class="acd-horizontal-splitter selector-jsonEditor"></div>' +
                    '<div id="jsonEditorPane" class="acd-json-editor-pane selector-jsonEditor"></div>' +
                    '<div id="bottomCollapsedPaneTabHost" style="border-top: 1px solid #D2D2D2;"></div>' +
                '</div>' +
                '<div id="rightCollapsedPaneTabHost" class="acd-verticalCollapsedTabContainer" style="border-left: 1px solid #D2D2D2;"></div>' +
            '</div>';

        this.toolbar.attachTo(document.getElementById("toolbarHost"));

        new Clipboard(
            this._copyJSONButton.renderedElement,
            {
                text: (trigger) => { return JSON.stringify(this.card.toJSON(), null, 4); }
            });

        // Tool palette pane
        this._toolPalettePane = new SidePane(
            document.getElementById("toolPalettePane"),
            document.getElementById("leftCollapsedPaneTabHost"),
            "toolPalette",
            "Tool box",
            "selector-toolPalette");
        this._toolPalettePane.onToggled = (sender: SidePane) => {
            this.updateFullLayout();
        }
        this._toolPalettePane.content = document.getElementById("toolPaletteHost");

        // Splitter for JSON editor pane
        let jsonEditorSplitter = new Splitter(
            document.getElementById("jsonEditorSplitter"),
            document.getElementById("jsonEditorPane"),
            false);
        jsonEditorSplitter.onResized = (splitter: Splitter, newSize: number) => {
            this.updateJsonEditorLayout();

            this._jsonEditorPane.saveState();
        }

        // JSON editor pane
        this._jsonEditorPane = new SidePane(
            document.getElementById("jsonEditorPane"),
            document.getElementById("bottomCollapsedPaneTabHost"),
            "jsonEditor",
            "JSON",
            "selector-jsonEditor",
            SidePaneOrientation.Horizontal
        )
        this._jsonEditorPane.onToggled = (sender: SidePane) => {
            this.updateFullLayout();
        }
        this._jsonEditorPane.content = document.createElement("div");
        this._jsonEditorPane.content.style.padding = "8px";
        this._jsonEditorPane.content.innerText = "Loading editor..."

        // Splitter for property sheet pane
        let propertySheetSplitter = new Splitter(
            document.getElementById("propertySheetSplitter"),
            document.getElementById("propertySheetPane"),
            true);
        propertySheetSplitter.minimum = 230;
        propertySheetSplitter.onResized = (splitter: Splitter, newSize: number) => {
            this.scheduleLayoutUpdate();

            this._propertySheetPane.saveState();
        }

        // Property sheet pane
        this._propertySheetPane = new SidePane(
            document.getElementById("propertySheetPane"),
            document.getElementById("rightCollapsedPaneTabHost"),
            "propertySheet",
            "Element properties",
            "selector-propertySheet");
        this._propertySheetPane.onToggled = (sender: SidePane) => {
            this.updateFullLayout();
        };
        this._propertySheetPane.content = document.getElementById("propertySheetHost");

        // Splitter for tree view pane
        let treeViewSplitter = new Splitter(
            document.getElementById("treeViewSplitter"),
            document.getElementById("treeViewPane"),
            true);
        treeViewSplitter.minimum = 140;
        treeViewSplitter.onResized = (splitter: Splitter, newSize: number) => {
            this.scheduleLayoutUpdate();

            this._treeViewPane.saveState();
        }

        // Tree view pane
        this._treeViewPane = new SidePane(
            document.getElementById("treeViewPane"),
            document.getElementById("rightCollapsedPaneTabHost"),
            "treeView",
            "Visual tree view",
            "selector-treeView");
        this._treeViewPane.onToggled = (sender: SidePane) => {
            this.updateFullLayout();
        };
        this._treeViewPane.content = document.getElementById("treeViewHost");

        this._designerHostElement = document.getElementById("designerHost")

        this.recreateDesignerSurface();


        this.loadMonaco(() => { this.monacoModuleLoaded(); });

        window.addEventListener("pointermove", (e: PointerEvent) => { this.handlePointerMove(e); });
        window.addEventListener("resize", () => { this.scheduleLayoutUpdate(); });
        window.addEventListener("pointerup", (e: PointerEvent) => { this.handlePointerUp(e); });

        let card = new Adaptive.AdaptiveCard();
        card.onImageLoaded = (image: Adaptive.Image) => {
            this.scheduleLayoutUpdate();
        }

        this.card = card;
    }

    undo() {
        if (this.canUndo) {
            this._undoStackIndex--;

            let card = this._undoStack[this._undoStackIndex];

            this.setJsonPayload(card);

            this.updateToolbar();
        }
    }

    redo() {
        if (this._undoStackIndex < this._undoStack.length - 1) {
            this._undoStackIndex++;

            let card = this._undoStack[this._undoStackIndex];

            this.setJsonPayload(card);

            this.updateToolbar();
        }
    }

    newCard() {
        let card = {
            type: "AdaptiveCard",
            version: "1.0",
            body: [
            ]
        }

        this.setJsonPayload(card);
    }

    setCard(payload: object) {
        try {
            this.preventJsonUpdate = true;

            if (!this.preventCardUpdate) {
                this.designerSurface.setCardPayloadAsObject(payload);
            }
        }
        finally {
            this.preventJsonUpdate = false;
        }

        this.updateJsonFromCard();
    }

    getCard(): object {
        return this.designerSurface.card.toJSON();
    }

    get activeHostContainer(): HostContainer {
        return this._activeHostContainer;
    }

    set activeHostContainer(value: HostContainer) {
        if (this._activeHostContainer !== value) {
            this._activeHostContainer = value;

            this.activeHostContainerChanged();
        }
    }

    get canUndo(): boolean {
        return this._undoStackIndex >= 1;
    }

    get canRedo(): boolean {
        return this._undoStackIndex < this._undoStack.length - 1;
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
                this._card.hostConfig = this.activeHostContainer.getHostConfig();
            }

            this.recreateDesignerSurface();
            this.updateCardFromJson();
        }
    }

    get designerSurface(): Designer.CardDesignerSurface {
        return this._designerSurface;
    }

    get treeViewPane(): SidePane {
        return this._treeViewPane;
    }

    get propertySheetPane(): SidePane {
        return this._propertySheetPane;
    }

    get jsonEditorPane(): SidePane {
        return this._jsonEditorPane;
    }

    get toolPalettePane(): SidePane {
        return this._toolPalettePane;
	}

	get assetPath(): string {
		return this._assetPath;
	}

	set assetPath(value: string) {
		this._assetPath = value;
	}
}

export module CardDesigner {
    export class ToolbarCommands {
        static FullScreen = "__fullScreenButton";
        static HostAppPicker = "__hostAppPicker";
        static Undo = "__undoButton";
        static Redo = "__redoButton";
        static NewCard = "__newCardButton";
        static CopyJSON = "__copyJsonButton";
    }
}
