/**
 * NumberInput Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputnumber
 */

import React from 'react';
import { DismissKeyboardView } from '../containers/dismiss-keyboard';
import { InputContextConsumer } from '../../utils/context'
import * as Constants from '../../utils/constants';
import { HostConfigManager } from '../../utils/host-config'
import { Input } from './input'

const NUM_REGEX = /^[0-9][\.\d]*(,\d+)?$/;

export class NumberInput extends React.Component {

    constructor(props) {
        super(props);

        this.payload = props.json;
        this.id = Constants.EmptyString;
        this.state = {
            isError: false,
            numberValue: Constants.EmptyString,
        }
    }

    render() {

        if (HostConfigManager.getHostConfig().supportsInteractivity === false) {
            return null;
        }

        this.parseHostConfig();

        return (
            <InputContextConsumer>
                {({ addInputItem }) => (
                 	<DismissKeyboardView>
						<Input 
							json={this.payload}
							handleFocus={this.handleFocus}
							handleBlur={this.handleBlur}
							textValueChanged={ (text) => { this.onTextChanged(text, addInputItem) }}
							value={this.state.numberValue} 
							isError={this.state.isError}     
						/>
				 	</DismissKeyboardView>
				)}
            </InputContextConsumer>

        );
    }

    /**
     * @description Parse hostconfig specific to this element
     */
    parseHostConfig() {
        this.min = this.payload.min;
        this.max = this.payload.max;
    }

    /**
     * @description handle text input when in focus
     */
    handleFocus = () => {

    }

    /**
     * @description handle text input when out of focus
     */
    handleBlur = () => {
        this.validate(this.state.numberValue);
    }

    /**
     * @description validate the input field
     */
    validate = (numberValue) => {
        this.setState({
            isError: this.checkRangeValue(numberValue)
        })
    };

    /**
     * @description Invoked on every change in Input field
     * @param {string} text
     */
    onTextChanged = (text, addInputItem) => {
        this.setState({
            numberValue: text,
            isError: this.checkRangeValue(text)
        })
        addInputItem(this.id, text);
    }


    checkRangeValue = (numberValue) => {
        if (numberValue === Constants.EmptyString) {
            return false
        }
        if (NUM_REGEX.test(numberValue)) {
            var parsedValue = parseFloat(numberValue)
            if (parsedValue < this.min || parsedValue > this.max) {
                return true
            } else {
                return false
            }
        }
        return true
    }
};


