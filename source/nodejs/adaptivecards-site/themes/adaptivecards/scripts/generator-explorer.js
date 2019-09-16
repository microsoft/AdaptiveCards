// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var markedschema = require("marked-schema");
var typedschema = require("typed-schema");
var marked = require("marked");
var fs = require("hexo-fs");

hexo.extend.generator.register("generator-explorer", function (locals) {

    return new Promise(function (resolve, reject) {

		try {
			var schemaModel = typedschema.markdown.buildModel({
				schema: "../../../schemas/src",
				toc: "./schema-explorer-toc.yml",
				rootDefinition: "AdaptiveCard",
				examplesPath: "../../../samples/v1.*"
			});
			
			var pages = [];

			schemaModel.forEach(function (root) {
				root.children.forEach(function (child) {
					child.htmlPath = "explorer/" + child.name + ".html";
					var page = {
						path: child.htmlPath,
						layout: "explorer",
						data: {
							title: "Schema Explorer",
							schema: schemaModel,
							element: child,
							childPath: child.htmlPath,
							propertiesSummary: typedschema.markdown.createPropertiesSummary(child.type, null, true, true, child.version)
						}
					}

					pages.push(page);

					// Set the default root as the index
					if (child.name === "AdaptiveCard") {
						pages.push({
							path: "explorer/index.html",
							layout: "explorer",
							data: {
								title: "Schema Explorer",
								schema: schemaModel,
								element: child,
								childPath: child.htmlPath,
								propertiesSummary: typedschema.markdown.createPropertiesSummary(child.type, null, false, true)
							}
						});
					}
				});
			});

			resolve(pages);
		} catch (err) {
			reject(err);
		}
    });
});
