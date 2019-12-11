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
    Linking,
    ScrollView
} from 'react-native';

import AdaptiveCard from '../adaptive-card';
import { RatingRenderer } from './rating-renderer';
import { Registry } from '../components/registration/registry';
import * as Utils from '../utils/util';

export default class Renderer extends React.Component {

    state = {
        isJSONVisible: false
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
    customThemeConfig = {
        button: {
            backgroundColor: '#66BB6A'
        }
    }

    constructor(props) {
        super(props);
        this.payload = props.payload;
        this.onModalClose = props.onModalClose;
    }

    render() {
        Registry.getManager().registerComponent('RatingBlock', RatingRenderer);
        let { isJSONVisible } = this.state;

        return (
            <View style={styles.container}>
                <View style={styles.header}>
                    <Button title="Close" onPress={this.onModalClose} />
                    <Text style={styles.title}>Adaptive Card</Text>
                    <Button title={isJSONVisible ? 'Card' : 'Json'} onPress={this.toggleJSONView} />
                </View>
                {isJSONVisible ?
                    <ScrollView contentContainerStyle={styles.jsonContainer}>
                        <Text style={{ fontFamily: 'Courier New' }}>
                            {JSON.stringify(this.payload, null, '  ')}
                        </Text>
                    </ScrollView>
                    :
                    <AdaptiveCard
                        payload={this.payload}
                        onExecuteAction={this.onExecuteAction}
                        hostConfig={this.customHostConfig}
                        themeConfig={this.customThemeConfig}
                        onParseError={this.onParseError}
                        ref="adaptiveCardRef" />
                }
            </View>
        );
    }

    /**
     * @description Handler for the payload actions.
     * @param {object} actionObject - Details and data about the action.
     */
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
        } else if (actionObject.type === "Action.OpenUrl" && !Utils.isNullOrEmpty(actionObject.url)) {
            Linking.canOpenURL(actionObject.url).then(supported => {
                if (supported) {
                    Linking.openURL(actionObject.url).catch(() => {
                        console.log("Failed to open URI: " + actionObject.url)
                        this.alertAction(actionObject);
                    });
                } else {
                    console.log("Don't know how to open URI: " + actionObject.url);
                    this.alertAction(actionObject);
                }
            });
        } else this.alertAction(actionObject);

    }

    /**
     * @description Alert the action object 
     * @param {object} actionObject - Details and data about the action.
     */

    alertAction = (actionObject) => {
        Alert.alert(
            'Action',
            JSON.stringify(actionObject),
            [
                { text: "Okay", onPress: () => console.log('OK Pressed') },
            ],
            { cancelable: false }
        )
    }

    /**
     * @description Handler for payload parsing errors(if any)
     * @param {object} errorObject - Details about the error.
     */
    onParseError = (errorObject) => {
        console.log("Error", JSON.stringify(errorObject.message));
    }

    /**
     * @description Toggle the view state between card and its payload.
     */
    toggleJSONView = () => {
        this.setState({
            isJSONVisible: !this.state.isJSONVisible
        })
    }
}

const styles = StyleSheet.create({
    container: {
        ...Platform.select({
            ios: {
                marginBottom: 84,
            }
        }),
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
        fontSize: 20,
        flexGrow: 1,
        textAlign: 'center'
    },
    jsonContainer: {
        backgroundColor: '#f7f7f7',
    }
});