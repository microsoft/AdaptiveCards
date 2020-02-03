import React from 'react';
import {
    TouchableOpacity,
    View,
    StyleSheet,
    Text,
    Platform,
    Alert
} from 'react-native';

import * as Constants from './constants';

const options = [Constants.AdaptiveCards, Constants.OtherCards, Constants.DialogFlow];

export default class MoreOptions extends React.Component {

    constructor(props) {
        super(props);
    }

    render() {
        return (
            <View style={styles.container}>
                {options.map((option, index) => (this.renderOption(option, index)))}
            </View>
        );
    }

    /**
     * @description This renders each options
     */
    renderOption = (option, key) => (
        <TouchableOpacity
            key={key}
            style={styles.moreOption}
            onPress={() => this.onPress(option)}>
            <Text style={styles.option}>
                {option}
            </Text>
        </TouchableOpacity>
    );

    /**
     * @description Click action for options
     */
    onPress = (option) => {
        if (option == Constants.DialogFlow)
            Alert.alert(
                Constants.InProgress,
                Constants.InProgressText,
                [
                    { text: "Okay", onPress: () => this.props.closeMoreOptions() },
                ],
                { cancelable: false }
            )
        else this.props.moreOptionClick(option);
    }
}

const styles = StyleSheet.create({
    container: {
        marginRight: 10,
        marginTop: Platform.OS === "ios" ? 50 : 10,
        alignSelf: "flex-end",
        paddingHorizontal: 20,
        backgroundColor: "white"
    },
    moreOption: {
        paddingTop: 10,
        paddingBottom: 10,
    },
    option: {
        color: "black",
        fontWeight: "300",
        fontSize: 17
    }
});