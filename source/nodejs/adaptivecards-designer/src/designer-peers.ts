import * as Adaptive  from "adaptivecards";
import * as Controls  from "adaptivecards-controls";
import { DraggableElement } from "./draggable-element";
import { PeerCommand } from "./peer-command";
import { CardDesignerSurface } from "./card-designer-surface";
import { TreeItem } from "./treeitem";
import { Rect, IPoint } from "./miscellaneous";

interface ILabelAndInput<TInput extends Adaptive.Input> {
    label: Adaptive.TextBlock;
    input: TInput;
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

    onChanged: (sender: NameValuePairEditor, refreshPropertySheet: boolean) => void;

    nameValuePairs: Array<INameValuePair> = [];
    title: string = "Name/value pairs";
    messageIfEmpty = "This collection is empty.";
    addButtonTitle: string = "Add a new pair";
    nameInputTitle: string = "Name";
    valueInputTitle: string = "Value";

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
                textInput.placeholder = this.nameInputTitle;
                textInput.defaultValue = this.nameValuePairs[i].name;
                textInput.onValueChanged = (sender) => {
                    this.nameValuePairs[i].name = sender.value;

                    this.changed();
                };

                let nameColumn = new Adaptive.Column("stretch");
                nameColumn.addItem(textInput);

                textInput = new Adaptive.TextInput();
                textInput.placeholder = this.valueInputTitle;
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

    protected getExcludedProperties(): Array<string> {
        return [];
    }

    protected abstract internalRemove(): boolean;

    readonly registration: DesignerPeerRegistrationBase;
    readonly designerSurface: CardDesignerSurface;
    readonly treeItem: TreeItem;

    parent: DesignerPeer;

    onSelectedChanged: (sender: DesignerPeer) => void;
    onChanged: (sender: DesignerPeer, updatePropertySheet: boolean) => void;
    onPeerRemoved: (sender: DesignerPeer) => void;
    onPeerAdded: (sender: DesignerPeer, newPeer: DesignerPeer) => void;

    abstract getCardObjectTypeName(): string;
    abstract internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean);

    constructor(designerSurface: CardDesignerSurface, registration: DesignerPeerRegistrationBase) {
        super();

        if (!registration) {
            alert((<any>this).constructor.name);
        }

        this.registration = registration;
        this.designerSurface = designerSurface;
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

    constructor(designerSurface: CardDesignerSurface, registration: DesignerPeerRegistrationBase, action: Adaptive.Action) {
        super(designerSurface, registration);

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
        let designSurfaceOffset = this.designerSurface.getDesignerSurfaceOffset();
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

        var iconUrl = addLabelAndInput(card, "Icon URL:", Adaptive.TextInput);
        iconUrl.input.defaultValue = this.action.iconUrl;
        iconUrl.input.placeholder = "(not set)";
        iconUrl.input.onValueChanged = () => {
            this.action.iconUrl = iconUrl.input.value;

            this.changed(false);
        }
    }

    get action(): Adaptive.Action {
        return this._action;
    }
}

export abstract class TypedActionPeer<TAction extends Adaptive.Action> extends ActionPeer {
    constructor(designerSurface: CardDesignerSurface, registration: DesignerPeerRegistrationBase, action: TAction) {
        super(designerSurface, registration, action);
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

            var newPeer = CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(this.designerSurface, this, newElement);

            this.peerAdded(newPeer);
        }
    }

    protected internalRemove(): boolean {
        return this.cardElement.remove();
    }

    constructor(designerSurface: CardDesignerSurface, registration: DesignerPeerRegistrationBase, cardElement: Adaptive.CardElement) {
        super(designerSurface, registration);

        this._cardElement = cardElement;

        if (cardElement instanceof Adaptive.CardElementContainer) {
            for (var i = 0; i < cardElement.getItemCount(); i++) {
                this.insertChild(CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(this.designerSurface, this, cardElement.getItemAt(i)));
            }
        }

        for (var i = 0; i < this.cardElement.getActionCount(); i++) {
            this.insertChild(CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, this, cardElement.getActionAt(i)));
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
        let designSurfaceOffset = this.designerSurface.getDesignerSurfaceOffset();
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

        let getExcludedProperties = this.getExcludedProperties();

        if (getExcludedProperties.indexOf("id") < 0) {
            let id = addLabelAndInput(card, "Id:", Adaptive.TextInput);
            id.input.defaultValue = this.cardElement.id;
            id.input.placeholder = "(not set)";
            id.input.onValueChanged = () => {
                this.cardElement.id = id.input.value;

                this.changed(false);
            }
        }


        if (getExcludedProperties.indexOf("spacing") < 0) {
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
        }

        if (getExcludedProperties.indexOf("separator") < 0) {
            let separator = addLabelAndInput(card, "Show separator:", Adaptive.ToggleInput);
            separator.input.defaultValue = String(this.cardElement.separator);
            separator.input.onValueChanged = () => {
                this.cardElement.separator = separator.input.value == "true";

                this.changed(false);
            }
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

            horizontalAlignment.input.onValueChanged = () => {
                if (horizontalAlignment.input.value) {
                    this.cardElement.horizontalAlignment = <Adaptive.HorizontalAlignment>parseInt(horizontalAlignment.input.value);
                }

                this.changed(false);
            }
        }

        if (getExcludedProperties.indexOf("height") < 0) {
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
    }

    get cardElement(): Adaptive.CardElement {
        return this._cardElement;
    }
}

export abstract class TypedCardElementPeer<TCardElement extends Adaptive.CardElement> extends CardElementPeer {
    constructor(designerSurface: CardDesignerSurface, registration: DesignerPeerRegistrationBase, cardElement: TCardElement) {
        super(designerSurface, registration, cardElement);
    }

    get cardElement(): TCardElement {
        return <TCardElement>this._cardElement;
    }
}

export class AdaptiveCardPeer extends TypedCardElementPeer<Adaptive.AdaptiveCard> {
    protected addAction(action: Adaptive.Action) {
        this.cardElement.addAction(action);

        this.insertChild(CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, this, action));
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

    protected getExcludedProperties(): Array<string> {
        return [ "id", "horizontalAlignment", "separator", "height", "spacing" ];
    }

    isDraggable(): boolean {
        return false;
    }

    canBeRemoved(): boolean {
        return false;
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, updatePropertySheet: boolean) {
        super.internalAddPropertySheetEntries(card, updatePropertySheet);

        let lang = addLabelAndInput(card, "Language:", Adaptive.TextInput);
        lang.input.defaultValue = this.cardElement.lang;
        lang.input.placeholder = "(not set) ISO 639-1 code";
        lang.input.onValueChanged = () => {
            this.cardElement.lang = lang.input.value;

            this.changed(false);
        }

        let fallbackText = addLabelAndInput(card, "Fallback text:", Adaptive.TextInput);
        fallbackText.input.defaultValue = this.cardElement.fallbackText;
        fallbackText.input.placeholder = "(not set)";
        fallbackText.input.isMultiline = true;
        fallbackText.input.onValueChanged = () => {
            this.cardElement.fallbackText = fallbackText.input.value;

            this.changed(false);
        }

        let speak = addLabelAndInput(card, "Speak:", Adaptive.TextInput);
        speak.input.defaultValue = this.cardElement.fallbackText;
        speak.input.placeholder = "(not set)";
        speak.input.isMultiline = true;
        speak.input.onValueChanged = () => {
            this.cardElement.speak = speak.input.value;

            this.changed(false);
        }

        let backgroundImage = addLabelAndInput(card, "Background image URL:", Adaptive.TextInput);
        backgroundImage.input.placeholder = "(not set)";

        if (this.cardElement.backgroundImage) {
            backgroundImage.input.defaultValue = this.cardElement.backgroundImage.url;
        }

        backgroundImage.input.onValueChanged = () => {
            if (backgroundImage.input.value) {
                this.cardElement.backgroundImage = new Adaptive.BackgroundImage();
                this.cardElement.backgroundImage.url = backgroundImage.input.value;
            }
            else {
                this.cardElement.backgroundImage = null;
            }

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
            let selectActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
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
            switch (this.cardElement.width) {
                case "stretch":
                    return "Stretch";
                case "auto":
                    return "Automatic";
                default:
                    return "";
            }
        }
    }

    isDraggable(): boolean {
        return false;
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        let backgroundImage = addLabelAndInput(card, "Background image URL:", Adaptive.TextInput);
        backgroundImage.input.placeholder = "(not set)";

        if (this.cardElement.backgroundImage) {
            backgroundImage.input.defaultValue = this.cardElement.backgroundImage.url;
        }

        backgroundImage.input.onValueChanged = () => {
            if (backgroundImage.input.value) {
                this.cardElement.backgroundImage = new Adaptive.BackgroundImage();
                this.cardElement.backgroundImage.url = backgroundImage.input.value;
            }
            else {
                this.cardElement.backgroundImage = null;
            }

            this.changed(false);
        }

        let style = addLabelAndInput(card, "Style:", Adaptive.ChoiceSetInput);
        style.input.isCompact = true;
        style.input.placeholder = "(not set)";
        style.input.choices.push(new Adaptive.Choice("Default", "default"));
        style.input.choices.push(new Adaptive.Choice("Emphasis", "emphasis"));

        if (this.cardElement.style) {
            style.input.defaultValue = this.cardElement.style.toString();
        }

        style.input.onValueChanged = () => {
            this.cardElement.style = style.input.value;

            this.changed(false);
        }

        let width = addLabelAndInput(card, "Width:", Adaptive.ChoiceSetInput);
        width.input.isCompact = true;
        width.input.choices.push(new Adaptive.Choice("Automatic", "auto"));
        width.input.choices.push(new Adaptive.Choice("Stretch", "stretch"));
        width.input.choices.push(new Adaptive.Choice("Weighted", "weighted"));
        width.input.choices.push(new Adaptive.Choice("Pixels", "pixels"));

        if (this.cardElement.width instanceof Adaptive.SizeAndUnit) {
            if (this.cardElement.width.unit == Adaptive.SizeUnit.Pixel) {
                width.input.defaultValue = "pixels";

                let pixelWidth = addLabelAndInput(card, "Width in pixels:", Adaptive.NumberInput);
                pixelWidth.input.defaultValue = this.cardElement.width.physicalSize.toString();
                pixelWidth.input.placeholder = "(not set)"
                pixelWidth.input.onValueChanged = () => {
                    try {
                        this.cardElement.width = new Adaptive.SizeAndUnit(parseInt(pixelWidth.input.value), Adaptive.SizeUnit.Pixel);

                        this.changed(false);
                    }
                    catch {
                        // Do nothing. The specified width is invalid
                    }
                }
            }
            else {
                width.input.defaultValue = "weighted";

                let weightedWidth = addLabelAndInput(card, "Weight:", Adaptive.NumberInput);
                weightedWidth.input.defaultValue = this.cardElement.width.physicalSize.toString();
                weightedWidth.input.placeholder = "(not set)"
                weightedWidth.input.onValueChanged = () => {
                    try {
                        this.cardElement.width = new Adaptive.SizeAndUnit(parseInt(weightedWidth.input.value), Adaptive.SizeUnit.Weight);

                        this.changed(false);
                    }
                    catch {
                        // Do nothing. The specified width is invalid
                    }
                }
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
                case "pixels":
                    this.cardElement.width = new Adaptive.SizeAndUnit(50, Adaptive.SizeUnit.Pixel);
                    break;
                case "weighted":
                    this.cardElement.width = new Adaptive.SizeAndUnit(50, Adaptive.SizeUnit.Weight);
                    break;
                case "stretch":
                default:
                    this.cardElement.width = "stretch";
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
            let selectActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
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

                        this.insertChild(CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(this.designerSurface, this, column));
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
            let selectActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
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

        let backgroundImage = addLabelAndInput(card, "Background image URL:", Adaptive.TextInput);
        backgroundImage.input.placeholder = "(not set)";

        if (this.cardElement.backgroundImage) {
            backgroundImage.input.defaultValue = this.cardElement.backgroundImage.url;
        }

        backgroundImage.input.onValueChanged = () => {
            if (backgroundImage.input.value) {
                this.cardElement.backgroundImage = new Adaptive.BackgroundImage();
                this.cardElement.backgroundImage.url = backgroundImage.input.value;
            }
            else {
                this.cardElement.backgroundImage = null;
            }

            this.changed(false);
        }

        let style = addLabelAndInput(card, "Style:", Adaptive.ChoiceSetInput);
        style.input.isCompact = true;
        style.input.placeholder = "(not set)";
        style.input.choices.push(new Adaptive.Choice("Default", "default"));
        style.input.choices.push(new Adaptive.Choice("Emphasis", "emphasis"));
        style.input.defaultValue = this.cardElement.style.toString();
        style.input.onValueChanged = () => {
            this.cardElement.style = style.input.value;

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
            let selectActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
            selectActionPeer.internalAddPropertySheetEntries(card, false);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
        }
    }
}

export class ActionSetPeer extends TypedCardElementPeer<Adaptive.AdaptiveCard> {
    protected addAction(action: Adaptive.Action) {
        this.cardElement.addAction(action);

        this.insertChild(CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, this, action));
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

                        this.insertChild(CardDesignerSurface.cardElementPeerRegistry.createPeerInstance(this.designerSurface, this, newImage));
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
            let designSurfaceOffset = this.designerSurface.getDesignerSurfaceOffset();
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
                let selectActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
                selectActionPeer.internalAddPropertySheetEntries(card, false);
                selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
            }
        }
    }
}

export class MediaPeer extends TypedCardElementPeer<Adaptive.Media> {
    getTreeItemText(): string {
        if (this.cardElement.selectedMediaType == "audio") {
            return "audio";
        }
        else if (this.cardElement.selectedMediaType == "video") {
            return "video";
        }
        else {
            return super.getTreeItemText();
        }
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        let altText = addLabelAndInput(card, "Alternate text:", Adaptive.TextInput);
        altText.input.placeholder = "(not set)";
        altText.input.defaultValue = this.cardElement.altText;
        altText.input.onValueChanged = () => {
            this.cardElement.altText = altText.input.value;

            this.changed(false);
        }

        var posterUrl = addLabelAndInput(card, "Poster URL:", Adaptive.TextInput);
        posterUrl.input.placeholder = "(not set)";
        posterUrl.input.defaultValue = this.cardElement.poster;
        posterUrl.input.onValueChanged = () => {
            this.cardElement.poster = posterUrl.input.value;

            this.changed(false);
        }

        let sourcesEditor = new NameValuePairEditor();
        sourcesEditor.title = "Sources:";
        sourcesEditor.addButtonTitle = "Add a new source";
        sourcesEditor.messageIfEmpty = "No source has been defined.";
        sourcesEditor.nameInputTitle = "URL";
        sourcesEditor.valueInputTitle = "MIME type";

        for (let source of this.cardElement.sources) {
            sourcesEditor.nameValuePairs.push({ "name": source.url, "value": source.mimeType });
        }

        sourcesEditor.onChanged = (sender, refreshPropertySheet) => {
            this.cardElement.sources = [];

            for (let nameValuePair of sender.nameValuePairs) {
                this.cardElement.sources.push(new Adaptive.MediaSource(nameValuePair.name, nameValuePair.value));
            }

            this.changed(refreshPropertySheet);
        };

        card.addItem(sourcesEditor.render());
    }
}

export class FactSetPeer extends TypedCardElementPeer<Adaptive.FactSet> {
    protected getExcludedProperties(): Array<string> {
        return [ "horizontalAlignment" ];
    }

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
    protected getExcludedProperties(): Array<string> {
        return [ "horizontalAlignment", "height" ];
    }

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
        choicesEditor.nameInputTitle = "Title";

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