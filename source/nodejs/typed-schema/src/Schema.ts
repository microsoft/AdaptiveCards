import { SchemaClass } from "./SchemaClass";
import { SchemaType } from "./SchemaType";
import { SchemaEnum } from "./SchemaEnum";

export class Schema {
	private _typeDictionary: Map<string, SchemaType> = new Map<string, SchemaType>();
	
	constructor (types: any[]) {

		types.forEach(type => {
			this._typeDictionary.set(type.type, this.parse(type));
		});

		// Resolve types
		this._typeDictionary.forEach(type => {
			type.resolve(this._typeDictionary);
		});

		this._typeDictionary.forEach(type => {
			if (type instanceof SchemaClass) {
				type.resolveImplementations(this._typeDictionary);
			}
		});
	}

	parse(sourceObj: any) : SchemaType {
		if (sourceObj.classType === "Enum") {
			return new SchemaEnum(sourceObj);
		} else if (sourceObj.classType === "Class" || sourceObj.classType === undefined) {
			return new SchemaClass(sourceObj);
		} else {
			throw new Error("Unknown classType " + sourceObj.classType);
		}
	}

	get typeDictionary() {
		return this._typeDictionary;
	}

	getType(typeName: string) : SchemaType {
		var answer = this._typeDictionary.get(typeName);
		if (answer === undefined) {
			var knownTypes = "";
			this._typeDictionary.forEach((value, key) => {
				if (knownTypes.length > 0) {
					knownTypes += ", ";
				}
				knownTypes += key;
			});
			throw new Error("Type " + typeName + " could not be found. Known types: " + knownTypes);
		}
		return answer;
	}
}