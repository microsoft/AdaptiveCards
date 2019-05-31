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
	private _typeDictionary: any;
	private _primaryTypes: any[] = [];
	private _definitions: any = {};
	private _implementationsOf: any = {};
	private _extendables: any = {};
	private _typePropertyName: string;
	private _defaultPrimaryTypeName: string|null;

	constructor (types: any[], primaryTypeName: string|string[], defaultPrimaryTypeName: string|null, typePropertyName: string) {
		this._typeDictionary = {};
		this._typePropertyName = typePropertyName;
		this._defaultPrimaryTypeName = defaultPrimaryTypeName;

		types.forEach(type => {
			this._typeDictionary[type.type] = type;
		});

		// Resolve extends
		types.forEach(type => {
			if (type.extends) {
				var extendsNames = type.extends.split(",");
				type.extends = [];
				extendsNames.forEach(extendedTypeName => {
					type.extends.push(this._typeDictionary[extendedTypeName.trim()]);
				});
			} else {
				type.extends = [];
			}
		});

		if (!Array.isArray(primaryTypeName)) {
			primaryTypeName = [ primaryTypeName ];
		}

		primaryTypeName.forEach(value => {
			this._primaryTypes.push(this._typeDictionary[value]);
		});
	}

	transform() {

		// First create all definitions for all types
		for (var key in this._typeDictionary) {
			this.defineType(this._typeDictionary[key]);
		}
	
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

	private transformType(type: any) {
		try {
			if (type.classType === "Enum") {
				var transformed: any = { ...type };
				delete transformed.type;
				delete transformed.values;
				delete transformed.classType;
				delete transformed.$schema;
				delete transformed.extends;
				transformed.enum = type.values;
				return transformed;
			} else if (type.classType && type.classType !== "Class") {
				throw new Error("Unknown class type " + type.classType);
			}

			var transformed: any = { ...type };
			transformed.type = "object";
			transformed.additionalProperties = false;

			delete transformed.isAbstract;
			delete transformed.classType;
			delete transformed.$schema;
			delete transformed.extends;

			if (!transformed.properties) {
				transformed.properties = [];
			}
		
			if (transformed.properties) {
				for (var key in transformed.properties) {

					var propVal = transformed.properties[key];

					try {
						propVal = this.transformPropertyValue(propVal);
					} catch (err) {
						throw new Error("Failed transforming property " + key + "\n\n" + err.stack);
					}

					if (propVal.required) {
						delete propVal.required;
						if (!transformed.required) {
							transformed.required = [];
						}
						transformed.required.push(key);
					}

					transformed.properties[key] = propVal;
				}
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
				transformed.allOf = [];
				type.extends.forEach(extended => {
					if (!isObjectEmpty(extended.properties)) {
						transformed.allOf.push({
							$ref: "#/definitions/Extendable." + extended.type
						});

						// Have to add placeholders for all the properties
						for (var extendedPropKey in extended.properties) {
							transformed.properties[extendedPropKey] = {};
						}
					}
					
					// Keep track of implementations
					if (!this._implementationsOf[extended.type]) {
						this._implementationsOf[extended.type] = [];
						
						// If extending type isn't abstract, add that as an implementation
						if (!this._typeDictionary[extended.type].isAbstract) {
							this._implementationsOf[extended.type].push(extended.type);
						}
					}
					this._implementationsOf[extended.type].push(type.type);
				});
				delete transformed.extends;

			}
		
			return transformed;
		} catch (err) {
			throw "Failed transforming type " + type.type + "\n\n" + err.stack;
		}
	}

	private transformPropertyValue(propertyValue: any) {
		var cleanPropertyValue = { ... propertyValue };
		delete cleanPropertyValue.type;
		delete cleanPropertyValue.shorthands;

		var typeNames = propertyValue.type.split("|");
		var values = [];

		if (propertyValue.shorthands) {
			propertyValue.shorthands.forEach(shorthand => {
				typeNames.push(shorthand.type);
			});
		}

		typeNames.forEach(typeName => {
			var transformedValue: any = {};
			var isNullable = typeName.endsWith("?");
			if (isNullable) {
				typeName = typeName.substr(0, typeName.length - 1);
			}
			var isArray = typeName.endsWith("[]");
			if (isArray) {
				typeName = typeName.substr(0, typeName.length - 2);
			}
			var isDictionary = typeName.startsWith("Dictionary<") && typeName.endsWith(">");
			if (isDictionary) {
				typeName = typeName.substr("Dictionary<".length);
				typeName = typeName.substr(0, typeName.length - 1);
			}
			switch (typeName) {
				case "uri":
					transformedValue.type = "string";
					transformedValue.format = "uri";
					break;
		
				case "string":
				case "number":
				case "boolean":
				case "object":
					transformedValue.type = typeName;
					break;

				case "any":
					// Don't set a type
					break;
		
				default:
					// Must be an object reference
					// Note that we can't check _implementationsOf, since that isn't fully populated till we've
					// processed all types
					transformedValue.$ref = "#/definitions/" + (this.hasMultipleImplementations(typeName) ? "ImplementationsOf." : "") + typeName;
					break;
			}
			if (isDictionary) {
				transformedValue = {
					"type": "object",
					"additionalProperties": {
						...transformedValue
					}
				};
			}
			if (isArray) {
				transformedValue = {
					"type": "array",
					"items": { ...transformedValue }
				};
				if (typeName === "any") {
					// Any types don't need type definitions
					delete transformedValue.items;
				}
			}

			if (propertyValue.shorthands) {
				propertyValue.shorthands.forEach(shorthand => {
					if (shorthand.type === typeName) {
						var cleanShorthandValue = { ...shorthand };
						delete cleanShorthandValue.type;
						transformedValue = { ...transformedValue, ...cleanShorthandValue };
					}
				});
			}

			values.push(transformedValue);

			if (isNullable) {
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
		for (var key in this._typeDictionary) {
			var extensions = this._typeDictionary[key].extends;
			for (var i = 0; i < extensions.length; i++) {
				if (extensions[i].type === typeName) {
					return true;
				}
			}
		}
		return false;
	}

	private defineType(type: any) {
		var typeName: string = type.type;
		var transformedType = this.transformType(type);

		// If there's multiple implementations of this type
		if (this.hasMultipleImplementations(typeName) && type.properties && !isObjectEmpty(type.properties)) {
			// Then we must define an extendable flavor that doesn't have the additionalProperties = false
			var extendableType = { ...transformedType };
			delete extendableType.additionalProperties;
			this._extendables[typeName] = extendableType;
		}

		// As long as it's not abstract (no reason to define those, they'll be defined as extendable if used)
		if (!type.isAbstract) {
			this._definitions[typeName] = transformedType;
		}
	}
}