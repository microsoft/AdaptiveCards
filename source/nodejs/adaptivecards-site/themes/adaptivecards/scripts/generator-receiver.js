// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var fs = require("hexo-fs");
var path = require("path");

hexo.extend.generator.register("generator-receiver", function (locals) {

    return {
        path: "receiver/index.html",
        layout: "receiver",
        data: {
			title: "Receiver",
			hideBreadcrumb: true
        }
    };

});
