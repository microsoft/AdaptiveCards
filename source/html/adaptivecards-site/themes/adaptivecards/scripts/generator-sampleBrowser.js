"use strict";

var fs = require("hexo-fs");
var glob = require("glob");
var path = require("path");
var changeCase = require("change-case");

var samplesPath = "C:/Dev/Projects/AdaptiveCards/samples/v1.0/Scenarios/*.json";

hexo.extend.generator.register("generator-sampleBrowser", function (locals) {

    var samples = glob.sync(samplesPath, { nocase: false }).map(function (samplePath) {
        return {
            jsonPath: samplePath,
            htmlPath: "samples/" + path.basename(samplePath, ".json") + ".html",
            name: changeCase.sentenceCase(path.basename(samplePath, ".json"))
        }
    });

    var generated = [];
    samples.forEach(function (sample, i) {
        var s = {
            path: sample.htmlPath,
            layout: "sample",
            data: {
                title: sample.name,
                sample: sample,
                samples: samples
            }
        };
        if(i === 0) {
            generated.push({
                path: "samples/index.html",
                layout: "sample",
                data: {
                    title: sample.name,
                    sample: sample,
                    samples: samples
                }
            })
        }
        generated.push(s);
    });

    return generated;
});