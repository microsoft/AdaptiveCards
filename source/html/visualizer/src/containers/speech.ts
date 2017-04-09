import { HostContainer} from "./host-container";
import * as Adaptive from "adaptive-cards";
import * as Utils from "../utils";

export class SpeechContainer extends HostContainer {
    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.showCardActionMode = Adaptive.ShowCardActionMode.Inline;
    }
}