// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var fs = require("fs");
var md5 = require("md5");

hexo.extend.helper.register('css', function (css) {

	// First find the correct path
	// This resolves to the original path that generator-adaptiveassets.js pulls from
	var cssFilePath;
	if (css.startsWith("css/")) {
		cssFilePath = "themes/adaptivecards/source/" + css;
	} else if (css.startsWith("visualizer/css/")) {
		cssFilePath = "node_modules/adaptivecards-" + css;
	} else {
		throw new Error("Unknown css path: " + css);
	}

	// We need to version the csss so that when the css changes, browsers update
	var cssContents = fs.readFileSync(cssFilePath, "utf8");
	var version = md5(cssContents);

	return `<link rel="stylesheet" href="/${css}?v=${version}">`;
});
