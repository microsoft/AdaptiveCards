// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";
var typedschema = require("ac-typed-schema");
var glob = require("glob");
var path = require("path");

hexo.extend.generator.register("generator-explorer", function (locals) {

    return new Promise(function (resolve, reject) {

		try {
            var languages = glob.sync("./languages/*");
            languages.forEach(function(languageDir) {
                var language = languageDir.substring(languageDir.lastIndexOf("/")+1);
			    var schemaModel = typedschema.markdown.buildModel({
				    schema: "../../../schemas/src",
				    toc: path.join(languageDir, "schema-explorer-toc.yml"),
				    rootDefinition: "AdaptiveCard",
				    examplesPath: "../../../samples"
			    });

			    var pages = [];

			    schemaModel.forEach(function (root) {
				    root.children.forEach(function (child) {
					    child.htmlPath = language + "/explorer/" + child.name + ".html";
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
							    path: language + "/explorer/" + "index.html",
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
            });

		} catch (err) {
			reject(err);
		}
    });
});
