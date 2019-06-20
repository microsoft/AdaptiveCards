import React from 'react';

import {
	DateInput,
	TimeInput,
	ToggleInput,
	NumberInput,
	ChoiceSetInput,
	InputText,
} from '../inputs';
import {
	TextBlock,
	Media,
	Img,
	RichTextBlock
} from '../elements';
import {
	Container,
	ColumnSet,
	Column,
	FactSet,
	ImageSet
} from '../containers';
import {
	ActionButton,
	ActionSet
} from '../actions';
import * as Enums from '../../utils/enums';
import * as Utils from '../../utils/util';

export class Registry {

	static registryInstance = null;

	static getManager() {
		if (!Registry.registryInstance) {
			Registry.registryInstance = new Registry();
		}
		return Registry.registryInstance;
	}

	/**
	 * @description Register a new Component or Override an Existing Component
	 * @param {string} key - Type of the Component to be overridden
	 * @param {Component} component - React Native component to be rendered
	 */
	registerComponent = (key, component) => {
		this.ElementRegistry[key] = component;
	}

	/**
	 * @description Remove an Existing Component
	 * @param {string} key - Type of the Component to be removed
	 */
	removeComponent = (key) => {
		delete this.ElementRegistry[key];
	}

	ElementRegistry = {
		'Container': Container,
		'ColumnSet': ColumnSet,
		'ImageSet': ImageSet,
		'Column': Column,
		'FactSet': FactSet,

		'Input.Text': InputText,
		'Input.Number': NumberInput,
		'Input.Toggle': ToggleInput,
		'Input.Date': DateInput,
		'Input.Time': TimeInput,
		'Input.ChoiceSet': ChoiceSetInput,

		'TextBlock': TextBlock,
		'Media': Media,
		'Image': Img,
		'RichTextBlock': RichTextBlock,

		'Action.ShowCard': ActionButton,
		'Action.Submit': ActionButton,
		'Action.OpenUrl': ActionButton,
		'Action.ToggleVisibility': ActionButton,
		'ActionSet': ActionSet
	};

	/**
	 * @description Get then component associated for the given element type
	 * @param {string} type - Type of the element
	 */
	getComponentOfType = (type) => {
		return this.ElementRegistry[type];
	}

	/**
	 * @description Register a required property for custom/overriding components
	 * @param {string} key - Type of the Component
	 * @param {requiredProps} component - Required properties of the custom component
	 */
	registerRequiredPropertySchema = (key, requiredProps) => {
		if (this.ElementRegistry.hasOwnProperty(key) && !Utils.isNullOrEmpty(requiredProps)) {
			this.RequiredPropertySchema[key] = requiredProps;

		}
	}
	RequiredPropertySchema = {
		'Container': { 'type': 'Container', 'children': 'Array' },
		'ColumnSet': { 'type': 'ColumnSet' },
		'Column': { 'items': 'Array' },
		'FactSet': { 'type': 'FactSet', 'children': 'Array' },
		'ImageSet': { 'type': 'ImageSet', 'children': 'Array' },

		'TextBlock': { 'type': 'TextBlock' },
		'Image': { 'type': 'Image', 'url': 'String' },
		'Media': { 'type': 'Media' },

		'Input.Text': { 'type': 'Input.Text', 'id': 'String' },
		'Input.Number': { 'type': 'Input.Number', 'id': 'String' },
		'Input.Toggle': { 'type': 'Input.Toggle', 'id': 'String' },
		'Input.Date': { 'type': 'Input.Date', 'id': 'String' },
		'Input.Time': { 'type': 'Input.Time', 'id': 'String' },
		'Input.ChoiceSet': { 'type': 'Input.ChoiceSet', 'id': 'String' },


		'Action.ShowCard': { 'type': 'Action.ShowCard', 'card': 'Object' },
		'Action.Submit': { 'type': 'Action.Submit' },
		'Action.OpenUrl': { 'type': 'Action.OpenUrl', 'url': 'String' },
		'ActionSet': { 'type': 'ActionSet' },
	};

	/**
	 * @description validate the schema for the given element type
	 * @param {string} type - Type of the element
	 */
	validateSchemaForType = (type) => {
		return this.RequiredPropertySchema[type];
	}

	/**
	 * @description Parse an Array of components
	 * @param {Array} componentArray - Json
	 */
	parseRegistryComponents = (componentArray, onParseError) => {
		const parsedElement = [];
		if (!componentArray)
			return parsedElement;
		componentArray.map((element, index) => {
			const currentElement = this.parseComponent(element,onParseError,index);
			if (currentElement){
				parsedElement.push(currentElement);
			}
		});
		return parsedElement;
	}

	/**
	 * @description Parse an individual component
	 * @param {Array} element - Json
	 */
	parseComponent = (element, onParseError, index = 0) => {
		const Element = this.getComponentOfType(element.type);

			if (Element) {
                /**
                 * Validate the schema and invoke onParseError handler incase of any error.
                 */
				let isValid = true;
				if (element.isFallbackActivated){
					if(element.fallbackType == "drop"){
						return null;
					}else if(!Utils.isNullOrEmpty(element.fallback)){
						return this.parseComponent(element.fallback,onParseError);
					}
				}
				for (var key in this.validateSchemaForType(element.type)) {
					if (!element.hasOwnProperty(key)) {
						let error = { "error": Enums.ValidationError.PropertyCantBeNull, "message": `Required property ${key} for ${element.type} is missing` };
						onParseError(error);
						isValid = false;
					}
				}
				if (isValid) {
					if (element.isVisible !== false) {
						const elementKey = Utils.isNullOrEmpty(element.id) ? `${element.type}-${index}` : `${element.type}-${index}-${element.id}`;
						return (<Element json={element} key={elementKey} />);
					}
				}
			} else {
				let error = { "error": Enums.ValidationError.UnknownElementType, "message": `Unknown Type ${element.type} encountered` };
				onParseError(error);
				return null;
			}
	}
}




