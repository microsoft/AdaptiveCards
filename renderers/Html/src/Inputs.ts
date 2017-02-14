import * as Utils from "./Utils";
import { IContainer, CardElement } from "./Interfaces";

export abstract class InputBase extends CardElement {
    id: string;
    title: string;
    value: string;

    // static createInput(container: Container, typeName: string): InputBase {
    //     switch (typeName) {
    //         case "TextInput":
    //             return new TextInput(container);
    //         case "MultichoiceInput":
    //             return new MultichoiceInput(container);
    //         case "DateInput":
    //             return new DateInput(container);
    //         case "ToggleInput":
    //             return new ToggleInput(container);
    //         default:
    //             throw new Error("Unknown input type: " + typeName);
    //     }
    // }

    parse(json: any) {
        super.parse(json);

        this.id = json["id"];
        this.title = json["title"];
        this.value = json["value"];
    }

    abstract render(): HTMLElement;

    renderSpeech(): string {
        if (this.speak != null)
            return this.speak;

        if (this.title)
            return '<s>' + this.title + '</s>\n';
        return null;
    }
}

export class TextInput extends InputBase {
    maxLength: number;
    isMultiline: boolean;

    constructor(container: IContainer) {
        super(container);
    }

    parse(json: any) {
        super.parse(json);

        this.maxLength = json["maxLength"];
        this.isMultiline = json["isMultiline"];
    }

    render(): HTMLElement {
        let element = document.createElement("textarea");
        element.className = "input textInput";

        if (this.isMultiline) {
            element.className += " multiline";
        }

        element.placeholder = this.title;

        return element;
    }
}

export class Choice {
    display: string;
    value: string;

    parse(json: any) {
        this.display = json["display"];
        this.value = json["value"];
    }
}

export class ToggleInput extends InputBase {
    render(): HTMLElement {
        let element = document.createElement("div");
        element.innerHTML = '<input type="checkbox" class="input toggleInput"></input><div class="toggleInputLabel">' + this.title + '</div>';

        return element;
    }
}

export class MultichoiceInput extends InputBase {
    private _choices: Array<Choice> = [];

    constructor(container: IContainer) {
        super(container);

        //this.size = Size.Medium;
    }

    parse(json: any) {
        super.parse(json);

        if (json["choices"] != undefined) {
            let choiceArray = json["choices"] as Array<any>;

            for (let i = 0; i < choiceArray.length; i++) {
                let choice = new Choice();

                choice.parse(choiceArray[i]);

                this._choices.push(choice);
            }
        }
    }

    render(): HTMLElement {
        let selectElement = document.createElement("select");
        selectElement.className = "input multichoiceInput";

        for (let i = 0; i < this._choices.length; i++) {
            let option = document.createElement("option");
            option.value = this._choices[i].value;
            option.text = this._choices[i].display;

            Utils.appendChild(selectElement, option);
        }

        return selectElement;
    }
}

export class DateInput extends InputBase{
    includeTime: boolean;

    constructor(container: IContainer) {
        super(container);

        //this.size = Size.Medium;
    }

    parse(json: any) {
        super.parse(json);

        this.includeTime = json["includeTime"];
    }

    render(): HTMLElement {
        let container = document.createElement("div");
        container.className = "input";
        container.style.display = "flex";

        let datePicker = document.createElement("input");
        datePicker.type = "date";
        datePicker.className = "dateInput";

        Utils.appendChild(container, datePicker);

        if (this.includeTime) {
            datePicker.style.flex = "1 1 67%";

            let timePicker = document.createElement("input");
            timePicker.type = "time";
            timePicker.className = "timeInput";
            timePicker.style.flex = "1 1 33%";

            Utils.appendChild(container, timePicker);
        }
        else {
            datePicker.style.flex = "1 1 100%";
        }

        return container;
    }
}
