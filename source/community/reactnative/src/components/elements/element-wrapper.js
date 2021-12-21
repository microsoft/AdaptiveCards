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
		const isColumnSet = this.props.json.type === Constants.TypeColumnSet;
		return (
			<React.Fragment>
				{!this.props.isFirst && !isColumnSet && this.getSpacingElement()}
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

		// padding
        if(payload.parent && payload.parent.type === Constants.TypeAdaptiveCard) {
            const padding = this.props.configManager.hostConfig.getEffectiveSpacing(Enums.Spacing.Padding);
            computedStyles.push({marginHorizontal: padding});
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
            Enums.Spacing.Default,
        );
        const spacing = this.props.configManager.hostConfig.getEffectiveSpacing(spacingEnumValue);
        
		let computedStyles = [{flex: 1}];
		if(payload.parent && payload.parent.type === Constants.TypeAdaptiveCard) {
            const padding = this.props.configManager.hostConfig.getEffectiveSpacing(Enums.Spacing.Padding);
            computedStyles.push({marginHorizontal: padding});
        }
		
		// spacing styles
        return (
            <View style={computedStyles}>
                {<View style={{height: spacing/2}}/>}
                {payload.separator && <View style={this.props.configManager.styleConfig.separatorStyle} />}
				{<View style={{height: spacing/2}}/>}
            </View>
        );
	}
}


const styles = StyleSheet.create({
	inputContainer: {
		backgroundColor: Constants.TransparentString
	}
})