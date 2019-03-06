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

import { InputContextConsumer } from '../../utils/context';
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

	styleConfig = StyleManager.getManager().styles;
	hostConfig = HostConfigManager.getHostConfig();
	spacing = 0;

	constructor(props) {
		super(props);
		this.column = props.json;
	}

	/**
	 * @description Parse the given payload and render the card accordingly
	 * @param {func} onParseError - Function reference to be invoked on parse errors (if any)
	 */
	parsePayload = (onParseError) => {
		const renderedElement = [];
		if (!this.column)
			return renderedElement;

		// parse elements
		if (!Utils.isNullOrEmpty(this.column.items)) {
			renderedElement.push(Registry.getManager().parseRegistryComponents(this.column.items, onParseError));
		}
		return renderedElement;
	}

	/**
	 * @description This function determines whether the current column element(this.column) 
	 * 				is the first element of the columns(this.props.columns) array. 
	 * @returns {boolean} true|false
	 */
	isForemostElement = () => {
		return this.props.columns[0] === this.column ? true : false;
	}

	/**
	 * @description This function calculates the Width percentage of the column to be 
 	 * 				rendered based on the width property from the payload. 
	 * @param {object} containerStyle - Computed style object
	 */
	calculateWidthPercentage = (containerStyle) => {
		var columns = this.props.columns
		var widthArray = columns.length > 0 ? columns.map((column) => column.width) : [];
		var spaceArray = columns.length > 0 ? columns.map((column) => column.spacing) : [];

		var containsNumber = false
		var containsString = false

		// checks if the width property of the column elements has type of string or a number
		widthArray.map((value) => {
			if (typeof (value) == 'number') {
				containsNumber = true
			} else if (typeof (value) == 'string') {
				containsString = true
			}
		})

		var spacing = 0
		spaceArray.map((space) => {
			const spacingEnumValue = Utils.parseHostConfigEnum(
				Enums.Spacing,
				space,
				Enums.Spacing.Default);
			spacing += this.hostConfig.getEffectiveSpacing(spacingEnumValue);
		})

		const spacePercentage = (spacing / deviceWidth) * 100
		const defaultWidthPercentage = (100 - spacePercentage) / columns.length

		var columnWidth;
		if (!containsString) {
			columnWidth = 0
			columns.forEach(function (column) {
				if (!Utils.isNullOrEmpty(column.width)) {
					columnWidth += column.width
				}
			});
		}

		let width = this.column.width
		if (Utils.isNullOrEmpty(width)) {
			width = 1
		}

		let widthPercentage;
		/**
		 * Scenario 1 : If the column has atleast one element
		 *  			of width property with type of string
		 * Scenario 2 : If the column has elements with width
		 * 				parameter only of type integer
		 */
		if (containsString) {
			/**
			 * Scenario 1 : width property has string value (Ex: '80px', 'stretch', 'auto'),
			 * Scenario 2 : width property has integer value (Ex: 1) 
			 */
			if (typeof (width) == 'string') {
				/**
				 * Scenario 1 : width property has string value (Ex: '80px'),
				 *               use the integer portion.
				 * Scenario 2 : If the width has string 'stretch' value,
				 *              ignore and use the size property to determine dimensions.
				 * Scenario 3 : If the width has string 'auto'value,
				 *              ignore and use the size property to determine dimensions. 
				 * 				(only if the other elements also has width parameter of type string).
				 * Scenario 4 : If width is missing, column width is divided equally.
				 */
				let lastIndex = width.lastIndexOf('px')
				if (lastIndex != -1) {
					let pixelWidth = parseInt(width.substring(0, lastIndex))
					widthPercentage = (pixelWidth / deviceWidth) * 100
				}
				else if (width == Constants.AlignStretch) {
					containerStyle.push({ flex: 1 })
				}
				else if (width == Constants.Auto) {
					if (!containsNumber) {
						containerStyle.push({ alignSelf: 'auto' })
					} else {
						widthPercentage = defaultWidthPercentage
					}
				}
				else {
					widthPercentage = defaultWidthPercentage
				}
			}
			else {
				widthPercentage = defaultWidthPercentage
			}
		}
		else {
			/**
			 * Scenario 1 : If width parameter is missing, column width is 
			 * 				divided equally excluding the default spacing ,
			 * Scenario 2 : width percentage is calculated based 
			 * 				on the width parameter from the json 
			 */
			if (Utils.isNullOrEmpty(this.column.width)) {
				widthPercentage = (((width / columns.length) * 100) - (spacePercentage / columns.length))
			}
			else {
				widthPercentage = (((this.column.width / columnWidth) * 100) - (spacePercentage / columns.length))
			}
		}

		return widthPercentage
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

	render() {
		const separator = this.column.separator || false;
		let backgroundStyle = this.column.style == Constants.Emphasis ?
			styles.emphasisStyle : styles.defaultBGStyle;
		let containerViewStyle = [backgroundStyle, {
			flexDirection: separator ?
				Constants.FlexRow : Constants.FlexColumn
		}];

		const spacingEnumValue = Utils.parseHostConfigEnum(
			Enums.Spacing,
			this.column.spacing,
			Enums.Spacing.Default);
		this.spacing = this.hostConfig.getEffectiveSpacing(spacingEnumValue);

		let spacingStyle = [];
		if (!this.isForemostElement()) {
			spacingStyle.push({ marginLeft: this.spacing })
		}
		spacingStyle.push({ flexGrow: 1 });

		let widthPercentage = this.calculateWidthPercentage(containerViewStyle);
		if (!Utils.isNullOrEmpty(widthPercentage)) {
			const spacePercentage = ((this.spacing / deviceWidth) * 100 + widthPercentage)
			containerViewStyle.push({ width: spacePercentage.toString() + '%' });
		}

		let ActionComponent = React.Fragment;
		let actionComponentProps = {};

		// select action
		if (this.column.selectAction && HostConfigManager.supportsInteractivity()) {
			ActionComponent = SelectAction;
			actionComponentProps = { selectActionData: this.column.selectAction };
		}

		return (<InputContextConsumer>
			{({ onParseError }) => <ContainerWrapper json={this.column} style={[containerViewStyle]}>
				<ActionComponent {...actionComponentProps}>
					{separator && this.renderSeparator()}
					{separator ?
						<View style={[containerViewStyle, styles.separatorStyle]}>
							{this.parsePayload(onParseError)}
						</View> :
						<View style={spacingStyle}>
							{this.parsePayload(onParseError)}
						</View>}
				</ActionComponent>
			</ContainerWrapper>}
		</InputContextConsumer>);
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
	emphasisStyle: {
		backgroundColor: Constants.EmphasisColor,
	},
});