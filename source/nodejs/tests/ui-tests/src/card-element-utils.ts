// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { WebElement, By } from "selenium-webdriver";
import { TestUtils } from "./test-utils";
import * as Assert from "assert";

export class Element {
    underlyingElement?: WebElement = undefined;

    protected constructor() {}

    elementWasFound(): boolean
    {
        return (this.underlyingElement !== undefined);
    }
}

export abstract class Input extends Element {
    protected constructor() {
        super();
    }

    abstract setData(data: string): Promise<void>;
}

export class InputText extends Input {
    private constructor(){
        super();
    }

    static async getInputWithId(id: string): Promise<InputText>
    {
        let input = new InputText();
        input.underlyingElement = await TestUtils.getInstance().getInput(id, "ac-textInput");
        return input;
    }

    override async setData(data: string): Promise<void>
    {
        await this.underlyingElement?.click();
        await this.underlyingElement?.sendKeys(data);
    }

    async isFocused(): Promise<boolean>
    {
        if (this.elementWasFound())
        {
            const inputId: string = await this.underlyingElement!.getAttribute("id");
            const activeElementId: string = await TestUtils.getInstance().getDriver().switchTo().activeElement().getAttribute("id");

            return (inputId === activeElementId);
        }

        return false;
    }
}

export class InputDate extends Input {
    private constructor(){
        super();
    }

    static async getInputWithId(id: string): Promise<InputDate>
    {
        let input = new InputDate();
        input.underlyingElement = await TestUtils.getInstance().getInput(id, "ac-dateInput");
        return input;
    }

    override async setData(data: string): Promise<void> 
    {
        await this.underlyingElement?.click();
        await this.underlyingElement?.sendKeys(data);
    }
}

export class InputTime extends Input {
    
    private constructor(){
        super();
    }

    static async getInputWithId(id: string): Promise<InputTime>
    {
        let input = new InputTime();
        input.underlyingElement = await TestUtils.getInstance().getInput(id, "ac-timeInput");
        return input;
    }
    
    override async setData(data: string): Promise<void> {
        await this.underlyingElement?.click();
        await this.underlyingElement?.sendKeys(data);
    }
    
}

export class InputNumber extends Input {

    private constructor(){
        super();
    }

    static async getInputWithId(id: string): Promise<InputNumber>
    {
        let input = new InputNumber();
        input.underlyingElement = await TestUtils.getInstance().getInput(id, "ac-numberInput");
        return input;
    }

    override async setData(data: string): Promise<void> {
        await this.underlyingElement?.click();
        await this.underlyingElement?.sendKeys(data);
    }
}

export class InputChoiceSet extends Input 
{
    isExpanded: boolean = false;
    isMultiSelect: boolean = false;
    underlyingElements: WebElement[];

    private constructor(isExpanded: boolean, isMultiSelect: boolean) {
        super();

        this.isExpanded = isExpanded;
        this.isMultiSelect = isMultiSelect;
    }

    private async getCompactChoiceSet(id: string): Promise<WebElement>
    {
        let compactChoiceSet = await TestUtils.getInstance().getElementWithId(id);
        let actualElement = await compactChoiceSet.findElement(By.className("ac-choiceSetInput-compact"));
        return actualElement;
    }

    private async getExpandedChoiceSet(id: string): Promise<WebElement[]>
    {
        return await TestUtils.getInstance().getElementsWithName(id);
    }

    static async getInputWithId(id: string, isExpanded: boolean, isMultiSelect: boolean): Promise<InputChoiceSet>
    {
        let input = new InputChoiceSet(isExpanded, isMultiSelect);

        if (!isExpanded)
        {
            input.underlyingElement = await input.getCompactChoiceSet(id);
        }
        else
        {
            input.underlyingElements = await input.getExpandedChoiceSet(id);
        }
        return input;
    }

    override async setData(data: string): Promise<void> {

        if (this.elementWasFound()) {
            if (this.isExpanded) {
                if (this.isMultiSelect) {
                    const options: string[] = data.split(",");
                    for (const choice of this.underlyingElements) 
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
                    for (const choice of this.underlyingElements)
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
            return this.underlyingElements.length > 0;
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
            const isInputSelected: boolean = await this.underlyingElement!.isSelected();
            let mustClick: boolean = true;

            if (data === "set") {
                mustClick = !isInputSelected; 
            } else if (data === "unset") {
                mustClick = isInputSelected;
            }

            if (mustClick)
            {
                this.underlyingElement?.click();
            }
        }
    }
}

export class Container extends Element 
{
    private constructor()
    {
        super();
    }

    static async getContainer(id: string): Promise<Container>
    {
        return new Container();
    }

    static async getContainerWithAction(tooltip: string): Promise<Container> 
    {
        let container = new Container();
        container.underlyingElement = await TestUtils.getInstance().tryGetContainerWithAction(tooltip);
        return container;
    }

    async click() 
    {
        await TestUtils.getInstance().clearInputs();
        await this.underlyingElement?.click();
    }
}

export class Action extends Element {
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

    async click() 
    {
        await TestUtils.getInstance().clearInputs();
        await this.underlyingElement?.click();
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