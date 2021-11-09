// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Assert from "assert";
import { assert } from "console";
import * as Webdriver from "selenium-webdriver";
import * as TestUtils from "./testUtils";

describe("Mock function", function() {
    let driver: Webdriver.WebDriver;
    let testUtils: TestUtils.TestUtils;

    // This is a constant value for the wait time between pressing an action and retrieving
    // the input value. Only use this if you see some test flakiness. Value is given in ms
    const delayForInputRetrieval: number = 500;
    const delayForCarouselArrows: number = 1000;

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

    test("Test actions are rendered and active below carousel", (async() => {
        await testUtils.goToTestCase("v1.6/Carousel.HostConfig");

        await testUtils.clickOnActionWithTitle("See more");

        await testUtils.delay(delayForInputRetrieval);

        const url: string = await testUtils.getInputFor("url");
        Assert.strictEqual("https://adaptivecards.io", url);
    }));

    test("Test page limit is honoured", (async() => {
        await testUtils.goToTestCase("v1.6/Carousel.HostConfig");

        await testUtils.assertElementWithIdDoesNotExist("page10");
    }));

    test("Unsupported elements are not rendered", (async() => {
        await testUtils.goToTestCase("v1.6/Carousel.ForbiddenElements");

        await testUtils.assertElementWithIdDoesNotExist("id1");
        await testUtils.assertElementWithIdDoesNotExist("id2");
        await testUtils.assertElementWithIdDoesNotExist("id3");
        await testUtils.assertElementWithIdDoesNotExist("id4");
        await testUtils.assertElementWithIdDoesNotExist("id5");
        await testUtils.assertElementWithIdDoesNotExist("id6");
        await testUtils.assertElementWithIdDoesNotExist("id7");
    }));

    test("Verify left and right buttons in carousel work", (async() => {
        await testUtils.goToTestCase("v1.6/Carousel.ScenarioCards");

        let firstCarouselPage = await testUtils.driver.findElement(Webdriver.By.id("firstCarouselPage"));
        let firstCarouselPageVisibility = await firstCarouselPage.getCssValue("visibility");

        Assert.strictEqual("visible", firstCarouselPageVisibility);

        const rightArrow = await testUtils.driver.findElement(Webdriver.By.className("ac-carousel-right"));
        await rightArrow.click();

        await testUtils.delay(delayForCarouselArrows);

        const secondCarouselPage = await testUtils.driver.findElement(Webdriver.By.id("theSecondCarouselPage"));
        const secondCarouselPageVisibility = await secondCarouselPage.getCssValue("visibility");

        Assert.strictEqual("visible", secondCarouselPageVisibility);

        const leftArrow = await testUtils.driver.findElement(Webdriver.By.className("ac-carousel-left"));
        await leftArrow.click();

        await testUtils.delay(delayForCarouselArrows);

        firstCarouselPage = await testUtils.driver.findElement(Webdriver.By.id("firstCarouselPage"));
        firstCarouselPageVisibility = await firstCarouselPage.getCssValue("visibility");

        Assert.strictEqual("visible", firstCarouselPageVisibility);
    }));

    test("Unsupported actions are not rendered", (async() => {
        await testUtils.goToTestCase("v1.6/Carousel.ForbiddenActions");

        const showCardAction = await testUtils.tryGetActionWithTitle("Action.ShowCard");
        Assert.strictEqual(null, showCardAction);

        const toggleVisibilityAction = await testUtils.tryGetActionWithTitle("Action.ToggleVisibility");
        Assert.strictEqual(null, toggleVisibilityAction);
    }));

    // Giving this test 7 seconds to run
    test("Test autoplay is disabled", (async() => {
        await testUtils.goToTestCase("v1.6/Carousel.ScenarioCards");

        let firstCarouselPage = await testUtils.driver.findElement(Webdriver.By.id("firstCarouselPage"));
        let firstCarouselPageVisibility = await firstCarouselPage.getCssValue("visibility");

        Assert.strictEqual("visible", firstCarouselPageVisibility);

        // Await for 5 seconds and verify no change happened
        await testUtils.delay(5000);

        firstCarouselPage = await testUtils.driver.findElement(Webdriver.By.id("firstCarouselPage"));
        firstCarouselPageVisibility = await firstCarouselPage.getCssValue("visibility");

        Assert.strictEqual("visible", firstCarouselPageVisibility);
    }), 7000);

    // Giving this test 9 seconds to run
    test("Test autoplay is applied", (async() => {
        await testUtils.goToTestCase("v1.6/Carousel.ScenarioCards.Timer");

        let firstCarouselPage = await testUtils.driver.findElement(Webdriver.By.id("firstCarouselPage"));
        let firstCarouselPageVisibility = await firstCarouselPage.getCssValue("visibility");

        Assert.strictEqual("visible", firstCarouselPageVisibility);

        // Await for 5 seconds and verify the first page is now hidden
        await testUtils.delay(7000);

        firstCarouselPage = await testUtils.driver.findElement(Webdriver.By.id("firstCarouselPage"));
        firstCarouselPageVisibility = await firstCarouselPage.getCssValue("visibility");
        Assert.strictEqual("hidden", firstCarouselPageVisibility);

        const secondCarouselPage = await testUtils.driver.findElement(Webdriver.By.id("theSecondCarouselPage"));
        const secondCarouselPageVisibility = await secondCarouselPage.getCssValue("visibility");

        Assert.strictEqual("visible", secondCarouselPageVisibility);
    }), 9000);
});
