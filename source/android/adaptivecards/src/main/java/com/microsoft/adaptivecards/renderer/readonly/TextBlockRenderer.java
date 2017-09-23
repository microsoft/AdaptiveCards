package com.microsoft.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Typeface;
import android.support.v4.app.FragmentManager;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.microsoft.adaptivecards.objectmodel.Separator;
import com.microsoft.adaptivecards.objectmodel.Spacing;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.Color;
import com.microsoft.adaptivecards.objectmodel.ColorsConfig;
import com.microsoft.adaptivecards.objectmodel.FontSizesConfig;
import com.microsoft.adaptivecards.objectmodel.HorizontalAlignment;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.TextBlock;
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

    static void setTextSize(TextView textView, TextSize textSize, HostConfig hostConfig)
    {
        FontSizesConfig fontSizesConfig = hostConfig.getFontSizes();
        if (textSize.swigValue() == TextSize.ExtraLarge.swigValue())
        {
            textView.setTextSize(fontSizesConfig.getExtraLargeFontSize());
        }
        else if (textSize.swigValue() == TextSize.Large.swigValue())
        {
            textView.setTextSize(fontSizesConfig.getLargeFontSize());
        }
        else if (textSize.swigValue() == TextSize.Medium.swigValue())
        {
            textView.setTextSize(fontSizesConfig.getMediumFontSize());
        }
        else if (textSize.swigValue() == TextSize.Normal.swigValue())
        {
            textView.setTextSize(fontSizesConfig.getNormalFontSize());
        }
        else if (textSize.swigValue() == TextSize.Small.swigValue())
        {
            textView.setTextSize(fontSizesConfig.getSmallFontSize());
        }
        else
        {
            throw new IllegalArgumentException("Unknown text size: " + textSize.toString());
        }
    }

    static void setTextColor(TextView textView, Color textColor, boolean isSubtle, ColorsConfig colorsConfig)
    {
        textView.setTextColor(getColor(textColor, colorsConfig, isSubtle));
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
        setTextSize(textView, textBlock.GetTextSize(), hostConfig);
        setSpacingAndSeparator(context, viewGroup, textBlock.GetSpacing(), textBlock.GetSeparator(), hostConfig, true);
        textView.setTextColor(getColor(textBlock.GetTextColor(), hostConfig.getColors(), textBlock.GetIsSubtle()));
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
