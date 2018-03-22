import * as Adaptive from "adaptivecards";
import { Spacing, PaddingDefinition } from "adaptivecards";

interface IPoint {
    x: number,
    y: number
}

class Rect {
    constructor(public top: number, public right: number, public bottom: number, public left: number) {
    }

    get width(): number {
        return this.right - this.left;
    }

    get height(): number {
        return this.bottom - this.top;
    }
}

function getScreenOffset(obj): IPoint {
    var p: IPoint = { x: 0, y: 0 };

    while (obj.offsetParent) {
        p.x = p.x + obj.offsetParent.offsetLeft;
        p.y = p.y + obj.offsetParent.offsetTop;

        if (obj == document.getElementsByTagName("body")[0]) {
            break;
        }
        else {
            obj = obj.offsetParent;
        }
    }

    return p;
}

function getBoundingClientRectIncludeMargins(element: HTMLElement): Rect {
    var clientRect = element.getBoundingClientRect();
    var computedStyles = window.getComputedStyle(element);

    var result = new Rect(
        clientRect.top - parseInt(computedStyles.marginTop),
        clientRect.right - parseInt(computedStyles.marginRight),
        clientRect.bottom - parseInt(computedStyles.marginBottom),
        clientRect.left - parseInt(computedStyles.marginLeft)
    );

    return result;
}

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

export abstract class CardElementPeer {
    private _renderedElement: HTMLElement;
    private _separatorElement: HTMLElement;
    private _badgeElement: HTMLElement;
    private _isSelected: boolean;
    private _isMouseOver: boolean;

    private get isMouseOver(): boolean {
        return this._isMouseOver;
    }

    private set isMouseOver(value: boolean) {
        if (value != this._isMouseOver) {
            this._isMouseOver = value;

            this.updateLayout();
        }
    }

    protected _cardElement: Adaptive.CardElement;

    protected addPropertySheetEntries(card: Adaptive.AdaptiveCard) {
        var id = addLabelAndInput(card, "Id:", Adaptive.TextInput);
        id.input.defaultValue = this.cardElement.id;
        id.input.placeholder = "(not set)";
        id.input.onValueChanged = () => {
            this.cardElement.id = id.input.value;

            this.cardElementChanged();
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

            this.cardElementChanged();
        }

        var separator = new Adaptive.ToggleInput();
        separator.title = "Show separator";
        separator.spacing = Adaptive.Spacing.Small;
        separator.defaultValue = String(this.cardElement.separator);
        separator.onValueChanged = () => {
            this.cardElement.separator = separator.value == "true";

            this.cardElementChanged();
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

            this.cardElementChanged();
        }

        var height = addLabelAndInput(card, "Height:", Adaptive.ChoiceSetInput);
        height.input.isCompact = true;
        height.input.choices.push(new Adaptive.Choice("Automatic", "auto"));
        height.input.choices.push(new Adaptive.Choice("Stretch", "stretch"));
        height.input.defaultValue = this.cardElement.height;
        height.input.onValueChanged = () => {
            this.cardElement.height = height.input.value === "auto" ? "auto" : "stretch";

            this.cardElementChanged();
        }
    }

    protected cardElementChanged() {
        if (this.onCardElementChanged) {
            this.onCardElementChanged(this);
        }
    }

    constructor(cardElement: Adaptive.CardElement) {
        this._cardElement = cardElement;
    }

    onSelectedChanged: (sender: CardElementPeer) => void;
    onCardElementChanged: (sender: CardElementPeer) => void;

    updateLayout() {
        if (this._renderedElement) {
            var clientRect = getBoundingClientRectIncludeMargins(this._cardElement.renderedElement);
            var screenOffset = getScreenOffset(this._cardElement.renderedElement);

            this._renderedElement.style.width = clientRect.width + "px";
            this._renderedElement.style.height = clientRect.height + "px";
            this._renderedElement.style.left = clientRect.left - screenOffset.x + "px";;
            this._renderedElement.style.top = clientRect.top - screenOffset.y + "px";;
        }

        if (this._separatorElement && this._cardElement.separatorElement) {
            var clientRect = getBoundingClientRectIncludeMargins(this._cardElement.separatorElement);
            var screenOffset = getScreenOffset(this._cardElement.separatorElement);            

            this._separatorElement.style.width = clientRect.width + "px";
            this._separatorElement.style.height = clientRect.height + "px";
            this._separatorElement.style.left = clientRect.left - screenOffset.x + "px";;
            this._separatorElement.style.top = clientRect.top - screenOffset.y + "px";;
        }

        this._badgeElement.style.visibility = this.isSelected || this.isMouseOver ? "visible" : "hidden";
        this._separatorElement.style.visibility = this.cardElement.spacing == Adaptive.Spacing.None ? "hidden" : this.isSelected || this.isMouseOver ? "visible" : "hidden";
    }

    render() {
        this._separatorElement = document.createElement("div");
        this._separatorElement.classList.add("acd-separation");
        this._separatorElement.style.position = "absolute";
        this._separatorElement.style.visibility = "hidden";

        this._renderedElement = document.createElement("div");
        this._renderedElement.onclick = () => {
            if (this.onSelectedChanged) {
                this.onSelectedChanged(this);
            }
        }
        this._renderedElement.classList.add("acd-peer");
        this._renderedElement.style.position = "absolute";

        this._badgeElement = document.createElement("div");
        this._badgeElement.classList.add("acd-badge");
        this._badgeElement.style.cssFloat = "right";
        this._badgeElement.style.visibility = "hidden";
        this._badgeElement.innerText = (<any>this._cardElement).constructor.name.toUpperCase();

        this._renderedElement.onmouseenter = () => { this.isMouseOver = true; };
        this._renderedElement.onmouseleave = () => { this.isMouseOver = false; };

        this._renderedElement.appendChild(this._badgeElement);

        this.updateLayout();
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

    get separatorElement(): HTMLElement {
        return this._separatorElement;
    }

    get cardElement(): Adaptive.CardElement {
        return this._cardElement;
    }

    get isSelected(): boolean {
        return this._isSelected;
    }

    set isSelected(value: boolean) {
        if (value != this._isSelected) {
            this._isSelected = value;

            if (this._isSelected) {
                this._renderedElement.classList.add("selected");
                this._badgeElement.classList.add("selected");
                this._separatorElement.classList.add("selected");
            }
            else {
                this._renderedElement.classList.remove("selected");
                this._badgeElement.classList.remove("selected");
                this._separatorElement.classList.remove("selected");
            }

            this.updateLayout();
        }
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

export class GenericCardElementPeer extends TypedCardElementPeer<Adaptive.CardElement> {
}

export class ImagePeer extends TypedCardElementPeer<Adaptive.Image> {
    protected addPropertySheetEntries(card: Adaptive.AdaptiveCard) {
        super.addPropertySheetEntries(card);

        var url = addLabelAndInput(card, "Url:", Adaptive.TextInput);
        url.input.defaultValue = this.cardElement.url;
        url.input.onValueChanged = () => {
            this.cardElement.url = url.input.value;
            
            this.cardElementChanged();
        }

        var altText = addLabelAndInput(card, "Alternate text:", Adaptive.TextInput);
        altText.input.defaultValue = this.cardElement.altText;
        altText.input.onValueChanged = () => {
            this.cardElement.altText = altText.input.value;
            
            this.cardElementChanged();
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

            this.cardElementChanged();
        }

        var style = addLabelAndInput(card, "Style:", Adaptive.ChoiceSetInput);
        style.input.isCompact = true;
        style.input.choices.push(new Adaptive.Choice("Default", Adaptive.ImageStyle.Default.toString()));
        style.input.choices.push(new Adaptive.Choice("Person", Adaptive.ImageStyle.Person.toString()));
        style.input.defaultValue = this.cardElement.style.toString();
        style.input.onValueChanged = () => {
            this.cardElement.style = <Adaptive.ImageStyle>parseInt(style.input.value);

            this.cardElementChanged();
        }

        var backgroundColor = addLabelAndInput(card, "Background color:", Adaptive.TextInput);
        backgroundColor.input.defaultValue = this.cardElement.backgroundColor;
        backgroundColor.input.onValueChanged = () => {
            this.cardElement.backgroundColor = backgroundColor.input.value;
            
            this.cardElementChanged();
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
            
            this.cardElementChanged();
        }

        var wrap = new Adaptive.ToggleInput();
        wrap.title = "Wrap";
        wrap.spacing = Adaptive.Spacing.Small;
        wrap.defaultValue = String(this.cardElement.wrap);
        wrap.onValueChanged = () => {
            this.cardElement.wrap = wrap.value == "true";

            this.cardElementChanged();
        }

        card.addItem(wrap);

        var maxLines = addLabelAndInput(card, "Maximum lines:", Adaptive.NumberInput);
        maxLines.input.placeholder = "(not set)";
        maxLines.input.defaultValue = String(this.cardElement.maxLines);
        maxLines.input.onValueChanged = () => {
            try {
                var newMaxLines = parseInt(maxLines.input.value);

                this.cardElement.maxLines = newMaxLines;
            
                this.cardElementChanged();
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

            this.cardElementChanged();
        }

        var weight = addLabelAndInput(card, "Weight:", Adaptive.ChoiceSetInput);
        weight.input.isCompact = true;
        weight.input.choices.push(new Adaptive.Choice("Lighter", Adaptive.TextWeight.Lighter.toString()));
        weight.input.choices.push(new Adaptive.Choice("Default", Adaptive.TextWeight.Default.toString()));
        weight.input.choices.push(new Adaptive.Choice("Bolder", Adaptive.TextWeight.Bolder.toString()));
        weight.input.defaultValue = this.cardElement.weight.toString();
        weight.input.onValueChanged = () => {
            this.cardElement.weight = <Adaptive.TextWeight>parseInt(weight.input.value);

            this.cardElementChanged();
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

            this.cardElementChanged();
        }

        var isSubtle = new Adaptive.ToggleInput();
        isSubtle.title = "Subtle";
        isSubtle.spacing = Adaptive.Spacing.Small;
        isSubtle.defaultValue = String(this.cardElement.isSubtle);
        isSubtle.onValueChanged = () => {
            this.cardElement.isSubtle = isSubtle.value == "true";

            this.cardElementChanged();
        }

        card.addItem(isSubtle);
    }
}

interface IDesignerPeerRegistration {
    cardElementType: { new(): Adaptive.CardElement },
    peerType: { new(cardElement: Adaptive.CardElement): CardElementPeer}
}

export class DesignerPeersRegistry {
    private _items: Array<IDesignerPeerRegistration> = [];

    private findTypeRegistration(cardElementType: { new(): Adaptive.CardElement }): IDesignerPeerRegistration {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].cardElementType === cardElementType) {
                return this._items[i];
            }
        }

        return null;
    }

    constructor() {
        this.reset();
    }

    clear() {
        this._items = [];
    }

    reset() {
        this.clear();

        this.registerPeer(Adaptive.TextBlock, TextBlockPeer);
        this.registerPeer(Adaptive.Image, ImagePeer);
    }

    registerPeer(cardElementType: { new(): Adaptive.CardElement }, peerType: { new(cardElement: Adaptive.CardElement): CardElementPeer }) {
        var registrationInfo = this.findTypeRegistration(cardElementType);

        if (registrationInfo != null) {
            registrationInfo.peerType = peerType;
        }
        else {
            registrationInfo = {
                cardElementType: cardElementType,
                peerType: peerType
            }

            this._items.push(registrationInfo);
        }
    }

    unregisterPeer(cardElementType: { new(): Adaptive.CardElement }) {
        for (var i = 0; i < this._items.length; i++) {
            if (this._items[i].cardElementType === cardElementType) {
                this._items.splice(i, 1);

                return;
            }
        }
    }

    createPeerInstance(cardElement: Adaptive.CardElement): CardElementPeer {
        var registrationInfo = this.findTypeRegistration((<any>cardElement).constructor);

        return registrationInfo ? new registrationInfo.peerType(cardElement) : new GenericCardElementPeer(cardElement);
    }
}

export class CardDesigner {
    static readonly peerRegistry: DesignerPeersRegistry = new DesignerPeersRegistry();

    private _card: Adaptive.AdaptiveCard;
    private _renderedCardHost: HTMLElement;
    private _designerSurface: HTMLDivElement;
    private _items: Array<CardElementPeer> = [];
    private _selectedPeer: CardElementPeer;

    private peerClicked(peer: CardElementPeer) {
        if (peer != this._selectedPeer) {
            if (this._selectedPeer) {
                this._selectedPeer.isSelected = false;
            }

            this._selectedPeer = peer;

            if (this._selectedPeer) {
                this._selectedPeer.isSelected = true;
            }

            if (this.onSelectedPeerChanged) {
                this.onSelectedPeerChanged(this._selectedPeer);
            }
        }
    }

    private peerCardElementChanged(peer: CardElementPeer) {
        this.renderCard()
        this.updateLayout();
    }

    private renderPeer(cardElement: Adaptive.CardElement) {
        var peer = CardDesigner.peerRegistry.createPeerInstance(cardElement);

        this._items.push(peer);

        peer.onSelectedChanged = (clickedPeer: CardElementPeer) => { this.peerClicked(clickedPeer); };
        peer.onCardElementChanged = (sender: CardElementPeer) => { this.peerCardElementChanged(sender); };
        peer.render();

        this._designerSurface.appendChild(peer.separatorElement);
        this._designerSurface.appendChild(peer.renderedElement);

        if (cardElement instanceof Adaptive.CardElementContainer) {
            for (var i = 0; i < cardElement.getItemCount(); i++) {
                this.renderPeer(cardElement.getItemAt(i));
            }            
        }
    }

    private renderCard() {
        this._renderedCardHost.innerHTML = "";

        if (this.card) {
            this._renderedCardHost.appendChild(this.card.render());
        }
    }

    readonly parentElement: HTMLElement;

    constructor(parentElement: HTMLElement) {
        this.parentElement = parentElement;

        var rootElement = document.createElement("div");
        rootElement.style.position = "relative";
        rootElement.style.width = "100%";
        rootElement.style.height = "auto";

        this._renderedCardHost = document.createElement("div");

        rootElement.appendChild(this._renderedCardHost);

        this._designerSurface = document.createElement("div");
        this._designerSurface.style.position = "absolute";
        this._designerSurface.style.left = "0";
        this._designerSurface.style.top = "0";
        this._designerSurface.style.width = "100%";
        this._designerSurface.style.height = "100%";

        rootElement.appendChild(this._designerSurface);

        this.parentElement.innerHTML = "";
        this.parentElement.appendChild(rootElement);
    }

    onSelectedPeerChanged: (peer: CardElementPeer) => void;

    render() {
        this._designerSurface.innerHTML = "";
        this._items = [];
        this._selectedPeer = null;

        this.renderCard();

        if (this.card) {
            this.renderPeer(this.card);
        }
    }

    updateLayout() {
        for (var i = 0; i < this._items.length; i++) {
            this._items[i].updateLayout();
        }
    }

    deleteSelected() {
        if (this.selectedPeer && this.selectedPeer.cardElement.parent) {
            if (this.selectedPeer.cardElement.parent instanceof Adaptive.CardElementContainer) {
                this.selectedPeer.cardElement.parent.removeItem(this.selectedPeer.cardElement);

                this.renderCard();

                this._items.splice(this._items.indexOf(this.selectedPeer), 1);

                this._designerSurface.removeChild(this.selectedPeer.renderedElement);
                this._designerSurface.removeChild(this.selectedPeer.separatorElement);

                this._selectedPeer = null;

                this.updateLayout();
            }
        }
    }

    get selectedPeer(): CardElementPeer {
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