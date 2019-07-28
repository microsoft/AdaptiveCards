// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

// Copy various adaptive card assets from elsehwere in the repo into the output folder

var fs = require("hexo-fs");
var path = require("path");
var glob = require("glob");
var md5 = require("md5");

var assets = [
    {
        // Sample payloads
        path: "../../../samples/v1.*/**/*.json",
        dest: function (p) { return "payloads/" + path.basename(p); }
	},
    {
		// Legacy JSON schema URL, it'll stay at 1.1 as a point-in-history and we're
		// deprecating that url path as it's not versioned
        path: "../../../schemas/1.1.0/adaptive-card.json",
        dest: function (p) { return "schemas/adaptive-card.json"; }
    },
    {
        path: "../../../schemas/*/adaptive-card.json",
        dest: function (p) {
			// Keep the last 2 path portions... 1.2.0/adaptive-card.json, and put it in the schemas folder
			return "schemas/" + p.split("/").slice(-2).join("/");
		}
    },
    {
        // adaptive cards module
        path: "node_modules/adaptivecards/dist/*.*",
        dest: function (p) { return p; }
	},
	// {
    //     // designer script (separated because we want to hash it)
    //     path: "node_modules/adaptivecards-designer/dist/adaptivecards-designer.js",
	// 	dest: function (p) { return p; }		
	// },
	{
        // designer assets 
        path: "node_modules/adaptivecards-designer/dist/*.*",
		dest: function (p) { return p; }
	},
	{
        // designer module (hashing not working for CSS files; the designer expects certain filenames)
        path: "node_modules/adaptivecards-designer/dist/containers/*.*",
		dest: function (p) { return p; },
		noHash: true
	},
	{
        // monaco-editor module
        path: "node_modules/monaco-editor/min/vs/**/*.*",
		dest: function (p) { return p; },
		noHash: true
    },
    {
        // visualizer script
        path: "node_modules/adaptivecards-visualizer/dist/adaptivecards-visualizer.min.js",
        dest: function (p) { return "visualizer/adaptivecards-visualizer.min.js"; }
    },
    {
        // visualizer css
        path: "node_modules/adaptivecards-visualizer/css/*.css",
        dest: function (p) { return "visualizer/css/" + path.basename(p); }
    },
    {
        // visualizer assets
        path: "node_modules/adaptivecards-visualizer/assets/*",
        dest: function (p) { return "visualizer/assets/" + path.basename(p); }
    },
    {
        // visualizer monaco loader
        path: "node_modules/adaptivecards-visualizer/src/monaco-loader.js",
		dest: function (p) { return "visualizer/monaco-loader.js" },
		noHash: true
	},
	{
        // site CSS
        path: "themes/adaptivecards/source/css/*.css",
		dest: function (p) { return "css/" + path.basename(p) }
	},
	{
        // site JS
        path: "themes/adaptivecards/source/js/*.js",
		dest: function (p) { return "js/" + path.basename(p) }
	}
];

hexo.extend.generator.register("generator-adaptiveassets", function (locals) {

	let allAssets = [];
	let hashExtensions = [ ".css", ".js" ];
	let hashedAssets = [];

    assets.forEach(function (asset) {
        var g = glob.sync(asset.path, { nocase: false }).map(function (sourcePath) {

			let destPath = asset.dest(sourcePath);

			if(!asset.noHash && hashExtensions.includes(path.extname(destPath))) {
				// For cache-busting append the md5 hash of our script and CSS content
				// EXAMPLE: adaptivecards.js => adaptivecards.c66a8322.js
				let originalDestPath = destPath;
				let hash = md5(fs.readFileSync(sourcePath)).substring(0, 6);
				let hashedFilename = path.basename(destPath, path.extname(destPath)) + "." + hash + path.extname(destPath);
				
				destPath = path.dirname(destPath) + "/" + hashedFilename;
				hashedAssets.push({
					originalPath: originalDestPath,
					hashedPath: destPath
				});
			}

			return {
                path: destPath,
                data: function () {
                    return fs.createReadStream(sourcePath);
                }
            }
        });

        g.forEach(function (item) { allAssets.push(item); });
	});
	
	hexo.locals.set("hashedAssets", () => hashedAssets);

    return allAssets;
});
