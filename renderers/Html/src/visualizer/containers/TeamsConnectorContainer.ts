import { HostContainer} from "./HostContainer";
import { ConnectorContainer } from "./ConnectorContainer";
import * as Adaptive from "../../Adaptive";
import * as Utils from "../../Utils";

export class TeamsConnectorContainer extends ConnectorContainer {
    render(card: Adaptive.AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        element.style.borderTop = "1px solid #F1F1F1";
        element.style.borderRight = "1px solid #F1F1F1";
        element.style.borderBottom = "1px solid #F1F1F1";
        element.style.border = "1px solid #F1F1F1"

        let renderedCard = card.render();

        Utils.appendChild(element, renderedCard);
        let hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, super.render(card));
        return hostDiv;
    }
}
