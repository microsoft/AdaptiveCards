package io.adaptivecards.objectmodel;

import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;

import java.util.ArrayList;

public class ImagePropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {
        final String ImageNoDefaultValuesExplicitSize =
            "{\"altText\":\"altText\"," +
            "\"backgroundColor\":\"#FF128192\"," +
            "\"height\":\"50px\"," +
            "\"horizontalAlignment\":\"center\"," +
            "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
            "\"style\":\"person\"," +
            "\"type\":\"Image\"," +
            "\"url\":\"http://\"," +
            "\"width\":\"50px\"}\n";

        Image image = TestUtil.createMockImage();

        image.SetAltText("altText");
        image.SetBackgroundColor("#FF128192");
        image.SetHorizontalAlignment(HorizontalAlignment.Center);
        image.SetImageStyle(ImageStyle.Person);
        image.SetPixelHeight(50);
        image.SetPixelWidth(50);
        image.SetSelectAction(TestUtil.createSampleSubmitAction());

        Assert.assertEquals(ImageNoDefaultValuesExplicitSize, image.Serialize());

        final String ImageNoDefaultValuesNonExplicitSize =
            "{\"altText\":\"altText\"," +
                "\"backgroundColor\":\"#FF128192\"," +
                "\"horizontalAlignment\":\"center\"," +
                "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                "\"size\":\"Medium\"," +
                "\"style\":\"person\"," +
                "\"type\":\"Image\"," +
                "\"url\":\"http://\"}\n";

        image = TestUtil.createMockImage();

        image.SetAltText("altText");
        image.SetBackgroundColor("#FF128192");
        image.SetHorizontalAlignment(HorizontalAlignment.Center);
        image.SetImageSize(ImageSize.Medium);
        image.SetImageStyle(ImageStyle.Person);
        image.SetSelectAction(TestUtil.createSampleSubmitAction());

        Assert.assertEquals(ImageNoDefaultValuesNonExplicitSize, image.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest()
    {
        {
            final String ImageNoDefaultValuesExplicitSize =
                "{\"altText\":\"altText\"," +
                    "\"backgroundColor\":\"#FF128192\"," +
                    "\"fallback\":{\"text\":\"Sample Text\",\"type\":\"TextBlock\"}," +
                    "\"height\":\"50px\"," +
                    "\"horizontalAlignment\":\"center\"," +
                    "\"id\":\"Sample id\"," +
                    "\"isVisible\":false," +
                    "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                    "\"separator\":true," +
                    "\"spacing\":\"medium\"," +
                    "\"style\":\"person\"," +
                    "\"type\":\"Image\"," +
                    "\"url\":\"http://\"," +
                    "\"width\":\"50px\"}\n";

            Image image = TestUtil.createMockImage();

            image.SetAltText("altText");
            image.SetBackgroundColor("#FF128192");
            image.SetFallbackType(FallbackType.Content);
            image.SetFallbackContent(TestUtil.createMockTextBlock("Sample Text"));
            image.SetHeight(HeightType.Stretch);
            image.SetHorizontalAlignment(HorizontalAlignment.Center);
            image.SetId("Sample id");
            image.SetIsVisible(false);
            image.SetImageStyle(ImageStyle.Person);
            image.SetPixelHeight(50);
            image.SetPixelWidth(50);
            image.SetSeparator(true);
            image.SetSpacing(Spacing.Medium);
            image.SetSelectAction(TestUtil.createSampleSubmitAction());

            Assert.assertEquals(ImageNoDefaultValuesExplicitSize, image.Serialize());
        }

        {
            final String ImageNoDefaultValuesExplicitSize =
                "{\"altText\":\"altText\"," +
                    "\"backgroundColor\":\"#FF128192\"," +
                    "\"fallback\":{\"text\":\"Sample Text\",\"type\":\"TextBlock\"}," +
                    "\"height\":\"Stretch\"," +
                    "\"horizontalAlignment\":\"center\"," +
                    "\"id\":\"Sample id\"," +
                    "\"isVisible\":false," +
                    "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                    "\"separator\":true," +
                    "\"spacing\":\"medium\"," +
                    "\"style\":\"person\"," +
                    "\"type\":\"Image\"," +
                    "\"url\":\"http://\"," +
                    "\"width\":\"50px\"}\n";

            Image image = TestUtil.createMockImage();

            image.SetAltText("altText");
            image.SetBackgroundColor("#FF128192");
            image.SetFallbackType(FallbackType.Content);
            image.SetFallbackContent(TestUtil.createMockTextBlock("Sample Text"));
            image.SetHorizontalAlignment(HorizontalAlignment.Center);
            image.SetId("Sample id");
            image.SetIsVisible(false);
            image.SetImageStyle(ImageStyle.Person);
            image.SetPixelWidth(50);
            image.SetHeight(HeightType.Stretch);
            image.SetSeparator(true);
            image.SetSpacing(Spacing.Medium);
            image.SetSelectAction(TestUtil.createSampleSubmitAction());

            Assert.assertEquals(ImageNoDefaultValuesExplicitSize, image.Serialize());
        }

        {
            final String ImageNoDefaultValuesNonExplicitSize =
                "{\"altText\":\"altText\"," +
                    "\"backgroundColor\":\"#FF128192\"," +
                    "\"fallback\":{\"text\":\"Sample Text\",\"type\":\"TextBlock\"}," +
                    "\"height\":\"Stretch\"," +
                    "\"horizontalAlignment\":\"center\"," +
                    "\"id\":\"Sample id\"," +
                    "\"isVisible\":false," +
                    "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                    "\"separator\":true," +
                    "\"size\":\"Medium\"," +
                    "\"spacing\":\"medium\"," +
                    "\"style\":\"person\"," +
                    "\"type\":\"Image\"," +
                    "\"url\":\"http://\"}\n";

            Image image = TestUtil.createMockImage();

            image.SetAltText("altText");
            image.SetBackgroundColor("#FF128192");
            image.SetHorizontalAlignment(HorizontalAlignment.Center);
            image.SetFallbackType(FallbackType.Content);
            image.SetFallbackContent(TestUtil.createMockTextBlock("Sample Text"));
            image.SetHeight(HeightType.Stretch);
            image.SetId("Sample id");
            image.SetImageSize(ImageSize.Medium);
            image.SetImageStyle(ImageStyle.Person);
            image.SetIsVisible(false);
            image.SetSelectAction(TestUtil.createSampleSubmitAction());
            image.SetSeparator(true);
            image.SetSpacing(Spacing.Medium);

            Assert.assertEquals(ImageNoDefaultValuesNonExplicitSize, image.Serialize());
        }
    }

    @Test
    public void AltTextTest() throws Exception
    {
        final String imageAltText = "{\"altText\":\"Alternative Text\",\"type\":\"Image\",\"url\":\"http://\"}\n";

        Image image = TestUtil.createMockImage();

        image.SetAltText("");
        Assert.assertEquals(s_defaultImage, image.Serialize());

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(s_defaultImage), "1.0");
        Image parsedImage = TestUtil.castToImage(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals("", parsedImage.GetAltText());

        image.SetAltText("Alternative Text");
        Assert.assertEquals(imageAltText, image.Serialize());

        result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(imageAltText), "1.0");
        parsedImage = TestUtil.castToImage(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals("Alternative Text", parsedImage.GetAltText());
    }

    @Test
    public void BackgroundColorTest() throws Exception
    {
        Image image = TestUtil.createMockImage();
        image.SetBackgroundColor("");

        Assert.assertEquals(s_defaultImage, image.Serialize());

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(s_defaultImage), "1.0");
        Image parsedImage = TestUtil.castToImage(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals("", parsedImage.GetBackgroundColor());

        final String imageBackgroundColor = "{\"backgroundColor\":\"%s\",\"type\":\"Image\",\"url\":\"http://\"}\n";
        ArrayList<Pair<String, String>> tests = new ArrayList<>();
        tests.add(new Pair<>("#128192", "#FF128192"));
        tests.add(new Pair<>("#abc123", "#FFabc123"));
        tests.add(new Pair<>("#ABC123", "#FFABC123"));
        tests.add(new Pair<>("RANDOMstring", "#00000000"));

        for(int i = 0; i < tests.size(); ++i)
        {
            final String inputColor = tests.get(i).first, expectedOutputColor = tests.get(i).second;
            final String expectedJson = String.format(imageBackgroundColor, inputColor);

            image.SetBackgroundColor(inputColor);
            Assert.assertEquals(expectedJson, image.Serialize());

            final String imagePayload = String.format(imageBackgroundColor, inputColor);
            result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(imagePayload), "1.0");
            parsedImage = TestUtil.castToImage(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(expectedOutputColor, parsedImage.GetBackgroundColor());
        }
    }

    @Test
    public void HorizontalAlignmentTest() throws Exception
    {
        final String imageCenterAlignment = "{\"horizontalAlignment\":\"center\",\"type\":\"Image\",\"url\":\"http://\"}\n";
        final String imageRightAlignment = "{\"horizontalAlignment\":\"right\",\"type\":\"Image\",\"url\":\"http://\"}\n";

        ArrayList<Pair<HorizontalAlignment, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(HorizontalAlignment.Left, s_defaultImage));
        tests.add(new Pair<>(HorizontalAlignment.Center, imageCenterAlignment));
        tests.add(new Pair<>(HorizontalAlignment.Right, imageRightAlignment));

        for (Pair<HorizontalAlignment, String> testTuple : tests)
        {
            Image image = TestUtil.createMockImage();

            image.SetHorizontalAlignment(testTuple.first);
            Assert.assertEquals(testTuple.second, image.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            Image parsedImage = TestUtil.castToImage(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first, parsedImage.GetHorizontalAlignment());
        }
    }

    @Test
    public void ImageSizeTest() throws Exception
    {
        final String imageSizeAuto = "{\"size\":\"Auto\",\"type\":\"Image\",\"url\":\"http://\"}\n";
        final String imageSizeStretch = "{\"size\":\"Stretch\",\"type\":\"Image\",\"url\":\"http://\"}\n";
        final String imageSizeSmall = "{\"size\":\"Small\",\"type\":\"Image\",\"url\":\"http://\"}\n";
        final String imageSizeMedium = "{\"size\":\"Medium\",\"type\":\"Image\",\"url\":\"http://\"}\n";
        final String imageSizeLarge = "{\"size\":\"Large\",\"type\":\"Image\",\"url\":\"http://\"}\n";

        ArrayList<Pair<ImageSize, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(ImageSize.None, s_defaultImage));
        tests.add(new Pair<>(ImageSize.Auto, imageSizeAuto));
        tests.add(new Pair<>(ImageSize.Stretch, imageSizeStretch));
        tests.add(new Pair<>(ImageSize.Small, imageSizeSmall));
        tests.add(new Pair<>(ImageSize.Medium, imageSizeMedium));
        tests.add(new Pair<>(ImageSize.Large, imageSizeLarge));

        for (Pair<ImageSize, String> testTuple : tests)
        {
            Image image = TestUtil.createMockImage();
            image.SetImageSize(testTuple.first);

            Assert.assertEquals(testTuple.second, image.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            Image parsedImage = TestUtil.castToImage(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first, parsedImage.GetImageSize());
        }
    }

    @Test
    public void ImageStyleTest() throws Exception
    {
        final String imageStylePerson = "{\"style\":\"person\",\"type\":\"Image\",\"url\":\"http://\"}\n";

        ArrayList<Pair<ImageStyle, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(ImageStyle.Default, s_defaultImage));
        tests.add(new Pair<>(ImageStyle.Person, imageStylePerson));

        for (Pair<ImageStyle, String> testTuple : tests)
        {
            Image image = TestUtil.createMockImage();
            image.SetImageStyle(testTuple.first);

            Assert.assertEquals(testTuple.second, image.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            Image parsedImage = TestUtil.castToImage(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first, parsedImage.GetImageStyle());
        }
    }

    @Test
    public void ImagePixelSizeTest() throws Exception
    {
        final String imageStylePerson = "{%s\"type\":\"Image\",\"url\":\"http://\"%s}\n";

        int pixelSize[] = {0, 25, 100};

        for (int i = 0; i < pixelSize.length; ++i)
        {
            for (int j = 0; j < pixelSize.length; ++j)
            {
                int width = pixelSize[i], height = pixelSize[j];
                final String heightJson = "\"height\":\"%dpx\",";
                final String widthJson = ",\"width\":\"%dpx\"";

                Image image = TestUtil.createMockImage();
                image.SetPixelWidth(width);
                image.SetPixelHeight(height);

                String expectedHeight = "";
                if (height != 0)
                {
                    expectedHeight = String.format(heightJson, height);
                }

                String expectedWidth = "";
                if (width != 0)
                {
                    expectedWidth = String.format(widthJson, width);
                }

                String expectedJson = String.format(imageStylePerson, expectedHeight, expectedWidth);

                Assert.assertEquals(expectedJson, image.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(expectedJson), "1.0");
                Image parsedImage = TestUtil.castToImage(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(pixelSize[i], parsedImage.GetPixelWidth());
                Assert.assertEquals(pixelSize[j], parsedImage.GetPixelHeight());
            }
        }
    }

    @Test
    public void ImageSelectActionSubmit() throws Exception
    {
        final String imageSelectActionSubmit = "{\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"},\"type\":\"Image\",\"url\":\"http://\"}\n";

        Image image = TestUtil.createMockImage();
        image.SetSelectAction(TestUtil.createSampleSubmitAction());

        Assert.assertEquals(imageSelectActionSubmit, image.Serialize());

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(imageSelectActionSubmit), "1.0");
        Image parsedImage = TestUtil.castToImage(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals("{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}\n", parsedImage.GetSelectAction().Serialize());
    }

    @Test
    public void ImageSelectActionOpenUrl() throws Exception
    {
        final String imageSelectActionOpenUrl = "{\"selectAction\":{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"},\"type\":\"Image\",\"url\":\"http://\"}\n";

        Image image = TestUtil.createMockImage();
        image.SetSelectAction(TestUtil.createSampleOpenUrlAction());

        Assert.assertEquals(imageSelectActionOpenUrl, image.Serialize());

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(imageSelectActionOpenUrl), "1.0");
        Image parsedImage = TestUtil.castToImage(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals("{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n", parsedImage.GetSelectAction().Serialize());
    }

    @Test
    public void ImageSelectActionToggleVisibility() throws Exception
    {
        final String imageSelectActionToggleVisibility =
            "{\"selectAction\":{\"targetElements\":[\"id1\",{\"elementId\":\"id2\",\"isVisible\":true}," +
            "{\"elementId\":\"id3\",\"isVisible\":false}],\"type\":\"Action.ToggleVisibility\"},\"type\":\"Image\",\"url\":\"http://\"}\n";

        Image image = TestUtil.createMockImage();
        image.SetSelectAction(TestUtil.createSampleToggleVisibilityAction());

        Assert.assertEquals(imageSelectActionToggleVisibility, image.Serialize());

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(imageSelectActionToggleVisibility), "1.0");
        Image parsedImage = TestUtil.castToImage(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals("{\"targetElements\":[\"id1\",{\"elementId\":\"id2\",\"isVisible\":true}," +
            "{\"elementId\":\"id3\",\"isVisible\":false}],\"type\":\"Action.ToggleVisibility\"}\n", parsedImage.GetSelectAction().Serialize());
    }

    // This string is the result for an empty image or an image with all default values
    // The url property can't be left empty otherwise a exception is thrown
    public static final String s_defaultImage = "{\"type\":\"Image\",\"url\":\"http://\"}\n";

}
