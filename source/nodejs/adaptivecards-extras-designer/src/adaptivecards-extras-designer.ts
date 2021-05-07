import { CardDesignerSurface } from "adaptivecards-designer";
import { ProgressBar } from "adaptivecards-extras";
import { ProgressBarPeer } from "./progress-bar-designer";

export * from "./progress-bar-designer";

export function initializeDesignerSupport() {
    CardDesignerSurface.cardElementPeerRegistry.registerPeer(ProgressBar, ProgressBarPeer, "Extras");
}