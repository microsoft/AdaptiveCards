import { HostContainer} from "./HostContainer";
import * as Adaptive from "../../Adaptive";

export abstract class ConnectorContainer extends HostContainer {
    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.actionShowCardInPopup = false;
        Adaptive.AdaptiveCard.renderOptions.defaultSeparation = Adaptive.Separation.Default;
    }
}