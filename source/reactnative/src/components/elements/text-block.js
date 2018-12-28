/**
 * TextBlock Element.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-textblock
 */

import React from 'react';
import {
	StyleSheet
} from 'react-native';

import { HostConfigManager } from '../../utils/host-config';
import { StyleManager } from '../../styles/style-config';
import ElementWrapper from '../elements/element-wrapper';
import { Label } from './';
import * as Constants from '../../utils/constants';

export class TextBlock extends React.Component {

	hostConfig = HostConfigManager.getHostConfig();
	styleConfig = StyleManager.getManager().styles;

	render() {
		let payload = this.props.json;

		return (
			<ElementWrapper json={payload} style={styles.textContainer}>
				<Label
					text={payload.text}
					size={payload.size}
					weight={payload.weight}
					color={payload.color}
					isSubtle={payload.isSubtle}
					wrap={payload.wrap}
					align={payload.horizontalAlignment}
					maxLines={payload.maxLines}
					style={styles.text} />
			</ElementWrapper>
		);
	}
}

const styles = StyleSheet.create({
	textContainer: {
		width: Constants.FullWidth,
		alignItems: Constants.CenterString,
		backgroundColor: 'transparent',
	},
	text: {
		width: Constants.FullWidth
	}
});

