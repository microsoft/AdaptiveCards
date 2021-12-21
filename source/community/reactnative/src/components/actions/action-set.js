/**
 * ActionSet Element.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-textblock
 */

import React from 'react';
import ElementWrapper from '../elements/element-wrapper';
import { ActionWrapper } from './action-wrapper';

export class ActionSet extends React.Component {

	render() {
		const payload = this.props.json;
		const styleConfig = this.props.configManager.styleConfig;

		return (
			<ElementWrapper configManager={this.props.configManager} style={styleConfig.actionSet} json={payload} isFirst={this.props.isFirst}>
				<ActionWrapper configManager={this.props.configManager} actions={payload.actions} />
			</ElementWrapper>
		);
	}
}

