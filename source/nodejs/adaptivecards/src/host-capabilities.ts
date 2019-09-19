// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Shared from "./shared";
import * as Serialization from "./serialization";

export class HostCapabilities extends Serialization.SerializableObject {
    private _capabilities: { [key: string]: Shared.TargetVersion } = {};

    protected getSchemaKey(): string {
        return "HostCapabilities";
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        super.parse(json, errors);

        if (json) {
            for (let name in json) {
                let jsonVersion = json[name];

                if (typeof jsonVersion === "string") {
                    if (jsonVersion == "*") {
                        this.addCapability(name, "*");
                    }
                    else {
                        let version = Shared.Version.parse(jsonVersion, errors);

                        if (version && version.isValid) {
                            this.addCapability(name, version);
                        }
                    }
                }
            }
        }
    }

    toJSON(): any {
        let result = super.toJSON();

        for (let key in this._capabilities) {
            result[key] = this._capabilities[key];
        }
        
        return result;
    }

    addCapability(name: string, version: Shared.TargetVersion) {
        this._capabilities[name] = version;
    }

    removeCapability(name: string) {
        delete this._capabilities[name];
    }

    clear() {
        this._capabilities = {};
    }

    hasCapability(name: string, version: Shared.TargetVersion): boolean {
        if (this._capabilities.hasOwnProperty(name)) {
            if (version == "*" || this._capabilities[name] == "*") {
                return true;
            }

            return version.compareTo(<Shared.Version>this._capabilities[name]) <= 0;
        }

        return false;
    }

    areAllMet(hostCapabilities: HostCapabilities): boolean {
        for (let capabilityName in this._capabilities) {
            if (!hostCapabilities.hasCapability(capabilityName, this._capabilities[capabilityName])) {
                return false;
            }
        }

        return true;
    }
}