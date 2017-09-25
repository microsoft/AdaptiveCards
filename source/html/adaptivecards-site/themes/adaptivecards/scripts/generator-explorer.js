"ustr strict";

var markedschema = require("marked-schema");
var marked = require("marked");
var fs = require("hexo-fs");

hexo.extend.generator.register("generator-explorer", function (locals) {

    return new Promise(function (resolve, reject) {

        markedschema.buildModel({
            // TODO: move to config
            schema: "C:/Dev/Projects/AdaptiveCards/schemas/adaptive-card.json",
            toc: "./node_modules/marked-schema/test/toc.yml",
            rootDefinition: "AdaptiveCard",
            examplesPath: "C:/Dev/Projects/AdaptiveCards/samples/v1.0/"
        }).then(function (schemaModel) {
            var pages = [];
 
            schemaModel.forEach(function (root) {
                root.children.forEach(function (child) {

                    pages.push({
                        path: "explorer/" + child.name + ".html",
                        layout: "explorer",
                        data: {
                            schema: schemaModel,
                            element: child,
                            propertiesSummary: markedschema.generateMarkdown.createPropertiesSummary(child.properties)
                        }
                    });
                });
            });

            resolve(pages);
        }).catch(function (err) {
            reject(err);
        });
    });
});