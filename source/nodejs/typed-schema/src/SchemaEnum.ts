import {SchemaType} from "./SchemaType";

export class SchemaEnum extends SchemaType {

	private _values: string[] = [];

	constructor(sourceObj: any) {
		super(sourceObj);

		this._values = sourceObj.values;
	}

	get values() {
		return this._values;
	}

	resolve(types: Map<string, SchemaType>) {
		// Nothing
	}

}