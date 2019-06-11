// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
var fs = require("fs");
import * as Ajv from "ajv";

var allCards = getAllFiles("../../../../samples");
var schemaTxt = fs.readFileSync("../../../../schemas/adaptive-card.json", "utf8");

var ajv = new Ajv();
var validate = ajv.compile(JSON.parse(schemaTxt));

var shouldFail: string[] = [
	"v1.2/Scenarios/SimpleFallback.json", // Uses custom types
	"v1.2/Elements/ActionFallback.json", // Uses custom types
	"v1.2/Elements/Action.Submit.Style.json", // Uses custom "other" style
	"v1.2/Elements/Action.ShowCard.Style.json", // Uses custom "other" style
	"v1.2/Elements/Action.OpenUrl.Style.json", // Uses custom "other" style
	"Tests/Input.Text.InlineAction.ShowCard.json", // Purposefully incorrect for test purposes
	"Tests/TypeIsRequired.json", // Purposefully omits type
	"Tests/FallbackParsing.json", // Uses custom types
	"Tests/EmptyFallbackCard.json", // Uses custom types
	"Tests/DeepFallback.json", // Uses custom types
	"Tests/CustomParsingTestUsingProgressBar.json", // Uses custom types
	"Tests/AdditionalProperty.json", // Uses custom property
	"Tests/AdaptiveCard.UnknownElements.json", // Uses custom type
	"Tests/Action.CustomParsing.json", // Uses custom type
];

var total = 0;
var passed = 0;

allCards.forEach(path => {
	var shouldBeValid = true;
	shouldFail.forEach(skip => {
		if (path.endsWith(skip)) {
			shouldBeValid = false;
		}
	});
	try {
		total++;
		var cardTxt = fs.readFileSync(path);
		var isValid = validate(JSON.parse(cardTxt));
		if (shouldBeValid) {
			if (!isValid) {
				console.warn(`${path}: INVALID`);
			} else {
				console.log(`${path}: Success`);
				passed++;
			}
		} else {
			if (!isValid) {
				console.log(`${path}: Success (correctly invalid)`);
				passed++;
			} else {
				console.warn(`${path}: FAILED (should be invalid but was valid)`);
			}
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
	list.forEach(function (file) {
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