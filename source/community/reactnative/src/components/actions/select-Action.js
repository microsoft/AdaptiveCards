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
		let actionPayload = { ... this.payload };
		switch (actionPayload.type) {
			case Constants.ActionOpenUrl:
				if (!Utils.isNullOrEmpty(this.props.selectActionData.url)) {
					actionPayload.url = this.props.selectActionData.url;
					this.onExecuteAction(actionPayload);
				}
				break;
			case Constants.ActionToggleVisibility:
				this.toggleVisibilityForElementWithID(this.props.selectActionData.targetElements);
				break;
			default:
				//As per the AC schema, ShowCard action type is not supported by selectAction.
				if (actionPayload.type != Constants.ActionShowCard) {
					//Pass complete payload for all other types. 
					this.onExecuteAction(actionPayload);
				}
				break;
		}
	}

	render() {
		if (!this.props.configManager.hostConfig.supportsInteractivity) {
			return null;
		}

		const ButtonComponent = TouchableOpacity;
		return (<InputContextConsumer>
			{({ onExecuteAction, toggleVisibilityForElementWithID }) => {
				this.onExecuteAction = onExecuteAction;
				this.toggleVisibilityForElementWithID = toggleVisibilityForElementWithID;

				return <ButtonComponent
					onPress={() => { this.onClickHandle() }}
					disabled={this.payload.isEnabled == undefined ? false : !this.payload.isEnabled} //isEnabled defaults to true
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
