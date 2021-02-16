// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { SerializableObject, Version, Versions } from "./serialization";

export interface ITypeRegistration<T extends SerializableObject> {
    typeName: string,
    objectType: { new(): T },
    schemaVersion: Version
}

export class CardObjectRegistry<T extends SerializableObject> {
    private _items: { [typeName: string]: ITypeRegistration<T> } = {};

    findByName(typeName: string): ITypeRegistration<T> | undefined {
        return this._items.hasOwnProperty(typeName) ? this._items[typeName] : undefined;
    }

    clear() {
        this._items = {};
    }

    register(typeName: string, objectType: { new(): T }, schemaVersion: Version = Versions.v1_0) {
        let registrationInfo = this.findByName(typeName);

        if (registrationInfo !== undefined) {
            registrationInfo.objectType = objectType;
        }
        else {
            registrationInfo = {
                typeName: typeName,
                objectType: objectType,
                schemaVersion: schemaVersion
            }
        }

        this._items[typeName] = registrationInfo;
    }

    unregister(typeName: string) {
        delete this._items[typeName];
    }

    createInstance(typeName: string, targetVersion: Version): T | undefined {
        let registrationInfo = this.findByName(typeName);

        return (registrationInfo && registrationInfo.schemaVersion.compareTo(targetVersion) <= 0) ? new registrationInfo.objectType() : undefined;
    }

    getItemCount(): number {
        return Object.keys(this._items).length;
    }

    getItemAt(index: number): ITypeRegistration<T> {
        return Object.values(this._items)[index];
    }
}
