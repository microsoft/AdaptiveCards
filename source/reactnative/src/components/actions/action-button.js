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
import { InputContextConsumer, InputContext } from '../../utils/context';
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
		this.type = Constants.EmptyString;
		this.iconUrl = Constants.EmptyString;
		this.data = {};
		if (props.json.type === 'Action.ShowCard') {
			this.showCardHandler = props.onShowCardTapped;
		}
	}

	componentDidMount() {
		if (!Utils.isNullOrEmpty(this.payload.iconUrl)) {
			this.context.addResourceInformation(this.payload.iconUrl, "");
		}
	}

	render() {
		if (HostConfigManager.getHostConfig().supportsInteractivity === false) {
			return null;
		}
		this.parseHostConfig();

		const ButtonComponent = Platform.OS === Constants.PlatformIOS ? TouchableOpacity : TouchableNativeFeedback;

		if (this.payload.type === Constants.ActionSubmit) {
			return (<InputContextConsumer>
				{({ inputArray, onExecuteAction }) => (
					<ButtonComponent style={{ flexGrow: 1 }} onPress={() => {
						this.onSubmitActionCalled(inputArray, onExecuteAction)
					}}>
						{this.buttonContent()}
					</ButtonComponent>
				)}
			</InputContextConsumer>);
		}
		else if (this.payload.type === Constants.ActionOpenUrl) {
			return (<InputContextConsumer>
				{({ onExecuteAction }) => (<ButtonComponent style={{ flexGrow: 1 }} onPress={() => {
					this.onOpenURLCalled(onExecuteAction)
				}}>{this.buttonContent()}
				</ButtonComponent>)}
			</InputContextConsumer>);
		} else if (this.payload.type === Constants.ActionShowCard) {
			return (<ButtonComponent
				style={{ flexGrow: 1 }}
				onPress={this.changeShowCardState}>
				{this.buttonContent()}
			</ButtonComponent>)
		} else if (this.payload.type === Constants.ActionToggleVisibility) {
			return (<InputContextConsumer>
				{({ toggleVisibilityForElementWithID }) => (
					<ButtonComponent style={{ flexGrow: 1 }} onPress={() => {
						this.onToggleActionCalled(toggleVisibilityForElementWithID)
					}}>
						{this.buttonContent()}
					</ButtonComponent>
				)}
			</InputContextConsumer>);
		}
	}

    /**
     * @description Invoked for the action type Constants.ActionSubmit
     */
	onSubmitActionCalled(inputItem, onExecuteAction) {
		let mergedObject = null;
		if (this.data !== null) {
			mergedObject = { ...this.data, ...inputItem };
		} else {
			mergedObject = inputItem;
		}
		let actionObject = { "type": this.payload.type, "data": mergedObject };
		onExecuteAction(actionObject);
	}

	/**
     * @description Invoked for the action type Constants.ActionToggleVisibility
     */
	onToggleActionCalled(toggleVisibilityForElementWithID){
		toggleVisibilityForElementWithID(this.payload.targetElements);
	}


	onOpenURLCalled = (onExecuteAction) => {
		let actionObject = { "type": this.payload.type, "url": this.payload.url };
		onExecuteAction(actionObject);
	}

	changeShowCardState = () => {
		this.showCardHandler(this.payload.card);
	}

	parseHostConfig() {
		this.title = this.payload.title;
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
		let computedStyles = [this.styleConfig.buttonBackgroundColor,
		this.styleConfig.buttonBorderRadius,
		this.styleConfig.actionIconFlex,
		styles.button];
		if (this.sentiment == Enums.Sentiment.Positive) {
			computedStyles.push(this.styleConfig.defaultPositiveButtonBackgroundColor);
		}

		return computedStyles;
	}

	/**
	* @description Return the button title styles applicable
	* @returns {Array} computedStyles - Styles based on the config
	*/
	getButtonTitleStyles = () => {
		var computedStyles = [this.styleConfig.fontConfig,
		this.styleConfig.buttonTitleColor,
		this.styleConfig.buttonTitleTransform];
		if (this.sentiment == Enums.Sentiment.Destructive) {
			computedStyles.push(this.styleConfig.defaultDestructiveButtonForegroundColor);
		}
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
		marginRight: 10,
		flexGrow: 1,
	},
	buttonIcon: {
		marginLeft: 5,
		marginRight: 10,
	}
});

