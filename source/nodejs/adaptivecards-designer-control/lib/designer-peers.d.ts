import * as Adaptive from "adaptivecards";
import { DraggableElement } from "./draggable-element";
import { PeerCommand } from "./peer-command";
import { CardDesignerSurface } from "./card-designer-surface";
import { TreeItem } from "./treeitem";
import { Rect, IPoint } from "./miscellaneous";
declare abstract class DesignerPeerInplaceEditor {
    onClose: (applyChanges: boolean) => void;
    abstract initialize(): any;
    abstract applyChanges(): any;
    abstract render(): HTMLElement;
}
export declare class DesignerPeerRegistrationBase {
    readonly category: string;
    readonly iconClass: string;
    constructor(category: string, iconClass?: string);
}
export declare class DesignerPeerRegistration<TSource, TPeer> extends DesignerPeerRegistrationBase {
    readonly sourceType: TSource;
    peerType: TPeer;
    constructor(sourceType: TSource, peerType: TPeer, category: string, iconClass?: string);
}
export declare abstract class DesignerPeer extends DraggableElement {
    private _children;
    private _isSelected;
    private _inplaceEditorOverlay;
    private _inplaceEditor;
    private closeInplaceEditor;
    private tryOpenInplaceEditor;
    protected doubleClick(e: MouseEvent): void;
    protected isContainer(): boolean;
    protected getToolTip(): string;
    protected pointerDown(e: PointerEvent): void;
    protected internalAddCommands(commands: Array<PeerCommand>): void;
    protected internalRender(): HTMLElement;
    protected internalUpdateCssStyles(): void;
    protected peerAdded(newPeer: DesignerPeer): void;
    protected changed(updatePropertySheet: boolean): void;
    protected peerRemoved(peer: DesignerPeer): void;
    protected internalUpdateLayout(): void;
    protected createInplaceEditor(): DesignerPeerInplaceEditor;
    protected getExcludedProperties(): Array<string>;
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
    abstract internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): any;
    constructor(designerSurface: CardDesignerSurface, registration: DesignerPeerRegistrationBase);
    abstract getBoundingRect(): Rect;
    abstract getCardObjectBoundingRect(): Rect;
    getTreeItemText(): string;
    canDrop(peer: DesignerPeer): boolean;
    canBeRemoved(): boolean;
    tryDrop(peer: DesignerPeer, insertionPoint: IPoint): boolean;
    insertChild(peer: DesignerPeer, index?: number): void;
    removeChild(peer: DesignerPeer): void;
    getChildCount(): number;
    getChildAt(index: number): DesignerPeer;
    getCommands(promoteParentCommands?: boolean): Array<PeerCommand>;
    remove(onlyFromCard: boolean, removeChildren: boolean): boolean;
    addElementsToDesignerSurface(designerSurface: HTMLElement, processChildren?: boolean): void;
    removeElementsFromDesignerSurface(processChildren?: boolean): void;
    buildPropertySheetCard(): Adaptive.AdaptiveCard;
    isSelected: boolean;
}
export declare class ActionPeer extends DesignerPeer {
    protected _action: Adaptive.Action;
    getCardObjectTypeName(): string;
    protected doubleClick(e: MouseEvent): void;
    protected internalRemove(): boolean;
    constructor(designerSurface: CardDesignerSurface, registration: DesignerPeerRegistrationBase, action: Adaptive.Action);
    getTreeItemText(): string;
    isDraggable(): boolean;
    getBoundingRect(): Rect;
    getCardObjectBoundingRect(): Rect;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
    readonly action: Adaptive.Action;
}
export declare abstract class TypedActionPeer<TAction extends Adaptive.Action> extends ActionPeer {
    constructor(designerSurface: CardDesignerSurface, registration: DesignerPeerRegistrationBase, action: TAction);
    readonly action: TAction;
}
export declare class HttpActionPeer extends TypedActionPeer<Adaptive.HttpAction> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
}
export declare class SubmitActionPeer extends TypedActionPeer<Adaptive.SubmitAction> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
}
export declare class OpenUrlActionPeer extends TypedActionPeer<Adaptive.OpenUrlAction> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
}
export declare class ShowCardActionPeer extends TypedActionPeer<Adaptive.ShowCardAction> {
    protected getToolTip(): string;
}
export declare class CardElementPeer extends DesignerPeer {
    protected _cardElement: Adaptive.CardElement;
    getCardObjectTypeName(): string;
    protected insertElementAfter(newElement: Adaptive.CardElement): void;
    protected internalRemove(): boolean;
    constructor(designerSurface: CardDesignerSurface, registration: DesignerPeerRegistrationBase, cardElement: Adaptive.CardElement);
    initializeCardElement(): void;
    canDrop(peer: DesignerPeer): boolean;
    tryDrop(peer: DesignerPeer, insertionPoint: IPoint): boolean;
    getBoundingRect(): Rect;
    getCardObjectBoundingRect(): Rect;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
    readonly cardElement: Adaptive.CardElement;
}
export declare abstract class TypedCardElementPeer<TCardElement extends Adaptive.CardElement> extends CardElementPeer {
    constructor(designerSurface: CardDesignerSurface, registration: DesignerPeerRegistrationBase, cardElement: TCardElement);
    readonly cardElement: TCardElement;
}
export declare class AdaptiveCardPeer extends TypedCardElementPeer<Adaptive.AdaptiveCard> {
    protected addAction(action: Adaptive.Action): void;
    protected internalRemove(): boolean;
    protected internalAddCommands(commands: Array<PeerCommand>): void;
    protected getExcludedProperties(): Array<string>;
    isDraggable(): boolean;
    canBeRemoved(): boolean;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, updatePropertySheet: boolean): void;
}
export declare class ColumnPeer extends TypedCardElementPeer<Adaptive.Column> {
    protected isContainer(): boolean;
    getTreeItemText(): string;
    isDraggable(): boolean;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
}
export declare class ColumnSetPeer extends TypedCardElementPeer<Adaptive.ColumnSet> {
    protected isContainer(): boolean;
    protected internalAddCommands(commands: Array<PeerCommand>): void;
    getTreeItemText(): string;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
    canDrop(peer: DesignerPeer): boolean;
}
export declare class ContainerPeer extends TypedCardElementPeer<Adaptive.Container> {
    protected isContainer(): boolean;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
}
export declare class ActionSetPeer extends TypedCardElementPeer<Adaptive.AdaptiveCard> {
    protected addAction(action: Adaptive.Action): void;
    protected internalAddCommands(commands: Array<PeerCommand>): void;
}
export declare class ImageSetPeer extends TypedCardElementPeer<Adaptive.ImageSet> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
    protected internalAddCommands(commands: Array<PeerCommand>): void;
}
export declare class ImagePeer extends TypedCardElementPeer<Adaptive.Image> {
    private readonly isParentImageSet;
    isDraggable(): boolean;
    getBoundingRect(): Rect;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
}
export declare class MediaPeer extends TypedCardElementPeer<Adaptive.Media> {
    getTreeItemText(): string;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
}
export declare class FactSetPeer extends TypedCardElementPeer<Adaptive.FactSet> {
    protected getExcludedProperties(): Array<string>;
    initializeCardElement(): void;
    getTreeItemText(): string;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
}
export declare abstract class InputPeer<TInput extends Adaptive.Input> extends TypedCardElementPeer<TInput> {
    protected getExcludedProperties(): Array<string>;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
    initializeCardElement(): void;
}
export declare class TextInputPeer extends InputPeer<Adaptive.TextInput> {
    initializeCardElement(): void;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
}
export declare class NumberInputPeer extends InputPeer<Adaptive.NumberInput> {
    initializeCardElement(): void;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
}
export declare class DateInputPeer extends InputPeer<Adaptive.DateInput> {
}
export declare class TimeInputPeer extends InputPeer<Adaptive.TimeInput> {
}
export declare class ToggleInputPeer extends InputPeer<Adaptive.ToggleInput> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
}
export declare class ChoiceSetInputPeer extends InputPeer<Adaptive.ChoiceSetInput> {
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
    initializeCardElement(): void;
}
export declare class TextBlockPeer extends TypedCardElementPeer<Adaptive.TextBlock> {
    protected createInplaceEditor(): DesignerPeerInplaceEditor;
    getToolTip(): string;
    getTreeItemText(): string;
    internalAddPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean): void;
    initializeCardElement(): void;
}
export {};
