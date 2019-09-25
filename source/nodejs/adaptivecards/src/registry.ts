// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { TargetVersion, SerializableObject } from "./serialization";

export interface ITypeRegistration<T extends SerializableObject> {
    typeName: string,
    objectType: { new(): T },
    schemaVersion: TargetVersion
}

export class CardObjectRegistry<T extends SerializableObject> {
    private _items: ITypeRegistration<T>[] = [];

    private findTypeRegistration(typeName: string): ITypeRegistration<T> | undefined {
        for (let item of this._items) {
            if (item.typeName === typeName) {
                return item;
            }
        }

        return undefined;
    }

    clear() {
        this._items = [];
    }

    register(typeName: string, objectType: { new(): T }, schemaVersion: TargetVersion = "*") {
        let registrationInfo = this.findTypeRegistration(typeName);

        if (registrationInfo !== undefined) {
            registrationInfo.objectType = objectType;
        }
        else {
            registrationInfo = {
                typeName: typeName,
                objectType: objectType,
                schemaVersion: schemaVersion
            }

            this._items.push(registrationInfo);
        }
    }

    unregister(typeName: string) {
        for (let i = 0; i < this._items.length; i++) {
            if (this._items[i].typeName === typeName) {
                this._items.splice(i, 1);

                return;
            }
        }
    }

    createInstance(typeName: string): T | undefined {
        let registrationInfo = this.findTypeRegistration(typeName);

        return registrationInfo ? new registrationInfo.objectType() : undefined;
    }

    getItemCount(): number {
        return this._items.length;
    }

    getItemAt(index: number): ITypeRegistration<T> {
        return this._items[index];
    }
}