// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package com.example.mobilechatapp;

import java.util.Random;

/**
 * Created by almedina on 8/20/2018.
 */

public class Utils
{

    private static Random getRandom()
    {
        if(s_random == null)
        {
            s_random = new Random();
        }
        return s_random;
    }

    // return in [lowerBound, upperBound) range
    public static int getRandom(int lowerBound, int upperBound)
    {
        final int rangeSize = (upperBound - lowerBound);
        return getRandom().nextInt(rangeSize) + lowerBound;
    }

    // Parse a number that we actually know it's a number
    public static int parseSafeNumber(String numberString)
    {
        try
        {
            return Integer.parseInt(numberString);
        }
        catch (Exception e) {}
        return 0;
    }

    public static Random s_random = null;
}
