// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp

import android.graphics.Bitmap
import androidx.test.runner.screenshot.ScreenCapture
import androidx.test.runner.screenshot.ScreenCaptureProcessor
import androidx.test.runner.screenshot.Screenshot
import org.junit.runner.Description

class ScreenshotHelper() {
    private var mIndex: Int = 0
    private var mTestName: String = ""

    // Constructor to be used for taking multiple screenshots in a single test
    constructor(testName: String) : this() {
        mTestName = testName
    }

    public fun takeScreenshot() {
        ++mIndex
        saveScreenshotAs("$mTestName-$mIndex")
    }

    // Function to be called from the succeeded or failed methods from a TestWatcher implementation
    public fun takeScreenshot(description: Description?, success: Boolean) {
        var suffix = "_success"
        if (!success) {
            suffix = "_fail";
        }

        val testName: String = description!!.methodName + suffix
        saveScreenshotAs(testName);
    }

    private fun saveScreenshotAs(filename: String) {
        val format: Bitmap.CompressFormat = Bitmap.CompressFormat.JPEG

        val capture: ScreenCapture = Screenshot.capture()
        capture.name = "$filename.$format"
        capture.format = format

        val processors: HashSet<ScreenCaptureProcessor> = HashSet()
        val captureProcessor = SaveScreenCaptureProcessor()
        processors.add(captureProcessor)
        capture.process(processors)
    }

}