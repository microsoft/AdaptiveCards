// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { WebElement, By, Locator } from "selenium-webdriver";
import { TestUtils } from "./test-utils";
import * as Assert from "assert";

export class Element {
    underlyingElement?: WebElement = undefined;

    protected constructor() {}

    elementWasFound(): boolean {
        return (this.underlyingElement !== undefined);
    }

    async getCssPropertyValue(propertyName: string): Promise<string | undefined> {
        if (this.elementWasFound()) {
            return await TestUtils.getInstance().getCssPropertyValueForElement(this.underlyingElement!, propertyName);
        } else {
            return undefined;
        }
    }

    async elementIsVisible(): Promise<boolean> {
        return (await this.underlyingElement?.getAttribute("visible") === "true") || (await this.underlyingElement!.isDisplayed());
    }

    async elementIsCssVisible(): Promise<boolean> {
        return (await this.getCssPropertyValue("visibility") === "visible");
    }
}

export class ActionableElement extends Element {

    async click() 
    {
        await TestUtils.getInstance().clearInputs();
        await this.underlyingElement?.click();
    }
} 

export abstract class Input extends Element {
    protected constructor() {
        super();
    }

    abstract setData(data: string): Promise<void>;
}

export class TypeableInput extends Input {

    override async setData(data: string): Promise<void>
    {
        await this.underlyingElement?.click();
        await this.underlyingElement?.sendKeys(data);
    }

    async isFocused(): Promise<boolean> {
        if (this.elementWasFound()) {
            const inputId: string = await this.underlyingElement!.getAttribute("id");
            const activeElementId: string = await TestUtils.getInstance().getDriver().switchTo().activeElement().getAttribute("id");

            return (inputId === activeElementId);
        }

        return false;
    }
}

export class InputText extends TypeableInput {
    private constructor() {
        super();
    }

    static async getInputWithId(id: string, container?: Container): Promise<InputText> {
        let input = new InputText();
        input.underlyingElement = await TestUtils.getInstance().getInput(id, "ac-textInput", container);
        return input;
    }
}

export class InputDate extends TypeableInput {
    private constructor() {
        super();
    }

    static async getInputWithId(id: string, container?: Container): Promise<InputDate> {
        let input = new InputDate();
        input.underlyingElement = await TestUtils.getInstance().getInput(id, "ac-dateInput", container);
        return input;
    }
}

export class InputTime extends TypeableInput {
    
    private constructor(){
        super();
    }

    static async getInputWithId(id: string, container?: Container): Promise<InputTime>
    {
        let input = new InputTime();
        input.underlyingElement = await TestUtils.getInstance().getInput(id, "ac-timeInput", container);
        return input;
    }  
}

export class InputNumber extends TypeableInput {

    private constructor(){
        super();
    }

    static async getInputWithId(id: string, container?: Container): Promise<InputNumber>
    {
        let input = new InputNumber();
        input.underlyingElement = await TestUtils.getInstance().getInput(id, "ac-numberInput", container);
        return input;
    }
}

export class InputChoiceSet extends Input 
{
    isExpanded: boolean = false;
    isMultiSelect: boolean = false;
    underlyingExpandedElements: WebElement[];

    private constructor(isExpanded: boolean, isMultiSelect: boolean) {
        super();

        this.isExpanded = isExpanded;
        this.isMultiSelect = isMultiSelect;
    }

    private async getCompactChoiceSet(id: string, container?: Container): Promise<WebElement | undefined>
    {
        let compactChoiceSet = await TestUtils.getInstance().getElementWithId(id, container);
        let actualElement = await compactChoiceSet?.findElement(By.className("ac-choiceSetInput-compact"));
        return actualElement;
    }

    private async getExpandedChoiceSet(id: string, container?: Container): Promise<WebElement[]>
    {
        return await TestUtils.getInstance().getElementsWithName(id, container);
    }

    static async getInputWithId(id: string, isExpanded: boolean, isMultiSelect: boolean, container?: Container): Promise<InputChoiceSet>
    {
        let input = new InputChoiceSet(isExpanded, isMultiSelect);

        if (!isExpanded)
        {
            input.underlyingElement = await input.getCompactChoiceSet(id, container);
        }
        else
        {
            input.underlyingExpandedElements = await input.getExpandedChoiceSet(id, container);
        }
        return input;
    }

    override async setData(data: string): Promise<void> {

        if (this.elementWasFound()) {
            if (this.isExpanded) {
                if (this.isMultiSelect) {
                    const options: string[] = data.split(",");
                    for (const choice of this.underlyingExpandedElements) 
                    {
                        const choiceValue = await choice.getAttribute("aria-label");
                        const choiceIsSelected: boolean = await choice.isSelected();

                        // if the choice has to be selected and it's not selected, click it
                        // or if the choice must not be selected but is selected, click it
                        if ((options.includes(choiceValue) && !choiceIsSelected) || 
                           (!options.includes(choiceValue) && choiceIsSelected)) {
                            await choice.click();
                        }
                    }
                }
                else
                {
                    for (const choice of this.underlyingExpandedElements)
                    {
                        const choiceValue = await choice.getAttribute("aria-label");
                        if (choiceValue === data) {
                            await choice.click();
                        }
                    }
                }

            } else {
                let underlyingElement: WebElement = this.underlyingElement!;
                await underlyingElement.click();

                let option = await underlyingElement.findElement(By.xpath(`//*[@aria-label='${data}']`));
                await option.click();
            }
        }
    }

    override elementWasFound(): boolean {
        if (this.isExpanded) {
            return this.underlyingExpandedElements.length > 0;
        }
        else {
            return super.elementWasFound();
        }
    }
}

export class InputToggle extends Input {
    private constructor(){
        super();
    }

    static async getInputWithId(id: string): Promise<InputToggle>
    {
        let input = new InputToggle();
        input.underlyingElement = await TestUtils.getInstance().getInput(id, "ac-toggleInput");
        return input;
    }
    
    override async setData(data: string): Promise<void> {
        if (this.elementWasFound())
        {
            if (data === "set") {
                await this.set();                
            } else if (data === "unset") {
                await this.unset();
            } else {
                await this.toggle();
            }
        }
    }

    async set(): Promise<void> {
        const isInputSelected: boolean = await this.underlyingElement!.isSelected();

        if (!isInputSelected) {
            await this.toggle();
        }
    }

    async unset(): Promise<void> {
        const isInputSelected: boolean = await this.underlyingElement!.isSelected();

        if (isInputSelected) {
            await this.toggle();
        }
    }

    async toggle(): Promise<void> {
        await this.underlyingElement?.click();
    }


}

export class Container extends ActionableElement {
    protected constructor()
    {
        super();
    }

    static async getContainer(id: string): Promise<Container>
    {
        return new Container();
    }

    static async getContainerWithAction(tooltip: string, parentContainer?: Container): Promise<Container> 
    {
        let container = new Container();
        container.underlyingElement = await TestUtils.getInstance().tryGetContainerWithAction(tooltip, parentContainer);
        return container;
    }
}

// Currently Column and ColumnSet behave just as container (except columnset having a different class name),
// leaving the empty classes for code clarity when used
export class Column extends Container {}

export class ColumnSet extends Container {}

export class Image extends ActionableElement {
    private constructor(){
        super();
    }

    static async getImage(title: string, container?: Container): Promise<Image>
    {
        let input = new Image();
        input.underlyingElement = await TestUtils.getInstance().getImageWithTitle(title, "ac-image", container);
        return input;
    }
}

export class Action extends ActionableElement {
    private constructor()
    {
        super();
    }

    static async clickOnActionWithTitle(title: string): Promise<void>
    {
        let action: Action = await this.getActionWithTitle(title);
        await action.click(); 
    }

    static async getActionWithTitle(title: string): Promise<Action> 
    {
        let action = new Action();
        action.underlyingElement = await TestUtils.getInstance().tryGetActionWithTitle(title);
        return action;
    }

    
}

// As currently there's only one carousel per card is supported then this tests are simpler
export class Carousel {

    private constructor(){}

    static async clickOnLeftArrow()
    {
        const leftArrow = await TestUtils.getInstance().getDriver().findElement(By.className("ac-carousel-left"));
        await leftArrow.click();
    }

    static async clickOnRightArrow()
    {
        const leftArrow = await TestUtils.getInstance().getDriver().findElement(By.className("ac-carousel-right"));
        await leftArrow.click();
    } 

    static async isPageVisible(pageId: string): Promise<Boolean>
    {
        let anyPageIsVisible = false;

        // Due to how the swiper library is made, the first and last pages are duplicated, if we were to use the regular
        // getElementWithId method we would retrieve the duplicated slide, so we have to get the second element with that id
        const pages = await TestUtils.getInstance().getElementsWithId(pageId);
        
        for (const page of pages)
        {
            const pageVisibility = await TestUtils.getInstance().getCssPropertyValueForElement(page, "visibility");
            anyPageIsVisible = anyPageIsVisible || (pageVisibility === "visible")
        }

        return anyPageIsVisible;
    }

    static async getPageDirection(pageId: string): Promise<string>
    {
        const pageElement = await TestUtils.getInstance().getElementWithId(pageId);
        // The actual direction is provided to a id-less div under the page, so
        // we query for that value 
        const pageContainer = await pageElement.findElement(By.xpath("./*"));
        const pageDirection = await pageContainer.getAttribute("dir");

        return pageDirection;
    }

    // This is a helper method to handle the odd scenario of the carousel not behaving correctly
    // when clicking an arrow while the carousel is moving
    static async waitForAnimationsToEnd(): Promise<void>
    {
        await TestUtils.getInstance().delay(1000); 
    }
}