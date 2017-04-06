import { HostContainer} from "./host-container";
import * as Adaptive from "adaptive-cards";
import * as Utils from "../utils";

export class LiveTileContainer extends HostContainer {
    static backgroundColor: string = "#0078D7";

    private _width: number;
    private _height: number;

    constructor(width: number, height: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
        this._height = height;
        this.supportsActionBar = false;
    }

    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.actionShowCardInPopup = false;
        // Adaptive.AdaptiveCard.renderOptions.defaultActionButtonStyle = Adaptive.ActionButtonStyle.Push;
        Adaptive.AdaptiveCard.renderOptions.defaultTextColor = Adaptive.TextColor.Light;
    }

    render(card: Adaptive.AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        element.style.width = this._width + "px";
        element.style.height = this._height + "px";
        element.style.backgroundColor = LiveTileContainer.backgroundColor;
        element.style.overflow = "hidden";

        let renderedCard = card.render();
        renderedCard.style.height = "100%";

        Utils.appendChild(element, renderedCard);
        let hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, super.render(card));
        return hostDiv;
    }
}