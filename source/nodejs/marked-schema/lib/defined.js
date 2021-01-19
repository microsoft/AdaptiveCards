"use strict";

module.exports = defined;

/**
* @function defined
* Determines if the specified value exists and is not null.
* @param  {object} value - The object to check.
* @return {boolean} true if value exists and is not null; false otherwise
*/
function defined(value) {
    return (value !== undefined) && (value !== null);
}
