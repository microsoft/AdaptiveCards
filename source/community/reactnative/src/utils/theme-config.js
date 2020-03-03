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
    }
}

class ThemeConfig {
    constructor(obj = {}) {
        this.button = new Config("button", obj);
        this.input = new Config("input", obj);
    }
} 

// Each instance of this class holds config of specific element type 
class Config {
    constructor(type, customConfig = {}) {
        this.type = type;
        this.ios = defaultThemeConfig[type].ios;
        this.android = defaultThemeConfig[type].android;
        this.windows = defaultThemeConfig[type].windows;

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
const defaultThemeConfig = {
    button: {
        ios: {
            borderRadius: 15,
            backgroundColor: "#1D9BF6",
            color: "#FFFFFF",
            textTransform: 'none'
        },
        android: {
            borderRadius: 15,
            backgroundColor: "#1D9BF6",
            color: "#FFFFFF",
            textTransform: undefined
        },
        windows: {
            borderRadius: 15,
            backgroundColor: "#1D9BF6",
            color: "#FFFFFF",
            textTransform: 'none'
        },
    },
    input: {
        ios: {
            borderColor: "#dcdcdc",
            backgroundColor: "#FFFFFF",
            borderRadius: 5,
            borderWidth: 1
        },
        android: {
            borderColor: "#dcdcdc",
            backgroundColor: "#FFFFFF",
            borderRadius: 5,
            borderWidth: 1
        },
        windows: {
            borderColor: "#dcdcdc",
            backgroundColor: "#FFFFFF",
            borderRadius: 5,
            borderWidth: 1
        },
    }
}