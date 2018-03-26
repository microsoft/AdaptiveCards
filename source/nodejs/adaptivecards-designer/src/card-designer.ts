import * as Adaptive from "adaptivecards";
import { Spacing, PaddingDefinition } from "adaptivecards";

const DRAG_THRESHOLD = 5;

interface ILabelAndInput<TInput extends Adaptive.Input> {
    label: Adaptive.TextBlock;
    input: TInput;
}

function addLabelAndInput<TInput extends Adaptive.Input>(
    container: Adaptive.Container,
    label: string,
    inputType: { new(): TInput }): ILabelAndInput<TInput> {

    var leftColumn = new Adaptive.Column();
    leftColumn.pixelWidth = 100;
    leftColumn.verticalContentAlignment = Adaptive.VerticalAlignment.Center;

    var rightColumn = new Adaptive.Column();
    rightColumn.width = "stretch";
    rightColumn.verticalContentAlignment = Adaptive.VerticalAlignment.Center;

    var columnSet = new Adaptive.ColumnSet();
    columnSet.spacing = Adaptive.Spacing.Small;
    columnSet.addColumn(leftColumn);
    columnSet.addColumn(rightColumn);

    var result = { label: new Adaptive.TextBlock(), input: new inputType() };
    result.label.text = label;
    result.label.wrap = true;

    leftColumn.addItem(result.label);
    rightColumn.addItem(result.input);

    container.addItem(columnSet);

    return result;
}

function getEffectiveMargins(element: HTMLElement): Rect {
    var computedStyles = window.getComputedStyle(element);

    return new Rect(
        parseInt(computedStyles.marginTop),
        parseInt(computedStyles.marginRight),
        parseInt(computedStyles.marginBottom),
        parseInt(computedStyles.marginLeft)
    );    
}

function getBoundingRectangleIncludingMargins(element: HTMLElement): Rect {
    var effectiveMargins = getEffectiveMargins(element);
    var boundingRect = element.getBoundingClientRect();

    return new Rect(
        boundingRect.top - effectiveMargins.top,
        boundingRect.right + effectiveMargins.right,
        boundingRect.bottom + effectiveMargins.bottom,
        boundingRect.left - effectiveMargins.left
    );
}

function getAbsoluteElementPosition(element): IPoint {
    var result: IPoint = { x: 0, y: 0 };

    while (element) {
        if (element.tagName == "BODY") {
            var xScroll = element.scrollLeft || document.documentElement.scrollLeft;
            var yScroll = element.scrollTop || document.documentElement.scrollTop;

            result.x += (element.offsetLeft - xScroll + element.clientLeft);
            result.y += (element.offsetTop - yScroll + element.clientTop);
        }
        else {
            result.x += (element.offsetLeft - element.scrollLeft + element.clientLeft);
            result.y += (element.offsetTop - element.scrollTop + element.clientTop);
        }

        element = element.offsetParent;
    }

    return result;
}

interface IPoint {
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

export interface IPeerCommand {
    name: string;
    execute: () => void
}

export abstract class DesignerPeer {
    private _children: Array<DesignerPeer> = [];
    private _renderedElement: HTMLElement;
    private _isSelected: boolean;
    private _isPointerOver: boolean;
    private _isPointerDown: boolean;
    private _lastClickedPoint: IPoint;
    private _dragging: boolean;

    protected get isPointerOver(): boolean {
        return this._isPointerOver;
    }

    protected set isPointerOver(value: boolean) {
        if (value != this._isPointerOver) {
            this._isPointerOver = value;

            this.updateLayout();
        }
    }

    protected abstract getBadgeText(): string;
    protected abstract addPropertySheetEntries(card: Adaptive.AdaptiveCard);
    abstract internalRemove(): boolean;

    protected internalAddCommands(commands: Array<IPeerCommand>) {
        commands.push(
            {
                name: "Remove",
                execute: () => { this.remove() }
            }
        );
    }

    protected isDraggable(): boolean {
        return true;
    }

    protected startDrag() {
        if (this.isDraggable() && !this._dragging) {
            this._dragging = true;

            if (this.onStartDrag) {
                this.onStartDrag(this);
            }
        }
    }

    protected internalRender() {
        this._renderedElement = document.createElement("div");
        this._renderedElement.classList.add("acd-peer");
        this._renderedElement.style.position = "absolute";

        this._renderedElement.onmousedown = (e: MouseEvent) => {e.preventDefault(); };
        this._renderedElement.onpointerenter = () => { this.isPointerOver = true; };
        this._renderedElement.onpointerleave = () => { this.isPointerOver = false; };
        this._renderedElement.onpointerdown = (e: PointerEvent) => {
            this.isSelected = true;

            this._isPointerDown = true;
            this._lastClickedPoint = { x: e.offsetX, y: e.offsetY };
            this._renderedElement.setPointerCapture(e.pointerId);
        };
        this._renderedElement.onpointerup = (e: PointerEvent) => {
            this._isPointerDown = false;
            this._renderedElement.releasePointerCapture(e.pointerId);

            this.endDrag();
        };
        this._renderedElement.onpointermove = (e: PointerEvent) => {
            if (this._isPointerDown) {
                if (Math.abs(e.offsetX - this._lastClickedPoint.x) >= DRAG_THRESHOLD || Math.abs(e.offsetY - this._lastClickedPoint.y) >= DRAG_THRESHOLD) {
                    this.startDrag();
                }
            }
        };
    }

    protected updateCssStyles() {
        if (this.isSelected) {
            this.renderedElement.classList.add("selected");
        }
        else {
            this.renderedElement.classList.remove("selected");
        }
    }

    protected newPeerCreated(newPeer: DesignerPeer) {
        this.changed();

        if (this.onNewPeerCreated) {
            this.onNewPeerCreated(this, newPeer);
        }
    }

    protected changed() {
        if (this.onChanged) {
            this.onChanged(this);
        }
    }

    protected peerRemoved(peer: DesignerPeer) {
        if (this.onPeerRemoved) {
            this.onPeerRemoved(peer);
        }
    }

    parent: DesignerPeer;

    onSelectedChanged: (sender: DesignerPeer) => void;
    onChanged: (sender: DesignerPeer) => void;
    onPeerRemoved: (sender: DesignerPeer) => void;
    onNewPeerCreated: (sender: DesignerPeer, newPeer: DesignerPeer) => void;
    onStartDrag: (sender: DesignerPeer) => void;
    onEndDrag: (sender: DesignerPeer) => void;

    constructor(parent: DesignerPeer) {
        this.parent = parent;
    }

    abstract getBoundingRect(): Rect;

    canDrop(peer: DesignerPeer) {
        return false;
    }

    drop(peer: DesignerPeer, insertionPoint: IPoint) {
        // Do nothing is base implementation
    }
    
    addChild(peer: DesignerPeer) {
        this._children.push(peer);
        peer.parent = this;
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

    endDrag() {
        if (this._dragging) {
            this._dragging = false;

            if (this.onEndDrag) {
                this.onEndDrag(this);
            }
        }
    }

    getCommands(): Array<IPeerCommand> {
        var result: Array<IPeerCommand> = [];

        this.internalAddCommands(result);

        return result;
    }

    remove(): boolean {
        var result = this.internalRemove();

        if (result) {
            if (this.parent) {
                this.parent.removeChild(this);
            }

            this.removeElementsFromDesignerSurface();

            this.peerRemoved(this);
        }

        return result;
    }

    render() {
        this.internalRender();
        this.updateLayout();
    }

    updateLayout() {
        if (this.renderedElement) {
            var clientRect = this.getBoundingRect();

            this.renderedElement.style.width = clientRect.width + "px";
            this.renderedElement.style.height = clientRect.height + "px";
            this.renderedElement.style.left = clientRect.left + "px";;
            this.renderedElement.style.top = clientRect.top + "px";;
        }
    }

    addElemnentsToDesignerSurface(designerSurface: HTMLElement) {
        designerSurface.appendChild(this.renderedElement);
    }

    removeElementsFromDesignerSurface() {
        this.renderedElement.remove();
    }

    buildPropertySheetCard(): Adaptive.AdaptiveCard {
        var result = new Adaptive.AdaptiveCard();
        result.padding = new PaddingDefinition(
            Adaptive.Spacing.None,
            Adaptive.Spacing.None,
            Adaptive.Spacing.None,
            Adaptive.Spacing.None);

        this.addPropertySheetEntries(result);

        return result;
    }

    get renderedElement(): HTMLElement {
        return this._renderedElement;
    }

    get isSelected(): boolean {
        return this._isSelected;
    }

    set isSelected(value: boolean) {
        if (value != this._isSelected) {
            this._isSelected = value;

            this.updateCssStyles();
            this.updateLayout();

            if (this.onSelectedChanged) {
                this.onSelectedChanged(this);
            }
        }
    }
}

export class ActionPeer extends DesignerPeer {
    protected _action: Adaptive.Action;

    protected getBadgeText(): string {
        return this.action.getJsonTypeName();
    }

    protected addPropertySheetEntries(card: Adaptive.AdaptiveCard) {
        var elementType = new Adaptive.TextBlock();
        elementType.text = "Action type: **" + this.action.getJsonTypeName() + "**";

        card.addItem(elementType);

        var id = addLabelAndInput(card, "Id:", Adaptive.TextInput);
        id.input.defaultValue = this.action.id;
        id.input.placeholder = "(not set)";
        id.input.onValueChanged = () => {
            this.action.id = id.input.value;

            this.changed();
        }
    }

    internalRemove(): boolean {
        return this.action.remove();
    }

    protected isDraggable(): boolean {
        return false;
    }

    constructor(parent: DesignerPeer, action: Adaptive.Action) {
        super(parent);

        this._action = action;
    }

    getBoundingRect(): Rect {
        var boundingRect = getBoundingRectangleIncludingMargins(this.action.renderedElement);
        var effectiveMargins = getEffectiveMargins(this.action.renderedElement);

        return new Rect(
            this.action.renderedElement.offsetTop - effectiveMargins.top,
            this.action.renderedElement.offsetLeft - effectiveMargins.left + boundingRect.width,
            this.action.renderedElement.offsetTop - effectiveMargins.top + boundingRect.height,
            this.action.renderedElement.offsetLeft - effectiveMargins.left
        );
    }

    get action(): Adaptive.Action {
        return this._action;
    }
}

export class CardElementPeer extends DesignerPeer {
    protected _cardElement: Adaptive.CardElement;

    protected updateCssStyles() {
        super.updateCssStyles();
    }

    protected getBadgeText(): string {
        return this.cardElement.getJsonTypeName();
    }

    protected insertElementAfter(newElement: Adaptive.CardElement) {
        if (this.cardElement.parent instanceof Adaptive.Container) {
            this.cardElement.parent.insertItemAfter(newElement, this.cardElement);

            var newPeer = CardDesigner.cardElementPeerRegistry.createPeerInstance(this, newElement);

            this.newPeerCreated(newPeer);
        }
    }

    protected internalAddCommands(commands: Array<IPeerCommand>) {
        super.internalAddCommands(commands);

        if (this.cardElement.parent instanceof Adaptive.Container) {
            commands.push(
                {
                    name: "Insert TextBlox after",
                    execute: () => {
                        var textBlock = new Adaptive.TextBlock();
                        textBlock.text = "New TextBlock";

                        this.insertElementAfter(textBlock);
                    }
                }
            );
        }
    }

    protected addPropertySheetEntries(card: Adaptive.AdaptiveCard) {
        var elementType = new Adaptive.TextBlock();
        elementType.text = "Element type: **" + this.cardElement.getJsonTypeName() + "**";

        card.addItem(elementType);

        var id = addLabelAndInput(card, "Id:", Adaptive.TextInput);
        id.input.defaultValue = this.cardElement.id;
        id.input.placeholder = "(not set)";
        id.input.onValueChanged = () => {
            this.cardElement.id = id.input.value;

            this.changed();
        }

        var spacing = addLabelAndInput(card, "Spacing:", Adaptive.ChoiceSetInput);
        spacing.input.isCompact = true;
        spacing.input.choices.push(new Adaptive.Choice("None", Adaptive.Spacing.None.toString()));
        spacing.input.choices.push(new Adaptive.Choice("Default", Adaptive.Spacing.Default.toString()));
        spacing.input.choices.push(new Adaptive.Choice("Medium", Adaptive.Spacing.Medium.toString()));
        spacing.input.choices.push(new Adaptive.Choice("Large", Adaptive.Spacing.Large.toString()));
        spacing.input.choices.push(new Adaptive.Choice("Extra large", Adaptive.Spacing.ExtraLarge.toString()));
        spacing.input.choices.push(new Adaptive.Choice("Default padding", Adaptive.Spacing.Padding.toString()));
        spacing.input.defaultValue = this.cardElement.spacing.toString();
        spacing.input.onValueChanged = () => {
            this.cardElement.spacing = <Adaptive.Spacing>parseInt(spacing.input.value);

            this.changed();
        }

        var separator = new Adaptive.ToggleInput();
        separator.title = "Show separator";
        separator.spacing = Adaptive.Spacing.Small;
        separator.defaultValue = String(this.cardElement.separator);
        separator.onValueChanged = () => {
            this.cardElement.separator = separator.value == "true";

            this.changed();
        }

        card.addItem(separator);

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

            this.changed();
        }

        var height = addLabelAndInput(card, "Height:", Adaptive.ChoiceSetInput);
        height.input.isCompact = true;
        height.input.choices.push(new Adaptive.Choice("Automatic", "auto"));
        height.input.choices.push(new Adaptive.Choice("Stretch", "stretch"));
        height.input.defaultValue = this.cardElement.height;
        height.input.onValueChanged = () => {
            this.cardElement.height = height.input.value === "auto" ? "auto" : "stretch";

            this.changed();
        }
    }

    internalRemove(): boolean {
        return this.cardElement.remove();
    }

    constructor(parent: DesignerPeer, cardElement: Adaptive.CardElement) {
        super(parent);

        this._cardElement = cardElement;

        for (var i = 0; i < this.cardElement.getActionCount(); i++) {
            this.addChild(CardDesigner.actionPeerRegistry.createPeerInstance(this, cardElement.getActionAt(i)));
        }

        if (cardElement instanceof Adaptive.Container) {
            for (var i = 0; i < cardElement.getItemCount(); i++) {
                this.addChild(CardDesigner.cardElementPeerRegistry.createPeerInstance(this, cardElement.getItemAt(i)));
            }            
        }
    }

    canDrop(peer: DesignerPeer) {
        return this.cardElement instanceof Adaptive.Container && peer instanceof CardElementPeer;
    }

    drop(peer: DesignerPeer, insertionPoint: IPoint) {
        if (this.cardElement instanceof Adaptive.Container && peer instanceof CardElementPeer) {
            let targetChild: DesignerPeer = null;
            let insertAfter: boolean;

            for (var i = 0; i< this.getChildCount(); i++) {
                let rect = this.getChildAt(i).getBoundingRect();

                if (rect.isInside(insertionPoint)) {
                    targetChild = this.getChildAt(i);

                    insertAfter = (insertionPoint.y - rect.top) >= (rect.height / 2);

                    break;
                }
            }

            if (targetChild != peer && peer.internalRemove()) {
                peer.parent.removeChild(peer);

                if (!targetChild) {
                    let rect = this.getBoundingRect();

                    insertAfter = (insertionPoint.y - rect.top) >= (rect.height / 2);

                    if (this.cardElement.getItemCount() > 0 && insertAfter) {
                        this.cardElement.insertItemAfter(peer.cardElement, this.cardElement.getItemAt(this.cardElement.getItemCount()));
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
    
                this.addChild(peer);
                this.changed();
            }
        }
    }
    
    getBoundingRect(): Rect {
        var cardElementBoundingRect = getBoundingRectangleIncludingMargins(this.cardElement.renderedElement);

        if (this.cardElement.hasVisibleSeparator) {
            let separatorBoundingRect = getBoundingRectangleIncludingMargins(this.cardElement.separatorElement);
            let effectiveMargins = getEffectiveMargins(this.cardElement.separatorElement);

            return new Rect(
                this.cardElement.separatorElement.offsetTop - effectiveMargins.top,
                this.cardElement.separatorElement.offsetLeft - effectiveMargins.left + (Math.max(cardElementBoundingRect.right, separatorBoundingRect.right) - Math.min(cardElementBoundingRect.left, separatorBoundingRect.left)),
                this.cardElement.separatorElement.offsetTop - effectiveMargins.top + (Math.max(cardElementBoundingRect.bottom, separatorBoundingRect.bottom) - Math.min(cardElementBoundingRect.top, separatorBoundingRect.top)),
                this.cardElement.separatorElement.offsetLeft - effectiveMargins.left
            )
        }
        else {
            let effectiveMargins = getEffectiveMargins(this.cardElement.renderedElement);

            return new Rect(
                this.cardElement.renderedElement.offsetTop - effectiveMargins.top,
                this.cardElement.renderedElement.offsetLeft - effectiveMargins.left + cardElementBoundingRect.width,
                this.cardElement.renderedElement.offsetTop - effectiveMargins.top + cardElementBoundingRect.height,
                this.cardElement.renderedElement.offsetLeft - effectiveMargins.left
            )
        }
    }

    get cardElement(): Adaptive.CardElement {
        return this._cardElement;
    }
}

export abstract class TypedCardElementPeer<TCardElement extends Adaptive.CardElement> extends CardElementPeer {
    constructor(parent: DesignerPeer, cardElement: TCardElement) {
        super(parent, cardElement);
    }

    get cardElement(): TCardElement {
        return <TCardElement>this._cardElement;
    }
}

export class AdaptiveCardPeer extends TypedCardElementPeer<Adaptive.AdaptiveCard> {
    protected addAction(action: Adaptive.Action) {
        this.cardElement.addAction(action);

        var newPeer = CardDesigner.actionPeerRegistry.createPeerInstance(this, action);

        this.newPeerCreated(newPeer);
    }

    protected isDraggable(): boolean {
        return false;
    }

    protected internalAddCommands(commands: Array<IPeerCommand>) {
        super.internalAddCommands(commands);

        commands.push(
            {
                name: "Add TextBlock inside",
                execute: () => {
                    var textBlock = new Adaptive.TextBlock();
    
                    this.cardElement.addItem(textBlock);
    
                    var newPeer = CardDesigner.cardElementPeerRegistry.createPeerInstance(this, textBlock);
            
                    this.newPeerCreated(newPeer);
                }
            },
            {
                name: "Add OpenUrl action",
                execute: () => {
                    var action = new Adaptive.OpenUrlAction();
                    action.title = "New OpenUrl action";

                    this.addAction(action);
                }
            },
            {
                name: "Add ShowCard action",
                execute: () => {
                    var action = new Adaptive.ShowCardAction();
                    action.title = "New ShowCard action";

                    this.addAction(action);
                }
            },
            {
                name: "Add Http action",
                execute: () => {
                    var action = new Adaptive.HttpAction();
                    action.title = "New Http action";

                    this.addAction(action);
                }
            }
        );
    }
}

export class ColumnPeer extends TypedCardElementPeer<Adaptive.Column> {
    protected isDraggable(): boolean {
        return false;
    }

    protected internalAddCommands(commands: Array<IPeerCommand>) {
        super.internalAddCommands(commands);

        commands.push(
            {
                name: "Add TextBlock inside",
                execute: () => {
                    var textBlock = new Adaptive.TextBlock();
                    textBlock.text = "New TextBlock";
    
                    this.cardElement.addItem(textBlock);
    
                    var newPeer = CardDesigner.cardElementPeerRegistry.createPeerInstance(this, textBlock);
            
                    this.newPeerCreated(newPeer);
                }
            }
        );
    }
}

export class ColumnSetPeer extends TypedCardElementPeer<Adaptive.ColumnSet> {
    protected internalAddCommands(commands: Array<IPeerCommand>) {
        super.internalAddCommands(commands);

        commands.push(
            {
                name: "Add Column",
                execute: () => {
                    var column = new Adaptive.Column();

                    this.cardElement.addColumn(column);

                    var newPeer = CardDesigner.cardElementPeerRegistry.createPeerInstance(this, column);
            
                    this.newPeerCreated(newPeer);
                }
            }
        );
    }

    constructor(parent: DesignerPeer, cardElement: Adaptive.ColumnSet) {
        super(parent, cardElement);

        for (var i = 0; i < cardElement.getItemCount(); i++) {
            this.addChild(CardDesigner.cardElementPeerRegistry.createPeerInstance(this, cardElement.getItemAt(i)));
        }            
    }

    canDrop(peer: DesignerPeer) {
        return false;
    }
}

export class ContainerPeer extends TypedCardElementPeer<Adaptive.Container> {
    protected internalAddCommands(commands: Array<IPeerCommand>) {
        super.internalAddCommands(commands);

        commands.push(
            {
                name: "Add TextBlock inside",
                execute: () => {
                    var textBlock = new Adaptive.TextBlock();
    
                    this.cardElement.addItem(textBlock);
    
                    var newPeer = CardDesigner.cardElementPeerRegistry.createPeerInstance(this, textBlock);
            
                    this.newPeerCreated(newPeer);
                }
            }
        );
    }
}

export class ActionSetPeer extends TypedCardElementPeer<Adaptive.AdaptiveCard> {
    protected addAction(action: Adaptive.Action) {
        this.cardElement.addAction(action);

        var newPeer = CardDesigner.actionPeerRegistry.createPeerInstance(this, action);

        this.newPeerCreated(newPeer);
    }

    protected internalAddCommands(commands: Array<IPeerCommand>) {
        super.internalAddCommands(commands);

        commands.push(
            {
                name: "Add OpenUrl action",
                execute: () => {
                    var action = new Adaptive.OpenUrlAction();
                    action.title = "New OpenUrl action";

                    this.addAction(action);
                }
            },
            {
                name: "Add ShowCard action",
                execute: () => {
                    var action = new Adaptive.ShowCardAction();
                    action.title = "New ShowCard action";

                    this.addAction(action);
                }
            },
            {
                name: "Add Http action",
                execute: () => {
                    var action = new Adaptive.HttpAction();
                    action.title = "New Http action";

                    this.addAction(action);
                }
            }
        );
    }
}

export class ImagePeer extends TypedCardElementPeer<Adaptive.Image> {
    protected addPropertySheetEntries(card: Adaptive.AdaptiveCard) {
        super.addPropertySheetEntries(card);

        var url = addLabelAndInput(card, "Url:", Adaptive.TextInput);
        url.input.defaultValue = this.cardElement.url;
        url.input.onValueChanged = () => {
            this.cardElement.url = url.input.value;
            
            this.changed();
        }

        var altText = addLabelAndInput(card, "Alternate text:", Adaptive.TextInput);
        altText.input.defaultValue = this.cardElement.altText;
        altText.input.onValueChanged = () => {
            this.cardElement.altText = altText.input.value;
            
            this.changed();
        }

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

            this.changed();
        }

        var style = addLabelAndInput(card, "Style:", Adaptive.ChoiceSetInput);
        style.input.isCompact = true;
        style.input.choices.push(new Adaptive.Choice("Default", Adaptive.ImageStyle.Default.toString()));
        style.input.choices.push(new Adaptive.Choice("Person", Adaptive.ImageStyle.Person.toString()));
        style.input.defaultValue = this.cardElement.style.toString();
        style.input.onValueChanged = () => {
            this.cardElement.style = <Adaptive.ImageStyle>parseInt(style.input.value);

            this.changed();
        }

        var backgroundColor = addLabelAndInput(card, "Background color:", Adaptive.TextInput);
        backgroundColor.input.defaultValue = this.cardElement.backgroundColor;
        backgroundColor.input.onValueChanged = () => {
            this.cardElement.backgroundColor = backgroundColor.input.value;
            
            this.changed();
        }
    }
}

export class TextBlockPeer extends TypedCardElementPeer<Adaptive.TextBlock> {
    protected addPropertySheetEntries(card: Adaptive.AdaptiveCard) {
        super.addPropertySheetEntries(card);

        var text = addLabelAndInput(card, "Text:", Adaptive.TextInput);
        text.input.defaultValue = this.cardElement.text;
        text.input.isMultiline = true;
        text.input.onValueChanged = () => {
            this.cardElement.text = text.input.value;
            
            this.changed();
        }

        var wrap = new Adaptive.ToggleInput();
        wrap.title = "Wrap";
        wrap.spacing = Adaptive.Spacing.Small;
        wrap.defaultValue = String(this.cardElement.wrap);
        wrap.onValueChanged = () => {
            this.cardElement.wrap = wrap.value == "true";

            this.changed();
        }

        card.addItem(wrap);

        var maxLines = addLabelAndInput(card, "Maximum lines:", Adaptive.NumberInput);
        maxLines.input.placeholder = "(not set)";
        maxLines.input.defaultValue = String(this.cardElement.maxLines);
        maxLines.input.onValueChanged = () => {
            try {
                var newMaxLines = parseInt(maxLines.input.value);

                this.cardElement.maxLines = newMaxLines;
            
                this.changed();
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

            this.changed();
        }

        var weight = addLabelAndInput(card, "Weight:", Adaptive.ChoiceSetInput);
        weight.input.isCompact = true;
        weight.input.choices.push(new Adaptive.Choice("Lighter", Adaptive.TextWeight.Lighter.toString()));
        weight.input.choices.push(new Adaptive.Choice("Default", Adaptive.TextWeight.Default.toString()));
        weight.input.choices.push(new Adaptive.Choice("Bolder", Adaptive.TextWeight.Bolder.toString()));
        weight.input.defaultValue = this.cardElement.weight.toString();
        weight.input.onValueChanged = () => {
            this.cardElement.weight = <Adaptive.TextWeight>parseInt(weight.input.value);

            this.changed();
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

            this.changed();
        }

        var isSubtle = new Adaptive.ToggleInput();
        isSubtle.title = "Subtle";
        isSubtle.spacing = Adaptive.Spacing.Small;
        isSubtle.defaultValue = String(this.cardElement.isSubtle);
        isSubtle.onValueChanged = () => {
            this.cardElement.isSubtle = isSubtle.value == "true";

            this.changed();
        }

        card.addItem(isSubtle);
    }
}

type CardElementType = { new(): Adaptive.CardElement };
type ActionType = { new(): Adaptive.Action };
type CardElementPeerType = { new(parent: DesignerPeer, cardElement: Adaptive.CardElement): CardElementPeer };
type ActionPeerType = { new(parent: DesignerPeer, action: Adaptive.Action): ActionPeer };

interface IDesignerPeerRegistration<TSource, TPeer> {
    sourceType: TSource,
    peerType: TPeer
}

export abstract class DesignerPeerRegistry<TSource, TPeer> {
    private _items: Array<IDesignerPeerRegistration<TSource, TPeer>> = [];

    protected findTypeRegistration(sourceType: TSource): IDesignerPeerRegistration<TSource, TPeer> {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].sourceType === sourceType) {
                return this._items[i];
            }
        }

        return null;
    }

    constructor() {
        this.reset();
    }

    abstract reset();

    clear() {
        this._items = [];
    }

    registerPeer(sourceType: TSource, peerType: TPeer) {
        var registrationInfo = this.findTypeRegistration(sourceType);

        if (registrationInfo != null) {
            registrationInfo.peerType = peerType;
        }
        else {
            registrationInfo = {
                sourceType: sourceType,
                peerType: peerType
            }

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

        this.registerPeer(Adaptive.Container, ContainerPeer);
        this.registerPeer(Adaptive.AdaptiveCard, AdaptiveCardPeer);
        this.registerPeer(Adaptive.TextBlock, TextBlockPeer);
        this.registerPeer(Adaptive.Image, ImagePeer);
        this.registerPeer(Adaptive.ActionSet, ActionSetPeer);
        this.registerPeer(Adaptive.ColumnSet, ColumnSetPeer);
        this.registerPeer(Adaptive.Column, ColumnPeer);
    }

    createPeerInstance(parent: DesignerPeer, cardElement: Adaptive.CardElement): CardElementPeer {
        var registrationInfo = this.findTypeRegistration((<any>cardElement).constructor);

        return registrationInfo ? new registrationInfo.peerType(parent, cardElement) : new CardElementPeer(parent, cardElement);
    }
}

export class ActionPeerRegistry extends DesignerPeerRegistry<ActionType, ActionPeerType> {
    reset() {
        this.clear();

        // TODO
    }

    createPeerInstance(parent: DesignerPeer, action: Adaptive.Action): ActionPeer {
        var registrationInfo = this.findTypeRegistration((<any>action).constructor);

        return registrationInfo ? new registrationInfo.peerType(parent, action) : new ActionPeer(parent, action);
    }
}

export class CardDesigner {
    static readonly cardElementPeerRegistry: CardElementPeerRegistry = new CardElementPeerRegistry();
    static readonly actionPeerRegistry: ActionPeerRegistry = new ActionPeerRegistry();

    private _card: Adaptive.AdaptiveCard;
    private _rootPeer: DesignerPeer;
    private _cardHost: HTMLElement;
    private _designerSurface: HTMLDivElement;
    private _allPeers: Array<DesignerPeer> = [];
    private _selectedPeer: DesignerPeer;
    private _draggedPeer: DesignerPeer;
    private _dropTarget: DesignerPeer;
    private _currentPointerOffset: IPoint;
    private _initialDragPointerOffset: IPoint;

    private setSelectedPeer(value: DesignerPeer) {
        if (value != this._selectedPeer) {
            if (this._selectedPeer) {
                this._selectedPeer.isSelected = false;
            }

            this._selectedPeer = value;

            if (this._selectedPeer) {
                this._selectedPeer.isSelected = true;

                var rect = this._selectedPeer.getBoundingRect();
                document.getElementById("status4").innerText = "Left: " + rect.left + ", Top: " + rect.top + ", Right: " + rect.right + ", Bottom: " + rect.bottom
            }
            else {
                document.getElementById("status4").innerText = "";
            }

            if (this.onSelectedPeerChanged) {
                this.onSelectedPeerChanged(this._selectedPeer);
            }
        }
    }

    private peerChanged(peer: DesignerPeer) {
        this.renderCard()
        this.updateLayout();
    }

    private peerRemoved(peer: DesignerPeer) {
        this._allPeers.splice(this._allPeers.indexOf(peer), 1);

        if (peer == this._selectedPeer) {
            this.setSelectedPeer(null);
        }

        this.renderCard();
        this.updateLayout();
    }

    private startDrag(peer: DesignerPeer) {
        this._initialDragPointerOffset = this._currentPointerOffset;
        this._draggedPeer = peer;
    }

    private endDrag(peer: DesignerPeer) {
        // Ensure that the dragged peer's elements are at the top in Z order
        this._draggedPeer.removeElementsFromDesignerSurface();
        this._draggedPeer.addElemnentsToDesignerSurface(this._designerSurface);

        this._dropTarget.renderedElement.classList.remove("dragover");

        this._draggedPeer = null;
    }

    private renderCard() {
        this._cardHost.innerHTML = "";

        if (this.card) {
            this._cardHost.appendChild(this.card.render());
        }
    }

    private addPeer(peer: DesignerPeer) {
        this._allPeers.push(peer);

        peer.onSelectedChanged = (clickedPeer: DesignerPeer) => { this.setSelectedPeer(clickedPeer.isSelected ? clickedPeer : null); };
        peer.onChanged = (sender: DesignerPeer) => { this.peerChanged(sender); };
        peer.onPeerRemoved = (sender: DesignerPeer) => { this.peerRemoved(sender); };
        peer.onNewPeerCreated = (sender: DesignerPeer, newPeer: DesignerPeer) => {
            this.addPeer(newPeer);

            newPeer.isSelected = true;
        };
        peer.onStartDrag = (sender: DesignerPeer) => {
            this.startDrag(sender);
        }
        peer.onEndDrag = (sender: DesignerPeer) => {
            this.endDrag(sender);
        }
        peer.render();
        peer.addElemnentsToDesignerSurface(this._designerSurface);

        for (var i = 0; i < peer.getChildCount(); i++) {
            this.addPeer(peer.getChildAt(i));
        }
    }

    private internalFindDropTarget(currentPeer: DesignerPeer, forPeer: DesignerPeer): DesignerPeer {
        var result: DesignerPeer = null;
        var boundingRect = currentPeer.getBoundingRect();

        if (boundingRect.isInside(this._currentPointerOffset)) {
            if (currentPeer.canDrop(forPeer)) {
                result = currentPeer;
            }

            for (var i = 0; i < currentPeer.getChildCount(); i++) {
                var deeperResult = this.internalFindDropTarget(currentPeer.getChildAt(i), forPeer);

                if (deeperResult) {
                    result = deeperResult;
                }
            }
        }

        return result;
    }

    readonly parentElement: HTMLElement;

    constructor(parentElement: HTMLElement) {
        this.parentElement = parentElement;

        var rootElement = document.createElement("div");
        rootElement.style.position = "relative";
        rootElement.style.width = "100%";
        rootElement.style.height = "auto";

        this._cardHost = document.createElement("div");
        this._cardHost.style.border = "1px solid #EEEEEE";

        rootElement.appendChild(this._cardHost);

        this._designerSurface = document.createElement("div");
        this._designerSurface.style.position = "absolute";
        this._designerSurface.style.left = "0";
        this._designerSurface.style.top = "0";
        this._designerSurface.style.width = "100%";
        this._designerSurface.style.height = "100%";

        this._designerSurface.onpointermove = (e: PointerEvent) => {
            var designerPosition = getAbsoluteElementPosition(this._designerSurface);

            this._currentPointerOffset = {
                x: e.x - designerPosition.x,
                y: e.y - designerPosition.y
            };

            document.getElementById("status").innerText = "x: " + this._currentPointerOffset.x + ", y: " + this._currentPointerOffset.y;

            if (this._draggedPeer) {
                if (this._dropTarget) {
                    this._dropTarget.renderedElement.classList.remove("dragover");
                }

                document.getElementById("status2").innerHTML = "Dragging " + (<any>this._draggedPeer).constructor.name;

                var newDropTarget = this.findDropTarget(this._draggedPeer);

                if (newDropTarget) {
                    this._dropTarget = newDropTarget;

                    document.getElementById("status3").innerHTML = "Found drop target: " + (<any>newDropTarget).constructor.name;

                    this._dropTarget.drop(this._draggedPeer, this._currentPointerOffset);

                    this._dropTarget.renderedElement.classList.add("dragover");
                }
                else {
                    document.getElementById("status3").innerHTML = "No drop target";
                }
            }
            else {
                document.getElementById("status2").innerHTML = "";
            }
        }

        rootElement.appendChild(this._designerSurface);

        this.parentElement.innerHTML = "";
        this.parentElement.appendChild(rootElement);
    }

    onSelectedPeerChanged: (peer: DesignerPeer) => void;

    findDropTarget(peer: DesignerPeer): DesignerPeer {
        return this.internalFindDropTarget(this._rootPeer, peer);
    }

    render() {
        this._designerSurface.innerHTML = "";
        this._allPeers = [];

        this.setSelectedPeer(null);

        this.renderCard();

        if (this.card) {
            this._rootPeer = CardDesigner.cardElementPeerRegistry.createPeerInstance(null, this.card);

            this.addPeer(this._rootPeer);
        }
    }

    updateLayout() {
        for (var i = 0; i < this._allPeers.length; i++) {
            this._allPeers[i].updateLayout();
        }
    }

    removeSelected() {
        if (this.selectedPeer) {
            this.selectedPeer.remove();
        }
    }

    get selectedPeer(): DesignerPeer {
        return this._selectedPeer;
    }

    get card(): Adaptive.AdaptiveCard {
        return this._card;
    }

    set card(value: Adaptive.AdaptiveCard) {
        if (value != this._card) {
            this._card = value;

            this.render();
        }
    }
}