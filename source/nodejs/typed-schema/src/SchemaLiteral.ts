import {SchemaType} from "./SchemaType";

export class SchemaLiteral extends SchemaType {

	private _schemaType?: string;
	private _schemaFormat?: string;

	constructor(schemaType?: string, schemaFormat?: string) {
		super(null);
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

	private static _string = new SchemaLiteral("string");
	private static _number = new SchemaLiteral("number");
	private static _object = new SchemaLiteral("object");
	private static _boolean = new SchemaLiteral("boolean");
	private static _uri = new SchemaLiteral("string", "uri");
	private static _uriReference = new SchemaLiteral("string", "uri-reference");
	private static _any = new SchemaLiteral();

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