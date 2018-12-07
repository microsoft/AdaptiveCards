/**
 * Column Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-column
 */

import React, { Component } from "react";
import { View, StyleSheet } from 'react-native';

import { Registry } from '../registration/registry'
import * as Utils from '../../utils/util';
import * as Constants from '../../utils/constants';
import { SelectAction } from '../actions';
import { HostConfigManager } from '../../utils/host-config'

export class Column extends Component {

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
        let width = this.payload.width
        if (Utils.isNullOrEmpty(width)) {
            width = 1
        }

        let widthPercentage;
        switch (typeof (this.props.columnWidth)) {
            case 'string':
                if (typeof (width) == 'string') {
                    let lastIndex = width.lastIndexOf('px')
                    if (lastIndex != -1) {
                        widthPercentage = parseInt(width.substring(0, lastIndex))
                    } else if (width == Constants.AlignStretch ||
                        width == Constants.Auto) {
                        containerStyle.push({ flex: 1 })
                    }
                    else {
                        widthPercentage = (100 / this.props.columns).toString() + '%'
                    }
                } else {
                    widthPercentage = (100 / this.props.columns).toString() + '%'
                }
                break;
            default:
                if (isNaN(this.props.columnWidth)) {
                    widthPercentage = ((width / this.props.columns) * 100).toString() + '%'
                } else {
                    widthPercentage = ((this.payload.width / this.props.columnWidth) * 100).toString() + '%'
                }

                break;
        }

        return widthPercentage
    }

    render() {
        let backgroundStyle = this.payload.style == Constants.Emphasis ?
            styles.emphasisStyle : styles.defaultBGStyle;

        let containerViewStyle = [styles.container, backgroundStyle];

        let widthPercentage = this.calculateWidthPercentage(containerViewStyle);
        if (!Utils.isNullOrEmpty(widthPercentage)) {
            containerViewStyle.push({ width: widthPercentage });
        }

        var columnContent = (
            <View style={containerViewStyle}>
                {this.parsePayload()}
            </View>
        );

        if ((this.payload.selectAction === undefined) ||
            (HostConfigManager.getHostConfig().supportsInteractivity === false)) {
            return columnContent;
        } else {
            return <View style={containerViewStyle}>
                <SelectAction selectActionData={this.payload.selectAction}>
                    {this.parsePayload()}
                </SelectAction>
            </View>;
        }
    }
};

const styles = StyleSheet.create({
    container: {
        flexDirection: Constants.FlexColumn
    },
    defaultBGStyle: {
        backgroundColor: Constants.TransparentString,
    },
    emphasisStyle: {
        backgroundColor: Constants.EmphasisColor,
    },
});