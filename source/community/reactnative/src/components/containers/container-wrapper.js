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
import {View} from 'react-native';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';
import * as Constants from '../../utils/constants';
import {BackgroundImage} from '../elements';

export class ContainerWrapper extends React.PureComponent {
    constructor(props) {
        super(props);
        this.payload = props.json;
    }

    render() {
        this.payload = this.props.json;
        const receivedStyles = this.props.style;
        const computedStyles = this.getComputedStyles();

        return Utils.isNullOrEmpty(this.payload.altText) ? (
            <React.Fragment>
                {!this.props.isFirst &&
                    this.payload.type !== Constants.TypeColumn &&
                    this.getSpacingElement()}
                <View style={[computedStyles, receivedStyles]}>
                    {!Utils.isNullOrEmpty(this.payload.backgroundImage)
                        ? this.getBackgroundImageContainer()
                        : this.props.children}
                </View>
            </React.Fragment>
        ) : (
            <React.Fragment>
                {!this.props.isFirst &&
                    this.payload.type !== Constants.TypeColumn &&
                    this.getSpacingElement()}
                <View
                    accessible={true}
                    accessibilityLabel={this.payload.altText}
                    style={[computedStyles, receivedStyles]}>
                    {!Utils.isNullOrEmpty(this.payload.backgroundImage)
                        ? this.getBackgroundImageContainer()
                        : this.props.children}
                </View>
            </React.Fragment>
        );
    }

    /**
     * @description The method will return the container with a background Image.
     */
    getBackgroundImageContainer = () => {
        if (Utils.isString(this.payload.backgroundImage)) {
            this.payload.backgroundImage = {
                url: this.payload.backgroundImage,
            };
        }
        // padding
        const padding = this.props.configManager.hostConfig.getEffectiveSpacing(
            Enums.Spacing.Padding,
        );
        return (
            <React.Fragment>
                <BackgroundImage
                    backgroundImage={this.payload.backgroundImage}
                />
                <View
                    style={{
                        marginHorizontal: padding,
                        paddingVertical: padding,
                    }}>
                    {this.props.children}
                </View>
            </React.Fragment>
        );
    };

    /**
     * @description The method will return true, if any of the parent containers having the style applied other than default.
     */
    hasAncestorStyle(payload) {
        if (payload.parent) {
            if (
                payload.parent['style'] &&
                payload.parent['style'] !== Enums.ContainerStyle.Default
            ) {
                return true;
            }
            // We will check for style in ancestors
            return this.hasAncestorStyle(payload.parent);
        } else {
            return false;
        }
    }

	/**
     * @description The method will return true, if any of the ancestor containers have backgroundImage.
     */
    hasAncestorBackgroundImage(payload) {
        if (payload.parent) {
            if (!Utils.isNullOrEmpty(payload.parent.backgroundImage)) {
                return true;
            }
            return this.hasAncestorBackgroundImage(payload.parent);
        } else {
            return false;
        }
    }

    /**
     * @description The method will return true, if any of the parent containers is column.
     */
    applyBleedMarginHorizontal(computedStyles) {
        const padding = this.props.configManager.hostConfig.getEffectiveSpacing(
            Enums.Spacing.Padding,
        );
        if (this.payload.type === Constants.TypeColumn) {
            //If parent that means columnset have style other than default, then we need to apply padding as -padding otherwise padding as 0
            const marginValue =
                this.payload.parent['style'] &&
                this.payload.parent['style'] === Enums.ContainerStyle.Default
                    ? 0
                    : -padding;
            if (this.props.isFirst && this.props.isLast) {
                computedStyles.push({marginHorizontal: marginValue});
            } else if (this.props.isFirst) {
                //First column
                computedStyles.push({marginLeft: marginValue});
            } else if (this.props.isLast) {
                //Last column
                computedStyles.push({marginRight: marginValue});
            }
        } else {
            computedStyles.push({marginHorizontal: -padding});
        }   
    }

    /**
     * @description The method will apply the bleed for the container.
     */
    applyBleedStyle(computedStyles) {
        // Bleed
        // If bleed is true and style is not undefined and Default, then we will remove marginHorizontal only if any of the parent containers having the style applied other than default and direct parent is adaptive card Otherwise, we will remove padding from the marginHorizontal.
        // If bleed is true and style is not undefined and Other than Default, then we will remove marginHorizontal only if the direct parent is adaptive card Otherwise, we will remove padding from the marginHorizontal.
        if (
            this.payload.bleed &&
            this.payload.parent &&
            this.payload.parent.type === Constants.TypeAdaptiveCard
        ) {
            computedStyles.push({marginHorizontal: 0});
        } else if (this.payload.bleed && this.payload.style) {
            if (this.payload.style === Enums.ContainerStyle.Default) {
                this.hasAncestorStyle(this.payload) &&
                    this.applyBleedMarginHorizontal(computedStyles);
            } else {
                this.payload.parent &&
                this.payload.parent.type === Constants.TypeAdaptiveCard
                    ? computedStyles.push({marginHorizontal: 0})
                    : this.applyBleedMarginHorizontal(computedStyles);
            }
        }
    }

    /**
     * @description The method will apply the padding for the container.
     */
    applyContainerStyle(computedStyles) {
        // Padding
        // We will add marginHorizontal for the adaptive card root containers...Top and bottom martgin is added in the adaptive card directly.
        // If style is not undefined and Default, then we will add padding only if any of the parent containers having the style applied other than default.
        // If style is not undefined and Other than Default, then we will add padding
        const padding = this.props.configManager.hostConfig.getEffectiveSpacing(
            Enums.Spacing.Padding,
        );
        this.payload.parent &&
            this.payload.parent.type === Constants.TypeAdaptiveCard &&
            computedStyles.push({
                //If payload type is columnset and it has style other than default, then apply marginHorizontal as padding
                marginHorizontal:
                    this.payload.type === Constants.TypeColumnSet
                        ? this.payload['style'] &&
                          this.payload['style'] !== Enums.ContainerStyle.Default
                            ? padding
                            : 0
                        : padding,
            });
        if (this.payload.style) {
            if (this.payload.style === Enums.ContainerStyle.Default) {
                (this.hasAncestorStyle(this.payload) ||
                    this.hasAncestorBackgroundImage(this.payload)) &&
                    computedStyles.push({
                        padding: padding,
                    });
            } else {
                computedStyles.push({
                    padding: padding,
                });
            }
        }
    }

    /**
     * @description Determine the styles applicable based on the given payload
     * @returns {object} - Styles computed based on the payload
     */
    getComputedStyles = () => {
        let computedStyles = [];
        const {hostConfig} = this.props.configManager;

        //Constructing the vertical Content Alignment for columnSet
        if (
            this.payload.parent &&
            this.payload.parent['verticalContentAlignment']
        ) {
            if (this.payload.type === Constants.TypeColumnSet) {
                this.payload.verticalContentAlignment =
                    this.payload.parent['verticalContentAlignment'];
            }
        }

        // vertical content alignment
        let verticalContentAlignment = Utils.parseHostConfigEnum(
            Enums.VerticalAlignment,
            this.payload['verticalContentAlignment'],
            Enums.VerticalAlignment.Top,
        );
        switch (verticalContentAlignment) {
            case Enums.VerticalAlignment.Center:
                computedStyles.push({justifyContent: Constants.CenterString});
                break;
            case Enums.VerticalAlignment.Bottom:
                computedStyles.push({justifyContent: Constants.FlexEnd});
                break;
            default:
                computedStyles.push({justifyContent: Constants.FlexStart});
                break;
        }
        computedStyles.push({backgroundColor: Constants.TransparentString});

        // container BG style
        let backgroundStyle;
        const styleDefinition = hostConfig.containerStyles.getStyleByName(
            this.payload['style'],
            hostConfig.containerStyles.getStyleByName('default'),
        );
        // If needed, we will use this hasBackgroundImage in the future. so commenting out the below line
        // const hasBackgroundImage = !Utils.isNullOrEmpty(this.payload.backgroundImage) || (this.payload.parent && !Utils.isNullOrEmpty(this.payload.parent.backgroundImage)) || (!Utils.isNullOrEmpty(this.props.hasBackgroundImage))
        if (!Utils.isNullOrEmpty(styleDefinition.backgroundColor)) {
            backgroundStyle = {
                backgroundColor:
                    this.payload['style'] !== undefined
                        ? Utils.hexToRGB(styleDefinition.backgroundColor)
                        : 'transparent',
            };
        }
        computedStyles.push(backgroundStyle);

        // border
        const borderThickness = styleDefinition.borderThickness || 0;
        const borderColor = styleDefinition.borderColor;
        computedStyles.push({
            borderWidth: borderThickness,
            borderColor: Utils.hexToRGB(borderColor),
        });

        this.applyContainerStyle(computedStyles);
        this.applyBleedStyle(computedStyles);

        // height
        const payloadHeight = this.payload.height || false;
        if (payloadHeight) {
            const heightEnumValue = Utils.parseHostConfigEnum(
                Enums.Height,
                this.payload.height,
                Enums.Height.Auto,
            );
            const height = hostConfig.getEffectiveHeight(heightEnumValue);
            computedStyles.push({flex: height});
            !this.payload['verticalContentAlignment'] &&
                height &&
                computedStyles.push({justifyContent: Constants.SpaceBetween});
        }

        return computedStyles;
    };

    /**
     * @description Return the element for spacing and/or separator
     * @returns {object} View element with spacing based on `spacing` and `separator` prop
     */
    getSpacingElement = () => {
        const {hostConfig, styleConfig} = this.props.configManager;
        const spacingEnumValue = Utils.parseHostConfigEnum(
            Enums.Spacing,
            this.payload.spacing,
            Enums.Spacing.Default,
        );
        const padding = this.props.configManager.hostConfig.getEffectiveSpacing(
            Enums.Spacing.Padding,
        );
        const spacing = hostConfig.getEffectiveSpacing(spacingEnumValue);
        const {isFirst} = this.props; //isFirst represent, it is first element

        let computedStyles = [{flex: 1}];

        this.payload.parent &&
            this.payload.parent.type === Constants.TypeAdaptiveCard &&
            computedStyles.push({
                //If payload type is columnset and it has style other than default, then apply marginHorizontal as padding
                marginHorizontal:
                    this.payload.type === Constants.TypeColumnSet
                        ? this.payload['style'] &&
                          this.payload['style'] !== Enums.ContainerStyle.Default
                            ? padding
                            : 0
                        : padding,
            });

        this.applyBleedStyle(computedStyles);
        // spacing styles
        return (
            <View style={computedStyles}>
                {<View style={{height: spacing / 2}} />}
                {this.payload.separator && !isFirst && (
                    <View style={styleConfig.separatorStyle} />
                )}
                {<View style={{height: spacing / 2}} />}
            </View>
        );
    };
}
