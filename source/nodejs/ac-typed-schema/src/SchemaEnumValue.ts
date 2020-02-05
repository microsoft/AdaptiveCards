// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
export class SchemaEnumValue {
	private _original: any;
	private _value: string;
	private _description?: string;

	constructor(sourceObj: any) {
		this._original = sourceObj;

		if (typeof sourceObj === "string") {
			this._value = sourceObj.toString();
		} else {
			if (!sourceObj.value) {
				throw new Error("Value on enum wasn't specified");
			}
			this._value = sourceObj.value;
			this._description = sourceObj.description;
		}
	}

	get value() {
		return this._value;
	}

	get description() {
		return this._description;
	}

	get original() {
		return this._original;
	}
}