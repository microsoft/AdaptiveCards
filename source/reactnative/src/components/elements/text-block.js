/**
 * TextBlock Element.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-textblock
 */

import React from 'react';
import { StyleSheet, Text,Platform } from 'react-native';
import { gethostConfig } from "../../utils/host-config";
import { TextFormatter } from '../../utils/text-formatters';
import Input from '../inputs/input';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';
import * as Constants from '../../utils/constants';
import processMDText from '../../utils/formatText';

const hostConfig = gethostConfig();

export class TextBlock extends React.Component {
    
    constructor(props) {
        super(props);

        this.payload = props.json;
        this.fontSize = 0;
        this.fontWeight = 0;
        this.color = Constants.EmptyString;
        this.id = Constants.EmptyString;
        this.horizontalAlignment = Constants.EmptyString;
        this.isSubtle = false
        this.maxLines = 0;
        this.wrap = false;
        this.type = Constants.EmptyString;
        this.text = Constants.EmptyString;
        this.spacing = Constants.EmptyString;
        this.separator = false;
        this.state = {
            isError: false
        }
    }

    render() {
        this.parseHostConfig();

        var formattedText = TextFormatter('en-US', this.text);
        var processedText = processMDText(formattedText);

        //TextBlock styles
        let textBlockComputedStyle = [styles.text];
        textBlockComputedStyle.push({
            fontSize: this.fontSize,
            fontWeight: this.fontWeight.toString(),
            color: this.color,
            textAlign: this.horizontalAlignment
        });

        return (
            <Input json={this.payload} style={styles.textContainer}>
                <Text
                    style={textBlockComputedStyle}
                    numberOfLines={this.wrap ? (this.maxLines != undefined ?
                        this.maxLines : 0) : 1}>
                    {processedText}
                </Text>
            </Input>
        );
    }

    /**
     * @description Parse hostconfig specific to this element
     */
    parseHostConfig() {
        this.id = this.payload.id;
        this.type = this.payload.type;
        this.isSubtle = this.payload.isSubtle;
        this.maxLines = this.payload.maxLines;
        this.weight = this.payload.weight;
        this.text = this.payload.text
        this.wrap = this.payload.wrap;
        this.separator = this.payload.separator

        let spacingValue = Utils.parseHostConfigEnum(
            Enums.Spacing,
            this.payload.spacing,
            Enums.Spacing.Small);

        this.fontSize = hostConfig.getTextFontSize(Utils.parseHostConfigEnum(
            Enums.TextSize,
            this.payload.size,
            Enums.TextSize.Default
        ));

        this.fontWeight = hostConfig.getTextFontWeight(Utils.parseHostConfigEnum(
            Enums.TextWeight,
            this.payload.weight,
            Enums.TextWeight.Default
        ));

        let colorDefinition = hostConfig.getTextColor(Utils.parseHostConfigEnum(
            Enums.TextColor,
            this.payload.color,
            Enums.TextColor.Default
        ));

        this.horizontalAlignment = hostConfig.getTextAlignment(Utils.parseHostConfigEnum(
            Enums.HorizontalAlignment,
            this.payload.horizontalAlignment,
            Enums.HorizontalAlignment.Left
        ));

        this.color = this.isSubtle ? colorDefinition.subtle : colorDefinition.default
        this.spacing = hostConfig.getEffectiveSpacing(spacingValue);
    }
}

const styles = StyleSheet.create({
    textContainer: {
        width: Constants.FullWidth,
        alignItems: Constants.CenterString,
        backgroundColor:'transparent',
    },
    text: {
        width: Constants.FullWidth,
        fontSize: hostConfig.fontSizes.default,
        fontWeight: hostConfig.fontWeights.default.toString(),
        textAlign: Constants.LeftAlign,
    }
});

