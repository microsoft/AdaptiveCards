// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Enums from "./enums";
import { Strings} from "./strings";
import { Dictionary, GlobalSettings } from "./shared";
import { HostConfig } from "./host-config";
import { HostCapabilities } from "./host-capabilities";
import { Versions, property, SerializableObject, StringProperty, SerializableObjectProperty, IValidationEvent, PropertyDefinition } from "./serialization";

/**
 * Hols the results of a card deserialization. 
 */
export class ValidationResults {
    /**
     * Holds a map of all the element and action Ids found during the deserialization of
     * a card, along with the number of times they appear.
     */
    readonly allIds: Dictionary<number> = {};

    /**
     * Holds a collection of validation events (information, warnings, etc.) that occured
     * while deserializing a card.
     */
    readonly validationEvents: IValidationEvent[] = [];

    /**
     * Add a validation event/failure to the `validationEvents` collection.
     * @param cardObject The card object that triggered the failure event 
     * @param event The validation event
     * @param message A message describing the event
     */
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

/**
 * Represents a CardObject type (constructor).
 */
export type CardObjectType = { new(): CardObject };

/**
 * The base class for all card objects (elements and actions), exposing the common
 * properties and methods.
 */
export abstract class CardObject extends SerializableObject {
    //#region Schema

    /**
     * The definition of the `type` property
     */
    static readonly typeNameProperty = new StringProperty(
        Versions.v1_0,
        "type",
        undefined,
        undefined,
        undefined,
        (sender: object) => {
            return (<CardObject>sender).getJsonTypeName()
        });
    
    /**
     * The definition of the `id` property.
     */
    static readonly idProperty = new StringProperty(Versions.v1_0, "id");

    /**
     * The definition of the `requires` property.
     */
    static readonly requiresProperty = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities,
        new HostCapabilities());

    protected getSchemaKey(): string {
        return this.getJsonTypeName();
    }

    /**
     * The id of this object.
     */
    @property(CardObject.idProperty)
    id?: string;

    /**
     * The list of capabilities required by this object.
     */
    @property(CardObject.requiresProperty)
    get requires(): HostCapabilities {
        return this.getValue(CardObject.requiresProperty);
    }

    //#endregion

    private _shouldFallback: boolean = false;

    /**
     * The parent of this object. Do NOT set explicitly. This field is handled internally.
     */
    protected _parent?: CardObject;

    /**
     * The rendered DOM element for this object. Do NOT set explicitly. This field is handled internally. 
     */
    protected _renderedElement?: HTMLElement;

    /**
     * This event allows a consuming application to pre-process the value of a property before it is rendered.
     * This is useful for text processing, for instance.
     */
    onPreProcessPropertyValue?: (sender: CardObject, property: PropertyDefinition, value: any) => any;

    /**
     * Gets the JSON type name of this object. The JSON type name is the type as used in raw card payloads,
     * e.g. "AdaptiveCard", "Action.OpenUrl", "Input.Text", etc. 
     */
    abstract getJsonTypeName(): string;

    /**
     * Gets the HostConfig instance associated with this object. Each object can have its own Host Config,
     * although generally the Host Config is set either globally or at the card level.
     */
    abstract get hostConfig(): HostConfig;

    /**
     * Pre-processes the value of a property by invoking the `onPreProcessPropertyValue` event, if set.
     * @param property The property to pre-process the value of.
     * @param propertyValue The current value of the property. This value might itself be a processed version of the property's raw value.
     * @returns The processed value of the property.
     */
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

    /**
     * Sets the parent of this object. Derived classes that hold references to other CardObject instances MUST sets those
     * objects' parent.
     * @param value The new parent of this object.
     */
    setParent(value: CardObject | undefined) {
        this._parent = value;
    }

    /**
     * Marks this object for fallback. This method is used during deserialization and has no effect in other contexts. Do not use.
     * @param value `true` to mark this object for fallback.
     */
    setShouldFallback(value: boolean) {
        this._shouldFallback = value;
    }

    /**
     * Indicates if this object should fall back, for example if its required capabilities are not satisfied. This method is
     * only meaningful during deserialization.
     * @returns`true` if this object should fall back, `false` otherwise.
     */
    shouldFallback(): boolean {
        return this._shouldFallback || !this.requires.areAllMet(this.hostConfig.hostCapabilities);
    }

    /**
     * Walks the parent tree to find the root object this object is a child of. Typically the root object is the Adaptive Card.
     * @returns The root object this object is a child of. If this object doesn't have a parent, then it is its own root.
     */
    getRootObject(): CardObject {
        let rootObject: CardObject = this;

        while (rootObject.parent) {
            rootObject = rootObject.parent;
        }

        return rootObject;
    }

    /**
     * Validates the values of this object's properties. Derived classes should override `internalValidateProperties` to
     * implement their own property validation logic. Always call `super.internalValidateProperties(results)`. Do not call this
     * method directly. Instead, call `validateProperties`.
     * @param results The validation results to add potential failures to.
     */
    internalValidateProperties(results: ValidationResults) {
        if (this.id) {
            if (results.allIds.hasOwnProperty(this.id)) {
                if (results.allIds[this.id] == 1) {
                    results.addFailure(
                        this,
                        Enums.ValidationEvent.DuplicateId,
                        Strings.errors.duplicateId(this.id));
                }

                results.allIds[this.id] += 1;
            }
            else {
                results.allIds[this.id] = 1;
            }
        }
    }

    /**
     * Validates the values of this object's properties.
     * @results The validation results to add potential failures to.
     */
    validateProperties(): ValidationResults {
        let result = new ValidationResults();

        this.internalValidateProperties(result);

        return result;
    }

    /**
     * Gets the parent of this object.
     */
    get parent(): CardObject | undefined {
        return this._parent;
    }

    /**
     * Gets the rendered DOM element for this object. `renderedElement` is initialized after the object has been rendered.
     */
    get renderedElement(): HTMLElement | undefined {
        return this._renderedElement;
    }
}
