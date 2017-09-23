#!/usr/bin/env node
"use strict";

var fs = require('fs');
var path = require('path');
var defined = require('../lib/defined');
var defaultValue = require('../lib/defaultValue');
var refParser = require('json-schema-ref-parser');
var argv = require('minimist')(process.argv.slice(2));
var yaml = require('js-yaml');
var generateMarkdown = require("../lib/generateMarkdown");

if (!defined(argv._[0]) || defined(argv.h) || defined(argv.help)) {
    var help = 'Usage: node ' + path.basename(__filename) + ' [path-to-json-schema-file] [path-to-toc-yml] [OPTIONS]\n';
    process.stdout.write(help);
    return;
}


var filepath = argv._[0];
var rawSchema = JSON.parse(fs.readFileSync(filepath));

var tocPath = argv._[1];
var toc = yaml.safeLoad(fs.readFileSync(tocPath));

var rootObject = defaultValue(argv.r, null);

refParser.dereference(rawSchema)
    .then(function (schema) {
        process.stdout.write(generateMarkdown.generateMarkdown({
            schema: schema,
            toc: toc,
            rootObject: rootObject
        }));
    })
    .catch(function (err) {
        console.error(err);
    });
