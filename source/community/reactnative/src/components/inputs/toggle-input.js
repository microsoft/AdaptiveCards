/**
 * Toggle Component based on the given payload.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputtoggle
 */

import React from 'react';
import {
	Switch,
	StyleSheet,
	View,
	Text
} from 'react-native';

import { StyleManager } from '../../styles/style-config';
import { HostConfigManager } from '../../utils/host-config';
import { InputContextConsumer } from '../../utils/context';
import { Label } from '../elements';
import ElementWrapper from '../elements/element-wrapper';
import * as Constants from '../../utils/constants';
import * as Enums from '../../utils/enums';
import InputLabel from "./input-label";

export class ToggleInput extends React.Component {

	styleConfig = StyleManager.getManager().styles;

	constructor(props) {
		super(props);

		this.title = props.json.title;
		this.valueOn = props.json.valueOn || Constants.TrueString;
		this.valueOff = props.json.valueOff || Constants.FalseString;
		this.value = props.json.value || this.valueOff;
		this.id = props.json.id || Constants.ToggleValueOn
		this.label = props.json.label;
		this.altText = props.json.altText;

		this.isValidationRequired = !!props.json.validation &&
			(Enums.ValidationNecessity.Required == props.json.validation.necessity ||
				Enums.ValidationNecessity.RequiredWithVisualCue == props.json.validation.necessity);

		this.validationRequiredWithVisualCue = (!props.json.validation ||
			Enums.ValidationNecessity.RequiredWithVisualCue == props.json.validation.necessity);

		this.wrapText = props.json.wrap || false

		// state
		this.state = {
			toggleValue: (this.value === this.valueOn),
			isError: this.isValidationRequired && (this.value === this.valueOff)
		}
	}

	/**
	 * @description Invoked on every change in Toggle
	 * @param {Boolean} toggleValue
	 * @param {InputContextConsumer} addInputItem
	 */
	toggleValueChanged = (toggleValue, addInputItem) => {
		const changedValue = toggleValue ? this.valueOn : this.valueOff;
		const isError = this.isValidationRequired ? changedValue === this.valueOff : false;
		this.setState({ toggleValue, isError });
		addInputItem(this.id, { value: changedValue, errorState: isError });
	}

	render() {
		if (HostConfigManager.getHostConfig().supportsInteractivity === false) {
			return null;
		}
		const { toggleValue } = this.state;
		return (
			<ElementWrapper json={this.props.json} style={styles.toggleContainer} isError={this.state.isError} isFirst={this.props.isFirst}>
				<InputContextConsumer>
					{({ addInputItem, inputArray, showErrors }) => {
						if (!inputArray[this.id]) {
							const initialValue = toggleValue ? this.valueOn : this.valueOff;
							const isError = this.isValidationRequired ? initialValue === this.valueOff : false;
							addInputItem(this.id, { value: initialValue, errorState: isError });
						}
						return (
							<View>
								<InputLabel label={this.label}/>
								<View
									accessible={true}
									accessibilityLabel={this.altText}
									style={this.getComputedStyles(showErrors)}>
									<Label text={this.title} wrap={this.wrapText} style={styles.title} />
									<Switch
										style={styles.switch}
										value={toggleValue}
										onValueChange={toggleValue => {
											this.toggleValueChanged(toggleValue, addInputItem)
										}}>
									</Switch>
								</View>
							</View>
						)
					}}
				</InputContextConsumer>
			</ElementWrapper>
		)
	}

	/**
	 * @description get styles for showing validation errors
	 * @param showErrors show errors based on this flag.
	 */
	getComputedStyles = (showErrors) => {
		let computedStyles = [styles.toggleView];
		if (this.state.isError && (showErrors || this.validationRequiredWithVisualCue)) {
			computedStyles.push(this.styleConfig.borderAttention);
			computedStyles.push({ borderWidth: 1 });
		}
		return computedStyles;
	}
}

const styles = StyleSheet.create({
	toggleContainer: {
		paddingTop: 5,
		paddingBottom: 5
	},
	toggleView: {
		padding: 5,
		flexDirection: Constants.FlexRow,
		justifyContent: Constants.SpaceBetween,
		alignItems: Constants.CenterString,
	},
	title: {
		flexShrink: 1,
		marginRight: 10
	}
});