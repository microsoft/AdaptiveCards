// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { GlobalSettings, SizeAndUnit } from "./shared";
import * as Utils from "./utils";
import * as Enums from "./enums";

export interface IValidationEvent {
    source?: SerializableObject,
    phase: Enums.ValidationPhase,
    event: Enums.ValidationEvent,
    message: string;
}

export class Version {
    private _versionString: string;
    private _major: number;
    private _minor: number;
    private _isValid: boolean = true;
    private _label?: string;

    constructor(major: number = 1, minor: number = 1, label?: string) {
        this._major = major;
        this._minor = minor;
        this._label = label;
    }

    static parse(versionString: string, context: BaseSerializationContext): Version | undefined {
        if (!versionString) {
            return undefined;
        }

        let result = new Version();
        result._versionString = versionString;

        let regEx = /(\d+).(\d+)/gi;
        let matches = regEx.exec(versionString);

        if (matches != null && matches.length == 3) {
            result._major = parseInt(matches[1]);
            result._minor = parseInt(matches[2]);
        }
        else {
            result._isValid = false;
        }

        if (!result._isValid) {
            context.logParseEvent(
                Enums.ValidationEvent.InvalidPropertyValue,
                "Invalid version string: " + result._versionString);
        }

        return result;
    }

    toString(): string {
        return !this._isValid ? this._versionString : this._major + "." + this._minor;
    }

    toJSON(): any {
        return this.toString();
    }

    compareTo(otherVersion: Version): number {
        if (!this.isValid || !otherVersion.isValid) {
            throw new Error("Cannot compare invalid version.");
        }

        if (this.major > otherVersion.major) {
            return 1;
        }
        else if (this.major < otherVersion.major) {
            return -1;
        }
        else if (this.minor > otherVersion.minor) {
            return 1;
        }
        else if (this.minor < otherVersion.minor) {
            return -1;
        }

        return 0;
    }

    get label(): string {
        return this._label ? this._label : this.toString();
    }

    get major(): number {
        return this._major;
    }

    get minor(): number {
        return this._minor;
    }

    get isValid(): boolean {
        return this._isValid;
    }
}

export type TargetVersion = Version | "*";

export class Versions {
    static readonly v1_0 = new Version(1, 0);
    static readonly v1_1 = new Version(1, 1);
    static readonly v1_2 = new Version(1, 2);
    static readonly latest = Versions.v1_2;
    static readonly vNext = new Version(1000, 0, "vNext");
}

export function isVersionLessOrEqual(version: TargetVersion, targetVersion: TargetVersion): boolean {
    if (version instanceof Version) {
        if (targetVersion instanceof Version) {
            return targetVersion.compareTo(version) >= 0;
        }
        else {
            // Target version is *
            return true;
        }
    }
    else {
        // Version is *
        return true;
    }
}

export abstract class BaseSerializationContext {
    private _validationEvents: IValidationEvent[] = [];

    constructor(public targetVersion: Version = Versions.latest) {}

    serializeValue(target: { [key: string]: any }, propertyName: string, propertyValue: any, defaultValue: any = undefined) {
        if (propertyValue === null || propertyValue === undefined || propertyValue === defaultValue) {
            delete target[propertyName];
        }
        else {
            target[propertyName] = propertyValue;
        }
    }

    serializeNumber(target: { [key: string]: any }, propertyName: string, propertyValue: number | undefined, defaultValue: number | undefined = undefined) {
        if (propertyValue === null || propertyValue === undefined || propertyValue === defaultValue || isNaN(propertyValue)) {
            delete target[propertyName];
        }
        else {
            target[propertyName] = propertyValue;
        }
    }

    serializeEnum(
        enumType: { [s: number]: string },
        target: { [key: string]: any },
        propertyName: string,
        propertyValue: number | undefined,
        defaultValue: number | undefined = undefined) {
        let targetValue = target[propertyName];

        let canDeleteTarget = targetValue == undefined ? true : enumType[targetValue] !== undefined;

        if (propertyValue == defaultValue) {
            if (canDeleteTarget) {
                delete target[propertyName];
            }
        }
        else {
            if (propertyValue == undefined) {
                if (canDeleteTarget) {
                    delete target[propertyName];
                }
            }
            else {
                target[propertyName] = enumType[propertyValue];
            }
        }
    }

    serializeArray(target: { [key: string]: any }, propertyName: string, propertyValue: any[] | undefined) {
        let items = [];

        if (propertyValue) {
            for (let item of propertyValue) {
                let serializedItem: any = undefined;

                if (item instanceof SerializableObject) {
                    serializedItem = item.toJSON(this);
                }
                else if (item.toJSON) {
                    serializedItem = item.toJSON();
                }
                else {
                    serializedItem = item;
                }

                if (serializedItem !== undefined) {
                    items.push(serializedItem);
                }
            }
        }

        if (items.length == 0) {
            if (target.hasOwnProperty(propertyName) && Array.isArray(target[propertyName])) {
                delete target[propertyName];
            }
        }
        else {
            this.serializeValue(target, propertyName, items);
        }
    }

    clearEvents() {
        this._validationEvents = [];
    }

    logEvent(
        phase: Enums.ValidationPhase,
        event: Enums.ValidationEvent,
        message: string,
        source?: SerializableObject) {
        this._validationEvents.push(
            {
                phase: phase,
                event: event,
                message: message
            }
        )
    }

    logParseEvent(event: Enums.ValidationEvent, message: string, source?: SerializableObject) {
        this.logEvent(Enums.ValidationPhase.Parse, event, message, source);
    }

    getEventAt(index: number): IValidationEvent {
        return this._validationEvents[index];
    }

    shouldSerialize(o: SerializableObject): boolean {
        return true;
    }

    get eventCount(): number {
        return this._validationEvents.length;
    }
}

class SimpleSerializationContext extends BaseSerializationContext {}

export class PropertyDefinition {
    private static _sequentialNumber: number = 0;

    getInternalName(): string {
        return this.name;
    }

    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): any {
        return source[this.name];
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: any, context: BaseSerializationContext): void {
        context.serializeValue(target, this.name, value, this.defaultValue);
    }

    readonly sequentialNumber: number;

    constructor(
        readonly targetVersion: Version,
        readonly name: string,
        readonly defaultValue?: any,
        readonly onGetInitialValue?: (sender: SerializableObject) => any) {
            this.sequentialNumber = PropertyDefinition._sequentialNumber;

            PropertyDefinition._sequentialNumber++;
        }
}

export class StringProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): string | undefined {
        let parsedValue = Utils.parseString(source[this.name], this.defaultValue);
        let isUndefined = parsedValue === undefined || (parsedValue === "" && this.treatEmptyAsUndefined);

        if (!isUndefined && this.regEx !== undefined) {
            let matches = this.regEx.exec(<string>parsedValue);

            if (!matches) {
                context.logParseEvent(
                    Enums.ValidationEvent.InvalidPropertyValue,
                    `Invalid "${this.name}" value "${parsedValue}"`,
                    sender);

                return undefined;
            }
        }

        return parsedValue;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: string | undefined, context: BaseSerializationContext) {
        context.serializeValue(
            target,
            this.name,
            value === "" && this.treatEmptyAsUndefined ? undefined : value,
            this.defaultValue);
    }

    constructor(
        readonly targetVersion: Version,
        readonly name: string,
        readonly treatEmptyAsUndefined: boolean = true,
        readonly regEx?: RegExp,
        readonly defaultValue?: string,
        readonly onGetInitialValue?: (sender: SerializableObject) => string) {
        super(targetVersion, name, defaultValue, onGetInitialValue);
    }
}

export class BoolProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): boolean | undefined {
        return Utils.parseBool(source[this.name], this.defaultValue);
    }

    toJSON(sender: SerializableObject, target: object, value: boolean | undefined, context: BaseSerializationContext) {
        context.serializeValue(
            target,
            this.name,
            value,
            this.defaultValue);
    }
}

export class NumProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): number | undefined {
        return Utils.parseNumber(source[this.name], this.defaultValue);
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: number | undefined, context: BaseSerializationContext) {
        context.serializeNumber(
            target,
            this.name,
            value,
            this.defaultValue);
    }
}

export class PixelSizeProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): number | undefined {
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
                context.logParseEvent(
                    Enums.ValidationEvent.InvalidPropertyValue,
                    "Invalid \"minHeight\" value: " + source[this.name],
                    sender);
            }
        }

        return result;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: number | undefined, context: BaseSerializationContext) {
        context.serializeValue(
            target,
            this.name,
            typeof value === "number" && !isNaN(value) ? value + "px" : undefined);
    }
}

export interface IVersionedValue<TValue> {
    value: TValue;
    targetVersion?: Version;
}

export class StringArrayProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): string[] | undefined {
        let sourceValue = source[this.name];

        if (sourceValue === undefined || !Array.isArray(sourceValue)) {
            return this.defaultValue;
        }

        let result: string[] = [];

        for (let value of sourceValue) {
            if (typeof value === "string") {
                result.push(value);
            }
            else {
                context.logParseEvent(
                    Enums.ValidationEvent.InvalidPropertyValue,
                    `Invalid array value "${value}" of type "${typeof value}" ignored for "${this.name}".`,
                    sender);
            }
        }

        return result;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: string[] | undefined, context: BaseSerializationContext) {
        context.serializeArray(target, this.name, value);
    }

    constructor(
        readonly targetVersion: Version,
        readonly name: string,
        readonly defaultValue?: string[],
        readonly onGetInitialValue?: (sender: SerializableObject) => string[] | undefined) {
        super(targetVersion, name, defaultValue, onGetInitialValue);
    }
}

export class ValueSetProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): string | undefined {
        let sourceValue = source[this.name];

        if (sourceValue === undefined) {
            return this.defaultValue;
        }

        if (typeof sourceValue === "string") {
            for (let versionedValue of this.values) {
                if (sourceValue.toLowerCase() === versionedValue.value.toLowerCase()) {
                    let targetVersion = versionedValue.targetVersion ? versionedValue.targetVersion : this.targetVersion;

                    if (targetVersion.compareTo(context.targetVersion) <= 0) {
                        return versionedValue.value;
                    }
                    else {
                        context.logParseEvent(
                            Enums.ValidationEvent.InvalidPropertyValue,
                            `"${this.name}" value "${sourceValue}" is supported in version ${targetVersion.toString()}, but you are using version ${context.targetVersion.toString()}`,
                            sender);

                        return this.defaultValue;
                    }
                }
            }
        }

        context.logParseEvent(
            Enums.ValidationEvent.InvalidPropertyValue,
            `Invalid "${this.name}" value "${sourceValue}"`,
            sender);

        return this.defaultValue;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: string | undefined, context: BaseSerializationContext) {
        let valueFound = false;

        for (let versionedValue of this.values) {
            if (versionedValue.value === value) {
                let targetVersion = versionedValue.targetVersion ? versionedValue.targetVersion : this.targetVersion;

                if (targetVersion.compareTo(context.targetVersion) <= 0) {
                    valueFound = true;

                    break;
                }
                else {
                    context.logEvent(
                        Enums.ValidationPhase.ToJSON,
                        Enums.ValidationEvent.InvalidPropertyValue,
                        `"${this.name}" value "${value}" is supported in version ${targetVersion.toString()}, but you are using version ${context.targetVersion.toString()}`,
                        sender);
                }
            }
        }

        if (valueFound) {
            context.serializeValue(
                target,
                this.name,
                value,
                this.defaultValue);
        }
    }

    constructor(
        readonly targetVersion: Version,
        readonly name: string,
        readonly values: IVersionedValue<string>[],
        readonly defaultValue?: string,
        readonly onGetInitialValue?: (sender: SerializableObject) => string) {
        super(targetVersion, name, defaultValue, onGetInitialValue);
    }
}

export class EnumProperty<TEnum extends { [s: number]: string }> extends PropertyDefinition {
    private _values: IVersionedValue<number>[] = [];

    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): number | undefined {
        let sourceValue = source[this.name];

        if (typeof sourceValue !== "string") {
            return this.defaultValue;
        }

        let enumValue = Utils.getEnumValueByName(this.enumType, sourceValue);

        if (enumValue !== undefined) {
            for (let versionedValue of this.values) {
                if (versionedValue.value === enumValue) {
                    let targetVersion = versionedValue.targetVersion ? versionedValue.targetVersion : this.targetVersion;

                    if (targetVersion.compareTo(context.targetVersion) <= 0) {
                        return enumValue;
                    }
                    else {
                        context.logParseEvent(
                            Enums.ValidationEvent.InvalidPropertyValue,
                            `"${this.name}" value "${sourceValue}" is supported in version ${targetVersion.toString()}, but you are using version ${context.targetVersion.toString()}`,
                            sender);

                        return this.defaultValue;
                    }
                }
            }
        }

        context.logParseEvent(
            Enums.ValidationEvent.InvalidPropertyValue,
            `Invalid "${this.name}" value "${sourceValue}"`,
            sender);

        return this.defaultValue;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: number | undefined, context: BaseSerializationContext) {
        if (value !== undefined) {
            let valueFound = false;

            for (let versionedValue of this.values) {
                if (versionedValue.value === value) {
                    let targetVersion = versionedValue.targetVersion ? versionedValue.targetVersion : this.targetVersion;

                    if (targetVersion.compareTo(context.targetVersion) <= 0) {
                        valueFound = true;

                        break;
                    }
                    else {
                        context.logEvent(
                            Enums.ValidationPhase.ToJSON,
                            Enums.ValidationEvent.InvalidPropertyValue,
                            `Invalid "${this.name}" value "${value}"`,
                            sender);
                    }
                }
            }

            if (valueFound) {
                context.serializeEnum(
                    this.enumType,
                    target,
                    this.name,
                    value,
                    this.defaultValue);
            }
        }
    }

    constructor(
        readonly targetVersion: Version,
        readonly name: string,
        readonly enumType: TEnum,
        readonly defaultValue?: number,
        values?: IVersionedValue<number>[],
        readonly onGetInitialValue?: (sender: SerializableObject) => number) {
        super(targetVersion, name, defaultValue, onGetInitialValue);

        if (!values) {
            for (let key in enumType) {
                let keyAsNumber = parseInt(key, 10);

                if (keyAsNumber >= 0) {
                    this._values.push( { value: keyAsNumber });
                }
            }
        }
        else {
            this._values = values;
        }
    }

    get values(): IVersionedValue<number>[] {
        return this._values;
    }
}

export type SerializableObjectType = { new(): SerializableObject };

export class SerializableObjectProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): SerializableObject | undefined {
        let sourceValue = source[this.name];

        if (sourceValue === undefined) {
            return this.onGetInitialValue ? this.onGetInitialValue(sender) : this.defaultValue;
        }

        let result = new this.objectType();
        result.parse(sourceValue, context);

        return result;
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: SerializableObject | undefined, context: BaseSerializationContext) {
        let serializedValue = value !== undefined ? value.toJSON(context) : value;

        if (typeof serializedValue === "object" && Object.keys(serializedValue).length === 0) {
            serializedValue = undefined;
        }

        super.toJSON(sender, target, serializedValue, context);
    }

    constructor(
        readonly targetVersion: Version,
        readonly name: string,
        readonly objectType: SerializableObjectType,
        readonly nullable: boolean = false) {
        super(
            targetVersion,
            name,
            undefined,
            (sender: SerializableObject) => { return this.nullable ? undefined : new this.objectType(); });
    }
}

export class SerializableObjectCollectionProperty extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): SerializableObject[] | undefined {
        let result: SerializableObject[] | undefined = [];

        let sourceCollection = source[this.name];

        if (Array.isArray(sourceCollection)) {
            for (let sourceItem of sourceCollection) {
                let item = new this.objectType();
                item.parse(sourceItem, context);

                result.push(item);

                if (this.onItemAdded) {
                    this.onItemAdded(sender, item);
                }
            }
        }

        return result.length > 0 ? result : (this.onGetInitialValue ? this.onGetInitialValue(sender) : undefined);
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: SerializableObject[] | undefined, context: BaseSerializationContext) {
        context.serializeArray(target, this.name, value);
    }

    constructor(
        readonly targetVersion: Version,
        readonly name: string,
        readonly objectType: SerializableObjectType,
        readonly onItemAdded?: (sender: SerializableObject, item: SerializableObject) => void) {
        super(
            targetVersion,
            name,
            undefined,
            (sender: SerializableObject) => { return []; });
    }
}

export class CustomProperty<T> extends PropertyDefinition {
    parse(sender: SerializableObject, source: PropertyBag, context: BaseSerializationContext): T {
        return this.onParse(sender, this, source, context);
    }

    toJSON(sender: SerializableObject, target: PropertyBag, value: T, context: BaseSerializationContext) {
        this.onToJSON(sender, this, target, value, context);
    }

    constructor(
        readonly targetVersion: Version,
        readonly name: string,
        readonly onParse: (sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => T,
        readonly onToJSON: (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: T, context: BaseSerializationContext) => void,
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

// This is a decorator function, used to map SerializableObject descendant class members to
// schema properties
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
    static onRegisterCustomProperties?: (sender: SerializableObject, schema: SerializableObjectSchema) => void;

    private static readonly _schemaCache: { [typeName: string]: SerializableObjectSchema } = {};

    private _propertyBag: PropertyBag = {};
    private _rawProperties: PropertyBag = {};

    protected abstract getSchemaKey(): string;

    protected populateSchema(schema: SerializableObjectSchema) {
        let ctor = <any>this.constructor;
        let properties: PropertyDefinition[] = [];

        for (let propertyName in ctor) {
            try {
                let propertyValue = ctor[propertyName];

                if (propertyValue instanceof PropertyDefinition) {
                    properties.push(propertyValue);
                }
            }
            catch {
                // If a property happens to have a getter function and
                // it throws an exception, we need to catch it here
            }
        }

        if (properties.length > 0) {
            let sortedProperties = properties.sort((p1: PropertyDefinition, p2: PropertyDefinition) => {
                if (p1.sequentialNumber > p2.sequentialNumber) {
                    return 1;
                }
                else if (p1.sequentialNumber < p2.sequentialNumber) {
                    return -1;
                }

                return 0;
            });

            schema.add(...sortedProperties);
        }

        if (SerializableObject.onRegisterCustomProperties) {
            SerializableObject.onRegisterCustomProperties(this, schema);
        }
    }

    protected getValue(property: PropertyDefinition): any {
        return this._propertyBag.hasOwnProperty(property.getInternalName()) ? this._propertyBag[property.getInternalName()] : property.defaultValue;
    }

    protected setValue(property: PropertyDefinition, value: any) {
        if (value === undefined || value === null) {
            delete this._propertyBag[property.getInternalName()];
        }
        else {
            this._propertyBag[property.getInternalName()] = value;
        }
    }

    protected internalParse(source: PropertyBag, context: BaseSerializationContext) {
        this._propertyBag = {};
        this._rawProperties = GlobalSettings.enableFullJsonRoundTrip ? (source ? source : {}) : {};

        if (source) {
            let s = this.getSchema();

            for (let i = 0; i < s.getCount(); i++) {
                let property = s.getItemAt(i);

                let propertyValue = property.onGetInitialValue ? property.onGetInitialValue(this) : undefined;

                if (source.hasOwnProperty(property.name)) {
                    if (property.targetVersion.compareTo(context.targetVersion) <= 0) {
                        propertyValue = property.parse(this, source, context);
                    }
                    else {
                        context.logParseEvent(
                            Enums.ValidationEvent.UnsupportedProperty,
                            `Property "${property.name}" is supported in version ${property.targetVersion.toString()}, but you are using version ${context.targetVersion.toString()}`,
                            this);
                    }
                }

                this.setValue(property, propertyValue);
            }
        }
        else {
            this.resetDefaultValues();
        }
    }

    protected internalToJSON(target: PropertyBag, context: BaseSerializationContext) {
        let s = this.getSchema();
        let serializedProperties: string[] = [];

        for (let i = 0; i < s.getCount(); i++) {
            let property = s.getItemAt(i);

            // Avoid serializing the same property multiple times. This is necessary
            // because some property definitions map to the same underlying schema
            // property
            if (property.targetVersion.compareTo(context.targetVersion) <= 0 && serializedProperties.indexOf(property.name) === -1) {
                property.toJSON(this, target, this.getValue(property), context);

                serializedProperties.push(property.name);
            }
        }
    }

    maxVersion: Version = Versions.latest;

    constructor() {
        let s = this.getSchema();

        for (let i = 0; i < s.getCount(); i++) {
            let property = s.getItemAt(i);

            if (property.onGetInitialValue) {
                this.setValue(property, property.onGetInitialValue(this));
            }
        }
    }

    parse(source: PropertyBag, context?: BaseSerializationContext) {
        this.internalParse(source, context ? context : new SimpleSerializationContext());
    }

    toJSON(context?: BaseSerializationContext): PropertyBag | undefined {
        let effectiveContext = context ? context : new SimpleSerializationContext();

        if (effectiveContext.shouldSerialize(this)) {
            let result: PropertyBag;

            if (GlobalSettings.enableFullJsonRoundTrip && this._rawProperties && typeof this._rawProperties === "object") {
                result = this._rawProperties;
            }
            else {
                result = {};
            }

            this.internalToJSON(result, effectiveContext);

            return result;
        }
        else {
            return undefined;
        }
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
        let shouldDeleteProperty = (typeof value === "string" && !value) || value === undefined || value === null;

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
