// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

const emitDebugOutput = false; // set to true to get debug spew firehose

function debugLog(msg) {
    if (emitDebugOutput) {
        console.log(msg);
    }
}

// Copy various adaptive card assets from elsehwere in the repo into the output folder

var fs = require("hexo-fs");
var path = require("path");
var glob = require("glob");
var md5 = require("md5");

// These are the flat asset files that will be copied into the output folder and available to
// reference in HTML templates. Note that these are expected to exist within the
// `adaptivecards-site/node_modules` directory
var simpleAssets = [
    "node_modules/adaptive-expressions/lib/*.*",
    "node_modules/@fortawesome/fontawesome-free/css/all.min.css",
    "node_modules/@fortawesome/fontawesome-free/webfonts/*.*",
    "node_modules/highlightjs/highlight.pack.min.js",
    "node_modules/highlightjs/styles/default.css",
    "node_modules/jquery/dist/jquery.min.js",
    "node_modules/markdown-it/dist/markdown-it.min.js"
];

// These are the other asset files that need to be copied into a specific location
// the dest param describes the dir/filename used in the output destination
var customAssets = [
    {
        // AC renderer
        path: "node_modules/adaptivecards/dist/*.*",
        pathPrefix: process.env.npm_config_local_prefix
    },
    {
        // AC designer
        path: "node_modules/adaptivecards-{templating,designer}/dist/*.*",
        pathPrefix: process.env.npm_config_local_prefix
    },
    {
        // markdown-it
        path: "node_modules/markdown-it/dist/markdown-it.min.js",
        pathPrefix: process.env.npm_config_local_prefix
    },
    {
        // Sample payloads and templates
        path: "../../../samples/{v1.*,Templates}/**/*.json",
        dest: function (p) {
            return "payloads/" + path.basename(p);
        }
    },
    {
        // Unversioned JSON schema URL, set to the 1.3 (current) version as versioned schema paths are not in use.
        // May be deprecated in the future in favor of versioned schema paths.
        path: "../../../schemas/1.5.0/adaptive-card.json",
        dest: function (p) {
            return "schemas/adaptive-card.json";
        }
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
        pathPrefix: process.env.npm_config_local_prefix,
        dest: function (p) {
            return "css/outlook.css";
        }
    },
    {
        // designer module (hashing not working for CSS files; the designer expects certain filenames)
        path: "node_modules/adaptivecards-designer/dist/containers/*.*",
        pathPrefix: process.env.npm_config_local_prefix,
        noHash: true
    },
    {
        // designer module (hashing not working for CSS files; the designer expects certain filenames)
        path: "node_modules/adaptivecards-designer/dist/adaptivecards-designer.css",
        pathPrefix: process.env.npm_config_local_prefix,
        noHash: true
    },
    {
        // monaco-editor module and maps, for science
        path: "node_modules/monaco-editor/{min,min-maps}/vs/**/*.*",
        pathPrefix: path.join(process.env.npm_config_local_prefix, "adaptivecards-site"),
        noHash: true
    },
    {
        // site CSS
        path: "themes/adaptivecards/source/css/*.css",
        dest: function (p) {
            return "css/" + path.basename(p);
        }
    },
    {
        // site JS
        path: "themes/adaptivecards/source/js/*.js",
        dest: function (p) {
            return "js/" + path.basename(p);
        }
    },
    {
        path: "node_modules/workbox-v*/*",
        dest: function (p) {
            return "node_modules/workbox/" + path.basename(p);
        },
        noHash: true
    }
];

hexo.extend.generator.register("generator-adaptiveassets", function (locals) {
    let allAssets = [];
    let hashExtensions = [".css", ".js"];
    let hashedAssets = [];

    debugLog("processing simple assets");
    debugLog(`  prefix: ${process.env.npm_config_local_prefix}`);
    simpleAssets.forEach(function (a) {
        debugLog(`  path: ${a}`);
        customAssets.push({
            path: a,
            pathPrefix: path.join(process.env.npm_config_local_prefix, "adaptivecards-site")
        });
    });

    debugLog("\ngenerating custom assets");
    customAssets.forEach(function (asset) {
        let assetPath = asset.path;
        if (asset.pathPrefix) {
            assetPath = path.join(asset.pathPrefix, asset.path);
        }
        debugLog(`--------------------`);
        debugLog(`asset path is "${assetPath}"`);

        var g = glob.sync(assetPath, { nocase: false }).map(function (sourcePath) {
            if (!asset.dest) {
                asset.dest = function (p) {
                    return p;
                };
            }

            let destPath = asset.dest(sourcePath);
            debugLog(`  source path: "${sourcePath}"`);
            if (sourcePath != destPath) {
                debugLog(`    adjusted destination path to "${destPath}"`);
            }

            if (asset.pathPrefix) {
                destPath = destPath.replace(asset.pathPrefix + "/", "");
            }
            debugLog(`  destination path: "${destPath}"`);

            if (!asset.noHash && hashExtensions.includes(path.extname(destPath))) {
                // For cache-busting append the md5 hash of our script and CSS content
                // EXAMPLE: adaptivecards.js => adaptivecards.c66a8322.js
                let originalDestPath = destPath;
                let hash = md5(fs.readFileSync(sourcePath)).substring(0, 6);
                let hashedFilename =
                    path.basename(destPath, path.extname(destPath)) +
                    "." +
                    hash +
                    path.extname(destPath);

                destPath = path.dirname(destPath) + "/" + hashedFilename;
                hashedAssets.push({
                    originalPath: originalDestPath,
                    hashedPath: destPath
                });
                debugLog(`  hashed path: "${destPath}"`);
            }

            debugLog("");
            return {
                path: destPath,
                data: function () {
                    debugLog(`  asset "${sourcePath}" => "${destPath}"`);
                    if (emitDebugOutput && !fs.existsSync(sourcePath)) {
                        debugLog(`===>ERROR: unable to find "${sourcePath}"<===`);
                    }
                    return fs.createReadStream(sourcePath);
                }
            };
        });

        g.forEach(function (item) {
            allAssets.push(item);
        });
    });

    hexo.locals.set("hashedAssets", () => hashedAssets);

    return allAssets;
});
