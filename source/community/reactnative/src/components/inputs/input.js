/**
 * InputText Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputtext
 */

import React from 'react';
import {
	StyleSheet,
	TextInput,
	Image,
	Text,
	View,
	TouchableOpacity,
} from 'react-native';

import { InputContextConsumer } from '../../utils/context';
import ElementWrapper from '../elements/element-wrapper';
import { StyleManager } from '../../styles/style-config';
import * as Constants from '../../utils/constants';
import { HostConfigManager } from '../../utils/host-config';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';
import InputLabel from "./input-label";

const ERROR_MESSAGE = "Inline ShowCard is not supported as of now";

export class Input extends React.Component {

	styleConfig = StyleManager.getManager().styles;

	constructor(props) {
		super(props);

		this.payload = props.json;
		this.id = Constants.EmptyString;
		this.isMultiline = Boolean;
		this.maxLength = 0;
		this.placeHolder = Constants.EmptyString;
		this.type = Constants.EmptyString;
		this.keyboardType = Constants.EmptyString;
		this.textStyle = Constants.EmptyString;
		this.label = Constants.EmptyString;
		this.isRequired = this.payload.isRequired || false;
		this.errorMessage = this.payload.errorMessage || Constants.ErrorMessage;

		this.inlineAction = {};
		this.state = {
			showInlineActionErrors: false,
			text: Constants.EmptyString,
		}
	}

	render() {
		if (HostConfigManager.getHostConfig().supportsInteractivity === false) {
			return null;
		}
		this.parseHostConfig();

		const {
			id,
			type,
			isMultiline,
			placeholder,
			maxLength,
			label
		} = this;

		if (!id || !type) {
			return null;
		}

		if (!Utils.isNullOrEmpty(this.inlineAction)) {
			TextBox = this.inlineActionComponent();
		}
		else {
			TextBox = (
				<InputContextConsumer>
					{({ addInputItem, showErrors, inputArray }) => {
						if (!inputArray[this.id])
							addInputItem(this.id, { value: this.props.value, errorState: this.props.isError });
						return (
							<ElementWrapper style={styles.elementWrapper} json={this.payload} isError={this.props.isError} isFirst={this.props.isFirst}>
								<InputLabel isRequired={this.isRequired} label={label} />
								<TextInput
									style={this.getComputedStyles(showErrors)}
									autoCapitalize={Constants.NoneString}
									autoCorrect={false}
									accessible={true}
									accessibilityLabel={this.payload.altText}
									placeholder={placeholder}
									multiline={isMultiline}
									maxLength={maxLength}
									underlineColorAndroid={Constants.TransparentString}
									clearButtonMode={Constants.WhileEditingString}
									textContentType={this.textStyle}
									keyboardType={this.keyboardType}
									onFocus={this.props.handleFocus}
									onBlur={this.props.handleBlur}
									value={this.props.value}
									onChangeText={(text) => this.props.textValueChanged(text, addInputItem)}
								/>
							</ElementWrapper>
						);
					}}
				</InputContextConsumer>
			)
		}
		return (
			TextBox
		);
	}

	/**
	 * @description Return the input styles applicable based on the given payload
	 * @returns {Array} - Computed styles based on the config 
	 */
	getComputedStyles = (showErrors) => {
		const { isMultiline } = this;

		let inputComputedStyles = [this.styleConfig.input, styles.input];
		isMultiline ?
			inputComputedStyles.push(styles.multiLineHeight) :
			inputComputedStyles.push(styles.singleLineHeight);
		this.props.isError && showErrors && this.isRequired ?
			inputComputedStyles.push(this.styleConfig.borderAttention) :
			inputComputedStyles.push(this.styleConfig.inputBorderColor);

		return inputComputedStyles;
	}

	/**
	 * @description Parse hostConfig specific to this element
	 */
	parseHostConfig = () => {
		this.id = this.payload.id;
		this.type = this.payload.type;
		this.isMultiline = this.payload.isMultiline === undefined ? false : this.payload.isMultiline;
		//if this.payload.maxLength is undefined or null, then maximumLength value will be null. So it will automatically handled the undefined and null cases also...
		const maximumLength = Utils.convertStringToNumber(this.payload.maxLength);
		//We will pass the style as array, since it can be updated in the container wrapper if required.
		this.maxLength = typeof maximumLength === "number" ? maximumLength : undefined;
		this.placeholder = this.payload.placeholder;
		this.textStyle = Utils.getEffectiveInputStyle(this.props.styleValue);
		this.keyboardType = Utils.getKeyboardType(this.props.styleValue);
		this.inlineAction = this.payload.inlineAction;
		this.label = this.payload.label;
	}

	/**
	 * @description Invoked on every change in Input field
	 * @param {string} text
	 */
	textValueChanged = (text) => {
		this.setState({ text });
	}

	/**
	 * @description Invoked when json payload contains inlineAction prop
	 */
	inlineActionComponent = () => {
		return (
			<InputContextConsumer>
				{({ addInputItem, onExecuteAction, onParseError, inputArray, showErrors }) => {
					if (!inputArray[this.id])
						addInputItem(this.id, { value: this.props.value, errorState: this.props.isError });
					return this.parsePayload(addInputItem, onExecuteAction, onParseError, showErrors)
				}}
			</InputContextConsumer>
		);
	}

	/**
	 * @description Parse the given payload and render the card accordingly
	 */
	parsePayload = (addInputItem, onExecuteAction, onParseError, showErrors) => {
		const {
			id,
			type,
			isMultiline,
			placeholder,
			maxLength,
			payload,
			textStyle,
			keyboardType,
			inlineAction,
			label,
		} = this;

		if (!id || !type) {
			return null;
		}

		var returnKeyType = Constants.ReturnDone
		let wrapperStyle = [styles.inlineActionWrapper];
		wrapperStyle.push({ alignItems: Constants.CenterString })

		if (isMultiline) {
			wrapperStyle.push({ alignItems: Constants.FlexEnd })
			returnKeyType = Constants.ReturnDefault;
		}
		if (inlineAction.type == Enums.ElementType.ActionShowCard) {
			let error = {
				error: Enums.ValidationError.ActionTypeNotAllowed,
				message: ERROR_MESSAGE
			};
			onParseError(error);
			return null;
		}
		else {
			return (
				<View>
					<ElementWrapper json={payload} style={wrapperStyle} isError={this.props.isError} isFirst={this.props.isFirst}>
						<View style={styles.elementWrapper}>
							<InputLabel isRequired={this.isRequired} label={label} />
							<TextInput
								style={[styles.inlineActionTextInput, this.getComputedStyles(this.state.showInlineActionErrors)]}
								autoCapitalize={Constants.NoneString}
								autoCorrect={false}
								accessible={true}
								accessibilityLabel={payload.altText}
								placeholder={placeholder}
								multiline={isMultiline}
								maxLength={maxLength}
								returnKeyLabel={'submit'}
								returnKeyType={returnKeyType}
								onSubmitEditing={() => this.onClickHandle(onExecuteAction, 'onSubmit')}
								underlineColorAndroid={Constants.TransparentString}
								clearButtonMode={Constants.WhileEditingString}
								textContentType={textStyle}
								keyboardType={keyboardType}
								onFocus={this.handleFocus}
								onBlur={this.props.handleBlur}
								onChangeText={(text) => {
									this.props.textValueChanged(text, addInputItem);
									this.textValueChanged(text);
								}}
								value={this.props.value}
							/>
						</View>
						<TouchableOpacity onPress={() => { this.onClickHandle(onExecuteAction, Constants.InlineAction) }}>
							{Utils.isNullOrEmpty(inlineAction.iconUrl) ?
								<Text style={styles.inlineActionText}>{inlineAction.title}</Text> :
								<Image
									style={styles.inlineActionImage}
									source=
									{{ uri: inlineAction.iconUrl }} />
							}
						</TouchableOpacity>
					</ElementWrapper>
					{this.props.isError && (this.state.showInlineActionErrors || showErrors) && this.showErrorMessage()}
				</View>
			);
		}

	}

	handleFocus = () => {
		this.setState({
			showInlineActionErrors: false
		});
		this.props.handleFocus();
	}

	/**
	 * @description Displays validation error message for inline action
	 */

	showErrorMessage = () => {
		return (
			<Text style={this.styleConfig.defaultDestructiveButtonForegroundColor}>
				{this.errorMessage}
			</Text>
		)
	}

	/**
	   * @description Invoked on tapping the inline-action image component
	 * @param {string} onExecuteAction - the action handler
	 * @param {string} action - parameter to determine the origin of the action('onSubmit' OR 'inline-action')
	 */
	onClickHandle(onExecuteAction, action) {
		if (this.isMultiline && action != Constants.InlineAction)
			return;
		this.setState({ showInlineActionErrors: true });
		if (!this.props.isError && this.inlineAction.type === Constants.ActionSubmit) {
			let actionObject = {
				"type": Constants.ActionSubmit,
				"data": this.state.text
			};
			onExecuteAction(actionObject, true);
		}
		else if (!this.props.isError && this.inlineAction.type === Constants.ActionOpenUrl) {
			if (!Utils.isNullOrEmpty(this.inlineAction.url)) {
				let actionObject = {
					"type": Constants.ActionOpenUrl,
					"url": this.inlineAction.url
				};
				onExecuteAction(actionObject, true);
			}
		}
	}
}

const styles = StyleSheet.create({
	inlineActionText: {
		marginLeft: 5,
		marginTop: 15,
		color: '#3a3a3a',
	},
	multiLineHeight: {
		height: 88,
	},
	singleLineHeight: {
		height: 44,
	},
	elementWrapper: {
		flex: 1,
		marginVertical: 3
	},
	input: {
		width: Constants.FullWidth,
		padding: 5,
		marginTop: 3,
	},
	inlineActionWrapper: {
		flexDirection: 'row',
		backgroundColor: "transparent",
		borderRadius: 5
	},
	inlineActionTextInput: {
		padding: 5,
		flex: 1,
		backgroundColor: 'transparent',
		color: '#3a3a3a',
		borderColor: "#9E9E9E",
		borderWidth: 1,
	},
	inlineActionImage: {
		marginLeft: 10,
		width: 40,
		height: 40,
		backgroundColor: 'transparent',
		flexShrink: 0,
	},
});


