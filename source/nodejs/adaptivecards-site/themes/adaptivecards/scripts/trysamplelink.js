"use strict";

var path = require("path");

hexo.extend.helper.register('trysamplelink', function (samplePath) {
  return '<a class="w3-btn w3-blue" target="_blank" href="/designer/index.html?card=/payloads/' + path.basename(samplePath) + '">Try it Yourself »</a>';
});
