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

import * as Utils from '../../utils/util';
import {
	InputContext,
	InputContextConsumer
} from '../../utils/context';
import * as Constants from '../../utils/constants';
import * as Enums from '../../utils/enums';


export class ActionButton extends React.Component {

	static contextType = InputContext;

	constructor(props) {
		super(props);

		this.payload = props.json;
		this.title = Constants.EmptyString;
		this.verb = Constants.EmptyString;
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
		this.hostConfig = props.configManager.hostConfig;
		this.styleConfig = props.configManager.styleConfig;
	}

	componentDidMount() {
		if (!Utils.isNullOrEmpty(this.payload.iconUrl)) {
			this.addResourceInformation(this.payload.iconUrl, "");
		}
	}

	getActionAlignment() {
		let computedStyles = [];
		if (this.hostConfig.actions.actionAlignment != Enums.ActionAlignment.Stretch) {
			computedStyles.push({ flexGrow: 0 })
		} else computedStyles.push({ flexGrow: 1 })
		if (this.hostConfig.actions.actionsOrientation === Enums.Orientation.Horizontal) {
			computedStyles.push({ maxWidth: this.props.maxWidth })
		}
		return computedStyles;
	}

	render() {
		if (!this.hostConfig.supportsInteractivity) {
			return null;
		}
		this.parsePayload();
		let computedStyle = [this.getActionAlignment()];
		computedStyle.push({ opacity: this.payload.isEnabled ? 1.0 : 0.4 })
		const ButtonComponent = Platform.OS === Constants.PlatformAndroid ? TouchableNativeFeedback : TouchableOpacity;
		return (<InputContextConsumer>
			{({ onExecuteAction, inputArray, addResourceInformation, toggleVisibilityForElementWithID }) => {
				this.inputArray = inputArray;
				this.onExecuteAction = onExecuteAction;
				this.addResourceInformation = addResourceInformation;
				this.toggleVisibilityForElementWithID = toggleVisibilityForElementWithID;

				return <ButtonComponent
					style={computedStyle}
					disabled={!this.payload.isEnabled}
					accessible={true}
					accessibilityLabel={this.altText}
					accessibilityRole={Constants.Button}
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
				this.onSubmitExecuteActionCalled();
				break;
			case Constants.ActionExecute:
				this.onSubmitExecuteActionCalled();
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
				//Invoked for the custom action type.
				this.onExecuteAction(this.payload);
				break;
		}
	}

	getMergeObject = () => {
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
		return mergedObject
	}

	/**
	 * @description Invoked for the action type Constants.ActionSubmit and Constants.ActionExecute
	 */
	onSubmitExecuteActionCalled() {
		const { type, verb = "", title = "", ignoreInputValidation } = this.payload;
		var actionObject = { "type": type, "title": title, "data": this.getMergeObject() };
		if (this.payload.type == Constants.ActionExecute) {
			actionObject["verb"] = verb
		}
		this.onExecuteAction(actionObject, ignoreInputValidation);
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

	parsePayload() {
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

		if (this.hostConfig.actions.actionAlignment != Enums.ActionAlignment.Stretch && this.hostConfig.actions.actionsOrientation === Enums.Orientation.Vertical) {
			switch (this.hostConfig.actions.actionAlignment) {
				case Enums.ActionAlignment.Center:
					computedStyles.push(styles.centerAlignment)
					break
				case Enums.ActionAlignment.Right:
					computedStyles.push(styles.rightAlignment)
					break
				default:
					computedStyles.push(styles.leftAlignment)
			}
		}

		computedStyles.push(this.props.style)
		return computedStyles;
	}

	/**
	* @description Return the button title styles applicable
	* @returns {Array} computedStyles - Styles based on the config
	*/
	getButtonTitleStyles = () => {
		var computedStyles = [this.styleConfig.defaultFontConfig,
		this.styleConfig.buttonTitle, this.props.titleStyle];
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
				<Text numberOfLines={1} style={this.getButtonTitleStyles()}>
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
	},
	leftAlignment: {
		alignSelf: Constants.FlexStart,
	},
	centerAlignment: {
		alignSelf: Constants.CenterString,
	},
	rightAlignment: {
		alignSelf: Constants.FlexEnd,
	}
});

