package io.adaptivecards.objectmodel;

import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;

import java.util.ArrayList;

public class BaseCardElementPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest() throws Exception
    {
        final String textBlockNoDefaultValues =
            "{\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"Sample id\"," +
                "\"isVisible\":false," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"text\":\"Test\"," +
                "\"type\":\"TextBlock\"}\n";

        TextBlock textBlock = TestUtil.createMockTextBlock("Test");
        textBlock.SetFallbackType(FallbackType.Content);
        textBlock.SetFallbackContent(TestUtil.createMockImage());
        textBlock.SetHeight(HeightType.Stretch);
        textBlock.SetId("Sample id");
        textBlock.SetIsVisible(false);
        textBlock.SetSeparator(true);
        textBlock.SetSpacing(Spacing.Medium);

        Assert.assertEquals(textBlockNoDefaultValues, textBlock.Serialize());
    }

    @Test
    public void FallbackContentTest() throws Exception
    {
        {
            final String textBlockJson = "{\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            TextBlock textBlock = TestUtil.createMockTextBlock("Test");
            textBlock.SetFallbackContent(null);
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(null, parsedTextBlock.GetFallbackContent());
        }

        {
            final String textBlockDropFallbackJson = "{\"fallback\":\"drop\",\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            TextBlock textBlock = TestUtil.createMockTextBlock("Test");
            textBlock.SetFallbackType(FallbackType.Drop);
            Assert.assertEquals(textBlockDropFallbackJson, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockDropFallbackJson), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(FallbackType.Drop, parsedTextBlock.GetFallbackType());
        }

        {
            final String textBlockImageFallbackJson = "{\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"},\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            TextBlock textBlock = TestUtil.createMockTextBlock("Test");
            textBlock.SetFallbackType(FallbackType.Content);
            textBlock.SetFallbackContent(TestUtil.createMockImage());
            Assert.assertEquals(textBlockImageFallbackJson, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockImageFallbackJson), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(FallbackType.Content, parsedTextBlock.GetFallbackType());

            BaseCardElement fallbackBaseCardElement = TestUtil.castToBaseCardElement(parsedTextBlock.GetFallbackContent());
            Image fallbackImage = TestUtil.castToImage(fallbackBaseCardElement);
            Assert.assertEquals("http://", fallbackImage.GetUrl());
        }

    }

    @Test
    public void HeightTest() throws Exception
    {
        {
            final String textBlockJson = "{\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            TextBlock textBlock = TestUtil.createMockTextBlock("Test");
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(HeightType.Auto, parsedTextBlock.GetHeight());

            textBlock = TestUtil.createMockTextBlock("Test");
            textBlock.SetHeight(HeightType.Auto);
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(HeightType.Auto, parsedTextBlock.GetHeight());
        }

        {
            final String textBlockJson = "{\"height\":\"Stretch\",\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            TextBlock textBlock = TestUtil.createMockTextBlock("Test");
            textBlock.SetHeight(HeightType.Stretch);
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(HeightType.Stretch, parsedTextBlock.GetHeight());
        }
    }

    @Test
    public void IdTest() throws Exception
    {
        {
            final String textBlockJson = "{\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            TextBlock textBlock = TestUtil.createMockTextBlock("Test");
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedTextBlock.GetId());

            textBlock = TestUtil.createMockTextBlock("Test");
            textBlock.SetId("");
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedTextBlock.GetId());
        }

        {
            final String textBlockJson = "{\"id\":\"Sample Id\",\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            TextBlock textBlock = TestUtil.createMockTextBlock("Test");
            textBlock.SetId("Sample Id");
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("Sample Id", parsedTextBlock.GetId());
        }
    }

    @Test
    public void IsVisibleTest() throws Exception
    {
        {
            final String textBlockJson = "{\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            TextBlock textBlock = TestUtil.createMockTextBlock("Test");
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(true, parsedTextBlock.GetIsVisible());

            textBlock = TestUtil.createMockTextBlock("Test");
            textBlock.SetIsVisible(true);
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(true, parsedTextBlock.GetIsVisible());
        }

        {
            final String textBlockJson = "{\"isVisible\":false,\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            TextBlock textBlock = TestUtil.createMockTextBlock("Test");
            textBlock.SetIsVisible(false);
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(false, parsedTextBlock.GetIsVisible());
        }
    }

    @Test
    public void SeparatorTest() throws Exception
    {
        {
            final String textBlockJson = "{\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            TextBlock textBlock = TestUtil.createMockTextBlock("Test");
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(false, parsedTextBlock.GetSeparator());

            textBlock = TestUtil.createMockTextBlock("Test");
            textBlock.SetSeparator(false);
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(false, parsedTextBlock.GetSeparator());
        }

        {
            final String textBlockJson = "{\"separator\":true,\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            TextBlock textBlock = TestUtil.createMockTextBlock("Test");
            textBlock.SetSeparator(true);
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(true, parsedTextBlock.GetSeparator());
        }
    }

    @Test
    public void SpacingTest() throws Exception
    {

        {
            final String textBlockJson = "{\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            TextBlock textBlock = TestUtil.createMockTextBlock("Test");
            Assert.assertEquals(textBlockJson, textBlock.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(textBlockJson), "1.0");
            TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(Spacing.Default, parsedTextBlock.GetSpacing());
        }

        {
            final String textBlockJson = "{\"text\":\"Test\",\"type\":\"TextBlock\"}\n";
            final String textBlockSpacingJson = "{\"spacing\":\"%s\",\"text\":\"Test\",\"type\":\"TextBlock\"}\n";

            ArrayList<Pair<Spacing, String>> tests = new ArrayList<>();
            tests.add(new Pair<>(Spacing.Default, textBlockJson));
            tests.add(new Pair<>(Spacing.None, String.format(textBlockSpacingJson, "none")));
            tests.add(new Pair<>(Spacing.Small, String.format(textBlockSpacingJson, "small")));
            tests.add(new Pair<>(Spacing.Medium, String.format(textBlockSpacingJson, "medium")));
            tests.add(new Pair<>(Spacing.Large, String.format(textBlockSpacingJson, "large")));
            tests.add(new Pair<>(Spacing.ExtraLarge, String.format(textBlockSpacingJson, "extraLarge")));
            tests.add(new Pair<>(Spacing.Padding, String.format(textBlockSpacingJson, "padding")));

            for (Pair<Spacing, String> testTuple : tests)
            {
                TextBlock textBlock = TestUtil.createMockTextBlock("Test");
                textBlock.SetSpacing(testTuple.first);
                Assert.assertEquals(testTuple.second, textBlock.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
                TextBlock parsedTextBlock = TestUtil.castToTextBlock(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(testTuple.first, parsedTextBlock.GetSpacing());
            }
        }

    }

}
