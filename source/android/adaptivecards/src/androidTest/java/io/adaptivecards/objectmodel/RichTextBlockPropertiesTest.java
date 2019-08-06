package io.adaptivecards.objectmodel;

import android.graphics.Color;
import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;
import org.w3c.dom.Text;

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
        final String richTextBlockNoDefaultValues =
            "{\"horizontalAlignment\":\"center\"," +
                "\"inlines\":[{\"text\":\"Test Run\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        TextRun textRun = TestUtil.createMockTextRun("Test Run");
        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun);
        richTextBlock.SetHorizontalAlignment(HorizontalAlignment.Center);

        Assert.assertEquals(richTextBlockNoDefaultValues, richTextBlock.Serialize());
    }

    @Test
    public void TextRunAllPropertiesTest()
    {
        final String richTextBlockNoDefaultValues =
            "{\"horizontalAlignment\":\"center\"," +
                "\"inlines\":[" +
                    "{\"color\":\"Accent\"," +
                    "\"fontType\":\"Monospace\"," +
                    "\"highlight\":true," +
                    "\"isSubtle\":true,"+
                    "\"italic\":true," +
                    "\"selectAction\":{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}," +
                    "\"size\":\"Medium\"," +
                    "\"strikethrough\":true," +
                    "\"text\":\"Test Run\"," +
                    "\"type\":\"TextRun\"," +
                    "\"weight\":\"Bolder\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        TextRun textRun = TestUtil.createMockTextRun("Test Run");
        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun);
        richTextBlock.SetHorizontalAlignment(HorizontalAlignment.Center);
        textRun.SetText("Test Run");
        textRun.SetFontType(FontType.Monospace);
        textRun.SetHighlight(true);
        textRun.SetIsSubtle(true);
        textRun.SetItalic(true);
        textRun.SetSelectAction(TestUtil.createSampleOpenUrlAction());
        textRun.SetStrikethrough(true);
        textRun.SetTextColor(ForegroundColor.Accent);
        textRun.SetTextSize(TextSize.Medium);
        textRun.SetTextWeight(TextWeight.Bolder);

        Assert.assertEquals(richTextBlockNoDefaultValues, richTextBlock.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest()
    {
        final String richTextBlockNoDefaultValues =
            "{\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"horizontalAlignment\":\"center\"," +
                "\"id\":\"Sample id\"," +
                "\"inlines\":[" +
                "{\"color\":\"Accent\"," +
                "\"fontType\":\"Monospace\"," +
                "\"highlight\":true," +
                "\"isSubtle\":true,"+
                "\"italic\":true," +
                "\"selectAction\":{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}," +
                "\"size\":\"Medium\"," +
                "\"strikethrough\":true," +
                "\"text\":\"Test Run\"," +
                "\"type\":\"TextRun\"," +
                "\"weight\":\"Bolder\"}]," +
                "\"isVisible\":false," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"type\":\"RichTextBlock\"}\n";

        TextRun textRun = TestUtil.createMockTextRun("Test Run");
        textRun.SetText("Test Run");
        textRun.SetFontType(FontType.Monospace);
        textRun.SetHighlight(true);
        textRun.SetIsSubtle(true);
        textRun.SetItalic(true);
        textRun.SetSelectAction(TestUtil.createSampleOpenUrlAction());
        textRun.SetStrikethrough(true);
        textRun.SetTextColor(ForegroundColor.Accent);
        textRun.SetTextSize(TextSize.Medium);
        textRun.SetTextWeight(TextWeight.Bolder);

        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun);
        richTextBlock.SetFallbackType(FallbackType.Content);
        richTextBlock.SetFallbackContent(TestUtil.createMockImage());
        richTextBlock.SetHeight(HeightType.Stretch);
        richTextBlock.SetHorizontalAlignment(HorizontalAlignment.Center);
        richTextBlock.SetId("Sample id");
        richTextBlock.SetIsVisible(false);
        richTextBlock.SetSeparator(true);
        richTextBlock.SetSpacing(Spacing.Medium);

        Assert.assertEquals(richTextBlockNoDefaultValues, richTextBlock.Serialize());
    }

    /**
     * RichTextBlock test
     * @throws Exception
     */
    @Test
    public void HorizontalAlignmentTest() throws Exception
    {
        final String defaultHorizontalAlignment =
            "{\"inlines\":[{\"text\":\"This is a sample TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        {
            RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock("This is a sample TextRun");
            Assert.assertEquals(defaultHorizontalAlignment, richTextBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(defaultHorizontalAlignment), "1.0");
            RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(HorizontalAlignment.Left, parsedRichTextBlock.GetHorizontalAlignment());
        }

        {
            final String richTextBlockTestInlineText =
                "{\"horizontalAlignment\":\"%s\"," +
                    "\"inlines\":[{\"text\":\"This is a sample TextRun\",\"type\":\"TextRun\"}]," +
                    "\"type\":\"RichTextBlock\"}\n";

            ArrayList<Pair<HorizontalAlignment, String>> tests = new ArrayList<>();
            tests.add(new Pair<>(HorizontalAlignment.Left, defaultHorizontalAlignment));
            tests.add(new Pair<>(HorizontalAlignment.Center, String.format(richTextBlockTestInlineText, "center")));
            tests.add(new Pair<>(HorizontalAlignment.Right, String.format(richTextBlockTestInlineText, "right")));

            for (Pair<HorizontalAlignment, String> test : tests)
            {
                RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock("This is a sample TextRun");
                richTextBlock.SetHorizontalAlignment(test.first);
                Assert.assertEquals(test.second, richTextBlock.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(test.second), "1.0");
                RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(test.first, parsedRichTextBlock.GetHorizontalAlignment());
            }
        }
    }

    /**
     * TextRun test
     * @throws Exception
     */
    @Test
    public void FontTypeTest() throws Exception
    {
        final String richTextBlockFontType =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"fontType\":\"Monospace\",\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        TextRun textRun1 = TestUtil.createMockTextRun("This is the first TextRun");

        TextRun textRun2 = TestUtil.createMockTextRun("This is the second TextRun");
        textRun2.SetFontType(FontType.Default);

        TextRun textRun3 = TestUtil.createMockTextRun("This is the third TextRun");
        textRun3.SetFontType(FontType.Monospace);

        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun1, textRun2, textRun3);

        Assert.assertEquals(richTextBlockFontType, richTextBlock.Serialize());

        final String richTextBlockFontTypeWithDefaultFontType =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"fontType\":\"Default\",\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"fontType\":\"Monospace\",\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(richTextBlockFontTypeWithDefaultFontType), "1.0");
        RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(3, parsedRichTextBlock.GetInlines().size());

        TextRun textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(0));
        Assert.assertEquals(FontType.Default, textRun.GetFontType());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(1));
        Assert.assertEquals(FontType.Default, textRun.GetFontType());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(2));
        Assert.assertEquals(FontType.Monospace, textRun.GetFontType());
    }

    /**
     * TextRun test
     * @throws Exception
     */
    @Test
    public void HighlightTest() throws Exception
    {
        final String richTextBlockIsSubtleSerializeExpected =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"highlight\":true,\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        TextRun textRun1 = TestUtil.createMockTextRun("This is the first TextRun");

        TextRun textRun2 = TestUtil.createMockTextRun("This is the second TextRun");
        textRun2.SetHighlight(false);

        TextRun textRun3 = TestUtil.createMockTextRun("This is the third TextRun");
        textRun3.SetHighlight(true);

        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun1, textRun2, textRun3);

        Assert.assertEquals(richTextBlockIsSubtleSerializeExpected, richTextBlock.Serialize());


        final String richTextBlockIsSubtle =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"highlight\":false,\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"highlight\":true,\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(richTextBlockIsSubtle), "1.0");
        RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(3, parsedRichTextBlock.GetInlines().size());

        TextRun textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(0));
        Assert.assertEquals(false, textRun.GetHighlight());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(1));
        Assert.assertEquals(false, textRun.GetHighlight());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(2));
        Assert.assertEquals(true, textRun.GetHighlight());
    }

    /**
     * TextRun test
     * @throws Exception
     */
    @Test
    public void IsSubtleTest() throws Exception
    {
        final String richTextBlockIsSubtleSerializeExpected =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"isSubtle\":true,\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        TextRun textRun1 = TestUtil.createMockTextRun("This is the first TextRun");

        TextRun textRun2 = TestUtil.createMockTextRun("This is the second TextRun");
        textRun2.SetIsSubtle(false);

        TextRun textRun3 = TestUtil.createMockTextRun("This is the third TextRun");
        textRun3.SetIsSubtle(true);

        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun1, textRun2, textRun3);

        Assert.assertEquals(richTextBlockIsSubtleSerializeExpected, richTextBlock.Serialize());


        final String richTextBlockIsSubtle =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"isSubtle\":false,\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"isSubtle\":true,\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(richTextBlockIsSubtle), "1.0");
        RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(3, parsedRichTextBlock.GetInlines().size());

        TextRun textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(0));
        Assert.assertEquals(false, textRun.GetIsSubtle());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(1));
        Assert.assertEquals(false, textRun.GetIsSubtle());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(2));
        Assert.assertEquals(true, textRun.GetIsSubtle());
    }

    /**
     * TextRun test
     * @throws Exception
     */
    @Test
    public void ItalicTest() throws Exception
    {
        final String richTextBlockIsSubtleSerializeExpected =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"italic\":true,\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        TextRun textRun1 = TestUtil.createMockTextRun("This is the first TextRun");

        TextRun textRun2 = TestUtil.createMockTextRun("This is the second TextRun");
        textRun2.SetItalic(false);

        TextRun textRun3 = TestUtil.createMockTextRun("This is the third TextRun");
        textRun3.SetItalic(true);

        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun1, textRun2, textRun3);

        Assert.assertEquals(richTextBlockIsSubtleSerializeExpected, richTextBlock.Serialize());


        final String richTextBlockIsSubtle =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"italic\":false,\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"italic\":true,\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(richTextBlockIsSubtle), "1.0");
        RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(3, parsedRichTextBlock.GetInlines().size());

        TextRun textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(0));
        Assert.assertEquals(false, textRun.GetItalic());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(1));
        Assert.assertEquals(false, textRun.GetItalic());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(2));
        Assert.assertEquals(true, textRun.GetItalic());
    }

    /**
     * TextRun test
     * @throws Exception
     */
    @Test
    public void SelectActionTest() throws Exception
    {
        final String richTextBlockTextWeightSerializeExpected =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"selectAction\":{\"targetElements\":[\"id1\",{\"elementId\":\"id2\",\"isVisible\":true},{\"elementId\":\"id3\",\"isVisible\":false}],\"type\":\"Action.ToggleVisibility\"},\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}," +
                "{\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"},\"text\":\"This is the fourth TextRun\",\"type\":\"TextRun\"}," +
                "{\"selectAction\":{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"},\"text\":\"This is the fifth TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        TextRun textRun1 = TestUtil.createMockTextRun("This is the first TextRun");

        TextRun textRun2 = TestUtil.createMockTextRun("This is the second TextRun");
        textRun2.SetSelectAction(null);

        TextRun textRun3 = TestUtil.createMockTextRun("This is the third TextRun");
        textRun3.SetSelectAction(TestUtil.createSampleToggleVisibilityAction());

        TextRun textRun4 = TestUtil.createMockTextRun("This is the fourth TextRun");
        textRun4.SetSelectAction(TestUtil.createSampleSubmitAction());

        TextRun textRun5 = TestUtil.createMockTextRun("This is the fifth TextRun");
        textRun5.SetSelectAction(TestUtil.createSampleOpenUrlAction());

        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun1, textRun2, textRun3, textRun4, textRun5);

        Assert.assertEquals(richTextBlockTextWeightSerializeExpected, richTextBlock.Serialize());

        final String richTextBlockTextWeight =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"selectAction\":{\"targetElements\":[\"id1\",{\"elementId\":\"id2\",\"isVisible\":true}," +
                "{\"elementId\":\"id3\",\"isVisible\":false}],\"type\":\"Action.ToggleVisibility\"},\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"},\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}," +
                "{\"selectAction\":{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"},\"text\":\"This is the fourth TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(richTextBlockTextWeight), "1.0");
        RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(4, parsedRichTextBlock.GetInlines().size());

        TextRun textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(0));
        Assert.assertEquals(null, textRun.GetSelectAction());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(1));
        ToggleVisibilityAction toggleVisibilityAction = TestUtil.castToToggleVisibilityAction(textRun.GetSelectAction());
        Assert.assertEquals(3, toggleVisibilityAction.GetTargetElements().size());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(2));
        SubmitAction submitAction = TestUtil.castToSubmitAction(textRun.GetSelectAction());
        Assert.assertEquals("{\"data\":\"Some data\"}\n", submitAction.GetDataJson());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(3));
        OpenUrlAction openUrlAction = TestUtil.castToOpenUrlAction(textRun.GetSelectAction());
        Assert.assertEquals("http://", openUrlAction.GetUrl());
    }

    /**
     * TextRun test
     * @throws Exception
     */
    @Test
    public void StrikeThroughTest() throws Exception
    {
        final String richTextBlockStrikeThroughSerializeExpected =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"strikethrough\":true,\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        TextRun textRun1 = TestUtil.createMockTextRun("This is the first TextRun");

        TextRun textRun2 = TestUtil.createMockTextRun("This is the second TextRun");
        textRun2.SetStrikethrough(false);

        TextRun textRun3 = TestUtil.createMockTextRun("This is the third TextRun");
        textRun3.SetStrikethrough(true);

        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun1, textRun2, textRun3);

        Assert.assertEquals(richTextBlockStrikeThroughSerializeExpected, richTextBlock.Serialize());


        final String richTextBlockStrikeThrough =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"strikethrough\":false,\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"strikethrough\":true,\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(richTextBlockStrikeThrough), "1.0");
        RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(3, parsedRichTextBlock.GetInlines().size());

        TextRun textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(0));
        Assert.assertEquals(false, textRun.GetStrikethrough());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(1));
        Assert.assertEquals(false, textRun.GetStrikethrough());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(2));
        Assert.assertEquals(true, textRun.GetStrikethrough());
    }

    /**
     * TextRun test
     * @throws Exception
     */
    @Test
    public void TextTest() throws Exception
    {
        final String richTextBlockTestInlineText =
            "{\"inlines\":[" +
                "{\"text\":\"\",\"type\":\"TextRun\"}," +
                "{\"text\":\"Test Run\",\"type\":\"TextRun\"}," +
                "{\"text\":\"{{DATE(2017-02-14T06:08:39Z,LONG)}}\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is some **bold** text\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        String tests[] = {"", "Test Run", "{{DATE(2017-02-14T06:08:39Z,LONG)}}", "This is some **bold** text"};
        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock();

        for (int i = 0; i < tests.length; ++i)
        {
            richTextBlock.GetInlines().add(TestUtil.createMockTextRun(tests[i]));
        }

        Assert.assertEquals(richTextBlockTestInlineText, richTextBlock.Serialize());

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(richTextBlockTestInlineText), "1.0");
        RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        InlineVector inlines = parsedRichTextBlock.GetInlines();

        for (int i = 0; i < tests.length; ++i)
        {
            TextRun textRun = TestUtil.castToTextRun(inlines.get(i));
            Assert.assertEquals(tests[i], textRun.GetText());
        }
    }

    /**
     * TextRun test
     * @throws Exception
     */
    @Test
    public void TextColorTest() throws Exception
    {
        final String richTextBlockTextColorSerializeExpected =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Dark\",\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Light\",\"text\":\"This is the fourth TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Accent\",\"text\":\"This is the fifth TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Good\",\"text\":\"This is the sixth TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Warning\",\"text\":\"This is the seventh TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Attention\",\"text\":\"This is the eighth TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        TextRun textRun1 = TestUtil.createMockTextRun("This is the first TextRun");

        TextRun textRun2 = TestUtil.createMockTextRun("This is the second TextRun");
        textRun2.SetTextColor(ForegroundColor.Default);

        TextRun textRun3 = TestUtil.createMockTextRun("This is the third TextRun");
        textRun3.SetTextColor(ForegroundColor.Dark);

        TextRun textRun4 = TestUtil.createMockTextRun("This is the fourth TextRun");
        textRun4.SetTextColor(ForegroundColor.Light);

        TextRun textRun5 = TestUtil.createMockTextRun("This is the fifth TextRun");
        textRun5.SetTextColor(ForegroundColor.Accent);

        TextRun textRun6 = TestUtil.createMockTextRun("This is the sixth TextRun");
        textRun6.SetTextColor(ForegroundColor.Good);

        TextRun textRun7 = TestUtil.createMockTextRun("This is the seventh TextRun");
        textRun7.SetTextColor(ForegroundColor.Warning);

        TextRun textRun8 = TestUtil.createMockTextRun("This is the eighth TextRun");
        textRun8.SetTextColor(ForegroundColor.Attention);

        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun1, textRun2, textRun3,
            textRun4, textRun5, textRun6, textRun7, textRun8);

        Assert.assertEquals(richTextBlockTextColorSerializeExpected, richTextBlock.Serialize());

        final String richTextBlockTextColor =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Default\",\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Dark\",\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Light\",\"text\":\"This is the fourth TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Accent\",\"text\":\"This is the fifth TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Good\",\"text\":\"This is the sixth TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Warning\",\"text\":\"This is the seventh TextRun\",\"type\":\"TextRun\"}," +
                "{\"color\":\"Attention\",\"text\":\"This is the eighth TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(richTextBlockTextColor), "1.0");
        RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(8, parsedRichTextBlock.GetInlines().size());

        TextRun textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(0));
        Assert.assertEquals(ForegroundColor.Default, textRun.GetTextColor());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(1));
        Assert.assertEquals(ForegroundColor.Default, textRun.GetTextColor());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(2));
        Assert.assertEquals(ForegroundColor.Dark, textRun.GetTextColor());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(3));
        Assert.assertEquals(ForegroundColor.Light, textRun.GetTextColor());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(4));
        Assert.assertEquals(ForegroundColor.Accent, textRun.GetTextColor());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(5));
        Assert.assertEquals(ForegroundColor.Good, textRun.GetTextColor());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(6));
        Assert.assertEquals(ForegroundColor.Warning, textRun.GetTextColor());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(7));
        Assert.assertEquals(ForegroundColor.Attention, textRun.GetTextColor());
    }

    /**
     * TextRun test
     * @throws Exception
     */
    @Test
    public void TextSizeTest() throws Exception
    {
        final String richTextBlockTextSizeSerializeExpected =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"size\":\"Small\",\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}," +
                "{\"size\":\"Medium\",\"text\":\"This is the fourth TextRun\",\"type\":\"TextRun\"}," +
                "{\"size\":\"Large\",\"text\":\"This is the fifth TextRun\",\"type\":\"TextRun\"}," +
                "{\"size\":\"ExtraLarge\",\"text\":\"This is the sixth TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        TextRun textRun1 = TestUtil.createMockTextRun("This is the first TextRun");

        TextRun textRun2 = TestUtil.createMockTextRun("This is the second TextRun");
        textRun2.SetTextSize(TextSize.Default);

        TextRun textRun3 = TestUtil.createMockTextRun("This is the third TextRun");
        textRun3.SetTextSize(TextSize.Small);

        TextRun textRun4 = TestUtil.createMockTextRun("This is the fourth TextRun");
        textRun4.SetTextSize(TextSize.Medium);

        TextRun textRun5 = TestUtil.createMockTextRun("This is the fifth TextRun");
        textRun5.SetTextSize(TextSize.Large);

        TextRun textRun6 = TestUtil.createMockTextRun("This is the sixth TextRun");
        textRun6.SetTextSize(TextSize.ExtraLarge);

        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun1, textRun2, textRun3,
            textRun4, textRun5, textRun6);

        Assert.assertEquals(richTextBlockTextSizeSerializeExpected, richTextBlock.Serialize());

        final String richTextBlockTextSize =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"size\":\"Small\",\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"size\":\"Default\",\"text\":\"This is the third TextRun\",\"type\":\"TextRun\"}," +
                "{\"size\":\"Medium\",\"text\":\"This is the fourth TextRun\",\"type\":\"TextRun\"}," +
                "{\"size\":\"Large\",\"text\":\"This is the fifth TextRun\",\"type\":\"TextRun\"}," +
                "{\"size\":\"ExtraLarge\",\"text\":\"This is the sixth TextRun\",\"type\":\"TextRun\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(richTextBlockTextSize), "1.0");
        RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(6, parsedRichTextBlock.GetInlines().size());

        TextRun textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(0));
        Assert.assertEquals(TextSize.Default, textRun.GetTextSize());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(1));
        Assert.assertEquals(TextSize.Small, textRun.GetTextSize());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(2));
        Assert.assertEquals(TextSize.Default, textRun.GetTextSize());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(3));
        Assert.assertEquals(TextSize.Medium, textRun.GetTextSize());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(4));
        Assert.assertEquals(TextSize.Large, textRun.GetTextSize());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(5));
        Assert.assertEquals(TextSize.ExtraLarge, textRun.GetTextSize());
    }

    /**
     * TextRun test
     * @throws Exception
     */
    @Test
    public void TextWeightTest() throws Exception
    {
        final String richTextBlockTextWeightSerializeExpected =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is the second TextRun\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is the third TextRun\",\"type\":\"TextRun\",\"weight\":\"Lighter\"}," +
                "{\"text\":\"This is the fourth TextRun\",\"type\":\"TextRun\",\"weight\":\"Bolder\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        TextRun textRun1 = TestUtil.createMockTextRun("This is the first TextRun");

        TextRun textRun2 = TestUtil.createMockTextRun("This is the second TextRun");
        textRun2.SetTextWeight(TextWeight.Default);

        TextRun textRun3 = TestUtil.createMockTextRun("This is the third TextRun");
        textRun3.SetTextWeight(TextWeight.Lighter);

        TextRun textRun4 = TestUtil.createMockTextRun("This is the fourth TextRun");
        textRun4.SetTextWeight(TextWeight.Bolder);

        RichTextBlock richTextBlock = TestUtil.createMockRichTextBlock(textRun1, textRun2, textRun3, textRun4);

        Assert.assertEquals(richTextBlockTextWeightSerializeExpected, richTextBlock.Serialize());

        final String richTextBlockTextWeight =
            "{\"inlines\":[" +
                "{\"text\":\"This is the first TextRun\",\"type\":\"TextRun\"}," +
                "{\"text\":\"This is the second TextRun\",\"type\":\"TextRun\",\"weight\":\"Default\"}," +
                "{\"text\":\"This is the third TextRun\",\"type\":\"TextRun\",\"weight\":\"Lighter\"}," +
                "{\"text\":\"This is the fourth TextRun\",\"type\":\"TextRun\",\"weight\":\"Bolder\"}]," +
                "\"type\":\"RichTextBlock\"}\n";

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(richTextBlockTextWeight), "1.0");
        RichTextBlock parsedRichTextBlock = TestUtil.castToRichTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(4, parsedRichTextBlock.GetInlines().size());

        TextRun textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(0));
        Assert.assertEquals(TextWeight.Default, textRun.GetTextWeight());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(1));
        Assert.assertEquals(TextWeight.Default, textRun.GetTextWeight());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(2));
        Assert.assertEquals(TextWeight.Lighter, textRun.GetTextWeight());

        textRun = TestUtil.castToTextRun(parsedRichTextBlock.GetInlines().get(3));
        Assert.assertEquals(TextWeight.Bolder, textRun.GetTextWeight());
    }
}
