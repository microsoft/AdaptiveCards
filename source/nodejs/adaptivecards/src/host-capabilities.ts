// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { TargetVersion, Version, SerializableObject, BaseSerializationContext, PropertyBag } from "./serialization";

export class HostCapabilities extends SerializableObject {
    private _capabilities: { [key: string]: TargetVersion } = {};

    protected getSchemaKey(): string {
        return "HostCapabilities";
    }

    protected internalParse(source: any, context: BaseSerializationContext) {
        super.internalParse(source, context);

        if (source) {
            for (let name in source) {
                let jsonVersion = source[name];

                if (typeof jsonVersion === "string") {
                    if (jsonVersion == "*") {
                        this.addCapability(name, "*");
                    }
                    else {
                        let version = Version.parse(jsonVersion, context);

                        if (version && version.isValid) {
                            this.addCapability(name, version);
                        }
                    }
                }
            }
        }
    }

    protected internalToJSON(target: PropertyBag, context: BaseSerializationContext) {
        super.internalToJSON(target, context);

        for (let key in this._capabilities) {
            target[key] = this._capabilities[key];
        }
    }

    addCapability(name: string, version: TargetVersion) {
        this._capabilities[name] = version;
    }

    removeCapability(name: string) {
        delete this._capabilities[name];
    }

    clear() {
        this._capabilities = {};
    }

    hasCapability(name: string, version: TargetVersion): boolean {
        if (this._capabilities.hasOwnProperty(name)) {
            if (version == "*" || this._capabilities[name] == "*") {
                return true;
            }

            return version.compareTo(<Version>this._capabilities[name]) <= 0;
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