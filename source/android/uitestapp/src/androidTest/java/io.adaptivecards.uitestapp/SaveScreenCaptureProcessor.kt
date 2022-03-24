// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp

import androidx.test.runner.screenshot.ScreenCapture
import androidx.test.runner.screenshot.ScreenCaptureProcessor

import android.os.Environment
import java.io.*

class SaveScreenCaptureProcessor : ScreenCaptureProcessor {
    override fun process(capture: ScreenCapture?): String {
        val file: String = capture?.name ?: "Default.jpg"
        val data: ByteArray = getImageData(capture)

        val screenshotPath =
            Environment.getExternalStorageDirectory().absolutePath + "/screenshots/"
        val screenshotDirectory = File(screenshotPath)
        if (!screenshotDirectory.exists()) {
            screenshotDirectory.mkdirs()
        }

        val screenshotFilePath = "$screenshotPath/$file"
        val screenshotFile = File(screenshotFilePath)
        screenshotFile.createNewFile()

        val fos = FileOutputStream(screenshotFile)
        fos.write(data)
        fos.flush()
        fos.close()

        return screenshotPath
    }

    @Throws(IOException::class)
    private fun getImageData(capture: ScreenCapture?): ByteArray {
        val outputStream = ByteArrayOutputStream()
        capture!!.bitmap.compress(capture.format, 100, outputStream)
        return outputStream.toByteArray()
    }
}