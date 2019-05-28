var fs = require("fs");

function transform(pathToTypeFiles: string, primaryTypeName: string) : string {
	var files = fs.readdirSync(pathToTypeFiles);
	var types: any = {};
	files.forEach((filePath) => {
		var fileTxt = fs.readFileSync(filePath, "utf8");
		var type = JSON.parse(fileTxt);
		types[type.type] = type;
	});

	var primaryType = types[primaryTypeName];
	
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