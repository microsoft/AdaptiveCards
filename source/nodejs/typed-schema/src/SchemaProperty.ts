// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { SchemaType } from "./SchemaType";
import { SchemaPropertyType } from "./SchemaPropertyType";

export class SchemaProperty {
	private _original: any;
	private _name: string;
	private _types: SchemaPropertyType[] = [];
	private _description?: string;
	private _required: boolean = false;
	private _shorthands: SchemaProperty[] = [];
	private _default: any;
	private _examples: any[] = [];
	private _override: boolean;

	constructor(name: string, sourceObj: any) {
		this._original = sourceObj;
		this._name = name;

		if (sourceObj.description) {
			this._description = sourceObj.description;
		}

		if (sourceObj.required) {
			this._required = true;
		}

		if (sourceObj.shorthands) {
			sourceObj.shorthands.forEach(shorthand => {
				this._shorthands.push(new SchemaProperty(name, shorthand));
			});
		}

		if (sourceObj.default) {
			this._default = sourceObj.default;
		}

		if (sourceObj.examples) {
			this._examples = sourceObj.examples;
		}

		if (sourceObj.override) {
			this._override = true;
		}
	}

	get name() {
		return this._name;
	}

	get original() {
		return this._original;
	}

	get types() {
		return this._types;
	}

	get description() {
		return this._description;
	}

	get required() {
		return this._required;
	}

	get shorthands() {
		return this._shorthands;
	}

	get default() {
		return this._default;
	}

	get examples() {
		return this._examples;
	}

	get override() {
		return this._override;
	}

	resolve(types: Map<string, SchemaType>) {

		// Resolve type
		if (!this.original.type) {
			throw new Error("type property on property wasn't provided.");
		}
		this.original.type.split("|").forEach(type => {
			this._types.push(new SchemaPropertyType(type, types));
		});

		// Resolve shorthands
		this._shorthands.forEach(shorthand => {
			shorthand.resolve(types);
		});

	}

	getAllTypes() {
		var answer = [];
		this.types.forEach(type => {
			answer.push(type);
		});
		this.shorthands.forEach(shorthand => {
			shorthand.types.forEach(type => {
				answer.push(type);
			});
		});
		return answer;
	}
}