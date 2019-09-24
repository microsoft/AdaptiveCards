// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { SchemaType } from "./SchemaType";

export class SchemaLiteral extends SchemaType {

	private _schemaType?: string;
	private _schemaFormat?: string;

	constructor(type: string, schemaType?: string, schemaFormat?: string) {
		super({
			type: type
		});
		this._schemaType = schemaType;
		this._schemaFormat = schemaFormat;
	}

	get schemaType() {
		return this._schemaType;
	}

	get schemaFormat() {
		return this._schemaFormat;
	}

	resolve(types: Map<string, SchemaType>) {
		// Nothing to do
	}

	private static _string = new SchemaLiteral("string", "string");
	private static _number = new SchemaLiteral("number", "number");
	private static _object = new SchemaLiteral("object", "object");
	private static _boolean = new SchemaLiteral("boolean", "boolean");
	private static _uri = new SchemaLiteral("uri", "string", "uri");
	private static _uriReference = new SchemaLiteral("uri-reference", "string", "uri-reference");
	private static _any = new SchemaLiteral("any");

	static get string() {
		return this._string;
	}

	static get number() {
		return this._number;
	}

	static get object() {
		return this._object;
	}

	static get boolean() {
		return this._boolean;
	}

	static get uri() {
		return this._uri;
	}

	static get uriReference() {
		return this._uriReference;
	}

	static get any() {
		return this._any;
	}
}