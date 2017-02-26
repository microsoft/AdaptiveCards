import { HostContainer} from "./HostContainer";
import * as Adaptive from "../../Adaptive";
import * as Utils from "../../Utils";

export class SpeechContainer extends HostContainer {
    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.options.actionShowCardInPopup = false;
    }

    render(card: Adaptive.AdaptiveCard): HTMLElement {
        let hostDiv = document.createElement("div");
        Utils.appendChild(hostDiv, super.render(card, true));
        return hostDiv;
    }
}