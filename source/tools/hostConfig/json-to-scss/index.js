"use strict";
/// <reference path="../color-string.d.ts" />
var colorString = require('color-string');
function convertToCssValue(value) {
    if (typeof value === 'number') {
        return value + 'px';
    }
    if (typeof value === 'string') {
        var color = colorString.get(value);
        if (color) {
            //Xaml is AARRGGBB, but hex is parsed as RRGGBBAA, so move Alpha to front
            //only when the Alpha is not 1, because 1 is the default when Alpha is not present
            if (color.value[3] !== 1) {
                color.value.push(color.value.shift());
            }
            console.log(value + ' ' + colorString.to.rgb(color.value));
            return colorString.to.rgb(color.value);
        }
    }
    return JSON.stringify(value);
}
function indent(level) {
    return new Array(level + 1).join('  ');
}
function appendToLast(output, append) {
    output[output.length - 1] += append;
}
function convertToSCSS(x, varName) {
    if (varName === void 0) { varName = '$hostConfig'; }
    var output = [];
    function walk(prefix, node, indentLevel) {
        output.push(indent(indentLevel) + prefix + ': (');
        var first = true;
        for (var key in node) {
            if (!first) {
                appendToLast(output, ',');
            }
            var value = node[key];
            if (typeof value === 'object') {
                walk(key, value, indentLevel + 1);
            }
            else {
                output.push(indent(indentLevel + 1) + key + ': ' + convertToCssValue(value));
            }
            first = false;
        }
        output.push(indent(indentLevel) + ')');
    }
    walk(varName, x, 0);
    appendToLast(output, ';');
    return output.join('\n');
}
module.exports = convertToSCSS;
