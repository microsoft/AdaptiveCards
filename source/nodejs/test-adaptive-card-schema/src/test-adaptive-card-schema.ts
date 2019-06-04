var fs = require("fs");
import * as Ajv from "ajv";

var allCards = getAllFiles("../../../samples");
var schemaTxt = fs.readFileSync("../../../schemas/adaptive-card-new.json", "utf8");

var ajv = new Ajv();
ajv.addMetaSchema(require('ajv/lib/refs/json-schema-draft-06.json'));
var validate = ajv.compile(JSON.parse(schemaTxt));

var total = 0;
var passed = 0;

allCards.forEach(path => {
	try {
		total++;
		var cardTxt = fs.readFileSync(path);
		var isValid = validate(JSON.parse(cardTxt));
		if (!isValid) {
			console.warn(`${path}: INVALID`);
		} else {
			console.log(`${path}: Success`);
			passed++;
		}
	} catch (err) {
		console.warn(`${path}: ${err}`);
	}
});

console.log(`${passed} of ${total} passed.`);

function getAllFiles(dir: string) {
	// https://stackoverflow.com/questions/5827612/node-js-fs-readdir-recursive-directory-search
	var results = [];
	var list = fs.readdirSync(dir);
	list.forEach(function(file) {
		var filePath = dir + '/' + file;
		var stat = fs.statSync(filePath);
		if (stat && stat.isDirectory()) { 

			// If HostConfig folder, ignore
			if (file == "HostConfig") {
				return;
			}
			
			/* Recurse into a subdirectory */
			results = results.concat(getAllFiles(filePath));
		} else { 

			// If doesn't end in .json, ignore
			if (!file.endsWith(".json")) {
				return;
			}

			/* Is a file */
			results.push(filePath);
		}
	});
	return results;
}