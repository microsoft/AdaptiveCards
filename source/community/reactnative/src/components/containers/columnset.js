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
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';
import * as Constants from '../../utils/constants';
import { ContainerWrapper } from './';

export class ColumnSet extends React.PureComponent {

	constructor(props) {
		super(props);
		this.hostConfig = props.configManager.hostConfig;
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
					configManager={this.props.configManager}
					hasBackgroundImage={payload.parent.backgroundImage}
					key={`ELEMENT-${index}`}
					isFirst={index === 0}
					isLast={index === payload.columns.length - 1}
				/>);
		});
		return children.map(ChildElement => React.cloneElement(ChildElement, { containerStyle: this.payload.style }));
	}

	internalRenderer() {
		const payload = this.payload;
		const { hostConfig } = this.props.configManager;

		// padding
        const spacingEnumValue = Utils.parseHostConfigEnum(
			Enums.Spacing,
			this.payload.spacing,
			Enums.Spacing.Default);
        const padding = hostConfig.getEffectiveSpacing(spacingEnumValue);

		const minHeight = Utils.convertStringToNumber(this.payload.minHeight);
		//We will pass the style as array, since it can be updated in the container wrapper if required.
		const containerStyle = typeof minHeight === "number" ? { minHeight } : {};
		
		var columnSetContent = (
			<ContainerWrapper configManager={this.props.configManager} style={[{ flex: this.payload.columns.length, marginTop: padding }, containerStyle]} json={payload} containerStyle={this.props.containerStyle}>
				<ElementWrapper configManager={this.props.configManager} json={payload} style={styles.defaultBGStyle} isFirst={this.props.isFirst}>
					{this.parsePayload()}
				</ElementWrapper>
			</ContainerWrapper>
		);

		if ((payload.selectAction === undefined) || !this.hostConfig.supportsInteractivity) {
			return columnSetContent;
		} else {
			return <SelectAction configManager={this.props.configManager} selectActionData={payload.selectAction}>
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