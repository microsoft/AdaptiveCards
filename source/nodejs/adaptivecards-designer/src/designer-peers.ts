// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive  from "adaptivecards";
import * as Controls  from "adaptivecards-controls";
import { DraggableElement } from "./draggable-element";
import { PeerCommand } from "./peer-command";
import { CardDesignerSurface } from "./card-designer-surface";
import { DesignerPeerTreeItem } from "./designer-peer-treeitem";
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
    
    // result.label.selectAction = new Adaptive.SubmitAction();
    // result.label.selectAction.onExecute = (sender: Adaptive.Action) => {
    //     alert("Clicked: " + label);
    // }

    leftColumn.addItem(result.label);
    rightColumn.addItem(result.input);

    container.addItem(columnSet);

    return result;
}

function addHeader(container: Adaptive.Container, text: string): Adaptive.CardElement {
    let header = new Adaptive.TextBlock();
    header.text = "**" + text + "**";

    container.addItem(header);

    return header;
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
    private _parent: DesignerPeer;
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

    protected click(e: MouseEvent) {
        super.click(e);

        this.isSelected = true;
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

    protected internalGetTreeItemText(): string {
        return null;
    }

    protected abstract internalRemove(): boolean;

    readonly registration: DesignerPeerRegistrationBase;
    readonly designerSurface: CardDesignerSurface;
    readonly treeItem: DesignerPeerTreeItem;

    onParentChanged: (sender: DesignerPeer) => void;
    onSelectedChanged: (sender: DesignerPeer) => void;
    onChanged: (sender: DesignerPeer, updatePropertySheet: boolean) => void;
    onPeerRemoved: (sender: DesignerPeer) => void;
    onPeerAdded: (sender: DesignerPeer, newPeer: DesignerPeer) => void;

    abstract getCardObject(): Adaptive.CardObject;
    abstract internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean);

    constructor(parent: DesignerPeer, designerSurface: CardDesignerSurface, registration: DesignerPeerRegistrationBase) {
        super();

        this._parent = parent;

        if (!registration) {
            alert((<any>this).constructor.name);
        }

        this.registration = registration;
        this.designerSurface = designerSurface;
        this.treeItem = new DesignerPeerTreeItem(this);
    }

    abstract getBoundingRect(): Rect;
    abstract getCardObjectBoundingRect(): Rect;

    changed(updatePropertySheet: boolean) {
        if (this.onChanged) {
            this.onChanged(this, updatePropertySheet);
        }
    }

    getTreeItemText(): string {
        return this.internalGetTreeItemText();
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

        actionSet.separator = true;

        result.addItem(actionSet);

        return result;
    }

    scrollIntoView() {
        if (this.renderedElement) {
            this.renderedElement.scrollIntoView();
        }

        if (this.treeItem && this.treeItem.renderedElement) {
            this.treeItem.renderedElement.scrollIntoView();
        }
    }

    get parent(): DesignerPeer {
        return this._parent;
    }

    set parent(value: DesignerPeer) {
        this._parent = value;

        if (this.onParentChanged) {
            this.onParentChanged(this);
        }
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

export abstract class PropertyEditor {
    abstract render(peer: DesignerPeer): Adaptive.CardElement;
}

export abstract class SingleInputPropertyEditor extends PropertyEditor {
    protected abstract createInput(): Adaptive.Input;

    protected getPropertyValue(peer: DesignerPeer): any {
        return peer.getCardObject()[this.propertyName];
    }

    protected setPropertyValue(peer: DesignerPeer, value: string) {
        peer.getCardObject()[this.propertyName] = value;        
    }

    render(peer: DesignerPeer, updatePropertySheet: boolean = false): Adaptive.CardElement {
        let leftColumn = new Adaptive.Column();
        leftColumn.width = new Adaptive.SizeAndUnit(100, Adaptive.SizeUnit.Pixel);
        leftColumn.verticalContentAlignment = Adaptive.VerticalAlignment.Center;
    
        let rightColumn = new Adaptive.Column();
        rightColumn.width = "stretch";
        rightColumn.verticalContentAlignment = Adaptive.VerticalAlignment.Center;
    
        let columnSet = new Adaptive.ColumnSet();
    
        /*
        if (separator) {
            columnSet.spacing = Adaptive.Spacing.Large;
            columnSet.separator = true;
        }
        else {
            columnSet.spacing = Adaptive.Spacing.Small;
        }
        */

        columnSet.spacing = Adaptive.Spacing.Small;
    
        columnSet.addColumn(leftColumn);
        columnSet.addColumn(rightColumn);

        let label = new Adaptive.TextBlock();
        label.horizontalAlignment = Adaptive.HorizontalAlignment.Right;
        label.wrap = true;
        label.text = this.label;

        let input = this.createInput();
        input.defaultValue = this.getPropertyValue(peer);
        input.onValueChanged = () => {
            this.setPropertyValue(peer, input.value);

            peer.changed(updatePropertySheet);
        }
    
        leftColumn.addItem(label);
        rightColumn.addItem(input);

        return columnSet;
    }

    constructor(readonly propertyName: string, readonly label: string) {
        super();
    }
}

export class StringPropertyEditor extends SingleInputPropertyEditor {
    protected createInput(): Adaptive.Input {
        let input = new Adaptive.TextInput();
        input.placeholder = this.placeholder;
        input.isMultiline = this.isMultiline;

        return input;
    }

    constructor(
        readonly propertyName: string,
        readonly label: string,
        readonly isMultiline: boolean = false,
        readonly placeholder: string = "(not set)") {
        super(propertyName, label);
    }
}

export class NumberPropertyEditor extends SingleInputPropertyEditor {
    protected setPropertyValue(peer: DesignerPeer, value: string) {
        try {
            peer.getCardObject()[this.propertyName] = parseFloat(value);
        }
        catch {
            peer.getCardObject()[this.propertyName] = this.defaultValue;
        }
    }

    protected createInput(): Adaptive.Input {
        let input = new Adaptive.NumberInput();
        input.placeholder = this.placeholder;

        return input;
    }

    constructor(
        readonly propertyName: string,
        readonly label: string,
        readonly defaultValue: number | undefined = undefined,
        readonly placeholder: string = "(not set)") {
        super(propertyName, label);
    }
}

export class ObjectPropertyEditor extends StringPropertyEditor {
    protected getPropertyValue(peer: DesignerPeer): any {
        return JSON.stringify(peer.getCardObject()[this.propertyName]);
    }

    protected setPropertyValue(peer: DesignerPeer, value: string) {
        peer.getCardObject()[this.propertyName] = JSON.parse(value);
    }
}

export class CustomCardObjectPropertyEditor extends StringPropertyEditor {
    protected getPropertyValue(peer: DesignerPeer): any {
        return peer.getCardObject().getCustomProperty(this.propertyName);
    }

    protected setPropertyValue(peer: DesignerPeer, value: string) {
        peer.getCardObject().setCustomProperty(this.propertyName, value);
    }
}

export class BooleanPropertyEditor extends SingleInputPropertyEditor {
    protected getPropertyValue(peer: DesignerPeer): any {
        let v = peer.getCardObject()[this.propertyName];

        return typeof v === "boolean" ? v.toString() : "false";
    }

    protected setPropertyValue(peer: DesignerPeer, value: string) {
        peer.getCardObject()[this.propertyName] = value == "true"; 
    }

    protected createInput(): Adaptive.Input {
        return new Adaptive.ToggleInput();
    }
}

export class ChoicePropertyEditor extends SingleInputPropertyEditor {
    protected createInput(): Adaptive.Input {
        let input = new Adaptive.ChoiceSetInput();
        input.isCompact = true;
        input.placeholder = this.placeholder;

        for (let choice of this.choices) {
            input.choices.push(new Adaptive.Choice(choice.name, choice.value));
        }

        return input;
    }

    constructor(
        readonly propertyName: string,
        readonly label: string,
        readonly choices: INameValuePair[],
        readonly placeholder: string = "(not set)") {
        super(propertyName, label);
    }
}

export class HeightPropertyEditor extends ChoicePropertyEditor {
    protected setPropertyValue(peer: DesignerPeer, value: string) {
        let processedValue: string;

        switch (value) {
            case "auto":
            case "stretch":
                processedValue = value;
                break;
            default:
                processedValue = "auto";
                break;
        }

        peer.getCardObject()[this.propertyName] = processedValue; 
    }
}

export class ActionPropertyEditor extends SingleInputPropertyEditor {
    protected getPropertyValue(peer: DesignerPeer): any {
        let action = <Adaptive.Action>peer.getCardObject()[this.propertyName];

        return action ? action.getJsonTypeName() : "none";
    }

    protected setPropertyValue(peer: DesignerPeer, value: string) {
        peer.getCardObject()[this.propertyName] = parseInt(value, 10);

        if (value == "none") {
            peer.getCardObject()[this.propertyName] = null;
        }
        else {
            peer.getCardObject()[this.propertyName] = Adaptive.AdaptiveCard.actionTypeRegistry.createInstance(value);
        }
    }

    protected createInput(): Adaptive.Input {
        let input = new Adaptive.ChoiceSetInput();
        input.isCompact = true;
        input.placeholder = this.placeholder;

        input.choices.push(new Adaptive.Choice("(not set)", "none"));
    
        for (var i = 0; i < Adaptive.AdaptiveCard.actionTypeRegistry.getItemCount(); i++) {
            let actionType = Adaptive.AdaptiveCard.actionTypeRegistry.getItemAt(i).typeName;
            let doAddActionType = this.forbiddenActionTypes ? this.forbiddenActionTypes.indexOf(actionType) < 0 : true;
    
            if (doAddActionType) {
                let choice = new Adaptive.Choice(actionType, actionType);
    
                input.choices.push(choice);
            }
        }

        return input;
    }

    render(peer: DesignerPeer, updatePropertySheet: boolean = false): Adaptive.CardElement {
        let renderedSingleInput = super.render(peer, updatePropertySheet);

        let container = new Adaptive.Container();

        let header = addHeader(container, this.title);
        header.separator = true;

        container.addItem(renderedSingleInput);
    
        return container;
    }

    constructor(
        readonly title: string,
        readonly propertyName: string,
        readonly label: string,
        readonly forbiddenActionTypes: string[] = [],
        readonly placeholder: string = "(not set)") {
        super(propertyName, label);
    }
}

export class EnumPropertyEditor extends SingleInputPropertyEditor {
    protected setPropertyValue(peer: DesignerPeer, value: string) {
        peer.getCardObject()[this.propertyName] = parseInt(value, 10);
    }

    protected createInput(): Adaptive.Input {
        let input = new Adaptive.ChoiceSetInput();
        input.isCompact = true;
        input.placeholder = this.placeholder;

        for (let key in this.enumType) {
            let v = parseInt(key, 10);

            if (!isNaN(v)) {
                input.choices.push(new Adaptive.Choice(this.enumType[key], key));
            }
        }

        return input;
    }

    constructor(
        readonly propertyName: string,
        readonly label: string,
        readonly enumType: { [s: number]: string },
        readonly placeholder: string = "(not set)") {
        super(propertyName, label);
    }
}

interface INameValuePair {
    name: string;
    value: string;
}

class NameValuePairPropertyEditor extends PropertyEditor {
    private changed(peer: DesignerPeer, nameValuePairs: INameValuePair[], refreshPropertySheet: boolean) {
        peer.getCardObject()[this.collectionPropertyName] = [];

        for (let nameValuePair of nameValuePairs) {
            let item = this.createCollectionItem(nameValuePair.name, nameValuePair.value);

            peer.getCardObject()[this.collectionPropertyName].push(item);
        }

        peer.changed(refreshPropertySheet);
    }

    render(peer: DesignerPeer): Adaptive.CardElement {
        let result = new Adaptive.Container();

        let titleTextBlock = new Adaptive.TextBlock();
        titleTextBlock.text = "**" + this.title + "**";

        result.addItem(titleTextBlock);

        let collection = peer.getCardObject()[this.collectionPropertyName];

        if (!Array.isArray(collection)) {
            throw new Error("The " + this.collectionPropertyName + " property on " + peer.getCardObject().getJsonTypeName() + " either doesn't exist or isn't an array.")
        }

        let nameValuePairs: INameValuePair[] = [];

        for (let pair of collection) {
            nameValuePairs.push(
                {
                    name: pair[this.namePropertyName],
                    value: pair[this.valuePropertyName]
                }
            )
        }

        if (nameValuePairs.length == 0) {
            let messageTextBlock = new Adaptive.TextBlock();
            messageTextBlock.spacing = Adaptive.Spacing.Small;
            messageTextBlock.text = this.messageIfEmpty;

            result.addItem(messageTextBlock);
        }
        else {
            for (let i = 0; i < nameValuePairs.length; i++) {
                let textInput = new Adaptive.TextInput();
                textInput.placeholder = this.namePropertyLabel;
                textInput.defaultValue = nameValuePairs[i].name;
                textInput.onValueChanged = (sender) => {
                    nameValuePairs[i].name = sender.value;

                    this.changed(peer, nameValuePairs, false);
                };

                let nameColumn = new Adaptive.Column("stretch");
                nameColumn.addItem(textInput);

                textInput = new Adaptive.TextInput();
                textInput.placeholder = this.valuePropertyLabel;
                textInput.defaultValue = nameValuePairs[i].value;
                textInput.onValueChanged = (sender) => {
                    nameValuePairs[i].value = sender.value;

                    this.changed(peer, nameValuePairs, false);
                };

                let valueColumn = new Adaptive.Column("stretch");
                valueColumn.spacing = Adaptive.Spacing.Small;
                valueColumn.addItem(textInput);

                let removeAction = new Adaptive.SubmitAction();
                removeAction.title = "X";
                removeAction.onExecute = (sender) => {
                    nameValuePairs.splice(i, 1);

                    this.changed(peer, nameValuePairs, true);
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
            nameValuePairs.push({ name: "", value: "" });

            this.changed(peer, nameValuePairs, true);
        }

        let actionSet = new Adaptive.ActionSet();
        actionSet.spacing = Adaptive.Spacing.Small;
        actionSet.addAction(addAction);

        result.addItem(actionSet);

        return result;
    }

    constructor(
        readonly collectionPropertyName: string,
        readonly namePropertyName: string,
        readonly valuePropertyName: string,
        readonly createCollectionItem: (name: string, value: string) => any,
        readonly title: string = "Name/value pairs",
        readonly namePropertyLabel: string = "Name",
        readonly valuePropertyLabel: string = "Value",
        readonly addButtonTitle: string = "Add",
        readonly messageIfEmpty: string = "This collection is empty") {
        super();
    }
}

export class ActionPeer extends DesignerPeer {
    static readonly idProperty = new StringPropertyEditor("id", "Id");
    static readonly titleProperty = new StringPropertyEditor("title", "Title");
    static readonly styleProperty = new ChoicePropertyEditor(
        "style",
        "Style",
        [
            { name: "Default", value: Adaptive.ActionStyle.Default },
            { name: "Positive", value: Adaptive.ActionStyle.Positive },
            { name: "Destructive", value: Adaptive.ActionStyle.Destructive }
        ]);
    static readonly iconUrlProperty = new StringPropertyEditor("iconUrl", "Icon URL");

    protected _action: Adaptive.Action;

    protected doubleClick(e: MouseEvent) {
        super.doubleClick(e);

        this.action.renderedElement.click();
    }

    protected internalRemove(): boolean {
        return this.action.remove();
    }

    constructor(
        parent: DesignerPeer,
        designerSurface: CardDesignerSurface,
        registration: DesignerPeerRegistrationBase,
        action: Adaptive.Action) {
        super(parent, designerSurface, registration);

        this._action = action;
    }

    protected internalGetTreeItemText(): string {
        if (this.action.title && this.action.title != "") {
            return this.action.title;
        }
        else {
            return super.internalGetTreeItemText();
        }
    }

    getCardObject(): Adaptive.CardObject {
        return this.action;
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

        card.addItem(ActionPeer.idProperty.render(this));
        card.addItem(ActionPeer.titleProperty.render(this));
        card.addItem(ActionPeer.styleProperty.render(this));
        card.addItem(ActionPeer.iconUrlProperty.render(this));
    }

    get action(): Adaptive.Action {
        return this._action;
    }
}

export abstract class TypedActionPeer<TAction extends Adaptive.Action> extends ActionPeer {
    constructor(
        parent: DesignerPeer,
        designerSurface: CardDesignerSurface,
        registration: DesignerPeerRegistrationBase,
        action: TAction) {
        super(parent, designerSurface, registration, action);
    }

    get action(): TAction {
        return <TAction>this._action;
    }
}

export class HttpActionPeer extends TypedActionPeer<Adaptive.HttpAction> {
    static readonly ignoreInputValidationProperty = new BooleanPropertyEditor("ignoreInputValidation", "Ignore input validation");
    static readonly methodProperty = new ChoicePropertyEditor(
        "method",
        "Method",
        [
            { name: "GET", value: "GET" },
            { name: "POST", value: "POST" }
        ]);
    static readonly urlProperty = new StringPropertyEditor("url", "Url");
    static readonly bodyProperty = new StringPropertyEditor("body", "Body", true);
    static readonly headersProperty = new NameValuePairPropertyEditor(
        "headers",
        "name",
        "value",
        (name: string, value: string) => { return new Adaptive.HttpHeader(name, value); },
        "HTTP headers",
        "Name",
        "Value",
        "Add a new header",
        "This action has no header.");

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        if (Adaptive.AdaptiveCard.useBuiltInInputValidation) {
            card.addItem(HttpActionPeer.ignoreInputValidationProperty.render(this));
        }

        card.addItem(HttpActionPeer.methodProperty.render(this, true));
        card.addItem(HttpActionPeer.urlProperty.render(this));

        if (this.action.method && this.action.method.toLowerCase() == "post") {
            card.addItem(HttpActionPeer.bodyProperty.render(this));
        }

        card.addItem(HttpActionPeer.headersProperty.render(this));
    }
}

export class SubmitActionPeer extends TypedActionPeer<Adaptive.SubmitAction> {
    static readonly ignoreInputValidationProperty = new BooleanPropertyEditor("ignoreInputValidation", "Ignore input validation");
    static readonly dataProperty = new ObjectPropertyEditor("data", "Data");

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(SubmitActionPeer.ignoreInputValidationProperty.render(this));
        card.addItem(SubmitActionPeer.dataProperty.render(this));
    }
}

export class OpenUrlActionPeer extends TypedActionPeer<Adaptive.OpenUrlAction> {
    static readonly urlProperty = new StringPropertyEditor("url", "Url");

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(OpenUrlActionPeer.urlProperty.render(this));
    }
}

export class ShowCardActionPeer extends TypedActionPeer<Adaptive.ShowCardAction> {
    protected getToolTip(): string {
        return "Double click to open/close";
    }
}

export class ToggleVisibilityActionPeer extends TypedActionPeer<Adaptive.ToggleVisibilityAction> {
}

export class CardElementPeer extends DesignerPeer {
    protected _cardElement: Adaptive.CardElement;

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

    protected internalAddBackgroundImageProperties(card: Adaptive.AdaptiveCard, backgroundImage: Adaptive.BackgroundImage) {
        let header = addHeader(card, "Background image");
        header.separator = true;

        let url = addLabelAndInput(card, "URL:", Adaptive.TextInput);
        url.input.placeholder = "(not set)";

        if (backgroundImage) {
            url.input.defaultValue = backgroundImage.url;
        }

        url.input.onValueChanged = () => {
            backgroundImage.url = url.input.value;

            this.changed(false);
        }

        let fillMode = addLabelAndInput(card, "Fill mode:", Adaptive.ChoiceSetInput);
        fillMode.input.isCompact = true;
        fillMode.input.placeholder = "(not set)";
        fillMode.input.choices.push(new Adaptive.Choice("Cover", Adaptive.FillMode.Cover.toString()));
        fillMode.input.choices.push(new Adaptive.Choice("Repeat horizontally", Adaptive.FillMode.RepeatHorizontally.toString()));
        fillMode.input.choices.push(new Adaptive.Choice("Repeat vertically", Adaptive.FillMode.RepeatVertically.toString()));
        fillMode.input.choices.push(new Adaptive.Choice("Repeat", Adaptive.FillMode.Repeat.toString()));

        if (backgroundImage) {
            fillMode.input.defaultValue = backgroundImage.fillMode.toString();
        }

        fillMode.input.onValueChanged = () => {
            if (horizontalAlignment.input.value) {
                backgroundImage.fillMode = <Adaptive.FillMode>parseInt(fillMode.input.value);
            }

            this.changed(false);
        }

        let horizontalAlignment = addLabelAndInput(card, "Horizontal alignment:", Adaptive.ChoiceSetInput);
        horizontalAlignment.input.isCompact = true;
        horizontalAlignment.input.placeholder = "(not set)";
        horizontalAlignment.input.choices.push(new Adaptive.Choice("Left", Adaptive.HorizontalAlignment.Left.toString()));
        horizontalAlignment.input.choices.push(new Adaptive.Choice("Center", Adaptive.HorizontalAlignment.Center.toString()));
        horizontalAlignment.input.choices.push(new Adaptive.Choice("Right", Adaptive.HorizontalAlignment.Right.toString()));

        if (backgroundImage) {
            horizontalAlignment.input.defaultValue = backgroundImage.horizontalAlignment.toString();
        }

        horizontalAlignment.input.onValueChanged = () => {
            if (horizontalAlignment.input.value) {
                backgroundImage.horizontalAlignment = <Adaptive.HorizontalAlignment>parseInt(horizontalAlignment.input.value);
            }

            this.changed(false);
        }

        let verticalAlignment = addLabelAndInput(card, "Vertical alignment:", Adaptive.ChoiceSetInput);
        verticalAlignment.input.isCompact = true;
        verticalAlignment.input.placeholder = "(not set)";
        verticalAlignment.input.choices.push(new Adaptive.Choice("Top", Adaptive.VerticalAlignment.Top.toString()));
        verticalAlignment.input.choices.push(new Adaptive.Choice("Center", Adaptive.VerticalAlignment.Center.toString()));
        verticalAlignment.input.choices.push(new Adaptive.Choice("Bottom", Adaptive.VerticalAlignment.Bottom.toString()));

        if (backgroundImage) {
            verticalAlignment.input.defaultValue = backgroundImage.verticalAlignment.toString();
        }

        verticalAlignment.input.onValueChanged = () => {
            if (verticalAlignment.input.value) {
                backgroundImage.verticalAlignment = <Adaptive.VerticalAlignment>parseInt(verticalAlignment.input.value);
            }

            this.changed(false);
        }
    }

    protected internalUpdateCssStyles() {
        super.internalUpdateCssStyles();

        if (this.cardElement.isVisible) {
            this.renderedElement.classList.remove("invisible");
        }
        else {
            this.renderedElement.classList.add("invisible");
        }
    }
    
    constructor(
        parent: DesignerPeer,
        designerSurface: CardDesignerSurface,
        registration: DesignerPeerRegistrationBase,
        cardElement: Adaptive.CardElement) {
        super(parent, designerSurface, registration);

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

    getTreeItemText(): string {
        let text = super.getTreeItemText();
        
        if (this.cardElement.isVisible) {
            return text;
        }
        else {
            let result = "Hidden";
            
            if (text) {
                result += " - " + text;
            }

            return result;
        }
    }

    getCardObject(): Adaptive.CardObject {
        return this.cardElement;
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

    static readonly dataContextProperty = new CustomCardObjectPropertyEditor("$data", "Data context");
    static readonly whenProperty = new CustomCardObjectPropertyEditor("$when", "Only show when");
    static readonly idProperty = new StringPropertyEditor("id", "Id");
    static readonly isVisibleProperty = new BooleanPropertyEditor("isVisible", "Initially visible");
    static readonly spacingProperty = new EnumPropertyEditor("spacing", "Spacing", Adaptive.Spacing);
    static readonly separatorProperty = new BooleanPropertyEditor("separator", "Separator");
    static readonly horizontalAlignmentProperty = new EnumPropertyEditor("horizontalAlignment", "Horizontal alignment", Adaptive.HorizontalAlignment);
    static readonly heightProperty = new HeightPropertyEditor(
        "height",
        "Height",
        [
            { name: "Automatic", value: "auto" },
            { name: "Stretch", value: "stretch" }
        ]);

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        if (includeHeader) {
            addHeader(card, this.cardElement.getJsonTypeName());
        }

        card.addItem(CardElementPeer.dataContextProperty.render(this));
        card.addItem(CardElementPeer.whenProperty.render(this));

        let getExcludedProperties = this.getExcludedProperties();

        if (getExcludedProperties.indexOf("id") < 0) {
            card.addItem(CardElementPeer.idProperty.render(this));
        }

        if (getExcludedProperties.indexOf("isVisible") < 0) {
            card.addItem(CardElementPeer.isVisibleProperty.render(this));
        }

        if (getExcludedProperties.indexOf("spacing") < 0) {
            card.addItem(CardElementPeer.spacingProperty.render(this));
        }

        if (getExcludedProperties.indexOf("separator") < 0) {
            card.addItem(CardElementPeer.separatorProperty.render(this));
        }

        if (getExcludedProperties.indexOf("horizontalAlignment") < 0) {
            card.addItem(CardElementPeer.horizontalAlignmentProperty.render(this));
        }

        if (getExcludedProperties.indexOf("height") < 0) {
            card.addItem(CardElementPeer.heightProperty.render(this));
        }
    }

    get cardElement(): Adaptive.CardElement {
        return this._cardElement;
    }
}

export abstract class TypedCardElementPeer<TCardElement extends Adaptive.CardElement> extends CardElementPeer {
    constructor(
        parent: DesignerPeer,
        designerSurface: CardDesignerSurface,
        registration: DesignerPeerRegistrationBase,
        cardElement: TCardElement) {
        super(parent, designerSurface, registration, cardElement);
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
        return [ "id", "isVisible", "horizontalAlignment", "separator", "height", "spacing" ];
    }

    isDraggable(): boolean {
        return false;
    }

    canBeRemoved(): boolean {
        return false;
    }

    static readonly langProperty = new StringPropertyEditor("lang", "Language");
    static readonly fallbackTextProperty = new StringPropertyEditor("fallbackText", "Fallback text", true);
    static readonly speakProperty = new StringPropertyEditor("speak", "Speak");

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, updatePropertySheet: boolean) {
        super.internalAddPropertySheetEntries(card, updatePropertySheet);

        card.addItem(AdaptiveCardPeer.langProperty.render(this));
        card.addItem(AdaptiveCardPeer.fallbackTextProperty.render(this));
        card.addItem(AdaptiveCardPeer.speakProperty.render(this));
        card.addItem(ContainerPeer.minHeightProperty.render(this));
        card.addItem(ContainerPeer.verticalContentAlignmentProperty.render(this));

        this.internalAddBackgroundImageProperties(card, this.cardElement.backgroundImage);

        card.addItem(ContainerPeer.selectActionProperty.render(this, true));

        if (this.cardElement.selectAction) {
            let selectActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
            selectActionPeer.internalAddPropertySheetEntries(card, false);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
        }
    }
}

export class ContainerStylePropertyEditor extends ChoicePropertyEditor {
    protected getPropertyValue(peer: DesignerPeer): any {
        let currentStyle = peer.getCardObject()[this.propertyName];

        return currentStyle ? currentStyle.toString() : "not_set";
    }

    protected setPropertyValue(peer: DesignerPeer, value: string) {
        if (value == "not_set") {
            peer.getCardObject()[this.propertyName] = null;
        }
        else {
            peer.getCardObject()[this.propertyName] = value;
        }
    }

    constructor(
        readonly propertyName: string,
        readonly label: string,
        readonly placeholder: string = "(not set)") {
        super(
            propertyName,
            label,
            [
                { name: "(not set)", value: "not_set" },
                { name: "Default", value: "default" },
                { name: "Emphasis", value: "emphasis" },
                { name: "Accent", value: "accent" },
                { name: "Good", value: "good" },
                { name: "Attention", value: "attention" },
                { name: "Warning", value: "warning" }
            ],
            placeholder);
    }
}

export class ColumnPeer extends TypedCardElementPeer<Adaptive.Column> {
    protected isContainer(): boolean {
        return true;
    }

    protected internalGetTreeItemText(): string {
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

        card.addItem(ContainerPeer.minHeightProperty.render(this));
        card.addItem(ContainerPeer.verticalContentAlignmentProperty.render(this));
        card.addItem(ContainerPeer.styleProperty.render(this));
        card.addItem(ContainerPeer.bleedProperty.render(this));

        this.internalAddBackgroundImageProperties(card, this.cardElement.backgroundImage);

        card.addItem(ContainerPeer.selectActionProperty.render(this, true));

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

    protected internalGetTreeItemText(): string {
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

        card.addItem(ContainerPeer.minHeightProperty.render(this));
        card.addItem(ContainerPeer.styleProperty.render(this));
        card.addItem(ContainerPeer.bleedProperty.render(this));
        card.addItem(ContainerPeer.selectActionProperty.render(this, true));

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
    static readonly selectActionProperty = new ActionPropertyEditor("Select action", "selectAction", "Action type", [ Adaptive.ShowCardAction.JsonTypeName ]);
    static readonly minHeightProperty = new NumberPropertyEditor("minPixelHeight", "Minimum height in pixels");
    static readonly verticalContentAlignmentProperty = new EnumPropertyEditor("verticalContentAlignment", "Vertical content alignment", Adaptive.VerticalAlignment);
    static readonly styleProperty = new ContainerStylePropertyEditor("style", "Style");
    static readonly bleedProperty = new BooleanPropertyEditor("bleed", "Bleed");

    protected isContainer(): boolean {
        return true;
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(ContainerPeer.minHeightProperty.render(this));
        card.addItem(ContainerPeer.verticalContentAlignmentProperty.render(this));
        card.addItem(ContainerPeer.styleProperty.render(this));
        card.addItem(ContainerPeer.bleedProperty.render(this));

        this.internalAddBackgroundImageProperties(card, this.cardElement.backgroundImage);

        card.addItem(ContainerPeer.selectActionProperty.render(this, true));

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

                        popupMenu.popup(clickedElement);
                    }
                })
        );
    }
}

export class ImageSetPeer extends TypedCardElementPeer<Adaptive.ImageSet> {
    static readonly ImageSizeProperty = new EnumPropertyEditor("imageSize", "Image size", Adaptive.Size);

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(ImageSetPeer.ImageSizeProperty.render(this));
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

        let url = addLabelAndInput(card, "Url:", Adaptive.TextInput);
        url.input.defaultValue = this.cardElement.url;
        url.input.onValueChanged = () => {
            this.cardElement.url = url.input.value;

            this.changed(false);
        }

        let altText = addLabelAndInput(card, "Alternate text:", Adaptive.TextInput);
        altText.input.placeholder = "(not set)";
        altText.input.defaultValue = this.cardElement.altText;
        altText.input.onValueChanged = () => {
            this.cardElement.altText = altText.input.value;

            this.changed(false);
        }

        if (!this.isParentImageSet) {
            let size = addLabelAndInput(card, "Size:", Adaptive.ChoiceSetInput);
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

            let width = addLabelAndInput(card, "Width in pixels:", Adaptive.TextInput);
            width.input.placeholder = "(not set)";

            if (this.cardElement.pixelWidth) {
                width.input.defaultValue = this.cardElement.pixelWidth.toString();
            }

            width.input.onValueChanged = () => {
                try {
                    this.cardElement.pixelWidth = parseInt(width.input.value);
                }
                catch (e) {
                    this.cardElement.pixelWidth = null;
                }

                this.changed(false);
            }

            let height = addLabelAndInput(card, "Height in pixels:", Adaptive.TextInput);
            height.input.placeholder = "(not set)";

            if (this.cardElement.pixelHeight) {
                height.input.defaultValue = this.cardElement.pixelHeight.toString();
            }

            height.input.onValueChanged = () => {
                try {
                    this.cardElement.pixelHeight = parseInt(height.input.value);
                }
                catch (e) {
                    this.cardElement.pixelHeight = null;
                }

                this.changed(false);
            }

            let style = addLabelAndInput(card, "Style:", Adaptive.ChoiceSetInput);
            style.input.isCompact = true;
            style.input.choices.push(new Adaptive.Choice("Default", Adaptive.ImageStyle.Default.toString()));
            style.input.choices.push(new Adaptive.Choice("Person", Adaptive.ImageStyle.Person.toString()));
            style.input.defaultValue = this.cardElement.style.toString();
            style.input.onValueChanged = () => {
                this.cardElement.style = <Adaptive.ImageStyle>parseInt(style.input.value);

                this.changed(false);
            }

            let backgroundColor = addLabelAndInput(card, "Background color:", Adaptive.TextInput);
            backgroundColor.input.placeholder = "(not set) Format: #RRGGBB";
            backgroundColor.input.defaultValue = this.cardElement.backgroundColor;
            backgroundColor.input.onValueChanged = () => {
                this.cardElement.backgroundColor = backgroundColor.input.value;

                this.changed(false);
            }

            card.addItem(ContainerPeer.selectActionProperty.render(this, true));

            if (this.cardElement.selectAction) {
                let selectActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
                selectActionPeer.internalAddPropertySheetEntries(card, false);
                selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
            }
        }
    }
}

export class MediaPeer extends TypedCardElementPeer<Adaptive.Media> {
    static readonly altTextProperty = new StringPropertyEditor("altText", "Alternate text");
    static readonly posterUrlProperty = new StringPropertyEditor("posterUrl", "Poster URL");
    static readonly sourcesProperty = new NameValuePairPropertyEditor(
        "sources",
        "url",
        "mimeType",
        (name: string, value: string) => { return new Adaptive.MediaSource(name, value); },
        "Sources",
        "URL",
        "MIME type",
        "Add a new source",
        "No source has been defined.");

    protected internalGetTreeItemText(): string {
        if (this.cardElement.selectedMediaType == "audio") {
            return "audio";
        }
        else if (this.cardElement.selectedMediaType == "video") {
            return "video";
        }
        else {
            return super.internalGetTreeItemText();
        }
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(MediaPeer.altTextProperty.render(this));
        card.addItem(MediaPeer.posterUrlProperty.render(this));
        card.addItem(MediaPeer.sourcesProperty.render(this));
    }
}

export class FactSetPeer extends TypedCardElementPeer<Adaptive.FactSet> {
    static readonly factsProperty = new NameValuePairPropertyEditor(
        "facts",
        "name",
        "value",
        (name: string, value: string) => { return new Adaptive.Fact(name, value); },
        "Facts",
        "Name",
        "Value",
        "Add a new fact",
        "This FactSet is empty.");

    protected getExcludedProperties(): Array<string> {
        return [ "horizontalAlignment" ];
    }

    protected internalGetTreeItemText(): string {
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

    initializeCardElement() {
        super.initializeCardElement();

        this.cardElement.facts.push(
            new Adaptive.Fact("Fact 1", "Value 1"),
            new Adaptive.Fact("Fact 2", "Value 2")
        );
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(FactSetPeer.factsProperty.render(this));
    }
}

export abstract class InputPeer<TInput extends Adaptive.Input> extends TypedCardElementPeer<TInput> {
    static readonly titleProperty = new StringPropertyEditor("title", "Title");

    protected getExcludedProperties(): Array<string> {
        return [ "horizontalAlignment", "height" ];
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(InputPeer.titleProperty.render(this));

        let validationNecessity = addLabelAndInput(card, "Necessity:", Adaptive.ChoiceSetInput);
        validationNecessity.input.isCompact = true;
        validationNecessity.input.choices.push(new Adaptive.Choice("Optional", Adaptive.InputValidationNecessity.Optional.toString()));
        validationNecessity.input.choices.push(new Adaptive.Choice("Required", Adaptive.InputValidationNecessity.Required.toString()));
        validationNecessity.input.choices.push(new Adaptive.Choice("Required with visual cue", Adaptive.InputValidationNecessity.RequiredWithVisualCue.toString()));
        validationNecessity.input.defaultValue = this.cardElement.validation.necessity.toString();
        validationNecessity.input.onValueChanged = () => {
            this.cardElement.validation.necessity = <Adaptive.InputValidationNecessity>parseInt(validationNecessity.input.value);

            this.changed(false);
        }

        let validationErrorMessage = addLabelAndInput(card, "Error message:", Adaptive.TextInput);
        validationErrorMessage.input.placeholder = "(not set)";
        validationErrorMessage.input.defaultValue = this.cardElement.validation.errorMessage;
        validationErrorMessage.input.onValueChanged = () => {
            this.cardElement.validation.errorMessage = validationErrorMessage.input.value;

            this.changed(false);
        }
    }

    initializeCardElement() {
        super.initializeCardElement();

        this.cardElement.title = "New Input.Toggle";
    }
}

export class TextInputPeer extends InputPeer<Adaptive.TextInput> {
    static readonly placeholderProperty = new StringPropertyEditor("placeholder", "Placeholder");
    static readonly isMultilineProperty = new BooleanPropertyEditor("isMultiline", "Multi-line");
    static readonly styleProperty = new EnumPropertyEditor("style", "Style", Adaptive.InputTextStyle);
    static readonly defaultValueProperty = new StringPropertyEditor("defaultValue", "Default value");
    static readonly inlineActionProperty = new ActionPropertyEditor("Inline action", "inlineAction", "Action type", [ Adaptive.ShowCardAction.JsonTypeName ]);

    initializeCardElement() {
        super.initializeCardElement();

        this.cardElement.placeholder = "Placeholder text";
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(TextInputPeer.placeholderProperty.render(this));
        card.addItem(TextInputPeer.isMultilineProperty.render(this, true));

        if (!this.cardElement.isMultiline) {
            card.addItem(TextInputPeer.styleProperty.render(this));
        }

        card.addItem(TextInputPeer.inlineActionProperty.render(this, true));

        if (this.cardElement.inlineAction) {
            let inlineActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.inlineAction);
            inlineActionPeer.internalAddPropertySheetEntries(card, false);
            inlineActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
        }

        card.addItem(TextInputPeer.defaultValueProperty.render(this));
    }
}

export class NumberInputPeer extends InputPeer<Adaptive.NumberInput> {
    static readonly placeholderProperty = new StringPropertyEditor("placeholder", "Placeholder");
    static readonly defaultValueProperty = new StringPropertyEditor("defaultValue", "Default value");
    static readonly minProperty = new StringPropertyEditor("min", "Maximum value");
    static readonly maxProperty = new StringPropertyEditor("max", "Maximum value");

    initializeCardElement() {
        super.initializeCardElement();

        this.cardElement.placeholder = "Placeholder text";
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(NumberInputPeer.placeholderProperty.render(this));
        card.addItem(NumberInputPeer.defaultValueProperty.render(this));
        card.addItem(NumberInputPeer.minProperty.render(this));
        card.addItem(NumberInputPeer.maxProperty.render(this));
    }
}

export class DateInputPeer extends InputPeer<Adaptive.DateInput> {
    static readonly defaultValueProperty = new StringPropertyEditor("defaultValue", "Default value");
    static readonly minProperty = new StringPropertyEditor("min", "Maximum value");
    static readonly maxProperty = new StringPropertyEditor("max", "Maximum value");

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(DateInputPeer.defaultValueProperty.render(this));
        card.addItem(DateInputPeer.minProperty.render(this));
        card.addItem(DateInputPeer.maxProperty.render(this));
    }
}

export class TimeInputPeer extends InputPeer<Adaptive.TimeInput> {
    static readonly defaultValueProperty = new StringPropertyEditor("defaultValue", "Default value");
    static readonly minProperty = new StringPropertyEditor("min", "Maximum value");
    static readonly maxProperty = new StringPropertyEditor("max", "Maximum value");

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(TimeInputPeer.defaultValueProperty.render(this));
        card.addItem(TimeInputPeer.minProperty.render(this));
        card.addItem(TimeInputPeer.maxProperty.render(this));
    }
}

export class ToggleInputPeer extends InputPeer<Adaptive.ToggleInput> {
    static readonly valueOnProperty = new StringPropertyEditor("valueOn", "Value when on");
    static readonly valueOffProperty = new StringPropertyEditor("valueOff", "Value when off");
    static readonly wrapProperty = new BooleanPropertyEditor("wrap", "Wrap");
    static readonly defaultValueProperty = new StringPropertyEditor("defaultValue", "Default value");

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(ToggleInputPeer.valueOnProperty.render(this));
        card.addItem(ToggleInputPeer.valueOffProperty.render(this));
        card.addItem(ToggleInputPeer.wrapProperty.render(this));
        card.addItem(ToggleInputPeer.defaultValueProperty.render(this));
    }
}

export class ChoiceSetInputPeer extends InputPeer<Adaptive.ChoiceSetInput> {
    static readonly placeholderProperty = new StringPropertyEditor("placeholder", "Placeholder");
    static readonly isMultiselectProperty = new BooleanPropertyEditor("isMultiSelect", "Allow multi selection");
    static readonly isCompactProperty = new BooleanPropertyEditor("isCompact", "Compact style");
    static readonly wrapProperty = new BooleanPropertyEditor("wrap", "Wrap");
    static readonly defaultValueProperty = new StringPropertyEditor("defaultValue", "Default value");
    static readonly choicesProperty = new NameValuePairPropertyEditor(
        "choices",
        "name",
        "value",
        (name: string, value: string) => { return new Adaptive.Choice(name, value); },
        "Choices",
        "Title",
        "Value",
        "Add a new choice",
        "This ChoiceSet is empty");

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(ChoiceSetInputPeer.placeholderProperty.render(this));
        card.addItem(ChoiceSetInputPeer.isMultiselectProperty.render(this));
        card.addItem(ChoiceSetInputPeer.isCompactProperty.render(this));
        card.addItem(ChoiceSetInputPeer.wrapProperty.render(this));
        card.addItem(ChoiceSetInputPeer.defaultValueProperty.render(this));
        card.addItem(ChoiceSetInputPeer.choicesProperty.render(this));
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

    protected internalGetTreeItemText(): string {
        return this.cardElement.text;
    }

    getToolTip(): string {
        return "Double click to edit";
    }

    static readonly textProperty = new StringPropertyEditor("text", "Text", true);
    static readonly wrapProperty = new BooleanPropertyEditor("wrap", "Wrap");
    static readonly maxLinesProperty = new NumberPropertyEditor("maxLines", "Maximum lines", 0);
    static readonly fontTypeProperty = new EnumPropertyEditor("fontType", "Font type", Adaptive.FontType);
    static readonly sizeProperty = new EnumPropertyEditor("size", "Size", Adaptive.TextSize);
    static readonly weightProperty = new EnumPropertyEditor("weight", "Weight", Adaptive.TextWeight);
    static readonly colorProperty = new EnumPropertyEditor("color", "Color", Adaptive.TextColor);
    static readonly subtleProperty = new BooleanPropertyEditor("subtle", "Subtle");


    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        card.addItem(TextBlockPeer.textProperty.render(this));
        card.addItem(TextBlockPeer.wrapProperty.render(this));
        card.addItem(TextBlockPeer.maxLinesProperty.render(this));
        card.addItem(TextBlockPeer.fontTypeProperty.render(this));
        card.addItem(TextBlockPeer.sizeProperty.render(this));
        card.addItem(TextBlockPeer.weightProperty.render(this));
        card.addItem(TextBlockPeer.colorProperty.render(this));
        card.addItem(TextBlockPeer.subtleProperty.render(this));
    }

    initializeCardElement() {
        if (!this.cardElement.text || this.cardElement.text == "") {
            this.cardElement.text = "New TextBlock";
        }
    }
}

export class RichTextBlockPeer extends TypedCardElementPeer<Adaptive.RichTextBlock> {
    protected internalGetTreeItemText(): string {
        return this.cardElement.asString();
    }

    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.internalAddPropertySheetEntries(card, includeHeader);

        let infoTextBlock = new Adaptive.TextBlock();
        infoTextBlock.text = "Use the **JSON editor** to edit the text of this RichTextBlock element.";
        infoTextBlock.wrap = true;
        infoTextBlock.spacing = Adaptive.Spacing.Large;
        infoTextBlock.separator = true;
        infoTextBlock.horizontalAlignment = Adaptive.HorizontalAlignment.Center;

        card.addItem(infoTextBlock);
    }

    initializeCardElement() {
        let textRun = new Adaptive.TextRun();
        textRun.text = "New RichTextBlock";

        this.cardElement.addInline(textRun);
    }
}