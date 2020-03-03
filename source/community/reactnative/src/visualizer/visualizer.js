/**
 * Visualizer that lists the sample card payloads and 
 * render the selected card.
 */

import React from 'react';
import {
    FlatList,
    View,
    StyleSheet,
    Image,
    Text,
    Platform,
    TouchableOpacity,
    Modal
} from 'react-native';

import Renderer from './renderer';
import { PayloadItem } from './payload-item.js';
import SegmentedControl from './segmented-control';
import MoreOptions from './more-options';
import * as Constants from './constants';
import * as Payloads from './payloads';
import * as AdaptiveCardBuilder from "../../experimental/adaptive-card-builder/AdaptiveCardBuilder";


const moreIcon = Platform.select({
    ios: require("./assets/more-ios.png"),
    android: require("./assets/more-android.png"),
    windows: require("./assets/more-android.png")
})


export default class Visualizer extends React.Component {

    state = {
        isModalVisible: false,
        isMoreVisible: false,
        selectedPayload: null,
        activeOption: Constants.AdaptiveCards,
        payloads: Payloads.AdaptiveCardPayloads,
        activeIndexValue: Constants.PayloadHeader // payload - scenarios selector
    };

    constructor(props) {
        super(props);
    }

    render() {
        const items = this.getPayloadItems();
        return (
            <View style={{ flex: 1 }}>
                <TouchableOpacity onPress={() => this.onMoreOptionsClick()} style={styles.moreContainer}>
                    <Image source={moreIcon} style={styles.moreIcon} />
                </TouchableOpacity>
                {this.state.activeOption !== Constants.OtherCards ? this.segmentedControl() : this.header()}
                <FlatList
                    data={items}
                    keyExtractor={(item, index) => index.toString()}
                    renderItem={({ item, index }) => (
                        <PayloadItem
                            onItemSelection={() => this.payloadDidSelect(item)}
                            item={item}
                            index={index} />
                    )}
                />
                <Modal
                    animationType="slide"
                    transparent={false}
                    supportedOrientations={['portrait', 'landscape']}
                    visible={this.state.isModalVisible}
                    onRequestClose={() => {
                    }}>
                    <Renderer
                        payload={this.state.selectedPayload}
                        isDataBinding={Constants.DataBinding === this.state.activeIndexValue}
                        onModalClose={this.closeModal}
                    />
                </Modal>
                <Modal
                    animationType="none"
                    transparent={true}
                    supportedOrientations={['portrait', 'landscape']}
                    visible={this.state.isMoreVisible}
                    onRequestClose={() => this.closeMoreOptions()}>
                    {this.modalLayout()}
                </Modal>
            </View>
        );
    }

    /**
     * @description get payload item depends on the activeIndexValue
     */
    getPayloadItems = () => {
        switch (this.state.activeIndexValue) {
            case Constants.PayloadHeader:
                return this.state.payloads;
            case Constants.Scenarios:
                return Payloads.AdaptiveCardScenarios;
            case Constants.DataBinding:
                return Payloads.DataBindingPayloads;
            default:
                return this.state.payloads;
        }
    }

    /**
     * @description Segment control for Payloads, Scenarios and DataBinding.
     */
    segmentedControl = () => {
        const segmentedItems = [
            { title: Constants.PayloadHeader, value: Constants.PayloadHeader },
            { title: Constants.Scenarios, value: Constants.Scenarios },
            { title: Constants.DataBinding, value: Constants.DataBinding }
        ];
        return (
            <SegmentedControl
                items={segmentedItems}
                onStatusChange={(index) => this.segmentedControlStatusDidChange(segmentedItems[index].value)}
            />
        );
    }

    /**
     * @description Add header for payloads if the active option is other card type
     */
    header = () => (
        <View style={styles.header}>
            <Text style={styles.title}>
                {Constants.PayloadHeader}
            </Text>
        </View>
    );

    /**
     * @description Present the modal
     * @param {object} payload - Selected payload
     */
    payloadDidSelect = (payload) => {
        /*  Check if the payload is HeroCard / ThumbnailCard */
        const notAdaptiveCard = payload.json.contentType &&
            (payload.json.contentType === "application/vnd.microsoft.card.hero" ||
                payload.json.contentType === "application/vnd.microsoft.card.thumbnail");

        this.setState({
            isModalVisible: true,
            selectedPayload: notAdaptiveCard ? AdaptiveCardBuilder.buildAdaptiveCard(payload.json.content, payload.json.contentType) : payload.json
        })
    }

    /**
     * @description Dismiss the modal
     */
    closeModal = () => {
        this.setState({
            isModalVisible: false
        })
    }

    /**
     * @description Invoked on payload type segmented control status change
     * @param {string} indexValue - value of the selected index in segmented control
     */
    segmentedControlStatusDidChange = (indexValue) => {
        this.setState({
            activeIndexValue: indexValue
        });
    }

    /**
     * @description Layout of the more option modal
     */
    modalLayout = () => (
        <TouchableOpacity
            activeOpacity={1}
            onPress={() => this.closeMoreOptions()}
            style={styles.moreOptionsModal}
        >
            <MoreOptions
                closeMoreOptions={this.closeMoreOptions}
                moreOptionClick={this.moreOptionClick}
            />
        </TouchableOpacity>
    );

    /**
     * @description Click action for more option
     * @param option - selected option
     */
    moreOptionClick = (option) => {
        const { activeOption } = this.state;
        switch (option) {
            case Constants.AdaptiveCards:
                if (activeOption !== Constants.AdaptiveCards)
                    this.setState({
                        isMoreVisible: false,
                        activeOption: Constants.AdaptiveCards,
                        payloads: Payloads.AdaptiveCardPayloads,
                        activeIndexValue: Constants.PayloadHeader
                    });
                else this.closeMoreOptions();
                break;
            case Constants.OtherCards:
                if (activeOption !== Constants.OtherCards)
                    this.setState({
                        isMoreVisible: false,
                        activeOption: Constants.OtherCards,
                        payloads: Payloads.OtherCardPayloads,
                        activeIndexValue: Constants.PayloadHeader
                    });
                else this.closeMoreOptions();
                break;
            default:
                if (activeOption !== Constants.AdaptiveCards)
                    this.setState({
                        isMoreVisible: false,
                        activeOption: Constants.AdaptiveCards,
                        payloads: Payloads.AdaptiveCardPayloads,
                        activeIndexValue: Constants.PayloadHeader
                    });
                else this.closeMoreOptions();
                break;
        }
    }

    /**
     * @description Click action for more icon, shows the options modal
     */
    onMoreOptionsClick = () => {
        this.setState({
            isMoreVisible: true
        })
    }

    /**
     * @description Dismiss the more options modal
     */
    closeMoreOptions = () => {
        this.setState({
            isMoreVisible: false
        })
    }
}

const styles = StyleSheet.create({
    payloadPicker: {
        width: '100%',
        height: 150,
        backgroundColor: '#f7f7f7',
    },
    header: {
        marginVertical: 12,
        justifyContent: "center",
        height: 34,
        backgroundColor: '#0078D7'
    },
    title: {
        fontSize: 17,
        fontWeight: '400',
        color: "white",
        alignSelf: "center"
    },
    moreContainer: {
        alignSelf: "flex-end"
    },
    moreIcon: {
        padding: 10,
        width: 25,
        height: 25
    },
    moreOptionsModal: {
        backgroundColor: "rgba(0, 0, 0, 0.1)"
    },
    more: {
        marginTop: 50,
        marginRight: 10,
        alignSelf: "flex-end",
        width: 100,
        height: 100,
        backgroundColor: "white"
    }
});