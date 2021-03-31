/**
 * Custom Image Element.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-textblock
 */

import React from 'react';
import { Img } from '../components/elements/image';

export class CustomImageRenderer extends React.Component {

    render() {
        let payload = this.props.json;

        if (payload.isVisible === false) {
            return null;
        }

        return (
            <Img json={payload} style={{ width: 100, backgroundColor: "green" }} />
        );
    }
}



