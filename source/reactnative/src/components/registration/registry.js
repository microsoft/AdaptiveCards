import { DateInput, TimeInput, ToggleInput, NumberInput, ChoiceSetInput, InputText, } from '../inputs';
import { TextBlock, Media, Img } from '../elements';
import { Container, ColumnSet, Column, FactSet, ImageSet } from '../containers';
import  { ActionButton } from '../actions';

export class Registry {
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
        'Image': Img
    };

    ActionRegistry = {
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
     * @description Get the component associated for the given action type
     * @param {string} type - Type of the action
     */
    getActionOfType = (type) => {
        return this.ActionRegistry[type];
    }
}




