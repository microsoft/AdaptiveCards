import { Size, TextSize, TextColor, TextWeight, HorizontalAlignment, ImageStyle, stringToHorizontalAlignment, stringToImageStyle, stringToSize, stringToTextColor, stringToTextSize, stringToTextWeight } from "./Enums";
import * as Utils from "./Utils";
import { CardElement, IContainer, ICard } from "./Interfaces";
import * as Factory from "./Renderer";

export class TextBlock extends CardElement {
    size: TextSize = TextSize.Normal;
    weight: TextWeight = TextWeight.Normal;
    color: TextColor = TextColor.Default;
    text: string;
    isSubtle: boolean = false;
    wrap: boolean = true;

    parse(json: any) {
        super.parse(json);

        this.text = json["text"];
        this.size = stringToTextSize(json["size"], TextSize.Normal);
        this.weight = stringToTextWeight(json["weight"], TextWeight.Normal);
        this.color = stringToTextColor(json["color"], TextColor.Default);
        this.isSubtle = json["isSubtle"];
        this.wrap = json["wrap"];
    }

    render(): HTMLElement {
        if (!Utils.isNullOrEmpty(this.text)) {
            let element = document.createElement("div");

            let cssStyle = "text ";

            switch (this.size) {
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

            let actualTextColor = this.color == TextColor.Default ? this.container.textColor : this.color;

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

            switch (this.weight) {
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

            // TODO: Fix processMarkdown
            element.innerHTML = this.text;
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

        if (json["facts"] != null) {
            var factArray = json["facts"] as Array<any>;

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
                textBlock.weight = TextWeight.Bolder;

                let renderedText = textBlock.internalRender();

                if (renderedText != null) {
                    html += renderedText.outerHTML;
                }

                html += '    </td>';
                html += '    <td class="factValue">';

                textBlock = new TextBlock(this.container);
                textBlock.text = this._items[i].value;
                textBlock.weight = TextWeight.Lighter;

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

export class Container extends CardElement implements IContainer {
    private _forbiddenItemTypes: Array<string>;
    private _items: Array<CardElement> = [];
    private _element: HTMLDivElement;
    private _textColor: TextColor = TextColor.Default;
    private _itemsCollectionPropertyName: string;

    isAllowedItemType(elementType: string) {
        if (this._forbiddenItemTypes == null) {
            return true;
        }

        for (let i = 0; i < this._forbiddenItemTypes.length; i++) {
            if (elementType == this._forbiddenItemTypes[i]) {
                return false;
            }
        }

        if (this.container != null) {            
            // TODO: support forbidden items
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
        container: IContainer,
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

            // if (this.container != null) {
            //     this.container.showBottomSpacer(this);
            // }
        }
    }

    hideBottomSpacer(requestingElement: CardElement) {
        if (this.isLastElement(requestingElement)) {
            this._element.style.paddingBottom = "0px";

            // if (this.container != null) {
            //     this.container.hideBottomSpacer(this);
            // }
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
                    let element = Factory.createCardElement(this, elementType);

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

    getRootContainer(): IContainer {
        let currentContainer: IContainer = this;

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

        if (json["columns"] != null) {
            let itemArray = json["columns"] as Array<any>;

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

