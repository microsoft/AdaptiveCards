/**
 * Column Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-column
 */

import React, { Component } from "react";
import { View, Text, StyleSheet } from 'react-native';
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
    parsePayload = () => {
        const renderedElement = [];
        if (!this.payload)
            return renderedElement;
        // parse elements
         if(!Utils.isNullOrEmpty(this.payload.items)){
            renderedElement.push(Registry.getManager().parseRegistryComponents(this.payload.items));
         }
        return renderedElement;
    }

    /**
     * @description Calculate the Width percentage of the column to be rendered
     */
    calculateWidthPercentage = (containerStyle) => {
        var columns = this.props.columns
        var widthArray = columns.length > 0 ? columns.map((column) => column.width) : [];

        var containsNumber = false
        var containsString = false

        widthArray.map((value) => {
            if (typeof(value) == 'number') {
                containsNumber = true
            } else if (typeof(value) == 'string') {
                containsString = true
            }
        })

        var columnWidth;
        if (!containsString) {
            columnWidth = 0
            columns.forEach(function(column) {
                if (!Utils.isNullOrEmpty(column.width)){
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
            if (typeof(width) == 'string'){
                let lastIndex = width.lastIndexOf('px')
                if (lastIndex != -1) {
                    widthPercentage = parseInt(width.substring(0, lastIndex))
                } 
                else if (width == Constants.AlignStretch) {
                    containerStyle.push({flex: 1})
                } 
                else if (width == Constants.Auto) {
                    if (!containsNumber) {
                        containerStyle.push({alignSelf: 'auto'})
                    } else {
                        widthPercentage = (100/columns.length).toString()+'%' 
                    }
                }
                else {
                    widthPercentage = (100/columns.length).toString()+'%' 
                }
            } 
            else {
                widthPercentage = (100/columns.length).toString()+'%' 
            }
        }
        else {
            if (Utils.isNullOrEmpty(this.payload.width)) {
                widthPercentage = ((width/columns.length) * 100).toString()+'%'
            } 
            else{
                 widthPercentage = ((this.payload.width/columnWidth) * 100).toString()+'%'
            }
        }

        return widthPercentage
    }

    render() {
        let backgroundStyle = this.payload.style == Constants.Emphasis ? 
        styles.emphasisStyle:styles.defaultBGStyle;

        let containerViewStyle = [styles.container, backgroundStyle];

        let widthPercentage = this.calculateWidthPercentage(containerViewStyle);
        if (!Utils.isNullOrEmpty(widthPercentage)) {
            containerViewStyle.push({width: widthPercentage});
        }

        var columnContent = (
            <View style={containerViewStyle}>
                     {this.parsePayload()}
            </View>
        );

        if ((this.payload.selectAction === undefined) || (HostConfigManager.getHostConfig().supportsInteractivity === false)) {
            return columnContent;
        } else {
            return  <View style={containerViewStyle}>
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