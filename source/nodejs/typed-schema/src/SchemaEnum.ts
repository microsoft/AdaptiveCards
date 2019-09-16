// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { SchemaType } from "./SchemaType";
import { SchemaEnumValue } from "./SchemaEnumValue";

export class SchemaEnum extends SchemaType {

	private _values: SchemaEnumValue[] = [];

	constructor(sourceObj: any) {
		super(sourceObj);

		if (sourceObj.values instanceof Array) {
			sourceObj.values.forEach(val => {
				this._values.push(new SchemaEnumValue(val));
			});
		} else {
			throw new Error("Enum didn't have any values");
		}
	}

	get values() {
		return this._values;
	}

	resolve(types: Map<string, SchemaType>) {
		// Nothing
	}

}