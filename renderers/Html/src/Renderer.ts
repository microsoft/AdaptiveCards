import { ICard, IContainer, CardElement } from "./Interfaces";
import { Column, ColumnSet, Container, Fact, FactSet, Image, ImageSet, TextBlock } from "./Elements";
import { ActionBar, Action, ActionButton, ActionButtonStyle } from "./Actions";
import { InputBase, InputText, InputDate, Choice, InputChoiceSet, InputToggle } from "./Inputs";
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
        case "ImageSet":
            return new ImageSet(container);
        case "FactSet":
            return new FactSet(container);
        case "ColumnSet":
            return new ColumnSet(container);
        case "Input.Text":
            return new InputText(container);
        case "Input.Number":
            return new InputText(container);
        case "Input.Date":
            return new InputDate(container);
        case "Input.ChoiceSet":
            return new InputChoiceSet(container);
        case "Inpu.Toggle":
            return new InputToggle(container);
        default:
            throw new Error("Unknown element type: " + typeName);
    }
}