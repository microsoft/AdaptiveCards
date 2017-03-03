import { HostContainer} from "./HostContainer";
import { ConnectorContainer } from "./ConnectorContainer";
import * as Adaptive from "../../Adaptive";
import * as Utils from "../../Utils";

export class OutlookConnectorContainer extends ConnectorContainer {
    private _themeColor: string;

    constructor(themeColor: string, styleSheet: string) {
        super(styleSheet);

        this._themeColor = themeColor;
    }

    render(card: Adaptive.AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        element.style.borderTop = "1px solid #F1F1F1";
        element.style.borderRight = "1px solid #F1F1F1";
        element.style.borderBottom = "1px solid #F1F1F1";

        if (Utils.isNullOrEmpty(this._themeColor)) {
            element.style.border = "1px solid #F1F1F1"
        }
        else {
            element.style.borderLeft = "3px solid " + this._themeColor;
        }

        let renderedCard = card.render();

        Utils.appendChild(element, renderedCard);
        let hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, super.render(card));
        return hostDiv;
    }
}
