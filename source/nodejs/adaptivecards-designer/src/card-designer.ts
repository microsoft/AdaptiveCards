import * as Adaptive from "adaptivecards";
import { Spacing, PaddingDefinition } from "adaptivecards";

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

export abstract class DesignerPeer {
    private _renderedElement: HTMLElement;
    private _isSelected: boolean;
    private _isMouseOver: boolean;

    protected get isMouseOver(): boolean {
        return this._isMouseOver;
    }

    protected set isMouseOver(value: boolean) {
        if (value != this._isMouseOver) {
            this._isMouseOver = value;

            this.updateLayout();
        }
    }

    protected abstract getBadgeText(): string;
    protected abstract addPropertySheetEntries(card: Adaptive.AdaptiveCard);
    protected abstract getReferenceRenderedElement(): HTMLElement;

    protected internalRender() {
        this._renderedElement = document.createElement("div");
        this._renderedElement.onclick = () => {
            if (this.onSelectedChanged) {
                this.onSelectedChanged(this);
            }
        }
        this._renderedElement.classList.add("acd-peer");
        this._renderedElement.style.position = "absolute";

        this._renderedElement.onmouseenter = () => { this.isMouseOver = true; };
        this._renderedElement.onmouseleave = () => { this.isMouseOver = false; };
    }

    protected updateCssStyles() {
        if (this.isSelected) {
            this.renderedElement.classList.add("selected");
        }
        else {
            this.renderedElement.classList.remove("selected");
        }
    }

    protected changed() {
        if (this.onChanged) {
            this.onChanged(this);
        }
    }

    onSelectedChanged: (sender: DesignerPeer) => void;
    onChanged: (sender: DesignerPeer) => void;

    constructor() {
    }

    render() {
        this.internalRender();
        this.updateLayout();
    }

    updateLayout() {
        if (this.renderedElement) {
            var clientRect = this.getReferenceRenderedElement().getBoundingClientRect();

            this.renderedElement.style.width = clientRect.width + "px";
            this.renderedElement.style.height = clientRect.height + "px";
            this.renderedElement.style.left = this.getReferenceRenderedElement().offsetLeft + "px";;
            this.renderedElement.style.top = this.getReferenceRenderedElement().offsetTop + "px";;
        }
    }

    addElemnentsToDesignerSurface(designerSurface: HTMLElement) {
        designerSurface.appendChild(this.renderedElement);
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
        }
    }
}

export class ActionPeer extends DesignerPeer {
    protected _action: Adaptive.Action;

    protected getBadgeText(): string {
        return this.action.getJsonTypeName();
    }

    protected getReferenceRenderedElement(): HTMLElement {
        return this.action.renderedElement;
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

    constructor(action: Adaptive.Action) {
        super();

        this._action = action;
    }

    get action(): Adaptive.Action {
        return this._action;
    }
}

export class CardElementPeer extends DesignerPeer {
    private _separatorElement: HTMLElement;

    protected _cardElement: Adaptive.CardElement;

    protected updateCssStyles() {
        super.updateCssStyles();

        if (this.isSelected) {
            this.separatorElement.classList.add("selected");
        }
        else {
            this.separatorElement.classList.remove("selected");
        }
    }

    protected getBadgeText(): string {
        return this.cardElement.getJsonTypeName();
    }

    protected getReferenceRenderedElement(): HTMLElement {
        return this.cardElement.renderedElement;
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

    protected internalRender() {
        super.internalRender();

        this._separatorElement = document.createElement("div");
        this._separatorElement.classList.add("acd-separation");
        this._separatorElement.style.position = "absolute";
        this._separatorElement.style.visibility = "hidden";
    }

    constructor(cardElement: Adaptive.CardElement) {
        super();

        this._cardElement = cardElement;
    }

    addElemnentsToDesignerSurface(designerSurface: HTMLElement) {
        super.addElemnentsToDesignerSurface(designerSurface);

        designerSurface.appendChild(this.separatorElement);
    }

    updateLayout() {
        super.updateLayout();

        if (this.separatorElement && this.cardElement.separatorElement) {
            var clientRect = this.cardElement.separatorElement.getBoundingClientRect();

            this.separatorElement.style.width = clientRect.width + "px";
            this.separatorElement.style.height = clientRect.height + "px";
            this.separatorElement.style.left = this.cardElement.separatorElement.offsetLeft + "px";;
            this.separatorElement.style.top = this.cardElement.separatorElement.offsetTop + "px";;
        }

        this.separatorElement.style.visibility = this.cardElement.spacing == Adaptive.Spacing.None ? "hidden" : this.isSelected || this.isMouseOver ? "visible" : "hidden";
    }

    get separatorElement(): HTMLElement {
        return this._separatorElement;
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
type CardElementPeerType = { new(cardElement: Adaptive.CardElement): CardElementPeer };
type ActionPeerType = { new(action: Adaptive.Action): ActionPeer };

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

        this.registerPeer(Adaptive.TextBlock, TextBlockPeer);
        this.registerPeer(Adaptive.Image, ImagePeer);
    }

    createPeerInstance(cardElement: Adaptive.CardElement): CardElementPeer {
        var registrationInfo = this.findTypeRegistration((<any>cardElement).constructor);

        return registrationInfo ? new registrationInfo.peerType(cardElement) : new CardElementPeer(cardElement);
    }
}

export class ActionPeerRegistry extends DesignerPeerRegistry<ActionType, ActionPeerType> {
    reset() {
        this.clear();

        /*
        this.registerPeer(Adaptive.TextBlock, TextBlockPeer);
        this.registerPeer(Adaptive.Image, ImagePeer);
        */
    }

    createPeerInstance(action: Adaptive.Action): ActionPeer {
        var registrationInfo = this.findTypeRegistration((<any>action).constructor);

        return registrationInfo ? new registrationInfo.peerType(action) : new ActionPeer(action);
    }
}

export class CardDesigner {
    static readonly cardElementPeerRegistry: CardElementPeerRegistry = new CardElementPeerRegistry();
    static readonly actionPeerRegistry: ActionPeerRegistry = new ActionPeerRegistry();

    private _card: Adaptive.AdaptiveCard;
    private _cardHost: HTMLElement;
    private _designerSurface: HTMLDivElement;
    private _items: Array<DesignerPeer> = [];
    private _selectedPeer: DesignerPeer;

    private peerClicked(peer: DesignerPeer) {
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

    private peerChanged(peer: DesignerPeer) {
        this.renderCard()
        this.updateLayout();
    }

    private initializePeer(peer: DesignerPeer) {
        this._items.push(peer);

        peer.onSelectedChanged = (clickedPeer: DesignerPeer) => { this.peerClicked(clickedPeer); };
        peer.onChanged = (sender: DesignerPeer) => { this.peerChanged(sender); };
        peer.render();
        peer.addElemnentsToDesignerSurface(this._designerSurface);
    }

    private renderPeer(cardElement: Adaptive.CardElement) {
        var cardElementPeer = CardDesigner.cardElementPeerRegistry.createPeerInstance(cardElement);

        this.initializePeer(cardElementPeer);

        for (var i = 0; i < cardElement.getActionCount(); i++) {
            var actionPeer = CardDesigner.actionPeerRegistry.createPeerInstance(cardElement.getActionAt(i));
            
            this.initializePeer(actionPeer);
        }

        if (cardElement instanceof Adaptive.CardElementContainer) {
            for (var i = 0; i < cardElement.getItemCount(); i++) {
                this.renderPeer(cardElement.getItemAt(i));
            }            
        }
    }

    private renderCard() {
        this._cardHost.innerHTML = "";

        if (this.card) {
            this._cardHost.appendChild(this.card.render());
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
        this._cardHost.style.border = "1px solid #EEEEEE";

        rootElement.appendChild(this._cardHost);

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

    onSelectedPeerChanged: (peer: DesignerPeer) => void;

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

    /*
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
    */

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