// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { listAllFiles, renderCard, cardRenderedCallback } from "./rendering-utils";

import 'adaptivecards/dist/adaptivecards.css';
import 'adaptivecards-controls/dist/adaptivecards-controls.css';
import './adaptivecards-ui-testapp.css';

function renderTestCasesList() {
    let elementList = listAllFiles();
    let testCaseListElement = document.getElementById("testCaseList");

    elementList.forEach(element => {
        testCaseListElement.appendChild(element);
    });
}

function hideInputsDiv() {
    const retrievedInputsDiv = document.getElementById("retrievedInputsDiv");
    retrievedInputsDiv.style.visibility = "hidden";
}

window.onload = () => {
    renderTestCasesList();

    // Render a sample card
    const card = {
        "type": "AdaptiveCard",
        "version": "1.0",
        "body": [
            {
                "type": "Image",
                "url": "http://adaptivecards.io/content/adaptive-card-50.png"
            },
            {
                "type": "TextBlock",
                "text": "Hello **Adaptive Cards!**"
            }
        ],
        "actions": [
            {
                "type": "Action.OpenUrl",
                "title": "Learn more",
                "url": "http://adaptivecards.io"
            },
            {
                "type": "Action.OpenUrl",
                "title": "GitHub",
                "url": "http://github.com/Microsoft/AdaptiveCards"
            }
        ]
    };

    renderCard(card, cardRenderedCallback);

    const hideInputsButton = document.getElementById("hideInputsBtn");
    hideInputsButton.addEventListener("click", (e: Event) => { hideInputsDiv() });
}
