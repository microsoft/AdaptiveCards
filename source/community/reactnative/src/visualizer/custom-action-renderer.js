/**
* Custom Action Element.
* 
*/

import React from 'react';
import {
    StyleSheet,
    Text,
    View,
    Platform,
    TouchableOpacity,
    TouchableNativeFeedback
} from 'react-native';
import {
    InputContext,
    InputContextConsumer
} from '../utils/context';
import ElementWrapper from '../components/elements/element-wrapper';
import * as Constants from '../utils/constants';

export class CustomActionRenderer extends React.Component {

    static contextType = InputContext;

    constructor(props) {
        super(props);
        this.onExecuteAction = undefined;
    }

    buttonContent = (title) => {
        return (
            <View
                style={styles.button}>
                <Text style={styles.text}>
                    {title}
                </Text>
            </View>
        );
    };

    /**
     * @description Invoked for the any action button selected
     */
	onActionButtonTapped = (url) => {
        //We can construct any object values and we can handle it in the renderer.js file
		let actionObject = { "type": "Custom Action", "url": url };
		this.onExecuteAction(actionObject);
	}

    render() {
        let payload = this.props.json;

        if (payload.isVisible === false) {
            return null;
        }
        const ButtonComponent = Platform.OS === "android" ? TouchableNativeFeedback : TouchableOpacity;
        return (
            <InputContextConsumer>
                {({ onExecuteAction }) => {
                    this.onExecuteAction = onExecuteAction;

                    return <ElementWrapper json={payload} style={styles.textContainer} isFirst={this.props.isFirst}>
                        <ButtonComponent
                            style={{ flexGrow: 1 }}
                            onPress={() => this.onActionButtonTapped(payload.url)}>
                            {this.buttonContent(payload.title)}
                        </ButtonComponent>
                        <Text>{payload.rating}</Text>
                    </ElementWrapper>
                }}
            </InputContextConsumer>);
    }
}

const styles = StyleSheet.create({
    textContainer: {
        width: Constants.FullWidth,
        alignItems: Constants.CenterString,
        backgroundColor: 'transparent',
        height: 50
    },
    text: {
        width: Constants.FullWidth,
        color: "#24A0ED",
        fontWeight: "bold",
        fontSize: 16
    },
    button: {
        alignItems: Constants.CenterString,
        justifyContent: Constants.CenterString,
        padding: 10,
        marginBottom: 10,
        flexGrow: 1,
        marginHorizontal: 5
    }
});

