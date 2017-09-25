"use strict";

// Copy scripts from node_modules into the public dir

var fs = require("hexo-fs");
var path = require("path");

var schemaPath = "C:/Dev/Projects/AdaptiveCards/schemas/adaptive-card.json";

hexo.extend.generator.register("generator-schemas", function (locals) {

    return {
        path: "schemas/" + path.basename(schemaPath),
        data: function () {
            return fs.createReadStream(schemaPath)
        }
    }

});