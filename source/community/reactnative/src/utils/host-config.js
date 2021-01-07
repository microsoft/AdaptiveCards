import * as Enums from './enums';
import * as Utils from './util';
import * as Constants from '../utils/constants';
import {
	Platform,
} from 'react-native';

export class TextColorDefinition {
	_default = "#000000";
	_subtle = "#666666";

	constructor(obj) {
		if (obj) {
			this._default = obj["default"] || this._default;
			this._subtle = obj["subtle"] || this._subtle;
		}
	}

	get subtle() {
		return Utils.hexToRGB(this._subtle);
	}

	set subtle(color) {
		this._subtle = color;
	}

	get default() {
		return Utils.hexToRGB(this._default);
	}

	set default(color) {
		this._default = color;
	}
	toJSON() {
		return {
			default: this._default,
			subtle: this._subtle
		}
	}
}

export class HostConfigManager {

	static hostConfig = null;

	/**
	 * @returns {HostConfigManager}
	 */
	static getHostConfig() {
		if (HostConfigManager.hostConfig === null) {
			HostConfigManager.hostConfig = new HostConfig(defaultHostConfig);
		}

		return this.hostConfig;
	}

	static setHostConfig(value) {
		this.hostConfig = new HostConfig(value);
	}

	/**
	 * @description Return whether supports interactivity is enabled or not in the host config
	 * @returns {boolean} - true|false based on the hostconfig supportsInteractivity value
	 */
	static supportsInteractivity() {
		return this.getHostConfig().supportsInteractivity;
	}
}

export class AdaptiveCardConfig {
	allowCustomStyle = false;

	constructor(obj) {
		if (obj) {
			this.allowCustomStyle = obj["allowCustomStyle"] || this.allowCustomStyle;
		}
	}
}

export class RichTextBlockConfig {
	highlightColor = "#FFFF00";

	constructor(obj) {
		if (obj) {
			this.highlightColor = obj["highlightColor"] != null ? obj["highlightColor"] : this.highlightColor;
		}
	}

	toJSON() {
		return {
			highlightColor: this.highlightColor
		}
	}
}

export class ImageSetConfig {
	imageSize = Enums.Size.Medium;
	maxImageHeight = 100;

	constructor(obj) {
		if (obj) {
			this.imageSize = obj["imageSize"] != null ? obj["imageSize"] : this.imageSize;
			this.maxImageHeight = obj["maxImageHeight"] || 100;
		}
	}

	toJSON() {
		return {
			imageSize: Enums.Size[this.imageSize],
			maxImageHeight: this.maxImageHeight
		}
	}
}

export class MediaConfig {
	defaultPoster;
	allowInlinePlayback = true;

	constructor(obj) {
		if (obj) {
			this.defaultPoster = obj["defaultPoster"];
			this.allowInlinePlayback = obj["allowInlinePlayback"] || this.allowInlinePlayback;
		}
	}

	toJSON() {
		return {
			defaultPoster: this.defaultPoster,
			allowInlinePlayback: this.allowInlinePlayback
		}
	}
}

export class FactTextDefinition {
	size = Enums.TextSize.Default;
	color = Enums.TextColor.Default;;
	isSubtle = false;
	weight = Enums.TextWeight.Default;
	wrap = true;

	constructor(obj) {
		if (obj) {
			this.size = Utils.parseHostConfigEnum(Enums.TextSize, obj["size"], Enums.TextSize.Default);
			this.color = Utils.parseHostConfigEnum(Enums.TextColor, obj["color"], Enums.TextColor.Default);
			this.isSubtle = obj["isSubtle"] || this.isSubtle;
			this.weight = Utils.parseHostConfigEnum(Enums.TextWeight, obj["weight"], this.getDefaultWeight());
			this.wrap = obj["wrap"] != null ? obj["wrap"] : this.wrap;
		}
	}

	getDefaultWeight() {
		return Enums.TextWeight.Default;
	}

	toJSON() {
		return {
			size: Enums.TextSize[this.size],
			color: Enums.TextColor[this.color],
			isSubtle: this.isSubtle,
			weight: Enums.TextWeight[this.weight],
			wrap: this.wrap
		}
	}
}

export class FactTitleDefinition extends FactTextDefinition {
	weight = Enums.TextWeight.Bolder;
	size = Enums.TextSize.Default;
	color = Enums.TextColor.Default;;
	isSubtle = false;
	wrap = true;

	constructor(obj) {
		super(obj);

		if (obj) {
			this.maxWidth = obj["maxWidth"] != null ? obj["maxWidth"] : this.maxWidth;
			this.size = Utils.parseHostConfigEnum(Enums.TextSize, obj["size"], Enums.TextSize.Default);
			this.color = Utils.parseHostConfigEnum(Enums.TextColor, obj["color"], Enums.TextColor.Default);
			this.isSubtle = obj["isSubtle"] || this.isSubtle;
			this.weight = Utils.parseHostConfigEnum(Enums.TextWeight, obj["weight"], this.getDefaultWeight());
			this.wrap = obj["wrap"] != null ? obj["wrap"] : this.wrap;
		}
	}

	getDefaultWeight() {
		return Enums.TextWeight.Bolder;
	}
}

export class FactSetConfig {
	title = new FactTitleDefinition();
	value = new FactTextDefinition();
	spacing = 10;

	constructor(obj) {
		if (obj) {
			this.title = new FactTitleDefinition(obj["title"]);
			this.value = new FactTextDefinition(obj["value"]);
			this.spacing = (obj['spacing'] != null) ? obj['spacing'] : this.spacing;
		}
	}
}

export class ShowCardActionConfig {
	actionMode = Enums.ShowCardActionMode.Inline;
	inlineTopMargin = 16;
	style = Enums.ContainerStyle.Emphasis;

	constructor(obj) {
		if (obj) {
			this.actionMode = Utils.parseHostConfigEnum(Enums.ShowCardActionMode, obj["actionMode"], Enums.ShowCardActionMode.Inline);
			this.inlineTopMargin = obj["inlineTopMargin"] != null ? obj["inlineTopMargin"] : this.inlineTopMargin;
			this.style = obj["style"] && typeof obj["style"] === "string" ? obj["style"] : Enums.ContainerStyle.Emphasis;
		}
	}

	toJSON() {
		return {
			actionMode: Enums.ShowCardActionMode[this.actionMode],
			inlineTopMargin: this.inlineTopMargin,
			style: this.style
		}
	}
}

export class ActionsConfig {
	maxActions = 5;
	spacing = Enums.Spacing.Default;
	buttonSpacing = 10;
	showCard = new ShowCardActionConfig();
	preExpandSingleShowCardAction = false;
	actionsOrientation = Enums.Orientation.Horizontal;
	actionAlignment = Enums.ActionAlignment.Left;
	iconPlacement = Enums.ActionIconPlacement.LeftOfTitle;
	allowTitleToWrap = false;
	iconSize = 24;

	constructor(obj) {
		if (obj) {
			this.maxActions = obj["maxActions"] != null ? obj["maxActions"] : this.maxActions;
			this.spacing = Utils.parseHostConfigEnum(Enums.Spacing, obj.spacing && obj.spacing, Enums.Spacing.Default);
			this.buttonSpacing = obj["buttonSpacing"] != null ? obj["buttonSpacing"] : this.buttonSpacing;
			this.showCard = new ShowCardActionConfig(obj["showCard"]);
			this.preExpandSingleShowCardAction = Utils.getValueOrDefault(obj["preExpandSingleShowCardAction"], false);
			this.actionsOrientation = Utils.parseHostConfigEnum(Enums.Orientation, obj["actionsOrientation"], Enums.Orientation.Horizontal);
			this.actionAlignment = Utils.parseHostConfigEnum(Enums.ActionAlignment, obj["actionAlignment"], Enums.ActionAlignment.Left);
			this.iconPlacement = Utils.parseHostConfigEnum(Enums.ActionIconPlacement, obj["iconPlacement"], Enums.ActionIconPlacement.LeftOfTitle);
			this.allowTitleToWrap = obj["allowTitleToWrap"] != null ? obj["allowTitleToWrap"] : this.allowTitleToWrap;

			try {
				let sizeAndUnit = Utils.SizeAndUnit.parse(obj["iconSize"]);

				if (sizeAndUnit.unit == Enums.SizeUnit.Pixel) {
					this.iconSize = sizeAndUnit.physicalSize;
				}
			}
			catch (e) {
				// Swallow this, keep default icon size
			}
		}
	}

	toJSON() {
		return {
			maxActions: this.maxActions,
			spacing: Enums.Spacing[this.spacing],
			buttonSpacing: this.buttonSpacing,
			showCard: this.showCard,
			preExpandSingleShowCardAction: this.preExpandSingleShowCardAction,
			actionsOrientation: Enums.Orientation[this.actionsOrientation],
			actionAlignment: Enums.ActionAlignment[this.actionAlignment]
		}
	}
}

export class ContainerStyleDefinition {
	getTextColorDefinition(value) {
		return new TextColorDefinition(value);
	}

	borderColor;
	borderThickness;
	backgroundColor;
	foregroundColors = {
		default: new TextColorDefinition(),
		accent: new TextColorDefinition(),
		good: new TextColorDefinition(),
		warning: new TextColorDefinition(),
		attention: new TextColorDefinition(),
		dark: new TextColorDefinition(),
		light: new TextColorDefinition()
	};

	parse(obj, type) {
		this.borderColor = defaultHostConfig["containerStyles"][type]["borderColor"];
		this.borderThickness = defaultHostConfig["containerStyles"][type]["borderThickness"];
		this.backgroundColor = defaultHostConfig["containerStyles"][type]["backgroundColor"];
		this.foregroundColors.default = this.getTextColorDefinition(defaultHostConfig["containerStyles"][type].foregroundColors["default"]);
		this.foregroundColors.accent = this.getTextColorDefinition(defaultHostConfig["containerStyles"][type].foregroundColors["accent"]);
		this.foregroundColors.good = this.getTextColorDefinition(defaultHostConfig["containerStyles"][type].foregroundColors["good"]);
		this.foregroundColors.warning = this.getTextColorDefinition(defaultHostConfig["containerStyles"][type].foregroundColors["warning"]);
		this.foregroundColors.attention = this.getTextColorDefinition(defaultHostConfig["containerStyles"][type].foregroundColors["attention"]);
		this.foregroundColors.dark = this.getTextColorDefinition(defaultHostConfig["containerStyles"][type].foregroundColors["dark"]);
		this.foregroundColors.light = this.getTextColorDefinition(defaultHostConfig["containerStyles"][type].foregroundColors["light"]);

		if (obj && obj[type]) {
			this.backgroundColor = obj[type]["backgroundColor"] ? obj[type]["backgroundColor"] : this.backgroundColor;
			this.borderColor = obj[type]["borderColor"] ? obj[type]["borderColor"] : this.borderColor;
			this.borderThickness = obj[type]["borderThickness"] ? obj[type]["borderThickness"] : this.borderThickness;
			if (obj[type]["foregroundColors"]) {
				this.foregroundColors.default = this.getTextColorDefinition(obj[type].foregroundColors["default"], this.foregroundColors.default.toJSON);
				this.foregroundColors.accent = this.getTextColorDefinition(obj[type].foregroundColors["accent"], this.foregroundColors.accent.toJSON);
				this.foregroundColors.good = this.getTextColorDefinition(obj[type].foregroundColors["good"], this.foregroundColors.good.toJSON);
				this.foregroundColors.warning = this.getTextColorDefinition(obj[type].foregroundColors["warning"], this.foregroundColors.warning.toJSON);
				this.foregroundColors.attention = this.getTextColorDefinition(obj[type].foregroundColors["attention"], this.foregroundColors.attention.toJSON);
				this.foregroundColors.dark = this.getTextColorDefinition(obj[type].foregroundColors["dark"], this.foregroundColors.dark.toJSON);
				this.foregroundColors.light = this.getTextColorDefinition(obj[type].foregroundColors["light"], this.foregroundColors.light.toJSON);
			}
		}
	}

	constructor(obj, type) {
		this.parse(obj, type);
	}

	get isBuiltIn() {
		return false;
	}
}

export class ContainerStyleSet {
	_allStyles = {};

	constructor(obj) {
		this._allStyles[Enums.ContainerStyle.Default] = new ContainerStyleDefinition(obj, Enums.ContainerStyle.Default);
		this._allStyles[Enums.ContainerStyle.Emphasis] = new ContainerStyleDefinition(obj, Enums.ContainerStyle.Emphasis);
		this._allStyles[Enums.ContainerStyle.Accent] = new ContainerStyleDefinition(obj, Enums.ContainerStyle.Accent);
		this._allStyles[Enums.ContainerStyle.Good] = new ContainerStyleDefinition(obj, Enums.ContainerStyle.Good);
		this._allStyles[Enums.ContainerStyle.Attention] = new ContainerStyleDefinition(obj, Enums.ContainerStyle.Attention);
		this._allStyles[Enums.ContainerStyle.Warning] = new ContainerStyleDefinition(obj, Enums.ContainerStyle.Warning);
	}

	toJSON() {
		var customStyleArray = [];

		Object.keys(this._allStyles).forEach(
			(key) => {
				if (!this._allStyles[key].isBuiltIn) {
					customStyleArray.push({
						name: key,
						style: this._allStyles[key]
					});
				}
			});

		var result = {
			default: this.default,
			emphasis: this.emphasis
		}

		if (customStyleArray.length > 0) {
			result.customStyles = customStyleArray;
		}

		return result;
	}

	getStyleByName(name, defaultValue = null) {
		return this._allStyles.hasOwnProperty(name) ? this._allStyles[name] : defaultValue;
	}

	get default() {
		return this._allStyles[Enums.ContainerStyle.Default];
	}

	get emphasis() {
		return this._allStyles[Enums.ContainerStyle.Emphasis];
	}
}


class FontStyleConfig {
	constructor(obj = {}) {
		this.default = new FontConfig("default", obj);
		this.monospace = new FontConfig("monospace", obj);
	}
}
/* Each instance of this class holds config of specific FontStyle type 
 customConfigFontFamily, customConfigWeights, customConfigFontSizes are deprecated and will be removed in future. */
class FontConfig {
	constructor(type, customConfig = {}) {
		this.type = type;
		let defaultFontStyles = defaultHostConfig["fontStyles"];
		this.fontFamily = defaultFontStyles[type].fontFamily;
		this.fontSizes = defaultFontStyles[type].fontSizes;
		this.fontWeights = defaultFontStyles[type].fontWeights;


		if (!Utils.isNullOrEmpty(customConfig[type])) { // any custom config ?
			let config = customConfig[type];
			if (type === "monospace") {
				this.fontFamily = (Platform.OS === Constants.PlatformAndroid) ? "monospace" : "Courier New";
			}
			else {
				this.fontFamily = config["fontFamily"] ? config["fontFamily"] : this.fontFamily;
			}
			this.fontSizes = config["fontSizes"] ? { ...this.fontSizes, ...config["fontSizes"] } : this.fontSizes;
			this.fontWeights = config["fontWeights"] ? { ...this.fontWeights, ...config["fontWeights"] } : this.fontWeights;
		}
		else if (!Utils.isNullOrEmpty(customConfig["fontFamily"])) {
			this.fontFamily = customConfig["fontFamily"];
		}
		else if (!Utils.isNullOrEmpty(customConfig["fontWeights"])) {
			this.fontWeights = customConfig["fontWeights"];
		}
		else if (!Utils.isNullOrEmpty(customConfig["fontSizes"])) {
			this.fontSizes = customConfig["fontSizes"];
		}
	}
}

export class HostConfig {
	choiceSetInputValueSeparator = ",";
	supportsInteractivity = true;
	lineHeights;

	fontFamily = "Helvetica";

	spacing = {
		none: 0,
		small: 3,
		default: 8,
		medium: 20,
		large: 30,
		extraLarge: 40,
		padding: 5
	};

	separator = {
		lineThickness: 1,
		lineColor: "#A9A9A9"
	};

	fontSizes = {
		small: 12,
		default: 14,
		medium: 17,
		large: 21,
		extraLarge: 26
	};
	horizontalAlignment = {
		left: "left",
		center: "center",
		right: "right"
	};
	fontWeights = {
		lighter: 200,
		default: 400,
		bolder: 600
	};
	imageSizes = {
		small: 40,
		medium: 80,
		large: 160
	};

	height = {
		auto: 0,
		stretch: 1
	};

	richTextBlock = {
		highlightColor: "#00FF00"
	};

	fontStyles = {
		default: {
			fontFamily: "Helvetica",
			fontSizes: {
				small: 12,
				default: 14,
				medium: 17,
				large: 21,
				extraLarge: 26
			},
			fontWeights: {
				lighter: 200,
				default: 400,
				bolder: 700
			}
		},
		monospace: {
			fontFamily: "Courier New",
			fontSizes: {
				small: 12,
				default: 14,
				medium: 17,
				large: 21,
				extraLarge: 26
			},
			fontWeights: {
				lighter: 200,
				default: 400,
				bolder: 700
			}
		}
	};

	containerStyles = new ContainerStyleSet();
	actions = new ActionsConfig();
	adaptiveCard = new AdaptiveCardConfig();
	richTextBlock = new RichTextBlockConfig();
	imageSet = new ImageSetConfig();
	media = new MediaConfig();
	factSet = new FactSetConfig();
	fontStyles = new FontStyleConfig();

	hostCapabilities = new HostCapabilities()
	cssClassNamePrefix = null;

	constructor(obj) {
		if (obj) {
			if (typeof obj === "string" || obj instanceof String) {
				obj = JSON.parse(obj);
			}
			this.choiceSetInputValueSeparator = (obj && typeof obj["choiceSetInputValueSeparator"] === "string") ? obj["choiceSetInputValueSeparator"] : this.choiceSetInputValueSeparator;
			this.supportsInteractivity = (obj && typeof obj["supportsInteractivity"] === "boolean") ? obj["supportsInteractivity"] : this.supportsInteractivity;
			this.fontFamily = obj["fontFamily"] || this.fontFamily;
			this.fontSizes = {
				small: obj.fontSizes && obj.fontSizes["small"] || this.fontSizes.small,
				default: obj.fontSizes && obj.fontSizes["default"] || this.fontSizes.default,
				medium: obj.fontSizes && obj.fontSizes["medium"] || this.fontSizes.medium,
				large: obj.fontSizes && obj.fontSizes["large"] || this.fontSizes.large,
				extraLarge: obj.fontSizes && obj.fontSizes["extraLarge"] || this.fontSizes.extraLarge
			};

			if (obj.lineHeights) {
				this.lineHeights = {
					small: obj.lineHeights["small"],
					default: obj.lineHeights["default"],
					medium: obj.lineHeights["medium"],
					large: obj.lineHeights["large"],
					extraLarge: obj.lineHeights["extraLarge"]
				};
			};

			this.fontWeights = {
				lighter: obj.fontWeights && obj.fontWeights["lighter"] || this.fontWeights.lighter,
				default: obj.fontWeights && obj.fontWeights["default"] || this.fontWeights.default,
				bolder: obj.fontWeights && obj.fontWeights["bolder"] || this.fontWeights.bolder
			};

			this.imageSizes = {
				small: obj.imageSizes && obj.imageSizes["small"] || this.imageSizes.small,
				medium: obj.imageSizes && obj.imageSizes["medium"] || this.imageSizes.medium,
				large: obj.imageSizes && obj.imageSizes["large"] || this.imageSizes.large,
			};

			this.containerStyles = new ContainerStyleSet(obj["containerStyles"]);
			this.spacing = {
				none: obj.spacing && obj.spacing["none"] || this.spacing.none,
				small: obj.spacing && obj.spacing["small"] || this.spacing.small,
				default: obj.spacing && obj.spacing["default"] || this.spacing.default,
				medium: obj.spacing && obj.spacing["medium"] || this.spacing.medium,
				large: obj.spacing && obj.spacing["large"] || this.spacing.large,
				extraLarge: obj.spacing && obj.spacing["extraLarge"] || this.spacing.extraLarge,
				padding: obj.spacing && obj.spacing["padding"] || this.spacing.padding
			};

			this.separator = {
				lineThickness: obj.separator && obj.separator["lineThickness"] || this.separator.lineThickness,
				lineColor: obj.separator && obj.separator["lineColor"] || this.separator.lineColor
			}

			this.actions = new ActionsConfig(obj.actions || this.actions);
			this.adaptiveCard = new AdaptiveCardConfig(obj.adaptiveCard || this.adaptiveCard);
			this.richTextBlock = new RichTextBlockConfig(obj["richTextBlock"]);
			this.imageSet = new ImageSetConfig(obj["imageSet"]);
			this.factSet = new FactSetConfig(obj["factSet"]);
			this.fontStyles = new FontStyleConfig(obj);
			this.hostCapabilities = new HostCapabilities(obj.hostCapabilities)
		}
	}

	/**
	 * @param {string} spacing 
	 */
	getEffectiveSpacing = (spacing) => {
		switch (spacing) {
			case Enums.Spacing.None:
				return this.spacing.none;
			case Enums.Spacing.Small:
				return this.spacing.small;
			case Enums.Spacing.Default:
				return this.spacing.default;
			case Enums.Spacing.Medium:
				return this.spacing.medium;
			case Enums.Spacing.Large:
				return this.spacing.large;
			case Enums.Spacing.ExtraLarge:
				return this.spacing.extraLarge;
			case Enums.Spacing.Padding:
				return this.spacing.padding;
			default:
				return this.spacing.small;
		}
	}

	/**
	 * @param {string} fontStyle 
	 */
	getTextFontStyle = (fontStyle) => {

		switch (fontStyle) {
			case Enums.FontStyle.Default:
				return this.fontStyles.default;
			case Enums.FontStyle.Monospace:
				return this.fontStyles.monospace;
			default:
				return this.fontStyles.default;
		}
	}

	/**
	 * @param {string} fontSize 
	 */
	getTextFontSize = (fontSize, fontStyle) => {

		switch (fontSize) {
			case Enums.TextSize.Small:
				return fontStyle.fontSizes.small;
			case Enums.TextSize.Default:
				return fontStyle.fontSizes.default;
			case Enums.TextSize.Medium:
				return fontStyle.fontSizes.medium;
			case Enums.TextSize.Large:
				return fontStyle.fontSizes.large;
			case Enums.TextSize.ExtraLarge:
				return fontStyle.fontSizes.extraLarge;
			default:
				return fontStyle.fontSizes.default;
		}
	}

	/**
	 * @param {string} weight
	 */
	getTextFontWeight = (weight, fontStyle) => {
		switch (weight) {
			case Enums.TextWeight.Lighter:
				return fontStyle.fontWeights.lighter;
			case Enums.TextWeight.Default:
				return fontStyle.fontWeights.default;
			case Enums.TextWeight.Bolder:
				return fontStyle.fontWeights.bolder;
			default:
				return fontStyle.fontWeights.default;
		}
	}

	/**
	 * @param {string} color
	 */
	getTextColor = (color) => {
		switch (color) {
			case Enums.TextColor.Attention:
				return this.containerStyles.default.foregroundColors.attention;
			case Enums.TextColor.Dark:
				return this.containerStyles.default.foregroundColors.dark;
			case Enums.TextColor.Light:
				return this.containerStyles.default.foregroundColors.light;
			case Enums.TextColor.Accent:
				return this.containerStyles.default.foregroundColors.accent;
			case Enums.TextColor.Good:
				return this.containerStyles.default.foregroundColors.good;
			case Enums.TextColor.Warning:
				return this.containerStyles.default.foregroundColors.warning;
			case Enums.TextColor.Default:
				return this.containerStyles.default.foregroundColors.default;
			default:
				return this.containerStyles.default.foregroundColors.default;
		}
	}

	/**
	 * @description Return the color definition for the given color in associated container style
	 * @param {Enums.TextColor} color
	 * @param {string} style
	 */
	getTextColorForStyle = (color, style) => {
		switch (color) {
			case Enums.TextColor.Attention:
				return this.containerStyles.getStyleByName(style, "default").foregroundColors.attention;
			case Enums.TextColor.Dark:
				return this.containerStyles.getStyleByName(style, "default").foregroundColors.dark;
			case Enums.TextColor.Light:
				return this.containerStyles.getStyleByName(style, "default").foregroundColors.light;
			case Enums.TextColor.Accent:
				return this.containerStyles.getStyleByName(style, "default").foregroundColors.accent;
			case Enums.TextColor.Good:
				return this.containerStyles.getStyleByName(style, "default").foregroundColors.good;
			case Enums.TextColor.Warning:
				return this.containerStyles.getStyleByName(style, "default").foregroundColors.warning;
			case Enums.TextColor.Default:
			default:
				return this.containerStyles.getStyleByName(style, "default").foregroundColors.default;
		}
	}

	/**
	 * @param {string} alignment
	 */
	getTextAlignment = (alignment) => {
		switch (alignment) {
			case Enums.HorizontalAlignment.Left:
				return this.horizontalAlignment.left;
			case Enums.HorizontalAlignment.Center:
				return this.horizontalAlignment.center;
			case Enums.HorizontalAlignment.Right:
				return this.horizontalAlignment.right;

			default:
				return this.horizontalAlignment.left;
		}
	}

	getEffectiveHeight = (height) => {
		switch (height) {
			case Enums.Height.Auto:
				return this.height.auto;
			case Enums.Height.Stretch:
				return this.height.stretch;
			default:
				return this.height.auto;
		}
	}

	getHostCapabilities = () => {
		return this.hostCapabilities
	}
}

export class HostCapabilities {
	capabilities = {}
	setCapability(name, version) {
		this.capabilities[name] = version
	}

	constructor(capabilities) {
		if(capabilities) {
			for(let capability in capabilities) {
				let version = new Version(capabilities[capability])
				if(version.isValid) {
					this.setCapability(capability, version)
				}
			}
		}
	}

	satisfied = (capabilities) => {
		for(let capability in this.capabilities) {
			let satisfied = capabilities.hasCapability(capability, this.capabilities[capability])
			if(!satisfied) {
				return false
			}
		}
		return true
	}

	hasCapability = (capability, version) => {
		if (this.capabilities.hasOwnProperty(capability)) {
			if(version.version == "*") {
				return true;
			} else {
				return version.compareTo(this.capabilities[capability]) <= 0;
			}
		} else {
			return false
		}
	}
}

export class Version {
	version = null
	major = 1
	minor = 1
	isValid = true

	constructor(version) {
		this.version = version
		let regEx = /(\d+).(\d+)/gi;
		let matches = regEx.exec(this.version);
		if (matches != null && matches.length == 3) {
			this.major = parseInt(matches[1])
			this.minor = parseInt(matches[2])
		} else if(version != '*') {
			this.isValid = false
		}
	}

	compareTo(other) {
        if (!this.isValid || !other.isValid) {
            return 1
        }
 		if (this.major > other.major) {
            return 1;
        } else if (this.major < other.major) {
            return -1;
        } else if (this.minor > other.minor) {
            return 1; 
        } else if (this.minor < other.minor) {
            return -1;
        }
        return 0;
    }
}

export const defaultHostConfig = {
	supportsInteractivity: true,
	richTextBlock: {
		highlightColor: "#00FF00"
	},
	fontStyles: {
		default: {
			fontFamily: "Helvetica",
			fontSizes: {
				small: 12,
				default: 14,
				medium: 17,
				large: 21,
				extraLarge: 26
			},
			fontWeights: {
				lighter: 200,
				default: 400,
				bolder: 700
			}
		},
		monospace: {
			fontFamily: "Courier New",
			fontSizes: {
				small: 12,
				default: 14,
				medium: 17,
				large: 21,
				extraLarge: 26
			},
			fontWeights: {
				lighter: 200,
				default: 400,
				bolder: 700
			}
		}
	},
	spacing: {
		none: 0,
		small: 3,
		default: 8,
		medium: 20,
		large: 30,
		extraLarge: 40,
		padding: 10
	},
	separator: {
		lineThickness: 1,
		lineColor: "#D9D9D9"
	},
	imageSizes: {
		small: 40,
		medium: 80,
		large: 160
	},
	containerStyles: {
		default: {
			"backgroundColor": "#EAEAEA",
			"foregroundColors": {
				"default": {
					"default": "#333333",
					"subtle": "#EE333333"
				},
				"accent": {
					"default": "#2E89FC",
					"subtle": "#882E89FC"
				},
				"good": {
					"default": "#54A254",
					"subtle": "#DD54A254"
				},
				"warning": {
					"default": "#C3AB23",
					"subtle": "#DDC3AB23"
				},
				"attention": {
					"default": "#FF0000",
					"subtle": "#DDFF0000"
				},
				"dark": {
					"default": "#000000",
					"subtle": "#EE333333"
				},
				"light": {
					"default": "#FFFFFF",
					"subtle": "#DDFFFFFF"
				}
			}
		},
		emphasis: {
			"backgroundColor": "#08000000",
			"borderColor": "#FF000000",
			"borderThickness": 2,
			"foregroundColors": {
				"default": {
					"default": "#333333",
					"subtle": "#EE333333"
				},
				"accent": {
					"default": "#2E89FC",
					"subtle": "#882E89FC"
				},
				"good": {
					"default": "#54A254",
					"subtle": "#DD54A254"
				},
				"warning": {
					"default": "#C3AB23",
					"subtle": "#DDC3AB23"
				},
				"attention": {
					"default": "#FF0000",
					"subtle": "#DDFF0000"
				},
				"dark": {
					"default": "#000000",
					"subtle": "#EE333333"
				},
				"light": {
					"default": "#FFFFFF",
					"subtle": "#DDFFFFFF"
				}
			}
		},
		good: {
			"backgroundColor": "#DD54A254",
			"foregroundColors": {
				"default": {
					"default": "#333333",
					"subtle": "#EE333333"
				},
				"accent": {
					"default": "#2E89FC",
					"subtle": "#882E89FC"
				},
				"good": {
					"default": "#54A254",
					"subtle": "#DD54A254"
				},
				"warning": {
					"default": "#C3AB23",
					"subtle": "#DDC3AB23"
				},
				"attention": {
					"default": "#FF0000",
					"subtle": "#DDFF0000"
				},
				"dark": {
					"default": "#000000",
					"subtle": "#EE333333"
				},
				"light": {
					"default": "#FFFFFF",
					"subtle": "#DDFFFFFF"
				}
			},
		},
		warning: {
			"backgroundColor": "#DDFF0000",
			"borderColor": "#FF000000",
			"borderThickness": 2,
			"foregroundColors": {
				"default": {
					"default": "#FFFFFF",
					"subtle": "#EE333333"
				},
				"accent": {
					"default": "#FFFFFF",
					"subtle": "#882E89FC"
				},
				"good": {
					"default": "#FFFFFF",
					"subtle": "#DD54A254"
				},
				"warning": {
					"default": "#FFFFFF",
					"subtle": "#DDC3AB23"
				},
				"attention": {
					"default": "#FFFFFF",
					"subtle": "#DDFF0000"
				},
				"dark": {
					"default": "#000000",
					"subtle": "#EE333333"
				},
				"light": {
					"default": "#FFFFFF",
					"subtle": "#DDFFFFFF"
				}
			},
		},
		attention: {
			"backgroundColor": "#DDC3AB23",
			"foregroundColors": {
				"default": {
					"default": "#333333",
					"subtle": "#EE333333"
				},
				"accent": {
					"default": "#2E89FC",
					"subtle": "#882E89FC"
				},
				"good": {
					"default": "#54A254",
					"subtle": "#DD54A254"
				},
				"warning": {
					"default": "#C3AB23",
					"subtle": "#DDC3AB23"
				},
				"attention": {
					"default": "#FF0000",
					"subtle": "#DDFF0000"
				},
				"dark": {
					"default": "#000000",
					"subtle": "#EE333333"
				},
				"light": {
					"default": "#FFFFFF",
					"subtle": "#DDFFFFFF"
				}
			}
		},
		accent: {
			"backgroundColor": "#882E89FC",
			"foregroundColors": {
				"default": {
					"default": "#333333",
					"subtle": "#EE333333"
				},
				"accent": {
					"default": "#2E89FC",
					"subtle": "#882E89FC"
				},
				"good": {
					"default": "#54A254",
					"subtle": "#DD54A254"
				},
				"warning": {
					"default": "#C3AB23",
					"subtle": "#DDC3AB23"
				},
				"attention": {
					"default": "#FF0000",
					"subtle": "#DDFF0000"
				},
				"dark": {
					"default": "#000000",
					"subtle": "#EE333333"
				},
				"light": {
					"default": "#FFFFFF",
					"subtle": "#DDFFFFFF"
				}
			}
		},
		dark: {
			"backgroundColor": "#EAEAEA",
			"foregroundColors": {
				"default": {
					"default": "#333333",
					"subtle": "#EE333333"
				},
				"accent": {
					"default": "#2E89FC",
					"subtle": "#882E89FC"
				},
				"good": {
					"default": "#54A254",
					"subtle": "#DD54A254"
				},
				"warning": {
					"default": "#C3AB23",
					"subtle": "#DDC3AB23"
				},
				"attention": {
					"default": "#FF0000",
					"subtle": "#DDFF0000"
				},
				"dark": {
					"default": "#000000",
					"subtle": "#EE333333"
				},
				"light": {
					"default": "#FFFFFF",
					"subtle": "#DDFFFFFF"
				}
			}
		},
		light: {
			"backgroundColor": "#EAEAEA",
			"foregroundColors": {
				"default": {
					"default": "#FFFFFF",
					"subtle": "#EE333333"
				},
				"accent": {
					"default": "#2E89FC",
					"subtle": "#882E89FC"
				},
				"good": {
					"default": "#54A254",
					"subtle": "#DD54A254"
				},
				"warning": {
					"default": "#C3AB23",
					"subtle": "#DDC3AB23"
				},
				"attention": {
					"default": "#FF0000",
					"subtle": "#DDFF0000"
				},
				"dark": {
					"default": "#000000",
					"subtle": "#EE333333"
				},
				"light": {
					"default": "#FFFFFF",
					"subtle": "#DDFFFFFF"
				}
			}
		}
	},
	actions: {
		maxActions: 5,
		spacing: Enums.Spacing.Default,
		buttonSpacing: 10,
		showCard: {
			actionMode: Enums.ShowCardActionMode.Inline,
			inlineTopMargin: 16
		},
		actionsOrientation: Enums.Orientation.Horizontal,
		actionAlignment: Enums.ActionAlignment.Left
	},
	adaptiveCard: {
		allowCustomStyle: false
	},
	imageSet: {
		imageSize: Enums.Size.Medium,
		maxImageHeight: 100
	},
	factSet: {
		title: {
			color: Enums.TextColor.Default,
			size: Enums.TextSize.Default,
			isSubtle: false,
			weight: Enums.TextWeight.Bolder,
			wrap: true,
		},
		value: {
			color: Enums.TextColor.Default,
			size: Enums.TextSize.Default,
			isSubtle: false,
			weight: Enums.TextWeight.Default,
			wrap: true,
		},
		spacing: 10
	}
}