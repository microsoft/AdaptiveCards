// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { WebElement, By, Locator } from "selenium-webdriver";
import { ByExtended, XpathBuilder } from "./selenium-utils";
import { TestUtils } from "./test-utils";
import { WaitUtils } from "./wait-utils";
import * as Assert from "assert";

export abstract class ACElement {
    private _id: string;
    private _underlyingElement?: WebElement = undefined;
    private _container?: ACContainer;

    protected constructor(underlyingElement: WebElement | string, container?: ACContainer) {
        if (typeof underlyingElement === "string") {
            this._id = underlyingElement;
        } else {
            this._underlyingElement = underlyingElement;
        }

        this._container = container;
    }

    public get id(): string {
        return this._id;
    }

    public get underlyingElement(): WebElement | undefined {
        return this._underlyingElement;
    }

    protected set underlyingElement(underlyingElement: WebElement | undefined) {
        this._underlyingElement = underlyingElement;
    }

    public get container(): ACContainer | undefined {
        return this._container;
    }

    abstract ensureUnderlyingElement(className?: string): Promise<void>;

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

    async getChildrenHtml(): Promise<string> {
        return (await this.underlyingElement!.getAttribute("innerHtml"));
    }

    async getHtml(): Promise<string> {
        return (await this.underlyingElement!.getAttribute("outerHtml"));
    }
}

export abstract class ACActionableElement extends ACElement {
    async click() 
    {
        await TestUtils.getInstance().clearInputs();
        await this.underlyingElement?.click();
    }
} 

export class Input extends ACElement {
    protected div: WebElement;
    protected label?: WebElement;
    protected errorMessage?: WebElement;

    async setData(data: string): Promise<void> {
        await this.underlyingElement?.click();
        await this.underlyingElement?.sendKeys(data);
    }

    override async ensureUnderlyingElement(className?: string): Promise<void> {
        this.div = await TestUtils.getInstance().getInputContainer(this.id, this.container);
        this.underlyingElement = await TestUtils.getInstance().getInput(className!, this.div);

        await this.getLabel();
    }

    hasLabel(): boolean {
        return (this.label !== undefined);
    }

    async getLabel(): Promise<string | undefined> {
        await this.ensureLabel();
        return await this.label?.getText();
    }

    async getErrorMessage(): Promise<string | undefined> {
        await this.ensureErrorMessage();
        return this.errorMessage?.getText();
    }

    async isRequired(): Promise<boolean> {
        return await this.classListContains(this.underlyingElement!, "ac-input-required");
    }

    async validationFailed(): Promise<boolean> {
        return await this.classListContains(this.underlyingElement!, "ac-input-validation-failed");        
    }

    async classListContains(element: WebElement, classToQuery: string): Promise<boolean> {
        return (await element.getAttribute("class")).split(" ").includes(classToQuery);
    }

    async ensureLabel(): Promise<void> {
        const htmlInputId: string = await this.underlyingElement!.getAttribute("id");
        const labels: WebElement[] = await this.div.findElements(By.xpath(new XpathBuilder().setTagName("label").addAttributeEquals("for", htmlInputId).buildXpath())); 
        this.label = (labels.length > 0) ? labels[0] : undefined;
    }

    async ensureErrorMessage(): Promise<void> {
        if (await this.validationFailed()) {        
            this.errorMessage = await this.div.findElement(By.id(await this.getErrorMessageId()));
        }
    }

    protected async getErrorMessageId(): Promise<string> {
        const ariaLabeledBy = await this.underlyingElement!.getAttribute("aria-labelledby");

        let labels: string[] = ariaLabeledBy.split(" ");
        Assert.strictEqual(labels.length, 2, `Labels contains more than two labels ${labels}`);
        
        labels.splice(labels.indexOf(await this.label!.getAttribute("id")), 1);
        Assert.strictEqual(labels.length, 1, `Labels contains more than one label ${labels}`);

        return labels[0];
    }

    async getChildrenHtml(): Promise<string> {
        return (await this.div.getAttribute("innerHtml"));
    }

    async getHtml(): Promise<string> {
        return (await this.div.getAttribute("outerHtml"));
    }
}

export class ACTypeableInput extends Input {
    async isFocused(): Promise<boolean> {
        if (this.elementWasFound()) {
            const inputId: string = await this.underlyingElement!.getAttribute("id");
            const activeElementId: string = await TestUtils.getInstance().driver.switchTo().activeElement().getAttribute("id");

            return (inputId === activeElementId);
        }

        return false;
    }
}

export class ACInputText extends ACTypeableInput {
    static async getInputWithId(id: string, container?: ACContainer): Promise<ACInputText> {
        const input = new ACInputText(id, container);
        await input.ensureUnderlyingElement("ac-textInput");
        return input; 
    }
}

export class ACInputDate extends ACTypeableInput {
    static async getInputWithId(id: string, container?: ACContainer): Promise<ACInputDate> {
        const input = new ACInputDate(id, container);
        await input.ensureUnderlyingElement("ac-dateInput");
        return input; 
    }

    async setDate(year: number, month: number, day: number) { 
        await this.setData(month.toString().padStart(2, "0") + day.toString().padStart(2, "0") + year.toString());
    }
}

export class ACInputTime extends ACTypeableInput {
    static async getInputWithId(id: string, container?: ACContainer): Promise<ACInputTime> {
        const input = new ACInputTime(id, container);
        await input.ensureUnderlyingElement("ac-timeInput");
        return input;
    }

    async setTime(hour: number, minute: number) {
        const meridian: string = (hour >= 12) ? "PM" : "AM";
        await this.setData(hour.toString().padStart(2, "0") + minute.toString().padStart(2, "0") + meridian);
    }
}

export class ACInputNumber extends ACTypeableInput {
    static async getInputWithId(id: string, container?: ACContainer): Promise<ACInputNumber> {
        const input = new ACInputNumber(id, container);
        await input.ensureUnderlyingElement("ac-numberInput");
        return input;
    }
}

export class ACInputChoiceSet extends Input 
{
    isExpanded: boolean = false;
    isMultiSelect: boolean = false;
    underlyingExpandedElements: WebElement[];

    private constructor(id: string, isExpanded: boolean, isMultiSelect: boolean, container?: ACContainer) {
        super(id, container);

        this.isExpanded = isExpanded;
        this.isMultiSelect = isMultiSelect;
    }

    override async ensureUnderlyingElement(className?: string): Promise<void> {
        this.div = await TestUtils.getInstance().getInputContainer(this.id, this.container);

        if (!this.isExpanded) {
            await this.getCompactChoiceSet(this.id, this.container);
        }
        else {
            await this.getExpandedChoiceSet(this.id, this.container);
        }
    }

    private async getCompactChoiceSet(id: string, container?: ACContainer): Promise<void> {
        this.underlyingElement = await this.div.findElement(By.className("ac-choiceSetInput-compact"));
    }

    private async getExpandedChoiceSet(id: string, container?: ACContainer): Promise<void> {
        if (this.isMultiSelect) {
            this.underlyingElement = await this.div.findElement(ByExtended.containsClass("ac-choiceSetInput-multiSelect"));
        } else {
            this.underlyingElement = await this.div.findElement(ByExtended.containsClass("ac-choiceSetInput-expanded"));
        }
        this.underlyingExpandedElements = await TestUtils.getInstance().getElementsWithName(id, container);
    }

    static async getInputWithId(id: string, isExpanded: boolean, isMultiSelect: boolean, container?: ACContainer): Promise<ACInputChoiceSet> {
        const input = new ACInputChoiceSet(id, isExpanded, isMultiSelect, container);
        await input.ensureUnderlyingElement();
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

    override async getErrorMessageId(): Promise<string> {
        if (this.isExpanded) {
            const ariaLabeledBy = await this.underlyingExpandedElements[0].getAttribute("aria-labelledby");
            const choiceId = await this.underlyingExpandedElements[0].getAttribute("id");

            let labels: string[] = ariaLabeledBy.split(" ");
            Assert.strictEqual(labels.length, 3, `Labels contains more than three labels ${labels}`);
            
            labels.splice(labels.indexOf(await this.label!.getAttribute("id")), 1);
            labels.splice(labels.indexOf(await this.getIdOfLabel(choiceId)), 1);
            Assert.strictEqual(labels.length, 1, `Labels contains more than one label ${labels}`);

            return labels[0];
        } else {
            return super.getErrorMessageId();
        }
    }

    private async getIdOfLabel(choiceId: string): Promise<string> {
        const label: WebElement = await this.div.findElement(By.xpath(new XpathBuilder().setTagName("label").addAttributeEquals("for", choiceId).buildXpath()));
        return await label.getAttribute("id");
    }
}

export class ACInputToggle extends Input {
    static async getInputWithId(id: string, container?: ACContainer): Promise<ACInputToggle> {
        const input = new ACInputToggle(id, container);
        await input.ensureUnderlyingElement("ac-toggleInput");
        return input;
    }
    
    override async setData(data: string): Promise<void> {
        if (this.elementWasFound()) {
            if (data === "set") {
                await this.set();                
            } 
            else if (data === "unset") {
                await this.unset();
            } 
            else {
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

export class ACContainer extends ACActionableElement {
    static async getContainer(id: string): Promise<ACContainer> {
        return new ACContainer(id);
    }

    static async getContainerWithAction(tooltip: string, parentContainer?: ACContainer): Promise<ACContainer> {
        const container = new ACContainer(tooltip, parentContainer);
        await container.ensureUnderlyingElement();
        return container;
    }

    override async ensureUnderlyingElement(className?: string): Promise<void> {
        this.underlyingElement = await TestUtils.getInstance().tryGetContainerWithAction(this.id, this.container);
    }
}

// Currently Column and ColumnSet behave just as container (except columnset having a different class name),
// leaving the empty classes for code clarity when used
export class ACColumn extends ACContainer {}

export class ACColumnSet extends ACContainer {}

export class ACCard extends ACContainer {

    private index: number = 0;

    constructor(underlyingElement: string, index?: number) {
        super(underlyingElement);

        if (index !==  undefined) {
            this.index = index;
        }
    }

    static async getCard(index?: number): Promise<ACCard> {
        const card = new ACCard("", index);
        await card.ensureUnderlyingElement("ac-adaptiveCard");
        return card;
    } 

    override async ensureUnderlyingElement(className?: string): Promise<void> {
        const cardList = await TestUtils.getInstance().getElementsWithClass(className!);
        this.underlyingElement = cardList[this.index];
    }
}

export class ACImage extends ACActionableElement {
    static async getImage(title: string, container?: ACContainer): Promise<ACImage>
    {
        const image = new ACImage(title, container);
        await image.ensureUnderlyingElement("ac-image");
        return image;
    }

    override async ensureUnderlyingElement(className?: string): Promise<void> {
        this.underlyingElement = await TestUtils.getInstance().getImageWithTitle(this.id, className!, this.container);
    }

    async getSrc(): Promise<string> {
        return await this.underlyingElement!.getAttribute("src");
    }
}

export class ACAction extends ACActionableElement {
    static async clickOnActionWithTitle(title: string): Promise<void>
    {
        let action: ACAction = await this.getActionWithTitle(title);
        await action.click(); 
    }

    static async getActionWithTitle(title: string): Promise<ACAction> 
    {
        let action = new ACAction(title);
        await action.ensureUnderlyingElement(); 
        return action;
    }

    override async ensureUnderlyingElement(className?: string): Promise<void> {
        this.underlyingElement = await TestUtils.getInstance().tryGetActionWithTitle(this.id);
    }
}

// As currently there's only one carousel per card is supported then this tests are simpler
export class ACCarousel {

    private constructor(){}

    static async clickOnLeftArrow()
    {
        const leftArrow = await TestUtils.getInstance().driver.findElement(By.className("ac-carousel-left"));
        await leftArrow.click();
    }

    static async clickOnRightArrow()
    {
        const leftArrow = await TestUtils.getInstance().driver.findElement(By.className("ac-carousel-right"));
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
        await WaitUtils.waitFor(1000); 
    }
}