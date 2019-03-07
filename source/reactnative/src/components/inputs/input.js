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
	TouchableOpacity,
} from 'react-native';

import { InputContextConsumer } from '../../utils/context';
import ElementWrapper from '../elements/element-wrapper';
import { StyleManager } from '../../styles/style-config';
import * as Constants from '../../utils/constants';
import { HostConfigManager } from '../../utils/host-config';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';


export class Input extends React.Component {

	styleConfig = StyleManager.getManager().styles;

	constructor(props) {
		super(props);

		this.payload = props.json;
		this.id = Constants.EmptyString;
		this.isMultiline = Boolean;
		this.maxlength = 0;
		this.placeHolder = Constants.EmptyString;
		this.type = Constants.EmptyString;
		this.value = Constants.EmptyString;
		this.keyboardType = Constants.EmptyString;
		this.textStyle = Constants.EmptyString;
		this.inlineAction = {};
		this.state = {
			isError: false,
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
			payload,
			textStyle,
			keyboardType,
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
					{({ addInputItem }) => (
						<ElementWrapper json={payload} style={this.receivedStyle}>
							<TextInput
								style={[this.getComputedStyles(), this.receivedStyle]}
								autoCapitalize={Constants.NoneString}
								autoCorrect={false}
								placeholder={placeholder}
								multiline={isMultiline}
								maxLength={maxLength}
								underlineColorAndroid={Constants.TransparentString}
								clearButtonMode={Constants.WhileEditingString}
								textContentType={textStyle}
								keyboardType={keyboardType}
								onFocus={this.props.handleFocus}
								onBlur={this.props.handleBlur}
								onChangeText={(text) => {
									this.props.textValueChanged(text, addInputItem);
								}}
								value={this.props.value}
							/>
						</ElementWrapper>
					)}
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
	getComputedStyles = () => {
		const { isMultiline } = this;

		let inputComputedStyles = [this.styleConfig.inputBorderWidth,
		this.styleConfig.inputBackgroundColor,
		this.styleConfig.inputBorderRadius,
		this.styleConfig.fontConfig,
		styles.input];
		isMultiline ?
			inputComputedStyles.push(styles.multiLineHeight) :
			inputComputedStyles.push(styles.singleLineHeight);
		this.props.isError ?
			inputComputedStyles.push(this.styleConfig.borderAttention) :
			inputComputedStyles.push(this.styleConfig.inputBorderColor);

		return inputComputedStyles;
	}

    /**
     * @description Parse hostconfig specific to this element
     */
	parseHostConfig = () => {
		this.id = this.payload.id;
		this.type = this.payload.type;
		this.isMultiline = this.payload.isMultiline === undefined ? false : this.payload.isMultiline;
		this.maxLength = (this.payload.maxLength == undefined ||
			this.payload.maxLength == 0) ? Number.MAX_VALUE : this.payload.maxLength;
		this.placeholder = this.payload.placeholder;
		this.textStyle = Utils.getEffectiveInputStyle(this.props.styleValue);
		this.keyboardType = Utils.getKeyboardType(this.props.styleValue);
		this.inlineAction = this.payload.inlineAction;
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
				{({ addInputItem, onExecuteAction, onParseError }) =>
					this.parsePayload(addInputItem, onExecuteAction, onParseError)
				}
			</InputContextConsumer>
		);
	}

	/**
	 * @description Parse the given payload and render the card accordingly
	 */
	parsePayload = (addInputItem, onExecuteAction, onParseError) => {
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
		} = this;

		if (!id || !type) {
			return null;
		}

		var returnKeyType = "done"
		let wrapperStyle = [styles.inlineActionWrapper];
		wrapperStyle.push({ alignItems: 'center' })

		if (isMultiline) {
			wrapperStyle.push({ alignItems: 'flex-end' })
			returnKeyType = "default";
		}
		if (inlineAction.type === "Action.ShowCard") {
			let error = {
				"error": Enums.ValidationError.ActionTypeNotAllowed,
				"message": `Inline ShowCard is not supported as of now`
			};
			onParseError(error);
			return null;
		}
		else {
			return (
				<ElementWrapper json={payload} style={wrapperStyle}>
					<TextInput
						style={[this.getComputedStyles(), styles.inlineActionTextInput]}
						autoCapitalize={Constants.NoneString}
						autoCorrect={false}
						placeholder={placeholder}
						placeholderTextColor='#3a3a3a'
						multiline={isMultiline}
						maxLength={maxLength}
						returnKeyLabel={'submit'}
						returnKeyType={returnKeyType}
						onSubmitEditing={() => this.onClickHandle(onExecuteAction, 'onSubmit')}
						underlineColorAndroid={Constants.TransparentString}
						clearButtonMode={Constants.WhileEditingString}
						textContentType={textStyle}
						keyboardType={keyboardType}
						onFocus={this.props.handleFocus}
						onBlur={this.props.handleBlur}
						onChangeText={(text) => {
							this.props.textValueChanged(text, addInputItem);
							this.textValueChanged(text);
						}}
						value={this.props.value}
					/>
					<TouchableOpacity onPress={() => { this.onClickHandle(onExecuteAction, 'inline-action') }}>
						{Utils.isNullOrEmpty(inlineAction.iconUrl) ?
							<Text style={styles.inlineActionText}>{inlineAction.title}</Text> :
							<Image
								style={styles.inlineActionImage}
								source=
								{{ uri: inlineAction.iconUrl }} />
						}
					</TouchableOpacity>
				</ElementWrapper>
			);
		}

	}

	/**
 	 * @description Invoked on tapping the inline-action image component
	 * @param {string} onExecuteAction - the action handler
	 * @param {string} action - parameter to determine the origin of the action('onSubmit' OR 'inline-action')
	 */
	onClickHandle(onExecuteAction, action) {
		if (this.isMultiline && action != 'inline-action')
			return;

		if (this.inlineAction.type === Constants.ActionSubmit) {
			let actionObject = {
				"type": Constants.ActionSubmit,
				"data": this.state.text
			};
			onExecuteAction(actionObject);
		}
		else if (this.inlineAction.type === Constants.ActionOpenUrl) {
			if (!Utils.isNullOrEmpty(this.inlineAction.url)) {
				let actionObject = {
					"type": Constants.ActionOpenUrl,
					"url": this.inlineAction.url
				};
				onExecuteAction(actionObject);
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
	input: {
		width: Constants.FullWidth,
		padding: 5,
		marginTop: 15,
	},
	inlineActionWrapper: {
		flexDirection: 'row',
		backgroundColor: "transparent",
		borderRadius: 5,
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
		marginTop: 15,
		backgroundColor: 'transparent',
		flexShrink: 0,
	},
});


