import { ICard, IContainer, CardElement } from "./Interfaces";
import { Column, ColumnGroup, Container, Fact, FactGroup, Image, ImageGallery, Separator, TextBlock } from "./Elements";
import { ActionBar, Action, ActionButton, ActionButtonStyle } from "./Actions";
import { InputBase, TextInput, DateInput, Choice, MultichoiceInput, ToggleInput } from "./Inputs";
import { AdaptiveCard } from "./AdaptiveCard";

export class Renderer {

    parseCard(json: string): AdaptiveCard {
        var card = new AdaptiveCard();
        card.parse(json);
        return card;
    }

    render(card: ICard): HTMLElement {
        return card.render();
    }
}


export function createCardElement(container: IContainer, typeName: string): CardElement {
    switch (typeName) {
        case "Container":
            return new Container(container);
        case "TextBlock":
            return new TextBlock(container);
        case "Image":
            return new Image(container);
        case "ImageGallery":
            return new ImageGallery(container);
        case "ActionBar":
            return new ActionBar(container);
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