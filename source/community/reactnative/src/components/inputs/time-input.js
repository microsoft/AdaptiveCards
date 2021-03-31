/**
 * Date component based on the given payload.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputtime
 */

import React from 'react';
import {
	TimePickerAndroid,
	Platform,
} from 'react-native';

import { HostConfigManager } from '../../utils/host-config';
import { StyleManager } from '../../styles/style-config';
import * as Constants from '../../utils/constants';
import { PickerInput } from '../inputs';

export class TimeInput extends React.Component {

	styleConfig = StyleManager.getManager().styles;

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
			chosenTime: this.payload.value ? this.parseTimeString(this.payload.value) : new Date(),
			minTime: this.payload.min ? this.parseTimeString(this.payload.min) : undefined,
			maxTime: this.payload.max ? this.parseTimeString(this.payload.max) : undefined,
			modalVisible: false,
			value: this.payload.value ? this.payload.value : Constants.EmptyString
		}

		this.state.setTime = this.setTime.bind(this);
	}

	/**
	 * @description Return Date object from string.
	 * @param {String} timeString 
	 */
	parseTimeString(timeString) {
		timeArray = timeString.split(':');
		date = new Date();
		date.setHours(Number.parseInt(timeArray[0], 10));
		date.setMinutes(Number.parseInt(timeArray[1], 10));
		return date;
	}

	/**
	 * @description Binds the selected time
	 * @param {Date} newTime 
     */
	setTime(newTime) {
		const updatedTime = ("0" + newTime.getHours()).slice(-2) + ":"
			+ ("0" + newTime.getMinutes()).slice(-2);

		this.setState({
			chosenTime: newTime,
			value: updatedTime
		});
	}

	/**
     * @description Toggles the TimePicker model visibility.
     * @param {Boolean} visible 
     */
	setModalVisible(visible) {
		this.setState({ modalVisible: visible });
	}

	/**
	 * @description Hides the TimePicker on close event
	 */
	handleModalClose = () => {
		this.setState({ modalVisible: false })
	}

	/**
	 * @description Updates the selected Time from Time picker model.
	 */
	handleTimeChange = time => this.setTime(time)

	/**
	 * @description Displays Android Time Picker
	 */
	async androidPicker() {
		try {
			const { action, hour, minute } = await TimePickerAndroid.open({
				hour: this.state.chosenTime.getHours(),
				minute: this.state.chosenTime.getMinutes()
			});
			if (action !== TimePickerAndroid.dismissedAction) {
				// Selected hour (0-23), minute (0-59)
				var date = new Date();
				date.setHours(hour);
				date.setMinutes(minute);
				this.setTime(date)
			}
		} catch ({ code, message }) {
			console.warn('Cannot open time picker', message);
		}
	}

	/**
	 * @description Displays Time Picker based on the platform.
	 */
	showTimePicker = () => {
		if (Platform.OS === Constants.PlatformIOS) {
			this.setState({ modalVisible: true });
		} else {
			this.androidPicker()
		}
	}

	render() {
		if (HostConfigManager.getHostConfig().supportsInteractivity === false) {
			return null;
		}

		return (
			<PickerInput
				json={this.payload}
				style={this.styleConfig.inputTime}
				value={this.state.value}
				format={"HH:mm"}
				showPicker={this.showTimePicker}
				modalVisible={this.state.modalVisible}
				handleModalClose={this.handleModalClose}
				chosenDate={this.state.chosenTime || new Date()}
				minDate={this.state.minTime}
				maxDate={this.state.maxTime}
				handleDateChange={this.handleTimeChange}
				mode='time'
			/>
		);
	}
}

