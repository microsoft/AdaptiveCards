// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.graphics.Typeface;
import android.view.Gravity;

import java.util.HashMap;
import java.util.Map;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.FontType;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HorizontalAlignment;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.TextSize;
import io.adaptivecards.objectmodel.TextWeight;

public class TextRendererUtil
{
    private static Map<String, Typeface> customTypefaces = new HashMap<>();

    public static void registerCustomTypeface(String name, Typeface typeface) {

        customTypefaces.put(name, typeface);
    }

    static int getTextAlignment(HorizontalAlignment textAlignment)
    {
        int alignment;
        if (textAlignment == HorizontalAlignment.Center)
        {
            alignment = Gravity.CENTER;
        }
        else if (textAlignment == HorizontalAlignment.Left)
        {
            alignment = Gravity.LEFT;
        }
        else if (textAlignment == HorizontalAlignment.Right)
        {
            alignment = Gravity.RIGHT;
        }
        else
        {
            throw new IllegalArgumentException("Invalid text alignment: " + textAlignment.toString());
        }

        return alignment;
    }

    static long getTextSize(FontType type, TextSize textSize, HostConfig hostConfig)
    {
        return hostConfig.GetFontSize(type, textSize);
    }

    static Typeface getTextFormat(HostConfig hostConfig, FontType type)
    {
        String fontFamily = hostConfig.GetFontFamily(type);

        Typeface typeface;
        if (fontFamily.isEmpty() && type == FontType.Monospace)
        {
            typeface = Typeface.MONOSPACE;
        }
        else if (customTypefaces.containsKey(fontFamily))
        {
            typeface = customTypefaces.get(fontFamily);
        }
        else
        {
            typeface = Typeface.create(fontFamily, Typeface.NORMAL);
        }

        return typeface;
    }

    static String getTextColor(ForegroundColor foregroundColor, HostConfig hostConfig, boolean isSubtle, ContainerStyle containerStyle)
    {
        return hostConfig.GetForegroundColor(containerStyle, foregroundColor, isSubtle);
    }

    static String getHighlightColor(ForegroundColor foregroundColor, HostConfig hostConfig, boolean isSubtle, ContainerStyle containerStyle)
    {
        return hostConfig.GetHighlightColor(containerStyle, foregroundColor, isSubtle);
    }

    static int getTextWeight(TextWeight textWeight)
    {
        int weight;
        if (textWeight == TextWeight.Default)
        {
            weight = Typeface.NORMAL;
        }
        else if (textWeight == TextWeight.Bolder)
        {
            weight = Typeface.BOLD;
        }
        else if (textWeight == TextWeight.Lighter)
        {
            weight = Typeface.ITALIC;
        }
        else
        {
            throw new IllegalArgumentException("Invalid text weight: " + textWeight.toString());
        }

        return weight;
    }

}
