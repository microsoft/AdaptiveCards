/**
 * Actions Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-action.openurl
 */

import React from 'react';
import {
	Text,
	View,
	StyleSheet,
	Image,
	Platform,
	TouchableOpacity,
	TouchableNativeFeedback
} from 'react-native';

import { StyleManager } from '../../styles/style-config';
import * as Utils from '../../utils/util';
import {
	InputContext,
	InputContextConsumer
} from '../../utils/context';
import * as Constants from '../../utils/constants';
import { HostConfigManager } from '../../utils/host-config';
import * as Enums from '../../utils/enums';


export class ActionButton extends React.Component {

	styleConfig = StyleManager.getManager().styles;
	static contextType = InputContext;

	constructor(props) {
		super(props);

		this.payload = props.json;
		this.title = Constants.EmptyString;
		this.altText = Constants.EmptyString;
		this.type = Constants.EmptyString;
		this.iconUrl = Constants.EmptyString;
		this.inputArray = undefined;
		this.onExecuteAction = undefined;
		this.addResourceInformation = undefined;
		this.toggleVisibilityForElementWithID = undefined;
		this.data = {};
		if (props.json.type === 'Action.ShowCard') {
			this.showCardHandler = props.onShowCardTapped;
		}
	}

	componentDidMount() {
		if (!Utils.isNullOrEmpty(this.payload.iconUrl)) {
			this.addResourceInformation(this.payload.iconUrl, "");
		}
	}

	render() {
		if (HostConfigManager.getHostConfig().supportsInteractivity === false) {
			return null;
		}
		this.parseHostConfig();

		const ButtonComponent = Platform.OS === Constants.PlatformAndroid ? TouchableNativeFeedback : TouchableOpacity;

		return (<InputContextConsumer>
			{({ onExecuteAction, inputArray, addResourceInformation, toggleVisibilityForElementWithID }) => {
				this.inputArray = inputArray;
				this.onExecuteAction = onExecuteAction;
				this.addResourceInformation = addResourceInformation;
				this.toggleVisibilityForElementWithID = toggleVisibilityForElementWithID;

				return <ButtonComponent
					style={{ flexGrow: 1 }}
					accessible={true}
					accessibilityLabel={this.altText}
					onPress={this.onActionButtonTapped}>
					{this.buttonContent()}
				</ButtonComponent>
			}}
		</InputContextConsumer>);
	}

	/**
	 * @description Invoked for the any action button selected
	 */
	onActionButtonTapped = () => {
		switch (this.payload.type) {
			case Constants.ActionSubmit:
				this.onSubmitActionCalled();
				break;
			case Constants.ActionOpenUrl:
				this.onOpenURLCalled();
				break;
			case Constants.ActionShowCard:
				this.changeShowCardState();
				break;
			case Constants.ActionToggleVisibility:
				this.onToggleActionCalled();
				break;
			default:
				break;
		}
	}

	/**
	 * @description Invoked for the action type Constants.ActionSubmit
	 */
	onSubmitActionCalled() {
		let mergedObject = {};
		for (const key in this.inputArray) {
			mergedObject[key] = this.inputArray[key].value;
		}
		if (this.data !== null) {
			if (this.data instanceof Object)
				mergedObject = { ...mergedObject, ...this.data }
			else
				mergedObject["actionData"] = this.data;
		}
		let actionObject = { "type": this.payload.type, "data": mergedObject };
		this.onExecuteAction(actionObject, this.payload.ignoreInputValidation === true);
	}

	/**
	 * @description Invoked for the action type Constants.ActionToggleVisibility
	 */
	onToggleActionCalled() {
		this.toggleVisibilityForElementWithID(this.payload.targetElements);
	}


	onOpenURLCalled = () => {
		let actionObject = { "type": this.payload.type, "url": this.payload.url };
		this.onExecuteAction(actionObject);
	}

	changeShowCardState = () => {
		this.showCardHandler(this.payload.children[0]);
	}

	parseHostConfig() {
		this.title = this.payload.title;
		this.altText = this.payload.altText || this.title;
		this.type = this.payload.type;
		let imageUrl = this.payload.iconUrl
		this.iconUrl = Utils.getImageUrl(imageUrl)
		this.data = this.payload.data;
		this.sentiment = this.payload.sentiment;
		this.sentiment = Utils.parseHostConfigEnum(
			Enums.Sentiment,
			this.payload.sentiment,
			Enums.Sentiment.Default
		);
	}

	/**
	 * @description Return the button styles applicable
	 * @returns {Array} computedStyles - Styles based on the config
	 */
	getButtonStyles = () => {
		let computedStyles = [this.styleConfig.button,
		this.styleConfig.actionIconFlex, styles.button];

		if (this.sentiment == Enums.Sentiment.Positive) {
			computedStyles.push(this.styleConfig.defaultPositiveButtonBackgroundColor);
		} else if (this.sentiment == Enums.Sentiment.Destructive) {
			computedStyles.push(this.styleConfig.defaultDestructiveButtonBackgroundColor);
		}

		return computedStyles;
	}

	/**
	* @description Return the button title styles applicable
	* @returns {Array} computedStyles - Styles based on the config
	*/
	getButtonTitleStyles = () => {
		var computedStyles = [this.styleConfig.defaultFontConfig,
		this.styleConfig.buttonTitle];
		return computedStyles;
	}

	buttonContent = () => {
		return (
			<View
				style={this.getButtonStyles()}>
				{
					!Utils.isNullOrEmpty(this.iconUrl) ?
						<Image resizeMode="center"
							source={{ uri: this.iconUrl }}
							style={[styles.buttonIcon, this.styleConfig.actionIcon]} />
						: null
				}
				<Text style={this.getButtonTitleStyles()}>
					{this.title}
				</Text>
			</View>
		);
	};
}

const styles = StyleSheet.create({
	button: {
		alignItems: Constants.CenterString,
		justifyContent: Constants.CenterString,
		padding: 10,
		marginBottom: 10,
		flexGrow: 1,
		marginHorizontal: 5
	},
	buttonIcon: {
		marginLeft: 5,
		marginRight: 10,
	}
});

