/**
 * Column Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-column
 */

import React from "react";
import { View, StyleSheet, Dimensions } from 'react-native';
import { Registry } from '../registration/registry'
import * as Utils from '../../utils/util';
import * as Constants from '../../utils/constants';
import * as Enums from '../../utils/enums';
import { SelectAction } from '../actions';
import { HostConfigManager } from '../../utils/host-config'
import { StyleManager } from '../../styles/style-config'

const deviceWidth = Dimensions.get('window').width;

export class Column extends React.Component {

	styleConfig = StyleManager.getManager().styles;
	hostConfig = HostConfigManager.getHostConfig();
	spacing = 0;

    constructor(props) {
        super(props);
        this.payload = props.json;
    }

    /**
     * @description Parse the given payload and render the card accordingly
     */
    parsePayload = (onParseError) => {
        const renderedElement = [];
        if (!this.payload)
            return renderedElement;
        // parse elements
        if (!Utils.isNullOrEmpty(this.payload.items)) {
            renderedElement.push(Registry.getManager().parseRegistryComponents(this.payload.items, onParseError));
        }
        return renderedElement;
    }

    /**
     * @description Calculate the Width percentage of the column to be rendered
     */
    calculateWidthPercentage = (containerStyle) => {
        var columns = this.props.columns
        var widthArray = columns.length > 0 ? columns.map((column) => column.width) : [];
        var spaceArray = columns.length > 0 ? columns.map((column) => column.spacing) : [];

        var containsNumber = false
        var containsString = false

        widthArray.map((value) => {
            if (typeof (value) == 'number') {
                containsNumber = true
            } else if (typeof (value) == 'string') {
                containsString = true
            }
		})
		
		var spacing = 0
        spaceArray.map((space) => {
            if (space != undefined) {
				const spacingEnumValue = Utils.parseHostConfigEnum(
					Enums.Spacing,
					space,
					Enums.Spacing.Small);
				spacing += this.hostConfig.getEffectiveSpacing(spacingEnumValue);
            } 
		})
		
		const spacePercentage = (spacing/deviceWidth) * 100

        var columnWidth;
        if (!containsString) {
            columnWidth = 0
            columns.forEach(function (column) {
                if (!Utils.isNullOrEmpty(column.width)) {
                    columnWidth += column.width
                }
            });
        }

        let width = this.payload.width
        if (Utils.isNullOrEmpty(width)) {
            width = 1
        }

        let widthPercentage;
        if (containsString) {
            if (typeof (width) == 'string') {
                let lastIndex = width.lastIndexOf('px')
                if (lastIndex != -1) {
                    widthPercentage = parseInt(width.substring(0, lastIndex))
                }
                else if (width == Constants.AlignStretch) {
                    containerStyle.push({ flex: 1 })
                }
                else if (width == Constants.Auto) {
                    if (!containsNumber) {
                        containerStyle.push({ alignSelf: 'auto' })
                    } else {
                        widthPercentage = (100-spacePercentage)/columns.length
                    }
                }
                else {
                    widthPercentage = (100-spacePercentage)/columns.length
                }
            }
            else {
                widthPercentage = (100-spacePercentage)/columns.length
            }
        }
        else {
            if (Utils.isNullOrEmpty(this.payload.width)) {
                widthPercentage = ((width/columns.length) * 100 - spacePercentage/columns.length)
            }
            else {
                widthPercentage = ((this.payload.width/columnWidth) * 100 - spacePercentage/columns.length)
            }
        }

        return widthPercentage
	}
	
	renderSeparator = () => {
		return (
			<View style={{ 
					borderLeftWidth: this.hostConfig.separator.lineThickness,
					borderLeftColor: this.hostConfig.separator.lineColor,
					marginLeft: (this.spacing - this.hostConfig.separator.lineThickness) /2,
					marginRight: (this.spacing - this.hostConfig.separator.lineThickness) /2
			 }}/>

		);
	}

    render() {
		const separator = this.payload.separator || false
        let backgroundStyle = this.payload.style == Constants.Emphasis ?
			styles.emphasisStyle : styles.defaultBGStyle;
		let containerViewStyle = [backgroundStyle, { flexDirection: separator ?
			 Constants.FlexRow: Constants.FlexColumn }];

		const spacingEnumValue = Utils.parseHostConfigEnum(
			Enums.Spacing,
			this.payload.spacing,
			Enums.Spacing.Small);
		this.spacing = Utils.isNullOrEmpty(this.payload.spacing) ? 0 : 
		this.hostConfig.getEffectiveSpacing(spacingEnumValue);

        let widthPercentage = this.calculateWidthPercentage(containerViewStyle);
        if (!Utils.isNullOrEmpty(widthPercentage)) {
			const spacePercentage = (this.spacing/deviceWidth) * 100 + widthPercentage
            containerViewStyle.push({ width: spacePercentage.toString() + '%' });
        }

        var columnContent = (
			<View style={containerViewStyle}>
				{ separator && this.renderSeparator() }
				{ separator ? <View style={[containerViewStyle, 
											{flexDirection: Constants.FlexColumn, flexGrow: 1}]}>
									{this.parsePayload()}
							  </View> : 
							  this.parsePayload() }
			</View>
        );

        if ((this.payload.selectAction === undefined) ||
            (HostConfigManager.getHostConfig().supportsInteractivity === false)) {
            return columnContent;
        } else {
            return <View style={containerViewStyle}>
						<SelectAction selectActionData={this.payload.selectAction}>
							{ separator && this.renderSeparator() }
							{ separator ? 
								<View style={[containerViewStyle, 
											{flexDirection: Constants.FlexColumn, flexGrow: 1}]}>
												{this.parsePayload()}
								</View> : 
								this.parsePayload() }
						</SelectAction>
            </View>;
        }
    }
};

const styles = StyleSheet.create({
	separatorStyle: {
		flexDirection: Constants.FlexColumn,
		flexGrow: 1
	},
    defaultBGStyle: {
        backgroundColor: Constants.TransparentString,
    },
    emphasisStyle: {
        backgroundColor: Constants.EmphasisColor,
    },
});