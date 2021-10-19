// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";
import * as hostConfigLight from "../../hostConfigs/berlin-light.json";
import * as hostConfigDark from "../../hostConfigs/berlin-dark.json";

abstract class BaseBerlinContainer extends HostContainer {
    public renderTo(hostElement: HTMLElement) {
        this.cardHost.classList.add("berlin-card");
        let outerFrame = document.createElement("div");
        outerFrame.classList.add("berlin-outer-container");
        outerFrame.classList.add(this.getAdditionalClassName());

        let header = document.createElement("div");
        header.className = "berlin-header";
        outerFrame.appendChild(header);

        let frame = document.createElement("div");
        frame.className = "berlin-inner-container";
        frame.appendChild(this.cardHost);

        outerFrame.appendChild(frame);
        hostElement.appendChild(outerFrame);
    }
    get targetVersion(): Adaptive.Version {
        return Adaptive.Versions.v1_5;
    }

    abstract getAdditionalClassName(): string;
}


abstract class LightBerlinContainer extends BaseBerlinContainer {
    public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfigLight);
    }
}

export class LightBerlinLargeContainer extends LightBerlinContainer {
    getAdditionalClassName(): string {
        return "berlin-large-container";
    }
}

export class LightBerlinSmallContainer extends LightBerlinContainer {
    getAdditionalClassName(): string {
        return "berlin-small-container";
    }
}

export class LightBerlinMediumContainer extends LightBerlinContainer {
    getAdditionalClassName(): string {
        return "berlin-medium-container";
    }
}

abstract class DarkBerlinContainer extends BaseBerlinContainer {
	public getBackgroundColor(): string {
        return "#201E1F";
    }

	public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfigDark);
    }
}

export class DarkBerlinLargeContainer extends DarkBerlinContainer {
    getAdditionalClassName(): string {
        return "berlin-large-container";
    }

	public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfigDark);
    }
}

export class DarkBerlinSmallContainer extends DarkBerlinContainer {
    getAdditionalClassName(): string {
        return "berlin-small-container";
    }

	public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfigDark);
    }
}

export class DarkBerlinMediumContainer extends DarkBerlinContainer {
    getAdditionalClassName(): string {
        return "berlin-medium-container";
    }

	public getHostConfig(): Adaptive.HostConfig {
        return new Adaptive.HostConfig(hostConfigDark);
    }
}
