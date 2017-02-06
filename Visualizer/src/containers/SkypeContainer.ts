import { HostContainer} from "./hostContainer";
import { AdaptiveCard, TextColor, ActionBar, ActionButtonStyle, appendChild } from "../adaptiveCard";

export class SkypeContainer extends HostContainer {
    render(card: AdaptiveCard): HTMLElement {
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


        ActionBar.buttonStyle = ActionButtonStyle.Push;

        let renderedCard = card.render();

        appendChild(element, botElement);
        appendChild(element, renderedCard);
        let hostDiv = document.createElement("div");
        appendChild(hostDiv, element);
        appendChild(hostDiv, super.render(card));
        return hostDiv;
    }
}