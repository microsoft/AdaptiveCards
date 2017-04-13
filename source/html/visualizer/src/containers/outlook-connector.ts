import { HostContainer} from "./host-container";
import { ConnectorContainer } from "./connector";
import * as Adaptive from "adaptive-cards";
import * as Utils from "../utils";

export class OutlookConnectorContainer extends ConnectorContainer {
    private _themeColor: string;

    constructor(themeColor: string, styleSheet: string) {
        super(styleSheet);

        this._themeColor = themeColor;
    }

    protected renderContainer(renderedCard: HTMLElement): HTMLElement {
        var element = document.createElement("div");
        element.style.borderTop = "1px solid #F1F1F1";
        element.style.borderRight = "1px solid #F1F1F1";
        element.style.borderBottom = "1px solid #F1F1F1";

        if (Utils.isNullOrEmpty(this._themeColor)) {
            element.style.border = "1px solid #F1F1F1"
        }
        else {
            element.style.borderLeft = "3px solid " + this._themeColor;
        }

        element.appendChild(renderedCard);        

        return element;
    }
}
