import { HostContainer} from "./host-container";
import * as Adaptive from "adaptive-cards";

export abstract class ConnectorContainer extends HostContainer {
    applyOptions() {
        super.applyOptions();
        
        Adaptive.AdaptiveCard.renderOptions.showCardActionMode = Adaptive.ShowCardActionMode.Inline;
        Adaptive.AdaptiveCard.renderOptions.defaultSeparation = Adaptive.Separation.Default;
    }
}