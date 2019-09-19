// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { GlobalSettings, TargetVersion, SizeAndUnit, IValidationError } from "./shared";
import * as Utils from "./utils";
import * as Enums from "./enums";

export class PropertyDefinition {
    getJsonPropertyName(): string {
        return this.name;
    }

    parse(sender: SerializableObject, source: PropertyBag, errors?: IValidationError[]): any {
        return source[this.name];
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: any): void {
        Utils.setProperty(target, this.name, value, this.defaultValue);
    }

    constructor(
        readonly targetVersion: TargetVersion,
        readonly name: string,
        readonly defaultValue?: any,
        readonly onGetInitialValue?: (sender: SerializableObject) => any) { }
}

export class StringProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, errors?: IValidationError[]): string | undefined {
        let parsedValue = Utils.getStringValue(source[this.name], this.defaultValue);
        let isUndefined = parsedValue === undefined || (parsedValue === "" && this.treatEmptyAsUndefined);

        if (!isUndefined && this.regEx !== undefined) {
            let matches = this.regEx.exec(<string>parsedValue);

            if (!matches) {
                // TODO: Log parse error
                return undefined;
            }
        }

        return parsedValue;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: string | undefined) {
        Utils.setProperty(
            target,
            this.name,
            value === "" && this.treatEmptyAsUndefined ? undefined : value,
            this.defaultValue);
    }

    constructor(
        readonly targetVersion: TargetVersion,
        readonly name: string,
        readonly treatEmptyAsUndefined: boolean = true,
        readonly regEx?: RegExp,
        readonly defaultValue?: string,
        readonly onGetInitialValue?: (sender: SerializableObject) => string) {
        super(targetVersion, name, defaultValue, onGetInitialValue);
    }
}

export class BoolProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, errors?: IValidationError[]): boolean | undefined {
        return Utils.getBoolValue(source[this.name], this.defaultValue);;
    }

    toJSON(sender: SerializableObject, target: object, value: boolean | undefined) {
        Utils.setProperty(
            target,
            this.name,
            value,
            this.defaultValue);
    }
}

export class NumProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, errors?: IValidationError[]): number | undefined {
        return Utils.getNumberValue(source[this.name], this.defaultValue);;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: number | undefined) {
        Utils.setNumberProperty(
            target,
            this.name,
            value,
            this.defaultValue);
    }
}

export class PixelSizeProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, errors?: IValidationError[]): number | undefined {
        let result: number | undefined = undefined;
        let value = source[this.name];

        if (typeof value === "string") {
            let isValid = false;

            try {
                let size = SizeAndUnit.parse(value, true);

                if (size.unit == Enums.SizeUnit.Pixel) {
                    result = size.physicalSize;

                    isValid = true;
                }
            }
            catch {
                // Do nothing. A parse error is emitted below
            }

            if (!isValid) {
                /* TODO
                raiseParseError(
                    {
                        error: Enums.ValidationError.InvalidPropertyValue,
                        message: "Invalid \"minHeight\" value: " + jsonMinHeight
                    },
                    errors
                );
                */
            }
        }

        return result;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: number | undefined) {
        Utils.setProperty(
            target,
            this.name,
            typeof value === "number" && !isNaN(value) ? value + "px" : undefined);
    }
}

export interface IVersionedValue<TValue> {
    value: TValue;
    targetVersion?: TargetVersion;
}

export class ValueSetProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, errors?: IValidationError[]): string | undefined {
        let parsedValue = Utils.getStringValue(source[this.name], this.defaultValue);

        if (parsedValue !== undefined) {
            for (let value of this.values) {
                if (parsedValue.toLowerCase() === value.value) {
                    return value.value;
                }
            }
        }

        return undefined;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: string | undefined) {
        Utils.setProperty(
            target,
            this.name,
            value,
            this.defaultValue);
    }

    constructor(
        readonly targetVersion: TargetVersion,
        readonly name: string,
        readonly values: IVersionedValue<string>[],
        readonly defaultValue?: string,
        readonly onGetInitialValue?: (sender: SerializableObject) => string) {
        super(targetVersion, name, defaultValue, onGetInitialValue);
    }
}

export class EnumProperty<TEnum extends { [s: number]: string }> extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, errors?: IValidationError[]): number | undefined {
        return Utils.getEnumValue(this.enumType, source[this.name], this.defaultValue);
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: number | undefined) {
        Utils.setEnumProperty(
            this.enumType,
            target,
            this.name,
            value,
            this.defaultValue);
    }

    constructor(
        readonly targetVersion: TargetVersion,
        readonly name: string,
        readonly enumType: TEnum,
        readonly defaultValue?: number,
        readonly values?: IVersionedValue<number>[],
        readonly onGetInitialValue?: (sender: SerializableObject) => number) {
        super(targetVersion, name, defaultValue, onGetInitialValue);

        if (!values) {
            values = [];

            for (let key in enumType) {
                if (typeof key === "number") {
                    values.push( { value: key });
                }
            }
        }
    }
}

export type SerializableObjectType = { new(): SerializableObject };

export class SerializableObjectProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, errors?: IValidationError[]): SerializableObject | undefined {
        let result: SerializableObject | undefined = undefined;
        let sourceValue = source[this.name];

        result = new this.objectType();
        result.parse(sourceValue);

        if (result === undefined && this.onGetInitialValue) {
            result = this.onGetInitialValue(sender);
        }

        /*
        else if (this.onGetInitialValue) {
            result = this.onGetInitialValue(sender);
        }
        */

        return result;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: SerializableObject | undefined) {
        let serializedValue = value !== undefined ? value.toJSON() : value;

        if (typeof serializedValue === "object" && Object.keys(serializedValue).length === 0) {
            serializedValue = undefined;
        }

        super.toJSON(sender, target, serializedValue);
    }

    constructor(
        readonly targetVersion: TargetVersion,
        readonly name: string,
        readonly objectType: SerializableObjectType) {
        super(
            targetVersion,
            name,
            undefined,
            (sender: SerializableObject) => { return new this.objectType(); });
    }
}

export class SerializableObjectCollectionProperty<T extends SerializableObject> extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, errors?: IValidationError[]): T[] | undefined {
        let result: T[] | undefined = [];

        let sourceCollection = source[this.name];

        if (Array.isArray(sourceCollection)) {
            for (let sourceItem of sourceCollection) {
                let item = this.onCreateCollectionItemInstance(sender, sourceItem);

                if (item) {
                    item.parse(sourceItem);

                    result.push(item);

                    if (this.onItemAdded) {
                        this.onItemAdded(sender, item);
                    }
                }
            }
        }

        return result.length > 0 ? result : (this.onGetInitialValue ? this.onGetInitialValue(sender) : undefined);
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: T[] | undefined) {
        Utils.setArrayProperty(target, this.name, value);
    }

    constructor(
        readonly targetVersion: TargetVersion,
        readonly name: string,
        readonly onCreateCollectionItemInstance: (sender: SerializableObject, sourceItem: any) => T,
        readonly onGetInitialValue?: (sender: SerializableObject) => T[],
        readonly onItemAdded?: (sender: SerializableObject, item: T) => void) {
        super(targetVersion, name, undefined, onGetInitialValue);

        if (!this.onCreateCollectionItemInstance) {
            throw new Error("SerializedObjectCollectionPropertyDefinition instances must have an onCreateCollectionItemInstance handler.");
        }
    }
}

export class CustomProperty<T> extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, errors?: IValidationError[]): T {
        return this.onParse(sender, this, source, errors);
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: T) {
        this.onToJSON(sender, this, target, value);
    }

    constructor(
        readonly targetVersion: TargetVersion,
        readonly name: string,
        readonly onParse: (sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, errors?: IValidationError[]) => T,
        readonly onToJSON: (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: T) => void,
        readonly defaultValue?: T,
        readonly onGetInitialValue?: (sender: SerializableObject) => T) {
        super(targetVersion, name, defaultValue, onGetInitialValue);

        if (!this.onParse) {
            throw new Error("CustomPropertyDefinition instances must have an onParse handler.");
        }

        if (!this.onToJSON) {
            throw new Error("CustomPropertyDefinition instances must have an onToJSON handler.");
        }
    }
}

export class SerializableObjectSchema {
    private _properties: PropertyDefinition[] = [];

    indexOf(property: PropertyDefinition): number {
        for (let i = 0; i < this._properties.length; i++) {
            if (this._properties[i] === property) {
                return i;
            }
        }

        return -1;
    }

    add(...properties: PropertyDefinition[]) {
        for (let i = 0; i < properties.length; i++) {
            if (this.indexOf(properties[i]) === -1) {
                this._properties.push(properties[i]);
            }
        }
    }

    remove(...properties: PropertyDefinition[]) {
        for (let property of properties) {
            while (true) {
                let index = this.indexOf(property);

                if (index >= 0) {
                    this._properties.splice(index, 1);
                }
                else {
                    break;
                }
            }
        }
    }

    getItemAt(index: number): PropertyDefinition {
        return this._properties[index];
    }

    getCount(): number {
        return this._properties.length;
    }
}

export function property(property: PropertyDefinition) {
    return function(target: any, propertyKey: string) {
        let descriptor = Object.getOwnPropertyDescriptor(target, propertyKey) || {};

        if (!descriptor.get && !descriptor.set) {
            descriptor.get = function(this: SerializableObject) { return this.getValue(property); };
            descriptor.set = function(this: SerializableObject, value: any) { this.setValue(property, value); };

            Object.defineProperty(target, propertyKey, descriptor)
        }
    }
}

export type PropertyBag = { [propertyName: string]: any };

export abstract class SerializableObject {
    private static readonly _schemaCache: { [typeName: string]: SerializableObjectSchema } = {};
    
    private _propertyBag: PropertyBag = {};
    private _rawProperties: PropertyBag = {};

    protected abstract getSchemaKey(): string;

    protected populateSchema(schema: SerializableObjectSchema) {
        let ctor = <any>this.constructor;

        for (let propertyName in ctor) {
            try {
                let propertyValue = ctor[propertyName];

                if (propertyValue instanceof PropertyDefinition) {
                    schema.add(propertyValue);
                }
            }
            catch {
                // If a property happens to have a getter function and
                // it throws an exception, we need to catch it here
            }
        }
    }

    protected getValue(property: PropertyDefinition) {
        return this._propertyBag.hasOwnProperty(property.name) ? this._propertyBag[property.name] : property.defaultValue;
    }

    protected setValue(property: PropertyDefinition, value: any) {
        if (value === undefined) {
            delete this._propertyBag[property.name];
        }
        else {
            this._propertyBag[property.name] = value;
        }
    }

    constructor() {
        let s = this.getSchema();

        for (let i = 0; i < s.getCount(); i++) {
            let property = s.getItemAt(i);

            if (property.onGetInitialValue) {
                this.setValue(property, property.onGetInitialValue(this));
            }
        }
    }

    parse(source: any, errors?: IValidationError[]) {
        this._propertyBag = {};
        this._rawProperties = GlobalSettings.enableFullJsonRoundTrip ? (source ? source : {}) : {};

        if (source) {
            let s = this.getSchema();

            for (let i = 0; i < s.getCount(); i++) {
                let property = s.getItemAt(i);

                this.setValue(property, property.parse(this, source, errors));
            }
        }
        else {
            this.resetDefaultValues();
        }
    }

    toJSON(): any {
        let result: any;

        if (GlobalSettings.enableFullJsonRoundTrip && this._rawProperties && typeof this._rawProperties === "object") {
            result = this._rawProperties;
        }
        else {
            result = {};
        }

        let s = this.getSchema();
        let serializedProperties: string[] = [];

        for (let i = 0; i < s.getCount(); i++) {
            let property = s.getItemAt(i);

            if (serializedProperties.indexOf(property.getJsonPropertyName()) == -1) {
                property.toJSON(this, result, this.getValue(property));

                serializedProperties.push(property.getJsonPropertyName());
            }
        }

        return result;
    }

    hasDefaultValue(property: PropertyDefinition): boolean {
        return this.getValue(property) === property.defaultValue;
    }

    hasAllDefaultValues(): boolean {
        let s = this.getSchema();

        for (let i = 0; i < s.getCount(); i++) {
            let property = s.getItemAt(i);

            if (!this.hasDefaultValue(property)) {
                return false;
            }
        }

        return true;
    }

    resetDefaultValues() {
        let s = this.getSchema();

        for (let i = 0; i < s.getCount(); i++) {
            let property = s.getItemAt(i);

            this.setValue(property, property.defaultValue);
        }
    }

    setCustomProperty(name: string, value: any) {
        let shouldDeleteProperty = (typeof value === "string" && Utils.isNullOrEmpty(value)) || value === undefined || value === null;

        if (shouldDeleteProperty) {
            delete this._rawProperties[name];
        }
        else {
            this._rawProperties[name] = value;
        }
    }

    getCustomProperty(name: string): any {
        return this._rawProperties[name];
    }

    getSchema(): SerializableObjectSchema {
        let schema: SerializableObjectSchema = SerializableObject._schemaCache[this.getSchemaKey()];

        if (!schema) {
            schema = new SerializableObjectSchema();
            
            this.populateSchema(schema);

            SerializableObject._schemaCache[this.getSchemaKey()] = schema;
        }

        return schema;
    }
}