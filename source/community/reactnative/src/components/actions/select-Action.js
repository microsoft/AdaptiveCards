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
				let actionObject = { "type": Constants.ActionSubmit, "data": this.props.selectActionData.data };
				this.onExecuteAction(actionObject);
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
				this.onCustomActionCalled();
				break;
		}
	}

	/**
	 * @description Invoked for the custom action type
	 */
	onCustomActionCalled() {
		let actionObject = {};
		for (let key in this.payload) {
			if (this.payload.hasOwnProperty(key)) {
				actionObject[key] = this.payload[key];
			}
		}
		this.onExecuteAction(actionObject);
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

				return <ButtonComponent onPress={() => { this.onClickHandle() }} style={this.props.style}>
					<React.Fragment>{this.props.children}</React.Fragment>
				</ButtonComponent>
			}}
		</InputContextConsumer>);
	}
}
