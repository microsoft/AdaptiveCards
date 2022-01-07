// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Assert from "assert";
import { ACAction, ACCarousel, ACColumn, ACColumnSet, ACContainer, ACInputChoiceSet, ACInputDate, ACInputNumber, ACInputText, ACInputTime, ACInputToggle, ACImage, ACElement } from "./card-element-utils";
import { TestUtils } from "./test-utils";
import { WaitUtils } from "./wait-utils";

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

        await ACAction.clickOnActionWithTitle("Set due date");

        let dueDateInput = await ACInputDate.getInputWithId("dueDate");
        await dueDateInput.setData("02041993");

        let commentInput = await ACInputText.getInputWithId("comment");
        await commentInput.setData("A comment");

        await ACAction.clickOnActionWithTitle("OK");

        const dueDateRetrievedValue: string = await utils.getInputFor("dueDate");
        Assert.strictEqual(dueDateRetrievedValue, "1993-02-04");

        const commentRetrievedValue: string = await utils.getInputFor("comment");
        Assert.strictEqual(commentRetrievedValue, "A comment");
    }));

    test("Test TextInput get focus on invalid submit", (async() => {
        await utils.goToTestCase("v1.3/Input.Text.ErrorMessage");

        let commentInput = await ACInputText.getInputWithId("id1");

        let commentInputIsFocused = await commentInput.isFocused()

        Assert.strictEqual(commentInputIsFocused, false);

        await ACAction.clickOnActionWithTitle("Submit");

        commentInputIsFocused = await commentInput.isFocused()

        Assert.strictEqual(commentInputIsFocused, true);
    }));

    test("Test interaction with Input.Number", (async() => {
        await utils.goToTestCase("v1.3/Input.Number.ErrorMessage");

        let input1 = await ACInputNumber.getInputWithId("input1");
        await input1.setData("1");

        let input2 = await ACInputNumber.getInputWithId("input2");
        await input2.setData("5");

        let input3 = await ACInputNumber.getInputWithId("input3");
        await input3.setData("10");

        let input4 = await ACInputNumber.getInputWithId("input4");
        await input4.setData("50");

        await ACAction.clickOnActionWithTitle("Submit");

        const input1Value: string = await utils.getInputFor("input1");
        Assert.strictEqual(input1Value, "1");

        const input2Value: string = await utils.getInputFor("input2");
        Assert.strictEqual(input2Value, "5");

        const input3Value: string = await utils.getInputFor("input3");
        Assert.strictEqual(input3Value, "10");

        const input4Value: string = await utils.getInputFor("input4");
        Assert.strictEqual(input4Value, "50");
    }));

    test("Test interaction with Input.ChoiceSet", (async() => {
        await utils.goToTestCase("v1.3/Input.ChoiceSet.ErrorMessage");

        let compactChoiceSet = await ACInputChoiceSet.getInputWithId("requiredCompactId", false, false);
        await compactChoiceSet.setData("Option 1");
        
        let expandedChoiceSet = await ACInputChoiceSet.getInputWithId("requiredExpandedId", true, false);
        await expandedChoiceSet.setData("Option 2");

        let multiselectChoiceSet = await ACInputChoiceSet.getInputWithId("requiredMultiselectId", true, true);
        await multiselectChoiceSet.setData("Option 1,Option 2");

        await ACAction.clickOnActionWithTitle("OK");

        const compactValue: string = await utils.getInputFor("requiredCompactId");
        Assert.strictEqual(compactValue, "1");

        const expandedValue: string = await utils.getInputFor("requiredExpandedId");
        Assert.strictEqual(expandedValue, "2");

        const multiselectValue: string = await utils.getInputFor("requiredMultiselectId");
        Assert.strictEqual(multiselectValue, "1,2");
    }));

    test("Test interaction with Input.Time", (async() => {
        await utils.goToTestCase("v1.3/Input.Time.ErrorMessage");

        let dueDateInput = await ACInputTime.getInputWithId("input1");
        await dueDateInput.setData("0109AM");

        let commentInput = await ACInputTime.getInputWithId("input4");
        await commentInput.setData("0230PM");

        await ACAction.clickOnActionWithTitle("OK");

        const dueDateRetrievedValue: string = await utils.getInputFor("input1");
        Assert.strictEqual(dueDateRetrievedValue, "01:09");

        const commentRetrievedValue: string = await utils.getInputFor("input4");
        Assert.strictEqual(commentRetrievedValue, "14:30");
    }));

    test("Test interaction with Input.Toggle", (async() => {
        await utils.goToTestCase("v1.3/Input.Toggle.ErrorMessage");

        let toggleInput = await ACInputToggle.getInputWithId("input2");
        await toggleInput.setData("set");

        await ACAction.clickOnActionWithTitle("OK");

        const dueDateRetrievedValue: string = await utils.getInputFor("input2");
        Assert.strictEqual(dueDateRetrievedValue, "true");
    }));

    test("Action.ShowCard: Test hidden card is shown", (async() => {
        await utils.goToTestCase("v1.0/Action.ShowCard");

        await ACAction.clickOnActionWithTitle("Action.ShowCard");

        const neatAction: ACAction = await ACAction.getActionWithTitle("Neat!");
        const neatActionIsVisible = async (params: any) => {
            let elements = params as ACElement[];
            return (await elements[0].elementIsVisible()) || (await elements[0].elementIsCssVisible());
        };

        await WaitUtils.waitUntilPredicateIsTrue([neatAction], neatActionIsVisible);

        await neatAction.click();

        const neatValue: string = await utils.getInputFor("neat");
        Assert.strictEqual(neatValue, "true");
    }));

    test("Image: Test select action can be clicked", (async() => {
        await utils.goToTestCase("v1.0/Image.SelectAction");

        let image = await ACImage.getImage("cool link");
        await image.click();
        
        const imageUrl: string = await utils.getInputFor("url");
        Assert.strictEqual(imageUrl, "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    }));

    test("Column: Test select action can be clicked", (async() => {
        await utils.goToTestCase("v1.0/Column.SelectAction");

        let firstColumn = await ACColumn.getContainerWithAction("cool link");
        await firstColumn.click();
        
        const firstColumnUrl: string = await utils.getInputFor("url");
        Assert.strictEqual(firstColumnUrl, "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    }));

    test("ColumnSet: Test select action can be clicked", (async() => {
        await utils.goToTestCase("v1.0/ColumnSet.SelectAction");

        let secondColumnSet = await ACColumnSet.getContainerWithAction("Remodel your kitchen with our new cabinet styles!");
        await secondColumnSet.click();
        
        const secondColumnSetUrl: string = await utils.getInputFor("url");
        Assert.strictEqual(secondColumnSetUrl, "https://www.AdaptiveCards.io");
    }));

    test("Container: Test select action can be clicked", (async() => {
        await utils.goToTestCase("v1.0/Container.SelectAction");

        let submitContainer = await ACContainer.getContainerWithAction("Submit action");
        await submitContainer.click();
        
        const submitActionInfo: string = await utils.getInputFor("info");
        Assert.strictEqual(submitActionInfo, "My submit action data");

        let emphasisContainer = await ACContainer.getContainerWithAction("Go to a different url");
        await emphasisContainer.click();
        
        const emphasisContainerUrl: string = await utils.getInputFor("url");
        Assert.strictEqual(emphasisContainerUrl, "https://msn.com");
    }));    

    test("Carousel: Test actions are rendered and active", (async() => {
        await utils.goToTestCase("v1.6/Carousel.HostConfig");

        await ACAction.clickOnActionWithTitle("See more");

        const url: string = await utils.getInputFor("url");
        Assert.strictEqual(url, "https://adaptivecards.io");
    }));

    test("Carousel: Test page limit is honoured", (async() => {
        await utils.goToTestCase("v1.6/Carousel.HostConfig");

        await utils.assertElementWithIdDoesNotExist("page10");
    }));

    test("Carousel: Unsupported elements are not rendered", (async() => {
        await utils.goToTestCase("v1.6/Carousel.ForbiddenElements");

        await utils.assertElementWithIdDoesNotExist("id1");
        await utils.assertElementWithIdDoesNotExist("id2");
        await utils.assertElementWithIdDoesNotExist("id3");
        await utils.assertElementWithIdDoesNotExist("id4");
        await utils.assertElementWithIdDoesNotExist("id5");
        await utils.assertElementWithIdDoesNotExist("id6");
        await utils.assertElementWithIdDoesNotExist("id7");
    }));

    test("Carousel: Verify left and right buttons work", (async() => {
        await utils.goToTestCase("v1.6/Carousel.ScenarioCards");

        let firstPageIsVisible = await ACCarousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, true);

        await ACCarousel.clickOnRightArrow();

        await WaitUtils.waitUntilElementIsCssVisible("theSecondCarouselPage", delayForCarouselTimer);

        let secondPageIsVisible = await ACCarousel.isPageVisible("theSecondCarouselPage");
        Assert.strictEqual(secondPageIsVisible, true);

        await ACCarousel.waitForAnimationsToEnd();
        await ACCarousel.clickOnLeftArrow();

        await WaitUtils.waitUntilElementIsCssVisible("firstCarouselPage");

        firstPageIsVisible = await ACCarousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, true);
    }), timeOutValueForSuddenJumpTest);

    test("Carousel: Unsupported actions are not rendered", (async() => {
        await utils.goToTestCase("v1.6/Carousel.ForbiddenActions");

        let showCardAction = await ACAction.getActionWithTitle("Action.ShowCard");
        Assert.strictEqual(showCardAction.elementWasFound(), false);

        let toggleVisibilityAction = await ACAction.getActionWithTitle("Action.ToggleVisibility");
        Assert.strictEqual(toggleVisibilityAction.elementWasFound(), false);
    }));

    // Giving this test 7 seconds to run
    test("Carousel: Test autoplay is disabled", (async() => {
        await utils.goToTestCase("v1.6/Carousel.ScenarioCards");

        let firstPageIsVisible = await ACCarousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, true);

        // Await for 5 seconds and verify no change happened
        await WaitUtils.waitFor(5000);

        firstPageIsVisible = await ACCarousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, true);
    }), 7000);

    // Giving this test 9 seconds to run
    test("Carousel: Test autoplay is applied", (async() => {
        await utils.goToTestCase("v1.6/Carousel.ScenarioCards.Timer");

        let firstPageIsVisible = await ACCarousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, true);

        // Await for 5 seconds and verify the first page is now hidden
        await WaitUtils.waitUntilElementIsNotVisible("firstCarouselPage");

        firstPageIsVisible = await ACCarousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, false);

        let secondPageIsVisible = await ACCarousel.isPageVisible("theSecondCarouselPage");
        Assert.strictEqual(secondPageIsVisible, true);
    }), timeOutValueForCarousel);

    test("Carousel: Test click on navigation does not cause sudden jump", (async() => {
        await utils.goToTestCase("v1.6/Carousel");

        let firstPageIsVisible = await ACCarousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, true);

        // wait for 2 pages to turn
        await WaitUtils.waitUntilElementIsCssVisible("last-carousel-page", delayForCarouselTimer * 2);

        firstPageIsVisible = await ACCarousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, false);

        let lastPageIsVisible = await ACCarousel.isPageVisible("last-carousel-page");
        Assert.strictEqual(lastPageIsVisible, true);

        // cause the page to go the 2nd page
        await ACCarousel.waitForAnimationsToEnd();
        await ACCarousel.clickOnLeftArrow();

        await WaitUtils.waitUntilElementIsCssVisible("theSecondCarouselPage");

        // make sure firstCarouselPage is hidden
        firstPageIsVisible = await ACCarousel.isPageVisible("firstCarouselPage");
        Assert.strictEqual(firstPageIsVisible, false);
    }), timeOutValueForSuddenJumpTest);

    test("Carousel: Test rtl", (async() => {
        await utils.goToTestCase("v1.6/Carousel.rtl");

        for (const page of [["firstCarouselPage", "rtl"], ["secondCarouselPage", "ltr"], ["thirdCarouselPage", "rtl"]]){
            const pageDirection = await ACCarousel.getPageDirection(page[0])
            Assert.strictEqual(pageDirection, page[1]);
        }
        
    }), timeOutValueForCarousel);
});
