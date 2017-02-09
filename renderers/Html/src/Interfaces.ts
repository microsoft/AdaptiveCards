import * as Utils from "./Utils";
import { TextColor, ImageStyle, TextSize, TextWeight, Size, HorizontalAlignment, stringToSize, stringToHorizontalAlignment } from "./Enums";

export interface IAction { 

}

export interface ICard {
    render(): HTMLElement;
    renderSpeech(): any;
    parse(json: any);
    OnAction(): Utils.IEvent<ICard, IAction>;
}

export interface IContainer {
    textColor: TextColor
    speak: string;
    horizontalAlignment: HorizontalAlignment;
    container: IContainer;
    isAllowedItemType(elementType: string);
}

export abstract class CardElement {

    private _container: IContainer;

    speak: string;
    size: Size = Size.Auto;
    horizontalAlignment: HorizontalAlignment = HorizontalAlignment.Left;

    constructor(container: IContainer) {
        this._container = container;
    }

    get container(): IContainer {
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