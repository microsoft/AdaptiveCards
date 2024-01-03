// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import { Builder, By, Capabilities, Locator, until, WebDriver, WebElement } from "selenium-webdriver";
import * as Assert from "assert";
import { WaitUntil, WaitUtils } from "./wait-utils";
import { ACCard, ACContainer } from "./card-element-utils";
import { ByExtended } from "./selenium-utils";

export class TestUtils {
    
    private _driver: WebDriver;
    private hideInputsButton: WebElement | undefined = undefined;
    private inputs: any = undefined;

    private static instance : TestUtils;

    private constructor() 
    {
        this._driver = new Builder().withCapabilities(Capabilities.edge()).build();
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
        if (TestUtils.instance == undefined) {
            TestUtils.instance = new TestUtils(); 
        }
        return TestUtils.instance;
    }

    get driver(): WebDriver {
        return this._driver;
    }

    async goToTestCase(testCaseName: string): Promise<ACCard> {
        const elementLinkText: WebElement = await this.driver.findElement(By.id(testCaseName));
        await elementLinkText.click();

        const renderedCardContainer: WebElement = await this.getElementWithId("renderedCardSpace");

        await this.driver.wait(until.elementIsVisible(renderedCardContainer), WaitUtils.timeoutForCardRendering);

        return await ACCard.getCard();
    }

    async getHideInputsButton(): Promise<WebElement> {
        if (this.hideInputsButton === undefined)
        {
            this.hideInputsButton = await this.getElementWithId("hideInputsBtn");
        }

        return this.hideInputsButton!;
    }

    async clearInputs(): Promise<void> {
        this.inputs = undefined;
        await this.hideInputsDiv();
    }

    async hideInputsDiv(): Promise<void> {
        const hideInputsButton = await this.getHideInputsButton(); 
        await hideInputsButton.click();
    }

    async getInputFor(inputId: string): Promise<string> {
        if (this.inputs === undefined) {
            await this.getRetrievedInputs();
        }

        return this.inputs[inputId];
    }

    async getUrlInRetrievedInputs(): Promise<string> {
        return await this.getInputFor("url");
    }

    async getRetrievedInputs(): Promise<void> {
        if (this.inputs === undefined) {
            const retrievedInputsDiv: WebElement = await this.getElementWithId("retrievedInputsDiv");

            let successFunction = async (params: any) => {
                let visibility = await TestUtils.getInstance().getCssPropertyValueForElement(retrievedInputsDiv, "visibility");
                return (visibility === "visible");
            };
    
            await WaitUntil.customWait(WaitUtils.timeoutForCardRendering, successFunction, retrievedInputsDiv);

            const retrievedInputs: string = await retrievedInputsDiv.getText();

            this.inputs = JSON.parse(retrievedInputs)
        }
    }

    getRoot(container?: ACContainer): WebElement | WebDriver {
        if (container !== undefined && container.elementWasFound()) {
            return container.underlyingElement!;
        } 
        else {
            return this.driver;
        }
    } 

    async tryGetActionWithTitle(actionTitle: string): Promise<WebElement | undefined> {
        const buttonList: WebElement[] = await this.driver.findElements(ByExtended.ariaLabel(actionTitle));
        return (buttonList.length > 0) ? buttonList[0] : undefined;
    }    

    async tryGetContainerWithAction(tooltip: string, container?: ACContainer): Promise<WebElement | undefined> {
        const containerList: WebElement[] = await this.getRoot(container).findElements(ByExtended.title(tooltip));
        return (containerList.length > 0) ? containerList[0] : undefined;
    }

    async getImageWithTitle(title: string, className: string, container?: ACContainer): Promise<WebElement | undefined> {
        return await this.getRoot(container).findElement(ByExtended.title(title));
    }

    async getActionWithTitle(actionTitle: string, container?: ACContainer): Promise<WebElement> {
        return await this.getRoot(container).findElement(ByExtended.title(actionTitle));
    }

    async getInputContainer(inputId: string, container?: ACContainer): Promise<WebElement> {
        return await this.getRoot(container).findElement(By.id(inputId));
    }

    async getInput(className: string, container: WebElement): Promise<WebElement> {
        return await container.findElement(By.className(className));
    }

    async getElementsWithClass(className: string, container?: ACContainer): Promise<WebElement[]> {
        return await this.getRoot(container).findElements(By.className(className));
    }

    async assertElementWithIdDoesNotExist(id: string): Promise<void> {
        const elementList = await this.getElementsWithId(id);
        Assert.strictEqual(elementList.length, 0);
    }

    async getElementsWithId(id: string): Promise<WebElement[]> {
        return this.driver.findElements(By.id(id));
    }

    async getElementWithId(id: string, container?: ACContainer): Promise<WebElement> {
        return await this.getRoot(container).findElement(By.id(id));
    }

    async getCssPropertyValueForElement(element: WebElement, cssProperty: string): Promise<string> {
        return element.getCssValue(cssProperty);
    }

    async getElementsWithName(id: string, container?: ACContainer): Promise<WebElement[]> {
        return await this.getRoot(container).findElements(By.name(id));
    }
}
