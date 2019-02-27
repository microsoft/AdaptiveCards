/**
 * Render the adaptive card for the given payload.
 */

import React from 'react';
import {
	StyleSheet,
	Text,
	ScrollView,
	ImageBackground
} from 'react-native';

import { Registry } from './components/registration/registry';
import { InputContextProvider } from './utils/context';
import { HostConfigManager } from './utils/host-config';
import { StyleManager } from './styles/style-config';
import { ActionWrapper } from './components/actions/action-wrapper';
import PropTypes from 'prop-types';
import * as Utils from './utils/util';
import { SelectAction } from './components/actions';
import ResourceInformation from './utils/resource-information';
import { ContainerWrapper } from './components/containers/';
import { ThemeConfigManager } from './utils/theme-config';

export default class AdaptiveCards extends React.Component {

	// Input elements with its identifier and value
	inputArray = {};
	version = "1.1"; // client supported version
	resourceInformationArray = [];
	
	constructor(props) {
		super(props);

		this.payload = props.payload;

		// hostconfig
		if (props.hostConfig) {
			HostConfigManager.setHostConfig(props.hostConfig);
		}
		
		// themeConfig
		if(props.themeConfig){
			ThemeConfigManager.setThemeConfig(props.themeConfig);
		}

		// commonly used styles
		this.styleConfig = StyleManager.getManager().styles;
	}

	/**
	 * @description Returns the resource information in the card elements as an array
	 * @returns {Array} - Array of items of type ResourceInformation
	 */
	getResourceInformation = () => {
		return this.resourceInformationArray;
	}

	/**
	 * @description Input elements present in the cards are added here with its value.
	 */
	addInputItem = (key, value) => {
		this.inputArray[key] = value;
	}

	/**
	 * @description Resource information present in the card elements are added here with the url and mimetype.
	 * @param {string} urlString - URL of the resource (Ex: URL of the Image element)
	 * @param {string} mimeTypeString - MIME type of the resource if the same is available in the element's payload
	 */
	addResourceInformation = (urlString, mimeTypeString) => {
		let newResourceObject = new ResourceInformation(urlString, mimeTypeString);
		this.resourceInformationArray.push(newResourceObject);
	}

	/**
	 * @description Parse the given payload and render the card accordingly
	 */
	parsePayload = () => {

		const renderedElement = [];
		const { body } = this.payload;

		if (!body)
			return renderedElement;

		renderedElement.push(Registry.getManager().parseRegistryComponents(body, this.onParseError));

		return renderedElement;
	}

	getAdaptiveCardConent() {
		var adaptiveCardContent =
			(
				<ContainerWrapper style={styles.container} json={this.payload}>
					<ScrollView alwaysBounceVertical={false} style={{flexGrow: 0}}>
						{this.parsePayload()}
						{!Utils.isNullOrEmpty(this.payload.actions) &&
							<ActionWrapper actions={this.payload.actions} />}
					</ScrollView>
				</ContainerWrapper>
			);

		// checks if BackgroundImage option is available for adaptive card
		if (!Utils.isNullOrEmpty(this.payload.backgroundImage)) {
			let backgroundImage = Utils.getImageUrl(this.payload.backgroundImage)
			adaptiveCardContent = (
				<ImageBackground source={{ uri: backgroundImage }} style={styles.backgroundImage}>
					{adaptiveCardContent}
				</ImageBackground>
			);
		}

		// checks if selectAction option is available for adaptive card
		if (!Utils.isNullOrEmpty(this.payload.selectAction)) {
			adaptiveCardContent = (
				<SelectAction style={styles.container} selectActionData={this.payload.selectAction}>
					{adaptiveCardContent}
				</SelectAction>
			);
		}
		return adaptiveCardContent;
	}

	render() {
		const { addInputItem, inputArray, addResourceInformation } = this;
		const onExecuteAction = this.onExecuteAction;
		const isTransparent = this.payload.backgroundImage ? true : false;
		const onParseError = this.onParseError;
		const lang = this.payload.lang || 'en';

		// version check
		if (!this.isSupportedVersion()) {
			const message = this.payload.fallbackText || "We're sorry, this card couldn't be displayed";
			return (
				<Text style={this.styleConfig.fontConfig}>{message}</Text>
			)
		}
		return (
			<InputContextProvider value={{ lang, addInputItem, inputArray, onExecuteAction, isTransparent, onParseError, addResourceInformation }}>
				{
					this.getAdaptiveCardConent()
				}
			</InputContextProvider>
		);
	}

	/**
	 * Check whether the payload schema version is supported by client.
	 * @return {boolean} - version supported or not
	 */
	isSupportedVersion = () => {

		//Ignore the schema version number when AdaptiveCard is used from Action.ShowCard as it is not mandatory
		if (this.props.isActionShowCard) {
			return true;
		}
		if (!this.payload.version)
			return false;

		const payloadVersion = Utils.parseVersion(this.payload.version);
		const clientVersion = Utils.parseVersion(this.version);

		if (clientVersion.major != payloadVersion.major) {
			return payloadVersion.major < clientVersion.major;
		}
		else if (clientVersion.minor != payloadVersion.minor) {
			return payloadVersion.minor < clientVersion.minor;
		}
		else {
			return true;
		}
	}

	// Invoke onParseError if the consumer app provide it via props.
	onParseError = (error) => {
		if (this.props.onParseError) {
			this.props.onParseError(error);
		}
	}

	// Invoke onExecuteAction if the consumer app provide it via props.
	onExecuteAction = (action) => {
		if (this.props.onExecuteAction) {
			this.props.onExecuteAction(action);
		}
	}
}

// AdaptiveCards.propTypes
AdaptiveCards.propTypes = {
	payload: PropTypes.object.isRequired,
	hostConfig: PropTypes.object,
	themeConfig: PropTypes.object,
	onExecuteAction: PropTypes.func,
	onParseError: PropTypes.func
};

const styles = StyleSheet.create({
	container: {
		flex: 1,
		backgroundColor: 'transparent',
	},
	actionContainer: {
		marginVertical: 10
	},
	backgroundImage: {
		width: "100%",
		flex: 1
	}
});

