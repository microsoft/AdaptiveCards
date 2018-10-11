"use strict";

var fs = require("hexo-fs");
var path = require("path");

hexo.extend.generator.register("generator-designer", function (locals) {

    return {
        path: "designer/index.html",
        layout: "designer",
        data: {
			title: "Designer",
			hideBreadcrumb: true
        }
    };
});
