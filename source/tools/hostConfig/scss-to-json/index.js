#! /usr/bin/env node
"use strict";
var path = require("path");
var sass = require("node-sass");
var colorString = require('color-string');
var css2json = require('css2json');
var boolean = { "true": true, "false": false };
function convertToAdaptiveCardConfigValue(value) {
    var color = colorString.get(value);
    if (color) {
        return colorString.to.rgb(color.value);
    }
    if (value in boolean) {
        return boolean[value];
    }
    var n = parseInt(value);
    if (!isNaN(n)) {
        return n;
    }
    return JSON.parse(value);
}
function travel(hostConfig, route, content) {
    var split = route.split('.');
    split.shift();
    var ref = hostConfig;
    split.forEach(function (v, i) {
        if (i === split.length - 1) {
            ref[v] = convertToAdaptiveCardConfigValue(content);
        }
        else {
            if (!(v in ref)) {
                ref[v] = {};
            }
            ref = ref[v];
        }
    });
}
function mixin(absPath) {
    var d = ['@import "' + absPath + '";'];
    d.push('@mixin walk($map) {');
    d.push('    @each $key, $value in $map {');
    d.push('        &.#{$key} {');
    d.push('            @if type-of($value) == map {');
    d.push('                @include walk($value) {');
    d.push('                    @content;');
    d.push('                }');
    d.push('            } @else {');
    d.push('                content: $value;');
    d.push('            }');
    d.push('        }');
    d.push('    }');
    d.push('}');
    d.push('#ac-hostConfig {');
    d.push('    @include walk($hostConfig);');
    d.push('}');
    return d.join('\n');
}
function convert(scssFile) {
    var result = sass.renderSync({ data: mixin(path.resolve(scssFile).replace(/\\/g, '/')) });
    var css = result.css.toString();
    var cssJson = css2json(css);
    var hostConfig = {};
    for (var key in cssJson) {
        var value = cssJson[key];
        if (key.indexOf('#ac-hostConfig') === 0) {
            travel(hostConfig, key, value.content);
        }
    }
    return hostConfig;
}
if (require.main === module) {
    var hostConfig = convert(process.argv[2]);
    var output = JSON.stringify(hostConfig, null, 2);
    //add BOM http://stackoverflow.com/questions/17879198/adding-utf-8-bom-to-string-blob
    //so that output works with unix-style redirects e.g. ">"
    var BOM = '\ufeff';
    if (process.argv[3] === '--exec') {
        process.stdout.write(BOM + 'AdaptiveCards.setHostConfig(' + output + ');\n');
    }
    else {
        process.stdout.write(BOM + output);
    }
}
module.exports = convert;
