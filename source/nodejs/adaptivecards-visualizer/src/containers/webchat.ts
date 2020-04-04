// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { HostContainer } from "./host-container";
import {
    AdaptiveCard,
    HostConfig,
} from "adaptivecards";
import * as webChatConfiguration from "../../../../../samples/HostConfig/webchat.json";

export class WebChatContainer extends HostContainer {
    protected renderContainer(adaptiveCard: AdaptiveCard, target: HTMLElement): HTMLElement {
        var outerElement = document.createElement("div");
        outerElement.className = "webChatOuterContainer";

        var resizeCard = () => {
            if (outerElement.parentElement) {
                var bounds = outerElement.parentElement.getBoundingClientRect();

                var newWidth: string = "216px";

                if (bounds.width >= 500) {
                    newWidth = "416px";
                }
                else if (bounds.width >= 400) {
                    newWidth = "320px";
                }

                if (outerElement.style.width != newWidth) {
                    outerElement.style.width = newWidth;
                }

                adaptiveCard.updateLayout();
            }
        };

        window.addEventListener("resize", resizeCard);

        var innerElement = document.createElement("div");
        innerElement.className = "webChatInnerContainer";

        target.appendChild(outerElement);
        outerElement.appendChild(innerElement);

        var renderedCard = adaptiveCard.render();
        innerElement.appendChild(renderedCard);
        resizeCard();

        return outerElement;
    }

    public getHostConfig(): HostConfig {
        return new HostConfig(webChatConfiguration);
    }
}
