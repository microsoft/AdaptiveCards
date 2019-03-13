/**
 * SelectAction Component.
 */

import React from 'react';
import {
	TouchableOpacity,
} from 'react-native';
import { InputContext } from '../../utils/context';
import * as Constants from '../../utils/constants';
import * as Utils from '../../utils/util';

export class SelectAction extends React.Component {

	static contextType = InputContext;
	render() {
		const ButtonComponent = TouchableOpacity;
		return (<ButtonComponent onPress={() => { this.onClickHandle() }} style={this.props.style}>
			<React.Fragment>{this.props.children}</React.Fragment>
		</ButtonComponent>);
	}

	/**
	 * @description Invoked on tapping the button component
	 */
	onClickHandle() {
		switch (this.props.selectActionData.type) {
			case Constants.ActionSubmit:
				let actionObject = { "type": Constants.ActionSubmit, "data": this.props.selectActionData.data };
				this.context.onExecuteAction(actionObject);
				break;
			case Constants.ActionOpenUrl:
				if (!Utils.isNullOrEmpty(this.props.selectActionData.url)) {
					let actionObject = { "type": Constants.ActionOpenUrl, "url": this.props.selectActionData.url };
					this.context.onExecuteAction(actionObject);
				}
				break;
			case Constants.ActionToggleVisibility:
				this.context.toggleVisibilityForElementWithID(this.props.selectActionData.targetElements);
				break;
			default:
				break;
		}
	}
}
