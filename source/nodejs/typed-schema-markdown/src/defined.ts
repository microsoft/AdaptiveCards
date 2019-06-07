// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

/**
* @function defined
* Determines if the specified value exists and is not null.
* @param  {object} value - The object to check.
* @return {boolean} true if value exists and is not null; false otherwise
*/
export function defined(value) {
	return (value !== undefined) && (value !== null);
}