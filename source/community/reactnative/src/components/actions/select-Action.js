/**
 * SelectAction Component.
 */

import React from 'react';
import {
	TouchableOpacity,
} from 'react-native';
import {
	InputContext,
	InputContextConsumer
} from '../../utils/context';
import * as Constants from '../../utils/constants';
import * as Utils from '../../utils/util';
import { HostConfigManager } from '../../utils/host-config';

export class SelectAction extends React.Component {

	static contextType = InputContext;

	constructor(props) {
		super(props);

		this.payload = this.props.selectActionData;
		this.onExecuteAction = undefined;
		this.toggleVisibilityForElementWithID = undefined;
	}

	/**
	 * @description Invoked on tapping the button component
	 */
	onClickHandle() {
		switch (this.payload.type) {
			case Constants.ActionSubmit:
				const { type, title = "", data } = this.payload;
				this.onExecuteAction({type, title, data});
				break;
			case Constants.ActionOpenUrl:
				if (!Utils.isNullOrEmpty(this.props.selectActionData.url)) {
					let actionObject = { "type": Constants.ActionOpenUrl, "url": this.props.selectActionData.url };
					this.onExecuteAction(actionObject);
				}
				break;
			case Constants.ActionToggleVisibility:
				this.toggleVisibilityForElementWithID(this.props.selectActionData.targetElements);
				break;
			default:
				//As per the AC schema, ShowCard action type is not supported by selectAction.
				if (this.payload.type != Constants.ActionShowCard) {
					//Invoked for the custom action type. 
					this.onExecuteAction(this.payload);
				}
				break;
		}
	}

	render() {
		if (HostConfigManager.getHostConfig().supportsInteractivity === false) {
			return null;
		}

		const ButtonComponent = TouchableOpacity;
		return (<InputContextConsumer>
			{({ onExecuteAction, toggleVisibilityForElementWithID }) => {
				this.onExecuteAction = onExecuteAction;
				this.toggleVisibilityForElementWithID = toggleVisibilityForElementWithID;

				return <ButtonComponent
					onPress={() => { this.onClickHandle() }}
					accessible={true}
					accessibilityLabel={this.payload.altText}
					accessibilityRole={Constants.Button}
					style={this.props.style}>
					<React.Fragment>{this.props.children}</React.Fragment>
				</ButtonComponent>
			}}
		</InputContextConsumer>);
	}
}
