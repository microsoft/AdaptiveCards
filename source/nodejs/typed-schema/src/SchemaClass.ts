import {SchemaType} from "./SchemaType";
import {SchemaProperty} from "./SchemaProperty";

export class SchemaClass extends SchemaType {
	private _properties: Map<string, SchemaProperty> = new Map<string, SchemaProperty>();
	private _isAbstract: boolean = false;
	private _extends: SchemaClass[] = [];
	private _implementations: SchemaClass[] = [];

	constructor(sourceObj: any) {
		super(sourceObj);

		if (sourceObj.properties) {
			for (var key in sourceObj.properties) {
				this._properties.set(key, new SchemaProperty(sourceObj.properties[key]));
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