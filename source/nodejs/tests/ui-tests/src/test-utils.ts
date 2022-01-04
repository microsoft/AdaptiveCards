// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Builder, By, Capabilities, until, WebDriver, WebElement } from "selenium-webdriver";
import * as Assert from "assert";
import { WaitUntil } from "./wait-utils";
import { Input, Container, Element } from "./card-element-utils";

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

            let successFunction = async (params: any) => {
                let visibility = await TestUtils.getInstance().getCssPropertyValueForElement(retrievedInputsDiv, "visibility");
                return (visibility === "visible");
            };
    
            await WaitUntil.customWait(this.timeoutForCardRendering, successFunction, retrievedInputsDiv);

            const retrievedInputs: string = await retrievedInputsDiv.getText();

            this.inputs = JSON.parse(retrievedInputs)
        }
    }

    getRoot(container?: Container): WebElement | WebDriver {
        if (container !== undefined && container.elementWasFound()) {
            return container.underlyingElement!;
        } else {
            return this.getDriver();
        }
    }

    async tryGetActionWithTitle(actionTitle: string): Promise<WebElement | undefined> {
        const buttonList: WebElement[] = await this.driver.findElements(By.xpath(`//*[@aria-label='${actionTitle}']`));
        return (buttonList.length > 0) ? buttonList[0] : undefined;
    }    

    async tryGetContainerWithAction(tooltip: string, container?: Container): Promise<WebElement | undefined> {
        const containerList: WebElement[] = await this.driver.findElements(By.xpath(`//*[@aria-description='${tooltip}']`));
        return (containerList.length > 0) ? containerList[0] : undefined;
    }

    async getImageWithTitle(title: string, className: string, container?: Container): Promise<WebElement | undefined> {
        return await this.getRoot(container).findElement(By.xpath(`//*[@title='${title}']`));
    }

    async getActionWithTitle(actionTitle: string): Promise<WebElement> {
        return await this.driver.findElement(By.xpath(`//*[@title='${actionTitle}']`));
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

        await WaitUntil.customWait(timeOut, successFunction, elementsToWaitFor);
    }

    async waitUntilPredicateIsTrue(elements: Element[], successPredicate: Function, timeoutInMs?: number) {
        const timeOut = (timeoutInMs !== undefined) ? timeoutInMs : this.timeoutForCardRendering;

        await WaitUntil.customWait(timeOut, successPredicate, elements);
    }

    async waitUntilElementIsVisible(id: string) {
        const elementToWaitFor: WebElement = await this.getElementWithId(id);
        await this.driver.wait(until.elementIsVisible(elementToWaitFor), this.timeoutForCardRendering);
    }

    async waitUntilElementIsNotVisible(id: string) {
        const elementToWaitFor: WebElement = await this.getElementWithId(id);
        await this.driver.wait(until.elementIsNotVisible(elementToWaitFor), this.timeoutForCardRendering);
    }

    async getInput(inputId: string, className: string, container?: Container): Promise<WebElement> {
        const inputDiv: WebElement = await this.getRoot(container).findElement(By.id(inputId));
        return await inputDiv.findElement(By.className(className));
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

    async getElementWithId(id: string, container?: Container): Promise<WebElement> {
        return await this.getRoot(container).findElement(By.id(id));
    }

    async getCssPropertyValueForElement(element: WebElement, cssProperty: string): Promise<string> {
        return element.getCssValue(cssProperty);
    }

    /*
    async getCssPropertyValueForElementWithId(id: string, cssProperty: string): Promise<string> {
        const element: WebElement | undefined = await this.getElementWithId(id);

        return this.getCssPropertyValueForElement(element, cssProperty);
    }
    */

    async getElementsWithName(id: string, container?: Container): Promise<WebElement[]> {
        return await this.getRoot(container).findElements(By.name(id));
    }
}
