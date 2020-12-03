"use strict";
var defined = require('./defined');

module.exports = defaultValue;

/**
* @function defaultValue
* Gets the value of an object, using a fallback default value if the primary
* value is not defined.
* @param  {object} value - The value to be returned, assuming it's defined.
* @param  {object} fallback - The fallback value if value is undefined
* @return {object} value if it was defined, otherwise fallback.
*/
function defaultValue(value, fallback) {
    if (defined(value)) {
        return value;
    }

    return fallback;
}
