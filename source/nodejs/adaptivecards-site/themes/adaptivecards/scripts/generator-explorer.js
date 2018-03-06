"ustr strict";

var markedschema = require("marked-schema");
var marked = require("marked");
var fs = require("hexo-fs");

// TODO: Get UHF
// https://uhf.microsoft.com/en-US/shell/xml/UHFPortal?headerId=MSDocsHeader-AdaptiveCards&footerid=UHFPortalFooter

hexo.extend.generator.register("generator-explorer", function (locals) {

    return new Promise(function (resolve, reject) {

        markedschema.buildModel({
            schema: "../../../schemas/adaptive-card.json",
            toc: "./node_modules/marked-schema/test/toc.yml",
            rootDefinition: "AdaptiveCard",
            examplesPath: "../../../samples/v1.0"
        }).then(function (schemaModel) {
            var pages = [];

            schemaModel.forEach(function (root) {
                root.children.forEach(function (child) {
                    var page = {
                        path: "explorer/" + child.name + ".html",
                        layout: "explorer",
                        data: {
                            title: "Schema Explorer",
                            schema: schemaModel,
                            element: child,
                            propertiesSummary: markedschema.generateMarkdown.createPropertiesSummary(child.properties)
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
                                propertiesSummary: markedschema.generateMarkdown.createPropertiesSummary(child.properties)
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