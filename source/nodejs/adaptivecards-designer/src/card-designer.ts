// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Clipboard from "clipboard";
import * as Adaptive from "adaptivecards";
import * as monaco from "monaco-editor";
import * as Constants from "./constants";
import * as Designer from "./card-designer-surface";
import * as DesignerPeers from "./designer-peers";
import { OpenSampleDialog } from "./open-sample-dialog";
import { HostContainer } from "./containers/host-container";
import { adaptiveCardSchema } from "./adaptive-card-schema";
import { FullScreenHandler } from "./fullscreen-handler";
import { Toolbar, ToolbarButton, ToolbarChoicePicker, ToolbarElementAlignment } from "./toolbar";
import { IPoint, Utils, defaultHostConfig } from "./miscellaneous";
import { BasePaletteItem, ElementPaletteItem, DataPaletteItem, CustomPaletteItem } from "./tool-palette";
import { DefaultContainer } from "./containers/default/default-container";
import { SidePanel, SidePanelAlignment } from "./side-panel";
import { Toolbox, IToolboxCommand } from "./tool-box";
import { FieldDefinition } from "./data";
import { DataTreeItem } from "./data-treeitem";
import { Strings } from "./strings";
import * as Shared from "./shared";
import { TreeView } from "./tree-view";
import { SampleCatalogue } from "./catalogue";

export class CardDesigner extends Designer.DesignContext {
    private static internalProcessMarkdown(text: string, result: Adaptive.IMarkdownProcessingResult) {
        if (CardDesigner.onProcessMarkdown) {
            CardDesigner.onProcessMarkdown(text, result);
        } else {
            // Check for markdownit
            if (window["markdownit"]) {
                result.outputHtml = window["markdownit"]().render(text);
                result.didProcess = true;
            }
		}
    }

    static onProcessMarkdown: (text: string, result: Adaptive.IMarkdownProcessingResult) => void = null;

    private static MAX_UNDO_STACK_SIZE = 50;

    private _isAttached: boolean = false;
    private _cardEditor: monaco.editor.IStandaloneCodeEditor;
    private _sampleDataEditor: monaco.editor.IStandaloneCodeEditor;
    private _hostContainers: Array<HostContainer>;
    private _isMonacoEditorLoaded: boolean = false;
    private _designerSurface: Designer.CardDesignerSurface;
    private _designerHostElement: HTMLElement;
    private _draggedPaletteItem: BasePaletteItem;
    private _draggedElement: HTMLElement;
    private _currentMousePosition: IPoint;
    private _hostContainer: HostContainer;
    private _undoStack: Array<object> = [];
    private _undoStackIndex: number = -1;
    private _startDragPayload: object;
    private _toolPaletteToolbox: Toolbox;
    private _propertySheetToolbox: Toolbox;
    private _treeViewToolbox: Toolbox;
    private _jsonEditorsPanel: SidePanel;
    private _cardEditorToolbox: Toolbox;
    private _sampleDataEditorToolbox: Toolbox;
    private _dataToolbox: Toolbox;
    private _assetPath: string;
    private _dataStructure: FieldDefinition;
    private _sampleData: any;
    private _bindingPreviewMode: Designer.BindingPreviewMode = Designer.BindingPreviewMode.NoPreview;
    private _customPeletteItems: CustomPaletteItem[];
    private _sampleCatalogue: SampleCatalogue = new SampleCatalogue();

    private togglePreview() {
        this._designerSurface.isPreviewMode = !this._designerSurface.isPreviewMode;

        if (this._designerSurface.isPreviewMode) {
            this._togglePreviewButton.toolTip = "Return to Design mode";
            this._designerSurface.setCardPayloadAsString(this.getCurrentCardEditorPayload());
        }
        else {
            this._togglePreviewButton.toolTip = "Switch to Preview mode";
            this.updateCardFromJson(false);
        }

        this.buildTreeView();
    }

    private buildTreeView() {
        if (this._treeViewToolbox.content) {
            this._treeViewToolbox.content.innerHTML = "";

            if (this.designerSurface.isPreviewMode) {
                this.treeViewToolbox.content.innerHTML =
                    '<div style="padding: 8px; display: flex; justify-content: center;">' +
                        '<div>The Card Structure isn\'t available in Preview mode.</div>' +
                    '</div>';
            }
            else {
                let treeView = new TreeView(this.designerSurface.rootPeer.treeItem);

                this._treeViewToolbox.content.appendChild(treeView.render());
            }
        }
    }

    private buildDataExplorer() {
        if (this._dataToolbox && this._dataToolbox.content) {
            this._dataToolbox.content.innerHTML = "";

            if (this.dataStructure) {
                let treeItem = new DataTreeItem(this.dataStructure);
                let treeView = new TreeView(treeItem);

                this._dataToolbox.content.appendChild(treeView.render());
            }
        }
    }

    private buildPropertySheet(peer: DesignerPeers.DesignerPeer) {
        if (this._propertySheetToolbox.content) {
            this._propertySheetToolbox.content.innerHTML = "";

            let card: Adaptive.AdaptiveCard;

            if (peer) {
                card = peer.buildPropertySheetCard(this);
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
                    },
                    new Adaptive.SerializationContext(this.targetVersion)
                );
                card.padding = new Adaptive.PaddingDefinition(
                    Adaptive.Spacing.Small,
                    Adaptive.Spacing.Small,
                    Adaptive.Spacing.Small,
                    Adaptive.Spacing.Small
                )
            }

            card.hostConfig = defaultHostConfig;

            this._propertySheetToolbox.content.appendChild(card.render());
        }
    }

    private addPaletteItem(paletteItem: BasePaletteItem, hostElement: HTMLElement) {
        paletteItem.render();
        paletteItem.onStartDrag = (sender: BasePaletteItem) => {
            this._draggedPaletteItem = sender;

            this._draggedElement = sender.renderDragVisual();
            this._draggedElement.style.position = "absolute";
            this._draggedElement.style.left = this._currentMousePosition.x + "px";
            this._draggedElement.style.top = this._currentMousePosition.y + "px";

            document.body.appendChild(this._draggedElement);
        }

        hostElement.appendChild(paletteItem.renderedElement);
    }

    private buildPalette() {
        if (!this._isAttached) {
            return;
        }

        this._toolPaletteToolbox.content.innerHTML = "";

        let categorizedTypes: object = {};

        for (let i = 0; i < this.hostContainer.elementsRegistry.getItemCount(); i++) {
            let registration = this.hostContainer.elementsRegistry.getItemAt(i);

            if (registration.schemaVersion.compareTo(this.targetVersion) <= 0) {
                let peerRegistration = Designer.CardDesignerSurface.cardElementPeerRegistry.findTypeRegistration(registration.objectType);

                if (peerRegistration) {
                    if (!categorizedTypes.hasOwnProperty(peerRegistration.category)) {
                        categorizedTypes[peerRegistration.category] = [];
                    }

                    let paletteItem = new ElementPaletteItem(
                        registration,
                        peerRegistration
                    )

                    categorizedTypes[peerRegistration.category].push(paletteItem);
                }
            }
        }

        if (this.customPaletteItems) {
            for (let item of this.customPaletteItems) {
                if (!categorizedTypes.hasOwnProperty(item.category)) {
                    categorizedTypes[item.category] = [];
                }

                categorizedTypes[item.category].push(item);
            }
        }

        for (let category in categorizedTypes) {
            let node = document.createElement('div');
            node.innerText = category;
            node.className = "acd-palette-category";

            this._toolPaletteToolbox.content.appendChild(node);

            for (var i = 0; i < categorizedTypes[category].length; i++) {
                this.addPaletteItem(categorizedTypes[category][i], this._toolPaletteToolbox.content);
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

    private renderErrorPaneElement(message: string, source?: Adaptive.SerializableObject): HTMLElement {
        let errorElement = document.createElement("div");
        errorElement.className = "acd-error-pane-message";

        if (source && source instanceof Adaptive.CardObject) {
            errorElement.classList.add("selectable");
            errorElement.title = "Click to select this element";
            errorElement.onclick = (e) => {
                let peer = this.designerSurface.findPeer(source);

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

		if (Utils.isAbsoluteUrl(this.hostContainer.styleSheet))
        {
			styleSheetLinkElement.href = this.hostContainer.styleSheet;
		}
		else
		{
			styleSheetLinkElement.href = Utils.joinPaths(this._assetPath, this.hostContainer.styleSheet);
		}

        let _cardArea = document.getElementById("cardArea");

        if (_cardArea) {
            _cardArea.style.backgroundColor = this.hostContainer.getBackgroundColor();
        }

        this.hostContainer.initialize();

        this._designerHostElement.innerHTML = "";
        this.hostContainer.renderTo(this._designerHostElement);

        let wasInPreviewMode = this._designerSurface ? this._designerSurface.isPreviewMode : false;

        this._designerSurface = new Designer.CardDesignerSurface(this);
        this._designerSurface.fixedHeightCard = this.hostContainer.isFixedHeight;
        this._designerSurface.onSelectedPeerChanged = (peer: DesignerPeers.DesignerPeer) => {
            this.buildPropertySheet(peer);
        };
        this._designerSurface.onLayoutUpdated = (isFullRefresh: boolean) => {
            if (isFullRefresh) {
                this.scheduleUpdateJsonFromCard();
                this.buildTreeView();
            }
        };
        this._designerSurface.onCardValidated = (logEntries: Adaptive.IValidationEvent[]) => {
            if (this.onCardValidated) {
                this.onCardValidated(this, logEntries);
            }

            let errorPane = document.getElementById("errorPane");
            errorPane.innerHTML = "";

            if (this.targetVersion.compareTo(this.hostContainer.targetVersion) > 0 && Shared.GlobalSettings.showTargetVersionMismatchWarning) {
                errorPane.appendChild(this.renderErrorPaneElement("[Warning] The selected Target Version (" + this.targetVersion.toString() + ") is greater than the version supported by " + this.hostContainer.name + " (" + this.hostContainer.targetVersion.toString() + ")"));
            }

            if (logEntries.length > 0) {
                let dedupedEntries: Adaptive.IValidationEvent[] = [];

                for (let entry of logEntries) {
                    if (dedupedEntries.indexOf(entry) < 0) {
                        dedupedEntries.push(entry);
                    }
                }

                for (let entry of dedupedEntries) {
                    let s: string = "";

                    switch (entry.phase) {
                        case Adaptive.ValidationPhase.Parse:
                            s = "[Parse]";
                            break;
                        case Adaptive.ValidationPhase.ToJSON:
                            s = "[Serialize]";
                            break;
                        default:
                            s = "[Validation]";
                            break;
                    }

                    errorPane.appendChild(this.renderErrorPaneElement(s + " " + entry.message, entry.source));
                }
            }

            if (errorPane.childElementCount > 0) {
                errorPane.classList.remove("acd-hidden");
            }
            else {
                errorPane.classList.add("acd-hidden");
            }
        };
        this._designerSurface.onStartDrag = (sender: Designer.CardDesignerSurface) => {
            this._startDragPayload = JSON.parse(this.getCurrentCardEditorPayload());
        };
        this._designerSurface.onEndDrag = (sender: Designer.CardDesignerSurface, wasCancelled: boolean) => {
            if (wasCancelled) {
                this.setCardPayload(this._startDragPayload, false);
            }
            else {
                this.addToUndoStack(this._designerSurface.getCardPayloadAsObject());
            }
        };

        this.buildPalette();
        this.buildPropertySheet(null);

        this.updateCardFromJson(false);
        this.updateSampleData();

        this._designerSurface.isPreviewMode = wasInPreviewMode;

        this.updateFullLayout();
    }

    private activeHostContainerChanged() {
        this.recreateDesignerSurface();

        if (this.onActiveHostContainerChanged) {
            this.onActiveHostContainerChanged(this);
        }
    }

    private targetVersionChanged() {
        let cardPayload = this.designerSurface.getCardPayloadAsObject();

        if (typeof cardPayload === "object") {
            cardPayload["version"] = this.targetVersion.toString();

            this.setCardPayload(cardPayload, false);
        }

        this.recreateDesignerSurface();

        if (this.onTargetVersionChanged) {
            this.onTargetVersionChanged(this);
        }
    }

    private updateToolboxLayout(toolbox: Toolbox, hostPanelRect: ClientRect | DOMRect) {
        if (toolbox) {
            let jsonEditorHeaderRect = toolbox.getHeaderBoundingRect();

            toolbox.content.style.height = (hostPanelRect.height - jsonEditorHeaderRect.height) + "px";
        }
    }

    private updateJsonEditorsLayout() {
        if (this._isMonacoEditorLoaded) {
            let jsonEditorsPaneRect = this._jsonEditorsPanel.contentHost.getBoundingClientRect();

            this.updateToolboxLayout(this._cardEditorToolbox, jsonEditorsPaneRect);
            this._cardEditor.layout();

            if (this._sampleDataEditorToolbox) {
                this.updateToolboxLayout(this._sampleDataEditorToolbox, jsonEditorsPaneRect);
                this._sampleDataEditor.layout();
            }
        }
    }

    private updateFullLayout() {
        this.scheduleLayoutUpdate();
        this.updateJsonEditorsLayout();
    }

    private _jsonUpdateTimer: any;
    private _cardUpdateTimer: any;
    private _updateLayoutTimer: any;
    private _preventCardUpdate: boolean = false;

    private cardPayloadChanged() {
        if (this.onCardPayloadChanged) {
            this.onCardPayloadChanged(this);
        }
    }

    private _cardEditorUpdateCounter = 0;

    private beginCardEditorUpdate() {
        this._cardEditorUpdateCounter++;
    }

    private endCardEditorUpdate() {
        if (this._cardEditorUpdateCounter > 0) {
            this._cardEditorUpdateCounter--;
        }
    }

    private setCardPayload(payload: object, addToUndoStack: boolean) {
        if (this._isMonacoEditorLoaded) {
            this.beginCardEditorUpdate();

            try {
                if (payload.hasOwnProperty("version")) {
                    payload["version"] = this.targetVersion.toString();
                }

                this._cardEditor.setValue(JSON.stringify(payload, null, 4));
                this.updateCardFromJson(addToUndoStack);
            }
            finally {
                this.endCardEditorUpdate();
            }
        }

        this.cardPayloadChanged();
    }

    private setSampleDataPayload(payload: any) {
        if (this._isMonacoEditorLoaded && this._sampleDataEditor) {
            this._sampleDataEditor.setValue(JSON.stringify(payload, null, 4));
        }
    }

    private updateJsonFromCard(addToUndoStack: boolean = true) {
        try {
            this._preventCardUpdate = true;

            if (!this.preventJsonUpdate && this._isMonacoEditorLoaded) {
                let cardPayload = this._designerSurface.getCardPayloadAsObject();

                this.setCardPayload(cardPayload, addToUndoStack);
            }
        }
        finally {
            this._preventCardUpdate = false;
        }
    }

    private scheduleUpdateJsonFromCard() {
        clearTimeout(this._jsonUpdateTimer);

        if (!this.preventJsonUpdate) {
            this._jsonUpdateTimer = setTimeout(() => { this.updateJsonFromCard(); }, 100);
        }
    }

    private preventJsonUpdate: boolean = false;

    private getCurrentCardEditorPayload(): string {
        return this._isMonacoEditorLoaded ? this._cardEditor.getValue() : Constants.defaultPayload;
    }

    private getCurrentSampleDataEditorPayload(): string {
        return this._isMonacoEditorLoaded && this._sampleDataEditor ? this._sampleDataEditor.getValue() : "";
    }

    private updateCardFromJson(addToUndoStack: boolean) {
        try {
            this.preventJsonUpdate = true;

            let currentEditorPayload = this.getCurrentCardEditorPayload();

            if (addToUndoStack) {
                try {
                    this.addToUndoStack(JSON.parse(currentEditorPayload));
                }
                catch {
                    // Swallow the parse error
                }
            }

            if (!this._preventCardUpdate) {
                this.designerSurface.setCardPayloadAsString(currentEditorPayload);

                this.cardPayloadChanged();
            }
        } finally {
            this.preventJsonUpdate = false;
        }
    }

    private scheduleUpdateCardFromJson() {
        clearTimeout(this._cardUpdateTimer);

        if (!this._preventCardUpdate) {
            this._cardUpdateTimer = setTimeout(() => { this.updateCardFromJson(true); }, 300);
        }
    }

    private _isEdgeHTML?: boolean = undefined;

    private isEdgeHTML(): boolean {
        if (this._isEdgeHTML === undefined) {
            this._isEdgeHTML = window.navigator.userAgent.toLowerCase().indexOf("edge") > -1;
        }

        return this._isEdgeHTML;
    }

    private scheduleLayoutUpdate() {
        if (this.designerSurface) {
            if (!this.isEdgeHTML()) {
                this.designerSurface.updateLayout(false);
            }
            else {
                // In "old" Edge, updateLayout() is *super* slow (because it uses getBoundingClientRect
                // heavily which is itself super slow) and we have to call it only on idle
                clearTimeout(this._updateLayoutTimer);

                this._updateLayoutTimer = setTimeout(
                    () => {
                        if (this.designerSurface) {
                            this.designerSurface.updateLayout(false);
                        }
                    },
                    5);
            }
        }
    }

    private _targetVersion: Adaptive.Version = Adaptive.Versions.latest;
    private _fullScreenHandler = new FullScreenHandler();
    private _fullScreenButton: ToolbarButton;
    private _hostContainerChoicePicker: ToolbarChoicePicker;
    private _versionChoicePicker: ToolbarChoicePicker;
    private _undoButton: ToolbarButton;
    private _redoButton: ToolbarButton;
    private _newCardButton: ToolbarButton;
    private _copyJSONButton: ToolbarButton;
    private _togglePreviewButton: ToolbarButton;
    private _preventRecursiveSetTargetVersion = false;

    private prepareToolbar() {
        if (Shared.GlobalSettings.showVersionPicker) {
            this._versionChoicePicker = new ToolbarChoicePicker(CardDesigner.ToolbarCommands.VersionPicker);
            this._versionChoicePicker.label = "Target version:"
            this._versionChoicePicker.width = 80;
            this._versionChoicePicker.alignment = ToolbarElementAlignment.Right;
            this._versionChoicePicker.separator = true;

            for (let i = 0; i < Shared.SupportedTargetVersions.length; i++) {
                this._versionChoicePicker.choices.push(
                    {
                        name: Shared.SupportedTargetVersions[i].label,
                        value: i.toString()
                    });
            }

            this.toolbar.addElement(this._versionChoicePicker);
        }

        this._newCardButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.NewCard,
            "New card",
            "acd-icon-newCard",
            (sender: ToolbarButton) => {
                let dialog = new OpenSampleDialog(this._sampleCatalogue);
                dialog.title = "Pick a sample as a starting point";
                dialog.closeButton.caption = "Cancel";
                dialog.width = "80%";
                dialog.height = "80%";
                dialog.onClose = (d) => {
                    if (dialog.selectedSample) {
                        dialog.selectedSample.onDownloaded = () => {
                            try {
                                let cardPayload = JSON.parse(dialog.selectedSample.cardPayload);

                                this.setCardPayload(cardPayload, true);
                            } catch {
                                alert("The sample could not be loaded.")
                            }

                            if (dialog.selectedSample.sampleData) {
                                try {
                                    let sampleDataPayload = JSON.parse(dialog.selectedSample.sampleData);

                                    this.setSampleDataPayload(sampleDataPayload);
                                    this.dataStructure = FieldDefinition.deriveFrom(sampleDataPayload);
                                }
                                catch {
                                    alert("The sample could not be loaded.")
                                }
                            }
                        };
                        dialog.selectedSample.download();
                    }
                };
                dialog.open();
            });
        this._newCardButton.separator = true;

        this.toolbar.addElement(this._newCardButton);

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
                this.hostContainer = this._hostContainers[Number.parseInt(this._hostContainerChoicePicker.value)];

                this.activeHostContainerChanged();
            };

            this.toolbar.addElement(this._hostContainerChoicePicker);
        }

        this._undoButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.Undo,
            "Undo",
            "acd-icon-undo",
            (sender: ToolbarButton) => { this.undo(); });
        this._undoButton.separator = true;
        this._undoButton.toolTip = "Undo your last change";
        this._undoButton.isEnabled = false;
        this._undoButton.displayCaption = false;

        this.toolbar.addElement(this._undoButton);

        this._redoButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.Redo,
            "Redo",
            "acd-icon-redo",
            (sender: ToolbarButton) => { this.redo(); });
        this._redoButton.toolTip = "Redo your last changes";
        this._redoButton.isEnabled = false;
        this._redoButton.displayCaption = false;

        this.toolbar.addElement(this._redoButton);

        this._copyJSONButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.CopyJSON,
            "Copy card JSON",
            "acd-icon-copy");
        this.toolbar.addElement(this._copyJSONButton);

        this._togglePreviewButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.TogglePreview,
            "Preview mode",
            "acd-icon-preview",
            (sender: ToolbarButton) => { this.togglePreview(); });
        this._togglePreviewButton.separator = true;
        this._togglePreviewButton.allowToggle = true;
        this._togglePreviewButton.isVisible = Shared.GlobalSettings.enableDataBindingSupport;

        this.toolbar.addElement(this._togglePreviewButton);

        this._fullScreenHandler = new FullScreenHandler();
        this._fullScreenHandler.onFullScreenChanged = (isFullScreen: boolean) => {
            this._fullScreenButton.toolTip = isFullScreen ? "Exit full screen" : "Enter full screen";

            this.updateFullLayout();
        }
    }

    private onResize() {
        this._cardEditor.layout();

        if (this._sampleDataEditor) {
            this._sampleDataEditor.layout();
        }
    }

    private updateSampleData() {
        try {
            this._sampleData = JSON.parse(this.getCurrentSampleDataEditorPayload());

            this.scheduleUpdateCardFromJson();
        }
        catch {
            // Swallow expression, the payload isn't a valid JSON document
        }
    }

    private updateToolbar() {
        this._undoButton.isEnabled = this.canUndo;
        this._redoButton.isEnabled = this.canRedo;
    }

    private addToUndoStack(payload: object) {
        let doAdd: boolean = !this._designerSurface.draggedPeer;

        if (doAdd) {
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
    }

    private handlePointerUp(e: PointerEvent) {
        this.endDrag();

        if (this.designerSurface) {
            this.designerSurface.endDrag(false);
        }
    }

    private handlePointerMove(e: PointerEvent) {
        this._currentMousePosition = { x: e.x, y: e.y };

        if (this.designerSurface) {
            let isPointerOverDesigner = this.designerSurface.isPointerOver(this._currentMousePosition.x, this._currentMousePosition.y);
            let peerDropped = false;

            if (this._draggedPaletteItem && isPointerOverDesigner) {
                let peer = this._draggedPaletteItem.createPeer(this, this.designerSurface);

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
    }

    readonly toolbar: Toolbar = new Toolbar();

    lockDataStructure: boolean = false;

    constructor(hostContainers: Array<HostContainer> = null) {
        super();

        Adaptive.GlobalSettings.enableFullJsonRoundTrip = true;
        Adaptive.GlobalSettings.allowPreProcessingPropertyValues = true;

        Adaptive.AdaptiveCard.onProcessMarkdown = (text: string, result: Adaptive.IMarkdownProcessingResult) => {
            CardDesigner.internalProcessMarkdown(text, result);
        }

        this._hostContainers = hostContainers ? hostContainers : [];

        this.prepareToolbar();
    }

    monacoModuleLoaded(monaco: any = null) {
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

		// TODO: set this in our editor instead of defaults
        monaco.languages.json.jsonDefaults.setDiagnosticsOptions(monacoConfiguration);

        // Setup card JSON editor
        this._cardEditorToolbox.content = document.createElement("div");
        this._cardEditorToolbox.content.style.overflow = "hidden";

        this._cardEditor = monaco.editor.create(
            this._cardEditorToolbox.content,
            {
                folding: true,
                fontSize: 13.5,
                language: 'json',
                minimap: {
                    enabled: false
                }
            }
        );

        this._cardEditor.onDidChangeModelContent(() => {
            if (this._cardEditorUpdateCounter == 0) {
                this.scheduleUpdateCardFromJson();
            }
        });

        if (this._sampleDataEditorToolbox) {
            // Setup sample data JSON editor
            this._sampleDataEditorToolbox.content = document.createElement("div");
            this._sampleDataEditorToolbox.content.style.overflow = "hidden";

            this._sampleDataEditor = monaco.editor.create(
                this._sampleDataEditorToolbox.content,
                {
                    folding: true,
                    fontSize: 13.5,
                    language: 'json',
                    minimap: {
                        enabled: false
                    }
                }
            );

            this._sampleDataEditor.onDidChangeModelContent(
                () => {
                    this.updateSampleData();

                    if (!this.lockDataStructure) {
                        try {
                            this.dataStructure = FieldDefinition.deriveFrom(JSON.parse(this.getCurrentSampleDataEditorPayload()));
                        }
                        catch {
                            // Swallow exception
                        }
                    }
                });
        }

        window.addEventListener('resize', () => { this.onResize(); });

        this._isMonacoEditorLoaded = true;

        this.updateJsonEditorsLayout();
        this.updateJsonFromCard(true);
    }

    attachTo(root: HTMLElement)  {
        let styleSheetLinkElement = document.createElement("link");
        styleSheetLinkElement.id = "__ac-designer";
        styleSheetLinkElement.rel = "stylesheet";
		styleSheetLinkElement.type = "text/css";
        styleSheetLinkElement.href = Utils.joinPaths(this._assetPath, "adaptivecards-designer.css");

        document.getElementsByTagName("head")[0].appendChild(styleSheetLinkElement);

        if (this._hostContainers && this._hostContainers.length > 0) {
            this._hostContainer = this._hostContainers[0];
        }
        else {
            this._hostContainer = new DefaultContainer("Default", "adaptivecards-defaulthost.css");
        }

        root.classList.add("acd-designer-root");
        root.style.flex = "1 1 auto";
        root.style.display = "flex";
        root.style.flexDirection = "column";
        root.style.overflow = "hidden";

        root.innerHTML =
            '<div id="toolbarHost"></div>' +
            '<div class="content" style="display: flex; flex: 1 1 auto; overflow-y: hidden;">' +
                '<div id="leftCollapsedPaneTabHost" class="acd-verticalCollapsedTabContainer acd-dockedLeft" style="border-right: 1px solid #D2D2D2;"></div>' +
                '<div id="toolPalettePanel" class="acd-toolPalette-pane"></div>' +
                '<div style="display: flex; flex-direction: column; flex: 1 1 100%; overflow: hidden;">' +
                    '<div style="display: flex; flex: 1 1 100%; overflow: hidden;">' +
                        '<div id="cardArea" class="acd-designer-cardArea">' +
                            '<div style="flex: 1 1 100%; overflow: auto;">' +
                                '<div id="designerHost" style="margin: 20px 40px 20px 20px;"></div>' +
                            '</div>' +
                            '<div id="errorPane" class="acd-error-pane acd-hidden"></div>' +
                        '</div>' +
                        '<div id="treeViewPanel" class="acd-treeView-pane"></div>' +
                       '<div id="propertySheetPanel" class="acd-propertySheet-pane"></div>' +
                    '</div>' +
                    '<div id="jsonEditorPanel" class="acd-json-editor-pane"></div>' +
                    '<div id="bottomCollapsedPaneTabHost" class="acd-horizontalCollapsedTabContainer" style="border-top: 1px solid #D2D2D2;"></div>' +
                '</div>' +
                '<div id="rightCollapsedPaneTabHost" class="acd-verticalCollapsedTabContainer acd-dockedRight" style="border-left: 1px solid #D2D2D2;"></div>' +
            '</div>';

        this.toolbar.attachTo(document.getElementById("toolbarHost"));

        if (this._versionChoicePicker) {
            this._versionChoicePicker.selectedIndex = Shared.SupportedTargetVersions.indexOf(this.targetVersion);
            this._versionChoicePicker.onChanged = (sender: ToolbarChoicePicker) => {
                this.targetVersion = Shared.SupportedTargetVersions[parseInt(this._versionChoicePicker.value)];
            }
        }

        if (this._copyJSONButton.isVisible) {
            new Clipboard(
                this._copyJSONButton.renderedElement,
                {
                    text: (trigger) => JSON.stringify(this.getCard(), null, 4)
                })
                .on("error", () => this._copyJSONButton.renderedElement.focus())
                .on("success", () => this._copyJSONButton.renderedElement.focus())
        }

        // Tool palette panel
        let toolPaletteHost = document.createElement("div");
        toolPaletteHost.className = "acd-dockedPane";

        this._toolPaletteToolbox = new Toolbox("toolPalette", Strings.toolboxes.toolPalette.title);
        this._toolPaletteToolbox.content = toolPaletteHost;

        let toolPalettePanel = new SidePanel(
            "toolPalettePanel",
            SidePanelAlignment.Left,
            document.getElementById("leftCollapsedPaneTabHost"));
        toolPalettePanel.addToolbox(this._toolPaletteToolbox);
        toolPalettePanel.isResizable = false;

        toolPalettePanel.attachTo(document.getElementById("toolPalettePanel"));

        // JSON editors panel
        this._cardEditorToolbox = new Toolbox("cardEditor", Strings.toolboxes.cardEditor.title);
        this._cardEditorToolbox.content = document.createElement("div");
        this._cardEditorToolbox.content.style.padding = "8px";
        this._cardEditorToolbox.content.innerText = Strings.loadingEditor;

        this._jsonEditorsPanel = new SidePanel(
            "jsonEditorPanel",
            SidePanelAlignment.Bottom,
            document.getElementById("bottomCollapsedPaneTabHost"));
        this._jsonEditorsPanel.onResized = (sender: SidePanel) => {
            this.updateJsonEditorsLayout();
        }
        this._jsonEditorsPanel.onToolboxResized = (sender: SidePanel) => {
            this.updateJsonEditorsLayout();
        }
        this._jsonEditorsPanel.onToolboxExpandedOrCollapsed = (sender: SidePanel) => {
            this.updateJsonEditorsLayout();
        }

        this._jsonEditorsPanel.addToolbox(this._cardEditorToolbox);

        if (Shared.GlobalSettings.enableDataBindingSupport && Shared.GlobalSettings.showSampleDataEditorToolbox) {
            this._sampleDataEditorToolbox = new Toolbox("sampleDataEditor", Strings.toolboxes.sampleDataEditor.title);
            this._sampleDataEditorToolbox.content = document.createElement("div");
            this._sampleDataEditorToolbox.content.style.padding = "8px";
            this._sampleDataEditorToolbox.content.innerText = Strings.loadingEditor;

            this._jsonEditorsPanel.addToolbox(this._sampleDataEditorToolbox);
        }

        this._jsonEditorsPanel.attachTo(document.getElementById("jsonEditorPanel"));

        // Property sheet panel
        let propertySheetHost = document.createElement("div");
        propertySheetHost.className = "acd-propertySheet-host";

        this._propertySheetToolbox = new Toolbox("propertySheet", Strings.toolboxes.propertySheet.title);
        this._propertySheetToolbox.content = propertySheetHost;

        let propertySheetPanel = new SidePanel(
            "propertySheetPanel",
            SidePanelAlignment.Right,
            document.getElementById("rightCollapsedPaneTabHost"));
        propertySheetPanel.addToolbox(this._propertySheetToolbox);
        propertySheetPanel.onResized = (sender: SidePanel) => {
            this.scheduleLayoutUpdate();
        }

        propertySheetPanel.attachTo(document.getElementById("propertySheetPanel"));

        // Tree view panel
        let treeViewHost = document.createElement("div");
        treeViewHost.className = "acd-treeView-host";

        this._treeViewToolbox = new Toolbox("treeView", Strings.toolboxes.cardStructure.title);
        this._treeViewToolbox.content = treeViewHost;

        let treeViewPanel = new SidePanel(
            "treeViewPanel",
            SidePanelAlignment.Right,
            document.getElementById("rightCollapsedPaneTabHost"));
        treeViewPanel.addToolbox(this._treeViewToolbox);
        treeViewPanel.onResized = (sender: SidePanel) => {
            this.scheduleLayoutUpdate();
        }

        if (Shared.GlobalSettings.enableDataBindingSupport && Shared.GlobalSettings.showDataStructureToolbox) {
            let dataExplorerHost = document.createElement("div");
            dataExplorerHost.className = "acd-treeView-host";

            this._dataToolbox = new Toolbox("data", Strings.toolboxes.dataStructure.title);
            this._dataToolbox.content = dataExplorerHost;

            treeViewPanel.addToolbox(this._dataToolbox);
        }

        treeViewPanel.attachTo(document.getElementById("treeViewPanel"));

        this._designerHostElement = document.getElementById("designerHost");

        window.addEventListener("pointermove", (e: PointerEvent) => { this.handlePointerMove(e); });
        window.addEventListener("resize", () => { this.scheduleLayoutUpdate(); });
        window.addEventListener("pointerup", (e: PointerEvent) => { this.handlePointerUp(e); });

        this._isAttached = true;

        this.recreateDesignerSurface();
    }

    clearUndoStack() {
        this._undoStack = [];
        this._undoStackIndex = -1;
        this.updateToolbar();
    }

    setCard(payload: object) {
        this.clearUndoStack();
        this.setCardPayload(payload, true);
    }

    getCard(): object {
        return this._designerSurface ? this._designerSurface.getCardPayloadAsObject() : undefined;
    }

    undo() {
        if (this.canUndo) {
            this._undoStackIndex--;

            let card = this._undoStack[this._undoStackIndex];

            this.setCardPayload(card, false);
            this.updateToolbar();
        }
    }

    redo() {
        if (this._undoStackIndex < this._undoStack.length - 1) {
            this._undoStackIndex++;

            let payload = this._undoStack[this._undoStackIndex];

            this.setCardPayload(payload, false);
            this.updateToolbar();
        }
    }

    newCard() {
        let card = {
            type: "AdaptiveCard",
            $schema: "http://adaptivecards.io/schemas/adaptive-card.json",
            version: this.targetVersion.toString(),
            body: [
            ]
        }

        this.setCardPayload(card, true);
    }

    onCardPayloadChanged: (designer: CardDesigner) => void;
    onCardValidated: (designer: CardDesigner, validationLogEntries: Adaptive.IValidationEvent[]) => void;
    onActiveHostContainerChanged: (designer: CardDesigner) => void;
    onTargetVersionChanged: (designer: CardDesigner) => void;

    get targetVersion(): Adaptive.Version {
        return this._targetVersion;
    }

    set targetVersion(value: Adaptive.Version) {
        if (this._targetVersion.compareTo(value) !== 0 && !this._preventRecursiveSetTargetVersion) {
            this._preventRecursiveSetTargetVersion = true;

            try {
                this._targetVersion = value;

                this.targetVersionChanged();

                if (this._versionChoicePicker) {
                    this._versionChoicePicker.selectedIndex = Shared.SupportedTargetVersions.indexOf(this._targetVersion);
                }
            }
            finally {
                this._preventRecursiveSetTargetVersion = false;
            }
        }
    }

    get dataStructure(): FieldDefinition {
        return this._dataStructure;
    }

    set dataStructure(value: FieldDefinition) {
        this._dataStructure = value;

        this.buildDataExplorer();
    }

    get sampleData(): any {
        return this._sampleData;
    }

    set sampleData(value: any) {
        this._sampleData = value;

        this.setSampleDataPayload(value);
    }

    get bindingPreviewMode(): Designer.BindingPreviewMode {
        return this._bindingPreviewMode;
    }

    set bindingPreviewMode(value: Designer.BindingPreviewMode) {
        this._bindingPreviewMode = value;
    }

    get hostContainer(): HostContainer {
        return this._hostContainer;
    }

    set hostContainer(value: HostContainer) {
        if (this._hostContainer !== value) {
            this._hostContainer = value;

            this.activeHostContainerChanged();

            if (Shared.GlobalSettings.selectedHostContainerControlsTargetVersion) {
                this.targetVersion = this._hostContainer.targetVersion;
            }
        }
    }

    get canUndo(): boolean {
        return this._undoStackIndex >= 1;
    }

    get canRedo(): boolean {
        return this._undoStackIndex < this._undoStack.length - 1;
    }

    get designerSurface(): Designer.CardDesignerSurface {
        return this._designerSurface;
    }

    get treeViewToolbox(): Toolbox {
        return this._treeViewToolbox;
    }

    get propertySheetToolbox(): Toolbox {
        return this._propertySheetToolbox;
    }

    get jsonEditorToolbox(): Toolbox {
        return this._cardEditorToolbox;
    }

    get toolPaletteToolbox(): Toolbox {
        return this._toolPaletteToolbox;
	}

    get dataToolbox(): Toolbox {
        return this._dataToolbox;
	}

	get assetPath(): string {
		return this._assetPath;
	}

	set assetPath(value: string) {
		this._assetPath = value;
    }

    get customPaletteItems(): CustomPaletteItem[] {
        return this._customPeletteItems;
    }

    set customPaletteItems(value: CustomPaletteItem[]) {
        this._customPeletteItems = value;

        this.buildPalette();
    }

    get sampleCatalogueUrl(): string {
        return this._sampleCatalogue.url;
    }

    set sampleCatalogueUrl(value: string) {
        this._sampleCatalogue.url = value;
    }
}

export module CardDesigner {
    export class ToolbarCommands {
        static readonly HostAppPicker = "__hostAppPicker";
        static readonly VersionPicker = "__versionPicker";
        static readonly Undo = "__undoButton";
        static readonly Redo = "__redoButton";
        static readonly NewCard = "__newCardButton";
        static readonly CopyJSON = "__copyJsonButton";
        static readonly TogglePreview = "__togglePreviewButton";
    }
}
