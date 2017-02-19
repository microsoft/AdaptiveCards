import * as Utils from "./Utils";
import { TextColor, ImageStyle, TextSize, TextWeight, HorizontalAlignment, stringToImageSize, stringToHorizontalAlignment } from "./Enums";

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
    container: IContainer;
    isAllowedItemType(elementType: string);
}

export abstract class CardElement {

    private _container: IContainer;

    speak: string;

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
            element.className += " stretch";
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
    }
}