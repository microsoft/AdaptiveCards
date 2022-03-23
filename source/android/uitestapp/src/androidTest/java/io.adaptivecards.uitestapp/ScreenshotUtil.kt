package io.adaptivecards.uitestapp

import android.graphics.Bitmap
import androidx.test.runner.screenshot.ScreenCapture
import androidx.test.runner.screenshot.ScreenCaptureProcessor
import androidx.test.runner.screenshot.Screenshot
import org.junit.runner.Description
import java.io.IOException

class ScreenshotUtil {

    private var mInstance : ScreenshotUtil? = null;

    public fun instance(): ScreenshotUtil
    {
        if (mInstance == null)
        {
            mInstance = ScreenshotUtil();
        }

        return mInstance as ScreenshotUtil;
    }

    public fun takeScreenshot(screenshotName: String)
    {
        saveScreenshot(screenshotName)
    }

    public fun takeScreenshot(description: Description?, success: Boolean)
    {
        var suffix = "_success"
        if (!success)
        {
            suffix = "_fail";
        }

        val testName: String = description!!.methodName + suffix
        saveScreenshot(testName);
    }

    private fun saveScreenshot(filename: String)
    {
        val format: Bitmap.CompressFormat = Bitmap.CompressFormat.JPEG

        val capture: ScreenCapture = Screenshot.capture()
        capture.name = "$filename.$format"
        capture.format = format

        val processors: HashSet<ScreenCaptureProcessor> = HashSet()
        val captureProcessor = SaveScreenCaptureProcessor()
        processors.add(captureProcessor)

        try
        {
            capture.process(processors)
        }
        catch (e: IOException)
        {
            throw e;
        }
    }

}