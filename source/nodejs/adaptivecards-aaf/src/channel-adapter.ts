import * as Adaptive from "adaptivecards";

export abstract class ChannelAdapter {
    abstract executeAction(action: Adaptive.SubmitAction): string;
}
