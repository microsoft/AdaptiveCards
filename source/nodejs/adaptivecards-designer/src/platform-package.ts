// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { HostContainer } from "./containers/host-container";
import { ToolbarChoicePicker } from "./toolbar";

export class PlatformPackage {
	private _choicePickerId: string;

	readonly type: PlatformType;
	readonly assoiciatedHosts: Array<HostContainer>;
	
	hostChoicePicker: ToolbarChoicePicker;
	currentHost: HostContainer;

	onSelectedHostChanged: () => void;

	// TODO: we need a hostOptions here (unless we remove hosts completely)
	// then maybe we only have one associated host?

    constructor(name: PlatformType, associatedHosts: Array<HostContainer>, choicePickerId: string) {
		this.type = name;
		this.assoiciatedHosts = associatedHosts;
		this._choicePickerId = choicePickerId;

		this.createHostChoicePicker();
	}
	
	private createHostChoicePicker(): void {
		if (this.assoiciatedHosts && this.assoiciatedHosts.length > 0) {
            this.hostChoicePicker = new ToolbarChoicePicker(this._choicePickerId);
            this.hostChoicePicker.separator = true;
            this.hostChoicePicker.label = "Select host app:";

            for (let i = 0; i < this.assoiciatedHosts.length; i++) {
                this.hostChoicePicker.choices.push(
                    {
                        name: this.assoiciatedHosts[i].name,
                        value: i.toString(),
                    }
                );
            }

            this.hostChoicePicker.onChanged = (sender) => {
                this.currentHost = this.assoiciatedHosts[parseInt(this.hostChoicePicker.value)];
            };
        }
	}
}

export enum PlatformType {
	Common = "Common",
	Windows = "Windows",
	Mobile = "Mobile"
}
