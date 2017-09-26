"use strict";

// Copy various adaptive card assets from elsehwere in the repo into the output folder

var fs = require("hexo-fs");
var path = require("path");
var glob = require("glob");

var assets = [
    {
        path: "../../../samples/v1.0/**/*.json",
        dest: function (p) { return "payloads/" + path.basename(p); }
    },
    {
        path: "../../../schemas/adaptive-card.json",
        dest: function (p) { return "schemas/adaptive-card.json"; }
    },
    {
        path: "../renderer/dist/adaptive-cards.json",
        dest: function (p) { return "js/adaptive-cards.json"; }
    },
    {
        path: "../visualizer/built/visualizer.js",
        dest: function (p) { return "js/visualizer.js"; }
    }
];

hexo.extend.generator.register("generator-nodemodules", function (locals) {

    return assets.forEach(function (asset) {
        glob.sync(asset.path, { nocase: false }).map(function (p) {

            return {
                path: asset.dest(p),
                data: function () {
                    return fs.createReadStream(p)
                }
            }
        });
    });
});