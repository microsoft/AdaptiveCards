import * as Adaptive from "adaptivecards";
import * as Templating from "adaptivecards-templating";
import { ChannelAdapter } from "./channel-adapter";

export class AdaptiveAppHost {
    private _card: Adaptive.AdaptiveCard | undefined;
    private _cardPayload: any;
    private _cardData: any;

    private internalReset() {
        // TODO
    }

    private internalExecuteAction(action: Adaptive.Action) {
        if (action instanceof Adaptive.SubmitAction) {
            if (this.channelAdapter) {
                let result = this.channelAdapter.executeAction(action);
                let parsedResult: any = undefined;

                try {
                    parsedResult = JSON.parse(result);
                }
                catch {
                    parsedResult = result;
                }

                if (typeof parsedResult === "string") {
                    alert(parsedResult);
                }
                else if (typeof parsedResult === "object") {
                    this.initialize(parsedResult, this._cardData);
                }
                else {
                    alert("Result is of unsupported type (" + typeof parsedResult + ")");
                }
            }
            else {
                alert("No proxy adapter set.");
            }
        }
    }

    readonly renderedElement: HTMLElement;

    channelAdapter: ChannelAdapter | undefined = undefined;

    constructor() {
        this.renderedElement = document.createElement("div");
    }

    initialize(cardPayload: any, cardData?: any) {
        try {
            let evaluationContext = new Templating.EvaluationContext();
            evaluationContext.$root = cardData;

            let template = new Templating.Template(cardPayload)
            let expandedCardPayload = template.expand(evaluationContext);

            let card = new Adaptive.AdaptiveCard();
            card.parse(expandedCardPayload);

            this._cardPayload = cardPayload;
            this._cardData = cardData;

            this._card = card;
            this._card.onExecuteAction = (action: Adaptive.Action) => {
                this.internalExecuteAction(action);
            }

            while (this.renderedElement.firstChild) {
                this.renderedElement.removeChild(this.renderedElement.firstChild);
            }

            this._card.render();

            if (this._card.renderedElement) {
                this.renderedElement.appendChild(this._card.renderedElement)

                this.internalReset();
            }
        }
        catch {
            // Ignore all errors
        }
    }
}
