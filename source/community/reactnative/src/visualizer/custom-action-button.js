/**
 * Custom Action Button Element.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-textblock
 */

import React from 'react';
import { ActionButton } from '../components/actions/action-button';

export class CustomActionButtonRenderer extends React.Component {

    render() {
        let payload = this.props.json;

        if (payload.isVisible === false) {
            return null;
        }

        return (
            <ActionButton json={payload} style={{ backgroundColor: "transparent" }} titleStyle={{color: "#147efb"}} />
        );
    }
}

