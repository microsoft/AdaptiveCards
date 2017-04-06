import { HostContainer} from "./host-container";
import * as Adaptive from "adaptive-cards";
import * as Utils from "../utils";

export class CortanaCarContainer extends HostContainer {
    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.showCardActionMode = Adaptive.ShowCardActionMode.Popup;
    }

    protected renderContainer(renderedCard: HTMLElement): HTMLElement {
        var element = document.createElement("div");        
        var imgDiv = document.createElement("div");
        imgDiv.classList.add("title");
        
        var img = document.createElement("img");
        img.classList.add("image", "cortanaLogo");
        img.src = "assets/cortana-logo.png";

        imgDiv.appendChild(img);

        renderedCard.insertBefore(imgDiv, renderedCard.firstChild);

        element.appendChild(renderedCard);

        return element;
    }
}