package io.adaptivecards.renderer.readonly;

import android.graphics.Typeface;
import android.view.Gravity;
import android.widget.TextView;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.FontStyle;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HorizontalAlignment;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.TextSize;
import io.adaptivecards.objectmodel.TextWeight;

public class TextRendererUtil
{

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

    static long getTextSize(FontStyle style, TextSize textSize, HostConfig hostConfig)
    {
        return hostConfig.GetFontSize(style, textSize);
    }

    static Typeface getTextFormat(HostConfig hostConfig, FontStyle style)
    {
        String fontFamily = hostConfig.GetFontFamily(style);

        Typeface typeface;
        if (fontFamily.isEmpty() && style == FontStyle.Monospace)
        {
            typeface = Typeface.MONOSPACE;
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
