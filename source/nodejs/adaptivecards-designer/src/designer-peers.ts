// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive  from "adaptivecards";
import * as Controls  from "adaptivecards-controls";
import { DraggableElement } from "./draggable-element";
import { PeerCommand } from "./peer-command";
import { CardDesignerSurface, DesignContext } from "./card-designer-surface";
import { DesignerPeerTreeItem } from "./designer-peer-treeitem";
import { Rect, IPoint } from "./miscellaneous";
import { GlobalSettings } from "./shared";
import { FieldPicker } from "./field-picker";

export abstract class DesignerPeerInplaceEditor {
    onClose: (applyChanges: boolean) => void;

    abstract initialize();
    abstract applyChanges();
    abstract render(): HTMLElement;
}

export abstract class CardElementPeerInplaceEditor<TCardElement extends Adaptive.CardElement> extends DesignerPeerInplaceEditor {
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

export class PropertySheetCategory {
    static readonly DefaultCategory = "__defaultCategory";
    static readonly LayoutCategory = "Layout";
    static readonly StyleCategory = "Style";
    static readonly SelectionAction = "Selection action";
    static readonly InlineAction = "Inline action";
    static readonly Validation = "Validation";

    private _entries: PropertySheetEntry[] = [];

    constructor(readonly name: string) { }

    render(container: Adaptive.Container, context: PropertySheetContext, displayCategoryName: boolean) {
        let entriesToRender: PropertySheetEntry[] = [];

        for (let entry of this._entries) {
            if (Adaptive.isVersionLessOrEqual(entry.targetVersion, context.designContext.targetVersion)) {
                entriesToRender.push(entry);
            }
        }

        if (entriesToRender.length > 0) {
            if (displayCategoryName) {
                let header = new Adaptive.TextBlock();
                header.separator = true;
                header.text = "**" + (this.name === PropertySheetCategory.DefaultCategory ? context.peer.getCardObject().getJsonTypeName() : this.name) + "**";

                container.addItem(header);
            }

            for (let entry of entriesToRender) {
                if (Adaptive.isVersionLessOrEqual(entry.targetVersion, context.designContext.targetVersion)) {
                    container.addItem(entry.render(context));
                }
            }
        }
    }

    add(...entries: PropertySheetEntry[]) {
        this._entries = this._entries.concat(entries);
    }

    remove(...entries: PropertySheetEntry[]) {
        for (let entry of entries) {
            let index: number;

            do {
                let index = this._entries.indexOf(entry);

                if (index >= 0) {
                    this._entries.splice(index, 1);
                }
            } while (index >= 0);
        }
    }

    getEntryAt(index: number): PropertySheetEntry {
        return this._entries[index];
    }

    get length(): number {
        return this._entries.length;
    }
}

export class PropertySheet {
    private _categories: { [key: string]: PropertySheetCategory } = {};

    constructor(readonly displayCategoryNames: boolean = true) {
        this._categories[PropertySheetCategory.DefaultCategory] = new PropertySheetCategory(PropertySheetCategory.DefaultCategory);
        this._categories[PropertySheetCategory.LayoutCategory] = new PropertySheetCategory(PropertySheetCategory.LayoutCategory);
        this._categories[PropertySheetCategory.StyleCategory] = new PropertySheetCategory(PropertySheetCategory.StyleCategory);
    }

    add(categoryName: string, ...entries: PropertySheetEntry[]) {
        let category = this._categories[categoryName];

        if (!category) {
            category = new PropertySheetCategory(categoryName);

            this._categories[categoryName] = category;
        }

        category.add(...entries);
    }

    remove(...entries: PropertySheetEntry[]) {
        for (let categoryName of Object.keys(this._categories)) {
            this._categories[categoryName].remove(...entries);
        }
    }

    render(container: Adaptive.Container, context: PropertySheetContext) {
        for (let categoryName of Object.keys(this._categories)) {
            this._categories[categoryName].render(container, context, this.displayCategoryNames);
        }
    }
}

export class PropertySheetContext {
    private _target: object = undefined;

    constructor(
        readonly designContext: DesignContext,
        readonly peer: DesignerPeer,
        target: object = undefined) {
        this._target = target;
    }

    get target(): object {
        return this._target != undefined ? this._target : this.peer.getCardObject();
    }
}

export abstract class PropertySheetEntry {
    abstract render(context: PropertySheetContext): Adaptive.CardElement;

    constructor(readonly targetVersion: Adaptive.TargetVersion) { }
}

export class SubPropertySheetEntry {
    render(context: PropertySheetContext): Adaptive.CardElement {
        let container = new Adaptive.Container();
        container.spacing = Adaptive.Spacing.Small;

        this.propertySheet.render(container, new PropertySheetContext(
            context.designContext,
            context.peer,
            this.target));

        return container;
    }

    constructor(readonly targetVersion: Adaptive.TargetVersion, readonly target: object, readonly propertySheet: PropertySheet) { }
}

export class CustomPropertySheetEntry extends PropertySheetEntry {
    render(context: PropertySheetContext): Adaptive.CardElement {
        if (this.onRender) {
            return this.onRender(context);
        }
    }

    constructor(readonly targetVersion: Adaptive.TargetVersion, readonly onRender: (context: PropertySheetContext) => Adaptive.CardElement) {
        super(targetVersion);
    }
}

export interface IPropertySheetEditorCommand {
    caption: string;
    onExecute: (sender: SingleInputPropertyEditor, clickedElement: HTMLElement) => void;
}

export abstract class SingleInputPropertyEditor extends PropertySheetEntry {
    protected abstract createInput(context: PropertySheetContext): Adaptive.Input;

    protected getPropertyValue(context: PropertySheetContext): any {
        return context.target[this.propertyName];
    }

    protected setPropertyValue(context: PropertySheetContext, value: string) {
        context.target[this.propertyName] = value;
    }

    protected getAdditionalCommands(context: PropertySheetContext): IPropertySheetEditorCommand[] {
        return [];
    }

    render(context: PropertySheetContext): Adaptive.CardElement {
        let leftColumn = new Adaptive.Column();
        leftColumn.width = new Adaptive.SizeAndUnit(100, Adaptive.SizeUnit.Pixel);
        leftColumn.verticalContentAlignment = Adaptive.VerticalAlignment.Center;

        let rightColumn = new Adaptive.Column();
        rightColumn.width = "stretch";
        rightColumn.verticalContentAlignment = Adaptive.VerticalAlignment.Center;

        let columnSet = new Adaptive.ColumnSet();

        columnSet.spacing = Adaptive.Spacing.Small;

        columnSet.addColumn(leftColumn);
        columnSet.addColumn(rightColumn);

        let label = new Adaptive.TextBlock();
        label.horizontalAlignment = Adaptive.HorizontalAlignment.Right;
        label.wrap = true;
        label.text = this.label;

        let input = this.createInput(context);
        input.onValueChanged = () => {
            this.setPropertyValue(context, input.value);

            context.peer.changed(this.causesPropertySheetRefresh);
        }

        leftColumn.addItem(label);
        rightColumn.addItem(input);

        let additionalCommands = this.getAdditionalCommands(context);

        if (additionalCommands && additionalCommands.length > 0) {
            let commandColumn = new Adaptive.Column();
            commandColumn.width = "auto";
            commandColumn.spacing = Adaptive.Spacing.Small;
            commandColumn.verticalContentAlignment = Adaptive.VerticalAlignment.Center;

            let actionSet = new Adaptive.ActionSet();

            for (let command of additionalCommands) {
                let action = new Adaptive.SubmitAction();
                action.title = command.caption;
                action.onExecute = (sender: Adaptive.Action) => { command.onExecute(this, sender.renderedElement); };

                actionSet.addAction(action);
            }

            commandColumn.addItem(actionSet);
            columnSet.addColumn(commandColumn);
        }

        return columnSet;
    }

    constructor(
        readonly targetVersion: Adaptive.TargetVersion,
        readonly propertyName: string,
        readonly label: string,
        readonly causesPropertySheetRefresh: boolean = false) {
        super(targetVersion);
    }
}

export class StringPropertyEditor extends SingleInputPropertyEditor {
    protected createInput(context: PropertySheetContext): Adaptive.Input {
        let input = new Adaptive.TextInput();
        input.defaultValue = this.getPropertyValue(context);
        input.placeholder = "(not set)";
        input.isMultiline = this.isMultiline;

        return input;
    }

    protected getAdditionalCommands(context: PropertySheetContext): IPropertySheetEditorCommand[] {
        if (GlobalSettings.enableDataBindingSupport && this.allowBinding) {
            return [
                {
                    caption: "...",
                    onExecute: (sender: SingleInputPropertyEditor, clickedElement: HTMLElement) => {
                        let fieldPicker = new FieldPicker(context.designContext.dataStructure);
                        fieldPicker.onClose = (sender, wasCancelled) => {
                            if (!wasCancelled) {
                                this.setPropertyValue(context, fieldPicker.selectedField.asExpression());

                                context.peer.changed(true);
                            }
                        }
                        fieldPicker.popup(clickedElement);
                    }
                }
            ];
        }
        else {
            return super.getAdditionalCommands(context);
        }
    }

    constructor(
        readonly targetVersion: Adaptive.TargetVersion,
        readonly propertyName: string,
        readonly label: string,
        readonly allowBinding: boolean = false,
        readonly isMultiline: boolean = false,
        readonly causesPropertySheetRefresh: boolean = false) {
        super(targetVersion, propertyName, label, causesPropertySheetRefresh);
    }
}

export class NumberPropertyEditor extends SingleInputPropertyEditor {
    protected setPropertyValue(context: PropertySheetContext, value: string) {
        try {
            context.target[this.propertyName] = parseFloat(value);
        }
        catch {
            context.target[this.propertyName] = this.defaultValue;
        }
    }

    protected createInput(context: PropertySheetContext): Adaptive.Input {
        let input = new Adaptive.NumberInput();
        input.defaultValue = this.getPropertyValue(context);
        input.placeholder = "(not set)";

        return input;
    }

    constructor(
        readonly targetVersion: Adaptive.TargetVersion,
        readonly propertyName: string,
        readonly label: string,
        readonly defaultValue: number | undefined = undefined,
        readonly causesPropertySheetRefresh: boolean = false) {
        super(targetVersion, propertyName, label, causesPropertySheetRefresh);
    }
}

export class ObjectPropertyEditor extends StringPropertyEditor {
    protected getPropertyValue(context: PropertySheetContext): any {
        return JSON.stringify(context.target[this.propertyName]);
    }

    protected setPropertyValue(context: PropertySheetContext, value: string) {
        context.target[this.propertyName] = JSON.parse(value);
    }
}

export class CustomCardObjectPropertyEditor extends StringPropertyEditor {
    protected getPropertyValue(context: PropertySheetContext): any {
        return context.peer.getCardObject().getCustomProperty(this.propertyName);
    }

    protected setPropertyValue(context: PropertySheetContext, value: string) {
        context.peer.getCardObject().setCustomProperty(this.propertyName, value);
    }
}

export class BooleanPropertyEditor extends SingleInputPropertyEditor {
    protected getPropertyValue(context: PropertySheetContext): any {
        let v = context.target[this.propertyName];

        return typeof v === "boolean" ? v.toString() : "false";
    }

    protected setPropertyValue(context: PropertySheetContext, value: string) {
        context.target[this.propertyName] = value == "true";
    }

    protected createInput(context: PropertySheetContext): Adaptive.Input {
        let input = new Adaptive.ToggleInput();
        input.defaultValue = this.getPropertyValue(context);

        return input;
    }
}

export interface IVersionedChoice {
    targetVersion: Adaptive.TargetVersion;
    name: string;
    value: string;
}

export class ChoicePropertyEditor extends SingleInputPropertyEditor {
    protected createInput(context: PropertySheetContext): Adaptive.Input {
        let input = new Adaptive.ChoiceSetInput();
        input.defaultValue = this.getPropertyValue(context);
        input.isCompact = true;
        input.placeholder = "(not set)";

        for (let choice of this.choices) {
            if (Adaptive.isVersionLessOrEqual(choice.targetVersion, context.designContext.targetVersion)) {
                input.choices.push(new Adaptive.Choice(choice.name, choice.value));
            }
        }

        return input;
    }

    constructor(
        readonly targetVersion: Adaptive.TargetVersion,
        readonly propertyName: string,
        readonly label: string,
        readonly choices: IVersionedChoice[],
        readonly causesPropertySheetRefresh: boolean = false) {
        super(targetVersion, propertyName, label, causesPropertySheetRefresh);
    }
}

export class ContainerStylePropertyEditor extends ChoicePropertyEditor {
    protected getPropertyValue(context: PropertySheetContext): any {
        let currentStyle = context.target[this.propertyName];

        return currentStyle ? currentStyle.toString() : "not_set";
    }

    protected setPropertyValue(context: PropertySheetContext, value: string) {
        if (value == "not_set") {
            context.target[this.propertyName] = null;
        }
        else {
            context.target[this.propertyName] = value;
        }
    }

    constructor(readonly targetVersion: Adaptive.TargetVersion,readonly propertyName: string, readonly label: string) {
        super(
            targetVersion,
            propertyName,
            label,
            [
                { targetVersion: Adaptive.Versions.v1_0, name: "(not set)", value: "not_set" },
                { targetVersion: Adaptive.Versions.v1_0, name: "Default", value: "default" },
                { targetVersion: Adaptive.Versions.v1_0, name: "Emphasis", value: "emphasis" },
                { targetVersion: Adaptive.Versions.v1_2, name: "Accent", value: "accent" },
                { targetVersion: Adaptive.Versions.v1_2, name: "Good", value: "good" },
                { targetVersion: Adaptive.Versions.v1_2, name: "Attention", value: "attention" },
                { targetVersion: Adaptive.Versions.v1_2, name: "Warning", value: "warning" }
            ]);
    }
}

export class ColumnWidthPropertyEditor extends ChoicePropertyEditor {
    protected getPropertyValue(context: PropertySheetContext): any {
        if (context.target[this.propertyName] instanceof Adaptive.SizeAndUnit) {
            if (context.target[this.propertyName].unit == Adaptive.SizeUnit.Pixel) {
                return "pixels";
            }
            else {
                return "weighted";
            }
        }
        else {
            return context.target[this.propertyName].toString();
        }
    }

    protected setPropertyValue(context: PropertySheetContext, value: string) {
        switch (value) {
            case "auto":
                context.target[this.propertyName] = "auto";
                break;
            case "pixels":
                context.target[this.propertyName] = new Adaptive.SizeAndUnit(50, Adaptive.SizeUnit.Pixel);
                break;
            case "weighted":
                context.target[this.propertyName] = new Adaptive.SizeAndUnit(50, Adaptive.SizeUnit.Weight);
                break;
            case "stretch":
            default:
                context.target[this.propertyName] = "stretch";
                break;
        }
    }
}

export class HeightPropertyEditor extends ChoicePropertyEditor {
    protected setPropertyValue(context: PropertySheetContext, value: string) {
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

        context.target[this.propertyName] = processedValue;
    }
}

export class SizeAndUnitPropertyEditor extends NumberPropertyEditor {
    protected getPropertyValue(context: PropertySheetContext): any {
        return (<Adaptive.SizeAndUnit>context.target[this.propertyName]).physicalSize.toString();
    }

    protected setPropertyValue(context: PropertySheetContext, value: string) {
        context.target[this.propertyName] = new Adaptive.SizeAndUnit(parseInt(value), this.sizeUnit);
    }

    constructor(
        readonly targetVersion: Adaptive.TargetVersion,
        readonly propertyName: string,
        readonly label: string,
        readonly sizeUnit: Adaptive.SizeUnit,
        readonly defaultValue: number | undefined = undefined,
        readonly causesPropertySheetRefresh: boolean = false) {
        super(targetVersion, propertyName, label, defaultValue, causesPropertySheetRefresh);
    }
}

export class ActionPropertyEditor extends SingleInputPropertyEditor {
    protected getPropertyValue(context: PropertySheetContext): any {
        let action = <Adaptive.Action>context.target[this.propertyName];

        return action ? action.getJsonTypeName() : "none";
    }

    protected setPropertyValue(context: PropertySheetContext, value: string) {
        context.target[this.propertyName] = parseInt(value, 10);

        if (value == "none") {
            context.target[this.propertyName] = null;
        }
        else {
            context.target[this.propertyName] = context.designContext.hostContainer.actionsRegistry.createInstance(value, context.designContext.targetVersion);
        }
    }

    protected createInput(context: PropertySheetContext): Adaptive.Input {
        let input = new Adaptive.ChoiceSetInput();
        input.defaultValue = this.getPropertyValue(context);
        input.isCompact = true;
        input.placeholder = "(not set)";
        input.choices.push(new Adaptive.Choice("(not set)", "none"));

        for (var i = 0; i < context.designContext.hostContainer.actionsRegistry.getItemCount(); i++) {
            let actionType = context.designContext.hostContainer.actionsRegistry.getItemAt(i).typeName;
            let doAddActionType = this.forbiddenActionTypes ? this.forbiddenActionTypes.indexOf(actionType) < 0 : true;

            if (doAddActionType) {
                let choice = new Adaptive.Choice(actionType, actionType);

                input.choices.push(choice);
            }
        }

        return input;
    }

    constructor(
        readonly targetVersion: Adaptive.TargetVersion,
        readonly propertyName: string,
        readonly label: string,
        readonly forbiddenActionTypes: string[] = [],
        readonly causesPropertySheetRefresh: boolean = false) {
        super(targetVersion, propertyName, label, causesPropertySheetRefresh);
    }
}

export class CompoundPropertyEditor extends PropertySheetEntry {
    render(context: PropertySheetContext): Adaptive.CardElement {
        let container = new Adaptive.Container();

        for (let entry of this.entries) {
            if (Adaptive.isVersionLessOrEqual(entry.targetVersion, context.designContext.targetVersion)) {
                container.addItem(
                    entry.render(
                        new PropertySheetContext(
                            context.designContext,
                            context.peer,
                            context.target[this.propertyName])));
            }
        }

        return container;
    }

    constructor(
        readonly targetVersion: Adaptive.TargetVersion,
        readonly propertyName: string,
        readonly entries: PropertySheetEntry[] = []) {
        super(targetVersion);
    }
}

export class EnumPropertyEditor extends SingleInputPropertyEditor {
    protected setPropertyValue(context: PropertySheetContext, value: string) {
        context.target[this.propertyName] = parseInt(value, 10);
    }

    protected createInput(context: PropertySheetContext): Adaptive.Input {
        let input = new Adaptive.ChoiceSetInput();
        input.defaultValue = this.getPropertyValue(context);
        input.isCompact = true;
        input.placeholder = "(not set)";

        for (let key in this.enumType) {
            let v = parseInt(key, 10);

            if (!isNaN(v)) {
                input.choices.push(new Adaptive.Choice(this.enumType[key], key));
            }
        }

        return input;
    }

    constructor(
        readonly targetVersion: Adaptive.TargetVersion,
        readonly propertyName: string,
        readonly label: string,
        readonly enumType: { [s: number]: string },
        readonly causesPropertySheetRefresh: boolean = false) {
        super(targetVersion, propertyName, label, causesPropertySheetRefresh);
    }
}

interface INameValuePair {
    name: string;
    value: string;
}

class NameValuePairPropertyEditor extends PropertySheetEntry {
    private collectionChanged(context: PropertySheetContext, nameValuePairs: INameValuePair[], refreshPropertySheet: boolean) {
        context.target[this.collectionPropertyName] = [];

        for (let nameValuePair of nameValuePairs) {
            let item = this.createCollectionItem(nameValuePair.name, nameValuePair.value);

            context.target[this.collectionPropertyName].push(item);
        }

        context.peer.changed(refreshPropertySheet);
    }

    render(context: PropertySheetContext): Adaptive.CardElement {
        let result = new Adaptive.Container();

        let collection = context.target[this.collectionPropertyName];

        if (!Array.isArray(collection)) {
            throw new Error("The " + this.collectionPropertyName + " property on " + context.peer.getCardObject().getJsonTypeName() + " either doesn't exist or isn't an array.")
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

                    this.collectionChanged(context, nameValuePairs, false);
                };

                let nameColumn = new Adaptive.Column("stretch");
                nameColumn.addItem(textInput);

                textInput = new Adaptive.TextInput();
                textInput.placeholder = this.valuePropertyLabel;
                textInput.defaultValue = nameValuePairs[i].value;
                textInput.onValueChanged = (sender) => {
                    nameValuePairs[i].value = sender.value;

                    this.collectionChanged(context, nameValuePairs, false);
                };

                let valueColumn = new Adaptive.Column("stretch");
                valueColumn.spacing = Adaptive.Spacing.Small;
                valueColumn.addItem(textInput);

                let removeAction = new Adaptive.SubmitAction();
                removeAction.title = "X";
                removeAction.onExecute = (sender) => {
                    nameValuePairs.splice(i, 1);

                    this.collectionChanged(context, nameValuePairs, true);
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

            this.collectionChanged(context, nameValuePairs, true);
        }

        let actionSet = new Adaptive.ActionSet();
        actionSet.spacing = Adaptive.Spacing.Small;
        actionSet.addAction(addAction);

        result.addItem(actionSet);

        return result;
    }

    constructor(
        readonly targetVersion: Adaptive.TargetVersion,
        readonly collectionPropertyName: string,
        readonly namePropertyName: string,
        readonly valuePropertyName: string,
        readonly createCollectionItem: (name: string, value: string) => any,
        readonly namePropertyLabel: string = "Name",
        readonly valuePropertyLabel: string = "Value",
        readonly addButtonTitle: string = "Add",
        readonly messageIfEmpty: string = "This collection is empty") {
        super(targetVersion);
    }
}

export abstract class DesignerPeer extends DraggableElement {
    static readonly idProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "id", "Id");

    private _parent: DesignerPeer;
    private _cardObject: Adaptive.CardObject;
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

            let cardObjectBoundingRect = this.getCardObjectBoundingRect();
            let peerBoundingRect = this.getBoundingRect();
            let topPadding = peerBoundingRect.height - cardObjectBoundingRect.height;

            let inplaceEditorHost = document.createElement("div");
            inplaceEditorHost.className = "acd-inplace-editor-host";
            inplaceEditorHost.style.left = Math.floor(cardObjectBoundingRect.left + pageXOffset) + "px";
            inplaceEditorHost.style.top = Math.floor(cardObjectBoundingRect.top + pageYOffset - topPadding) + "px";
            inplaceEditorHost.style.width = Math.ceil(peerBoundingRect.width) + "px";
            inplaceEditorHost.style.height = Math.ceil(peerBoundingRect.height) + "px";
            inplaceEditorHost.style.paddingTop = topPadding + "px";

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

    protected internalAddCommands(context: DesignContext, commands: Array<PeerCommand>) {
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

    getCardObject(): Adaptive.CardObject {
        return this._cardObject;
    }

    constructor(
        parent: DesignerPeer,
        designerSurface: CardDesignerSurface,
        registration: DesignerPeerRegistrationBase,
        cardObject: Adaptive.CardObject) {
        super();

        this._parent = parent;

        this.registration = registration;
        this.designerSurface = designerSurface;
        this._cardObject = cardObject;
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

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        // Do nothing in base implementation
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

    getCommands(context: DesignContext, promoteParentCommands: boolean = false): Array<PeerCommand> {
        let result: Array<PeerCommand> = [];

        this.internalAddCommands(context, result);

        if (promoteParentCommands && this.parent) {
            let parentCommands = this.parent.getCommands(context);

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

    buildPropertySheetCard(context: DesignContext): Adaptive.AdaptiveCard {
        let card = new Adaptive.AdaptiveCard();
        card.padding = new Adaptive.PaddingDefinition(
            Adaptive.Spacing.Small,
            Adaptive.Spacing.Small,
            Adaptive.Spacing.Small,
            Adaptive.Spacing.Small);

        let propertySheet = new PropertySheet();

        this.populatePropertySheet(propertySheet);

        propertySheet.render(
            card,
            new PropertySheetContext(context, this));

        let actionSet = new Adaptive.ActionSet();
        let commands = this.getCommands(context, true);

        for (let command of commands) {
            if (command.showInPropertySheet) {
                let action = new Adaptive.SubmitAction();
                action.title = command.name;
                action.onExecute = (sender: Adaptive.Action) => {
                    command.execute(command, action.renderedElement);
                }

                actionSet.addAction(action);
            }
        }

        actionSet.separator = true;

        card.addItem(actionSet);

        return card;
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
            this.treeItem.isSelected = this._isSelected;

            if (this.onSelectedChanged) {
                this.onSelectedChanged(this);
            }
        }
    }
}

export class ActionPeer extends DesignerPeer {
    static readonly titleProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "title", "Title");
    static readonly styleProperty = new ChoicePropertyEditor(
        Adaptive.Versions.v1_2,
        "style",
        "Style",
        [
            { targetVersion: Adaptive.Versions.v1_2, name: "Default", value: Adaptive.ActionStyle.Default },
            { targetVersion: Adaptive.Versions.v1_2, name: "Positive", value: Adaptive.ActionStyle.Positive },
            { targetVersion: Adaptive.Versions.v1_2, name: "Destructive", value: Adaptive.ActionStyle.Destructive }
        ]);
    static readonly iconUrlProperty = new StringPropertyEditor(Adaptive.Versions.v1_1, "iconUrl", "Icon URL");

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
        super(parent, designerSurface, registration, action);
    }

    protected internalGetTreeItemText(): string {
        if (this.action.title && this.action.title != "") {
            return this.action.title;
        }
        else {
            return super.internalGetTreeItemText();
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

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            ActionPeer.idProperty,
            ActionPeer.titleProperty,
            ActionPeer.styleProperty,
            ActionPeer.iconUrlProperty);
    }

    get action(): Adaptive.Action {
        return <Adaptive.Action>this.getCardObject();
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
        return <TAction>this.getCardObject();
    }
}

export class HttpActionPeer extends TypedActionPeer<Adaptive.HttpAction> {
    static readonly ignoreInputValidationProperty = new BooleanPropertyEditor(Adaptive.Versions.v1_3, "ignoreInputValidation", "Ignore input validation");
    static readonly methodProperty = new ChoicePropertyEditor(
        Adaptive.Versions.v1_0,
        "method",
        "Method",
        [
            { targetVersion: Adaptive.Versions.v1_0, name: "GET", value: "GET" },
            { targetVersion: Adaptive.Versions.v1_0, name: "POST", value: "POST" }
        ],
        true);
    static readonly urlProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "url", "Url");
    static readonly bodyProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "body", "Body", false, true);
    static readonly headersProperty = new NameValuePairPropertyEditor(
        Adaptive.Versions.v1_0,
        "headers",
        "name",
        "value",
        (name: string, value: string) => { return new Adaptive.HttpHeader(name, value); },
        "Name",
        "Value",
        "Add a new header",
        "This action has no header.");

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            PropertySheetCategory.DefaultCategory,
            HttpActionPeer.ignoreInputValidationProperty);

        propertySheet.add(
            defaultCategory,
            HttpActionPeer.methodProperty,
            HttpActionPeer.urlProperty);

        if (this.action.method == "POST") {
            propertySheet.add(
                defaultCategory,
                HttpActionPeer.bodyProperty);
        }

        propertySheet.add(
            "HTTP headers",
            HttpActionPeer.headersProperty);
    }
}

export class SubmitActionPeer extends TypedActionPeer<Adaptive.SubmitAction> {
    static readonly ignoreInputValidationProperty = new BooleanPropertyEditor(Adaptive.Versions.v1_3, "ignoreInputValidation", "Ignore input validation");
    static readonly dataProperty = new ObjectPropertyEditor(Adaptive.Versions.v1_0, "data", "Data");

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            SubmitActionPeer.ignoreInputValidationProperty,
            SubmitActionPeer.dataProperty);
    }
}

export class OpenUrlActionPeer extends TypedActionPeer<Adaptive.OpenUrlAction> {
    static readonly urlProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "url", "Url");

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            OpenUrlActionPeer.urlProperty);
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
    static readonly dataContextProperty = new CustomCardObjectPropertyEditor("*", "$data", "Data context", true);
    static readonly whenProperty = new CustomCardObjectPropertyEditor("*", "$when", "Only show when", true);
    static readonly idProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "id", "Id");
    static readonly isVisibleProperty = new BooleanPropertyEditor(Adaptive.Versions.v1_2, "isVisible", "Initially visible");
    static readonly spacingProperty = new EnumPropertyEditor(Adaptive.Versions.v1_0, "spacing", "Spacing", Adaptive.Spacing);
    static readonly separatorProperty = new BooleanPropertyEditor(Adaptive.Versions.v1_0, "separator", "Separator");
    static readonly horizontalAlignmentProperty = new EnumPropertyEditor(Adaptive.Versions.v1_0, "horizontalAlignment", "Horizontal alignment", Adaptive.HorizontalAlignment);
    static readonly heightProperty = new HeightPropertyEditor(
        Adaptive.Versions.v1_1,
        "height",
        "Height",
        [
            { targetVersion: Adaptive.Versions.v1_1, name: "Automatic", value: "auto" },
            { targetVersion: Adaptive.Versions.v1_1, name: "Stretch", value: "stretch" }
        ]);

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
        super(parent, designerSurface, registration, cardElement);

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

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        if (GlobalSettings.enableDataBindingSupport) {
            propertySheet.add(
                defaultCategory,
                CardElementPeer.dataContextProperty,
                CardElementPeer.whenProperty);
        }

        propertySheet.add(
            defaultCategory,
            CardElementPeer.idProperty,
            CardElementPeer.isVisibleProperty);

        propertySheet.add(
            PropertySheetCategory.LayoutCategory,
            CardElementPeer.spacingProperty,
            CardElementPeer.separatorProperty,
            CardElementPeer.horizontalAlignmentProperty,
            CardElementPeer.heightProperty);
    }

    get cardElement(): Adaptive.CardElement {
        return <Adaptive.CardElement>this.getCardObject();
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
        return <TCardElement>this.getCardObject();
    }
}

export class AdaptiveCardPeer extends TypedCardElementPeer<Adaptive.AdaptiveCard> {
    static readonly langProperty = new StringPropertyEditor(Adaptive.Versions.v1_1, "lang", "Language");
    static readonly fallbackTextProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "fallbackText", "Fallback text", false, true);
    static readonly speakProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "speak", "Speak");

    protected addAction(action: Adaptive.Action) {
        this.cardElement.addAction(action);

        this.insertChild(CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, this, action));
    }

    protected internalRemove(): boolean {
        return true;
    }

    protected internalAddCommands(context: DesignContext, commands: Array<PeerCommand>) {
        super.internalAddCommands(context, commands);

        let availableActions: Adaptive.ITypeRegistration<Adaptive.Action>[] = [];

        for (var i = 0; i < context.hostContainer.actionsRegistry.getItemCount(); i++) {
            let typeRegistration = context.hostContainer.actionsRegistry.getItemAt(i);

            if (typeRegistration.schemaVersion.compareTo(context.targetVersion) <= 0) {
                availableActions.push(typeRegistration);
            }
        }

        if (availableActions.length > 0) {
            commands.push(
                new PeerCommand(
                    {
                        name: "Add an action",
                        alwaysShowName: true,
                        iconClass: "acd-icon-bolt",
                        showInPropertySheet: true,
                        execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                            let popupMenu = new Controls.PopupMenu();

                            for (let i = 0; i < availableActions.length; i++) {
                                let menuItem = new Controls.DropDownItem(i.toString(), availableActions[i].typeName);
                                menuItem.onClick = (clickedItem: Controls.DropDownItem) => {
                                    let registration = availableActions[i];
                                    let action = new registration.objectType();
                                    action.title = registration.typeName;

                                    this.addAction(action);

                                    popupMenu.closePopup(false);
                                };

                                popupMenu.items.add(menuItem);
                            }

                            popupMenu.popup(clickedElement);
                        }
                    })
            );
        }
    }

    isDraggable(): boolean {
        return false;
    }

    canBeRemoved(): boolean {
        return false;
    }

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.remove(
            DesignerPeer.idProperty,
            CardElementPeer.isVisibleProperty,
            CardElementPeer.horizontalAlignmentProperty,
            CardElementPeer.separatorProperty,
            CardElementPeer.heightProperty,
            CardElementPeer.spacingProperty);

        propertySheet.add(
            defaultCategory,
            AdaptiveCardPeer.langProperty,
            AdaptiveCardPeer.fallbackTextProperty,
            AdaptiveCardPeer.speakProperty);

        propertySheet.add(
            PropertySheetCategory.LayoutCategory,
            ContainerPeer.minHeightProperty,
            ContainerPeer.verticalContentAlignmentProperty);

        propertySheet.add(
            "Background image",
            ContainerPeer.backgroundImageProperty);

        propertySheet.add(
            PropertySheetCategory.SelectionAction,
            ContainerPeer.selectActionProperty);

        if (this.cardElement.selectAction) {
            let selectActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };

            let subPropertySheet = new PropertySheet(false);
            selectActionPeer.populatePropertySheet(subPropertySheet, PropertySheetCategory.SelectionAction);

            subPropertySheet.remove(
                ActionPeer.iconUrlProperty,
                ActionPeer.styleProperty);

            propertySheet.add(
                PropertySheetCategory.SelectionAction,
                new SubPropertySheetEntry(Adaptive.Versions.v1_0, this.cardElement.selectAction, subPropertySheet));
        }
    }
}

export class ColumnPeer extends TypedCardElementPeer<Adaptive.Column> {
    private static readonly pixelWidthProperty = new SizeAndUnitPropertyEditor(Adaptive.Versions.v1_1, "width", "Width in pixels", Adaptive.SizeUnit.Pixel);
    private static readonly weightProperty = new SizeAndUnitPropertyEditor(Adaptive.Versions.v1_0, "width", "Weight", Adaptive.SizeUnit.Weight);

    static readonly widthProperty = new ColumnWidthPropertyEditor(
        Adaptive.Versions.v1_0,
        "width",
        "Width",
        [
            { targetVersion: Adaptive.Versions.v1_0, name: "Automatic", value: "auto" },
            { targetVersion: Adaptive.Versions.v1_0, name: "Stretch", value: "stretch" },
            { targetVersion: Adaptive.Versions.v1_0, name: "Weighted", value: "weighted" },
            { targetVersion: Adaptive.Versions.v1_1, name: "Pixels", value: "pixels" }
        ],
        true);

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

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            PropertySheetCategory.LayoutCategory,
            ColumnPeer.widthProperty);

        if (this.cardElement.width instanceof Adaptive.SizeAndUnit) {
            if (this.cardElement.width.unit == Adaptive.SizeUnit.Pixel) {
                propertySheet.add(
                    PropertySheetCategory.LayoutCategory,
                    ColumnPeer.pixelWidthProperty);
            }
            else {
                propertySheet.add(
                    PropertySheetCategory.LayoutCategory,
                    ColumnPeer.weightProperty);
            }
        }

        propertySheet.add(
            PropertySheetCategory.LayoutCategory,
            ContainerPeer.minHeightProperty,
            ContainerPeer.verticalContentAlignmentProperty);

        propertySheet.add(
            PropertySheetCategory.StyleCategory,
            ContainerPeer.styleProperty,
            ContainerPeer.bleedProperty);

        propertySheet.add(
            "Background image",
            ContainerPeer.backgroundImageProperty);

        propertySheet.add(
            PropertySheetCategory.SelectionAction,
            ContainerPeer.selectActionProperty);

        if (this.cardElement.selectAction) {
            let selectActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };

            let subPropertySheet = new PropertySheet(false);
            selectActionPeer.populatePropertySheet(subPropertySheet, PropertySheetCategory.SelectionAction);

            subPropertySheet.remove(
                ActionPeer.iconUrlProperty,
                ActionPeer.styleProperty);

            propertySheet.add(
                PropertySheetCategory.SelectionAction,
                new SubPropertySheetEntry(Adaptive.Versions.v1_0, this.cardElement.selectAction, subPropertySheet));
        }
    }
}

export class ColumnSetPeer extends TypedCardElementPeer<Adaptive.ColumnSet> {
    protected isContainer(): boolean {
        return true;
    }

    protected internalAddCommands(context: DesignContext, commands: Array<PeerCommand>) {
        super.internalAddCommands(context, commands);

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
        let columnCount = this.cardElement.getItemCount();

        switch (columnCount) {
            case 0:
                return "No column";
            case 1:
                return "1 column";
            default:
                return columnCount + " columns";
        }
    }

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            ContainerPeer.minHeightProperty,
            ContainerPeer.styleProperty,
            ContainerPeer.bleedProperty);

        propertySheet.add(
            PropertySheetCategory.SelectionAction,
            ContainerPeer.selectActionProperty);

        if (this.cardElement.selectAction) {
            let selectActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };

            let subPropertySheet = new PropertySheet(false);
            selectActionPeer.populatePropertySheet(subPropertySheet, PropertySheetCategory.SelectionAction);

            subPropertySheet.remove(
                ActionPeer.iconUrlProperty,
                ActionPeer.styleProperty);

            propertySheet.add(
                PropertySheetCategory.SelectionAction,
                new SubPropertySheetEntry(Adaptive.Versions.v1_0, this.cardElement.selectAction, subPropertySheet));
        }
    }

    canDrop(peer: DesignerPeer) {
        return true;
    }
}

export class ContainerPeer extends TypedCardElementPeer<Adaptive.Container> {
    static readonly selectActionProperty = new ActionPropertyEditor(Adaptive.Versions.v1_0, "selectAction", "Action type", [ Adaptive.ShowCardAction.JsonTypeName ], true);
    static readonly minHeightProperty = new NumberPropertyEditor(Adaptive.Versions.v1_2, "minPixelHeight", "Minimum height in pixels");
    static readonly verticalContentAlignmentProperty = new EnumPropertyEditor(Adaptive.Versions.v1_1, "verticalContentAlignment", "Vertical content alignment", Adaptive.VerticalAlignment);
    static readonly styleProperty = new ContainerStylePropertyEditor(Adaptive.Versions.v1_0, "style", "Style");
    static readonly bleedProperty = new BooleanPropertyEditor(Adaptive.Versions.v1_2, "bleed", "Bleed");
    static readonly backgroundImageProperty = new CompoundPropertyEditor(
        Adaptive.Versions.v1_0,
        "backgroundImage",
        [
            new StringPropertyEditor(Adaptive.Versions.v1_0, "url", "URL", true),
            new EnumPropertyEditor(Adaptive.Versions.v1_2, "fillMode", "Fill mode", Adaptive.FillMode),
            new EnumPropertyEditor(Adaptive.Versions.v1_2, "horizontalAlignment", "Horizontal alignment", Adaptive.HorizontalAlignment),
            new EnumPropertyEditor(Adaptive.Versions.v1_2, "verticalAlignment", "Vertical alignment", Adaptive.VerticalAlignment)
        ]
    );

    protected isContainer(): boolean {
        return true;
    }

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            PropertySheetCategory.LayoutCategory,
            ContainerPeer.minHeightProperty,
            ContainerPeer.verticalContentAlignmentProperty);

        propertySheet.add(
            PropertySheetCategory.StyleCategory,
            ContainerPeer.styleProperty,
            ContainerPeer.bleedProperty);

        propertySheet.add(
            "Background image",
            ContainerPeer.backgroundImageProperty);

        propertySheet.add(
            PropertySheetCategory.SelectionAction,
            ContainerPeer.selectActionProperty);

        if (this.cardElement.selectAction) {
            let selectActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };

            let subPropertySheet = new PropertySheet(false);
            selectActionPeer.populatePropertySheet(subPropertySheet, PropertySheetCategory.SelectionAction);

            subPropertySheet.remove(
                ActionPeer.iconUrlProperty,
                ActionPeer.styleProperty);

            propertySheet.add(
                PropertySheetCategory.SelectionAction,
                new SubPropertySheetEntry(Adaptive.Versions.v1_0, this.cardElement.selectAction, subPropertySheet));
        }
    }
}

export class ActionSetPeer extends TypedCardElementPeer<Adaptive.AdaptiveCard> {
    protected addAction(action: Adaptive.Action) {
        this.cardElement.addAction(action);

        this.insertChild(CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, this, action));
    }

    protected internalAddCommands(context: DesignContext, commands: Array<PeerCommand>) {
        super.internalAddCommands(context, commands);

        let availableActions: Adaptive.ITypeRegistration<Adaptive.Action>[] = [];

        for (var i = 0; i < context.hostContainer.actionsRegistry.getItemCount(); i++) {
            let typeRegistration = context.hostContainer.actionsRegistry.getItemAt(i);

            if (typeRegistration.schemaVersion.compareTo(context.targetVersion) <= 0) {
                availableActions.push(typeRegistration);
            }
        }

        if (availableActions.length > 0) {
            commands.push(
                new PeerCommand(
                    {
                        name: "Add an action",
                        alwaysShowName: true,
                        iconClass: "acd-icon-bolt",
                        showInPropertySheet: true,
                        execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                            let popupMenu = new Controls.PopupMenu();

                            for (let i = 0; i < availableActions.length; i++) {
                                let menuItem = new Controls.DropDownItem(i.toString(), availableActions[i].typeName);
                                menuItem.onClick = (clickedItem: Controls.DropDownItem) => {
                                    let registration = availableActions[i];
                                    let action = new registration.objectType();
                                    action.title = registration.typeName;

                                    this.addAction(action);

                                    popupMenu.closePopup(false);
                                };

                                popupMenu.items.add(menuItem);
                            }

                            popupMenu.popup(clickedElement);
                        }
                    })
            );
        }
    }
}

export class ImageSetPeer extends TypedCardElementPeer<Adaptive.ImageSet> {
    static readonly ImageSizeProperty = new EnumPropertyEditor(Adaptive.Versions.v1_0, "imageSize", "Image size", Adaptive.ImageSize);

    protected internalAddCommands(context: DesignContext, commands: Array<PeerCommand>) {
        super.internalAddCommands(context, commands);

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

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            ImageSetPeer.ImageSizeProperty);
    }
}

export class ImagePeer extends TypedCardElementPeer<Adaptive.Image> {
    static readonly urlProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "url", "Url", true);
    static readonly altTextProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "altText", "Alternate text", true);
    static readonly sizeProperty = new EnumPropertyEditor(Adaptive.Versions.v1_0, "size", "Size", Adaptive.Size);
    static readonly pixelWidthProperty = new NumberPropertyEditor(Adaptive.Versions.v1_1, "pixelWidth", "Width in pixels");
    static readonly pixelHeightProperty = new NumberPropertyEditor(Adaptive.Versions.v1_1, "pixelHeight", "Height in pixels");
    static readonly styleProperty = new EnumPropertyEditor(Adaptive.Versions.v1_0, "style", "Style", Adaptive.ImageStyle);
    static readonly backgroundColorProperty = new StringPropertyEditor(Adaptive.Versions.v1_1, "backgroundColor", "Background color");

    private get isParentImageSet(): boolean {
        return this.parent && this.parent instanceof ImageSetPeer;
    }

    protected internalAddCommands(context: DesignContext, commands: Array<PeerCommand>) {
        super.internalAddCommands(context, commands);

        if (GlobalSettings.enableDataBindingSupport && context.dataStructure) {
            commands.push(
                new PeerCommand(
                    {
                        name: "Bind...",
                        alwaysShowName: true,
                        toolTip: "Select a data field to bind this Image to.",
                        execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                            let fieldPicker = new FieldPicker(context.dataStructure);
                            fieldPicker.onClose = (sender, wasCancelled) => {
                                if (!wasCancelled) {
                                    this.cardElement.url = fieldPicker.selectedField.asExpression();

                                    this.changed(true);
                                }
                            }
                            fieldPicker.popup(clickedElement);
                        }
                    })
            );
        }
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

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            ImagePeer.urlProperty,
            ImagePeer.altTextProperty);

        if (!this.isParentImageSet) {
            propertySheet.add(
                PropertySheetCategory.LayoutCategory,
                ImagePeer.sizeProperty,
                ImagePeer.pixelWidthProperty,
                ImagePeer.pixelHeightProperty);

            propertySheet.add(
                PropertySheetCategory.StyleCategory,
                ImagePeer.styleProperty,
                ImagePeer.backgroundColorProperty);

            propertySheet.add(
                PropertySheetCategory.SelectionAction,
                ContainerPeer.selectActionProperty);

            if (this.cardElement.selectAction) {
                let selectActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.selectAction);
                selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };

                let subPropertySheet = new PropertySheet(false);
                selectActionPeer.populatePropertySheet(subPropertySheet, PropertySheetCategory.SelectionAction);

                subPropertySheet.remove(
                    ActionPeer.iconUrlProperty,
                    ActionPeer.styleProperty);

                propertySheet.add(
                    PropertySheetCategory.SelectionAction,
                    new SubPropertySheetEntry(Adaptive.Versions.v1_0, this.cardElement.selectAction, subPropertySheet));            }
        }
    }
}

export class MediaPeer extends TypedCardElementPeer<Adaptive.Media> {
    static readonly altTextProperty = new StringPropertyEditor(Adaptive.Versions.v1_1, "altText", "Alternate text", true);
    static readonly posterUrlProperty = new StringPropertyEditor(Adaptive.Versions.v1_1, "posterUrl", "Poster URL", true);
    static readonly sourcesProperty = new NameValuePairPropertyEditor(
        Adaptive.Versions.v1_1,
        "sources",
        "url",
        "mimeType",
        (name: string, value: string) => { return new Adaptive.MediaSource(name, value); },
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

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            MediaPeer.altTextProperty,
            MediaPeer.posterUrlProperty);

        propertySheet.add(
            "Sources",
            MediaPeer.sourcesProperty);
    }
}

export class FactSetPeer extends TypedCardElementPeer<Adaptive.FactSet> {
    static readonly factsProperty = new NameValuePairPropertyEditor(
        Adaptive.Versions.v1_0,
        "facts",
        "name",
        "value",
        (name: string, value: string) => { return new Adaptive.Fact(name, value); },
        "Name",
        "Value",
        "Add a new fact",
        "This FactSet is empty.");

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

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            "Facts",
            FactSetPeer.factsProperty);

        propertySheet.remove(CardElementPeer.horizontalAlignmentProperty);
    }
}

export abstract class InputPeer<TInput extends Adaptive.Input> extends TypedCardElementPeer<TInput> {
    static readonly labelProperty = new StringPropertyEditor(
        Adaptive.Versions.v1_3,
        "label",
        "Label");

    static readonly isRequiredProperty = new BooleanPropertyEditor(
        Adaptive.Versions.v1_3,
        "isRequired",
        "Required");

    static readonly errorMessageProperty = new StringPropertyEditor(
        Adaptive.Versions.v1_3,
        "errorMessage",
        "Error message");

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(defaultCategory, InputPeer.labelProperty);
        propertySheet.add(
            PropertySheetCategory.Validation,
            InputPeer.isRequiredProperty,
            InputPeer.errorMessageProperty);

        propertySheet.remove(
            CardElementPeer.horizontalAlignmentProperty,
            CardElementPeer.heightProperty);
    }
}

export class TextInputPeer extends InputPeer<Adaptive.TextInput> {
    static readonly defaultValueProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "defaultValue", "Default value");
    static readonly placeholderProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "placeholder", "Placeholder");
    static readonly isMultilineProperty = new BooleanPropertyEditor(Adaptive.Versions.v1_0, "isMultiline", "Multi-line", true);
    static readonly styleProperty = new EnumPropertyEditor(Adaptive.Versions.v1_0, "style", "Style", Adaptive.InputTextStyle);
    static readonly maxLengthProperty = new NumberPropertyEditor(Adaptive.Versions.v1_0, "maxLength", "Maximum length");
    static readonly inlineActionProperty = new ActionPropertyEditor(Adaptive.Versions.v1_2, "inlineAction", "Action type", [ Adaptive.ShowCardAction.JsonTypeName ], true);
    static readonly regexProperty = new StringPropertyEditor(Adaptive.Versions.v1_3, "regex", "Pattern");


    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            TextInputPeer.placeholderProperty,
            TextInputPeer.isMultilineProperty);

        if (!this.cardElement.isMultiline) {
            propertySheet.add(
                PropertySheetCategory.DefaultCategory,
                TextInputPeer.styleProperty);
        }

        propertySheet.add(
            PropertySheetCategory.InlineAction,
            TextInputPeer.inlineActionProperty);

        if (this.cardElement.inlineAction) {
            let inlineActionPeer = CardDesignerSurface.actionPeerRegistry.createPeerInstance(this.designerSurface, null, this.cardElement.inlineAction);
            inlineActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };

            let subPropertySheet = new PropertySheet(false);
            inlineActionPeer.populatePropertySheet(subPropertySheet, PropertySheetCategory.InlineAction);

            subPropertySheet.remove(ActionPeer.styleProperty);

            propertySheet.add(
                PropertySheetCategory.InlineAction,
                new SubPropertySheetEntry(Adaptive.Versions.v1_2, this.cardElement.inlineAction, subPropertySheet));
        }

        propertySheet.add(
            defaultCategory,
            TextInputPeer.maxLengthProperty,
            TextInputPeer.defaultValueProperty);

        propertySheet.add(
            PropertySheetCategory.Validation,
            TextInputPeer.regexProperty);
    }

    initializeCardElement() {
        super.initializeCardElement();

        this.cardElement.placeholder = "Placeholder text";
    }
}

export class NumberInputPeer extends InputPeer<Adaptive.NumberInput> {
    static readonly defaultValueProperty = new NumberPropertyEditor(Adaptive.Versions.v1_0, "defaultValue", "Default value");
    static readonly placeholderProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "placeholder", "Placeholder");
    static readonly minProperty = new NumberPropertyEditor(Adaptive.Versions.v1_0, "min", "Minimum value");
    static readonly maxProperty = new NumberPropertyEditor(Adaptive.Versions.v1_0, "max", "Maximum value");

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            NumberInputPeer.placeholderProperty,
            NumberInputPeer.defaultValueProperty,
            NumberInputPeer.minProperty,
            NumberInputPeer.maxProperty);
    }

    initializeCardElement() {
        super.initializeCardElement();

        this.cardElement.placeholder = "Placeholder text";
    }
}

export class DateInputPeer extends InputPeer<Adaptive.DateInput> {
    static readonly defaultValueProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "defaultValue", "Default value");
    static readonly minProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "min", "Minimum value");
    static readonly maxProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "max", "Maximum value");

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            DateInputPeer.defaultValueProperty,
            DateInputPeer.minProperty,
            DateInputPeer.maxProperty);
    }
}

export class TimeInputPeer extends InputPeer<Adaptive.TimeInput> {
    static readonly defaultValueProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "defaultValue", "Default value");
    static readonly minProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "min", "Minimum value");
    static readonly maxProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "max", "Maximum value");

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            TimeInputPeer.defaultValueProperty,
            TimeInputPeer.minProperty,
            TimeInputPeer.maxProperty);
    }
}

export class ToggleInputPeer extends InputPeer<Adaptive.ToggleInput> {
    static readonly defaultValueProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "defaultValue", "Default value");
    static readonly titleProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "title", "Title", true);
    static readonly valueOnProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "valueOn", "Value when on");
    static readonly valueOffProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "valueOff", "Value when off");
    static readonly wrapProperty = new BooleanPropertyEditor(Adaptive.Versions.v1_2, "wrap", "Wrap");

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            ToggleInputPeer.titleProperty,
            ToggleInputPeer.valueOnProperty,
            ToggleInputPeer.valueOffProperty,
            ToggleInputPeer.defaultValueProperty);

        propertySheet.add(
            PropertySheetCategory.LayoutCategory,
            ToggleInputPeer.wrapProperty);
    }

    initializeCardElement() {
        this.cardElement.title = "New Input.Toggle";
    }
}

export class ChoiceSetInputPeer extends InputPeer<Adaptive.ChoiceSetInput> {
    static readonly defaultValueProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "defaultValue", "Default value");
    static readonly placeholderProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "placeholder", "Placeholder");
    static readonly isMultiselectProperty = new BooleanPropertyEditor(Adaptive.Versions.v1_0, "isMultiSelect", "Allow multi selection");
    static readonly isCompactProperty = new BooleanPropertyEditor(Adaptive.Versions.v1_0, "isCompact", "Compact style");
    static readonly wrapProperty = new BooleanPropertyEditor(Adaptive.Versions.v1_2, "wrap", "Wrap");
    static readonly choicesProperty = new NameValuePairPropertyEditor(
        Adaptive.Versions.v1_0,
        "choices",
        "title",
        "value",
        (name: string, value: string) => { return new Adaptive.Choice(name, value); },
        "Title",
        "Value",
        "Add a new choice",
        "This ChoiceSet is empty");

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            ChoiceSetInputPeer.placeholderProperty,
            ChoiceSetInputPeer.isMultiselectProperty,
            ChoiceSetInputPeer.isCompactProperty,
            ChoiceSetInputPeer.defaultValueProperty);

        propertySheet.add(
            PropertySheetCategory.LayoutCategory,
            ToggleInputPeer.wrapProperty);

        propertySheet.add(
            "Choices",
            ChoiceSetInputPeer.choicesProperty);
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
    static readonly textProperty = new StringPropertyEditor(Adaptive.Versions.v1_0, "text", "Text", true, true);
    static readonly wrapProperty = new BooleanPropertyEditor(Adaptive.Versions.v1_0, "wrap", "Wrap");
    static readonly maxLinesProperty = new NumberPropertyEditor(Adaptive.Versions.v1_0, "maxLines", "Maximum lines", 0);
    static readonly fontTypeProperty = new EnumPropertyEditor(Adaptive.Versions.v1_2, "fontType", "Font type", Adaptive.FontType);
    static readonly sizeProperty = new EnumPropertyEditor(Adaptive.Versions.v1_0, "size", "Size", Adaptive.TextSize);
    static readonly weightProperty = new EnumPropertyEditor(Adaptive.Versions.v1_0, "weight", "Weight", Adaptive.TextWeight);
    static readonly colorProperty = new EnumPropertyEditor(Adaptive.Versions.v1_0, "color", "Color", Adaptive.TextColor);
    static readonly subtleProperty = new BooleanPropertyEditor(Adaptive.Versions.v1_0, "isSubtle", "Subtle");

    protected createInplaceEditor(): DesignerPeerInplaceEditor {
        return new TextBlockPeerInplaceEditor(this.cardElement);
    }

    protected internalGetTreeItemText(): string {
        return this.cardElement.text;
    }

    protected internalAddCommands(context: DesignContext, commands: Array<PeerCommand>) {
        super.internalAddCommands(context, commands);

        if (context.dataStructure) {
            commands.push(
                new PeerCommand(
                    {
                        name: "Bind...",
                        alwaysShowName: true,
                        toolTip: "Select a data field to bind this TextBlock to.",
                        execute: (command: PeerCommand, clickedElement: HTMLElement) => {
                            let fieldPicker = new FieldPicker(context.dataStructure);
                            fieldPicker.onClose = (sender, wasCancelled) => {
                                if (!wasCancelled) {
                                    this.cardElement.text = fieldPicker.selectedField.asExpression();

                                    this.changed(true);
                                }
                            }
                            fieldPicker.popup(clickedElement);
                        }
                    })
            );
        }
    }

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            TextBlockPeer.textProperty);

        propertySheet.add(
            PropertySheetCategory.LayoutCategory,
            TextBlockPeer.wrapProperty,
            TextBlockPeer.maxLinesProperty);

        propertySheet.add(
            PropertySheetCategory.StyleCategory,
            TextBlockPeer.fontTypeProperty,
            TextBlockPeer.sizeProperty,
            TextBlockPeer.weightProperty,
            TextBlockPeer.colorProperty,
            TextBlockPeer.subtleProperty);
    }

    getToolTip(): string {
        return "Double click to edit";
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

    populatePropertySheet(propertySheet: PropertySheet, defaultCategory: string = PropertySheetCategory.DefaultCategory) {
        super.populatePropertySheet(propertySheet, defaultCategory);

        propertySheet.add(
            defaultCategory,
            new CustomPropertySheetEntry(
                "*",
                (context: PropertySheetContext) => {
                    let infoTextBlock = new Adaptive.TextBlock();
                    infoTextBlock.text = "Use the **Card Payload Editor** to edit the text of this RichTextBlock element.";
                    infoTextBlock.wrap = true;
                    infoTextBlock.spacing = Adaptive.Spacing.Large;
                    infoTextBlock.separator = true;
                    infoTextBlock.horizontalAlignment = Adaptive.HorizontalAlignment.Center;

                    return infoTextBlock;
                }
            )
        );
    }

    initializeCardElement() {
        let textRun = new Adaptive.TextRun();
        textRun.text = "New RichTextBlock";

        this.cardElement.addInline(textRun);
    }
}
