/**
 * NumberInput Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputnumber
 */

import React from 'react';
import * as Constants from '../../utils/constants';
import { HostConfigManager } from '../../utils/host-config';
import { Input } from './input';
import * as Enums from '../../utils/enums';

const NUM_REGEX = /^\-?[1-9]\d*(\.\d*)?$/;

export class NumberInput extends React.Component {

	constructor(props) {
		super(props);

		this.payload = props.json;
		this.id = Constants.EmptyString;
		this.styleValue = Enums.InputTextStyle.Number;

		this.isValidationRequired = !!this.payload.validation &&
			(Enums.ValidationNecessity.Required == this.payload.validation.necessity ||
				Enums.ValidationNecessity.RequiredWithVisualCue == this.payload.validation.necessity);

		this.state = {
			isError: this.isValidationRequired,
			numberValue: Constants.EmptyString,
		}
	}

	render() {
		if (HostConfigManager.getHostConfig().supportsInteractivity === false) {
			return null;
		}
		this.parseHostConfig();

		return (
			<Input
				json={this.payload}
				handleFocus={this.handleFocus}
				handleBlur={this.handleBlur}
				textValueChanged={(text, addInputItem) => { this.onTextChanged(text, addInputItem) }}
				value={this.state.numberValue}
				isError={this.state.isError}
				styleValue={this.styleValue}
			/>
		);
	}

    /**
     * @description Parse hostConfig specific to this element
     */
	parseHostConfig() {
		this.id = this.payload.id;
		this.min = this.payload.min;
		this.max = this.payload.max;
	}

    /**
     * @description handle text input when in focus
     */
	handleFocus = () => {
		this.setState({
			isError: false
		});
	}

    /**
     * @description handle text input when out of focus
     */
	handleBlur = () => {
		this.validate(this.state.numberValue);
	}

    /**
     * @description validate the input field
     */
	validate = (numberValue) => {
		this.setState({
			isError: this.checkRangeValue(numberValue)
		})
	};

    /**
     * @description Invoked on every change in Input field
     * @param {string} text
     */
	onTextChanged = (text, addInputItem) => {
		this.setState({
			numberValue: text
		})
		addInputItem(this.id, { value: text, errorState: this.state.isError });
	}


	checkRangeValue = (numberValue) => {
		if (!this.isValidationRequired) {
			return false
		}
		if (NUM_REGEX.test(numberValue)) {
			var parsedValue = parseFloat(numberValue);
			if (parsedValue < this.min || parsedValue > this.max) {
				return true
			} else {
				return false
			}
		}
		return true
	}
};


