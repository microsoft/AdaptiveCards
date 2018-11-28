/**
 * Toggle Component based on the given payload.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#inputtoggle
 */

import React from 'react';
import { Text, Switch, StyleSheet } from 'react-native';
import Input from './input';
import * as Constants from '../../utils/constants';
import { InputContextConsumer } from '../../utils/context'
import { gethostConfig } from "../../utils/host-config";

const hostConfig = gethostConfig();
const TrueString = "true";
const FalseString = "false";
const ToggleValueOn = "toggleValueOn;";

export class ToggleInput extends React.Component {
    
    constructor(props) {
        super(props);

        this.title = props.json.title;
        this.valueOn = props.json.valueOn || TrueString;
        this.valueOff = props.json.valueOff || FalseString;
        this.value = props.json.value || this.valueOff;
        this.id = props.json.id || ToggleValueOn

        // state
        this.state = {
            toggleValue: (this.value === this.valueOn)
        }
    }

    /**
     * @description Invoked on every change in Toggle
     * @param {Boolean} toggleValue
     * @param {InputContextConsumer} addInputItem
     */
    toggleValueChanged = (toggleValue, addInputItem) => {
        this.setState({toggleValue});
        addInputItem(this.id, toggleValue);
    }

    render() {
        const { toggleValue } = this.state;

        return (
            <Input json={this.props.json} style={styles.toggleContainer}>
                <Text style={styles.title}>{this.title}</Text>
                <InputContextConsumer>
                    {({ addInputItem} ) => (
                        <Switch 
                            style={styles.switch} 
                            value={toggleValue} 
                            onValueChange={toggleValue => {
                                this.toggleValueChanged(toggleValue, addInputItem)
                        }}>
                        </Switch>
                    )}
                </InputContextConsumer>
            </Input>
        )
    }
}

const styles = StyleSheet.create({
    toggleContainer: {
        flexDirection: Constants.FlexRow,
        justifyContent: Constants.SpaceBetween,
        alignItems: Constants.CenterString,
        paddingTop: 5,
        paddingBottom: 5
    },
    title: {
        fontSize: hostConfig.fontSizes.default,
        fontWeight: hostConfig.fontWeights.default.toString(),
        flexShrink: 1,
        marginRight: 10
    }
});