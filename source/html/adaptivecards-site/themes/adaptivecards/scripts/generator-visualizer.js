"use strict";

var fs = require("hexo-fs");
var path = require("path");

hexo.extend.generator.register("generator-visualizer", function (locals) {

    return [
        {
            path: "visualizer/index.html",
            layout: "visualizer",
            data: {}
        },
        {
            path: "js/visualizer.js",
            data: function () {
                var file = fs.createWriteStream("../visualizer/built/visualizer.js")
                if (!file) {
                    throw new Error("MISSING Visualizer script. Did you build it?");
                }
                return file;
            }
        }
    ];

});

