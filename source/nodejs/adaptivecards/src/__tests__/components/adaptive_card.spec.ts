// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Action, AdaptiveCard } from "../../card-elements";
import { HostConfig } from "../../host-config";

test("AdaptiveCard should be instantiated", () => {
    const adaptiveCard = new AdaptiveCard();
    expect(adaptiveCard).toEqual(expect.anything());
});

describe("AdaptiveCard fallback card", () => {
    const originalRender = AdaptiveCard.prototype.render;
    const globalObject = globalThis as any;
    const originalDocument = globalObject.document;

    afterEach(() => {
        AdaptiveCard.prototype.render = originalRender;
        globalObject.document = originalDocument;
    });

    function renderAndCaptureFallbackCard(card: AdaptiveCard): AdaptiveCard | undefined {
        let fallbackCard: AdaptiveCard | undefined;

        // Rendering requires a DOM; stub out the fallback card's own rendering
        // and capture it so its configuration can be inspected
        globalObject.document = {};
        AdaptiveCard.prototype.render = function (this: AdaptiveCard, target?: HTMLElement) {
            if (this === card) {
                return originalRender.call(this, target);
            }

            fallbackCard = this;

            return undefined;
        };

        card.render();

        return fallbackCard;
    }

    test("uses the host config and event handlers of the parent card", () => {
        const card = new AdaptiveCard();
        const hostConfig = new HostConfig({ supportsInteractivity: true });
        const onExecuteAction = (_action: Action) => {};
        const onAnchorClicked = () => true;
        const onInputValueChanged = () => {};

        card.hostConfig = hostConfig;
        card.onExecuteAction = onExecuteAction;
        card.onAnchorClicked = onAnchorClicked;
        card.onInputValueChanged = onInputValueChanged;
        card.parse({
            type: "AdaptiveCard",
            version: "99.0",
            body: [{ type: "TextBlock", text: "Main content" }],
            fallback: {
                type: "ActionSet",
                actions: [{ type: "Action.Submit", id: "fallbackSubmit", title: "Submit" }]
            }
        });

        const fallbackCard = renderAndCaptureFallbackCard(card);

        expect(fallbackCard).toBeDefined();
        expect(fallbackCard!.getActionById("fallbackSubmit")).toBeDefined();
        expect(fallbackCard!.hostConfig).toBe(hostConfig);
        expect(fallbackCard!.onExecuteAction).toBe(onExecuteAction);
        expect(fallbackCard!.onAnchorClicked).toBe(onAnchorClicked);
        expect(fallbackCard!.onInputValueChanged).toBe(onInputValueChanged);
    });
});
