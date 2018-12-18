/**
 * Visualizer that lists the sample card payloads and 
 * render the selected card.
 */

import React from 'react';
import {
    FlatList,
    View,
    StyleSheet,
    Modal
} from 'react-native';

import Renderer from './renderer';
import { PayloadItem } from './payload-item.js';
import SegmentedControl from './segmented-control';

// sample scenarios
const calendarReminderPayload = require('./payloads/scenarios/calendar-reminder.json');
const flightUpdatePayload = require('./payloads/scenarios/flight-update.json');
const inputFormPayload = require('./payloads/scenarios/input-form.json');
const restaturantPayload = require('./payloads/scenarios/restaurant.json');
const containerPayload = require('./payloads/scenarios/container-item.json');
const weatherPayload = require('./payloads/scenarios/weather-large.json');
const activityUpdatePayload = require('./payloads/scenarios/activity-update.json');

import payloads from '../visualizer/payloads/payloads/';

export default class Visualizer extends React.Component {
    state = {
        isModalVisible: false,
        selectedPayload: null,
        activeIndex: 0 // payload - scenarios selector
    };

    constructor(props) {
        super(props);

        this.scenarios = [{
            title: 'Calendar reminder',
            json: calendarReminderPayload,
            tags: this.getTags(calendarReminderPayload),
            icon: require('./assets/calendar.png')
        }, {
            title: 'Flight update',
            json: flightUpdatePayload,
            tags: this.getTags(flightUpdatePayload),
            icon: require('./assets/flight.png')
        }, {
            title: 'Weather Large',
            json: weatherPayload,
            tags: this.getTags(weatherPayload),
            icon: require('./assets/cloud.png')
        }, {
            title: 'Activity Update',
            json: activityUpdatePayload,
            tags: this.getTags(activityUpdatePayload),
            icon: require('./assets/done.png')
        },
        {
            title: 'Input form',
            json: inputFormPayload,
            tags: this.getTags(inputFormPayload),
            icon: require('./assets/form.png')
        }, {
            title: 'Restaurant',
            json: restaturantPayload,
            tags: this.getTags(restaturantPayload),
            icon: require('./assets/restaurant.png')
        }, {
            title: 'Container type',
            json: containerPayload,
            tags: this.getTags(containerPayload),
            icon: require('./assets/restaurant.png')
        }];
    }

    render() {
        const segmentedItems = [
            { title: 'Payloads', value: 'payloads' },
            { title: 'Scenarios', value: 'scenarios' }
        ];

        const items = this.state.activeIndex === 0 ? payloads : this.scenarios;

        return (
            <View style={styles.container}>
                <SegmentedControl
                    items={segmentedItems}
                    onStatusChange={(index) => this.segmentedControlStatusDidChange(index)}
                />
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
                        Alert.alert('Modal has been closed.');
                    }}>
                    <Renderer
                        payload={this.state.selectedPayload}
                        onModalClose={this.closeModal}
                    />
                </Modal>
            </View>
        )
    }

    /**
     * @description Present the modal
     * @param {object} payload - Selected payload
     */
    payloadDidSelect = (payload) => {
        this.setState({
            isModalVisible: true,
            selectedPayload: payload.json
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
     * @description Return the unique element types present in the given payload json
     * @param {object} json - payload json
     * @return {Array} - Array of element types
     */
    getTags = (json) => {
        let tags = new Set();
        // elements
        json.body.map(element => {
            tags.add(element.type);
        });
        // actions
        if (json.actions && json.actions.length > 0) {
            tags.add("Actions");
        }
        return Array.from(tags);
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
        flex: 1
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