import { HostConfigManager } from '../utils/host-config';
import { StyleSheet } from 'react-native';
import * as Constants from '../utils/constants';

export class StyleManager {
	static styleManagerInstance = null;
	hostConfig = HostConfigManager.getHostConfig();

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
		}
	});
}