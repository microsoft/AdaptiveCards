/**
 * Column Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-column
 */

import React from 'react';
import {
	View,
	StyleSheet,
	Dimensions
} from 'react-native';

import { InputContext } from '../../utils/context';
import { Registry } from '../registration/registry';
import * as Utils from '../../utils/util';
import * as Constants from '../../utils/constants';
import * as Enums from '../../utils/enums';
import { SelectAction } from '../actions';
import { HostConfigManager } from '../../utils/host-config';
import { StyleManager } from '../../styles/style-config';
import { ContainerWrapper } from './';

const deviceWidth = Dimensions.get('window').width;

export class Column extends React.Component {

	static contextType = InputContext;
	styleConfig = StyleManager.getManager().styles;
	hostConfig = HostConfigManager.getHostConfig();
	spacing = 0;

	constructor(props) {
		super(props);
		this.column = props.json;
	}

	/**
	 * @description Parse the given payload and render the card accordingly
	 * @returns {object} Return the child elements of the column
	 */
	parsePayload = () => {
		let children = [];
		if (!this.column)
			return children;

		if (this.column.isFallbackActivated) {
			if (this.column.fallbackType == "drop") {
				return null;
			} else if (!Utils.isNullOrEmpty(element.fallback)) {
				return Registry.getManager().parseComponent(this.column.fallback, this.context.onParseError);
			}
		}
		// parse elements
		if (!Utils.isNullOrEmpty(this.column.items) && (this.column.isVisible !== false)) {
			children = Registry.getManager().parseRegistryComponents(this.column.items, this.context.onParseError);
		}
		return children.map((ChildElement, index) => React.cloneElement(ChildElement, { containerStyle: this.column.style, isFirst: index === 0 , columnWidth: this.column.width}));
	}

	/**
	 * @description This function determines whether the current column element(this.column) 
	 * 				is the first element of the columns(this.props.columns) array. 
	 * @returns {boolean} true|false
	 */
	isForemostElement = () => {
		return this.props.columns[0] === this.column;
	}

	/**
     * @description This function renders a separator between the columns 
	 * 				based on the separator property from the payload. 
	 * @returns {Component|null}
     */
	renderSeparator = () => {
		const { lineColor, lineThickness } = this.hostConfig.separator
		const margin = (this.spacing - lineThickness) / 2
		if (!this.isForemostElement()) {
			return (
				<View style={{
					borderLeftWidth: lineThickness,
					borderLeftColor: lineColor,
					marginLeft: margin,
					marginRight: margin
				}} />
			);
		} else {
			return null;
		}
	}

	/**
     * @description This function calculates flex value
	 * 				based on the column width property from the payload. 
	 * @returns {flex}
     */

	flex = (containerViewStyle) => {
		var flex = 0
		var columns = this.props.columns
		const widthArray = columns.map((column) => column.width);
		var sizeValues = []
		widthArray.map((value) => {
			if (Utils.isaNumber(value)) {
				sizeValues.push(value)
			}
		})
		var minValue = Math.min.apply(null, sizeValues)
		var maxValue = Math.max.apply(null, sizeValues)
		if (Utils.isaNumber(this.column.width)) {
			flex = this.column.width / maxValue
		}
		else if (!this.column || this.column.width === 'auto') {
			if (sizeValues.length == 0) {
				containerViewStyle.push({ flexWrap: 'wrap' })
			} else {
				flex = minValue / maxValue
			}
		}
		else if (this.column.width === undefined || this.column.width === 'stretch') {
			flex = 1
		}
		return flex;
	}

	render() {
		const { isFirst, isLast } = this.props;
		const separator = this.column.separator || false;
		let containerViewStyle = [{
			flexDirection: separator ?
				Constants.FlexRow : Constants.FlexColumn
		}];

		const spacingEnumValue = Utils.parseHostConfigEnum(
			Enums.Spacing,
			this.column.spacing,
			Enums.Spacing.Default);
		this.spacing = this.hostConfig.getEffectiveSpacing(spacingEnumValue);

		let spacingStyle = [];
		if (!this.isForemostElement() && this.column.spacing) {
			spacingStyle.push({ marginLeft: this.spacing })
		}
		spacingStyle.push({ flexGrow: 1 });

		if (Utils.isPixelValue(this.column.width) && Utils.isaNumber(this.column.width)) {
			containerViewStyle.push({ width: parseInt(this.column.width) })
		} else {
			containerViewStyle.push({ flex: this.flex(containerViewStyle) })
		}

		let ActionComponent = React.Fragment;
		let actionComponentProps = {};

		// select action
		if ((!Utils.isNullOrEmpty(this.column.selectAction)) && HostConfigManager.supportsInteractivity()) {
			ActionComponent = SelectAction;
			actionComponentProps = { selectActionData: this.column.selectAction };
		}

		let separatorStyles = [spacingStyle];

		if (separator) {
			separatorStyles = [containerViewStyle, styles.separatorStyle];
		}

		return <ContainerWrapper json={this.column} hasBackgroundImage={this.props.hasBackgroundImage} isFirst={isFirst} isLast={isLast} style={[containerViewStyle]} containerStyle={this.props.containerStyle}>
			<ActionComponent {...actionComponentProps}>
				{separator && this.renderSeparator()}
				<View style={separatorStyles}>
					{this.parsePayload()}
				</View>
			</ActionComponent>
		</ContainerWrapper>
	}
};

const styles = StyleSheet.create({
	separatorStyle: {
		flexDirection: Constants.FlexColumn,
		flexGrow: 1,
	},
	defaultBGStyle: {
		backgroundColor: Constants.TransparentString,
	},
});