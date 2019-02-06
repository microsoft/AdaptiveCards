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

	componentDidMount(){
		if(!Utils.isNullOrEmpty(this.payload.iconUrl)){
			this.context.addResourceInformation(this.payload.iconUrl,"");
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
		this.iconUrl = this.payload.iconUrl;
		this.data = this.payload.data;
	}

	buttonContent = () => {
		return (
			<View
				style={[
					styles.button, this.styleConfig.actionIconFlex]}>
				{
					!Utils.isNullOrEmpty(this.iconUrl) ?
						<Image resizeMode="center"
							source={{ uri: this.iconUrl }}
							style={[styles.buttonIcon, this.styleConfig.actionIcon]} />
						: null
				}
				<Text style={[styles.buttonTitle, this.styleConfig.fontConfig]}>
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
		backgroundColor: "#1D9BF6",
		borderRadius: 15,
		flexGrow: 1,
	},
	buttonTitle: {
		color: Constants.WhiteColor,
	},
	buttonIcon: {
		marginLeft: 5,
		marginRight: 10,
	}
});

