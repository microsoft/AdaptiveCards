package io.adaptivecards.objectmodel;

import android.graphics.Color;
import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;

import java.util.ArrayList;

import static org.junit.Assert.*;

/**
 * Class for testing RichTextBlock and TextRun properties
 */
public class RichTextBlockPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {
        final String textBlockNoDefaultValues =
            "{\"color\":\"Accent\"," +
                "\"fontType\":\"Monospace\"," +
                "\"horizontalAlignment\":\"center\"," +
                "\"isSubtle\":true," +
                "\"maxLines\":1," +
                "\"size\":\"Large\"," +
                "\"text\":\"Sample text\"," +
                "\"type\":\"TextBlock\"," +
                "\"weight\":\"Bolder\"," +
                "\"wrap\":true}\n";

        TextRun textRun = TestUtil.createMockTextRun("Test Run");
        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun);
        /*
        richTextBlock.SetHorizontalAlignment(HorizontalAlignment.Center);
        textRun.SetText();
        textRun.SetFontType();
        textRun.SetHighlight();
        textRun.SetIsSubtle();
        textRun.SetItalic();
        textRun.SetLanguage();
        textRun.SetSelectAction();
        textRun.SetStrikethrough();
        textRun.SetTextColor();
        textRun.SetTextSize();
        textRun.SetTextWeight();
*/
        Assert.assertEquals(textBlockNoDefaultValues, richTextBlock.Serialize());
    }

    @Test
    public void TextRunAllPropertiesTest()
    {
        final String textBlockNoDefaultValues =
            "{\"color\":\"Accent\"," +
                "\"fontType\":\"Monospace\"," +
                "\"horizontalAlignment\":\"center\"," +
                "\"isSubtle\":true," +
                "\"maxLines\":1," +
                "\"size\":\"Large\"," +
                "\"text\":\"Sample text\"," +
                "\"type\":\"TextBlock\"," +
                "\"weight\":\"Bolder\"," +
                "\"wrap\":true}\n";

        TextRun textRun = TestUtil.createMockTextRun("Test Run");
        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun);
        richTextBlock.SetHorizontalAlignment(HorizontalAlignment.Center);
        textRun.SetText("Test Run");
        textRun.SetFontType(FontType.Monospace);
        textRun.SetHighlight(true);
        textRun.SetIsSubtle(true);
        textRun.SetItalic(true);
        textRun.SetLanguage("");
        textRun.SetSelectAction(TestUtil.createSampleOpenUrlAction());
        textRun.SetStrikethrough(true);
        textRun.SetTextColor(ForegroundColor.Accent);
        textRun.SetTextSize(TextSize.Medium);
        textRun.SetTextWeight(TextWeight.Bolder);

        Assert.assertEquals(textBlockNoDefaultValues, richTextBlock.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest()
    {
        final String textBlockNoDefaultValues =
            "{\"color\":\"Accent\"," +
                "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"fontType\":\"Monospace\"," +
                "\"height\":\"Stretch\"," +
                "\"horizontalAlignment\":\"center\"," +
                "\"id\":\"Sample id\"," +
                "\"isSubtle\":true," +
                "\"isVisible\":false," +
                "\"maxLines\":1," +
                "\"separator\":true," +
                "\"size\":\"Large\"," +
                "\"spacing\":\"medium\"," +
                "\"text\":\"Sample text\"," +
                "\"type\":\"TextBlock\"," +
                "\"weight\":\"Bolder\"," +
                "\"wrap\":true}\n";

        TextBlock textBlock = new TextBlock();

        textBlock.SetFallbackType(FallbackType.Content);
        textBlock.SetFallbackContent(TestUtil.createMockImage());
        textBlock.SetFontType(FontType.Monospace);
        textBlock.SetHeight(HeightType.Stretch);
        textBlock.SetHorizontalAlignment(HorizontalAlignment.Center);
        textBlock.SetId("Sample id");
        textBlock.SetIsSubtle(true);
        textBlock.SetIsVisible(false);
        textBlock.SetMaxLines(1);
        textBlock.SetSeparator(true);
        textBlock.SetSpacing(Spacing.Medium);
        textBlock.SetText("Sample text");
        textBlock.SetTextColor(ForegroundColor.Accent);
        textBlock.SetTextSize(TextSize.Large);
        textBlock.SetTextWeight(TextWeight.Bolder);
        textBlock.SetWrap(true);

        Assert.assertEquals(textBlockNoDefaultValues, textBlock.Serialize());
    }

    @Test
    public void TextTest() throws Exception
    {
        final String textBlockMonospaceFontType =
            "{\"inlines\":[" +
                "{\"text\":\"q\",\"type\":\"TextRun\"}," +
                "{\"text\":\"Test Run\",\"type\":\"TextRun\"}," +
                "{\"text\":\"{{DATE(2017-02-14T06:08:39Z,LONG)}}\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is some **bold** text\",\"type\":\"TextRun\"}," +
                "\"type\":\"RichTextBlock\"}\n";

        String tests[] = {"q", "Test Run", "{{DATE(2017-02-14T06:08:39Z,LONG)}}", "This is some **bold** text"};
        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock();

        for (int i = 0; i < tests.length; ++i)
        {
            richTextBlock.GetInlines().add(TestUtil.createMockTextRun(tests[i]));
        }

        // TODO: this test is broken due to the Serialize method failing
        richTextBlock.Serialize();

        Assert.assertEquals(textBlockMonospaceFontType, "");

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockMonospaceFontType), "1.0");
        RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        InlineVector inlines = parsedRichTextBlock.GetInlines();

        for (int i = 0; i < tests.length; ++i)
        {
            TextRun textRun = TestUtil.castToTextRun(inlines.get(i));
            Assert.assertEquals(tests[i], textRun.GetText());
        }
    }



}
