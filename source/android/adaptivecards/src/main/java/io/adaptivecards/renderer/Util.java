// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.util.DisplayMetrics;
import android.util.TypedValue;

import io.adaptivecards.objectmodel.CharVector;

public final class Util {

    public static int dpToPixels(Context context, long dp)
    {
        DisplayMetrics metrics = context.getResources().getDisplayMetrics();
        int returnVal = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, dp, metrics);
        return returnVal;
    }

    public static byte[] getBytes(CharVector charVector)
    {
        long vectorSize = charVector.size();
        byte[] byteArray = new byte[(int)vectorSize];
        for(int i = 0; i < vectorSize; ++i)
        {
            byteArray[i] = (byte)charVector.get(i).charValue();
        }

        return byteArray;
    }
}
