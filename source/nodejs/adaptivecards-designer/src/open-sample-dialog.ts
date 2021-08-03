// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as ACData from "adaptivecards-templating";
import * as Adaptive from "adaptivecards";
import { CatalogueEntry, SampleCatalogue } from "./catalogue";
import { Dialog } from "./dialog";

export interface CardData {
    cardPayload?: string
    sampleData?: string
    thumbnail?: HTMLElement | (() => HTMLElement)
}

type CardDataCallback = (output: CardData) => any;
type CardDataProvider = (callback?: CardDataCallback) => CardData | void;

interface OpenSampleItemProps {
    label: string,
    onClick?: (ev: MouseEvent) => any
    cardData?: CardData | CardDataProvider,
}

class OpenSampleItem {
    onComplete: CardDataCallback

    constructor(readonly props: OpenSampleItemProps) { }

    private static _id = 0;
    private static getNewItemId(prefix: string): string {
        const newId = prefix + "-" + OpenSampleItem._id;

        OpenSampleItem._id++;

        return newId;
    }

    render(): HTMLElement {
        const newItemId = OpenSampleItem.getNewItemId("acd-open-sample-item-title");

        const element = document.createElement("div");
        element.className = "acd-open-sample-item";
        element.tabIndex = 0;
        element.setAttribute("aria-labelledBy", newItemId);
        element.setAttribute("role", "listitem");
        element.onclick = this.props.onClick ?? (
            (e) => {
                if (this.onComplete) {
                    if (this.props.cardData instanceof Function) {
                        const cardData = this.props.cardData(this.onComplete);
                        if (cardData) {
                            this.onComplete(cardData);
                        }
                    } else if (this.props.cardData) {
                        this.onComplete(this.props.cardData);
                    }
                }
            })

        const thumbnailHost = document.createElement("div");
        thumbnailHost.className = "acd-open-sample-item-thumbnail";

        if (this.props.cardData instanceof Function) {
            const spinner = document.createElement("div");
            spinner.className = "acd-spinner";
            spinner.style.width = "28px";
            spinner.style.height = "28px";

            thumbnailHost.appendChild(spinner);

            const cardData = this.props.cardData((cardData: CardData) => {
                thumbnailHost.removeChild(spinner);
                if (cardData.thumbnail instanceof Function) {
                    thumbnailHost.appendChild(cardData.thumbnail())
                } else if (cardData.thumbnail) {
                    thumbnailHost.appendChild(cardData.thumbnail)
                }
            })

            if (cardData) {
                thumbnailHost.removeChild(spinner);
                if (cardData.thumbnail instanceof Function) {
                    thumbnailHost.appendChild(cardData.thumbnail())
                } else if (cardData.thumbnail) {
                    thumbnailHost.appendChild(cardData.thumbnail)
                }
            }
        } else if (this.props.cardData) {
            if (this.props.cardData.thumbnail instanceof Function) {
                thumbnailHost.appendChild(this.props.cardData.thumbnail())
            } else if (this.props.cardData.thumbnail) {
                thumbnailHost.appendChild(this.props.cardData.thumbnail)
            }
        }

        const displayNameElement = document.createElement("div");
        displayNameElement.className = "acd-open-sample-item-title";
        displayNameElement.id = newItemId;
        displayNameElement.innerText = this.props.label;

        element.appendChild(thumbnailHost);
        element.appendChild(displayNameElement);

        return element;
    }
}


export interface OpenSampleDialogProps {
    handlers?: (OpenSampleItemProps | null)[],
    catalogue?: SampleCatalogue,
}

export class OpenSampleDialog extends Dialog {
    private _output: CardData;
    private static _builtinItems: OpenSampleItemProps[] = [
        {
            label: "Blank Card",
            cardData: {
                cardPayload: JSON.stringify(
                    {
                        type: "AdaptiveCard",
                        $schema: "http://adaptivecards.io/schemas/adaptive-card.json",
                        version: "1.0",
                        body: [
                        ]
                    }
                ),
            },
        },
    ];

    constructor(readonly props: OpenSampleDialogProps) {
        super();
    }

    private renderSection(title: string | null, items: (OpenSampleItemProps | null)[]): HTMLElement {
        const renderedElement = document.createElement("div");

        if (title) {
            const titleElement = document.createElement("div");
            titleElement.className = "acd-dialog-title";
            titleElement.innerText = title;
            titleElement.style.marginTop = "10px";

            renderedElement.appendChild(titleElement);
        }

        const listElement = document.createElement("div");
        listElement.className = "acd-open-sample-item-container";
        listElement.setAttribute("role", "list");

        for (const item of items) {
            if (!item) continue;
            const itemElement = new OpenSampleItem(item);
            itemElement.onComplete = (output: CardData) => {
                this._output = output;
                this.close();
            }

            listElement.appendChild(itemElement.render());
        }

        renderedElement.appendChild(listElement);

        return renderedElement;
    }

    protected renderContent(): HTMLElement {
        const renderedElement = document.createElement("div");
        renderedElement.style.overflow = "auto";

        const featuredSection = this.renderSection(null, OpenSampleDialog._builtinItems.concat(this.props.handlers))
        renderedElement.appendChild(featuredSection);

        if (this.props.catalogue) {
            const divider = document.createElement("hr");
            renderedElement.appendChild(divider);

            this.props.catalogue.onDownloaded = (sender: SampleCatalogue) => {
                if (sender.isDownloaded) {
                    const catalogueSection = this.renderSection("Explore",
                        this.props.catalogue.entries.map((entry: CatalogueEntry) => {
                            return {
                                label: entry.displayName,
                                cardData: (callback) => {
                                    entry.onDownloaded = (sender: CatalogueEntry) => {
                                        let success: boolean = sender.cardPayloadDownloaded;

                                        if (success) {
                                            try {
                                                const cardPayload = JSON.parse(sender.cardPayload);
                                                const card = new Adaptive.AdaptiveCard();
                                                const cardData = sender.sampleData ?
                                                    new ACData.Template(cardPayload).expand(
                                                        {
                                                            $root: JSON.parse(sender.sampleData)
                                                        }
                                                    )
                                                    : cardPayload
                                                    ;

                                                card.parse(cardData);
                                                card.render();
                                                card.renderedElement.style.width = "100%";

                                                return callback({
                                                    cardPayload: entry.cardPayload,
                                                    sampleData: entry.sampleData,
                                                    thumbnail: card.renderedElement,
                                                });
                                            }
                                            catch (e) {
                                                // Swallow the exception
                                                console.error("Unable to load card sample. Error: " + e);

                                                success = false;
                                            }
                                        }
                                    };
                                    entry.download();
                                },
                            }
                        })
                    );
                    renderedElement.appendChild(catalogueSection);
                }
                else {
                    console.error("Sender is not downloaded");
                }
            };


            this.props.catalogue.download();
        }

        const firstChild = featuredSection.firstElementChild as HTMLElement;
        firstChild.focus();

        return renderedElement;
    }

    get output(): CardData {
        return this._output;
    }
}