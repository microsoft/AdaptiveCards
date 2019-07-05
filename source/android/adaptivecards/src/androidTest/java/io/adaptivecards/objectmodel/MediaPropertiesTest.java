package io.adaptivecards.objectmodel;

import org.junit.Assert;
import org.junit.Test;

public class MediaPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    public static Media cast(BaseCardElement baseCardElement)
    {
        Media media = null;

        if (baseCardElement instanceof Media)
        {
            media = (Media) baseCardElement;
        }
        else if ((media = Media.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to Media object model.");
        }

        return media;
    }

    public static Media createMockMedia()
    {
        Media media = new Media();

        MediaSource mediaSource = new MediaSource();
        mediaSource.SetUrl("http://");
        mediaSource.SetMimeType("video/mp4");
        media.GetSources().add(mediaSource);

        return media;
    }

    @Test
    public void TestMockMedia()
    {
        Assert.assertEquals(s_defaultMedia, createMockMedia().Serialize());
    }

    @Test
    public void AllPropertiesTest()
    {
        final String mediaAltText =
            "{\"altText\":\"Alternative Text\"," +
                "\"poster\":\"http://\"," +
                "\"sources\":[{\"mimeType\":\"video/mp4\",\"url\":\"http://\"}]," +
                "\"type\":\"Media\"}\n";

        Media media = createMockMedia();
        media.SetAltText("Alternative Text");
        media.SetPoster("http://");

        Assert.assertEquals(mediaAltText, media.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest() throws Exception
    {
        final String mediaNoDefaultValues =
            "{\"altText\":\"Alternative Text\"," +
                "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"Sample id\"," +
                "\"isVisible\":false," +
                "\"poster\":\"http://\"," +
                "\"separator\":true," +
                "\"sources\":[{\"mimeType\":\"video/mp4\",\"url\":\"http://\"}]," +
                "\"spacing\":\"medium\"," +
                "\"type\":\"Media\"}\n";

        Media media = createMockMedia();
        media.SetAltText("Alternative Text");
        media.SetFallbackType(FallbackType.Content);
        media.SetFallbackContent(TestUtil.createMockImage());
        media.SetHeight(HeightType.Stretch);
        media.SetId("Sample id");
        media.SetIsVisible(false);
        media.SetPoster("http://");
        media.SetSeparator(true);
        media.SetSpacing(Spacing.Medium);

        Assert.assertEquals(mediaNoDefaultValues, media.Serialize());
    }

    @Test
    public void AltTextTest() throws Exception
    {
        {
            Media media = createMockMedia();
            media.SetAltText("");
            Assert.assertEquals(s_defaultMedia, media.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(s_defaultMedia), "1.0");
            Media parsedMedia = MediaPropertiesTest.cast(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedMedia.GetAltText());
        }

        {
            final String mediaAltText = "{\"altText\":\"Alternative Text\",\"sources\":[{\"mimeType\":\"video/mp4\",\"url\":\"http://\"}],\"type\":\"Media\"}\n";

            Media media = createMockMedia();
            media.SetAltText("Alternative Text");
            Assert.assertEquals(mediaAltText, media.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(mediaAltText), "1.0");
            Media parsedMedia = MediaPropertiesTest.cast(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("Alternative Text", parsedMedia.GetAltText());
        }
    }

    @Test
    public void PosterTest() throws Exception
    {
        {
            Media media = createMockMedia();
            media.SetAltText("");
            Assert.assertEquals(s_defaultMedia, media.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(s_defaultMedia), "1.0");
            Media parsedMedia = MediaPropertiesTest.cast(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedMedia.GetAltText());
        }

        {
            final String mediaPoster = "{\"poster\":\"http://\",\"sources\":[{\"mimeType\":\"video/mp4\",\"url\":\"http://\"}],\"type\":\"Media\"}\n";

            Media media = createMockMedia();
            media.SetPoster("http://");
            Assert.assertEquals(mediaPoster, media.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(mediaPoster), "1.0");
            Media parsedMedia = MediaPropertiesTest.cast(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("http://", parsedMedia.GetPoster());
        }
    }

    private static String s_defaultMedia = "{\"sources\":[{\"mimeType\":\"video/mp4\",\"url\":\"http://\"}],\"type\":\"Media\"}\n";
}
