import { HostContainer} from "./hostContainer";
import { AdaptiveCard, appendChild } from "../adaptiveCard";


export class SpeechContainer extends HostContainer {

    render(card: AdaptiveCard): HTMLElement {
        let hostDiv = document.createElement("div");
        appendChild(hostDiv, super.render(card, true));
        return hostDiv;
    }
}