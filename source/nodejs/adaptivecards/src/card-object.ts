// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";
import * as Utils from "./utils";
import { Strings} from "./strings";
import { Dictionary, GlobalSettings } from "./shared";
import { HostConfig } from "./host-config";
import { HostCapabilities } from "./host-capabilities";
import { Versions, property, SerializableObject, StringProperty, SerializableObjectProperty, IValidationEvent, PropertyDefinition } from "./serialization";

export class ValidationResults {
    readonly allIds: Dictionary<number> = {};
    readonly validationEvents: IValidationEvent[] = [];

    addFailure(cardObject: CardObject, event: Enums.ValidationEvent, message: string) {
        this.validationEvents.push(
            {
                phase: Enums.ValidationPhase.Validation,
                source: cardObject,
                event: event,
                message: message
            }
        );
    }
}

export type CardObjectType = { new(): CardObject };

export abstract class CardObject extends SerializableObject {
    //#region Schema

    static readonly typeNameProperty = new StringProperty(
        Versions.v1_0,
        "type",
        undefined,
        undefined,
        undefined,
        (sender: object) => {
            return (<CardObject>sender).getJsonTypeName()
        });
    static readonly idProperty = new StringProperty(Versions.v1_0, "id");
    static readonly requiresProperty = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities,
        new HostCapabilities());

    protected getSchemaKey(): string {
        return this.getJsonTypeName();
    }

    @property(CardObject.idProperty)
    id?: string;

    @property(CardObject.requiresProperty)
    get requires(): HostCapabilities {
        return this.getValue(CardObject.requiresProperty);
    }

    //#endregion

    private _shouldFallback: boolean = false;

    protected _parent?: CardObject;
    protected _renderedElement?: HTMLElement;

    onPreProcessPropertyValue?: (sender: CardObject, property: PropertyDefinition, value: any) => any;

    abstract getJsonTypeName(): string;

    abstract get hostConfig(): HostConfig;

    preProcessPropertyValue(property: PropertyDefinition, propertyValue?: any): any {
        let value = propertyValue === undefined ? this.getValue(property) : propertyValue;

        if (GlobalSettings.allowPreProcessingPropertyValues) {
            let currentObject: CardObject | undefined = this;

            while (currentObject && !currentObject.onPreProcessPropertyValue) {
                currentObject = currentObject.parent;
            }

            if (currentObject && currentObject.onPreProcessPropertyValue) {
                return currentObject.onPreProcessPropertyValue(this, property, value);
            }
        }

        return value;
    }

    setParent(value: CardObject | undefined) {
        this._parent = value;
    }

    setShouldFallback(value: boolean) {
        this._shouldFallback = value;
    }

    shouldFallback(): boolean {
        return this._shouldFallback || !this.requires.areAllMet(this.hostConfig.hostCapabilities);
    }

    getRootObject(): CardObject {
        let rootObject: CardObject = this;

        while (rootObject.parent) {
            rootObject = rootObject.parent;
        }

        return rootObject;
    }

    internalValidateProperties(context: ValidationResults) {
        if (this.id) {
            if (context.allIds.hasOwnProperty(this.id)) {
                if (context.allIds[this.id] == 1) {
                    context.addFailure(
                        this,
                        Enums.ValidationEvent.DuplicateId,
                        Strings.errors.duplicateId(this.id));
                }

                context.allIds[this.id] += 1;
            }
            else {
                context.allIds[this.id] = 1;
            }
        }
    }

    validateProperties(): ValidationResults {
        let result = new ValidationResults();

        this.internalValidateProperties(result);

        return result;
    }

    get parent(): CardObject | undefined {
        return this._parent;
    }

    get renderedElement(): HTMLElement | undefined {
        return this._renderedElement;
    }
}
