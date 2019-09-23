// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { SchemaType } from "./SchemaType";
import { SchemaLiteral } from "./SchemaLiteral";

export class SchemaPropertyType {
	private _type: SchemaType;
	private _isNullable: boolean;
	private _isArray: boolean;
	private _isDictionary: boolean;

	constructor(typeName: string, types: Map<string, SchemaType>) {

		this._isNullable = typeName.endsWith("?");
		if (this._isNullable) {
			typeName = typeName.substr(0, typeName.length - 1);
		}
		this._isArray = typeName.endsWith("[]");
		if (this._isArray) {
			typeName = typeName.substr(0, typeName.length - 2);
		}
		this._isDictionary = typeName.startsWith("Dictionary<") && typeName.endsWith(">");
		if (this._isDictionary) {
			typeName = typeName.substr("Dictionary<".length);
			typeName = typeName.substr(0, typeName.length - 1);
		}

		switch (typeName) {
			case "uri":
				this._type = SchemaLiteral.uri;
				break;

			case "uri-reference":
				this._type = SchemaLiteral.uriReference;
				break;

			case "string":
				this._type = SchemaLiteral.string;
				break;

			case "number":
				this._type = SchemaLiteral.number;
				break;

			case "boolean":
				this._type = SchemaLiteral.boolean;
				break;

			case "object":
				this._type = SchemaLiteral.object;
				break;

			case "any":
				this._type = SchemaLiteral.any;
				break;

			default:
				// Must be an object reference
				var foundType = types.get(typeName);
				if (foundType == undefined) {
					throw new Error(`Property references ${typeName} type, but ${typeName} couldn't be found.`);
				}
				this._type = foundType;
				break;
		}

	}

	get type() {
		return this._type;
	}

	get isNullable() {
		return this._isNullable;
	}

	get isArray() {
		return this._isArray;
	}

	get isDictionary() {
		return this._isDictionary;
	}
}