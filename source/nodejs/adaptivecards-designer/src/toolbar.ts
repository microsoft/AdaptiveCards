// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { DropDown, DropDownItem } from "adaptivecards-controls";
import { v4 as uuidv4 } from "uuid";

export enum ToolbarElementAlignment {
    Left,
    Right
}

export abstract class ToolbarElement {
    private _renderedElement: HTMLElement = undefined;

    protected abstract internalRender(): HTMLElement;

    protected internalUpdateLayout() {
        // Do nothing in base implementation
    }

    readonly id: string;

    isVisible: boolean = true;
    separator: boolean = false;
    label: string = null;
    alignment: ToolbarElementAlignment = ToolbarElementAlignment.Left;

    constructor(id: string) {
        if (!id || id === "") {
            throw new Error("Toolbar elements must have an Id.");
        }

        this.id = id;
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

export class ToolbarButton extends ToolbarElement {
    private _caption: string;
    private _displayCaption: boolean = true;
    private _iconClass: string = undefined;
    private _toolTip: string = undefined;
    private _isEnabled: boolean = true;
    private _allowToggle: boolean = false;
    private _isToggled: boolean = false;

    protected clicked() {
        if (this.onClick) {
            this.onClick(this);
        }
    }

    protected internalUpdateLayout() {
        this.renderedElement.className = "acd-toolbar-button";
        (this.renderedElement as HTMLButtonElement).disabled = !this.isEnabled;

        if (this.isToggled) {
            this.renderedElement.classList.add("acd-toolbar-button-toggled");
        }
        else {
            this.renderedElement.classList.remove("acd-toolbar-button-toggled");
        }
        this.renderedElement.setAttribute("aria-pressed", this.isToggled.toString());

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
            if (this.allowToggle) {
                this.isToggled = !this.isToggled;
            }
            
            this.clicked();
        }

        return element;
    }

    onClick: (sender: ToolbarButton) => void;

    constructor(
        id: string,
        caption: string,
        iconClass: string,
        onClick: (sender: ToolbarButton) => void = null) {
        super(id);

        this.caption = caption;
        this.iconClass = iconClass;
        this.onClick = onClick;
    }

    get allowToggle(): boolean {
        return this._allowToggle;
    }

    set allowToggle(value: boolean) {
        this._allowToggle = value;

        if (!this._allowToggle) {
            this.isToggled = false;
        }
    }

    get isToggled(): boolean {
        return this._isToggled;
    }

    set isToggled(value: boolean) {
        this._isToggled = value;

        this.updateLayout();
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
    private _labelledById: string; // id to use for our label element

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

        if (this.width && this.width > 0) {
            pickerElement.style.width = this.width + "px";
        }

        // update label ids so we can generate correct aria
        if (this.label && !this._labelledById) {
            this._labelledById = uuidv4();
            this._dropDown.parentLabelId = this._labelledById;
        }

        this._dropDown.attach(pickerElement);

        let pickerContainerElement = document.createElement("div");
        pickerContainerElement.className = "acd-toolbar-choicePicker";
        pickerContainerElement.style.display = "flex";
        pickerContainerElement.style.alignItems = "center";

        if (this.label) {
            let labelElement = document.createElement("span");
            labelElement.className = "acd-toolbar-label";
            labelElement.innerText = this.label;
            labelElement.id = this._labelledById;

            pickerContainerElement.appendChild(labelElement);
        }

        pickerContainerElement.appendChild(pickerElement);

        return pickerContainerElement;
    }

    onChanged: (sender: ToolbarChoicePicker) => void;

    label: string = null;
    choices: Array<IChoicePickerItem> = [];
    width?: number = null;

    get value(): string {
        return this._dropDown.value.key;
    }

    get selectedIndex(): number {
        return this._dropDown.selectedIndex;
    }

    set selectedIndex(value: number) {
        this._dropDown.selectedIndex = value;
    }
}

export class Toolbar {
    private _elements: Array<ToolbarElement> = [];
    private _attachedTo: HTMLElement;

    private createSeparatorElement(): HTMLElement {
        let separatorElement = document.createElement("div");
        separatorElement.className = "acd-toolbar-separator";

        return separatorElement;
    }

    private renderElementsInto(
        container: HTMLElement,
        elements: Array<ToolbarElement>,
        separatorPosition: ToolbarElementAlignment) {
        for (let i = 0; i < elements.length; i++) {
            if (elements[i].separator && separatorPosition == ToolbarElementAlignment.Left && i > 0) {
                container.appendChild(this.createSeparatorElement());
            }

            container.appendChild(elements[i].render());

            if (elements[i].separator && separatorPosition == ToolbarElementAlignment.Right && i < elements.length - 1) {
                container.appendChild(this.createSeparatorElement());
            }
        }
    }

    attachTo(element: HTMLElement) {
        this._attachedTo = element;
        this._attachedTo.className = "acd-toolbar";
        this._attachedTo.style.display = "flex";
        this._attachedTo.style.justifyContent = "space-between";
        this._attachedTo.innerHTML = "";

        let leftElements: Array<ToolbarElement> = [];
        let rightElements: Array<ToolbarElement> = [];

        for (let element of this._elements) {
            if (element.isVisible) {
                if (element.alignment == ToolbarElementAlignment.Left) {
                    leftElements.push(element);
                }
                else {
                    rightElements.push(element);
                }
            }
        }

        let leftContainer = document.createElement("div");
        leftContainer.style.display = "flex";
        leftContainer.style.alignItems = "center";

        let rightContainer = document.createElement("div");
        rightContainer.style.display = "flex";
        rightContainer.style.alignItems = "center";

        this.renderElementsInto(
            leftContainer,
            leftElements,
            ToolbarElementAlignment.Left);
        this.renderElementsInto(
            rightContainer,
            rightElements,
            ToolbarElementAlignment.Right);

        this._attachedTo.appendChild(leftContainer);
        this._attachedTo.appendChild(rightContainer);
    }

    addElement(element: ToolbarElement) {
        this._elements.push(element);
    }

    getElementById(elementId: string): ToolbarElement {
        for (let element of this._elements) {
            if (element.id == elementId) {
                return element;
            }
        }

        return null;
    }

    insertElementAfter(element: ToolbarElement, afterElementId: string) {
        for (let i = 0; i < this._elements.length; i++) {
            if (this._elements[i].id == afterElementId) {
                this._elements.splice(i + 1, 0, element);

                return;
            }
        }

        // Add as the last element if no element was found with the
        // specified id
        this._elements.push(element);
    }

    insertElementBefore(element: ToolbarElement, beforeElementId: string) {
        for (let i = this._elements.length - 1; i >= 0; i--) {
            if (this._elements[i].id == beforeElementId) {
                this._elements.splice(i, 0, element);

                return;
            }
        }

        // Insert as first element if no element was found with the
        // specified id
        this._elements.splice(0, 0, element);
    }
}
