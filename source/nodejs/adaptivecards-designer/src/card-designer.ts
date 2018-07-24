import * as Adaptive from "adaptivecards";
import * as Controls from "adaptivecards-controls";
import { SizeAndUnit, HorizontalAlignment, PaddingDefinition } from "adaptivecards";
import TreeItem from "./components/treeitem";
import * as Outlook from "./containers/outlook-container";

const DRAG_THRESHOLD = 10;

interface ILabelAndInput<TInput extends Adaptive.Input> {
    label: Adaptive.TextBlock;
    input: TInput;
}

interface INameValuePair {
    name: string;
    value: string;
}

class NameValuePairEditor {
    private changed(refreshPropertySheet: boolean = false) {
        if (this.onChanged) {
            this.onChanged(this, refreshPropertySheet);
        }
    }

    nameValuePairs: Array<INameValuePair> = [];

    onChanged: (sender: NameValuePairEditor, refreshPropertySheet: boolean) => void;

    title: string = "Name/value pairs";
    messageIfEmpty = "This collection is empty.";
    addButtonTitle: string = "Add a new pair";

    render(): Adaptive.Container {
        let result = new Adaptive.Container();

        let titleTextBlock = new Adaptive.TextBlock();
        titleTextBlock.text = "**" + this.title + "**";

        result.addItem(titleTextBlock);

        if (this.nameValuePairs.length == 0) {
            let messageTextBlock = new Adaptive.TextBlock();
            messageTextBlock.spacing = Adaptive.Spacing.Small;
            messageTextBlock.text = this.messageIfEmpty;

            result.addItem(messageTextBlock);
        }
        else {
            for (let i = 0; i < this.nameValuePairs.length; i++) {
                let textInput = new Adaptive.TextInput();
                textInput.placeholder = "Name";
                textInput.defaultValue = this.nameValuePairs[i].name;
                textInput.onValueChanged = (sender) => {
                    this.nameValuePairs[i].name = sender.value;

                    this.changed();
                };

                let nameColumn = new Adaptive.Column("stretch");
                nameColumn.addItem(textInput);

                textInput = new Adaptive.TextInput();
                textInput.placeholder = "Value";
                textInput.defaultValue = this.nameValuePairs[i].value;
                textInput.onValueChanged = (sender) => {
                    this.nameValuePairs[i].value = sender.value;

                    this.changed();
                };

                let valueColumn = new Adaptive.Column("stretch");
                valueColumn.spacing = Adaptive.Spacing.Small;
                valueColumn.addItem(textInput);

                let removeAction = new Adaptive.SubmitAction();
                removeAction.title = "X";
                removeAction.onExecute = (sender) => {
                    this.nameValuePairs.splice(i, 1);

                    this.changed(true);
                }

                let actionSet = new Adaptive.ActionSet();
                actionSet.addAction(removeAction);

                let removeColumn = new Adaptive.Column("auto");
                removeColumn.spacing = Adaptive.Spacing.Small;
                removeColumn.addItem(actionSet);

                let columnSet = new Adaptive.ColumnSet();
                columnSet.spacing = Adaptive.Spacing.Small;
                columnSet.addColumn(nameColumn);
                columnSet.addColumn(valueColumn);
                columnSet.addColumn(removeColumn);

                result.addItem(columnSet);
            }
        }

        let addAction = new Adaptive.SubmitAction();
        addAction.title = this.addButtonTitle;
        addAction.onExecute = (sender) => {
            this.nameValuePairs.push({ "name": "", "value": "" });

            this.changed(true);
        }

        let actionSet = new Adaptive.ActionSet();
        actionSet.spacing = Adaptive.Spacing.Small;
        actionSet.addAction(addAction);

        result.addItem(actionSet);

        return result;
    }
}

function addLabelAndInput<TInput extends Adaptive.Input>(
    container: Adaptive.Container,
    label: string,
    inputType: { new(): TInput },
    separator: boolean = false): ILabelAndInput<TInput> {

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

    var result = { label: new Adaptive.TextBlock(), input: new inputType() };
    result.label.horizontalAlignment = HorizontalAlignment.Right;
    result.label.text = label;
    result.label.wrap = true;

    leftColumn.addItem(result.label);
    rightColumn.addItem(result.input);

    container.addItem(columnSet);

    return result;
}

export interface IPoint {
    x: number;
    y: number;
}

class Rect {
    top: number;
    right: number;
    bottom: number;
    left: number;

    constructor(top: number = 0, right: number = 0, bottom: number = 0, left: number = 0) {
        this.top = top;
        this.right = right;
        this.bottom = bottom;
        this.left = left;
    }

    union(otherRect: Rect) {
        this.top = Math.min(this.top, otherRect.top);
        this.left = Math.min(this.left, otherRect.left);
        this.bottom = Math.max(this.bottom, otherRect.bottom);
        this.right = Math.max(this.right, otherRect.right);
    }

    isInside(point: IPoint): boolean {
        return point.x >= this.left && point.x <= this.right && point.y >= this.top && point.y <= this.bottom;
    }

    get width(): number {
        return this.right - this.left;
    }

    get height(): number {
        return this.bottom - this.top;
    }
}

export abstract class DraggableElement {
    private _renderedElement: HTMLElement;
    private _isPointerOver: boolean;
    private _isPointerDown: boolean;
    private _lastClickedPoint: IPoint;
    private _dragging: boolean;

    private releasePointerCapture(pointerId: number) {
        this.renderedElement.releasePointerCapture(pointerId);

        this._isPointerDown = false;
    }

    protected get isPointerOver(): boolean {
        return this._isPointerOver;
    }

    protected set isPointerOver(value: boolean) {
        if (value != this._isPointerOver) {
            this._isPointerOver = value;

            this.updateLayout();
        }
    }

    protected startDrag() {
        if (this.isDraggable() && !this.dragging) {
            this.dragging = true;

            if (this.onStartDrag) {
                this.onStartDrag(this);
            }
        }
    }

    protected pointerDown(e: PointerEvent) {
        if (!this._isPointerDown) {
            this._isPointerDown = true;
            this._lastClickedPoint = { x: e.offsetX, y: e.offsetY };

            this.renderedElement.setPointerCapture(e.pointerId);
        }
    }

    protected pointerUp(e: PointerEvent) {
        if (this._isPointerDown) {
            this.releasePointerCapture(e.pointerId);

            this.endDrag();
        }
    }

    protected pointerMove(e: PointerEvent) {
        if (this._isPointerDown) {
            if (Math.abs(e.offsetX - this._lastClickedPoint.x) >= DRAG_THRESHOLD || Math.abs(e.offsetY - this._lastClickedPoint.y) >= DRAG_THRESHOLD) {
                this.releasePointerCapture(e.pointerId);

                this.startDrag();
            }
        }
    }

    protected doubleClick(e: MouseEvent) {
        if (this.onDoubleClick) {
            this.onDoubleClick(this);
        }
    }

    protected internalUpdateCssStyles() {
        // Do nothing in base implementation
    }

    protected internalUpdateLayout() {
        // Do nothing in base implementation
    }

    protected abstract internalRender(): HTMLElement;

    onStartDrag: (sender: DraggableElement) => void;
    onEndDrag: (sender: DraggableElement) => void;
    onDoubleClick: (sender: DraggableElement) => void;

    isDraggable(): boolean {
        return true;
    }

    endDrag() {
        if (this.dragging) {
            this.dragging = false;

            if (this.onEndDrag) {
                this.onEndDrag(this);
            }
        }
    }

    updateLayout() {
        this.internalUpdateCssStyles();
        this.internalUpdateLayout();
    }

    render() {
        this._renderedElement = this.internalRender();

        this._renderedElement.onmousedown = (e: MouseEvent) => { e.preventDefault(); };
        this._renderedElement.ondblclick = (e: MouseEvent) => { this.doubleClick(e); };

        this._renderedElement.onpointerenter = () => { this.isPointerOver = true; };
        this._renderedElement.onpointerleave = () => { this.isPointerOver = false; };
        this._renderedElement.onpointerdown = (e: PointerEvent) => { this.pointerDown(e); };
        this._renderedElement.onpointerup = (e: PointerEvent) => { this.pointerUp(e); };
        this._renderedElement.onpointermove = (e: PointerEvent) => { this.pointerMove(e); };
    }

    get renderedElement(): HTMLElement {
        return this._renderedElement;
    }

    get dragging(): boolean {
        return this._dragging;
    }

    set dragging(value: boolean) {
        this._dragging = value;

        this.internalUpdateCssStyles();
    }
}

class PeerCommand {
    private _renderedElement: HTMLElement;

    protected internalRender(): HTMLElement {
        var buttonElement = document.createElement("button");
        buttonElement.type = "button";
        buttonElement.title = this.name;
        buttonElement.classList.add("acd-peerButton");
        buttonElement.classList.add(this.iconClass);
        buttonElement.style.display = "flex";
        buttonElement.style.flex = "0 0 auto";
        buttonElement.style.alignItems = "center";
        buttonElement.onclick = (e: MouseEvent) => {
            if (this.execute) {
                this.execute(this, buttonElement);
            }
        }
        buttonElement.onpointerdown = (e: PointerEvent) => { e.cancelBubble = true; };

        return buttonElement;
    }

    name: string;
    iconClass: string;
    isPromotable: boolean = false;
    execute: (command: PeerCommand, clickedElement: HTMLElement) => void;

    constructor(init?: Partial<PeerCommand>) {
        Object.assign(this, init);
    }

    render(): HTMLElement {
        this._renderedElement = this.internalRender();

        return this._renderedElement;
    }

    get renderedElement(): HTMLElement {
        return this._renderedElement;
    }
}

abstract class DesignerPeerInplaceEditor {
    onClose: (applyChanges: boolean) => void;

    abstract initialize();
    abstract applyChanges();
    abstract render(): HTMLElement;
}

abstract class CardElementPeerInplaceEditor<TCardElement extends Adaptive.CardElement> extends DesignerPeerInplaceEditor {
    readonly cardElement: TCardElement;

    constructor(cardElement: TCardElement) {
        super();

        this.cardElement = cardElement;
    }
}

export abstract class DesignerPeer extends DraggableElement {
    private _children: Array<DesignerPeer> = [];
    private _isSelected: boolean = false;
    private _inplaceEditorOverlay: HTMLElement;
    private _inplaceEditor: DesignerPeerInplaceEditor = null;

    private closeInplaceEditor(applyChanges: boolean) {
        if (this._inplaceEditor) {
            if (applyChanges) {
                this._inplaceEditor.applyChanges();

                this.changed(true);
            }

            this._inplaceEditor = null;

            this._inplaceEditorOverlay.remove();
        }
    }

    private tryOpenInplaceEditor(): boolean {
        this._inplaceEditor = this.createInplaceEditor();

        if (this._inplaceEditor) {
            this._inplaceEditor.onClose = (applyChanges: boolean) => {
                this.closeInplaceEditor(applyChanges);
            }

            this._inplaceEditorOverlay = document.createElement("div");
            this._inplaceEditorOverlay.tabIndex = 0;
            this._inplaceEditorOverlay.style.zIndex = "600";
            this._inplaceEditorOverlay.style.backgroundColor = "transparent";
            this._inplaceEditorOverlay.style.position = "absolute";
            this._inplaceEditorOverlay.style.left = "0";
            this._inplaceEditorOverlay.style.top = "0";
            this._inplaceEditorOverlay.style.width = document.documentElement.scrollWidth + "px";
            this._inplaceEditorOverlay.style.height = document.documentElement.scrollHeight + "px";
            this._inplaceEditorOverlay.onfocus = (e) => { this.closeInplaceEditor(true); };

            let boundingRect = this.getCardObjectBoundingRect();

            let inplaceEditorHost = document.createElement("div");
            inplaceEditorHost.className = "acd-inplace-editor-host";
            inplaceEditorHost.style.left = Math.floor(boundingRect.left + pageXOffset) + "px";
            inplaceEditorHost.style.top = Math.floor(boundingRect.top + pageYOffset) + "px";
            inplaceEditorHost.style.width = Math.ceil(boundingRect.width) + "px";
            inplaceEditorHost.style.height = Math.ceil(boundingRect.height) + "px";

            let renderedInplaceEditor = this._inplaceEditor.render();
            renderedInplaceEditor.classList.add("acd-inplace-editor");
            renderedInplaceEditor.tabIndex = 0;
            renderedInplaceEditor.onblur = (e) => { this.closeInplaceEditor(true); };

            inplaceEditorHost.appendChild(renderedInplaceEditor);

            this._inplaceEditorOverlay.appendChild(inplaceEditorHost);

            document.body.appendChild(this._inplaceEditorOverlay);

            this._inplaceEditor.initialize();

            return true;
        }

        return false;
    }

    protected doubleClick(e: MouseEvent) {
        super.doubleClick(e);

        this.tryOpenInplaceEditor();
    }

    protected isContainer(): boolean {
        return false;
    }

    protected getToolTip(): string {
        return null;
    }

    protected pointerDown(e: PointerEvent) {
        super.pointerDown(e);

        this.isSelected = true;
    }

    protected internalAddCommands(commands: Array<PeerCommand>) {
        // Do nothing in base implementation
    }

    protected internalRender(): HTMLElement {
        let element = document.createElement("div");
        element.classList.add("acd-peer");

        let toolTip = this.getToolTip();

        if (toolTip) {
            element.title = toolTip;
        }

        if (this.isContainer()) {
            element.classList.add("container");
        }

        element.style.position = "absolute";

        return element;
    }

    protected internalUpdateCssStyles() {
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
    }

    protected peerAdded(newPeer: DesignerPeer) {
        this.changed(false);

        if (this.onPeerAdded) {
            this.onPeerAdded(this, newPeer);
        }
    }

    protected changed(updatePropertySheet: boolean) {
        if (this.onChanged) {
            this.onChanged(this, updatePropertySheet);
        }
    }

    protected peerRemoved(peer: DesignerPeer) {
        if (this.onPeerRemoved) {
            this.onPeerRemoved(peer);
        }
    }

    protected internalUpdateLayout() {
        if (this.renderedElement) {
            let clientRect = this.getBoundingRect();

            this.renderedElement.style.width = clientRect.width + "px";
            this.renderedElement.style.height = clientRect.height + "px";
            this.renderedElement.style.left = clientRect.left + "px";
            this.renderedElement.style.top = clientRect.top + "px";
        }
    }

    protected createInplaceEditor(): DesignerPeerInplaceEditor {
        return null;
    }

    protected abstract internalRemove(): boolean;
    protected abstract internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean);

    readonly registration: DesignerPeerRegistrationBase;
    readonly designer: CardDesigner;
    readonly treeItem: TreeItem;

    parent: DesignerPeer;

    onSelectedChanged: (sender: DesignerPeer) => void;
    onChanged: (sender: DesignerPeer, updatePropertySheet: boolean) => void;
    onPeerRemoved: (sender: DesignerPeer) => void;
    onPeerAdded: (sender: DesignerPeer, newPeer: DesignerPeer) => void;

    abstract getCardObjectTypeName(): string;

    constructor(designer: CardDesigner, registration: DesignerPeerRegistrationBase) {
        super();

        if (!registration) {
            alert((<any>this).constructor.name);
        }

        this.registration = registration;
        this.designer = designer;
        this.treeItem = new TreeItem(this);
    }

    abstract getBoundingRect(): Rect;
    abstract getCardObjectBoundingRect(): Rect;

    getTreeItemText(): string {
        return null;
    }

    canDrop(peer: DesignerPeer): boolean {
        return false;
    }

    canBeRemoved(): boolean {
        return true;
    }

    tryDrop(peer: DesignerPeer, insertionPoint: IPoint): boolean {
        return false;
    }

    insertChild(peer: DesignerPeer, index: number = -1) {
        if (index == -1) {
            this._children.push(peer);
        }
        else {
            this._children.splice(index, 0, peer);
        }

        peer.parent = this;

        this.peerAdded(peer);
    }

    removeChild(peer: DesignerPeer) {
        var index = this._children.indexOf(peer);

        if (index >= 0) {
            peer.parent = null;
            this._children.splice(index, 1);
        }
    }

    getChildCount(): number {
        return this._children.length;
    }

    getChildAt(index: number): DesignerPeer {
        return this._children[index];
    }

    getCommands(promoteParentCommands: boolean = false): Array<PeerCommand> {
        let result: Array<PeerCommand> = [];

        this.internalAddCommands(result);

        if (promoteParentCommands && this.parent) {
            let parentCommands = this.parent.getCommands();

            for (let command of parentCommands) {
                if (command.isPromotable) {
                    result.push(command);
                }
            }
        }

        return result;
    }

    remove(onlyFromCard: boolean, removeChildren: boolean): boolean {
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
    }

    addElementsToDesignerSurface(designerSurface: HTMLElement, processChildren: boolean = false) {
        designerSurface.appendChild(this.renderedElement);

        if (processChildren) {
            for (var i = 0; i < this.getChildCount(); i++) {
                this.getChildAt(i).addElementsToDesignerSurface(designerSurface, processChildren);
            }
        }
    }

    removeElementsFromDesignerSurface(processChildren: boolean = false) {
        this.renderedElement.remove();

        if (processChildren) {
            for (var i = 0; i < this.getChildCount(); i++) {
                this.getChildAt(i).removeElementsFromDesignerSurface(processChildren);
            }
        }
    }

    buildPropertySheetCard(): Adaptive.AdaptiveCard {
        let result = new Adaptive.AdaptiveCard();
        result.padding = new Adaptive.PaddingDefinition(
            Adaptive.Spacing.Small,
            Adaptive.Spacing.Small,
            Adaptive.Spacing.Small,
            Adaptive.Spacing.Small);

        this.internalAddPropertySheetEntries(result, true);

        let actionSet = new Adaptive.ActionSet();
        let commands = this.getCommands(true);

        for (let command of commands) {
            let action = new Adaptive.SubmitAction();
            action.title = command.name;
            action.onExecute = (sender: Adaptive.Action) => {
                command.execute(command, action.renderedElement);
            }

            actionSet.addAction(action);
        }

        result.addItem(actionSet);

        return result;
    }

    get isSelected(): boolean {
        return this._isSelected;
    }

    set isSelected(value: boolean) {
        if (value != this._isSelected) {
            this._isSelected = value;

            this.updateLayout();
            this.treeItem.updateLayout();

            if (this.onSelectedChanged) {
                this.onSelectedChanged(this);
            }
        }
    }
}

export class ActionPeer extends DesignerPeer {
    protected _action: Adaptive.Action;

    getCardObjectTypeName(): string {
        return this.action.getJsonTypeName();
    }

    protected doubleClick(e: MouseEvent) {
        super.doubleClick(e);

        this.action.renderedElement.click();
    }

    protected internalRemove(): boolean {
        return this.action.remove();
    }

    constructor(designer: CardDesigner, registration: DesignerPeerRegistrationBase, action: Adaptive.Action) {
        super(designer, registration);

        this._action = action;
    }

    getTreeItemText(): string {
        if (this.action.title && this.action.title != "") {
            return this.action.title;
        }
        else {
            return super.getTreeItemText();
        }
    }

    isDraggable(): boolean {
        return false;
    }

    getBoundingRect(): Rect {
        let designSurfaceOffset = this.designer.getDesignerSurfaceOffset();
        let actionBoundingRect = this.action.renderedElement.getBoundingClientRect();

        return new Rect(
            actionBoundingRect.top - designSurfaceOffset.y,
            actionBoundingRect.right - designSurfaceOffset.x,
            actionBoundingRect.bottom - designSurfaceOffset.y,
            actionBoundingRect.left - designSurfaceOffset.x
        );
    }

    getCardObjectBoundingRect(): Rect {
        let actionBoundingRect = this.action.renderedElement.getBoundingClientRect();

        return new Rect(
            actionBoundingRect.top,
            actionBoundingRect.right,
            actionBoundingRect.bottom,
            actionBoundingRect.left
        );
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        if (includeHeader) {
            let actionType = new Adaptive.TextBlock();
            actionType.text = "**" + this.action.getJsonTypeName() + "**";

            card.addItem(actionType);
        }

        var id = addLabelAndInput(card, "Id:", Adaptive.TextInput);
        id.input.defaultValue = this.action.id;
        id.input.placeholder = "(not set)";
        id.input.onValueChanged = () => {
            this.action.id = id.input.value;

            this.changed(false);
        }

        var title = addLabelAndInput(card, "Title:", Adaptive.TextInput);
        title.input.defaultValue = this.action.title;
        title.input.placeholder = "(not set)";
        title.input.onValueChanged = () => {
            this.action.title = title.input.value;

            this.changed(false);
        }
    }

    get action(): Adaptive.Action {
        return this._action;
    }
}

export abstract class TypedActionPeer<TAction extends Adaptive.Action> extends ActionPeer {
    constructor(designer: CardDesigner, registration: DesignerPeerRegistrationBase, action: TAction) {
        super(designer, registration, action);
    }

    get action(): TAction {
        return <TAction>this._action;
    }
}

export class HttpActionPeer extends TypedActionPeer<Adaptive.HttpAction> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        var method = addLabelAndInput(card, "Method:", Adaptive.ChoiceSetInput);
        method.input.isCompact = true;
        method.input.choices.push(new Adaptive.Choice("GET", "GET"));
        method.input.choices.push(new Adaptive.Choice("POST", "POST"));
        method.input.placeholder = "(not set)";
        method.input.defaultValue = this.action.method;
        method.input.onValueChanged = () => {
            this.action.method = method.input.value;

            this.changed(true);
        }

        var url = addLabelAndInput(card, "Url:", Adaptive.TextInput);
        url.input.defaultValue = this.action.url;
        url.input.placeholder = "(not set)";
        url.input.onValueChanged = () => {
            this.action.url = url.input.value;

            this.changed(false);
        }

        if (this.action.method && this.action.method.toLowerCase() == "post") {
            var body = addLabelAndInput(card, "Body:", Adaptive.TextInput);
            body.input.isMultiline = true;
            body.input.defaultValue = this.action.body;
            body.input.placeholder = "(not set)";
            body.input.onValueChanged = () => {
                this.action.body = body.input.value;

                this.changed(false);
            }
        }

        let headersEditor = new NameValuePairEditor();
        headersEditor.title = "HTTP headers:";
        headersEditor.addButtonTitle = "Add a new header";
        headersEditor.messageIfEmpty = "This action has no headers.";

        for (let choice of this.action.headers) {
            headersEditor.nameValuePairs.push({ "name": choice.name, "value": choice.value });
        }

        headersEditor.onChanged = (sender, refreshPropertySheet) => {
            this.action.headers = [];

            for (let nameValuePair of sender.nameValuePairs) {
                this.action.headers.push(new Adaptive.HttpHeader(nameValuePair.name, nameValuePair.value));
            }

            this.changed(refreshPropertySheet);
        };

        card.addItem(headersEditor.render());
    }
}

export class SubmitActionPeer extends TypedActionPeer<Adaptive.SubmitAction> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        var data = addLabelAndInput(card, "Data:", Adaptive.TextInput);
        data.input.isMultiline = true;
        data.input.defaultValue = JSON.stringify(this.action.data);
        data.input.placeholder = "(not set)";
        data.input.onValueChanged = () => {
            this.action.data = JSON.parse(data.input.value);

            this.changed(false);
        }
    }
}

export class OpenUrlActionPeer extends TypedActionPeer<Adaptive.OpenUrlAction> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        var url = addLabelAndInput(card, "Url:", Adaptive.TextInput);
        url.input.defaultValue = this.action.url;
        url.input.placeholder = "(not set)";
        url.input.onValueChanged = () => {
            this.action.url = url.input.value;

            this.changed(false);
        }
    }
}

export class ShowCardActionPeer extends TypedActionPeer<Adaptive.ShowCardAction> {
    protected getToolTip(): string {
        return "Double click to open/close";
    }
}

export class CardElementPeer extends DesignerPeer {
    protected _cardElement: Adaptive.CardElement;

    getCardObjectTypeName(): string {
        return this.cardElement.getJsonTypeName();
    }

    protected insertElementAfter(newElement: Adaptive.CardElement) {
        if (this.cardElement.parent instanceof Adaptive.Container) {
            this.cardElement.parent.insertItemAfter(newElement, this.cardElement);

            var newPeer = CardDesigner.cardElementPeerRegistry.createPeerInstance(this.designer, this, newElement);

            this.peerAdded(newPeer);
        }
    }

    protected internalRemove(): boolean {
        return this.cardElement.remove();
    }

    constructor(designer: CardDesigner, registration: DesignerPeerRegistrationBase, cardElement: Adaptive.CardElement) {
        super(designer, registration);

        this._cardElement = cardElement;

        if (cardElement instanceof Adaptive.CardElementContainer) {
            for (var i = 0; i < cardElement.getItemCount(); i++) {
                this.insertChild(CardDesigner.cardElementPeerRegistry.createPeerInstance(this.designer, this, cardElement.getItemAt(i)));
            }
        }

        for (var i = 0; i < this.cardElement.getActionCount(); i++) {
            this.insertChild(CardDesigner.actionPeerRegistry.createPeerInstance(this.designer, this, cardElement.getActionAt(i)));
        }
    }

    initializeCardElement() {
        // Do nothing in base implementation
    }

    canDrop(peer: DesignerPeer) {
        return this.cardElement instanceof Adaptive.Container && peer instanceof CardElementPeer;
    }

    tryDrop(peer: DesignerPeer, insertionPoint: IPoint): boolean {
        if (this.cardElement instanceof Adaptive.Container && peer instanceof CardElementPeer) {
            let targetChild: DesignerPeer = null;
            let insertAfter: boolean;

            for (var i = 0; i < this.getChildCount(); i++) {
                let rect = this.getChildAt(i).getBoundingRect();

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
                    let rect = this.getBoundingRect();

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
                        this.cardElement.insertItemAfter(peer.cardElement, (<CardElementPeer>targetChild).cardElement);
                    }
                    else {
                        this.cardElement.insertItemBefore(peer.cardElement, (<CardElementPeer>targetChild).cardElement);
                    }
                }
    
                this.insertChild(peer, peer.cardElement.index);
                this.changed(false);

                return true;
            }
        }

        return false;
    }

    getBoundingRect(): Rect {
        let designSurfaceOffset = this.designer.getDesignerSurfaceOffset();
        let cardElementBoundingRect = this.cardElement.renderedElement.getBoundingClientRect();

        if (this.cardElement.hasVisibleSeparator) {
            let separatorBoundingRect = this.cardElement.separatorElement.getBoundingClientRect();

            return new Rect(
                Math.min(separatorBoundingRect.top, cardElementBoundingRect.top) - designSurfaceOffset.y,
                Math.max(separatorBoundingRect.right, cardElementBoundingRect.right) - designSurfaceOffset.x,
                Math.max(separatorBoundingRect.bottom, cardElementBoundingRect.bottom) - designSurfaceOffset.y,
                Math.min(separatorBoundingRect.left, cardElementBoundingRect.left) - designSurfaceOffset.x,
            )
        }
        else {
            return new Rect(
                cardElementBoundingRect.top - designSurfaceOffset.y,
                cardElementBoundingRect.right - designSurfaceOffset.x,
                cardElementBoundingRect.bottom - designSurfaceOffset.y,
                cardElementBoundingRect.left - designSurfaceOffset.x
            );
        }
    }

    getCardObjectBoundingRect(): Rect {
        let cardElementBoundingRect = this.cardElement.renderedElement.getBoundingClientRect();

        return new Rect(
            cardElementBoundingRect.top,
            cardElementBoundingRect.right,
            cardElementBoundingRect.bottom,
            cardElementBoundingRect.left
        );
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        if (includeHeader) {
            let elementType = new Adaptive.TextBlock();
            elementType.text = "**" + this.cardElement.getJsonTypeName() + "**";

            card.addItem(elementType);
        }

        let id = addLabelAndInput(card, "Id:", Adaptive.TextInput);
        id.input.defaultValue = this.cardElement.id;
        id.input.placeholder = "(not set)";
        id.input.onValueChanged = () => {
            this.cardElement.id = id.input.value;

            this.changed(false);
        }

        let spacing = addLabelAndInput(card, "Spacing:", Adaptive.ChoiceSetInput);
        spacing.input.isCompact = true;
        spacing.input.choices.push(new Adaptive.Choice("None", Adaptive.Spacing.None.toString()));
        spacing.input.choices.push(new Adaptive.Choice("Small", Adaptive.Spacing.Small.toString()));
        spacing.input.choices.push(new Adaptive.Choice("Default", Adaptive.Spacing.Default.toString()));
        spacing.input.choices.push(new Adaptive.Choice("Medium", Adaptive.Spacing.Medium.toString()));
        spacing.input.choices.push(new Adaptive.Choice("Large", Adaptive.Spacing.Large.toString()));
        spacing.input.choices.push(new Adaptive.Choice("Extra large", Adaptive.Spacing.ExtraLarge.toString()));
        spacing.input.choices.push(new Adaptive.Choice("Default padding", Adaptive.Spacing.Padding.toString()));
        spacing.input.defaultValue = this.cardElement.spacing.toString();
        spacing.input.onValueChanged = () => {
            this.cardElement.spacing = <Adaptive.Spacing>parseInt(spacing.input.value);

            this.changed(false);
        }

        let separator = addLabelAndInput(card, "Show separator:", Adaptive.ToggleInput);
        separator.input.defaultValue = String(this.cardElement.separator);
        separator.input.onValueChanged = () => {
            this.cardElement.separator = separator.input.value == "true";

            this.changed(false);
        }

        var horizontalAlignment = addLabelAndInput(card, "Horizontal alignment:", Adaptive.ChoiceSetInput);
        horizontalAlignment.input.isCompact = true;
        horizontalAlignment.input.placeholder = "(not set)";
        horizontalAlignment.input.choices.push(new Adaptive.Choice("Left", Adaptive.HorizontalAlignment.Left.toString()));
        horizontalAlignment.input.choices.push(new Adaptive.Choice("Center", Adaptive.HorizontalAlignment.Center.toString()));
        horizontalAlignment.input.choices.push(new Adaptive.Choice("Right", Adaptive.HorizontalAlignment.Right.toString()));

        if (this.cardElement.horizontalAlignment) {
            horizontalAlignment.input.defaultValue = this.cardElement.horizontalAlignment.toString();
        }

        horizontalAlignment.input.onValueChanged = () => {
            if (horizontalAlignment.input.value) {
                this.cardElement.horizontalAlignment = <Adaptive.HorizontalAlignment>parseInt(horizontalAlignment.input.value);
            }

            this.changed(false);
        }

        var height = addLabelAndInput(card, "Height:", Adaptive.ChoiceSetInput);
        height.input.isCompact = true;
        height.input.choices.push(new Adaptive.Choice("Automatic", "auto"));
        height.input.choices.push(new Adaptive.Choice("Stretch", "stretch"));
        height.input.defaultValue = this.cardElement.height;
        height.input.onValueChanged = () => {
            this.cardElement.height = height.input.value === "auto" ? "auto" : "stretch";

            this.changed(false);
        }
    }

    get cardElement(): Adaptive.CardElement {
        return this._cardElement;
    }
}

export abstract class TypedCardElementPeer<TCardElement extends Adaptive.CardElement> extends CardElementPeer {
    constructor(designer: CardDesigner, registration: DesignerPeerRegistrationBase, cardElement: TCardElement) {
        super(designer, registration, cardElement);
    }

    get cardElement(): TCardElement {
        return <TCardElement>this._cardElement;
    }
}

export class AdaptiveCardPeer extends TypedCardElementPeer<Adaptive.AdaptiveCard> {
    protected addAction(action: Adaptive.Action) {
        this.cardElement.addAction(action);

        this.insertChild(CardDesigner.actionPeerRegistry.createPeerInstance(this.designer, this, action));
    }

    protected internalRemove(): boolean {
        return true;
    }

    protected internalAddCommands(commands: Array<PeerCommand>) {
        super.internalAddCommands(commands);

        commands.push(
            new PeerCommand(
                {
                    name: "Add an action",
                    iconClass: "acd-icon-bolt",
                    execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                        let popupMenu = new Controls.PopupMenu();

                        for (var i = 0; i < Adaptive.AdaptiveCard.actionTypeRegistry.getItemCount(); i++) {
                            let menuItem = new Controls.DropDownItem(i.toString(), Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(i).typeName);
                            menuItem.onClick = (clickedItem: Controls.DropDownItem) => {
                                let registryItem = Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(Number.parseInt(clickedItem.key));
                                let action = registryItem.createInstance();
                                action.title = registryItem.typeName;

                                this.addAction(action);

                                popupMenu.closePopup();
                            };

                            popupMenu.items.add(menuItem);
                        }

                        popupMenu.popup(clickedElement);
                    }
                })
        );
    }

    isDraggable(): boolean {
        return false;
    }

    canBeRemoved(): boolean {
        return false;
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, updatePropertySheet: boolean) {
        super.internalAddPropertySheetEntries(card, updatePropertySheet);

        var actionSelector = createActionSelector(card, this.cardElement.selectAction ? this.cardElement.selectAction.getJsonTypeName() : "none");

        actionSelector.input.onValueChanged = () => {
            if (actionSelector.input.value == "none") {
                this.cardElement.selectAction = null;
            }
            else {
                this.cardElement.selectAction = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(actionSelector.input.value);
            }

            this.changed(true);
        }

        if (this.cardElement.selectAction) {
            let selectActionPeer = CardDesigner.actionPeerRegistry.createPeerInstance(this.designer, null, this.cardElement.selectAction);
            selectActionPeer.internalAddPropertySheetEntries(card, false);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
        }
    }
}

export class ColumnPeer extends TypedCardElementPeer<Adaptive.Column> {
    protected isContainer(): boolean {
        return true;
    }

    getTreeItemText(): string {
        if (this.cardElement.width instanceof Adaptive.SizeAndUnit) {
            switch (this.cardElement.width.unit) {
                case Adaptive.SizeUnit.Weight:
                    return "Weight: " + this.cardElement.width.physicalSize;
                default:
                    return this.cardElement.width.physicalSize + " pixels";
            }
        }
        else {
            return this.cardElement.width.toString();
        }
    }

    isDraggable(): boolean {
        return false;
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        let width = addLabelAndInput(card, "Width:", Adaptive.ChoiceSetInput);
        width.input.isCompact = true;
        width.input.choices.push(new Adaptive.Choice("Automatic", "auto"));
        width.input.choices.push(new Adaptive.Choice("Stretched", "stretch"));
        width.input.choices.push(new Adaptive.Choice("Explicit", "explicit"));

        if (this.cardElement.width instanceof Adaptive.SizeAndUnit) {
            if (this.cardElement.width.unit == Adaptive.SizeUnit.Pixel) {
                width.input.defaultValue = "explicit";

                let explicitWidth = addLabelAndInput(card, "Explicit width (in pixels):", Adaptive.NumberInput);
                explicitWidth.input.defaultValue = this.cardElement.width.physicalSize.toString();
                explicitWidth.input.placeholder = "(not set)"
                explicitWidth.input.onValueChanged = () => {
                    try {
                        this.cardElement.width = new Adaptive.SizeAndUnit(parseInt(explicitWidth.input.value), Adaptive.SizeUnit.Pixel);

                        this.changed(false);
                    }
                    catch {
                        // Do nothing. The specified width is invalid
                    }
                }
            }
            else {
                width.input.defaultValue = "stretch";
            }
        }
        else {
            width.input.defaultValue = this.cardElement.width.toString();
        }

        width.input.placeholder = "(not set)";

        width.input.onValueChanged = () => {
            switch (width.input.value) {
                case "auto":
                    this.cardElement.width = "auto";
                    break;
                case "stretch":
                    this.cardElement.width = "stretch";
                    break;
                case "explicit":
                    this.cardElement.width = new Adaptive.SizeAndUnit(50, Adaptive.SizeUnit.Pixel);
                    break;
            }

            this.changed(true);
        }

        let verticalContentAlignment = addLabelAndInput(card, "Vertical content alignment:", Adaptive.ChoiceSetInput);
        verticalContentAlignment.input.isCompact = true;
        verticalContentAlignment.input.choices.push(new Adaptive.Choice("Top", Adaptive.VerticalAlignment.Top.toString()));
        verticalContentAlignment.input.choices.push(new Adaptive.Choice("Center", Adaptive.VerticalAlignment.Center.toString()));
        verticalContentAlignment.input.choices.push(new Adaptive.Choice("Bottom", Adaptive.VerticalAlignment.Bottom.toString()));
        verticalContentAlignment.input.defaultValue = this.cardElement.spacing.toString();
        verticalContentAlignment.input.placeholder = "(not set)";
        verticalContentAlignment.input.onValueChanged = () => {
            this.cardElement.verticalContentAlignment = <Adaptive.VerticalAlignment>parseInt(verticalContentAlignment.input.value);

            this.changed(false);
        }

        let actionSelector = createActionSelector(card, this.cardElement.selectAction ? this.cardElement.selectAction.getJsonTypeName() : "none");

        actionSelector.input.onValueChanged = () => {
            if (actionSelector.input.value == "none") {
                this.cardElement.selectAction = null;
            }
            else {
                this.cardElement.selectAction = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(actionSelector.input.value);
            }

            this.changed(true);
        }

        if (this.cardElement.selectAction) {
            let selectActionPeer = CardDesigner.actionPeerRegistry.createPeerInstance(this.designer, null, this.cardElement.selectAction);
            selectActionPeer.internalAddPropertySheetEntries(card, false);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
        }
    }
}

export class ColumnSetPeer extends TypedCardElementPeer<Adaptive.ColumnSet> {
    protected isContainer(): boolean {
        return true;
    }

    protected internalAddCommands(commands: Array<PeerCommand>) {
        super.internalAddCommands(commands);

        commands.push(
            new PeerCommand(
                {
                    name: "Add a column",
                    iconClass: "acd-icon-addColumn",
                    isPromotable: true,
                    execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                        var column = new Adaptive.Column();
                        column.width = "stretch";

                        this.cardElement.addColumn(column);

                        this.insertChild(CardDesigner.cardElementPeerRegistry.createPeerInstance(this.designer, this, column));
                    }
                })
        );
    }

    getTreeItemText(): string {
        let columnCount = this.cardElement.getCount();

        switch (columnCount) {
            case 0:
                return "No column";
            case 1:
                return "1 column";
            default:
                return columnCount + " columns";
        }
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        var actionSelector = createActionSelector(card, this.cardElement.selectAction ? this.cardElement.selectAction.getJsonTypeName() : "none");

        actionSelector.input.onValueChanged = () => {
            if (actionSelector.input.value == "none") {
                this.cardElement.selectAction = null;
            }
            else {
                this.cardElement.selectAction = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(actionSelector.input.value);
            }

            this.changed(true);
        }

        if (this.cardElement.selectAction) {
            let selectActionPeer = CardDesigner.actionPeerRegistry.createPeerInstance(this.designer, null, this.cardElement.selectAction);
            selectActionPeer.internalAddPropertySheetEntries(card, false);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
        }
    }

    canDrop(peer: DesignerPeer) {
        return true;
    }
}

export class ContainerPeer extends TypedCardElementPeer<Adaptive.Container> {
    protected isContainer(): boolean {
        return true;
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        var actionSelector = createActionSelector(card, this.cardElement.selectAction ? this.cardElement.selectAction.getJsonTypeName() : "none");

        actionSelector.input.onValueChanged = () => {
            if (actionSelector.input.value == "none") {
                this.cardElement.selectAction = null;
            }
            else {
                this.cardElement.selectAction = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(actionSelector.input.value);
            }

            this.changed(true);
        }

        if (this.cardElement.selectAction) {
            let selectActionPeer = CardDesigner.actionPeerRegistry.createPeerInstance(this.designer, null, this.cardElement.selectAction);
            selectActionPeer.internalAddPropertySheetEntries(card, false);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
        }
    }
}

export class ActionSetPeer extends TypedCardElementPeer<Adaptive.AdaptiveCard> {
    protected addAction(action: Adaptive.Action) {
        this.cardElement.addAction(action);

        this.insertChild(CardDesigner.actionPeerRegistry.createPeerInstance(this.designer, this, action));
    }

    protected internalAddCommands(commands: Array<PeerCommand>) {
        super.internalAddCommands(commands);

        commands.push(
            new PeerCommand(
                {
                    name: "Add an action",
                    iconClass: "acd-icon-bolt",
                    execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                        let popupMenu = new Controls.PopupMenu();

                        for (var i = 0; i < Adaptive.AdaptiveCard.actionTypeRegistry.getItemCount(); i++) {
                            let menuItem = new Controls.DropDownItem(i.toString(), Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(i).typeName);
                            menuItem.onClick = (clickedItem: Controls.DropDownItem) => {
                                let registryItem = Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(Number.parseInt(clickedItem.key));
                                let action = registryItem.createInstance();
                                action.title = registryItem.typeName;

                                this.addAction(action);

                                popupMenu.closePopup();
                            };

                            popupMenu.items.add(menuItem);
                        }

                        popupMenu.popup(command.renderedElement);
                    }
                })
        );
    }
}

function createActionSelector(card: Adaptive.AdaptiveCard, defaultValue: string): ILabelAndInput<Adaptive.ChoiceSetInput> {
    var actionSelector = addLabelAndInput(card, "Select action:", Adaptive.ChoiceSetInput, true);
    actionSelector.input.isCompact = true;
    actionSelector.input.choices.push(new Adaptive.Choice("(not set)", "none"));

    for (var i = 0; i < Adaptive.AdaptiveCard.actionTypeRegistry.getItemCount(); i++) {
        let choice = new Adaptive.Choice(Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(i).typeName, Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(i).typeName);

        actionSelector.input.choices.push(choice);
    }

    actionSelector.input.defaultValue = defaultValue;

    return actionSelector;
}

export class ImageSetPeer extends TypedCardElementPeer<Adaptive.ImageSet> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        var imageSize = addLabelAndInput(card, "Image Size:", Adaptive.ChoiceSetInput);
        imageSize.input.isCompact = true;
        imageSize.input.choices.push(new Adaptive.Choice("Automatic", Adaptive.Size.Auto.toString()));
        imageSize.input.choices.push(new Adaptive.Choice("Small", Adaptive.Size.Small.toString()));
        imageSize.input.choices.push(new Adaptive.Choice("Medium", Adaptive.Size.Medium.toString()));
        imageSize.input.choices.push(new Adaptive.Choice("Large", Adaptive.Size.Large.toString()));
        imageSize.input.choices.push(new Adaptive.Choice("Stretch", Adaptive.Size.Stretch.toString()));
        imageSize.input.defaultValue = this.cardElement.imageSize.toString();
        imageSize.input.onValueChanged = () => {
            this.cardElement.imageSize = <Adaptive.Size>parseInt(imageSize.input.value);

            this.changed(false);
        }
    }

    protected internalAddCommands(commands: Array<PeerCommand>) {
        super.internalAddCommands(commands);

        commands.push(
            new PeerCommand(
                {
                    name: "Add an image",
                    iconClass: "acd-icon-image",
                    isPromotable: true,
                    execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                        let newImage = new Adaptive.Image();

                        this.cardElement.addImage(newImage);

                        this.insertChild(CardDesigner.cardElementPeerRegistry.createPeerInstance(this.designer, this, newImage));
                    }
                })
        );
    }
}

export class ImagePeer extends TypedCardElementPeer<Adaptive.Image> {
    private get isParentImageSet(): boolean {
        return this.parent && this.parent instanceof ImageSetPeer;
    }

    isDraggable(): boolean {
        return !this.isParentImageSet;
    }

    getBoundingRect(): Rect {
        if (this.isParentImageSet) {
            let designSurfaceOffset = this.designer.getDesignerSurfaceOffset();
            let actionBoundingRect = this.cardElement.renderedElement.getBoundingClientRect();

            return new Rect(
                actionBoundingRect.top - designSurfaceOffset.y,
                actionBoundingRect.right - designSurfaceOffset.x,
                actionBoundingRect.bottom - designSurfaceOffset.y,
                actionBoundingRect.left - designSurfaceOffset.x
            );
        }
        else {
            return super.getBoundingRect();
        }
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        var url = addLabelAndInput(card, "Url:", Adaptive.TextInput);
        url.input.defaultValue = this.cardElement.url;
        url.input.onValueChanged = () => {
            this.cardElement.url = url.input.value;

            this.changed(false);
        }

        var altText = addLabelAndInput(card, "Alternate text:", Adaptive.TextInput);
        altText.input.placeholder = "(not set)";
        altText.input.defaultValue = this.cardElement.altText;
        altText.input.onValueChanged = () => {
            this.cardElement.altText = altText.input.value;

            this.changed(false);
        }

        if (!this.isParentImageSet) {
            var size = addLabelAndInput(card, "Size:", Adaptive.ChoiceSetInput);
            size.input.isCompact = true;
            size.input.choices.push(new Adaptive.Choice("Automatic", Adaptive.Size.Auto.toString()));
            size.input.choices.push(new Adaptive.Choice("Small", Adaptive.Size.Small.toString()));
            size.input.choices.push(new Adaptive.Choice("Medium", Adaptive.Size.Medium.toString()));
            size.input.choices.push(new Adaptive.Choice("Large", Adaptive.Size.Large.toString()));
            size.input.choices.push(new Adaptive.Choice("Stretch", Adaptive.Size.Stretch.toString()));
            size.input.defaultValue = this.cardElement.size.toString();
            size.input.onValueChanged = () => {
                this.cardElement.size = <Adaptive.Size>parseInt(size.input.value);

                this.changed(false);
            }

            var width = addLabelAndInput(card, "Width (preview):", Adaptive.TextInput);
            width.input.placeholder = "(not set) Format: <N>px, e.g. 50px";

            if (this.cardElement.pixelWidth) {
                width.input.defaultValue = this.cardElement.pixelWidth.toString();
            }

            width.input.onValueChanged = () => {
                try {
                    let size = Adaptive.SizeAndUnit.parse(width.input.value);

                    if (size.unit == Adaptive.SizeUnit.Pixel) {
                        this.cardElement.pixelWidth = size.physicalSize;
                    }
                }
                catch (e) {
                    this.cardElement.pixelWidth = null;
                }
                this.changed(false);
            }

            var height = addLabelAndInput(card, "Height  (preview):", Adaptive.TextInput);
            height.input.placeholder = "(not set) Format: <N>px, e.g. 50px";

            if (this.cardElement.pixelHeight) {
                height.input.defaultValue = this.cardElement.pixelHeight.toString();
            }

            height.input.onValueChanged = () => {
                try {
                    let size = Adaptive.SizeAndUnit.parse(height.input.value);

                    if (size.unit == Adaptive.SizeUnit.Pixel) {
                        this.cardElement.pixelHeight = size.physicalSize;
                    }
                }
                catch (e) {
                    this.cardElement.pixelHeight = null;
                }

                this.changed(false);
            }

            var style = addLabelAndInput(card, "Style:", Adaptive.ChoiceSetInput);
            style.input.isCompact = true;
            style.input.choices.push(new Adaptive.Choice("Default", Adaptive.ImageStyle.Default.toString()));
            style.input.choices.push(new Adaptive.Choice("Person", Adaptive.ImageStyle.Person.toString()));
            style.input.defaultValue = this.cardElement.style.toString();
            style.input.onValueChanged = () => {
                this.cardElement.style = <Adaptive.ImageStyle>parseInt(style.input.value);

                this.changed(false);
            }

            var backgroundColor = addLabelAndInput(card, "Background color:", Adaptive.TextInput);
            backgroundColor.input.placeholder = "(not set) Format: #RRGGBB";
            backgroundColor.input.defaultValue = this.cardElement.backgroundColor;
            backgroundColor.input.onValueChanged = () => {
                this.cardElement.backgroundColor = backgroundColor.input.value;

                this.changed(false);
            }

            var actionSelector = createActionSelector(card, this.cardElement.selectAction ? this.cardElement.selectAction.getJsonTypeName() : "none");

            actionSelector.input.onValueChanged = () => {
                if (actionSelector.input.value == "none") {
                    this.cardElement.selectAction = null;
                }
                else {
                    this.cardElement.selectAction = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(actionSelector.input.value);
                }

                this.changed(true);
            }

            if (this.cardElement.selectAction) {
                let selectActionPeer = CardDesigner.actionPeerRegistry.createPeerInstance(this.designer, null, this.cardElement.selectAction);
                selectActionPeer.internalAddPropertySheetEntries(card, false);
                selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
            }
        }
    }
}

export class FactSetPeer extends TypedCardElementPeer<Adaptive.FactSet> {
    initializeCardElement() {
        super.initializeCardElement();

        this.cardElement.facts.push(
            new Adaptive.Fact("Fact 1", "Value 1"),
            new Adaptive.Fact("Fact 2", "Value 2")
        );
    }

    getTreeItemText(): string {
        if (this.cardElement.facts.length == 0) {
            return "No fact";
        }

        let allNames = this.cardElement.facts.map(
            (value, index, array) => {
                return value.name;
            }
        )

        return allNames.join(", ");
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        let factsEditor = new NameValuePairEditor();
        factsEditor.title = "Facts:";
        factsEditor.addButtonTitle = "Add a new fact";
        factsEditor.messageIfEmpty = "This FactSet is empty.";

        for (let fact of this.cardElement.facts) {
            factsEditor.nameValuePairs.push({ "name": fact.name, "value": fact.value });
        }

        factsEditor.onChanged = (sender, refreshPropertySheet) => {
            this.cardElement.facts = [];

            for (let nameValuePair of sender.nameValuePairs) {
                this.cardElement.facts.push(new Adaptive.Fact(nameValuePair.name, nameValuePair.value));
            }

            this.changed(refreshPropertySheet);
        };

        card.addItem(factsEditor.render());
    }
}

export abstract class InputPeer<TInput extends Adaptive.Input> extends TypedCardElementPeer<TInput> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        var title = addLabelAndInput(card, "Title:", Adaptive.TextInput);
        title.input.placeholder = "(not set)";
        title.input.defaultValue = this.cardElement.title;
        title.input.onValueChanged = () => {
            this.cardElement.title = title.input.value;

            this.changed(false);
        }

        var defaultValue = addLabelAndInput(card, "Default value:", Adaptive.TextInput);
        defaultValue.input.placeholder = "(not set)";
        defaultValue.input.defaultValue = this.cardElement.defaultValue;
        defaultValue.input.onValueChanged = () => {
            this.cardElement.defaultValue = defaultValue.input.value;

            this.changed(false);
        }
    }

    initializeCardElement() {
        super.initializeCardElement();

        this.cardElement.title = "New Input.Toggle";
    }
}

export class TextInputPeer extends InputPeer<Adaptive.TextInput> {
    initializeCardElement() {
        super.initializeCardElement();

        this.cardElement.placeholder = "Placeholder text";
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        let placeholder = addLabelAndInput(card, "Placeholder:", Adaptive.TextInput);
        placeholder.input.placeholder = "(not set)";
        placeholder.input.defaultValue = this.cardElement.placeholder;
        placeholder.input.onValueChanged = () => {
            this.cardElement.placeholder = placeholder.input.value;

            this.changed(false);
        }

        let isMultiline = addLabelAndInput(card, "Multi-line:", Adaptive.ToggleInput);
        isMultiline.input.defaultValue = String(this.cardElement.isMultiline);
        isMultiline.input.onValueChanged = () => {
            this.cardElement.isMultiline = isMultiline.input.value == "true";

            this.changed(true);
        }

        if (!this.cardElement.isMultiline) {
            let style = addLabelAndInput(card, "Style:", Adaptive.ChoiceSetInput);
            style.input.isCompact = true;
            style.input.choices.push(new Adaptive.Choice("Text", Adaptive.InputTextStyle.Text.toString()));
            style.input.choices.push(new Adaptive.Choice("Email", Adaptive.InputTextStyle.Email.toString()));
            style.input.choices.push(new Adaptive.Choice("Telephone", Adaptive.InputTextStyle.Tel.toString()));
            style.input.choices.push(new Adaptive.Choice("Url", Adaptive.InputTextStyle.Url.toString()));
            style.input.defaultValue = this.cardElement.style.toString();
            style.input.onValueChanged = () => {
                this.cardElement.style = <Adaptive.InputTextStyle>parseInt(style.input.value);

                this.changed(false);
            }
        }
    }
}

export class NumberInputPeer extends InputPeer<Adaptive.NumberInput> {
    initializeCardElement() {
        super.initializeCardElement();

        this.cardElement.placeholder = "Placeholder text";
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        var placeholder = addLabelAndInput(card, "Placeholder:", Adaptive.TextInput);
        placeholder.input.placeholder = "(not set)";
        placeholder.input.defaultValue = this.cardElement.placeholder;
        placeholder.input.onValueChanged = () => {
            this.cardElement.placeholder = placeholder.input.value;

            this.changed(false);
        }

        var min = addLabelAndInput(card, "Minimum value:", Adaptive.NumberInput);
        min.input.placeholder = "(not set)";
        min.input.defaultValue = this.cardElement.min;
        min.input.onValueChanged = () => {
            this.cardElement.min = min.input.value;

            this.changed(false);
        }

        var max = addLabelAndInput(card, "Maximum value:", Adaptive.NumberInput);
        max.input.placeholder = "(not set)";
        max.input.defaultValue = this.cardElement.max;
        max.input.onValueChanged = () => {
            this.cardElement.max = max.input.value;

            this.changed(false);
        }
    }
}

export class DateInputPeer extends InputPeer<Adaptive.DateInput> {
}

export class TimeInputPeer extends InputPeer<Adaptive.TimeInput> {
}

export class ToggleInputPeer extends InputPeer<Adaptive.ToggleInput> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        var valueOn = addLabelAndInput(card, "Value when on:", Adaptive.TextInput);
        valueOn.input.placeholder = "(not set)";
        valueOn.input.defaultValue = this.cardElement.valueOn;
        valueOn.input.onValueChanged = () => {
            this.cardElement.valueOn = valueOn.input.value;

            this.changed(false);
        }

        var valueOff = addLabelAndInput(card, "Value when off:", Adaptive.TextInput);
        valueOff.input.placeholder = "(not set)";
        valueOff.input.defaultValue = this.cardElement.valueOff;
        valueOff.input.onValueChanged = () => {
            this.cardElement.valueOff = valueOff.input.value;

            this.changed(false);
        }
    }
}

export class ChoiceSetInputPeer extends InputPeer<Adaptive.ChoiceSetInput> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        let placeholder = addLabelAndInput(card, "Placeholder:", Adaptive.TextInput);
        placeholder.input.placeholder = "(not set)";
        placeholder.input.defaultValue = this.cardElement.placeholder;
        placeholder.input.onValueChanged = () => {
            this.cardElement.placeholder = placeholder.input.value;

            this.changed(false);
        }

        let isMultiSelect = addLabelAndInput(card, "Allow multi selection:", Adaptive.ToggleInput);
        isMultiSelect.input.defaultValue = String(this.cardElement.isMultiSelect);
        isMultiSelect.input.onValueChanged = () => {
            this.cardElement.isMultiSelect = isMultiSelect.input.value == "true";

            this.changed(true);
        }

        if (!this.cardElement.isMultiSelect) {
            let isCompact = addLabelAndInput(card, "Compact style:", Adaptive.ToggleInput);
            isCompact.input.defaultValue = String(this.cardElement.isCompact);
            isCompact.input.onValueChanged = () => {
                this.cardElement.isCompact = isCompact.input.value == "true";

                this.changed(false);
            }
        }

        let choicesEditor = new NameValuePairEditor();
        choicesEditor.title = "Choices:";
        choicesEditor.addButtonTitle = "Add a new choice";
        choicesEditor.messageIfEmpty = "This ChoiceSet is empty.";

        for (let choice of this.cardElement.choices) {
            choicesEditor.nameValuePairs.push({ "name": choice.title, "value": choice.value });
        }

        choicesEditor.onChanged = (sender, refreshPropertySheet) => {
            this.cardElement.choices = [];

            for (let nameValuePair of sender.nameValuePairs) {
                this.cardElement.choices.push(new Adaptive.Choice(nameValuePair.name, nameValuePair.value));
            }

            this.changed(refreshPropertySheet);
        };

        card.addItem(choicesEditor.render());
    }

    initializeCardElement() {
        this.cardElement.placeholder = "Placeholder text";

        this.cardElement.choices.push(
            new Adaptive.Choice("Choice 1", "Choice 1"),
            new Adaptive.Choice("Choice 2", "Choice 2")
        );
    }
}

class TextBlockPeerInplaceEditor extends CardElementPeerInplaceEditor<Adaptive.TextBlock> {
    private _renderedElement: HTMLTextAreaElement;

    private close(applyChanges: boolean) {
        if (this.onClose) {
            this.onClose(applyChanges);
        }
    }

    initialize() {
        this._renderedElement.select();
    }

    applyChanges() {
        this.cardElement.text = this._renderedElement.value;
    }

    render() {
        this._renderedElement = document.createElement("textarea");
        this._renderedElement.className = "acd-textBlock-inplace-editor";
        this._renderedElement.value = this.cardElement.text;
        this._renderedElement.onkeydown = (e) => {
            switch (e.keyCode) {
                case Controls.KEY_ESCAPE:
                   this.close(false);

                   e.preventDefault();
                   e.cancelBubble = true;

                   break;
                case Controls.KEY_ENTER:
                    this.close(true);

                    e.preventDefault();
                    e.cancelBubble = true;

                    break;
            }

            return !e.cancelBubble;
        };

        this.cardElement.applyStylesTo(this._renderedElement);

        return this._renderedElement;
    }
}

export class TextBlockPeer extends TypedCardElementPeer<Adaptive.TextBlock> {
    protected createInplaceEditor(): DesignerPeerInplaceEditor {
        return new TextBlockPeerInplaceEditor(this.cardElement);
    }

    getToolTip(): string {
        return "Double click to edit";
    }

    getTreeItemText(): string {
        return this.cardElement.text;
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        var text = addLabelAndInput(card, "Text:", Adaptive.TextInput);
        text.input.defaultValue = this.cardElement.text;
        text.input.isMultiline = true;
        text.input.onValueChanged = () => {
            this.cardElement.text = text.input.value;

            this.changed(false);
        }

        var wrap = addLabelAndInput(card, "Wrap:", Adaptive.ToggleInput);
        wrap.input.defaultValue = String(this.cardElement.wrap);
        wrap.input.onValueChanged = () => {
            this.cardElement.wrap = wrap.input.value == "true";

            this.changed(false);
        }

        var maxLines = addLabelAndInput(card, "Maximum lines:", Adaptive.NumberInput);
        maxLines.input.placeholder = "(not set)";
        maxLines.input.defaultValue = String(this.cardElement.maxLines);
        maxLines.input.onValueChanged = () => {
            try {
                var newMaxLines = parseInt(maxLines.input.value);

                this.cardElement.maxLines = newMaxLines;

                this.changed(false);
            }
            catch (ex) {
                // Do nothing
            }
        }

        var size = addLabelAndInput(card, "Size:", Adaptive.ChoiceSetInput);
        size.input.isCompact = true;
        size.input.choices.push(new Adaptive.Choice("Small", Adaptive.TextSize.Small.toString()));
        size.input.choices.push(new Adaptive.Choice("Default", Adaptive.TextSize.Default.toString()));
        size.input.choices.push(new Adaptive.Choice("Medium", Adaptive.TextSize.Medium.toString()));
        size.input.choices.push(new Adaptive.Choice("Large", Adaptive.TextSize.Large.toString()));
        size.input.choices.push(new Adaptive.Choice("Extra large", Adaptive.TextSize.ExtraLarge.toString()));
        size.input.defaultValue = this.cardElement.size.toString();
        size.input.onValueChanged = () => {
            this.cardElement.size = <Adaptive.TextSize>parseInt(size.input.value);

            this.changed(false);
        }

        var weight = addLabelAndInput(card, "Weight:", Adaptive.ChoiceSetInput);
        weight.input.isCompact = true;
        weight.input.choices.push(new Adaptive.Choice("Lighter", Adaptive.TextWeight.Lighter.toString()));
        weight.input.choices.push(new Adaptive.Choice("Default", Adaptive.TextWeight.Default.toString()));
        weight.input.choices.push(new Adaptive.Choice("Bolder", Adaptive.TextWeight.Bolder.toString()));
        weight.input.defaultValue = this.cardElement.weight.toString();
        weight.input.onValueChanged = () => {
            this.cardElement.weight = <Adaptive.TextWeight>parseInt(weight.input.value);

            this.changed(false);
        }

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
        color.input.onValueChanged = () => {
            this.cardElement.color = <Adaptive.TextColor>parseInt(color.input.value);

            this.changed(false);
        }

        var isSubtle = addLabelAndInput(card, "Subtle:", Adaptive.ToggleInput);
        isSubtle.input.defaultValue = String(this.cardElement.isSubtle);
        isSubtle.input.title = "";
        isSubtle.input.onValueChanged = () => {
            this.cardElement.isSubtle = isSubtle.input.value == "true";
 
            this.changed(false);
        }
    }

    initializeCardElement() {
        this.cardElement.text = "New TextBlock";
    }
}

export type CardElementType = { new(): Adaptive.CardElement };
export type ActionType = { new(): Adaptive.Action };
export type CardElementPeerType = { new(designer: CardDesigner, registration: DesignerPeerRegistrationBase, cardElement: Adaptive.CardElement): CardElementPeer };
export type ActionPeerType = { new(designer: CardDesigner, registration: DesignerPeerRegistrationBase, action: Adaptive.Action): ActionPeer };

class DesignerPeerCategory {
    static Unknown = "Unknown";
    static Containers = "Containers";
    static Elements = "Elements";
    static Inputs = "Inputs";
    static Actions = "Actions";
}

export class DesignerPeerRegistrationBase {
    readonly category: string;
    readonly iconClass: string;

    constructor(category: string, iconClass: string = null) {
        this.category = category;
        this.iconClass = iconClass;
    }
}

export class DesignerPeerRegistration<TSource, TPeer> extends DesignerPeerRegistrationBase{
    readonly sourceType: TSource;

    peerType: TPeer;

    constructor(sourceType: TSource, peerType: TPeer, category: string, iconClass: string = null) {
        super(category, iconClass);

        this.sourceType = sourceType;
        this.peerType = peerType;
    }
}

export abstract class DesignerPeerRegistry<TSource, TPeer> {
    protected _items: Array<DesignerPeerRegistration<TSource, TPeer>> = [];

    readonly defaultRegistration = new DesignerPeerRegistrationBase(DesignerPeerCategory.Unknown, "acd-icon-unknownPeer");

    constructor() {
        this.reset();
    }

    abstract reset();

    clear() {
        this._items = [];
    }

    findTypeRegistration(sourceType: TSource): DesignerPeerRegistration<TSource, TPeer> {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].sourceType === sourceType) {
                return this._items[i];
            }
        }

        return null;
    }

    registerPeer(sourceType: TSource, peerType: TPeer, category: string, iconClass: string = null) {
        var registrationInfo = this.findTypeRegistration(sourceType);

        if (registrationInfo != null) {
            registrationInfo.peerType = peerType;
        }
        else {
            registrationInfo = new DesignerPeerRegistration<TSource, TPeer> (
                sourceType,
                peerType,
                category,
                iconClass);

            this._items.push(registrationInfo);
        }
    }

    unregisterPeer(sourceType: TSource) {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].sourceType === sourceType) {
                this._items.splice(i, 1);

                return;
            }
        }
    }
}

export class CardElementPeerRegistry extends DesignerPeerRegistry<CardElementType, CardElementPeerType> {
    reset() {
        this.clear();

        this.registerPeer(Adaptive.AdaptiveCard, AdaptiveCardPeer, DesignerPeerCategory.Containers, "acd-icon-adaptiveCard");
        this.registerPeer(Adaptive.Container, ContainerPeer, DesignerPeerCategory.Containers, "acd-icon-container");
        this.registerPeer(Adaptive.ColumnSet, ColumnSetPeer, DesignerPeerCategory.Containers, "acd-icon-columnSet");
        this.registerPeer(Adaptive.Column, ColumnPeer, DesignerPeerCategory.Containers, "acd-icon-column");
        this.registerPeer(Adaptive.ImageSet, ImageSetPeer, DesignerPeerCategory.Containers, "acd-icon-imageSet");
        this.registerPeer(Adaptive.FactSet, FactSetPeer, DesignerPeerCategory.Containers, "acd-icon-factSet");

        this.registerPeer(Adaptive.TextBlock, TextBlockPeer, DesignerPeerCategory.Elements, "acd-icon-textBlock");
        this.registerPeer(Adaptive.Image, ImagePeer, DesignerPeerCategory.Elements, "acd-icon-image");
        this.registerPeer(Adaptive.ActionSet, ActionSetPeer, DesignerPeerCategory.Elements, "acd-icon-actionSet");

        this.registerPeer(Adaptive.TextInput, TextInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputText");
        this.registerPeer(Adaptive.DateInput, DateInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputDate");
        this.registerPeer(Adaptive.TimeInput, TimeInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputTime");
        this.registerPeer(Adaptive.ToggleInput, ToggleInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputToggle");
        this.registerPeer(Adaptive.NumberInput, NumberInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputNumber");
        this.registerPeer(Adaptive.ChoiceSetInput, ChoiceSetInputPeer, DesignerPeerCategory.Inputs, "acd-icon-inputChoiceSet");
    }

    createPeerInstance(designer: CardDesigner, parent: DesignerPeer, cardElement: Adaptive.CardElement): CardElementPeer {
        /*
        var registrationInfo: IDesignerPeerRegistration<CardElementType, CardElementPeerType> = undefined;

        for (var i = 0; i < this._items.length; i++) {
            if (cardElement instanceof this._items[i].sourceType) {
                registrationInfo = this._items[i];

                break;
            }
        }
        */

        var registrationInfo = this.findTypeRegistration((<any>cardElement).constructor);

        var peer = registrationInfo ? new registrationInfo.peerType(designer, registrationInfo, cardElement) : new CardElementPeer(designer, this.defaultRegistration, cardElement);
        peer.parent = parent;

        return peer;
    }
}

export class ActionPeerRegistry extends DesignerPeerRegistry<ActionType, ActionPeerType> {
    reset() {
        this.clear();

        this.registerPeer(Adaptive.HttpAction, HttpActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionHttp");
        this.registerPeer(Adaptive.SubmitAction, SubmitActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionSubmit");
        this.registerPeer(Adaptive.OpenUrlAction, OpenUrlActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionOpenUrl");
        this.registerPeer(Adaptive.ShowCardAction, ShowCardActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionShowCard");

        this.registerPeer(Outlook.ToggleVisibilityAction, ActionPeer, DesignerPeerCategory.Actions, "acd-icon-actionToggleVisibility");
    }

    createPeerInstance(designer: CardDesigner, parent: DesignerPeer, action: Adaptive.Action): ActionPeer {
        var registrationInfo = this.findTypeRegistration((<any>action).constructor);

        var peer = registrationInfo ? new registrationInfo.peerType(designer, registrationInfo, action) : new ActionPeer(designer, this.defaultRegistration, action);
        peer.parent = parent;

        return peer;
    }
}

class DragHandle extends DraggableElement {
    protected internalRender(): HTMLElement {
        let element = document.createElement("div");
        element.classList.add("acd-peerButton", "acd-icon-drag");
        element.title = "Drag to move this element";
        element.style.visibility = "hidden";
        element.style.position = "absolute";
        element.style.zIndex = "500";

        return element;
    }
}

export class CardDesigner {
    static readonly cardElementPeerRegistry: CardElementPeerRegistry = new CardElementPeerRegistry();
    static readonly actionPeerRegistry: ActionPeerRegistry = new ActionPeerRegistry();

    private _updateCount: number = 0;

    private _card: Adaptive.AdaptiveCard;
    private _allPeers: Array<DesignerPeer> = [];
    private _rootPeer: DesignerPeer;
    private _cardHost: HTMLElement;
    private _designerSurface: HTMLDivElement;
    private _selectedPeer: DesignerPeer;
    private _draggedPeer: DesignerPeer;
    private _dropTarget: DesignerPeer;
    private _dragHandle: DragHandle;
    private _removeCommandElement: HTMLElement;
    private _peerCommandsHostElement: HTMLElement;
    private _lastParseErrors: Array<Adaptive.IValidationError> = [];

    private updatePeerCommandsLayout() {
        if (this._selectedPeer) {
            let peerRect = this._selectedPeer.getBoundingRect();
            let dragHandleRect = this._dragHandle.renderedElement.getBoundingClientRect();
            let removeButtonRect = this._removeCommandElement.getBoundingClientRect();
            let commandsHostRect = this._peerCommandsHostElement.getBoundingClientRect();

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
    }

    private setSelectedPeer(value: DesignerPeer) {
        if (this._selectedPeer != value) {
            if (this._selectedPeer) {
                this._selectedPeer.isSelected = false;
            }

            this._selectedPeer = value;

            this._peerCommandsHostElement.innerHTML = "";

            if (this._selectedPeer) {
                this._selectedPeer.isSelected = true;

                let commands = this._selectedPeer.getCommands();

                for (let command of commands) {
                    this._peerCommandsHostElement.appendChild(command.render());
                }

                this._designerSurface.focus();
            }

            this.updatePeerCommandsLayout();

            if (this.onSelectedPeerChanged) {
                this.onSelectedPeerChanged(this._selectedPeer);
            }
        }
    }

    private peerChanged(peer: DesignerPeer, updatePropertySheet: boolean) {
        this._lastParseErrors = [];

        this.renderCard()
        this.updateLayout();

        if (updatePropertySheet && this.onSelectedPeerChanged) {
            this.onSelectedPeerChanged(this._selectedPeer);
        }
    }

    private peerRemoved(peer: DesignerPeer) {
        this._allPeers.splice(this._allPeers.indexOf(peer), 1);

        if (peer == this._selectedPeer) {
            this.setSelectedPeer(null);
        }

        if (this._updateCount == 0) {
            this.renderCard();
            this.updateLayout();
        }
    }

    private renderCard() {
        this._cardHost.innerHTML = "";

        if (this.card) {
            let validationErrors = this.card.validate();

            let allErrors = validationErrors.concat(this._lastParseErrors);

            if (this.onCardValidated) {
                this.onCardValidated(allErrors);
            }

            this._cardHost.appendChild(this.card.render());
        }
    }

    private addPeer(peer: DesignerPeer) {
        if (this._allPeers.indexOf(peer) < 0) {
            this._allPeers.push(peer);

            peer.render();

            peer.onSelectedChanged = (peer: DesignerPeer) => {
                if (peer.isSelected) {
                    this.setSelectedPeer(peer);
                }
                else {
                    if (this._selectedPeer == peer) {
                        this.setSelectedPeer(null);
                    }
                }
            };
            peer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.peerChanged(sender, updatePropertySheet); };
            peer.onPeerRemoved = (sender: DesignerPeer) => { this.peerRemoved(sender); };
            peer.onPeerAdded = (sender: DesignerPeer, newPeer: DesignerPeer) => { this.addPeer(newPeer); };
            peer.onStartDrag = (sender: DesignerPeer) => { this.startDrag(sender); }
            peer.onEndDrag = (sender: DesignerPeer) => { this.endDrag(); }

            peer.addElementsToDesignerSurface(this._designerSurface);

            for (var i = 0; i < peer.getChildCount(); i++) {
                this.addPeer(peer.getChildAt(i));
            }
        }
    }

    private internalFindDropTarget(pointerPosition: IPoint, currentPeer: DesignerPeer, forPeer: DesignerPeer): DesignerPeer {
        if (currentPeer == forPeer) {
            return null;
        }

        var result: DesignerPeer = null;
        var lookDeeper = currentPeer instanceof ActionPeer;

        if (!lookDeeper) {
            var boundingRect = currentPeer.getBoundingRect();

            lookDeeper = boundingRect.isInside(pointerPosition);
        }

        if (lookDeeper) {
            let canDrop = currentPeer.canDrop(forPeer);

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
    }

    private findCardElementPeer(cardElement: Adaptive.CardElement): CardElementPeer {
        for (var i = 0; i < this._allPeers.length; i++) {
            var peer = this._allPeers[i];

            if (peer instanceof CardElementPeer && peer.cardElement == cardElement) {
                return peer;
            }
        }

        return null;
    }

    private findActionPeer(action: Adaptive.Action): ActionPeer {
        for (var i = 0; i < this._allPeers.length; i++) {
            var peer = this._allPeers[i];

            if (peer instanceof ActionPeer && peer.action == action) {
                return peer;
            }
        }

        return null;
    }

    private inlineCardExpanded(action: Adaptive.ShowCardAction, isExpanded: boolean) {
        let peer = this.findCardElementPeer(action.card);

        if (isExpanded) {
            if (!peer) {
                let registration = CardDesigner.cardElementPeerRegistry.findTypeRegistration(Adaptive.AdaptiveCard);

                // peer = new AdaptiveCardPeer(this, , action.card);
                peer = new registration.peerType(this, registration, action.card);
                
                let parentPeer = this.findActionPeer(action);

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
    }

    private get draggedPeer(): DesignerPeer {
        return this._draggedPeer;
    }

    private set draggedPeer(value: DesignerPeer) {
        if (this._draggedPeer != value) {
            if (this._draggedPeer) {
                this._draggedPeer.dragging = false;
            }

            this._draggedPeer = value;

            if (this._draggedPeer) {
                this._draggedPeer.dragging = true;
            }
        }
    }

    readonly parentElement: HTMLElement;

    constructor(parentElement: HTMLElement) {
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

        this._designerSurface.onkeydown = (e: KeyboardEvent) => {
            if (this._selectedPeer) {
                switch (e.keyCode) {
                    case Controls.KEY_ESCAPE:
                        this.setSelectedPeer(this._selectedPeer.parent);

                        break;
                    case Controls.KEY_DELETE:
                        this.removeSelected();

                        break;
                }
            }

            return !e.cancelBubble;
        }

        this._designerSurface.onpointermove = (e: PointerEvent) => {
            let clientRect = this._designerSurface.getBoundingClientRect();

            this.tryDrop({ x: e.x - clientRect.left, y: e.y - clientRect.top }, this.draggedPeer);
        }

        this._designerSurface.onpointerup = (e: PointerEvent) => {
            if (this.draggedPeer) {
                this.endDrag();
            }
        }

        rootElement.appendChild(this._designerSurface);

        this.parentElement.innerHTML = "";
        this.parentElement.appendChild(rootElement);
    }

    onCardValidated: (errors: Array<Adaptive.IValidationError>) => void;
    onSelectedPeerChanged: (peer: DesignerPeer) => void;
    onLayoutUpdated: (isFullRefresh: boolean) => void;

    getDesignerSurfaceOffset(): IPoint {
        let clientRect = this._designerSurface.getBoundingClientRect();

        return { x: clientRect.left, y: clientRect.top };
    }

    findDropTarget(pointerPosition: IPoint, peer: DesignerPeer): DesignerPeer {
        return this.internalFindDropTarget(pointerPosition, this._rootPeer, peer);
    }

    beginUpdate() {
        this._updateCount++;
    }

    endUpdate(renderCard: boolean) {
        if (this._updateCount > 0) {
            this._updateCount--;

            if (this._updateCount == 0) {
                if (renderCard) {
                    this.renderCard();
                }

                this.updateLayout();
            }
        }
    }

    render() {
        this._designerSurface.innerHTML = "";
        this._allPeers = [];

        this.setSelectedPeer(null);

        this.renderCard();

        if (this.card) {
            this._rootPeer = CardDesigner.cardElementPeerRegistry.createPeerInstance(this, null, this.card);

            this.addPeer(this._rootPeer);
        }

        this._removeCommandElement = document.createElement("div");
        this._removeCommandElement.classList.add("acd-peerButton", "acd-icon-remove");
        this._removeCommandElement.title = "Remove";
        this._removeCommandElement.style.visibility = "hidden";
        this._removeCommandElement.style.position = "absolute";
        this._removeCommandElement.style.zIndex = "500";
        this._removeCommandElement.onclick = (e) => {
            this.removeSelected();
        }

        this._dragHandle = new DragHandle();
        this._dragHandle.onStartDrag = (sender) => {
            this._dragHandle.endDrag();
            this.startDrag(this._selectedPeer);
        }
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
    }

    parseCard(json: string) {
        this._lastParseErrors = [];

        this.card.parse(JSON.parse(json), this._lastParseErrors);

        this.render();
    }




    updateLayout(isFullRefresh: boolean = true) {
        for (var i = 0; i < this._allPeers.length; i++) {
            this._allPeers[i].updateLayout();
        }

        this.updatePeerCommandsLayout();

        if (this.onLayoutUpdated) {
            this.onLayoutUpdated(isFullRefresh);
        }
    }

    removeSelected() {
        if (this.selectedPeer) {
            this.beginUpdate();

            try {
                let parent = this.selectedPeer.parent;

                if (this.selectedPeer.remove(false, true)) {
                    this.setSelectedPeer(parent);
                }
            }
            finally {
                this.endUpdate(true);
            }
        }
    }

    startDrag(peer: DesignerPeer) {
        if (!this.draggedPeer) {
            this._designerSurface.classList.add("dragging");

            this.draggedPeer = peer;

            this.setSelectedPeer(this.draggedPeer);
        }
    }

    endDrag() {
        if (this.draggedPeer) {
            // Ensure that the dragged peer's elements are at the top in Z order
            this.draggedPeer.removeElementsFromDesignerSurface(true);
            this.draggedPeer.addElementsToDesignerSurface(this._designerSurface, true);

            this._dropTarget.renderedElement.classList.remove("dragover");

            this.draggedPeer = null;

            this._designerSurface.classList.remove("dragging");
        }
    }

    tryDrop(pointerPosition: IPoint, peer: DesignerPeer): boolean {
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
    }

    isPointerOver(x: number, y: number) {
        let clientRect = this._designerSurface.getBoundingClientRect();

        return (x >= clientRect.left) && (x <= clientRect.right) && (y >= clientRect.top) && (y <= clientRect.bottom);
    }

    pageToClientCoordinates(x: number, y: number): IPoint {
        let clientRect = this._designerSurface.getBoundingClientRect();

        return {
            x: x - clientRect.left,
            y: y - clientRect.top
        }
    }

    get rootPeer(): DesignerPeer {
        return this._rootPeer;
    }

    get selectedPeer(): DesignerPeer {
        return this._selectedPeer;
    }

    get card(): Adaptive.AdaptiveCard {
        return this._card;
    }

    set card(value: Adaptive.AdaptiveCard) {
        if (value != this._card) {
            if (this._card) {
                this._card.onInlineCardExpanded = null;
            }

            this._card = value;

            if (this._card) {
                this._card.onInlineCardExpanded = (action: Adaptive.ShowCardAction, isExpanded: boolean) => { this.inlineCardExpanded(action, isExpanded); };
            }

            this.render();
        }
    }
}
