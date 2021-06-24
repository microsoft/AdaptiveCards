/**
 * Toggle Component based on the given payload.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputtoggle
 */

import React from 'react';
import {
	Switch,
	StyleSheet,
	View
} from 'react-native';

import { InputContextConsumer } from '../../utils/context';
import ElementWrapper from '../elements/element-wrapper';
import * as Constants from '../../utils/constants';
import InputLabel from "./input-label";

export class ToggleInput extends React.Component {

	constructor(props) {
		super(props);
		this.hostConfig = props.configManager.hostConfig;

		this.title = props.json.title;
		this.valueOn = props.json.valueOn || Constants.TrueString;
		this.valueOff = props.json.valueOff || Constants.FalseString;
		this.value = props.json.value || this.valueOff;
		this.id = props.json.id || Constants.ToggleValueOn
		this.altText = props.json.altText;
		this.isRequired = props.json.isRequired || false;
		this.wrapText = props.json.wrap || false

		// state
		this.state = {
			toggleValue: (this.value == this.valueOn),
			isError: this.isRequired && (this.value == this.valueOff)
		}
	}

	/**
	 * @description Invoked on every change in Toggle
	 * @param {Boolean} toggleValue
	 * @param {InputContextConsumer} addInputItem
	 */
	toggleValueChanged = (toggleValue, addInputItem) => {
		const changedValue = toggleValue ? this.valueOn : this.valueOff;
		const isError = this.isRequired ? changedValue === this.valueOff : false;
		this.setState({ toggleValue, isError });
		addInputItem(this.id, { value: changedValue, errorState: isError });
	}

	render() {
		if (!this.hostConfig.supportsInteractivity) {
			return null;
		}
		const { toggleValue } = this.state;

		return (
			<ElementWrapper configManager={this.props.configManager} json={this.props.json} style={styles.toggleContainer} isError={this.state.isError} isFirst={this.props.isFirst}>
				<InputContextConsumer>
					{({ addInputItem, inputArray }) => {
						if (!inputArray[this.id]) {
							const initialValue = toggleValue ? this.valueOn : this.valueOff;
							const isError = this.isRequired ? initialValue === this.valueOff : false;
							addInputItem(this.id, { value: initialValue, errorState: isError });
						}
						return (
							<View
								accessible={true}
								accessibilityLabel={this.altText}
								style={styles.toggleView}>
								<Switch
									style={styles.switch}
									value={toggleValue}
									onValueChange={toggleValue => {
										this.toggleValueChanged(toggleValue, addInputItem)
									}}>
								</Switch>
								<View style={styles.titleContainer}>
									<InputLabel configManager={this.props.configManager} isRequired={this.isRequired} wrap={this.wrapText} style={styles.title} label={this.title} />
								</View>
							</View>
						)
					}}
				</InputContextConsumer>
			</ElementWrapper>
		)
	}
}

const styles = StyleSheet.create({
	toggleContainer: {
		paddingTop: 5,
		paddingBottom: 5
	},
	toggleView: {
		padding: 5,
		flexDirection: Constants.FlexRowReverse,
		justifyContent: Constants.SpaceBetween,
		alignItems: Constants.CenterString,
	},
	title: {
		flexShrink: 1,
	},
	titleContainer: {
		flex: 1
	},
	switch: {
		marginLeft: 10
	}
});