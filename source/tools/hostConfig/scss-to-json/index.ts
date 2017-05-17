#! /usr/bin/env node
/// <reference path="../color-string.d.ts" />

import * as path from 'path';
import * as sass from 'node-sass';

const colorString = require('color-string') as typeof ColorString;

const css2json = require('css2json') as { (css: string): { [selector: string]: { content: string } } };

const boolean = { "true": true, "false": false };

function convertToAdaptiveCardConfigValue(value: string) {
    const color = colorString.get(value);
    if (color) {
        return colorString.to.rgb(color.value);
    }
    if (value in boolean) {
        return boolean[value];
    }
    const n = parseInt(value);
    if (!isNaN(n)) {
        return n;
    }
    return JSON.parse(value);
}

function travel(hostConfig: any, route: string, content: string) {
    const split = route.split('.');
    split.shift();
    let ref = hostConfig;
    split.forEach(function (v, i) {
        if (i === split.length - 1) {
            ref[v] = convertToAdaptiveCardConfigValue(content);
        } else {
            if (!(v in ref)) {
                ref[v] = {};
            }
            ref = ref[v];
        }
    });
}

function mixin(absPath: string) {
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

function convert(scssFile: string) {
    const result = sass.renderSync({ data: mixin(path.resolve(scssFile).replace(/\\/g, '/')) });
    const css = result.css.toString();
    const cssJson = css2json(css);
    const hostConfig = {};

    for (const key in cssJson) {
        const value = cssJson[key];
        if (key.indexOf('#ac-hostConfig') === 0) {
            travel(hostConfig, key, value.content);
        }
    }

    return hostConfig;
}

export = convert;

if (require.main === module) {
    var hostConfig = convert(process.argv[2]);
    var output = JSON.stringify(hostConfig, null, 2);

    //add BOM http://stackoverflow.com/questions/17879198/adding-utf-8-bom-to-string-blob
    //so that output works with unix-style redirects e.g. ">"
    const BOM = '\ufeff';

    if (process.argv[3] === '--exec') {
        process.stdout.write(BOM + 'AdaptiveCards.setHostConfig(' + output + ');\n');
    } else {
        process.stdout.write(BOM + output);
    }

}
