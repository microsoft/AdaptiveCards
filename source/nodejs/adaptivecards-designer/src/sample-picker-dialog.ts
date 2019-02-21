import { parseCatalogue, CatalogueEntry } from "./catalogue";
import { Template } from "./template-engine/template-engine";
import { EvaluationContext } from "./template-engine/expression-parser";
import * as Adaptive from "adaptivecards";
import { Dialog } from "./dialog";
import { defaultHostConfig } from "./miscellaneous";
import { Downloader } from "./downloader";

export class SamplePickerDialog extends Dialog {
    private _renderedElement: HTMLElement;
    private _selectedSample: CatalogueEntry;

    private renderMessage(message: string) {
        let messageElement = document.createElement("div");
        messageElement.className = "acd-sample-picker-message";
        messageElement.innerText = message;

        this._renderedElement.innerHTML = "";
        this._renderedElement.appendChild(messageElement);
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

        let template = new Template(templatePayload);
        
        let context = new EvaluationContext();
        context.$root = {
            title: this.title,
            catalogue: catalogue
        };

        let expandedCardPayload = template.expand(context);

        let card = new Adaptive.AdaptiveCard();
        card.hostConfig = defaultHostConfig;
        card.hostConfig.alwaysAllowBleed = true;
        card.onExecuteAction = (action: Adaptive.Action) => {
            if (action.id == "cancel") {
                this.close();
            }
            else if (action instanceof Adaptive.SubmitAction) {
                this._selectedSample = catalogue[action.data["catalogueIndex"]];

                this.close();
            }
        }
        card.onParseElement = (element: Adaptive.CardElement, json: any, errors?: Adaptive.IValidationError[]) => {
            if (element instanceof Adaptive.CardElementContainer) {
                element.allowVerticalOverflow = Adaptive.getBoolValue(json["allowVerticalOverflow"], false);
            }
        }
        card.parse(expandedCardPayload);

        let renderedCard = card.render();
        renderedCard.style.height = "100%";

        this._renderedElement.innerHTML = "";
        this._renderedElement.appendChild(renderedCard);
    }

    protected renderContent(): HTMLElement {
        this._renderedElement = document.createElement("div");
        this._renderedElement.style.overflow = "auto";

        this.renderMessage("Loading sample catalogue...");

        /*
        let request = new XMLHttpRequest();
        request.onerror = () => {
            this.renderMessage("The catalogue couldn't be loaded. Please try again later.");
        }
        request.onload = () => {
            if (request.responseText && request.responseText != "") {
                try {
                    let catalogue = parseCatalogue(JSON.parse(request.responseText));

                    this.renderCatalogue(catalogue);
                }
                catch (e) {
                    this.renderMessage("The catalogue couldn't be loaded. Please try again later.");
                }
            }
        };

        try {
            request.open("GET", this.catalogueUrl, true);
            request.send();
        }
        catch (e) {
            this.renderMessage("The catalogue couldn't be loaded. Please try again later.");
        }
        */

        let downloader = new Downloader(this.catalogueUrl);
        downloader.onError = () => { this.renderMessage("The catalogue couldn't be loaded. Please try again later."); };
        downloader.onSuccess = () => {
            if (!Adaptive.isNullOrEmpty(downloader.data)) {
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