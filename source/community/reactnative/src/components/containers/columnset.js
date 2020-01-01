/**
 * ColumnSet Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-columnset
 */

import React from 'react';
import {
	StyleSheet
} from 'react-native';

import { SelectAction } from '../actions';
import ElementWrapper from '../elements/element-wrapper';
import { Column } from "./column";
import * as Constants from '../../utils/constants';
import { HostConfigManager } from '../../utils/host-config';
import { ContainerWrapper } from './';

export class ColumnSet extends React.PureComponent {

	constructor(props) {
		super(props);
		this.payload = props.json;
	}

    /**
     * @description Parse the given payload and render the card accordingly
	 * @returns {object} Return the child elements of the columnset
     */
	parsePayload = () => {
		const payload = this.payload;
		const children = [];
		if (!this.payload)
			return children;

		// parse elements
		payload.columns.map((element, index) => {
			children.push(
				<Column json={element}
					columns={payload.columns}
					key={`ELEMENT-${index}`}
					isFirst={index === 0}
					isLast={index === payload.columns.length - 1}
				/>);
		});
		return children.map(ChildElement => React.cloneElement(ChildElement, { containerStyle: this.payload.style }));
	}

	internalRenderer() {
		const payload = this.payload;

		var columnSetContent = (
			<ContainerWrapper style={{ flex: this.payload.columns.length }} json={payload} containerStyle={this.props.containerStyle}>
				<ElementWrapper json={payload} isColumnSet={true} style={styles.defaultBGStyle} isFirst={this.props.isFirst}>
					{this.parsePayload()}
				</ElementWrapper>
			</ContainerWrapper>
		);

		if ((payload.selectAction === undefined) ||
			(HostConfigManager.supportsInteractivity() === false)) {
			return columnSetContent;
		} else {
			return <SelectAction selectActionData={payload.selectAction}>
				{columnSetContent}
			</SelectAction>;
		}
	}

	render() {
		let containerRender = this.internalRenderer();
		return containerRender;
	}
};

const styles = StyleSheet.create({
	defaultBGStyle: {
		backgroundColor: Constants.TransparentString,
		flexDirection: Constants.FlexRow,
	},
});