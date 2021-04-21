/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow strict-local
 */

import React from 'react';
import {
    StyleSheet,
    View,
    Platform
} from 'react-native';
import Visualizer from './src/visualizer/visualizer';

export default class App extends React.Component {
    render() {
        return (
            <View style={styles.container}>
                <Visualizer />
            </View>
        );
    }
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: 'white',
        padding: 10,
        ...Platform.select({
            ios: {
                paddingTop: 50,
            }
        })
    }
});
