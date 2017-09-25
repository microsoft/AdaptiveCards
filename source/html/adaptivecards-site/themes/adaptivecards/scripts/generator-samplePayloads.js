"ustr strict";

var fs = require("hexo-fs");
var path = require("path");
var glob = require("glob");

var samplesPath = "C:/Dev/Projects/AdaptiveCards/samples/v1.0/**/*.json";

hexo.extend.generator.register("generator-samplePayloads", function (locals) {

    return glob.sync(samplesPath, { nocase: false }).map(function (samplePath) {

        return {
            path: "payloads/" + path.basename(samplePath),
            data: function () {
                
                return fs.createReadStream(samplePath)
            }
        }
    });
});