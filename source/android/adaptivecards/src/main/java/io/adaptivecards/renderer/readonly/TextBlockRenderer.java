package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Typeface;
import android.os.Build;
import android.support.v4.app.FragmentManager;
import android.text.Editable;
import android.text.Html;
import android.text.Spanned;
import android.text.TextUtils;
import android.text.method.LinkMovementMethod;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.ForegroundColor;
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
        else if (textSize.swigValue() == TextSize.Default.swigValue())
        {
            textView.setTextSize(fontSizesConfig.getDefaultFontSize());
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

    static void setTextColor(TextView textView, ForegroundColor foregroundColor, HostConfig hostConfig, boolean isSubtle, ContainerStyle containerStyle)
    {
        if (containerStyle.swigValue() == ContainerStyle.Emphasis.swigValue())
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
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N)
        {
            Spanned htmlString = Html.fromHtml(textString, Html.FROM_HTML_MODE_COMPACT, null, new UlTagHandler());
            textView.setText(trimHtmlString(htmlString));
        }
        else
        {
            // Before Android N, html.fromHtml adds two newline characters to end of string
            Spanned htmlString = Html.fromHtml(textString, null, new UlTagHandler());
            textView.setText(trimHtmlString(htmlString));
        }
        textView.setSingleLine(!textBlock.GetWrap());
        textView.setEllipsize(TextUtils.TruncateAt.END);
        textView.setMovementMethod(LinkMovementMethod.getInstance());
        textView.setHorizontallyScrolling(false);
        setTextWeight(textView, textBlock.GetTextWeight());
        setTextSize(context, textView, textBlock.GetTextSize(), hostConfig);
        setSpacingAndSeparator(context, viewGroup, textBlock.GetSpacing(), textBlock.GetSeparator(), hostConfig, true);
        setTextColor(textView, textBlock.GetTextColor(), hostConfig, textBlock.GetIsSubtle(), containerStyle);
        setTextAlignment(textView, textBlock.GetHorizontalAlignment());
        textView.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
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
