// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { SchemaEnum } from "./SchemaEnum";
import { SchemaClass } from "./SchemaClass";

export abstract class SchemaType {
	private _type: string;
	private _description?: string;
	private _original: any;

	constructor(sourceObj: any) {
		this._original = sourceObj;
		if (sourceObj) {
			this._type = sourceObj.type;
			if (sourceObj.description) {
				this._description = sourceObj.description;
			}
		}
	}

	get type() {
		return this._type;
	}

	get description() {
		return this._description;
	}

	get original() {
		return this._original;
	}

	abstract resolve(types: Map<string, SchemaType>): void;
}