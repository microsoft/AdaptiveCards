/**
 * InputText Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputtext
 */

import React from 'react';
import {
	StyleSheet,
	TextInput
} from 'react-native';

import { InputContextConsumer } from '../../utils/context';
import ElementWrapper from '../elements/element-wrapper';
import { StyleManager } from '../../styles/style-config';
import * as Constants from '../../utils/constants';
import { HostConfigManager } from '../../utils/host-config';

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

		return (
			<InputContextConsumer>
				{({ addInputItem }) => (
					<ElementWrapper json={this.payload}>
						<TextInput
							style={this.getComputedStyles()}
							autoCapitalize={Constants.NoneString}
							autoCorrect={false}
							placeholder={placeholder}
							multiline={isMultiline}
							maxLength={maxLength}
							underlineColorAndroid={Constants.TransparentString}
							clearButtonMode={Constants.WhileEditingString}
							textContentType={this.props.textStyle}
							keyboardType={this.props.keyboardType}
							onFocus={this.props.handleFocus}
							onBlur={this.props.handleBlur}
							onChangeText={(text) => this.props.textValueChanged(text, addInputItem)}
							value={this.props.value}
						/>
					</ElementWrapper>
				)}
			</InputContextConsumer>
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
	}
}

const styles = StyleSheet.create({
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
		marginTop: 15,
		borderWidth: 1,
		backgroundColor: Constants.WhiteColor,
		borderRadius: 5,
	},
});


