package io.adaptivecards.objectmodel;

import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;

import java.util.ArrayList;

public class ImageSetPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest() throws Exception
    {
        final String imageSetNoDefaultValuesJson =
            "{\"imageSize\":\"Medium\"," +
                "\"images\":[" +
                "{\"altText\":\"altText\"," +
                    "\"backgroundColor\":\"#FF128192\"," +
                    "\"height\":\"50px\"," +
                    "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                    "\"style\":\"person\"," +
                    "\"type\":\"Image\"," +
                    "\"url\":\"http://\"," +
                    "\"width\":\"50px\"}," +
                "{\"horizontalAlignment\":\"center\"," +
                    "\"selectAction\":{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}," +
                    "\"size\":\"Small\"," +
                    "\"type\":\"Image\"," +
                    "\"url\":\"http://\"}," +
                "{\"horizontalAlignment\":\"right\"," +
                    "\"selectAction\":{\"targetElements\":[" +
                        "\"id1\",{\"elementId\":\"id2\",\"isVisible\":true},{\"elementId\":\"id3\",\"isVisible\":false}]," +
                        "\"type\":\"Action.ToggleVisibility\"}," +
                    "\"size\":\"Large\"," +
                    "\"style\":\"person\"," +
                    "\"type\":\"Image\"," +
                    "\"url\":\"http://\"}]," +
                "\"type\":\"ImageSet\"}\n";

        {
            Image imageExplicitSize = TestUtil.createMockImage();
            imageExplicitSize.SetAltText("altText");
            imageExplicitSize.SetBackgroundColor("#FF128192");
            imageExplicitSize.SetHorizontalAlignment(HorizontalAlignment.Left);
            imageExplicitSize.SetImageStyle(ImageStyle.Person);
            imageExplicitSize.SetPixelHeight(50);
            imageExplicitSize.SetPixelWidth(50);
            imageExplicitSize.SetSelectAction(TestUtil.createSampleSubmitAction());

            Image imageSmall = TestUtil.createMockImage();
            imageSmall.SetHorizontalAlignment(HorizontalAlignment.Center);
            imageSmall.SetImageSize(ImageSize.Small);
            imageSmall.SetSelectAction(TestUtil.createSampleOpenUrlAction());

            Image imageLarge = TestUtil.createMockImage();
            imageLarge.SetHorizontalAlignment(HorizontalAlignment.Right);
            imageLarge.SetImageSize(ImageSize.Large);
            imageLarge.SetImageStyle(ImageStyle.Person);
            imageLarge.SetSelectAction(TestUtil.createSampleToggleVisibilityAction());

            ImageSet imageSet = TestUtil.createMockImageSet(imageExplicitSize, imageSmall, imageLarge);
            imageSet.SetImageSize(ImageSize.Medium);

            Assert.assertEquals(imageSetNoDefaultValuesJson, imageSet.Serialize());
        }

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(imageSetNoDefaultValuesJson), "1.0");
        ImageSet parsedImageSet = TestUtil.castToImageSet(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(ImageSize.Medium, parsedImageSet.GetImageSize());
        Assert.assertEquals(3, parsedImageSet.GetImages().size());

        {
            Image parsedExplicitSizeImage = TestUtil.castToImage(parsedImageSet.GetImages().get(0));
            Assert.assertEquals("altText", parsedExplicitSizeImage.GetAltText());
            Assert.assertEquals("#FF128192", parsedExplicitSizeImage.GetBackgroundColor());
            Assert.assertEquals(HorizontalAlignment.Left, parsedExplicitSizeImage.GetHorizontalAlignment());
            Assert.assertEquals(ImageStyle.Person, parsedExplicitSizeImage.GetImageStyle());
            Assert.assertEquals(50, parsedExplicitSizeImage.GetPixelHeight());
            Assert.assertEquals(50, parsedExplicitSizeImage.GetPixelWidth());

            SubmitAction submitAction = TestUtil.castToSubmitAction(parsedExplicitSizeImage.GetSelectAction());
            Assert.assertEquals("{\"data\":\"Some data\"}\n", submitAction.GetDataJson());
        }

        {
            Image parsedSmallSizeImage = TestUtil.castToImage(parsedImageSet.GetImages().get(1));
            Assert.assertEquals(HorizontalAlignment.Center, parsedSmallSizeImage.GetHorizontalAlignment());
            Assert.assertEquals(ImageSize.Small, parsedSmallSizeImage.GetImageSize());

            OpenUrlAction openUrlAction = TestUtil.castToOpenUrlAction(parsedSmallSizeImage.GetSelectAction());
            Assert.assertEquals("http://", openUrlAction.GetUrl());
        }

        {
            Image parsedLargeSizeImage = TestUtil.castToImage(parsedImageSet.GetImages().get(2));
            Assert.assertEquals(HorizontalAlignment.Right, parsedLargeSizeImage.GetHorizontalAlignment());
            Assert.assertEquals(ImageStyle.Person, parsedLargeSizeImage.GetImageStyle());
            Assert.assertEquals(ImageSize.Large, parsedLargeSizeImage.GetImageSize());

            ToggleVisibilityAction toggleVisibilityAction = TestUtil.castToToggleVisibilityAction(parsedLargeSizeImage.GetSelectAction());

            {
                ToggleVisibilityTarget toggleTarget = toggleVisibilityAction.GetTargetElements().get(0);
                Assert.assertEquals("id1", toggleTarget.GetElementId());
                Assert.assertEquals(IsVisible.IsVisibleToggle, toggleTarget.GetIsVisible());
            }

            {
                ToggleVisibilityTarget toggleTarget = toggleVisibilityAction.GetTargetElements().get(1);
                Assert.assertEquals("id2", toggleTarget.GetElementId());
                Assert.assertEquals(IsVisible.IsVisibleTrue, toggleTarget.GetIsVisible());
            }

            {
                ToggleVisibilityTarget toggleTarget = toggleVisibilityAction.GetTargetElements().get(2);
                Assert.assertEquals("id3", toggleTarget.GetElementId());
                Assert.assertEquals(IsVisible.IsVisibleFalse, toggleTarget.GetIsVisible());
            }
        }
    }

    @Test
    public void AllPropertiesWithInheritedTest() throws Exception
    {
        final String imageSetNoDefaultValuesJson =
            "{\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"Sample id\"," +
                "\"imageSize\":\"Medium\"," +
                "\"images\":[" +
                "{\"altText\":\"altText\"," +
                "\"backgroundColor\":\"#FF128192\"," +
                "\"height\":\"50px\"," +
                "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                "\"style\":\"person\"," +
                "\"type\":\"Image\"," +
                "\"url\":\"http://\"," +
                "\"width\":\"50px\"}," +
                "{\"horizontalAlignment\":\"center\"," +
                "\"selectAction\":{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}," +
                "\"size\":\"Small\"," +
                "\"type\":\"Image\"," +
                "\"url\":\"http://\"}," +
                "{\"horizontalAlignment\":\"right\"," +
                "\"selectAction\":{\"targetElements\":[" +
                "\"id1\",{\"elementId\":\"id2\",\"isVisible\":true},{\"elementId\":\"id3\",\"isVisible\":false}]," +
                "\"type\":\"Action.ToggleVisibility\"}," +
                "\"size\":\"Large\"," +
                "\"style\":\"person\"," +
                "\"type\":\"Image\"," +
                "\"url\":\"http://\"}]," +
                "\"isVisible\":false," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"type\":\"ImageSet\"}\n";

        {
            Image imageExplicitSize = TestUtil.createMockImage();
            imageExplicitSize.SetAltText("altText");
            imageExplicitSize.SetBackgroundColor("#FF128192");
            imageExplicitSize.SetHorizontalAlignment(HorizontalAlignment.Left);
            imageExplicitSize.SetImageStyle(ImageStyle.Person);
            imageExplicitSize.SetPixelHeight(50);
            imageExplicitSize.SetPixelWidth(50);
            imageExplicitSize.SetSelectAction(TestUtil.createSampleSubmitAction());

            Image imageSmall = TestUtil.createMockImage();
            imageSmall.SetHorizontalAlignment(HorizontalAlignment.Center);
            imageSmall.SetImageSize(ImageSize.Small);
            imageSmall.SetSelectAction(TestUtil.createSampleOpenUrlAction());

            Image imageLarge = TestUtil.createMockImage();
            imageLarge.SetHorizontalAlignment(HorizontalAlignment.Right);
            imageLarge.SetImageSize(ImageSize.Large);
            imageLarge.SetImageStyle(ImageStyle.Person);
            imageLarge.SetSelectAction(TestUtil.createSampleToggleVisibilityAction());

            ImageSet imageSet = TestUtil.createMockImageSet(imageExplicitSize, imageSmall, imageLarge);
            imageSet.SetFallbackType(FallbackType.Content);
            imageSet.SetFallbackContent(TestUtil.createMockImage());
            imageSet.SetHeight(HeightType.Stretch);
            imageSet.SetId("Sample id");
            imageSet.SetImageSize(ImageSize.Medium);
            imageSet.SetIsVisible(false);
            imageSet.SetSeparator(true);
            imageSet.SetSpacing(Spacing.Medium);

            Assert.assertEquals(imageSetNoDefaultValuesJson, imageSet.Serialize());
        }

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(imageSetNoDefaultValuesJson), "1.0");
        ImageSet parsedImageSet = TestUtil.castToImageSet(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(ImageSize.Medium, parsedImageSet.GetImageSize());
        Assert.assertEquals(3, parsedImageSet.GetImages().size());

        {
            Image parsedExplicitSizeImage = TestUtil.castToImage(parsedImageSet.GetImages().get(0));
            Assert.assertEquals("altText", parsedExplicitSizeImage.GetAltText());
            Assert.assertEquals("#FF128192", parsedExplicitSizeImage.GetBackgroundColor());
            Assert.assertEquals(HorizontalAlignment.Left, parsedExplicitSizeImage.GetHorizontalAlignment());
            Assert.assertEquals(ImageStyle.Person, parsedExplicitSizeImage.GetImageStyle());
            Assert.assertEquals(50, parsedExplicitSizeImage.GetPixelHeight());
            Assert.assertEquals(50, parsedExplicitSizeImage.GetPixelWidth());

            SubmitAction submitAction = TestUtil.castToSubmitAction(parsedExplicitSizeImage.GetSelectAction());
            Assert.assertEquals("{\"data\":\"Some data\"}\n", submitAction.GetDataJson());
        }

        {
            Image parsedSmallSizeImage = TestUtil.castToImage(parsedImageSet.GetImages().get(1));
            Assert.assertEquals(HorizontalAlignment.Center, parsedSmallSizeImage.GetHorizontalAlignment());
            Assert.assertEquals(ImageSize.Small, parsedSmallSizeImage.GetImageSize());

            OpenUrlAction openUrlAction = TestUtil.castToOpenUrlAction(parsedSmallSizeImage.GetSelectAction());
            Assert.assertEquals("http://", openUrlAction.GetUrl());
        }

        {
            Image parsedLargeSizeImage = TestUtil.castToImage(parsedImageSet.GetImages().get(2));
            Assert.assertEquals(HorizontalAlignment.Right, parsedLargeSizeImage.GetHorizontalAlignment());
            Assert.assertEquals(ImageStyle.Person, parsedLargeSizeImage.GetImageStyle());
            Assert.assertEquals(ImageSize.Large, parsedLargeSizeImage.GetImageSize());

            ToggleVisibilityAction toggleVisibilityAction = TestUtil.castToToggleVisibilityAction(parsedLargeSizeImage.GetSelectAction());

            {
                ToggleVisibilityTarget toggleTarget = toggleVisibilityAction.GetTargetElements().get(0);
                Assert.assertEquals("id1", toggleTarget.GetElementId());
                Assert.assertEquals(IsVisible.IsVisibleToggle, toggleTarget.GetIsVisible());
            }

            {
                ToggleVisibilityTarget toggleTarget = toggleVisibilityAction.GetTargetElements().get(1);
                Assert.assertEquals("id2", toggleTarget.GetElementId());
                Assert.assertEquals(IsVisible.IsVisibleTrue, toggleTarget.GetIsVisible());
            }

            {
                ToggleVisibilityTarget toggleTarget = toggleVisibilityAction.GetTargetElements().get(2);
                Assert.assertEquals("id3", toggleTarget.GetElementId());
                Assert.assertEquals(IsVisible.IsVisibleFalse, toggleTarget.GetIsVisible());
            }
        }
    }

    @Test
    public void ImageSizeTest() throws Exception
    {
        final String imageSetImageSize =
            "{\"imageSize\":\"%s\"," +
                "\"images\":[" +
                "{\"type\":\"Image\",\"url\":\"http://\"}," +
                "{\"type\":\"Image\",\"url\":\"http://\"}," +
                "{\"type\":\"Image\",\"url\":\"http://\"}]," +
                "\"type\":\"ImageSet\"}\n";

        Image image = TestUtil.createMockImage();
        ImageSet imageSet = TestUtil.createMockImageSet(image, image, image);

        ArrayList<Pair<ImageSize, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(ImageSize.None, s_defaultImageSet));
        tests.add(new Pair<>(ImageSize.Auto, String.format(imageSetImageSize, "Auto")));
        tests.add(new Pair<>(ImageSize.Stretch, String.format(imageSetImageSize, "Stretch")));
        tests.add(new Pair<>(ImageSize.Small, String.format(imageSetImageSize, "Small")));
        tests.add(new Pair<>(ImageSize.Medium, String.format(imageSetImageSize, "Medium")));
        tests.add(new Pair<>(ImageSize.Large, String.format(imageSetImageSize, "Large")));

        for (Pair<ImageSize, String> testTuple : tests)
        {
            imageSet.SetImageSize(testTuple.first);

            Assert.assertEquals(testTuple.second, imageSet.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            ImageSet parsedImage = TestUtil.castToImageSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first, parsedImage.GetImageSize());
        }
    }

    private static final String s_defaultImageSet =
        "{\"images\":[{\"type\":\"Image\",\"url\":\"http://\"}," +
            "{\"type\":\"Image\",\"url\":\"http://\"}," +
            "{\"type\":\"Image\",\"url\":\"http://\"}]," +
            "\"type\":\"ImageSet\"}\n";

}
