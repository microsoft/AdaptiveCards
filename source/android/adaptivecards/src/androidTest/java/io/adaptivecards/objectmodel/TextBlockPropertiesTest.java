package io.adaptivecards.objectmodel;

import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;

import java.util.ArrayList;

public class TextBlockPropertiesTest
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

        TextBlock textBlock = new TextBlock();

        textBlock.SetFontType(FontType.Monospace);
        textBlock.SetHorizontalAlignment(HorizontalAlignment.Center);
        textBlock.SetIsSubtle(true);
        textBlock.SetMaxLines(1);
        textBlock.SetText("Sample text");
        textBlock.SetTextColor(ForegroundColor.Accent);
        textBlock.SetTextSize(TextSize.Large);
        textBlock.SetTextWeight(TextWeight.Bolder);
        textBlock.SetWrap(true);

        Assert.assertEquals(textBlockNoDefaultValues, textBlock.Serialize());
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
    public void FontTypeTest() throws Exception
    {
        final String textBlockMonospaceFontType = "{\"fontType\":\"Monospace\",\"text\":\"\",\"type\":\"TextBlock\"}\n";

        ArrayList<Pair<FontType, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(FontType.Default, s_defaultTextBlock));
        tests.add(new Pair<>(FontType.Monospace, textBlockMonospaceFontType));

        for (Pair<FontType, String> testTuple : tests)
        {
            TextBlock textBlock = new TextBlock();
            textBlock.SetFontType(testTuple.first);
            Assert.assertEquals(testTuple.second, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first, parsedTextBlock.GetFontType());
        }
    }

    @Test
    public void HorizontalAlignmentTest() throws Exception
    {
        final String textBlockCenterAlignment = "{\"horizontalAlignment\":\"center\",\"text\":\"\",\"type\":\"TextBlock\"}\n";
        final String textBlockRightAlignment = "{\"horizontalAlignment\":\"right\",\"text\":\"\",\"type\":\"TextBlock\"}\n";

        ArrayList<Pair<HorizontalAlignment, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(HorizontalAlignment.Left, s_defaultTextBlock));
        tests.add(new Pair<>(HorizontalAlignment.Center, textBlockCenterAlignment));
        tests.add(new Pair<>(HorizontalAlignment.Right, textBlockRightAlignment));

        for (Pair<HorizontalAlignment, String> testTuple : tests)
        {
            TextBlock textBlock = new TextBlock();
            textBlock.SetHorizontalAlignment(testTuple.first);
            Assert.assertEquals(testTuple.second, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first, parsedTextBlock.GetHorizontalAlignment());
        }
    }

    @Test
    public void IsSubtleTest() throws Exception
    {
        final String textBlockTrueIsSubtle = "{\"isSubtle\":true,\"text\":\"\",\"type\":\"TextBlock\"}\n";

        ArrayList<Pair<Boolean, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(false, s_defaultTextBlock));
        tests.add(new Pair<>(true, textBlockTrueIsSubtle));

        for (Pair<Boolean, String> testTuple : tests)
        {
            TextBlock textBlock = new TextBlock();
            textBlock.SetIsSubtle(testTuple.first);
            Assert.assertEquals(testTuple.second, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals((boolean)testTuple.first, parsedTextBlock.GetIsSubtle());
        }
    }

    @Test
    public void MaxLinesTest() throws Exception
    {
        TextBlock textBlock = new TextBlock();
        textBlock.SetMaxLines(0);
        Assert.assertEquals(s_defaultTextBlock, textBlock.Serialize());

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(s_defaultTextBlock), "1.0");
        TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(0, parsedTextBlock.GetMaxLines());

        final String textBlockMaxLines = "{\"maxLines\":%d,\"text\":\"\",\"type\":\"TextBlock\"}\n";
        long[] tests = {1, 5, 10};
        for (int i = 1; i < tests.length; ++i)
        {
            String maxLinesJson = String.format(textBlockMaxLines, tests[i]);

            textBlock.SetMaxLines(tests[i]);
            Assert.assertEquals(maxLinesJson, textBlock.Serialize());

            result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(maxLinesJson), "1.0");
            parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(tests[i], parsedTextBlock.GetMaxLines());
        }
    }

    @Test
    public void TextTest() throws Exception
    {
        TextBlock textBlock = new TextBlock();
        textBlock.SetText("");
        Assert.assertEquals(s_defaultTextBlock, textBlock.Serialize());

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(s_defaultTextBlock), "1.0");
        TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals("", parsedTextBlock.GetText());

        final String textBlockText = "{\"text\":\"%s\",\"type\":\"TextBlock\"}\n";
        String tests[] = {"Sample text", "{{DATE(2017-02-14T06:08:39Z,LONG)}}", "This is some **bold** text"};

        for (int i = 0; i < tests.length; ++i)
        {
            String textBlockJson = String.format(textBlockText, tests[i]);

            textBlock.SetText(tests[i]);
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(tests[i], parsedTextBlock.GetText());
        }
    }

    @Test
    public void TextColorTest() throws Exception
    {
        final String textBlockAccentTextColor = "{\"color\":\"Accent\",\"text\":\"\",\"type\":\"TextBlock\"}\n";
        final String textBlockAttentionTextColor = "{\"color\":\"Attention\",\"text\":\"\",\"type\":\"TextBlock\"}\n";
        final String textBlockDarkTextColor = "{\"color\":\"Dark\",\"text\":\"\",\"type\":\"TextBlock\"}\n";
        final String textBlockGoodTextColor = "{\"color\":\"Good\",\"text\":\"\",\"type\":\"TextBlock\"}\n";
        final String textBlockLightTextColor = "{\"color\":\"Light\",\"text\":\"\",\"type\":\"TextBlock\"}\n";
        final String textBlockWarningTextColor = "{\"color\":\"Warning\",\"text\":\"\",\"type\":\"TextBlock\"}\n";

        ArrayList<Pair<ForegroundColor, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(ForegroundColor.Default, s_defaultTextBlock));
        tests.add(new Pair<>(ForegroundColor.Accent, textBlockAccentTextColor));
        tests.add(new Pair<>(ForegroundColor.Attention, textBlockAttentionTextColor));
        tests.add(new Pair<>(ForegroundColor.Dark, textBlockDarkTextColor));
        tests.add(new Pair<>(ForegroundColor.Good, textBlockGoodTextColor));
        tests.add(new Pair<>(ForegroundColor.Light, textBlockLightTextColor));
        tests.add(new Pair<>(ForegroundColor.Warning, textBlockWarningTextColor));

        for (Pair<ForegroundColor, String> testTuple : tests)
        {
            TextBlock textBlock = new TextBlock();
            textBlock.SetTextColor(testTuple.first);
            Assert.assertEquals(testTuple.second, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first, parsedTextBlock.GetTextColor());
        }
    }

    @Test
    public void TextSizeTest() throws Exception
    {
        final String textBlockSmallTextSize = "{\"size\":\"Small\",\"text\":\"\",\"type\":\"TextBlock\"}\n";
        final String textBlockMediumTextSize = "{\"size\":\"Medium\",\"text\":\"\",\"type\":\"TextBlock\"}\n";
        final String textBlockLargeTextSize = "{\"size\":\"Large\",\"text\":\"\",\"type\":\"TextBlock\"}\n";
        final String textBlockExtraLargeTextSize = "{\"size\":\"ExtraLarge\",\"text\":\"\",\"type\":\"TextBlock\"}\n";

        ArrayList<Pair<TextSize, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(TextSize.Default, s_defaultTextBlock));
        tests.add(new Pair<>(TextSize.Small, textBlockSmallTextSize));
        tests.add(new Pair<>(TextSize.Medium, textBlockMediumTextSize));
        tests.add(new Pair<>(TextSize.Large, textBlockLargeTextSize));
        tests.add(new Pair<>(TextSize.ExtraLarge, textBlockExtraLargeTextSize));

        for (Pair<TextSize, String> testTuple : tests)
        {
            TextBlock textBlock = new TextBlock();
            textBlock.SetTextSize(testTuple.first);
            Assert.assertEquals(testTuple.second, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first, parsedTextBlock.GetTextSize());
        }
    }

    @Test
    public void TextWeightTest() throws Exception
    {
        final String textBlockSmallTextSize = "{\"text\":\"\",\"type\":\"TextBlock\",\"weight\":\"Bolder\"}\n";
        final String textBlockMediumTextSize = "{\"text\":\"\",\"type\":\"TextBlock\",\"weight\":\"Lighter\"}\n";

        ArrayList<Pair<TextWeight, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(TextWeight.Default, s_defaultTextBlock));
        tests.add(new Pair<>(TextWeight.Bolder, textBlockSmallTextSize));
        tests.add(new Pair<>(TextWeight.Lighter, textBlockMediumTextSize));

        for (Pair<TextWeight, String> testTuple : tests)
        {
            TextBlock textBlock = new TextBlock();
            textBlock.SetTextWeight(testTuple.first);
            Assert.assertEquals(testTuple.second, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first, parsedTextBlock.GetTextWeight());
        }
    }

    @Test
    public void WrapTest() throws Exception
    {
        final String textBlockTrueWrap = "{\"text\":\"\",\"type\":\"TextBlock\",\"wrap\":true}\n";

        ArrayList<Pair<Boolean, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(false, s_defaultTextBlock));
        tests.add(new Pair<>(true, textBlockTrueWrap));

        for (Pair<Boolean, String> testTuple : tests)
        {
            TextBlock textBlock = new TextBlock();
            textBlock.SetWrap(testTuple.first);
            Assert.assertEquals(testTuple.second, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals((boolean)testTuple.first, parsedTextBlock.GetWrap());
        }
    }

    // This string is the result for an empty textblock or a textblock with all default values
    public static final String s_defaultTextBlock = "{\"text\":\"\",\"type\":\"TextBlock\"}\n";

}
