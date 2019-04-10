import { HostConfigManager } from '../utils/host-config';
import { ThemeConfigManager } from '../utils/theme-config';
import { StyleSheet } from 'react-native';
import * as Constants from '../utils/constants';
import {
	Platform,
} from 'react-native';

export class StyleManager {
	static styleManagerInstance = null;
	hostConfig = HostConfigManager.getHostConfig();
	themeConfig = ThemeConfigManager.getThemeConfig();

	getFontType = () => {
		return this.hostConfig.fontFamily;
	}

	static getManager() {
		if (!StyleManager.styleManagerInstance) {
			StyleManager.styleManagerInstance = new StyleManager();
		}
		return StyleManager.styleManagerInstance;
	}

	styles = StyleSheet.create({
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
		buttonBackgroundColor: {
			backgroundColor: this.themeConfig.button[Platform.OS].backgroundColor,
		},
		buttonTitleColor:{
			color: this.themeConfig.button[Platform.OS].color,
		},
		buttonBorderRadius: {
			borderRadius: this.themeConfig.button[Platform.OS].borderRadius,
		},
		buttonTitleTransform:{
			textTransform: this.themeConfig.button[Platform.OS].textTransform,
		},
		inputBorderColor: {
			borderColor: this.themeConfig.input[Platform.OS].borderColor,
		},
		inputBackgroundColor: {
			backgroundColor: this.themeConfig.input[Platform.OS].backgroundColor,
		},
		inputBorderRadius: {
			borderRadius: this.themeConfig.input[Platform.OS].borderRadius,
		},
		inputBorderWidth: {
			borderWidth: this.themeConfig.input[Platform.OS].borderWidth,
		},
		defaultPositiveButtonBackgroundColor: {
			backgroundColor: this.hostConfig.containerStyles.default.foregroundColors.accent.default,
		},
		defaultDestructiveButtonForegroundColor: {
			color: this.hostConfig.containerStyles.default.foregroundColors.attention.default,
		},
	});
}