#! /usr/bin/env node

import * as fs from 'fs';
import * as path from 'path';
import * as sass from 'node-sass';

const css2json = require('css2json') as { (css: string): { [selector: string]: { content: string } } };
const cssColorNames = require('css-color-names') as { [name: string]: string };
const boolean = { "true": true, "false": false };

function parseNumericList(s: string): number[] {
    var result: number[] = [];

    var re = /[\.-]?(?:0|[1-9]\d*)(?:\.\d*)?/g;
    var matches: RegExpExecArray;

    while ((matches = re.exec(s)) !== null) {
        if (matches.index === re.lastIndex) {
            re.lastIndex++;
        }
        result.push(parseFloat(matches[0]));
    }

    return result;
}

function rgbToAARRGGBB(value: string) {
    const rgba = parseNumericList(value);
    const alpha = Math.round((rgba[3] || 1) * 255);
    const argb = [alpha].concat(rgba.slice(0, 3));
    const hex = argb.map(n => ('0' + n.toString(16).toUpperCase()).substr(-2));
    return '#' + hex.join('');
}

function convertToAdaptiveCardConfigValue(value: string) {
    if (typeof value === 'string' && value.indexOf('#') === 0) {
        return value;
    }
    if (typeof value === 'string' && value.indexOf('rgb') === 0) {
        return rgbToAARRGGBB(value);
    }
    if (value in cssColorNames) {
        return cssColorNames[value];
    }
    if (value in boolean) {
        return boolean[value];
    }
    const n = parseInt(value);
    if (!isNaN(n)) {
        return n;
    }
    try {
        return JSON.parse(value);
    }
    catch (e) {
        return value;
    }
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

function executeCommandLine() {
    var hostConfig = convert(process.argv[2]);
    var output = JSON.stringify(hostConfig, null, 2);

    //add BOM http://stackoverflow.com/questions/17879198/adding-utf-8-bom-to-string-blob
    //so that output works with unix-style redirects e.g. ">"
    const BOM = '\ufeff';

    if (process.argv.length > 3) {
        if (process.argv[3] === '--exec') {
            process.stdout.write(BOM + 'AdaptiveCards.setHostConfig(' + output + ');\n');
            return;

        } else if (process.argv[3].indexOf('--css') === 0) {
            const css = '#ac-hostConfig {\n content: ' + JSON.stringify(JSON.stringify(hostConfig)) + ';\n}\n';

            if (process.argv[3] === '--css-append') {
                fs.appendFileSync(process.argv[4], '\n' + css);
                return;

            } else {
                process.stdout.write(BOM + css);
                return;
            }
        }
    }

    process.stdout.write(BOM + output);
}

if (require.main === module) {
    executeCommandLine();
}
