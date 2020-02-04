import * as Adaptive from "adaptivecards";

export abstract class ProxyAdapter {
    abstract executeAction(action: Adaptive.SubmitAction): string;
}
