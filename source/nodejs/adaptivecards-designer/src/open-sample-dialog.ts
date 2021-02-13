import { SampleCatalogue, CatalogueEntry } from "./catalogue";
import * as ACData from "adaptivecards-templating";
import * as Adaptive from "adaptivecards";
import { Dialog } from "./dialog";
import { Downloader } from "./downloader";

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

        element.append(thumbnailHost, displayNameElement);

        this.entry.onDownloaded = (sender: CatalogueEntry) => {
            thumbnailHost.removeChild(spinner);

            if (sender.cardPayloadDownloaded) {
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
            else {
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
        let renderedElement = document.createElement("div");
        renderedElement.className = "acd-open-sample-item-container";
        renderedElement.setAttribute("role", "list");

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

    protected renderContent(): HTMLElement {
        this._renderedElement = document.createElement("div");
        this._renderedElement.style.overflow = "auto";

        this.setContent(this.renderMessage("Loading sample catalogue, please wait...", true));

        this.catalogue.onDownloaded = (sender: SampleCatalogue) => {
            if (sender.isDownloaded) {
                this.setContent(this.renderCatalogue());
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
