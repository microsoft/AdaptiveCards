// Copyright (C) Microsoft Corporation. All rights reserved.
import * as AC from 'adaptivecards';
import * as markdownit from 'markdown-it';
import * as monaco from 'monaco-editor/esm/vs/editor/editor.api'

/**
 * Our input change handler for 'file-picker'
 * @param {Event} e The change event
 */
function fileChosen(e: Event): void {
    // get input element
    const fileInputElem = <HTMLInputElement>e.target;

    // get file list
    const fileList = fileInputElem.files;
    if (fileList.length === 1) {
        // only render a card if a file was chosen
        setTimeout(() => onCardChosen(fileList[0]), 0);
    }
}

/**
 * Remove all child elements from supplied element.
 * @param {HTMLElement} element
 */
function clearChildren(element: HTMLElement): void {
    while (element.lastElementChild) {
        element.removeChild(element.lastElementChild);
    }
}

/**
 * Given the supplied json string, render the card to the 'card-target' element.
 * @param {string} json
 */
function renderAdaptiveCard(json: string): void {
    // get element we want to render to
    const renderTarget = document.getElementById('card-target');

    // clear any existing children (in case this isn't the first card we've
    // rendered)
    clearChildren(renderTarget);

    // if we actually have a payload, attempt to parse/render it
    if (json.length > 0) {
        // render the adaptive card
        const adaptiveCard = new AC.AdaptiveCard();
        const context = new AC.SerializationContext();

        // errors will appended as children to this element
        const errorTarget = document.getElementById('errors');

        try {
            // attempt to parse
            adaptiveCard.parse(JSON.parse(json), context);

            if (context.eventCount >= 0) {
                // we got some errors - we should display them
                clearChildren(errorTarget);

                // iterate over errors and add them
                for (let i = 0; i < context.eventCount; i++) {
                    const errorEvent = context.getEventAt(i);
                    const errorDiv = document.createElement("div");
                    errorDiv.textContent = errorEvent.message;
                    errorTarget.appendChild(errorDiv);
                }
            }
        }
        catch (e) {
            // encountered an exception while parsing -- we should display the error
            clearChildren(errorTarget);
            const exceptionDiv = document.createElement("div");
            exceptionDiv.textContent = e.toString();
            errorTarget.appendChild(exceptionDiv);
        }

        // attempt to render card to the target
        adaptiveCard.render(renderTarget);

        // note that you could also choose to render to a local HTMLElement
        // object like this:
        //   let myRenderedCard = adaptiveCard.render();
    }
}

/**
 * Reads card from the supplied file and then renders it.
 * @param {File} jsonFile File to render as an Adaptive Card
 */
function onCardChosen(jsonFile: File): void {
    // read text out of chosen file
    const textPromise = jsonFile.text();

    // file content ready
    textPromise.then((fileContent) => {
        // load card value into editor
        monacoEditor.setValue(fileContent);

        // render new card
        renderAdaptiveCard(fileContent);
    });
}

// wire up file picker change event handler
document.getElementById('file-picker').addEventListener('change', fileChosen);

// enable markdown processing
AC.AdaptiveCard.onProcessMarkdown = function(text, result) {
    result.outputHtml = markdownit().render(text);
    result.didProcess = true;
};

// handle AdaptiveCard actions
AC.AdaptiveCard.onExecuteAction = (action: AC.Action) => {
    let message = `Action invoked:\nTitle: ${action.title}\nType: ${action.getJsonTypeName()}`;

    // show action-specific information
    if (action instanceof AC.OpenUrlAction) {
        message += `\nURL: ${action.url}`;
    }
    else if (action instanceof AC.SubmitAction) {
        message += `\nData: ${JSON.stringify(action.data)}`;
    }

    alert(message);

    // custom action handling like opening a URL or posting submits to a REST
    // endpoint would go here.
}

// make initial editor load trigger a card render
monaco.editor.onDidCreateEditor(function(e) {
    setTimeout(() => { renderAdaptiveCard(e.getValue()) }, 0);
});

// create monaco JSON editor
let monacoEditor = monaco.editor.create(document.getElementById('json-editor'), {
    value: `{
	"type": "AdaptiveCard",
	"$schema": "https://adaptivecards.io/schemas/adaptive-card.json",
	"version": "1.5",
    "body": [
        {
            "type": "TextBlock",
            "text": "Sample card text"
        }
    ]
}`,
    language: 'json',
    minimap: {
        enabled: false
    }
});

// watch window resize events and trigger a monaco layout
window.onresize = () => {
    monacoEditor.layout();
};

// trigger a re-render when editor content changes (i.e. user is typing content in the editor).
let typingTimeout: ReturnType<typeof setTimeout>;
monacoEditor.onDidChangeModelContent(function(e) {
    // we're using a timeout here to prevent flooding the user with errors while they're typing.
    clearTimeout(typingTimeout);
    typingTimeout = setTimeout(() => { renderAdaptiveCard(monacoEditor.getValue()) }, 300);
});
