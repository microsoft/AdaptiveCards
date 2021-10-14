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
import { View } from 'react-native';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';
import * as Constants from "../../utils/constants";
import { BackgroundImage } from '../elements';

export class ContainerWrapper extends React.PureComponent {

    constructor(props) {
        super(props);
        this.payload = props.json;
    }

    render() {
        const receivedStyles = this.props.style;
        const computedStyles = this.getComputedStyles();

        return (
            Utils.isNullOrEmpty(this.payload.altText) ?
                <View style={[computedStyles, receivedStyles]}>
                    {!Utils.isNullOrEmpty(this.payload.backgroundImage) ? this.getBackgroundImageContainer() : this.props.children}
                </View> :
                <View
                    accessible={true}
                    accessibilityLabel={this.payload.altText}
                    style={[computedStyles, receivedStyles]}>
                    {!Utils.isNullOrEmpty(this.payload.backgroundImage) ? this.getBackgroundImageContainer() : this.props.children}
                </View>
        );
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
            <React.Fragment>
                <BackgroundImage backgroundImage={this.payload.backgroundImage} />
                {this.props.children}
            </React.Fragment >
        );
    }

    /**
     * @description Determine the styles applicable based on the given payload
     * @returns {object} - Styles computed based on the payload
     */
    getComputedStyles = () => {
        let computedStyles = [];
        const { hostConfig } = this.props.configManager;

        //Constructing the vertical Content Alignment for columnSet
        if (this.payload.parent && this.payload.parent["verticalContentAlignment"]) {
            if(this.payload.type === Constants.TypeColumnSet) {
                this.payload.verticalContentAlignment = this.payload.parent["verticalContentAlignment"];
            }
        }

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
        // If needed, we will use this hasBackgroundImage in the future. so commenting out the below line
        // const hasBackgroundImage = !Utils.isNullOrEmpty(this.payload.backgroundImage) || (this.payload.parent && !Utils.isNullOrEmpty(this.payload.parent.backgroundImage)) || (!Utils.isNullOrEmpty(this.props.hasBackgroundImage))
        if (!Utils.isNullOrEmpty(styleDefinition.backgroundColor)) {
            backgroundStyle = { backgroundColor: this.payload["style"] !== undefined ? Utils.hexToRGB(styleDefinition.backgroundColor) : "transparent" };
        }
        computedStyles.push(backgroundStyle);

        // border
        const borderThickness = styleDefinition.borderThickness || 0;
        const borderColor = styleDefinition.borderColor;
        computedStyles.push({ borderWidth: borderThickness, borderColor: Utils.hexToRGB(borderColor) });

        
        // padding
        // const padding = hostConfig.getEffectiveSpacing(Enums.Spacing.Padding);
        if (this.payload.style) {
            computedStyles.push({ padding: Constants.containerPadding});
        }

        // bleed
        if (this.payload.bleed && this.payload.style) {
            computedStyles.push({ padding: -Constants.containerPadding});
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