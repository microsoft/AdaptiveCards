package io.adaptivecards.uitestapp

import androidx.test.runner.screenshot.ScreenCapture
import androidx.test.runner.screenshot.ScreenCaptureProcessor

import android.os.Environment
import java.io.*


class SaveScreenCaptureProcessor: ScreenCaptureProcessor
{
    override fun process(capture: ScreenCapture?): String {
        val file:String = capture?.name ?: "Default.jpg"
        val data: ByteArrayOutputStream = getImageData(capture)

        val screenshotPath = Environment.getExternalStorageDirectory().absolutePath + "/Screenshots"
        val screenshotDirectory = File(screenshotPath)
        if (!screenshotDirectory.exists()) {
            screenshotDirectory.mkdirs();
        }

        val screenshotFilePath = "$screenshotPath/$file"
        val screenshotFile = File(screenshotFilePath)

        screenshotFile.createNewFile()

        try {
            val fos = FileOutputStream(screenshotFile)
            fos.write(data.toByteArray())
            fos.flush()
            fos.close()
        } catch (e: Exception) {
            throw e;
        }

        return ""
    }


    @Throws(IOException::class)
    private fun getImageData(capture: ScreenCapture?): ByteArrayOutputStream {
        val outputStream = ByteArrayOutputStream()
        capture!!.bitmap.compress(capture!!.format, 100, outputStream)
        outputStream.close()
        return outputStream;
    }
}