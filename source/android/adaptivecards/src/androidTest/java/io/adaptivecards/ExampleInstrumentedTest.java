package io.adaptivecards;

import android.content.Context;
import android.support.test.InstrumentationRegistry;
import android.support.test.runner.AndroidJUnit4;

import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;

import io.adaptivecards.objectmodel.TextBlock;

import static org.junit.Assert.*;

/**
 * Instrumentation test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class ExampleInstrumentedTest {

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void testSomething() throws Exception
    {
        TextBlock textBlock = new TextBlock();
        textBlock.SetText("Text");

        Assert.assertEquals("not the same", "Text", textBlock.GetText());
    }

    @Test
    public void useAppContext() throws Exception {
        // Context of the app under test.
        Context appContext = InstrumentationRegistry.getTargetContext();

        assertEquals("io.adaptivecards.test", appContext.getPackageName());
    }


}
