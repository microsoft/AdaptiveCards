/**
 * Image Element.
 * 
 * Refer https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/card-schema#schema-image
 */

import React from 'react';
import {
	StyleSheet,
	Image,
} from 'react-native';

import { HostConfigManager } from '../../utils/host-config';
import * as Utils from '../../utils/util';
import * as Enums from '../../utils/enums';
import * as Constants from '../../utils/constants';
import ElementWrapper from '../elements/element-wrapper';
import { SelectAction } from '../actions';
import { StyleManager } from '../../styles/style-config';

const ContainResizeMode = 'contain';

export class Img extends React.Component {

	hostConfig = HostConfigManager.getHostConfig();
	styleConfig = StyleManager.getManager().styles;

	constructor(props) {
		super(props);

		this.payload = props.json;
		this.state = {
			imageWidth: 0,
			imageHeight: 0,
		}
	}

    /**
     * @description Parse hostconfig specific to this element
     */
	parseHostConfig() {

		this.altText = this.payload.altText || Constants.EmptyString;
		this.horizontalAlignment = this.getImageAlignment();
		this.selectAction = this.payload.selectAction || null;

		if (Utils.isNullOrEmpty(this.payload.size)) {
			this.payload.size = Constants.Auto;
		}
		this.sizeStyling = this.applySize();

		this.type = this.payload.type || Constants.EmptyString;
		this.url = this.payload.url || Constants.EmptyString;
		this.id = this.payload.id || Constants.EmptyString;
		let spacingValue = Utils.parseHostConfigEnum(
			Enums.Spacing,
			this.payload.spacing,
			Enums.Spacing.Small);
		this.spacing = this.hostConfig.getEffectiveSpacing(spacingValue);
		this.separator = this.payload.separator || false;
		this.backgroundColor = this.payload.backgroundColor || Constants.TransparentString;
	}

    /**
     * @description This function determines the style of the image. Default value is "Default"
     */
	isPersonStyle() {
		let styleValue = Utils.parseHostConfigEnum(
			Enums.ImageStyle,
			this.payload.style,
			Enums.ImageStyle.Default);
		return parseInt(styleValue, 10) === 0 ? false : true;

	}
    /**
     * @description The function is used for determining the horizontal image Alignment
     */
	getImageAlignment() {
		let imageAlignmentStyle = [];

		switch (this.payload.horizontalAlignment) {
			case Constants.CenterString:
				imageAlignmentStyle.push(styles.centerAlignment);
				break;
			case Constants.RightString:
				imageAlignmentStyle.push(styles.rightAlignment);
				break;
			default:
				imageAlignmentStyle.push(styles.leftAlignment);
				break;
		}
		return imageAlignmentStyle;
	}

    /**
	 * @description
     * This function is to the create styling for the size of the image based  on the size property 
     * from the payload. If the payload consists of explicit width and height property, 
     * give highest priority.  
     * 
     */
	applySize() {
		let sizeStyle = [];
		let sizeValue = Utils.parseHostConfigEnum(Enums.Size, this.payload.size, Enums.Size.Auto)

        /**
         * Scenario 1 : Either height or width has string value (Ex: '80px'),
         *               use the integer portion.
         * Scenario 2 : If the height or width has string value (Ex: 'stretch'),
         *              ignore and use the size property to determine dimensions.
         * Scenario 3 : If either width or height is missing, apply the given value to the 
         *              other property.
         */
		if (Utils.isaNumber(this.payload.width) || Utils.isaNumber(this.payload.height)) {

			if (this.payload.width) {
				this.width = parseInt(this.payload.width, 10);
				sizeStyle.push({ width: this.width })
			}
			else {
				this.height = parseInt(this.payload.height, 10);
				sizeStyle.push({ width: this.height })
				this.width = this.height;

			}
			if (this.payload.height) {
				this.height = parseInt(this.payload.height, 10);
				sizeStyle.push({ height: this.height })
			}
			else {
				this.width = parseInt(this.payload.width, 10);
				sizeStyle.push({ height: this.width })
				this.height = this.width;
			}
		}
		else {
			switch (sizeValue) {
				case 1:
					{
						sizeStyle.push([styles.imageStretch,
						{
							width: this.state.imageWidth,
							height: this.state.imageHeight
						}]);
						break;
					}
				case 2:
					{
						sizeStyle.push({ width: this.hostConfig.imageSizes.small });
                        /**
                         * "width:80px height:not set", "size": "small"
                         */
						this.isPersonStyle() ?
							sizeStyle.push({ height: this.hostConfig.imageSizes.small }) :
							sizeStyle.push({ height: this.state.imageHeight })

                        /**
                         * When images are rendered from imageset,
                         * give priority to aspect ratio for image height.
                         */
						this.payload.fromImageSet == true ?
							sizeStyle.push({ height: this.state.imageHeight }) :
							sizeStyle.push({ height: this.hostConfig.imageSizes.small })
						break;
					}
				case 3:
					{
						sizeStyle.push({ width: this.hostConfig.imageSizes.medium });

						this.isPersonStyle() ?
							sizeStyle.push({ height: this.hostConfig.imageSizes.medium }) :
							sizeStyle.push({ height: this.state.imageHeight })

						this.payload.fromImageSet == true ?
							sizeStyle.push({ height: this.state.imageHeight }) :
							sizeStyle.push({ height: this.hostConfig.imageSizes.medium })

						this.width = this.hostConfig.imageSizes.medium;
						break;
					}
				case 4:
					{
						sizeStyle.push({ width: this.hostConfig.imageSizes.large });
						this.isPersonStyle() ?
							sizeStyle.push({ height: this.hostConfig.imageSizes.large }) :
							sizeStyle.push({ height: this.state.imageHeight })

						this.payload.fromImageSet == true ?
							sizeStyle.push({ height: this.state.imageHeight }) :
							sizeStyle.push({ height: this.hostConfig.imageSizes.large })

						this.width = this.hostConfig.imageSizes.large;
						break;
					}
				default:
					{
						sizeStyle.push([styles.imageAuto, {
							width: this.state.imageWidth,
							height: this.state.imageHeight
						}]);
						this.width = this.state.imageWidth;
						this.height = this.state.imageHeight;
						break;
					}
			}
		}

		return sizeStyle;
	}


	onPageLayoutHandler = (event) => {

		const { width: layoutWidth, height: layoutHeight } = event.nativeEvent.layout;

		//This function is implemented to determine the actual dimensions of the component.
		Image.getSize(this.url, (width, height) => {

            /**
             * Calculating the width to height ratio based on layoutWidth and actual image width.
             */
			const w2hratio = layoutWidth / width
            /**
                * The image-width and height are set in state to 
                * re-render the element once we get the determine of the image.
                */

            /**
             * If the payload contains "fromImageset" i.e(if the image is rendered via ImageSet),
             * the height and width of the image is set to maxImageHeight for sizes "auto" and "stretch"
             */

			if (this.payload.fromImageSet == true &&
				(this.payload.size === Constants.Auto ||
					this.payload.size === Constants.AlignStretch)) {
				this.setState({
					imageWidth: this.hostConfig.imageSet.maxImageHeight,
					imageHeight: this.hostConfig.imageSet.maxImageHeight,
				});
				this.width = this.payload.width || this.hostConfig.imageSet.maxImageHeight;
				this.height = this.payload.height || this.hostConfig.imageSet.maxImageHeight;
			}
			else {
				this.setState({
					imageWidth: layoutWidth,
					imageHeight: w2hratio * height,
				});
				this.width = this.payload.width || layoutWidth;
				this.height = this.payload.height || w2hratio * height;
			}

		}, (error) => {
			console.log(`Couldn't get the image size: ${error.message}`);
		});
	}

	render() {
		this.parseHostConfig();

		const {
			type,
			url,
			spacing,
		} = this;

		if (!type) {
			return null;
		}

		let imageComputedStyle = [this.sizeStyling];

		let wrapperComputedStyle = this.horizontalAlignment;
		wrapperComputedStyle.push({ backgroundColor: this.backgroundColor })
		if (this.payload.fromImageSet == true) {
			wrapperComputedStyle.push({ margin: spacing });
		}

        /**
         * If the payload size is "auto" or "stretch" and 
         * if the payload does not contain explicit width and height, computing the border radius 
         * from the state variable "imageWidth" which is determined using Image.getSize()
         */
		if ((this.payload.size === Constants.Auto ||
			this.payload.size === Constants.AlignStretch) &&
			!(this.payload.width || this.payload.height)) {
			this.isPersonStyle() ?
				imageComputedStyle.push({ borderRadius: this.state.imageWidth / 2 }) : null;
		}
		else {
			this.isPersonStyle() ?
				imageComputedStyle.push({ borderRadius: this.width / 2 }) : null;
		}

		var containerContent = (<ElementWrapper json={this.payload}
			style={wrapperComputedStyle}
			onPageLayout={this.onPageLayoutHandler}>

			<Image style={imageComputedStyle}
				source={{ uri: url }} />
		</ElementWrapper>);

		if ((this.payload.selectAction === undefined)
			|| (HostConfigManager.getHostConfig().supportsInteractivity === false)) {
			return containerContent;
		} else {
			return <SelectAction selectActionData={this.payload.selectAction}>
				{containerContent}
			</SelectAction>;
		}
	}
}

const styles = StyleSheet.create({
	leftAlignment: {
		alignItems: Constants.FlexStart,
	},
	centerAlignment: {
		alignItems: Constants.CenterString,
	},
	rightAlignment: {
		alignItems: Constants.FlexEnd,
	},
	image: {
		marginTop: 15,
	},
	imageStretch: {
		alignSelf: Constants.AlignStretch,
		resizeMode: Constants.AlignStretch,
	},
	imageAuto: {
		alignSelf: Constants.CenterString,
		resizeMode: ContainResizeMode,
	},
});
