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
	
	var typeDictionary: any = {};

	types.forEach(type => {
		typeDictionary[type.type] = type;
	});

	var primaryType = typeDictionary[primaryTypeName];

	var answer: any = {
		"$schema": "http://json-schema.org/draft-06/schema#",
		"id": "http://adaptivecards.io/schemas/adaptive-card.json"
	};

	var answer = transformType(primaryType, typeDictionary);

	answer = {
		"$schema": "http://json-schema.org/draft-06/schema#",
		"id": "http://adaptivecards.io/schemas/adaptive-card.json",
		...answer
	};

	return answer;
}

function transformType(type: any, typeDictionary: any) {
	var transformed: any = { ...type };
	transformed.type = "object";
	return transformed;
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