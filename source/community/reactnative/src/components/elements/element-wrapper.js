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
import { InputContext } from '../../utils/context';
import * as Constants from '../../utils/constants';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';

export default class ElementWrapper extends React.Component {

	static contextType = InputContext;

	static propTypes = {
		isFirst: PropTypes.bool
	};

	static defaultProps = {
		isFirst: false
	};

	render() {
		this.styleConfig = this.props.configManager.styleConfig;
		const computedStyles = this.getComputedStyles();
		const showValidationText = this.props.isError && this.context.showErrors && Utils.isNullOrEmpty(this.props.json.inlineAction);
		const { isFirst } = this.props; //isFirst represent, it is first element
		const isColumnSet = this.props.json.type === Constants.TypeColumnSet;
		return (
			<React.Fragment>
				{!isColumnSet ? !isFirst && this.getSpacingElement() : this.props.json.separator && !isFirst && this.getSeparatorElement()}
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
			const height = this.props.configManager.hostConfig.getEffectiveHeight(heightEnumValue);
			computedStyles.push({ flex: height });
		}
		if (payload.parent && payload.parent["verticalContentAlignment"] && payload.parent.type === Constants.TypeColumn) {
			// vertical content alignment
			let verticalContentAlignment = Utils.parseHostConfigEnum(
				Enums.VerticalAlignment,
				payload.parent["verticalContentAlignment"],
				Enums.VerticalAlignment.Top
			);
			switch (verticalContentAlignment) {
				case Enums.VerticalAlignment.Center:
					computedStyles.push({ justifyContent: Constants.CenterString });
					break;
				case Enums.VerticalAlignment.Bottom:
					computedStyles.push({ justifyContent: Constants.FlexEnd });
					break;
				default:
					computedStyles.push({ justifyContent: Constants.FlexStart });
					break;
			}
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
		return (
			<Text style={validationTextStyles}>
				{payload.errorMessage || Constants.ErrorMessage}
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
		const spacing = this.props.configManager.hostConfig.getEffectiveSpacing(spacingEnumValue);
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

	/**
	 * @description Return the element for separator
	 * @returns {object} View element with `separator` prop
	 */
	getSeparatorElement = () => {
		const spacingEnumValue = Utils.parseHostConfigEnum(
			Enums.Spacing,
			this.props.json.spacing,
			Enums.Spacing.Default);
		const spacing = this.props.configManager.hostConfig.getEffectiveSpacing(spacingEnumValue);
		return <View style={[this.styleConfig.separatorStyle, { height: 3, marginBottom: spacing }]}></View>
	}
}


const styles = StyleSheet.create({
	inputContainer: {
		backgroundColor: Constants.TransparentString
	}
})