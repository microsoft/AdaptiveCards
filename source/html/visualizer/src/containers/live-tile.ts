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

    protected renderContainer(renderedCard: HTMLElement): HTMLElement {
        var element = document.createElement("div");
        element.style.width = this._width + "px";
        element.style.height = this._height + "px";
        element.style.backgroundColor = LiveTileContainer.backgroundColor;
        element.style.overflow = "hidden";

        renderedCard.style.height = "100%";

        element.appendChild(renderedCard);

        return element;
    }

    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.showCardActionMode = Adaptive.ShowCardActionMode.Popup;
        Adaptive.AdaptiveCard.renderOptions.defaultTextColor = Adaptive.TextColor.Light;
    }
}