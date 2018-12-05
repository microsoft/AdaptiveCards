/**
 * Actions Component.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-action.openurl
 */

import React, { Component } from "react";
import { Text, View, StyleSheet, Image, Platform, Linking, Modal, Button, WebView, Alert } from "react-native";
import { StyleManager } from '../../styles/style-config'
import * as Utils from '../../utils/util';
import { InputContextConsumer } from '../../utils/context'
import AdaptiveCards from '../../adaptive-cards'
import * as Constants from '../../utils/constants';
import { HostConfigManager } from '../../utils/host-config'


export class ActionButton extends Component {

    styleConfig = StyleManager.getManager().styles;

    constructor(props) {
        super(props);

        this.payload = props.json;
        this.title = Constants.EmptyString;
        this.type = Constants.EmptyString;
        this.iconUrl = Constants.EmptyString;
        this.data = {};
    }

    state = {
        modalVisible: false,
        showCard: false,
    };

    setModalVisible(visible) {
        this.setState({ modalVisible: visible });
    }

    render() {
        if(HostConfigManager.getHostConfig().supportsInteractivity === false){
            return null;
        }
        this.parseHostConfig();
        const ButtonComponent = Platform.select({
            ios: () => require('TouchableOpacity'),
            android: () => require('TouchableNativeFeedback'),
        })();
        
        if (this.payload.type === Constants.ActionSubmit) {
            return (<InputContextConsumer>
                {({ inputArray, onExecuteAction }) => (
                    <ButtonComponent onPress={() => {
                        this.onSubmitActionCalled(inputArray,onExecuteAction)
                     }}>
                        {this.buttonContent()}
                    </ButtonComponent>
                )}
            </InputContextConsumer>);
        }
        else if (this.payload.type === Constants.ActionOpenUrl) {

            return (<InputContextConsumer>
                {({ onExecuteAction }) => (<ButtonComponent onPress={() => {
                        this.onOpenURLCalled(onExecuteAction)
                     }}>{this.buttonContent()}
            </ButtonComponent>)}
            </InputContextConsumer>);
        }else if (this.payload.type === Constants.ActionShowCard) {

            return (<InputContextConsumer>
                {({ onExecuteAction }) => (<View><ButtonComponent onPress={this.changeShowCardState}>{this.buttonContent()}
            </ButtonComponent>
            { (this.payload.type === Constants.ActionShowCard) ? (this.state.showCard ? 
                                    (<AdaptiveCards payload={this.payload.card} onExecuteAction={onExecuteAction}/>):null) : null}
            </View>)}
            </InputContextConsumer>);
        }
    }

    /**
     * @description Invoked for the action type Constants.ActionSubmit
     */
    onSubmitActionCalled(inputItem, onExecuteAction) {
        let mergedObject = null;
        if(this.data!==null)
        {
            mergedObject = {...this.data,...inputItem};
        }else{
            mergedObject = inputItem;
        }
        let actionObject = {"type":this.payload.type,"data":mergedObject};        
        onExecuteAction(actionObject);
    }

    onOpenURLCalled = ( onExecuteAction ) => {
        let actionObject = {"type":this.payload.type,"url":this.payload.url};        
        onExecuteAction(actionObject);
    }

    /**
     * @description Invoked for the action type Constants.ActionOpenUrl
     */
    onButtonTapped = () => {
        if (this.payload.type === Constants.ActionOpenUrl) {
            this.handleOpenUrlAction();
        }
    };

    closeModal = () => {
        this.setState({
            modalVisible: false
        })
    }

    changeShowCardState = () => {
        this.setState(prevState => ({
            showCard: !prevState.showCard
          }));
    }

    /**
     * @description Shows the Constants.ActionOpenUrl contents in modal view
     */
    getModalConent() {

        var modalComponent = null;
        if (this.payload.type === Constants.ActionOpenUrl) {
            modalComponent = (<Modal
                animationType="slide"
                transparent={false}
                supportedOrientations={['portrait', 'landscape']}
                visible={this.state.modalVisible}
                onRequestClose={() => {
                    Alert.alert('Modal has been closed.');
                }}>
                <View style={styles.webViewHeader}>
                    <Button 
                        style={styles.backButton} 
                        title=" < Back" 
                        onPress={this.closeModal}/>
                </View>
                <WebView
                    source={{ uri: this.payload.url }}
                    style={{ flex: 1 }} />
            </Modal>);
        }
        return modalComponent;
    }

    /**
     * @description Invoked for the action type Constants.ActionOpenUrl
     */
    handleOpenUrlAction() {
        this.setState({
            modalVisible: true
        });
        /*
        // For now opening the url in the native browser since navigation is not present.
        Linking.canOpenURL(this.payload.url).then(supported => {
            if (supported) {
              Linking.openURL(this.payload.url);
            } else {
              console.log("Don't know how to open URI: " + this.payload.url);
            }
          });  */
    }

    parseHostConfig() {
        this.title = this.payload.title;
        this.type = this.payload.type;
        this.iconUrl = this.payload.iconUrl;
        this.data = this.payload.data;
    }

    buttonContent = () => {
        return (
            <View
                style={[
                    styles.button,this.styleConfig.actionIconFlex]}>
                {
                    !Utils.isNullOrEmpty(this.iconUrl) ?
                        <Image resizeMode="center"
                            source={{ uri: this.iconUrl }}
                            style={[styles.buttonIcon,this.styleConfig.actionIcon]} />
                        : null
                }
                <Text style={[styles.buttonTitle,this.styleConfig.fontConfig]}>
                    {this.title}
                </Text>
                {/* {this.getModalConent()} */}
            </View>
        );
    };
}

const styles = StyleSheet.create({
    button: {
        flexWrap: 'nowrap',
        alignItems: Constants.CenterString,
        justifyContent: Constants.CenterString,
        padding: 10,
		marginBottom: 10,
		marginRight: 10,
        backgroundColor: "#1D9BF6",
        borderRadius: 15,
    },
    buttonTitle: {
        color: Constants.WhiteColor,
    },
    buttonIcon: {
        marginLeft: 5,
        marginRight: 10,
    },
    webViewHeader: {
        flexDirection: Constants.FlexRow,
        alignItems: Constants.CenterString,
        justifyContent: Constants.SpaceBetween,
        ...Platform.select({
            android: {
                padding: 10,
            },
            ios: {
                marginTop: 30 ,
                padding: 5
            }
        }),
        marginBottom: 10,
    },
    backButton: { alignItems: Constants.FlexStart, marginLeft: 20 }
});

