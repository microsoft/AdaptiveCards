// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var fs = require("hexo-fs");
var glob = require("glob");
var path = require("path");
var changeCase = require("change-case");

var samplesPath = "../../../samples/v1.*/Scenarios/*.json";

hexo.extend.generator.register("generator-sampleBrowser", function(locals) {
	const url_for = hexo.extend.helper.get('url_for').bind(hexo);

    // Get all the samples from the Scenarios folder
    var samples = glob.sync(samplesPath, { nocase: false }).map(function(samplePath, index) {
        return {
            jsonPath: samplePath,
            jsonUrl: "../payloads/" + path.basename(samplePath),
            htmlPath: "samples/" + path.basename(samplePath, ".json") + ".html",
            name: changeCase.sentenceCase(path.basename(samplePath, ".json")),
            index: index
        }
    });

    var generated = [];
    var designerSampleCatalog = [];

    samples.forEach(function(sample, i) {
        var page = {
            path: sample.htmlPath,
            layout: "sample",
            data: {
                title: "Samples",
                sample: sample,
                samples: samples,
                samplePath: sample.htmlPath,
                jsonPath: sample.jsonPath
            }
        };

        designerSampleCatalog.push({
            displayName: sample.name,
            cardPayloadUrl: url_for("/payloads/" + path.basename(sample.jsonPath))
        });

        // Generate an index.html for the first one
        if (i === 0) {
            generated.push({
                path: "samples/index.html",
                layout: "sample",
                data: {
                    title: "Samples",
                    sample: sample,
                    samples: samples,
                    samplePath: sample.htmlPath,
                    jsonPath: sample.jsonPath

                }
            })
        }
        generated.push(page);
    });

    // Publish the designer sample catalog file
    generated.push({
        path: "designer/sample-catalogue.json",
        data: function() {
            return designerSampleCatalog
        }
    });

    return generated;
});
