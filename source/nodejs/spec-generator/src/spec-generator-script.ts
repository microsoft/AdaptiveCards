// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as specgenerator from "./spec-generator";

console.log("Updating specs...");
specgenerator.generateAsync().then(function () {
	console.log("Updated specs!");
	process.exit();
}).catch(function (err) {
	console.log("Failed to update specs. Error: " + err);
	process.exit();
});