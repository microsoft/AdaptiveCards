// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as AdaptiveCards from "adaptivecards";
import * as Assert from "assert";
import * as Webdriver from "selenium-webdriver";

describe("Mock function", function() {
    let driver : Webdriver.WebDriver;

    beforeAll(async function() {
        driver = new Webdriver.Builder().withCapabilities(Webdriver.Capabilities.edge()).build();
        await driver.get("http://127.0.0.1:8080/");
    });

    afterAll(async function() {
        if (driver) {
            // driver.quit();
        }
    });

    test("Test case should work", async function() {
        Assert.equal(true, true);
    });
});
