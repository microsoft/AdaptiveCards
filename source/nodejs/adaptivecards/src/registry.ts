// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { CardObject } from "./card-object";
import { CardElement, Action, Container, TextBlock, RichTextBlock, TextRun, Image, ImageSet,
    Media, FactSet, ActionSet, ColumnSet, ChoiceSetInput, TextInput, DateInput, TimeInput,
    NumberInput, ToggleInput, OpenUrlAction, SubmitAction, ShowCardAction, ToggleVisibilityAction } from "./card-elements";
import { TargetVersion, Versions, ParseContext, SerializableObject } from "./serialization";

export interface ICardObjectRegistration<T extends CardObject> {
    typeName: string,
    objectType: { new(): T },
    schemaVersion: TargetVersion
}

export class CardObjectRegistry<T extends CardObject> {
    private _items: ICardObjectRegistration<T>[] = [];

    private findTypeRegistration(typeName: string): ICardObjectRegistration<T> | undefined {
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

    getItemAt(index: number): ICardObjectRegistration<T> {
        return this._items[index];
    }
}

export class GlobalRegistry {
    static readonly elements = new CardObjectRegistry<CardElement>();
    static readonly actions = new CardObjectRegistry<Action>();

    static resetElements() {
        GlobalRegistry.elements.clear();

        GlobalRegistry.elements.register("Container", Container);
        GlobalRegistry.elements.register("TextBlock", TextBlock);
        GlobalRegistry.elements.register("RichTextBlock", RichTextBlock, Versions.v1_2);
        GlobalRegistry.elements.register("TextRun", TextRun, Versions.v1_2);
        GlobalRegistry.elements.register("Image", Image);
        GlobalRegistry.elements.register("ImageSet", ImageSet);
        GlobalRegistry.elements.register("Media", Media, Versions.v1_1);
        GlobalRegistry.elements.register("FactSet", FactSet);
        GlobalRegistry.elements.register("ColumnSet", ColumnSet);
        GlobalRegistry.elements.register("ActionSet", ActionSet, Versions.v1_2);
        GlobalRegistry.elements.register("Input.Text", TextInput);
        GlobalRegistry.elements.register("Input.Date", DateInput);
        GlobalRegistry.elements.register("Input.Time", TimeInput);
        GlobalRegistry.elements.register("Input.Number", NumberInput);
        GlobalRegistry.elements.register("Input.ChoiceSet", ChoiceSetInput);
        GlobalRegistry.elements.register("Input.Toggle", ToggleInput);
    }

    static resetActions() {
        GlobalRegistry.actions.clear();

        GlobalRegistry.actions.register(OpenUrlAction.JsonTypeName, OpenUrlAction);
        GlobalRegistry.actions.register(SubmitAction.JsonTypeName, SubmitAction);
        GlobalRegistry.actions.register(ShowCardAction.JsonTypeName, ShowCardAction);
        GlobalRegistry.actions.register(ToggleVisibilityAction.JsonTypeName, ToggleVisibilityAction, Versions.v1_2);
    }

    static reset() {
        GlobalRegistry.resetElements();
        GlobalRegistry.resetActions();
    }
}

GlobalRegistry.reset();

export class CardObjectParseContext extends ParseContext {
    objectParsed(o: SerializableObject, source: any) {
        if (o instanceof Action && this.onParseAction) {
            this.onParseAction(o, source, this);
        }
        else if (o instanceof CardElement && this.onParseElement) {
            this.onParseElement(o, source, this);
        }
        else if (this.onParseObject) {
            this.onParseObject(o, source, this);
        }
    }

    createElementInstance(jsonTypeName: string): CardElement | undefined {
        return GlobalRegistry.elements.createInstance(jsonTypeName);
    }

    createActionInstance(jsonTypeName: string): Action | undefined {
        return GlobalRegistry.actions.createInstance(jsonTypeName);
    }

    onParseAction?: (action: Action, source: any, context: CardObjectParseContext) => void;
    onParseElement?: (element: CardElement, source: any, context: CardObjectParseContext) => void;
    onParseObject?: (o: SerializableObject, source: any, context: CardObjectParseContext) => void;
}