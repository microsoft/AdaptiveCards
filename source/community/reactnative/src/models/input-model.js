import { BaseModel } from './base-model'
import { ElementType } from '../utils/enums'

export class BaseInputModel extends BaseModel {
    constructor(payload, parent) {
        super(payload, parent);
        this.placeholder = payload.placeholder;
        this.value = payload.value;
        this.inlineAction = payload.inlineAction;
        this.label = payload.label;
        this.altText = payload.altText;
        this.errorMessage = payload.errorMessage;
        this.isRequired = payload.isRequired;
    }
}

export class TextInputModel extends BaseInputModel {
    type = ElementType.TextInput;

    constructor(payload, parent) {
        super(payload, parent);
        this.isMultiline = payload.isMultiline || false;
        this.maxLength = payload.maxLength;
        this.style = payload.style;
        this.regex = payload.regex;
    }

}

export class NumberInputModel extends BaseInputModel {
    type = ElementType.NumberInput;

    constructor(payload, parent) {
        super(payload, parent);
        this.max = payload.max;
        this.min = payload.min;
    }
}

export class DateInputModel extends BaseInputModel {
    type = ElementType.DateInput;

    constructor(payload, parent) {
        super(payload, parent);
        this.max = payload.max;
        this.min = payload.min;
    }
}

export class TimeInputModel extends BaseInputModel {
    type = ElementType.TimeInput;

    constructor(payload, parent) {
        super(payload, parent);
        this.max = payload.max;
        this.min = payload.min;
    }

}

export class ToggleInputModel extends BaseInputModel {
    type = ElementType.ToggleInput;

    constructor(payload, parent) {
        super(payload, parent);
        this.title = payload.title;
        this.valueOff = payload.valueOff;
        this.valueOn = payload.valueOn;
        this.value = payload.value;
        this.wrap = payload.wrap;
    }
}

export class ChoiceSetModel extends BaseInputModel {
    type = ElementType.ChoiceSetInput;

    constructor(payload, parent) {
        super(payload, parent);
        this.isMultiSelect = payload.isMultiSelect;
        this.style = payload.style;
        this.wrap = payload.wrap;
        if (payload.choices) {
            payload.choices.forEach((item, index) => {
                let choice = new ChoiceModel(item, this);
                if (choice) {
                    this.children.push(choice);
                }
            });
        }

        if (payload.value) {
            let selected = (payload.value).split(',');
            if (selected) {
                selected.forEach(current => {
                    let choice = this.choices.find(c => c.value === current);
                    if (choice) {
                        choice.selected = true;
                    }
                });
            }
        }
    }

    get choices() {
        return this.children;
    }


}

export class ChoiceModel extends BaseInputModel {
    parent;
    type = 'Input.Choice';
    title;
    value;
    selected;

    constructor(payload, parent) {
        super(payload, parent);

        this.title = payload.title;
        this.value = payload.value;
        this.selected = false;
    }
}









