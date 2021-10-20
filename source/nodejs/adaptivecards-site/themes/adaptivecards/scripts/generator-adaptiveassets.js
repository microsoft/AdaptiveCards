// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

// Copy various adaptive card assets from elsehwere in the repo into the output folder

var fs = require("hexo-fs");
var path = require("path");
var glob = require("glob");
var md5 = require("md5");

// These are the flat asset files that will be copied into the output folder
// and available to reference in HTML templates
var simpleAssets = [
	"node_modules/adaptivecards/dist/*.*",
	"node_modules/adaptive-expressions/lib/*.*",
	"node_modules/adaptivecards-designer/dist/*.*",
	"node_modules/adaptivecards-templating/dist/*.*",
	"node_modules/@fortawesome/fontawesome-free/css/all.min.css",
	"node_modules/@fortawesome/fontawesome-free/webfonts/*.*",
	"node_modules/highlightjs/highlight.pack.min.js",
	"node_modules/highlightjs/styles/default.css",
	"node_modules/jquery/dist/jquery.min.js",
	"node_modules/markdown-it/dist/markdown-it.min.js",
];

// These are the other asset files that need to be copied into a specific location
// the dest param describes the dir/filename used in the output destination
var customAssets = [
    {
        // Sample payloads
        path: "../../../samples/v1.*/**/*.json",
        dest: function (p) { return "payloads/" + path.basename(p); }
	},
	{
        // Sample template payloads
        path: "../../../samples/Templates/**/*.json",
        dest: function (p) { return "payloads/" + path.basename(p); }
	},
    {
		// Unversioned JSON schema URL, set to the 1.3 (current) version as versioned schema paths are not in use.
		// May be deprecated in the future in favor of versioned schema paths.
        path: "../../../schemas/1.3.0/adaptive-card.json",
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
        // CSS used for samples on the site
        path: "node_modules/adaptivecards-designer/dist/containers/outlook-container.css",
	    dest: function (p) { return "css/outlook.css"; }
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

	simpleAssets.forEach(function(a) {
		customAssets.push({
			path: a,
			dest: function(p) { return p; }
		});
	});

    customAssets.forEach(function (asset) {
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
