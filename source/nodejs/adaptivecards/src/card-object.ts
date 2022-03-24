// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";
import { Strings } from "./strings";
import { Dictionary, GlobalSettings } from "./shared";
import { HostConfig } from "./host-config";
import { HostCapabilities } from "./host-capabilities";
import {
    Versions,
    property,
    SerializableObject,
    StringProperty,
    SerializableObjectProperty,
    IValidationEvent,
    PropertyDefinition
} from "./serialization";

export class ValidationResults {
    readonly allIds: Dictionary<number> = {};
    readonly validationEvents: IValidationEvent[] = [];

    addFailure(cardObject: CardObject, event: Enums.ValidationEvent, message: string) {
        this.validationEvents.push({
            phase: Enums.ValidationPhase.Validation,
            source: cardObject,
            event: event,
            message: message
        });
    }
}

export type CardObjectType = { new (): CardObject };

export abstract class CardObject extends SerializableObject {
    //#region Schema

    static readonly typeNameProperty = new StringProperty(
        Versions.v1_0,
        "type",
        undefined,
        undefined,
        undefined,
        (sender: object) => {
            return (<CardObject>sender).getJsonTypeName();
        }
    );
    static readonly idProperty = new StringProperty(Versions.v1_0, "id");
    static readonly requiresProperty = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities,
        false,
        new HostCapabilities()
    );

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

    /**
     * Checks if this CardObject contains the given DOM Node.
     * @param node The DOM Node to look for.
     * @returns `true` if the DOM Node was found, `false` otherwise.
     */
    protected contains(node: Node): boolean {
        if (this._renderedElement) {
            return this._renderedElement.contains(node);
        }

        return false;
    }

    onPreProcessPropertyValue?: (
        sender: CardObject,
        property: PropertyDefinition,
        value: any
    ) => any;

    abstract getJsonTypeName(): string;

    abstract get hostConfig(): HostConfig;

    preProcessPropertyValue(prop: PropertyDefinition, propertyValue?: any): any {
        const value = propertyValue === undefined ? this.getValue(prop) : propertyValue;

        if (GlobalSettings.allowPreProcessingPropertyValues) {
            // eslint-disable-next-line @typescript-eslint/no-this-alias
            let currentObject: CardObject | undefined = this;

            while (currentObject && !currentObject.onPreProcessPropertyValue) {
                currentObject = currentObject.parent;
            }

            if (currentObject && currentObject.onPreProcessPropertyValue) {
                return currentObject.onPreProcessPropertyValue(this, prop, value);
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
        // eslint-disable-next-line @typescript-eslint/no-this-alias
        let currentObject: CardObject = this;

        while (currentObject.parent) {
            currentObject = currentObject.parent;
        }

        return currentObject;
    }

    internalValidateProperties(context: ValidationResults) {
        if (this.id) {
            if (context.allIds.hasOwnProperty(this.id)) {
                if (context.allIds[this.id] === 1) {
                    context.addFailure(
                        this,
                        Enums.ValidationEvent.DuplicateId,
                        Strings.errors.duplicateId(this.id)
                    );
                }

                context.allIds[this.id] += 1;
            } else {
                context.allIds[this.id] = 1;
            }
        }
    }

    validateProperties(): ValidationResults {
        const result = new ValidationResults();

        this.internalValidateProperties(result);

        return result;
    }

    /**
     * Recursively searches this CardObject and any children to find the
     * innermost CardObject that owns the given DOM Node.
     *
     * @param node The DOM Node to look for.
     *
     * @returns The owner of the given DOM Node, or `undefined` if no owner was found.
     */
    findDOMNodeOwner(node: Node): CardObject | undefined {
        // default implementation for CardObjects with no associated children
        return this.contains(node) ? this : undefined;
    }

    releaseDOMResources() {
        // Do nothing in base implementation
    }

    get parent(): CardObject | undefined {
        return this._parent;
    }

    get renderedElement(): HTMLElement | undefined {
        return this._renderedElement;
    }
}
