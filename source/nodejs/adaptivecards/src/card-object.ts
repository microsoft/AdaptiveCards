// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";
import { Dictionary, IValidationError } from "./shared";
import { HostConfig } from "./host-config";
import { HostCapabilities } from "./host-capabilities";
import { TargetVersion, Versions, property, SerializableObject, StringProperty, SerializableObjectProperty } from "./serialization";

export class ValidationFailure {
    readonly errors: IValidationError[] = [];

    constructor(readonly cardObject: CardObject) { }
}

export class ValidationResults {
    readonly allIds: Dictionary<number> = {};
    readonly failures: ValidationFailure[] = [];

    addFailure(cardObject: CardObject, error: IValidationError) {
        let index = this.failures.findIndex((value) => { return value.cardObject === cardObject; });
        let failure: ValidationFailure;

        if (index < 0) {
            failure = new ValidationFailure(cardObject);

            this.failures.push(failure);
        }
        else {
            failure = this.failures[index];
        }

        failure.errors.push(error);
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
        HostCapabilities);

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

    abstract getJsonTypeName(): string;

    abstract get hostConfig(): HostConfig;

    setParent(value: CardObject | undefined) {
        this._parent = value;
    }

    setShouldFallback(value: boolean) {
        this._shouldFallback = value;
    }

    shouldFallback(): boolean {
        return this._shouldFallback || !this.requires.areAllMet(this.hostConfig.hostCapabilities);
    }

    internalValidateProperties(context: ValidationResults) {
        if (this.id) {
            if (context.allIds.hasOwnProperty(this.id)) {
                if (context.allIds[this.id] == 1) {
                    context.addFailure(
                        this,
                        {
                            error: Enums.ValidationError.DuplicateId,
                            message: "Duplicate Id: " + this.id
                        });
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
}