package io.adaptivecards.objectmodel;

import android.content.Context;
import android.support.test.InstrumentationRegistry;

import junit.framework.Assert;

import org.junit.Test;

import io.adaptivecards.renderer.AdaptiveCardRenderer;

public class APITest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void TestGetResourceInformationAPI() throws Exception
    {
        final String cardJson =
            "{" +
                "\"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\"," +
                "\"type\": \"AdaptiveCard\",\"version\": \"1.2\",\"backgroundImage\": {" +
                "\"url\": \"https://picsum.photos/id/237/200/200\", \"verticalAlignment\": \"center\"," +
                "\"horizontalAlignment\": \"center\"},\"body\": [{\"type\": \"Media\"," +
                "\"poster\": \"https://adaptivecards.io/content/poster-video.png\",\"sources\": [{" +
                "\"mimeType\": \"video/mp4\",\"url\": \"https://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp4\"" +
                "}]},{\"type\": \"Media\",\"poster\": \"https://adaptivecards.io/content/poster-audio.jpg\"," +
                "\"sources\": [{\"mimeType\": \"audio/mpeg\",\"url\": \"https://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp3\"" +
                "}]},{\"type\": \"ImageSet\",\"imageSize\": \"medium\",\"images\": [{\"type\": \"Image\"," +
                "\"url\": \"https://picsum.photos/200/200?image=100\"},{\"type\": \"Image\"," +
                "\"url\": \"https://picsum.photos/300/200?image=200\"},{\"type\": \"Image\"," +
                "\"url\": \"https://picsum.photos/300/200?image=301\"},{\"type\": \"Image\"," +
                "\"url\": \"https://picsum.photos/200/200?image=400\"},{\"type\": \"Image\"," +
                "\"url\": \"https://picsum.photos/300/200?image=500\"},{\"type\": \"Image\"," +
                "\"url\": \"https://picsum.photos/200/200?image=600\"},{\"type\": \"Image\"," +
                "\"url\": \"https://picsum.photos/300/200?image=700\"},{\"type\": \"Image\"," +
                "\"url\": \"https://picsum.photos/300/200?image=800\"},{\"type\": \"Image\"," +
                "\"url\": \"https://picsum.photos/300/200?image=900\"}]}],\"actions\": [{" +
                "\"type\": \"Action.OpenUrl\",\"iconUrl\": \"http://adaptivecards.io/content/cats/1.png\"," +
                "\"url\": \"http://adaptivecards.io\",\"title\": \"With Icon\"}]}";

        ParseContext parseContext = new ParseContext();
        ParseResult parseResult = AdaptiveCard.DeserializeFromString(cardJson, AdaptiveCardRenderer.VERSION, parseContext);

        RemoteResourceInformationVector resourceInformationVector = parseResult.GetAdaptiveCard().GetResourceInformation();

        for (RemoteResourceInformation resourceInformation : resourceInformationVector)
        {
            Assert.assertEquals("", );
        }
    }

}

