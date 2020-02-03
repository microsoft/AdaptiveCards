export enum ValueKind { String, Boolean, Number }

export abstract class DataType {
    static create(parent: FieldDefinition, value: any): DataType {
        if (typeof value === "string") {
            return new ValueData(parent, ValueKind.String);
        }
        else if (typeof value === "boolean") {
            return new ValueData(parent, ValueKind.Boolean);
        }
        else if (typeof value === "number") {
            return new ValueData(parent, ValueKind.Number);
        }
        else if (typeof value === "object") {
            if (Array.isArray(value)) {
                return ArrayData.create(parent, value);
            }
            else {
                return ObjectData.create(parent, value);
            }
        }
        else {
            throw new Error("Unsupported data type: " + typeof value);
        }
    }

    constructor(readonly owner: FieldDefinition) {}

    getChildFields(): FieldDefinition[] {
        return null;
    }

    qualifyFieldName(fieldName: string, fieldIsLeaf: boolean) {
        return fieldName;
    }

    abstract get typeName(): string;

    get isCollection(): boolean {
        return false;
    }
}

export class ValueData extends DataType {
    constructor(readonly owner: FieldDefinition, readonly valueKind: ValueKind) {
        super(owner);
    }

    get typeName(): string {
        return ValueKind[this.valueKind];
    }
}

export class ArrayData extends DataType {
    static create(parent: FieldDefinition, input: Object): ArrayData {
        if (!Array.isArray(input)) {
            throw new Error("Input is not an array.");
        }

        let result = new ArrayData(parent);

        if (input.length > 0) {
            result.dataType = DataType.create(parent, input[0]);
        }

        return result;
    }

    dataType: DataType = undefined;

    constructor(readonly owner: FieldDefinition) {
        super(owner);
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

    get typeName(): string {
        return "Array";
    }
}

export class ObjectData extends DataType {
    static create(parent: FieldDefinition, input: Object): ObjectData {
        let result = new ObjectData(parent);

        for (let key of Object.keys(input)) {
            let field = new FieldDefinition(parent);
            field.dataType =  DataType.create(field, input[key]);
            field.name = key;

            result.fields.push(field);
        }

        return result;
    }

    readonly fields: FieldDefinition[] = [];

    constructor(readonly owner: FieldDefinition) {
        super(owner);
    }
    
    getChildFields(): FieldDefinition[] {
        return this.fields;
    }

    get typeName(): string {
        return "Object";
    }
}

export class FieldDefinition {
    static create(input: any): FieldDefinition {
        let field = new FieldDefinition(null);
        field.name = "$root";
        field.dataType = DataType.create(field, input);

        return field;
    }

    name: string;
    displayName: string;
    dataType: DataType;

    constructor(readonly parent: FieldDefinition) {}

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

    get children(): FieldDefinition[] {
        return this.dataType.getChildFields();
    }

    get isCollection(): boolean {
        return this.dataType.isCollection;
    }

    get typeName(): string {
        return this.dataType.typeName;
    }
}