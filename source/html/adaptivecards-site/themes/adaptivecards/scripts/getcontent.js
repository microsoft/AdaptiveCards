"use strict";

var fs = require("fs");

hexo.extend.helper.register('getcontent', function (path) {
  return fs.readFileSync(path);
});