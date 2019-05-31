var fs = require("fs");

export function transformFolder(pathToTypeFiles: string, primaryTypeName: string|string[], defaultPrimaryTypeName: string|null = null, typePropertyName: string = "type") : any {
	var files = fs.readdirSync(pathToTypeFiles);
	var types: any[] = [];
	files.forEach((filePath) => {
		var fileTxt = fs.readFileSync(pathToTypeFiles + "/" + filePath, "utf8");
		var type = JSON.parse(fileTxt);
		types.push(type);
		types[type.type] = type;
	});

	return transformTypes(types, primaryTypeName, defaultPrimaryTypeName, typePropertyName);
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

			// If it's not the default primary type name, make type required
			if (primaryType.type !== this._defaultPrimaryTypeName) {
				definition.required = [ this._typePropertyName ];
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
		var transformed: any = { ...type };
		transformed.type = "object";
		transformed.additionalProperties = false;

		delete transformed.isAbstract;

		if (!transformed.properties) {
			transformed.properties = [];
		}
	
		if (transformed.properties) {
			for (var key in transformed.properties) {

				var propVal = transformed.properties[key];

				propVal = this.transformPropertyValue(propVal);

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

		if (type.extends) {
			transformed.allOf = [
				{
					$ref: "#/definitions/Extendable." + type.extends
				}
			];
			delete transformed.extends;

			// Keep track of implementations
			if (!this._implementationsOf[type.extends]) {
				this._implementationsOf[type.extends] = [];
				
				// If extending type isn't abstract, add that as an implementation
				if (!this._typeDictionary[type.extends].isAbstract) {
					this._implementationsOf[type.extends].push(type.extends);
				}
			}
			this._implementationsOf[type.extends].push(type.type);
		}
	
		return transformed;
	}

	private transformPropertyValue(propertyValue: any) {
		var cleanPropertyValue = { ... propertyValue };
		delete cleanPropertyValue.type;

		var typeNames = propertyValue.type.split("|");
		var values = [];

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
			if (this._typeDictionary[key].extends === typeName) {
				return true;
			}
		}
		return false;
	}

	private defineType(type: any) {
		var typeName: string = type.type;
		var transformedType = this.transformType(type);

		// If there's multiple implementations of this type
		if (this.hasMultipleImplementations(typeName)) {
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