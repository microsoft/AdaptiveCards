/**
 * PickerInput component that wraps picker input elements.
 * 
 */

import React from 'react';
import {
	View,
	StyleSheet,
	TouchableOpacity,
	TextInput,
	Modal,
	Button,
	ViewPropTypes,
	Platform
} from 'react-native';

import { InputContextConsumer } from '../../utils/context';
import ElementWrapper from '../elements/element-wrapper';
import * as Constants from '../../utils/constants';
import DateTimePicker from '@react-native-community/datetimepicker'
import InputLabel from "./input-label";

export class PickerInput extends React.Component {

	constructor(props) {
		super(props);

		this.hostConfig = props.configManager.hostConfig;
		this.styleConfig = props.configManager.styleConfig;
		this.payload = props.json;
		this.id = Constants.EmptyString;
		this.placeHolder = Constants.EmptyString;
		this.placeholderTextColor = props.placeholderTextColor;
		this.type = Constants.EmptyString;
		this.modalButtonText = Constants.DoneString;
		this.label = Constants.EmptyString;
		this.parseHostConfig();

		this.errorMessage = this.payload.errorMessage || Constants.ErrorMessage;

		this.state = {
			isRequired: this.payload.isRequired || false,
			isError: (this.payload.isRequired || false) && !this.props.value
		}
	}

	/**
	 * @description Parse hostConfig specific to this element
	 */
	parseHostConfig() {
		this.id = this.payload.id;
		this.type = this.payload.type;
		this.placeholder = this.payload.placeholder;
		this.label = this.payload.label;
	}

	static getDerivedStateFromProps(nextProps, prevState) {
		if(!!nextProps.value) {
			return { isError: prevState.isRequired && !nextProps.value };
		}

		return prevState;
	}

	render() {
		if (!this.hostConfig.supportsInteractivity) {
			return null;
		}

		const {
			id,
			type,
			placeholder,
			modalButtonText,
			label
		} = this;

		if (!id || !type) {
			return null;
		}

		modalOverlayStyle = ViewPropTypes.style,
			modalStyle = ViewPropTypes.style,
			modalButtonStyle = ViewPropTypes.style,
			modalBtnContainer = ViewPropTypes.style

		return (
			<InputContextConsumer>
				{({ addInputItem, showErrors }) => (
					<ElementWrapper configManager={this.props.configManager} style={styles.elementWrapper} json={this.payload} isError={this.state.isError} isFirst={this.props.isFirst}>
						<InputLabel configManager={this.props.configManager} isRequired={this.state.isRequired} label={label} />
						<TouchableOpacity style={styles.inputWrapper} onPress={this.props.showPicker}
							accessibilityLabel={Platform.OS === 'android' ? (this.payload.altText || this.props.value || placeholder) : undefined}
							accessibilityRole='button'>
							{/* added extra view to fix touch event in ios . */}
							<View
								accessible={true}
								importantForAccessibility={'no-hide-descendants'}
								accessibilityLabel={this.payload.altText || this.props.value || placeholder}
								pointerEvents='none'>
								<TextInput
									style={this.getComputedStyles(showErrors)}
									autoCapitalize={Constants.NoneString}
									autoCorrect={false}
									placeholder={placeholder}
									placeholderTextColor={this.placeholderTextColor}
									textContentType={Constants.NoneString}
									underlineColorAndroid={Constants.TransparentString}
									value={this.props.value}>
									{addInputItem(this.id, { value: this.props.value, errorState: this.state.isError })}
								</TextInput>
							</View>
						</TouchableOpacity>
						<Modal
							animationType='slide'
							transparent
							visible={this.props.modalVisible}
							onRequestClose={this.props.handleModalClose}>
							<View style={[styles.overlay, modalOverlayStyle]}>
								<View style={[this.styleConfig.dateTimePicker, modalStyle]}>
									<View style={[styles.modalBtnContainer, modalBtnContainer]}>
										<Button
											style={[modalButtonStyle]}
											title={modalButtonText}
											onPress={this.props.handleModalClose}
										/>
									</View>
									<DateTimePicker
										display={Platform.OS === Constants.PlatformIOS ? 'spinner' : 'default'}
										mode={this.props.mode}
										format={this.props.format}
										value={this.props.chosenDate || new Date()}
										minimumDate={this.props.minDate}
										maximumDate={this.props.maxDate}
										textColor={this.styleConfig.dateTimePicker.textColor}
										onChange={(event, date) => this.props.handleDateChange(date)} />
								</View>
							</View>
						</Modal>
					</ElementWrapper>
				)}
			</InputContextConsumer>
		);
	}

	/**
	 * @description get styles for showing validation errors
	 * @param showErrors show errors based on this flag.
	 */
	getComputedStyles = (showErrors) => {
		// remove placeholderTextColor from styles object before using
		const { placeholderTextColor, ...stylesObject } = this.props.style;
		let computedStyles = [stylesObject, this.styleConfig.defaultFontConfig];
		if (this.state.isError && showErrors && this.state.isRequired) {
			computedStyles.push(this.styleConfig.borderAttention);
			computedStyles.push({ borderWidth: 1 });
		}
		return computedStyles;
	}
}

const styles = StyleSheet.create({
	inputWrapper: {
		width: Constants.FullWidth,
		marginTop: 3
	},
	elementWrapper: {
		marginVertical: 3
	},
	overlay: {
		flex: 1,
		backgroundColor: Constants.BackgroundDisabledColor,
		alignItems: Constants.CenterString,
		justifyContent: Constants.FlexEnd
	},
	modalBtnContainer: {
		width: Constants.FullWidth,
		alignItems: Constants.CenterString,
		flexDirection: Constants.FlexRow,
		justifyContent: Constants.FlexEnd
	}
});
