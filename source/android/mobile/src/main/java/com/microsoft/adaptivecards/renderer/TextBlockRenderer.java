package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Typeface;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.ColorOptions;
import com.microsoft.adaptivecards.objectmodel.FontSizeOptions;
import com.microsoft.adaptivecards.objectmodel.HorizontalAlignment;
import com.microsoft.adaptivecards.objectmodel.HostOptions;
import com.microsoft.adaptivecards.objectmodel.SeparationOptions;
import com.microsoft.adaptivecards.objectmodel.SeparationStyle;
import com.microsoft.adaptivecards.objectmodel.TextBlock;
import com.microsoft.adaptivecards.objectmodel.TextColor;
import com.microsoft.adaptivecards.objectmodel.TextSize;
import com.microsoft.adaptivecards.objectmodel.TextWeight;

import java.util.HashMap;

/**
 * Created by bekao on 2/11/2017.
 */

public class TextBlockRenderer extends BaseCardElementRenderer
{
    private TextBlockRenderer()
    {
        // Set up Text Weight Map
        m_textWeightMap.put(TextWeight.Normal, g_textWeightNormal);
        m_textWeightMap.put(TextWeight.Bolder, g_textWeightBolder);
        m_textWeightMap.put(TextWeight.Lighter, g_textWeightLighter);
    }

    public static TextBlockRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new TextBlockRenderer();
        }

        return s_instance;
    }

    static SeparationOptions setTextSize(TextView textView, TextSize textSize, HostOptions hostOptions)
    {
        FontSizeOptions fontSizeOptions = hostOptions.getFontSizes();
        SeparationOptions separationOptions;
        if (textSize.swigValue() == TextSize.ExtraLarge.swigValue())
        {
            textView.setTextSize(fontSizeOptions.getExtraLargeFontSize());
            separationOptions = hostOptions.getTextBlock().getExtraLargeSeparation();
        }
        else if (textSize.swigValue() == TextSize.Large.swigValue())
        {
            textView.setTextSize(fontSizeOptions.getLargeFontSize());
            separationOptions = hostOptions.getTextBlock().getLargeSeparation();
        }
        else if (textSize.swigValue() == TextSize.Medium.swigValue())
        {
            textView.setTextSize(fontSizeOptions.getMediumFontSize());
            separationOptions = hostOptions.getTextBlock().getMediumSeparation();
        }
        else if (textSize.swigValue() == TextSize.Normal.swigValue())
        {
            textView.setTextSize(fontSizeOptions.getNormalFontSize());
            separationOptions = hostOptions.getTextBlock().getNormalSeparation();
        }
        else if (textSize.swigValue() == TextSize.Small.swigValue())
        {
            textView.setTextSize(fontSizeOptions.getSmallFontSize());
            separationOptions = hostOptions.getTextBlock().getSmallSeparation();
        }
        else
        {
            throw new IllegalArgumentException("Unknown text size: " + textSize.toString());
        }

        return separationOptions;
    }

    static void setTextSizeAndSeparationOptions(Context context, TextView textView, ViewGroup viewGroup, TextSize textSize, SeparationStyle separationStyle, HostOptions hostOptions)
    {
        SeparationOptions separationOptions = setTextSize(textView, textSize, hostOptions);
        setSeparationOptions(context, viewGroup, separationStyle, separationOptions, hostOptions.getStrongSeparation(), true /* horizontal line */);
    }

    static void setTextColor(TextView textView, TextColor textColor, boolean isSubtle, ColorOptions colorOptions)
    {
        com.microsoft.adaptivecards.objectmodel.ColorOption colorOption;
        if (textColor.swigValue() == TextColor.Accent.swigValue())
        {
            colorOption = colorOptions.getAccent();
        }
        else if (textColor.swigValue() == TextColor.Attention.swigValue())
        {
            colorOption = colorOptions.getAttention();
        }
        else if (textColor.swigValue() == TextColor.Dark.swigValue())
        {
            colorOption = colorOptions.getDark();
        }
        else if (textColor.swigValue() == TextColor.Default.swigValue())
        {
            colorOption = colorOptions.getDefaultColor();
        }
        else if (textColor.swigValue() == TextColor.Good.swigValue())
        {
            colorOption = colorOptions.getGood();
        }
        else if (textColor.swigValue() == TextColor.Light.swigValue())
        {
            colorOption = colorOptions.getLight();
        }
        else if (textColor.swigValue() == TextColor.Warning.swigValue())
        {
            colorOption = colorOptions.getWarning();
        }
        else
        {
            throw new IllegalArgumentException("Unknown text color: " + textColor.toString());
        }

        textView.setTextColor(Color.parseColor(isSubtle ? colorOption.getSubtle() : colorOption.getNormal()));
    }

    static void setTextAlignment(TextView textView, HorizontalAlignment textAlignment)
    {
        int alignment;
        if (textAlignment.swigValue() == HorizontalAlignment.Center.swigValue())
        {
            alignment = Gravity.CENTER;
        }
        else if (textAlignment.swigValue() == HorizontalAlignment.Left.swigValue())
        {
            alignment = Gravity.LEFT;
        }
        else if (textAlignment.swigValue() == HorizontalAlignment.Right.swigValue())
        {
            alignment = Gravity.RIGHT;
        }
        else
        {
            throw new IllegalArgumentException("Invalid text alignment: " + textAlignment.toString());
        }

        textView.setGravity(alignment);
    }

    void setTextWeight(TextView textView, TextWeight textWeight)
    {
        textView.setTypeface(null, m_textWeightMap.get(textWeight));
    }

    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostOptions hostOptions)
    {
        TextBlock textBlock = null;
        if (baseCardElement instanceof TextBlock)
        {
            textBlock = (TextBlock) baseCardElement;
        }
        else if ((textBlock = TextBlock.dynamic_cast(baseCardElement)) == null)
        {
            return viewGroup;
        }

        TextView textView = new TextView(context);
        textView.setText(textBlock.GetText());
        textView.setSingleLine(!textBlock.GetWrap());
        setTextWeight(textView, textBlock.GetTextWeight());
        setTextSizeAndSeparationOptions(context, textView, viewGroup, textBlock.GetTextSize(), textBlock.GetSeparationStyle(), hostOptions);
        setTextColor(textView, textBlock.GetTextColor(), textBlock.GetIsSubtle(), hostOptions.getColors());
        setTextAlignment(textView, textBlock.GetHorizontalAlignment());
        textView.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        int maxLines = (int)textBlock.GetMaxLines();
        if (maxLines != 0)
        {
            textView.setMaxLines(maxLines);
        }

        viewGroup.addView(textView);
        return viewGroup;
    }

    private static TextBlockRenderer s_instance = null;

    private HashMap<TextWeight, Integer> m_textWeightMap = new HashMap<TextWeight, Integer>();

    // Text Weight Constants
    private final int g_textWeightNormal = Typeface.NORMAL;
    private final int g_textWeightBolder = Typeface.BOLD;
    private final int g_textWeightLighter = Typeface.ITALIC;
}
