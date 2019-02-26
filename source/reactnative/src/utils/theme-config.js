
import * as Constants from '../utils/constants';

export class ThemeConfigManager {

    static themeConfig = null;

	/**
     * @description Return the theme config
	 * @returns {ThemeConfigManager}
	 */
    static getThemeConfig() {
        if (!ThemeConfigManager.themeConfig) {
            ThemeConfigManager.themeConfig = new ThemeConfig(defaultThemeConfig);
        }
        return this.themeConfig;
    }

    /**
     * @description Set the custom theme config property
     * @param {object} value 
     */
    static setThemeConfig(value) {
        let newThemeConfig = { ...defaultThemeConfig, ...value }
        this.themeConfig = new ThemeConfig(newThemeConfig);
        console.log("came here:",this.themeConfig);
    }
}

class ThemeConfig {

    input = inputConfig;
    button = new ButtonConfig();

    constructor(obj) {
        if (obj) {
            this.button = new ButtonConfig(obj.button || this.button);
            this.input = obj["input"] != null ? { ...this.input, ...obj["input"] } : this.input;
        }
    }
}

let inputConfig = {
    borderColor: Constants.LightGreyColor,
    backgroundColor: Constants.WhiteColor,
    borderWidth: 1,
    borderRadius: 5
};

let iosButtonConfig  = {
    borderRadius: 15,
    backgroundColor: "#1D9BF6",
    titleColor: "#FFFFFF"
}

let androidButtonConfig  = {
    borderRadius: 15,
    backgroundColor: "#1D9BF6",
    titleColor: "#FFFFFF"
}

class ButtonConfig {
    ios = iosButtonConfig;
    android = androidButtonConfig;

    constructor(obj) {
        if (obj) {
            this.ios = obj["ios"] != null ? {...this.ios, ...obj["ios"]} : {...this.ios, ...obj};
            this.android = obj["android"] != null ? {...this.android, ...obj["android"]} : {...this.android, ...obj};
        }
    }

}

/**
 * @description Default Theme config JSON. This can be overriden by invoking setThemeConfig method.
 */
export const defaultThemeConfig = {
    button: {
        ios: {
            borderRadius: 15,
            backgroundColor: "#1D9BF6",
            titleColor: "white",
        },
        android: {
            borderRadius: 15,
            backgroundColor: "#1D9BF6",
            titleColor: "white",
        }
    },
    input: {
        borderColor: "#dcdcdc",
        backgroundColor: "white",
        borderRadius: 5,
        borderWidth: 1,
    }
}