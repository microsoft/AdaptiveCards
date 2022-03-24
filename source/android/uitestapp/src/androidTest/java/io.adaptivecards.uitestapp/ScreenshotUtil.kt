// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp

import android.graphics.Bitmap
import androidx.test.runner.screenshot.ScreenCapture
import androidx.test.runner.screenshot.ScreenCaptureProcessor
import androidx.test.runner.screenshot.Screenshot
import org.junit.runner.Description

class ScreenshotUtil {

    private lateinit var mInstance: ScreenshotUtil

    public fun instance(): ScreenshotUtil {
        if (!(this::mInstance.isInitialized)) {
            mInstance = ScreenshotUtil()
        }

        return mInstance
    }

    public fun takeScreenshot(screenshotName: String) {
        saveScreenshot(screenshotName)
    }

    public fun takeScreenshot(description: Description?, success: Boolean) {
        var suffix = "_success"
        if (!success) {
            suffix = "_fail";
        }

        val testName: String = description!!.methodName + suffix
        saveScreenshot(testName);
    }

    private fun saveScreenshot(filename: String) {
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