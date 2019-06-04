import {SchemaType} from "./SchemaType";
import {SchemaClass} from "./SchemaClass";
import {SchemaEnum} from "./SchemaEnum";
import {SchemaProperty} from "./SchemaProperty";
import {SchemaPropertyType} from "./SchemaPropertyType";
import {SchemaLiteral} from "./SchemaLiteral";
import { Schema } from "./Schema";

var fs = require("fs");
var path = require("path");


export * from "./SchemaType";
export * from "./SchemaClass";
export * from "./SchemaEnum";
export * from "./SchemaProperty";
export * from "./SchemaPropertyType";
export * from "./SchemaLiteral";
export * from "./Schema";

export function transformFolder(pathToTypeFiles: string, primaryTypeName: string|string[], defaultPrimaryTypeName: string|null = null, typePropertyName: string = "type") : any {
	return new Transformer(Schema.fromFolder(pathToTypeFiles), primaryTypeName, defaultPrimaryTypeName, typePropertyName).transform();
}

export function transformTypes(types: any[], primaryTypeName: string|string[], defaultPrimaryTypeName: string|null = null, typePropertyName: string = "type") : any {
	return new Transformer(new Schema(types), primaryTypeName, defaultPrimaryTypeName, typePropertyName).transform();
}

function readFileAsync(fileName: string, encoding: string) : Promise<string> {
	return new Promise(function(resolve, reject) {
		fs.readFile(fileName, encoding, (err, data) => {
			if (err) {
				reject(err);
			} else {
				resolve(data);
			}
		});
	});
}

function isObjectEmpty(obj: any) {
	if (!obj) {
		return true;
	}
	for (var key in obj) {
		return false;
	}
	return true;
}

class Transformer {
	private _schema: Schema;
	private _primaryTypes: SchemaClass[] = [];
	private _definitions: any = {};
	private _implementationsOf: any = {};
	private _extendables: any = {};
	private _typePropertyName: string;
	private _defaultPrimaryTypeName: string|null;

	constructor (schema: Schema, primaryTypeName: string|string[], defaultPrimaryTypeName: string|null, typePropertyName: string) {
		this._schema = schema;
		this._typePropertyName = typePropertyName;
		this._defaultPrimaryTypeName = defaultPrimaryTypeName;

		if (!Array.isArray(primaryTypeName)) {
			primaryTypeName = [ primaryTypeName ];
		}

		primaryTypeName.forEach(value => {
			this._primaryTypes.push(this.getType(value) as SchemaClass);
		});
	}

	transform() {

		// First create all definitions for all types
		this._schema.typeDictionary.forEach(type => {
			this.defineType(type);
		});
	
		var answer:any = {
			"$schema": "http://json-schema.org/draft-06/schema#",
			"id": "http://adaptivecards.io/schemas/adaptive-card.json",
			"definitions": {}
		};

		var anyOf = [];

		this._primaryTypes.forEach(primaryType => {
			var definition:any = {
				"allOf": [
					{
						"$ref": "#/definitions/" + primaryType.type
					}
				]
			};

			// If there's multiple primary types, we have to enforce type at top level to differentiate
			if (this._primaryTypes.length > 1) {
				// If it's not the default primary type name, make type required
				if (primaryType.type !== this._defaultPrimaryTypeName) {
					definition.required = [ this._typePropertyName ];
				}
			}

			anyOf.push(definition);
		});

		answer.anyOf = anyOf;

		if (!isObjectEmpty(this._definitions)) {
			answer.definitions = { ...this._definitions };
		}

		if (!isObjectEmpty(this._implementationsOf)) {
			for (var key in this._implementationsOf) {

				var anyOfValue = [];

				this._implementationsOf[key].forEach(implementationTypeName => {
					anyOfValue.push({
						"required": [ this._typePropertyName ],
						"allOf": [
							{
								"$ref": "#/definitions/" + implementationTypeName
							}
						]
					});
				});

				answer.definitions["ImplementationsOf." + key] = {
					"anyOf": anyOfValue
				};
			}
		}

		if (!isObjectEmpty(this._extendables)) {
			for (var key in this._extendables) {
				answer.definitions["Extendable." + key] = this._extendables[key];
			}
		}
	
		return answer;
	}

	private getType(typeName: string) : SchemaType {
		return this._schema.getType(typeName);
	}

	private transformType(type: SchemaType) {
		try {
			if (type instanceof SchemaEnum) {
				var enumType = type as SchemaEnum;
				var transformed: any = { ...type.original };
				delete transformed.type;
				delete transformed.values;
				delete transformed.classType;
				delete transformed.$schema;
				delete transformed.extends;
				transformed.enum = [];
				enumType.values.forEach(val => {
					transformed.enum.push(val.value);
				});
				return transformed;
			} else if (!(type instanceof SchemaClass)) {
				throw new Error("Unknown class type " + type);
			}

			var transformed: any = { ...type.original };
			transformed.type = "object";
			transformed.additionalProperties = false;

			delete transformed.isAbstract;
			delete transformed.classType;
			delete transformed.$schema;
			delete transformed.extends;
			delete transformed.shorthand;

			transformed.properties = {};
			var overridesProperties = false;
			var properties = new Map<string, SchemaProperty>();

			if (type.extends.length > 0) {

				type.properties.forEach(prop => {
					if (prop.override) {
						// If property exists in base classes
						if (type.getAllExtendedProperties().indexOf(prop.name) !== -1) {
							// Note that JSON schema doesn't support the concept of overriding properties, so instead
							// we need to copy all the properties and NOT inherit.
							overridesProperties = true;
						} else {
							console.warn(`${type.type}.${prop.name} has override set to true, but it doesn't override any base class properties.`);
						}
					} else {
						// If property exists in base classes
						if (type.getAllExtendedProperties().indexOf(prop.name) !== -1) {
							console.warn(`Ignoring ${type.type}.${prop.name} as there's already this property specified in a base class. If you want to keep this property, add "override": "true".`);
						}
					}
				});
			}

			if (overridesProperties) {
				type.getAllProperties().forEach((propVal, key) => {
					properties.set(key, propVal);
				});
			} else {
				properties = type.properties;
			}
		
			if (properties.size > 0) {
				properties.forEach((propVal, key) => {

					var transformedPropVal: any;
					try {
						transformedPropVal = this.transformPropertyValue(propVal);
					} catch (err) {
						throw new Error("Failed transforming property " + key + "\n\n" + err.stack);
					}

					if (transformedPropVal.required) {
						delete transformedPropVal.required;
						if (!transformed.required) {
							transformed.required = [];
						}
						transformed.required.push(key);
					}

					transformed.properties[key] = transformedPropVal;
				});
			}

			if (!type.isAbstract) {
				// If it's not abstract, we add the type property
				// Note that we don't require it though, it's optional
				var newProperties:any = {};
				newProperties[this._typePropertyName] = {
					"enum": [ type.type ],
					"description": "Must be `" + type.type + "`"
				};
				transformed.properties = {
					...newProperties,
					...transformed.properties
				};
			}

			if (type.extends.length > 0) {

				if (!overridesProperties) {
					// Have to add placeholders for all the properties
					type.getAllExtendedProperties().forEach(extendedPropKey => {

						// If there's an existing property defined, skip
						var existingProp = type.properties.get(extendedPropKey);
						if (existingProp !== undefined) {
							if (!existingProp.override) {
								console.warn(`Overriding extended property ${extendedPropKey} on type ${type.type}. If this was intentional, add "override": "true" to this property to prevent this warning from appearing.`);
							}
							return;
						}

						transformed.properties[extendedPropKey] = {};
					});

					transformed.allOf = [];
					type.extends.forEach(extended => {
						if (extended.getAllProperties().size > 0) {
							transformed.allOf.push({
								$ref: "#/definitions/Extendable." + extended.type
							});
						}
					});
					if (transformed.allOf.length == 0) {
						delete transformed.allOf;
					}
				}

				// Keep track of implementations
				type.getAllExtended().forEach(extended => {
					if (!this._implementationsOf[extended.type]) {
						this._implementationsOf[extended.type] = [];
						
						// If extending type isn't abstract, add that as an implementation
						if (!extended.isAbstract) {
							this._implementationsOf[extended.type].push(extended.type);
						}
					}

					if (!type.isAbstract) {
						this._implementationsOf[extended.type].push(type.type);
					}
				});

				delete transformed.extends;
			}

			if (type.shorthand) {
				transformed.anyOf = [
					{
						...transformed.properties[type.shorthand.name]
					},
					{
						type: transformed.type,
						properties: transformed.properties,
						required: transformed.required,
						additionalProperties: false
					}
				];
				delete transformed.type;
				delete transformed.properties;
				delete transformed.required;
				delete transformed.additionalProperties;
			}
		
			return transformed;
		} catch (err) {
			throw "Failed transforming type " + type.type + "\n\n" + err.stack;
		}
	}

	private transformPropertyValue(propertyValue: SchemaProperty) {
		var cleanPropertyValue = { ... propertyValue.original };
		delete cleanPropertyValue.type;
		delete cleanPropertyValue.shorthands;
		delete cleanPropertyValue.override;

		var types: SchemaPropertyType[] = [];
		var values = [];

		propertyValue.types.forEach(type => {
			types.push(type);
		});

		propertyValue.shorthands.forEach(shorthand => {
			shorthand.types.forEach(type => {
				types.push(type);
			});
		});

		types.forEach(type => {
			var transformedValue: any = {};

			if (type.type instanceof SchemaLiteral) {
				if (type.type.schemaType) {
					transformedValue.type = type.type.schemaType;
				}
				if (type.type.schemaFormat) {
					transformedValue.format = type.type.schemaFormat;
				}
			} else {
				// Must be an object reference
				transformedValue.$ref = "#/definitions/" + (this.hasMultipleImplementations(type.type.type) ? "ImplementationsOf." : "") + type.type.type;
			}

			if (type.isDictionary) {
				transformedValue = {
					"type": "object",
					"additionalProperties": {
						...transformedValue
					}
				};
			}
			if (type.isArray) {
				transformedValue = {
					"type": "array",
					"items": { ...transformedValue }
				};
				if (type.type == SchemaLiteral.any) {
					// Any types don't need type definitions
					delete transformedValue.items;
				}
			}

			propertyValue.shorthands.forEach(shorthand => {
				if (shorthand.types.indexOf(type) != -1) {
					var cleanShorthandValue = { ...shorthand.original };
					delete cleanShorthandValue.type;
					transformedValue = { ...transformedValue, ...cleanShorthandValue };
				}
			});

			values.push(transformedValue);

			if (type.isNullable) {
				values.push({
					"type": "null"
				});
			}
		});

		if (values.length == 1) {
			return {
				...values[0],
				...cleanPropertyValue
			};
		} else {
			return {
				anyOf: values,
				...cleanPropertyValue
			};
		}
	}

	private hasMultipleImplementations(typeName: string) {
		var type = this._schema.typeDictionary.get(typeName);
		if (type instanceof SchemaClass && type.implementations.length > 0) {
			return true;
		}
		return false;
	}

	private defineType(type: SchemaType) {
		var typeName: string = type.type;
		var transformedType = this.transformType(type);

		// If there's multiple implementations of this type
		if (this.hasMultipleImplementations(typeName) && type instanceof SchemaClass && type.getAllProperties().size > 0) {
			// Then we must define an extendable flavor that doesn't have the additionalProperties = false
			var extendableType = { ...transformedType };
			delete extendableType.additionalProperties;
			this._extendables[typeName] = extendableType;
		}

		// As long as it's not abstract (no reason to define those, they'll be defined as extendable if used)
		if (!(type instanceof SchemaClass && type.isAbstract)) {
			this._definitions[typeName] = transformedType;
		}
	}
}