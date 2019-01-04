/**
 * SelectAction Component.
 */

import React from 'react';
import {
	Platform,
	TouchableOpacity,
	TouchableNativeFeedback
} from 'react-native';
import { InputContextConsumer } from '../../utils/context';
import * as Constants from '../../utils/constants';
import * as Utils from '../../utils/util';

export class SelectAction extends React.Component {

	render() {
		const ButtonComponent = Platform.OS === Constants.PlatformIOS ? TouchableOpacity : TouchableNativeFeedback;

		return (<InputContextConsumer>
			{({ onExecuteAction }) => <ButtonComponent onPress={() => { this.onClickHandle(onExecuteAction) }} style={this.props.style}>
				{this.props.children}
			</ButtonComponent>}
		</InputContextConsumer>);
	}

    /**
     * @description Invoked on tapping the button component
     */
	onClickHandle(onExecuteAction) {
		if (this.props.selectActionData.type === Constants.ActionSubmit) {
			let actionObject = { "type": Constants.ActionSubmit, "data": this.props.selectActionData.data };
			onExecuteAction(actionObject);
		} else if (this.props.selectActionData.type === Constants.ActionOpenUrl && !Utils.isNullOrEmpty(this.props.selectActionData.url)) {
			let actionObject = { "type": Constants.ActionOpenUrl, "url": this.props.selectActionData.url };
			onExecuteAction(actionObject);
		}
	}
}
