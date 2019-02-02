export enum ValueKind { String, Boolean, Number }

export type PropertyDictionary = { [key: string]: DataType };

export abstract class DataType {
    private static internalCreateDataTypeFrom(parent: DataType, input: any, label: string): DataType {
        if (typeof input === "string") {
            return new ValueType(parent, label, ValueKind.String);
        }
        else if (typeof input === "boolean") {
            return new ValueType(parent, label, ValueKind.Boolean);
        }
        else if (typeof input === "number") {
            return new ValueType(parent, label, ValueKind.Number);
        }
        else if (typeof input === "object") {
            if (Array.isArray(input)) {
                let result = new ArrayType(parent, label);

                result.itemDataType = input.length == 0 ? undefined : DataType.internalCreateDataTypeFrom(result, input[0], "");

                return result;
            }
            else {
                let result = new ObjectType(parent, label);
    
                for (let key of Object.keys(input)) {
                    let dataType = DataType.internalCreateDataTypeFrom(result, input[key], key);

                    if (dataType) {
                        result.properties[key] = dataType;
                    }
                }
    
                return result;
            }
        }
        else {
            throw new Error("Unsupported data type: " + typeof input);
        }
    }

    static createDataTypeFrom(input: any): DataType {
        return DataType.internalCreateDataTypeFrom(null, input, "$root");
    }

    constructor(readonly parent: DataType, readonly label: string) {}

    abstract getTypeName(): string;

    getPath(asLeaf: boolean): string {
        let parentPath: string = "";
        
        if (this.parent) {
            parentPath = this.parent.getPath(false);
        }
        
        return parentPath + this.label;
    }

    getProperties(): PropertyDictionary {
        return null;
    }
}

export class ValueType extends DataType {
    constructor(readonly parent: DataType, readonly label: string, readonly valueTypeKind: ValueKind) {
        super(parent, label);
    }

    getTypeName(): string {
        return ValueKind[this.valueTypeKind];
    }
}

export class ArrayType extends DataType {
    itemDataType: DataType;

    constructor(readonly parent: DataType, readonly label: string) {
        super(parent, label);
    }

    getPath(asLeaf: boolean): string {
        let result = super.getPath(asLeaf);

        if (!asLeaf) {
            result += "[0]";
        }

        return result;
    }

    getProperties(): PropertyDictionary {
        if (this.itemDataType instanceof ObjectType) {
            return this.itemDataType.properties;
        }
        else {
            return null;
        }
    }

    getTypeName(): string {
        return "Array";
    }
}

export class ObjectType extends DataType {
    readonly properties: PropertyDictionary = {};

    constructor(readonly parent: DataType, readonly label: string) {
        super(parent, label);
    }
    
    getPath(asLeaf: boolean): string {
        let result = super.getPath(asLeaf);

        if (!asLeaf) {
            result += ".";
        }

        return result;
    }

    getProperties(): PropertyDictionary {
        return this.properties;
    }

    getTypeName(): string {
        return "Object";
    }
}