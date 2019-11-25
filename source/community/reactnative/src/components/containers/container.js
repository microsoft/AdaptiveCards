/**
 * Container Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-container
 */

import React from 'react';
import {
	StyleSheet
} from 'react-native';

import ElementWrapper from '../elements/element-wrapper';
import { Registry } from '../registration/registry';
import { SelectAction } from '../actions';
import * as Constants from '../../utils/constants';
import * as Utils from '../../utils/util';
import { HostConfigManager } from '../../utils/host-config';
import { InputContext } from '../../utils/context';
import { ContainerWrapper } from './';

export class Container extends React.Component {

	static contextType = InputContext;

	constructor(props) {
		super(props);
		this.payload = props.json;
		this.selectionActionData = props.json.selectAction;
	}

    /**
     * @description Parse the given payload and render the card accordingly
	 * @returns {object} Return the child elements of the container
     */
	parsePayload = () => {
		let children = [];
		if (!this.payload) {
			return children;
		}

		if (this.payload.isFallbackActivated) {
			if (this.payload.fallbackType == "drop") {
				return null;
			} else if (!Utils.isNullOrEmpty(element.fallback)) {
				return Registry.getManager().parseComponent(this.payload.fallback, this.context.onParseError);
			}
		}

		children = Registry.getManager().parseRegistryComponents(this.payload.items, this.context.onParseError);
		return children.map((ChildElement, index) => React.cloneElement(ChildElement, { containerStyle: this.payload.style, isFirst: index === 0 }));
	}

	internalRenderer = () => {
		const payload = this.payload;
		const minHeight = Utils.convertStringToNumber(payload.minHeight);
		const containerStyle = [styles.container, minHeight && { minHeight }];

		var containerContent = (
			<ContainerWrapper json={this.payload} style={containerStyle} containerStyle={this.props.containerStyle}>
				<ElementWrapper json={this.payload} style={[styles.defaultBGStyle, { flexGrow: 0 }]} isFirst={this.props.isFirst}>
					{this.parsePayload()}
				</ElementWrapper>
			</ContainerWrapper>
		);
		if ((payload.selectAction === undefined)
			|| (HostConfigManager.supportsInteractivity() === false)) {
			return containerContent;
		} else {
			return <SelectAction selectActionData={payload.selectAction}>
				{containerContent}
			</SelectAction>;
		}
	}

	render() {
		let containerRender = this.internalRenderer();
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
});