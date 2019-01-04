/**
 * ElementWrapper component that wraps all other specific input element.
 * 
 * @example
 * <ElementWrapper json={payload}>
 *  <InputElement json={payload}></InputElement>
 * </ElementWrapper>
 */

import React from 'react';
import {
	View,
	StyleSheet
} from 'react-native';

import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';
import { HostConfigManager } from "../../utils/host-config";
import * as Constants from '../../utils/constants';
import { StyleManager } from "../../styles/style-config";

export default class ElementWrapper extends React.Component {

	hostConfig = HostConfigManager.getHostConfig();
	styleConfig = StyleManager.getManager().styles;

	render() {
		const computedStyles = this.getComputedStyles();

		return (
			<View style={computedStyles} onLayout={this.props.onPageLayout}>
				{this.props.children}
			</View>
		)
	}

    /**
     * @description Return the styles applicable based on the given payload
     */
	getComputedStyles = () => {
		const payload = this.props.json;
		const receivedStyles = this.props.style;

		let computedStyles = [styles.inputContainer, receivedStyles];

		// spacing
		const spacingEnumValue = Utils.parseHostConfigEnum(
			Enums.Spacing,
			payload.spacing,
			Enums.Spacing.Small);
		const spacing = this.hostConfig.getEffectiveSpacing(spacingEnumValue);
		computedStyles.push({ marginTop: spacing });

		// separator
		const separator = payload.separator || false;
		if (separator) {
			computedStyles.push(this.styleConfig.separatorStyle);
			computedStyles.push({ paddingTop: spacing / 2, marginTop: spacing / 2 });
		}

		// height 
		const height = payload.height || false;
		if (height) {
			const heightEnumValue = Utils.parseHostConfigEnum(
				Enums.Height,
				payload.height,
				Enums.Height.Auto);
			const height = this.hostConfig.getEffectiveHeight(heightEnumValue);
			computedStyles.push({ flex: height });
		}

		return computedStyles;
	}
}


const styles = StyleSheet.create({
	inputContainer: {
		backgroundColor: Constants.WhiteColor
	}
})