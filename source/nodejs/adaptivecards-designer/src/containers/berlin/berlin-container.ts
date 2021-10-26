// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";
import * as hostConfigLight from "../../hostConfigs/berlin-light.json";
import * as hostConfigDark from "../../hostConfigs/berlin-dark.json";

enum ContainerSize {
	Small = "Small",
	Medium = "Medium",
	Large = "Large"
};

enum ColorTheme {
	Light = "Light",
	Dark = "Dark"
};

export class BerlinContainer extends HostContainer {
	private readonly _containerSize: ContainerSize;
	private readonly _colorTheme: ColorTheme;

	constructor(size: ContainerSize, theme: ColorTheme) {
		super(`Berlin - ${theme} - ${size} (Test)`,
			`containers/berlin-container-${theme.toLowerCase()}.css`);
		this._containerSize = size;
		this._colorTheme = theme;
	}

	public renderTo(hostElement: HTMLElement) {
		this.cardHost.classList.add(`berlin-${this._containerSize.toLowerCase()}-card`);
		const outerFrame = document.createElement("div");
		outerFrame.classList.add("berlin-outer-container");
		outerFrame.classList.add(`berlin-${this._containerSize.toLowerCase()}-container`);

		const header = document.createElement("div");
		header.className = "berlin-header";
		outerFrame.appendChild(header);

		const frame = document.createElement("div");
		frame.className = "berlin-inner-container";
		frame.appendChild(this.cardHost);

		outerFrame.appendChild(frame);
		hostElement.appendChild(outerFrame);
	}

	public getHostConfig(): Adaptive.HostConfig {
		return new Adaptive.HostConfig((this._colorTheme === ColorTheme.Light) ? hostConfigLight : hostConfigDark);
	}

	public getBackgroundColor(): string {
		return this._colorTheme === ColorTheme.Light ? "#D2D2D2" : "#616161";
	}

	get targetVersion(): Adaptive.Version {
		return Adaptive.Versions.v1_5;
	}

	public static allContainers(): BerlinContainer[] {
		let containers: BerlinContainer[] = [];
		for (const size in ContainerSize) {
			for (const theme in ColorTheme) {
				containers.push(new BerlinContainer(size as ContainerSize, theme as ColorTheme));
			}
		}
		return containers;
	}
}
