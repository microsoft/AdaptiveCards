import React from "react";
import { View, Text, StyleSheet } from "react-native";
import * as Constants from "../../utils/constants";
import Video from "react-native-video";

export class Media extends React.Component {
    render() {
        return (
            <View style={styles.container}>
                <Video
                    source={{
                        uri:
                            "https://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp4"
                    }}
                    controls={true}
                    style={styles.nativeVideoControls}
                />
            </View>
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
    nativeVideoControls: {
        height: 300,
        width: Constants.FullWidth
    }
});
