// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import { until, WebElement } from "selenium-webdriver";
import { TestUtils } from "./test-utils";
import { ACElement } from "./card-element-utils";

export class WaitUntil {

    static async customWait(timeoutMs: number, successFunction: Function, params: any) : Promise<void> 
    {
        let milisPassed: number = 0;

        while (milisPassed < timeoutMs) {
            const successFunctionResult = await successFunction(params);
            if (successFunctionResult === true)
            {
                break;
            }
            milisPassed += 100;
            await WaitUtils.waitFor(100);
        }
    }
}

export class WaitUtils {

    static timeoutForCardRendering: number = 10000;

    // Await for x miliseconds
    static async waitFor(miliseconds: number): Promise<void> {
        return new Promise(res => setTimeout(res, miliseconds));
    }

    static async waitUntilPredicateIsTrue(elements: ACElement[], successPredicate: Function, timeoutInMs?: number) {
        const timeOut = (timeoutInMs !== undefined) ? timeoutInMs : WaitUtils.timeoutForCardRendering;
        await WaitUntil.customWait(timeOut, successPredicate, elements);
    }

    static async waitUntilElementIsVisible(id: string) {
        const elementToWaitFor: WebElement = await TestUtils.getInstance().getElementWithId(id);
        await TestUtils.getInstance().driver.wait(until.elementIsVisible(elementToWaitFor), WaitUtils.timeoutForCardRendering);
    }

    static async waitUntilElementIsNotVisible(id: string) {
        const elementToWaitFor: WebElement = await TestUtils.getInstance().getElementWithId(id);
        await TestUtils.getInstance().driver.wait(until.elementIsNotVisible(elementToWaitFor), WaitUtils.timeoutForCardRendering);
    }

    static async waitUntilElementIsCssVisible(id: string, timeoutInMs?: number) {
        const elementsToWaitFor: WebElement[] = await TestUtils.getInstance().getElementsWithId(id);
        const timeOut = timeoutInMs !== undefined ? timeoutInMs : WaitUtils.timeoutForCardRendering;

        let successFunction = async (params: any) => {
            let elementIsVisible: boolean = false;

            for (let element of elementsToWaitFor)
            {
                let visibility = await TestUtils.getInstance().getCssPropertyValueForElement(element, "visibility");
                elementIsVisible = elementIsVisible || (visibility === "visible");
            }

            return elementIsVisible;
        };

        await WaitUntil.customWait(timeOut, successFunction, elementsToWaitFor);
    }
}