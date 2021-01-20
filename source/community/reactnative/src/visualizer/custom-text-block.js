/**
 * Custom TextBlock Element.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-textblock
 */

import React from 'react';
import {
    StyleSheet
} from 'react-native';
import ElementWrapper from '../components/elements/element-wrapper';
import { TextBlock } from '../components/elements/text-block';
import * as Constants from '../utils/constants';

export class CustomTextBlockRenderer extends React.Component {

    render() {
        let payload = this.props.json;

        if (payload.isVisible === false) {
            return null;
        }

        return (
            <ElementWrapper json={payload} style={styles.textContainer} isFirst={this.props.isFirst}>
                <TextBlock json={payload} style={{ color: "green" }} />
            </ElementWrapper>
        );
    }
}

const styles = StyleSheet.create({
    textContainer: {
        width: Constants.FullWidth,
        alignItems: Constants.CenterString,
        backgroundColor: 'transparent',
    }
});

