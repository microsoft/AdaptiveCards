/**
 * Render the adaptive card for the given payload.
 */

import React from 'react';
import {
	StyleSheet,
	Text,
	ScrollView
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
import { ContainerWrapper } from './components/containers';
import { ThemeConfigManager } from './utils/theme-config';

export default class AdaptiveCard extends React.Component {

	// Input elements with its identifier and value
	inputArray = {};
	version = "1.2"; // client supported version
	resourceInformationArray = [];
	constructor(props) {
		super(props);

		this.payload = props.payload;

		this.state = {
			showErrors: false,
			payload: this.payload,
		}

		// hostConfig
		if (props.hostConfig) {
			HostConfigManager.setHostConfig(props.hostConfig);
		}

		// themeConfig
		if (props.themeConfig) {
			ThemeConfigManager.setThemeConfig(props.themeConfig);
		}

		// commonly used styles
		this.styleConfig = StyleManager.getManager().styles;

	}

	toggleVisibilityForElementWithID = (idArray) => {
		this.toggleObjectWithIDArray(this.payload, [...idArray]);
		this.setState({
			payload: this.payload,
		})
	}

	/**
	 * @description Toggles the visibility of the components by their ids recursively
	 * @param {Object} object - the object to be searched for ids
	 * @param {Array} idArrayValue - the array of IDs to be toggled
	 */
	toggleObjectWithIDArray = (object, idArrayValue) => {
		if (idArrayValue.length === 0) return
		if (object.hasOwnProperty('id')) {
			this.checkTargetElementsForID(object, idArrayValue);
			if (idArrayValue.length === 0) return
		}
		Object.keys(object).forEach(element => {
			if (idArrayValue.length === 0) return
			if (typeof object[element] == "object") {
				this.toggleObjectWithIDArray(object[element], idArrayValue);
			}
		});
		return;
	}

	/**
	 * @description Checks the elements recursively to change the isVisible property
	 * @param {Object} object - the object to be searched
	 * @param {Array} targetElements - the array of target Ids to be toggled
	 */
	checkTargetElementsForID = (object, targetElements) => {
		targetElements.forEach(target => {
			if (target instanceof String || typeof target === 'string'){
				if(target == object["id"]){
					this.toggleObjectVisibility(object);
					var index = targetElements.indexOf(object["id"]);
					if (index !== -1) targetElements.splice(index, 1);
					return
				}
			}else if((target instanceof Object || typeof target === 'object') && target !== null){
				if(target["elementId"] === object["id"]){
					if (!Utils.isNullOrEmpty(target["isVisible"])) {
						object.isVisible = target["isVisible"]
					} else {
						this.toggleObjectVisibility(object);
					}
					var index = targetElements.indexOf(target);
					if (index !== -1) targetElements.splice(index, 1);
					return
				}
			}
		});
	}

	/**
	 * @description Toggles the isVisible property of an Object
	 * @param {Object} object - the object to be toggles
	 */
	toggleObjectVisibility = (object) => {
		if (!Utils.isNullOrEmpty(object.isVisible)) {
			object.isVisible = !object.isVisible
		} else {
			object.isVisible = false;
		}
	}

	/**
	 * @description Conveniece method to toggle the visibility of the component by a single id recursively
	 * @param {Object} object - the object to be searched for ids
	 * @param {string} idValue - the id of the component to be toggled
	 */
	toggleObjectWithID = (object, idValue) => {
		if (object.hasOwnProperty('id') && object["id"] == idValue) {
			if (!Utils.isNullOrEmpty(object.isVisible)) {
				object.isVisible = !object.isVisible
			} else {
				object.isVisible = false;
			}
			return;
		}
		Object.keys(object).forEach(element => {
			if (typeof object[element] == "object") {
				this.toggleObjectWithID(object[element], idValue);
			}
		});
		return;
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
	 * @returns {object} Child elements of the card
	 */
	parsePayload = () => {
		let children = [];
		const { body } = this.state.payload;

		if (!body)
			return children;

		children = Registry.getManager().parseRegistryComponents(body, this.onParseError);
		return children.map((ChildElement, index) => React.cloneElement(ChildElement, { containerStyle: this.state.payload.style, isFirst: index === 0 }));
	}

	getAdaptiveCardContent() {
		var adaptiveCardContent =
			(
				<ContainerWrapper style={styles.container} json={this.state.payload}>
					<ScrollView alwaysBounceVertical={false} style={{ flexGrow: 0 }}>
						{this.parsePayload()}
						{!Utils.isNullOrEmpty(this.state.payload.actions) &&
							<ActionWrapper actions={this.state.payload.actions} />}
					</ScrollView>
				</ContainerWrapper>
			);

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
		const { addInputItem, inputArray, addResourceInformation, toggleVisibilityForElementWithID } = this;
		const onExecuteAction = this.onExecuteAction;
		const isTransparent = this.payload.backgroundImage ? true : false;
		const onParseError = this.onParseError;
		const lang = this.payload.lang || 'en';
		const { showErrors } = this.state;

		// version check
		if (!this.isSupportedVersion()) {
			const message = this.payload.fallbackText || "We're sorry, this card couldn't be displayed";
			return (
				<Text style={this.styleConfig.defaultFontConfig}>{message}</Text>
			)
		}
		return (
			<InputContextProvider value={{ lang, addInputItem, inputArray, onExecuteAction, isTransparent, onParseError, addResourceInformation, showErrors, toggleVisibilityForElementWithID }}>
				{
					this.getAdaptiveCardContent()
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
	onExecuteAction = (action, ignoreInputValidation) => {
		if (!ignoreInputValidation && !this.validateInputs())
			this.setState({ showErrors: true });
		else if (this.props.onExecuteAction) {
			this.props.onExecuteAction(action);
		}
	}

	validateInputs = () => {
		const { inputArray } = this;
		if (inputArray) {
			for (const key in inputArray) {
				if (inputArray[key].errorState)
					return false;
			}
		}
		return true;
	}
}

// AdaptiveCard.propTypes
AdaptiveCard.propTypes = {
	payload: PropTypes.object.isRequired,
	hostConfig: PropTypes.object,
	themeConfig: PropTypes.object,
	onExecuteAction: PropTypes.func,
	onParseError: PropTypes.func
};

const styles = StyleSheet.create({
	container: {
		flex: 1,
	},
	actionContainer: {
		marginVertical: 10
	},
	backgroundImage: {
		width: "100%",
		flex: 1
	}
});

