// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { SampleCatalogue, CatalogueEntry } from "./catalogue";
import * as ACData from "adaptivecards-templating";
import * as Adaptive from "adaptivecards";
import { Dialog } from "./dialog";
import { Pic2Card } from "./pic2card";

class CatalogueItem {
    onClick: (sender: CatalogueItem) => void;

    constructor(readonly entry: CatalogueEntry) { }

    private static _id = 0;
    private static getNewItemId(prefix: string): string {
        let newId = prefix + "-" + CatalogueItem._id;

        CatalogueItem._id++;

        return newId;
    }

    render(): HTMLElement {
        const newItemId = CatalogueItem.getNewItemId("acd-open-sample-item-title");

        let element = document.createElement("div");
        element.className = "acd-open-sample-item";
        element.tabIndex = 0;
        element.setAttribute("aria-labelledBy", newItemId);
        element.setAttribute("role", "listitem");
        element.onclick = (e) => {
            if (this.onClick) {
                this.onClick(this);
            }
        }

        let thumbnailHost = document.createElement("div");
        thumbnailHost.className = "acd-open-sample-item-thumbnail";

        let spinner = document.createElement("div");
        spinner.className = "acd-spinner";
        spinner.style.width = "28px";
        spinner.style.height = "28px";

        thumbnailHost.appendChild(spinner);

        let displayNameElement = document.createElement("div");
        displayNameElement.className = "acd-open-sample-item-title";
        displayNameElement.id = newItemId;
        displayNameElement.innerText = this.entry.displayName;

        element.appendChild(thumbnailHost);
        element.appendChild(displayNameElement);

        this.entry.onDownloaded = (sender: CatalogueEntry) => {
            thumbnailHost.removeChild(spinner);

            let success: boolean = sender.cardPayloadDownloaded;

            if (success) {
                try {
                    let cardPayload = JSON.parse(sender.cardPayload);

                    if (sender.sampleData) {
                        let template = new ACData.Template(cardPayload);

                        cardPayload = template.expand(
                            {
                                $root: JSON.parse(sender.sampleData)
                            }
                        );
                    }

                    let card = new Adaptive.AdaptiveCard();
                    card.parse(cardPayload);
                    card.render();
                    card.renderedElement.style.width = "100%";

                    thumbnailHost.appendChild(card.renderedElement);
                }
                catch (e) {
                    // Swallow the exception
                    console.error("Unable to load card sample. Error: " + e);

                    success = false;
                }
            }

            if (!success) {
                let errorMessage = document.createElement("div");
                errorMessage.className = "acd-dialog-message";
                errorMessage.innerText = "Preview not available";

                thumbnailHost.appendChild(errorMessage);
            }
        }
        this.entry.download();

        return element;
    }
}

export class OpenSampleDialog extends Dialog {
    private _renderedElement: HTMLElement;
    private _selectedSample: CatalogueEntry;

    private setContent(element: HTMLElement) {
        while (this._renderedElement.firstChild) {
            this._renderedElement.removeChild(this._renderedElement.firstChild);
        }

        if (element) {
            this._renderedElement.appendChild(element);
        }
    }

    private renderMessage(message: string, showSpinner: boolean): HTMLElement {
        let messageHostElement = document.createElement("div");
        messageHostElement.style.display = "flex";
        messageHostElement.style.flexDirection = "column";
        messageHostElement.style.alignItems = "center";
        messageHostElement.style.justifyContent = "center";
        messageHostElement.style.height = "100%";

        if (showSpinner) {
            let spinnerElement = document.createElement("div");
            spinnerElement.className = "acd-spinner";
            spinnerElement.style.width = "28px";
            spinnerElement.style.height = "28px";

            messageHostElement.appendChild(spinnerElement);
        }

        let textElement = document.createElement("div");
        textElement.className = "acd-dialog-message";
        textElement.innerText = message;
        textElement.style.marginTop = "10px";

        messageHostElement.appendChild(textElement);

        return messageHostElement;
    }

    private renderCatalogue(): HTMLElement {
        const pic2cardService = Pic2Card.pic2cardService !== '' ? Pic2Card.pic2cardService : process.env.PIC_TO_CARD_PREDICTION_API;
        let renderedElement = document.createElement("div");
        renderedElement.className = "acd-open-sample-item-container";
        renderedElement.setAttribute("role", "list");

        // add pic2card option only if pic2card service url configured
        if(pic2cardService && pic2cardService !== '') {
            renderedElement.appendChild(this.renderImageOption());
        }
        
        for (let entry of this.catalogue.entries) {
            let item = new CatalogueItem(entry);
            item.onClick = (sender: CatalogueItem) => {
                this._selectedSample = sender.entry;

                this.close();
            }

            renderedElement.appendChild(item.render());
        }

        return renderedElement;
    }

    protected renderImageOption(): HTMLElement {
        const imageOption = document.createElement("div");
        const pic2CardID = "PIC_2_CARD";
        imageOption.className = "acd-image-container";
        imageOption.innerHTML = `<div class="acd-image-upload acd-open-sample-item"><img alt="pic2card image" src="data:image/png;base64,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" />
            <div class="acd-image-text-container"><div class="acd-image-new-title">NEW PREVIEW</div>
            <div class="acd-image-upload-title">Create from Image </div>
            <div class="acd-image-description">Upload your own image and convert it magically to an Adaptive card</div><input class="acd-try-now-button" value="Try Now" type="button" /></div></div><div class="acd-open-sample-item-title">Create from Image</div>`;
        imageOption.addEventListener("click", () => {
            this._selectedSample = new CatalogueEntry("Create From Image (Preview)", "", "", pic2CardID);
            this.close();
        });

        return imageOption;
    }

    protected renderContent(): HTMLElement {
        this._renderedElement = document.createElement("div");
        this._renderedElement.style.overflow = "auto";

        this.setContent(this.renderMessage("Loading sample catalogue, please wait...", true));

        this.catalogue.onDownloaded = (sender: SampleCatalogue) => {
            if (sender.isDownloaded) {
                let catalogue = this.renderCatalogue();
                this.setContent(catalogue);

                // now set focus on the first card in the catalog (usually the Blank Card)
                let firstChild = catalogue.firstElementChild as HTMLElement;
                firstChild.focus();
            }
            else {
                this.setContent(this.renderMessage("The catalogue couldn't be loaded. Please try again later.", false));
            }
        };
        this.catalogue.download();

        return this._renderedElement;
    }

    constructor(readonly catalogue: SampleCatalogue) {
        super();
    }

    get selectedSample(): CatalogueEntry {
        return this._selectedSample;
    }
}
