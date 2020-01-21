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
        computedStyles.push({ backgroundColor: Constants.TransparentString });

        // container BG style
        let backgroundStyle;
        const styleDefinition = hostConfig.containerStyles.getStyleByName(this.payload["style"], hostConfig.containerStyles.getStyleByName("default"));
        //we won't apply the background color for the container which has backgroundImage. Even we won't apply color if its parent container having backgroundImage
        const hasBackgroundImage = !Utils.isNullOrEmpty(this.payload.backgroundImage) || (this.payload.parent && !Utils.isNullOrEmpty(this.payload.parent.backgroundImage)) || (!Utils.isNullOrEmpty(this.props.hasBackgroundImage))
        if (!hasBackgroundImage && !Utils.isNullOrEmpty(styleDefinition.backgroundColor)) {
            backgroundStyle = { backgroundColor: Utils.hexToRGB(styleDefinition.backgroundColor) };
        }
        computedStyles.push(backgroundStyle);

        // border
        const borderThickness = styleDefinition.borderThickness || 0;
        const borderColor = styleDefinition.borderColor;
        computedStyles.push({ borderWidth: borderThickness, borderColor: Utils.hexToRGB(borderColor) });

        // padding
        const padding = hostConfig.getEffectiveSpacing(Enums.Spacing.Padding);
        computedStyles.push({ padding: padding });

        // bleed
        if (this.payload.bleed && this.props.containerStyle) {
            const { isFirst, isLast } = this.props;
            const marginLeft = isFirst ? -padding : 0;
            const marginRight = isLast ? -padding : 0;

            computedStyles.push({ marginVertical: -padding, marginLeft, marginRight });
        }

        // height 
        const payloadHeight = this.payload.height || false;
        if (payloadHeight) {
            const heightEnumValue = Utils.parseHostConfigEnum(
                Enums.Height,
                this.payload.height,
                Enums.Height.Auto);
            const height = hostConfig.getEffectiveHeight(heightEnumValue);
            computedStyles.push({ flex: height });
            !this.payload["verticalContentAlignment"] && height && computedStyles.push({ justifyContent: Constants.SpaceBetween })
        }

        return computedStyles;
    }
}

const styles = StyleSheet.create({
    backgroundImage: {
        width: Constants.FullWidth,
    }
});