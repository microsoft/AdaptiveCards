import * as Constants from '../utils/constants';
import {
	Platform,
} from 'react-native';

export class StyleConfig {

	constructor(hostConfig, themeConfig) {
		this.hostConfig = hostConfig;
		this.themeConfig = themeConfig;
	}

	/**
	 * Create the styles based on hostConfig and themeConfig
	 * @returns StyleConfig
	 */
	getStyleConfig() {
		const styles = {
			defaultFontFamilyName: {
				fontFamily: this.hostConfig.fontStyles.default.fontFamily
			},
			defaultFontConfig: {
				fontSize: this.hostConfig.fontStyles.default.fontSizes.default,
				fontWeight: this.hostConfig.fontStyles.default.fontWeights.default.toString(),
				fontFamily: this.hostConfig.fontStyles.default.fontFamily
			},
			actionIconFlex: {
				flexDirection: (this.hostConfig.actions.iconPlacement === 0) ?
					Constants.FlexRow : Constants.FlexColumn
			},
			actionIcon: {
				width: this.hostConfig.actions.iconSize,
				height: this.hostConfig.actions.iconSize,
			},
			separatorStyle: {
				borderColor: this.hostConfig.separator.lineColor,
				borderTopWidth: this.hostConfig.separator.lineThickness
			},
			borderAttention: {
				borderColor: this.hostConfig.containerStyles.default.foregroundColors.attention.default,
			},
			button: {
				...this.themeConfig.button[Platform.OS]
			},
			buttonTitle: {
				color: this.themeConfig.button[Platform.OS].color,
				textTransform: this.themeConfig.button[Platform.OS].textTransform,
			},
			input: {
				...this.themeConfig.input[Platform.OS]
			},
			defaultPositiveButtonBackgroundColor: {
				backgroundColor: this.hostConfig.containerStyles.default.foregroundColors.accent.default,
			},
			defaultDestructiveButtonBackgroundColor: {
				backgroundColor: this.hostConfig.containerStyles.default.foregroundColors.attention.default,
			},
			defaultDestructiveButtonForegroundColor: {
				color: this.hostConfig.containerStyles.default.foregroundColors.attention.default,
			},
			inputDate: {
				...this.themeConfig.inputDate[Platform.OS]
			},
			inputTime: {
				...this.themeConfig.inputTime[Platform.OS]
			},
			radioButton: {
				...this.themeConfig.radioButton[Platform.OS]
			},
			checkBox: {
				...this.themeConfig.checkBox[Platform.OS]
			},
			radioButtonText: {
				...this.themeConfig.radioButtonText[Platform.OS]
			},
			checkBoxText: {
				...this.themeConfig.checkBoxText[Platform.OS]
			},
			dropdown: {
				...this.themeConfig.dropdown[Platform.OS]
			},
			dropdownText: {
				...this.themeConfig.dropdownText[Platform.OS]
			},
			picker: {
				...this.themeConfig.picker[Platform.OS]
			},
			dateTimePicker: {
				...this.themeConfig.dateTimePicker[Platform.OS]
			}
		};
		return styles;
	}
}