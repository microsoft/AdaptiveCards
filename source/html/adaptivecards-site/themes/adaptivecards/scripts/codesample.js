"use strict";

var markedschema = require("marked-schema");
var marked = require("marked");
var fs = require("fs");

hexo.extend.helper.register('codesample', function (path) {
  //var path = pathFn.join(hexo.source_dir, filename);
  var content = fs.readFileSync(path);
  return '<pre><code>' + content + '</code></pre>';

});