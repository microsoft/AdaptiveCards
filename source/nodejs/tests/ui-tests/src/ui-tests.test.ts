// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Assert from "assert";
import * as Webdriver from "selenium-webdriver";
import * as TestUtils from "./testUtils";

describe("Mock function", function() {
    let driver: Webdriver.WebDriver;
    let testUtils: TestUtils.TestUtils;

    beforeAll(async function() {
        driver = new Webdriver.Builder().withCapabilities(Webdriver.Capabilities.edge()).build();
        await driver.get("http://127.0.0.1:8080/");

        testUtils = new TestUtils.TestUtils(driver);
    });

    afterAll(async function() {
        if (driver) {
            // driver.quit();
        }
    });

    test("Test case should work", async function() {
        Assert.strictEqual(true, true);
    });

    test("Test ActivityUpdate submit", async function() {
        const elementLinkText: Webdriver.WebElement = await driver.findElement(Webdriver.By.id("v1.0/ActivityUpdate"));
        await elementLinkText.click();

        const dueDateButton: Webdriver.WebElement = await driver.findElement(Webdriver.By.xpath("//*[@aria-label='Set due date']"));
        await dueDateButton.click();

        const dueDateInputDiv: Webdriver.WebElement = await driver.findElement(Webdriver.By.id("dueDate"));
        const dueDateInput = await dueDateInputDiv.findElement(Webdriver.By.className("ac-dateInput"));
        await dueDateInput.click();
        await dueDateInput.sendKeys("02041993");

        const commentInputDiv: Webdriver.WebElement = await driver.findElement(Webdriver.By.id("comment"));
        const commentInput = await commentInputDiv.findElement(Webdriver.By.className("ac-textInput"));
        await commentInput.click();
        await commentInput.sendKeys("A comment");

        const okButton: Webdriver.WebElement = await driver.findElement(Webdriver.By.xpath("//*[@aria-label='OK']"));
        await okButton.click();

        const dueDateRetrievedValue: string = await testUtils.getInputFor("dueDate");
        Assert.strictEqual("1993-02-04", dueDateRetrievedValue);

        const commentRetrievedValue: string = await testUtils.getInputFor("comment");
        Assert.strictEqual("A comment", commentRetrievedValue);
    });
});
