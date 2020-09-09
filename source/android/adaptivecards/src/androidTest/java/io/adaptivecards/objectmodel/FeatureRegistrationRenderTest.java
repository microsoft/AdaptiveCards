package io.adaptivecards.objectmodel;

import android.content.Context;
<<<<<<< HEAD
import android.support.test.InstrumentationRegistry;
import android.widget.LinearLayout;

import junit.framework.Assert;
=======
import androidx.test.platform.app.InstrumentationRegistry;
>>>>>>> origin/golddove/androidx

import org.junit.Test;

import io.adaptivecards.renderer.AdaptiveCardRenderer;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class FeatureRegistrationRenderTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void TestDefaultRendering() throws Exception
    {
        final String cardJson  =
            "{\"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\"," +
                "\"type\": \"AdaptiveCard\"," +
                "\"version\": \"1.0\"," +
                "\"body\": [{\"type\": \"TextBlock\",\"text\": \"This is some text\"}]" +
            "}";

        HostConfig hostConfig = new HostConfig();

        ParseContext parseContext = new ParseContext();
        ParseResult parseResult = AdaptiveCard.DeserializeFromString(cardJson, AdaptiveCardRenderer.VERSION, parseContext);
        Context context = InstrumentationRegistry.getTargetContext();
        AdaptiveCardRenderer.getInstance().render(context, null, parseResult.GetAdaptiveCard(), null, hostConfig);
    }

    @Test
    public void TestFeatureRegistrationRendering() throws Exception
    {
        final String cardJson  =
            "{\"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\"," +
                "\"type\": \"AdaptiveCard\"," +
                "\"version\": \"1.0\"," +
                "\"body\": [{\"type\": \"TextBlock\",\"text\": \"This is some text\"}]" +
                "}";

        HostConfig hostConfig = new HostConfig();

        ParseContext parseContext = new ParseContext();
        ParseResult parseResult = AdaptiveCard.DeserializeFromString(cardJson, AdaptiveCardRenderer.VERSION, parseContext);
        Context context = InstrumentationRegistry.getTargetContext();

        FeatureRegistration featureRegistration = new FeatureRegistration();
        featureRegistration.AddFeature("featureName", "1.0");
        CardRendererRegistration.getInstance().registerFeatureRegistration(featureRegistration);

        AdaptiveCardRenderer.getInstance().render(context, null, parseResult.GetAdaptiveCard(), null, hostConfig);
    }

}
