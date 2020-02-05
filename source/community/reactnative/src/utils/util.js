import * as Enums from './enums';
import { HostConfigManager } from './host-config';

export function getValueOrDefault(obj, defaultValue) {
	return obj ? obj : defaultValue;
}

export function isNullOrEmpty(value) {
	return value === undefined || value === null || value === "";
}

export function isString(value) {
	return typeof value === 'string' || value instanceof String;
}

export function isaNumber(value) {
	var parsedValue = parseInt(value, 10);
	if (!isNaN(parsedValue)) {
		return true;
	}
	return false;
}

/**
 * @description
 * This function will return the Number for the specified pixel string / number
 * it will return null, if it is not an number.
 * for example..convertStringToNumber('100')    // 100
				convertStringToNumber('100px')  // 100
				convertStringToNumber('100a5')  // 100
				convertStringToNumber(100)  	  // 100
				convertStringToNumber('ABC')    // null
				convertStringToNumber(null)     // null
				convertStringToNumber('ABC100')   // null 
 * @param {string/number} value 
 */
export function convertStringToNumber(value) {
	let intValue = parseInt(value);
	if (isNaN(intValue)) {
		return null;
	} else {
		return intValue;
	}
}

/**
 * @description
 * This function will return the Enum value for the specified Key if its present or
 * it will return the defaultValue.
 * for eg.. Utils.parseHostConfigEnum(
                Enums.InputTextStyle,
                payload.style,
                Enums.InputTextStyle.Text)
 * @param {Enum} targetEnum 
 * @param {string} keyName 
 * @param {Enum} defaultValue 
 */
export function getEnumValueOrDefault(targetEnum, keyName, defaultValue) {
	if (isNullOrEmpty(keyName)) {
		return defaultValue;
	}
	for (var key in targetEnum) {
		let value = targetEnum[key];
		if (key.toLowerCase() === keyName.toLowerCase()) {
			return value;
		}
	}
	return defaultValue;
}

/**
 * @description Returns the corresponding Enum Value from the TargetEnum based on the value.
 * @param {Enum} targetEnum 
 * @param {string/number} value 
 * @param {Enum} defaultValue 
 */
export function parseHostConfigEnum(targetEnum, value, defaultValue) {
	if (typeof value === "string") {
		return getEnumValueOrDefault(targetEnum, value, defaultValue);
	} else if (typeof value === "number") {
		return getValueOrDefault(value, defaultValue);
	} else {
		return defaultValue;
	}
}

/**
 * @description Returns the keyboard type that needs to be opened based on the text content type.
 * @param {Enums.InputTextStyle} textContentType
 * @return {string} Actual keyboard type value
 */
export function getKeyboardType(textContentType) {
	switch (textContentType) {
		case Enums.InputTextStyle.Text:
			return "default";
		case Enums.InputTextStyle.Tel:
			return "phone-pad";
		case Enums.InputTextStyle.Url:
			return "default";
		case Enums.InputTextStyle.Email:
			return "email-address";
		case Enums.InputTextStyle.Number:
			return "numeric"
		default:
			return "none";
	}
}

/**
 * @description Returns the effective style that needs to be set to the text input.
 * @param {Enums.InputTextStyle} style 
 * @return {string} Actual style value
 */
export function getEffectiveInputStyle(style) {
	switch (style) {
		case Enums.InputTextStyle.Text:
			return "name";
		case Enums.InputTextStyle.Tel:
			return "telephoneNumber";
		case Enums.InputTextStyle.Url:
			return "URL";
		case Enums.InputTextStyle.Email:
			return "emailAddress";
		default:
			return "none";
	}
}

/**
 * @description Returns the actual size value based on the given enum value.
 * @param {Enums.Size} size 
 * @return {number | string} Actual size value
 */
export function getEffectiveSize(size) {
	switch (size) {
		case Enums.Size.Auto:
			return "contain";
		case Enums.Size.Stretch:
			return "stretch";
		case Enums.Size.Small:
			return HostConfigManager.getHostConfig().imageSizes.small;
		case Enums.Size.Medium:
			return HostConfigManager.getHostConfig().imageSizes.medium;
		case Enums.Size.Large:
			return HostConfigManager.getHostConfig().imageSizes.large;
		default:
			return "contain";
	}
}

/**
 * @description Parse the given version string
 * @param {string} versionString 
 * @return {object} Version object with major and minor values
 */
export function parseVersion(versionString) {
	var result = {
		major: 0,
		minor: 0
	};

	if (!versionString)
		return result;

	var regEx = /([\d]+)(?:\.([\d]+))?/gi;
	var matches = regEx.exec(versionString);
	if (matches != null) {
		// major
		result.major = parseInt(matches[1]);

		// minor
		result.minor = parseInt(matches[2]) || result.minor;
	}
	return result;
}

/**
 * @description Validate the given url for proper remote URL / data: format
 * @param {url} url of the image 
 * @return {boolean}
 */
export function validateUrl(url) {
	let urlRegEx = /^(?:[a-z]+:)?\/\/[\w.]+/i;
	let dataregex = /^\s*data:([a-z]+\/[a-z]+(;[a-z\-]+\=[a-z\-]+)?)?(;base64)?,[a-z0-9\!\$\&\'\,\(\)\*\+\,\;\=\-\.\_\~\:\@\/\?\%\s]*\s*$/i;

	return urlRegEx.test(url) || dataregex.test(url);
}

/**
 * @description Check whether the given image path format is a proper remote URL / data URI / local asset
 * @param {string} input - Image path
 * @returns {boolean}
 */
export function isValidImageURI(input) {
	const assetRegex = /^Assets\//;
	return validateUrl(input) || assetRegex.test(input);
}

/**
 * @description Return the image url based on its validation (Base64, Absolute)
 * @param {string|object} image
 * @return {string}  url of the image
 */
export function getImageUrl(image) {
	if (isNullOrEmpty(image)) {
		return image
	}
	image = this.isString(image) ? image : image.url
	return validateUrl(image) ? image : image.split('/').pop().split('.')[0];
}

/**
 * @description Convert the color in aRGB hex format to RGBa CSS format
 * @param {string} color 
 * @return {object} RGBa CSS format
 */
/**
 * argb in hex to css rgba
 */
export function hexToRGB(color) {
	var regEx = /#([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})?/gi;

	var matches = regEx.exec(color);

	if (matches && matches[4]) {
		var a = parseInt(matches[1], 16) / 255;
		var r = parseInt(matches[2], 16);
		var g = parseInt(matches[3], 16);
		var b = parseInt(matches[4], 16);

		return "rgba(" + r + "," + g + "," + b + "," + a + ")";
	}
	else {
		return color;
	}
}

/**
 * @description Generates an unique ID for the element if its not part of the payload
 * @return {string} ID as string
 */
/**
 * argb in hex to css rgba
 */
export function generateID() {
	return Math.random().toString(36).substr(2, 9);
}