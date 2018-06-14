package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Typeface;
import android.os.Build;
import android.support.v4.app.FragmentManager;
import android.text.Editable;
import android.text.Html;
import android.text.Layout;
import android.text.Selection;
import android.text.Spannable;
import android.text.SpannableString;
import android.text.Spanned;
import android.text.TextUtils;
import android.text.method.LinkMovementMethod;
import android.text.style.ClickableSpan;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.MarkDownParser;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.FontSizesConfig;
import io.adaptivecards.objectmodel.HorizontalAlignment;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.TextBlock;
import io.adaptivecards.objectmodel.TextSize;
import io.adaptivecards.objectmodel.TextWeight;
import io.adaptivecards.renderer.BaseCardElementRenderer;

import org.xml.sax.XMLReader;

import java.util.HashMap;
import java.util.Vector;

public class TextBlockRenderer extends BaseCardElementRenderer
{
    private TextBlockRenderer()
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

    static void setTextSize(Context context, TextView textView, TextSize textSize, HostConfig hostConfig)
    {
        FontSizesConfig fontSizesConfig = hostConfig.getFontSizes();
        if (textSize == TextSize.ExtraLarge)
        {
            textView.setTextSize(fontSizesConfig.getExtraLargeFontSize());
        }
        else if (textSize == TextSize.Large)
        {
            textView.setTextSize(fontSizesConfig.getLargeFontSize());
        }
        else if (textSize == TextSize.Medium)
        {
            textView.setTextSize(fontSizesConfig.getMediumFontSize());
        }
        else if (textSize == TextSize.Default)
        {
            textView.setTextSize(fontSizesConfig.getDefaultFontSize());
        }
        else if (textSize == TextSize.Small)
        {
            textView.setTextSize(fontSizesConfig.getSmallFontSize());
        }
        else
        {
            throw new IllegalArgumentException("Unknown text size: " + textSize.toString());
        }
    }

    static void setTextAlignment(TextView textView, HorizontalAlignment textAlignment)
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

        textView.setGravity(alignment);
    }

    void setTextFormat(TextView textView, String textFamily, TextWeight textWeight)
    {
        textView.setTypeface(Typeface.create(textFamily, Typeface.NORMAL), m_textWeightMap.get(textWeight));
    }

    static void setTextColor(TextView textView, ForegroundColor foregroundColor, HostConfig hostConfig, boolean isSubtle, ContainerStyle containerStyle)
    {
        if (containerStyle == ContainerStyle.Emphasis)
        {
            textView.setTextColor(getColor(foregroundColor, hostConfig.getContainerStyles().getEmphasisPalette().getForegroundColors(), isSubtle));
        }
        else
        {
            textView.setTextColor(getColor(foregroundColor, hostConfig.getContainerStyles().getDefaultPalette().getForegroundColors(), isSubtle));
        }
    }

    // Class to replace ul and li tags
    public class UlTagHandler implements Html.TagHandler{
        @Override
        public void handleTag(boolean opening, String tag, Editable output,
                              XMLReader xmlReader) {
            if(tag.equals("ul") && !opening) output.append("\n");
            if(tag.equals("li") && opening) output.append("\n\t• ");
        }
    }

    private CharSequence trimHtmlString(Spanned htmlString)
    {
        int numToRemoveFromEnd = 0;
        int numToRemoveFromStart = 0;

        for (int i = htmlString.length()-1; i >= 0; --i)
        {
            if (htmlString.charAt(i) == '\n')
            {
                numToRemoveFromEnd++;
            }
            else
            {
                break;
            }
        }

        for (int i = 0; i <= htmlString.length()-1; ++i)
        {
            if (htmlString.charAt(i) == '\n')
            {
                numToRemoveFromStart++;
            }
            else
            {
                break;
            }
        }

        //Sanity check
        if (numToRemoveFromStart + numToRemoveFromEnd >= htmlString.length())
        {
            return htmlString;
        }

        return htmlString.subSequence(numToRemoveFromStart, htmlString.length()-numToRemoveFromEnd);
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
            ContainerStyle containerStyle)
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

        DateTimeParser parser = new DateTimeParser(textBlock.GetLanguage());
        String textWithFormattedDates = parser.GenerateString(textBlock.GetTextForDateParsing());

        MarkDownParser markDownParser = new MarkDownParser(textWithFormattedDates);
        String textString = markDownParser.TransformToHtml();
        Spanned htmlString;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N)
        {
            htmlString = Html.fromHtml(textString, Html.FROM_HTML_MODE_COMPACT, null, new UlTagHandler());
        }
        else
        {
            // Before Android N, html.fromHtml adds two newline characters to end of string
            htmlString = Html.fromHtml(textString, null, new UlTagHandler());
        }
        textView.setText(trimHtmlString(htmlString));
        textView.setSingleLine(!textBlock.GetWrap());
        textView.setEllipsize(TextUtils.TruncateAt.END);
        textView.setOnTouchListener(new TouchTextView(new SpannableString(trimHtmlString(htmlString))));
        textView.setHorizontallyScrolling(false);
        setTextFormat(textView, hostConfig.getFontFamily(), textBlock.GetTextWeight());
        setTextSize(context, textView, textBlock.GetTextSize(), hostConfig);
        setSpacingAndSeparator(context, viewGroup, textBlock.GetSpacing(), textBlock.GetSeparator(), hostConfig, true);
        setTextColor(textView, textBlock.GetTextColor(), hostConfig, textBlock.GetIsSubtle(), containerStyle);
        setTextAlignment(textView, textBlock.GetHorizontalAlignment());

        if( textBlock.GetHeight() == HeightType.Stretch )
        {
            textView.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1));
        }
        else
        {
            textView.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        }

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
