"use strict";

var fs = require("hexo-fs");
var glob = require("glob");
var path = require("path");
var changeCase = require("change-case");

var samplesPath = "C:/Dev/Projects/AdaptiveCards/samples/v1.0/Scenarios/*.json";

hexo.extend.generator.register("generator-sampleBrowser", function (locals) {
    
    var samples = glob.sync(samplesPath, { nocase: false }).map(function(samplePath) {
      return {
          jsonPath: samplePath,
          htmlPath: "samples/" + path.basename(samplePath, ".json") + ".html",
          name: changeCase.sentenceCase(path.basename(samplePath, ".json"))
      }  
    });

    return samples.map(function (sample) {
        return {
            path: sample.htmlPath,
            layout: "sample",
            data: {
                title: sample.name,
                sample: sample,
                samples: samples
            }
        }
    });
});