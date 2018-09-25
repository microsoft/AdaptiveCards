package io.adaptivecards.renderer.readonly;

import android.os.Build;
import android.text.Html;
import android.text.Spanned;

import io.adaptivecards.objectmodel.MarkDownParser;

public class RendererUtil {

    public static CharSequence handleSpecialText(String textWithFormattedDates)
    {
        MarkDownParser markDownParser = new MarkDownParser(textWithFormattedDates);
        String textString = markDownParser.TransformToHtml();
        Spanned htmlString;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N)
        {
            htmlString = Html.fromHtml(textString, Html.FROM_HTML_MODE_COMPACT, null, new TextBlockRenderer.UlTagHandler());
        }
        else
        {
            // Before Android N, html.fromHtml adds two newline characters to end of string
            htmlString = Html.fromHtml(textString, null, new TextBlockRenderer.UlTagHandler());
        }
        return trimHtmlString(htmlString);
    }

    public static CharSequence trimHtmlString(Spanned htmlString)
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


}
