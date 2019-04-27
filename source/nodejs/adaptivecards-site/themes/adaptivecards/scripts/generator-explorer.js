// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var markedschema = require("marked-schema");
var marked = require("marked");
var fs = require("hexo-fs");

hexo.extend.generator.register("generator-explorer", function (locals) {

    return new Promise(function (resolve, reject) {

        markedschema.buildModel({
            schema: "../../../schemas/adaptive-card.json",
            toc: "./schema-explorer-toc.yml",
            rootDefinition: "AdaptiveCard",
            examplesPath: "../../../samples/v1.*"
        }).then(function (schemaModel) {
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
                            propertiesSummary: markedschema.generateMarkdown.createPropertiesSummary(child.properties, null, true, true, child.version)
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
                              propertiesSummary: markedschema.generateMarkdown.createPropertiesSummary(child.properties, null, false, true)
                            }
                        });
                    }
                });
            });

            resolve(pages);
        }).catch(function (err) {
            reject(err);
        });
    });
});
