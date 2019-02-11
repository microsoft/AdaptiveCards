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
			maxLength
		} = this;

		if (!id || !type) {
			return null;
		}

		if (!Utils.isNullOrEmpty(this.inlineAction)) {
			if (this.inlineAction.type === "Action.ShowCard") {
				let error = { "error": Enums.ValidationError.ActionTypeNotAllowed, "message": `Inline ShowCard is not supported as of now` };
				onParseError(error);
				return null;
			}
			TextBox = this.inlineActionComponent();
		}
		else {
			TextBox = (
				<InputContextConsumer>
					{({ addInputItem }) => (
						<ElementWrapper json={this.payload} style={this.receivedStyle}>
							<TextInput
								style={[this.getComputedStyles(), this.receivedStyle]}
								autoCapitalize={Constants.NoneString}
								autoCorrect={false}
								placeholder={placeholder}
								multiline={isMultiline}
								maxLength={maxLength}
								underlineColorAndroid={Constants.TransparentString}
								clearButtonMode={Constants.WhileEditingString}
								textContentType={this.textStyle}
								keyboardType={this.keyboardType}
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
     */
	getComputedStyles = () => {
		const { isMultiline } = this;

		let inputComputedStyles = [styles.input, this.styleConfig.fontConfig];
		isMultiline ?
			inputComputedStyles.push(styles.multiLineHeight) :
			inputComputedStyles.push(styles.singleLineHeight);
		this.props.isError ?
			inputComputedStyles.push(this.styleConfig.borderAttention) :
			inputComputedStyles.push(styles.withBorderColor);

		return inputComputedStyles;
	}

    /**
     * @description Parse hostconfig specific to this element
     */
	parseHostConfig = () => {
		this.id = this.payload.id;
		this.type = this.payload.type;
		this.isMultiline = (this.payload.isMultiline !== undefined) ? this.payload.isMultiline : false;
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
		const {
			id,
			type,
			isMultiline,
			placeholder,
			maxLength
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
		return (
			<InputContextConsumer>
				{({ addInputItem, onExecuteAction }) => (
					<ElementWrapper json={this.payload} style={wrapperStyle}>
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
							onSubmitEditing={() => this.onClickHandle(onExecuteAction)}
							underlineColorAndroid={Constants.TransparentString}
							clearButtonMode={Constants.WhileEditingString}
							textContentType={this.textStyle}
							keyboardType={this.keyboardType}
							onFocus={this.props.handleFocus}
							onBlur={this.props.handleBlur}
							onChangeText={(text) => {
								this.props.textValueChanged(text, addInputItem);
								this.textValueChanged(text);
							}}
							value={this.props.value}
						/>
						<TouchableOpacity onPress={() => { this.onClickHandle(onExecuteAction) }}>
							{Utils.isNullOrEmpty(this.inlineAction.iconUrl) ?
								<Text style={styles.inlineActionText}>{this.inlineAction.title}</Text> :
								<Image
									style={styles.inlineActionImage}
									source=
									{{ uri: this.inlineAction.iconUrl }} />
							}
						</TouchableOpacity>
					</ElementWrapper>
				)}
			</InputContextConsumer>
		);

	}

	/**
 	* @description Invoked on tapping the image component
	*/
	onClickHandle(onExecuteAction) {
		if (this.payload.inlineAction.type === Constants.ActionSubmit && !this.isMultiline) {
			let actionObject = { "type": Constants.ActionSubmit, "data": this.state.text };
			onExecuteAction(actionObject);
		}
	}
}

const styles = StyleSheet.create({
	inlineActionText: {
		marginLeft: 5,
		color: '#3a3a3a',
	},
	withBorderColor: {
		borderColor: Constants.LightGreyColor,
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
		borderWidth: 1,
		backgroundColor: Constants.WhiteColor,
		borderRadius: 5,
	},
	inlineActionWrapper: {
		flexDirection: 'row',
		backgroundColor: "transparent",
		borderRadius: 5,
	},
	inlineActionTextInput: {
		padding: 5,
		width: '85%',
		backgroundColor: 'transparent',
		color: '#3a3a3a',
		borderColor:"#9E9E9E",
		borderWidth: 1,
	},
	inlineActionImage: {
		marginLeft: 10,
		width: 20,
		height: 20,
		backgroundColor: 'transparent',
	},
});


