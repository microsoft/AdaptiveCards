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
var DesignerPeers = require("./designer-peers");
var DesignerPeerCategory = /** @class */ (function () {
    function DesignerPeerCategory() {
    }
    DesignerPeerCategory.Unknown = "Unknown";
    DesignerPeerCategory.Containers = "Containers";
    DesignerPeerCategory.Elements = "Elements";
    DesignerPeerCategory.Inputs = "Inputs";
    DesignerPeerCategory.Actions = "Actions";
    return DesignerPeerCategory;
}());
var DesignerPeerRegistry = /** @class */ (function () {
    function DesignerPeerRegistry() {
        this._items = [];
        this.defaultRegistration = new DesignerPeers.DesignerPeerRegistrationBase(DesignerPeerCategory.Unknown, "acd-icon-unknownPeer");
        this.reset();
    }
    DesignerPeerRegistry.prototype.clear = function () {
        this._items = [];
    };
    DesignerPeerRegistry.prototype.findTypeRegistration = function (sourceType) {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].sourceType === sourceType) {
                return this._items[i];
            }
        }
        return null;
    };
    DesignerPeerRegistry.prototype.registerPeer = function (sourceType, peerType, category, iconClass) {
        if (iconClass === void 0) { iconClass = null; }
        var registrationInfo = this.findTypeRegistration(sourceType);
        if (registrationInfo != null) {
            registrationInfo.peerType = peerType;
        }
        else {
            registrationInfo = new DesignerPeers.DesignerPeerRegistration(sourceType, peerType, category, iconClass);
            this._items.push(registrationInfo);
        }
    };
    DesignerPeerRegistry.prototype.unregisterPeer = function (sourceType) {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].sourceType === sourceType) {
                this._items.splice(i, 1);
                return;
            }
        }
    };
    return DesignerPeerRegistry;
}());
exports.DesignerPeerRegistry = DesignerPeerRegistry;
var CardElementPeerRegistry = /** @class */ (function (_super) {
    __extends(CardElementPeerRegistry, _super);
    function CardElementPeerRegistry() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    CardElementPeerRegistry.prototype.reset = function () {
        this.clear();
        this.registerPeer(Adaptive.AdaptiveCard, DesignerPeers.AdaptiveCardPeer, DesignerPeerCategory.Containers, "acd-icon-adaptiveCard");
        this.registerPeer(Adaptive.Container, DesignerPeers.ContainerPeer, DesignerPeerCategory.Containers, "acd-icon-container");
        this.registerPeer(Adaptive.ColumnSet, DesignerPeers.ColumnSetPeer, DesignerPeerCategory.Containers, "acd-icon-columnSet");
        this.registerPeer(Adaptive.Column, DesignerPeers.ColumnPeer, DesignerPeerCategory.Containers, "acd-icon-column");
        this.registerPeer(Adaptive.ImageSet, DesignerPeers.ImageSetPeer, DesignerPeerCategory.Containers, "acd-icon-imageSet");
        this.registerPeer(Adaptive.FactSet, DesignerPeers.FactSetPeer, DesignerPeerCategory.Containers, "acd-icon-factSet");
        this.registerPeer(Adaptive.TextBlock, DesignerPeers.TextBlockPeer, DesignerPeerCategory.Elements, "acd-icon-textBlock");
        this.registerPeer(Adaptive.Image, DesignerPeers.ImagePeer, DesignerPeerCategory.Elements, "acd-icon-image");
        this.registerPeer(Adaptive.Media, DesignerPeers.MediaPeer, DesignerPeerCategory.Elements, "acd-icon-media");
        this.registerPeer(Adaptive.ActionSet, DesignerPeers.ActionSetPeer, DesignerPeerCategory.Elements, "acd-icon-actionSet");
        this.registerPeer(Adaptive.TextInput, DesignerPeers.TextInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputText");
        this.registerPeer(Adaptive.DateInput, DesignerPeers.DateInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputDate");
        this.registerPeer(Adaptive.TimeInput, DesignerPeers.TimeInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputTime");
        this.registerPeer(Adaptive.ToggleInput, DesignerPeers.ToggleInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputToggle");
        this.registerPeer(Adaptive.NumberInput, DesignerPeers.NumberInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputNumber");
        this.registerPeer(Adaptive.ChoiceSetInput, DesignerPeers.ChoiceSetInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputChoiceSet");
    };
    CardElementPeerRegistry.prototype.createPeerInstance = function (designerSurface, parent, cardElement) {
        /*
        var registrationInfo: IDesignerPeerRegistration<CardElementType, CardElementPeerType> = undefined;

        for (var i = 0; i < this._items.length; i++) {
            if (cardElement instanceof this._items[i].sourceType) {
                registrationInfo = this._items[i];

                break;
            }
        }
        */
        var registrationInfo = this.findTypeRegistration(cardElement.constructor);
        var peer = registrationInfo ? new registrationInfo.peerType(designerSurface, registrationInfo, cardElement) : new DesignerPeers.CardElementPeer(designerSurface, this.defaultRegistration, cardElement);
        peer.parent = parent;
        return peer;
    };
    return CardElementPeerRegistry;
}(DesignerPeerRegistry));
exports.CardElementPeerRegistry = CardElementPeerRegistry;
var ActionPeerRegistry = /** @class */ (function (_super) {
    __extends(ActionPeerRegistry, _super);
    function ActionPeerRegistry() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    ActionPeerRegistry.prototype.reset = function () {
        this.clear();
        this.registerPeer(Adaptive.HttpAction, DesignerPeers.HttpActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionHttp");
        this.registerPeer(Adaptive.SubmitAction, DesignerPeers.SubmitActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionSubmit");
        this.registerPeer(Adaptive.OpenUrlAction, DesignerPeers.OpenUrlActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionOpenUrl");
        this.registerPeer(Adaptive.ShowCardAction, DesignerPeers.ShowCardActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionShowCard");
    };
    ActionPeerRegistry.prototype.createPeerInstance = function (designerSurface, parent, action) {
        var registrationInfo = this.findTypeRegistration(action.constructor);
        var peer = registrationInfo ? new registrationInfo.peerType(designerSurface, registrationInfo, action) : new DesignerPeers.ActionPeer(designerSurface, this.defaultRegistration, action);
        peer.parent = parent;
        return peer;
    };
    return ActionPeerRegistry;
}(DesignerPeerRegistry));
exports.ActionPeerRegistry = ActionPeerRegistry;
var DragHandle = /** @class */ (function (_super) {
    __extends(DragHandle, _super);
    function DragHandle() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    DragHandle.prototype.internalRender = function () {
        var element = document.createElement("div");
        element.classList.add("acd-peerButton", "acd-icon-drag");
        element.title = "Drag to move this element";
        element.style.visibility = "hidden";
        element.style.position = "absolute";
        element.style.zIndex = "500";
        return element;
    };
    return DragHandle;
}(draggable_element_1.DraggableElement));
var CardDesignerSurface = /** @class */ (function () {
    function CardDesignerSurface(parentElement) {
        var _this = this;
        this._updateCount = 0;
        this._allPeers = [];
        this._lastParseErrors = [];
        this.parentElement = parentElement;
        var rootElement = document.createElement("div");
        rootElement.style.position = "relative";
        rootElement.style.width = "100%";
        rootElement.style.height = "auto";
        this._cardHost = document.createElement("div");
        rootElement.appendChild(this._cardHost);
        this._designerSurface = document.createElement("div");
        this._designerSurface.classList.add("acd-designersurface");
        this._designerSurface.tabIndex = 0;
        this._designerSurface.style.position = "absolute";
        this._designerSurface.style.left = "0";
        this._designerSurface.style.top = "0";
        this._designerSurface.style.width = "100%";
        this._designerSurface.style.height = "100%";
        this._designerSurface.onkeydown = function (e) {
            if (_this._selectedPeer) {
                switch (e.keyCode) {
                    case Controls.KEY_ESCAPE:
                        _this.setSelectedPeer(_this._selectedPeer.parent);
                        break;
                    case Controls.KEY_DELETE:
                        _this.removeSelected();
                        break;
                }
            }
            return !e.cancelBubble;
        };
        this._designerSurface.onpointermove = function (e) {
            var clientRect = _this._designerSurface.getBoundingClientRect();
            _this.tryDrop({ x: e.x - clientRect.left, y: e.y - clientRect.top }, _this.draggedPeer);
        };
        this._designerSurface.onpointerup = function (e) {
            if (_this.draggedPeer) {
                _this.endDrag();
            }
        };
        rootElement.appendChild(this._designerSurface);
        this.parentElement.innerHTML = "";
        this.parentElement.appendChild(rootElement);
    }
    CardDesignerSurface.prototype.updatePeerCommandsLayout = function () {
        if (this._selectedPeer) {
            var peerRect = this._selectedPeer.getBoundingRect();
            var dragHandleRect = this._dragHandle.renderedElement.getBoundingClientRect();
            var removeButtonRect = this._removeCommandElement.getBoundingClientRect();
            var commandsHostRect = this._peerCommandsHostElement.getBoundingClientRect();
            this._dragHandle.renderedElement.style.left = (peerRect.left - dragHandleRect.width) + "px";
            this._dragHandle.renderedElement.style.top = (peerRect.top - dragHandleRect.height) + "px";
            this._removeCommandElement.style.left = peerRect.right + "px";
            this._removeCommandElement.style.top = (peerRect.top - removeButtonRect.height) + "px";
            this._peerCommandsHostElement.style.left = (peerRect.right - commandsHostRect.width) + "px";
            this._peerCommandsHostElement.style.top = (peerRect.bottom + 2) + "px";
            this._dragHandle.renderedElement.style.visibility = this._selectedPeer.isDraggable() ? "visible" : "hidden";
            this._removeCommandElement.style.visibility = this._selectedPeer.canBeRemoved() ? "visible" : "hidden";
            this._peerCommandsHostElement.style.visibility = this._peerCommandsHostElement.childElementCount > 0 ? "visible" : "hidden";
        }
        else {
            this._dragHandle.renderedElement.style.visibility = "hidden";
            this._removeCommandElement.style.visibility = "hidden";
            this._peerCommandsHostElement.style.visibility = "hidden";
        }
    };
    CardDesignerSurface.prototype.setSelectedPeer = function (value) {
        if (this._selectedPeer != value) {
            if (this._selectedPeer) {
                this._selectedPeer.isSelected = false;
            }
            this._selectedPeer = value;
            this._peerCommandsHostElement.innerHTML = "";
            if (this._selectedPeer) {
                this._selectedPeer.isSelected = true;
                var commands = this._selectedPeer.getCommands();
                for (var _i = 0, commands_1 = commands; _i < commands_1.length; _i++) {
                    var command = commands_1[_i];
                    this._peerCommandsHostElement.appendChild(command.render());
                }
                this._designerSurface.focus();
            }
            this.updatePeerCommandsLayout();
            if (this.onSelectedPeerChanged) {
                this.onSelectedPeerChanged(this._selectedPeer);
            }
        }
    };
    CardDesignerSurface.prototype.peerChanged = function (peer, updatePropertySheet) {
        this._lastParseErrors = [];
        this.renderCard();
        this.updateLayout();
        if (updatePropertySheet && this.onSelectedPeerChanged) {
            this.onSelectedPeerChanged(this._selectedPeer);
        }
    };
    CardDesignerSurface.prototype.peerRemoved = function (peer) {
        this._allPeers.splice(this._allPeers.indexOf(peer), 1);
        if (peer == this._selectedPeer) {
            this.setSelectedPeer(null);
        }
        if (this._updateCount == 0) {
            this.renderCard();
            this.updateLayout();
        }
    };
    CardDesignerSurface.prototype.renderCard = function () {
        this._cardHost.innerHTML = "";
        if (this.card) {
            var validationErrors = this.card.validate();
            var allErrors = validationErrors.concat(this._lastParseErrors);
            if (this.onCardValidated) {
                this.onCardValidated(allErrors);
            }
            this._cardHost.appendChild(this.card.render());
        }
    };
    CardDesignerSurface.prototype.addPeer = function (peer) {
        var _this = this;
        if (this._allPeers.indexOf(peer) < 0) {
            this._allPeers.push(peer);
            peer.render();
            peer.onSelectedChanged = function (peer) {
                if (peer.isSelected) {
                    _this.setSelectedPeer(peer);
                }
                else {
                    if (_this._selectedPeer == peer) {
                        _this.setSelectedPeer(null);
                    }
                }
            };
            peer.onChanged = function (sender, updatePropertySheet) { _this.peerChanged(sender, updatePropertySheet); };
            peer.onPeerRemoved = function (sender) { _this.peerRemoved(sender); };
            peer.onPeerAdded = function (sender, newPeer) {
                _this.addPeer(newPeer);
                _this.updateLayout();
            };
            peer.onStartDrag = function (sender) { _this.startDrag(sender); };
            peer.onEndDrag = function (sender) { _this.endDrag(); };
            peer.addElementsToDesignerSurface(this._designerSurface);
            for (var i = 0; i < peer.getChildCount(); i++) {
                this.addPeer(peer.getChildAt(i));
            }
        }
    };
    CardDesignerSurface.prototype.internalFindDropTarget = function (pointerPosition, currentPeer, forPeer) {
        if (currentPeer == forPeer) {
            return null;
        }
        var result = null;
        var lookDeeper = currentPeer instanceof DesignerPeers.ActionPeer;
        if (!lookDeeper) {
            var boundingRect = currentPeer.getBoundingRect();
            lookDeeper = boundingRect.isInside(pointerPosition);
        }
        if (lookDeeper) {
            var canDrop = currentPeer.canDrop(forPeer);
            if (canDrop) {
                result = currentPeer;
            }
            for (var i = 0; i < currentPeer.getChildCount(); i++) {
                var deeperResult = this.internalFindDropTarget(pointerPosition, currentPeer.getChildAt(i), forPeer);
                if (deeperResult) {
                    result = deeperResult;
                    break;
                }
            }
        }
        return result;
    };
    CardDesignerSurface.prototype.findCardElementPeer = function (cardElement) {
        for (var i = 0; i < this._allPeers.length; i++) {
            var peer = this._allPeers[i];
            if (peer instanceof DesignerPeers.CardElementPeer && peer.cardElement == cardElement) {
                return peer;
            }
        }
        return null;
    };
    CardDesignerSurface.prototype.findActionPeer = function (action) {
        for (var i = 0; i < this._allPeers.length; i++) {
            var peer = this._allPeers[i];
            if (peer instanceof DesignerPeers.ActionPeer && peer.action == action) {
                return peer;
            }
        }
        return null;
    };
    CardDesignerSurface.prototype.inlineCardExpanded = function (action, isExpanded) {
        var peer = this.findCardElementPeer(action.card);
        if (isExpanded) {
            if (!peer) {
                var registration = CardDesignerSurface.cardElementPeerRegistry.findTypeRegistration(Adaptive.AdaptiveCard);
                peer = new registration.peerType(this, registration, action.card);
                var parentPeer = this.findActionPeer(action);
                if (parentPeer) {
                    parentPeer.insertChild(peer);
                }
                else {
                    this._rootPeer.insertChild(peer);
                }
            }
            else {
                peer.addElementsToDesignerSurface(this._designerSurface, true);
            }
        }
        else {
            if (peer) {
                peer.removeElementsFromDesignerSurface(true);
            }
        }
        this.updateLayout();
    };
    Object.defineProperty(CardDesignerSurface.prototype, "draggedPeer", {
        get: function () {
            return this._draggedPeer;
        },
        set: function (value) {
            if (this._draggedPeer != value) {
                if (this._draggedPeer) {
                    this._draggedPeer.dragging = false;
                }
                this._draggedPeer = value;
                if (this._draggedPeer) {
                    this._draggedPeer.dragging = true;
                }
            }
        },
        enumerable: true,
        configurable: true
    });
    CardDesignerSurface.prototype.getDesignerSurfaceOffset = function () {
        var clientRect = this._designerSurface.getBoundingClientRect();
        return { x: clientRect.left, y: clientRect.top };
    };
    CardDesignerSurface.prototype.findDropTarget = function (pointerPosition, peer) {
        return this.internalFindDropTarget(pointerPosition, this._rootPeer, peer);
    };
    CardDesignerSurface.prototype.beginUpdate = function () {
        this._updateCount++;
    };
    CardDesignerSurface.prototype.endUpdate = function (renderCard) {
        if (this._updateCount > 0) {
            this._updateCount--;
            if (this._updateCount == 0) {
                if (renderCard) {
                    this.renderCard();
                }
                this.updateLayout();
            }
        }
    };
    CardDesignerSurface.prototype.render = function () {
        var _this = this;
        this._designerSurface.innerHTML = "";
        this._allPeers = [];
        this.setSelectedPeer(null);
        this.renderCard();
        if (this.card) {
            this._rootPeer = CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(this, null, this.card);
            this.addPeer(this._rootPeer);
        }
        this._removeCommandElement = document.createElement("div");
        this._removeCommandElement.classList.add("acd-peerButton", "acd-icon-remove");
        this._removeCommandElement.title = "Remove";
        this._removeCommandElement.style.visibility = "hidden";
        this._removeCommandElement.style.position = "absolute";
        this._removeCommandElement.style.zIndex = "500";
        this._removeCommandElement.onclick = function (e) {
            _this.removeSelected();
        };
        this._dragHandle = new DragHandle();
        this._dragHandle.onStartDrag = function (sender) {
            _this._dragHandle.endDrag();
            _this.startDrag(_this._selectedPeer);
        };
        this._dragHandle.render();
        this._peerCommandsHostElement = document.createElement("div");
        this._peerCommandsHostElement.style.visibility = "hidden";
        this._peerCommandsHostElement.style.position = "absolute";
        this._peerCommandsHostElement.style.display = "flex";
        this._peerCommandsHostElement.style.zIndex = "500";
        this._designerSurface.appendChild(this._dragHandle.renderedElement);
        this._designerSurface.appendChild(this._removeCommandElement);
        this._designerSurface.appendChild(this._peerCommandsHostElement);
        this.updateLayout();
    };
    CardDesignerSurface.prototype.setCardPayloadAsObject = function (payload) {
        this._lastParseErrors = [];
        this.card.parse(payload, this._lastParseErrors);
        this.render();
    };
    CardDesignerSurface.prototype.setCardPayloadAsString = function (payload) {
        this.setCardPayloadAsObject(JSON.parse(payload));
    };
    CardDesignerSurface.prototype.updateLayout = function (isFullRefresh) {
        if (isFullRefresh === void 0) { isFullRefresh = true; }
        for (var i = 0; i < this._allPeers.length; i++) {
            this._allPeers[i].updateLayout();
        }
        this.updatePeerCommandsLayout();
        if (this.onLayoutUpdated) {
            this.onLayoutUpdated(isFullRefresh);
        }
    };
    CardDesignerSurface.prototype.removeSelected = function () {
        if (this.selectedPeer) {
            this.beginUpdate();
            try {
                var parent_1 = this.selectedPeer.parent;
                if (this.selectedPeer.remove(false, true)) {
                    this.setSelectedPeer(parent_1);
                }
            }
            finally {
                this.endUpdate(true);
            }
        }
    };
    CardDesignerSurface.prototype.startDrag = function (peer) {
        if (!this.draggedPeer) {
            this._designerSurface.classList.add("dragging");
            this.draggedPeer = peer;
            this.setSelectedPeer(this.draggedPeer);
        }
    };
    CardDesignerSurface.prototype.endDrag = function () {
        if (this.draggedPeer) {
            // Ensure that the dragged peer's elements are at the top in Z order
            this.draggedPeer.removeElementsFromDesignerSurface(true);
            this.draggedPeer.addElementsToDesignerSurface(this._designerSurface, true);
            this._dropTarget.renderedElement.classList.remove("dragover");
            this.draggedPeer = null;
            this._designerSurface.classList.remove("dragging");
        }
    };
    CardDesignerSurface.prototype.tryDrop = function (pointerPosition, peer) {
        var result = false;
        if (peer) {
            if (this._dropTarget) {
                this._dropTarget.renderedElement.classList.remove("dragover");
            }
            var newDropTarget = this.findDropTarget(pointerPosition, peer);
            if (newDropTarget) {
                this._dropTarget = newDropTarget;
                this._dropTarget.renderedElement.classList.add("dragover");
                result = this._dropTarget.tryDrop(peer, pointerPosition);
            }
        }
        return result;
    };
    CardDesignerSurface.prototype.isPointerOver = function (x, y) {
        var clientRect = this._designerSurface.getBoundingClientRect();
        return (x >= clientRect.left) && (x <= clientRect.right) && (y >= clientRect.top) && (y <= clientRect.bottom);
    };
    CardDesignerSurface.prototype.pageToClientCoordinates = function (x, y) {
        var clientRect = this._designerSurface.getBoundingClientRect();
        return {
            x: x - clientRect.left,
            y: y - clientRect.top
        };
    };
    Object.defineProperty(CardDesignerSurface.prototype, "rootPeer", {
        get: function () {
            return this._rootPeer;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardDesignerSurface.prototype, "selectedPeer", {
        get: function () {
            return this._selectedPeer;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CardDesignerSurface.prototype, "card", {
        get: function () {
            return this._card;
        },
        set: function (value) {
            var _this = this;
            if (value != this._card) {
                if (this._card) {
                    this._card.onInlineCardExpanded = null;
                }
                this._card = value;
                if (this._card) {
                    this._card.onInlineCardExpanded = function (action, isExpanded) { _this.inlineCardExpanded(action, isExpanded); };
                }
                this.render();
            }
        },
        enumerable: true,
        configurable: true
    });
    CardDesignerSurface.cardElementPeerRegistry = new CardElementPeerRegistry();
    CardDesignerSurface.actionPeerRegistry = new ActionPeerRegistry();
    return CardDesignerSurface;
}());
exports.CardDesignerSurface = CardDesignerSurface;
//# sourceMappingURL=card-designer-surface.js.map