/**
 * Input component that wraps all other specific input element.
 * 
 * @example
 * <Input json={payload}>
 *  <InputElement json={payload}></InputElement>
 * </Input>
 */

import React from 'react';
import { View, StyleSheet } from 'react-native';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';
import { gethostConfig } from "../../utils/host-config";
import * as Constants from '../../utils/constants';

const hostConfig = gethostConfig();

export default class Input extends React.Component {

    render() {
        const computedStyles = this.getComputedStyles();

        return (
            <View style={computedStyles} onLayout ={this.props.onPageLayout}>
                {this.props.children}
            </View>
        )
    }

    /**
     * @description Return the styles applicable based on the given payload
     */
    getComputedStyles = () => {
        const payload = this.props.json;
        const receivedStyles = this.props.style;

        let computedStyles = [styles.inputContainer, receivedStyles];

        // spacing
        const spacingEnumValue = Utils.parseHostConfigEnum(
            Enums.Spacing,
            payload.spacing,
            Enums.Spacing.Small);
        const spacing = hostConfig.getEffectiveSpacing(spacingEnumValue);
        computedStyles.push({ marginTop: spacing });

        // separator
        const separator = payload.separator || false;
        if (separator) {
            computedStyles.push(styles.withSeparator);
            computedStyles.push({ paddingTop: spacing / 2, marginTop: spacing / 2 });
        }

        // height 
        const height = payload.height || false;
        if (height) {
            const heightEnumValue = Utils.parseHostConfigEnum(
                Enums.Height,
                payload.height,
                Enums.Height.Auto);
            const height = hostConfig.getEffectiveHeight(heightEnumValue);
            computedStyles.push({ flex: height});
        }
       
        return computedStyles;
    }
}


const styles = StyleSheet.create({
    inputContainer: {
        backgroundColor: Constants.WhiteColor
    },
    withSeparator: {
        borderColor: hostConfig.separator.lineColor,
        borderTopWidth: hostConfig.separator.lineThickness,
    }
})