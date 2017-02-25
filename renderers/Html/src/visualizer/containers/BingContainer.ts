import { HostContainer} from "./HostContainer";
import * as Adaptive from "../../Adaptive";
import * as Utils from "../../Utils";

export class BingContainer extends HostContainer {
    static backgroundColor: string = "#fff";
    static textColor: Adaptive.TextColor = Adaptive.TextColor.Dark;

    private _width: number;
    private _height: number;

    constructor(width: number, height: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
        this._height = height;
    }

    applyOptions() {
        Adaptive.AdaptiveCard.options.actionShowCardInPopup = false;
    }

    render(card: Adaptive.AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        element.style.width = this._width + "px";
        element.style.height = this._height + "px";
        element.style.backgroundColor = BingContainer.backgroundColor;
        element.style.overflow = "hidden";

        card.root.textColor = BingContainer.textColor;

        Adaptive.Container.defaultActionButtonStyle = Adaptive.ActionButtonStyle.Push;

        let renderedCard = card.render();
        renderedCard.style.height = "100%";

        Utils.appendChild(element, renderedCard);
        let hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, super.render(card));
        return hostDiv;
    }
}