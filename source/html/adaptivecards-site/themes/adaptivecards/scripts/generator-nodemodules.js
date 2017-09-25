"use strict";

// Copy scripts from node_modules into the public dir

var fs = require("hexo-fs");
var path = require("path");

var modules = [
    // TODO get from renderer
    //"node_modules/microsoft-adaptivecards/dist/adaptive-cards.js"
];

hexo.extend.generator.register("generator-nodemodules", function (locals) {
    return modules.map(function (file) {
        return {
            path: "js/" + path.basename(file),
            data: function () {
                return fs.createReadStream(file)
            }
        }
    });
});