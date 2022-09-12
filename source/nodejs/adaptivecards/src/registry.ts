// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { CardElement, Action } from "./card-elements";
import { SerializableObject, Version, Versions } from "./serialization";

export interface ITypeRegistration<T extends SerializableObject> {
    typeName: string;
    objectType: { new (): T };
    schemaVersion: Version;
}

export class CardObjectRegistry<T extends SerializableObject> {
    private _items: { [typeName: string]: ITypeRegistration<T> } = {};

    findByName(typeName: string): ITypeRegistration<T> | undefined {
        return this._items.hasOwnProperty(typeName) ? this._items[typeName] : undefined;
    }

    clear() {
        this._items = {};
    }

    copyTo(target: CardObjectRegistry<T>) {
        const keys = Object.keys(this._items);

        for (const key of keys) {
            const typeRegistration = this._items[key];

            target.register(
                typeRegistration.typeName,
                typeRegistration.objectType,
                typeRegistration.schemaVersion
            );
        }
    }

    register(
        typeName: string,
        objectType: { new (): T },
        schemaVersion: Version = Versions.v1_0
    ) {
        let registrationInfo = this.findByName(typeName);

        if (registrationInfo !== undefined) {
            registrationInfo.objectType = objectType;
        } else {
            registrationInfo = {
                typeName: typeName,
                objectType: objectType,
                schemaVersion: schemaVersion
            };
        }

        this._items[typeName] = registrationInfo;
    }

    unregister(typeName: string) {
        delete this._items[typeName];
    }

    createInstance(typeName: string, targetVersion: Version): T | undefined {
        const registrationInfo = this.findByName(typeName);

        return registrationInfo && registrationInfo.schemaVersion.compareTo(targetVersion) <= 0
            ? new registrationInfo.objectType()
            : undefined;
    }

    getItemCount(): number {
        return Object.keys(this._items).length;
    }

    getItemAt(index: number): ITypeRegistration<T> {
        return Object.keys(this._items).map((e) => this._items[e])[index];
    }
}

// eslint-disable-next-line @typescript-eslint/no-extraneous-class
export class GlobalRegistry {
    private static _elements?: CardObjectRegistry<CardElement>;
    private static _actions?: CardObjectRegistry<Action>;

    static populateWithDefaultElements(registry: CardObjectRegistry<CardElement>) {
        registry.clear();

        GlobalRegistry.defaultElements.copyTo(registry);
    }

    static populateWithDefaultActions(registry: CardObjectRegistry<Action>) {
        registry.clear();

        GlobalRegistry.defaultActions.copyTo(registry);
    }

    static readonly defaultElements = new CardObjectRegistry<CardElement>();
    static readonly defaultActions = new CardObjectRegistry<Action>();
    static get elements(): CardObjectRegistry<CardElement> {
        if (!GlobalRegistry._elements) {
            GlobalRegistry._elements = new CardObjectRegistry<CardElement>();
            GlobalRegistry.populateWithDefaultElements(GlobalRegistry._elements);
        }

        return GlobalRegistry._elements;
    }

    static get actions(): CardObjectRegistry<Action> {
        if (!GlobalRegistry._actions) {
            GlobalRegistry._actions = new CardObjectRegistry<Action>();
            GlobalRegistry.populateWithDefaultActions(GlobalRegistry._actions);
        }

        return GlobalRegistry._actions;
    }

    static reset() {
        GlobalRegistry._elements = undefined;
        GlobalRegistry._actions = undefined;
    }
}
