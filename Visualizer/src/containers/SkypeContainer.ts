import { HostContainer } from "./HostContainer";
import * as Adaptive from "../Adaptive";
import * as Utils from "../Utils";

export class SkypeContainer extends HostContainer {
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


        Adaptive.ActionBar.buttonStyle = Adaptive.ActionButtonStyle.Push;

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