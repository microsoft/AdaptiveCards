"use strict";

// Copy scripts from node_modules into the public dir

var fs = require("hexo-fs");
var path = require("path");


var modules = [
    // TODO get from renderer
    //"node_modules/microsoft-adaptivecards/dist/adaptive-cards.js"
];

var visualizerPath = "C:/Dev/Projects/AdaptiveCards/source/html/visualizer/";

hexo.extend.generator.register("generator-visualizer", function (locals) {

    return {
        path: "visualizer/index.html",
        layout: "visualizer",
        data: {
            
        }
    }

});

