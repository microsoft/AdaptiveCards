// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
"use strict";

var fs = require("fs");

hexo.extend.helper.register('get_content', function (path) {
  return fs.readFileSync(path);
});
