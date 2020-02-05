/**
 * TextBlock Element.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-textblock
 */

import React from 'react';
import {
    StyleSheet,
    Text
} from 'react-native';
import ElementWrapper from '../components/elements/element-wrapper';
import * as Constants from '../utils/constants';



export class RatingRenderer extends React.Component {

	render() {
		let payload = this.props.json;

		if (payload.isVisible === false) {
			return null;
		}

		return (
			<ElementWrapper json={payload} style={styles.textContainer} isFirst={this.props.isFirst}>
                    <Text>{payload.rating}</Text>
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

