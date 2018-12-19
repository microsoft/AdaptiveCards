/**
 * InputText Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputtext
 */

import React from 'react';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';
import * as Constants from '../../utils/constants';
import { HostConfigManager } from '../../utils/host-config';
import { Input } from './input';

const EMAIL_REGEX = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/;
const URL_REGEX = /((([A-Za-z]{3,9}:(?:\/\/)?)(?:[\-;:&=\+\$,\w]+@)?[A-Za-z0-9\.\-]+|(?:www\.|[\-;:&=\+\$,\w]+@)[A-Za-z0-9\.\-]+)((?:\/[\+~%\/\.\w\-_]*)?\??(?:[\-\+=&;%@\.\w_]*)#?(?:[\.\!\/\\\w]*))?)/;
const TEL_REGEX = /^[2-9]\d{2}[2-9]\d{2}\d{4}$/;

export class InputText extends React.Component {

    constructor(props) {
        super(props);

		this.payload = props.json;
		this.id = props.json.id;
        this.state = {
            isError: false,
            text: Constants.EmptyString,
        }
    }

    /**
     * @description Invoked on every change in Input field
     * @param {string} text
     */
    textValueChanged = (text, addInputItem) => {
        this.setState({ text });
        addInputItem(this.id, text);
    }

    render() {

        if (HostConfigManager.getHostConfig().supportsInteractivity === false) {
            return null;
        }

        return (
			<Input 
				json={this.payload}
				handleFocus={this.handleFocus}
				handleBlur={this.handleBlur}
				textValueChanged={ (text, addInputItem) => 
					{ this.textValueChanged(text, addInputItem) }}
				value={this.state.text}    
				isError={this.state.isError} 
			/>
        );
    }

    /**
     * @description validate the text in the textinput field based on style of the textinput.
     */
    validate = () => {
        let isError = true;
        let REGEX;
        let text = this.state.text;

        if (text === Constants.EmptyString) {
            isError = false;
        }
        else {
            switch (this.style) {
                case Enums.InputTextStyle.Email: {
                    REGEX = EMAIL_REGEX;
                }
                    break;
                case Enums.InputTextStyle.Url: {
                    REGEX = URL_REGEX;
                }
                    break;
                case Enums.InputTextStyle.Tel: {
                    REGEX = TEL_REGEX;
                    text = text.replace(/\D/g, Constants.EmptyString);
                }
                    break;
            }

            if (REGEX) {
                isError = !REGEX.test(text);
            }
        }
        this.setState({ isError });
    };

    /**
     * @description handle textinput when in focus
     */
    handleFocus = () => {
        this.setState({
            isError: false
        });
    }

    /**
     * @description handle textinput when out of focus
     */
    handleBlur = () => {
        this.validate();
    }
}
