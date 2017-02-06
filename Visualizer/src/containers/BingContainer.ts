import { HostContainer} from "./hostContainer";
import { AdaptiveCard, TextColor, ActionBar, ActionButtonStyle, appendChild } from "../adaptiveCard";

export class BingContainer extends HostContainer {
    static backgroundColor: string = "#fff";
    static textColor: TextColor = TextColor.Dark;

    private _width: number;
    private _height: number;

    constructor(width: number, height: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
        this._height = height;
    }

    render(card: AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        element.style.width = this._width + "px";
        element.style.height = this._height + "px";
        element.style.backgroundColor = BingContainer.backgroundColor;
        element.style.overflow = "hidden";

        card.body.textColor = BingContainer.textColor;

        ActionBar.buttonStyle = ActionButtonStyle.Push;

        let renderedCard = card.render();
        renderedCard.style.height = "100%";

        appendChild(element, renderedCard);
        let hostDiv = document.createElement("div");
        appendChild(hostDiv, element);
        appendChild(hostDiv, super.render(card));
        return hostDiv;
    }
}