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
	DatePickerIOS,
	Modal,
	Text,
	Button,
	ViewPropTypes
} from 'react-native';

import { InputContextConsumer } from '../../utils/context';
import ElementWrapper from '../elements/element-wrapper';
import * as Constants from '../../utils/constants';
import * as Enums from '../../utils/enums';
import { StyleManager } from '../../styles/style-config';
import { HostConfigManager } from '../../utils/host-config';

export class PickerInput extends React.Component {

	styleConfig = StyleManager.getManager().styles;

	constructor(props) {
		super(props);

		this.payload = props.json;
		this.id = Constants.EmptyString;
		this.placeHolder = Constants.EmptyString;
		this.type = Constants.EmptyString;
		this.modalButtonText = Constants.DoneString;
		this.parseHostConfig();

		this.isValidationRequired = !!this.payload.validation &&
			(Enums.ValidationNecessity.Required == this.payload.validation.necessity ||
				Enums.ValidationNecessity.RequiredWithVisualCue == this.payload.validation.necessity);

		this.validationRequiredWithVisualCue = (!this.payload.validation ||
			Enums.ValidationNecessity.RequiredWithVisualCue == this.payload.validation.necessity);

		this.state = {
			isError: this.isValidationRequired && !this.props.value
		}
	}

	/**
	 * @description Parse hostConfig specific to this element
	 */
	parseHostConfig() {
		this.id = this.payload.id;
		this.type = this.payload.type;
		this.placeholder = this.payload.placeholder;
	}

	componentWillReceiveProps(newProps) {
		this.setState({ isError: this.isValidationRequired && !newProps.value })
	}

	render() {
		if (HostConfigManager.getHostConfig().supportsInteractivity === false) {
			return null;
		}

		const {
			id,
			type,
			placeholder,
			modalButtonText
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
					<ElementWrapper json={this.payload} isError={this.state.isError} isFirst={this.props.isFirst}>
						<TouchableOpacity style={styles.inputWrapper} onPress={this.props.showPicker}>
							{/* added extra view to fix touch event in ios . */}
							<View pointerEvents='none' style={this.getComputedStyles(showErrors)}>
								<TextInput
									style={[styles.input, this.styleConfig.defaultFontConfig]}
									autoCapitalize={Constants.NoneString}
									autoCorrect={false}
									placeholder={placeholder}
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
								<View style={[styles.modal, modalStyle]}>
									<View style={[styles.modalBtnContainer, modalBtnContainer]}>
										<Button
											style={[modalButtonStyle]}
											title={modalButtonText}
											onPress={this.props.handleModalClose}
										/>
									</View>
									<DatePickerIOS
										mode={this.props.mode}
										format={this.props.format}
										date={this.props.chosenDate || new Date()}
										minimumDate={this.props.minDate}
										maximumDate={this.props.maxDate}
										onDateChange={this.props.handleDateChange} />
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
		let computedStyles = [];
		if (this.state.isError && (showErrors || this.validationRequiredWithVisualCue)) {
			computedStyles.push(this.styleConfig.borderAttention);
			computedStyles.push({ borderWidth: 1 });
		}
		return computedStyles;
	}
}

const styles = StyleSheet.create({
	inputWrapper: {
		width: Constants.FullWidth,
		marginTop: 15,
	},
	input: {
		width: Constants.FullWidth,
		height: 44,
		padding: 5,
		borderWidth: 1,
		backgroundColor: Constants.WhiteColor,
		borderColor: Constants.LightGreyColor,
		borderRadius: 5,
	},
	overlay: {
		flex: 1,
		backgroundColor: 'rgba(0,0,0,.3)',
		alignItems: Constants.CenterString,
		justifyContent: Constants.FlexEnd
	},
	modal: {
		backgroundColor: Constants.WhiteColor,
		height: 260,
		width: Constants.FullWidth
	},
	modalBtnContainer: {
		width: Constants.FullWidth,
		alignItems: Constants.CenterString,
		flexDirection: Constants.FlexRow,
		justifyContent: Constants.FlexEnd,
		paddingHorizontal: 15,
		marginTop: 15
	}
});
