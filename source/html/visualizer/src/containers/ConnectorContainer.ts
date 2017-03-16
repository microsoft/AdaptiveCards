import { HostContainer} from "./HostContainer";
import * as Adaptive from "adaptive-card-html-renderer/Adaptive";

export abstract class ConnectorContainer extends HostContainer {
    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.actionShowCardInPopup = false;
    }
}