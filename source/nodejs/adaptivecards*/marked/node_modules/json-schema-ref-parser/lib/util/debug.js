'use strict';

var debug = require('debug');

/**
 * Writes messages to stdout.
 * Log messages are suppressed by default, but can be enabled by setting the DEBUG variable.
 * @type {function}
 */
module.exports = debug('json-schema-ref-parser');
