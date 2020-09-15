// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Typeface;
import android.graphics.fonts.Font;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.support.v4.app.FragmentManager;
import android.text.Layout;
import android.text.Selection;
import android.text.Spannable;
import android.text.SpannableString;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.text.style.ClickableSpan;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.graphics.fonts.FontStyle;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.FontType;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HorizontalAlignment;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.TextBlock;
import io.adaptivecards.objectmodel.TextSize;
import io.adaptivecards.objectmodel.TextWeight;
import io.adaptivecards.renderer.BaseCardElementRenderer;

import java.util.HashMap;

public class TextBlockRenderer extends BaseCardElementRenderer
{
    protected TextBlockRenderer()
    {
        // Set up Text Weight Map
        m_textWeightMap.put(TextWeight.Default, g_textWeightDefault);
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

    public static void setTextAlignment(TextView textView, HorizontalAlignment textAlignment)
    {
        textView.setGravity(TextRendererUtil.getTextAlignment(textAlignment));
    }

    public static void setTextSize(TextView textView, FontType type, TextSize textSize, HostConfig hostConfig)
    {
        textView.setTextSize(TextRendererUtil.getTextSize(type, textSize, hostConfig));
    }

    public void setTextFormat(TextView textView, HostConfig hostConfig, FontType type, TextWeight textWeight)
    {
        Typeface typeface = TextRendererUtil.getTextFormat(hostConfig, type, textWeight == TextWeight.Lighter);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P)
        {
            Typeface weightedTypeface = Typeface.create(typeface, (int) hostConfig.GetFontWeight(type, textWeight), false);
            textView.setTypeface(weightedTypeface);
        }
        else
        {
            if (textWeight == TextWeight.Bolder)
            {
                textView.setTypeface(typeface, Typeface.BOLD);
            }
            else
            {
                textView.setTypeface(typeface);
            }
        }

    }

    public static void setTextColor(TextView textView, ForegroundColor foregroundColor, HostConfig hostConfig, boolean isSubtle, ContainerStyle containerStyle)
    {
        textView.setTextColor(getColor(TextRendererUtil.getTextColor(foregroundColor, hostConfig, isSubtle, containerStyle)));
    }

    static class TouchTextView implements View.OnTouchListener
    {
        Spannable spannable;

        public TouchTextView (Spannable spannable)
        {
            this.spannable = spannable;
        }

        @Override
        public boolean onTouch(View v, MotionEvent event)
        {
            int action = event.getAction();
            if (!(v instanceof TextView))
            {
                return false;
            }
            TextView textView  = (TextView) v;
            if (action == MotionEvent.ACTION_UP ||
                    action == MotionEvent.ACTION_DOWN)
            {
                int x = (int) event.getX();
                int y = (int) event.getY();

                x -= textView.getTotalPaddingLeft();
                y -= textView.getTotalPaddingTop();

                x += textView.getScrollX();
                y += textView.getScrollY();

                Layout layout = textView.getLayout();
                int line = layout.getLineForVertical(y);
                int off = layout.getOffsetForHorizontal(line, x);

                ClickableSpan[] link = spannable.getSpans(off, off, ClickableSpan.class);

                if (link.length != 0)
                {
                    if (action == MotionEvent.ACTION_UP)
                    {
                        link[0].onClick(textView);
                    }
                    else if (action == MotionEvent.ACTION_DOWN)
                    {
                        Selection.setSelection(spannable,
                                spannable.getSpanStart(link[0]),
                                spannable.getSpanEnd(link[0]));
                    }

                    return true;

                }
                else
                {
                    Selection.removeSelection(spannable);
                }
            }

            return false;
        }
    }

    @Override
    public View render(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            RenderArgs renderArgs) throws Exception
    {
        TextBlock textBlock = Util.castTo(baseCardElement, TextBlock.class);

        if (textBlock.GetText().isEmpty())
        {
            return null;
        }

        TextView textView = new TextView(context);
        textView.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));

        textView.setTag(new TagContent(textBlock));

        DateTimeParser parser = new DateTimeParser(textBlock.GetLanguage());
        String textWithFormattedDates = parser.GenerateString(textBlock.GetTextForDateParsing());

        CharSequence text = RendererUtil.handleSpecialText(textWithFormattedDates);
        textView.setText(text);

        if (!textBlock.GetWrap())
        {
            textView.setMaxLines(1);
        }
        textView.setEllipsize(TextUtils.TruncateAt.END);
        textView.setOnTouchListener(new TouchTextView(new SpannableString(text)));
        textView.setHorizontallyScrolling(false);
        setTextFormat(textView, hostConfig, textBlock.GetFontType(), textBlock.GetTextWeight());
        setTextSize(textView, textBlock.GetFontType(), textBlock.GetTextSize(), hostConfig);
        setTextColor(textView, textBlock.GetTextColor(), hostConfig, textBlock.GetIsSubtle(), renderArgs.getContainerStyle());
        setTextAlignment(textView, textBlock.GetHorizontalAlignment());

        int maxLines = (int)textBlock.GetMaxLines();
        if (maxLines > 0 && textBlock.GetWrap())
        {
            textView.setMaxLines(maxLines);
        }
        else if (!textBlock.GetWrap())
        {
            textView.setMaxLines(1);
        }

        viewGroup.addView(textView);
        return textView;
    }

    private static TextBlockRenderer s_instance = null;

    private HashMap<TextWeight, Integer> m_textWeightMap = new HashMap<TextWeight, Integer>();

    // Text Weight Constants
    private final int g_textWeightDefault = Typeface.NORMAL;
    private final int g_textWeightBolder = Typeface.BOLD;
    private final int g_textWeightLighter = Typeface.ITALIC;
}
