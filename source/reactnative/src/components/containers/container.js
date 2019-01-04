/**
 * Container Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-container
 */

import React from 'react';
import {
	View,
	StyleSheet
} from 'react-native';

import ElementWrapper from '../elements/element-wrapper';
import { Registry } from '../registration/registry';
import { SelectAction } from '../actions';
import * as Constants from '../../utils/constants';
import { HostConfigManager } from '../../utils/host-config';
import { InputContextConsumer } from '../../utils/context';

export class Container extends React.Component {

	constructor(props) {
		super(props);

		this.renderedElement = [];
		this.payload = props.json;
		this.selectionActionData = props.json.selectAction;
	}

    /**
     * @description Parse the given payload and render the card accordingly
     */
	parsePayload = (containerJson, onParseError) => {
		if (!this.payload)
			return this.renderedElement;
		// parse elements

		this.renderedElement.push(Registry.getManager().parseRegistryComponents(containerJson.items, onParseError));
		return this.renderedElement;
	}

	internalRenderer(containerJson) {
		let backgroundStyle = containerJson.style == Constants.Emphasis ?
			styles.emphasisStyle : styles.defaultBGStyle;

		// verticalContentAlignment property is not considered for now as the container size is determined by its content.
		var containerContent = (
			<InputContextConsumer>
				{({ onParseError }) =>
					(
						<View style={[styles.container, backgroundStyle]}>
							<ElementWrapper json={containerJson} style={backgroundStyle}>
								{this.parsePayload(containerJson, onParseError)}
							</ElementWrapper>
						</View>
					)
				}
			</InputContextConsumer>

		);
		if ((containerJson.selectAction === undefined)
			|| (HostConfigManager.getHostConfig().supportsInteractivity === false)) {
			return containerContent;
		} else {
			return <SelectAction selectActionData={containerJson.selectAction}>
				{containerContent}
			</SelectAction>;
		}
	}

	render() {
		let containerRender = this.internalRenderer(this.props.json);
		return containerRender;
	}
};

const styles = StyleSheet.create({
	container: {
		flex: 1,
	},
	defaultBGStyle: {
		backgroundColor: Constants.TransparentString,
	},
	emphasisStyle: {
		backgroundColor: Constants.EmphasisColor,
	},
});