/**
 * ColumnSet Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-columnset
 */

import React from 'react';
import {
	View,
	StyleSheet
} from 'react-native';

import { SelectAction } from '../actions';
import ElementWrapper from '../elements/element-wrapper';
import { Column } from "./column";
import * as Constants from '../../utils/constants';
import { HostConfigManager } from '../../utils/host-config';

export class ColumnSet extends React.PureComponent {

	constructor(props) {
		super(props);

		this.renderedElement = [];
		this.payload = props.json;
	}

    /**
     * @description Parse the given payload and render the card accordingly
     */
	parsePayload = (columnSetJson) => {
		if (!this.payload)
			return this.renderedElement;

		// parse elements
		columnSetJson.columns.map((element, index) => {
			this.renderedElement.push(
				<Column json={element}
					columns={columnSetJson.columns}
					key={`ELEMENT-${this.generateNumber()}`}
				/>);
		});
		return this.renderedElement;
	}

    /**
     * @description Generates a random number
     */
	generateNumber = () => {
		min = 1;
		max = 100000;
		const rndNum = Math.floor(Math.random() * (max - min + 1) + min);

		return rndNum
	};

	internalRenderer(columnSetJson) {
		let backgroundStyle = columnSetJson.style == Constants.Emphasis ?
			styles.emphasisStyle : styles.defaultBGStyle;

		var columnSetContent = (
			<View style={[backgroundStyle, { flex: this.payload.columns.length }]}>
				<ElementWrapper json={columnSetJson} style={backgroundStyle}>
					{this.parsePayload(columnSetJson)}
				</ElementWrapper>
			</View>
		);

		if ((columnSetJson.selectAction === undefined) ||
			(HostConfigManager.getHostConfig().supportsInteractivity === false)) {
			return columnSetContent;
		} else {
			return <SelectAction selectActionData={columnSetJson.selectAction}>
				{columnSetContent}
			</SelectAction>;
		}
	}

	render() {
		let containerRender = this.internalRenderer(this.props.json);
		return containerRender;
	}

};

const styles = StyleSheet.create({
	defaultBGStyle: {
		flex: 1,
		backgroundColor: Constants.TransparentString,
		flexDirection: Constants.FlexRow,
	},
	emphasisStyle: {
		flex: 1,
		backgroundColor: Constants.EmphasisColor,
		flexDirection: Constants.FlexRow,
	},
});