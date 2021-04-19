import { ThemeElement } from '../utils/enums';
import * as Constants from '../utils/constants';


export class ThemeConfig {
    constructor(obj = {}) {
        this.button = new Config(ThemeElement.Button, obj);
        this.input = new Config(ThemeElement.Input, obj);
        this.inputDate = new Config(ThemeElement.InputDate, obj);
        this.inputTime = new Config(ThemeElement.InputTime, obj);
        this.radioButton = new Config(ThemeElement.RadioButton, obj);
        this.checkBox = new Config(ThemeElement.CheckBox, obj);
        this.radioButtonText = new Config(ThemeElement.RadioButtonText, obj);
        this.checkBoxText = new Config(ThemeElement.CheckBoxText, obj);
        this.dropdown = new Config(ThemeElement.Dropdown, obj);
        this.dropdownText = new Config(ThemeElement.DropdownText, obj);
    }
}

// Each instance of this class holds config of specific element type 
class Config {
    constructor(type, customConfig = {}) {
        this.type = type;
        this.ios = defaultThemeConfig[type].ios || defaultThemeConfig[type];
        this.android = defaultThemeConfig[type].android || defaultThemeConfig[type];
        this.windows = defaultThemeConfig[type].windows || defaultThemeConfig[type];

        if (customConfig[type]) { // any custom config ?
            let config = customConfig[type];

            this.ios = config["ios"] ? { ...this.ios, ...config["ios"] } : { ...this.ios, ...config };
            this.android = config["android"] ? { ...this.android, ...config["android"] } : { ...this.android, ...config };
            this.windows = config["windows"] ? { ...this.windows, ...config["windows"] } : { ...this.windows, ...config };
        }
    }
}

/**
 * @description Default Theme config JSON. This can be overriden by invoking setThemeConfig method.
 */

// Open Issue : Setting `textTransform` style in android doesn't render the text itself.
// Refer : https://github.com/facebook/react-native/issues/21966
export const defaultThemeConfig = {
    button: {
        ios: {
            borderRadius: 15,
            backgroundColor: Constants.buttonDefaultColor,
            color: Constants.WhiteColor,
            textTransform: 'none'
        },
        android: {
            borderRadius: 15,
            backgroundColor: Constants.buttonDefaultColor,
            color: Constants.WhiteColor,
            textTransform: undefined
        },
        windows: {
            borderRadius: 15,
            backgroundColor: Constants.buttonDefaultColor,
            color: Constants.WhiteColor,
            textTransform: 'none'
        },
    },
    input: {
        borderColor: Constants.EmphasisColor,
        backgroundColor: Constants.WhiteColor,
        borderRadius: 5,
        borderWidth: 1
    },
    inputDate: {
        width: Constants.FullWidth,
        height: 44,
        padding: 5,
        borderWidth: 1,
        backgroundColor: Constants.WhiteColor,
        borderColor: Constants.LightGreyColor,
        borderRadius: 5,
    },
    inputTime: {
        width: Constants.FullWidth,
        height: 44,
        padding: 5,
        borderWidth: 1,
        backgroundColor: Constants.WhiteColor,
        borderColor: Constants.LightGreyColor,
        borderRadius: 5,
    },
    radioButton: {
        width: 24,
        height: 24,
        activeColor: Constants.BlackColor,
        inactiveColor: Constants.LightBlack,
    },
    radioButtonText: {
        marginLeft: 8,
        flexShrink: 1,
        activeColor: Constants.BlackColor,
        inactiveColor: Constants.LightBlack,
    },
    checkBox: {
        width: 28,
        height: 28,
        activeColor: Constants.BlackColor,
        inactiveColor: Constants.LightBlack,
    },
    checkBoxText: {
        marginLeft: 8,
        flexShrink: 1,
        activeColor: Constants.BlackColor,
        inactiveColor: Constants.LightBlack,
    },
    dropdown: {
        flexDirection: Constants.FlexRow,
        justifyContent: Constants.SpaceBetween,
        alignItems: Constants.FlexEnd,
        borderWidth: 1,
        backgroundColor: Constants.WhiteColor,
        borderColor: Constants.LightGreyColor,
        borderRadius: 5,
    },
    dropdownText: {
        color: Constants.BlackColor,
        textAlign: Constants.LeftAlign,
        marginTop: 10,
        marginLeft: 8,
        height: 30,
    }

}