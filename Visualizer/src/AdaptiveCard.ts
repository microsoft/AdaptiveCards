import * as Utils from "./Utils";
import { InputBase, TextInput, DateInput, Choice, MultichoiceInput, ToggleInput } from "./Inputs";
import { ActionBar, Action, ActionButton, ActionButtonStyle } from "./Actions";

import markdownIt = require("markdown-it");
let markdownProcessor = new markdownIt();

export function processMarkdown(text: string): any {
    return markdownProcessor.render(text);
}

/*
Strongly typed events from https://keestalkstech.com/2016/03/strongly-typed-event-handlers-in-typescript-part-1/
*/
export enum Size {
    Auto,
    Stretch,
    Small,
    Medium,
    Large
}

export enum TextSize {
    Small,
    Normal,
    Medium,
    Large,
    ExtraLarge
}

export enum TextWeight {
    Lighter,
    Normal,
    Bolder
}

export enum TextColor {
    Default,
    Dark,
    Light,
    Accent,
    Good,
    Warning,
    Attention
}

export enum HorizontalAlignment {
    Left,
    Center,
    Right
}

export enum ImageStyle {
    Normal,
    Person
}

export function stringToSize(value: string, defaultValue: Size): Size {
    switch (value) {
        case "auto":
            return Size.Auto;
        case "stretch":
            return Size.Stretch;
        case "small":
            return Size.Small;
        case "medium":
            return Size.Medium;
        case "large":
            return Size.Large;
        default:
            return defaultValue;
    }
}

export function stringToTextSize(value: string, defaultValue: TextSize): TextSize {
    switch (value) {
        case "small":
            return TextSize.Small;
        case "normal":
            return TextSize.Normal;
        case "medium":
            return TextSize.Medium;
        case "large":
            return TextSize.Large;
        case "extraLarge":
            return TextSize.ExtraLarge;
        default:
            return defaultValue;
    }
}

export function stringToTextWeight(value: string, defaultValue: TextWeight): TextWeight {
    switch (value) {
        case "lighter":
            return TextWeight.Lighter;
        case "normal":
            return TextWeight.Normal;
        case "bolder":
            return TextWeight.Bolder;
        default:
            return defaultValue;
    }
}

export function stringToTextColor(value: string, defaultValue: TextColor): TextColor {
    switch (value) {
        case "default":
            return TextColor.Default;
        case "dark":
            return TextColor.Dark;
        case "light":
            return TextColor.Light;
        case "accent":
            return TextColor.Accent;
        case "good":
            return TextColor.Good;
        case "warning":
            return TextColor.Warning;
        case "attention":
            return TextColor.Attention;
        default:
            return defaultValue;
    }
}

export function stringToHorizontalAlignment(value: string, defaultValue: HorizontalAlignment): HorizontalAlignment {
    switch (value) {
        case "left":
            return HorizontalAlignment.Left;
        case "center":
            return HorizontalAlignment.Center;
        case "right":
            return HorizontalAlignment.Right;
        default:
            return defaultValue;
    }
}

export function stringToImageStyle(value: string, defaultValue: ImageStyle): ImageStyle {
    switch (value) {
        case "person":
            return ImageStyle.Person;
        case "normal":
            return ImageStyle.Normal;
        default:
            return defaultValue;
    }
}


export abstract class CardElement {
    static createElement(container: Container, typeName: string): CardElement {
        switch (typeName) {
            case "Container":
                return new Container(container);
            case "TextBlock":
                return new TextBlock(container);
            case "Image":
                return new Image(container);
            case "ImageGallery":
                return new ImageGallery(container);
            // case "ActionBar":
            //     return new ActionBar(container);
            case "FactGroup":
                return new FactGroup(container);
            case "Separator":
                return new Separator(container);
            case "ColumnGroup":
                return new ColumnGroup(container);
            case "TextInput":
                return new TextInput(container);
            case "DateInput":
                return new DateInput(container);
            case "MultichoiceInput":
                return new MultichoiceInput(container);
            case "ToggleInput":
                return new ToggleInput(container);
            default:
                throw new Error("Unknown element type: " + typeName);
        }
    }

    private _container: Container;

    speak: string;
    size: Size = Size.Auto;
    horizontalAlignment: HorizontalAlignment = HorizontalAlignment.Left;

    constructor(container: Container) {
        this._container = container;
    }

    get container(): Container {
        return this._container;
    }

    get hideOverflow(): boolean {
        return true;
    }

    get useDefaultSizing(): boolean {
        return true;
    }

    abstract render(): HTMLElement;

    abstract renderSpeech(): string;

    removeTopSpacing(element: HTMLElement) {
        element.style.marginTop = "0px";
    }

    adjustLayout(element: HTMLElement) {
        if (this.useDefaultSizing) {
            switch (this.size) {
                case Size.Stretch:
                    element.className += " stretch";
                    break;
                case Size.Small:
                    element.className += " smallSize";
                    break;
                case Size.Medium:
                    element.className += " mediumSize";
                    break;
                case Size.Large:
                    element.className += " largeSize";
                    break;
            }
        }

        switch (this.horizontalAlignment) {
            case HorizontalAlignment.Center:
                element.style.textAlign = "center";
                break;
            case HorizontalAlignment.Right:
                element.style.textAlign = "right";
                break;
        }

        if (this.hideOverflow) {
            element.style.overflow = "hidden";
        }
    }

    internalRender(): HTMLElement {
        let renderedElement = this.render();

        if (renderedElement != null) {
            this.adjustLayout(renderedElement);
        }

        return renderedElement;
    }

    parse(json: any) {
        this.speak = json["speak"];
        this.size = stringToSize(json["size"], this.size);
        this.horizontalAlignment = stringToHorizontalAlignment(json["horizontalAlignment"], this.horizontalAlignment);
    }
}

export class TextBlock extends CardElement {
    textSize: TextSize = TextSize.Normal;
    textWeight: TextWeight = TextWeight.Normal;
    textColor: TextColor = TextColor.Default;
    text: string;
    isSubtle: boolean = false;
    wrap: boolean = true;

    parse(json: any) {
        super.parse(json);

        this.text = json["text"];
        this.textSize = stringToTextSize(json["textSize"], TextSize.Normal);
        this.textWeight = stringToTextWeight(json["textWeight"], TextWeight.Normal);
        this.textColor = stringToTextColor(json["textColor"], TextColor.Default);
        this.isSubtle = json["isSubtle"];
        this.wrap = json["wrap"];
    }

    render(): HTMLElement {
        if (!Utils.isNullOrEmpty(this.text)) {
            let element = document.createElement("div");

            let cssStyle = "text ";

            switch (this.textSize) {
                case TextSize.Small:
                    cssStyle += "small ";
                    break;
                case TextSize.Medium:
                    cssStyle += "medium ";
                    break;
                case TextSize.Large:
                    cssStyle += "large ";
                    break;
                case TextSize.ExtraLarge:
                    cssStyle += "extraLarge ";
                    break;
                default:
                    cssStyle += "defaultSize ";
                    break;
            }

            let actualTextColor = this.textColor == TextColor.Default ? this.container.textColor : this.textColor;

            switch (actualTextColor) {
                case TextColor.Dark:
                    cssStyle += "darkColor ";
                    break;
                case TextColor.Light:
                    cssStyle += "lightColor ";
                    break;
                case TextColor.Accent:
                    cssStyle += "accentColor ";
                    break;
                case TextColor.Good:
                    cssStyle += "goodColor ";
                    break;
                case TextColor.Warning:
                    cssStyle += "warningColor ";
                    break;
                case TextColor.Attention:
                    cssStyle += "attentionColor ";
                    break;
                default:
                    cssStyle += "defaultColor ";
                    break;
            }

            if (this.isSubtle) {
                cssStyle += "subtle ";
            }

            switch (this.textWeight) {
                case TextWeight.Lighter:
                    cssStyle += "lighter ";
                    break;
                case TextWeight.Bolder:
                    cssStyle += "bolder ";
                    break;
                default:
                    cssStyle += "defaultWeight ";
                    break;
            }

            element.innerHTML = processMarkdown(this.text);
            element.className = cssStyle;

            if (element.firstElementChild instanceof (HTMLElement)) {
                (<HTMLElement>element.firstElementChild).style.marginTop = "0px";
            }

            if (element.lastElementChild instanceof (HTMLElement)) {
                (<HTMLElement>element.lastElementChild).style.marginBottom = "0px";
            }

            var anchors = element.getElementsByTagName("a");

            for (var i = 0; i < anchors.length; i++) {
                anchors[i].target = "_blank";
            }

            if (!this.wrap) {
                element.style.whiteSpace = "nowrap";
                element.style.textOverflow = "ellipsis";
            }

            return element;
        }
        else {
            return null;
        }
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak + '\n';

        if (this.text)
            return '<s>' + this.text + '</s>\n';
        return null;
    }

    removeTopSpacing(element: HTMLElement) {
        element.style.paddingTop = "0px";
    }
}

export class Fact {
    name: string;
    value: string;
    speak: string;

    parse(json: any) {
        this.name = json["name"];
        this.value = json["value"];
        this.speak = json["speak"];
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak + '\n';
        return '<s>' + this.name + ' ' + this.value + '</s>\n';
    }
}

export class FactGroup extends CardElement {
    private _items: Array<Fact> = [];

    get items(): Array<Fact> {
        return this._items;
    }

    parse(json: any) {
        super.parse(json);

        if (json["items"] != null) {
            var factArray = json["items"] as Array<any>;

            for (var i = 0; i < factArray.length; i++) {
                let fact = new Fact();

                fact.parse(factArray[i]);

                this._items.push(fact);
            }
        }
    }

    render(): HTMLElement {
        let element: HTMLElement = null;

        if (this._items.length > 0) {
            element = document.createElement("table");
            element.className = "factGroup";

            let html: string = '';

            for (var i = 0; i < this._items.length; i++) {
                html += '<tr>';
                html += '    <td class="factName">';

                let textBlock = new TextBlock(this.container);
                textBlock.text = this._items[i].name;
                textBlock.textWeight = TextWeight.Bolder;

                let renderedText = textBlock.internalRender();

                if (renderedText != null) {
                    html += renderedText.outerHTML;
                }

                html += '    </td>';
                html += '    <td class="factValue">';

                textBlock = new TextBlock(this.container);
                textBlock.text = this._items[i].value;
                textBlock.textWeight = TextWeight.Lighter;

                renderedText = textBlock.internalRender();

                if (renderedText != null) {
                    html += renderedText.outerHTML;
                }

                html += '    </td>';
                html += '</tr>';
            }

            element.innerHTML = html;
        }

        return element;
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak + '\n';

        // render each fact 
        let speak = null;
        if (this._items.length > 0) {
            speak = '';
            for (var i = 0; i < this._items.length; i++) {
                let speech = this._items[i].renderSpeech();
                if (speech)
                    speak += speech;
            }
        }
        return '<p>' + speak + '\n</p>\n';
    }

}

export class Image extends CardElement {
    style: ImageStyle = ImageStyle.Normal;
    url: string;

    get useDefaultSizing() {
        return false;
    }

    parse(json: any) {
        super.parse(json);

        this.url = json["url"];
        this.style = stringToImageStyle(json["style"], ImageStyle.Normal);
    }

    render(): HTMLElement {
        let imageElement: HTMLImageElement = null;

        if (!Utils.isNullOrEmpty(this.url)) {
            imageElement = document.createElement("img");

            let cssStyle = "image";

            switch (this.size) {
                case Size.Auto:
                    cssStyle += " autoSize";
                    break;
                case Size.Stretch:
                    cssStyle += " stretch";
                    break;
                case Size.Small:
                    cssStyle += " small";
                    break;
                case Size.Large:
                    cssStyle += " large";
                    break;
                default:
                    cssStyle += " medium";
                    break;
            }

            if (this.style == ImageStyle.Person) {
                cssStyle += " person";
            }

            imageElement.className = cssStyle;

            imageElement.src = this.url;
        }

        return imageElement;
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak + '\n';
        return null;
    }
}

export class ImageGallery extends CardElement {
    private _items: Array<Image> = [];
    imageSize: Size = Size.Medium;

    get items(): Array<Image> {
        return this._items;
    }

    parse(json: any) {
        super.parse(json);

        this.imageSize = stringToSize(json["imageSize"], Size.Medium);

        if (json["items"] != null) {
            let imageArray = json["items"] as Array<any>;

            for (let i = 0; i < imageArray.length; i++) {
                let image = new Image(this.container);

                image.size = this.imageSize;
                image.url = imageArray[i];

                this._items.push(image);
            }
        }
    }

    render(): HTMLElement {
        let element: HTMLElement = null;

        if (this._items.length > 0) {
            element = document.createElement("div");
            element.className = "imageGallery";

            for (var i = 0; i < this._items.length; i++) {
                let renderedImage = this._items[i].internalRender();
                renderedImage.style.margin = "0px";
                renderedImage.style.marginRight = "10px";

                Utils.appendChild(element, renderedImage);
            }
        }

        return element;
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak;

        let speak = null;
        if (this._items.length > 0) {
            speak = '';
            for (var i = 0; i < this._items.length; i++) {
                speak += this._items[i].renderSpeech();
            }
        }

        return speak;
    }
}

export class Separator extends CardElement {
    parse(json: any) {
        super.parse(json);

        // Nothing else to parse
    }

    render() {
        let element = document.createElement("div");
        element.className = "separator";

        return element;
    }

    renderSpeech(): string {
        return null;
    }

}

export class Container extends CardElement {
    private _forbiddenItemTypes: Array<string>;
    private _items: Array<CardElement> = [];
    private _element: HTMLDivElement;
    private _textColor: TextColor = TextColor.Default;
    private _itemsCollectionPropertyName: string;

    private isAllowedItemType(elementType: string) {
        if (this._forbiddenItemTypes == null) {
            return true;
        }

        for (let i = 0; i < this._forbiddenItemTypes.length; i++) {
            if (elementType == this._forbiddenItemTypes[i]) {
                return false;
            }
        }

        if (this.container != null) {
            return this.container.isAllowedItemType(elementType);
        }
        else {
            return true;
        }
    }

    protected get cssClassName(): string {
        return "container";
    }

    backgroundImageUrl: string;
    backgroundColor: string;

    constructor(
        container: Container,
        forbiddenItemTypes: Array<string> = null,
        itemsCollectionPropertyName: string = "items") {
        super(container);

        this._itemsCollectionPropertyName = itemsCollectionPropertyName;
        this._forbiddenItemTypes = forbiddenItemTypes;
    }

    get items(): Array<CardElement> {
        return this._items;
    }

    get elementCount(): number {
        return this._items.length;
    }

    get hideOverflow() {
        return false;
    }

    get textColor(): TextColor {
        if (this.container == null) {
            return this._textColor == TextColor.Default ? TextColor.Dark : this._textColor;
        }

        if (this._textColor == TextColor.Default) {
            return this.container.textColor;
        }

        return this._textColor;
    }

    set textColor(value: TextColor) {
        this._textColor = value;
    }

    addElement(element: CardElement) {
        if (element != null) {
            this._items.push(element);
        }
    }

    isLastElement(element: CardElement): boolean {
        return this._items.indexOf(element) == this.elementCount - 1;
    }

    getElement(index: number): CardElement {
        return this._items[index];
    }

    showBottomSpacer(requestingElement: CardElement) {
        if (this.isLastElement(requestingElement)) {
            this._element.style.paddingBottom = null;

            if (this.container != null) {
                this.container.showBottomSpacer(this);
            }
        }
    }

    hideBottomSpacer(requestingElement: CardElement) {
        if (this.isLastElement(requestingElement)) {
            this._element.style.paddingBottom = "0px";

            if (this.container != null) {
                this.container.hideBottomSpacer(this);
            }
        }
    }

    parse(json: any) {
        super.parse(json);

        this.backgroundImageUrl = json["backgroundImage"];
        this.backgroundColor = json["backgroundColor"];

        this._textColor = stringToTextColor(json["textColor"], TextColor.Default);

        if (json[this._itemsCollectionPropertyName] != null) {
            let items = json[this._itemsCollectionPropertyName] as Array<any>;

            for (let i = 0; i < items.length; i++) {
                let elementType = items[i]["@type"];

                if (this.isAllowedItemType(elementType)) {
                    let element = CardElement.createElement(this, elementType);

                    element.parse(items[i]);

                    this.addElement(element);
                }
                else {
                    throw new Error("Elements of type " + elementType + " are not allowed in this container.");
                }
            }
        }
    }

    render(): HTMLElement {
        if (this.elementCount > 0) {
            this._element = document.createElement("div");
            this._element.className = this.cssClassName;

            if (!Utils.isNullOrEmpty(this.backgroundColor)) {
                this._element.style.backgroundColor = this.backgroundColor;
            }

            let html: string = '';
            let previousElement: CardElement = null;

            for (var i = 0; i < this.elementCount; i++) {
                let renderedElement = this.getElement(i).internalRender();

                if (renderedElement != null) {
                    if (previousElement == null) {
                        this.getElement(i).removeTopSpacing(renderedElement);
                    }

                    Utils.appendChild(this._element, renderedElement);
                }

                previousElement = this.getElement(i);
            }

            if (!Utils.isNullOrEmpty(this.backgroundImageUrl)) {
                this._element.style.backgroundImage = 'url("' + this.backgroundImageUrl + '")';
                this._element.style.backgroundRepeat = "no-repeat";
                this._element.style.backgroundSize = "cover";
            }
        }

        return this._element;
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak;

        // render each item
        let speak = null;
        if (this._items.length > 0) {
            speak = '';
            for (var i = 0; i < this._items.length; i++) {
                var result = this._items[i].renderSpeech();
                if (result)
                    speak += result;
            }
        }
        return speak;
    }

    getRootContainer(): Container {
        let currentContainer: Container = this;

        while (currentContainer.container != null) {
            currentContainer = currentContainer.container;
        }

        return currentContainer;
    }
}

export class Column extends Container {
    private get useWeight(): boolean {
        return this.size === undefined;
    }

    weight: number = 100;

    protected get cssClassName(): string {
        return "column";
    }

    parse(json: any) {
        super.parse(json);

        this.size = stringToSize(json["size"], undefined);

        if (this.size === undefined) {
            this.weight = Number(json["size"]);
        }
    }

    adjustLayout(element: HTMLElement) {
        if (this.useWeight) {
            element.style.flex = "1 1 " + this.weight + "%";
        }
        else {
            switch (this.size) {
                case Size.Stretch:
                    element.style.flex = "1 1 auto";
                    break;
                default: // Default to Auto
                    element.style.flex = "0 0 auto";
                    break;
            }
        }
    }
}

export class ColumnGroup extends CardElement {
    private _items: Array<Column> = [];

    addColumn(): Column {
        let column = new Column(this.container, ["ActionBar"]);

        this._items.push(column);

        return column;
    }

    parse(json: any) {
        super.parse(json);

        if (json["items"] != null) {
            let itemArray = json["items"] as Array<any>;

            for (let i = 0; i < itemArray.length; i++) {
                let column = this.addColumn();
                column.parse(itemArray[i]);
            }
        }
    }

    render(): HTMLElement {
        if (this._items.length > 0) {
            let element = document.createElement("div");
            element.className = "columnGroup";
            element.style.display = "flex";

            for (let i = 0; i < this._items.length; i++) {
                let renderedColumn = this._items[i].internalRender();

                Utils.appendChild(element, renderedColumn);

                if (this._items.length > 1 && i < this._items.length - 1) {
                    let spacer = document.createElement("div");
                    spacer.className = "columnSpacer";
                    spacer.style.flex = "0 0 auto";

                    Utils.appendChild(element, spacer);
                }
            }

            return element;
        }
        else {
            return null;
        }
    }

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak;

        // render each item
        let speak = '';
        if (this._items.length > 0) {
            for (var i = 0; i < this._items.length; i++) {
                speak += this._items[i].renderSpeech();
            }
        }
        return speak;
    }

}

export interface ICard {
    render(): HTMLElement;
    parse(json: any);
    OnAction(): Utils.IEvent<ICard, Action>;

}

export class AdaptiveCard implements ICard {
    // TODO: Add Input as forbidden?
    private _body = new Container(null, null, "body");
    private _actions: ActionBar = new ActionBar(this.body);
    private _onClick: Utils.EventDispatcher<AdaptiveCard, Action> = new Utils.EventDispatcher<AdaptiveCard, Action>();

    OnAction(): Utils.IEvent<ICard, Action> {
        return this._onClick;
    }

    get body() {
        return this._body;
    }

    get actions() {
        return this._actions;
    }

    parse(json: any) {
        this.body.parse(json);
        this.actions.parse(json);
    }

    render(): HTMLElement {
        let renderedContainer = this.body.internalRender();
        renderedContainer.className = "rootContainer";

        if (this.actions) {
            let actionsBar = this.actions.render();

            Utils.appendChild(renderedContainer, actionsBar);
        }

        return renderedContainer;
    }

    renderSpeech(): string {
        return this.body.renderSpeech();
    }
}

