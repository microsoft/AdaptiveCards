/**
 * Date component based on the given payload.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputdate
 */

import React from 'react';
import {
	DatePickerAndroid,
	Platform,
} from 'react-native';

import * as Constants from '../../utils/constants';
import { HostConfigManager } from '../../utils/host-config';
import { PickerInput } from '../inputs';

export class DateInput extends React.Component {

	constructor(props) {
		super(props);

		this.payload = props.json;
		this.parseHostConfig();
	}

	/**
	 * @description Parse hostconfig specific to this element
	 */
	parseHostConfig() {
		this.state = {
			chosenDate: this.payload.value ? this.parseDateString(this.payload.value) : new Date(),
			minDate: this.payload.min ? this.parseDateString(this.payload.min) : undefined,
			maxDate: this.payload.max ? this.parseDateString(this.payload.max) : undefined,
			modalVisible: false,
			value: this.payload.value ? this.payload.value : Constants.EmptyString
		}

		this.state.setDate = this.setDate.bind(this);
	}

    /**
     * @description Updates the selected date
     * @param {Date} newDate 
     */
	setDate(newDate) {
		this.setState({ chosenDate: newDate })
		this.setState({
			value: newDate.getFullYear() + "-" +
				`${newDate.getMonth() + 1}`.padStart(2, '0') + "-" +
				`${newDate.getDate()}`.padStart(2, '0')
		})
	}

    /**
     * @description Toggles the DatePicker model visibility.
     * @param {Boolean} visible 
     */
	setModalVisible(visible) {
		this.setState({ modalVisible: visible });
	}

    /**
     * @description Hides the DatePicker on close event
     */
	handleModalClose = () => {
		this.setState({ modalVisible: false })
	}

    /**
     * @description Updates the selected date from date picker model.
     */
	handleDateChange = date => this.setDate(date)

    /**
     * @description Displays Android Date Picker
     */
	async androidPicker() {
		try {
			const { action, year, month, day } = await DatePickerAndroid.open({
				// Use `new Date()` for current date.
				date: this.state.chosenDate,
				minDate: this.state.minDate,
				maxDate: this.state.maxDate,
			});
			if (action !== DatePickerAndroid.dismissedAction) {
				// Selected year, month (0-11), day
				this.setDate(new Date(year, month, day))
			}
		} catch ({ code, message }) {
			console.log('Cannot open date picker', message);
		}
	}

    /**
     * @description Displays Date Picker based on the platform.
     */
	showDatePicker = () => {
		if (Platform.OS === Constants.PlatformIOS) {
			this.setState({ modalVisible: true });
		} else {
			this.androidPicker()
		}
	}

    /**
     * @description Return Date object from string.
     * @param {String} dateString 
     */
	parseDateString(dateString) {
		elements = dateString.split('-');
		return new Date(elements[0], elements[1], elements[2])
	}

	render() {

		if (HostConfigManager.getHostConfig().supportsInteractivity === false) {
			return null;
		}

		return (
			<PickerInput
				json={this.payload}
				value={this.state.value}
				showPicker={this.showDatePicker}
				modalVisible={this.state.modalVisible}
				handleModalClose={this.handleModalClose}
				chosenDate={this.state.chosenDate || new Date()}
				minDate={this.state.minDate}
				maxDate={this.state.maxDate}
				handleDateChange={this.handleDateChange}
				mode='date'
			/>
		);
	}
}

