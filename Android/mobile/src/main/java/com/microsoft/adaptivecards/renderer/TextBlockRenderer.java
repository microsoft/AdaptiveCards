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
import com.microsoft.adaptivecards.objectmodel.TextWrap;

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
        m_textColorMap.put(TextColor.Default, Color.GRAY);
        m_textColorMap.put(TextColor.Dark, Color.DKGRAY);
        m_textColorMap.put(TextColor.Light, Color.LTGRAY);
        m_textColorMap.put(TextColor.Accent, Color.CYAN);
        m_textColorMap.put(TextColor.Good, Color.GREEN);
        m_textColorMap.put(TextColor.Warning, Color.YELLOW);
        m_textColorMap.put(TextColor.Attention, Color.RED);

        // Set up Text Size Map
        // TODO:: should use dimensions.xml instead - res/values/dimensions.xml
        // http://stackoverflow.com/questions/9494037/how-to-set-text-size-of-textview-dynamically-for-different-screens
        m_textSizeMap.put(TextSize.Small, 8);
        m_textSizeMap.put(TextSize.Normal, 12);
        m_textSizeMap.put(TextSize.Medium, 16);
        m_textSizeMap.put(TextSize.Large, 20);
        m_textSizeMap.put(TextSize.ExtraLarge, 24);

        // Set up Text Weight Map
        m_textWeightMap.put(TextWeight.Normal, Typeface.NORMAL);
        m_textWeightMap.put(TextWeight.Bolder, Typeface.BOLD);
        m_textWeightMap.put(TextWeight.Lighter, Typeface.ITALIC);

        // Set up Text Wrap Map
        m_textWrapMap.put(TextWrap.NoWrap, false);
        m_textWrapMap.put(TextWrap.Wrap, true);

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
    private HashMap<TextWrap, Boolean> m_textWrapMap = new HashMap<TextWrap, Boolean>();
}
