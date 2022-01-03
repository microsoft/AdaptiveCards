// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Assert from "assert";
import { assert } from "console";
import { util } from "prettier";
import { By, WebElement } from "selenium-webdriver";
import { Action, Carousel, InputDate, InputText } from "./card-element-utils";
import { TestUtils } from "./test-utils";

describe("Mock function", function() {
    let utils: TestUtils;

    // This is a constant value for the wait time between pressing an action and retrieving
    // the input value. Only use this if you see some test flakiness. Value is given in ms
    const delayForCarouselTimer: number = 6000;
    const timeOutValueForCarousel: number = 30000;
    const timeOutValueForSuddenJumpTest: number = 20000;

    // Timeout of 10 minutes for the dev server to start up in the CI jobs, the dev-server
    // usually takes between 1 to 2 minutes but we have no way to determine when the server
    // is ready to run tests. This issues is being tracked in issue #6716
    const timeoutForServerStartupInCIBuild: number = 600000;

    beforeAll(async() => {
        utils = TestUtils.getInstance();
        utils.initializeDriver();
    }, timeoutForServerStartupInCIBuild);

    afterAll(async() => {
        await utils.stopDriver();
    });

    test("Test ActivityUpdate submit", (async() => {
        await utils.goToTestCase("v1.0/ActivityUpdate");

        await utils.clickOnActionWithTitle("Set due date");

        let dueDateInput = await InputDate.getInputWithId("dueDate");
        await dueDateInput.setData("02041993");

        let commentInput = await InputText.getInputWithId("comment");
        await commentInput.setData("A comment");

        let okAction = await Action.getActionWithTitle("OK");
        await okAction.click();

        const dueDateRetrievedValue: string = await utils.getInputFor("dueDate");
        Assert.strictEqual(dueDateRetrievedValue, "1993-02-04");

        const commentRetrievedValue: string = await utils.getInputFor("comment");
        Assert.strictEqual(commentRetrievedValue, "A comment");
    }));

    test("Test TextInput get focus on invalid submit", (async() => {
        await utils.goToTestCase("v1.3/Input.Text.ErrorMessage");

        let commentInput = await InputText.getInputWithId("id1");

        let commentInputIsFocused = await commentInput.isFocused()

        Assert.strictEqual(commentInputIsFocused, false);

        let submitAction = await Action.getActionWithTitle("Submit");
        await submitAction.click();

        commentInputIsFocused = await commentInput.isFocused()

        Assert.strictEqual(commentInputIsFocused, true);
    }));

    test("Test interaction with Input.ChoiceSet", (async() => {
        await utils.goToTestCase("v1.3/Input.ChoiceSet.ErrorMessage");

        let compactChoiceSet = await utils.getElementWithId("requiredCompactId");
        let actualElement = await compactChoiceSet.findElement(By.className("ac-choiceSetInput-compact"));
        await actualElement.click();
        
        await (await actualElement.findElement(By.xpath(`//*[@aria-label='Option 1']`))).click();

        let expandedChoiceSet = await utils.getElementsWithName("requiredExpandedId");
        Assert.strictEqual(await expandedChoiceSet[0].getAttribute("value"), "1");
        Assert.strictEqual(await expandedChoiceSet[1].getAttribute("value"), "2");

        let multiselectChoiceSet = await utils.getElementsWithName("requiredMultiselectId");
        Assert.strictEqual(await multiselectChoiceSet[0].getAttribute("value"), "1");
        Assert.strictEqual(await multiselectChoiceSet[1].getAttribute("value"), "2");
    }));

    test("Test actions are rendered and active below carousel", (async() => {
        await utils.goToTestCase("v1.6/Carousel.HostConfig");

        let seeMoreAction = await Action.getActionWithTitle("See more");
        await seeMoreAction.click();

        const url: string = await utils.getInputFor("url");
        Assert.strictEqual(url, "https://adaptivecards.io");
    }));

    test("Test page limit is honoured", (async() => {
        await utils.goToTestCase("v1.6/Carousel.HostConfig");

        await utils.assertElementWithIdDoesNotExist("page10");
    }));

    test("Unsupported elements are not rendered", (async() => {
        await utils.goToTestCase("v1.6/Carousel.ForbiddenElements");

        await utils.assertElementWithIdDoesNotExist("id1");
        await utils.assertElementWithIdDoesNotExist("id2");
        await utils.assertElementWithIdDoesNotExist("id3");
        await utils.assertElementWithIdDoesNotExist("id4");
        await utils.assertElementWithIdDoesNotExist("id5");
        await utils.assertElementWithIdDoesNotExist("id6");
        await utils.assertElementWithIdDoesNotExist("id7");
    }));

    test("Verify left and right buttons in carousel work", (async() => {
        await utils.goToTestCase("v1.6/Carousel.ScenarioCards");

        let firstPageIsVisible = await Carousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, true);

        await Carousel.clickOnRightArrow();

        await utils.waitUntilElementIsCssVisible("theSecondCarouselPage", delayForCarouselTimer);

        let secondPageIsVisible = await Carousel.isPageVisible("theSecondCarouselPage");
        Assert.strictEqual(secondPageIsVisible, true);

        await Carousel.waitForAnimationsToEnd();
        await Carousel.clickOnLeftArrow();

        await utils.waitUntilElementIsCssVisible("firstCarouselPage");

        firstPageIsVisible = await Carousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, true);
    }), timeOutValueForSuddenJumpTest);

    test("Unsupported actions are not rendered", (async() => {
        await utils.goToTestCase("v1.6/Carousel.ForbiddenActions");

        let showCardAction = await Action.getActionWithTitle("Action.ShowCard");
        Assert.strictEqual(showCardAction.elementWasFound(), false);

        let toggleVisibilityAction = await Action.getActionWithTitle("Action.ToggleVisibility");
        Assert.strictEqual(toggleVisibilityAction.elementWasFound(), false);
    }));

    // Giving this test 7 seconds to run
    test("Test autoplay is disabled", (async() => {
        await utils.goToTestCase("v1.6/Carousel.ScenarioCards");

        let firstPageIsVisible = await Carousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, true);

        // Await for 5 seconds and verify no change happened
        await utils.delay(5000);

        firstPageIsVisible = await Carousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, true);
    }), 7000);

    // Giving this test 9 seconds to run
    test("Test autoplay is applied", (async() => {
        await utils.goToTestCase("v1.6/Carousel.ScenarioCards.Timer");

        let firstPageIsVisible = await Carousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, true);

        // Await for 5 seconds and verify the first page is now hidden
        await utils.waitUntilElementIsNotVisible("firstCarouselPage");

        firstPageIsVisible = await Carousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, false);

        let secondPageIsVisible = await Carousel.isPageVisible("theSecondCarouselPage");
        Assert.strictEqual(secondPageIsVisible, true);
    }), timeOutValueForCarousel);

    test("Test click on navigation does not cause sudden jump", (async() => {
        await utils.goToTestCase("v1.6/Carousel");

        let firstPageIsVisible = await Carousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, true);

        // wait for 2 pages to turn
        await utils.waitUntilElementIsCssVisible("last-carousel-page", delayForCarouselTimer * 2);

        firstPageIsVisible = await Carousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, false);

        let lastPageIsVisible = await Carousel.isPageVisible("last-carousel-page");
        Assert.strictEqual(lastPageIsVisible, true);

        // cause the page to go the 2nd page
        await Carousel.waitForAnimationsToEnd();
        await Carousel.clickOnLeftArrow();

        await utils.waitUntilElementIsCssVisible("theSecondCarouselPage");

        // make sure firstCarouselPage is hidden
        firstPageIsVisible = await Carousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, false);
    }), timeOutValueForSuddenJumpTest);

    test("Test rtl on carousel", (async() => {
        await utils.goToTestCase("v1.6/Carousel.rtl");

        for (const page of [["firstCarouselPage", "rtl"], ["secondCarouselPage", "ltr"], ["thirdCarouselPage", "rtl"]]){
            const pageDirection = await Carousel.getPageDirection(page[0])
            Assert.strictEqual(pageDirection, page[1]);
        }
        
    }), timeOutValueForCarousel);
});
