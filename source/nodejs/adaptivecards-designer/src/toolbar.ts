import { DropDown, DropDownItem } from "adaptivecards-controls";

export abstract class ToolbarElement {
    private _renderedElement: HTMLElement = undefined;

    protected abstract internalRender(): HTMLElement;

    protected internalUpdateLayout() {
        // Do nothing in base implementation
    }

    updateLayout() {
        if (this._renderedElement) {
            this.internalUpdateLayout();
        }
    }

    render(): HTMLElement {
        this._renderedElement = this.internalRender();

        this.updateLayout();

        return this._renderedElement;
    }

    get renderedElement(): HTMLElement {
        return this._renderedElement;
    }
}

export class ToolbarSeparator extends ToolbarElement {
    protected internalRender(): HTMLElement {
        let element = document.createElement("div");
        element.className = "acd-toolbar-separator";

        return element;
    }
}

export class ToolbarLabel extends ToolbarElement {
    private _text: string = undefined;

    protected internalUpdateLayout() {
        this.renderedElement.innerText = this._text;
    }

    protected internalRender(): HTMLElement {
        let element = document.createElement("span");
        element.className = "acd-toolbar-label";

        return element;
    }

    constructor(text: string) {
        super();

        this.text = text;
    }

    get text(): string {
        return this._text;
    }

    set text(value: string) {
        this._text = value;

        this.updateLayout();
    }
}

export class ToolbarButton extends ToolbarElement {
    private _caption: string;
    private _displayCaption: boolean = true;
    private _iconClass: string = undefined;
    private _toolTip: string = undefined;
    private _isEnabled: boolean = true;

    protected clicked() {
        if (this.onClick) {
            this.onClick(this);
        }
    }

    protected internalUpdateLayout() {
        this.renderedElement.className = "acd-toolbar-button";
        (this.renderedElement as HTMLButtonElement).disabled = !this.isEnabled;

        if (this.iconClass) {
            this.renderedElement.classList.add(this.iconClass);
        }

        if (!this.displayCaption) {
            this.renderedElement.classList.add("acd-toolbar-button-iconOnly");
            this.renderedElement.innerText = "";
        }
        else {
            this.renderedElement.innerText = this.caption;
        }

        this.renderedElement.title = this.toolTip ? this.toolTip : "";
    }

    protected internalRender(): HTMLElement {
        let element = document.createElement("button");

        element.onclick = (e) => {
            this.clicked();
        }

        return element;
    }

    onClick: (sender: ToolbarButton) => void;

    constructor(
        caption: string,
        iconClass: string,
        onClick: (sender: ToolbarButton) => void = null) {
        super();

        this.caption = caption;
        this.iconClass = iconClass;
        this.onClick = onClick;
    }

    get caption(): string {
        return this._caption;
    }

    set caption(value: string) {
        this._caption = value;

        this.updateLayout();
    }

    get displayCaption(): boolean {
        return this._displayCaption;
    }

    set displayCaption(value: boolean) {
        this._displayCaption = value;

        this.updateLayout();
    }

    get iconClass(): string {
        return this._iconClass;
    }

    set iconClass(value: string) {
        this._iconClass = value;

        this.updateLayout();
    }

    get toolTip(): string {
        return this._toolTip;
    }

    set toolTip(value: string) {
        this._toolTip = value;

        this.updateLayout();
    }

    get isEnabled(): boolean {
        return this._isEnabled;
    }

    set isEnabled(value: boolean) {
        this._isEnabled = value;

        this.updateLayout();
    }
}

export interface IChoicePickerItem {
    name: string;
    value: string;
}

export class ToolbarChoicePicker extends ToolbarElement {
    private _dropDown: DropDown;

    protected internalRender(): HTMLElement {
        this._dropDown = new DropDown();

        for (let choice of this.choices) {
            let dropDownItem = new DropDownItem(choice.value, choice.name);

            this._dropDown.items.add(dropDownItem);
        }

        this._dropDown.selectedIndex = 0;
        this._dropDown.onValueChanged = (sender) => {
            if (this.onChanged) {
                this.onChanged(this);
            }
        }

        let pickerElement = document.createElement("div");

        this._dropDown.attach(pickerElement);

        let pickerContainerElement = document.createElement("div");
        pickerContainerElement.className = "acd-toolbar-choicePicker";
        pickerContainerElement.appendChild(pickerElement);

        return pickerContainerElement;
    }

    onChanged: (sender: ToolbarChoicePicker) => void;

    choices: Array<IChoicePickerItem> = [];

    get value(): string {
        return this._dropDown.value.key;
    }
}

export class Toolbar {
    private _elements: Array<ToolbarElement> = [];
    private _attachedTo: HTMLElement;

    attachTo(element: HTMLElement) {
        this._attachedTo = element;
        this._attachedTo.className = "acd-toolbar";
        this._attachedTo.innerHTML = "";

        for (let toolbarElement of this._elements) {
            let renderedToolbarElement = toolbarElement.render();

            this._attachedTo.appendChild(renderedToolbarElement);
        }
    }

    addElement(element: ToolbarElement) {
        this._elements.push(element);
    }
}