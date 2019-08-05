// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import * as Designer from "../../adaptivecards-designer";

export class CustomContainer extends Designer.HostContainer {

     public getHostConfig(): Adaptive.HostConfig {
        return this._cardHostConfig;
    }

	public renderTo(hostElement: HTMLElement) {
        var outerFrame = document.createElement("div");
        outerFrame.className = "custom-frame";

        let innerFrame = document.createElement("div");
        innerFrame.className = "custom-inner-frame";

        this.cardHost.classList.add("custom-card");

        let botNameAndTime = document.createElement("div");
        botNameAndTime.className = "custom-botNameAndTime";
        botNameAndTime.innerText = "Sent from Bot ( 2:36 PM )";

        innerFrame.appendChild(botNameAndTime);
        innerFrame.appendChild(this.cardHost);

        outerFrame.appendChild(innerFrame);

        hostElement.appendChild(outerFrame);
	}
}

