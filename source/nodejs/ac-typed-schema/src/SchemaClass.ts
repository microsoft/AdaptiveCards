// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { SchemaType } from "./SchemaType";
import { SchemaProperty } from "./SchemaProperty";

export class SchemaClass extends SchemaType {
	private _properties: Map<string, SchemaProperty> = new Map<string, SchemaProperty>();
	private _isAbstract: boolean = false;
	private _extends: SchemaClass[] = [];
	private _implementations: SchemaClass[] = [];
	private _shorthand?: SchemaProperty;

	constructor(sourceObj: any) {
		super(sourceObj);

		if (sourceObj.properties) {
			for (var key in sourceObj.properties) {
				this._properties.set(key, new SchemaProperty(key, sourceObj.properties[key]));
			}
		}
		if (sourceObj.isAbstract) {
			this._isAbstract = true;
		}
	}

	get properties() {
		return this._properties;
	}

	get isAbstract() {
		return this._isAbstract;
	}

	get extends() {
		return this._extends;
	}

	get implementations() {
		return this._implementations;
	}

	get shorthand() {
		return this._shorthand;
	}

	// Gets all extended, including descendants
	getAllExtended() {
		var answer: SchemaClass[] = [];
		this.extends.forEach(extended => {
			answer.push(extended);

			extended.getAllExtended().forEach(descendantExtended => {
				answer.push(descendantExtended);
			});
		});
		return answer;
	}

	getAllExtendedProperties() {
		var answer: string[] = [];
		this.getAllExtended().forEach(extended => {
			extended.properties.forEach((value, key) => {
				answer.push(key);
			});
		});
		return answer;
	}

	// Gets all properties, including inherited properties
	getAllProperties() {
		var answer = new Map<string, SchemaProperty>();
		this.properties.forEach((value, key) => {
			answer.set(key, value);
		});
		this.getAllExtended().forEach(extended => {
			extended.properties.forEach((value, key) => {
				if (answer.has(key)) {
					// If the property didn't have override on it, it gets overwritten by base property
					if (!answer.get(key).override) {
						answer.set(key, value);
					}
				} else {
					answer.set(key, value);
				}
			});
		});
		return answer;
	}

	resolve(types: Map<string, SchemaType>) {

		// Resolve extends
		if (this.original.extends) {
			this.original.extends.split(",").forEach(extended => {
				extended = extended.trim();

				var foundType = types.get(extended) as SchemaClass;
				if (foundType == undefined) {
					throw new Error(`Class ${this.type} extends ${extended}, but ${extended} couldn't be found.`);
				}

				this.extends.push(foundType);
			})
		}

		// Resolve properties
		this.properties.forEach(prop => {
			prop.resolve(types);
		});

		if (this.original.shorthand) {
			var shorthandProp = this.properties.get(this.original.shorthand);
			if (shorthandProp === undefined) {
				throw new Error(`Shorthand property ${this.original.shorthand} wasn't found`);
			}
			this._shorthand = shorthandProp;
		}
	}

	resolveImplementations(types: Map<string, SchemaType>) {
		// This must be called AFTER resolve has been called, as it depends on extends
		types.forEach(type => {
			if (type instanceof SchemaClass) {
				if (type.extends.indexOf(this) != -1) {
					this._implementations.push(type);
				}
			}
		});
	}
}