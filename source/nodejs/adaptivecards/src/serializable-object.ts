// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Shared from "./shared";
import * as Utils from "./utils";

export abstract class PropertyDefinition {
    abstract parse(value: any, errors?: Shared.IValidationError[]): any;
    abstract toJSON(target: object, value: any): void;

    constructor(
        readonly targetVersion: Shared.TargetVersion,
        readonly name: string,
        readonly defaultValue?: any,
        readonly onGetInitialValue?: (sender: object) => any) { }
}

export abstract class TypedPropertyDefinition<T> extends PropertyDefinition {
    abstract parse(value: any, errors?: Shared.IValidationError[]): T | undefined;

    constructor(
        readonly targetVersion: Shared.TargetVersion,
        readonly name: string,
        readonly defaultValue?: T,
        readonly onGetInitialValue?: (sender: object) => T) {
        super(targetVersion, name, defaultValue, onGetInitialValue);
    }
}

export class StringPropertyDefinition extends TypedPropertyDefinition<string> {
    parse(value: any, errors?: Shared.IValidationError[]): string | undefined {
        let parsedValue = Utils.getStringValue(value, this.defaultValue);
        let isUndefined = parsedValue === undefined || (parsedValue === "" && this.treatEmptyAsUndefined);

        if (!isUndefined && this.regEx !== undefined) {
            let matches = this.regEx.exec(value);

            if (!matches) {
                // TODO: Log parse error
                return undefined;
            }
        }

        return parsedValue;
    }

    toJSON(target: object, value: any) {
        Utils.setProperty(
            target,
            this.name,
            value === "" && this.treatEmptyAsUndefined ? undefined : value,
            this.defaultValue);
    }

    constructor(
        readonly targetVersion: Shared.TargetVersion,
        readonly name: string,
        readonly treatEmptyAsUndefined: boolean = true,
        readonly regEx?: RegExp,
        readonly defaultValue?: string,
        readonly onGetInitialValue?: (sender: object) => string) {
        super(targetVersion, name, defaultValue, onGetInitialValue);
    }
}

export class BooleanPropertyDefinition extends TypedPropertyDefinition<boolean> {
    parse(value: any, errors?: Shared.IValidationError[]): boolean | undefined {
        return Utils.getBoolValue(value, this.defaultValue);;
    }

    toJSON(target: object, value: any) {
        Utils.setProperty(
            target,
            this.name,
            value,
            this.defaultValue);
    }
}

export class NumberPropertyDefinition extends TypedPropertyDefinition<number> {
    parse(value: any, errors?: Shared.IValidationError[]): number | undefined {
        return Utils.getNumberValue(value, this.defaultValue);;
    }

    toJSON(target: object, value: any) {
        Utils.setNumberProperty(
            target,
            this.name,
            value,
            this.defaultValue);
    }
}

export interface IVersionedValue<TValue> {
    targetVersion: Shared.TargetVersion;
    value: TValue;
}

export class ValueSetPropertyDefinition extends TypedPropertyDefinition<string> {
    parse(value: any, errors?: Shared.IValidationError[]): string | undefined {
        let parsedValue = Utils.getStringValue(value, this.defaultValue);

        for (let value of this.values) {
            if (parsedValue.toLowerCase() === value.value) {
                return value.value;
            }
        }

        return undefined;
    }

    toJSON(target: object, value: any) {
        Utils.setProperty(
            target,
            this.name,
            value,
            this.defaultValue);
    }

    constructor(
        readonly targetVersion: Shared.TargetVersion,
        readonly name: string,
        readonly values: IVersionedValue<string>[],
        readonly defaultValue?: string,
        readonly onGetInitialValue?: (sender: object) => string) {
        super(targetVersion, name, defaultValue, onGetInitialValue);
    }
}

export class EnumPropertyDefinition<TEnum extends { [s: number]: string }> extends TypedPropertyDefinition<number> {
    parse(value: any, errors?: Shared.IValidationError[]): number | undefined {
        return Utils.getEnumValue(this.enumType, value, this.defaultValue);
    }

    toJSON(target: object, value: any) {
        Utils.setEnumProperty(
            this.enumType,
            target,
            this.name,
            value,
            this.defaultValue);
    }

    constructor(
        readonly targetVersion: Shared.TargetVersion,
        readonly name: string,
        readonly enumType: TEnum,
        readonly values: IVersionedValue<number>[],
        readonly defaultValue?: number,
        readonly onGetInitialValue?: (sender: object) => number) {
        super(targetVersion, name, defaultValue, onGetInitialValue);
    }
}

export class SerializableObjectPropertyDefinition<T extends SerializableObject> extends TypedPropertyDefinition<T> {
    parse(value: any, errors?: Shared.IValidationError[]): T | undefined {
        let result = this.createInstance();
        result.parse(value);

        return result;
    }

    toJSON(target: PropertyBag, value: T) {
        let serializedValue = value.toJSON();

        if (Object.keys(serializedValue).length > 0) {
            target[this.name] = serializedValue;
        }
    }

    constructor(
        readonly targetVersion: Shared.TargetVersion,
        readonly name: string,
        readonly createInstance: () => T,
        readonly onGetInitialValue?: (sender: object) => T) {
        super(targetVersion, name, undefined, onGetInitialValue);
    }
}

export class CustomPropertyDefinition<T> extends TypedPropertyDefinition<T> {
    parse(value: any, errors?: Shared.IValidationError[]): T | undefined {
        if (!this.onParse) {
            throw new Error("CustomPropertyDefinition instances must have an onParse handler.");
        }

        return this.onParse(this, value, errors);
    }

    toJSON(target: PropertyBag, value: T) {
        if (!this.onToJSON) {
            throw new Error("CustomPropertyDefinition instances must have an onToJSON handler.");
        }

        this.onToJSON(this, target, value);
    }

    constructor(
        readonly targetVersion: Shared.TargetVersion,
        readonly name: string,
        readonly onParse: (sender: PropertyDefinition, value: any, errors?: Shared.IValidationError[]) => T | undefined,
        readonly onToJSON: (sender: PropertyDefinition, target: PropertyBag, value: T) => void,
        readonly defaultValue?: T,
        readonly onGetInitialValue?: (sender: object) => T) {
        super(targetVersion, name, defaultValue, onGetInitialValue);
    }
}

export class SerializableObjectSchema implements Iterable<PropertyDefinition> {
    private _properties: PropertyDefinition[] = [];

    indexOf(property: PropertyDefinition): number {
        for (let i = 0; i < this._properties.length; i++) {
            if (this._properties[i] === property) {
                return i;
            }
        }

        return -1;
    }

    add(property: PropertyDefinition) {
        if (this.indexOf(property) === -1) {
            this._properties.push(property);
        }
    }

    remove(property: PropertyDefinition) {
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

    [Symbol.iterator]() {
        let index = 0;
        let properties = this._properties;

        return {
            next(): IteratorResult<PropertyDefinition> {
                if (index < properties.length) {
                    return {
                        done: false,
                        value: properties[index++]
                    }
                }
                else {
                    return {
                        done: true,
                        value: undefined as unknown as PropertyDefinition
                    }
                }
            }
        }
    }
}

export type PropertyBag = { [propertyName: string]: any };

export abstract class SerializableObject {
    private static readonly _schemaCache: { [typeName: string]: SerializableObjectSchema } = {};
    
    private _propertyBag: PropertyBag = {};
    private _rawProperties: PropertyBag = {};

    protected getSchemaKey(): string {
        return this.constructor.name;
    }

    protected populateSchema(schema: SerializableObjectSchema) {
        // Do nothing in base implementation
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
        for (let property of this.schema) {
            if (property.onGetInitialValue) {
                this.setValue(property, property.onGetInitialValue(this));
            }
        }
    }

    parse(json: any, errors?: Shared.IValidationError[]) {
        this._propertyBag = {};
        this._rawProperties = Shared.GlobalSettings.enableFullJsonRoundTrip ? json : {};

        for (let property of this.schema) {
            this.setValue(property, property.parse(json[property.name], errors));
        }
    }

    toJSON(): any {
        let result: any;

        if (Shared.GlobalSettings.enableFullJsonRoundTrip && this._rawProperties && typeof this._rawProperties === "object") {
            result = this._rawProperties;
        }
        else {
            result = {};
        }

        for (let property of this.schema) {
            property.toJSON(result, this.getValue(property));
        }

        return result;
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

    get schema(): SerializableObjectSchema {
        let schema: SerializableObjectSchema = SerializableObject._schemaCache[this.getSchemaKey()];

        if (!schema) {
            schema = new SerializableObjectSchema();
            
            this.populateSchema(schema);

            SerializableObject._schemaCache[this.getSchemaKey()] = schema;
        }

        return schema;
    }
}