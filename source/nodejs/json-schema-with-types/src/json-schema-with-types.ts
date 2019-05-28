var fs = require("fs");

export function transformFolder(pathToTypeFiles: string, primaryTypeName: string) : any {
	var files = fs.readdirSync(pathToTypeFiles);
	var types: any[] = [];
	files.forEach((filePath) => {
		var fileTxt = fs.readFileSync(filePath, "utf8");
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

class Transformer {
	private _typeDictionary: any;
	private _primaryType: any;

	constructor (types: any[], primaryTypeName: string) {
		this._typeDictionary = {};

		types.forEach(type => {
			this._typeDictionary[type.type] = type;
		});

		this._primaryType = this._typeDictionary[primaryTypeName];
	}

	transform() {
		var answer: any = {
			"$schema": "http://json-schema.org/draft-06/schema#",
			"id": "http://adaptivecards.io/schemas/adaptive-card.json"
		};
	
		var answer = this.transformType(this._primaryType);
	
		answer = {
			"$schema": "http://json-schema.org/draft-06/schema#",
			"id": "http://adaptivecards.io/schemas/adaptive-card.json",
			...answer
		};
	
		return answer;
	}

	private transformType(type: any) {
		var transformed: any = { ...type };
		transformed.type = "object";
	
		if (transformed.properties) {
			for (var key in transformed.properties) {
	
				var propVal = transformed.properties[key];
	
				this.transformPropertyValue(propVal);
	
				if (propVal.required) {
					delete propVal.required;
					if (!transformed.required) {
						transformed.required = [];
					}
					transformed.required.push(key);
				}
			}
		}
	
		return transformed;
	}

	private transformPropertyValue(propertyValue: any) {
		switch (propertyValue.type) {
			case "uri":
				propertyValue.type = "string";
				propertyValue.format = "uri";
				break;
	
			case "string":
			case "number":
				break;
	
			default:
				// Must be an object reference
	
				break;
		}
	}
}