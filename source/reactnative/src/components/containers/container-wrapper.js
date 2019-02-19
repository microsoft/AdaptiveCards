/**
 * ContainerWrapper component that wraps the container type element
 * and takes care of common container related parsing & styling.
 * 
 * @example
 * <ContainerWrapper json={payload}>
 *  <Column json={payload}></Column>
 * </ContainerWrapper>
 */

import React from 'react';
import { View } from 'react-native';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';

export class ContainerWrapper extends React.PureComponent {

    render() {
        const receivedStyles = this.props.style;
        const computedStyles = this.getComputedStyles();
        return (
            <View style={[computedStyles, receivedStyles]}>
                {this.props.children}
            </View>
        )
    }

    /**
     * @description Determine the styles applicable based on the given payload
     * @returns {object} - Styles computed based on the payload
     */
    getComputedStyles = () => {
        const payload = this.props.json;
        let computedStyles = [];

        // vertical content alignment
        let verticalContentAlignment = Utils.parseHostConfigEnum(
            Enums.VerticalAlignment,
            payload["verticalContentAlignment"],
            Enums.VerticalAlignment.Top
        );
        switch (verticalContentAlignment) {
            case Enums.VerticalAlignment.Center:
                computedStyles.push({ justifyContent: 'center' });
                break;
            case Enums.VerticalAlignment.Bottom:
                computedStyles.push({ justifyContent: 'flex-end' });
                break;
            default:
                computedStyles.push({ justifyContent: 'flex-start' });
                break;
        }
        return computedStyles;
    }
}