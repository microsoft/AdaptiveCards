// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var fs = require("hexo-fs");
var glob = require("glob");
var path = require("path");
var changeCase = require("change-case");

var scenariosSamplesPath = "../../../samples/v1.*/Scenarios/*.json";

hexo.extend.generator.register("generator-sampleBrowser", function(locals) {
	const url_for = hexo.extend.helper.get('url_for').bind(hexo);

    var generated = [];
    var designerSampleCatalog = [];

    // Get all the samples from the Scenarios folder
    var scenarios = glob.sync(scenariosSamplesPath, { nocase: false }).map(function(samplePath, index) {
		var fileNameWithoutExt = path.basename(samplePath, ".json");
        return {
            jsonPath: samplePath,
			jsonUrl: url_for(`/payloads/${path.basename(samplePath)}`),
			templatePath: `../../../samples/templates/Scenarios/${fileNameWithoutExt}.template.json`,
			templateUrl: url_for(`/payloads/${fileNameWithoutExt}.template.json`),
			dataPath: `../../../samples/templates/Scenarios/${fileNameWithoutExt}.data.json`,
			dataUrl: url_for(`/payloads/${fileNameWithoutExt}.data.json`),
            htmlPath: `samples/${fileNameWithoutExt}.html`,
            name: changeCase.sentenceCase(fileNameWithoutExt),
            index: index
        }
	});

    scenarios.forEach(function(sample, i) {
        var page = {
            path: sample.htmlPath,
            layout: "sample",
            data: {
                title: "Samples and Templates",
                sample: sample,
                samples: scenarios,
                samplePath: sample.htmlPath,
				jsonPath: sample.jsonPath,
				templatePath: sample.templatePath,
				dataPath: sample.dataPath
            }
		};

		// TODO: Find way to include the template samples here, for now, just load the regular samples
        designerSampleCatalog.push({
            displayName: sample.name,
			cardPayloadUrl: sample.jsonUrl
			//dataSampleUrl: sample.dataUrl
        });

        // Generate an index.html for the first one
        if (i === 0) {
            generated.push({
                path: "samples/index.html",
                layout: "sample",
                data: {
                    title: "Samples and Templates",
                    sample: sample,
                    samples: scenarios,
                    samplePath: sample.htmlPath,
					jsonPath: sample.jsonPath,
					templatePath: sample.templatePath,
					dataPath: sample.dataPath
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
