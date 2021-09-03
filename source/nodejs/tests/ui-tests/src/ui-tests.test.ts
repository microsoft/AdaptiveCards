// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Assert from "assert";
import * as Webdriver from "selenium-webdriver";
import * as TestUtils from "./testUtils";

describe("Mock function", function() {
    let driver: Webdriver.WebDriver;
    let testUtils: TestUtils.TestUtils;

    beforeAll(async() => {
        driver = new Webdriver.Builder().withCapabilities(Webdriver.Capabilities.edge()).build();
        await driver.get("http://127.0.0.1:8080/");

        testUtils = new TestUtils.TestUtils(driver);
    });

    afterAll(async() => {
        if (driver) {
            await driver.quit();
        }
    });

    test("Test ActivityUpdate submit", (async() => {
        await testUtils.goToTestCase("v1.0/ActivityUpdate");

        await testUtils.clickOnActionWithTitle("Set due date");

        await testUtils.setDateOnDateInput("dueDate", "02041993");
        await testUtils.setTextOnTextInput("comment", "A comment");

        await testUtils.clickOnActionWithTitle("OK");

        const dueDateRetrievedValue: string = await testUtils.getInputFor("dueDate");
        Assert.strictEqual("1993-02-04", dueDateRetrievedValue);

        const commentRetrievedValue: string = await testUtils.getInputFor("comment");
        Assert.strictEqual("A comment", commentRetrievedValue);
    }));

    test("Test TextInput get focus on invalid submit", (async() => {
        await testUtils.goToTestCase("v1.3/Input.Text.ErrorMessage");

        await testUtils.clickOnActionWithTitle("Submit");

        const firstInput: Webdriver.WebElement = await testUtils.getTextInput("id1");

        const firstInputId: string = await firstInput.getAttribute("id");
        const activeElementId: string = await driver.switchTo().activeElement().getAttribute("id");

        Assert.strictEqual(firstInputId, activeElementId);
    }));
});
