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
    const delayForCarouselTimer: number = 5500;
    const timeOutValueForCarousel: number = 9000;
    const timeOutValueForSuddenJumpTest: number = 20000;

    // Timeout of 10 minutes for the dev server to start up in the CI jobs, the dev-server
    // usually takes between 1 to 2 minutes but we have no way to determine when the server
    // is ready to run tests. This issues is being tracked in issue #6716
    const timeoutForServerStartupInCIBuild: number = 600000;

    beforeAll(async() => {
        driver = new Webdriver.Builder().withCapabilities(Webdriver.Capabilities.edge()).build();
        await driver.get("http://127.0.0.1:8080/");

        testUtils = new TestUtils.TestUtils(driver);
    }, timeoutForServerStartupInCIBuild);

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

        testUtils.delay(1000);

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

        let firstCarouselPageVisibility: string = await testUtils.getCssPropertyValueForElementWithId("firstCarouselPage", "visibility");
        Assert.strictEqual("visible", firstCarouselPageVisibility);

        const rightArrow = await testUtils.driver.findElement(Webdriver.By.className("ac-carousel-right"));
        await rightArrow.click();

        await testUtils.delay(delayForCarouselArrows);

        const secondCarouselPageVisibility: string =
            await testUtils.getCssPropertyValueForElementWithId("theSecondCarouselPage", "visibility");
        Assert.strictEqual("visible", secondCarouselPageVisibility);

        const leftArrow = await testUtils.driver.findElement(Webdriver.By.className("ac-carousel-left"));
        await leftArrow.click();

        await testUtils.delay(delayForCarouselArrows);

        firstCarouselPageVisibility = await testUtils.getCssPropertyValueForElementWithId("firstCarouselPage", "visibility");
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

        let firstCarouselPageVisibility: string = await testUtils.getCssPropertyValueForElementWithId("firstCarouselPage", "visibility");
        Assert.strictEqual("visible", firstCarouselPageVisibility);

        // Await for 5 seconds and verify no change happened
        await testUtils.delay(5000);

        firstCarouselPageVisibility = await testUtils.getCssPropertyValueForElementWithId("firstCarouselPage", "visibility");
        Assert.strictEqual("visible", firstCarouselPageVisibility);
    }), 7000);

    // Giving this test 9 seconds to run
    test("Test autoplay is applied", (async() => {
        await testUtils.goToTestCase("v1.6/Carousel.ScenarioCards.Timer");

        let firstCarouselPageVisibility: string = await testUtils.getCssPropertyValueForElementWithId("firstCarouselPage", "visibility");

        Assert.strictEqual("visible", firstCarouselPageVisibility);

        // Await for 5 seconds and verify the first page is now hidden
        await testUtils.delay(7000);

        firstCarouselPageVisibility = await testUtils.getCssPropertyValueForElementWithId("firstCarouselPage", "visibility");
        Assert.strictEqual("hidden", firstCarouselPageVisibility);

        const secondCarouselPageVisibility: string =
            await testUtils.getCssPropertyValueForElementWithId("theSecondCarouselPage", "visibility");
        Assert.strictEqual("visible", secondCarouselPageVisibility);
    }), timeOutValueForCarousel);

    test("Test click on navigation does not cause sudden jump", (async() => {
        await testUtils.goToTestCase("v1.6/Carousel");

        let firstCarouselPageVisibility: string = await testUtils.getCssPropertyValueForElementWithId("firstCarouselPage", "visibility");

        Assert.strictEqual("visible", firstCarouselPageVisibility);

        // wait for 2 pages to turn
        await testUtils.delay(delayForCarouselTimer * 2);

        firstCarouselPageVisibility = await testUtils.getCssPropertyValueForElementWithId("firstCarouselPage", "visibility");
        Assert.strictEqual("hidden", firstCarouselPageVisibility);

        // Due to how the swiper library is made, the first and last pages are duplicated, if we were to use the regular
        // getElementWithId method we would retrieve the duplicated slide, so we have to get the second element with that id

        const lastPages = await testUtils.getElementsWithId("last-carousel-page");
        Assert.strictEqual(lastPages.length, 2);

        const thirdCarouselPageVisibility: string =
            await testUtils.getCssPropertyValueForElement(lastPages[1], "visibility");
        Assert.strictEqual("visible", thirdCarouselPageVisibility);

        // cause the page to go the 2nd page
        const leftArrow = await testUtils.driver.findElement(Webdriver.By.className("ac-carousel-left"));
        await leftArrow.click();
        await testUtils.delay(delayForCarouselArrows);

        // make sure firstCarouselPage is hidden
        firstCarouselPageVisibility = await testUtils.getCssPropertyValueForElementWithId("firstCarouselPage", "visibility");
        Assert.strictEqual("hidden", firstCarouselPageVisibility);
    }), timeOutValueForSuddenJumpTest);

    test("Test rtl on carousel", (async() => {
        await testUtils.goToTestCase("v1.6/Carousel.rtl");

        const firstPage = await testUtils.getElementWithId("firstCarouselPage");
        const firstPageContainer = firstPage.findElement(Webdriver.By.xpath("./*"));
        const firstPageDirection: string = await firstPageContainer.getAttribute("dir");
        Assert.strictEqual(firstPageDirection, "rtl");

        const secondPage = await testUtils.getElementWithId("secondCarouselPage");
        const secondPageContainer = secondPage.findElement(Webdriver.By.xpath("./*"));
        const secondPageDirection: string = await secondPageContainer.getAttribute("dir");
        Assert.strictEqual(secondPageDirection, "ltr");

        const thirdPage = await testUtils.getElementWithId("thirdCarouselPage");
        const thirdPageContainer = thirdPage.findElement(Webdriver.By.xpath("./*"));
        const thirdPageDirection: string = await thirdPageContainer.getAttribute("dir");
        Assert.strictEqual(thirdPageDirection, "rtl");
    }), timeOutValueForCarousel);
});
