// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Builder, By, Capabilities, until, WebDriver, WebElement } from "selenium-webdriver";
import * as Assert from "assert";
import { WaitUntil } from "./wait-utils";

export class TestUtils {
    timeoutForCardRendering: number = 10000;
    private driver: WebDriver;
    private hideInputsButton: WebElement | undefined = undefined;
    private inputs: any = undefined;

    private static instance : TestUtils;

    private constructor() 
    {
        this.driver = new Builder().withCapabilities(Capabilities.edge()).build();
    }

    async initializeDriver()
    {
        await TestUtils.instance.driver.get("http://127.0.0.1:8080/");
    }

    async stopDriver()
    {
        if (this.driver) {
            await this.driver.quit();
        }
    }

    static getInstance()
    {
        if (TestUtils.instance == undefined){
            TestUtils.instance = new TestUtils(); 
        }
        return TestUtils.instance;
    }

    getDriver()
    {
        return this.driver;
    }

    async goToTestCase(testCaseName: string): Promise<void> {
        const elementLinkText: WebElement = await this.driver.findElement(By.id(testCaseName));
        await elementLinkText.click();

        const renderedCardContainer: WebElement = await this.getElementWithId("renderedCardSpace");

        await this.driver.wait(until.elementIsVisible(renderedCardContainer), this.timeoutForCardRendering);
    }

    async getHideInputsButton(): Promise<WebElement>
    {
        if (this.hideInputsButton === undefined)
        {
            this.hideInputsButton = await this.getElementWithId("hideInputsBtn");
        }

        return this.hideInputsButton!;
    }

    async clearInputs(): Promise<void>
    {
        this.inputs = undefined;
        await this.hideInputsDiv();
    }

    async hideInputsDiv(): Promise<void> 
    {
        const hideInputsButton = await this.getHideInputsButton(); 
        await hideInputsButton.click();
    }

    async getInputFor(inputId: string): Promise<string> {
        if (this.inputs === undefined)
        {
            await this.getRetrievedInputs();
        }

        return this.inputs[inputId];
    }

    async getRetrievedInputs(): Promise<void> {
        if (this.inputs === undefined)
        {
            const retrievedInputsDiv: WebElement = await this.getElementWithId("retrievedInputsDiv");
            await this.driver.wait(until.elementIsVisible(retrievedInputsDiv), this.timeoutForCardRendering);

            const retrievedInputs: string = await retrievedInputsDiv.getText();

            this.inputs = JSON.parse(retrievedInputs)
        }
    }

    async tryGetActionWithTitle(actionTitle: string): Promise<WebElement | undefined> {
        const buttonList: WebElement[] = await this.driver.findElements(By.xpath(`//*[@aria-label='${actionTitle}']`));

        return (buttonList.length > 0) ? buttonList[0] : undefined;
    }

    async tryGetContainerWithAction(tooltip: string): Promise<WebElement | undefined> {
        const containerList: WebElement[] = await this.driver.findElements(By.xpath(`//*[@aria-description='${tooltip}']`));

        return (containerList.length > 0) ? containerList[0] : undefined;
    }

    async getActionWithTitle(actionTitle: string): Promise<WebElement> {
        const button: WebElement = await this.driver.findElement(By.xpath(`//*[@title='${actionTitle}']`));

        return button;
    }

    async clickOnActionWithTitle(actionTitle: string): Promise<void> {
        const button: WebElement = await this.getActionWithTitle(actionTitle);
        await button.click();
    }

    async waitUntilElementIsCssVisible(id: string, timeoutInMs?: number)
    {
        const elementsToWaitFor: WebElement[] = await this.getElementsWithId(id);
        const timeOut = timeoutInMs !== undefined ? timeoutInMs : this.timeoutForCardRendering;

        let successFunction = async (params: any) => {
            let elementIsVisible: boolean = false;

            for (let element of elementsToWaitFor)
            {
                let visibility = await TestUtils.getInstance().getCssPropertyValueForElement(element, "visibility");
                elementIsVisible = elementIsVisible || (visibility === "visible");
            }

            return elementIsVisible;
        };

        await WaitUntil.customWait(timeOut, successFunction, elementsToWaitFor)
    }

    async waitUntilElementIsVisible(id: string) {
        const elementToWaitFor: WebElement = await this.getElementWithId(id);
        await this.driver.wait(until.elementIsVisible(elementToWaitFor), this.timeoutForCardRendering);
    }

    async waitUntilElementIsNotVisible(id: string) {
        const elementToWaitFor: WebElement = await this.getElementWithId(id);
        await this.driver.wait(until.elementIsNotVisible(elementToWaitFor), this.timeoutForCardRendering);
    }

    async getInput(inputId: string, className: string): Promise<WebElement> {
        const inputDiv: WebElement = await this.driver.findElement(By.id(inputId));
        const input = await inputDiv.findElement(By.className(className));

        return input;
    }

    async setValueOnInput(inputId: string, className: string, value: string) {
        const input: WebElement = await this.getInput(inputId, className);
        await input.click();
        await input.sendKeys(value);
    }

    async setDateOnDateInput(dateInputId: string, value: string): Promise<void> {
        await this.setValueOnInput(dateInputId, "ac-dateInput", value);
    }

    async getTextInput(textInputId: string): Promise<WebElement> {
        const textInput: WebElement = await this.getInput(textInputId, "ac-textInput");

        return textInput;
    }

    // Await for x miliseconds
    async delay(miliseconds: number): Promise<void> {
        return new Promise(res => setTimeout(res, miliseconds));
    }

    async assertElementWithIdDoesNotExist(id: string): Promise<void> {
        const elementList = await this.driver.findElements(By.id(id));
        Assert.strictEqual(0, elementList.length);
    }

    async getElementsWithId(id: string): Promise<WebElement[]> {
        return this.driver.findElements(By.id(id));
    }

    async getElementWithId(id: string): Promise<WebElement> {
        return this.driver.findElement(By.id(id));
    }

    async getCssPropertyValueForElement(element: WebElement, cssProperty: string): Promise<string> {
        return element.getCssValue(cssProperty);
    }

    async getCssPropertyValueForElementWithId(id: string, cssProperty: string): Promise<string> {
        const element: WebElement = await this.getElementWithId(id);

        return this.getCssPropertyValueForElement(element, cssProperty);
    }

    async getElementsWithName(id: string): Promise<WebElement[]>
    {
        return await this.driver.findElements(By.name(id));
    }
}
