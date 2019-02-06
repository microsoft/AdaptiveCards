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
import * as Enums from '../../utils/enums';
import Video from "react-native-video";
import ElementWrapper from './element-wrapper'
import { InputContextConsumer, InputContext } from '../../utils/context';
import * as Utils from '../../utils/util';


export class Media extends React.Component {

    static contextType = InputContext;

    constructor(props) {
        super(props);
        this.payload = props.json;
        this.sources = this.getMediaSources(this.payload.sources)
        this.state = {
            currentSourceIndex: 0,
            onLoad: false,
        }
    }

    componentDidMount() {
        if (this.payload.sources && this.payload.sources.length > 0) {
            this.payload.sources.forEach(source => {
                this.context.addResourceInformation(source.url, source.mimeType);
            })
        }
        if(!Utils.isNullOrEmpty(this.payload.poster)){
            this.context.addResourceInformation(this.payload.poster, "");
        }
    }

    getMediaSources = (sources) => {
        if (this.payload.sources && this.payload.sources.length > 0) {
            sources.forEach(source => {
                this.addUriAttribute(source);
            })
            return sources;
        } else {
            return null;
        }
    }

    addUriAttribute = (source) => {
        if (source.url) {
            source.uri = source.url
        }
        return source;
    }

    videoError = (onParseError) => {
        if (this.state.currentSourceIndex < (this.sources.length - 1)) {
            this.setState({
                currentSourceIndex: this.state.currentSourceIndex + 1
            })
        } else {
            let error = { "error": Enums.ValidationError.InvalidPropertyValue, "message": `Not able to play the source` };
            onParseError(error);
        }
    }

    videoLoadSuccess = () => {
        this.setState({
            onLoad: true
        })
    }

    render() {
        return (
            <InputContextConsumer>
                {({ onParseError }) =>
                    (
                        <ElementWrapper json={this.payload}>
                            <View style={styles.container}>
                                {
                                    this.sources &&
                                    <Video
                                        source={this.sources[this.state.currentSourceIndex]}
                                        fullscreen={true}
                                        controls={true}
                                        id={this.payload.id ? this.payload.id : "video"}
                                        paused={false}
                                        onError={() => { this.videoError(onParseError) }}
                                        onLoad={this.videoLoadSuccess}
                                        style={styles.nativeVideoControls}
                                    />
                                }
                                {(!this.state.onLoad && this.payload.poster) && <Image source={{ uri: this.payload.poster }} style={styles.nativeVideoControls}></Image>}
                            </View>
                        </ElementWrapper>
                    )
                }
            </InputContextConsumer>
        );
    }
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        justifyContent: Constants.CenterString,
        alignItems: Constants.CenterString,
        backgroundColor: Constants.BlackColor,
        height: 300,
        width: Constants.FullWidth,
    },
    nativeVideoControls: {
        position: 'absolute',
        top: 0,
        left: 0,
        bottom: 0,
        right: 0,
    }
});
