import * as Enums from "./enums";
import { gethostConfig } from "./host-config";

const hostConfig = gethostConfig();

export function getValueOrDefault(obj, defaultValue) {
    return obj ? obj : defaultValue;
}

export function isNullOrEmpty(value) {
    return value === undefined || value === null || value === "";
}
/**
 *  This function will return the Enum value for the specified Key if its present or
 *  it will return the defaultValue.
 *  for eg.. Utils.parseHostConfigEnum(
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
 *  Returns the corresponding Enum Value from the TargetEnum based on the value.
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
 * Returns the keyboard type that needs to be opened based on the text content type.
 * @param {Enums.InputTextStyle} textContentType  
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
 *  Returns the effective style that needs to be set to the text input.
 * @param {Enums.InputTextStyle} style 
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




export function getEffectiveSize(size) {
    switch (size) {
        case Enums.Size.Auto:
            return "contain";
        case Enums.Size.Stretch:
            return "stretch";
        case Enums.Size.Small:
            return hostConfig.imageSizes.small;
        case Enums.Size.Medium:
            return hostConfig.imageSizes.medium;
        case Enums.Size.Large:
            return hostConfig.imageSizes.large;
        default:
            return "contain";
    }
}







