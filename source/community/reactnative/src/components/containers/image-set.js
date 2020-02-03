/**
 * ImageSet Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-imageset
 */

import React from 'react';

import { StyleSheet } from 'react-native';
import { Registry } from '../registration/registry';
import ElementWrapper from '../elements/element-wrapper';
import { InputContextConsumer } from '../../utils/context';
import * as Constants from '../../utils/constants';
import * as Enums from '../../utils/enums';

const FlexWrap = 'wrap';
const SizeKey = "size";
const ImageSetKey = "fromImageSet";

export class ImageSet extends React.PureComponent {

	constructor(props) {
		super(props);

		this.payload = props.json;
	}

    /**
     * @description Parse the given payload and render the card accordingly
     */
	parsePayload = (imageSetJson, onParseError) => {
		const renderedElement = [];
		if (!this.payload)
			return renderedElement;

		const register = Registry.getManager();
		// parse elements 
		// This function is repetitive across containers. Needs to be made Generic.
		imageSetJson.images.map((element, index) => {
			element[SizeKey] = this.payload.imageSize;
			element[ImageSetKey] = true;
			const Element = register.getComponentOfType(element.type);
			if (Element) {
				renderedElement.push(<Element json={element}
					key={`ELEMENT-${index}`} />);
			} else {
				let error = { "error": Enums.ValidationError.UnknownElementType, "message": `Unknown Type ${element.type} encountered` };
				onParseError(error);
				return null;
			}
		});
		return renderedElement;
	}

	internalRenderer(imageSetJson) {
		return (
			(<InputContextConsumer>
				{({ onParseError }) => <ElementWrapper json={imageSetJson} style={[styles.container, styles.defaultBGStyle]} isFirst={this.props.isFirst}>
					{this.parsePayload(imageSetJson, onParseError)}
				</ElementWrapper>}
			</InputContextConsumer>)
		);
	}

	render() {
		let containerRender = this.internalRenderer(this.props.json);
		return containerRender;
	}
}

const styles = StyleSheet.create({
	container: {
		flex: 1,
		flexDirection: Constants.FlexRow,
		flexWrap: FlexWrap,
	},
	defaultBGStyle: {
		backgroundColor: Constants.TransparentString,
	},
});