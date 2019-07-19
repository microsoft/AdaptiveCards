// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var fs = require("fs");
var md5 = require("md5");

hexo.extend.helper.register('js', function (script) {

	// First find the correct path
	// This resolves to the original path that generator-adaptiveassets.js pulls from
	var scriptFilePath;
	if (script.startsWith("node_modules/")) {
		scriptFilePath = script;
	} else if (script.startsWith("js/")) {
		scriptFilePath = "themes/adaptivecards/source/" + script;
	} else if (script === "visualizer/monaco-loader.js") {
		scriptFilePath = "node_modules/adaptivecards-visualizer/src/monaco-loader.js";
	} else if (script === "visualizer/adaptivecards-visualizer.min.js") {
		scriptFilePath = "node_modules/adaptivecards-visualizer/dist/adaptivecards-visualizer.min.js";
	} else {
		throw new Error("Unknown script path");
	}

	// We need to version the scripts so that when the script changes, browsers update
	var scriptContents = fs.readFileSync(scriptFilePath, "utf8");
	var version = md5(scriptContents);

	return `<script src="/${script}?v=${version}"></script>`;
});
