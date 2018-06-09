import * as Adaptive from "adaptivecards";
import * as Controls from "adaptivecards-controls";
import { SizeAndUnit } from "adaptivecards";

const DRAG_THRESHOLD = 10;

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

        this._renderedElement.onmousedown = (e: MouseEvent) => {e.preventDefault(); };
        this._renderedElement.ondblclick = (e: MouseEvent) => { this.doubleClick(e); };

        this._renderedElement.onpointerenter = () => { this.isPointerOver = true; };
        this._renderedElement.onpointerleave = () => { this.isPointerOver = false; };
        this._renderedElement.onpointerdown = (e: PointerEvent) => { this.pointerDown(e); };
        this._renderedElement.onpointerup = (e: PointerEvent) => { this.pointerUp(e); };
        this._renderedElement.onpointermove = (e: PointerEvent) => { this.pointerMove(e); };

        this.updateLayout();
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
                this.execute(this);
            }
        }
        buttonElement.onpointerdown = (e: PointerEvent) => { e.cancelBubble = true; };

        return buttonElement;
    }

    name: string;
    iconClass: string;
    execute: (command: PeerCommand) => void;

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

export abstract class DesignerPeer extends DraggableElement {
    private _children: Array<DesignerPeer> = [];
    private _isSelected: boolean;
    private _propertySheetHostConfig: Adaptive.HostConfig;

    protected abstract getCardObjectTypeName(): string;

    protected isContainer(): boolean {
        return false;
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
            var clientRect = this.getBoundingRect();

            this.renderedElement.style.width = clientRect.width + "px";
            this.renderedElement.style.height = clientRect.height + "px";
            this.renderedElement.style.left = clientRect.left + "px";
            this.renderedElement.style.top = clientRect.top + "px";
        }
    }

    protected abstract internalRemove(): boolean;

    parent: DesignerPeer;

    onSelectedChanged: (sender: DesignerPeer) => void;
    onChanged: (sender: DesignerPeer, updatePropertySheet: boolean) => void;
    onPeerRemoved: (sender: DesignerPeer) => void;
    onPeerAdded: (sender: DesignerPeer, newPeer: DesignerPeer) => void;

    constructor() {
        super();

        this._propertySheetHostConfig = new Adaptive.HostConfig(
            {
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
                        backgroundColor: "#FFFFFF",
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
            }
        );
            
        this._propertySheetHostConfig.cssClassNamePrefix = "default";
    }

    abstract getBoundingRect(): Rect;
    abstract addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean);

    canDrop(peer: DesignerPeer): boolean {
        return false;
    }

    canBeRemoved(): boolean {
        return true;
    }

    tryDrop(peer: DesignerPeer, insertionPoint: IPoint): boolean {
        return false;
    }
    
    addChild(peer: DesignerPeer) {
        this._children.push(peer);
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

    getCommands(): Array<PeerCommand> {
        var result: Array<PeerCommand> = [];

        this.internalAddCommands(result);

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
        var result = new Adaptive.AdaptiveCard();
        result.hostConfig = this._propertySheetHostConfig;
        result.padding = new Adaptive.PaddingDefinition(
            Adaptive.Spacing.None,
            Adaptive.Spacing.None,
            Adaptive.Spacing.None,
            Adaptive.Spacing.None);

        this.addPropertySheetEntries(result, true);

        return result;
    }

    get isSelected(): boolean {
        return this._isSelected;
    }

    set isSelected(value: boolean) {
        if (value != this._isSelected) {
            this._isSelected = value;

            this.updateLayout();

            if (this.onSelectedChanged) {
                this.onSelectedChanged(this);
            }
        }
    }
}

export class ActionPeer extends DesignerPeer {
    protected _action: Adaptive.Action;

    protected getCardObjectTypeName(): string {
        return this.action.getJsonTypeName();
    }

    protected doubleClick(e: MouseEvent) {
        super.doubleClick(e);

        this.action.renderedElement.click();
    }

    protected internalRemove(): boolean {
        return this.action.remove();
    }

    constructor(action: Adaptive.Action) {
        super();

        this._action = action;
    }

    isDraggable(): boolean {
        return false;
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

    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        if (includeHeader) {
            let container = new Adaptive.Container();
            container.style = "emphasis";
            container.padding = new Adaptive.PaddingDefinition(
                Adaptive.Spacing.Small,
                Adaptive.Spacing.Small,
                Adaptive.Spacing.Small,
                Adaptive.Spacing.Small);

            var actionType = new Adaptive.TextBlock();
            actionType.text = "Action type: **" + this.action.getJsonTypeName() + "**";

            container.addItem(actionType);

            card.addItem(container);
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
    constructor(action: TAction) {
        super(action);
    }

    get action(): TAction {
        return <TAction>this._action;
    }
}

export class HttpActionPeer extends TypedActionPeer<Adaptive.HttpAction> {
    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);

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
    }
}

export class SubmitActionPeer extends TypedActionPeer<Adaptive.SubmitAction> {
    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);

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
    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);

        var url = addLabelAndInput(card, "Url:", Adaptive.TextInput);
        url.input.defaultValue = this.action.url;
        url.input.placeholder = "(not set)";
        url.input.onValueChanged = () => {
            this.action.url = url.input.value;

            this.changed(false);
        }
    }
}

export class CardElementPeer extends DesignerPeer {
    protected _cardElement: Adaptive.CardElement;

    protected getCardObjectTypeName(): string {
        return this.cardElement.getJsonTypeName();
    }

    protected insertElementAfter(newElement: Adaptive.CardElement) {
        if (this.cardElement.parent instanceof Adaptive.Container) {
            this.cardElement.parent.insertItemAfter(newElement, this.cardElement);

            var newPeer = CardDesigner.cardElementPeerRegistry.createPeerInstance(this, newElement);

            this.peerAdded(newPeer);
        }
    }

    protected internalRemove(): boolean {
        return this.cardElement.remove();
    }

    constructor(cardElement: Adaptive.CardElement) {
        super();

        this._cardElement = cardElement;

        if (cardElement instanceof Adaptive.CardElementContainer) {
            for (var i = 0; i < cardElement.getItemCount(); i++) {
                this.addChild(CardDesigner.cardElementPeerRegistry.createPeerInstance(this, cardElement.getItemAt(i)));
            }            
        }

        for (var i = 0; i < this.cardElement.getActionCount(); i++) {
            this.addChild(CardDesigner.actionPeerRegistry.createPeerInstance(this, cardElement.getActionAt(i)));
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

            for (var i = 0; i< this.getChildCount(); i++) {
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
    
                this.addChild(peer);
                this.changed(false);

                return true;
            }
        }

        return false;
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

    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        if (includeHeader) {
            let container = new Adaptive.Container();
            container.style = "emphasis";
            container.padding = new Adaptive.PaddingDefinition(
                Adaptive.Spacing.Small,
                Adaptive.Spacing.Small,
                Adaptive.Spacing.Small,
                Adaptive.Spacing.Small);

            let elementType = new Adaptive.TextBlock();
            elementType.text = "Element type: **" + this.cardElement.getJsonTypeName() + "**";

            container.addItem(elementType);

            card.addItem(container);
        }

        var id = addLabelAndInput(card, "Id:", Adaptive.TextInput);
        id.input.defaultValue = this.cardElement.id;
        id.input.placeholder = "(not set)";
        id.input.onValueChanged = () => {
            this.cardElement.id = id.input.value;

            this.changed(false);
        }

        var spacing = addLabelAndInput(card, "Spacing:", Adaptive.ChoiceSetInput);
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

        var separator = new Adaptive.ToggleInput();
        separator.title = "Show separator";
        separator.spacing = Adaptive.Spacing.Small;
        separator.defaultValue = String(this.cardElement.separator);
        separator.onValueChanged = () => {
            this.cardElement.separator = separator.value == "true";

            this.changed(false);
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
    constructor(cardElement: TCardElement) {
        super(cardElement);
    }

    get cardElement(): TCardElement {
        return <TCardElement>this._cardElement;
    }
}

export class AdaptiveCardPeer extends TypedCardElementPeer<Adaptive.AdaptiveCard> {
    protected addAction(action: Adaptive.Action) {
        this.cardElement.addAction(action);

        this.addChild(CardDesigner.actionPeerRegistry.createPeerInstance(this, action));
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
                    execute: (command: PeerCommand) => {
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

    isDraggable(): boolean {
        return false;
    }

    canBeRemoved(): boolean {
        return false;
    }

    addPropertySheetEntries(card: Adaptive.AdaptiveCard, updatePropertySheet: boolean) {
        super.addPropertySheetEntries(card, updatePropertySheet);

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
            let selectActionPeer = CardDesigner.actionPeerRegistry.createPeerInstance(null, this.cardElement.selectAction);
            selectActionPeer.addPropertySheetEntries(card, false);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
        }
    }
}

export class ColumnPeer extends TypedCardElementPeer<Adaptive.Column> {
    protected isContainer(): boolean {
        return true;
    }

    isDraggable(): boolean {
        return false;
    }

    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);
        
        var width = addLabelAndInput(card, "Width:", Adaptive.TextInput);

        if (this.cardElement.width instanceof Adaptive.SizeAndUnit) {
            width.input.defaultValue = this.cardElement.width.physicalSize + (this.cardElement.width.unit == Adaptive.SizeUnit.Pixel ? "px" : "*");
        }
        else {
            width.input.defaultValue = this.cardElement.width.toString();
        }

        width.input.onValueChanged = () => {
            try {
                this.cardElement.width = SizeAndUnit.parse(width.input.value);
            }
            catch (e) {
                if (width.input.value == "stretch") {
                    this.cardElement.width = "stretch";
                }
                else {
                    this.cardElement.width = "auto";
                }
            }
            
            this.changed(false);
        }

        var verticalContentAlignment = addLabelAndInput(card, "Vertical content alignment:", Adaptive.ChoiceSetInput);
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
            let selectActionPeer = CardDesigner.actionPeerRegistry.createPeerInstance(null, this.cardElement.selectAction);
            selectActionPeer.addPropertySheetEntries(card, false);
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
                    execute: (command: PeerCommand) => {
                        var column = new Adaptive.Column();
                        column.width = "stretch";

                        this.cardElement.addColumn(column);

                        this.addChild(CardDesigner.cardElementPeerRegistry.createPeerInstance(this, column));
                    }
                })
            );
    }

    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);

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
            let selectActionPeer = CardDesigner.actionPeerRegistry.createPeerInstance(null, this.cardElement.selectAction);
            selectActionPeer.addPropertySheetEntries(card, false);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
        }
    }

    canDrop(peer: DesignerPeer) {
        return false;
    }
}

export class ContainerPeer extends TypedCardElementPeer<Adaptive.Container> {
    protected isContainer(): boolean {
        return true;
    }

    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);

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
            let selectActionPeer = CardDesigner.actionPeerRegistry.createPeerInstance(null, this.cardElement.selectAction);
            selectActionPeer.addPropertySheetEntries(card, false);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
        }
    }
}

export class ActionSetPeer extends TypedCardElementPeer<Adaptive.AdaptiveCard> {
    protected addAction(action: Adaptive.Action) {
        this.cardElement.addAction(action);

        this.addChild(CardDesigner.actionPeerRegistry.createPeerInstance(this, action));
    }

    protected internalAddCommands(commands: Array<PeerCommand>) {
        super.internalAddCommands(commands);

        commands.push(
            new PeerCommand(
                {
                    name: "Add an action",
                    iconClass: "acd-icon-bolt",
                    execute: (command: PeerCommand) => {
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

export class ImagePeer extends TypedCardElementPeer<Adaptive.Image> {
    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);

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
            let selectActionPeer = CardDesigner.actionPeerRegistry.createPeerInstance(null, this.cardElement.selectAction);
            selectActionPeer.addPropertySheetEntries(card, false);
            selectActionPeer.onChanged = (sender: DesignerPeer, updatePropertySheet: boolean) => { this.changed(updatePropertySheet); };
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
}

export abstract class InputPeer<TInput extends Adaptive.Input> extends TypedCardElementPeer<TInput> {
    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);

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

    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);

        var placeholder = addLabelAndInput(card, "Placeholder:", Adaptive.TextInput);
        placeholder.input.placeholder = "(not set)";
        placeholder.input.defaultValue = this.cardElement.placeholder;
        placeholder.input.onValueChanged = () => {
            this.cardElement.placeholder = placeholder.input.value;
            
            this.changed(false);
        }

        var isMultiline = new Adaptive.ToggleInput();
        isMultiline.title = "Multi-line:";
        isMultiline.spacing = Adaptive.Spacing.Small;
        isMultiline.defaultValue = String(this.cardElement.isMultiline);
        isMultiline.onValueChanged = () => {
            this.cardElement.isMultiline = isMultiline.value == "true";

            this.changed(false);
        }

        card.addItem(isMultiline);
    }
}

export class NumberInputPeer extends InputPeer<Adaptive.NumberInput> {
    initializeCardElement() {
        super.initializeCardElement();

        this.cardElement.placeholder = "Placeholder text";
    }

    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);

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

export class ToggleInputPeer extends InputPeer<Adaptive.ToggleInput> {
    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);

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
    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);

        var placeholder = addLabelAndInput(card, "Placeholder:", Adaptive.TextInput);
        placeholder.input.placeholder = "(not set)";
        placeholder.input.defaultValue = this.cardElement.placeholder;
        placeholder.input.onValueChanged = () => {
            this.cardElement.placeholder = placeholder.input.value;
            
            this.changed(false);
        }

        var isMultiSelect = new Adaptive.ToggleInput();
        isMultiSelect.title = "Allow multi selection";
        isMultiSelect.spacing = Adaptive.Spacing.Small;
        isMultiSelect.defaultValue = String(this.cardElement.isMultiSelect);
        isMultiSelect.onValueChanged = () => {
            this.cardElement.isMultiSelect = isMultiSelect.value == "true";

            this.changed(true);
        }

        card.addItem(isMultiSelect);

        if (!this.cardElement.isMultiSelect) {
            var isCompact = new Adaptive.ToggleInput();
            isCompact.title = "Compact style";
            isCompact.spacing = Adaptive.Spacing.Small;
            isCompact.defaultValue = String(this.cardElement.isCompact);
            isCompact.onValueChanged = () => {
                this.cardElement.isCompact = isCompact.value == "true";

                this.changed(false);
            }

            card.addItem(isCompact);
        }
    }

    initializeCardElement() {
        this.cardElement.placeholder = "Placeholder text";

        this.cardElement.choices.push(
            new Adaptive.Choice("Choice 1", "Choice 1"),
            new Adaptive.Choice("Choice 2", "Choice 2")
        );
    }
}

export class TextBlockPeer extends TypedCardElementPeer<Adaptive.TextBlock> {
    addPropertySheetEntries(card: Adaptive.AdaptiveCard, includeHeader: boolean) {
        super.addPropertySheetEntries(card, includeHeader);

        var text = addLabelAndInput(card, "Text:", Adaptive.TextInput);
        text.input.defaultValue = this.cardElement.text;
        text.input.isMultiline = true;
        text.input.onValueChanged = () => {
            this.cardElement.text = text.input.value;
            
            this.changed(false);
        }

        var wrap = new Adaptive.ToggleInput();
        wrap.title = "Wrap";
        wrap.spacing = Adaptive.Spacing.Small;
        wrap.defaultValue = String(this.cardElement.wrap);
        wrap.onValueChanged = () => {
            this.cardElement.wrap = wrap.value == "true";

            this.changed(false);
        }

        card.addItem(wrap);

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

        var isSubtle = new Adaptive.ToggleInput();
        isSubtle.title = "Subtle";
        isSubtle.spacing = Adaptive.Spacing.Small;
        isSubtle.defaultValue = String(this.cardElement.isSubtle);
        isSubtle.onValueChanged = () => {
            this.cardElement.isSubtle = isSubtle.value == "true";

            this.changed(false);
        }

        card.addItem(isSubtle);
    }

    initializeCardElement() {
        this.cardElement.text = "New TextBlock";
    }
}

type CardElementType = { new(): Adaptive.CardElement };
type ActionType = { new(): Adaptive.Action };
type CardElementPeerType = { new(cardElement: Adaptive.CardElement): CardElementPeer };
type ActionPeerType = { new(action: Adaptive.Action): ActionPeer };

interface IDesignerPeerRegistration<TSource, TPeer> {
    sourceType: TSource,
    peerType: TPeer
}

export abstract class DesignerPeerRegistry<TSource, TPeer> {
    protected _items: Array<IDesignerPeerRegistration<TSource, TPeer>> = [];

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
        this.registerPeer(Adaptive.FactSet, FactSetPeer);
        this.registerPeer(Adaptive.Image, ImagePeer);
        this.registerPeer(Adaptive.ActionSet, ActionSetPeer);
        this.registerPeer(Adaptive.ColumnSet, ColumnSetPeer);
        this.registerPeer(Adaptive.Column, ColumnPeer);
        this.registerPeer(Adaptive.TextInput, TextInputPeer);
        this.registerPeer(Adaptive.DateInput, DateInputPeer);
        this.registerPeer(Adaptive.NumberInput, NumberInputPeer);
        this.registerPeer(Adaptive.ToggleInput, ToggleInputPeer);
        this.registerPeer(Adaptive.ChoiceSetInput, ChoiceSetInputPeer);
    }

    createPeerInstance(parent: DesignerPeer, cardElement: Adaptive.CardElement): CardElementPeer {
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

        var peer = registrationInfo ? new registrationInfo.peerType(cardElement) : new CardElementPeer(cardElement);
        peer.parent = parent;

        return peer;
    }
}

export class ActionPeerRegistry extends DesignerPeerRegistry<ActionType, ActionPeerType> {
    reset() {
        this.clear();

        this.registerPeer(Adaptive.HttpAction, HttpActionPeer);
        this.registerPeer(Adaptive.SubmitAction, SubmitActionPeer);
        this.registerPeer(Adaptive.OpenUrlAction, OpenUrlActionPeer);
    }

    createPeerInstance(parent: DesignerPeer, action: Adaptive.Action): ActionPeer {
        var registrationInfo = this.findTypeRegistration((<any>action).constructor);

        var peer = registrationInfo ? new registrationInfo.peerType(action) : new ActionPeer(action);
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
        element.style.zIndex = "1000";

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

            this._dragHandle.renderedElement.style.visibility = this._selectedPeer.isDraggable() ? "visible": "hidden";
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
            if (currentPeer.canDrop(forPeer)) {
                result = currentPeer;
            }

            for (var i = 0; i < currentPeer.getChildCount(); i++) {
                var deeperResult = this.internalFindDropTarget(pointerPosition, currentPeer.getChildAt(i), forPeer);

                if (deeperResult) {
                    result = deeperResult;
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
        var peer = this.findCardElementPeer(action.card);

        if (isExpanded) {
            if (!peer) {
                peer = new AdaptiveCardPeer(action.card);
                
                var parentPeer = this.findActionPeer(action);

                if (parentPeer) {
                    parentPeer.addChild(peer);
                }
                else {
                    this._rootPeer.addChild(peer);
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

    onSelectedPeerChanged: (peer: DesignerPeer) => void;
    onLayoutUpdated: (isFullRefresh: boolean) => void;

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
            this._rootPeer = CardDesigner.cardElementPeerRegistry.createPeerInstance(null, this.card);

            this.addPeer(this._rootPeer);
        }

        this._removeCommandElement = document.createElement("div");
        this._removeCommandElement.classList.add("acd-peerButton", "acd-circularButton", "acd-icon-remove");
        this._removeCommandElement.title = "Remove";
        this._removeCommandElement.style.visibility = "hidden";
        this._removeCommandElement.style.position = "absolute";   
        this._removeCommandElement.style.zIndex = "1000";   
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
        this._peerCommandsHostElement.style.zIndex = "1000";   

        this._designerSurface.appendChild(this._dragHandle.renderedElement);
        this._designerSurface.appendChild(this._removeCommandElement);
        this._designerSurface.appendChild(this._peerCommandsHostElement);
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