// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as Adaptive from "adaptivecards";
import * as monaco from "monaco-editor";
import { Dialog, DialogButton } from "./dialog";
import { CardData } from "./open-sample-dialog";
import { JSONSchemaCard } from "adaptivecards-templating";

export class OpenJsonSchemaDialog extends Dialog {
    private _output: CardData;
    private _previewContainer: HTMLElement;
    private _previewElement: HTMLElement;
    private _editor: monaco.editor.IStandaloneCodeEditor;

    readonly submitButton: DialogButton;

    constructor() {
        super();

        this.submitButton = new DialogButton("Create");
        this.submitButton.onClick = (sender) => {
            this.close();
        }
        this.buttons = [this.submitButton];
    }

    open() {
        super.open();
        this._editor.layout();
    }

    private renderPreview(): HTMLElement {
        const renderedElement = document.createElement("div");
        renderedElement.className = "acd-open-code-dialog-preview";

        const card = new Adaptive.AdaptiveCard();

        if (this.output?.cardPayload) {
            try {
                const cardData = JSON.parse(this.output.cardPayload);
                card.parse(cardData);
            } catch (e) {
                console.error(e);
            }
        } else {
            card.parse({
                "type": "AdaptiveCard",
                "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
                "version": "1.0",
                "body": [
                    {
                        "type": "TextBlock",
                        "text": "Input JSON Schema to create a card!",
                        "wrap": true,
                        "size": "Large"
                    }
                ]
            })
        }

        card.render();
        card.renderedElement.style.width = "100%";

        renderedElement.appendChild(card.renderedElement);

        return renderedElement
    }

    private refreshPreview() {
        this._previewContainer.removeChild(this._previewElement);
        this._previewElement = this.renderPreview();
        this._previewContainer.appendChild(this._previewElement);
    }

    private renderEditor(): HTMLElement {
        const renderedElement = document.createElement("div");
        renderedElement.className = "acd-open-code-dialog-editor";

        const monaco = window["monaco"];
        this._editor = monaco.editor.create(
            renderedElement,
            {
                folding: true,
                fontSize: 13.5,
                language: 'json',
            }
        );
        this._editor.layout();

        this._editor.onDidChangeModelContent(() => {
            try {
                const model = this._editor.getValue();
                const json = JSON.parse(model);

                const card = JSONSchemaCard(json);
                this._output = {
                    cardPayload: JSON.stringify(card),
                };

                this.refreshPreview();
            } catch (e) {
                console.error(e)
            }
        });

        return renderedElement
    }

    protected renderContent(): HTMLElement {
        const renderedElement = document.createElement("div");
        renderedElement.className = "acd-open-code-dialog-container";

        const editorContainer = document.createElement("div");
        editorContainer.className = "acd-open-code-dialog-editor-container";
        renderedElement.appendChild(editorContainer);

        const editorLabel = document.createElement("h3");
        editorLabel.innerText = "JSON Schema"
        editorContainer.appendChild(editorLabel);

        const editorElement = this.renderEditor();
        editorContainer.appendChild(editorElement);

        this._previewContainer = document.createElement("div");
        this._previewContainer.className = "acd-open-code-dialog-preview-container";
        renderedElement.appendChild(this._previewContainer);

        this._previewElement = this.renderPreview()
        this._previewContainer.appendChild(this._previewElement)


        return renderedElement;
    }

    get output(): CardData {
        return this._output;
    }
}