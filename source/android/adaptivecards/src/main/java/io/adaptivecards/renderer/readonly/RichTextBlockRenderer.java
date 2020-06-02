// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Typeface;
import android.support.annotation.NonNull;
import android.support.v4.app.FragmentManager;
import android.text.Spannable;
import android.text.SpannableStringBuilder;
import android.text.Spanned;
import android.text.TextUtils;
import android.text.method.LinkMovementMethod;
import android.text.style.AbsoluteSizeSpan;
import android.text.style.BackgroundColorSpan;
import android.text.style.ClickableSpan;
import android.text.style.ForegroundColorSpan;
import android.text.style.StrikethroughSpan;
import android.text.style.StyleSpan;
import android.text.style.TypefaceSpan;
import android.text.style.UnderlineSpan;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Inline;
import io.adaptivecards.objectmodel.InlineElementType;
import io.adaptivecards.objectmodel.InlineVector;
import io.adaptivecards.objectmodel.RichTextBlock;
import io.adaptivecards.objectmodel.TextBlock;
import io.adaptivecards.objectmodel.TextRun;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public class RichTextBlockRenderer extends BaseCardElementRenderer
{

    public static RichTextBlockRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new RichTextBlockRenderer();
        }

        return s_instance;
    }

    private class ActionSpan extends ClickableSpan
    {
        public ActionSpan(BaseActionElement action, RenderedAdaptiveCard renderedCard, ICardActionHandler cardActionHandler)
        {
            m_actionListener = new BaseActionElementRenderer.SelectActionOnClickListener(renderedCard, action, cardActionHandler);
        }

        @Override
        public void onClick(@NonNull View widget)
        {
            // Delegate the job to the listener
            m_actionListener.onClick(widget);
        }

        private BaseActionElementRenderer.SelectActionOnClickListener m_actionListener;
    }

    public static SpannableStringBuilder setColor(SpannableStringBuilder paragraph,
                                                  int spanStart,
                                                  int spanEnd,
                                                  ForegroundColor textColor,
                                                  boolean isSubtle,
                                                  HostConfig hostConfig,
                                                  RenderArgs renderArgs)
    {
        int color = getColor(TextRendererUtil.getTextColor(textColor, hostConfig, isSubtle, renderArgs.getContainerStyle()));
        paragraph.setSpan(new ForegroundColorSpan(color), spanStart, spanEnd, Spannable.SPAN_INCLUSIVE_EXCLUSIVE);
        return paragraph;
    }

    public static TextRun castInlineToTextRun(Inline inline)
    {
        TextRun textRun = null;
        if (inline instanceof TextRun)
        {
            textRun = (TextRun) inline;
        }
        else if ((textRun = TextRun.dynamic_cast(inline)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to TextBlock object model.");
        }
        return textRun;
    }

    private SpannableStringBuilder buildSpannableParagraph(
                RenderedAdaptiveCard renderedCard,
                InlineVector inlines,
                ICardActionHandler cardActionHandler,
                HostConfig hostConfig,
                RenderArgs renderArgs)
    {
        SpannableStringBuilder paragraph = new SpannableStringBuilder();
        int lastStringLength = 0;
        for(int i = 0; i < inlines.size(); ++i, lastStringLength = paragraph.length())
        {
            Inline inline = inlines.get(i);
            if(inline.GetInlineType() == InlineElementType.TextRun)
            {
                TextRun textRun = null;
                if (inline instanceof TextRun)
                {
                    textRun = (TextRun) inline;
                }
                else if ((textRun = TextRun.dynamic_cast(inline)) == null)
                {
                    throw new InternalError("Unable to convert BaseCardElement to TextBlock object model.");
                }

                DateTimeParser parser = new DateTimeParser(textRun.GetLanguage());
                String textWithFormattedDates = parser.GenerateString(textRun.GetTextForDateParsing());
                CharSequence text = RendererUtil.handleSpecialText(textWithFormattedDates);

                paragraph.append(text);

                int spanStart = lastStringLength;
                int spanEnd = lastStringLength + text.length();

                int color = getColor(TextRendererUtil.getTextColor(textRun.GetTextColor(), hostConfig, textRun.GetIsSubtle(), renderArgs.getContainerStyle()));
                paragraph.setSpan(new ForegroundColorSpan(color), spanStart, spanEnd, Spannable.SPAN_INCLUSIVE_EXCLUSIVE);

                if (textRun.GetHighlight())
                {
                    int highlightColor = getColor(TextRendererUtil.getHighlightColor(textRun.GetTextColor(), hostConfig, textRun.GetIsSubtle(), renderArgs.getContainerStyle()));
                    paragraph.setSpan(new BackgroundColorSpan(highlightColor), spanStart, spanEnd, Spannable.SPAN_INCLUSIVE_EXCLUSIVE);
                }

                if (textRun.GetStrikethrough())
                {
                    paragraph.setSpan(new StrikethroughSpan(), spanStart, spanEnd, Spannable.SPAN_INCLUSIVE_EXCLUSIVE);
                }

                if (textRun.GetUnderline())
                {
                    paragraph.setSpan(new UnderlineSpan(), spanStart, spanEnd, Spannable.SPAN_INCLUSIVE_EXCLUSIVE);
                }

                // This line sets the bold or lighter weight
                paragraph.setSpan(new StyleSpan(TextRendererUtil.getTextWeight(textRun.GetTextWeight())), spanStart, spanEnd, Spannable.SPAN_INCLUSIVE_EXCLUSIVE);

                if (textRun.GetItalic())
                {
                    paragraph.setSpan(new StyleSpan(Typeface.ITALIC), spanStart, spanEnd, Spanned.SPAN_INCLUSIVE_EXCLUSIVE);
                }

                long textSize = TextRendererUtil.getTextSize(textRun.GetFontType(), textRun.GetTextSize(), hostConfig);
                paragraph.setSpan(new AbsoluteSizeSpan((int)textSize, true), spanStart, spanEnd, Spanned.SPAN_INCLUSIVE_EXCLUSIVE);

                // On API 28, TypefaceSpan(Typeface) was added so we don't have to use the TypefaceSpan(String) constructor
                String fontName = hostConfig.GetFontFamily(textRun.GetFontType());
                if (fontName.isEmpty())
                {
                    fontName = "monospace";
                }

                paragraph.setSpan(new TypefaceSpan(fontName), spanStart, spanEnd, Spanned.SPAN_INCLUSIVE_EXCLUSIVE);

                if(textRun.GetSelectAction() != null)
                {
                    paragraph.setSpan(new ActionSpan(textRun.GetSelectAction(), renderedCard, cardActionHandler), spanStart, spanEnd, Spanned.SPAN_INCLUSIVE_EXCLUSIVE);
                }
            }
        }

        return paragraph;
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
            RenderArgs renderArgs)
    {
        RichTextBlock richTextBlock = null;
        if (baseCardElement instanceof TextBlock)
        {
            richTextBlock = (RichTextBlock) baseCardElement;
        }
        else if ((richTextBlock = RichTextBlock.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to TextBlock object model.");
        }

        TextView textView = new TextView(context);
        textView.setEllipsize(TextUtils.TruncateAt.END);
        textView.setHorizontallyScrolling(false);

        // BaseCardElement properties
        // Separator
        // Height
        // IsVisible
        // Spacing
        View separator = setSpacingAndSeparator(context, viewGroup, richTextBlock.GetSpacing(), richTextBlock.GetSeparator(), hostConfig, true);

        textView.setTag(new TagContent(richTextBlock, separator, viewGroup));
        setVisibility(baseCardElement.GetIsVisible(), textView);

        if (richTextBlock.GetHeight() == HeightType.Stretch)
        {
            textView.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1));
        }
        else
        {
            textView.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        }

        // RichTextBlock properties
        // HorizontalAlignment
        // Inlines

        textView.setGravity(TextRendererUtil.getTextAlignment(richTextBlock.GetHorizontalAlignment()));

        // This is the section for rendering the paragraphs
        // Every paragraph may contain contains any number of inlines
        // The current inline element types are TextRun
        InlineVector inlines = richTextBlock.GetInlines();

        textView.setText("");
        SpannableStringBuilder convertedString = buildSpannableParagraph(renderedCard, inlines, cardActionHandler, hostConfig, renderArgs);
        textView.append(convertedString);

        // Properties required for actions to fire onClick event
        textView.setMovementMethod(LinkMovementMethod.getInstance());
        textView.setClickable(true);

        viewGroup.addView(textView);
        return textView;
    }

    private static RichTextBlockRenderer s_instance = null;
}
