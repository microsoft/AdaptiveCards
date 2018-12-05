import { DateInput, TimeInput, ToggleInput, NumberInput, ChoiceSetInput, InputText, } from '../inputs';
import { TextBlock, Media, Img } from '../elements';
import { Container, ColumnSet, Column, FactSet, ImageSet } from '../containers';
import  { ActionButton } from '../actions';
import React from 'react';

export class Registry {

    static registryInstance = null;

    static getManager() {
        if (!Registry.registryInstance) {
            Registry.registryInstance = new Registry();
        }
        return Registry.registryInstance;
    }

    registerComponent = ( key, component ) => {
        this.ElementRegistry[key] = component;
    }

    removeComponent = ( key ) => {
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

        'Action.ShowCard': ActionButton,
        'Action.Submit': ActionButton,
        'Action.OpenUrl': ActionButton
    };

    /**
     * @description Get then component associated for the given element type
     * @param {string} type - Type of the element
     */
    getComponentOfType = (type) => {
        return this.ElementRegistry[type];
    }

    /**
     * @description Parse an Array of components
     * @param {Array} componentArray - Json
     */
    parseRegistryComponents = ( componentArray ) => {
        const parsedElement = [];
        if (!componentArray)
             return parsedElement;
        componentArray.map((element, index) => {
            const Element = this.getComponentOfType(element.type);
            if (Element) {
                parsedElement.push(<Element json={element} key={`${element.type}-${index}-${this.generateNumber()}`} />);
            } else {
             return null;
            }
          });
          return parsedElement;
    }

    /**
     * @description Generates a random number
     */
    generateNumber = () => {
        min = 1;
        max = 100000;
        const rndNum = Math.floor(Math.random() * (max - min + 1) + min)
        return rndNum
    };
}




