import {SchemaType} from "./SchemaType";
import {SchemaClass} from "./SchemaClass";
import {SchemaEnum} from "./SchemaEnum";
import {SchemaProperty} from "./SchemaProperty";
import {SchemaPropertyType} from "./SchemaPropertyType";
import {SchemaLiteral} from "./SchemaLiteral";

var fs = require("fs");
var path = require("path");

export function transformFolder(pathToTypeFiles: string, primaryTypeName: string|string[], defaultPrimaryTypeName: string|null = null, typePropertyName: string = "type") : any {
	var files = getAllFiles(pathToTypeFiles);
	var types: any[] = [];
	files.forEach((filePath) => {
		if (filePath.endsWith(".json")) {
			var fileTxt = fs.readFileSync(filePath, "utf8");
			var type = JSON.parse(fileTxt);

			// Infer type name from file name if not specified
			if (!type.type) {
				var stat = fs.statSync(filePath);
				if (stat) {
					type.type = path.basename(filePath, ".json");
				}
			}

			types.push(type);
			types[type.type] = type;
		}
	});

	return transformTypes(types, primaryTypeName, defaultPrimaryTypeName, typePropertyName);
}

function getAllFiles(dir: string) {
	// https://stackoverflow.com/questions/5827612/node-js-fs-readdir-recursive-directory-search
	var results = [];
	var list = fs.readdirSync(dir);
	list.forEach(function(file) {
		file = dir + '/' + file;
		var stat = fs.statSync(file);
		if (stat && stat.isDirectory()) { 
			/* Recurse into a subdirectory */
			results = results.concat(getAllFiles(file));
		} else { 
			/* Is a file */
			results.push(file);
		}
	});
	return results;
}

export function transformTypes(types: any[], primaryTypeName: string|string[], defaultPrimaryTypeName: string|null = null, typePropertyName: string = "type") : any {
	return new Transformer(types, primaryTypeName, defaultPrimaryTypeName, typePropertyName).transform();
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
	private _typeDictionary: Map<string, SchemaType> = new Map<string, SchemaType>();
	private _primaryTypes: SchemaClass[] = [];
	private _definitions: any = {};
	private _implementationsOf: any = {};
	private _extendables: any = {};
	private _typePropertyName: string;
	private _defaultPrimaryTypeName: string|null;

	constructor (types: any[], primaryTypeName: string|string[], defaultPrimaryTypeName: string|null, typePropertyName: string) {
		this._typePropertyName = typePropertyName;
		this._defaultPrimaryTypeName = defaultPrimaryTypeName;

		types.forEach(type => {
			this._typeDictionary.set(type.type, this.parse(type));
		});

		// Resolve types
		this._typeDictionary.forEach(type => {
			type.resolve(this._typeDictionary);
		});

		this._typeDictionary.forEach(type => {
			if (type instanceof SchemaClass) {
				type.resolveImplementations(this._typeDictionary);
			}
		});

		if (!Array.isArray(primaryTypeName)) {
			primaryTypeName = [ primaryTypeName ];
		}

		primaryTypeName.forEach(value => {
			this._primaryTypes.push(this.getType(value) as SchemaClass);
		});
	}

	parse(sourceObj: any) : SchemaType {
		if (sourceObj.classType === "Enum") {
			return new SchemaEnum(sourceObj);
		} else if (sourceObj.classType === "Class" || sourceObj.classType === undefined) {
			return new SchemaClass(sourceObj);
		} else {
			throw new Error("Unknown classType " + sourceObj.classType);
		}
	}

	transform() {

		// First create all definitions for all types
		this._typeDictionary.forEach(type => {
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
		var answer = this._typeDictionary.get(typeName);
		if (answer === undefined) {
			var knownTypes = "";
			this._typeDictionary.forEach((value, key) => {
				if (knownTypes.length > 0) {
					knownTypes += ", ";
				}
				knownTypes += key;
			});
			throw new Error("Type " + typeName + " could not be found. Known types: " + knownTypes);
		}
		return answer;
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
				transformed.enum = enumType.values;
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

			if (!transformed.properties) {
				transformed.properties = [];
			}
		
			if (type.properties.size > 0) {
				type.properties.forEach((propVal, key) => {

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

				// Have to add placeholders for all the properties
				type.getAllExtendedProperties().forEach(extendedPropKey => {
					transformed.properties[extendedPropKey] = {};
				});

				transformed.allOf = [];
				type.extends.forEach(extended => {
					if (extended.properties.size > 0) {
						transformed.allOf.push({
							$ref: "#/definitions/Extendable." + extended.type
						});
					}
				});

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
		
			return transformed;
		} catch (err) {
			throw "Failed transforming type " + type.type + "\n\n" + err.stack;
		}
	}

	private transformPropertyValue(propertyValue: SchemaProperty) {
		var cleanPropertyValue = { ... propertyValue.original };
		delete cleanPropertyValue.type;
		delete cleanPropertyValue.shorthands;

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
		var type = this._typeDictionary.get(typeName);
		if (type instanceof SchemaClass && type.implementations.length > 0) {
			return true;
		}
		return false;
	}

	private defineType(type: SchemaType) {
		var typeName: string = type.type;
		var transformedType = this.transformType(type);

		// If there's multiple implementations of this type
		if (this.hasMultipleImplementations(typeName) && type instanceof SchemaClass && type.properties.size > 0) {
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