// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { PlatformType } from "./platform-package";

export class DesignerExtensionPeerRegistration {
	private _iconClass?: string;

	readonly category: string;
	readonly typeName: string;
	readonly platformType: PlatformType;

	constructor(category: string, typeName: string, platformType: PlatformType, iconClass: string = null) {
		this.category = category;
        this._iconClass = iconClass;
		this.typeName = typeName;
		this.platformType = platformType;
	}

	get iconClass(): string {
        return this._iconClass ? this._iconClass : "acd-icon-defaultElementIcon";
    }
}

export class ExtensionsHelper {
	static getDefaultExtensionResigtrations() : Array<DesignerExtensionPeerRegistration> {
		return new Array(
			new DesignerExtensionPeerRegistration("Extensions", "Test", PlatformType.Windows, "acd-designer-icon-test"),
			new DesignerExtensionPeerRegistration("Extensions", "Pizza", PlatformType.Common, "acd-designer-icon-test"),
			new DesignerExtensionPeerRegistration("Extensions", "Test100000", PlatformType.Mobile, "acd-designer-icon-test")
		);
	}
}