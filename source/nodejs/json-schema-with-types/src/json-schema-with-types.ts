var fs = require("fs");

export function transformFolder(pathToTypeFiles: string, primaryTypeName: string) : any {
	var files = fs.readdirSync(pathToTypeFiles);
	var types: any[] = [];
	files.forEach((filePath) => {
		var fileTxt = fs.readFileSync(pathToTypeFiles + "/" + filePath, "utf8");
		var type = JSON.parse(fileTxt);
		types.push(type);
		types[type.type] = type;
	});

	return transformTypes(types, primaryTypeName);
}

export function transformTypes(types: any[], primaryTypeName: string) : any {
	return new Transformer(types, primaryTypeName).transform();
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
	private _primaryType: any;
	private _definitions: any = {};
	private _implementationsOf: any = {};

	constructor (types: any[], primaryTypeName: string) {
		this._typeDictionary = {};

		types.forEach(type => {
			this._typeDictionary[type.type] = type;
		});

		this._primaryType = this._typeDictionary[primaryTypeName];
	}

	transform() {

		// First create all definitions
		for (var key in this._typeDictionary) {
			if (key !== this._primaryType.type) {
				this.defineTypeIfNeeded(key);
			}
		}
	
		var answer = this.transformType(this._primaryType);
	
		answer = {
			"$schema": "http://json-schema.org/draft-06/schema#",
			"id": "http://adaptivecards.io/schemas/adaptive-card.json",
			...answer
		};

		if (!isObjectEmpty(this._definitions)) {
			answer.definitions = { ...this._definitions };
		}

		if (!isObjectEmpty(this._implementationsOf)) {
			for (var key in this._implementationsOf) {

				var anyOfValue = [];

				this._implementationsOf[key].forEach(implementationTypeName => {
					anyOfValue.push({
						"properties": {
							"type": {
								"enum": [ implementationTypeName ]
							}
						},
						"required": [ "type" ],
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
	
		return answer;
	}

	private transformType(type: any) {
		var transformed: any = { ...type };
		transformed.type = "object";
		transformed.additionalProperties = false;

		delete transformed.isAbstract;
	
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

		if (type.extends) {
			this.defineTypeIfNeeded(type.extends);
			transformed.allOf = [
				{
					$ref: "#/definitions/" + type.extends
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
					transformedValue.type = typeName;
					break;
		
				default:
					// Must be an object reference
					this.defineTypeIfNeeded(typeName);

					transformedValue.$ref = "#/definitions/" + ((typeName in this._implementationsOf) ? "ImplementationsOf." : "") + typeName;
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
			}
			values.push(transformedValue);
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

	private defineTypeIfNeeded(typeName: string) {
		if (!(typeName in this._definitions)) {
			var transformedType = this.transformType(this._typeDictionary[typeName]);
			this._definitions[typeName] = transformedType;
		}
	}
}