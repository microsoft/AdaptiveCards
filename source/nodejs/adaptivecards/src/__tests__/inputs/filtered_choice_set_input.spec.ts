/**
 * @jest-environment jsdom
 */
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { AdaptiveCard } from "../../card-elements";
import { defaultHostConfig } from "../../host-config";

const waitForInputDebounce = () =>
    new Promise((resolve) =>
        setTimeout(resolve, defaultHostConfig.inputs.debounceTimeInMilliSeconds + 10)
    );

async function renderFilteredChoiceSet() {
    const card = new AdaptiveCard();
    card.parse({
        type: "AdaptiveCard",
        version: "1.6",
        body: [
            {
                type: "Input.ChoiceSet",
                id: "choiceSet",
                choices: [
                    { title: "Alpha", value: "a" },
                    { title: "Beta", value: "b" }
                ],
                "choices.data": { type: "Data.Query", dataset: "test" }
            }
        ]
    });

    const renderedCard = card.render()!;
    const textInput = renderedCard.querySelector<HTMLInputElement>(
        ".ac-choiceSetInput-filtered-textbox"
    )!;

    textInput.value = "a";
    textInput.dispatchEvent(new Event("input"));
    await waitForInputDebounce();

    const firstChoice = renderedCard.querySelector<HTMLElement>(".ac-choiceSetInput-choice")!;
    let firstChoiceClickCount = 0;
    firstChoice.addEventListener("click", () => firstChoiceClickCount++);

    return {
        renderedCard,
        textInput,
        firstChoice,
        getFirstChoiceClickCount: () => firstChoiceClickCount
    };
}

function selectHighlightedChoiceWithKeyboard(textInput: HTMLInputElement) {
    textInput.dispatchEvent(new KeyboardEvent("keydown", { key: "ArrowDown" }));
    textInput.dispatchEvent(new KeyboardEvent("keydown", { key: "Enter" }));
}

beforeAll(() => {
    // jsdom does not implement scrollIntoView
    HTMLElement.prototype.scrollIntoView = () => {};
});

afterEach(() => {
    document.body.innerHTML = "";
});

test("Filtered ChoiceSet keyboard selection is not redirected to another element with the same id", async () => {
    const { renderedCard, textInput, firstChoice, getFirstChoiceClickCount } =
        await renderFilteredChoiceSet();

    const otherElement = document.createElement("div");
    otherElement.id = firstChoice.id;
    let otherElementClickCount = 0;
    otherElement.addEventListener("click", () => otherElementClickCount++);
    document.body.appendChild(otherElement);
    document.body.appendChild(renderedCard);

    selectHighlightedChoiceWithKeyboard(textInput);

    expect(otherElementClickCount).toBe(0);
    expect(otherElement.className).toBe("");
    expect(getFirstChoiceClickCount()).toBe(1);
});

test("Filtered ChoiceSet keyboard selection works inside a shadow root", async () => {
    const { renderedCard, textInput, getFirstChoiceClickCount } = await renderFilteredChoiceSet();

    const host = document.createElement("div");
    document.body.appendChild(host);
    host.attachShadow({ mode: "open" }).appendChild(renderedCard);

    selectHighlightedChoiceWithKeyboard(textInput);

    expect(getFirstChoiceClickCount()).toBe(1);
});
