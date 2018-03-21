import * as Adaptive from "adaptivecards";

export class ObservableTextInput extends Adaptive.TextInput {
    private get inputElement(): HTMLInputElement {
        return <HTMLInputElement>this.renderedElement;
    }
    
    onValueChanged: (sender: ObservableTextInput) => void;

    render(): HTMLElement {
        var result = super.render();

        this.inputElement.oninput = () => {
            if (this.onValueChanged) {
                this.onValueChanged(this);
            }
        }

        return result;
    }
}

interface IPoint {
    x: number,
    y: number;
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

export abstract class CardElementPeer {
    private _renderedElement: HTMLElement;
    private _separatorElement: HTMLElement;
    private _badgeElement: HTMLElement;
    private _isSelected: boolean;
    private _isMouseOver: boolean;

    private updateElementsVisibility() {
        this._badgeElement.style.visibility = this.isSelected || this.isMouseOver ? "visible" : "hidden";
        this._separatorElement.style.visibility = this.isSelected || this.isMouseOver ? "visible" : "hidden";
    }

    private get isMouseOver(): boolean {
        return this._isMouseOver;
    }

    private set isMouseOver(value: boolean) {
        if (value != this._isMouseOver) {
            this._isMouseOver = value;

            this.updateElementsVisibility();
        }
    }

    protected _cardElement: Adaptive.CardElement;

    protected addPropertySheetEntries(card: Adaptive.AdaptiveCard) {
        var label = new Adaptive.TextBlock();
        label.text = "Id:";

        card.addItem(label);

        var idInput = new ObservableTextInput();
        idInput.defaultValue = this.cardElement.id;
        idInput.spacing = Adaptive.Spacing.None;
        idInput.onValueChanged = () => {
            if (this.cardElementChanged) {
                this.cardElementChanged(this);
            }    
        }

        card.addItem(idInput);
    }

    constructor(cardElement: Adaptive.CardElement) {
        this._cardElement = cardElement;
    }

    selectedChanged: (sender: CardElementPeer) => void;
    cardElementChanged: (sender: CardElementPeer) => void;

    updateLayout() {
        if (this._renderedElement) {
            var clientRect = this._cardElement.renderedElement.getBoundingClientRect();
            var screenOffset = getScreenOffset(this._cardElement.renderedElement);

            this._renderedElement.style.width = clientRect.width + "px";
            this._renderedElement.style.height = clientRect.height + "px";
            this._renderedElement.style.left = clientRect.left - screenOffset.x + "px";;
            this._renderedElement.style.top = clientRect.top - screenOffset.y + "px";;
        }

        if (this._separatorElement && this._cardElement.separatorElement) {
            var clientRect = this._cardElement.separatorElement.getBoundingClientRect();
            var screenOffset = getScreenOffset(this._cardElement.separatorElement);            

            this._separatorElement.style.width = clientRect.width + "px";
            this._separatorElement.style.height = clientRect.height + "px";
            this._separatorElement.style.left = clientRect.left - screenOffset.x + "px";;
            this._separatorElement.style.top = clientRect.top - screenOffset.y + "px";;
        }
    }

    render() {
        this._separatorElement = document.createElement("div");
        this._separatorElement.classList.add("acd-separation");
        this._separatorElement.style.position = "absolute";
        this._separatorElement.style.visibility = "hidden";

        this._renderedElement = document.createElement("div");
        this._renderedElement.onclick = () => {
            if (this.selectedChanged) {
                this.selectedChanged(this);
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

            this.updateElementsVisibility();
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

export class TextBlockPeer extends TypedCardElementPeer<Adaptive.TextBlock> {
    protected addPropertySheetEntries(card: Adaptive.AdaptiveCard) {
        super.addPropertySheetEntries(card);

        var label = new Adaptive.TextBlock();
        label.text = "Text:";

        card.addItem(label);

        var textInput = new ObservableTextInput();
        textInput.defaultValue = this.cardElement.text;
        textInput.spacing = Adaptive.Spacing.None;
        textInput.onValueChanged = () => {
            this.cardElement.text = textInput.value;
            
            if (this.cardElementChanged) {
                this.cardElementChanged(this);
            }    
        }

        card.addItem(textInput);
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

            if (this.selectedPeerChanged) {
                this.selectedPeerChanged(this._selectedPeer);
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

        peer.selectedChanged = (clickedPeer: CardElementPeer) => { this.peerClicked(clickedPeer); };
        peer.cardElementChanged = (sender: CardElementPeer) => { this.peerCardElementChanged(sender); };
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

    selectedPeerChanged: (peer: CardElementPeer) => void;

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