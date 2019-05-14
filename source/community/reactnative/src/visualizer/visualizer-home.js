import React from 'react';
import {
    TouchableOpacity,
    View,
    StyleSheet,
    Text,
    Image,
    FlatList,
    BackHandler,
    Alert
} from 'react-native';

import AdaptiveCardPayloads from '../visualizer/payloads/payloads/';
import OtherCardPayloads from '../../experimental/adaptive-card-builder/payloads/';
import * as Constants from './constants';

// sample scenarios
const calendarReminderPayload = require('./payloads/scenarios/calendar-reminder.json');
const flightUpdatePayload = require('./payloads/scenarios/flight-update.json');
const inputFormPayload = require('./payloads/scenarios/input-form.json');
const restaurantPayload = require('./payloads/scenarios/restaurant.json');
const containerPayload = require('./payloads/scenarios/container-item.json');
const weatherPayload = require('./payloads/scenarios/weather-large.json');
const activityUpdatePayload = require('./payloads/scenarios/activity-update.json');
const foodOrderPayload = require('./payloads/scenarios/food-order.json');
const imageGalleryPayload = require('./payloads/scenarios/image-gallery.json');
const sportingEventPayload = require('./payloads/scenarios/sporting-event.json');
const mediaPayload = require('./payloads/scenarios/media.json');
const markdownPayload = require('./payloads/scenarios/markdown.json');

const HEIGHT = 40;
const rightArrow = require("./assets/right_arrow.png")

const items = [
    {
        title: Constants.AdaptiveCardVisualizer,
        color: "#53BA94",
        text: Constants.AdaptiveCardVisualizerInfo
    },
    {
        sectionHeader: Constants.AdaptiveCardExperiments,
        title: Constants.OtherCards,
        color: "#BA5C96",
        text: Constants.AdaptiveCardExperimentsInfo
    },
    {
        title: Constants.DialogFlow,
        color: "#C78D4D",
        text: Constants.DialogFlowInfo
    }
];



export default class VisualizerHome extends React.Component {

    static navigationOptions = {
        title: Constants.NavigationTitle,
        headerStyle: {
            height: HEIGHT,
            backgroundColor: '#0078D7'
        },
        headerTitleStyle: { color: "white", alignSelf: "center" }
    }

    constructor(props) {
        super(props);
        this.adaptiveCardScenarios = [{
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
            title: 'Food order',
            json: foodOrderPayload,
            tags: this.getTags(foodOrderPayload),
            icon: require('./assets/fastfood.png')
        },
        {
            title: 'Image gallery',
            json: imageGalleryPayload,
            tags: this.getTags(imageGalleryPayload),
            icon: require('./assets/photo_library.png')
        },
        {
            title: 'Sporting event',
            json: sportingEventPayload,
            tags: this.getTags(sportingEventPayload),
            icon: require('./assets/run.png')
        }, {
            title: 'Restaurant',
            json: restaurantPayload,
            tags: this.getTags(restaurantPayload),
            icon: require('./assets/restaurant.png')
        },
        {
            title: 'Input form',
            json: inputFormPayload,
            tags: this.getTags(inputFormPayload),
            icon: require('./assets/form.png')
        },
        {
            title: 'Media',
            json: mediaPayload,
            tags: this.getTags(mediaPayload),
            icon: require('./assets/video_library.png')
        },
        {
            title: 'Stock Update',
            json: containerPayload,
            tags: this.getTags(containerPayload),
            icon: require('./assets/square.png')
        },
        {
            title: 'Markdown',
            json: markdownPayload,
            tags: this.getTags(markdownPayload),
            icon: require('./assets/code.png')
        }];

    }

    componentWillMount() {
        BackHandler.addEventListener("hardwareBackPress", this.onBackPress);
    }

    componentWillUnmount() {
        BackHandler.removeEventListener("hardwareBackPress", this.onBackPress);
    }

    onBackPress = () => {
        //Exit the App
        BackHandler.exitApp();
        return true;
    };

    render() {
        return (
            <View style={styles.container}>
                <FlatList
                    data={items}
                    keyExtractor={(item, index) => index.toString()}
                    renderItem={this.renderItem}
                />
            </View>
        );
    }

    renderItem = ({ item }) => {
        return item.sectionHeader ? this.renderHeader(item) : this.renderContent(item);
    }

    /**
     * @description This renders the content in the flat list
     */
    renderContent = (item) => (
        <TouchableOpacity
            style={[styles.navigationItem, { backgroundColor: item.color }]}
            onPress={() => this.onPress(item.title)}>
            <View style={styles.textContainer}>
                <Text style={styles.title}>
                    {item.title}
                </Text>
                <Text style={styles.text}>
                    {item.text}
                </Text>
            </View>
            <Image source={rightArrow} style={styles.rightArrow} />
        </TouchableOpacity>
    );

    /**
     * @description This renders the section header and content
     */
    renderHeader = (item) => (
        <View>
            <Text style={styles.sectionHeader}>{item.sectionHeader}</Text>
            {this.renderContent(item)}
        </View>
    );

    /**
     * @description OnPress action
     */
    onPress = (title) => {
        if (title == Constants.AdaptiveCardVisualizer)
            this.props.navigation.navigate("Visualizer", {
                payloads: AdaptiveCardPayloads,
                scenarios: this.adaptiveCardScenarios
            });
        else if (title == Constants.OtherCards)
            this.props.navigation.navigate("Visualizer", {
                payloads: OtherCardPayloads
            });
        else {
            Alert.alert(
                Constants.InProgress,
                Constants.InProgressText,
                [
                    { text: "Okay", onPress: () => console.log('OK Pressed') },
                ],
                { cancelable: false }
            )
        }
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
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: 'white',
        padding: 10,
        paddingTop: 25
    },
    navigationItem: {
        flex: 1,
        flexDirection: 'row',
        justifyContent: "space-between",
        padding: 10,
        borderRadius: 5,
        marginBottom: 10
    },
    textContainer: {
        flex: 1
    },
    title: {
        color: "white",
        fontWeight: "bold",
        fontStyle: 'italic',
        fontSize: 16,
        marginBottom: 8
    },
    text: {
        color: "white"
    },
    sectionHeader: {
        color: "black",
        fontSize: 18,
        fontStyle: 'italic',
        fontWeight: "600",
        marginBottom: 10
    },
    rightArrow: {
        alignSelf: "center",
        width: 40,
        height: 40
    }
});