/**
 * TextBlock Element.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-textblock
 */

import React from 'react';
import {
	StyleSheet
} from 'react-native';

import ElementWrapper from '../elements/element-wrapper';
import { Label } from './';
import * as Constants from '../../utils/constants';

export class TextBlock extends React.Component {

	render() {
		let payload = this.props.json;

		if (payload.isVisible === false) {
			return null;
		}
		
		return (
			<ElementWrapper configManager={this.props.configManager} json={payload} style={styles.textContainer} isFirst={this.props.isFirst}>
				<Label
					text={payload.text}
					altText={payload.altText}
					size={payload.size}
					weight={payload.weight}
					color={payload.color}
					isSubtle={payload.isSubtle}
					fontStyle={payload.fontStyle}
					wrap={payload.wrap}
					align={payload.horizontalAlignment}
					maxLines={payload.maxLines}
					style={[styles.text, this.props.style]}
					configManager={this.props.configManager}
					containerStyle={this.props.containerStyle} />
			</ElementWrapper>
		);
	}
}

const styles = StyleSheet.create({
	textContainer: {
		alignItems: Constants.CenterString,
		backgroundColor: 'transparent',
	},
	text: {
		width: Constants.FullWidth
	}
});

