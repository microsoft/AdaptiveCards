package com.microsoft.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Typeface;
import android.support.v4.app.FragmentManager;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.ColorsConfig;
import com.microsoft.adaptivecards.objectmodel.FontSizesConfig;
import com.microsoft.adaptivecards.objectmodel.HorizontalAlignment;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.SeparationConfig;
import com.microsoft.adaptivecards.objectmodel.SeparationStyle;
import com.microsoft.adaptivecards.objectmodel.TextBlock;
import com.microsoft.adaptivecards.objectmodel.TextColor;
import com.microsoft.adaptivecards.objectmodel.TextSize;
import com.microsoft.adaptivecards.objectmodel.TextWeight;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;

import java.util.HashMap;
import java.util.Vector;

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

    static SeparationConfig setTextSize(TextView textView, TextSize textSize, HostConfig hostConfig)
    {
        FontSizesConfig fontSizesConfig = hostConfig.getFontSizes();
        SeparationConfig separationConfig;
        if (textSize.swigValue() == TextSize.ExtraLarge.swigValue())
        {
            textView.setTextSize(fontSizesConfig.getExtraLargeFontSize());
            separationConfig = hostConfig.getTextBlock().getExtraLargeSeparation();
        }
        else if (textSize.swigValue() == TextSize.Large.swigValue())
        {
            textView.setTextSize(fontSizesConfig.getLargeFontSize());
            separationConfig = hostConfig.getTextBlock().getLargeSeparation();
        }
        else if (textSize.swigValue() == TextSize.Medium.swigValue())
        {
            textView.setTextSize(fontSizesConfig.getMediumFontSize());
            separationConfig = hostConfig.getTextBlock().getMediumSeparation();
        }
        else if (textSize.swigValue() == TextSize.Normal.swigValue())
        {
            textView.setTextSize(fontSizesConfig.getNormalFontSize());
            separationConfig = hostConfig.getTextBlock().getNormalSeparation();
        }
        else if (textSize.swigValue() == TextSize.Small.swigValue())
        {
            textView.setTextSize(fontSizesConfig.getSmallFontSize());
            separationConfig = hostConfig.getTextBlock().getSmallSeparation();
        }
        else
        {
            throw new IllegalArgumentException("Unknown text size: " + textSize.toString());
        }

        return separationConfig;
    }

    static void setTextSizeAndSeparationConfig(Context context, TextView textView, ViewGroup viewGroup, TextSize textSize, SeparationStyle separationStyle, HostConfig hostConfig)
    {
        SeparationConfig separationConfig = setTextSize(textView, textSize, hostConfig);
        setSeparationConfig(context, viewGroup, separationStyle, separationConfig, hostConfig.getStrongSeparation(), true /* horizontal line */);
    }

    static void setTextColor(TextView textView, TextColor textColor, boolean isSubtle, ColorsConfig colorsConfig)
    {
        com.microsoft.adaptivecards.objectmodel.ColorConfig colorConfig;
        if (textColor.swigValue() == TextColor.Accent.swigValue())
        {
            colorConfig = colorsConfig.getAccent();
        }
        else if (textColor.swigValue() == TextColor.Attention.swigValue())
        {
            colorConfig = colorsConfig.getAttention();
        }
        else if (textColor.swigValue() == TextColor.Dark.swigValue())
        {
            colorConfig = colorsConfig.getDark();
        }
        else if (textColor.swigValue() == TextColor.Default.swigValue())
        {
            colorConfig = colorsConfig.getDefaultColor();
        }
        else if (textColor.swigValue() == TextColor.Good.swigValue())
        {
            colorConfig = colorsConfig.getGood();
        }
        else if (textColor.swigValue() == TextColor.Light.swigValue())
        {
            colorConfig = colorsConfig.getLight();
        }
        else if (textColor.swigValue() == TextColor.Warning.swigValue())
        {
            colorConfig = colorsConfig.getWarning();
        }
        else
        {
            throw new IllegalArgumentException("Unknown text color: " + textColor.toString());
        }

        textView.setTextColor(Color.parseColor(isSubtle ? colorConfig.getSubtle() : colorConfig.getNormal()));
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

    @Override
    public View render(
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            Vector<IInputHandler> inputActionHandlerList,
            HostConfig hostConfig)
    {
        TextBlock textBlock = null;
        if (baseCardElement instanceof TextBlock)
        {
            textBlock = (TextBlock) baseCardElement;
        }
        else if ((textBlock = TextBlock.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to TextBlock object model.");
        }

        TextView textView = new TextView(context);
        textView.setTag(baseCardElement);
        textView.setText(textBlock.GetText());
        textView.setSingleLine(!textBlock.GetWrap());
        setTextWeight(textView, textBlock.GetTextWeight());
        setTextSizeAndSeparationConfig(context, textView, viewGroup, textBlock.GetTextSize(), textBlock.GetSeparationStyle(), hostConfig);
        setTextColor(textView, textBlock.GetTextColor(), textBlock.GetIsSubtle(), hostConfig.getColors());
        setTextAlignment(textView, textBlock.GetHorizontalAlignment());
        textView.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        int maxLines = (int)textBlock.GetMaxLines();
        if (maxLines > 0)
        {
            textView.setMaxLines(maxLines);
        }

        viewGroup.addView(textView);
        return textView;
    }

    private static TextBlockRenderer s_instance = null;

    private HashMap<TextWeight, Integer> m_textWeightMap = new HashMap<TextWeight, Integer>();

    // Text Weight Constants
    private final int g_textWeightNormal = Typeface.NORMAL;
    private final int g_textWeightBolder = Typeface.BOLD;
    private final int g_textWeightLighter = Typeface.ITALIC;
}
