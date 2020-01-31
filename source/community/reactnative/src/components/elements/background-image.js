/**
 * BackgroungImage Element.
 * 
 * Refer https://github.com/Microsoft/AdaptiveCards/issues/2032
 */

import React from "react";
import {
    View,
    StyleSheet,
    Image
} from "react-native";

import * as Constants from "../../utils/constants";
import * as Enums from '../../utils/enums';
import * as Utils from '../../utils/util';
import PropTypes from 'prop-types';
import { InputContextConsumer } from '../../utils/context';

export class BackgroundImage extends React.Component {

    constructor(props) {
        super(props);
        this.backgroundImage = props.backgroundImage;
        this.parseHostConfig();
        this.backgroundImage.url = Utils.getImageUrl(this.backgroundImage.url)
        this.state = {
            backgroundImageHeight: 0,
            backgroundImageWidth: 0
        }
    }

    componentDidMount() {
        Image.getSize(this.backgroundImage.url, (backgroundImageWidth, backgroundImageHeight) => {
            this.setState({ backgroundImageWidth, backgroundImageHeight })
        });
    }

    /**
     * @description Parse hostconfig specific to this element
     */
    parseHostConfig = () => {
        this.backgroundImageModeEnumValue = Utils.parseHostConfigEnum(
            Enums.BackgroundImageMode,
            this.backgroundImage.fillMode || this.backgroundImage.mode,
            Constants.AlignStretch);
        this.verticalAlignmentEnumValue = Utils.parseHostConfigEnum(
            Enums.VerticalAlignment,
            this.backgroundImage.verticalAlignment,
            Constants.Top);
        this.horizontalAlignmentEnumValue = Utils.parseHostConfigEnum(
            Enums.HorizontalAlignment,
            this.backgroundImage.horizontalAlignment,
            Constants.LeftAlign);
    }

    /**
     * @description
     * This function is to handle the error occurred loading the image 
     * 
     */
    onError = (onParseError) => {
        let error = { "error": Enums.ValidationError.InvalidPropertyValue, "message": `Not able to load the image` };
        onParseError(error);
    }

    /**
     * @description
     * This function will return the vertical alignment of the image
     * 
     */
    getImageVerticalAlignment = () => {
        switch (this.verticalAlignmentEnumValue) {
            case Enums.VerticalAlignment.Bottom:
                return { justifyContent: Constants.FlexEnd }
            case Enums.VerticalAlignment.Center:
                return { justifyContent: Constants.CenterString }
            case Enums.VerticalAlignment.Top:
            default:
                return { justifyContent: Constants.FlexStart }
        }
    }

    /**
     * @description
     * This function will return the horizontal alignment of the image
     * 
     */
    getImageHorizontalAlignment = () => {
        switch (this.horizontalAlignmentEnumValue) {
            case Enums.HorizontalAlignment.Right:
                return { alignItems: Constants.FlexEnd }
            case Enums.HorizontalAlignment.Center:
                return { alignItems: Constants.CenterString }
            case Enums.HorizontalAlignment.Left:
            default:
                return { alignItems: Constants.FlexStart }
        }
    }

    /**
     * @description
     * This function will return the background image based on the mode.
     * 
     */
    getBackgroundImage = (onParseError) => {
        let imageContainerStyle = [];
        let backgroundImage = [];
        imageContainerStyle.push(styles.imageContainer)
        switch (this.backgroundImageModeEnumValue) {
            case Enums.BackgroundImageMode.Repeat:
                imageContainerStyle.push(this.getImageHorizontalAlignment());
                imageContainerStyle.push(this.getImageVerticalAlignment());
                backgroundImage.push(
                    <Image
                        key="image-repeat-horizontal"
                        resizeMethod={Constants.Resize}
                        source={{ uri: this.backgroundImage.url }}
                        onError={() => { this.onError(onParseError) }}
                        /**
                         * when the resize mode for the image is "repeat". it's always taking the row count as 3. So, we have divided the image height by 3.
                         * Refer https://github.com/facebook/react-native/issues/17684
                         */
                        style={{ width: Constants.FullWidth, height: this.state.backgroundImageHeight / 3, resizeMode: Constants.Repeat }}
                    />
                );
                backgroundImage.push(
                    <Image
                        key="image-repeat-vertical"
                        resizeMethod={Constants.Resize}
                        source={{ uri: this.backgroundImage.url }}
                        onError={() => { this.onError(onParseError) }}
                        style={{ width: this.state.backgroundImageWidth / 3, height: Constants.FullWidth, resizeMode: Constants.Repeat }}
                    />
                );
                break;
            case Enums.BackgroundImageMode.RepeatHorizontally:
                imageContainerStyle.push(this.getImageVerticalAlignment());
                backgroundImage.push(
                    <Image
                        key="image-repeat-horizontal"
                        resizeMethod={Constants.Resize}
                        source={{ uri: this.backgroundImage.url }}
                        onError={() => { this.onError(onParseError) }}
                        style={{ width: Constants.FullWidth, height: this.state.backgroundImageHeight / 3, resizeMode: Constants.Repeat }}
                    />
                );
                break;
            case Enums.BackgroundImageMode.RepeatVertically:
                imageContainerStyle.push(this.getImageHorizontalAlignment());
                backgroundImage.push(
                    <Image
                        key="image-repeat-vertical"
                        resizeMethod={Constants.Resize}
                        source={{ uri: this.backgroundImage.url }}
                        onError={() => { this.onError(onParseError) }}
                        style={{ width: this.state.backgroundImageWidth / 3, height: Constants.FullWidth, resizeMode: Constants.Repeat }}
                    />
                );
                break;
            case Enums.BackgroundImageMode.Stretch:
            default:
                backgroundImage.push(
                    <Image
                        key="image-stretch"
                        source={{ uri: this.backgroundImage.url }}
                        onError={() => { this.onError(onParseError) }}
                        style={{ width: Constants.FullWidth, height: Constants.FullWidth, resizeMode: Constants.AlignStretch }}
                    />
                );
                break;
        }
        return (
            < View style={imageContainerStyle} >
                {backgroundImage}
            </View >
        );
    }

    render() {
        return (
            <InputContextConsumer>
                {({ onParseError }) => (this.getBackgroundImage(onParseError))}
            </InputContextConsumer>
        );
    }
}

BackgroundImage.propTypes = {
    backgroundImage: PropTypes.object.isRequired
};

const styles = StyleSheet.create({
    imageContainer: {
        position: Constants.Absolute,
        width: Constants.FullWidth,
        height: Constants.FullWidth
    }
});
