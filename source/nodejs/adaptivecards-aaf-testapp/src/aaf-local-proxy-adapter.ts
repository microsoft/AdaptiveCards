import * as AAF from "adaptivecards-aaf";
import * as Adaptive from "adaptivecards";
import * as Shared from "./shared";

export class LocalProxyAdapter extends AAF.ProxyAdapter {
    executeAction(action: Adaptive.SubmitAction): string {
        return JSON.stringify(Shared.sampleRefreshCard);
    }
}
