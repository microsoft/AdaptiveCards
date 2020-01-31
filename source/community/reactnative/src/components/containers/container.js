/**
 * Container Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-container
 */

import React from 'react';
import {
	StyleSheet,
	View,
	Text
} from 'react-native';

import { Registry } from '../registration/registry';
import { SelectAction } from '../actions';
import * as Constants from '../../utils/constants';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';
import { HostConfigManager } from '../../utils/host-config';
import { StyleManager } from "../../styles/style-config";
import { InputContext } from '../../utils/context';
import { ContainerWrapper } from './';

export class Container extends React.Component {

	hostConfig = HostConfigManager.getHostConfig();
	styleConfig = StyleManager.getManager().styles;
	static contextType = InputContext;

	constructor(props) {
		super(props);
		this.payload = props.json;
		this.selectionActionData = props.json.selectAction;
	}

    /**
     * @description Parse the given payload and render the card accordingly
	 * @returns {object} Return the child elements of the container
     */
	parsePayload = () => {
		let children = [];
		if (!this.payload) {
			return children;
		}

		if (this.payload.isFallbackActivated) {
			if (this.payload.fallbackType == "drop") {
				return null;
			} else if (!Utils.isNullOrEmpty(element.fallback)) {
				return Registry.getManager().parseComponent(this.payload.fallback, this.context.onParseError);
			}
		}

		children = Registry.getManager().parseRegistryComponents(this.payload.items, this.context.onParseError);
		return children.map((ChildElement, index) => React.cloneElement(ChildElement, { containerStyle: this.payload.style, isFirst: index === 0 }));
	}

	internalRenderer = () => {
		const payload = this.payload;
		const minHeight = Utils.convertStringToNumber(payload.minHeight);
		//We will pass the style as array, since it can be updated in the container wrapper if required.
		const containerStyle = typeof minHeight === "number" ? [{ minHeight }] : [];

		const showValidationText = this.props.isError && this.context.showErrors;

		var containerContent = (
			<ContainerWrapper json={this.payload} style={containerStyle} containerStyle={this.props.containerStyle}>
				{this.payload.spacing && this.payload.separator && this.getSpacingElement()}
				{this.parsePayload()}
				{showValidationText && this.getValidationText()}
			</ContainerWrapper>
		);
		if ((payload.selectAction === undefined)
			|| (HostConfigManager.supportsInteractivity() === false)) {
			return containerContent;
		} else {
			return <SelectAction selectActionData={payload.selectAction}>
				{containerContent}
			</SelectAction>;
		}
	}

	/**
		 * @description Return the element for spacing and/or separator
		 * @returns {object} View element with spacing based on `spacing` and `separator` prop
		 */
	getSpacingElement = () => {
		const spacingEnumValue = Utils.parseHostConfigEnum(
			Enums.Spacing,
			this.payload.spacing,
			Enums.Spacing.Default);
		const spacing = this.hostConfig.getEffectiveSpacing(spacingEnumValue);

		// spacing styles
		const separatorStyles = [{ height: spacing }];

		// separator styles
		separatorStyles.push(this.styleConfig.separatorStyle);
		separatorStyles.push({ paddingTop: spacing / 2, marginTop: spacing / 2, height: 0 });
		return <View style={separatorStyles}></View>
	}

	/**
	 * @description Return the validation text message
	 * @returns {object} Text element with the message
	 */
	getValidationText = () => {
		const payload = this.payload;
		const validationTextStyles = [this.styleConfig.fontFamilyName, this.styleConfig.defaultDestructiveButtonForegroundColor];
		const errorMessage = (payload.validation && payload.validation.errorMessage) ?
			payload.validation.errorMessage : Constants.ErrorMessage;

		return (
			<Text style={validationTextStyles}>
				{errorMessage}
			</Text>
		)
	}

	render() {
		let containerRender = this.internalRenderer();
		return containerRender;
	}
};

const styles = StyleSheet.create({
	defaultBGStyle: {
		backgroundColor: Constants.TransparentString,
	},
});