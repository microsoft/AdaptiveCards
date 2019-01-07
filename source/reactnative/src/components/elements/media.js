/**
 * Media Element.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#media
 */

import React from "react";
import {
    View,
    StyleSheet,
    Image
} from "react-native";

import * as Constants from "../../utils/constants";
import Video from "react-native-video";
import ElementWrapper from './element-wrapper'

export class Media extends React.Component {
    constructor(props) {
        super(props);
        this.payload = props.json;
        this.sources = this.getMediaSources(this.payload.sources)
        this.state = {
            currentSourceIndex: 0,
            onLoad: false,
        }
    }

    getMediaSources = (sources) => {
        sources.forEach(source => {
            this.addUriAttribute(source)
        })
        return sources;
    }

    addUriAttribute = (source) => {
        if (source.url) {
            source.uri = source.url
        }
        return source;
    }

    videoError = () => {
        if (this.state.currentSourceIndex < (this.sources.length - 1)) {
            this.setState({
                currentSourceIndex: this.state.currentSourceIndex + 1
            })
        }
    }

    videoLoadSuccess = () => {
        this.setState({
            onLoad: true
        })
    }

    render() {
        return (
            <ElementWrapper json={this.payload}>
                <View style={styles.container}>
                    <Video
                        source={this.sources[this.state.currentSourceIndex]}
                        fullscreen={true}
                        controls={true}
                        id={this.payload.id ? this.payload.id : "video"}
                        paused={false}
                        onError={this.videoError}
                        onLoad={this.videoLoadSuccess}
                        style={styles.nativeVideoControls}
                    />
                    {(!this.state.onLoad && this.payload.poster) && <Image source={{ uri: this.payload.poster }} style={styles.fullScreen}></Image>}
                </View>
            </ElementWrapper>
        );
    }
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        justifyContent: Constants.CenterString,
        alignItems: Constants.CenterString,
        backgroundColor: Constants.blackColor,
    },
    fullScreen: {
        position: 'absolute',
        top: 0,
        left: 0,
        bottom: 0,
        right: 0,
    },
    nativeVideoControls: {
        height: 300,
        width: Constants.FullWidth,
    }
});
