import * as Enums from './enums';
import * as Utils from './util';

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
		return this.hexTorgb(this._subtle);
	}

	set subtle(color) {
		this._subtle = color;
	}

	get default() {
		return this.hexTorgb(this._default);
	}

	set default(color) {
		this._default = color;
	}

    /**
     * argb in hex to css rgba
     */
	hexTorgb(color) {
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
		newHostConfig = { ...defaultHostConfig, ...value }
		this.hostConfig = new HostConfig(newHostConfig);
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
	maxWidth = 150;
	weight = Enums.TextWeight.Bolder;

	constructor(obj) {
		super(obj);

		if (obj) {
			this.maxWidth = obj["maxWidth"] != null ? obj["maxWidth"] : this.maxWidth;
			this.weight = Utils.parseHostConfigEnum(Enums.TextWeight, obj["weight"], Enums.TextWeight.Bolder);
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
	buttonSpacing = 20;
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
	getTextColorDefinitionOrDefault(obj, defaultValue) {
		return new TextColorDefinition(obj ? obj : defaultValue);
	}

	backgroundColor;

	foregroundColors = {
		default: new TextColorDefinition(),
		dark: new TextColorDefinition(),
		light: new TextColorDefinition(),
		accent: new TextColorDefinition(),
		good: new TextColorDefinition(),
		warning: new TextColorDefinition(),
		attention: new TextColorDefinition()
	};

	parse(obj) {
		if (obj) {
			this.backgroundColor = obj["backgroundColor"];

			if (obj.foregroundColors) {
				this.foregroundColors.default = this.getTextColorDefinitionOrDefault(obj.foregroundColors["default"], { default: "#333333", subtle: "#EE333333" });
				this.foregroundColors.dark = this.getTextColorDefinitionOrDefault(obj.foregroundColors["dark"], { default: "#000000", subtle: "#66000000" });
				this.foregroundColors.light = this.getTextColorDefinitionOrDefault(obj.foregroundColors["light"], { default: "#FFFFFF", subtle: "#33000000" });
				this.foregroundColors.accent = this.getTextColorDefinitionOrDefault(obj.foregroundColors["accent"], { default: "#2E89FC", subtle: "#882E89FC" });
				this.foregroundColors.good = this.getTextColorDefinitionOrDefault(obj.foregroundColors["good"], { default: "#54A254", subtle: "#DD54A254" });
				this.foregroundColors.warning = this.getTextColorDefinitionOrDefault(obj.foregroundColors["warning"], { default: "#E69500", subtle: "#DDE69500" });
				this.foregroundColors.attention = this.getTextColorDefinitionOrDefault(obj.foregroundColors["attention"], { default: "#CC3300", subtle: "#DDCC3300" });
			}
		}
	}

	constructor(obj) {
		this.parse(obj);
	}

	get isBuiltIn() {
		return false;
	}
}

class BuiltInContainerStyleDefinition extends ContainerStyleDefinition {
	get isBuiltIn() {
		return true;
	}
}

export class ILineHeightDefinitions {
	small;
	medium;
	default;
	large;
	extraLarge;
}

export class ContainerStyleSet {
	_allStyles = {};

	constructor(obj) {
		this._allStyles[Enums.ContainerStyle.Default] = new BuiltInContainerStyleDefinition();
		this._allStyles[Enums.ContainerStyle.Emphasis] = new BuiltInContainerStyleDefinition();

		if (obj) {
			this._allStyles[Enums.ContainerStyle.Default].parse(obj[Enums.ContainerStyle.Default]);
			this._allStyles[Enums.ContainerStyle.Emphasis].parse(obj[Enums.ContainerStyle.Emphasis]);

			const customStyleArray = obj["customStyles"];

			if (customStyleArray && Array.isArray(customStyleArray)) {
				for (var customStyle of customStyleArray) {
					if (customStyle) {
						var styleName = customStyle["name"];

						if (styleName && typeof styleName === "string") {
							if (this._allStyles.hasOwnProperty(styleName)) {
								this._allStyles[styleName].parse(customStyle["style"]);
							}
							else {
								this._allStyles[styleName] = new ContainerStyleDefinition(customStyle["style"]);
							}
						}
					}
				}
			}
		}
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

export class HostConfig {
	choiceSetInputValueSeparator = ",";
	supportsInteractivity = true;
	lineHeights;

	fontFamily = "Segoe UI,Segoe,Segoe WP,Helvetica Neue,Helvetica,sans-serif";

	spacing = {
		none: 0,
		small: 3,
		default: 8,
		medium: 20,
		large: 30,
		extraLarge: 40,
		padding: 15
	};

	separator = {
		lineThickness: 1,
		lineColor: "#EEEEEE"
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

	containerStyles = new ContainerStyleSet();
	actions = new ActionsConfig();
	adaptiveCard = new AdaptiveCardConfig();
	imageSet = new ImageSetConfig();
	media = new MediaConfig();
	factSet = new FactSetConfig();

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
			this.imageSet = new ImageSetConfig(obj["imageSet"]);
			this.factSet = new FactSetConfig(obj["factSet"])
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
	 * @param {string} fontSize 
	 */
	getTextFontSize = (fontSize) => {
		switch (fontSize) {
			case Enums.TextSize.Small:
				return this.fontSizes.small;
			case Enums.TextSize.Default:
				return this.fontSizes.default;
			case Enums.TextSize.Medium:
				return this.fontSizes.medium;
			case Enums.TextSize.Large:
				return this.fontSizes.large;
			case Enums.TextSize.ExtraLarge:
				return this.fontSizes.extraLarge;

			default:
				return this.fontSizes.default;
		}
	}

	/**
	 * @param {string} weight
	 */
	getTextFontWeight = (weight) => {
		switch (weight) {
			case Enums.TextWeight.Lighter:
				return this.fontWeights.lighter;
			case Enums.TextWeight.Default:
				return this.fontWeights.default;
			case Enums.TextWeight.Bolder:
				return this.fontWeights.bolder;

			default:
				return this.fontWeights.default;
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

	makeCssClassName = (...classNames) => {
		let result = "";

		for (let i = 0; i < classNames.length; i++) {
			if (i > 0) {
				result += " ";
			}

			if (this.cssClassNamePrefix) {
				result += this.cssClassNamePrefix + "-";
			}

			result += classNames[i];
		}

		return result;
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
}

export const defaultHostConfig = {
	supportsInteractivity: true,
	fontFamily: "Segoe UI",
	spacing: {
		none: 0,
		small: 10,
		default: 20,
		medium: 30,
		large: 40,
		extraLarge: 50,
		padding: 20
	},
	separator: {
		lineThickness: 1,
		lineColor: "#EEEEEE"
	},
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
		bolder: 600
	},
	imageSizes: {
		small: 40,
		medium: 80,
		large: 160
	},
	containerStyles: {
		default: {
			backgroundColor: "#FFFFFF",
			foregroundColors: {
				default: {
					default: "#333333",
					subtle: "#EE333333"
				},
				dark: {
					default: "#000000",
					subtle: "#66000000"
				},
				light: {
					default: "#FFFFFF",
					subtle: "#33000000"
				},
				accent: {
					default: "#2E89FC",
					subtle: "#882E89FC"
				},
				attention: {
					default: "#cc3300",
					subtle: "#DDcc3300"
				},
				good: {
					default: "#54a254",
					subtle: "#DD54a254"
				},
				warning: {
					default: "#e69500",
					subtle: "#DDe69500"
				}
			}
		},
		emphasis: {
			backgroundColor: "#08000000",
			foregroundColors: {
				default: {
					default: "#333333",
					subtle: "#EE333333"
				},
				dark: {
					default: "#000000",
					subtle: "#66000000"
				},
				light: {
					default: "#FFFFFF",
					subtle: "#33000000"
				},
				accent: {
					default: "#2E89FC",
					subtle: "#882E89FC"
				},
				attention: {
					default: "#cc3300",
					subtle: "#DDcc3300"
				},
				good: {
					default: "#54a254",
					subtle: "#DD54a254"
				},
				warning: {
					default: "#e69500",
					subtle: "#DDe69500"
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
			maxWidth: 150,
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










