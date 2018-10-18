"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var Adaptive = require("adaptivecards");
var Controls = require("adaptivecards-controls");
var draggable_element_1 = require("./draggable-element");
var peer_command_1 = require("./peer-command");
var card_designer_surface_1 = require("./card-designer-surface");
var treeitem_1 = require("./treeitem");
var miscellaneous_1 = require("./miscellaneous");
function addLabelAndInput(container, label, inputType, separator) {
    if (separator === void 0) { separator = false; }
    var leftColumn = new Adaptive.Column();
    leftColumn.width = new Adaptive.SizeAndUnit(100, Adaptive.SizeUnit.Pixel);
    leftColumn.verticalContentAlignment = Adaptive.VerticalAlignment.Center;
    var rightColumn = new Adaptive.Column();
    rightColumn.width = "stretch";
    rightColumn.verticalContentAlignment = Adaptive.VerticalAlignment.Center;
    var columnSet = new Adaptive.ColumnSet();
    if (separator) {
        columnSet.spacing = Adaptive.Spacing.Large;
        columnSet.separator = true;
    }
    else {
        columnSet.spacing = Adaptive.Spacing.Small;
    }
    columnSet.addColumn(leftColumn);
    columnSet.addColumn(rightColumn);
    var result = {
        label: new Adaptive.TextBlock(),
        input: new inputType()
    };
    result.label.horizontalAlignment = Adaptive.HorizontalAlignment.Right;
    result.label.text = label;
    result.label.wrap = true;
    /*
    result.label.selectAction = new Adaptive.SubmitAction();
    result.label.selectAction.onExecute = (sender: Adaptive.Action) => {
        alert("Clicked: " + label);
    }
    */
    leftColumn.addItem(result.label);
    rightColumn.addItem(result.input);
    container.addItem(columnSet);
    return result;
}
var NameValuePairEditor = /** @class */ (function () {
    function NameValuePairEditor() {
        this.nameValuePairs = [];
        this.title = "Name/value pairs";
        this.messageIfEmpty = "This collection is empty.";
        this.addButtonTitle = "Add a new pair";
        this.nameInputTitle = "Name";
        this.valueInputTitle = "Value";
    }
    NameValuePairEditor.prototype.changed = function (refreshPropertySheet) {
        if (refreshPropertySheet === void 0) { refreshPropertySheet = false; }
        if (this.onChanged) {
            this.onChanged(this, refreshPropertySheet);
        }
    };
    NameValuePairEditor.prototype.render = function () {
        var _this = this;
        var result = new Adaptive.Container();
        var titleTextBlock = new Adaptive.TextBlock();
        titleTextBlock.text = "**" + this.title + "**";
        result.addItem(titleTextBlock);
        if (this.nameValuePairs.length == 0) {
            var messageTextBlock = new Adaptive.TextBlock();
            messageTextBlock.spacing = Adaptive.Spacing.Small;
            messageTextBlock.text = this.messageIfEmpty;
            result.addItem(messageTextBlock);
        }
        else {
            var _loop_1 = function (i) {
                var textInput = new Adaptive.TextInput();
                textInput.placeholder = this_1.nameInputTitle;
                textInput.defaultValue = this_1.nameValuePairs[i].name;
                textInput.onValueChanged = function (sender) {
                    _this.nameValuePairs[i].name = sender.value;
                    _this.changed();
                };
                var nameColumn = new Adaptive.Column("stretch");
                nameColumn.addItem(textInput);
                textInput = new Adaptive.TextInput();
                textInput.placeholder = this_1.valueInputTitle;
                textInput.defaultValue = this_1.nameValuePairs[i].value;
                textInput.onValueChanged = function (sender) {
                    _this.nameValuePairs[i].value = sender.value;
                    _this.changed();
                };
                var valueColumn = new Adaptive.Column("stretch");
                valueColumn.spacing = Adaptive.Spacing.Small;
                valueColumn.addItem(textInput);
                var removeAction = new Adaptive.SubmitAction();
                removeAction.title = "X";
                removeAction.onExecute = function (sender) {
                    _this.nameValuePairs.splice(i, 1);
                    _this.changed(true);
                };
                var actionSet_1 = new Adaptive.ActionSet();
                actionSet_1.addAction(removeAction);
                var removeColumn = new Adaptive.Column("auto");
                removeColumn.spacing = Adaptive.Spacing.Small;
                removeColumn.addItem(actionSet_1);
                var columnSet = new Adaptive.ColumnSet();
                columnSet.spacing = Adaptive.Spacing.Small;
                columnSet.addColumn(nameColumn);
                columnSet.addColumn(valueColumn);
                columnSet.addColumn(removeColumn);
                result.addItem(columnSet);
            };
            var this_1 = this;
            for (var i = 0; i < this.nameValuePairs.length; i++) {
                _loop_1(i);
            }
        }
        var addAction = new Adaptive.SubmitAction();
        addAction.title = this.addButtonTitle;
        addAction.onExecute = function (sender) {
            _this.nameValuePairs.push({ "name": "", "value": "" });
            _this.changed(true);
        };
        var actionSet = new Adaptive.ActionSet();
        actionSet.spacing = Adaptive.Spacing.Small;
        actionSet.addAction(addAction);
        result.addItem(actionSet);
        return result;
    };
    return NameValuePairEditor;
}());
var DesignerPeerInplaceEditor = /** @class */ (function () {
    function DesignerPeerInplaceEditor() {
    }
    return DesignerPeerInplaceEditor;
}());
var CardElementPeerInplaceEditor = /** @class */ (function (_super) {
    __extends(CardElementPeerInplaceEditor, _super);
    function CardElementPeerInplaceEditor(cardElement) {
        var _this = _super.call(this) || this;
        _this.cardElement = cardElement;
        return _this;
    }
    return CardElementPeerInplaceEditor;
}(DesignerPeerInplaceEditor));
var DesignerPeerRegistrationBase = /** @class */ (function () {
    function DesignerPeerRegistrationBase(category, iconClass) {
        if (iconClass === void 0) { iconClass = null; }
        this.category = category;
        this.iconClass = iconClass;
    }
    return DesignerPeerRegistrationBase;
}());
exports.DesignerPeerRegistrationBase = DesignerPeerRegistrationBase;
var DesignerPeerRegistration = /** @class */ (function (_super) {
    __extends(DesignerPeerRegistration, _super);
    function DesignerPeerRegistration(sourceType, peerType, category, iconClass) {
        if (iconClass === void 0) { iconClass = null; }
        var _this = _super.call(this, category, iconClass) || this;
        _this.sourceType = sourceType;
        _this.peerType = peerType;
        return _this;
    }
    return DesignerPeerRegistration;
}(DesignerPeerRegistrationBase));
exports.DesignerPeerRegistration = DesignerPeerRegistration;
var DesignerPeer = /** @class */ (function (_super) {
    __extends(DesignerPeer, _super);
    function DesignerPeer(designerSurface, registration) {
        var _this = _super.call(this) || this;
        _this._children = [];
        _this._isSelected = false;
        _this._inplaceEditor = null;
        if (!registration) {
            alert(_this.constructor.name);
        }
        _this.registration = registration;
        _this.designerSurface = designerSurface;
        _this.treeItem = new treeitem_1.TreeItem(_this);
        return _this;
    }
    DesignerPeer.prototype.closeInplaceEditor = function (applyChanges) {
        if (this._inplaceEditor) {
            if (applyChanges) {
                this._inplaceEditor.applyChanges();
                this.changed(true);
            }
            this._inplaceEditor = null;
            this._inplaceEditorOverlay.remove();
        }
    };
    DesignerPeer.prototype.tryOpenInplaceEditor = function () {
        var _this = this;
        this._inplaceEditor = this.createInplaceEditor();
        if (this._inplaceEditor) {
            this._inplaceEditor.onClose = function (applyChanges) {
                _this.closeInplaceEditor(applyChanges);
            };
            this._inplaceEditorOverlay = document.createElement("div");
            this._inplaceEditorOverlay.tabIndex = 0;
            this._inplaceEditorOverlay.style.zIndex = "600";
            this._inplaceEditorOverlay.style.backgroundColor = "transparent";
            this._inplaceEditorOverlay.style.position = "absolute";
            this._inplaceEditorOverlay.style.left = "0";
            this._inplaceEditorOverlay.style.top = "0";
            this._inplaceEditorOverlay.style.width = document.documentElement.scrollWidth + "px";
            this._inplaceEditorOverlay.style.height = document.documentElement.scrollHeight + "px";
            this._inplaceEditorOverlay.onfocus = function (e) { _this.closeInplaceEditor(true); };
            var boundingRect = this.getCardObjectBoundingRect();
            var inplaceEditorHost = document.createElement("div");
            inplaceEditorHost.className = "acd-inplace-editor-host";
            inplaceEditorHost.style.left = Math.floor(boundingRect.left + pageXOffset) + "px";
            inplaceEditorHost.style.top = Math.floor(boundingRect.top + pageYOffset) + "px";
            inplaceEditorHost.style.width = Math.ceil(boundingRect.width) + "px";
            inplaceEditorHost.style.height = Math.ceil(boundingRect.height) + "px";
            var renderedInplaceEditor = this._inplaceEditor.render();
            renderedInplaceEditor.classList.add("acd-inplace-editor");
            renderedInplaceEditor.tabIndex = 0;
            renderedInplaceEditor.onblur = function (e) { _this.closeInplaceEditor(true); };
            inplaceEditorHost.appendChild(renderedInplaceEditor);
            this._inplaceEditorOverlay.appendChild(inplaceEditorHost);
            document.body.appendChild(this._inplaceEditorOverlay);
            this._inplaceEditor.initialize();
            return true;
        }
        return false;
    };
    DesignerPeer.prototype.doubleClick = function (e) {
        _super.prototype.doubleClick.call(this, e);
        this.tryOpenInplaceEditor();
    };
    DesignerPeer.prototype.isContainer = function () {
        return false;
    };
    DesignerPeer.prototype.getToolTip = function () {
        return null;
    };
    DesignerPeer.prototype.pointerDown = function (e) {
        _super.prototype.pointerDown.call(this, e);
        this.isSelected = true;
    };
    DesignerPeer.prototype.internalAddCommands = function (commands) {
        // Do nothing in base implementation
    };
    DesignerPeer.prototype.internalRender = function () {
        var element = document.createElement("div");
        element.classList.add("acd-peer");
        var toolTip = this.getToolTip();
        if (toolTip) {
            element.title = toolTip;
        }
        if (this.isContainer()) {
            element.classList.add("container");
        }
        element.style.position = "absolute";
        return element;
    };
    DesignerPeer.prototype.internalUpdateCssStyles = function () {
        if (this.isSelected) {
            this.renderedElement.classList.add("selected");
        }
        else {
            this.renderedElement.classList.remove("selected");
        }
        if (this.dragging) {
            this.renderedElement.classList.add("dragging");
        }
        else {
            this.renderedElement.classList.remove("dragging");
        }
    };
    DesignerPeer.prototype.peerAdded = function (newPeer) {
        this.changed(false);
        if (this.onPeerAdded) {
            this.onPeerAdded(this, newPeer);
        }
    };
    DesignerPeer.prototype.changed = function (updatePropertySheet) {
        if (this.onChanged) {
            this.onChanged(this, updatePropertySheet);
        }
    };
    DesignerPeer.prototype.peerRemoved = function (peer) {
        if (this.onPeerRemoved) {
            this.onPeerRemoved(peer);
        }
    };
    DesignerPeer.prototype.internalUpdateLayout = function () {
        if (this.renderedElement) {
            var clientRect = this.getBoundingRect();
            this.renderedElement.style.width = clientRect.width + "px";
            this.renderedElement.style.height = clientRect.height + "px";
            this.renderedElement.style.left = clientRect.left + "px";
            this.renderedElement.style.top = clientRect.top + "px";
        }
    };
    DesignerPeer.prototype.createInplaceEditor = function () {
        return null;
    };
    DesignerPeer.prototype.getExcludedProperties = function () {
        return [];
    };
    DesignerPeer.prototype.getTreeItemText = function () {
        return null;
    };
    DesignerPeer.prototype.canDrop = function (peer) {
        return false;
    };
    DesignerPeer.prototype.canBeRemoved = function () {
        return true;
    };
    DesignerPeer.prototype.tryDrop = function (peer, insertionPoint) {
        return false;
    };
    DesignerPeer.prototype.insertChild = function (peer, index) {
        if (index === void 0) { index = -1; }
        if (index == -1) {
            this._children.push(peer);
        }
        else {
            this._children.splice(index, 0, peer);
        }
        peer.parent = this;
        this.peerAdded(peer);
    };
    DesignerPeer.prototype.removeChild = function (peer) {
        var index = this._children.indexOf(peer);
        if (index >= 0) {
            peer.parent = null;
            this._children.splice(index, 1);
        }
    };
    DesignerPeer.prototype.getChildCount = function () {
        return this._children.length;
    };
    DesignerPeer.prototype.getChildAt = function (index) {
        return this._children[index];
    };
    DesignerPeer.prototype.getCommands = function (promoteParentCommands) {
        if (promoteParentCommands === void 0) { promoteParentCommands = false; }
        var result = [];
        this.internalAddCommands(result);
        if (promoteParentCommands && this.parent) {
            var parentCommands = this.parent.getCommands();
            for (var _i = 0, parentCommands_1 = parentCommands; _i < parentCommands_1.length; _i++) {
                var command = parentCommands_1[_i];
                if (command.isPromotable) {
                    result.push(command);
                }
            }
        }
        return result;
    };
    DesignerPeer.prototype.remove = function (onlyFromCard, removeChildren) {
        if (removeChildren) {
            while (this._children.length > 0) {
                this._children[0].remove(onlyFromCard, removeChildren);
            }
        }
        var result = this.internalRemove();
        if (result && !onlyFromCard) {
            if (this.parent) {
                this.parent.removeChild(this);
            }
            this.removeElementsFromDesignerSurface();
            this.peerRemoved(this);
        }
        return result;
    };
    DesignerPeer.prototype.addElementsToDesignerSurface = function (designerSurface, processChildren) {
        if (processChildren === void 0) { processChildren = false; }
        designerSurface.appendChild(this.renderedElement);
        if (processChildren) {
            for (var i = 0; i < this.getChildCount(); i++) {
                this.getChildAt(i).addElementsToDesignerSurface(designerSurface, processChildren);
            }
        }
    };
    DesignerPeer.prototype.removeElementsFromDesignerSurface = function (processChildren) {
        if (processChildren === void 0) { processChildren = false; }
        this.renderedElement.remove();
        if (processChildren) {
            for (var i = 0; i < this.getChildCount(); i++) {
                this.getChildAt(i).removeElementsFromDesignerSurface(processChildren);
            }
        }
    };
    DesignerPeer.prototype.buildPropertySheetCard = function () {
        var result = new Adaptive.AdaptiveCard();
        result.padding = new Adaptive.PaddingDefinition(Adaptive.Spacing.Small, Adaptive.Spacing.Small, Adaptive.Spacing.Small, Adaptive.Spacing.Small);
        this.internalAddPropertySheetEntries(result, true);
        var actionSet = new Adaptive.ActionSet();
        var commands = this.getCommands(true);
        var _loop_2 = function (command) {
            var action = new Adaptive.SubmitAction();
            action.title = command.name;
            action.onExecute = function (sender) {
                command.execute(command, action.renderedElement);
            };
            actionSet.addAction(action);
        };
        for (var _i = 0, commands_1 = commands; _i < commands_1.length; _i++) {
            var command = commands_1[_i];
            _loop_2(command);
        }
        result.addItem(actionSet);
        return result;
    };
    Object.defineProperty(DesignerPeer.prototype, "isSelected", {
        get: function () {
            return this._isSelected;
        },
        set: function (value) {
            if (value != this._isSelected) {
                this._isSelected = value;
                this.updateLayout();
                this.treeItem.updateLayout();
                if (this.onSelectedChanged) {
                    this.onSelectedChanged(this);
                }
            }
        },
        enumerable: true,
        configurable: true
    });
    return DesignerPeer;
}(draggable_element_1.DraggableElement));
exports.DesignerPeer = DesignerPeer;
var ActionPeer = /** @class */ (function (_super) {
    __extends(ActionPeer, _super);
    function ActionPeer(designerSurface, registration, action) {
        var _this = _super.call(this, designerSurface, registration) || this;
        _this._action = action;
        return _this;
    }
    ActionPeer.prototype.getCardObjectTypeName = function () {
        return this.action.getJsonTypeName();
    };
    ActionPeer.prototype.doubleClick = function (e) {
        _super.prototype.doubleClick.call(this, e);
        this.action.renderedElement.click();
    };
    ActionPeer.prototype.internalRemove = function () {
        return this.action.remove();
    };
    ActionPeer.prototype.getTreeItemText = function () {
        if (this.action.title && this.action.title != "") {
            return this.action.title;
        }
        else {
            return _super.prototype.getTreeItemText.call(this);
        }
    };
    ActionPeer.prototype.isDraggable = function () {
        return false;
    };
    ActionPeer.prototype.getBoundingRect = function () {
        var designSurfaceOffset = this.designerSurface.getDesignerSurfaceOffset();
        var actionBoundingRect = this.action.renderedElement.getBoundingClientRect();
        return new miscellaneous_1.Rect(actionBoundingRect.top - designSurfaceOffset.y, actionBoundingRect.right - designSurfaceOffset.x, actionBoundingRect.bottom - designSurfaceOffset.y, actionBoundingRect.left - designSurfaceOffset.x);
    };
    ActionPeer.prototype.getCardObjectBoundingRect = function () {
        var actionBoundingRect = this.action.renderedElement.getBoundingClientRect();
        return new miscellaneous_1.Rect(actionBoundingRect.top, actionBoundingRect.right, actionBoundingRect.bottom, actionBoundingRect.left);
    };
    ActionPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        if (includeHeader) {
            var actionType = new Adaptive.TextBlock();
            actionType.text = "**" + this.action.getJsonTypeName() + "**";
            card.addItem(actionType);
        }
        var id = addLabelAndInput(card, "Id:", Adaptive.TextInput);
        id.input.defaultValue = this.action.id;
        id.input.placeholder = "(not set)";
        id.input.onValueChanged = function () {
            _this.action.id = id.input.value;
            _this.changed(false);
        };
        var title = addLabelAndInput(card, "Title:", Adaptive.TextInput);
        title.input.defaultValue = this.action.title;
        title.input.placeholder = "(not set)";
        title.input.onValueChanged = function () {
            _this.action.title = title.input.value;
            _this.changed(false);
        };
        var iconUrl = addLabelAndInput(card, "Icon URL:", Adaptive.TextInput);
        iconUrl.input.defaultValue = this.action.iconUrl;
        iconUrl.input.placeholder = "(not set)";
        iconUrl.input.onValueChanged = function () {
            _this.action.iconUrl = iconUrl.input.value;
            _this.changed(false);
        };
    };
    Object.defineProperty(ActionPeer.prototype, "action", {
        get: function () {
            return this._action;
        },
        enumerable: true,
        configurable: true
    });
    return ActionPeer;
}(DesignerPeer));
exports.ActionPeer = ActionPeer;
var TypedActionPeer = /** @class */ (function (_super) {
    __extends(TypedActionPeer, _super);
    function TypedActionPeer(designerSurface, registration, action) {
        return _super.call(this, designerSurface, registration, action) || this;
    }
    Object.defineProperty(TypedActionPeer.prototype, "action", {
        get: function () {
            return this._action;
        },
        enumerable: true,
        configurable: true
    });
    return TypedActionPeer;
}(ActionPeer));
exports.TypedActionPeer = TypedActionPeer;
var HttpActionPeer = /** @class */ (function (_super) {
    __extends(HttpActionPeer, _super);
    function HttpActionPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    HttpActionPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var method = addLabelAndInput(card, "Method:", Adaptive.ChoiceSetInput);
        method.input.isCompact = true;
        method.input.choices.push(new Adaptive.Choice("GET", "GET"));
        method.input.choices.push(new Adaptive.Choice("POST", "POST"));
        method.input.placeholder = "(not set)";
        method.input.defaultValue = this.action.method;
        method.input.onValueChanged = function () {
            _this.action.method = method.input.value;
            _this.changed(true);
        };
        var url = addLabelAndInput(card, "Url:", Adaptive.TextInput);
        url.input.defaultValue = this.action.url;
        url.input.placeholder = "(not set)";
        url.input.onValueChanged = function () {
            _this.action.url = url.input.value;
            _this.changed(false);
        };
        if (this.action.method && this.action.method.toLowerCase() == "post") {
            var body = addLabelAndInput(card, "Body:", Adaptive.TextInput);
            body.input.isMultiline = true;
            body.input.defaultValue = this.action.body;
            body.input.placeholder = "(not set)";
            body.input.onValueChanged = function () {
                _this.action.body = body.input.value;
                _this.changed(false);
            };
        }
        var headersEditor = new NameValuePairEditor();
        headersEditor.title = "HTTP headers:";
        headersEditor.addButtonTitle = "Add a new header";
        headersEditor.messageIfEmpty = "This action has no headers.";
        for (var _i = 0, _a = this.action.headers; _i < _a.length; _i++) {
            var choice = _a[_i];
            headersEditor.nameValuePairs.push({ "name": choice.name, "value": choice.value });
        }
        headersEditor.onChanged = function (sender, refreshPropertySheet) {
            _this.action.headers = [];
            for (var _i = 0, _a = sender.nameValuePairs; _i < _a.length; _i++) {
                var nameValuePair = _a[_i];
                _this.action.headers.push(new Adaptive.HttpHeader(nameValuePair.name, nameValuePair.value));
            }
            _this.changed(refreshPropertySheet);
        };
        card.addItem(headersEditor.render());
    };
    return HttpActionPeer;
}(TypedActionPeer));
exports.HttpActionPeer = HttpActionPeer;
var SubmitActionPeer = /** @class */ (function (_super) {
    __extends(SubmitActionPeer, _super);
    function SubmitActionPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    SubmitActionPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var data = addLabelAndInput(card, "Data:", Adaptive.TextInput);
        data.input.isMultiline = true;
        data.input.defaultValue = JSON.stringify(this.action.data);
        data.input.placeholder = "(not set)";
        data.input.onValueChanged = function () {
            _this.action.data = JSON.parse(data.input.value);
            _this.changed(false);
        };
    };
    return SubmitActionPeer;
}(TypedActionPeer));
exports.SubmitActionPeer = SubmitActionPeer;
var OpenUrlActionPeer = /** @class */ (function (_super) {
    __extends(OpenUrlActionPeer, _super);
    function OpenUrlActionPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    OpenUrlActionPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var url = addLabelAndInput(card, "Url:", Adaptive.TextInput);
        url.input.defaultValue = this.action.url;
        url.input.placeholder = "(not set)";
        url.input.onValueChanged = function () {
            _this.action.url = url.input.value;
            _this.changed(false);
        };
    };
    return OpenUrlActionPeer;
}(TypedActionPeer));
exports.OpenUrlActionPeer = OpenUrlActionPeer;
var ShowCardActionPeer = /** @class */ (function (_super) {
    __extends(ShowCardActionPeer, _super);
    function ShowCardActionPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ShowCardActionPeer.prototype.getToolTip = function () {
        return "Double click to open/close";
    };
    return ShowCardActionPeer;
}(TypedActionPeer));
exports.ShowCardActionPeer = ShowCardActionPeer;
var CardElementPeer = /** @class */ (function (_super) {
    __extends(CardElementPeer, _super);
    function CardElementPeer(designerSurface, registration, cardElement) {
        var _this = _super.call(this, designerSurface, registration) || this;
        _this._cardElement = cardElement;
        if (cardElement instanceof Adaptive.CardElementContainer) {
            for (var i = 0; i < cardElement.getItemCount(); i++) {
                _this.insertChild(card_designer_surface_1.CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(_this.designerSurface, _this, cardElement.getItemAt(i)));
            }
        }
        for (var i = 0; i < _this.cardElement.getActionCount(); i++) {
            _this.insertChild(card_designer_surface_1.CardDesignerSurface.actionPeerRegistry.createPeerInstance(_this.designerSurface, _this, cardElement.getActionAt(i)));
        }
        return _this;
    }
    CardElementPeer.prototype.getCardObjectTypeName = function () {
        return this.cardElement.getJsonTypeName();
    };
    CardElementPeer.prototype.insertElementAfter = function (newElement) {
        if (this.cardElement.parent instanceof Adaptive.Container) {
            this.cardElement.parent.insertItemAfter(newElement, this.cardElement);
            var newPeer = card_designer_surface_1.CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(this.designerSurface, this, newElement);
            this.peerAdded(newPeer);
        }
    };
    CardElementPeer.prototype.internalRemove = function () {
        return this.cardElement.remove();
    };
    CardElementPeer.prototype.initializeCardElement = function () {
        // Do nothing in base implementation
    };
    CardElementPeer.prototype.canDrop = function (peer) {
        return this.cardElement instanceof Adaptive.Container && peer instanceof CardElementPeer;
    };
    CardElementPeer.prototype.tryDrop = function (peer, insertionPoint) {
        if (this.cardElement instanceof Adaptive.Container && peer instanceof CardElementPeer) {
            var targetChild = null;
            var insertAfter = void 0;
            for (var i = 0; i < this.getChildCount(); i++) {
                var rect = this.getChildAt(i).getBoundingRect();
                if (rect.isInside(insertionPoint)) {
                    targetChild = this.getChildAt(i);
                    insertAfter = (insertionPoint.y - rect.top) >= (rect.height / 2);
                    break;
                }
            }
            if (targetChild != peer) {
                if (peer.cardElement.parent) {
                    if (!peer.remove(true, false)) {
                        return false;
                    }
                    peer.parent.removeChild(peer);
                }
                if (!targetChild) {
                    var rect = this.getBoundingRect();
                    insertAfter = (insertionPoint.y - rect.top) >= (rect.height / 2);
                    if (this.cardElement.getItemCount() > 0 && insertAfter) {
                        this.cardElement.insertItemAfter(peer.cardElement, this.cardElement.getItemAt(this.cardElement.getItemCount() - 1));
                    }
                    else {
                        this.cardElement.insertItemAfter(peer.cardElement, null);
                    }
                }
                else {
                    if (insertAfter) {
                        this.cardElement.insertItemAfter(peer.cardElement, targetChild.cardElement);
                    }
                    else {
                        this.cardElement.insertItemBefore(peer.cardElement, targetChild.cardElement);
                    }
                }
                this.insertChild(peer, peer.cardElement.index);
                this.changed(false);
                return true;
            }
        }
        return false;
    };
    CardElementPeer.prototype.getBoundingRect = function () {
        var designSurfaceOffset = this.designerSurface.getDesignerSurfaceOffset();
        var cardElementBoundingRect = this.cardElement.renderedElement.getBoundingClientRect();
        if (this.cardElement.hasVisibleSeparator) {
            var separatorBoundingRect = this.cardElement.separatorElement.getBoundingClientRect();
            return new miscellaneous_1.Rect(Math.min(separatorBoundingRect.top, cardElementBoundingRect.top) - designSurfaceOffset.y, Math.max(separatorBoundingRect.right, cardElementBoundingRect.right) - designSurfaceOffset.x, Math.max(separatorBoundingRect.bottom, cardElementBoundingRect.bottom) - designSurfaceOffset.y, Math.min(separatorBoundingRect.left, cardElementBoundingRect.left) - designSurfaceOffset.x);
        }
        else {
            return new miscellaneous_1.Rect(cardElementBoundingRect.top - designSurfaceOffset.y, cardElementBoundingRect.right - designSurfaceOffset.x, cardElementBoundingRect.bottom - designSurfaceOffset.y, cardElementBoundingRect.left - designSurfaceOffset.x);
        }
    };
    CardElementPeer.prototype.getCardObjectBoundingRect = function () {
        var cardElementBoundingRect = this.cardElement.renderedElement.getBoundingClientRect();
        return new miscellaneous_1.Rect(cardElementBoundingRect.top, cardElementBoundingRect.right, cardElementBoundingRect.bottom, cardElementBoundingRect.left);
    };
    CardElementPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        if (includeHeader) {
            var elementType = new Adaptive.TextBlock();
            elementType.text = "**" + this.cardElement.getJsonTypeName() + "**";
            card.addItem(elementType);
        }
        var getExcludedProperties = this.getExcludedProperties();
        if (getExcludedProperties.indexOf("id") < 0) {
            var id_1 = addLabelAndInput(card, "Id:", Adaptive.TextInput);
            id_1.input.defaultValue = this.cardElement.id;
            id_1.input.placeholder = "(not set)";
            id_1.input.onValueChanged = function () {
                _this.cardElement.id = id_1.input.value;
                _this.changed(false);
            };
        }
        if (getExcludedProperties.indexOf("spacing") < 0) {
            var spacing_1 = addLabelAndInput(card, "Spacing:", Adaptive.ChoiceSetInput);
            spacing_1.input.isCompact = true;
            spacing_1.input.choices.push(new Adaptive.Choice("None", Adaptive.Spacing.None.toString()));
            spacing_1.input.choices.push(new Adaptive.Choice("Small", Adaptive.Spacing.Small.toString()));
            spacing_1.input.choices.push(new Adaptive.Choice("Default", Adaptive.Spacing.Default.toString()));
            spacing_1.input.choices.push(new Adaptive.Choice("Medium", Adaptive.Spacing.Medium.toString()));
            spacing_1.input.choices.push(new Adaptive.Choice("Large", Adaptive.Spacing.Large.toString()));
            spacing_1.input.choices.push(new Adaptive.Choice("Extra large", Adaptive.Spacing.ExtraLarge.toString()));
            spacing_1.input.choices.push(new Adaptive.Choice("Default padding", Adaptive.Spacing.Padding.toString()));
            spacing_1.input.defaultValue = this.cardElement.spacing.toString();
            spacing_1.input.onValueChanged = function () {
                _this.cardElement.spacing = parseInt(spacing_1.input.value);
                _this.changed(false);
            };
        }
        if (getExcludedProperties.indexOf("separator") < 0) {
            var separator_1 = addLabelAndInput(card, "Show separator:", Adaptive.ToggleInput);
            separator_1.input.defaultValue = String(this.cardElement.separator);
            separator_1.input.onValueChanged = function () {
                _this.cardElement.separator = separator_1.input.value == "true";
                _this.changed(false);
            };
        }
        if (getExcludedProperties.indexOf("horizontalAlignment") < 0) {
            var horizontalAlignment = addLabelAndInput(card, "Horizontal alignment:", Adaptive.ChoiceSetInput);
            horizontalAlignment.input.isCompact = true;
            horizontalAlignment.input.placeholder = "(not set)";
            horizontalAlignment.input.choices.push(new Adaptive.Choice("Left", Adaptive.HorizontalAlignment.Left.toString()));
            horizontalAlignment.input.choices.push(new Adaptive.Choice("Center", Adaptive.HorizontalAlignment.Center.toString()));
            horizontalAlignment.input.choices.push(new Adaptive.Choice("Right", Adaptive.HorizontalAlignment.Right.toString()));
            if (this.cardElement.horizontalAlignment) {
                horizontalAlignment.input.defaultValue = this.cardElement.horizontalAlignment.toString();
            }
            horizontalAlignment.input.onValueChanged = function () {
                if (horizontalAlignment.input.value) {
                    _this.cardElement.horizontalAlignment = parseInt(horizontalAlignment.input.value);
                }
                _this.changed(false);
            };
        }
        if (getExcludedProperties.indexOf("height") < 0) {
            var height = addLabelAndInput(card, "Height:", Adaptive.ChoiceSetInput);
            height.input.isCompact = true;
            height.input.choices.push(new Adaptive.Choice("Automatic", "auto"));
            height.input.choices.push(new Adaptive.Choice("Stretch", "stretch"));
            height.input.defaultValue = this.cardElement.height;
            height.input.onValueChanged = function () {
                _this.cardElement.height = height.input.value === "auto" ? "auto" : "stretch";
                _this.changed(false);
            };
        }
    };
    Object.defineProperty(CardElementPeer.prototype, "cardElement", {
        get: function () {
            return this._cardElement;
        },
        enumerable: true,
        configurable: true
    });
    return CardElementPeer;
}(DesignerPeer));
exports.CardElementPeer = CardElementPeer;
var TypedCardElementPeer = /** @class */ (function (_super) {
    __extends(TypedCardElementPeer, _super);
    function TypedCardElementPeer(designerSurface, registration, cardElement) {
        return _super.call(this, designerSurface, registration, cardElement) || this;
    }
    Object.defineProperty(TypedCardElementPeer.prototype, "cardElement", {
        get: function () {
            return this._cardElement;
        },
        enumerable: true,
        configurable: true
    });
    return TypedCardElementPeer;
}(CardElementPeer));
exports.TypedCardElementPeer = TypedCardElementPeer;
var AdaptiveCardPeer = /** @class */ (function (_super) {
    __extends(AdaptiveCardPeer, _super);
    function AdaptiveCardPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    AdaptiveCardPeer.prototype.addAction = function (action) {
        this.cardElement.addAction(action);
        this.insertChild(card_designer_surface_1.CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, this, action));
    };
    AdaptiveCardPeer.prototype.internalRemove = function () {
        return true;
    };
    AdaptiveCardPeer.prototype.internalAddCommands = function (commands) {
        var _this = this;
        _super.prototype.internalAddCommands.call(this, commands);
        commands.push(new peer_command_1.PeerCommand({
            name: "Add an action",
            iconClass: "acd-icon-bolt",
            execute: function (command, clickedElement) {
                var popupMenu = new Controls.PopupMenu();
                for (var i = 0; i < Adaptive.AdaptiveCard.actionTypeRegistry.getItemCount(); i++) {
                    var menuItem = new Controls.DropDownItem(i.toString(), Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(i).typeName);
                    menuItem.onClick = function (clickedItem) {
                        var registryItem = Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(Number.parseInt(clickedItem.key));
                        var action = registryItem.createInstance();
                        action.title = registryItem.typeName;
                        _this.addAction(action);
                        popupMenu.closePopup();
                    };
                    popupMenu.items.add(menuItem);
                }
                popupMenu.popup(clickedElement);
            }
        }));
    };
    AdaptiveCardPeer.prototype.getExcludedProperties = function () {
        return ["id", "horizontalAlignment", "separator", "height", "spacing"];
    };
    AdaptiveCardPeer.prototype.isDraggable = function () {
        return false;
    };
    AdaptiveCardPeer.prototype.canBeRemoved = function () {
        return false;
    };
    AdaptiveCardPeer.prototype.internalAddPropertySheetEntries = function (card, updatePropertySheet) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, updatePropertySheet);
        var lang = addLabelAndInput(card, "Language:", Adaptive.TextInput);
        lang.input.defaultValue = this.cardElement.lang;
        lang.input.placeholder = "(not set) ISO 639-1 code";
        lang.input.onValueChanged = function () {
            _this.cardElement.lang = lang.input.value;
            _this.changed(false);
        };
        var fallbackText = addLabelAndInput(card, "Fallback text:", Adaptive.TextInput);
        fallbackText.input.defaultValue = this.cardElement.fallbackText;
        fallbackText.input.placeholder = "(not set)";
        fallbackText.input.isMultiline = true;
        fallbackText.input.onValueChanged = function () {
            _this.cardElement.fallbackText = fallbackText.input.value;
            _this.changed(false);
        };
        var speak = addLabelAndInput(card, "Speak:", Adaptive.TextInput);
        speak.input.defaultValue = this.cardElement.fallbackText;
        speak.input.placeholder = "(not set)";
        speak.input.isMultiline = true;
        speak.input.onValueChanged = function () {
            _this.cardElement.speak = speak.input.value;
            _this.changed(false);
        };
        var backgroundImage = addLabelAndInput(card, "Background image URL:", Adaptive.TextInput);
        backgroundImage.input.placeholder = "(not set)";
        if (this.cardElement.backgroundImage) {
            backgroundImage.input.defaultValue = this.cardElement.backgroundImage.url;
        }
        backgroundImage.input.onValueChanged = function () {
            if (backgroundImage.input.value) {
                _this.cardElement.backgroundImage = new Adaptive.BackgroundImage();
                _this.cardElement.backgroundImage.url = backgroundImage.input.value;
            }
            else {
                _this.cardElement.backgroundImage = null;
            }
            _this.changed(false);
        };
        var actionSelector = createActionSelector(card, this.cardElement.selectAction ? this.cardElement.selectAction.getJsonTypeName() : "none");
        actionSelector.input.onValueChanged = function () {
            if (actionSelector.input.value == "none") {
                _this.cardElement.selectAction = null;
            }
            else {
                _this.cardElement.selectAction = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(actionSelector.input.value);
            }
            _this.changed(true);
        };
        if (this.cardElement.selectAction) {
            var selectActionPeer = card_designer_surface_1.CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
            selectActionPeer.internalAddPropertySheetEntries(card, false);
            selectActionPeer.onChanged = function (sender, updatePropertySheet) { _this.changed(updatePropertySheet); };
        }
    };
    return AdaptiveCardPeer;
}(TypedCardElementPeer));
exports.AdaptiveCardPeer = AdaptiveCardPeer;
var ColumnPeer = /** @class */ (function (_super) {
    __extends(ColumnPeer, _super);
    function ColumnPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ColumnPeer.prototype.isContainer = function () {
        return true;
    };
    ColumnPeer.prototype.getTreeItemText = function () {
        if (this.cardElement.width instanceof Adaptive.SizeAndUnit) {
            switch (this.cardElement.width.unit) {
                case Adaptive.SizeUnit.Weight:
                    return "Weight: " + this.cardElement.width.physicalSize;
                default:
                    return this.cardElement.width.physicalSize + " pixels";
            }
        }
        else {
            switch (this.cardElement.width) {
                case "stretch":
                    return "Stretch";
                case "auto":
                    return "Automatic";
                default:
                    return "";
            }
        }
    };
    ColumnPeer.prototype.isDraggable = function () {
        return false;
    };
    ColumnPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var backgroundImage = addLabelAndInput(card, "Background image URL:", Adaptive.TextInput);
        backgroundImage.input.placeholder = "(not set)";
        if (this.cardElement.backgroundImage) {
            backgroundImage.input.defaultValue = this.cardElement.backgroundImage.url;
        }
        backgroundImage.input.onValueChanged = function () {
            if (backgroundImage.input.value) {
                _this.cardElement.backgroundImage = new Adaptive.BackgroundImage();
                _this.cardElement.backgroundImage.url = backgroundImage.input.value;
            }
            else {
                _this.cardElement.backgroundImage = null;
            }
            _this.changed(false);
        };
        var style = addLabelAndInput(card, "Style:", Adaptive.ChoiceSetInput);
        style.input.isCompact = true;
        style.input.placeholder = "(not set)";
        style.input.choices.push(new Adaptive.Choice("Default", "default"));
        style.input.choices.push(new Adaptive.Choice("Emphasis", "emphasis"));
        style.input.defaultValue = this.cardElement.style.toString();
        style.input.onValueChanged = function () {
            _this.cardElement.style = style.input.value;
            _this.changed(false);
        };
        var width = addLabelAndInput(card, "Width:", Adaptive.ChoiceSetInput);
        width.input.isCompact = true;
        width.input.choices.push(new Adaptive.Choice("Automatic", "auto"));
        width.input.choices.push(new Adaptive.Choice("Stretch", "stretch"));
        width.input.choices.push(new Adaptive.Choice("Weighted", "weighted"));
        width.input.choices.push(new Adaptive.Choice("Pixels", "pixels"));
        if (this.cardElement.width instanceof Adaptive.SizeAndUnit) {
            if (this.cardElement.width.unit == Adaptive.SizeUnit.Pixel) {
                width.input.defaultValue = "pixels";
                var pixelWidth_1 = addLabelAndInput(card, "Width in pixels:", Adaptive.NumberInput);
                pixelWidth_1.input.defaultValue = this.cardElement.width.physicalSize.toString();
                pixelWidth_1.input.placeholder = "(not set)";
                pixelWidth_1.input.onValueChanged = function () {
                    try {
                        _this.cardElement.width = new Adaptive.SizeAndUnit(parseInt(pixelWidth_1.input.value), Adaptive.SizeUnit.Pixel);
                        _this.changed(false);
                    }
                    catch (_a) {
                        // Do nothing. The specified width is invalid
                    }
                };
            }
            else {
                width.input.defaultValue = "weighted";
                var weightedWidth_1 = addLabelAndInput(card, "Weight:", Adaptive.NumberInput);
                weightedWidth_1.input.defaultValue = this.cardElement.width.physicalSize.toString();
                weightedWidth_1.input.placeholder = "(not set)";
                weightedWidth_1.input.onValueChanged = function () {
                    try {
                        _this.cardElement.width = new Adaptive.SizeAndUnit(parseInt(weightedWidth_1.input.value), Adaptive.SizeUnit.Weight);
                        _this.changed(false);
                    }
                    catch (_a) {
                        // Do nothing. The specified width is invalid
                    }
                };
            }
        }
        else {
            width.input.defaultValue = this.cardElement.width.toString();
        }
        width.input.placeholder = "(not set)";
        width.input.onValueChanged = function () {
            switch (width.input.value) {
                case "auto":
                    _this.cardElement.width = "auto";
                    break;
                case "pixels":
                    _this.cardElement.width = new Adaptive.SizeAndUnit(50, Adaptive.SizeUnit.Pixel);
                    break;
                case "weighted":
                    _this.cardElement.width = new Adaptive.SizeAndUnit(50, Adaptive.SizeUnit.Weight);
                    break;
                case "stretch":
                default:
                    _this.cardElement.width = "stretch";
                    break;
            }
            _this.changed(true);
        };
        var verticalContentAlignment = addLabelAndInput(card, "Vertical content alignment:", Adaptive.ChoiceSetInput);
        verticalContentAlignment.input.isCompact = true;
        verticalContentAlignment.input.choices.push(new Adaptive.Choice("Top", Adaptive.VerticalAlignment.Top.toString()));
        verticalContentAlignment.input.choices.push(new Adaptive.Choice("Center", Adaptive.VerticalAlignment.Center.toString()));
        verticalContentAlignment.input.choices.push(new Adaptive.Choice("Bottom", Adaptive.VerticalAlignment.Bottom.toString()));
        verticalContentAlignment.input.defaultValue = this.cardElement.spacing.toString();
        verticalContentAlignment.input.placeholder = "(not set)";
        verticalContentAlignment.input.onValueChanged = function () {
            _this.cardElement.verticalContentAlignment = parseInt(verticalContentAlignment.input.value);
            _this.changed(false);
        };
        var actionSelector = createActionSelector(card, this.cardElement.selectAction ? this.cardElement.selectAction.getJsonTypeName() : "none");
        actionSelector.input.onValueChanged = function () {
            if (actionSelector.input.value == "none") {
                _this.cardElement.selectAction = null;
            }
            else {
                _this.cardElement.selectAction = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(actionSelector.input.value);
            }
            _this.changed(true);
        };
        if (this.cardElement.selectAction) {
            var selectActionPeer = card_designer_surface_1.CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
            selectActionPeer.internalAddPropertySheetEntries(card, false);
            selectActionPeer.onChanged = function (sender, updatePropertySheet) { _this.changed(updatePropertySheet); };
        }
    };
    return ColumnPeer;
}(TypedCardElementPeer));
exports.ColumnPeer = ColumnPeer;
var ColumnSetPeer = /** @class */ (function (_super) {
    __extends(ColumnSetPeer, _super);
    function ColumnSetPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ColumnSetPeer.prototype.isContainer = function () {
        return true;
    };
    ColumnSetPeer.prototype.internalAddCommands = function (commands) {
        var _this = this;
        _super.prototype.internalAddCommands.call(this, commands);
        commands.push(new peer_command_1.PeerCommand({
            name: "Add a column",
            iconClass: "acd-icon-addColumn",
            isPromotable: true,
            execute: function (command, clickedElement) {
                var column = new Adaptive.Column();
                column.width = "stretch";
                _this.cardElement.addColumn(column);
                _this.insertChild(card_designer_surface_1.CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(_this.designerSurface, _this, column));
            }
        }));
    };
    ColumnSetPeer.prototype.getTreeItemText = function () {
        var columnCount = this.cardElement.getCount();
        switch (columnCount) {
            case 0:
                return "No column";
            case 1:
                return "1 column";
            default:
                return columnCount + " columns";
        }
    };
    ColumnSetPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var actionSelector = createActionSelector(card, this.cardElement.selectAction ? this.cardElement.selectAction.getJsonTypeName() : "none");
        actionSelector.input.onValueChanged = function () {
            if (actionSelector.input.value == "none") {
                _this.cardElement.selectAction = null;
            }
            else {
                _this.cardElement.selectAction = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(actionSelector.input.value);
            }
            _this.changed(true);
        };
        if (this.cardElement.selectAction) {
            var selectActionPeer = card_designer_surface_1.CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
            selectActionPeer.internalAddPropertySheetEntries(card, false);
            selectActionPeer.onChanged = function (sender, updatePropertySheet) { _this.changed(updatePropertySheet); };
        }
    };
    ColumnSetPeer.prototype.canDrop = function (peer) {
        return true;
    };
    return ColumnSetPeer;
}(TypedCardElementPeer));
exports.ColumnSetPeer = ColumnSetPeer;
var ContainerPeer = /** @class */ (function (_super) {
    __extends(ContainerPeer, _super);
    function ContainerPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ContainerPeer.prototype.isContainer = function () {
        return true;
    };
    ContainerPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var backgroundImage = addLabelAndInput(card, "Background image URL:", Adaptive.TextInput);
        backgroundImage.input.placeholder = "(not set)";
        if (this.cardElement.backgroundImage) {
            backgroundImage.input.defaultValue = this.cardElement.backgroundImage.url;
        }
        backgroundImage.input.onValueChanged = function () {
            if (backgroundImage.input.value) {
                _this.cardElement.backgroundImage = new Adaptive.BackgroundImage();
                _this.cardElement.backgroundImage.url = backgroundImage.input.value;
            }
            else {
                _this.cardElement.backgroundImage = null;
            }
            _this.changed(false);
        };
        var style = addLabelAndInput(card, "Style:", Adaptive.ChoiceSetInput);
        style.input.isCompact = true;
        style.input.placeholder = "(not set)";
        style.input.choices.push(new Adaptive.Choice("Default", "default"));
        style.input.choices.push(new Adaptive.Choice("Emphasis", "emphasis"));
        style.input.defaultValue = this.cardElement.style.toString();
        style.input.onValueChanged = function () {
            _this.cardElement.style = style.input.value;
            _this.changed(false);
        };
        var actionSelector = createActionSelector(card, this.cardElement.selectAction ? this.cardElement.selectAction.getJsonTypeName() : "none");
        actionSelector.input.onValueChanged = function () {
            if (actionSelector.input.value == "none") {
                _this.cardElement.selectAction = null;
            }
            else {
                _this.cardElement.selectAction = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(actionSelector.input.value);
            }
            _this.changed(true);
        };
        if (this.cardElement.selectAction) {
            var selectActionPeer = card_designer_surface_1.CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
            selectActionPeer.internalAddPropertySheetEntries(card, false);
            selectActionPeer.onChanged = function (sender, updatePropertySheet) { _this.changed(updatePropertySheet); };
        }
    };
    return ContainerPeer;
}(TypedCardElementPeer));
exports.ContainerPeer = ContainerPeer;
var ActionSetPeer = /** @class */ (function (_super) {
    __extends(ActionSetPeer, _super);
    function ActionSetPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ActionSetPeer.prototype.addAction = function (action) {
        this.cardElement.addAction(action);
        this.insertChild(card_designer_surface_1.CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, this, action));
    };
    ActionSetPeer.prototype.internalAddCommands = function (commands) {
        var _this = this;
        _super.prototype.internalAddCommands.call(this, commands);
        commands.push(new peer_command_1.PeerCommand({
            name: "Add an action",
            iconClass: "acd-icon-bolt",
            execute: function (command, clickedElement) {
                var popupMenu = new Controls.PopupMenu();
                for (var i = 0; i < Adaptive.AdaptiveCard.actionTypeRegistry.getItemCount(); i++) {
                    var menuItem = new Controls.DropDownItem(i.toString(), Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(i).typeName);
                    menuItem.onClick = function (clickedItem) {
                        var registryItem = Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(Number.parseInt(clickedItem.key));
                        var action = registryItem.createInstance();
                        action.title = registryItem.typeName;
                        _this.addAction(action);
                        popupMenu.closePopup();
                    };
                    popupMenu.items.add(menuItem);
                }
                popupMenu.popup(command.renderedElement);
            }
        }));
    };
    return ActionSetPeer;
}(TypedCardElementPeer));
exports.ActionSetPeer = ActionSetPeer;
function createActionSelector(card, defaultValue) {
    var actionSelector = addLabelAndInput(card, "Select action:", Adaptive.ChoiceSetInput, true);
    actionSelector.input.isCompact = true;
    actionSelector.input.choices.push(new Adaptive.Choice("(not set)", "none"));
    for (var i = 0; i < Adaptive.AdaptiveCard.actionTypeRegistry.getItemCount(); i++) {
        var choice = new Adaptive.Choice(Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(i).typeName, Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(i).typeName);
        actionSelector.input.choices.push(choice);
    }
    actionSelector.input.defaultValue = defaultValue;
    return actionSelector;
}
var ImageSetPeer = /** @class */ (function (_super) {
    __extends(ImageSetPeer, _super);
    function ImageSetPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ImageSetPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var imageSize = addLabelAndInput(card, "Image Size:", Adaptive.ChoiceSetInput);
        imageSize.input.isCompact = true;
        imageSize.input.choices.push(new Adaptive.Choice("Automatic", Adaptive.Size.Auto.toString()));
        imageSize.input.choices.push(new Adaptive.Choice("Small", Adaptive.Size.Small.toString()));
        imageSize.input.choices.push(new Adaptive.Choice("Medium", Adaptive.Size.Medium.toString()));
        imageSize.input.choices.push(new Adaptive.Choice("Large", Adaptive.Size.Large.toString()));
        imageSize.input.choices.push(new Adaptive.Choice("Stretch", Adaptive.Size.Stretch.toString()));
        imageSize.input.defaultValue = this.cardElement.imageSize.toString();
        imageSize.input.onValueChanged = function () {
            _this.cardElement.imageSize = parseInt(imageSize.input.value);
            _this.changed(false);
        };
    };
    ImageSetPeer.prototype.internalAddCommands = function (commands) {
        var _this = this;
        _super.prototype.internalAddCommands.call(this, commands);
        commands.push(new peer_command_1.PeerCommand({
            name: "Add an image",
            iconClass: "acd-icon-image",
            isPromotable: true,
            execute: function (command, clickedElement) {
                var newImage = new Adaptive.Image();
                _this.cardElement.addImage(newImage);
                _this.insertChild(card_designer_surface_1.CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(_this.designerSurface, _this, newImage));
            }
        }));
    };
    return ImageSetPeer;
}(TypedCardElementPeer));
exports.ImageSetPeer = ImageSetPeer;
var ImagePeer = /** @class */ (function (_super) {
    __extends(ImagePeer, _super);
    function ImagePeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    Object.defineProperty(ImagePeer.prototype, "isParentImageSet", {
        get: function () {
            return this.parent && this.parent instanceof ImageSetPeer;
        },
        enumerable: true,
        configurable: true
    });
    ImagePeer.prototype.isDraggable = function () {
        return !this.isParentImageSet;
    };
    ImagePeer.prototype.getBoundingRect = function () {
        if (this.isParentImageSet) {
            var designSurfaceOffset = this.designerSurface.getDesignerSurfaceOffset();
            var actionBoundingRect = this.cardElement.renderedElement.getBoundingClientRect();
            return new miscellaneous_1.Rect(actionBoundingRect.top - designSurfaceOffset.y, actionBoundingRect.right - designSurfaceOffset.x, actionBoundingRect.bottom - designSurfaceOffset.y, actionBoundingRect.left - designSurfaceOffset.x);
        }
        else {
            return _super.prototype.getBoundingRect.call(this);
        }
    };
    ImagePeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var url = addLabelAndInput(card, "Url:", Adaptive.TextInput);
        url.input.defaultValue = this.cardElement.url;
        url.input.onValueChanged = function () {
            _this.cardElement.url = url.input.value;
            _this.changed(false);
        };
        var altText = addLabelAndInput(card, "Alternate text:", Adaptive.TextInput);
        altText.input.placeholder = "(not set)";
        altText.input.defaultValue = this.cardElement.altText;
        altText.input.onValueChanged = function () {
            _this.cardElement.altText = altText.input.value;
            _this.changed(false);
        };
        if (!this.isParentImageSet) {
            var size = addLabelAndInput(card, "Size:", Adaptive.ChoiceSetInput);
            size.input.isCompact = true;
            size.input.choices.push(new Adaptive.Choice("Automatic", Adaptive.Size.Auto.toString()));
            size.input.choices.push(new Adaptive.Choice("Small", Adaptive.Size.Small.toString()));
            size.input.choices.push(new Adaptive.Choice("Medium", Adaptive.Size.Medium.toString()));
            size.input.choices.push(new Adaptive.Choice("Large", Adaptive.Size.Large.toString()));
            size.input.choices.push(new Adaptive.Choice("Stretch", Adaptive.Size.Stretch.toString()));
            size.input.defaultValue = this.cardElement.size.toString();
            size.input.onValueChanged = function () {
                _this.cardElement.size = parseInt(size.input.value);
                _this.changed(false);
            };
            var width = addLabelAndInput(card, "Width (preview):", Adaptive.TextInput);
            width.input.placeholder = "(not set) Format: <N>px, e.g. 50px";
            if (this.cardElement.pixelWidth) {
                width.input.defaultValue = this.cardElement.pixelWidth.toString();
            }
            width.input.onValueChanged = function () {
                try {
                    var size_1 = Adaptive.SizeAndUnit.parse(width.input.value);
                    if (size_1.unit == Adaptive.SizeUnit.Pixel) {
                        _this.cardElement.pixelWidth = size_1.physicalSize;
                    }
                }
                catch (e) {
                    _this.cardElement.pixelWidth = null;
                }
                _this.changed(false);
            };
            var height = addLabelAndInput(card, "Height  (preview):", Adaptive.TextInput);
            height.input.placeholder = "(not set) Format: <N>px, e.g. 50px";
            if (this.cardElement.pixelHeight) {
                height.input.defaultValue = this.cardElement.pixelHeight.toString();
            }
            height.input.onValueChanged = function () {
                try {
                    var size_2 = Adaptive.SizeAndUnit.parse(height.input.value);
                    if (size_2.unit == Adaptive.SizeUnit.Pixel) {
                        _this.cardElement.pixelHeight = size_2.physicalSize;
                    }
                }
                catch (e) {
                    _this.cardElement.pixelHeight = null;
                }
                _this.changed(false);
            };
            var style = addLabelAndInput(card, "Style:", Adaptive.ChoiceSetInput);
            style.input.isCompact = true;
            style.input.choices.push(new Adaptive.Choice("Default", Adaptive.ImageStyle.Default.toString()));
            style.input.choices.push(new Adaptive.Choice("Person", Adaptive.ImageStyle.Person.toString()));
            style.input.defaultValue = this.cardElement.style.toString();
            style.input.onValueChanged = function () {
                _this.cardElement.style = parseInt(style.input.value);
                _this.changed(false);
            };
            var backgroundColor = addLabelAndInput(card, "Background color:", Adaptive.TextInput);
            backgroundColor.input.placeholder = "(not set) Format: #RRGGBB";
            backgroundColor.input.defaultValue = this.cardElement.backgroundColor;
            backgroundColor.input.onValueChanged = function () {
                _this.cardElement.backgroundColor = backgroundColor.input.value;
                _this.changed(false);
            };
            var actionSelector = createActionSelector(card, this.cardElement.selectAction ? this.cardElement.selectAction.getJsonTypeName() : "none");
            actionSelector.input.onValueChanged = function () {
                if (actionSelector.input.value == "none") {
                    _this.cardElement.selectAction = null;
                }
                else {
                    _this.cardElement.selectAction = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(actionSelector.input.value);
                }
                _this.changed(true);
            };
            if (this.cardElement.selectAction) {
                var selectActionPeer = card_designer_surface_1.CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
                selectActionPeer.internalAddPropertySheetEntries(card, false);
                selectActionPeer.onChanged = function (sender, updatePropertySheet) { _this.changed(updatePropertySheet); };
            }
        }
    };
    return ImagePeer;
}(TypedCardElementPeer));
exports.ImagePeer = ImagePeer;
var MediaPeer = /** @class */ (function (_super) {
    __extends(MediaPeer, _super);
    function MediaPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    MediaPeer.prototype.getTreeItemText = function () {
        if (this.cardElement.selectedMediaType == "audio") {
            return "audio";
        }
        else if (this.cardElement.selectedMediaType == "video") {
            return "video";
        }
        else {
            return _super.prototype.getTreeItemText.call(this);
        }
    };
    MediaPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var altText = addLabelAndInput(card, "Alternate text:", Adaptive.TextInput);
        altText.input.placeholder = "(not set)";
        altText.input.defaultValue = this.cardElement.altText;
        altText.input.onValueChanged = function () {
            _this.cardElement.altText = altText.input.value;
            _this.changed(false);
        };
        var posterUrl = addLabelAndInput(card, "Poster URL:", Adaptive.TextInput);
        posterUrl.input.placeholder = "(not set)";
        posterUrl.input.defaultValue = this.cardElement.poster;
        posterUrl.input.onValueChanged = function () {
            _this.cardElement.poster = posterUrl.input.value;
            _this.changed(false);
        };
        var sourcesEditor = new NameValuePairEditor();
        sourcesEditor.title = "Sources:";
        sourcesEditor.addButtonTitle = "Add a new source";
        sourcesEditor.messageIfEmpty = "No source has been defined.";
        sourcesEditor.nameInputTitle = "URL";
        sourcesEditor.valueInputTitle = "MIME type";
        for (var _i = 0, _a = this.cardElement.sources; _i < _a.length; _i++) {
            var source = _a[_i];
            sourcesEditor.nameValuePairs.push({ "name": source.url, "value": source.mimeType });
        }
        sourcesEditor.onChanged = function (sender, refreshPropertySheet) {
            _this.cardElement.sources = [];
            for (var _i = 0, _a = sender.nameValuePairs; _i < _a.length; _i++) {
                var nameValuePair = _a[_i];
                _this.cardElement.sources.push(new Adaptive.MediaSource(nameValuePair.name, nameValuePair.value));
            }
            _this.changed(refreshPropertySheet);
        };
        card.addItem(sourcesEditor.render());
    };
    return MediaPeer;
}(TypedCardElementPeer));
exports.MediaPeer = MediaPeer;
var FactSetPeer = /** @class */ (function (_super) {
    __extends(FactSetPeer, _super);
    function FactSetPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    FactSetPeer.prototype.getExcludedProperties = function () {
        return ["horizontalAlignment"];
    };
    FactSetPeer.prototype.initializeCardElement = function () {
        _super.prototype.initializeCardElement.call(this);
        this.cardElement.facts.push(new Adaptive.Fact("Fact 1", "Value 1"), new Adaptive.Fact("Fact 2", "Value 2"));
    };
    FactSetPeer.prototype.getTreeItemText = function () {
        if (this.cardElement.facts.length == 0) {
            return "No fact";
        }
        var allNames = this.cardElement.facts.map(function (value, index, array) {
            return value.name;
        });
        return allNames.join(", ");
    };
    FactSetPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var factsEditor = new NameValuePairEditor();
        factsEditor.title = "Facts:";
        factsEditor.addButtonTitle = "Add a new fact";
        factsEditor.messageIfEmpty = "This FactSet is empty.";
        for (var _i = 0, _a = this.cardElement.facts; _i < _a.length; _i++) {
            var fact = _a[_i];
            factsEditor.nameValuePairs.push({ "name": fact.name, "value": fact.value });
        }
        factsEditor.onChanged = function (sender, refreshPropertySheet) {
            _this.cardElement.facts = [];
            for (var _i = 0, _a = sender.nameValuePairs; _i < _a.length; _i++) {
                var nameValuePair = _a[_i];
                _this.cardElement.facts.push(new Adaptive.Fact(nameValuePair.name, nameValuePair.value));
            }
            _this.changed(refreshPropertySheet);
        };
        card.addItem(factsEditor.render());
    };
    return FactSetPeer;
}(TypedCardElementPeer));
exports.FactSetPeer = FactSetPeer;
var InputPeer = /** @class */ (function (_super) {
    __extends(InputPeer, _super);
    function InputPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    InputPeer.prototype.getExcludedProperties = function () {
        return ["horizontalAlignment", "height"];
    };
    InputPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var title = addLabelAndInput(card, "Title:", Adaptive.TextInput);
        title.input.placeholder = "(not set)";
        title.input.defaultValue = this.cardElement.title;
        title.input.onValueChanged = function () {
            _this.cardElement.title = title.input.value;
            _this.changed(false);
        };
        var defaultValue = addLabelAndInput(card, "Default value:", Adaptive.TextInput);
        defaultValue.input.placeholder = "(not set)";
        defaultValue.input.defaultValue = this.cardElement.defaultValue;
        defaultValue.input.onValueChanged = function () {
            _this.cardElement.defaultValue = defaultValue.input.value;
            _this.changed(false);
        };
    };
    InputPeer.prototype.initializeCardElement = function () {
        _super.prototype.initializeCardElement.call(this);
        this.cardElement.title = "New Input.Toggle";
    };
    return InputPeer;
}(TypedCardElementPeer));
exports.InputPeer = InputPeer;
var TextInputPeer = /** @class */ (function (_super) {
    __extends(TextInputPeer, _super);
    function TextInputPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    TextInputPeer.prototype.initializeCardElement = function () {
        _super.prototype.initializeCardElement.call(this);
        this.cardElement.placeholder = "Placeholder text";
    };
    TextInputPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var placeholder = addLabelAndInput(card, "Placeholder:", Adaptive.TextInput);
        placeholder.input.placeholder = "(not set)";
        placeholder.input.defaultValue = this.cardElement.placeholder;
        placeholder.input.onValueChanged = function () {
            _this.cardElement.placeholder = placeholder.input.value;
            _this.changed(false);
        };
        var isMultiline = addLabelAndInput(card, "Multi-line:", Adaptive.ToggleInput);
        isMultiline.input.defaultValue = String(this.cardElement.isMultiline);
        isMultiline.input.onValueChanged = function () {
            _this.cardElement.isMultiline = isMultiline.input.value == "true";
            _this.changed(true);
        };
        if (!this.cardElement.isMultiline) {
            var style_1 = addLabelAndInput(card, "Style:", Adaptive.ChoiceSetInput);
            style_1.input.isCompact = true;
            style_1.input.choices.push(new Adaptive.Choice("Text", Adaptive.InputTextStyle.Text.toString()));
            style_1.input.choices.push(new Adaptive.Choice("Email", Adaptive.InputTextStyle.Email.toString()));
            style_1.input.choices.push(new Adaptive.Choice("Telephone", Adaptive.InputTextStyle.Tel.toString()));
            style_1.input.choices.push(new Adaptive.Choice("Url", Adaptive.InputTextStyle.Url.toString()));
            style_1.input.defaultValue = this.cardElement.style.toString();
            style_1.input.onValueChanged = function () {
                _this.cardElement.style = parseInt(style_1.input.value);
                _this.changed(false);
            };
        }
    };
    return TextInputPeer;
}(InputPeer));
exports.TextInputPeer = TextInputPeer;
var NumberInputPeer = /** @class */ (function (_super) {
    __extends(NumberInputPeer, _super);
    function NumberInputPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    NumberInputPeer.prototype.initializeCardElement = function () {
        _super.prototype.initializeCardElement.call(this);
        this.cardElement.placeholder = "Placeholder text";
    };
    NumberInputPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var placeholder = addLabelAndInput(card, "Placeholder:", Adaptive.TextInput);
        placeholder.input.placeholder = "(not set)";
        placeholder.input.defaultValue = this.cardElement.placeholder;
        placeholder.input.onValueChanged = function () {
            _this.cardElement.placeholder = placeholder.input.value;
            _this.changed(false);
        };
        var min = addLabelAndInput(card, "Minimum value:", Adaptive.NumberInput);
        min.input.placeholder = "(not set)";
        min.input.defaultValue = this.cardElement.min;
        min.input.onValueChanged = function () {
            _this.cardElement.min = min.input.value;
            _this.changed(false);
        };
        var max = addLabelAndInput(card, "Maximum value:", Adaptive.NumberInput);
        max.input.placeholder = "(not set)";
        max.input.defaultValue = this.cardElement.max;
        max.input.onValueChanged = function () {
            _this.cardElement.max = max.input.value;
            _this.changed(false);
        };
    };
    return NumberInputPeer;
}(InputPeer));
exports.NumberInputPeer = NumberInputPeer;
var DateInputPeer = /** @class */ (function (_super) {
    __extends(DateInputPeer, _super);
    function DateInputPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    return DateInputPeer;
}(InputPeer));
exports.DateInputPeer = DateInputPeer;
var TimeInputPeer = /** @class */ (function (_super) {
    __extends(TimeInputPeer, _super);
    function TimeInputPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    return TimeInputPeer;
}(InputPeer));
exports.TimeInputPeer = TimeInputPeer;
var ToggleInputPeer = /** @class */ (function (_super) {
    __extends(ToggleInputPeer, _super);
    function ToggleInputPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ToggleInputPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var valueOn = addLabelAndInput(card, "Value when on:", Adaptive.TextInput);
        valueOn.input.placeholder = "(not set)";
        valueOn.input.defaultValue = this.cardElement.valueOn;
        valueOn.input.onValueChanged = function () {
            _this.cardElement.valueOn = valueOn.input.value;
            _this.changed(false);
        };
        var valueOff = addLabelAndInput(card, "Value when off:", Adaptive.TextInput);
        valueOff.input.placeholder = "(not set)";
        valueOff.input.defaultValue = this.cardElement.valueOff;
        valueOff.input.onValueChanged = function () {
            _this.cardElement.valueOff = valueOff.input.value;
            _this.changed(false);
        };
    };
    return ToggleInputPeer;
}(InputPeer));
exports.ToggleInputPeer = ToggleInputPeer;
var ChoiceSetInputPeer = /** @class */ (function (_super) {
    __extends(ChoiceSetInputPeer, _super);
    function ChoiceSetInputPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ChoiceSetInputPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var placeholder = addLabelAndInput(card, "Placeholder:", Adaptive.TextInput);
        placeholder.input.placeholder = "(not set)";
        placeholder.input.defaultValue = this.cardElement.placeholder;
        placeholder.input.onValueChanged = function () {
            _this.cardElement.placeholder = placeholder.input.value;
            _this.changed(false);
        };
        var isMultiSelect = addLabelAndInput(card, "Allow multi selection:", Adaptive.ToggleInput);
        isMultiSelect.input.defaultValue = String(this.cardElement.isMultiSelect);
        isMultiSelect.input.onValueChanged = function () {
            _this.cardElement.isMultiSelect = isMultiSelect.input.value == "true";
            _this.changed(true);
        };
        if (!this.cardElement.isMultiSelect) {
            var isCompact_1 = addLabelAndInput(card, "Compact style:", Adaptive.ToggleInput);
            isCompact_1.input.defaultValue = String(this.cardElement.isCompact);
            isCompact_1.input.onValueChanged = function () {
                _this.cardElement.isCompact = isCompact_1.input.value == "true";
                _this.changed(false);
            };
        }
        var choicesEditor = new NameValuePairEditor();
        choicesEditor.title = "Choices:";
        choicesEditor.addButtonTitle = "Add a new choice";
        choicesEditor.messageIfEmpty = "This ChoiceSet is empty.";
        choicesEditor.nameInputTitle = "Title";
        for (var _i = 0, _a = this.cardElement.choices; _i < _a.length; _i++) {
            var choice = _a[_i];
            choicesEditor.nameValuePairs.push({ "name": choice.title, "value": choice.value });
        }
        choicesEditor.onChanged = function (sender, refreshPropertySheet) {
            _this.cardElement.choices = [];
            for (var _i = 0, _a = sender.nameValuePairs; _i < _a.length; _i++) {
                var nameValuePair = _a[_i];
                _this.cardElement.choices.push(new Adaptive.Choice(nameValuePair.name, nameValuePair.value));
            }
            _this.changed(refreshPropertySheet);
        };
        card.addItem(choicesEditor.render());
    };
    ChoiceSetInputPeer.prototype.initializeCardElement = function () {
        this.cardElement.placeholder = "Placeholder text";
        this.cardElement.choices.push(new Adaptive.Choice("Choice 1", "Choice 1"), new Adaptive.Choice("Choice 2", "Choice 2"));
    };
    return ChoiceSetInputPeer;
}(InputPeer));
exports.ChoiceSetInputPeer = ChoiceSetInputPeer;
var TextBlockPeerInplaceEditor = /** @class */ (function (_super) {
    __extends(TextBlockPeerInplaceEditor, _super);
    function TextBlockPeerInplaceEditor() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    TextBlockPeerInplaceEditor.prototype.close = function (applyChanges) {
        if (this.onClose) {
            this.onClose(applyChanges);
        }
    };
    TextBlockPeerInplaceEditor.prototype.initialize = function () {
        this._renderedElement.select();
    };
    TextBlockPeerInplaceEditor.prototype.applyChanges = function () {
        this.cardElement.text = this._renderedElement.value;
    };
    TextBlockPeerInplaceEditor.prototype.render = function () {
        var _this = this;
        this._renderedElement = document.createElement("textarea");
        this._renderedElement.className = "acd-textBlock-inplace-editor";
        this._renderedElement.value = this.cardElement.text;
        this._renderedElement.onkeydown = function (e) {
            switch (e.keyCode) {
                case Controls.KEY_ESCAPE:
                    _this.close(false);
                    e.preventDefault();
                    e.cancelBubble = true;
                    break;
                case Controls.KEY_ENTER:
                    _this.close(true);
                    e.preventDefault();
                    e.cancelBubble = true;
                    break;
            }
            return !e.cancelBubble;
        };
        this.cardElement.applyStylesTo(this._renderedElement);
        return this._renderedElement;
    };
    return TextBlockPeerInplaceEditor;
}(CardElementPeerInplaceEditor));
var TextBlockPeer = /** @class */ (function (_super) {
    __extends(TextBlockPeer, _super);
    function TextBlockPeer() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    TextBlockPeer.prototype.createInplaceEditor = function () {
        return new TextBlockPeerInplaceEditor(this.cardElement);
    };
    TextBlockPeer.prototype.getToolTip = function () {
        return "Double click to edit";
    };
    TextBlockPeer.prototype.getTreeItemText = function () {
        return this.cardElement.text;
    };
    TextBlockPeer.prototype.internalAddPropertySheetEntries = function (card, includeHeader) {
        var _this = this;
        _super.prototype.internalAddPropertySheetEntries.call(this, card, includeHeader);
        var text = addLabelAndInput(card, "Text:", Adaptive.TextInput);
        text.input.defaultValue = this.cardElement.text;
        text.input.isMultiline = true;
        text.input.onValueChanged = function () {
            _this.cardElement.text = text.input.value;
            _this.changed(false);
        };
        var wrap = addLabelAndInput(card, "Wrap:", Adaptive.ToggleInput);
        wrap.input.defaultValue = String(this.cardElement.wrap);
        wrap.input.onValueChanged = function () {
            _this.cardElement.wrap = wrap.input.value == "true";
            _this.changed(false);
        };
        var maxLines = addLabelAndInput(card, "Maximum lines:", Adaptive.NumberInput);
        maxLines.input.placeholder = "(not set)";
        maxLines.input.defaultValue = String(this.cardElement.maxLines);
        maxLines.input.onValueChanged = function () {
            try {
                var newMaxLines = parseInt(maxLines.input.value);
                _this.cardElement.maxLines = newMaxLines;
                _this.changed(false);
            }
            catch (ex) {
                // Do nothing
            }
        };
        var size = addLabelAndInput(card, "Size:", Adaptive.ChoiceSetInput);
        size.input.isCompact = true;
        size.input.choices.push(new Adaptive.Choice("Small", Adaptive.TextSize.Small.toString()));
        size.input.choices.push(new Adaptive.Choice("Default", Adaptive.TextSize.Default.toString()));
        size.input.choices.push(new Adaptive.Choice("Medium", Adaptive.TextSize.Medium.toString()));
        size.input.choices.push(new Adaptive.Choice("Large", Adaptive.TextSize.Large.toString()));
        size.input.choices.push(new Adaptive.Choice("Extra large", Adaptive.TextSize.ExtraLarge.toString()));
        size.input.defaultValue = this.cardElement.size.toString();
        size.input.onValueChanged = function () {
            _this.cardElement.size = parseInt(size.input.value);
            _this.changed(false);
        };
        var weight = addLabelAndInput(card, "Weight:", Adaptive.ChoiceSetInput);
        weight.input.isCompact = true;
        weight.input.choices.push(new Adaptive.Choice("Lighter", Adaptive.TextWeight.Lighter.toString()));
        weight.input.choices.push(new Adaptive.Choice("Default", Adaptive.TextWeight.Default.toString()));
        weight.input.choices.push(new Adaptive.Choice("Bolder", Adaptive.TextWeight.Bolder.toString()));
        weight.input.defaultValue = this.cardElement.weight.toString();
        weight.input.onValueChanged = function () {
            _this.cardElement.weight = parseInt(weight.input.value);
            _this.changed(false);
        };
        var color = addLabelAndInput(card, "Color:", Adaptive.ChoiceSetInput);
        color.input.isCompact = true;
        color.input.choices.push(new Adaptive.Choice("Default", Adaptive.TextColor.Default.toString()));
        color.input.choices.push(new Adaptive.Choice("Dark", Adaptive.TextColor.Dark.toString()));
        color.input.choices.push(new Adaptive.Choice("Light", Adaptive.TextColor.Light.toString()));
        color.input.choices.push(new Adaptive.Choice("Accent", Adaptive.TextColor.Accent.toString()));
        color.input.choices.push(new Adaptive.Choice("Good", Adaptive.TextColor.Good.toString()));
        color.input.choices.push(new Adaptive.Choice("Warning", Adaptive.TextColor.Warning.toString()));
        color.input.choices.push(new Adaptive.Choice("Attention", Adaptive.TextColor.Attention.toString()));
        color.input.defaultValue = this.cardElement.color.toString();
        color.input.onValueChanged = function () {
            _this.cardElement.color = parseInt(color.input.value);
            _this.changed(false);
        };
        var isSubtle = addLabelAndInput(card, "Subtle:", Adaptive.ToggleInput);
        isSubtle.input.defaultValue = String(this.cardElement.isSubtle);
        isSubtle.input.title = "";
        isSubtle.input.onValueChanged = function () {
            _this.cardElement.isSubtle = isSubtle.input.value == "true";
            _this.changed(false);
        };
    };
    TextBlockPeer.prototype.initializeCardElement = function () {
        this.cardElement.text = "New TextBlock";
    };
    return TextBlockPeer;
}(TypedCardElementPeer));
exports.TextBlockPeer = TextBlockPeer;
//# sourceMappingURL=designer-peers.js.map