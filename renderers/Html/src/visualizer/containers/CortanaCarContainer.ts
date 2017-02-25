import { HostContainer} from "./HostContainer";
import * as Adaptive from "../../Adaptive";
import * as Utils from "../../Utils";

export class CortanaCarContainer extends HostContainer {
    applyOptions() {
        Adaptive.AdaptiveCard.options.actionShowCardInPopup = true;
    }

    render(card: Adaptive.AdaptiveCard): HTMLElement {
        let element = document.createElement("div");
        
        Adaptive.Container.defaultActionButtonStyle = Adaptive.ActionButtonStyle.Link;

        let renderedCard = card.render();

        let imgDiv = document.createElement("div");
        imgDiv.classList.add("title");
        
        let img = document.createElement("img");
        img.classList.add("image", "cortanaLogo");
        img.src = "./../../assets/cortana-logo.png";
        Utils.appendChild(imgDiv, img);
        renderedCard.insertBefore(imgDiv, renderedCard.firstChild);

        Utils.appendChild(element, renderedCard);
        let hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, element);
        Utils.appendChild(hostDiv, super.render(card));
        return hostDiv;
    }
}