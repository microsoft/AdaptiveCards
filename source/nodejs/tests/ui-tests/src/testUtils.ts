// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Webdriver from "selenium-webdriver";

export class TestUtils {
    driver: Webdriver.WebDriver;

    constructor(driver: Webdriver.WebDriver) {
        this.driver = driver;
    }

    async goToTestCase(testCaseName: string): Promise<void> {
        const elementLinkText: Webdriver.WebElement = await this.driver.findElement(Webdriver.By.id(testCaseName));
        await elementLinkText.click();
    }

    async getActionWithTitle(actionTitle: string): Promise<Webdriver.WebElement> {
        const button: Webdriver.WebElement = await this.driver.findElement(Webdriver.By.xpath("//*[@aria-label='" + actionTitle + "']"));

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
}
