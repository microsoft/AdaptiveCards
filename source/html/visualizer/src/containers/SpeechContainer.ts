import { HostContainer} from "./HostContainer";
import * as Adaptive from "adaptive-card-html-renderer/Adaptive";
import * as Utils from "adaptive-card-html-renderer/Utils";

export class SpeechContainer extends HostContainer {
    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.actionShowCardInPopup = false;
    }

    render(card: Adaptive.AdaptiveCard): HTMLElement {
        let hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, super.render(card, true));
        return hostDiv;
    }
}