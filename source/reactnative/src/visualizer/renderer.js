/**
 * Render the adaptive card for the given payload.
 */

import React from 'react';
import {
    View,
    Text,
    StyleSheet,
    Button,
    Platform,
    Alert,
    Linking
} from 'react-native';

import AdaptiveCards from '../adaptive-cards';
import { RatingRenderer } from './rating-renderer';
import { Registry } from '../components/registration/registry';

export default class Renderer extends React.Component {
    constructor(props) {
        super(props);
        this.payload = props.payload;
        this.onModalClose = props.onModalClose;
    }

    customHostConfig = {
        fontFamily: "Helvetica",
        supportsInteractivity: true,
        fontSizes: {
            small: 12,
            default: 14,
            medium: 17,
            large: 21,
            extraLarge: 26
        }
    }

    
    onExecuteAction = (actionObject) => {
        if (actionObject.type === "Action.Submit") {
            Alert.alert(
                'Rendered Submit',
                JSON.stringify(actionObject.data),
                [
                    { text: "Okay", onPress: () => console.log('OK Pressed') },
                ],
                { cancelable: false }
            )
        } else if (actionObject.type === "Action.OpenUrl") {
            Linking.canOpenURL(actionObject.url).then(supported => {
                if (supported) {
                    Linking.openURL(actionObject.url);
                } else {
                    console.log("Don't know how to open URI: " + actionObject.url);
                }
            });
        }

    }

    onParseError = (errorObject) => {
        console.log("Error", JSON.stringify(errorObject.message));

    }

    render() {
        Registry.getManager().registerComponent('RatingBlock', RatingRenderer);
        return (
            <View style={styles.container}>
                <View style={styles.header}>
                    <Button title="Close" onPress={this.onModalClose} />
                    <Text style={styles.title}>Adaptive Card</Text>
                    <Button title="Close" onPress={this.onModalClose} />
                </View>
                <AdaptiveCards
                    payload={this.payload}
                    onExecuteAction={this.onExecuteAction}
                    hostConfig={this.customHostConfig}
                    onParseError={this.onParseError}
                    ref="adaptiveCardRef" />
            </View>
        );
    }

}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        padding: 10,
        ...Platform.select({
            ios: {
                paddingTop: 50,
            }
        }),
    },
    header: {
        flexDirection: 'row',
        alignItems: 'center',
        justifyContent: 'space-between',
        marginBottom: 10
    },
    title: {
        fontSize: 20
    },
});