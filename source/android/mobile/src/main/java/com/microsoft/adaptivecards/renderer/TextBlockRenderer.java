package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Typeface;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.TextBlock;
import com.microsoft.adaptivecards.objectmodel.TextColor;
import com.microsoft.adaptivecards.objectmodel.TextSize;
import com.microsoft.adaptivecards.objectmodel.TextWeight;

import org.w3c.dom.Text;

import java.util.HashMap;

/**
 * Created by bekao on 2/11/2017.
 */

public class TextBlockRenderer implements BaseCardElementRenderer
{
    private TextBlockRenderer()
    {
        // Set up Text Color Map
        m_textColorMap.put(TextColor.Default, g_textColorDefault);
        m_textColorMap.put(TextColor.Dark, g_textColorDark);
        m_textColorMap.put(TextColor.Light, g_textColorLight);
        m_textColorMap.put(TextColor.Accent, g_textColorAccent);
        m_textColorMap.put(TextColor.Good, g_textColorGood);
        m_textColorMap.put(TextColor.Warning, g_textColorWarning);
        m_textColorMap.put(TextColor.Attention, g_textColorAttention);

        // Set up Text Size Map
        // TODO:: should use dimensions.xml instead - res/values/dimensions.xml
        // http://stackoverflow.com/questions/9494037/how-to-set-text-size-of-textview-dynamically-for-different-screens
        m_textSizeMap.put(TextSize.Small, g_textSizeSmall);
        m_textSizeMap.put(TextSize.Normal, g_textSizeNormal);
        m_textSizeMap.put(TextSize.Medium, g_textSizeMedium);
        m_textSizeMap.put(TextSize.Large, g_textSizeLarge);
        m_textSizeMap.put(TextSize.ExtraLarge, g_textSizeExtraLarge);

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

    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement)
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
        textView.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        textView.setText(textBlock.GetText());
        textView.setTextSize(m_textSizeMap.get(textBlock.GetTextSize()));
        textView.setTypeface(null, m_textWeightMap.get(textBlock.GetTextWeight()));
        textView.setTextColor(m_textColorMap.get(textBlock.GetTextColor()));
        //textView.setSingleLine(m_textWrapMap.get(textBlock.GetWrap()));
        viewGroup.addView(textView);
        return viewGroup;
    }

    private static TextBlockRenderer s_instance = null;

    private HashMap<TextColor, Integer> m_textColorMap = new HashMap<TextColor, Integer>();
    private HashMap<TextSize, Integer> m_textSizeMap = new HashMap<TextSize, Integer>();
    private HashMap<TextWeight, Integer> m_textWeightMap = new HashMap<TextWeight, Integer>();

    // Text Color Constants
    private int g_textColorDefault = Color.GRAY;
    private int g_textColorDark = Color.DKGRAY;
    private int g_textColorLight = Color.LTGRAY;
    private int g_textColorAccent = Color.CYAN;
    private int g_textColorGood = Color.GREEN;
    private int g_textColorWarning = Color.YELLOW;
    private int g_textColorAttention = Color.RED;

    // Text Size Constants
    private int g_textSizeSmall = 8;
    private int g_textSizeNormal = 12;
    private int g_textSizeMedium = 16;
    private int g_textSizeLarge = 20;
    private int g_textSizeExtraLarge = 24;

    // Text Weight Constants
    private int g_textWeightNormal = Typeface.NORMAL;
    private int g_textWeightBolder = Typeface.BOLD;
    private int g_textWeightLighter = Typeface.ITALIC;
}
