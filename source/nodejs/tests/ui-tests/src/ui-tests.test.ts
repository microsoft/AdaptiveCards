// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as AdaptiveCards from "adaptivecards";
import * as Assert from "assert";
// import * as Test from "selenium-webdriver/testing";
import * as Webdriver from "selenium-webdriver";


describe("Mock function", function() {
    it("Test case should work", function() {
        Assert.equal(true, true);
    });
});

/*
describe("Verify setup with Google Search", function() {
    it("test case should work", function() {
        const driver = new Webdriver.Builder().withCapabilities(Webdriver.Capabilities.edge()).build();
        driver.get("http://www.google.com");
        const searchBox = driver.findElement(Webdriver.By.name("q"));
        searchBox.sendKeys("selenium node automation");
        searchBox.getAttribute("value").then(function(value) {
            Assert.equal(value, "selenium node automation");
        });
        // driver.quit();
    });
});
*/
