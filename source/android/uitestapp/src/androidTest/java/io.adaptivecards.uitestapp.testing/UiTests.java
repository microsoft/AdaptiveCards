// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp.testing;

import io.adaptivecards.uitestapp.MainActivityUITestApp;

import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.io.IOException;

import androidx.test.internal.runner.junit4.AndroidJUnit4ClassRunner;

@RunWith(AndroidJUnit4ClassRunner.class)
public class UiTests {

    static
    {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void MockTest() throws IOException
    {
        Assert.assertTrue(true);
    }

}
