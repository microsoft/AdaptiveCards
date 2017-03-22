import { HostContainer} from "./HostContainer";
import * as Adaptive from "adaptive-cards";

export abstract class ConnectorContainer extends HostContainer {
    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.actionShowCardInPopup = false;
    }
}