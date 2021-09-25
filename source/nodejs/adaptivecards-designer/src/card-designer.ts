// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Clipboard from "clipboard";
import * as Adaptive from "adaptivecards";
import * as monaco from "monaco-editor";
import * as Constants from "./constants";
import * as Designer from "./card-designer-surface";
import * as DesignerPeers from "./designer-peers";
import { Pic2Card } from "./pic2card";
import { OpenSampleDialog } from "./open-sample-dialog";
import { OpenJsonSchemaDialog } from "./open-json-schema-dialog";
import { HostContainer } from "./containers/host-container";
import { adaptiveCardSchema } from "./adaptive-card-schema";
import { OpenImageDialog } from "./open-image-dialog";
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
import { HelpDialog } from "./help-dialog";

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
    private _propertySheetCard: Adaptive.AdaptiveCard;
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
            // if focus is already on _propertySheetCard, remember the focused object's id
            const restoreFocusId = this._propertySheetCard?.findDOMNodeOwner(document.activeElement)?.id;
            this._propertySheetToolbox.content.innerHTML = "";

            if (peer) {
                this._propertySheetCard = peer.buildPropertySheetCard(this);
            }
            else {
                this._propertySheetCard = new Adaptive.AdaptiveCard();
                this._propertySheetCard.parse(
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
                this._propertySheetCard.padding = new Adaptive.PaddingDefinition(
                    Adaptive.Spacing.Small,
                    Adaptive.Spacing.Small,
                    Adaptive.Spacing.Small,
                    Adaptive.Spacing.Small
                );
            }

            this._propertySheetCard.hostConfig = defaultHostConfig;

            this._propertySheetToolbox.content.appendChild(this._propertySheetCard.render());

            if (restoreFocusId) {
                // attempt to restore focus if new card has object with same id
                const focusTarget = this._propertySheetCard.getElementById(restoreFocusId) ?? this._propertySheetCard.getActionById(restoreFocusId);
                focusTarget?.renderedElement?.focus();
            }
        }
    }

    private addPaletteItem(paletteItem: BasePaletteItem, hostElement: HTMLElement) {
        paletteItem.render();
        paletteItem.onStartDrag = (sender: BasePaletteItem) => {
            this._draggedPaletteItem = sender;

            this._draggedElement = sender.renderDragVisual();
            this._draggedElement.style.position = "absolute";
            const adjustedPosition = Utils.adjustPointForScroll(this._currentMousePosition);
            this._draggedElement.style.left = adjustedPosition.x + "px";
            this._draggedElement.style.top = adjustedPosition.y + "px";

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

                    paletteItem.onDoubleClick = (sender) => {
                        const peer = paletteItem.createPeer(this, this.designerSurface);

                        if (this.designerSurface.rootPeer.tryAdd(peer)) {
                            peer.isSelected = true;
                        };
                    }

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

            let categoryList = document.createElement('div');
            categoryList.setAttribute("aria-label", category)

            let node = document.createElement('div');
            categoryList.appendChild(node);
            node.innerText = category;
            node.className = "acd-palette-category";

            this._toolPaletteToolbox.content.appendChild(categoryList);

            let paletteItemContainer = document.createElement('div');
            paletteItemContainer.className = "acd-palette-item-container";

            for (var i = 0; i < categorizedTypes[category].length; i++) {
                this.addPaletteItem(categorizedTypes[category][i], paletteItemContainer);
            }

            categoryList.appendChild(paletteItemContainer);
        }
    }

    private endDrag() {
        if (this._draggedPaletteItem) {
            this._draggedPaletteItem.endDrag();
            this._draggedElement.parentNode.removeChild(this._draggedElement);

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

        let cardArea = document.getElementById("cardArea");

        if (cardArea) {
            cardArea.style.backgroundColor = this.hostContainer.getBackgroundColor();
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
    private _helpButton: ToolbarButton;
    private _preventRecursiveSetTargetVersion = false;

    private prepareToolbar() {
        if (Shared.GlobalSettings.showVersionPicker) {
            this._versionChoicePicker = new ToolbarChoicePicker(CardDesigner.ToolbarCommands.VersionPicker);
            this._versionChoicePicker.label = "Target version:"
            this._versionChoicePicker.alignment = ToolbarElementAlignment.Right;
            this._versionChoicePicker.separator = true;

            for (let i = 0; i < Shared.GlobalSettings.supportedTargetVersions.length; i++) {
                this._versionChoicePicker.choices.push(
                    {
                        name: Shared.GlobalSettings.supportedTargetVersions[i].label,
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
                let dialog = new OpenSampleDialog({
                    catalogue: this._sampleCatalogue,
                    handlers: [
                        {
                            label: "From JSON Schema",
                            onClick: () => {
                                dialog.close()
                                this.launchJsonSchemaPopup()
                            },
                            cardData: {
                                thumbnail: () => {
                                    const thumbnail = document.createElement("div");
                                    thumbnail.className = "acd-image-container";
                                    thumbnail.innerHTML = `<div class="acd-image-upload acd-open-sample-item">
                                        <img alt="json schema image" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAIoAAACKCAMAAABCWSJWAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAJDUExURQAAAAAAAEBAQGBgYFVVVU1NTUZGRl1dXVVVVU5OTlVVVVBQUEtLS1FRUVFRUVJSUlJSUk9PT1JSUlBQUFNTU1BQUE5OTlNTU1FRUU5OTlNTU09PT1NTU1FRUU9PT1NTU1BQUE5OTlJSUlBQUFJSUlBQUE9PT1JSUlFRUU9PT05OTlFRUU5OTlJSUlFRUVBQUFFRUU9PT05OTlFRUVBQUE9PT05OTlJSUlFRUVFRUVBQUFBQUE9PT1FRUVBQUE9PT1FRUU9PT05OTlBQUFBQUFBQUE9PT1FRUVFRUU9PT1BQUE9PT1FRUU9PT09PT1BQUE1NTVBQUE9PT1BQUE9PT05OTlBQUFFRUVBQUFBQUE9PT1FRUVFRUVBQUE9PT1FRUVBQUE9PT1FRUVBQUE9PT05OTlBQUFBQUFBQUFBQUE9PT1BQUE9PT1FRUVBQUFFRUVBQUFFRUVBQUFBQUFBQUFFRUVBQUFBQUFBQUFFRUVFRUVBQUFBQUFBQUE9PT1FRUVBQUFBQUE9PT1FRUVBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFFRUVBQUFBQUE9PT1FRUVBQUE9PT1BQUFBQUFBQUFBQUFBQUFBQUFBQUFFRUU9PT1FRUVBQUFBQUFBQUFFRUVBQUFBQUFBQUFBQUE9PT1BQUFFRUVBQUFBQUE9PT1FRUVBQUFBQUFBQUFFRUVBQUFBQUFBQUFFRUVBQUE9PT1BQUE9PT1FRUVBQUFBQUFBQUE9PT1BQUE9PT1BQUFFRUc/1aIgAAAC+dFJOUwABBAgJCgsLDA0PEBETFhkcHR8gIiMkJSYnKCorLC0uMDEyMzU2Nzg5Ojs8Pj4/Q0VHSEhJSktLTE9QU1RVVldYWltcXWBhYWJkZmdoamtscHN0eX5/gIGCg4SEhYaIiImKi4yOj4+QlZaXmZqbnJ6goaKjpqeoqaqqq6ytsLGxsrO0tLW2ubq7vL2/wcLDxMTFx8jJysvNzs/R1NTV1tra293e4OHj4+Xm5+fo6erq6+zt7e7y9ff3+Pr8/v6BMG3iAAAACXBIWXMAADLAAAAywAEoZFrbAAAEwklEQVR4Xu2c+1tURRjHVxSEAhXTLBNLCSMzu6nYFpQheEXCSk3D1MrQUjQTLbxg3lBERUHMa0ZZlikQRVg6/mntvvNdd3b33T17mDknnp75/MLznXn3nQ+H3XPmUYZAKnLLG9q6BoQX3Bf3+i43b5iJlRx47hBe5iU3a3OwXHIe+wLFXtNbgxWTMasblT7QOAKLslSjyh/OP4FlGd5EjV+cT3pdiu6g5Le62eNSXj13TPkTfXs2zx2fmVewpAlZfI2KBDpR8H4mBgxxBn0/yMZAoPgAhpK8dxfL2e5ZyKaokH375iIT6+Rgz0jkWH6Qs9MRjXFV9o27rcFlDWIMZXJuPqIxXpV9FyI+QP6MbiDFIO9tLUjm+Jz6tiFFeZbGxQxElV6aCSKZ4wb1fQNJQV6WdUgKE2hiIAPRGPnUVzz48ERZShNHkRRm0kQrkjmKqG8HkkoBzVxEUpB32gYkcwSp7z4klTya6UVSqKKJOiRzVFLfeiSVETQzgKTgv8o4mulCUvBfZTbNJH7K/wOVTTSzE0nBd5XM2zRTjqjgu8pqmhC5iAp+q5TQuDiEqOKzygz5nGH3Af6qYA8jtiPH4KNKVtkpGhTi1gQMxRCv8nq9DsvQJaLyHcZD7G2/S0NhXkFRLPEqBykPlnPoElHhqUJNHP6r9JeiJB7fVc4WoiIBn1WuJex1o/ip8uvWlPvWeJVRlTpMRpeIykmMhwhOy8dUMuJVTCFVmGdQcqwKh1XhsCocVoXDqnDEq5h9HFqVMFaF4/+qYgqrwmFVOKwKh1XhsCocBlTGVulQhC5GVOyTOYxV4RjCKnPqdIj+o58BFVNYFQ6rwmFVOKwKh1XhMKCyokOHTehiRMVuEsJYFY4hrBJ4WodhaGJGxRBrqW8nUlp4pTKEropV4bAqHFaFw6pwWBUOq8JhVTisCodLlfyiYOUOeslx/B6dFm+/98kidHanEtwiz6oY5Q6au1FZcI1KTeNeZWo7FZrHtUrpX1TnAW5V5IfGE1yqvExFRMd+/A63Bl9FDjoK8ftPh7FGeiqP3qIiIU6V8Yf/XHIC7bp2jMEIkY5K5LRwBbImNWi3CjlCGio4a9fLHbYbBNk9sl/CN5aGyjdUIkoQdVkj2y1HjOKs8jBViNWI2lygdgeQFJxV3qKK7ixEXSZSO1GMqOCs8iVVbEbSRr5p25FUnFVOU4Wpd0rgU2r3LpKKs8r3VDEeSZtd1I45iJqGSj9VGDvO3UrtuBuDs0ofVeQhaXOE2r2EpCLfRR8jcVyiigIkbbZRO+7G/RHNJN5vojRTxRIkbWqp3WdIKvLzMQ+JYwNVNCFpI8/9/oykgOPMTyJyyOPL4hlEXXJku8SrvJHGryDx3KQaY5dF/nmSHx9CjFBIw2I9Io/86YoPEXXB38DYjwhyr8jhp5B5cnAc0pRLi2y3ezhymMexi4/+nxlPZK/TxDzDBsGLaNf5GgZCe2fsYf6O2dZx7JGFoUf70gID9zqcxA1tUN+ZOjojf3qtvKGHcN4nZn2L0hD38NULVmK9VEyKunioshGrpSazEeUeqlRjLUdq8M7ySuXYC1goDbJrfwm/xBuV9mSnUJPx/Prmi3/gxab453rH3upHsEAqAoF/ATgD/WK2xh4JAAAAAElFTkSuQmCC" />
                                        <div class="acd-image-text-container">
                                            <div class="acd-image-upload-title">From JSON Schema</div>
                                        </div>
                                    </div>`;
                                    return thumbnail;
                                },
                            },
                        },
                        Pic2Card.pic2cardService ?
                            {
                                label: "Pic2Card",
                                onClick: () => {
                                    dialog.close()
                                    this.launchImagePopup()
                                },
                                cardData: {
                                    thumbnail: () => {
                                        const thumbnail = document.createElement("div");
                                        thumbnail.className = "acd-image-container";
                                        thumbnail.innerHTML = `<div class="acd-image-upload acd-open-sample-item">
                                            <img alt="pic2card image" src="data:image/png;base64,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" />
                                            <div class="acd-image-text-container">
                                                <div class="acd-image-new-title">NEW PREVIEW</div>
                                                <div class="acd-image-upload-title">Create from Image </div>
                                                <div id="image-description-id" class="acd-image-description">Upload your own image and convert it magically to an Adaptive card</div>
                                                <input aria-labelledby="image-description-id" class="acd-try-now-button" value="Try Now" type="button" />
                                            </div>
                                        </div>`;
                                        return thumbnail;
                                    },
                                },
                            } : null,
                    ]
                });
                dialog.title = "Create";
                dialog.closeButton.caption = "Cancel";
                dialog.width = "80%";
                dialog.height = "80%";
                dialog.onClose = (d) => {
                    const newCardButton = this._newCardButton.renderedElement;
                    if (dialog.output) {
                        try {
                            let cardPayload = JSON.parse(dialog.output.cardPayload);

                            this.setCardPayload(cardPayload, true);
                        } catch {
                            alert("The card template could not be loaded.");
                            return
                        }

                        if (dialog.output.sampleData) {
                            try {
                                let sampleDataPayload = JSON.parse(dialog.output.sampleData);

                                this.setSampleDataPayload(sampleDataPayload);
                                this.dataStructure = FieldDefinition.deriveFrom(sampleDataPayload);
                            } catch {
                                alert("The card data could not be loaded.")
                            }
                        } else {
                            this.setSampleDataPayload({});
                        }
                    }
                    if (newCardButton) {
                        newCardButton.focus();
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

            for (let i = 0; i < this._hostContainers.length; i++) {
                this._hostContainerChoicePicker.choices.push(
                    {
                        name: this._hostContainers[i].name,
                        value: i.toString(),
                    }
                );
            }

            this._hostContainerChoicePicker.onChanged = (sender) => {
                this.hostContainer = this._hostContainers[parseInt(this._hostContainerChoicePicker.value)];

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

        this.toolbar.addElement(this._undoButton);

        this._redoButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.Redo,
            "Redo",
            "acd-icon-redo",
            (sender: ToolbarButton) => { this.redo(); });
        this._redoButton.toolTip = "Redo your last changes";
        this._redoButton.isEnabled = false;

        this.toolbar.addElement(this._redoButton);

        this._copyJSONButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.CopyJSON,
            "Copy card payload",
            "acd-icon-copy");
        this._copyJSONButton.toolTip = "Copy the generated JSON payload of the card (template bound with data) to the clipboard. To copy only the template payload, use the Card Payload Editor.";
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

        this._helpButton = new ToolbarButton(
            CardDesigner.ToolbarCommands.Help,
            "Help",
            "acd-icon-help",
            (sender: ToolbarButton) => { this.showHelp(); });
        this._helpButton.toolTip = "Display help.";
        this._helpButton.separator = true;
        this._helpButton.alignment = ToolbarElementAlignment.Right;
        this.toolbar.addElement(this._helpButton);

        this._fullScreenHandler = new FullScreenHandler();
        this._fullScreenHandler.onFullScreenChanged = (isFullScreen: boolean) => {
            this._fullScreenButton.toolTip = isFullScreen ? "Exit full screen" : "Enter full screen";

            this.updateFullLayout();
        }
    }

    private launchJsonSchemaPopup() {
        let dialog = new OpenJsonSchemaDialog();
        dialog.title = "Create from JSON Schema";
        dialog.closeButton.caption = "Cancel";
        dialog.preventLightDismissal = true;
        dialog.width = "80%";
        dialog.height = "80%";
        dialog.open();

        dialog.submitButton.onClick = () => {
            dialog.close();
            if (dialog.output) {
                try {
                    let cardPayload = JSON.parse(dialog.output.cardPayload);

                    this.setCardPayload(cardPayload, true);
                } catch {
                    alert("The card template could not be loaded.");
                    return
                }

                if (dialog.output.sampleData) {
                    try {
                        let sampleDataPayload = JSON.parse(dialog.output.sampleData);

                        this.setSampleDataPayload(sampleDataPayload);
                        this.dataStructure = FieldDefinition.deriveFrom(sampleDataPayload);
                    } catch {
                        alert("The card data could not be loaded.")
                    }
                } else {
                    this.setSampleDataPayload({});
                }
            }

            const newCardButton = this._newCardButton.renderedElement;

            if (newCardButton) {
                newCardButton.focus();
            }
        }

        dialog.onClose = (d) => {
            const newCardButton = this._newCardButton.renderedElement;

            if (newCardButton) {
                newCardButton.focus();
            }
        };
    }


    private launchImagePopup() {
        let dialog = new OpenImageDialog();
        dialog.title = "Pic2card Dialog for Image Upload";
        dialog.closeButton.caption = "Cancel";
        dialog.preventLightDismissal = true;
        dialog.width = "80%";
        dialog.height = "80%";
        dialog.open();
        dialog.onClose = (d) => {
            const newCardButton = this._newCardButton.renderedElement;

            if (dialog.predictedCardJSON) {
                const { card, data } = dialog.predictedCardJSON;
                const addToUndoStack = true;

                this.setCardPayload(card, addToUndoStack);
                this.setSampleDataPayload(data);

                let loadNotification = document.createElement("span");
                loadNotification.id = "pic2cardLoadNotification";
                loadNotification.setAttribute("role", "status");
                loadNotification.setAttribute("aria-label", "Pic2Card generated Adaptive Card loaded");

                // It's a bit odd to jump up to the parent element here, but we need a place to park this empty element
                // so that it's seen by accessibility tools. If we put it on the button itself, the status message gets
                // read twice (once on DOM entry and again on focus).
                newCardButton.parentElement.appendChild(loadNotification);

                // element needs to enter the DOM, but shouldn't stay forever, lest it be read again...
                setTimeout(() => {
                    newCardButton.parentElement.removeChild(loadNotification);
                }, 500);
            }

            if (newCardButton) {
                newCardButton.focus();
            }
        };
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
                const adjustedPosition = Utils.adjustPointForScroll(this._currentMousePosition);
                this._draggedElement.style.left = adjustedPosition.x - 10 + "px";
                this._draggedElement.style.top = adjustedPosition.y - 10 + "px";
            }
        }
    }

    readonly toolbar: Toolbar = new Toolbar();

    lockDataStructure: boolean = false;

    constructor(hostContainers: Array<HostContainer> = null) {
        super();

        Adaptive.GlobalSettings.enableFullJsonRoundTrip = true;
        Adaptive.GlobalSettings.allowPreProcessingPropertyValues = true;
        Adaptive.GlobalSettings.setTabIndexAtCardRoot = false;

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
            validate: true,
            allowComments: true
        }

		// TODO: set this in our editor instead of defaults
        monaco.languages.json.jsonDefaults.setDiagnosticsOptions(monacoConfiguration);

        // Setup card JSON editor
        this._cardEditorToolbox.content = document.createElement("div");
        this._cardEditorToolbox.content.setAttribute("role", "region");
        this._cardEditorToolbox.content.setAttribute("aria-label", "card payload editor");
        this._cardEditorToolbox.content.classList.add("acd-code-editor");

        this._cardEditor = monaco.editor.create(
            this._cardEditorToolbox.content,
            {
                folding: true,
                fontSize: 13.5,
                language: 'json',
                minimap: {
                    enabled: true
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
            this._sampleDataEditorToolbox.content.setAttribute("role", "region");
            this._sampleDataEditorToolbox.content.setAttribute("aria-label", "sample data editor");
            this._sampleDataEditorToolbox.content.classList.add("acd-code-editor");

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
            '<div id="toolbarHost" role="region" aria-label="toolbar"></div>' +
            '<div class="content">' +
                '<div id="leftCollapsedPaneTabHost" class="acd-verticalCollapsedTabContainer acd-dockedLeft"></div>' +
                '<div id="toolPalettePanel" class="acd-toolPalette-pane" role="region" aria-label="card elements"></div>' +
                '<div class="acd-previewRightAndBottomDocks">' +
                    '<div class="acd-previewAndBottomDocks">' +
                        '<div class="acd-designer-card-header">CARD PREVIEW</div>' +
                        '<div id="cardArea" class="acd-designer-cardArea" role="region" aria-label="card preview">' +
                            '<div style="flex: 1 1 100%; overflow: auto;">' +
                                '<div id="designerHost" class="acd-designer-host"></div>' +
                            '</div>' +
                            '<div id="errorPane" class="acd-error-pane acd-hidden"></div>' +
                        '</div>' +
                        '<div id="treeViewPanel" class="acd-treeView-pane" role="region" aria-label="card structure"></div>' +
                       '<div id="propertySheetPanel" class="acd-propertySheet-pane" role="region" aria-label="element properties"></div>' +
                    '</div>' +
                    '<div id="jsonEditorPanel" class="acd-json-editor-pane"></div>' +
                    '<div id="bottomCollapsedPaneTabHost" class="acd-horizontalCollapsedTabContainer"></div>' +
                '</div>' +
                '<div id="rightCollapsedPaneTabHost" class="acd-verticalCollapsedTabContainer acd-dockedRight"></div>' +
            '</div>';

        this.toolbar.attachTo(document.getElementById("toolbarHost"));

        if (this._versionChoicePicker) {
            this._versionChoicePicker.selectedIndex = Shared.GlobalSettings.supportedTargetVersions.indexOf(this.targetVersion);
            this._versionChoicePicker.onChanged = (sender: ToolbarChoicePicker) => {
                this.targetVersion = Shared.GlobalSettings.supportedTargetVersions[parseInt(this._versionChoicePicker.value)];
            }
        }

        if (this._copyJSONButton.isVisible) {
            new Clipboard(
                this._copyJSONButton.renderedElement,
                {
                    text: (trigger) => JSON.stringify(this.getBoundCard(), null, 4)
                })
                .on("error", () => this._copyJSONButton.renderedElement.focus())
                .on("success", () => this._copyJSONButton.renderedElement.focus());
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

    getBoundCard(): object {
        return this._designerSurface ? this._designerSurface.getBoundCardPayloadAsObject() : undefined;
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

    showHelp() {
        let helpDialog = new HelpDialog();
        helpDialog.title = "Help";
        helpDialog.open();
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
                    this._versionChoicePicker.selectedIndex = Shared.GlobalSettings.supportedTargetVersions.indexOf(this._targetVersion);
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
        static readonly Help = "__helpButton";
    }
}
