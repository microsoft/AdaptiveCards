package io.adaptivecards.uitestapp

import android.graphics.Bitmap
import androidx.test.runner.screenshot.ScreenCapture
import androidx.test.runner.screenshot.ScreenCaptureProcessor
import androidx.test.runner.screenshot.Screenshot
import org.junit.rules.TestWatcher
import org.junit.runner.Description
import java.io.IOException

public class TestWatchRule : TestWatcher() {

    protected override fun starting(description: Description)
    {
        print("Starting test run");
    }

    protected override fun succeeded(description: Description?) {
        super.succeeded(description)

        ScreenshotUtil().instance().takeScreenshot(description, true)
    }

    protected override fun failed(e: Throwable?, description: Description?)
    {
        super.failed(e, description)

        ScreenshotUtil().instance().takeScreenshot(description, false)
    }


}
