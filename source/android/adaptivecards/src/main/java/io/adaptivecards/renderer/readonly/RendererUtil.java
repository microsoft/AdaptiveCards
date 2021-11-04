// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.os.Build;
import android.text.Editable;
import android.text.Html;
import android.text.Spanned;

import org.xml.sax.Attributes;
import org.xml.sax.ContentHandler;
import org.xml.sax.Locator;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;

import java.util.ArrayDeque;
import java.util.Calendar;
import java.util.GregorianCalendar;

import io.adaptivecards.objectmodel.DateTimePreparser;
import io.adaptivecards.objectmodel.HorizontalAlignment;
import io.adaptivecards.objectmodel.MarkDownParser;
import io.adaptivecards.renderer.RenderArgs;

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
    public static class UlTagHandler implements Html.TagHandler, ContentHandler
    {
        private int tagNumber = 0;
        private boolean orderedList = false;
        private ContentHandler defaultContentHandler = null;
        private Editable text = null;
        private ArrayDeque<Boolean> tagStatusQueue = new ArrayDeque<>();

        private String getAttribute(String attributeName, Attributes attributes)
        {
            return attributes.getValue(attributeName);
        }

        public boolean handleTag(boolean opening, String tag, Editable output, Attributes attributes)
        {
            boolean tagWasHandled = false;

            if (tag.equals("ul") && !opening)
            {
                output.append("\n");
                tagWasHandled = true;
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
                tagWasHandled = true;
            }

            if (tag.equals("ol") && opening)
            {
                orderedList = true;
                String tagNumberString = getAttribute("start", attributes);

                int retrievedTagNumber = 1;
                if (tagNumberString != null)
                {
                    retrievedTagNumber = Integer.parseInt(tagNumberString);
                }

                tagNumber = retrievedTagNumber;
                tagWasHandled = true;
            }

            return tagWasHandled;
        }

        @Override
        public void handleTag(boolean opening, String tag, Editable output, XMLReader xmlReader)
        {
            if (defaultContentHandler == null)
            {
                // save input text
                text = output;

                // store default XMLReader object
                defaultContentHandler = xmlReader.getContentHandler();

                // replace content handler with our own that forwards to calls to default when needed
                xmlReader.setContentHandler(this);

                // handle endElement() callback for <inject/> tag
                tagStatusQueue.addLast(Boolean.FALSE);
            }
        }

        // ContentHandler override methods
        @Override
        public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException
        {
            boolean isHandled = handleTag(true, localName, text, attributes);
            tagStatusQueue.addLast(isHandled);

            if (!isHandled)
            {
                defaultContentHandler.startElement(uri, localName, qName, attributes);
            }
        }

        @Override
        public void endElement(String uri, String localName, String qName) throws SAXException
        {
            if (!tagStatusQueue.removeLast())
            {
                defaultContentHandler.endElement(uri, localName, qName);
            }

            handleTag(false, localName, text, (Attributes)null);
        }

        @Override
        public void setDocumentLocator(Locator locator)
        {
            defaultContentHandler.setDocumentLocator(locator);
        }

        @Override
        public void startDocument() throws SAXException
        {
            defaultContentHandler.startDocument();
        }

        @Override
        public void endDocument() throws SAXException
        {
            defaultContentHandler.endDocument();
        }

        @Override
        public void startPrefixMapping(String prefix, String uri) throws SAXException
        {
            defaultContentHandler.startPrefixMapping(prefix, uri);
        }

        @Override
        public void endPrefixMapping(String prefix) throws SAXException
        {
            defaultContentHandler.endPrefixMapping(prefix);
        }

        @Override
        public void characters(char[] chars, int start, int length) throws SAXException {
            defaultContentHandler.characters(chars, start, length);
        }

        @Override
        public void ignorableWhitespace(char[] chars, int start, int length) throws SAXException
        {
            defaultContentHandler.ignorableWhitespace(chars, start, length);
        }

        @Override
        public void processingInstruction(String target, String data) throws SAXException
        {
            defaultContentHandler.processingInstruction(target, data);
        }

        @Override
        public void skippedEntity(String name) throws SAXException
        {
            defaultContentHandler.skippedEntity(name);
        }
    }

    static HorizontalAlignment computeHorizontalAlignment(HorizontalAlignment declaredAlignment, RenderArgs renderArgs)
    {
        if (declaredAlignment != null)
        {
            return declaredAlignment;
        }
        if (renderArgs != null && renderArgs.getHorizontalAlignment() != null)
        {
            return renderArgs.getHorizontalAlignment();
        }
        return HorizontalAlignment.Left;
    }
}
