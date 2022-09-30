// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { getTestCasesList } from "./file-retriever-utils";
import { Action, AdaptiveCard, ExecuteAction, HostConfig, IMarkdownProcessingResult, Input, OpenUrlAction, PropertyBag, SerializationContext, SubmitAction, Version, Versions } from "adaptivecards";
import * as Remarkable from "remarkable";

const ttPolicy = (typeof window === 'undefined') ? undefined : window.trustedTypes?.createPolicy('adaptivecards-ui-testapp', {
    createHTML: value => value,
});

export function listAllFiles(): HTMLLIElement[] {
    const testCasesList: HTMLLIElement[] = [];

    const files: string[] = getTestCasesList();

    files.forEach((testCase) => {
        const firstSlash: number = testCase.indexOf("/");
        const lastSlash: number = testCase.lastIndexOf("/");
        const lastPeriod: number = testCase.lastIndexOf(".");
        const testCaseName: string = testCase.substring(0, firstSlash) + testCase.substring(lastSlash, lastPeriod);

        const itemLink: HTMLAnchorElement = document.createElement("a");
        itemLink.href = "#";
        itemLink.onclick = () => { readAndRenderCard(testCase, cardRenderedCallback); };
        itemLink.id = testCaseName;

        const itemLinkText: Text = document.createTextNode(testCaseName);
        itemLink.appendChild(itemLinkText);

        const itemListItem: HTMLLIElement = document.createElement("li");
        itemListItem.appendChild(itemLink);

        testCasesList.push(itemListItem);
    });

    return testCasesList;
}

export async function readAndRenderCard(fileName: string, callbackFunction: Function) {
    const renderedCardSpaceDiv: HTMLElement = document.getElementById("renderedCardSpace");
    renderedCardSpaceDiv.style.visibility = "hidden";
    
    const response = await fetch(`samples/${fileName}`);

    let jsonToRender: any;
    if (response.ok) {
        jsonToRender = JSON.parse(await response.text());
    }
    else {
        jsonToRender = {
            type: "AdaptiveCard",
            body: [
                {
                    type: "TextBlock",
                    wrap: true,
                    weight: "bolder",
                    size: "large",
                    color: "attention",
                    text: `Error retrieving 'samples/${fileName}'. Reponse was '${response.status} - ${response.statusText}'`
                }
            ]
        };
    }

    renderCard(jsonToRender, callbackFunction);
}

export function renderCard(cardJson: any, callbackFunction: Function): void {
    // Create an AdaptiveCard instance
    const adaptiveCard: AdaptiveCard = new AdaptiveCard();

    // Set its hostConfig property unless you want to use the default Host Config
    // Host Config defines the style and behavior of a card
    adaptiveCard.hostConfig = new HostConfig({
        fontFamily: "Segoe UI, Helvetica Neue, sans-serif"
        // More host config options
    });

    // Set the adaptive card's event handlers. onExecuteAction is invoked
    // whenever an action is clicked in the card
    adaptiveCard.onExecuteAction = (action: Action) => {
        const actionType: string = action.getJsonTypeName();
        let inputsAsJson: string = "";

        if (actionType === SubmitAction.JsonTypeName || actionType === ExecuteAction.JsonTypeName) {
            const card: AdaptiveCard = adaptiveCard;
            const inputs: Input[] = card.getAllInputs(true);
            const inputsMap = {};

            inputs.forEach((input) => {
                inputsMap[input.id] = input.value;
            });

            if (actionType === SubmitAction.JsonTypeName)
            {
                const submitAction = action as SubmitAction;

                for (const [key, value] of Object.entries(submitAction.data))
                {
                    inputsMap[key] = value;
                }
            }

            inputsAsJson = JSON.stringify(inputsMap);
        }
        else if (actionType === OpenUrlAction.JsonTypeName) {
            const actionAsOpenUrl: OpenUrlAction = action;
            inputsAsJson = inputsAsJson.concat("{\"url\": \"", actionAsOpenUrl.url, "\"}");
        }

        const retrievedInputsDiv: HTMLElement = document.getElementById("retrievedInputsDiv");

        const trustedHtml = ttPolicy?.createHTML(inputsAsJson) ?? inputsAsJson;
        retrievedInputsDiv.innerHTML = trustedHtml as string;
        retrievedInputsDiv.style.visibility = "visible";
    };

    // For markdown support you need a third-party library
    // E.g., to use markdown-it, include in your HTML page:

    AdaptiveCard.onProcessMarkdown = function(text: string, result: IMarkdownProcessingResult) {
        result.outputHtml = new Remarkable.Remarkable().render(text);
        result.didProcess = true;
    };

    // Parse the card payload
    const context: SerializationContext = new SerializationContext();
    context.targetVersion = Versions.v1_6;

    adaptiveCard.parse(cardJson, context);

    // Render the card to an HTML element:
    callbackFunction(adaptiveCard.render());
}

export function cardRenderedCallback(renderedCard: HTMLElement) {
    const renderedCardDiv = document.getElementById("renderedCardSpace");
    const trustedHtml = (typeof window === 'undefined') ? "" : (window.trustedTypes?.emptyHTML ?? "");
    renderedCardDiv.innerHTML = trustedHtml as string;
    renderedCardDiv.appendChild(renderedCard);
    renderedCardDiv.style.visibility = "visible";
}
