/**
 * SelectAction Component.
 * 
 */

import React, { Component } from "react";
import { Linking, Platform, Alert } from 'react-native'

import * as Constants from '../../utils/constants';

export class SelectAction extends Component {

    constructor(props) {
        super(props);
    }

    /**
     * @description Invoked on tapping the parent component
     */
    onClickHandle() {
        if (this.props.selectActionData.type === Constants.ActionSubmit) {
            this.onSubmitActionCalled();
        } else if (this.props.selectActionData.type === Constants.ActionOpenUrl) {
            this.openUrlContent();
        }
    }

    /**
     * @description Invoked for the action type Constants.ActionOpenUrl
     */
    openUrlContent() {
        Linking.canOpenURL(this.props.selectActionData.url).then(supported => {
            if (supported) {
                Linking.openURL(this.props.selectActionData.url);
            } else {
                console.log("Can't open URL: " + this.props.selectionActionData.url);
            }
        });
    }

    /**
     * @description Invoked for the action type Constants.ActionSubmit
     */
    onSubmitActionCalled() {
        Alert.alert(
            'Submit Action',
            JSON.stringify(this.props.selectActionData.data),
            [
                { text: Constants.OkText, onPress: () => console.log('OK Pressed') },
            ],
            { cancelable: false }
        )
    }

    render() {
        const ButtonComponent = Platform.select({
            ios: () => require('TouchableOpacity'),
            android: () => require('TouchableNativeFeedback'),
        })();

        return (<ButtonComponent onPress={() => { this.onClickHandle() }}>
            {this.props.children}
        </ButtonComponent>);
    }
}
