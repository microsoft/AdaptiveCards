// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp

import org.junit.rules.TestWatcher
import org.junit.runner.Description

public class TestWatchRule : TestWatcher() {

    protected override fun starting(description: Description) {
        print("Starting test run");
    }

    protected override fun succeeded(description: Description?) {
        super.succeeded(description)

        ScreenshotHelper().takeScreenshot(description, true)
    }

    protected override fun failed(e: Throwable?, description: Description?) {
        super.failed(e, description)

        ScreenshotHelper().takeScreenshot(description, false)
    }
}
