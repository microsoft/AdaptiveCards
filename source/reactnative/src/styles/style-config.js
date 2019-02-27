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
		fontFamilyName: {
			fontFamily: this.hostConfig.fontFamily
		},
		fontConfig: {
			fontSize: this.hostConfig.fontSizes.default,
			fontWeight: this.hostConfig.fontWeights.default.toString(),
			fontFamily: this.hostConfig.fontFamily
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
		buttonBackgroundColor:{
			backgroundColor: Platform.OS === Constants.PlatformIOS ? this.themeConfig.button.ios.backgroundColor : this.themeConfig.button.android.backgroundColor,
		},
		buttonTitleColor:{
			color: Platform.OS === Constants.PlatformIOS ? this.themeConfig.button.ios.titleColor : this.themeConfig.button.android.titleColor,
		},
		buttonBorderRadius:{
			borderRadius: Platform.OS === Constants.PlatformIOS ? this.themeConfig.button.ios.borderRadius : this.themeConfig.button.android.borderRadius,
		},
		buttonTitleTransform:{
			textTransform: Platform.OS === Constants.PlatformIOS ? this.themeConfig.button.ios.titleTransform : this.themeConfig.button.android.titleTransform,
		},
		inputBorderColor:{
			borderColor: Platform.OS === Constants.PlatformIOS ? this.themeConfig.input.ios.borderColor : this.themeConfig.input.android.borderColor,
		},
		inputBackgroundColor:{
			backgroundColor: Platform.OS === Constants.PlatformIOS ? this.themeConfig.input.ios.backgroundColor : this.themeConfig.input.android.backgroundColor,
		},
		inputBorderRadius:{
			borderRadius: Platform.OS === Constants.PlatformIOS ? this.themeConfig.input.ios.borderRadius : this.themeConfig.input.android.borderRadius,
		},
		inputBorderWidth:{
			borderWidth: Platform.OS === Constants.PlatformIOS ? this.themeConfig.input.ios.borderWidth : this.themeConfig.input.android.borderWidth,
		},
		defaultDestructiveForegroundColor:{
			color: this.hostConfig.containerStyles.default.foregroundColors.attention.default,
		},
	});
}