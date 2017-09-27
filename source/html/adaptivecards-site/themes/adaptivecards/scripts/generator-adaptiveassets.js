"use strict";

// Copy various adaptive card assets from elsehwere in the repo into the output folder

var fs = require("hexo-fs");
var path = require("path");
var glob = require("glob");

var assets = [
    {
        // Sample payloads
        path: "../../../samples/v1.0/**/*.json",
        dest: function (p) { return "payloads/" + path.basename(p); }
    },
    {
        // JSON-schema file
        path: "../../../schemas/adaptive-card.json",
        dest: function (p) { return "schemas/adaptive-card.json"; }
    },
    {
        // renderer script
        path: "../renderer/dist/adaptive-cards.js",
        dest: function (p) { return "js/adaptive-cards.js"; }
    },
    {
        // visualizer script
        path: "../visualizer/built/visualizer-with-renderer.js",
        dest: function (p) { return "visualizer/js/visualizer-with-renderer.js"; }
    },
    {
        // visualizer css
        path: "../visualizer/css/*.css",
        dest: function (p) { return "visualizer/css/" + path.basename(p); }
    }
];

hexo.extend.generator.register("generator-adaptiveassets", function (locals) {

    var allAssets = [];

    assets.forEach(function (asset) {
        var g = glob.sync(asset.path, { nocase: false }).map(function (p) {

            return {
                path: asset.dest(p),
                data: function () {
                    return fs.createReadStream(p);
                }
            }
        });

        g.forEach(function (item) {

            allAssets.push(item);
        });
    });

    return allAssets;
});