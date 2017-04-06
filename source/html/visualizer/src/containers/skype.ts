import { HostContainer } from "./host-container";
import * as Adaptive from "adaptive-cards";
import * as Utils from "../utils";

export class SkypeContainer extends HostContainer {
    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.actionShowCardInPopup = true;
        // Adaptive.AdaptiveCard.renderOptions.defaultActionButtonStyle = Adaptive.ActionButtonStyle.Push;
    }

    render(card: Adaptive.AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        element.className = "skypeContainer";

        // Draw the hexagon bot logo
        let botElement = document.createElement("div");
        botElement.className = "hexagon";

        var botElementIn1 = document.createElement("div");
        botElementIn1.className = "hexagon-in1";
        botElement.appendChild(botElementIn1);

        var botElementIn2 = document.createElement("div");
        botElementIn2.className = "hexagon-in2";
        botElementIn1.appendChild(botElementIn2);

        //card.onAction = (action) => { alert(action.title);}
        let renderedCard = card.render();

        Utils.appendChild(element, botElement);
        Utils.appendChild(element, renderedCard);
        let hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, super.render(card));
        return hostDiv;
    }
}