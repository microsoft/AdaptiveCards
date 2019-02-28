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

        if (customConfig[type]) { // any custom config ?
            let config = customConfig[type];

            this.ios = config["ios"] ? { ...this.ios, ...config["ios"] } : { ...this.ios, ...config };
            this.android = config["android"] ? { ...this.android, ...config["android"] } : { ...this.android, ...config };
        }
    }
}

/**
 * @description Default Theme config JSON. This can be overriden by invoking setThemeConfig method.
 */
const defaultThemeConfig = {
    button: {
        ios: {
            borderRadius: 15,
            backgroundColor: "#1D9BF6",
            titleColor: "#FFFFFF",
            titleTransform: 'none'
        },
        android: {
            borderRadius: 15,
            backgroundColor: "#1D9BF6",
            titleColor: "#FFFFFF",
            titleTransform: 'none'
        }
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
        }
    }
}