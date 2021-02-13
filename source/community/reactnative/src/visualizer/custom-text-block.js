/**
 * Custom TextBlock Element.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-textblock
 */

import React from 'react';
import { TextBlock } from '../components/elements/text-block';

export class CustomTextBlockRenderer extends React.Component {

    render() {
        let payload = this.props.json;
        if (payload.isVisible === false) {
            return null;
        }

        let textStyle = {};
        switch (payload.subType) {
            case 'subTypeGreen':
                textStyle = { color: "green" };
                break;
            case 'subTypeRed':
                textStyle = { color: "red" };
                break;
            case 'subTypeBlue':
                textStyle = { color: "blue" };
                break;
        }
        return (
            <TextBlock json={payload} style={textStyle} />
        );
    }
}

