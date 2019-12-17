/**
 * ContainerWrapper component that wraps the container type element
 * and takes care of common container related parsing & styling.
 * 
 * @example
 * <ContainerWrapper json={payload}>
 *  <Column json={payload}></Column>
 * </ContainerWrapper>
 */

import React from 'react';
import {
    View,
    StyleSheet
} from 'react-native';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';
import * as Constants from "../../utils/constants";
import { BackgroundImage } from '../elements';
import { HostConfigManager } from '../../utils/host-config';

export class ContainerWrapper extends React.PureComponent {

    constructor(props) {
        super(props);
        this.payload = props.json;
    }

    render() {
        const receivedStyles = this.props.style;
        const computedStyles = this.getComputedStyles();
        return (
            <View style={[computedStyles, receivedStyles]}>
                {!Utils.isNullOrEmpty(this.payload.backgroundImage) ? this.getBackgroundImageContainer() : this.props.children}
            </View>
        )
    }

    /**
     * @description The method will return the container with a background Image.
     */
    getBackgroundImageContainer = () => {
        if (Utils.isString(this.payload.backgroundImage)) {
            this.payload.backgroundImage = {
                url: this.payload.backgroundImage
            }
        }
        return (
            <View style={styles.backgroundImage}>
                <BackgroundImage backgroundImage={this.payload.backgroundImage} />
                {this.props.children}
            </View >
        );
    }

    /**
     * @description Determine the styles applicable based on the given payload
     * @returns {object} - Styles computed based on the payload
     */
    getComputedStyles = () => {
        let computedStyles = [];
        let hostConfig = HostConfigManager.getHostConfig();

        // vertical content alignment
        let verticalContentAlignment = Utils.parseHostConfigEnum(
            Enums.VerticalAlignment,
            this.payload["verticalContentAlignment"],
            Enums.VerticalAlignment.Top
        );
        switch (verticalContentAlignment) {
            case Enums.VerticalAlignment.Center:
                computedStyles.push({ justifyContent: Constants.CenterString });
                break;
            case Enums.VerticalAlignment.Bottom:
                computedStyles.push({ justifyContent: Constants.FlexEnd });
                break;
            default:
                computedStyles.push({ justifyContent: Constants.FlexStart });
                break;
        }

        // container BG style
        let backgroundStyle;
        let styleDefinition = hostConfig.containerStyles.getStyleByName(this.payload["style"], hostConfig.containerStyles.getStyleByName("default"));
        if (!Utils.isNullOrEmpty(styleDefinition.backgroundColor)) {
            backgroundStyle = { backgroundColor: Utils.hexToRGB(styleDefinition.backgroundColor) };
        }
        computedStyles.push(backgroundStyle);

        // border
        const borderThickness = styleDefinition.borderThickness || 0;
        const borderColor = styleDefinition.borderColor;
        computedStyles.push({borderWidth: borderThickness, borderColor: Utils.hexToRGB(borderColor)});

        // padding & bleed
        if (this.canApplyPadding()) {
            const padding = hostConfig.getEffectiveSpacing(Enums.Spacing.Padding);
            computedStyles.push({ padding: padding });

            // bleed
            if (this.payload.bleed && this.props.containerStyle) {
                computedStyles.push({ marginHorizontal: -padding });
            }
        }
        computedStyles.push({backgroundColor: Constants.TransparentString});

        return computedStyles;
    }

    /**
     * @description Determing whether padding can be applied to container 
     * @returns {boolean}
     */
    canApplyPadding = () => {
        //Removing the default padding applied to Adaptive card root element
        /* if (this.payload.type === 'AdaptiveCard') {
            return true;
        } */
        const parentContainerStyle = this.props.containerStyle;
        return this.payload.style && parentContainerStyle != this.payload.style;
    }
}

const styles = StyleSheet.create({
    backgroundImage: {
        width: Constants.FullWidth,
        flex: 1
    }
});