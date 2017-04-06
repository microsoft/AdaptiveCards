import { HostContainer} from "./host-container";
import * as Adaptive from "adaptive-cards";
import * as Utils from "../utils";

export class ToastContainer extends HostContainer {
    static backgroundColor: string = "#1F1F1F";
    static textColor: Adaptive.TextColor = Adaptive.TextColor.Light;

    private _width: number;

    protected renderContainer(renderedCard: HTMLElement): HTMLElement {
        var element = document.createElement("div");
        element.style.border = "#474747 1px solid";
        element.style.width = this._width + "px";
        element.style.backgroundColor = ToastContainer.backgroundColor;
        element.style.overflow = "hidden";

        element.appendChild(renderedCard);

        return element;
    }

    constructor(width: number, styleSheet: string) {
        super(styleSheet);

        this._width = width;
    }

    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.showCardActionMode = Adaptive.ShowCardActionMode.Inline;
        Adaptive.AdaptiveCard.renderOptions.defaultTextColor = Adaptive.TextColor.Light;
    }
}