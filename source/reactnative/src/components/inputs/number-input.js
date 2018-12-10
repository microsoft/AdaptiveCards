/**
 * NumberInput Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputnumber
 */

import React, { Component } from "react";
import { StyleSheet, TextInput } from 'react-native';

import { DismissKeyboardView } from '../containers/dismiss-keyboard';
import { InputContextConsumer } from '../../utils/context'
import Input from './input';
import * as Constants from '../../utils/constants';
import { StyleManager } from "../../styles/style-config";
import { HostConfigManager } from '../../utils/host-config'


const NUM_REGEX = /^[0-9][\.\d]*(,\d+)?$/;

export class NumberInput extends Component {

    styleConfig = StyleManager.getManager().styles;

    constructor(props) {
        super(props);

        this.payload = props.json;
        this.id = Constants.EmptyString;
        this.isMultiline = false;
        this.maxlength = 0;
        this.placeHolder = Constants.EmptyString;
        this.style = Constants.EmptyString;
        this.type = Constants.EmptyString;
        this.value = Constants.EmptyString;
        this.keyboardType = Constants.EmptyString;
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

        const {
            id,
            type,
            placeholder,
            keyboardType
        } = this;

        if (!id || !type) {
            return null;
        }

        return (
            <InputContextConsumer>
                {({ addInputItem }) => (
                    <Input json={this.payload}>
                        <DismissKeyboardView>
                            <TextInput
                                style={this.getComputedStyles()}
                                autoCapitalize={Constants.NoneString}
                                autoCorrect={false}
                                placeholder={placeholder}
                                underlineColorAndroid={Constants.TransparentString}
                                clearButtonMode={Constants.WhileEditingString}
                                textContentType={Constants.NoneString}
                                keyboardType={keyboardType}
                                onFocus={this.handleFocus}
                                onBlur={this.handleBlur}
                                onChangeText={(text) => this.onTextChanged(text, addInputItem)}
                                value={this.state.numberValue}
                            />
                        </DismissKeyboardView>
                    </Input>)}
            </InputContextConsumer>

        );
    }

    /**
     * @description Return the input styles applicable based on the given payload
     */
    getComputedStyles = () => {
        const { isMultiline } = this;

        let inputComputedStyles = [styles.input, this.styleConfig.fontConfig];
        isMultiline ?
            inputComputedStyles.push(styles.multiLineHeight) :
            inputComputedStyles.push(styles.singleLineHeight);
        this.state.isError ?
            inputComputedStyles.push(styles.withBorderColorRed) :
            inputComputedStyles.push(styles.withBorderColor);

        return inputComputedStyles;
    }

    /**
     * @description Parse hostconfig specific to this element
     */
    parseHostConfig() {
        this.id = this.payload.id;
        this.type = this.payload.type;
        this.min = this.payload.min;
        this.max = this.payload.max;
        this.placeholder = this.payload.placeholder;
        this.keyboardType = Constants.NumericString;
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

const styles = StyleSheet.create({
    withBorderColor: {
        borderColor: Constants.LightGreyColor,
    },
    withBorderColorRed: {
        borderColor: '#cc3300',
    },
    multiLineHeight: {
        height: 88,
    },
    singleLineHeight: {
        height: 44,
    },
    input: {
        width: Constants.FullWidth,
        padding: 5,
        marginTop: 15,
        borderWidth: 1,
        backgroundColor: Constants.WhiteColor,
        borderRadius: 5,
    },
});


