import { HostContainer } from "./host-container";
import * as Adaptive from "adaptive-cards";
import * as Utils from "../utils";

export class SkypeContainer extends HostContainer {
    protected renderContainer(renderedCard: HTMLElement): HTMLElement {
        var element = document.createElement("div");
        element.className = "skypeContainer";

        // Draw the hexagon bot logo
        var botElement = document.createElement("div");
        botElement.className = "hexagon";

        var botElementIn1 = document.createElement("div");
        botElementIn1.className = "hexagon-in1";
        botElement.appendChild(botElementIn1);

        var botElementIn2 = document.createElement("div");
        botElementIn2.className = "hexagon-in2";
        botElementIn1.appendChild(botElementIn2);

        element.appendChild(botElement);
        element.appendChild(renderedCard);

        return element;
    }

    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.showCardActionMode = Adaptive.ShowCardActionMode.Popup;
    }
}