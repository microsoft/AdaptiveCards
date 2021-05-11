// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { CardElement, Container, TextBlock, RichTextBlock, TextRun, ImageSet, Media, FactSet, ColumnSet, Image,
    ActionSet, TextInput, DateInput, TimeInput, NumberInput, ChoiceSetInput, ToggleInput, Action,
    OpenUrlAction, SubmitAction, ShowCardAction, ToggleVisibilityAction, ExecuteAction } from "./card-elements";
import { SerializableObject, Version, Versions } from "./serialization";
import { Table } from "./table";

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
        return Object.keys(this._items).map(e => this._items[e])[index];
    }
}

export class GlobalRegistry {
    static populateWithDefaultElements(registry: CardObjectRegistry<CardElement>) {
        registry.clear();

        registry.register("Container", Container);
        registry.register("TextBlock", TextBlock);
        registry.register("RichTextBlock", RichTextBlock, Versions.v1_2);
        registry.register("TextRun", TextRun, Versions.v1_2);
        registry.register("Image", Image);
        registry.register("ImageSet", ImageSet);
        registry.register("Media", Media, Versions.v1_1);
        registry.register("FactSet", FactSet);
        registry.register("ColumnSet", ColumnSet);
        registry.register("ActionSet", ActionSet, Versions.v1_2);
        registry.register("Table", Table, Versions.v1_5);
        registry.register("Input.Text", TextInput);
        registry.register("Input.Date", DateInput);
        registry.register("Input.Time", TimeInput);
        registry.register("Input.Number", NumberInput);
        registry.register("Input.ChoiceSet", ChoiceSetInput);
        registry.register("Input.Toggle", ToggleInput);
    }

    static populateWithDefaultActions(registry: CardObjectRegistry<Action>) {
        registry.clear();

        registry.register(OpenUrlAction.JsonTypeName, OpenUrlAction);
        registry.register(SubmitAction.JsonTypeName, SubmitAction);
        registry.register(ShowCardAction.JsonTypeName, ShowCardAction);
        registry.register(ToggleVisibilityAction.JsonTypeName, ToggleVisibilityAction, Versions.v1_2);
        registry.register(ExecuteAction.JsonTypeName, ExecuteAction, Versions.v1_4);
    }

    static readonly elements = new CardObjectRegistry<CardElement>();
    static readonly actions = new CardObjectRegistry<Action>();

    static reset() {
        GlobalRegistry.populateWithDefaultElements(GlobalRegistry.elements);
        GlobalRegistry.populateWithDefaultActions(GlobalRegistry.actions);
    }
}

GlobalRegistry.reset();