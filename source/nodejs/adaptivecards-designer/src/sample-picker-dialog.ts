import { parseCatalogue, CatalogueEntry } from "./catalogue";
import * as ACData from "adaptivecards-templating";
import * as Adaptive from "adaptivecards";
import { Dialog } from "./dialog";
import { defaultHostConfig } from "./miscellaneous";
import { Downloader } from "./downloader";

export class SamplePickerDialog extends Dialog {
    private _renderedElement: HTMLElement;
    private _selectedSample: CatalogueEntry;

    private renderMessage(message: string) {
        let templatePayload = {
            type: "AdaptiveCard",
            version: "1.0",
            body: [
                {
                    type: "TextBlock",
                    text: "**{title}**",
                    size: "large"
                },
                {
                    type: "Container",
                    verticalContentAlignment: "center",
                    height: "stretch",
                    items: [
                        {
                            type: "TextBlock",
                            text: "{message}",
                            horizontalAlignment: "center",
                            wrap: true
                        }
                    ]
                },
                {
                    type: "ActionSet",
                    horizontalAlignment: "right",
                    actions: [
                        {
                            type: "Action.Submit",
                            id: "cancel",
                            title: "Cancel"
                        }
                    ]
                }
            ]
        };

        let template = new ACData.Template(templatePayload);
        
        let context = new ACData.EvaluationContext();
        context.$root = {
            title: this.title,
            message: message
        };

        let expandedCardPayload = template.expand(context);

        let card = new Adaptive.AdaptiveCard();
        card.hostConfig = defaultHostConfig;
        card.onExecuteAction = (action: Adaptive.Action) => {
            if (action.id == "cancel") {
                this.close();
            }
        }

        card.parse(expandedCardPayload, new Adaptive.SerializationContext());

        let renderedCard = card.render();
        renderedCard.style.height = "100%";

        this._renderedElement.innerHTML = "";
        this._renderedElement.appendChild(renderedCard);
    }

    private renderCatalogue(catalogue: CatalogueEntry[]) {
        let templatePayload = {
            type: "AdaptiveCard",
            version: "1.0",
            body: [
                {
                    type: "TextBlock",
                    text: "**{title}**",
                    size: "large"
                },
                {
                    type: "Container",
                    height: "stretch",
                    allowVerticalOverflow: true,
                    items: [
                        {
                            type: "Container",
                            $data: "{catalogue}",
                            minHeight: "36px",
                            verticalContentAlignment: "center",
                            selectAction: {
                                type: "Action.Submit",
                                data: {
                                    catalogueIndex: "{$index}"
                                }
                            },
                            spacing: "none",
                            items: [
                                {
                                    type: "TextBlock",
                                    text: "{displayName}",
                                    size: "medium"
                                }
                            ]
                        }
                    ]
                },
                {
                    type: "ActionSet",
                    horizontalAlignment: "right",
                    actions: [
                        {
                            type: "Action.Submit",
                            id: "cancel",
                            title: "Cancel"
                        }
                    ]
                }
            ]
        };

        let template = new ACData.Template(templatePayload);
        
        let context = new ACData.EvaluationContext();
        context.$root = {
            title: this.title,
            catalogue: catalogue
        };

        let expandedCardPayload = template.expand(context);

        let card = new Adaptive.AdaptiveCard();
        card.hostConfig = defaultHostConfig;
        card.onExecuteAction = (action: Adaptive.Action) => {
            if (action.id == "cancel") {
                this.close();
            }
            else if (action instanceof Adaptive.SubmitAction) {
                this._selectedSample = catalogue[action.data["catalogueIndex"]];

                this.close();
            }
        }

        let serializationContext = new Adaptive.SerializationContext();
        serializationContext.onParseElement = (element: Adaptive.CardElement, source: any, context: Adaptive.SerializationContext) => {
            if (element instanceof Adaptive.CardElementContainer) {
                element.allowVerticalOverflow = Adaptive.parseBool(source["allowVerticalOverflow"], false);
            }
        };

        card.parse(expandedCardPayload, serializationContext);

        let renderedCard = card.render();
        renderedCard.style.height = "100%";

        this._renderedElement.innerHTML = "";
        this._renderedElement.appendChild(renderedCard);
    }

    protected renderContent(): HTMLElement {
        this._renderedElement = document.createElement("div");
        this._renderedElement.style.overflow = "auto";

        this.renderMessage("Loading sample catalogue...");

        let downloader = new Downloader(this.catalogueUrl);
        downloader.onError = () => { this.renderMessage("The catalogue couldn't be loaded. Please try again later."); };
        downloader.onSuccess = () => {
            if (downloader.data) {
                try {
                    let catalogue = parseCatalogue(JSON.parse(downloader.data));

                    this.renderCatalogue(catalogue);
                }
                catch (e) {
                    this.renderMessage("The catalogue couldn't be loaded. Please try again later.");
                }
            }
        };
        downloader.download();

        return this._renderedElement;
    }

    catalogueUrl: string;

    get selectedSample(): CatalogueEntry {
        return this._selectedSample;
    }
}