// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Version } from "adaptivecards";

export class PlatformPackage {

	readonly name: string;

	// For version, will we want a base and beta version
	// TODO: we could have an extension class of Version for packages?
	// then we could override comparing logic?
	readonly version: Version;

	// potentially add a supported host here
    constructor(name: string, version: Version) {
		this.name = name;
		this.version = version;
    }
}

export class PlatformVersions {
	static readonly CommonVersion = new Version(1, 0, "CommonVersion");
	static readonly WindowsVersion = new Version(1, 0, "WindowsVersion");
	static readonly MobileVersion = new Version(1, 0, "MobileVersion");
}
