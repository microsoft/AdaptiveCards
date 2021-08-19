// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Webdriver from "selenium-webdriver";

export class TestUtils {
    driver: Webdriver.WebDriver;

    constructor(driver: Webdriver.WebDriver) {
        this.driver = driver;
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
