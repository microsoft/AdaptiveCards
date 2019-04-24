// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var fs = require("hexo-fs");
var path = require("path");

hexo.extend.generator.register("generator-visualizer", function (locals) {

    return {
        path: "visualizer/index.html",
        layout: "visualizer",
        data: {
			title: "Visualizer",
			hideBreadcrumb: true
        }
    };

});
