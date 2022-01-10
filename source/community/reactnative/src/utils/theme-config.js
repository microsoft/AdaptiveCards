import { ThemeElement } from '../utils/enums';
import * as Constants from '../utils/constants';


export class ThemeConfig {
    constructor(obj = {}) {
        this.button = new Config(ThemeElement.Button, obj);
        this.input = new Config(ThemeElement.Input, obj);
        this.inputLabel = new Config(ThemeElement.InputLabel, obj);
        this.inputDate = new Config(ThemeElement.InputDate, obj);
        this.inputTime = new Config(ThemeElement.InputTime, obj);
        this.radioButton = new Config(ThemeElement.RadioButton, obj);
        this.checkBox = new Config(ThemeElement.CheckBox, obj);
        this.radioButtonText = new Config(ThemeElement.RadioButtonText, obj);
        this.checkBoxText = new Config(ThemeElement.CheckBoxText, obj);
        this.dropdown = new Config(ThemeElement.Dropdown, obj);
        this.dropdownText = new Config(ThemeElement.DropdownText, obj);
        this.picker = new Config(ThemeElement.Picker, obj);
        this.dateTimePicker = new Config(ThemeElement.DateTimePicker, obj)
        this.switch = new Config(ThemeElement.Switch, obj);
        this.inlineAction = new Config(ThemeElement.InlineAction, obj);
        this.inlineActionText = new Config(ThemeElement.InlineActionText, obj);
		this.actionSet = new Config(ThemeElement.ActionSet, obj);
		this.inputContainer = new Config(ThemeElement.InputContainer, obj);
    }
}

// Each instance of this class holds config of specific element type 
// this class holds config of specific element type 
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
		activeColor: Constants.BlackColor,
		inactiveColor: Constants.LightBlack,
		borderColor: Constants.EmphasisColor,
        backgroundColor: Constants.WhiteColor,
        borderRadius: 5,
        borderWidth: 1
    },
    inputLabel: {
        fontSize: 14,
        fontWeight: '400',
        color: Constants.Grey900
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
        ios: {
            flexDirection: Constants.FlexRow,
            justifyContent: Constants.SpaceBetween,
            alignItems: Constants.FlexEnd,
            borderWidth: 1,
            backgroundColor: Constants.WhiteColor,
            borderColor: Constants.LightGreyColor,
            borderRadius: 5,
        },
        android: {
			flexDirection: Constants.FlexRow,
            justifyContent: Constants.SpaceBetween,
            alignItems: Constants.FlexEnd,
            borderWidth: 1,
            backgroundColor: Constants.WhiteColor,
            borderColor: Constants.LightGreyColor,
            borderRadius: 5,
            backgroundColor: Constants.LightGreyColor,
        },
        windows: {
            flexDirection: Constants.FlexRow,
            justifyContent: Constants.SpaceBetween,
            alignItems: Constants.FlexEnd,
            borderWidth: 1,
            backgroundColor: Constants.WhiteColor,
            borderColor: Constants.LightGreyColor,
            borderRadius: 5,
        }
    },
    dropdownText: {
        color: Constants.BlackColor,
        textAlign: Constants.LeftAlign,
        marginTop: 10,
        marginLeft: 8,
        height: 30,
    },
    picker: {
        borderWidth: 1,
        backgroundColor: Constants.LightGreyColor,
        borderColor: Constants.LightGreyColor,
        color: Constants.BlackColor,
        borderRadius: 5,
        marginHorizontal: 2
    },
    dateTimePicker: {
        backgroundColor: Constants.WhiteColor,
        height: 260,
        width: Constants.FullWidth,
        textColor: Constants.BlackColor
    },
    /// (Input.Toggle) Based on React-Native props of the same name that can be passed to switch.
    switch: {
        trackColor: undefined, /// Object of type {true: color; false: color} (See RN Docs)
        thumbColor: undefined, /// Object of type {true: color; false: color}
        ios_backgroundColor: undefined
    },
    inlineAction: {},
    inlineActionText: {},
	actionSet: {},
	inputContainer: {}
}