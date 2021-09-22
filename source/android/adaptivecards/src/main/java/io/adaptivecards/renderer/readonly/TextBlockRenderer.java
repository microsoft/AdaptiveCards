// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Typeface;
import android.os.Build;
import android.text.Layout;
import android.text.Selection;
import android.text.Spannable;
import android.text.SpannableString;
import android.text.TextUtils;
import android.text.method.LinkMovementMethod;
import android.text.style.ClickableSpan;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.view.AccessibilityDelegateCompat;
import androidx.core.view.ViewCompat;
import androidx.core.view.accessibility.AccessibilityNodeInfoCompat;
import androidx.fragment.app.FragmentManager;

import java.util.HashMap;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.FontType;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HorizontalAlignment;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.TextBlock;
import io.adaptivecards.objectmodel.TextSize;
import io.adaptivecards.objectmodel.TextStyle;
import io.adaptivecards.objectmodel.TextWeight;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

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

    public static void applyHorizontalAlignment(TextView textView, HorizontalAlignment horizontalAlignment, RenderArgs renderArgs)
    {
        horizontalAlignment = RendererUtil.computeHorizontalAlignment(horizontalAlignment, renderArgs);
        textView.setTextAlignment(TextRendererUtil.getTextAlignment(horizontalAlignment));
    }

    public static void applyTextSize(TextView textView, HostConfig hostConfig, TextStyle textStyle, FontType fontType, TextSize textSize, RenderArgs renderArgs)
    {
        textSize = TextRendererUtil.computeTextSize(hostConfig, textStyle, textSize, renderArgs);
        fontType = TextRendererUtil.computeFontType(hostConfig, textStyle, fontType, renderArgs);

        textView.setTextSize(TextRendererUtil.getTextSize(fontType, textSize, hostConfig));
    }

    public static void applyAccessibilityHeading(@NonNull final TextView textView, @Nullable final TextStyle textStyle)
    {
        // Indicate Heading to accessibility service
        // TODO: Refactor to ViewCompat.setAccessibilityHeading after AndroidX upgrade
        ViewCompat.setAccessibilityDelegate(textView, new AccessibilityDelegateCompat() {
            @Override
            public void onInitializeAccessibilityNodeInfo(View host, AccessibilityNodeInfoCompat info) {
                super.onInitializeAccessibilityNodeInfo(host, info);
                info.setHeading(textStyle == TextStyle.Heading);
            }
        });
    }

    public static void applyTextFormat(TextView textView, HostConfig hostConfig, TextStyle textStyle, FontType type, TextWeight textWeight, RenderArgs renderArgs)
    {
        type = TextRendererUtil.computeFontType(hostConfig, textStyle, type, renderArgs);
        textWeight = TextRendererUtil.computeTextWeight(hostConfig, textStyle, textWeight, renderArgs);

        Typeface typeface = TextRendererUtil.getTextFormat(hostConfig, type, textWeight == TextWeight.Lighter);

        // As of API 28, the create(Typeface, int, bool) method used below was added to the android API, the second parameter is the
        // font weight, in prior versions we had to look up for an specific font family name
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

    public static void applyTextColor(TextView textView, HostConfig hostConfig, TextStyle textStyle, ForegroundColor foregroundColor, Boolean isSubtle, ContainerStyle containerStyle, RenderArgs renderArgs)
    {
        foregroundColor = TextRendererUtil.computeTextColor(hostConfig, textStyle, foregroundColor, renderArgs);
        isSubtle = TextRendererUtil.computeIsSubtle(hostConfig, textStyle, isSubtle, renderArgs);

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
        applyTextFormat(textView, hostConfig, textBlock.GetStyle(), textBlock.GetFontType(), textBlock.GetTextWeight(), renderArgs);
        applyTextSize(textView, hostConfig, textBlock.GetStyle(), textBlock.GetFontType(), textBlock.GetTextSize(), renderArgs);
        applyTextColor(textView, hostConfig, textBlock.GetStyle(), textBlock.GetTextColor(), textBlock.GetIsSubtle(), renderArgs.getContainerStyle(), renderArgs);
        applyHorizontalAlignment(textView, textBlock.GetHorizontalAlignment(), renderArgs);
        applyAccessibilityHeading(textView, textBlock.GetStyle());

        int maxLines = (int)textBlock.GetMaxLines();
        if (maxLines > 0 && textBlock.GetWrap())
        {
            textView.setMaxLines(maxLines);
        }
        else if (!textBlock.GetWrap())
        {
            textView.setMaxLines(1);
        }

        textView.setMovementMethod(LinkMovementMethod.getInstance());

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
