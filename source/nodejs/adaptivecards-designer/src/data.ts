// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export type ValueType = "String" | "Boolean" | "Number" | "Array" | "Object";

export interface IStringData {
    valueType: "String"
    sampleValue?: string;
}

export interface INumberData {
    valueType: "Number"
    sampleValue?: number;
}

export interface IBooleanData {
    valueType: "Boolean"
    sampleValue?: boolean;
}

export interface IArrayData {
    valueType: "Array";
    itemType: IData;
}

export interface IObjectData {
    valueType: "Object";
    fields: IField[];
}

export type IData = IStringData | IBooleanData | INumberData | IArrayData | IObjectData;

export interface IDataField {
    name: string;
    displayName: string;
}

export interface IStringField extends IDataField, IStringData { }
export interface INumberField extends IDataField, INumberData { }
export interface IBooleanField extends IDataField, IBooleanData { }
export interface IObjectField extends IDataField, IObjectData { }
export interface IArrayField extends IDataField, IArrayData { }

export type IField = IStringField | INumberField | IBooleanField | IObjectField | IArrayField;

export abstract class DataType {
    static parse(parent: FieldDefinition, data: IData): DataType {
        switch (data.valueType) {
            case "String":
                return new ValueTypeData<string>(parent, "Sample data", data.sampleValue);
            case "Number":
                return new ValueTypeData<number>(parent, 123, data.sampleValue);
            case "Boolean":
                return new ValueTypeData<boolean>(parent, true, data.sampleValue);
            case "Array":
                return ArrayData.parse(parent, data);
            case "Object":
                return ObjectData.parse(parent, data);
        }
    }

    static deriveFrom(parent: FieldDefinition, value: any): DataType {
        if (typeof value === "string") {
            return new ValueTypeData<string>(parent, "Sample data", value);
        }
        else if (typeof value === "boolean") {
            return new ValueTypeData<boolean>(parent, true, value);
        }
        else if (typeof value === "number") {
            return new ValueTypeData<number>(parent, 123, value);
        }
        else if (typeof value === "object") {
            if (Array.isArray(value)) {
                return ArrayData.deriveFrom(parent, value);
            }
            else {
                return ObjectData.deriveFrom(parent, value);
            }
        }
        else {
            throw new Error("Unsupported data type: " + typeof value);
        }
    }

    constructor(readonly owner: FieldDefinition) {}

    abstract generateSampleData(): any;

    getChildFields(): FieldDefinition[] {
        return null;
    }

    qualifyFieldName(fieldName: string, fieldIsLeaf: boolean) {
        return fieldName;
    }

    abstract get valueType(): ValueType;

    get isCollection(): boolean {
        return false;
    }
}

export class ValueTypeData<T extends string | number | boolean> extends DataType {
    private _sampleValue: T;

    constructor(
        readonly owner: FieldDefinition,
        readonly defaultSampleValue: T,
        sampleValue?: T) {
        super(owner);

        this._sampleValue = sampleValue;
    }

    generateSampleData(): T {
        return this.sampleValue ? this.sampleValue : this.defaultSampleValue;
    }

    get sampleValue() {
        return this._sampleValue;
    }

    get valueType(): ValueType {
        switch (typeof this.defaultSampleValue) {
            case "string":
                return "String";
            case "number":
                return "Number";
            case "boolean":
                return "Boolean";
        }
    }
}

export class ArrayData extends DataType {
    static parse(parent: FieldDefinition, data: IArrayData): ArrayData {
        let result = new ArrayData(parent);
        result.dataType = DataType.parse(parent, data.itemType);

        return result;
    }

    static deriveFrom(parent: FieldDefinition, input: object): ArrayData {
        if (!Array.isArray(input)) {
            throw new Error("Input is not an array.");
        }

        let result = new ArrayData(parent);

        if (input.length > 0) {
            result.dataType = DataType.deriveFrom(parent, input[0]);
        }

        return result;
    }

    dataType: DataType = undefined;

    constructor(readonly owner: FieldDefinition) {
        super(owner);
    }

    generateSampleData(): any {
        let result = [];

        for (let i = 1; i <= 3; i++) {
            result.push(this.dataType.generateSampleData());
        }

        return result;
    }

    getChildFields(): FieldDefinition[] {
        return this.dataType.getChildFields();
    }

    qualifyFieldName(fieldName: string, fieldIsLeaf: boolean) {
        if (!fieldIsLeaf) {
            return fieldName + "[0]";
        }
        else {
            return super.qualifyFieldName(fieldName, fieldIsLeaf);
        }
    }

    get isCollection(): boolean {
        return true;
    }

    get valueType(): ValueType {
        return "Array";
    }
}

export class ObjectData extends DataType {
    static parse(parent: FieldDefinition, data: IObjectData): ObjectData {
        let result = new ObjectData(parent);

        for (let field of data.fields) {
            let fieldDefinition = new FieldDefinition(parent);
            fieldDefinition.name = field.name;
            fieldDefinition.displayName = field.displayName;
            fieldDefinition.dataType = DataType.parse(fieldDefinition, <IData>field);

            result.fields.push(fieldDefinition);
        }

        return result;
    }

    static deriveFrom(parent: FieldDefinition, input: object): ObjectData {
        let result = new ObjectData(parent);

        for (let key of Object.keys(input)) {
            let field = new FieldDefinition(parent);
            field.dataType =  DataType.deriveFrom(field, input[key]);
            field.name = key;

            result.fields.push(field);
        }

        return result;
    }

    readonly fields: FieldDefinition[] = [];

    constructor(readonly owner: FieldDefinition) {
        super(owner);
    }

    generateSampleData(): any {
        let result = {};

        for (let field of this.fields) {
            result[field.name] = field.dataType.generateSampleData();
        }

        return result;
    }

    getChildFields(): FieldDefinition[] {
        return this.fields;
    }

    get valueType(): ValueType {
        return "Object";
    }
}

export class FieldDefinition {
    static parse(data: IData): FieldDefinition {
        let field = new FieldDefinition(null);
        field.name = "$root";
        field.dataType = DataType.parse(field, data);

        return field;
    }

    static deriveFrom(input: any): FieldDefinition {
        let field = new FieldDefinition(null);
        field.name = "$root";
        field.dataType = DataType.deriveFrom(field, input);

        return field;
    }

    private _displayName: string;

    name: string;
    dataType: DataType;

    constructor(readonly parent: FieldDefinition) {}

    asExpression(): string {
        return "${" + this.getPath() + "}";
    }

    getPath(asLeaf: boolean = true): string {
        let result: string = this.qualifiedName(asLeaf);
        let currentField = this.parent;

        while (currentField) {
            result = currentField.qualifiedName(false) + "." + result;

            currentField = currentField.parent;
        }

        return result;
    }

    qualifiedName(asLeaf: boolean): string {
        return this.dataType.qualifyFieldName(this.name, asLeaf);
    }

    get displayName(): string {
        return this._displayName ? this._displayName : this.name;
    }

    set displayName(value: string) {
        this._displayName = value;
    }

    get children(): FieldDefinition[] {
        return this.dataType.getChildFields();
    }

    get isCollection(): boolean {
        return this.dataType.isCollection;
    }

    get valueType(): string {
        return this.dataType.valueType;
    }
}
