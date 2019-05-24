// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var specgenerator = require("spec-generator");
var fs = require("fs");

hexo.extend.generator.register("generator-specs", function (locals) {

    return new Promise(function (resolve, reject) {
		specgenerator.generateAsync().then(function () {
			resolve([]);
		}).catch(function (err) {
			reject(err);
		});
    });
});
