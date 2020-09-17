// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";
var fs = require("hexo-fs");
var path = require("path");
var glob = require("glob");

hexo.extend.generator.register("generator-integrate", function (locals) {
    return new Promise(function (resolve, reject) {
        try {
            var pages = [];

            var sdksPath = "../../../manifests/sdks.json";
            var hostsPath = "../../../manifests/hosts/*.json";
            var pluginsPath = "../../../manifests/plugins/*.json";

            var sdks = JSON.parse(fs.readFileSync(sdksPath));

            var plugins = glob
                .sync(pluginsPath, { nocase: false })
                .map(function (filePath) {
                    return JSON.parse(fs.readFileSync(filePath));
                });

            var hosts = glob
                .sync(hostsPath, { nocase: false })
                .map(function (filePath) {
					var host = JSON.parse(fs.readFileSync(filePath));
					host.pluginsExpanded = [];
					Object.keys(host.plugins).forEach(pluginName => {
						pluginsExpanded.push(plugins.find(p => p.name === pluginName));
					});
                    return host;
                });

            pages.push({
                path: "integrate/index.html",
                layout: "integrate",
                data: {
                    title: "Integrate",
                    hosts: hosts,
                    sdks: sdks,
                    plugins: plugins,
                },
            });

            resolve(pages);
        } catch (err) {
            reject(err);
        }
    });
});
