"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var Clipboard = require("clipboard");
var Adaptive = require("adaptivecards");
var Constants = require("./constants");
var Designer = require("./card-designer-surface");
var adaptive_card_schema_1 = require("./adaptive-card-schema");
var fullscreen_handler_1 = require("./fullscreen-handler");
var toolbar_1 = require("./toolbar");
var side_pane_1 = require("./side-pane");
var splitter_1 = require("./splitter");
var tool_palette_1 = require("./tool-palette");
var default_container_1 = require("./containers/default-container");
var CardDesigner = /** @class */ (function () {
    function CardDesigner(hostContainers) {
        if (hostContainers === void 0) { hostContainers = null; }
        this._isMonacoEditorLoaded = false;
        this._undoStack = [];
        this._undoStackIndex = -1;
        this.preventCardUpdate = false;
        this.preventJsonUpdate = false;
        this._fullScreenHandler = new fullscreen_handler_1.FullScreenHandler();
        this.toolbar = new toolbar_1.Toolbar();
        this._hostContainers = hostContainers ? hostContainers : [];
        this.prepareToolbar();
        this._propertySheetHostConfig = new Adaptive.HostConfig({
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
        });
        this._propertySheetHostConfig.cssClassNamePrefix = "default";
    }
    CardDesigner.prototype.buildTreeView = function () {
        if (this._treeViewPane.content) {
            this._treeViewPane.content.innerHTML = "";
            this._treeViewPane.content.appendChild(this.designerSurface.rootPeer.treeItem.render());
        }
    };
    CardDesigner.prototype.buildPropertySheet = function (peer) {
        if (this._propertySheetPane.content) {
            this._propertySheetPane.content.innerHTML = "";
            var card = void 0;
            if (peer) {
                card = peer.buildPropertySheetCard();
            }
            else {
                card = new Adaptive.AdaptiveCard();
                card.parse({
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
                });
                card.padding = new Adaptive.PaddingDefinition(Adaptive.Spacing.Small, Adaptive.Spacing.Small, Adaptive.Spacing.Small, Adaptive.Spacing.Small);
            }
            card.hostConfig = this._propertySheetHostConfig;
            this._propertySheetPane.content.appendChild(card.render());
        }
    };
    CardDesigner.prototype.addPaletteItem = function (paletteItem, hostElement) {
        var _this = this;
        paletteItem.render();
        paletteItem.onStartDrag = function (sender) {
            _this._draggedPaletteItem = sender;
            _this._draggedElement = sender.cloneElement();
            _this._draggedElement.style.position = "absolute";
            _this._draggedElement.style.left = _this._currentMousePosition.x + "px";
            _this._draggedElement.style.top = _this._currentMousePosition.y + "px";
            document.body.appendChild(_this._draggedElement);
        };
        hostElement.appendChild(paletteItem.renderedElement);
    };
    CardDesigner.prototype.buildPalette = function () {
        this._toolPalettePane.content.innerHTML = "";
        var categorizedTypes = {};
        for (var i_1 = 0; i_1 < Adaptive.AdaptiveCard.elementTypeRegistry.getItemCount(); i_1++) {
            var dummyCardElement = Adaptive.AdaptiveCard.elementTypeRegistry.getItemAt(i_1).createInstance();
            var peerRegistration = Designer.CardDesignerSurface.cardElementPeerRegistry.findTypeRegistration(dummyCardElement.constructor);
            if (peerRegistration) {
                if (!categorizedTypes.hasOwnProperty(peerRegistration.category)) {
                    categorizedTypes[peerRegistration.category] = [];
                }
                var paletteItem = new tool_palette_1.ElementPaletteItem(Adaptive.AdaptiveCard.elementTypeRegistry.getItemAt(i_1), peerRegistration);
                categorizedTypes[peerRegistration.category].push(paletteItem);
            }
        }
        for (var category in categorizedTypes) {
            var node = document.createElement('li');
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
    };
    CardDesigner.prototype.endDrag = function () {
        if (this._draggedPaletteItem) {
            this._draggedPaletteItem.endDrag();
            this._draggedElement.remove();
            this._draggedPaletteItem = null;
            this._draggedElement = null;
        }
    };
    CardDesigner.prototype.recreateDesignerSurface = function () {
        var _this = this;
        var styleSheetLinkElement = document.getElementById("adaptiveCardStylesheet");
        if (styleSheetLinkElement == null) {
            styleSheetLinkElement = document.createElement("link");
            styleSheetLinkElement.id = "adaptiveCardStylesheet";
            document.getElementsByTagName("head")[0].appendChild(styleSheetLinkElement);
        }
        styleSheetLinkElement.rel = "stylesheet";
        styleSheetLinkElement.type = "text/css";
        styleSheetLinkElement.href = this.activeHostContainer.styleSheet;
        var designerBackground = document.getElementById("designerBackground");
        if (designerBackground) {
            designerBackground.style.backgroundColor = this.activeHostContainer.getBackgroundColor();
        }
        this.activeHostContainer.initialize();
        this._designerHostElement.innerHTML = "";
        this.activeHostContainer.renderTo(this._designerHostElement);
        this._designerSurface = new Designer.CardDesignerSurface(this.activeHostContainer.cardHost);
        this._designerSurface.onSelectedPeerChanged = function (peer) {
            _this.buildPropertySheet(peer);
        };
        this._designerSurface.onLayoutUpdated = function (isFullRefresh) {
            if (isFullRefresh) {
                _this.scheduleUpdateJsonFromCard();
            }
            _this.buildTreeView();
        };
        this._designerSurface.onCardValidated = function (errors) {
            var errorPane = document.getElementById("errorPane");
            errorPane.innerHTML = "";
            if (errors.length > 0) {
                var errorMessages = [];
                for (var _i = 0, errors_1 = errors; _i < errors_1.length; _i++) {
                    var error = errors_1[_i];
                    if (errorMessages.indexOf(error.message) < 0) {
                        errorMessages.push(error.message);
                    }
                }
                for (var _a = 0, errorMessages_1 = errorMessages; _a < errorMessages_1.length; _a++) {
                    var message = errorMessages_1[_a];
                    var errorElement = document.createElement("div");
                    errorElement.style.overflow = "hidden";
                    errorElement.style.textOverflow = "ellipsis";
                    errorElement.innerText = message;
                    errorPane.appendChild(errorElement);
                }
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
    };
    CardDesigner.prototype.activeHostContainerChanged = function () {
        this.recreateDesignerSurface();
    };
    CardDesigner.prototype.updateJsonEditorLayout = function () {
        if (this._isMonacoEditorLoaded) {
            // Monaco is very finicky. It will apparently only properly layout if
            // its direct container has an explicit height.
            var jsonEditorPaneRect = this._jsonEditorPane.attachedTo.getBoundingClientRect();
            var jsonEditorHeaderRect = this._jsonEditorPane.getHeaderBoundingRect();
            this._jsonEditorPane.content.style.height = (jsonEditorPaneRect.height - jsonEditorHeaderRect.height) + "px";
            this._monacoEditor.layout();
        }
    };
    CardDesigner.prototype.updateFullLayout = function () {
        this.scheduleLayoutUpdate();
        this.updateJsonEditorLayout();
    };
    CardDesigner.prototype.setJsonPayload = function (payload) {
        this._monacoEditor.setValue(JSON.stringify(payload, null, 4));
    };
    CardDesigner.prototype.updateJsonFromCard = function (addToUndoStack) {
        if (addToUndoStack === void 0) { addToUndoStack = true; }
        try {
            this.preventCardUpdate = true;
            if (!this.preventJsonUpdate && this._isMonacoEditorLoaded) {
                var cardPayload = this.card.toJSON();
                if (addToUndoStack) {
                    this.addToUndoStack(cardPayload);
                }
                this.setJsonPayload(cardPayload);
            }
        }
        finally {
            this.preventCardUpdate = false;
        }
    };
    CardDesigner.prototype.scheduleUpdateJsonFromCard = function () {
        var _this = this;
        clearTimeout(this.jsonUpdateTimer);
        if (!this.preventJsonUpdate) {
            this.jsonUpdateTimer = setTimeout(function () { _this.updateJsonFromCard(); }, 100);
        }
    };
    CardDesigner.prototype.getCurrentJsonPayload = function () {
        return this._isMonacoEditorLoaded ? this._monacoEditor.getValue() : Constants.defaultPayload;
    };
    CardDesigner.prototype.updateCardFromJson = function () {
        try {
            this.preventJsonUpdate = true;
            if (!this.preventCardUpdate) {
                this.designerSurface.setCardPayloadAsString(this.getCurrentJsonPayload());
            }
        }
        finally {
            this.preventJsonUpdate = false;
        }
    };
    CardDesigner.prototype.scheduleUpdateCardFromJson = function () {
        var _this = this;
        clearTimeout(this.cardUpdateTimer);
        if (!this.preventCardUpdate) {
            this.cardUpdateTimer = setTimeout(function () { _this.updateCardFromJson(); }, 100);
        }
    };
    CardDesigner.prototype.scheduleLayoutUpdate = function () {
        var _this = this;
        clearTimeout(this.updateLayoutTimer);
        this.updateLayoutTimer = setTimeout(function () { _this.designerSurface.updateLayout(false); }, 50);
    };
    CardDesigner.prototype.prepareToolbar = function () {
        var _this = this;
        this._fullScreenButton = new toolbar_1.ToolbarButton("Enter Full Screen", "acd-icon-fullScreen", function (sender) { _this._fullScreenHandler.toggleFullScreen(); });
        this.toolbar.addElement(this._fullScreenButton);
        if (this._hostContainers && this._hostContainers.length > 0) {
            this.toolbar.addElement(new toolbar_1.ToolbarSeparator());
            this.toolbar.addElement(new toolbar_1.ToolbarLabel("Select Host app:"));
            this._hostContainerChoicePicker = new toolbar_1.ToolbarChoicePicker();
            for (var i = 0; i < this._hostContainers.length; i++) {
                this._hostContainerChoicePicker.choices.push({
                    name: this._hostContainers[i].name,
                    value: i.toString(),
                });
            }
            this._hostContainerChoicePicker.onChanged = function (sender) {
                _this.activeHostContainer = _this._hostContainers[Number.parseInt(_this._hostContainerChoicePicker.value)];
                _this.activeHostContainerChanged();
            };
            this.toolbar.addElement(this._hostContainerChoicePicker);
        }
        this.toolbar.addElement(new toolbar_1.ToolbarSeparator());
        this._undoButton = new toolbar_1.ToolbarButton("Undo", "acd-icon-undo", function (sender) { _this.undo(); });
        this._undoButton.toolTip = "Undo your last change";
        this._undoButton.isEnabled = false;
        this._undoButton.displayCaption = false;
        this.toolbar.addElement(this._undoButton);
        this._redoButton = new toolbar_1.ToolbarButton("Redo", "acd-icon-redo", function (sender) { _this.redo(); });
        this._redoButton.toolTip = "Redo your last changes";
        this._redoButton.isEnabled = false;
        this._redoButton.displayCaption = false;
        this.toolbar.addElement(this._redoButton);
        this.toolbar.addElement(new toolbar_1.ToolbarSeparator());
        this.toolbar.addElement(new toolbar_1.ToolbarButton("New card", "acd-icon-newCard", function (sender) { _this.newCard(); }));
        this._copyJSONButton = new toolbar_1.ToolbarButton("Copy JSON", "acd-icon-copy");
        this.toolbar.addElement(this._copyJSONButton);
        this._fullScreenHandler = new fullscreen_handler_1.FullScreenHandler();
        this._fullScreenHandler.onFullScreenChanged = function (isFullScreen) {
            _this._fullScreenButton.caption = isFullScreen ? "Exit full screen" : "Enter full screen";
            _this.updateFullLayout();
        };
    };
    CardDesigner.prototype.onResize = function () {
        this._monacoEditor.layout();
    };
    CardDesigner.prototype.loadMonaco = function (callback) {
        window["require"].config({ paths: { 'vs': './editor/monaco/min/vs' } });
        window["require"](['vs/editor/editor.main'], function () {
            callback();
        });
    };
    CardDesigner.prototype.monacoEditorLoaded = function () {
        var _this = this;
        var monacoConfiguration = {
            schemas: [
                {
                    uri: "http://adaptivecards.io/schemas/adaptive-card.json",
                    schema: adaptive_card_schema_1.adaptiveCardSchema,
                    fileMatch: ["*"],
                }
            ],
            validate: false,
            allowComments: true
        };
        window["monaco"].languages.json.jsonDefaults.setDiagnosticsOptions(monacoConfiguration);
        this._jsonEditorPane.content = document.createElement("div");
        this._monacoEditor = window["monaco"].editor.create(this._jsonEditorPane.content, {
            folding: true,
            validate: false,
            fontSize: 13.5,
            language: 'json',
            minimap: {
                enabled: false
            }
        });
        this._monacoEditor.onDidChangeModelContent(function () { _this.scheduleUpdateCardFromJson(); });
        window.addEventListener('resize', function () { _this.onResize(); });
        this._isMonacoEditorLoaded = true;
        this.updateJsonEditorLayout();
        this.updateJsonFromCard(false);
    };
    CardDesigner.prototype.updateToolbar = function () {
        this._undoButton.isEnabled = this.canUndo;
        this._redoButton.isEnabled = this.canRedo;
    };
    CardDesigner.prototype.addToUndoStack = function (payload) {
        var doAdd = true;
        if (this._undoStack.length > 0) {
            doAdd = this._undoStack[this._undoStack.length - 1] != payload;
        }
        if (doAdd) {
            var undoPayloadsToDiscard = this._undoStack.length - (this._undoStackIndex + 1);
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
    };
    CardDesigner.prototype.handlePointerUp = function (e) {
        this.endDrag();
        this.designerSurface.endDrag();
    };
    CardDesigner.prototype.handlePointerMove = function (e) {
        this._currentMousePosition = { x: e.x, y: e.y };
        var isPointerOverDesigner = this.designerSurface.isPointerOver(this._currentMousePosition.x, this._currentMousePosition.y);
        var peerDropped = false;
        if (this._draggedPaletteItem && isPointerOverDesigner) {
            var peer = this._draggedPaletteItem.createPeer(this.designerSurface);
            var clientCoordinates = this.designerSurface.pageToClientCoordinates(this._currentMousePosition.x, this._currentMousePosition.y);
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
    };
    CardDesigner.prototype.attachTo = function (root) {
        var _this = this;
        if (this._hostContainers && this._hostContainers.length > 0) {
            this._activeHostContainer = this._hostContainers[0];
        }
        else {
            this._activeHostContainer = new default_container_1.DefaultContainer("Default", "./css/default-container.css");
        }
        root.style.flex = "1 1 auto";
        root.style.display = "flex";
        root.style.flexDirection = "column";
        root.style.overflow = "hidden";
        root.innerHTML =
            '<div id="toolbarHost"></div>' +
                '<div class="content" style="display: flex; flex: 1 1 auto; overflow-y: hidden;">' +
                '<div id="leftCollapsedPaneTabHost" class="acd-verticalCollapsedTabContainer" style="border-right: 1px solid #D2D2D2;"></div>' +
                '<div id="toolPalettePane" class="selector-toolPalette" style="background-color: white; border-right: 1px solid #D2D2D2;">' +
                '<div id="toolPaletteHost" class="acd-dockedPane"></div>' +
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
        new Clipboard(this._copyJSONButton.renderedElement, {
            text: function () {
                return JSON.stringify(this.card.toJSON(), null, 4);
            }
        });
        // Tool palette pane
        this._toolPalettePane = new side_pane_1.SidePane(document.getElementById("toolPalettePane"), document.getElementById("leftCollapsedPaneTabHost"), "toolPalette", "Tool box", "selector-toolPalette");
        this._toolPalettePane.onToggled = function (sender) {
            _this.updateFullLayout();
        };
        this._toolPalettePane.content = document.getElementById("toolPaletteHost");
        // Splitter for JSON editor pane
        var jsonEditorSplitter = new splitter_1.Splitter(document.getElementById("jsonEditorSplitter"), document.getElementById("jsonEditorPane"), false);
        jsonEditorSplitter.onResized = function (splitter, newSize) {
            _this.updateJsonEditorLayout();
            _this._jsonEditorPane.saveState();
        };
        // JSON editor pane
        this._jsonEditorPane = new side_pane_1.SidePane(document.getElementById("jsonEditorPane"), document.getElementById("bottomCollapsedPaneTabHost"), "jsonEditor", "JSON", "selector-jsonEditor", side_pane_1.SidePaneOrientation.Horizontal);
        this._jsonEditorPane.onToggled = function (sender) {
            _this.updateFullLayout();
        };
        this._jsonEditorPane.content = document.createElement("div");
        this._jsonEditorPane.content.style.padding = "8px";
        this._jsonEditorPane.content.innerText = "Loading editor...";
        // Splitter for property sheet pane
        var propertySheetSplitter = new splitter_1.Splitter(document.getElementById("propertySheetSplitter"), document.getElementById("propertySheetPane"), true);
        propertySheetSplitter.minimum = 230;
        propertySheetSplitter.onResized = function (splitter, newSize) {
            _this.scheduleLayoutUpdate();
            _this._propertySheetPane.saveState();
        };
        // Property sheet pane
        this._propertySheetPane = new side_pane_1.SidePane(document.getElementById("propertySheetPane"), document.getElementById("rightCollapsedPaneTabHost"), "propertySheet", "Element properties", "selector-propertySheet");
        this._propertySheetPane.onToggled = function (sender) {
            _this.updateFullLayout();
        };
        this._propertySheetPane.content = document.getElementById("propertySheetHost");
        // Splitter for tree view pane
        var treeViewSplitter = new splitter_1.Splitter(document.getElementById("treeViewSplitter"), document.getElementById("treeViewPane"), true);
        treeViewSplitter.minimum = 140;
        treeViewSplitter.onResized = function (splitter, newSize) {
            _this.scheduleLayoutUpdate();
            _this._treeViewPane.saveState();
        };
        // Tree view pane
        this._treeViewPane = new side_pane_1.SidePane(document.getElementById("treeViewPane"), document.getElementById("rightCollapsedPaneTabHost"), "treeView", "Visual tree view", "selector-treeView");
        this._treeViewPane.onToggled = function (sender) {
            _this.updateFullLayout();
        };
        this._treeViewPane.content = document.getElementById("treeViewHost");
        this._designerHostElement = document.getElementById("designerHost");
        this.recreateDesignerSurface();
        this.loadMonaco(function () { _this.monacoEditorLoaded(); });
        window.addEventListener("pointermove", function (e) { _this.handlePointerMove(e); });
        window.addEventListener("resize", function () { _this.scheduleLayoutUpdate(); });
        window.addEventListener("pointerup", function (e) { _this.handlePointerUp(e); });
        var card = new Adaptive.AdaptiveCard();
        card.onImageLoaded = function (image) {
            _this.scheduleLayoutUpdate();
        };
        this.card = card;
    };
    CardDesigner.prototype.undo = function () {
        if (this.canUndo) {
            this._undoStackIndex--;
            var card = this._undoStack[this._undoStackIndex];
            this.setJsonPayload(card);
            this.updateToolbar();
        }
    };
    CardDesigner.prototype.redo = function () {
        if (this._undoStackIndex < this._undoStack.length - 1) {
            this._undoStackIndex++;
            var card = this._undoStack[this._undoStackIndex];
            this.setJsonPayload(card);
            this.updateToolbar();
        }
    };
    CardDesigner.prototype.newCard = function () {
        var card = {
            type: "AdaptiveCard",
            version: "1.0",
            body: []
        };
        this.setJsonPayload(card);
    };
    CardDesigner.prototype.setCard = function (payload) {
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
    };
    CardDesigner.prototype.getCard = function () {
        return this.designerSurface.card.toJSON();
    };
    Object.defineProperty(CardDesigner.prototype, "activeHostContainer", {
        get: function () {
            return this._activeHostContainer;
        },
        set: function (value) {
            if (this._activeHostContainer !== value) {
                this._activeHostContainer = value;
                this.activeHostContainerChanged();
            }
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardDesigner.prototype, "canUndo", {
        get: function () {
            return this._undoStackIndex >= 1;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardDesigner.prototype, "canRedo", {
        get: function () {
            return this._undoStackIndex < this._undoStack.length - 1;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardDesigner.prototype, "card", {
        get: function () {
            return this._card;
        },
        set: function (value) {
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
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardDesigner.prototype, "designerSurface", {
        get: function () {
            return this._designerSurface;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardDesigner.prototype, "treeViewPane", {
        get: function () {
            return this._treeViewPane;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardDesigner.prototype, "propertySheetPane", {
        get: function () {
            return this._propertySheetPane;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardDesigner.prototype, "jsonEditorPane", {
        get: function () {
            return this._jsonEditorPane;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardDesigner.prototype, "toolPalettePane", {
        get: function () {
            return this._toolPalettePane;
        },
        enumerable: true,
        configurable: true
    });
    CardDesigner.MAX_UNDO_STACK_SIZE = 50;
    return CardDesigner;
}());
exports.CardDesigner = CardDesigner;
//# sourceMappingURL=card-designer.js.map