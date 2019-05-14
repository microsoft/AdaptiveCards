/**
 * Visualizer that lists the sample card payloads and 
 * render the selected card.
 */

import React from 'react';
import {
    FlatList,
    View,
    Text,
    StyleSheet,
    BackHandler,
    Modal
} from 'react-native';

import Renderer from './renderer';
import { PayloadItem } from './payload-item.js';
import SegmentedControl from './segmented-control';
import * as Constants from './constants';
import * as AdaptiveCardBuilder from "../../experimental/adaptive-card-builder/AdaptiveCardBuilder";

const HEIGHT = 40;

export default class Visualizer extends React.Component {

    static navigationOptions = props => {
        return {
            title: Constants.NavigationTitle,
            headerStyle: {
                height: HEIGHT,
                backgroundColor: '#0078D7'
            },
            headerTitleStyle: { color: "white", alignSelf: "center" },
            headerLeft: (<Text
                style={{ color: "white", paddingLeft: 10, fontSize: 15 }}
                onPress={() => props.navigation.goBack()}
            >Back</Text>)
        }
    }

    state = {
        isModalVisible: false,
        selectedPayload: null,
        activeIndex: 0 // payload - scenarios selector
    };

    constructor(props) {
        super(props);

        this.scenarios = this.props.navigation.state.params.scenarios;
        this.payloads = this.props.navigation.state.params.payloads;
    }

    componentWillMount() {
        BackHandler.addEventListener("hardwareBackPress", this.onBackPress);
    }

    componentWillUnmount() {
        BackHandler.removeEventListener("hardwareBackPress", this.onBackPress);
    }

    onBackPress = () => {
        this.props.navigation.goBack();
        return true;
    };

    render() {
        const items = this.state.activeIndex === 0 ? this.payloads : this.scenarios;
        return (
            <View style={styles.container}>
                {this.scenarios && this.scenarios.length > 0 && this.segmentedControl()}
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
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        padding: 10
    },
    payloadPicker: {
        width: '100%',
        height: 150,
        backgroundColor: '#f7f7f7',
    },
    title: {
        fontSize: 20,
        fontWeight: 'bold',
        marginVertical: 12,
    }
});