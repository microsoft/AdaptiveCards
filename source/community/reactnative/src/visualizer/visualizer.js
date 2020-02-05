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
        scenarios: Payloads.AdaptiveCardScenarios,
        activeIndex: 0 // payload - scenarios selector
    };

    constructor(props) {
        super(props);
    }

    render() {
        const { activeIndex, payloads, scenarios } = this.state;

        const items = activeIndex === 0 ? payloads : scenarios;
        return (
            <View style={styles.container}>
                <TouchableOpacity onPress={() => this.onMoreOptionsClick()} style={styles.moreContainer}>
                    <Image source={moreIcon} style={styles.moreIcon} />
                </TouchableOpacity>
                {scenarios && scenarios.length > 0 ? this.segmentedControl() : this.header()}
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
     * @description Segment control for payloads and scenarios.
     */
    segmentedControl = () => {
        const segmentedItems = [
            { title: 'Payloads', value: 'payloads' },
            { title: 'Scenarios', value: 'scenarios' }
        ];
        return (
            <SegmentedControl
                items={segmentedItems}
                onStatusChange={(index) => this.segmentedControlStatusDidChange(index)}
            />
        );
    }

    /**
     * @description Add header for payloads as there is no scenarios
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
     * @param {number} index - index of the selected item
     */
    segmentedControlStatusDidChange = (index) => {
        this.setState({
            activeIndex: index
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
                        scenarios: Payloads.AdaptiveCardScenarios,
                        activeIndex : 0
                    });
                else this.closeMoreOptions();
                break;
            case Constants.OtherCards:
                if (activeOption !== Constants.OtherCards)
                    this.setState({
                        isMoreVisible: false,
                        activeOption: Constants.OtherCards,
                        payloads: Payloads.OtherCardPayloads,
                        scenarios: [],
                        activeIndex : 0
                    });
                else this.closeMoreOptions();
                break;
            default:
                if (activeOption !== Constants.AdaptiveCards)
                    this.setState({
                        isMoreVisible: false,
                        activeOption: Constants.AdaptiveCards,
                        payloads: Payloads.AdaptiveCardPayloads,
                        scenarios: Payloads.AdaptiveCardScenarios,
                        activeIndex : 0
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
    container: {
        flex: 1
    },
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
        flex: 1,
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