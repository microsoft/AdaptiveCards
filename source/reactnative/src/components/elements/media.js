import React from "react";
import { View, StyleSheet, TouchableOpacity, Image, Platform } from "react-native";
import MediaControls, { PLAYER_STATES } from 'react-native-media-controls';
import * as Constants from "../../utils/constants";
import Video from "react-native-video";
import ElementWrapper from './element-wrapper'

export class Media extends React.Component {
    videoPlayer;
    constructor(props) {
        super(props);
        this.payload = props.json;
        this.sources = this.getMediaSources(this.payload.sources)
        this.state = {
            currentSourceIndex: 0,
            onLoad: false,
            currentTime: 0,
            duration: 0,
            isFullScreen: false,
            isLoading: true,
            paused: true,
            playerState: PLAYER_STATES.PAUSED,

        }
    }

    getMediaSources = (sources) => {
        sources.forEach(source => {
            this.addUriAttribute(source)
        })
        return sources
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

    onSeek = seek => {
        this.videoPlayer.seek(seek);
    };

    onPaused = playerState => {
        this.setState({
            paused: !this.state.paused,
            playerState,
        });
    };

    onReplay = () => {
        this.setState({ playerState: PLAYER_STATES.PLAYING });
        this.videoPlayer.seek(0);
    };

    onProgress = data => {
        const { isLoading, playerState } = this.state;
        // Video Player will continue progress even if the video already ended
        if (!isLoading && playerState !== PLAYER_STATES.ENDED) {
            this.setState({ currentTime: data.currentTime });
        }
    };

    onLoad = data => this.setState({ duration: data.duration, isLoading: false });

    onLoadStart = data => this.setState({ isLoading: true });

    onEnd = () => this.setState({ playerState: PLAYER_STATES.ENDED });

    exitFullScreen = () => { };

    enterFullScreen = () => { };

    onFullScreen = () => { };

    onSeeking = currentTime => this.setState({ currentTime });

    render() {
        return (
            <ElementWrapper json={this.payload}>
                <View style={styles.container}>
                    <Video
                        source={this.sources[this.state.currentSourceIndex]}
                        fullscreen={true}
                        controls={true}
                        id={this.payload.id ? this.payload.id : "video"}
                        // paused={true}
                        onError={this.videoError}
                        // onLoad={this.videoLoadSuccess}
                        onEnd={this.onEnd}
                        onLoad={this.onLoad}
                        onLoadStart={this.onLoadStart}
                        onProgress={this.onProgress}
                        paused={this.state.paused}
                        ref={videoPlayer => (this.videoPlayer = videoPlayer)}
                        style={styles.nativeVideoControls}
                    />
                    {Platform.OS !== 'ios' && (
                        <MediaControls
                            duration={this.state.duration}
                            isLoading={this.state.isLoading}
                            mainColor="orange"
                            onFullScreen={this.onFullScreen}
                            onPaused={this.onPaused}
                            onReplay={this.onReplay}
                            onSeek={this.onSeek}
                            onSeeking={this.onSeeking}
                            isFullScreen={true}
                            playerState={this.state.playerState}
                            progress={this.state.currentTime}
                        />
                    )}
                    {(this.state.isLoading && this.payload.poster) && <Image source={{ uri: this.payload.poster }} style={styles.fullScreen}></Image>}
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
        backgroundColor: Constants.blackColor
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
        width: Constants.FullWidth
    }
});
