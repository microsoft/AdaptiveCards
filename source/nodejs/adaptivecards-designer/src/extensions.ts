// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { DesignerPeerRegistrationBase } from "./designer-peers";
//import { DesignerPeerCategory } from "./card-designer-surface";
import { Version } from "adaptivecards";
import { PlatformVersions } from "./platform-package";

export class DesignerExtensionPeerRegistration extends DesignerPeerRegistrationBase {
	typeName: string;
	schemaVersion: Version;
	//peerType: ExtensionPeer;

	constructor(category: string, typeName: string, schemaVersion: Version, iconClass: string = null) {
		super(category, iconClass);

		this.typeName = typeName;
		this.schemaVersion = schemaVersion;
		//this.peerType = peerType;
	}
}

export class ExtensionsHelper {
	static getDefaultExtensionResigtrations() : Array<DesignerExtensionPeerRegistration> {
		return new Array(
			new DesignerExtensionPeerRegistration("Extensions", "Test", PlatformVersions.WindowsVersion, "acd-designer-icon-test")
		);
	}
}