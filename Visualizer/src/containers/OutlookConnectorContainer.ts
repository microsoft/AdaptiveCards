import { HostContainer} from "./hostContainer";
import { ConnectorContainer } from "./connectorContainer";
import { AdaptiveCard, TextColor, ActionBar, ActionButtonStyle, isNullOrEmpty, appendChild } from "../adaptiveCard";

export class OutlookConnectorContainer extends ConnectorContainer {
    private _themeColor: string;

    constructor(themeColor: string, styleSheet: string) {
        super(styleSheet);

        this._themeColor = themeColor;
    }

    render(card: AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        element.style.borderTop = "1px solid #F1F1F1";
        element.style.borderRight = "1px solid #F1F1F1";
        element.style.borderBottom = "1px solid #F1F1F1";

        if (isNullOrEmpty(this._themeColor)) {
            element.style.border = "1px solid #F1F1F1"
        }
        else {
            element.style.borderLeft = "3px solid " + this._themeColor;
        }

        let headerElement = this.renderHeader(card);

        if (headerElement != null) {
            appendChild(element, headerElement);
        }

        ActionBar.buttonStyle = ActionButtonStyle.Link;

        let renderedCard = card.render();

        appendChild(element, renderedCard);
        let hostDiv = document.createElement("div");
        appendChild(hostDiv, element);
        appendChild(hostDiv, super.render(card));
        return hostDiv;
    }
}
