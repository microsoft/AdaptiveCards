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
    private constructor() {
        super();
    }

    static async getInputWithId(id: string, isExpanded: boolean, isMultiSelect: boolean): Promise<InputChoiceSet>
    {
        let input = new InputChoiceSet();
        input.underlyingElement = await TestUtils.getInstance().getInput(id, "ac-choiceSetInput-expanded");
        return input;
    }

    override async setData(data: string): Promise<void> {
        await this.underlyingElement?.click();
        await this.underlyingElement?.sendKeys(data);
    }
}

export class Action extends Element {
    private constructor()
    {
        super();
    }

    static async getActionWithTitle(title: string): Promise<Action> 
    {
        let action = new Action();
        action.underlyingElement = await TestUtils.getInstance().tryGetActionWithTitle(title);
        return action;
    }

    async click() 
    {
        await TestUtils.getInstance().hideInputsDiv();
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