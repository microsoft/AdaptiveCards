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

        takeScreenshot(description, true)
    }

    protected override fun failed(e: Throwable?, description: Description?)
    {
        super.failed(e, description)

        takeScreenshot(description, false)
    }

    private fun takeScreenshot(description: Description?, success: Boolean)
    {
        var suffix = "_success"
        if (!success)
        {
            suffix = "_fail";
        }

        val testName: String = description!!.methodName + suffix
        val format: Bitmap.CompressFormat = Bitmap.CompressFormat.JPEG
        val filename = "$testName.$format"
        val capture: ScreenCapture = Screenshot.capture()
        capture.name = filename
        capture.format = format

        val processors: HashSet<ScreenCaptureProcessor> = HashSet()
        val captureProcessor = SaveScreenCaptureProcessor()
        processors.add(captureProcessor)

        try {
            capture.process(processors)
        } catch (e: IOException) {}
    }
}
