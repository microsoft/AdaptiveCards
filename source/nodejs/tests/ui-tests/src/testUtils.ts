// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Webdriver from "selenium-webdriver";
import * as Assert from "assert";

export class TestUtils {
    driver: Webdriver.WebDriver;
    timeoutForCardRendering: number = 10000;

    constructor(driver: Webdriver.WebDriver) {
        this.driver = driver;
    }

    async goToTestCase(testCaseName: string): Promise<void> {
        const elementLinkText: Webdriver.WebElement = await this.driver.findElement(Webdriver.By.id(testCaseName));
        await elementLinkText.click();

        const renderedCardContainer: Webdriver.WebElement = await this.getElementWithId("renderedCardSpace");

        await this.driver.wait(Webdriver.until.elementIsVisible(renderedCardContainer), this.timeoutForCardRendering);
    }

    async tryGetActionWithTitle(actionTitle: string): Promise<Webdriver.WebElement | null> {
        const buttonList: Webdriver.WebElement[] = await this.driver.findElements(Webdriver.By.xpath(`//*[@aria-label='${actionTitle}']`));

        return (buttonList.length > 0) ? buttonList[0] : null;
    }

    async getActionWithTitle(actionTitle: string): Promise<Webdriver.WebElement> {
        const button: Webdriver.WebElement = await this.driver.findElement(Webdriver.By.xpath(`//*[@title='${actionTitle}']`));

        return button;
    }

    async clickOnActionWithTitle(actionTitle: string): Promise<void> {
        const button: Webdriver.WebElement = await this.getActionWithTitle(actionTitle);
        await button.click();
    }

    async getRetrievedInputs(): Promise<string> {
        const retrievedInputsDiv: Webdriver.WebElement = await this.driver.findElement(Webdriver.By.id("retrievedInputsDiv"));
        const retrievedInputsText: string = await retrievedInputsDiv.getText();

        return retrievedInputsText;
    }

    async getInputFor(inputId: string): Promise<string> {
        const retrievedInputsAsJsonString: string = await this.getRetrievedInputs();
        const retrievedInputs: any = JSON.parse(retrievedInputsAsJsonString);

        return retrievedInputs[inputId];
    }

    async getInput(inputId: string, className: string): Promise<Webdriver.WebElement> {
        const inputDiv: Webdriver.WebElement = await this.driver.findElement(Webdriver.By.id(inputId));
        const input = await inputDiv.findElement(Webdriver.By.className(className));

        return input;
    }

    async setValueOnInput(inputId: string, className: string, value: string) {
        const input: Webdriver.WebElement = await this.getInput(inputId, className);
        await input.click();
        await input.sendKeys(value);
    }

    async setDateOnDateInput(dateInputId: string, value: string): Promise<void> {
        await this.setValueOnInput(dateInputId, "ac-dateInput", value);
    }

    async setTextOnTextInput(textInputId: string, value: string): Promise<void> {
        await this.setValueOnInput(textInputId, "ac-textInput", value);
    }

    async getTextInput(textInputId: string): Promise<Webdriver.WebElement> {
        const textInput: Webdriver.WebElement = await this.getInput(textInputId, "ac-textInput");

        return textInput;
    }

    // Await for x miliseconds
    async delay(miliseconds: number): Promise<void> {
        return new Promise(res => setTimeout(res, miliseconds));
    }

    async assertElementWithIdDoesNotExist(id: string): Promise<void> {
        const elementList = await this.driver.findElements(Webdriver.By.id(id));
        Assert.strictEqual(0, elementList.length);
    }

    async getElementsWithId(id: string): Promise<Webdriver.WebElement[]> {
        return this.driver.findElements(Webdriver.By.id(id));
    }

    async getElementWithId(id: string): Promise<Webdriver.WebElement> {
        return this.driver.findElement(Webdriver.By.id(id));
    }

    async getCssPropertyValueForElement(element: Webdriver.WebElement, cssProperty: string): Promise<string> {
        return element.getCssValue(cssProperty);
    }

    async getCssPropertyValueForElementWithId(id: string, cssProperty: string): Promise<string> {
        const element: Webdriver.WebElement = await this.getElementWithId(id);

        return this.getCssPropertyValueForElement(element, cssProperty);
    }
}
