// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.os.Build;
import android.text.Editable;
import android.text.Html;
import android.text.Spanned;

import org.xml.sax.XMLReader;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

import io.adaptivecards.objectmodel.DateTimePreparser;
import io.adaptivecards.objectmodel.MarkDownParser;

public class RendererUtil
{
    public static boolean isValidDate(String s)
    {
        long[] year = {0}, month = {0}, day = {0};
        return DateTimePreparser.TryParseSimpleDate(s, year, month, day);
    }

    public static Calendar getDate(String s)
    {
        Calendar calendar = new GregorianCalendar();

        long[] year = {0}, month = {0}, day = {0};
        if (DateTimePreparser.TryParseSimpleDate(s, year, month, day))
        {
            // The month must be subtracted one as java.util.Calendar class starts indexing the months at 0
            calendar.set((int)year[0], (int)month[0] - 1, (int)day[0]);
        }

        return calendar;
    }

    public static boolean isValidTime(String s)
    {
        long[] hour = {0}, minutes = {0};
        return DateTimePreparser.TryParseSimpleTime(s, hour, minutes);
    }

    public static Calendar getTime(String s)
    {
        Calendar calendar = new GregorianCalendar();
        long[] hour = {0}, minutes = {0};

        if (DateTimePreparser.TryParseSimpleTime(s, hour, minutes))
        {
            calendar.set(Calendar.HOUR_OF_DAY, (int)hour[0]);
            calendar.set(Calendar.MINUTE, (int)minutes[0]);
            calendar.set(Calendar.SECOND, 0);
        }

        return calendar;
    }

    public static CharSequence handleSpecialText(String textWithFormattedDates)
    {
        MarkDownParser markDownParser = new MarkDownParser(textWithFormattedDates);
        String textString = markDownParser.TransformToHtml();

        // preprocess string to change <li> to <listItem> so we get a chance to handle them
        textString = textString.replace("<li>", "<listItem>");
        textString = textString.replaceAll("(" + System.lineSeparator() + "|\r\n|\n\r|\r|\n)", "<br/>");

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

    // Class to replace ul and li tags
    public static class UlTagHandler implements Html.TagHandler
    {
        private int tagNumber = 0;
        private boolean orderedList = false;

        @Override
        public void handleTag(boolean opening, String tag, Editable output, XMLReader xmlReader)
        {
            if (tag.equals("ul") && !opening)
            {
                output.append("\n");
            }

            if (tag.equals("listItem") && opening)
            {
                if (orderedList)
                {
                    output.append("\n");
                    output.append(String.valueOf(tagNumber));
                    output.append(". ");
                    tagNumber++;
                }
                else
                {
                    output.append("\n• ");
                }
            }

            if (tag.equals("ol") && opening)
            {
                orderedList = true;
                tagNumber = 1;
            }
        }
    }
}
