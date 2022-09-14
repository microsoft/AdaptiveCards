// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Assert from "assert";
import { ACAction, ACColumn, ACColumnSet, ACContainer, ACInputChoiceSet, ACInputDate, ACInputNumber, ACInputText, ACInputTime, ACInputToggle, ACImage, ACElement } from "./card-element-utils";
import { TestUtils } from "./test-utils";
import { WaitUtils } from "./wait-utils";

describe("Mock function", function() {
    let utils: TestUtils;

    // This is a constant value for the wait time between pressing an action and retrieving
    // the input value. Only use this if you see some test flakiness. Value is given in ms
    const timeOutValueForSuddenJumpTest: number = 20000;

    // Timeout of 10 minutes for the dev server to start up in the CI jobs, the dev-server
    // usually takes between 1 to 2 minutes but we have no way to determine when the server
    // is ready to run tests. This issues is being tracked in issue #6716
    const timeoutForServerStartupInCIBuild: number = 600000;

    beforeAll(async() => {
        utils = TestUtils.getInstance();
        await utils.initializeDriver();
    }, timeoutForServerStartupInCIBuild);

    afterAll(async() => {
        await utils.stopDriver();
    });

    test("Test ActivityUpdate submit", (async() => {
        await utils.goToTestCase("v1.0/ActivityUpdate");

        await ACAction.clickOnActionWithTitle("Set due date");

        let dueDateInput = await ACInputDate.getInputWithId("dueDate");
        await dueDateInput.setDate(1993, 2, 4);

        let commentInput = await ACInputText.getInputWithId("comment");
        await commentInput.setData("A comment");

        await ACAction.clickOnActionWithTitle("OK");

        Assert.strictEqual(await utils.getInputFor("dueDate"), "1993-02-04");
        Assert.strictEqual(await utils.getInputFor("comment"), "A comment");
    }));

    test("Test TextInput get focus on invalid submit", (async() => {
        await utils.goToTestCase("v1.3/Input.Text.ErrorMessage");

        const commentInput = await ACInputText.getInputWithId("id1");

        Assert.strictEqual(await commentInput.getLabel(), "Required Input.Text *");
        Assert.strictEqual(await commentInput.isRequired(), true);
        Assert.strictEqual(await commentInput.getErrorMessage(), undefined);
        Assert.strictEqual(await commentInput.isFocused(), false);

        await ACAction.clickOnActionWithTitle("Submit");

        Assert.strictEqual(await commentInput.getErrorMessage(), "This is a required input");
        Assert.strictEqual(await commentInput.isFocused(), true);
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

        Assert.strictEqual(await utils.getInputFor("input1"), "1");
        Assert.strictEqual(await utils.getInputFor("input2"), "5");
        Assert.strictEqual(await utils.getInputFor("input3"), "10");
        Assert.strictEqual(await utils.getInputFor("input4"), "50");
    }));

    test("Input.ChoiceSet: Test input interaction", (async() => {
        await utils.goToTestCase("v1.3/Input.ChoiceSet.ErrorMessage");

        let compactChoiceSet = await ACInputChoiceSet.getInputWithId("requiredCompactId", false, false);
        await compactChoiceSet.setData("Option 1");
        
        let expandedChoiceSet = await ACInputChoiceSet.getInputWithId("requiredExpandedId", true, false);
        await expandedChoiceSet.setData("Option 2");

        let multiselectChoiceSet = await ACInputChoiceSet.getInputWithId("requiredMultiselectId", true, true);
        await multiselectChoiceSet.setData("Option 1,Option 2");

        await ACAction.clickOnActionWithTitle("OK");

        Assert.strictEqual(await utils.getInputFor("requiredCompactId"), "1");
        Assert.strictEqual(await utils.getInputFor("requiredExpandedId"), "2");
        Assert.strictEqual(await utils.getInputFor("requiredMultiselectId"), "1,2");
    }));

    test("Input.ChoiceSet: Test compact required validation", (async() => {
        await utils.goToTestCase("v1.3/Input.ChoiceSet.ErrorMessage");

        const compactChoiceSet = await ACInputChoiceSet.getInputWithId("requiredCompactId", false, false);
        Assert.strictEqual(await compactChoiceSet.getLabel(), "Required Input.ChoiceSet label (compact) *");
        Assert.strictEqual(await compactChoiceSet.isRequired(), true);
        Assert.strictEqual(await compactChoiceSet.getErrorMessage(), undefined);

        await ACAction.clickOnActionWithTitle("OK");

        Assert.strictEqual(await compactChoiceSet.validationFailed(), true);
        Assert.strictEqual(await compactChoiceSet.getErrorMessage(), "This is a required input");
    }));

    test("Input.ChoiceSet: Test expanded required validation", (async() => {
        await utils.goToTestCase("v1.3/Input.ChoiceSet.ErrorMessage");

        const expandedChoiceSet = await ACInputChoiceSet.getInputWithId("requiredExpandedId", true, false);
        Assert.strictEqual(await expandedChoiceSet.getLabel(), "Required Input.ChoiceSet label (expanded) *");
        Assert.strictEqual(await expandedChoiceSet.isRequired(), true);
        Assert.strictEqual(await expandedChoiceSet.getErrorMessage(), undefined);

        await ACAction.clickOnActionWithTitle("OK");

        Assert.strictEqual(await expandedChoiceSet.validationFailed(), true);
        Assert.strictEqual(await expandedChoiceSet.getErrorMessage(), "This is a required input");
    }));

    test("Input.ChoiceSet: Test multiselect required validation", (async() => {
        await utils.goToTestCase("v1.3/Input.ChoiceSet.ErrorMessage");

        const multiselectChoiceSet = await ACInputChoiceSet.getInputWithId("requiredMultiselectId", true, true);
        Assert.strictEqual(await multiselectChoiceSet.getLabel(), "Required Input.ChoiceSet label (expanded, multiselect) *");
        Assert.strictEqual(await multiselectChoiceSet.isRequired(), true);
        Assert.strictEqual(await multiselectChoiceSet.getErrorMessage(), undefined);

        await ACAction.clickOnActionWithTitle("OK");

        Assert.strictEqual(await multiselectChoiceSet.validationFailed(), true);
        Assert.strictEqual(await multiselectChoiceSet.getErrorMessage(), "This is a required input");
    }));

    test("Test interaction with Input.Time", (async() => {
        await utils.goToTestCase("v1.3/Input.Time.ErrorMessage");

        let timeInput1 = await ACInputTime.getInputWithId("input1");
        await timeInput1.setTime(1, 9);

        let timeInput4 = await ACInputTime.getInputWithId("input4");
        await timeInput4.setTime(14, 30);

        await ACAction.clickOnActionWithTitle("OK");

        Assert.strictEqual(await utils.getInputFor("input1"), "01:09");
        Assert.strictEqual(await utils.getInputFor("input4"), "14:30");
    }));

    test("Test interaction with Input.Toggle", (async() => {
        await utils.goToTestCase("v1.3/Input.Toggle.ErrorMessage");

        let toggleInput = await ACInputToggle.getInputWithId("input2");
        await toggleInput.set();

        await ACAction.clickOnActionWithTitle("OK");

        Assert.strictEqual(await utils.getInputFor("input2"), "true");
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

        Assert.strictEqual(await utils.getInputFor("neat"), "true");
    }));

    test("Image: Test select action can be clicked", (async() => {
        await utils.goToTestCase("v1.0/Image.SelectAction");

        let image = await ACImage.getImage("cool link");
        await image.click();
        
        Assert.strictEqual(await utils.getUrlInRetrievedInputs(), "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    }));

    test("Column: Test select action can be clicked", (async() => {
        await utils.goToTestCase("v1.0/Column.SelectAction");

        let firstColumn = await ACColumn.getContainerWithAction("cool link");
        await firstColumn.click();
        
        Assert.strictEqual(await utils.getUrlInRetrievedInputs(), "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    }));

    test("ColumnSet: Test select action can be clicked", (async() => {
        await utils.goToTestCase("v1.0/ColumnSet.SelectAction");

        let secondColumnSet = await ACColumnSet.getContainerWithAction("Remodel your kitchen with our new cabinet styles!");
        await secondColumnSet.click();
        
        Assert.strictEqual(await utils.getUrlInRetrievedInputs(), "https://www.AdaptiveCards.io");
    }));

    test("Container: Test select action can be clicked", (async() => {
        await utils.goToTestCase("v1.0/Container.SelectAction");

        let submitContainer = await ACContainer.getContainerWithAction("Submit action");
        await submitContainer.click();
        
        Assert.strictEqual(await utils.getInputFor("info"), "My submit action data");

        let emphasisContainer = await ACContainer.getContainerWithAction("Go to a different url");
        await emphasisContainer.click();
        
        Assert.strictEqual(await utils.getUrlInRetrievedInputs(), "https://msn.com");
    }));    

});
