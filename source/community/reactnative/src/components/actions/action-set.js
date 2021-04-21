/**
 * ActionSet Element.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-textblock
 */

import React from 'react';
import {
	StyleSheet
} from 'react-native';

import ElementWrapper from '../elements/element-wrapper';
import { ActionWrapper } from './action-wrapper';

export class ActionSet extends React.Component {

	render() {
		let payload = this.props.json;

		return (
			<ElementWrapper configManager={this.props.configManager} json={payload} isFirst={this.props.isFirst}>
				<ActionWrapper configManager={this.props.configManager} actions={payload.actions} />
			</ElementWrapper>
		);
	}
}

