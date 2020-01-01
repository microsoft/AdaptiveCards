/**
 * ElementWrapper component that wraps all other element types and 
 * takes care of common parsing & styling.
 * 
 * @example
 * <ElementWrapper json={payload}>
 *  <InputElement json={payload}></InputElement>
 * </ElementWrapper>
 */

import React from 'react';
import {
	View,
	Text,
	StyleSheet
} from 'react-native';
import PropTypes from 'prop-types';
import { HostConfigManager } from "../../utils/host-config";
import { StyleManager } from "../../styles/style-config";
import { InputContext } from '../../utils/context';
import * as Constants from '../../utils/constants';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';

export default class ElementWrapper extends React.Component {

	hostConfig = HostConfigManager.getHostConfig();
	styleConfig = StyleManager.getManager().styles;

	static contextType = InputContext;

	static propTypes = {
		isColumnSet: PropTypes.bool,
		isFirst: PropTypes.bool
	};

	static defaultProps = {
		isColumnSet: false,
		isFirst: false
	};

	render() {
		const computedStyles = this.getComputedStyles();
		const showValidationText = this.props.isError && this.context.showErrors;
		const { isColumnSet, isFirst } = this.props; //isFirst represent, it is first element

		return (
			<React.Fragment>
				{!isColumnSet && !isFirst && this.getSpacingElement()}
				<View style={computedStyles} onLayout={this.props.onPageLayout}>
					{this.props.children}
					{showValidationText && this.getValidationText()}
				</View>
			</React.Fragment>
		)
	}

    /**
     * @description Return the styles applicable based on the given payload
	 * @returns {Array} computedStyles
     */
	getComputedStyles = () => {
		const payload = this.props.json;
		const receivedStyles = this.props.style;

		let computedStyles = [styles.inputContainer, receivedStyles];

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

	/**
	 * @description Return the validation text message
	 * @returns {object} Text element with the message
	 */
	getValidationText = () => {
		const payload = this.props.json;
		const validationTextStyles = [this.styleConfig.fontFamilyName, this.styleConfig.defaultDestructiveButtonForegroundColor];
		const errorMessage = (payload.validation && payload.validation.errorMessage) ?
			payload.validation.errorMessage : Constants.ErrorMessage;

		return (
			<Text style={validationTextStyles}>
				{errorMessage}
			</Text>
		)
	}

	/**
     * @description Return the element for spacing and/or separator
     * @returns {object} View element with spacing based on `spacing` and `separator` prop
     */
	getSpacingElement = () => {
		const payload = this.props.json;
		const spacingEnumValue = Utils.parseHostConfigEnum(
			Enums.Spacing,
			payload.spacing,
			Enums.Spacing.Default);
		const spacing = this.hostConfig.getEffectiveSpacing(spacingEnumValue);
		const separator = payload.separator || false;

		// spacing styles
		const separatorStyles = [{ height: spacing }];

		// separator styles
		if (separator) {
			separatorStyles.push(this.styleConfig.separatorStyle);
			separatorStyles.push({ paddingTop: spacing / 2, marginTop: spacing / 2, height: 0 });
		}

		return <View style={separatorStyles}></View>
	}
}


const styles = StyleSheet.create({
	inputContainer: {
		backgroundColor: Constants.TransparentString
	}
})